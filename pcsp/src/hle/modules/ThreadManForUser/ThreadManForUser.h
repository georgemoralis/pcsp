#ifndef ThreadManForUser_h__
#define ThreadManForUser_h__

#include "hle/kernel/kernel_object.h"
#include "hle/kernel/kernel_thread.h"
#include "hle/kernel/kernel_fpl.h"
#include "hle/kernel/kernel_vpl.h"

namespace Log
{
    extern LogSubCategory sceKernelGetSystemTime;
    extern LogSubCategory sceKernelGetSystemTimeWide;
    extern LogSubCategory sceKernelGetSystemTimeLow;

    extern LogSubCategory sceKernelCreateFpl;
    extern LogSubCategory sceKernelDeleteFpl;
    extern LogSubCategory sceKernelAllocateFpl;
    extern LogSubCategory sceKernelAllocateFplCB;
    extern LogSubCategory sceKernelTryAllocateFpl;
    extern LogSubCategory sceKernelFreeFpl;
    extern LogSubCategory sceKernelCancelFpl;
    extern LogSubCategory sceKernelReferFplStatus;

    extern LogSubCategory sceKernelCreateVpl;
    extern LogSubCategory sceKernelDeleteVpl;
    extern LogSubCategory sceKernelAllocateVpl;
    extern LogSubCategory sceKernelAllocateVplCB;
    extern LogSubCategory sceKernelTryAllocateVpl;
    extern LogSubCategory sceKernelFreeVpl;
    extern LogSubCategory sceKernelCancelVpl;
    extern LogSubCategory sceKernelReferVplStatus;
}

namespace ThreadManForUser
{
    extern bool Reboot();
    extern bool ShutDown();

	///Main Thread functions

    extern int sceKernelCreateThread(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5);
    extern int sceKernelDeleteThread(u32 a0);
    extern int sceKernelStartThread(u32 a0, u32 a1, u32 a2); 
	extern int sceKernelExitThread(u32 a0);
	extern int sceKernelExitDeleteThread(u32 a0); 
    extern int sceKernelTerminateThread(); 
	extern int sceKernelTerminateDeleteThread(); 
	extern int sceKernelSuspendDispatchThread(); 
	extern int sceKernelResumeDispatchThread(); 
	extern int sceKernelChangeCurrentThreadAttr(); 
    extern int sceKernelChangeThreadPriority(u32 a0, u32 a1);
	extern int sceKernelRotateThreadReadyQueue();
    extern int sceKernelReleaseWaitThread();  
	extern int sceKernelGetThreadId(); 
	extern int sceKernelGetThreadCurrentPriority(); 
	extern int sceKernelGetThreadExitStatus(u32 a0); 
    extern int sceKernelReferThreadStatus(); 
	extern int sceKernelReferThreadRunStatus(); 
	extern int sceKernelCheckThreadStack();
	extern int sceKernelGetThreadStackFreeSize(u32 a0);
    
    extern void _sceKernelStartThread();
	extern void _sceKernelExitThread(); 

	/// EVH ///

    extern int sceKernelRegisterThreadEventHandler();
    extern int sceKernelReleaseThreadEventHandler(); 
	extern int sceKernelReferThreadEventHandlerStatus();

	/// SLEEP/SUSPEND/WAITEND ///

	extern int sceKernelSleepThread(); 
    extern int sceKernelSleepThreadCB();
    extern int sceKernelWakeupThread();
	extern int sceKernelCancelWakeupThread(); 
	extern int sceKernelSuspendThread(); 
    extern int sceKernelResumeThread(); 
	extern int sceKernelWaitThreadEnd(); 
    extern int sceKernelWaitThreadEndCB(); 

    /// SEMA ///

    extern int sceKernelCreateSema();
    extern int sceKernelDeleteSema();
    extern int sceKernelSignalSema(); 
    extern int sceKernelWaitSema(); 
    extern int sceKernelWaitSemaCB();
    extern int sceKernelPollSema();
    extern int sceKernelCancelSema();
	extern int sceKernelReferSemaStatus();

	/// EVENTFLAG ///

    extern int sceKernelCreateEventFlag();
    extern int sceKernelDeleteEventFlag();
    extern int sceKernelSetEventFlag();
    extern int sceKernelClearEventFlag(); 
    extern int sceKernelWaitEventFlag(); 
    extern int sceKernelWaitEventFlagCB();
	extern int sceKernelPollEventFlag(); 
	extern int sceKernelCancelEventFlag();
	extern int sceKernelReferEventFlagStatus(); 

