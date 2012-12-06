#include "stdafx.h"
#include "common_base.h"
#include "kernel_thread.h"
#include "kernel_semaphore.h"

void KernelSemaphore::GetQuickInfos(char *data, size_t size)
{
    ::strncpy(data, GetType(), size-1);
}

KernelSemaphore::KernelSemaphore(char const *name, SceUInt attributes, int initial_count, int maximum_count, SceKernelSemaOptParam *opt_param)
:   KernelWaitQueue(name, attributes)
,   m_initial_count(initial_count)
,   m_maximum_count(maximum_count)
,   m_current_count(initial_count)
,   m_opt_param(opt_param)
{
}

KernelSemaphore::~KernelSemaphore()
{

}

int KernelSemaphore::Signal(int count)
{
  Panic();
  return 0;
}

int KernelSemaphore::Wait(int count, SceUInt *timeout, bool check_callbacks)
{
    unsigned int result;

    if (sceKernelIsIntrContext())
    {
        return SCE_KERNEL_ERROR_ILLEGAL_CONTEXT;
    }

    if (count <= 0)
    {
        return SCE_KERNEL_ERROR_ILLEGAL_COUNT;
    }

    int state = sceKernelCpuSuspendIntr();

    if (state == 0 || theKernelScheduler.m_dispatch_thread_suspended != 0)
    {
        sceKernelCpuResumeIntr(state);

        return SCE_KERNEL_ERROR_CAN_NOT_WAIT;
    }

    if (count > this->m_maximum_count)
    {
        sceKernelCpuResumeIntr(state);

        return SCE_KERNEL_ERROR_ILLEGAL_COUNT;
    }

    SceKernelSysClock sysclock(KernelSysClock::Get());

    if (timeout)
    {
        sysclock += u64(*timeout);
    }

    bool is_waiting = false;

    do
    {
        KernelThread *current_thread = theKernelScheduler.m_current_thread;

        if (check_callbacks && current_thread->m_callback_notify)
        {
            current_thread->DispatchCallbacks(state);
        }

        bool is_fifo = !(this->m_attr & WAITQUEUE_PRIORITY);

        if ((this->m_waiters_count <= 0) || is_fifo || (current_thread->m_current_priority < this->m_waiters_queue.First()->m_current_priority))
        {
            if (is_fifo)
            {
                is_waiting = true;
            }

            if (is_waiting || (this->m_current_count < count))
            {
                current_thread->m_cb_arg1 = count;
            }
            else
            {
                result = 0;

                this->m_current_count -= count;

                break;
            }
        }
        else
        {
            is_waiting = true;

            current_thread->m_cb_arg1 = count;
        }

        current_thread->m_check_callbacks = check_callbacks;

        result = KernelWaitQueue::AddWaitingThread(current_thread, WAITTYPE_SEMA, sysclock, timeout);
    }
    while (check_callbacks && (result == SCE_KERNEL_ERROR_NOTIFY_CALLBACK));

    sceKernelCpuResumeIntr(state);

    return result;
}

int KernelSemaphore::Poll(int count)
{
    if (count <= 0)
    {
        return SCE_KERNEL_ERROR_ILLEGAL_COUNT;
    }

    int state = sceKernelCpuSuspendIntr();

    if (count > this->m_maximum_count)
    {
        sceKernelCpuResumeIntr(state);

        return SCE_KERNEL_ERROR_ILLEGAL_COUNT;
    }

    KernelThread *current_thread = theKernelScheduler.m_current_thread;

    if ((this->m_waiters_count > 0 && (!(this->m_attr & WAITQUEUE_PRIORITY) || current_thread->m_current_priority >= this->m_waiters_queue.First()->m_current_priority)) || this->m_current_count < count)
    {
        sceKernelCpuResumeIntr(state);

        return SCE_KERNEL_ERROR_SEMA_ZERO;
    }

    this->m_current_count -= count;

    sceKernelCpuResumeIntr(state);

    return 0;
}

int KernelSemaphore::Cancel(int count, int *waiters)
{
    int state = sceKernelCpuSuspendIntr();

    if (count > this->m_maximum_count)
    {
        sceKernelCpuResumeIntr(state);

        return SCE_KERNEL_ERROR_ILLEGAL_COUNT;
    }

    int result = KernelWaitQueue::Cancel();

    if (count < 0)
    {
        count = this->m_initial_count;
    }

    this->m_current_count = count;

    if (waiters)
    {
        *waiters = result;
    }

    sceKernelCpuResumeIntr(state);

    return 0;
}

int KernelSemaphore::ReferStatus(SceKernelSemaInfo *info)
{
    int state = sceKernelCpuSuspendIntr();

    size_t size = info->size < sizeof(SceKernelSemaInfo) ? info->size : sizeof(SceKernelSemaInfo);

    if (size >= sizeof(SceKernelStructureSize))
    {
        ::memset(info, 0, size);

        info->size = sizeof(SceKernelSemaInfo);

        if (size >= sizeof(SceKernelStructureName))
        {
            if (this->m_name)
            {
                ::strncpy(info->name, this->m_name, sizeof(this->m_name) - 1);
            }

            if (size >= sizeof(SceKernelStructureAttr))
            {
                info->attributes = this->m_attr;

                if (size >= sizeof(SceKernelSemaInfo))
                {
                    info->initial_count   = this->m_initial_count;
                    info->current_count   = this->m_current_count;
                    info->maximum_count   = this->m_maximum_count;
                    info->waiting_threads = this->m_waiters_count;
                }
            } 
        }
    }

    sceKernelCpuResumeIntr(state);

    return 0;
}
