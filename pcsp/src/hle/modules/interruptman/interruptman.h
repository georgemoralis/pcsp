#pragma once

#include "hle/kernel/object.h"
#include "hle/kernel/partition.h"

namespace InterruptManager
{
	extern int sceKernelRegisterSubIntrHandler();
	extern int sceKernelReleaseSubIntrHandler();
	extern int sceKernelEnableSubIntr();
	extern int sceKernelDisableSubIntr();
	extern int sceKernelSuspendSubIntr();
	extern int sceKernelResumeSubIntr();
	extern int sceKernelIsSubInterruptOccurred();
	extern int QueryIntrHandlerInfo();
	extern int sceKernelRegisterUserSpaceIntrStack();
}
