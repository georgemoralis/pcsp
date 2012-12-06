#include "stdafx.h"

#include <QtCore>

#include "emulator.h"
#include "sc_thread.h"
#include "al/al.h"
#include "hle/kernel.h"
#include "wtf/core/psp/hle/sceKernelModule.h"

#include "common_fiber.h"
#include "common_skew_heap.h"

#include "sceKernelThread.h"

#include <list>
#include "hle/modules/sceAudio/sceAudio.h"
#include "hle/modules/sysmem/sysmem.h"

#define KERNELOBJECT_MAX_NAME_LENGTH 31

#define MAX_THREAD_PRIORITY     127
#define MIN_THREAD_STACKSIZE    0x200
#define THREAD_KSTACKSIZE       0x800

namespace hle
{
	//Wraps after 20 fake minutes - ONLY use by subtraction
	u32 pspMicroSeconds;

	enum ThreadStatus
	{
		THREADSTATUS_RUN = 1,
		THREADSTATUS_READY = 2,
		THREADSTATUS_WAIT = 4,
		THREADSTATUS_SUSPEND = 8,
		THREADSTATUS_DORMANT = 16,
		THREADSTATUS_DEAD = 32
	};

	struct SceKernelSysClock {
		u32 low;
		u32 hi;
	};

	struct NativeThread
	{
		u32 nativeSize;
		char name[KERNELOBJECT_MAX_NAME_LENGTH+1];

		// Threading stuff
		u32	attr;
		u32 status;
		u32 entrypoint;
		u32 initialStack;
		int stackSize;
		u32 gpreg;

		int initialPriority;
		int currentPriority;
		WaitType waitType;
		SceUID waitID;
		int wakeupCount;
		int exitStatus;
		SceKernelSysClock runForClocks;
		int numInterruptPreempts;
		int numThreadPreempts;
		int numReleases;
	};

    struct Context
    :   public AlContext
	{
        bool  fast;
	};

	class PspThread
    :   public KernelObject
    ,   public ScFiber< PspThread >
    ,   public SkewHeap< PspThread >::Node
	{
	public:

        static void       EnqueueReady(PspThread *t);
        static PspThread *DequeueReady();

		const char *GetName() const {return nt.name;}
		const char *GetType() const {return "Thread";}
		
        void GetQuickInfos(char *ptr, size_t size)
		{
			sprintf(ptr, "pc= %08x sp= %08x %s %s %s %s %s (wt=%i wid=%i wv= %08x )",
				m_thread_context.pc, m_thread_context.gpr[ALLEGREX_SP],
				(nt.status & THREADSTATUS_RUN) ? "RUN" : "", 
				(nt.status & THREADSTATUS_READY) ? "READY" : "", 
				(nt.status & THREADSTATUS_WAIT) ? "WAIT" : "", 
				(nt.status & THREADSTATUS_SUSPEND) ? "SUSPEND" : "", 
				(nt.status & THREADSTATUS_DORMANT) ? "DORMANT" : "",
				nt.waitType,
				nt.waitID,
				waitValue);
		}

		void GrabStack(int stacksize)
		{
			char threadstack[256];
			sprintf(threadstack,"%s stack",nt.name);
            SceUID stackid = sysmem::hleKernelAllocPartitionMemory(2, threadstack, 1, stacksize, 0);

            if (stackid > 0)
            {
                stackBlock = (u32)sysmem::hleKernelGetBlockHeadAddr(stackid);
                m_thread_context.gpr[ALLEGREX_SP] = stackBlock+stacksize;
                nt.initialStack = m_thread_context.gpr[ALLEGREX_SP];
                m_thread_context.gpr[ALLEGREX_K0] = m_thread_context.gpr[ALLEGREX_SP] - 512;
                m_thread_context.gpr[ALLEGREX_SP] -= 512;
                m_thread_context.gpr[ALLEGREX_FP] = m_thread_context.gpr[ALLEGREX_SP];
            }
		}

        PspThread(char const *name)
        :   KernelObject(name)
        ,   readyQueued(false)
        {
            Clear();
        }

		~PspThread()
		{
            if (stackid)
            {
                sysmem::hleKernelFreePartitionMemory(stackid);
            }
		}

        void HandleAudioEvent(u32 channel)
        {
            infof(sceAudio, "threadman: HandleAudioEvent(%d)", channel);
            //theEmulator.Unlock();
            hle::__KernelTrigger(hle::WAITTYPE_AUDIOCHANNEL, channel, false);
            //theEmulator.Lock();
            theEmulator.Resume();
        }

        void HandleClockEvent()
        {
            theEmulator.IncreaseEventCounter();
            theEmulator.Resume();
            KernelSysClock::SetTimer(KernelSysClock::Get() + 1000000);
        }

        void HandleVsyncEvent()
        {
            infof(sceDisplay, "threadman: HandleVsyncEvent()");
            //theEmulator.Unlock();
            hle::__KernelTrigger(hle::WAITTYPE_VSYNC, 0, false);
            //theEmulator.Lock();
            theEmulator.Resume();
        }

		NativeThread nt;

        friend bool operator <= (PspThread const &lnode, PspThread const &rnode)
        {
            return u32(lnode.nt.currentPriority) <= u32(rnode.nt.currentPriority);
        }

		u32 waitValue;
		bool sleeping;
        bool readyQueued;

		bool isProcessingCallbacks;

		// Okay, the other silly stuffpr comes here
		// context
		Context m_thread_context;

		std::queue<SceUID> callbacks;

		u32 stackBlock;
        SceUID stackid;

        static PspThread *m_idle_thread;
        static PspThread *m_cleanup_thread;
	};

