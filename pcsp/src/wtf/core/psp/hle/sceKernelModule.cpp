#include "stdafx.h"
#include "sceKernelModule.h"
#include "wtf/core/elf/ElfReader.h"
#include "wtf/core/psp/hle/sceKernelThread.h"
#include "hle/kernel.h"
#include <string.h>

namespace hle
{

	//////////////////////////////////////////////////////////////////////////
	// MODULES
	//////////////////////////////////////////////////////////////////////////
	struct StartModuleInfo
	{
		u32 size;
		u32 mpidtext;
		u32 mpiddata;
		u32 threadpriority;
		u32 threadattributes;
	};

	//////////////////////////////////////////////////////////////////////////
	// STATE BEGIN
	int numberModules;
	// STATE END
	//////////////////////////////////////////////////////////////////////////
	
	struct PspModuleInfo
	{
		// 0, 0, 1, 1 ?
		u16 moduleAttrs; //0x0000 User Mode, 0x1000 Kernel Mode
		u16 moduleVersion;
		// 28 bytes of module name, packed with 0's.
		char name[28];
		u32 gp;           // ptr to MIPS GOT data  (global offset table)
		u32 libent;       // ptr to .lib.ent section 
		u32 libentend;    // ptr to end of .lib.ent section 
		u32 libstub;      // ptr to .lib.stub section 
		u32 libstubend;   // ptr to end of .lib.stub section 
	};

	struct PspLibStubEntry
	{
		// pointer to module name (will be in .rodata.sceResident section)
        unsigned int moduleNameSymbol;
		// mod version??
		unsigned short version;
		unsigned short val1;
		unsigned char val2; // 0x5
		unsigned char val3;
		// number of function symbols
		unsigned short numFuncs;
		// each symbol has an associated nid; nidData is a pointer
        // (in .rodata.sceNid section) to an array of u32, one
		// for each function, which identifies the function whose
		// address is to be inserted.
		//
		// The hash is the first 4 bytes of a SHA-1 hash of the function
        // name.  (Represented as a little-endian u32, so the order
		// of the bytes is reversed.)
        unsigned int nidData;
		// the address of the function stubs where the function address jumps
		// should be filled in
        unsigned int firstSymAddr;
	};

