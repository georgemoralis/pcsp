#ifndef sceUmdUser_h__
#define sceUmdUser_h__

namespace sceUmdUser
{
    extern bool Reboot();
    extern bool ShutDown();

	extern int sceUmdDeactivate(); 
	extern int sceUmdReplacePermit(); 
	extern int sceUmdActivate(); 
	extern int sceUmdUnRegisterUMDCallBack(); 
	extern int sceUmdRegisterUMDCallBack(); 
	extern int sceUmdWaitDriveStat(); 
	extern int sceUmdReplaceProhibit(); 
	extern int sceUmdGetDriveStat(); 
	extern int sceUmdCancelWaitDriveStat(); 
	extern int sceUmdWaitDriveStatWithTimer(); 
	extern int sceUmdWaitDriveStatCB(); 
	extern int sceUmdCheckMedium(); 
	extern int sceUmdGetDiscInfo(); 
	extern int sceUmdGetErrorStat(); 
}
#endif // sceUmdUser_h__
