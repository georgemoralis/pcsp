#pragma once
#include "kernel_object.h"
#include "kernel_thread.h"

struct KernelMsgBox
:   KernelWaitQueue
{
    declare_kernel_type(KernelMsgBox, KernelWaitQueue);
};

