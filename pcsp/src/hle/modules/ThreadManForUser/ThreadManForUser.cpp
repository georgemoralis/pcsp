#include "stdafx.h"
#include "ThreadManForUser.h"
#include "hle/types.h"
#include "hle/kernel.h"
#include "hle/modules/sysmem/sysmem.h"
#include "log.h"

namespace hle
{
    extern void __KernelThreadingInit();
    extern void __KernelThreadingShutdown();
}

LogSubCategory Log::sceKernelGetSystemTime     (Log::ThreadManForUser, "sceKernelGetSystemTime");
LogSubCategory Log::sceKernelGetSystemTimeWide (Log::ThreadManForUser, "sceKernelGetSystemTimeWide");
LogSubCategory Log::sceKernelGetSystemTimeLow  (Log::ThreadManForUser, "sceKernelGetSystemTimeLow");

LogSubCategory Log::sceKernelCreateFpl         (Log::ThreadManForUser, "sceKernelCreateFpl");
LogSubCategory Log::sceKernelDeleteFpl         (Log::ThreadManForUser, "sceKernelDeleteFpl");
LogSubCategory Log::sceKernelAllocateFpl       (Log::ThreadManForUser, "sceKernelAllocateFpl");
LogSubCategory Log::sceKernelAllocateFplCB     (Log::ThreadManForUser, "sceKernelAllocateFplCB");
LogSubCategory Log::sceKernelTryAllocateFpl    (Log::ThreadManForUser, "sceKernelTryAllocateFpl");
LogSubCategory Log::sceKernelFreeFpl           (Log::ThreadManForUser, "sceKernelFreeFpl");
LogSubCategory Log::sceKernelCancelFpl         (Log::ThreadManForUser, "sceKernelCancelFpl");
LogSubCategory Log::sceKernelReferFplStatus    (Log::ThreadManForUser, "sceKernelReferFplStatus");

LogSubCategory Log::sceKernelCreateVpl         (Log::ThreadManForUser, "sceKernelCreateVpl");
LogSubCategory Log::sceKernelDeleteVpl         (Log::ThreadManForUser, "sceKernelDeleteVpl");
LogSubCategory Log::sceKernelAllocateVpl       (Log::ThreadManForUser, "sceKernelAllocateVpl");
LogSubCategory Log::sceKernelAllocateVplCB     (Log::ThreadManForUser, "sceKernelAllocateVplCB");
LogSubCategory Log::sceKernelTryAllocateVpl    (Log::ThreadManForUser, "sceKernelTryAllocateVpl");
LogSubCategory Log::sceKernelFreeVpl           (Log::ThreadManForUser, "sceKernelFreeVpl");
LogSubCategory Log::sceKernelCancelVpl         (Log::ThreadManForUser, "sceKernelCancelVpl");
LogSubCategory Log::sceKernelReferVplStatus    (Log::ThreadManForUser, "sceKernelReferVplStatus");

namespace threadman
{
    /// TIME/SOFT TIME MANAGEMENT
	int hleKernelGetSystemTime(SceKernelSysClock *sysclk)
	{
        *sysclk = KernelSysClock::Get();
		return 0; 
	}

    int hleKernelGetSystemTimeLow()
	{
		return u32(hleKernelGetSystemTimeWide());
	}

    u64 hleKernelGetSystemTimeWide()
	{
	   return KernelSysClock::Get();
	}

    int hleKernelSysClock2USec(SceKernelSysClock *sysclk, u32 *sec, u32 *usec)
	{
        u64 clk = *sysclk;
        *sec  = (u32)(clk/1000000UL);
        *usec = (u32)(clk%1000000UL);
		return 0;
	}

    int hleKernelSysClock2USecWide(u64 clk, u32 *sec, u32 *usec)
	{
        *sec  = (u32)(clk/1000000UL);
        *usec = (u32)(clk%1000000UL);
		return 0;
	}

    int hleKernelUSec2SysClock(u32 usec, SceKernelSysClock *sysclk)
	{
        *sysclk = (u64)usec;
		return 0;
	}

    u64 hleKernelUSec2SysClockWide(u32 usec)
	{
		return (u64)usec;
	}

    /// FPL ///
	int hleKernelCreateFpl(char const *name, SceUID partition_uid, SceUInt attr, SceSize block_size, int block_count, SceKernelFplOptParam *opt_param)
	{
        int result = 0;

        int state = sceKernelCpuSuspendIntr();

        result = sysmem::hleKernelCreateHeap(partition_uid, block_size * block_count, 0, "FPL");
        
        if (result > 0)
        {
            KernelFpl *fpl = new KernelFpl((SceUID)result, block_size, block_count, attr, opt_param, name);

            result = fpl->GetUid();

            if (result <= 0)
            {
                delete fpl;
            }
        }

        sceKernelCpuResumeIntr(state);

        return result;
	}

	int hleKernelDeleteFpl(SceUID uid)
	{
        KernelFpl *fpl;

        int state = sceKernelCpuSuspendIntr();

        int result = theKernelObjects.Get(uid, fpl);

        if (!result)
        {
            sysmem::hleKernelDeleteHeap(fpl->m_heap_uid);

            delete fpl;
        }

        sceKernelCpuResumeIntr(state);

        return result;
	}


	int hleKernelAllocateFpl(SceUID uid, u32 *addr, SceUInt *timeout)
	{
        int result;

        KernelFpl *fpl;

        int state = sceKernelCpuSuspendIntr();

        result = theKernelObjects.Get(uid, fpl);

        if (!result)
        {
            result = fpl->Allocate(addr, timeout);
        }

        sceKernelCpuResumeIntr(state);

        return result;
	}
	int hleKernelAllocateFplCB(SceUID uid, u32 *addr, SceUInt *timeout)
	{
        int result;

        KernelFpl *fpl;

        int state = sceKernelCpuSuspendIntr();

        result = theKernelObjects.Get(uid, fpl);

        if (!result)
        {
            result = fpl->AllocateCB(addr, timeout);
        }

        sceKernelCpuResumeIntr(state);

        return result;
	}

	int hleKernelTryAllocateFpl(SceUID uid, u32 *addr)
	{
        int result;

        KernelFpl *fpl;

        int state = sceKernelCpuSuspendIntr();

        result = theKernelObjects.Get(uid, fpl);

        if (!result)
        {
            fpl->TryAllocate(addr);
        }

        sceKernelCpuResumeIntr(state);

        return result;
	}

    int hleKernelFreeFpl(SceUID uid, u32 addr)
	{
        int result;

        KernelFpl *fpl;

        int state = sceKernelCpuSuspendIntr();

        result = theKernelObjects.Get(uid, fpl);

        if (!result)
        {
            result = fpl->Free(addr);
        }

        sceKernelCpuResumeIntr(state);

        return result;
	}

    int hleKernelCancelFpl(SceUID uid, int *waiting_threads)
	{
        int result;

        KernelFpl *fpl;

        int state = sceKernelCpuSuspendIntr();

        result = theKernelObjects.Get(uid, fpl);

        if (!result)
        {
            result = fpl->Cancel(waiting_threads);
        }

        sceKernelCpuResumeIntr(state);

        return result;
	}

    int hleKernelReferFplStatus(SceUID uid, SceKernelFplInfo *info)
	{
        int result;

        KernelFpl *fpl;

        int state = sceKernelCpuSuspendIntr();

        result = theKernelObjects.Get(uid, fpl);

        if (!result)
        {
            result = fpl->ReferStatus(info);
        }

        sceKernelCpuResumeIntr(state);

        return result;
	}

    /// VPL ///
	int hleKernelCreateVpl(char const *name, SceUID partition_uid, SceUInt attr, SceSize size, SceKernelVplOptParam *opt_param)
	{
        int result = 0;

        int state = sceKernelCpuSuspendIntr();

        result = sysmem::hleKernelCreateHeap(partition_uid, size, 0, "FPL");
        
        if (result > 0)
        {
            KernelVpl *vpl = new KernelVpl((SceUID)result, size, attr, opt_param, name);

            result = vpl->GetUid();

            if (result <= 0)
            {
                delete vpl;
            }
        }

        sceKernelCpuResumeIntr(state);

        return result;
	}

	int hleKernelDeleteVpl(SceUID uid)
	{
        KernelVpl *vpl;

        int state = sceKernelCpuSuspendIntr();

        int result = theKernelObjects.Get(uid, vpl);

        if (!result)
        {
            delete vpl;
        }

        sceKernelCpuResumeIntr(state);

        return result;
	}


