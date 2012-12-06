#ifndef StdioForUser_h__
#define StdioForUser_h__

namespace StdioForUser
{
    extern bool Reboot();
    extern bool ShutDown();

    extern int sceKernelStderr(); 
	extern int sceKernelStdout(); 
	extern int sceKernelStdioSendChar(); 
	extern int sceKernelStdioWrite(); 
	extern int sceKernelStdioClose(); 
	extern int sceKernelStdioOpen(); 
	extern int sceKernelRegisterStderrPipe(); 
	extern int sceKernelRegisterStdoutPipe(); 
	extern int sceKernelStdioRead(); 
	extern int sceKernelStdin(); 
	extern int sceKernelStdioLseek(); 
}
#endif // StdioForUser_h__