    SkewHeap< PspThread > readyqueue;

    void PspThread::EnqueueReady(PspThread *t)
    {
        t->nt.status = THREADSTATUS_READY;
        if (!t->readyQueued)
        {
            t->Clear();
            readyqueue.Enqueue(*t);
        }
    }

    PspThread *PspThread::DequeueReady()
    {
        PspThread *t = &readyqueue.Front();
        if (t)
        {
            readyqueue.Dequeue();
            t->readyQueued = false;
        }
        return t;
    }


	//////////////////////////////////////////////////////////////////////////
	//STATE BEGIN
	//////////////////////////////////////////////////////////////////////////
	struct PspTimeout
    :   SkewHeap< PspTimeout >
	{
		u64 time;
        PspThread *thread;
		//SceUID threadId;

        friend __forceinline bool operator <= (PspTimeout const &a, PspTimeout const &b)
        {
            return a.time <= b.time;
        }
	};

	static PspThread *CurrentThread;
    static u32 threadHackAddr;
    static SceUID threadHackAddrId = 0;
	static std::vector<PspThread *> threadqueue; //Change to SceUID
	static SkewHeap<PspTimeout> timeouts;

	//u32 guard2[64];

	//////////////////////////////////////////////////////////////////////////
	//STATE END
	//////////////////////////////////////////////////////////////////////////

	void __KernelThreadingInit()
	{
        readyqueue.Clear();
        timeouts.Clear();
        threadHackAddrId = sysmem::hleKernelAllocPartitionMemory(1, "threadrethack", 0, 16, 0);
        threadHackAddr   = sysmem::hleKernelGetBlockHeadAddr(threadHackAddrId);
        theKernelModuleManager.WriteSyscall("FakeSysCalls", 0xc0debabe, threadHackAddr + 0);
        theKernelModuleManager.WriteSyscall("FakeSysCalls", 0xc1debabe, threadHackAddr + 8);
	}

	void __KernelThreadingShutdown()
	{
        if (threadHackAddrId > 0)
        {
            sysmem::hleKernelFreePartitionMemory(threadHackAddrId);
        }

		threadHackAddr=0;
        threadHackAddrId=0;
		CurrentThread=0;
        threadqueue.clear();
        timeouts.Clear();
	}

	u32 __KernelGetWaitValue(SceUID threadID, u32 &error)
	{
		PspThread *t = theKernelObjects.Get<PspThread>(threadID, error);
		if (t)
		{
			return t->waitValue;
		}
		else
		{
			errorf(ThreadManForUser,"__KernelGetWaitValue ERROR: thread %i", threadID);
			return 0;
		}
	}