	/// MBX ///

    extern int sceKernelCreateMbx();
    extern int sceKernelDeleteMbx(); 
    extern int sceKernelSendMbx(); 	
    extern int sceKernelReceiveMbx(); 
    extern int sceKernelReceiveMbxCB(); 
    extern int sceKernelPollMbx();
    extern int sceKernelCancelReceiveMbx(); 
    extern int sceKernelReferMbxStatus();

    /// MPP ///
    extern int sceKernelCreateMsgPipe(); 
    extern int sceKernelDeleteMsgPipe();
	extern int sceKernelSendMsgPipe(); 
   	extern int sceKernelSendMsgPipeCB(); 
	extern int sceKernelTrySendMsgPipe();
	extern int sceKernelReceiveMsgPipe(); 
    extern int sceKernelReceiveMsgPipeCB(); 
    extern int sceKernelTryReceiveMsgPipe();
	extern int sceKernelCancelMsgPipe(); 
	extern int sceKernelReferMsgPipeStatus(); 

    /// VPL ///

    extern int sceKernelCreateVpl(u32 a0, u32 a1, u32 a2, u32 a3, u32 t0);
    extern int sceKernelDeleteVpl(u32 a0);
    extern int sceKernelAllocateVpl(u32 a0, u32 a1, u32 a2, u32 a3);
    extern int sceKernelAllocateVplCB(u32 a0, u32 a1, u32 a2, u32 a3);
    extern int sceKernelTryAllocateVpl(u32 a0, u32 a1, u32 a2);
    extern int sceKernelFreeVpl(u32 a0, u32 a1);
    extern int sceKernelCancelVpl(u32 a0, u32 a1);
    extern int sceKernelReferVplStatus(u32 a0, u32 a1);

	/// FPL ///

    extern int sceKernelCreateFpl(u32 a0, u32 a1, u32 a2, u32 a3, u32 t0, u32 t1);
    extern int sceKernelDeleteFpl(u32 a0);
    extern int sceKernelAllocateFpl(u32 a0, u32 a1, u32 a2);
    extern int sceKernelAllocateFplCB(u32 a0, u32 a1, u32 a2);
    extern int sceKernelTryAllocateFpl(u32 a0, u32 a1);
    extern int sceKernelFreeFpl(u32 a0, u32 a1);
    extern int sceKernelCancelFpl(u32 a0, u32 a1);
    extern int sceKernelReferFplStatus(u32 a0, u32 a1);

    /// TIME/SOFT TIME MANAGEMENT ///

    extern int sceKernelGetSystemTime(u32 a0); 
	extern int sceKernelGetSystemTimeLow(u32 a0); 
	extern u64 sceKernelGetSystemTimeWide(); 
	extern int sceKernelSysClock2USec(u32 a0, u32 a1, u32 a2); 
	extern int sceKernelSysClock2USecWide(u64 a1a0, u32 a2, u32 a3); 
	extern int sceKernelUSec2SysClock(u32 a0, u32 a1); 
	extern u64 sceKernelUSec2SysClockWide(u32 a0); 

	////// DELAY ///

    extern int sceKernelDelayThread(); 
    extern int sceKernelDelayThreadCB();    
    extern int sceKernelDelaySysClockThread(); 
    extern int sceKernelDelaySysClockThreadCB();

    ////// ALARM ///

    extern int sceKernelSetAlarm();
    extern int sceKernelSetSysClockAlarm(); 
    extern int sceKernelCancelAlarm();
	extern int sceKernelReferAlarmStatus(); 

    ////// VTIMER ///

    extern int sceKernelCreateVTimer(); 
    extern int sceKernelDeleteVTimer(); 
    extern int sceKernelGetVTimerBase(); 
    extern int sceKernelGetVTimerTime(); 
    extern int sceKernelSetVTimerTime(); 
    extern int sceKernelStartVTimer();
    extern int sceKernelStopVTimer(); 
    extern int sceKernelSetVTimerHandler(); 
    extern int sceKernelCancelVTimerHandler(); 
    extern int sceKernelGetVTimerBaseWide(); 
    extern int sceKernelGetVTimerTimeWide(); 
	extern int sceKernelSetVTimerTimeWide(); 
	extern int sceKernelSetVTimerHandlerWide(); 
	extern int sceKernelReferVTimerStatus(); 
	extern int _sceKernelReturnFromTimerHandler(); 

