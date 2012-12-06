#include "stdafx.h"

#include "kernel_msgpipe.h"

void KernelMsgPipe::GetQuickInfos(char *data, size_t size)
{
    ::strncpy(data, GetType(), size-1);
}
