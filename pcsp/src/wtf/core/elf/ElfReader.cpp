#include "stdafx.h"
#include "common_base.h"
#include "ElfReader.h"

//#include "../PSP/HLE/sceKernelMemory.h"

#include "hle/modules/sysmem/sysmem.h"

#include "log.h"
#include "memory/memory.h"
#include "al/al.h"

const char *ElfReader::GetSectionName(int section)
{
	if (sections[section].sh_type == SHT_NULL)
		return 0;

	int nameOffset = sections[section].sh_name;
	char *ptr = (char*)GetSectionDataPtr(header->e_shstrndx);

	if (ptr)
		return ptr + nameOffset;
	else
		return 0;
}



void addrToHiLo(u32 addr, u16 &hi, s16 &lo)
{
	lo = (addr & 0xFFFF);
	u32 naddr = addr - lo;
	hi = naddr>>16;
	
	u32 test = (hi<<16) + lo;
	if (test != addr)
	{
		DebugBreak();
	}
}


bool ElfReader::LoadInto(u32 vaddr)
{
	Log::loader.info("String section: %i", header->e_shstrndx);

	sectionOffsets = new u32[GetNumSections()];
	sectionAddrs = new u32[GetNumSections()];
	
	// Should we relocate?
	bRelocate = (header->e_type != ET_EXEC);

	entryPoint = header->e_entry;
	if (bRelocate)
	{
		Log::loader.info("Relocatable module");
		entryPoint += vaddr;
	}
	else
	{
		Log::loader.info("Prerelocated executable");
	}

	Log::loader.info("%i segments:", header->e_phnum);

	// First pass : Get the damn bits into RAM
	u32 segmentVAddr[32];

	u32 baseAddress = bRelocate ? vaddr : 0;
	for (int i=0; i<header->e_phnum; i++)
	{
		Elf32_Phdr *p = segments + i;

		Log::loader.info( "Type: %i Vaddr: %08x Filesz: %i Memsz: %i ", p->p_type, p->p_vaddr, p->p_filesz, p->p_memsz);
		
		if (p->p_type == PT_LOAD)
		{
			segmentVAddr[i] = baseAddress + p->p_vaddr;
			u32 writeAddr = segmentVAddr[i];

			u8 *src = GetSegmentPtr(i);
			u8 *dst = Memory::addr< u8 >(writeAddr);
			u32 srcSize = p->p_filesz;
			u32 dstSize = p->p_memsz;

            SceUID mbid = sysmem::hleKernelAllocPartitionMemory(2, "ELF", 2, dstSize, writeAddr);

            if (mbid > 0)
            {
                ::memcpy(dst, src, srcSize);

                if (srcSize < dstSize)
                {
                    ::memset(dst + srcSize, 0, dstSize-srcSize); //zero out bss
                }

                Log::loader.info("Loadable Segment Copied to %08x, size %08x", writeAddr, p->p_memsz);
            }
		}
	}
	
    //hle::userMemory.ListBlocks();

	Log::loader.info("%i sections:", header->e_shnum);

	for (int i=0; i<GetNumSections(); i++)
	{
		Elf32_Shdr *s = &sections[i];
		const char *name = GetSectionName(i);
		
		u32 writeAddr = s->sh_addr + baseAddress;
		sectionOffsets[i] = writeAddr - vaddr;
		sectionAddrs[i] = writeAddr;

		if (s->sh_flags & SHF_ALLOC)
		{
			Log::loader.info("Data Section found: %s     Sitting at %08x, size %08x", name, writeAddr, s->sh_size);
	
		}
		else
		{
			Log::loader.info("NonData Section found: %s     Ignoring (size=%08x) (flags=%08x)", name, s->sh_size, s->sh_flags);
		}
	}

	Log::loader.info("Relocations:");

	// Second pass: Do necessary relocations
	for (int i=0; i<GetNumSections(); i++)
	{
		Elf32_Shdr *s = &sections[i];
		const char *name = GetSectionName(i);

		if (s->sh_type == SHT_PSPREL)
		{
			//We have a relocation table!
			//int symbolSection = s->sh_link;
			int sectionToModify = s->sh_info;

			if (!(sections[sectionToModify].sh_flags & SHF_ALLOC))
			{
				Log::loader.warn("Trying to relocate non-loaded section %s",GetSectionName(sectionToModify));
				continue;
			}
			
			int numRelocs = s->sh_size / sizeof(Elf32_Rel);

			Elf32_Rel *rels = (Elf32_Rel *)GetSectionDataPtr(i);

			Log::loader.info("%s: Performing %i relocations on %s",name,numRelocs,GetSectionName(sectionToModify));

			for (int r = 0; r < numRelocs; r++)
			{
				u32 info = rels[r].r_info;
				u32 addr = rels[r].r_offset;


				int type = info & 0xf;

				int readwrite = (info>>8) & 0xff; 
				int relative  = (info>>16) & 0xff;
				
				//0 = code
				//1 = data
				
				addr += segmentVAddr[readwrite];
				
				u32 op = Memory::memw(addr);


				const bool log = false;


				//log=true;
				if (log)
				{
					Log::loader.info("rel at: %08x  type: %08x",addr,info);
				}
				u32 relocateTo = segmentVAddr[relative];

#define R_MIPS32 2
#define R_MIPS26 4
#define R_MIPS16_HI 5
#define R_MIPS16_LO 6

				switch (type) 
				{
				case R_MIPS32:
					if (log)
						Log::loader.info("Full address reloc %08x", addr);
					//full address, no problemo
					//if (readwrite != 0)
						op += relocateTo;
					break;

				case R_MIPS26: //j, jal
					//add on to put in correct address space
					if (log)
						Log::loader.info("j/jal reloc %08x", addr);
					op = (op & 0xFC000000) | (((op&0x03FFFFFF)+(relocateTo>>2))&0x03FFFFFFF);
					break;

				case R_MIPS16_HI: //lui part of lui-addiu pairs
					{
						if (log)
							Log::loader.info("HI reloc %08x", addr);

						u32 cur = (op & 0xFFFF) << 16;
						u16 hi = 0;
						s16 lo;
						bool found = false;
						for (int t = r + 1; t<numRelocs; t++)
						{
							if ((rels[t].r_info & 0xF) == R_MIPS16_LO) 
							{
								u32 corrLoAddr = rels[t].r_offset + segmentVAddr[readwrite];
								if (log)
								{
									Log::loader.info("Corresponding lo found at %08x", corrLoAddr);
								}

								lo = Memory::mem< s16 >(corrLoAddr); //signed??
								cur += lo;
								cur += relocateTo;
								addrToHiLo(cur, hi, lo);
								found = true;
								break;
							}
						}
						if (!found)
							DebugBreak();

						op = (op & 0xFFFF0000) | (hi);
					}
					break;

				case R_MIPS16_LO: //addiu part of lui-addiu pairs
					{
						if (log)
							Log::loader.info("LO reloc %08x", addr);
						u32 cur = op & 0xFFFF;
						cur += relocateTo;
						cur &= 0xFFFF;
						op = (op & 0xFFFF0000) | cur;
					}
					break;

				case 7: //gp
					if (log)
						Log::loader.info("ARGH IT'S A GP!!!!!!!! %08x", addr);
					break;

				case 0: // another GP reloc!
					{
						char temp[256];
						//MIPSDisAsm(op, 0, temp);
						Log::loader.info("WARNING: GP reloc? @ %08x : 0 : %s", addr, temp );
					}
					break;

				default:
					Log::loader.info("ARGH IT'S A UNKNOWN RELOCATION!!!!!!!! %08x", addr);
					DebugBreak();
					break;
				}
				Memory::memw(addr) = op;
			}
		}
		else if (s->sh_type == SHT_REL)
		{
			Log::loader.info( "Traditional relocation section found.");
			if (bRelocate)
			{
				Log::loader.info( "Binary is prerelocated. Skipping relocations.");
			}
			else
			{
				//We have a relocation table!
				//int symbolSection = s->sh_link;
				int sectionToModify = s->sh_info;
				if (!(sections[sectionToModify].sh_flags & SHF_ALLOC))
				{
					Log::loader.warn("Trying to relocate non-loaded section %s, ignoring",GetSectionName(sectionToModify));
					continue;
				}
				Log::loader.error("Traditional relocations unsupported.");
			}
		}
	}

	Log::loader.info("Done.");

	return true;
}

