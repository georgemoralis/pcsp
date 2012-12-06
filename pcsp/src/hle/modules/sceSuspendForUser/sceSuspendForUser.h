#ifndef sceSuspendForUser_h__
#define sceSuspendForUser_h__

namespace sceSuspendForUser
{
	static bool volatileMemLocked;


    extern bool Reboot();
    extern bool ShutDown();

	extern int sceKernelPowerLock(); 
	extern int sceKernelVolatileMemUnlock(); 
	extern int sceKernelVolatileMemTryLock(); 
	extern int sceKernelVolatileMemLock(); 
	extern int sceKernelPowerUnlock(); 
	extern int sceKernelPowerTick(); 
}
#endif // sceSuspendForUser_h__
