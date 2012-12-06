#include "stdafx.h"
#include "emulator.h"
#include "al/al.h"
#include "hle/kernel.h"

#include "sceKernelThread.h"
#include "sceKernelSemaphore.h"

namespace hle
{
	/** Current state of a semaphore.
	* @see sceKernelReferSemaStatus.
	*/

	struct NativeSemaphore
	{
		/** Size of the ::SceKernelSemaInfo structure. */
		SceSize 	size;
		/** NUL-terminated name of the semaphore. */
		char 		name[32];
		/** Attributes. */
		SceUInt 	attr;
		/** The initial count the semaphore was created with. */
		int 		initCount;
		/** The current count. */
		int 		currentCount;
		/** The maximum count. */
		int 		maxCount;
		/** The number of threads waiting on the semaphore. */
		int 		numWaitThreads;
	};


	struct Semaphore : public KernelObject 
	{
		const char *GetName() const {return ns.name;}
		const char *GetType() const {return "Semaphore";}
		NativeSemaphore ns;
		std::vector<SceUID> waitingThreads;
	};

	void HLEDECL sceKernelCancelSema(AlContext &context)
	{
		SceUID id = context.gpr[ALLEGREX_A0];
		errorf(ThreadManForUser,"UNIMPL: sceKernelCancelSema()");
		context.gpr[ALLEGREX_V0] = 0;
	}

	//SceUID sceKernelCreateSema(const char *name, SceUInt attr, int initVal, int maxVal, SceKernelSemaOptParam *option);
	void HLEDECL sceKernelCreateSema(AlContext &context)
	{
		const char *name = Memory::addr< const char >(context.gpr[ALLEGREX_A0]);

		Semaphore *s = new Semaphore;
		SceUID id = s->GetUid();

		strncpy(s->ns.name, name, 31);
		s->ns.attr = context.gpr[ALLEGREX_A1];
		s->ns.initCount = context.gpr[ALLEGREX_A2];
		s->ns.currentCount = s->ns.initCount;
		s->ns.maxCount = context.gpr[ALLEGREX_A3];

		infof(ThreadManForUser,"%i=sceKernelCreateSema(name %s, attr %08x, init %i, max %i, A4 %08x)", id, s->ns.name, s->ns.attr, s->ns.initCount, s->ns.maxCount, context.gpr[ALLEGREX_A4]);

		context.gpr[ALLEGREX_V0] = id;
	}

	//int sceKernelDeleteSema(SceUID semaid);
	void HLEDECL sceKernelDeleteSema(AlContext &context)
	{
		SceUID id = context.gpr[ALLEGREX_A0];
		infof(ThreadManForUser,"sceKernelDeleteSema(%i)", id);
		context.gpr[ALLEGREX_V0] = theKernelObjects.Release<Semaphore>(id);
	}

	void HLEDECL sceKernelReferSemaStatus(AlContext &context)
	{
		SceUID id = context.gpr[ALLEGREX_A0];
		u32 error;
		Semaphore *s = theKernelObjects.Get<Semaphore>(id, error);
		if (s)
		{
			infof(ThreadManForUser,"sceKernelReferSemaStatus(%i, %08x)", id, context.gpr[ALLEGREX_A1]);
			NativeSemaphore *outptr = Memory::addr< NativeSemaphore >(context.gpr[ALLEGREX_A1]);
			int szToCopy = outptr->size - 4;
			memcpy((char*)outptr + 4, (char*)s + 4, szToCopy);
			context.gpr[ALLEGREX_V0] = 0;
		}
		else
		{
			errorf(ThreadManForUser,"Error %08x", error);
			context.gpr[ALLEGREX_V0] = error;
		}
	}
	
	//int sceKernelSignalSema(SceUID semaid, int signal);
	void HLEDECL sceKernelSignalSema(AlContext &context)
	{
		//TODO: check that this thing really works :)
		SceUID id = context.gpr[ALLEGREX_A0];
		u32 signal = context.gpr[ALLEGREX_A1];
		u32 error;
		Semaphore *s = theKernelObjects.Get<Semaphore>(id, error);
		if (s)
		{
			int oldval = s->ns.currentCount;
			s->ns.currentCount += signal;
			infof(ThreadManForUser,"sceKernelSignalSema(%i, %i) (old: %i, new: %i)", id, signal, oldval, s->ns.currentCount);
			
			bool wokeThreads = false;
retry:
			//TODO: check for threads to wake up - wake them
			std::vector<SceUID>::iterator iter;
			for (iter = s->waitingThreads.begin(); iter!=s->waitingThreads.end(); s++)
			{
				SceUID id = *iter;
				int wVal = (int)__KernelGetWaitValue(id, error);
				if (wVal <= s->ns.currentCount)
				{
					__KernelWakeThread(id, 0);
					s->ns.currentCount -= wVal;
					wokeThreads = true;
					s->waitingThreads.erase(iter);
					goto retry;
				}
				else
				{
					break;
				}
			}
			//pop the thread that were released from waiting

			if (wokeThreads)
				__KernelReSchedule();

			context.gpr[ALLEGREX_V0] = 0;
		}
		else
		{
			errorf(ThreadManForUser, "sceKernelSignalSema : Trying to signal invalid semaphore %i", id);
			context.gpr[ALLEGREX_V0] = error;
		}
	}