	void __KernelWakeThread(SceUID threadID, u32 returnStatus)
	{
		u32 error;
		PspThread *t = theKernelObjects.Get<PspThread>(threadID, error);
		if (t)
		{
			t->nt.status &= ~THREADSTATUS_WAIT;
			if (t->nt.status & (THREADSTATUS_SUSPEND | THREADSTATUS_WAIT))
			{
				//damn, still sleeping..
			}
			else
			{
				t->nt.status |= THREADSTATUS_READY;
                PspThread::EnqueueReady(t);
			}
			//no need to clear waittype etc
		}
		else
		{
			errorf(ThreadManForUser,"__KernelWakeThread ERROR: thread %i", threadID);
		}
	}


	void HLEDECL sceKernelReferThreadStatus(AlContext &context)
	{
		SceUID threadID = context.gpr[ALLEGREX_A0];
		if (threadID == 0)
			threadID = __KernelGetCurThreadId();

		u32 error;
		PspThread *t = theKernelObjects.Get<PspThread>(threadID, error);
		if (t)
		{
			infof(ThreadManForUser,"sceKernelReferThreadStatus(%i, %08x)", threadID, context.gpr[ALLEGREX_A1]);
			void *outptr = Memory::addr< void >(context.gpr[ALLEGREX_A1]);
			int sz = sizeof(NativeThread);
			t->nt.nativeSize = sz;
			memcpy(outptr, &(t->nt), sz);
			context.gpr[ALLEGREX_V0] = 0;
		}
		else
		{
			errorf(ThreadManForUser,"sceReferThreadStatus Error %08x", error);
			context.gpr[ALLEGREX_V0] = error;
		}
	}

	// Switch a CPU context
	void __KernelSwitchContext(PspThread *t)
	{
        tracef(sceAudio, "__KernelSwitchContext: %31s --> %31s", CurrentThread->m_name, t->m_name);
        theEmulator.context = &t->m_thread_context;
        CurrentThread       = t;
        CurrentThread->nt.status = THREADSTATUS_RUN;
        t->Fiber::SwitchTo();
	}

	// DANGEROUS
	// Only run when you can safely accept a context switch
	// Triggers a waitable event, that is, it wakes up all threads that waits for it
	// If any changes were made, it will context switch if allowed
	bool __KernelTrigger(WaitType type, int id, bool reschedule)
	{
		bool doneAnything = false;

		for (u32 i = 0; i < threadqueue.size(); i++)
		{
			PspThread *t = threadqueue[i];
			if (t->nt.status & THREADSTATUS_WAIT)
			{
				if (t->nt.waitType == type && t->nt.waitID == id)
				{
					// This threads is waiting for the triggered object
					t->nt.status &= ~THREADSTATUS_WAIT;
					if (t->nt.status == 0)
                    {
						t->nt.status = THREADSTATUS_READY;
                        PspThread::EnqueueReady(t);
                        doneAnything = true;
                    }
				}
			}
		}

		if (doneAnything)
		{
            if (reschedule)
            {
			    __KernelReSchedule();
            }
            else
            {
                theEmulator.reschedule = true;
            }
			return true;
		}
		return false;
	}

	bool __KernelTrigger(Mutex &mutex, WaitType type, int id)
	{
		bool doneAnything = false;

		for (u32 i = 0; i < threadqueue.size(); i++)
		{
			PspThread *t = threadqueue[i];
			if (t->nt.status & THREADSTATUS_WAIT)
			{
				if (t->nt.waitType == type && t->nt.waitID == id)
				{
					// This threads is waiting for the triggered object
					t->nt.status &= ~THREADSTATUS_WAIT;
					if (t->nt.status == 0)
                    {
						t->nt.status = THREADSTATUS_READY;
                        PspThread::EnqueueReady(t);
                        doneAnything = true;
                    }
				}
			}
		}

		if (doneAnything)
		{
            mutex.Unlock();
    	    __KernelReSchedule();
			return true;
		}
		return false;
	}

	// makes the current thread wait for an event
	void __KernelWaitCurThread(Mutex &mutex, WaitType type, SceUID id, u32 value, bool processCallbacks)
	{
        hle::PspThread *that = CurrentThread;
		CurrentThread->nt.status = THREADSTATUS_WAIT;
		CurrentThread->nt.waitID = id;
		CurrentThread->nt.waitType = type;
		CurrentThread->nt.numReleases++;
		CurrentThread->waitValue = value;
		CurrentThread->isProcessingCallbacks = processCallbacks;
        CurrentThread->m_thread_context.gpr[ALLEGREX_V0] = 0;
        mutex.Unlock();
        __KernelReSchedule();
	}