	int hleKernelAllocateVpl(SceUID uid, SceSize size, u32 *addr, SceUInt *timeout)
	{
        int result;

        KernelVpl *vpl;

        int state = sceKernelCpuSuspendIntr();

        result = theKernelObjects.Get(uid, vpl);

        if (!result)
        {
            result = vpl->Allocate(size, addr, timeout);
        }

        sceKernelCpuResumeIntr(state);

        return result;
	}

	int hleKernelAllocateVplCB(SceUID uid, SceSize size, u32 *addr, SceUInt *timeout)
	{
        int result;

        KernelVpl *vpl;

        int state = sceKernelCpuSuspendIntr();

        result = theKernelObjects.Get(uid, vpl);

        if (!result)
        {
            result = vpl->AllocateCB(size, addr, timeout);
        }

        sceKernelCpuResumeIntr(state);

        return result;
	}

	int hleKernelTryAllocateVpl(SceUID uid, SceSize size, u32 *addr)
	{
        int result;

        KernelVpl *vpl;

        int state = sceKernelCpuSuspendIntr();

        result = theKernelObjects.Get(uid, vpl);

        if (!result)
        {
            vpl->TryAllocate(size, addr);
        }

        sceKernelCpuResumeIntr(state);

        return result;
	}

    int hleKernelFreeVpl(SceUID uid, u32 addr)
	{
        int result;

        KernelVpl *vpl;

        int state = sceKernelCpuSuspendIntr();

        result = theKernelObjects.Get(uid, vpl);

        if (!result)
        {
            result = vpl->Free(addr);
        }

        sceKernelCpuResumeIntr(state);

        return result;
	}

    int hleKernelCancelVpl(SceUID uid, int *waiting_threads)
	{
        int result;

        KernelVpl *vpl;

        int state = sceKernelCpuSuspendIntr();

        result = theKernelObjects.Get(uid, vpl);

        if (!result)
        {
            result = vpl->Cancel(waiting_threads);
        }

        sceKernelCpuResumeIntr(state);

        return result;
	}

    int hleKernelReferVplStatus(SceUID uid, SceKernelVplInfo *info)
	{
        int result;

        KernelVpl *vpl;

        int state = sceKernelCpuSuspendIntr();

        result = theKernelObjects.Get(uid, vpl);

        if (!result)
        {
            result = vpl->ReferStatus(info);
        }

        sceKernelCpuResumeIntr(state);

        return result;
	}
}

namespace ThreadManForUser
{
    bool ready = false;
    bool Reboot()
    {
        if (!ready || ShutDown())
        {
            if (theKernelModuleManager.SyscallsModuleExists("SysMemUserForUser"))
            {
                //KernelTimer::Initialize();
                hle::__KernelThreadingInit();
                ready = true;
                return true;
            }
        }
        return false;
    }

    bool ShutDown()
    {
        if (ready)
        {
            hle::__KernelThreadingShutdown();
            //KernelTimer::Terminate();
            ready = false;
            return true;
        }
        return !ready;
    }

    ///Main Thread functions

    int sceKernelCreateThread(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5)
    {
        (void)a5;

        int intr = sceKernelCpuSuspendIntr();

        int result = KernelThread::Create(Memory::addr< char const >(a0), SceKernelThreadEntry(a1), int(a2), SceSize(a3), SceUInt(a4), intr);

        sceKernelCpuResumeIntr(intr);

        return result;
    }

    int sceKernelDeleteThread(u32 a0)
    {
        if (sceKernelIsIntrContext() || theKernelScheduler.m_current_thread->m_event_mask)
        {
            return SCE_KERNEL_ERROR_ILLEGAL_CONTEXT;
        }

        if (!a0)
        {
            return SCE_KERNEL_ERROR_ILLEGAL_THID;
        }

        int intr = sceKernelCpuSuspendIntr();

        KernelThread *deleted_thread;

        u32 error = theKernelObjects.Get(SceUID(a0), deleted_thread);
        if (error)
        {
            return SCE_KERNEL_ERROR_UNKNOWN_THID;
        }

        int result = deleted_thread->Delete(intr);

        sceKernelCpuResumeIntr(intr);

        return result;
    }

    int sceKernelStartThread(u32 a0, u32 a1, u32 a2)
    {
        int intr = sceKernelCpuSuspendIntr();

        KernelThread *starting_thread;

        if (SceUID(a0) == theKernelScheduler.m_current_thread->GetUid())
        {
            return SCE_KERNEL_ERROR_ILLEGAL_THID;
        }

        u32 error = theKernelObjects.Get(SceUID(a0), starting_thread);
        if (error)
        {
            return SCE_KERNEL_ERROR_UNKNOWN_THID;
        }

        int result = starting_thread->Start(SceSize(a1), a2, intr);

        sceKernelCpuResumeIntr(intr);

        return result;
    }

	int sceKernelExitThread(u32 a0)
	{
        KernelThread *exiting_thread = theKernelScheduler.m_current_thread;

        if (sceKernelIsIntrContext() || exiting_thread->m_event_mask)
        {
            return SCE_KERNEL_ERROR_ILLEGAL_CONTEXT;
        }

        if (int(a0) < 0)
        {
            a0 = SCE_KERNEL_ERROR_ILLEGAL_ARGUMENT;
        }

        exiting_thread->m_exit_status = a0;

        for (;;)
        {
            int intr = sceKernelCpuSuspendIntr();

            exiting_thread->Exit(int(a0), intr, false);

            sceKernelCpuResumeIntr(intr);
        }
    }

	int sceKernelExitDeleteThread(u32 a0)
	{
        KernelThread *exiting_thread = theKernelScheduler.m_current_thread;

        if (sceKernelIsIntrContext() || exiting_thread->m_event_mask)
        {
            return SCE_KERNEL_ERROR_ILLEGAL_CONTEXT;
        }

        if (int(a0) < 0)
        {
            a0 = SCE_KERNEL_ERROR_ILLEGAL_ARGUMENT;
        }

        exiting_thread->m_exit_status = a0;

        for (;;)
        {
            int intr = sceKernelCpuSuspendIntr();

            exiting_thread->Exit(int(a0), intr, true);

            sceKernelCpuResumeIntr(intr);
        }
	}

	int sceKernelTerminateThread()
	{
		//TODO implement me
		errorf(ThreadManForUser,"UNIMPLEMENTED sceKernelTerminateThread instruction");
		return 0;
	}

	int sceKernelTerminateDeleteThread()
	{
		//TODO implement me
		errorf(ThreadManForUser,"UNIMPLEMENTED sceKernelTerminateDeleteThread instruction");
		return 0;
	}

	int sceKernelSuspendDispatchThread()
	{
		if (sceKernelIsIntrContext())
		{
			return SCE_KERNEL_ERROR_ILLEGAL_CONTEXT;
		}

		int intr = sceKernelCpuSuspendIntr();

		int result = theKernelScheduler.SuspendDispatchThread(intr);

		sceKernelCpuResumeIntr(intr);

		return result;
	}

	int sceKernelResumeDispatchThread(u32 a0)
	{
		if (sceKernelIsIntrContext())
		{
			return SCE_KERNEL_ERROR_ILLEGAL_CONTEXT;
		}

		int intr = sceKernelCpuSuspendIntr();

		int result = theKernelScheduler.ResumeDispatchThread(int(a0), intr);

		sceKernelCpuResumeIntr(intr);

		return result;
	}

	int sceKernelChangeCurrentThreadAttr()
	{
		//TODO implement me
		errorf(ThreadManForUser,"UNIMPLEMENTED sceKernelChangeCurrentThreadAttr instruction");
		return 0;
	}

	int sceKernelChangeThreadPriority(u32 a0, u32 a1)
	{
		int intr = sceKernelCpuSuspendIntr();

		KernelThread *current_thread;

		if (a0)
		{
			u32 error = theKernelObjects.Get(SceUID(a0), current_thread);
			if (error)
			{
				return SCE_KERNEL_ERROR_UNKNOWN_THID;
			}
		}
		else
		{
			current_thread = theKernelScheduler.m_current_thread;
		}

		int result = current_thread->ChangeThreadPriority(int(a1), intr);

		sceKernelCpuResumeIntr(intr);

		return result;
	}

	int sceKernelRotateThreadReadyQueue()
	{
		//TODO implement me
		errorf(ThreadManForUser,"UNIMPLEMENTED sceKernelRotateThreadReadyQueue instruction");
		return 0;
	}

	int sceKernelReleaseWaitThread()
	{
		//TODO implement me
		errorf(ThreadManForUser,"UNIMPLEMENTED sceKernelReleaseWaitThread instruction");
		return 0;
	}

