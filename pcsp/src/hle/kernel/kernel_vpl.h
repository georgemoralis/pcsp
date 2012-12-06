#pragma once
#include "kernel_object.h"
#include "kernel_thread.h"

struct KernelVpl
:   KernelWaitQueue
{
    declare_kernel_type(KernelVpl, KernelWaitQueue);

    int                                 m_pool_size;
    int                                 m_free_size;
    SceKernelVplOptParam                m_opt_param;
    SceUID                              m_heap_uid;

    KernelVpl(SceUID heap_uid, SceUInt attributes, SceSize size, SceKernelVplOptParam *opt_param, char const *name);
    ~KernelVpl();

    int Allocate(SceSize size, u32 *addr, SceUInt *timeout);
    int AllocateCB(SceSize size, u32 *addr, SceUInt *timeout);
    int TryAllocate(SceSize size, u32 *addr);
    int Free(u32 addr);
    int Cancel(int *waiting_threads);
    int ReferStatus(SceKernelVplInfo *info);
};