    // makes the current thread wait for an event
    void __KernelWaitCurThread(WaitType type, SceUID id, u32 value, bool processCallbacks, bool reschedule)
    {
        hle::PspThread *that = CurrentThread;
        CurrentThread->nt.status = THREADSTATUS_WAIT;
        CurrentThread->nt.waitID = id;
        CurrentThread->nt.waitType = type;
        CurrentThread->nt.numReleases++;
        CurrentThread->waitValue = value;
        CurrentThread->isProcessingCallbacks = processCallbacks;
        CurrentThread->m_thread_context.gpr[ALLEGREX_V0] = 0;
        if (reschedule)
        {
            __KernelReSchedule();
        }
        else
        {
            theEmulator.reschedule = true;
        }
    }

    // makes the current thread wait for an event
    void __KernelWaitCurThread(AlContext &context, WaitType type, SceUID id, u32 value, bool processCallbacks, bool reschedule)
    {
        hle::PspThread *that = CurrentThread;
        CurrentThread->nt.status = THREADSTATUS_WAIT;
        CurrentThread->nt.waitID = id;
        CurrentThread->nt.waitType = type;
        CurrentThread->nt.numReleases++;
        CurrentThread->waitValue = value;
        CurrentThread->isProcessingCallbacks = processCallbacks;
        context.gpr[ALLEGREX_V0] = 0;
        if (reschedule)
        {
            __KernelReSchedule();
        }
        else
        {
            theEmulator.reschedule = true;
        }
    }

	void __KernelScheduleWakeup(int usFromNow)
	{
		PspTimeout *w = new PspTimeout;
        w->Clear();
        w->time   = KernelSysClock::Get() + u64(u32(usFromNow));
		w->thread = CurrentThread;
		timeouts.Enqueue(*w);
	}


    void __KernelReSchedule()
    {
        PspThread *t = 0;
        
        u64 time = KernelSysClock::Get();

        PspTimeout *w = 0;

        while (!timeouts.Empty() && (w = &timeouts.Front())->time <= time)
        {
            timeouts.Dequeue();

            __KernelWakeThread(w->thread->GetUid(), 0);

            delete w;
        }

        while ((t = PspThread::DequeueReady()))
        {
            if (t->nt.status == THREADSTATUS_READY)
            {
                break;
            }
        }

        if (t)
        {
            if (CurrentThread->nt.status == THREADSTATUS_RUN)
            {
                PspThread::EnqueueReady(CurrentThread);
            }

            __KernelSwitchContext(t);
        }
    }




	//////////////////////////////////////////////////////////////////////////
	// Thread Management
	//////////////////////////////////////////////////////////////////////////
	void HLEDECL sceKernelCheckThreadStack(AlContext &context)
	{
		infof(ThreadManForUser, "sceKernelCheckThreadStack() (returned 65536 (lie))");
		context.gpr[ALLEGREX_V0] = 65536; //Blatant lie
	}



	PspThread *__KernelCreateThread(SceUID &id, SceUID moduleID, const char *name, u32 entryPoint, u32 priority, int stacksize, u32 attr)
	{
		PspThread *t = new PspThread(name);
		id = t->GetUid();

		threadqueue.push_back(t);

        ::memset(&t->m_thread_context.gpr[ALLEGREX_ZR], 0, sizeof(u32)*32);
        ::memset(&t->m_thread_context.fpr[ALLEGREX_F0], 0, sizeof(f32)*32);
        ::memset(&t->m_thread_context.vpr[0          ], 0, sizeof(f32)*4*4*8);
        //::memset(&t->context.vcr[0          ], 0, sizeof(u32)*16);

        t->m_thread_context.fcr31 = 0;
        t->m_thread_context.fast = false;

        t->m_thread_context.vcr.Reset();
        t->m_thread_context.rnd.SetSeed(0x3f800001);

		//t->context.vcr[VFPU_CTRL_SPREFIX] = 0xe4; //passthru
		//t->context.vcr[VFPU_CTRL_TPREFIX] = 0xe4; //passthru
		//t->context.vcr[VFPU_CTRL_CC] = 0x3f; 

        memset(&t->nt, 0xCD, sizeof(t->nt));
		t->nt.attr = attr;
		t->nt.initialPriority = priority;
        t->nt.currentPriority = priority;
		t->m_thread_context.hilo = 0;
		t->m_thread_context.pc = entryPoint;
		t->nt.stackSize = stacksize;
		t->nt.status = THREADSTATUS_DORMANT;
		t->nt.waitType = WAITTYPE_NONE;
		t->nt.waitID = 0;
		t->waitValue = 0;
		t->nt.exitStatus = 0;
		t->nt.numInterruptPreempts = 0;
		t->nt.numReleases = 0;
		t->nt.numThreadPreempts = 0;
		t->nt.runForClocks.low = 0;
		t->nt.runForClocks.hi = 0;
		t->nt.wakeupCount = 0;
		strncpy(t->nt.name, name, 31);
		t->m_thread_context.gpr[ALLEGREX_GP] = __KernelGetModuleGP(moduleID); //m->gp_value;
		t->m_thread_context.gpr[ALLEGREX_RA] = threadHackAddr; //hack! TODO fix
		t->GrabStack(stacksize);
		return t;
	}