	int sceKernelGetThreadId()
	{
        if (sceKernelIsIntrContext())
        {
            return SCE_KERNEL_ERROR_ILLEGAL_CONTEXT;
        }

        return theKernelScheduler.m_current_thread->GetUid();
	}

	int sceKernelGetThreadCurrentPriority()
	{
        if (sceKernelIsIntrContext())
        {
            return SCE_KERNEL_ERROR_ILLEGAL_CONTEXT;
        }

        return theKernelScheduler.m_current_thread->m_current_priority;
	}

	int sceKernelGetThreadExitStatus(u32 a0)
	{
        int intr = sceKernelCpuSuspendIntr();

        KernelThread *status_thread;

        u32 error = theKernelObjects.Get(SceUID(a0), status_thread);
        if (error)
        {
            return SCE_KERNEL_ERROR_UNKNOWN_THID;
        }

        int result = status_thread->m_exit_status;

        sceKernelCpuResumeIntr(intr);

        return result;
	}

	int sceKernelReferThreadStatus()
	{
		//TODO implement me
		errorf(ThreadManForUser,"UNIMPLEMENTED sceKernelReferThreadStatus instruction");
		return 0;
	}

	int sceKernelReferThreadRunStatus()
	{
		//TODO implement me
		errorf(ThreadManForUser,"UNIMPLEMENTED sceKernelReferThreadRunStatus instruction");
		return 0;
	}

	int sceKernelCheckThreadStack()
	{
        if (sceKernelIsIntrContext())
        {
            return SCE_KERNEL_ERROR_ILLEGAL_CONTEXT;
        }

		return theKernelScheduler.m_current_thread->CheckStack();
	}

	int sceKernelGetThreadStackFreeSize(u32 a0)
	{
        if (sceKernelIsIntrContext())
        {
            return SCE_KERNEL_ERROR_ILLEGAL_CONTEXT;
        }

        int intr = sceKernelCpuSuspendIntr();

        KernelThread *stack_thread;

        if (a0)
        {
            u32 error = theKernelObjects.Get(SceUID(a0), stack_thread);
            if (error)
            {
                return SCE_KERNEL_ERROR_UNKNOWN_THID;
            }
        }
        else
        {
            stack_thread = theKernelScheduler.m_current_thread;
        }

        int size = stack_thread->m_stack_size;
        SceThreadStack *stack = Memory::addr< SceThreadStack >(stack_thread->m_stack);

        sceKernelCpuResumeIntr(intr);

        for (int i = 0; i < int((size - 16) / sizeof(int)); ++i)
        {
            if (stack->value[i] != -1)
            {
                return i * sizeof(int);
            }
        }

        return size;
	}

    void _sceKernelStartThread()
    {
        int intr = sceKernelCpuSuspendIntr();

        theKernelScheduler.m_current_thread->_Start(intr);

        sceKernelCpuResumeIntr(intr);
    }

    void _sceKernelExitThread()
    {
        sceKernelExitThread(SCE_KERNEL_ERROR_THREAD_TERMINATED);
    }

	/// EVH ///

	int sceKernelRegisterThreadEventHandler()
	{
		//TODO implement me
		errorf(ThreadManForUser,"UNIMPLEMENTED sceKernelRegisterThreadEventHandler instruction");
		return 0;
	}

	int sceKernelReleaseThreadEventHandler()
	{
		//TODO implement me
		errorf(ThreadManForUser,"UNIMPLEMENTED sceKernelReleaseThreadEventHandler instruction");
		return 0;
	}

	int sceKernelReferThreadEventHandlerStatus()
	{
		//TODO implement me
		errorf(ThreadManForUser,"UNIMPLEMENTED sceKernelReferThreadEventHandlerStatus instruction");
		return 0;
	}

    /// SLEEP/SUSPEND/WAITEND ///

	int sceKernelSleepThread()
	{
		//TODO implement me
		errorf(ThreadManForUser,"UNIMPLEMENTED sceKernelSleepThread instruction");
		return 0;
	}

	int sceKernelSleepThreadCB()
	{
		//TODO implement me
		errorf(ThreadManForUser,"UNIMPLEMENTED sceKernelSleepThreadCB instruction");
		return 0;
	}

	int sceKernelWakeupThread()
	{
		//TODO implement me
		errorf(ThreadManForUser,"UNIMPLEMENTED sceKernelWakeupThread instruction");
		return 0;
	}

	int sceKernelCancelWakeupThread()
	{
		//TODO implement me
		errorf(ThreadManForUser,"UNIMPLEMENTED sceKernelCancelWakeupThread instruction");
		return 0;
	}

	int sceKernelSuspendThread()
	{
		//TODO implement me
		errorf(ThreadManForUser,"UNIMPLEMENTED sceKernelSuspendThread instruction");
		return 0;
	}

	int sceKernelResumeThread()
	{
		//TODO implement me
		errorf(ThreadManForUser,"UNIMPLEMENTED sceKernelResumeThread instruction");
		return 0;
	}

	int sceKernelWaitThreadEnd()
	{
		//TODO implement me
		errorf(ThreadManForUser,"UNIMPLEMENTED sceKernelWaitThreadEnd instruction");
		return 0;
	}

	int sceKernelWaitThreadEndCB()
	{
		//TODO implement me
		errorf(ThreadManForUser,"UNIMPLEMENTED sceKernelWaitThreadEndCB instruction");
		return 0;
	}

    /// SEMA ///

	int sceKernelCreateSema()
	{
		//TODO implement me
		errorf(ThreadManForUser,"UNIMPLEMENTED sceKernelCreateSema instruction");
		return 0;
	}

	int sceKernelDeleteSema()
	{
		//TODO implement me
		errorf(ThreadManForUser,"UNIMPLEMENTED sceKernelDeleteSema instruction");
		return 0;
	}

	int sceKernelSignalSema()
	{
		//TODO implement me
		errorf(ThreadManForUser,"UNIMPLEMENTED sceKernelSignalSema instruction");
		return 0;
	}

	int sceKernelWaitSema()
	{
		//TODO implement me
		errorf(ThreadManForUser,"UNIMPLEMENTED sceKernelWaitSema instruction");
		return 0;
	}

	int sceKernelWaitSemaCB()
	{
		//TODO implement me
		errorf(ThreadManForUser,"UNIMPLEMENTED sceKernelWaitSemaCB instruction");
		return 0;
	}

	int sceKernelPollSema()
	{
		//TODO implement me
		errorf(ThreadManForUser,"UNIMPLEMENTED sceKernelPollSema instruction");
		return 0;
	}

	int sceKernelCancelSema()
	{
		//TODO implement me
		errorf(ThreadManForUser,"UNIMPLEMENTED sceKernelCancelSema instruction");
		return 0;
	}

	int sceKernelReferSemaStatus()
	{
		//TODO implement me
		errorf(ThreadManForUser,"UNIMPLEMENTED sceKernelReferSemaStatus instruction");
		return 0;
	}

	/// EVENTFLAG ///

	int sceKernelCreateEventFlag()
	{
		//TODO implement me
		errorf(ThreadManForUser,"UNIMPLEMENTED sceKernelCreateEventFlag instruction");
		return 0;
	}

	int sceKernelDeleteEventFlag()
	{
		//TODO implement me
		errorf(ThreadManForUser,"UNIMPLEMENTED sceKernelDeleteEventFlag instruction");
		return 0;
	}

	int sceKernelSetEventFlag()
	{
		//TODO implement me
		errorf(ThreadManForUser,"UNIMPLEMENTED sceKernelSetEventFlag instruction");
		return 0;
	}

	int sceKernelClearEventFlag()
	{
		//TODO implement me
		errorf(ThreadManForUser,"UNIMPLEMENTED sceKernelClearEventFlag instruction");
		return 0;
	}

	int sceKernelWaitEventFlag()
	{
		//TODO implement me
		errorf(ThreadManForUser,"UNIMPLEMENTED sceKernelWaitEventFlag instruction");
		return 0;
	}

	int sceKernelWaitEventFlagCB()
	{
		//TODO implement me
		errorf(ThreadManForUser,"UNIMPLEMENTED sceKernelWaitEventFlagCB instruction");
		return 0;
	}

	int sceKernelPollEventFlag()
	{
		//TODO implement me
		errorf(ThreadManForUser,"UNIMPLEMENTED sceKernelPollEventFlag instruction");
		return 0;
	}

	int sceKernelCancelEventFlag()
	{
		//TODO implement me
		errorf(ThreadManForUser,"UNIMPLEMENTED sceKernelCancelEventFlag instruction");
		return 0;
	}

