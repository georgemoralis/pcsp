#pragma once

#include "kernel_object.h"
#include "kernel_thread.h"
#include "kernel_types.h"

struct KernelEventFlag
:   KernelWaitQueue
{
    declare_kernel_type(KernelEventFlag, KernelWaitQueue);

    enum WaitAttribute
    {
        WAITATTR_SINGLE   = 0x0000U,
        WAITATTR_MULTIPLE = 0x0200U
    };

    enum WaitMode
    {
        WAITMODE_AND           = 0x0000,
        WAITMODE_OR            = 0x0001,
        WAITMODE_CLEAR_ALL     = 0x0010,
        WAITMODE_CLEAR_MATCHED = 0x0020
    };

    int                         m_initial_pattern;
    int                         m_current_pattern;
    SceKernelEventFlagOptParam  m_opt_param;

    KernelEventFlag(char const *name, SceUInt attr, SceUInt initial_pattern, SceKernelEventFlagOptParam *opt_param);
    ~KernelEventFlag();

    int Set(SceUInt pattern);
    int Clear(SceUInt pattern);
    int Wait(SceUInt pattern, int waitmode, SceUInt *result_pattern, SceUInt *timeout, bool is_cb = false);
    int Poll(SceUInt pattern, int waitmode, SceUInt *result_pattern);
    int Cancel(SceUInt pattern, int *waiters);
    int ReferStatus(SceKernelEventFlagInfo *info);
private:
};

