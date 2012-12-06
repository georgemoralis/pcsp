#ifndef InterruptManager_h__
#define InterruptManager_h__

namespace InterruptManager
{
    extern bool Reboot();
    extern bool ShutDown();

	extern int sceKernelIsSubInterruptOccurred(); 
	extern int sceKernelEnableSubIntr(); 
	extern int sceKernelRegisterUserSpaceIntrStack(); 
	extern int sceKernelReleaseSubIntrHandler(); 
	extern int QueryIntrHandlerInfo(); 
	extern int sceKernelRegisterSubIntrHandler(); 
	extern int sceKernelDisableSubIntr(); 
	extern int sceKernelResumeSubIntr(); 
	extern int sceKernelSuspendSubIntr(); 
}
#endif // InterruptManager_h__
