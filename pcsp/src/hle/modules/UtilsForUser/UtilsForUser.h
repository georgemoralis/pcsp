#ifndef UtilsForUser_h__
#define UtilsForUser_h__

namespace UtilsForUser
{
    extern bool Reboot();
    extern bool ShutDown();

    extern int sceKernelIcacheReadTag(); 
	extern int sceKernelUtilsSha1BlockInit(); 
	extern int UtilsForUser_F0155BCA(); 
	extern int sceKernelUtilsMt19937Init(); 
	extern int UtilsForUser_DBBE9A46(); 
	extern int sceKernelUtilsMd5Digest(); 
	extern int sceKernelIcacheInvalidateRange(); 
	extern int sceKernelDcacheInvalidateRange(); 
	extern int sceKernelUtilsMd5BlockResult(); 
	extern int UtilsForUser_B83A1E76(); 
	extern int sceKernelDcacheWritebackInvalidateAll(); 
	extern int UtilsForUser_AF3766BB(); 
	extern int sceKernelUtilsMd5BlockInit(); 
	extern int UtilsForUser_99134C3F(); 
	extern int sceKernelIcacheInvalidateAll(); 
	extern int sceKernelLibcClock(); 
	extern int sceKernelPutUserLog(); 
	extern int sceKernelUtilsSha1Digest(); 
	extern int sceKernelDcacheProbe(); 
	extern int sceKernelDcacheWritebackAll(); 
	extern int sceKernelDcacheProbeRange(); 
	extern int UtilsForUser_740DF7F0(); 
	extern int UtilsForUser_7333E539(); 
	extern int sceKernelLibcGettimeofday(u32 a0); 
	extern int sceKernelSetGPO(); 
	extern int UtilsForUser_6231A71D(); 
	extern int sceKernelUtilsMd5BlockUpdate(); 
	extern int UtilsForUser_5C7F2B1A(); 
	extern int sceKernelUtilsSha1BlockResult(); 
	extern int UtilsForUser_515B4FAF(); 
	extern int sceKernelIcacheProbe(); 
	extern int UtilsForUser_43C9A8DB(); 
	extern int UtilsForUser_3FD3D324(); 
	extern int sceKernelDcacheWritebackRange(); 
	extern int UtilsForUser_39F49610(); 
	extern int sceKernelGetGPI(); 
	extern int sceKernelDcacheWritebackInvalidateRange(); 
	extern int sceKernelUtilsSha1BlockUpdate(); 
	extern int sceKernelLibcTime(u32 a0); 
	extern int UtilsForUser_1B0592A3(); 
	extern int sceKernelDcacheReadTag(); 
	extern int UtilsForUser_157A383A(); 
	extern int sceKernelUtilsMt19937UInt(); 
	extern int UtilsForUser_004D4DEE(); 
}

#endif // UtilsForUser_h__
