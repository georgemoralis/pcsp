#include "stdafx.h"

#include "kernel_eventhandler.h"
#include "kernel_thread.h"

void KernelEventHandler::GetQuickInfos(char *data, size_t size)
{
    ::strncpy(data, GetType(), size-1);
}
