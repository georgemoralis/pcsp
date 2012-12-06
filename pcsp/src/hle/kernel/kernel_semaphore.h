#pragma once
#include "kernel_object.h"
#include "kernel_thread.h"

struct KernelSemaphore
:   KernelWaitQueue
{
    declare_kernel_type(KernelSemaphore, KernelWaitQueue);

    int                    m_initial_count;
    int                    m_maximum_count;
    int                    m_current_count;
    SceKernelSemaOptParam *m_opt_param;

    KernelSemaphore(char const *name, SceUInt attributes, int initial_count, int maximum_count, SceKernelSemaOptParam *opt_param);
    ~KernelSemaphore();

    int Signal(int count);
    int Wait(int count, SceUInt *timeout, bool is_cb = false);
    int Poll(int count);
    int Cancel(int count, int *waiters);
    int ReferStatus(SceKernelSemaInfo *info);
};