	int sceKernelReferEventFlagStatus()
	{
		//TODO implement me
		errorf(ThreadManForUser,"UNIMPLEMENTED sceKernelReferEventFlagStatus instruction");
		return 0;
	}

	/// MBX ///

	int sceKernelCreateMbx()
	{
		//TODO implement me
		errorf(ThreadManForUser,"UNIMPLEMENTED sceKernelCreateMbx instruction");
		return 0;
	}

	int sceKernelDeleteMbx()
	{
		//TODO implement me
		errorf(ThreadManForUser,"UNIMPLEMENTED sceKernelDeleteMbx instruction");
		return 0;
	}

	int sceKernelSendMbx()
	{
		//TODO implement me
		errorf(ThreadManForUser,"UNIMPLEMENTED sceKernelSendMbx instruction");
		return 0;
	}

	int sceKernelReceiveMbx()
	{
		//TODO implement me
		errorf(ThreadManForUser,"UNIMPLEMENTED sceKernelReceiveMbx instruction");
		return 0;
	}

	int sceKernelReceiveMbxCB()
	{
		//TODO implement me
		errorf(ThreadManForUser,"UNIMPLEMENTED sceKernelReceiveMbxCB instruction");
		return 0;
	}

	int sceKernelPollMbx()
	{
		//TODO implement me
		errorf(ThreadManForUser,"UNIMPLEMENTED sceKernelPollMbx instruction");
		return 0;
	}

	int sceKernelCancelReceiveMbx()
	{
		//TODO implement me
		errorf(ThreadManForUser,"UNIMPLEMENTED sceKernelCancelReceiveMbx instruction");
		return 0;
	}

	int sceKernelReferMbxStatus()
	{
		//TODO implement me
		errorf(ThreadManForUser,"UNIMPLEMENTED sceKernelReferMbxStatus instruction");
		return 0;
	}

	/// MPP ///

	int sceKernelCreateMsgPipe()
	{
		//TODO implement me
		errorf(ThreadManForUser,"UNIMPLEMENTED sceKernelCreateMsgPipe instruction");
		return 0;
	}

	int sceKernelDeleteMsgPipe()
	{
		//TODO implement me
		errorf(ThreadManForUser,"UNIMPLEMENTED sceKernelDeleteMsgPipe instruction");
		return 0;
	}

	int sceKernelSendMsgPipe()
	{
		//TODO implement me
		errorf(ThreadManForUser,"UNIMPLEMENTED sceKernelSendMsgPipe instruction");
		return 0;
	}

	int sceKernelSendMsgPipeCB()
	{
		//TODO implement me
		errorf(ThreadManForUser,"UNIMPLEMENTED sceKernelSendMsgPipeCB instruction");
		return 0;
	}

	int sceKernelTrySendMsgPipe()
	{
		//TODO implement me
		errorf(ThreadManForUser,"UNIMPLEMENTED sceKernelTrySendMsgPipe instruction");
		return 0;
	}

	int sceKernelReceiveMsgPipe()
	{
		//TODO implement me
		errorf(ThreadManForUser,"UNIMPLEMENTED sceKernelReceiveMsgPipe instruction");
		return 0;
	}

	int sceKernelReceiveMsgPipeCB()
	{
		//TODO implement me
		errorf(ThreadManForUser,"UNIMPLEMENTED sceKernelReceiveMsgPipeCB instruction");
		return 0;
	}

	int sceKernelTryReceiveMsgPipe()
	{
		//TODO implement me
		errorf(ThreadManForUser,"UNIMPLEMENTED sceKernelTryReceiveMsgPipe instruction");
		return 0;
	}

	int sceKernelCancelMsgPipe()
	{
		//TODO implement me
		errorf(ThreadManForUser,"UNIMPLEMENTED sceKernelCancelMsgPipe instruction");
		return 0;
	}

	int sceKernelReferMsgPipeStatus()
	{
		//TODO implement me
		errorf(ThreadManForUser,"UNIMPLEMENTED sceKernelReferMsgPipeStatus instruction");
		return 0;
	}

	/// VPL ///
	int sceKernelCreateVpl(u32 a0, u32 a1, u32 a2, u32 a3, u32 t0)  { return threadman::hleKernelCreateVpl(Memory::addr< char const >(a0), (SceUID)a1, (SceUInt)a2, (SceSize)a3, t0?Memory::addr< SceKernelVplOptParam >(t0):0); }  
	int sceKernelDeleteVpl(u32 a0)                                  { return threadman::hleKernelDeleteVpl((SceUID)a0); }
	int sceKernelAllocateVpl(u32 a0, u32 a1, u32 a2, u32 a3)        { return threadman::hleKernelAllocateVpl((SceUID)a0, (SceSize)a1, a2?Memory::addr< u32 >(a2):0, a3?Memory::addr< SceUInt >(a3):0); }
	int sceKernelAllocateVplCB(u32 a0, u32 a1, u32 a2, u32 a3)      { return threadman::hleKernelAllocateVplCB((SceUID)a0, (SceSize)a1, a2?Memory::addr< u32 >(a2):0, a3?Memory::addr< SceUInt >(a3):0); }
	int sceKernelTryAllocateVpl(u32 a0, u32 a1, u32 a2)             { return threadman::hleKernelTryAllocateVpl((SceUID)a0, (SceSize)a1, a2?Memory::addr< u32 >(a2):0); }
	int sceKernelFreeVpl(u32 a0, u32 a1)                            { return threadman::hleKernelFreeVpl((SceUID)a0, a1); }
	int sceKernelCancelVpl(u32 a0, u32 a1)                          { return threadman::hleKernelCancelVpl((SceUID)a0, Memory::addr< int >(a1)); }
	int sceKernelReferVplStatus(u32 a0, u32 a1)                     { return threadman::hleKernelReferVplStatus((SceUID)a0, Memory::addr< SceKernelVplInfo >(a1)); }

	/// FPL ///
	int sceKernelCreateFpl(u32 a0, u32 a1, u32 a2, u32 a3, u32 t0, u32 t1)  { return threadman::hleKernelCreateFpl(Memory::addr< char const >(a0), (SceUID)a1, (SceUInt)a2, (SceSize)a3, (int)t0, t1?Memory::addr< SceKernelFplOptParam >(t1):0); }  
	int sceKernelDeleteFpl(u32 a0)                                          { return threadman::hleKernelDeleteFpl((SceUID)a0); }
	int sceKernelAllocateFpl(u32 a0, u32 a1, u32 a2)                        { return threadman::hleKernelAllocateFpl((SceUID)a0, a1?Memory::addr< u32 >(a1):0, a2?Memory::addr< SceUInt >(a2):0); }
	int sceKernelAllocateFplCB(u32 a0, u32 a1, u32 a2)                      { return threadman::hleKernelAllocateFplCB((SceUID)a0, a1?Memory::addr< u32 >(a1):0, a2?Memory::addr< SceUInt >(a2):0); }
	int sceKernelTryAllocateFpl(u32 a0, u32 a1)                             { return threadman::hleKernelTryAllocateFpl((SceUID)a0, a1?Memory::addr< u32 >(a1):0); }
	int sceKernelFreeFpl(u32 a0, u32 a1)                                    { return threadman::hleKernelFreeFpl((SceUID)a0, a1); }
	int sceKernelCancelFpl(u32 a0, u32 a1)                                  { return threadman::hleKernelCancelFpl((SceUID)a0, Memory::addr< int >(a1)); }
	int sceKernelReferFplStatus(u32 a0, u32 a1)                             { return threadman::hleKernelReferFplStatus((SceUID)a0, Memory::addr< SceKernelFplInfo >(a1)); }

	/// TIME/SOFT TIME MANAGEMENT /// right now, we're using QTime::currentTime(), but we'll need to change it a true µs timer (as VTime needs so)
	int sceKernelGetSystemTime(u32 a0)                          { return threadman::hleKernelGetSystemTime(Memory::addr< SceKernelSysClock >(a0)); }
	int sceKernelGetSystemTimeLow()                             { return threadman::hleKernelGetSystemTimeLow(); }
	u64 sceKernelGetSystemTimeWide()                            { return threadman::hleKernelGetSystemTimeWide(); }
	int sceKernelSysClock2USec(u32 a0, u32 a1, u32 a2)          { return threadman::hleKernelSysClock2USec(Memory::addr< SceKernelSysClock >(a0), Memory::addr< u32 >(a1), Memory::addr< u32 >(a2)); }
	int sceKernelSysClock2USecWide(u64 a1a0, u32 a2, u32 a3)    { return threadman::hleKernelSysClock2USecWide(a1a0, Memory::addr< u32 >(a2), Memory::addr< u32 >(a3)); }
	int sceKernelUSec2SysClock(u32 a0, u32 a1)                  { return threadman::hleKernelUSec2SysClock(a0, Memory::addr< SceKernelSysClock >(a1)); }
	u64 sceKernelUSec2SysClockWide(u32 a0)                      { return threadman::hleKernelUSec2SysClockWide(a0); }

