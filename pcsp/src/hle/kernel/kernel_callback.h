#ifndef kernel_callback_h__
#define kernel_callback_h__

#include "kernel_waitqueue.h"

struct KernelCallback;

struct KernelCallbackQueue : public LinkedList< KernelCallback >
{
    KernelCallbackQueue() : LinkedList< KernelCallback >() { Clear(); }
};

struct KernelCallback
:   KernelWaitQueue
,   KernelCallbackQueue::Node
{
    declare_kernel_type(KernelCallback, KernelWaitQueue);

    bool                       m_to_delete;
    int                        m_uses;
    KernelThread              *m_thread;
    int                        m_notify_count;
    int                        m_notify_arg;
    SceKernelCallbackFunction  m_function;
    u32                        m_cookie;
    u32                        m_gp;

	KernelCallback(char const *name, SceKernelCallbackFunction callback, u32 cookie);
	~KernelCallback();

    static int Create(char const *name, SceKernelCallbackFunction callback, u32 cookie, int intr);
    int        Delete(int intr);
    int        Notify(int arg, int intr);
    int        Cancel(int intr);
    int        GetCount(int intr);
    int        Check(int intr);
    int        ReferStatus(SceKernelCallbackInfo *info, int intr);
};

#endif // kernel_callback_h__
