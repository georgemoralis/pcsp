#ifndef sysmem_h__
#define sysmem_h__

#include "hle/kernel/kernel_object.h"
#include "hle/kernel/kernel_partition.h"

#include "log.h"

namespace Log
{
    extern LogSubCategory sceKernelMaxFreeMemSize;
    extern LogSubCategory sceKernelTotalFreeMemSize;
    extern LogSubCategory sceKernelAllocPartitionMemory;
    extern LogSubCategory sceKernelFreePartitionMemory;
    extern LogSubCategory sceKernelGetBlockHeadAddr;
    extern LogSubCategory sceKernelPrintf;
    extern LogSubCategory sceKernelDevkitVersion;
    extern LogSubCategory sceKernelSetCompilerVersion;
    extern LogSubCategory sceKernelSetCompiledSdkVersion;
}

typedef struct PspSysmemPartitionInfo
{
	u32 size;
	u32 startaddr;
	u32 memsize;
	u32 attr;
} PspSysmemPartitionInfo;


namespace SysMemUserForUser
{
    extern bool Reboot();
    extern bool ShutDown();

	extern int sceKernelMaxFreeMemSize();
	extern int sceKernelTotalFreeMemSize();
	extern int sceKernelAllocPartitionMemory(int a0, int a1, int a2, int a3, int t0);
	extern int sceKernelFreePartitionMemory(int a0);
	extern int sceKernelGetBlockHeadAddr(int a0);
	extern int sceKernelPrintf();
	extern int sceKernelDevkitVersion();
    extern int sceKernelSetCompilerVersion(int a0);
    extern int sceKernelSetCompiledSdkVersion(int a0);
    extern int sceKernelGetCompiledSdkVersion(int a0);
	extern int SysMemUserForUser_057E7380();
	extern int sceKernelQueryMemoryInfo();
	extern int SysMemUserForUser_315AD3A0();
	extern int SysMemUserForUser_342061E5();
	extern int SysMemUserForUser_50F61D8A();	
	extern int SysMemUserForUser_91DE343C();
	extern int SysMemUserForUser_A6848DF8();
	extern int SysMemUserForUser_ACBD88CA();
	extern int SysMemUserForUser_D8DE5C1E();
	extern int SysMemUserForUser_DB83A952();
	extern int SysMemUserForUser_EBD5C3E6();
	extern int sceKernelGetCompiledSdkVersion(int a0);
	extern int SysMemUserForUser_FE707FDF();
}

namespace sysmem
{
	extern KernelPartition *hleKernelGetPartition(SceUID uid);
	extern u32              hleKernelMaxFreeMemSize(SceUID uid);
	extern u32              hleKernelTotalFreeMemSize(SceUID uid);
    extern SceUID           hleKernelAllocPartitionMemory(KernelPartition &partition, const char *name, int type, u32 size, u32 addr, KernelPartitionBlock *&that);
    extern SceUID           hleKernelAllocPartitionMemory(SceUID uid, const char *name, int type, u32 size, u32 addr);
    extern int              hleKernelFreePartitionMemory(SceUID uid);
	extern int              hleKernelGetBlockHeadAddr(SceUID uid);

    extern SceUID           hleKernelCreateHeap(SceUID uid, SceSize size, int attr, const char *name);
    extern int              hleKernelDeleteHeap(SceUID uid);
    extern u32              hleKernelAllocHeapMemoryWithOption(SceUID uid, SceSize size, SceKernelHeapOptParam *option);
    extern u32              hleKernelAllocHeapMemory(SceUID uid, SceSize size);
    extern int              hleKernelFreeHeapMemory(SceUID uid, u32 address);
    extern SceSize          hleKernelHeapTotalFreeSize(SceUID uid);
}
#endif // sysmem_h__
