#pragma once

#include "common_defines.h"
#include "hle/kernel/kernel_types.h"

namespace hle
{
	extern void HLEDECL sceKernelChangeThreadPriority(AlContext &context);
	extern void HLEDECL sceKernelCreateThread(AlContext &context);
	extern void HLEDECL sceKernelDelayThread(AlContext &context);
	extern void HLEDECL sceKernelDelayThreadCB(AlContext &context);
	extern void HLEDECL sceKernelDeleteThread(AlContext &context);
	extern void HLEDECL sceKernelExitDeleteThread(AlContext &context);
	extern void HLEDECL sceKernelExitThread(AlContext &context);
	extern void HLEDECL _sceKernelExitThread(AlContext &context);
	extern void HLEDECL sceKernelGetThreadId(AlContext &context);
	extern void HLEDECL sceKernelStartThread(AlContext &context);
	extern void HLEDECL sceKernelWaitThreadEnd(AlContext &context);
	extern void HLEDECL sceKernelReferThreadStatus(AlContext &context);
	extern void HLEDECL sceKernelChangeCurrentThreadAttr(AlContext &context);
	extern void HLEDECL sceKernelRotateThreadReadyQueue(AlContext &context);
	extern void HLEDECL sceKernelCheckThreadStack(AlContext &context);
	extern void HLEDECL sceKernelSuspendThread(AlContext &context);
	extern void HLEDECL sceKernelResumeThread(AlContext &context);
	extern void HLEDECL sceKernelWakeupThread(AlContext &context);
	extern void HLEDECL sceKernelTerminateDeleteThread(AlContext &context);
	extern void HLEDECL sceKernelTerminateThread(AlContext &context);
	extern void HLEDECL sceKernelSleepThread(AlContext &context); 
	extern void HLEDECL sceKernelSleepThreadCB(AlContext &context); 
	
    extern void __KernelThreadingInit();
	extern void __KernelThreadingShutdown();
	

	enum WaitType //probably not the real values
	{
		WAITTYPE_NONE         = 0,
		WAITTYPE_THREAD       = 1,
		WAITTYPE_SEMA         = 2,
		WAITTYPE_EVENTFLAG    = 3,
		WAITTYPE_MBX          = 4,
		WAITTYPE_VPL          = 5,
		WAITTYPE_FPL          = 6,
		WAITTYPE_THREADEND    = 9,
		WAITTYPE_AUDIOCHANNEL = 10, // this is fake, should be replaced with 8 eventflags
        WAITTYPE_UMD          = 11, // this is fake, should be replaced with 1 eventflag
        WAITTYPE_VSYNC        = 12, // this is fake
        WAITTYPE_SLEEP        = 64,
        WAITTYPE_DELAY        = 65,
        WAITTYPE_SUSPEND      = 66,
        WAITTYPE_DORMANT      = 67,
	};


	extern bool __KernelTrigger(WaitType type, int id, bool reschedule = true);
	extern bool __KernelTrigger(Mutex &mutex, WaitType type, int id);
	extern u32  __KernelGetWaitValue(SceUID threadID, u32 &error);
	extern void __KernelWakeThread(SceUID threadID, u32 returnStatus);
    extern void __KernelWaitCurThread(AlContext &context, WaitType type, SceUID id, u32 value = 0, bool processCallbacks = false, bool reschedule = true);
    extern void __KernelWaitCurThread(WaitType type, SceUID id, u32 value = 0, bool processCallbacks = false, bool reschedule = true);
	extern void __KernelWaitCurThread(Mutex &mutex, WaitType type, SceUID id, u32 value = 0, bool processCallbacks = false);
	extern void __KernelReSchedule();
    extern void __KernelScheduleWakeup(int threadnumber);

    extern u32   *__KernelGetCurThreadStatus();
    extern SceUID __KernelGetCurThreadId();
    extern void   __KernelSetupInitThread(SceUID moduleId, int args, const char *argp, int prio, int stacksize, int attr); //represents the real PSP elf loader, run before execution
    extern void   __KernelSetupIdleThread();
    extern void   __KernelSetupCleanerThread();

    extern void HLEDECL _sceKernelReturnFromThread(AlContext &context);
    extern void HLEDECL _sceKernelIdleThread(AlContext &context);
}

