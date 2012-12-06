#include "stdafx.h"
#include "elf.h"
#include "log.h"

elf::elf()
 : m_pElf(NULL)
 , m_iElfSize(0)
 , m_pElfPrograms(NULL)
 , m_iPHCount(0)
 , m_pElfSections(NULL)
 , m_iSHCount(0)
 , m_pElfStrtab(NULL)
 , m_pElfSymbols(NULL)
 , m_iSymCount(0)

{
  memset(&m_elfHeader, 0, sizeof(m_elfHeader));
}

elf::~elf()
{
  FreeMemory();
}
void elf::FreeMemory()
{
	if(m_pElfSections != NULL)
	{
		delete m_pElfSections;
		m_pElfSections = NULL;
	}

	if(m_pElfPrograms != NULL)
	{
		delete m_pElfPrograms;
		m_pElfPrograms = NULL;
	}

	if(m_pElfSymbols != NULL)
	{
		delete m_pElfSymbols;
		m_pElfSymbols = NULL;
	}

	
	m_pElfStrtab = NULL;

	if(m_pElf != NULL)
	{
		delete m_pElf;
		m_pElf = NULL;
	}
	/*m_iElfSize = 0;

	if(m_pElfBin != NULL)
	{
		delete m_pElfBin;
		m_pElfBin = NULL;
	}
	m_iBinSize = 0;

	m_blElfLoaded = false;*/
}
/** Load an ELF from a file */
bool elf::LoadFromMemory(const u8 *ptr,u32 size,u32 AddressToLoad)
{
  	bool loaded = false;
    loadAddress = AddressToLoad;
	/* Return the object to a know state */
	FreeMemory();

	m_pElf = (u8*)ptr;
	m_iElfSize=size;

	if((m_pElf != NULL) && (ElfValidateHeader() == true))
	{
		LoadPrograms();
		LoadSections();
		LoadSymbols();

	/*	if((LoadPrograms() == true) && (LoadSections() == true) && (LoadSymbols() == true) && (BuildBinaryImage() == true))
		{
			strncpy(m_szFilename, szFilename, MAXPATH-1);
			m_szFilename[MAXPATH-1] = 0;
			loaded = true;
			m_blElfLoaded = true;
		}*/
	}

	/*if(loaded == false)
	{
		FreeMemory();
	}*/

	return loaded;
}
//first step .validate header
bool elf::ElfValidateHeader()
{
	Elf_Ehdr* pHeader;
	bool blRet = false;

	pHeader = (Elf_Ehdr*) m_pElf;
    m_elfHeader.iMagic 		= pHeader->e_magic;
	m_elfHeader.iClass 		= pHeader->e_class;
	m_elfHeader.iData 		= pHeader->e_data;
	m_elfHeader.iIdver 		= pHeader->e_idver;
	m_elfHeader.iType 		= pHeader->e_type;
	m_elfHeader.iMachine 	= pHeader->e_machine;
	m_elfHeader.iVersion 	= pHeader->e_version;
	m_elfHeader.iEntry 		= pHeader->e_entry;
	m_elfHeader.iPhoff 		= pHeader->e_phoff;
	m_elfHeader.iShoff 		= pHeader->e_shoff;
	m_elfHeader.iFlags 		= pHeader->e_flags;
	m_elfHeader.iEhsize		= pHeader->e_ehsize;
	m_elfHeader.iPhentsize 	= pHeader->e_phentsize;
	m_elfHeader.iPhnum 		= pHeader->e_phnum;
	m_elfHeader.iShentsize 	= pHeader->e_shentsize;
	m_elfHeader.iShnum 		= pHeader->e_shnum;
	m_elfHeader.iShstrndx 	= pHeader->e_shstrndx;

	if(m_elfHeader.iMagic == ELF_MAGIC)
	{
		u32 iPhend = 0;
		u32 iShend = 0;

		/* Check that if we have program and section headers they are valid */
		if(m_elfHeader.iPhnum > 0)
		{
			iPhend = m_elfHeader.iPhoff + (m_elfHeader.iPhentsize * m_elfHeader.iPhnum);
		}

		if(m_elfHeader.iShnum > 0)
		{
			iShend = m_elfHeader.iShoff + (m_elfHeader.iShentsize * m_elfHeader.iShnum);
		}
        debugf(loader,"%08X, %08X, %08X\n", iPhend, iShend, m_iElfSize);

		if((iPhend <= m_iElfSize) && (iShend <= m_iElfSize))
		{
			blRet = true;
		}
		else
		{
			errorf(loader,"Program or sections header information invalid");
		}
	}
	else
	{
		errorf(loader,"Magic value incorrect (not an ELF?)");
	}
	ElfDumpHeader();
	return blRet;
}