    /// CALLBACK ///

	extern int sceKernelCreateCallback(u32 a0, u32 a1, u32 a2); 
	extern int sceKernelDeleteCallback(u32 a0); 
	extern int sceKernelNotifyCallback(u32 a0, u32 a1); 
	extern int sceKernelGetCallbackCount(u32 a0);
	extern int sceKernelCancelCallback(u32 a0);
    extern int sceKernelCheckCallback();
	extern int sceKernelReferCallbackStatus(u32 a0, u32 a1); 
	extern int _sceKernelReturnFromCallback(); 

	/// SYSTEM STATUS ///

    extern int sceKernelReferSystemStatus();
    extern int sceKernelGetThreadmanIdList(); 
	extern int sceKernelGetThreadmanIdType(); 

    /// MUTEX ///

	extern int sceKernelCreateMutex(); 
	extern int sceKernelDeleteMutex(); 
    extern int sceKernelTryLockMutex(); 
    extern int sceKernelLockMutex();
    extern int sceKernelLockMutexCB(); 
    extern int sceKernelUnlockMutex();
    extern int sceKernelCancelMutex(); 
    extern int sceKernelReferMutexStatus(); 

    /// LWMUTEX ///

    extern int sceKernelCreateLwMutex(); 
    extern int sceKernelDeleteLwMutex();
    extern int sceKernelReferLwMutexStatusByID(); 

	/// MISC. ///

    extern int sceKernelReferGlobalProfiler(); 
    extern int sceKernelReferThreadProfiler(); 
    extern int sceKernelDonateWakeupThread(); 

    /// UNKNOWN ///

	extern int ThreadManForUser_BEED3A47(); 
	extern int ThreadManForUser_8672E3D0(); 	
	extern int ThreadManForUser_7CFF8CF3(); 
	extern int ThreadManForUser_71040D5C(); 
	extern int ThreadManForUser_31327F19(); 	
}

namespace threadman
{
    /// TIME/SOFT TIME MANAGEMENT ///
	extern int hleKernelGetSystemTime(SceKernelSysClock *sysclk);
    extern int hleKernelGetSystemTimeLow();
    extern u64 hleKernelGetSystemTimeWide();
    extern int hleKernelSysClock2USec(SceKernelSysClock *sysclk, u32 *sec, u32 *usec);
    extern int hleKernelSysClock2USecWide(u64 clk, u32 *sec, u32 *usec);
    extern int hleKernelUSec2SysClock(u32 usec, SceKernelSysClock *sysclk);
    extern u64 hleKernelUSec2SysClockWide(u32 usec);

    /// FPL ///
	extern int hleKernelCreateFpl(char const *name, SceUID partition_uid, SceUInt attributes, SceSize block_size, int block_count, SceKernelFplOptParam *opt_param);
	extern int hleKernelDeleteFpl(SceUID uid);
	extern int hleKernelAllocateFpl(SceUID uid, u32 *addr, SceUInt *timeout);
	extern int hleKernelAllocateFplCB(SceUID uid, u32 *addr, SceUInt *timeout);
	extern int hleKernelTryAllocateFpl(SceUID uid, u32 *addr);
    extern int hleKernelFreeFpl(SceUID uid, u32 addr);
    extern int hleKernelCancelFpl(SceUID uid, int *waiting_threads);
    extern int hleKernelReferFplStatus(SceUID uid, SceKernelFplInfo *info);

    /// VPL ///
	extern int hleKernelCreateVpl(char const *name, SceUID partition_uid, SceUInt attributes, SceSize size, SceKernelFplOptParam *opt_param);
    extern int hleKernelDeleteVpl(SceUID uid);
	extern int hleKernelAllocateVpl(SceUID uid, SceSize size, u32 *addr, SceUInt *timeout);
	extern int hleKernelAllocateVplCB(SceUID uid, SceSize size, u32 *addr, SceUInt *timeout);
	extern int hleKernelTryAllocateVpl(SceUID uid, SceSize size, u32 *addr);
    extern int hleKernelFreeVpl(SceUID uid, u32 addr);
    extern int hleKernelCancelVpl(SceUID uid, int *waiting_threads);
    extern int hleKernelReferVplStatus(SceUID uid, SceKernelVplInfo *info);
}
#endif // ThreadManForUser_h__
