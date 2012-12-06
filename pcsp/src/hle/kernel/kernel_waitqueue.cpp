#include "stdafx.h"

#include "kernel_waitqueue.h"
#include "kernel_thread.h"

void KernelWaitQueue::GetQuickInfos(char *data, size_t size)
{
    ::strncpy(data, GetType(), size-1);
}

KernelWaitQueue::KernelWaitQueue(char const *name, SceUInt attr)
:   KernelObject(name)
,   m_attr(attr)
,   m_waiters_count(0)
{
}

KernelWaitQueue::~KernelWaitQueue()
{
}

int KernelWaitQueue::Cancel()
{
    int i;

    KernelThread *waiting_thread;

    // for each thread in the wait queue, we wake them up 
    for (i = 0, waiting_thread = this->m_waiters_queue.First(); waiting_thread; ++i, waiting_thread = this->m_waiters_queue.Next(waiting_thread))
    {
        waiting_thread->ReleaseWaitingThread();
        waiting_thread->m_callback_status = SCE_KERNEL_ERROR_WAIT_CANCEL;
    }

    if (i != 0)
    {
        theKernelScheduler.m_next_thread = 0;
        theKernelScheduler.m_current_thread->ReleaseWait(false, 0);
    }

    return i;
}


int KernelWaitQueue::AddWaitingThread(KernelThread *current_thread, int wait_type, u64 time, SceUInt *timeout)
{
    current_thread->m_timeout_object = 0;
    current_thread->m_timeout        = 0;

    if (timeout)
    {
        int result = current_thread->RequestTimeout(time);
        if (!result)
        {
            return result;
        }

        current_thread->m_timeout = (int *)timeout;
    }

    current_thread->m_status          = KernelThread::STATUS_WAIT;
    current_thread->m_wait_type       = wait_type;
    current_thread->m_wait_queue      = this;
    current_thread->m_callback_status = 0;

    this->m_waiters_count++;

    if (!(this->m_attr & WAITQUEUE_PRIORITY))
    {
        this->m_waiters_queue.Append(current_thread);
    }
    else
    {
        KernelThread *previous_thread;

        for (previous_thread = this->m_waiters_queue.First(); previous_thread; previous_thread = this->m_waiters_queue.Next(previous_thread))
        {
            if (previous_thread->m_current_priority > current_thread->m_current_priority)
            {
                current_thread->InsertInListBefore(previous_thread);

                break;
            }
        }

        if (!previous_thread)
        {
            this->m_waiters_queue.Append(current_thread);
        }
    }

    theKernelScheduler.m_next_thread = 0;
    current_thread->ReleaseWait(true, 0);

    return current_thread->m_callback_status;
}

int KernelWaitQueue::Acquire()
{
    return 0;
}

int KernelWaitQueue::Release()
{
    this->m_waiters_count--;

    return 0;
}

bool KernelWaitQueue::RemoveWaitingThread(KernelThread *this_thread)
{
    return this_thread->ReleaseWaitingThread();
}

void KernelWaitQueue::RemoveWaitingThread(KernelThread *this_thread, int intr_context, int state)
{
    this_thread->ReleaseWaitingThread(intr_context, state);
}