    SceUID curModule;
    void __KernelSetupInitThread(SceUID moduleID, int args, const char *argp, int prio, int stacksize, int attr) 
	{
		curModule = moduleID;
		//grab mips regs
		SceUID id;
		CurrentThread = __KernelCreateThread(id, moduleID, "SceThreadmanInit", theEmulator.context->pc, prio, stacksize, attr);

		strncpy(CurrentThread->nt.name, "SceThreadmanInit", 31);

        CurrentThread->m_thread_context.gpr[ALLEGREX_A0] = args;
        CurrentThread->m_thread_context.gpr[ALLEGREX_SP] -= 256;
        u32 location = CurrentThread->m_thread_context.gpr[ALLEGREX_SP];
        CurrentThread->m_thread_context.gpr[5] = location;
        ::memcpy(Memory::addr< void >(location), (const void *)argp, args);
		__KernelSwitchContext(CurrentThread);
    }

    static PspThread *IdleThread = 0;
    void __KernelSetupIdleThread()
    {
        SceUID id;
        IdleThread = __KernelCreateThread(id, curModule, "SceThreadmanIdle", threadHackAddr + 8, MAX_THREAD_PRIORITY, THREAD_KSTACKSIZE, 0);
        IdleThread->nt.status = THREADSTATUS_READY; // do not schedule

        IdleThread->m_thread_context.gpr[ALLEGREX_A0] = 0;
        IdleThread->m_thread_context.gpr[ALLEGREX_A1] = 0;
        IdleThread->m_thread_context.gpr[ALLEGREX_RA] = threadHackAddr + 8;

        strncpy(IdleThread->nt.name, "SceThreadmanIdle", 31);
        readyqueue.Enqueue(*IdleThread);
    }

    static PspThread *CleanerThread = 0;
    void __KernelSetupCleanUpThread()
    {
        SceUID id;
        CleanerThread = __KernelCreateThread(id, curModule, "SceThreadmanCleaner", 0, 1, THREAD_KSTACKSIZE, 0);
        CleanerThread->nt.status = THREADSTATUS_WAIT; // do not schedule

        CleanerThread->m_thread_context.gpr[ALLEGREX_A0] = 0;
        CleanerThread->m_thread_context.gpr[ALLEGREX_A1] = 0;

        strncpy(CleanerThread->nt.name, "SceThreadmanCleaner", 31);
        readyqueue.Enqueue(*IdleThread);
    }


	void HLEDECL sceKernelCreateThread(AlContext &context)
	{
		u32 nameAddr = context.gpr[ALLEGREX_A0];
		const char *threadName = Memory::addr< const char >(nameAddr);
		u32 entry = context.gpr[ALLEGREX_A1];
		u32 prio  = context.gpr[ALLEGREX_A2];
		int stacksize = context.gpr[ALLEGREX_A3];
		u32 attr  = context.gpr[ALLEGREX_A4];
		//ignore context.gpr[ALLEGREX_A5] 
		SceUID id;
		PspThread *t = __KernelCreateThread(id, curModule, threadName, entry, prio, stacksize, attr);
		infof(ThreadManForUser,"%i = sceKernelCreateThread(name=\"%s\", entry=0x%08X, prio=%d, stacksize=%i )", id, threadName, entry, prio, stacksize);
		context.gpr[ALLEGREX_V0] = id;
	}


