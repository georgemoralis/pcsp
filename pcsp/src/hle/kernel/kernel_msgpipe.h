#pragma once
#include "kernel_object.h"
#include "kernel_thread.h"

struct KernelMsgPipe
:   KernelWaitQueue
{
    declare_kernel_type(KernelMsgPipe, KernelWaitQueue);
};