    ////// DELAY ///

	int sceKernelDelayThread()
	{
		//TODO implement me
		errorf(ThreadManForUser,"UNIMPLEMENTED sceKernelDelayThread instruction");
		return 0;
	}

	int sceKernelDelayThreadCB()
	{
		//TODO implement me
		errorf(ThreadManForUser,"UNIMPLEMENTED sceKernelDelayThreadCB instruction");
		return 0;
	}

	int sceKernelDelaySysClockThread()
	{
		//TODO implement me
		errorf(ThreadManForUser,"UNIMPLEMENTED sceKernelDelaySysClockThread instruction");
		return 0;
	}

	int sceKernelDelaySysClockThreadCB()
	{
		//TODO implement me
		errorf(ThreadManForUser,"UNIMPLEMENTED sceKernelDelaySysClockThreadCB instruction");
		return 0;
	}

    ////// ALARM ///

	int sceKernelSetAlarm()
	{
		//TODO implement me
		errorf(ThreadManForUser,"UNIMPLEMENTED sceKernelSetAlarm instruction");
		return 0;
	}

	int sceKernelSetSysClockAlarm()
	{
		//TODO implement me
		errorf(ThreadManForUser,"UNIMPLEMENTED sceKernelSetSysClockAlarm instruction");
		return 0;
	}

	int sceKernelCancelAlarm()
	{
		//TODO implement me
		errorf(ThreadManForUser,"UNIMPLEMENTED sceKernelCancelAlarm instruction");
		return 0;
	}

	int sceKernelReferAlarmStatus()
	{
		//TODO implement me
		errorf(ThreadManForUser,"UNIMPLEMENTED sceKernelReferAlarmStatus instruction");
		return 0;
	}

	////// VTIMER ///
	int sceKernelCreateVTimer()
	{
		//TODO implement me
		errorf(ThreadManForUser,"UNIMPLEMENTED sceKernelCreateVTimer instruction");
		return 0;
	}

	int sceKernelDeleteVTimer()
	{
		//TODO implement me
		errorf(ThreadManForUser,"UNIMPLEMENTED sceKernelDeleteVTimer instruction");
		return 0;
	}

	int sceKernelGetVTimerBase()
	{
		//TODO implement me
		errorf(ThreadManForUser,"UNIMPLEMENTED sceKernelGetVTimerBase instruction");
		return 0;
	}

	int sceKernelGetVTimerTime()
	{
		//TODO implement me
		errorf(ThreadManForUser,"UNIMPLEMENTED sceKernelGetVTimerTime instruction");
		return 0;
	}

	int sceKernelSetVTimerTime()
	{
		//TODO implement me
		errorf(ThreadManForUser,"UNIMPLEMENTED sceKernelSetVTimerTime instruction");
		return 0;
	}

	int sceKernelStartVTimer()
	{
		//TODO implement me
		errorf(ThreadManForUser,"UNIMPLEMENTED sceKernelStartVTimer instruction");
		return 0;
	}

	int sceKernelStopVTimer()
	{
		//TODO implement me
		errorf(ThreadManForUser,"UNIMPLEMENTED sceKernelStopVTimer instruction");
		return 0;
	}

	int sceKernelSetVTimerHandler()
	{
		//TODO implement me
		errorf(ThreadManForUser,"UNIMPLEMENTED sceKernelSetVTimerHandler instruction");
		return 0;
	}

	int sceKernelCancelVTimerHandler()
	{
		//TODO implement me
		errorf(ThreadManForUser,"UNIMPLEMENTED sceKernelCancelVTimerHandler instruction");
		return 0;
	}

	int sceKernelGetVTimerBaseWide()
	{
		//TODO implement me
		errorf(ThreadManForUser,"UNIMPLEMENTED sceKernelGetVTimerBaseWide instruction");
		return 0;
	}

	int sceKernelGetVTimerTimeWide()
	{
		//TODO implement me
		errorf(ThreadManForUser,"UNIMPLEMENTED sceKernelGetVTimerTimeWide instruction");
		return 0;
	}

	int sceKernelSetVTimerTimeWide()
	{
		//TODO implement me
		errorf(ThreadManForUser,"UNIMPLEMENTED sceKernelSetVTimerTimeWide instruction");
		return 0;
	}

	int sceKernelSetVTimerHandlerWide()
	{
		//TODO implement me
		errorf(ThreadManForUser,"UNIMPLEMENTED sceKernelSetVTimerHandlerWide instruction");
		return 0;
	}

	int sceKernelReferVTimerStatus()
	{
		//TODO implement me
		errorf(ThreadManForUser,"UNIMPLEMENTED sceKernelReferVTimerStatus instruction");
		return 0;
	}

	int _sceKernelReturnFromTimerHandler()
	{
		//TODO implement me
		errorf(ThreadManForUser,"UNIMPLEMENTED _sceKernelReturnFromTimerHandler instruction");
		return 0;
	}

    /// CALLBACK ///

    int sceKernelCreateCallback(u32 a0, u32 a1, u32 a2)
    {
        int intr = sceKernelCpuSuspendIntr();

        int result = KernelCallback::Create(Memory::addr< char const >(a0), a1, a2, intr);

        sceKernelCpuResumeIntr(intr);

        return result;
    }

    int sceKernelDeleteCallback(u32 a0)
    {
        if (sceKernelIsIntrContext() || theKernelScheduler.m_current_thread->m_callback)
        {
            return SCE_KERNEL_ERROR_ILLEGAL_CONTEXT;
        }

        int intr = sceKernelCpuSuspendIntr();

        KernelCallback *callback;

        u32 error = theKernelObjects.Get(SceUID(a0), callback);
        if (error)
        {
            return SCE_KERNEL_ERROR_UNKNOWN_CBID;
        }

        int result = callback->Delete(intr);

        sceKernelCpuResumeIntr(intr);

        return result;
    }

    int sceKernelNotifyCallback(u32 a0, u32 a1)
    {
        int intr = sceKernelCpuSuspendIntr();

        KernelCallback *callback;

        u32 error = theKernelObjects.Get(SceUID(a0), callback);
        if (error)
        {
            return SCE_KERNEL_ERROR_UNKNOWN_CBID;
        }

        int result = callback->Notify(int(a1), intr);

        sceKernelCpuResumeIntr(intr);

        return result;
    }

    int sceKernelCancelCallback(u32 a0)
    {
        int intr = sceKernelCpuSuspendIntr();

        KernelCallback *callback;

        u32 error = theKernelObjects.Get(SceUID(a0), callback);
        if (error)
        {
            return SCE_KERNEL_ERROR_UNKNOWN_CBID;
        }

        int result = callback->Cancel(intr);

        sceKernelCpuResumeIntr(intr);

        return result;
    }

    int sceKernelGetCallbackCount(u32 a0)
    {
        int intr = sceKernelCpuSuspendIntr();

        KernelCallback *callback;

        u32 error = theKernelObjects.Get(SceUID(a0), callback);
        if (error)
        {
            return SCE_KERNEL_ERROR_UNKNOWN_CBID;
        }

        int result = callback->GetCount(intr);

        sceKernelCpuResumeIntr(intr);

        return result;
    }

    int sceKernelCheckCallback()
    {
        if (sceKernelIsIntrContext() || theKernelScheduler.m_current_thread->m_callback)
        {
            return SCE_KERNEL_ERROR_ILLEGAL_CONTEXT;
        }

        int intr = sceKernelCpuSuspendIntr();

        KernelCallback *callback;

        theKernelObjects.Get(theKernelScheduler.m_current_thread->GetUid(), callback);

        int result = callback->Check(intr);

        sceKernelCpuResumeIntr(intr);

        return result;
    }

    int sceKernelReferCallbackStatus(u32 a0, u32 a1)
    {
        int intr = sceKernelCpuSuspendIntr();

        KernelCallback *callback;

        u32 error = theKernelObjects.Get(SceUID(a0), callback);
        if (error)
        {
            return SCE_KERNEL_ERROR_UNKNOWN_CBID;
        }

        int result = callback->ReferStatus(Memory::addr< SceKernelCallbackInfo >(a1), intr);

        sceKernelCpuResumeIntr(intr);

        return result;
    }