	void HLEDECL sceKernelStartThread(AlContext &context)
	{
		int threadToStartID = context.gpr[ALLEGREX_A0];
		u32 argSize = context.gpr[ALLEGREX_A1];
		u32 argBlockPtr = context.gpr[ALLEGREX_A2];

		if (threadToStartID != CurrentThread->GetUid())
		{
			u32 error;
			PspThread *startThread = theKernelObjects.Get<PspThread>(threadToStartID, error);
			if(startThread)//make sure a thread is there...
			{
				if (startThread->nt.status != THREADSTATUS_DORMANT)
				{
				//Not dormant, WTF? TODO
				}

				infof(ThreadManForUser,"sceKernelStartThread(thread=%i, argSize=%i, argPtr= %08x )",
				threadToStartID,argSize,argBlockPtr);

				context.gpr[ALLEGREX_V0] = 0; //return success (this does not exit this function)
			
				u32 sp = startThread->m_thread_context.gpr[ALLEGREX_SP];
				startThread->m_thread_context.gpr[ALLEGREX_A0] = argSize;
				startThread->m_thread_context.gpr[ALLEGREX_A1] = sp; 

				//now copy argument to stack
				::memcpy(Memory::addr< char >(sp), Memory::addr< char >(argBlockPtr), (int)argSize);

                startThread->nt.status = THREADSTATUS_READY;
                PspThread::EnqueueReady(startThread);
            }
			else
			{
               infof(ThreadManForUser,"thread %i trying to start a thread that doesn't exist", threadToStartID);
			}
		}
		else
		{
			infof(ThreadManForUser,"thread %i trying to start itself", threadToStartID);
			context.gpr[ALLEGREX_V0] = -1;
		}
	}

	//This one is fake but necessary :)
    void HLEDECL _sceKernelReturnFromThread(AlContext &context)
    {
        infof(ThreadManForUser,"_sceKernelReturnFromThread");
        CurrentThread->nt.exitStatus = CurrentThread->m_thread_context.gpr[2];
        CurrentThread->nt.status = THREADSTATUS_DORMANT;

        //Find threads that waited for me
        // Wake them
        if (!__KernelTrigger(WAITTYPE_THREADEND, __KernelGetCurThreadId()))
            __KernelReSchedule();
    }

    
    void HLEDECL _sceKernelIdleThread(AlContext &context)
    {
        infof(ThreadManForUser, "_sceKernelldle");
        if (!theEmulator.IsLeaving())
        {
            __KernelReSchedule();
        }
    }

	void HLEDECL sceKernelExitThread(AlContext &context)
	{
        CurrentThread->nt.exitStatus = context.gpr[ALLEGREX_A0];
        CurrentThread->nt.status = THREADSTATUS_DORMANT;
		//PspThread &t = threadqueue[currentThread];
		infof(ThreadManForUser,"sceKernelExitThread FAKED");
		//Find threads that waited for me
		// Wake them
        
        __KernelTrigger(WAITTYPE_THREADEND, __KernelGetCurThreadId());

	}

	void HLEDECL sceKernelExitDeleteThread(AlContext &context)
	{
		infof(ThreadManForUser,"sceKernelExitDeleteThread FAKED");
        CurrentThread->nt.exitStatus = context.gpr[ALLEGREX_A0];
        CurrentThread->nt.status = THREADSTATUS_DORMANT;
        //currentThread->nt.status = THREADSTATUS_DEAD;
        //CleanerThread->nt.status = THREADSTATUS_READY;
		if (!__KernelTrigger(WAITTYPE_THREADEND, __KernelGetCurThreadId()))
			__KernelReSchedule();
	}	


	void _sceKernelExitThread(AlContext &context)
	{
		//PspThread &t = threads[currentThread];
		infof(ThreadManForUser,"_sceKernelExitThread FAKED");
        CurrentThread->nt.status = THREADSTATUS_DORMANT;
		CurrentThread->nt.exitStatus = CurrentThread->m_thread_context.gpr[2];
		//Find threads that waited for me
		// Wake them
		if (!__KernelTrigger(WAITTYPE_THREADEND, __KernelGetCurThreadId()))
			__KernelReSchedule();
	}


	void HLEDECL sceKernelRotateThreadReadyQueue(AlContext &context)
	{
		infof(ThreadManForUser,"sceKernelRotateThreadReadyQueue : rescheduling");
		__KernelReSchedule();
	}

