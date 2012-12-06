#ifndef Kernel_Library_h__
#define Kernel_Library_h__



namespace Kernel_Library
{
	#define FLAG_INTERRUPTS_ENABLED   1
    #define FLAG_INTERRUPTS_DISABLED  0
	static bool interruptsEnabled = true;

    extern bool Reboot();
    extern bool ShutDown();

    extern int sceKernelTryLockLwMutex(); 
	extern int sceKernelReferLwMutexStatus(); 
	extern int sceKernelLockLwMutex(); 
	extern int sceKernelIsCpuIntrEnable(); 
	extern int sceKernelCpuResumeIntr(); 
	extern int sceKernelIsCpuIntrSuspended(); 
	extern int sceKernelCpuResumeIntrWithSync(); 
	extern int sceKernelLockLwMutexCB(); 
	extern int sceKernelUnlockLwMutex(); 
	extern int sceKernelCpuSuspendIntr(); 
}
#endif // Kernel_Library_h__