    int _sceKernelReturnFromCallback()
    {
        //TODO implement me
        errorf(ThreadManForUser,"UNIMPLEMENTED _sceKernelReturnFromCallback function");
        return 0;
    }

    /// SYSTEM STATUS ///

	int sceKernelReferSystemStatus()
	{
		//TODO implement me
		errorf(ThreadManForUser,"UNIMPLEMENTED sceKernelReferSystemStatus instruction");
		return 0;
	}

	int sceKernelGetThreadmanIdList()
	{
		//TODO implement me
		errorf(ThreadManForUser,"UNIMPLEMENTED sceKernelGetThreadmanIdList instruction");
		return 0;
	}

	int sceKernelGetThreadmanIdType()
	{
		//TODO implement me
		errorf(ThreadManForUser,"UNIMPLEMENTED sceKernelGetThreadmanIdType instruction");
		return 0;
	}

    /// MUTEX ///

	int sceKernelCreateMutex()
	{
		//TODO implement me
		errorf(ThreadManForUser,"UNIMPLEMENTED sceKernelCreateMutex instruction");
		return 0;
	}

	int sceKernelDeleteMutex()
	{
		//TODO implement me
		errorf(ThreadManForUser,"UNIMPLEMENTED sceKernelDeleteMutex instruction");
		return 0;
	}

	int sceKernelTryLockMutex()
	{
		//TODO implement me
		errorf(ThreadManForUser,"UNIMPLEMENTED sceKernelTryLockMutex instruction");
		return 0;
	}

	int sceKernelLockMutex()
	{
		//TODO implement me
		errorf(ThreadManForUser,"UNIMPLEMENTED sceKernelLockMutex instruction");
		return 0;
	}

	int sceKernelLockMutexCB()
	{
		//TODO implement me
		errorf(ThreadManForUser,"UNIMPLEMENTED sceKernelLockMutexCB instruction");
		return 0;
	}

	int sceKernelUnlockMutex()
	{
		//TODO implement me
		errorf(ThreadManForUser,"UNIMPLEMENTED sceKernelUnlockMutex instruction");
		return 0;
	}

	int sceKernelCancelMutex()
	{
		//TODO implement me
		errorf(ThreadManForUser,"UNIMPLEMENTED sceKernelCancelMutex instruction");
		return 0;
	}

	int sceKernelReferMutexStatus()
	{
		//TODO implement me
		errorf(ThreadManForUser,"UNIMPLEMENTED sceKernelReferMutexStatus instruction");
		return 0;
	}

	/// LWMUTEX ///

	int sceKernelCreateLwMutex()
	{
		//TODO implement me
		errorf(ThreadManForUser,"UNIMPLEMENTED sceKernelCreateLwMutex instruction");
		return 0;
	}

	int sceKernelDeleteLwMutex()
	{
		//TODO implement me
		errorf(ThreadManForUser,"UNIMPLEMENTED sceKernelDeleteLwMutex instruction");
		return 0;
	}

	int sceKernelReferLwMutexStatusByID()
	{
		//TODO implement me
		errorf(ThreadManForUser,"UNIMPLEMENTED sceKernelReferLwMutexStatusByID instruction");
		return 0;
	}

	/// MISC. ///

	int sceKernelReferGlobalProfiler()
	{
		//TODO implement me
		errorf(ThreadManForUser,"UNIMPLEMENTED sceKernelReferGlobalProfiler instruction");
		return 0;
	}

	int sceKernelReferThreadProfiler()
	{
		//TODO implement me
		errorf(ThreadManForUser,"UNIMPLEMENTED sceKernelReferThreadProfiler instruction");
		return 0;
	}

	int sceKernelDonateWakeupThread()
	{
		//TODO implement me
		errorf(ThreadManForUser,"UNIMPLEMENTED sceKernelDonateWakeupThread instruction");
		return 0;
	}

    /// UNKNOWN ///
	int ThreadManForUser_BEED3A47()
	{
		//TODO implement me
		errorf(ThreadManForUser,"UNIMPLEMENTED ThreadManForUser_BEED3A47 instruction");
		return 0;
	}

	int ThreadManForUser_8672E3D0()
	{
		//TODO implement me
		errorf(ThreadManForUser,"UNIMPLEMENTED ThreadManForUser_8672E3D0 instruction");
		return 0;
	}

	int ThreadManForUser_7CFF8CF3()
	{
		//TODO implement me
		errorf(ThreadManForUser,"UNIMPLEMENTED ThreadManForUser_7CFF8CF3 instruction");
		return 0;
	}

	int ThreadManForUser_31327F19()
	{
		//TODO implement me
		errorf(ThreadManForUser,"UNIMPLEMENTED ThreadManForUser_31327F19 instruction");
		return 0;
	}

	int ThreadManForUser_71040D5C()
	{
		//TODO implement me
		errorf(ThreadManForUser,"UNIMPLEMENTED ThreadManForUser_71040D5C instruction");
		return 0;
	}
}

namespace syscalls
{
    void sceKernelCreateThread(AlContext &context)             { V0 = ThreadManForUser::sceKernelCreateThread(A0, A1, A2, A3, T0, T1);   }
    void sceKernelDeleteThread(AlContext &context)             { V0 = ThreadManForUser::sceKernelDeleteThread(A0);                       }
    void sceKernelStartThread(AlContext &context)              { V0 = ThreadManForUser::sceKernelStartThread(A0, A1, A2);                }
    void sceKernelExitThread(AlContext &context)               { V0 = ThreadManForUser::sceKernelExitThread(A0);                         }
    void sceKernelExitDeleteThread(AlContext &context)         { V0 = ThreadManForUser::sceKernelExitDeleteThread(A0);                   }
    void sceKernelTerminateThread(AlContext &context)          { V0 = ThreadManForUser::sceKernelTerminateThread();                      }
    void sceKernelTerminateDeleteThread(AlContext &context)    { V0 = ThreadManForUser::sceKernelTerminateDeleteThread();                }
    void sceKernelSuspendDispatchThread(AlContext &context)    { V0 = ThreadManForUser::sceKernelSuspendDispatchThread();                }
    void sceKernelResumeDispatchThread(AlContext &context)     { V0 = ThreadManForUser::sceKernelResumeDispatchThread(A0);               }
    void sceKernelChangeCurrentThreadAttr(AlContext &context)  { V0 = ThreadManForUser::sceKernelChangeCurrentThreadAttr();              }
    void sceKernelChangeThreadPriority(AlContext &context)     { V0 = ThreadManForUser::sceKernelChangeThreadPriority(A0, A1);           }
    void sceKernelRotateThreadReadyQueue(AlContext &context)   { V0 = ThreadManForUser::sceKernelRotateThreadReadyQueue();               }
    void sceKernelReleaseWaitThread(AlContext &context)        { V0 = ThreadManForUser::sceKernelReleaseWaitThread();                    }	
    void sceKernelGetThreadId(AlContext &context)              { V0 = ThreadManForUser::sceKernelGetThreadId();                          }
    void sceKernelGetThreadCurrentPriority(AlContext &context) { V0 = ThreadManForUser::sceKernelGetThreadCurrentPriority();             }
    void sceKernelGetThreadExitStatus(AlContext &context)      { V0 = ThreadManForUser::sceKernelGetThreadExitStatus(A0);                }
    void sceKernelReferThreadStatus(AlContext &context)        { V0 = ThreadManForUser::sceKernelReferThreadStatus();                    }
    void sceKernelReferThreadRunStatus(AlContext &context)     { V0 = ThreadManForUser::sceKernelReferThreadRunStatus();                 }
    void sceKernelCheckThreadStack(AlContext &context)         { V0 = ThreadManForUser::sceKernelCheckThreadStack();                     }
    void sceKernelGetThreadStackFreeSize(AlContext &context)   { V0 = ThreadManForUser::sceKernelGetThreadStackFreeSize(A0);             }

    void _sceKernelStartThread(AlContext &context)             { ThreadManForUser::_sceKernelStartThread(); }
    void _sceKernelExitThread(AlContext &context)              { ThreadManForUser::_sceKernelExitThread();  }

    /// EVH ///
    void sceKernelRegisterThreadEventHandler(AlContext &context)    { V0 = ThreadManForUser::sceKernelRegisterThreadEventHandler();    }
    void sceKernelReleaseThreadEventHandler(AlContext &context)     { V0 = ThreadManForUser::sceKernelReleaseThreadEventHandler();     }
    void sceKernelReferThreadEventHandlerStatus(AlContext &context) { V0 = ThreadManForUser::sceKernelReferThreadEventHandlerStatus(); }		