bool ElfReader::UnLoadInto()
{
	safe_delete_array(sectionOffsets);
	safe_delete_array(sectionAddrs);
	delete this;
	return true;
}

SectionID ElfReader::GetSectionByName(const char *name, int firstSection)
{
	for (int i = firstSection; i < header->e_shnum; i++)
	{
		const char *secname = GetSectionName(i);

		if (secname != 0 && strcmp(name, secname) == 0)
		{
			return i;
		}
	}
	return -1;
}

bool ElfReader::LoadSymbols()
{
	bool hasSymbols = false;
	SectionID sec = GetSectionByName(".symtab");
	if (sec != -1)
	{
		int stringSection = sections[sec].sh_link;

		const char *stringBase = (const char*)GetSectionDataPtr(stringSection);

		//We have a symbol table!
		Elf32_Sym *symtab = (Elf32_Sym *)(GetSectionDataPtr(sec));

		int numSymbols = sections[sec].sh_size / sizeof(Elf32_Sym);
		
		for (int sym = 0; sym<numSymbols; sym++)
		{
			int size = symtab[sym].st_size;
			if (size == 0)
				continue;

			//int bind = symtab[sym].st_info >> 4;
			int type = symtab[sym].st_info & 0xF;
			int sectionIndex = symtab[sym].st_shndx;
			int value = symtab[sym].st_value;
			const char *name = stringBase + symtab[sym].st_name;

			if (bRelocate)
				value += sectionAddrs[sectionIndex];
			SymbolType symtype = ST_DATA;

			switch (type)
			{
			case STT_OBJECT:
				symtype = ST_DATA; break;
			case STT_FUNC:
				symtype = ST_FUNCTION; break;
			default:
				continue;
			}
//			Debugger::add_symbol(name, value, size, symtype);
			hasSymbols = true;
			//...
		}
	}
	return hasSymbols;
}