// Second step: load program headers
bool elf::LoadPrograms()
{
	bool blRet = true;

	if((m_elfHeader.iPhoff > 0) && (m_elfHeader.iPhnum > 0) && (m_elfHeader.iPhentsize > 0))
	{
		Elf_Phdr *pHeader;
		u8 *pData;
		u32 iLoop;

		pData = m_pElf + m_elfHeader.iPhoff;

		SAFE_ALLOC(m_pElfPrograms, ElfProgram[m_elfHeader.iPhnum]);

		if(m_pElfPrograms != NULL)
		{
			m_iPHCount = m_elfHeader.iPhnum;

			for(iLoop = 0; iLoop < (u32) m_iPHCount; iLoop++)
			{
				pHeader = (Elf_Phdr *) pData;
				m_pElfPrograms[iLoop].iType = pHeader->p_type;
				m_pElfPrograms[iLoop].iOffset = pHeader->p_offset;
				m_pElfPrograms[iLoop].iVaddr = pHeader->p_vaddr;
				m_pElfPrograms[iLoop].iPaddr = pHeader->p_paddr;
				m_pElfPrograms[iLoop].iFilesz = pHeader->p_filesz;
				m_pElfPrograms[iLoop].iMemsz = pHeader->p_memsz;
				m_pElfPrograms[iLoop].iFlags = pHeader->p_flags;
				m_pElfPrograms[iLoop].iAlign = pHeader->p_align;
				m_pElfPrograms[iLoop].pData = m_pElf + m_pElfPrograms[iLoop].iOffset;

				pData += m_elfHeader.iPhentsize;
			}
			ElfDumpProgramHeader();
		}
		else
		{
			blRet = false;
		}
	}

	return blRet;
}
bool elf::LoadSections()
{
	bool blRet = true;

	if((m_elfHeader.iShoff != 0) && (m_elfHeader.iShnum > 0) && (m_elfHeader.iShentsize > 0))
	{
		SAFE_ALLOC(m_pElfSections, ElfSection[m_elfHeader.iShnum]);
		if(m_pElfSections != NULL)
		{
			int iLoop;
			u8 *pData;
			Elf_Shdr *pSection;

			m_iSHCount = m_elfHeader.iShnum;
			memset(m_pElfSections, 0, sizeof(ElfSection) * m_iSHCount);
			pData = m_pElf + m_elfHeader.iShoff;

			for(iLoop = 0; iLoop < m_iSHCount; iLoop++)
			{
				pSection = (Elf_Shdr*) pData;
				if(FillSection(m_pElfSections[iLoop], pSection) == false)
				{
					blRet = false;
					break;
				}

				pData += m_elfHeader.iShentsize;
			}

			if((m_elfHeader.iShstrndx > 0) && (m_elfHeader.iShstrndx < (u32) m_iSHCount))
			{
				if(m_pElfSections[m_elfHeader.iShstrndx].iType == SHT_STRTAB)
				{
					m_pElfStrtab = &m_pElfSections[m_elfHeader.iShstrndx];
				}
			}

			if(blRet)
			{
				/* If we found a string table let's run through the sections fixing up names */
				if(m_pElfStrtab != NULL)
				{
					for(iLoop = 0; iLoop < m_iSHCount; iLoop++)
					{
						strncpy(m_pElfSections[iLoop].szName, 
								(char *) (m_pElfStrtab->pData + m_pElfSections[iLoop].iName), ELF_SECT_MAX_NAME - 1);
						m_pElfSections[iLoop].szName[ELF_SECT_MAX_NAME-1] = 0;
					}
				}
				ElfDumpSections();

			}
		}
		else
		{
			errorf(loader, "Could not allocate memory for sections");
			blRet = false;
		}
	}
	return blRet;
}
bool elf::FillSection(ElfSection& elfSect, const Elf_Shdr *pSection)
{
	

	elfSect.iName = pSection->sh_name;
	elfSect.iType = pSection->sh_type;
	elfSect.iFlags = pSection->sh_flags;
	elfSect.iAddr = pSection->sh_addr;
	elfSect.iOffset = pSection->sh_offset;
	elfSect.iSize = pSection->sh_size;
	elfSect.iLink = pSection->sh_link;
	elfSect.iInfo = pSection->sh_info;
	elfSect.iAddralign = pSection->sh_addralign;
	elfSect.iEntsize = pSection->sh_entsize;
	elfSect.pData = m_pElf + elfSect.iOffset;
	elfSect.pRelocs = NULL;
	elfSect.iRelocCount = 0;

	if(((elfSect.pData + elfSect.iSize) > (m_pElf + m_iElfSize)) && (elfSect.iType != SHT_NOBITS))
	{
		errorf(loader,"Section too big for file");
		elfSect.pData = NULL;
		return false;
	}

	return true;
}
bool elf::LoadSymbols()
{
	ElfSection *pSymtab;
	bool blRet = true;

	debugf(loader,"Size %d\n", sizeof(Elf_Sym));

	pSymtab = ElfFindSection(".symtab");
	if((pSymtab != NULL) && (pSymtab->iType == SHT_SYMTAB) && (pSymtab->pData != NULL))
	{
		Elf_Sym *pSym;
		int iLoop, iSymcount;
		u32 symidx;

		symidx = pSymtab->iLink;
		iSymcount = pSymtab->iSize / sizeof(Elf_Sym);
		SAFE_ALLOC(m_pElfSymbols, ElfSymbol[iSymcount]);
		if(m_pElfSymbols != NULL)
		{
			m_iSymCount = iSymcount;
			pSym = (Elf_Sym*) pSymtab->pData;
			for(iLoop = 0; iLoop < iSymcount; iLoop++)
			{
				m_pElfSymbols[iLoop].name = pSym->st_name;
				m_pElfSymbols[iLoop].symname = GetSymbolName(m_pElfSymbols[iLoop].name, symidx);
				m_pElfSymbols[iLoop].value = pSym->st_value;
				m_pElfSymbols[iLoop].size = pSym->st_size;
				m_pElfSymbols[iLoop].info = pSym->st_info;
				m_pElfSymbols[iLoop].other = pSym->st_other;
				m_pElfSymbols[iLoop].shndx = pSym->st_shndx;
				pSym++;
			}
			ElfDumpSymbols();
		}
		else
		{
			errorf(loader, "Could not allocate memory for symbols\n");
			blRet = false;
		}
	}

	return blRet;
}


