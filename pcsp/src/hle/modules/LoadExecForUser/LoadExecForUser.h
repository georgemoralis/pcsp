#ifndef LoadExecForUser_h__
#define LoadExecForUser_h__

namespace LoadExecForUser
{
    extern bool Reboot();
    extern bool ShutDown();

    extern int LoadExecForUser_D1FB50DC(); 
	extern int sceKernelLoadExec(); 
	extern int LoadExecForUser_8ADA38D3(); 
	extern int sceKernelRegisterExitCallback(); 
	extern int LoadExecForUser_362A956B(); 
	extern int sceKernelExitGameWithStatus(); 
	extern int sceKernelExitGame(); 
}

#endif // LoadExecForUser_h__
