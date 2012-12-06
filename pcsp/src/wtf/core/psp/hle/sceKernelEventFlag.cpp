#include "stdafx.h"


#include "emulator.h"
#include "al/al.h"
#include "hle/kernel.h"

#include "sceKernelThread.h"
#include "sceKernelEventFlag.h"

#define KERNELOBJECT_MAX_NAME_LENGTH 31

namespace hle
{
	class EventFlag : public KernelObject
	{
	public:
		const char *GetName() const {return name;}
		const char *GetType() const {return "EventFlag";}
		void GetQuickInfos(char *ptr, size_t size)
		{
			sprintf(ptr, "init=%08x cur=%08x numwait=%i",
				initPattern,
				currentPattern,
				numWaitThreads);
		}
		SceSize 	size;
		char 		name[KERNELOBJECT_MAX_NAME_LENGTH+1];
		SceUInt 	attr;
		SceUInt 	initPattern;
		SceUInt 	currentPattern;
		int 		numWaitThreads;
	};


	/** Event flag creation attributes */
	enum PspEventFlagAttributes
	{
		/** Allow the event flag to be waited upon by multiple threads */
		PSP_EVENT_WAITMULTIPLE = 0x200
	};

	/** Event flag wait types */
	enum PspEventFlagWaitTypes
	{
		/** Wait for all bits in the pattern to be set */
		PSP_EVENT_WAITAND = 0,
		/** Wait for one or more bits in the pattern to be set */
		PSP_EVENT_WAITOR  = 1,
		/** Clear the wait pattern when it matches */
		PSP_EVENT_WAITCLEAR = 0x20
	};

	//SceUID sceKernelCreateEventFlag(const char *name, int attr, int bits, SceKernelEventFlagOptParam *opt);
	void HLEDECL sceKernelCreateEventFlag(AlContext &context)
	{
		const char *name = Memory::addr< const char >(context.gpr[ALLEGREX_A0]);

		EventFlag *e = new EventFlag;
		SceUID id = e->GetUid();

		e->size = sizeof(EventFlag);
		strncpy(e->name, name, 31);
		e->attr = context.gpr[ALLEGREX_A1];
		e->initPattern = context.gpr[ALLEGREX_A2];
		e->currentPattern = e->initPattern;
		e->numWaitThreads = 0;

		infof(ThreadManForUser,"%i=sceKernelCreateEventFlag(\"%s\", %08x, %08x, %08x)", id, e->name, e->attr, e->currentPattern, context.gpr[ALLEGREX_A3]);
		context.gpr[ALLEGREX_V0] = id;
	}

	//int sceKernelClearEventFlag(SceUID evid, u32 bits);
	void HLEDECL sceKernelClearEventFlag(AlContext &context)
	{
		SceUID id = context.gpr[ALLEGREX_A0];
		u32 bits = context.gpr[ALLEGREX_A1];

		u32 error;
		EventFlag *e = theKernelObjects.Get<EventFlag>(id, error);
		if (e)
		{
			e->currentPattern &= bits;
			context.gpr[ALLEGREX_V0] = 0;
		}
		else
		{
			context.gpr[ALLEGREX_V0] = error;
		}
		infof(ThreadManForUser,"sceKernelClearEventFlag(%i, %08x)", id, bits);
		context.gpr[ALLEGREX_V0] = 0;
	}

	//int sceKernelDeleteEventFlag(int evid);
	void HLEDECL sceKernelDeleteEventFlag(AlContext &context)
	{
		SceUID id = context.gpr[ALLEGREX_A0];
		infof(ThreadManForUser,"sceKernelDeleteEventFlag(%i)", id);
		context.gpr[ALLEGREX_V0] = theKernelObjects.Release<EventFlag>(id);
	}

	//int sceKernelSetEventFlag(SceUID evid, u32 bits);
	void HLEDECL sceKernelSetEventFlag(AlContext &context)
	{
		SceUID id = context.gpr[ALLEGREX_A0];
		u32 bits = context.gpr[ALLEGREX_A1];
		u32 error;
		EventFlag *e = theKernelObjects.Get<EventFlag>(id, error);
		if (e)
		{
			e->currentPattern |= bits;
			context.gpr[ALLEGREX_V0] = 0;
		}
		else
		{
			context.gpr[ALLEGREX_V0] = error;
		}
	}

	//int sceKernelWaitEventFlag(SceUID evid, u32 bits, u32 wait, u32 *outBits, SceUInt *timeout);
	void HLEDECL sceKernelWaitEventFlag(AlContext &context)
	{
		SceUID id = context.gpr[ALLEGREX_A0];
		u32 bits = context.gpr[ALLEGREX_A1];
		u32 wait = context.gpr[ALLEGREX_A2];
		u32 outBitsPtr = context.gpr[ALLEGREX_A3];
		u32 timeoutPtr = context.gpr[ALLEGREX_A4];

		errorf(ThreadManForUser,"UNIMPL: sceKernelWaitEventFlag(%i, %08x, %i, %08x, %08x)", id, bits, wait, outBitsPtr, timeoutPtr);
		__KernelWaitCurThread(context, WAITTYPE_EVENTFLAG, id);
	}

	//int sceKernelWaitEventFlagCB(SceUID evid, u32 bits, u32 wait, u32 *outBits, SceUInt *timeout);
	void HLEDECL sceKernelWaitEventFlagCB(AlContext &context)
	{
		SceUID id = context.gpr[ALLEGREX_A0];
		u32 bits = context.gpr[ALLEGREX_A1];
		u32 wait = context.gpr[ALLEGREX_A2];
		u32 outBitsPtr = context.gpr[ALLEGREX_A3];
		u32 timeoutPtr = context.gpr[ALLEGREX_A4];

		errorf(ThreadManForUser,"UNIMPL: sceKernelWaitEventFlagCB(%i, %08x, %i, %08x, %08x)", id, bits, wait, outBitsPtr, timeoutPtr);
		context.gpr[ALLEGREX_V0] = 0;
	}

	//int sceKernelPollEventFlag(int evid, u32 bits, u32 wait, u32 *outBits);
	void HLEDECL sceKernelPollEventFlag(AlContext &context)
	{
		SceUID id = context.gpr[ALLEGREX_A0];
		u32 bits = context.gpr[ALLEGREX_A1];
		u32 wait = context.gpr[ALLEGREX_A2];
		u32 outBitsPtr = context.gpr[ALLEGREX_A3];

		errorf(ThreadManForUser,"UNIMPL: sceKernelPollEventFlag(%i, %08x, %i, %08x)", id, bits, wait, outBitsPtr);
		context.gpr[ALLEGREX_V0] = 0;
	}

	//int sceKernelReferEventFlagStatus(SceUID event, SceKernelEventFlagInfo *status);
	void HLEDECL sceKernelReferEventFlagStatus(AlContext &context)
	{
		SceUID id = context.gpr[ALLEGREX_A0];
		errorf(ThreadManForUser,"UNIMPL: sceKernelReferEventFlagStatus()");
		context.gpr[ALLEGREX_V0] = 0;
	}

	//odd one out - never seen
	void HLEDECL sceKernelCancelEventFlag(AlContext &context)
	{
		errorf(ThreadManForUser,"UNIMPL: sceKernelCancelEventFlag()");
		context.gpr[ALLEGREX_V0] = 0;
	}
}