    /// SLEEP/SUSPEND/WAITEND ///
    void sceKernelSleepThread(AlContext &context)        { V0 = ThreadManForUser::sceKernelSleepThread();        }
    void sceKernelSleepThreadCB(AlContext &context)      { V0 = ThreadManForUser::sceKernelSleepThreadCB();      }
    void sceKernelWakeupThread(AlContext &context)       { V0 = ThreadManForUser::sceKernelWakeupThread();       }
    void sceKernelCancelWakeupThread(AlContext &context) { V0 = ThreadManForUser::sceKernelCancelWakeupThread(); }
    void sceKernelSuspendThread(AlContext &context)      { V0 = ThreadManForUser::sceKernelSuspendThread();      }
    void sceKernelResumeThread(AlContext &context)       { V0 = ThreadManForUser::sceKernelResumeThread();       }
    void sceKernelWaitThreadEnd(AlContext &context)      { V0 = ThreadManForUser::sceKernelWaitThreadEnd();      }
    void sceKernelWaitThreadEndCB(AlContext &context)    { V0 = ThreadManForUser::sceKernelWaitThreadEndCB();    }

    /// SEMA ///
    void sceKernelCreateSema(AlContext &context)      { V0 = ThreadManForUser::sceKernelCreateSema();      }
    void sceKernelDeleteSema(AlContext &context)      { V0 = ThreadManForUser::sceKernelDeleteSema();      }
    void sceKernelSignalSema(AlContext &context)      { V0 = ThreadManForUser::sceKernelSignalSema();      }
    void sceKernelWaitSema(AlContext &context)        { V0 = ThreadManForUser::sceKernelWaitSema();        }
    void sceKernelWaitSemaCB(AlContext &context)      { V0 = ThreadManForUser::sceKernelWaitSemaCB();      }
    void sceKernelPollSema(AlContext &context)        { V0 = ThreadManForUser::sceKernelPollSema();        }
    void sceKernelCancelSema(AlContext &context)      { V0 = ThreadManForUser::sceKernelCancelSema();      }
    void sceKernelReferSemaStatus(AlContext &context) { V0 = ThreadManForUser::sceKernelReferSemaStatus(); }

    /// EVENTFLAG ///
    void sceKernelCreateEventFlag(AlContext &context)      { V0 = ThreadManForUser::sceKernelCreateEventFlag();      }
    void sceKernelDeleteEventFlag(AlContext &context)      { V0 = ThreadManForUser::sceKernelDeleteEventFlag();      }
    void sceKernelSetEventFlag(AlContext &context)         { V0 = ThreadManForUser::sceKernelSetEventFlag();         }
    void sceKernelClearEventFlag(AlContext &context)       { V0 = ThreadManForUser::sceKernelClearEventFlag();       }
    void sceKernelWaitEventFlag(AlContext &context)        { V0 = ThreadManForUser::sceKernelWaitEventFlag();        }
    void sceKernelWaitEventFlagCB(AlContext &context)      { V0 = ThreadManForUser::sceKernelWaitEventFlagCB();      }
    void sceKernelPollEventFlag(AlContext &context)        { V0 = ThreadManForUser::sceKernelPollEventFlag();        }
    void sceKernelCancelEventFlag(AlContext &context)      { V0 = ThreadManForUser::sceKernelCancelEventFlag();      }
    void sceKernelReferEventFlagStatus(AlContext &context) { V0 = ThreadManForUser::sceKernelReferEventFlagStatus(); }

    /// MBX ///
    void sceKernelCreateMbx(AlContext &context)        { V0 = ThreadManForUser::sceKernelCreateMbx();        }
    void sceKernelDeleteMbx(AlContext &context)        { V0 = ThreadManForUser::sceKernelDeleteMbx();        }
    void sceKernelSendMbx(AlContext &context)          { V0 = ThreadManForUser::sceKernelSendMbx();          }	
    void sceKernelReceiveMbx(AlContext &context)       { V0 = ThreadManForUser::sceKernelReceiveMbx();       }
    void sceKernelReceiveMbxCB(AlContext &context)     { V0 = ThreadManForUser::sceKernelReceiveMbxCB();     }
    void sceKernelPollMbx(AlContext &context)          { V0 = ThreadManForUser::sceKernelPollMbx();          }
    void sceKernelCancelReceiveMbx(AlContext &context) { V0 = ThreadManForUser::sceKernelCancelReceiveMbx(); }
    void sceKernelReferMbxStatus(AlContext &context)   { V0 = ThreadManForUser::sceKernelReferMbxStatus();   }

    /// MPP ///
    void sceKernelCreateMsgPipe(AlContext &context)      { V0 = ThreadManForUser::sceKernelCreateMsgPipe();      }
    void sceKernelDeleteMsgPipe(AlContext &context)      { V0 = ThreadManForUser::sceKernelDeleteMsgPipe();      }
    void sceKernelSendMsgPipe(AlContext &context)        { V0 = ThreadManForUser::sceKernelSendMsgPipe();        }
    void sceKernelSendMsgPipeCB(AlContext &context)      { V0 = ThreadManForUser::sceKernelSendMsgPipeCB();      }
    void sceKernelTrySendMsgPipe(AlContext &context)     { V0 = ThreadManForUser::sceKernelTrySendMsgPipe();     }
    void sceKernelReceiveMsgPipe(AlContext &context)     { V0 = ThreadManForUser::sceKernelReceiveMsgPipe();     }	
    void sceKernelReceiveMsgPipeCB(AlContext &context)   { V0 = ThreadManForUser::sceKernelReceiveMsgPipeCB();   }
    void sceKernelTryReceiveMsgPipe(AlContext &context)  { V0 = ThreadManForUser::sceKernelTryReceiveMsgPipe();  }
    void sceKernelCancelMsgPipe(AlContext &context)      { V0 = ThreadManForUser::sceKernelCancelMsgPipe();      }
    void sceKernelReferMsgPipeStatus(AlContext &context) { V0 = ThreadManForUser::sceKernelReferMsgPipeStatus(); }

    /// VPL ///
    void sceKernelCreateVpl(AlContext &context)      { V0 = ThreadManForUser::sceKernelCreateVpl(A0, A1, A2, A3, T0); }
    void sceKernelDeleteVpl(AlContext &context)      { V0 = ThreadManForUser::sceKernelDeleteVpl(A0);                 }
    void sceKernelAllocateVpl(AlContext &context)    { V0 = ThreadManForUser::sceKernelAllocateVpl(A0, A1, A2, A3);   }
    void sceKernelAllocateVplCB(AlContext &context)  { V0 = ThreadManForUser::sceKernelAllocateVplCB(A0, A1, A2, A3); }
    void sceKernelTryAllocateVpl(AlContext &context) { V0 = ThreadManForUser::sceKernelTryAllocateVpl(A0, A1, A2);    }
    void sceKernelFreeVpl(AlContext &context)        { V0 = ThreadManForUser::sceKernelFreeVpl(A0, A1);               }
    void sceKernelCancelVpl(AlContext &context)      { V0 = ThreadManForUser::sceKernelCancelVpl(A0, A1);             }
    void sceKernelReferVplStatus(AlContext &context) { V0 = ThreadManForUser::sceKernelReferVplStatus(A0, A1);        }

    /// FPL ///
    void sceKernelCreateFpl(AlContext &context)      { V0 = ThreadManForUser::sceKernelCreateFpl(A0, A1, A2, A3, T0, T1); }
    void sceKernelDeleteFpl(AlContext &context)      { V0 = ThreadManForUser::sceKernelDeleteFpl(A0);                     }
    void sceKernelAllocateFpl(AlContext &context)    { V0 = ThreadManForUser::sceKernelAllocateFpl(A0, A1, A2);           }
    void sceKernelAllocateFplCB(AlContext &context)  { V0 = ThreadManForUser::sceKernelAllocateFplCB(A0, A1, A2);         }
    void sceKernelTryAllocateFpl(AlContext &context) { V0 = ThreadManForUser::sceKernelTryAllocateFpl(A0, A1);            }
    void sceKernelFreeFpl(AlContext &context)        { V0 = ThreadManForUser::sceKernelFreeFpl(A0, A1);                   }
    void sceKernelCancelFpl(AlContext &context)      { V0 = ThreadManForUser::sceKernelCancelFpl(A0, A1);                 }
    void sceKernelReferFplStatus(AlContext &context) { V0 = ThreadManForUser::sceKernelReferFplStatus(A0, A1);            }

