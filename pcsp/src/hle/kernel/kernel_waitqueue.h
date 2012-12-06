#ifndef kernel_waitqueue_h__
#define kernel_waitqueue_h__

#include "kernel_object.h"
#include "kernel_threadqueue.h"

struct KernelWaitQueue
:   KernelObject
{
    declare_kernel_type(KernelWaitQueue, KernelObject);

    enum Attributes
    {
        WAITQUEUE_FIFO     = 0x000U,
        WAITQUEUE_PRIORITY = 0x100U,
    };

    enum WaitType
    {
        WAITTYPE_NONE            =  0,
        WAITTYPE_THREAD          =  1,
        WAITTYPE_SEMA            =  2,
        WAITTYPE_EVENTFLAG       =  3,
        WAITTYPE_MBX             =  4,
        WAITTYPE_VPL             =  5,
        WAITTYPE_FPL             =  6,
        WAITTYPE_MPIPE           =  7,
        WAITTYPE_CALLBACK        =  8,
        WAITTYPE_EVENTHANDLER    =  9,
        WAITTYPE_ALARM           = 10,
        WAITTYPE_VTIMER          = 11,
        WAITTYPE_MUTEX           = 12,
        WAITTYPE_LWMUTEX         = 13,
        WAITTYPE_SLEEP           = 64,
        WAITTYPE_DELAY           = 65,
        WAITTYPE_SUSPEND         = 66,
        WAITTYPE_DORMANT         = 67,
    };

    SceUInt           m_attr;
    u32               m_waiters_count;
    KernelThreadQueue m_waiters_queue;

    KernelWaitQueue(char const *name, SceUInt attr);
    ~KernelWaitQueue();


    int  AddWaitingThread(KernelThread *, int wait_type, u64 time, SceUInt *timeout);
    bool RemoveWaitingThread(KernelThread *);
    void RemoveWaitingThread(KernelThread *, int intr_context, int state);

    virtual int Cancel();

    virtual int Acquire();
    virtual int Release();
};
#endif // kernel_waitqueue_h__