	void HLEDECL sceKernelDeleteThread(AlContext &context)
	{
		int threadno = context.gpr[ALLEGREX_A0];
		if (threadno != CurrentThread->GetUid())
		{
            PspThread *deletedThread;
            if ((context.gpr[ALLEGREX_V0] = theKernelObjects.Get(threadno, deletedThread)) >= 0)
            {
			    //TODO: remove from threadqueue!
			    infof(ThreadManForUser,"sceKernelDeleteThread(%i)",threadno);
			    context.gpr[ALLEGREX_V0] = theKernelObjects.Release<PspThread>(threadno);
			    if (!__KernelTrigger(WAITTYPE_THREADEND, threadno))
                {
                    //threadqueue.erase(std::find(threadqueue.begin(), threadqueue.end(), deletedThread));
				    __KernelReSchedule();
                }
            }
		}
		else
		{
			infof(ThreadManForUser, "Thread \"%s\" tries to delete itself! :(",CurrentThread->GetName());
			context.gpr[ALLEGREX_V0] = -1;
		}
	}


	void HLEDECL sceKernelTerminateDeleteThread(AlContext &context)
	{
		int threadno = context.gpr[ALLEGREX_A0];
		if (threadno != CurrentThread->GetUid())
		{
			//TODO: remove from threadqueue!
			infof(ThreadManForUser,"sceKernelTerminateDeleteThread(%i)",threadno);
			context.gpr[ALLEGREX_V0] = 0; //kernel_objects.Release<PspThread>(threadno));
			if (!__KernelTrigger(WAITTYPE_THREADEND, threadno))
				__KernelReSchedule();
		}
		else
		{
			infof(ThreadManForUser, "Thread \"%s\" tries to delete itself! :(",CurrentThread->GetName());
			context.gpr[ALLEGREX_V0] = -1;
		}
	}
    void HLEDECL sceKernelTerminateThread(AlContext &context)
	{
	/*	int threadno = context.gpr[ALLEGREX_A0];
		if (threadno != currentThread->get_uid())
		{
			//TODO: remove from threadqueue!
			infof(ThreadManForUser,"sceKernelTerminateDeleteThread(%i)",threadno);
			context.gpr[ALLEGREX_V0] = 0; //kernel_objects.Release<PspThread>(threadno));
			if (!__KernelTrigger(WAITTYPE_DELAY, threadno))
				__KernelReSchedule();
		}
		else
		{
			infof(ThreadManForUser, "Thread \"%s\" tries to delete itself! :(",currentThread->get_name());
			RETURN(-1);
		}*/
	}


    u32 *__KernelGetCurThreadStatus()
    {
        return &CurrentThread->nt.status;
    }

    SceUID __KernelGetCurThreadId()
    {
        return CurrentThread->GetUid();
    }


	void HLEDECL sceKernelGetThreadId(AlContext &context)
	{
		u32 retVal = CurrentThread->GetUid();
		infof(ThreadManForUser,"%i = sceKernelGetThreadId()", retVal);
		context.gpr[ALLEGREX_V0] = retVal;
	}
	void HLEDECL sceKernelChangeCurrentThreadAttr(AlContext &context)
	{
		int clearAttr = context.gpr[ALLEGREX_A0];
		int setAttr = context.gpr[ALLEGREX_A1];
		infof(ThreadManForUser,"0 = sceKernelChangeCurrentThreadAttr(clear = %08x, set = %08x", clearAttr, setAttr);
		CurrentThread->nt.attr = (CurrentThread->nt.attr & ~clearAttr) | setAttr;
		context.gpr[ALLEGREX_V0] = 0;
	}

	void HLEDECL sceKernelChangeThreadPriority(AlContext &context)
	{
		int id = context.gpr[ALLEGREX_A0];
		if (id == 0) id = CurrentThread->GetUid(); //special

		u32 error;
		PspThread *thread = theKernelObjects.Get<PspThread>(id, error);
		if (thread)
		{
			infof(ThreadManForUser,"sceKernelChangeThreadPriority(%i, %i)", id, context.gpr[ALLEGREX_A1]);
            thread->nt.currentPriority = context.gpr[ALLEGREX_A1];
            while (PspThread::DequeueReady());
            for (u32 i = 0; i < threadqueue.size(); ++i)
            {
                PspThread *t = threadqueue[i];
                if (t->nt.status == THREADSTATUS_READY)
                {
                    PspThread::EnqueueReady(t);
                }
            }
			context.gpr[ALLEGREX_V0] = 0;
            //__KernelReSchedule();
		}
		else
		{
			infof(ThreadManForUser,"%08x=sceKernelChangeThreadPriority(%i, %i) failed", error);
			context.gpr[ALLEGREX_V0] = error;
		}
	}

