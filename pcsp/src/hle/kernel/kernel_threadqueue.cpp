#include "stdafx.h"

#include "kernel_threadqueue.h"
#include "kernel_thread.h"

int KernelThreadQueue::AddWaitingThread(KernelThread *this_thread, int wait_type)
{
    this->Append(this_thread);
    this_thread->m_status          = KernelThread::STATUS_WAIT;
    this_thread->m_wait_type       = wait_type;
    this_thread->m_wait_queue      = 0; // no KernelWaitQueue 
    this_thread->m_callback_status = 0;

    return 0;
}
