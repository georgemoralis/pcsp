#include "stdafx.h"

#include "kernel_types.h"

#include "kernel_eventflag.h"
#include "kernel_thread.h"

void KernelEventFlag::GetQuickInfos(char *data, size_t size)
{
    ::strncpy(data, GetType(), size-1);
}

KernelEventFlag::KernelEventFlag(char const *name, SceUInt attributes, SceUInt initial_pattern, SceKernelEventFlagOptParam *opt_param)
:   KernelWaitQueue(name, attributes)
,   m_initial_pattern(initial_pattern)
,   m_current_pattern(initial_pattern)
,   m_opt_param(*opt_param)
{
}

KernelEventFlag::~KernelEventFlag()
{

}

int KernelEventFlag::Set(SceUInt pattern)
{
    int state = sceKernelCpuSuspendIntr();

    int is_intr_context = sceKernelIsIntrContext();

    if (pattern != 0)
    {
        this->m_current_pattern |= pattern;

        KernelThread *this_thread, *last_thread;
    
        int ready_threads = 0;

        for (this_thread = this->m_waiters_queue.First(); this_thread; this_thread = this->m_waiters_queue.Next(this_thread))
        {
            if (this->m_current_pattern == 0)
            {
                break;
            }

            int matched;
            int pattern  = this_thread->m_cb_arg1;
            int waitmode = this_thread->m_cb_arg2;

            if (this_thread->m_cb_arg2 & WAITMODE_OR)
            {
                matched = this->m_current_pattern & pattern;
            }
            else
            {
                matched = (this->m_current_pattern & pattern) == pattern;
            }

            if (matched)
            {
                if (this_thread->m_cb_arg3 != 0)
                {
                    Memory::mem< int >(this_thread->m_cb_arg3) = this->m_current_pattern;
                }

                if (waitmode & WAITMODE_CLEAR_ALL)
                {
                    this->m_current_pattern = 0;
                }
                else if (waitmode & WAITMODE_CLEAR_MATCHED)
                {
                    this->m_current_pattern &= ~pattern;
                }

                if (this_thread->ReleaseWaitingThread())
                {
                    theKernelScheduler.AddThreadToReadyQueue(this_thread);

                    last_thread = this_thread;

                    ++ready_threads;
                }
            }
        }

        if (is_intr_context && ready_threads > 0) 
        {
            theKernelScheduler.m_next_thread = 0;
        }
        else if (ready_threads == 1)
        {
            theKernelScheduler.RemoveThreadFromReadyQueue(last_thread);
            last_thread->SwitchTo(state);
        }
        else if (ready_threads > 0)
        {
            theKernelScheduler.m_next_thread = 0;
            this_thread->ReleaseWait(0, state);
        }
    }

    sceKernelCpuResumeIntr(state);

    return 0;
}

int KernelEventFlag::Clear(SceUInt pattern)
{
    int intr = sceKernelCpuSuspendIntr();

    this->m_current_pattern &= pattern;

    sceKernelCpuResumeIntr(intr);

    return 0;
}

int KernelEventFlag::Wait(SceUInt pattern, int waitmode, SceUInt *result_pattern, SceUInt *timeout, bool is_cb)
{
    int result = 0;

    if (sceKernelIsIntrContext())
    {
        return SCE_KERNEL_ERROR_ILLEGAL_CONTEXT;
    }

    if ((waitmode & ~(WAITMODE_CLEAR_MATCHED|WAITMODE_CLEAR_ALL|WAITMODE_OR)) || (waitmode & (WAITMODE_CLEAR_MATCHED|WAITMODE_CLEAR_ALL)) == (WAITMODE_CLEAR_MATCHED|WAITMODE_CLEAR_ALL))
    {
        return SCE_KERNEL_ERROR_ILLEGAL_MODE;
    }

    if (pattern == 0)
    {
        return SCE_KERNEL_ERROR_EVF_ILPAT;
    }

    int state = sceKernelCpuSuspendIntr();

    if (state == 0 || theKernelScheduler.m_dispatch_thread_suspended)
    {
        sceKernelCpuResumeIntr(state);

        return SCE_KERNEL_ERROR_CAN_NOT_WAIT;
    }

    if (!(this->m_attr & WAITATTR_MULTIPLE) && this->m_waiters_count > 0)
    {
        sceKernelCpuResumeIntr(state);

        return SCE_KERNEL_ERROR_EVF_MULTI;
    }

    KernelThread *this_thread = theKernelScheduler.m_current_thread;

    SceKernelSysClock sysclock(KernelSysClock::Get());

    if (timeout)
    {
        sysclock += u64(*timeout);
    }

    do
    {
        if (timeout && theKernelScheduler.m_current_thread->m_callback_notify != 0)
        {
            this_thread->DispatchCallbacks(state);
        }

        u32 matched;

        if (waitmode & WAITMODE_OR)
        {
            matched = this->m_current_pattern & pattern;
        }
        else
        {
            matched = ((this->m_current_pattern & pattern) == pattern);
        }

        if (matched)
        {
            if (result_pattern)
            {
                *result_pattern = this->m_current_pattern;
            }

            if (waitmode & WAITMODE_CLEAR_ALL)
            {
                this->m_current_pattern = 0;
            }
            else if (waitmode & WAITMODE_CLEAR_MATCHED)
            {
                this->m_current_pattern &= ~pattern;
            }

            sceKernelCpuResumeIntr(state);

            return 0;
        }

        *((SceUInt  *)this_thread->m_cb_arg1) = pattern;
        *((int      *)this_thread->m_cb_arg2) = waitmode;
        *((SceUInt **)this_thread->m_cb_arg3) = result_pattern;
        this_thread->m_check_callbacks = is_cb;

        result = this_thread->m_wait_queue->AddWaitingThread(this_thread, KernelWaitQueue::WAITTYPE_EVENTFLAG, sysclock, timeout);
    }
    while(is_cb && (result == SCE_KERNEL_ERROR_NOTIFY_CALLBACK));

    if (result > 0 && result_pattern)
    {
        *result_pattern = this->m_current_pattern;
    }

    sceKernelCpuResumeIntr(state);

    return result;
}


