#ifndef kernel_threadqueue_h__
#define kernel_threadqueue_h__

#include "kernel_object.h"

#include "common_linked_list.h"

struct KernelThread;

struct KernelThreadQueue : public LinkedList< KernelThread >
{
    KernelThreadQueue() : LinkedList< KernelThread >() { Clear(); }

    int AddWaitingThread(KernelThread *, int wait_type);
};
#endif // kernel_threadqueue_h__
