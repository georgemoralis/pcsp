#include "stdafx.h"

#include "emulator.h"
#include "al/al.h"
#include "hle/modules/sysmem/sysmem.h"
#include "hle/kernel.h"

#include "sceKernelThread.h"

#include "sceKernelCallback.h"

namespace hle
{
	class Callback : public KernelObject
	{
	public:
		const char *GetName() const {return name;}
		const char *GetType() const {return "CallBack";}

		void GetQuickInfos(char *ptr, size_t size)
		{
			sprintf(ptr, "hack= %08x , thread=%i, argument= %08x",
				hackAddress,
				threadId,
				argument);
		}

		~Callback()
		{
            sysmem::hleKernelFreePartitionMemory(hackAddressUid);
		}

		void GrabAndWriteHack()
		{
            hackAddressUid = sysmem::hleKernelAllocPartitionMemory(1, "hackCB", 0, 8, 0);
            if (hackAddressUid > 0)
            {
                hackAddress = sysmem::hleKernelGetBlockHeadAddr(hackAddressUid);
			    Memory::memw(hackAddress + 0) = MIPS_MAKE_JAL(entrypoint);
			    Memory::memw(hackAddress + 4) = MIPS_MAKE_NOP();
            }
		}

		SceUInt size;
		char name[32];
		u32 entrypoint;
		SceUID threadId;
		u32 argument;
		u32 notifyCount;
        u32 hackAddress;
        SceUID hackAddressUid;

		u32 oldPC;
		u32 oldRA;

		SceUInt 	attr;
		SceUInt 	initPattern;
		SceUInt 	currentPattern;
		int 		numWaitThreads;
	
	};

	//////////////////////////////////////////////////////////////////////////
	// CALLBACKS
	//////////////////////////////////////////////////////////////////////////

	//extern Thread *currentThread;
	void sceKernelCreateCallback(AlContext &context)
	{
		u32 entrypoint = context.gpr[ALLEGREX_A1];
		u32 argument = context.gpr[ALLEGREX_A2];

		const char *name = Memory::addr< const char >(context.gpr[ALLEGREX_A0]);

		Callback *c = new Callback;
		SceUID id = c->GetUid();
		infof(ThreadManForUser,"%i=sceKernelCreateCallback(name=%s,entry= %08x )", id, name, entrypoint);

		c->size = sizeof(Callback);
		strncpy(c->name, name, 31);

		c->entrypoint = entrypoint;
		c->threadId = __KernelGetCurThreadId();
		c->argument = argument;

		c->GrabAndWriteHack();
		context.gpr[ALLEGREX_V0] = id;
	}

	//Hacks should really point to this guy
	void _sceKernelReturnFromCallback(AlContext &context)
	{
		SceUID id = context.gpr[ALLEGREX_A0];
		infof(ThreadManForUser,"_sceKernelReturnFromCallback(%i)", id);
		//blah blah
	}

	void sceKernelDeleteCallback(AlContext &context)
	{
		SceUID id = context.gpr[ALLEGREX_A0];
		infof(ThreadManForUser,"sceKernelDeleteCallback(%i)", id);
		context.gpr[ALLEGREX_V0] = theKernelObjects.Release<Callback>(id);
	}

	void sceKernelNotifyCallback(AlContext &context)
	{
		SceUID id = context.gpr[ALLEGREX_A0];
		errorf(ThreadManForUser,"UNIMPL sceKernelNofityCallback(%i)", id);
	}

	void __KernelCallCallback(AlContext &context, SceUID id)
	{
		//First, make sure we're on the right thread
		u32 error;
		Callback *c = theKernelObjects.Get<Callback>(id, error);
		if (c)
		{
			if (c->threadId == __KernelGetCurThreadId())
			{
				//Alright, we're on the right thread
				u32 oldPC = theEmulator.context->pc;
				u32 oldRA = theEmulator.context->gpr[ALLEGREX_RA];

				theEmulator.context->pc = c->entrypoint;
				
			}
		}
		else
		{
			//ARGH!
		}
		//Write  
		//jal callback 
		//nop
		//li a0, callbackno
		//syscall PostCallback
		//to the hack memory area
	}

	void sceKernelCheckCallback(AlContext &context)
	{
		//only check those of current thread
		infof(ThreadManForUser,"sceKernelCheckCallback");
		context.gpr[ALLEGREX_V0] = 0;
	}

}

