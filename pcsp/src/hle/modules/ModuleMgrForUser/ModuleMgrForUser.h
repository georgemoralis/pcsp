#ifndef ModuleMgrForUser_h__
#define ModuleMgrForUser_h__

namespace ModuleMgrForUser
{
    extern bool Reboot();
    extern bool ShutDown();

	extern int ModuleMgrForUser_FEF27DC1(); 
	extern int ModuleMgrForUser_FBE27467(); 
	extern int sceKernelLoadModuleBufferUsbWlan(); 
	extern int ModuleMgrForUser_F2D8D1B4(); 
	extern int sceKernelGetModuleId(); 
	extern int ModuleMgrForUser_E4C4211C(); 
	extern int sceKernelGetModuleIdByAddress(); 
	extern int sceKernelSelfStopUnloadModule(); 
	extern int sceKernelGetModuleGPByAddress(); 
	extern int sceKernelStopModule(); 
	extern int sceKernelStopUnloadSelfModule(); 
	extern int sceKernelLoadModuleByID(); 
	extern int sceKernelLoadModule(); 
	extern int ModuleMgrForUser_8F2DF740(); 
	extern int sceKernelQueryModuleInfo(); 
	extern int sceKernelLoadModuleMs(); 
	extern int sceKernelGetModuleIdList(); 
	extern int sceKernelStartModule(); 
	extern int sceKernelUnloadModule(); 
	extern int ModuleMgrForUser_24EC0641(); 
	extern int ModuleMgrForUser_1196472E(); 
}
#endif // ModuleMgrForUser_h__
