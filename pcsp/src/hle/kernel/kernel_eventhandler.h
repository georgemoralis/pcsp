#pragma once

#include "kernel_object.h"
#include "kernel_thread.h"

struct KernelEventHandler
:   KernelWaitQueue
,   LinkedList< KernelEventHandler >::Node
{
    declare_kernel_type(KernelEventHandler, KernelWaitQueue);
};
