#pragma once
#include "kernel_object.h"
#include "kernel_thread.h"

struct KernelFpl
:   KernelWaitQueue
{
    declare_kernel_type(KernelFpl, KernelWaitQueue);

    int                                 m_pool_blocks;
    int                                 m_free_blocks;
    SceKernelFplOptParam                m_opt_param;
    int                                 m_block_size;
    SceUID                              m_heap_uid;

    KernelFpl(SceUID heap_uid, SceUInt attributes, SceSize block_size, int block_count, SceKernelFplOptParam *opt_param, char const *name);
    ~KernelFpl();

    int Allocate(u32 *addr, SceUInt *timeout);
    int AllocateCB(u32 *addr, SceUInt *timeout);
    int TryAllocate(u32 *addr);
    int Free(u32 addr);
    int Cancel(int *waiting_threads);
    int ReferStatus(SceKernelFplInfo *info);
};