//help functions
ElfSection* elf::ElfFindSection(const char *szName)
{
	ElfSection* pSection = NULL;

	if((m_pElfSections != NULL) && (m_iSHCount > 0) && (m_pElfStrtab != NULL))
	{
		int iLoop;

		if(szName == NULL)
		{
			/* Return the default entry, kinda pointless :P */
			pSection = &m_pElfSections[0];
		}
		else
		{
			for(iLoop = 0; iLoop < m_iSHCount; iLoop++)
			{
				if(strcmp(m_pElfSections[iLoop].szName, szName) == 0)
				{
					pSection = &m_pElfSections[iLoop];
				}
			}
		}
	}

	return pSection;
}
const char *elf::GetSymbolName(u32 name, u32 shndx)
{
	if((shndx > 0) && (shndx < (u32) m_iSHCount))
	{
		if((m_pElfSections[shndx].iType == SHT_STRTAB) && (name < m_pElfSections[shndx].iSize))
		{
			return (char *) (m_pElfSections[shndx].pData + name);
		}
	}

	return "";
}

//dump functions for debug mostly
void elf::ElfDumpHeader()
{
	debugf(loader, "ELF Header:");
	debugf(loader, "Magic %08X", m_elfHeader.iMagic);
	debugf(loader, "Class %d", m_elfHeader.iClass);
	debugf(loader, "Data %d", m_elfHeader.iData);
	debugf(loader, "Idver %d", m_elfHeader.iIdver);
	debugf(loader, "Type %04X", m_elfHeader.iType);
	debugf(loader, "Start %08X", m_elfHeader.iEntry);
	debugf(loader, "PH Offs %08X", m_elfHeader.iPhoff);
	debugf(loader, "SH Offs %08X", m_elfHeader.iShoff);
	debugf(loader, "Flags %08X", m_elfHeader.iFlags);
	debugf(loader, "EH Size %d", m_elfHeader.iEhsize);
	debugf(loader, "PHEntSize %d", m_elfHeader.iPhentsize);
	debugf(loader, "PHNum %d", m_elfHeader.iPhnum);
	debugf(loader, "SHEntSize %d", m_elfHeader.iShentsize);
	debugf(loader, "SHNum %d", m_elfHeader.iShnum);
	debugf(loader, "SHStrndx %d\n", m_elfHeader.iShstrndx);
}
void elf::ElfDumpProgramHeader()
{
	u32 iLoop;
	for(iLoop = 0; iLoop < (u32) m_iPHCount; iLoop++)
	{
		debugf(loader, "Program Header %d:", iLoop);
		debugf(loader, "Type: %08X", m_pElfPrograms[iLoop].iType);
		debugf(loader, "Offset: %08X", m_pElfPrograms[iLoop].iOffset);
		debugf(loader, "VAddr: %08X", m_pElfPrograms[iLoop].iVaddr);
		debugf(loader, "PAddr: %08X", m_pElfPrograms[iLoop].iPaddr);
		debugf(loader, "FileSz: %d", m_pElfPrograms[iLoop].iFilesz);
		debugf(loader, "MemSz: %d", m_pElfPrograms[iLoop].iMemsz);
		debugf(loader, "Flags: %08X", m_pElfPrograms[iLoop].iFlags);
		debugf(loader, "Align: %08X\n", m_pElfPrograms[iLoop].iAlign);
	}
}
void elf::ElfDumpSections()
{
	int iLoop;
	for(iLoop = 0; iLoop < m_iSHCount; iLoop++)
	{
		ElfSection* pSection;

		pSection = &m_pElfSections[iLoop];
		debugf(loader,"Section %d", iLoop);
		debugf(loader,"Name: %d %s", pSection->iName, pSection->szName);
		debugf(loader, "Type: %08X", pSection->iType);
		debugf(loader, "Flags: %08X", pSection->iFlags);
		debugf(loader, "Addr: %08X", pSection->iAddr);
		debugf(loader, "Offset: %08X", pSection->iOffset);
		debugf(loader, "Size: %08X", pSection->iSize);
		debugf(loader, "Link: %08X", pSection->iLink);
		debugf(loader, "Info: %08X", pSection->iInfo);
		debugf(loader, "Addralign: %08X", pSection->iAddralign);
		debugf(loader, "Entsize: %08X", pSection->iEntsize);
		debugf(loader, "Data %p\n", pSection->pData);
	}
}
void elf::ElfDumpSymbols()
{
  int iLoop;
  for(iLoop = 0; iLoop < m_iSymCount; iLoop++)
  {
	debugf(loader, "Symbol %d", iLoop);
	debugf(loader, "Name %d, '%s'", m_pElfSymbols[iLoop].name, m_pElfSymbols[iLoop].symname);
	debugf(loader, "Value %08X",m_pElfSymbols[iLoop].value);
	debugf(loader, "Size  %08X", m_pElfSymbols[iLoop].size);
	debugf(loader, "Info  %02X", m_pElfSymbols[iLoop].info);
	debugf(loader, "Other %02X", m_pElfSymbols[iLoop].other);
	debugf(loader, "Shndx %04X\n", m_pElfSymbols[iLoop].shndx);
  }

}