	//int sceKernelWaitSema(SceUID semaid, int signal, SceUInt *timeout);
	void HLEDECL sceKernelWaitSema(AlContext &context)
	{
		SceUID id = context.gpr[ALLEGREX_A0];
		int signal = context.gpr[ALLEGREX_A1];
		u32 timeoutPtr = context.gpr[ALLEGREX_A2];
		int timeout = context.gpr[ALLEGREX_A3];

		infof(ThreadManForUser,"sceKernelWaitSema(%i, %i, %i)", id, signal, timeout);
		
		u32 error;
		Semaphore *s = theKernelObjects.Get<Semaphore>(id, error);
		if (s)
		{
			if (s->ns.currentCount >= signal)
			{
				s->ns.currentCount -= signal;
			}
			else
			{
				s->waitingThreads.push_back(__KernelGetCurThreadId());
				__KernelWaitCurThread(context, WAITTYPE_SEMA, id, signal);
				return;
			}
			context.gpr[ALLEGREX_V0] = 0;
		}
		else
		{
			context.gpr[ALLEGREX_V0] = error;
		}
	} 

	//Should be same as WaitSema but without the wait
	void HLEDECL sceKernelPollSema(AlContext &context)
	{
		SceUID semid = context.gpr[ALLEGREX_A0];
		int needcount = context.gpr[ALLEGREX_A1];

		infof(ThreadManForUser,"sceKernelPollSema(%i, %i)", semid, needcount);

		if (needcount <= 0) 
		{
			errorf(ThreadManForUser, "sceKernelPollSema : SCE_KERNEL_ERROR_ILLEGAL_COUNT");
            context.gpr[ALLEGREX_V0] = SCE_KERNEL_ERROR_ILLEGAL_COUNT;
            return;
        }

		u32 error;
		Semaphore *s = theKernelObjects.Get<Semaphore>(semid, error);
		int targetvalue = s->ns.currentCount;
        int waitThreads = s->ns.numWaitThreads;
        if (!s) 
		{
			errorf(ThreadManForUser, "sceKernelPollSema : SCE_KERNEL_ERROR_UNKNOWN_SEMID");
			context.gpr[ALLEGREX_V0] = SCE_KERNEL_ERROR_UNKNOWN_SEMID;
        }
		else if (targetvalue < needcount) 
		{
			/*sceKernelPollSema differs from sceKernelWaitSema in  that when the count value of the target semaphore 
			is less than the needcount it returns the error SCE_KERNEL_ERROR_SEMA_ZERO */
			errorf(ThreadManForUser, "sceKernelPollSema : SCE_KERNEL_ERROR_SEMA_ZERO");
            context.gpr[ALLEGREX_V0] = SCE_KERNEL_ERROR_SEMA_ZERO;
        } 
		else 
		{
            s->ns.currentCount -= needcount;
            context.gpr[ALLEGREX_V0] = 0;
        }
	}


	//int sceKernelWaitSemaCB(SceUID semaid, int signal, SceUInt *timeout);
	void HLEDECL sceKernelWaitSemaCB(AlContext &context)
	{
		SceUID id = context.gpr[ALLEGREX_A0];
		int signal = context.gpr[ALLEGREX_A1];
		int timeout = context.gpr[ALLEGREX_A2];
		infof(ThreadManForUser,"sceKernelWaitSemaCB(%i, %i, %i)", id, signal, timeout);
		u32 error;
		Semaphore *s = theKernelObjects.Get<Semaphore>(id, error);
		if (s)
		{
			infof(ThreadManForUser,"CurrentCount: %i, Signal: %i", s->ns.currentCount, signal);
			if (s->ns.currentCount >= signal) //TODO fix
			{
				infof(ThreadManForUser,"Subtracting sema");
				s->ns.currentCount -= signal;
			}
			else
			{
				s->waitingThreads.push_back(__KernelGetCurThreadId());
				__KernelWaitCurThread(context, WAITTYPE_SEMA, id, signal, true);
				return;
			}
			infof(ThreadManForUser,"After: CurrentCount: %i, Signal: %i", s->ns.currentCount, signal);
			context.gpr[ALLEGREX_V0] = 0;
		}
		else
		{
			errorf(ThreadManForUser,"sceKernelWaitSemaCB - Bad semaphore");
			context.gpr[ALLEGREX_V0] = error;
		}
	}
}

