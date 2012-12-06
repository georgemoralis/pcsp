#include "stdafx.h"

#include "kernel_msgbox.h"

void KernelMsgBox::GetQuickInfos(char *data, size_t size)
{
    ::strncpy(data, GetType(), size-1);
}
