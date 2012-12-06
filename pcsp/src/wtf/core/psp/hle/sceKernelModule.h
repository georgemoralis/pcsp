#include "hle/kernel/kernel_types.h"
#include "hle/kernel/kernel_module.h"

namespace hle
{
	extern KernelModule *__KernelLoadModule(u8 *fileptr, SceUID &id, SceKernelLMOption *options);
	extern void __KernelStartModule(KernelModule *m, int args, const char *argp, SceKernelSMOption *options);
    extern void __KernelLoadExec(u8 *ptr, const char *filename);	
    extern void __KernelUnLoadModule();
    extern u32  __KernelGetModuleGP(SceUID module);
}