    /// TIME/SOFT TIME MANAGEMENT FUNCTIONS ///
    void sceKernelGetSystemTime(AlContext &context)     { V0   = ThreadManForUser::sceKernelGetSystemTime(A0);   }
    void sceKernelGetSystemTimeWide(AlContext &context) { V1V0 = ThreadManForUser::sceKernelGetSystemTimeWide(); }
    void sceKernelGetSystemTimeLow(AlContext &context)  { V0   = ThreadManForUser::sceKernelGetSystemTimeLow();  }
    void sceKernelUSec2SysClock(AlContext &context)     { V0   = ThreadManForUser::sceKernelUSec2SysClock(A0, A1);           }
    void sceKernelSysClock2USec(AlContext &context)     { V0   = ThreadManForUser::sceKernelSysClock2USec(A0, A1, A2);       }
    void sceKernelUSec2SysClockWide(AlContext &context) { V1V0 = ThreadManForUser::sceKernelUSec2SysClockWide(A0);           }
    void sceKernelSysClock2USecWide(AlContext &context) { V0   = ThreadManForUser::sceKernelSysClock2USecWide(A1A0, A2, A3); }
    
    ////// DELAY ///
    void sceKernelDelayThread(AlContext &context)           { V0   = ThreadManForUser::sceKernelDelayThread();           }
    void sceKernelDelayThreadCB(AlContext &context)         { V0   = ThreadManForUser::sceKernelDelayThreadCB();         }
    void sceKernelDelaySysClockThread(AlContext &context)   { V0   = ThreadManForUser::sceKernelDelaySysClockThread();   }
    void sceKernelDelaySysClockThreadCB(AlContext &context) { V0   = ThreadManForUser::sceKernelDelaySysClockThreadCB(); }
    
    ////// ALARM ///
    void sceKernelSetAlarm(AlContext &context)         { V0 = ThreadManForUser::sceKernelSetAlarm();         }
    void sceKernelSetSysClockAlarm(AlContext &context) { V0 = ThreadManForUser::sceKernelSetSysClockAlarm(); }
    void sceKernelCancelAlarm(AlContext &context)      { V0 = ThreadManForUser::sceKernelCancelAlarm();      }
    void sceKernelReferAlarmStatus(AlContext &context) { V0 = ThreadManForUser::sceKernelReferAlarmStatus(); }
    
    ////// VTIMER ///
    void sceKernelCreateVTimer(AlContext &context)         { V0 = ThreadManForUser::sceKernelCreateVTimer();         }
    void sceKernelDeleteVTimer(AlContext &context)         { V0 = ThreadManForUser::sceKernelDeleteVTimer();         }
    void sceKernelGetVTimerBase(AlContext &context)        { V0 = ThreadManForUser::sceKernelGetVTimerBase();        }
    void sceKernelGetVTimerTime(AlContext &context)        { V0 = ThreadManForUser::sceKernelGetVTimerTime();        }
    void sceKernelSetVTimerTime(AlContext &context)        { V0 = ThreadManForUser::sceKernelSetVTimerTime();        }
    void sceKernelStartVTimer(AlContext &context)          { V0 = ThreadManForUser::sceKernelStartVTimer();          }
    void sceKernelStopVTimer(AlContext &context)           { V0 = ThreadManForUser::sceKernelStopVTimer();           }
    void sceKernelSetVTimerHandler(AlContext &context)     { V0 = ThreadManForUser::sceKernelSetVTimerHandler();     }
    void sceKernelCancelVTimerHandler(AlContext &context)  { V0 = ThreadManForUser::sceKernelCancelVTimerHandler();  }
    void sceKernelGetVTimerBaseWide(AlContext &context)    { V0 = ThreadManForUser::sceKernelGetVTimerBaseWide();    }
    void sceKernelGetVTimerTimeWide(AlContext &context)    { V0 = ThreadManForUser::sceKernelGetVTimerTimeWide();    }
    void sceKernelSetVTimerTimeWide(AlContext &context)    { V0 = ThreadManForUser::sceKernelSetVTimerTimeWide();    }
    void sceKernelSetVTimerHandlerWide(AlContext &context) { V0 = ThreadManForUser::sceKernelSetVTimerHandlerWide(); }
    void sceKernelReferVTimerStatus(AlContext &context)    { V0 = ThreadManForUser::sceKernelReferVTimerStatus();    }

    void _sceKernelReturnFromTimerHandler(AlContext &context) { V0 = ThreadManForUser::_sceKernelReturnFromTimerHandler(); }

    /// CALLBACK ///
    void sceKernelCreateCallback(AlContext &context)      { V0 = ThreadManForUser::sceKernelCreateCallback(A0, A1, A2);  }
    void sceKernelDeleteCallback(AlContext &context)      { V0 = ThreadManForUser::sceKernelDeleteCallback(A0);          }
    void sceKernelNotifyCallback(AlContext &context)      { V0 = ThreadManForUser::sceKernelNotifyCallback(A0, A1);      }
    void sceKernelGetCallbackCount(AlContext &context)    { V0 = ThreadManForUser::sceKernelGetCallbackCount(A0);        }
    void sceKernelCancelCallback(AlContext &context)      { V0 = ThreadManForUser::sceKernelCancelCallback(A0);          }
    void sceKernelCheckCallback(AlContext &context)       { V0 = ThreadManForUser::sceKernelCheckCallback();             }
    void sceKernelReferCallbackStatus(AlContext &context) { V0 = ThreadManForUser::sceKernelReferCallbackStatus(A0, A1); }
    void _sceKernelReturnFromCallback(AlContext &context) { V0 = ThreadManForUser::_sceKernelReturnFromCallback();       }

    /// SYSTEM STATUS ///
    void sceKernelReferSystemStatus(AlContext &context)  { V0 = ThreadManForUser::sceKernelReferSystemStatus();  }
    void sceKernelGetThreadmanIdList(AlContext &context) { V0 = ThreadManForUser::sceKernelGetThreadmanIdList(); }
    void sceKernelGetThreadmanIdType(AlContext &context) { V0 = ThreadManForUser::sceKernelGetThreadmanIdType(); }

    /// MUTEX ///
    void sceKernelCreateMutex(AlContext &context)      { V0 = ThreadManForUser::sceKernelCreateMutex();      }
    void sceKernelDeleteMutex(AlContext &context)      { V0 = ThreadManForUser::sceKernelDeleteMutex();      }
    void sceKernelTryLockMutex(AlContext &context)     { V0 = ThreadManForUser::sceKernelTryLockMutex();     }
    void sceKernelLockMutex(AlContext &context)        { V0 = ThreadManForUser::sceKernelLockMutex();        }
	void sceKernelLockMutexCB(AlContext &context)      { V0 = ThreadManForUser::sceKernelLockMutexCB();      }
	void sceKernelUnlockMutex(AlContext &context)      { V0 = ThreadManForUser::sceKernelUnlockMutex();      }
    void sceKernelCancelMutex(AlContext &context)      { V0 = ThreadManForUser::sceKernelCancelMutex();      }
    void sceKernelReferMutexStatus(AlContext &context) { V0 = ThreadManForUser::sceKernelReferMutexStatus(); }

    /// LWMUTEX ///
    void sceKernelCreateLwMutex(AlContext &context)          { V0 = ThreadManForUser::sceKernelCreateLwMutex();          }
    void sceKernelDeleteLwMutex(AlContext &context)          { V0 = ThreadManForUser::sceKernelDeleteLwMutex();          }        
    void sceKernelReferLwMutexStatusByID(AlContext &context) { V0 = ThreadManForUser::sceKernelReferLwMutexStatusByID(); }

    /// MISC. ///
    void sceKernelReferGlobalProfiler(AlContext &context) { V0 = ThreadManForUser::sceKernelReferGlobalProfiler();};
    void sceKernelReferThreadProfiler(AlContext &context) { V0 = ThreadManForUser::sceKernelReferThreadProfiler();};
    void sceKernelDonateWakeupThread(AlContext &context)  { V0 = ThreadManForUser::sceKernelDonateWakeupThread();};

    /// UNKNOWN ///
    void ThreadManForUser_BEED3A47(AlContext &context){ V0 = ThreadManForUser::ThreadManForUser_BEED3A47();};
	void ThreadManForUser_8672E3D0(AlContext &context){ V0 = ThreadManForUser::ThreadManForUser_8672E3D0();};
	void ThreadManForUser_7CFF8CF3(AlContext &context){ V0 = ThreadManForUser::ThreadManForUser_7CFF8CF3();};
	void ThreadManForUser_71040D5C(AlContext &context){ V0 = ThreadManForUser::ThreadManForUser_71040D5C();};	
	void ThreadManForUser_31327F19(AlContext &context){ V0 = ThreadManForUser::ThreadManForUser_31327F19();};
}