int KernelEventFlag::Poll(SceUInt pattern, int waitmode, SceUInt *result_pattern)
{
    if ((waitmode & ~(WAITMODE_CLEAR_MATCHED|WAITMODE_CLEAR_ALL|WAITMODE_OR)) || (waitmode & (WAITMODE_CLEAR_MATCHED|WAITMODE_CLEAR_ALL)) == (WAITMODE_CLEAR_MATCHED|WAITMODE_CLEAR_ALL))
    {
        return SCE_KERNEL_ERROR_ILLEGAL_MODE;
    }

    if (pattern == 0)
    {
        return SCE_KERNEL_ERROR_EVF_ILPAT;
    }

    int state = sceKernelCpuSuspendIntr();

    if (!(this->m_attr & WAITATTR_MULTIPLE) && this->m_waiters_count > 0)
    {
        sceKernelCpuResumeIntr(state);

        return SCE_KERNEL_ERROR_EVF_MULTI;
    }

    u32 matched;

    if (waitmode & WAITMODE_OR)
    {
        matched = this->m_current_pattern & pattern;
    }
    else
    {
        matched = ((this->m_current_pattern & pattern) == pattern);
    }

    if (result_pattern)
    {
        *result_pattern = this->m_current_pattern;
    }

    if (matched == 0)
    {
        sceKernelCpuResumeIntr(state);

        return SCE_KERNEL_ERROR_EVF_COND;
    }

    if (waitmode & WAITMODE_CLEAR_ALL)
    {
        this->m_current_pattern = 0;
    }
    else if (waitmode & WAITMODE_CLEAR_MATCHED)
    {
        this->m_current_pattern &= ~pattern;
    }

    sceKernelCpuResumeIntr(state);

    return 0;
}

int KernelEventFlag::Cancel(SceUInt pattern, int *waiters)
{
    int intr = sceKernelCpuSuspendIntr();

    int result = KernelWaitQueue::Cancel();

    this->m_current_pattern = pattern;

    if (waiters)
    {
        *waiters = result;
    }

    sceKernelCpuResumeIntr(intr);

    return 0;
}

int KernelEventFlag::ReferStatus(SceKernelEventFlagInfo *info)
{
    int intr = sceKernelCpuSuspendIntr();

    int size = info->size < sizeof(SceKernelEventFlagInfo) ? info->size : sizeof(SceKernelEventFlagInfo);

    if (size >= sizeof(SceKernelStructureSize))
    {
        ::memset(info, 0, size);

        info->size = sizeof(SceKernelEventFlagInfo);

        if (size >= sizeof(SceKernelStructureName))
        {
            if (this->m_name)
            {
                ::strncpy(info->name, this->m_name, sizeof(this->m_name) - 1);
            }

            if (size >= sizeof(SceKernelStructureAttr))
            {
                info->attributes = this->m_attr;

                if (size >= sizeof(SceKernelEventFlagInfo))
                {
                    info->initial_pattern = this->m_initial_pattern;
                    info->current_pattern = this->m_current_pattern;
                    info->waiting_threads = this->m_waiters_count;
                }
            }
        }
    }

    sceKernelCpuResumeIntr(intr);

    return 0;
}