	void HLEDECL sceKernelDelayThreadCB(AlContext &context)
	{
		u32 usec=context.gpr[ALLEGREX_A0];
		infof(ThreadManForUser,"sceKernelDelayThreadCB(%i usec)",usec);

		__KernelScheduleWakeup(usec);
		__KernelWaitCurThread(context, WAITTYPE_DELAY, 0, 0, true);
	}
	void HLEDECL sceKernelDelayThread(AlContext &context)
	{
		u32 usec=context.gpr[ALLEGREX_A0];
		infof(ThreadManForUser,"sceKernelDelayThread(%i usec)",usec);
		__KernelScheduleWakeup(usec);
		__KernelWaitCurThread(context, WAITTYPE_DELAY, 0, 0, false);
	}

	//////////////////////////////////////////////////////////////////////////
	// WAIT/SLEEP ETC
	//////////////////////////////////////////////////////////////////////////
	void HLEDECL sceKernelWakeupThread(AlContext &context)
	{
		SceUID id = context.gpr[ALLEGREX_A0];
		u32 error;
		PspThread *t = theKernelObjects.Get<PspThread>(id, error);
		if (t)
		{
			t->nt.wakeupCount++;
			infof(ThreadManForUser,"sceKernelWakeupThread(%i) - wakeupCount incremented to %i",id,t->nt.wakeupCount);
			if (t->nt.waitType == WAITTYPE_SLEEP && t->nt.wakeupCount>=0)
			{
				__KernelWakeThread(id, 0);
			}
		}
		context.gpr[ALLEGREX_V0] = 0;
	}

	void HLEDECL sceKernelSleepThread(AlContext &context)
	{
		CurrentThread->nt.wakeupCount--;
		infof(ThreadManForUser,"sceKernelSleepThread() - wakeupCount decremented to %i", CurrentThread->nt.wakeupCount);
		if (CurrentThread->nt.wakeupCount < 0)
        {
			__KernelWaitCurThread(context, WAITTYPE_SLEEP, 0, 0, false);
        }
		else
		{
			context.gpr[ALLEGREX_V0] = 0;
		}
	}

	//the homebrew PollCallbacks
	void HLEDECL sceKernelSleepThreadCB(AlContext &context)
	{
		infof(ThreadManForUser,"sceKernelSleepThreadCB()");
		//set it to waiting
		__KernelWaitCurThread(context, WAITTYPE_SLEEP, 0, 0, true);
	}

	void HLEDECL sceKernelWaitThreadEnd(AlContext &context)
	{
		SceUID id = context.gpr[ALLEGREX_A0];
		infof(ThreadManForUser,"sceKernelWaitThreadEnd(%i)",id);
		u32 error;
		PspThread *t = theKernelObjects.Get<PspThread>(id, error);
		if (t)
		{
			if (t->nt.status != THREADSTATUS_DORMANT)
			{
				__KernelWaitCurThread(context, WAITTYPE_THREADEND, id, 0, false);
				return;
			}
			infof(ThreadManForUser,"sceKernelWaitThreadEnd - thread %i already ended. Doing nothing.", id);
		}
		else
		{
			infof(ThreadManForUser,"sceKernelWaitThreadEnd - bad thread %i", id);
		}
		context.gpr[ALLEGREX_V0] = 0;
	}

	void HLEDECL sceKernelSuspendThread(AlContext &context)
	{
		infof(ThreadManForUser,"UNIMPL sceKernelSuspendThread");
		context.gpr[ALLEGREX_V0] = 0;
	}

	void HLEDECL sceKernelResumeThread(AlContext &context)
	{
		infof(ThreadManForUser,"UNIMPL sceKernelResumeThread");
		context.gpr[ALLEGREX_V0] = 0;
	}

}

void Emulator::Reschedule()
{
    hle::__KernelReSchedule();
}