	KernelModule *__KernelLoadELFFromPtr(const u8 *ptr,u32 loadAddress, SceUID &id)
	{
		u32 hej = *((u32 *)ptr);
		if (*(u32 *)ptr != 0x464c457f)
		{
                    #ifdef WIN32
                        DebugBreak();
                    #endif
		}

		// Open ELF reader
        ElfReader *reader  = new ElfReader((void *)ptr);
		if (!reader->LoadInto(loadAddress))
		{
                    #ifdef WIN32
                        DebugBreak();
                    #endif
		}

		struct libent
		{
			u32 exportName; //default 0
			u16 bcdVersion;
			u16 moduleAttributes;
			u8  exportEntrySize;
			u8  numVariables;
			u16 numFunctions;
            u32 __entrytableAddr;
		};

		SectionID entSection = reader->GetSectionByName(".lib.ent");
		SectionID textSection = reader->GetSectionByName(".text");

		u32 sceResidentAddr = 0;
		u32 moduleInfoAddr = 0;
		u32 textStart = reader->GetSectionAddr(textSection);
		u32 textSize = reader->GetSectionSize(textSection);

		SectionID sceResidentSection = reader->GetSectionByName(".rodata.sceResident");
		SectionID sceModuleInfoSection = reader->GetSectionByName(".rodata.sceModuleInfo");

		bool hasSymbols = false;
		bool dontadd = false;

    	//have fun
		//lib->l1+=0;
		sceResidentAddr = reader->GetSectionAddr(sceResidentSection);
		moduleInfoAddr  = reader->GetSectionAddr(sceModuleInfoSection);

		struct PspResidentData 
		{
            unsigned int l1; // unknown 0xd632acdb
            unsigned int l2; // unknown 0xf01d73a7
            unsigned int startAddress; // address of _start
            unsigned int moduleInfoAddr; // address of sceModuleInfo struct
		};

		Log::loader.info("Resident data addr: %08x",  sceResidentAddr);


		PspModuleInfo *modinfo = Memory::addr< PspModuleInfo >(moduleInfoAddr);

        KernelModule *m = new KernelModule(modinfo->name, modinfo->gp, 0, 0x7FFF);

        SceUID uid = m->GetUid();

		Log::loader.info("Module %s: %08x %08x %08x", modinfo->name, modinfo->gp, modinfo->libent, modinfo->libstub);

		int numModules = (modinfo->libstubend - modinfo->libstub)/sizeof(PspLibStubEntry);

		Log::loader.info("Num Modules: %i", numModules);
		Log::loader.info("===================================================");

		PspLibStubEntry *entry = Memory::addr< PspLibStubEntry >(modinfo->libstub);

		int numSyms = 0;
		for (int m = 0; m < numModules; m++)
		{
			char *modulename = Memory::addr< char >(entry[m].moduleNameSymbol);
			u32  *nidDataPtr = Memory::addr< u32  >(entry[m].nidData);
			u32  *stubs      = Memory::addr< u32  >(entry[m].firstSymAddr);

			Log::loader.info("Importing Module %s, stubs at %08x", modulename, entry[m].firstSymAddr);

			for (int i = 0; i < entry[m].numFuncs; i++)
			{
				u32 addrToWriteSyscall = entry[m].firstSymAddr+i*8;
				Log::loader.info("%s : %08x", theKernelModuleManager.GetSyscallName(modulename, nidDataPtr[i]), addrToWriteSyscall);
				//write a syscall here
                theKernelModuleManager.WriteSyscall(modulename, nidDataPtr[i], addrToWriteSyscall);
				if (!dontadd)
				{
					char temp[256];
					snprintf(temp,255,"zz_%s", theKernelModuleManager.GetSyscallName(modulename, nidDataPtr[i]));
//					Debugger::add_symbol(temp, addrToWriteSyscall, 4, ST_FUNCTION);
				}
				numSyms++;
			}
			Log::loader.info("-------------------------------------------------------------");
		}

		m->m_entry_addr = reader->GetEntryPoint();
		
        if (reader)
        {
            reader->UnLoadInto();
        }

		return m;
	}

	KernelModule *__KernelLoadModule(u8 *fileptr, SceUID &id, SceKernelLMOption *options)
	{
		KernelModule *m = __KernelLoadELFFromPtr(fileptr, 0x08880000, id);

		return m;
	}

	void __KernelUnLoadModule()
	{
	}

	void __KernelStartModule(KernelModule *m, int args, const char *argp, SceKernelSMOption *options)
	{
        __KernelSetupIdleThread();
		__KernelSetupInitThread(m->GetUid(), args, argp, options->priority, options->stacksize, options->attribute);
	}


	u32 __KernelGetModuleGP(SceUID module)
	{
		u32 error;
		KernelModule *m = theKernelObjects.Get< KernelModule >(module, error);
		if (m)
		{
			return m->m_gp_value;
		}
		else
		{
			return 0;
		}
	}

    void __KernelLoadExec(u8 *ptr, const char *filename)
	{
        SceUID moduleID;
		KernelModule *m = __KernelLoadModule(ptr, moduleID, 0);
        theEmulator.context     = new AlContext;
        theEmulator.context->pc = m->m_entry_addr;
        SceKernelSMOption option;
        option.size      = sizeof(SceKernelSMOption);
        option.attribute = 0;
        option.mpidstack = 2;
        option.priority  = 32;
        option.stacksize = 0x4000;

		__KernelStartModule(m, strlen(filename), filename, &option);
	}
}