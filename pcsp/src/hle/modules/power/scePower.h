#ifndef scePower_h__
#define scePower_h__

#define PSP_POWER_CB_POWER_SWITCH     0x80000000
#define PSP_POWER_CB_HOLD_SWITCH      0x40000000
#define PSP_POWER_CB_STANDBY          0x00080000
#define PSP_POWER_CB_RESUME_COMPLETE  0x00040000
#define PSP_POWER_CB_RESUMING         0x00020000
#define PSP_POWER_CB_SUSPENDING       0x00010000
#define PSP_POWER_CB_AC_POWER         0x00001000
#define PSP_POWER_CB_BATTERY_LOW      0x00000100
#define PSP_POWER_CB_BATTERY_EXIST    0x00000080
#define PSP_POWER_CB_BATTPOWER        0x0000007F

namespace scePower
{
    extern bool Reboot();
    extern bool ShutDown();

	static int cpuClock = 222;
	static int busClock = 111;
    static int backlightMaximum = 4;
    static int lifeTime = (5 * 60);
    static int temperature = 28;
    static int voltage = 4135;
    static bool pluggedIn = true;
    static bool present = true;
    static int currentPowerPercent = 100;
    static int lowPercent = 12;
    static int forceSuspendPercent = 4;
    static int fullCapacity = 1800;
    static bool charging = false;


	extern int scePowerGetCpuClockFrequency(); 
	extern int scePowerGetCpuClockFrequencyInt(); 
	extern int scePowerGetBatteryFullCapacity(); 
	extern int scePowerVolatileMemTryLock(); 
	extern int scePowerTick(); 
	extern int scePowerGetIdleTimer(); 
	extern int scePower_EBD177D6(); 
	extern int scePowerGetPllClockFrequencyFloat(); 
	extern int scePower_E8E4E204(); 
	extern int scePowerUnregisterCallback(); 
	extern int scePowerUnregitserCallback(); 
	extern int scePowerCancelRequest(); 
	extern int scePowerLock(); 
	extern int scePowerIsLowBattery(); 
	extern int scePowerGetBatteryChargeCycle(); 
	extern int scePowerUnlock(); 
	extern int scePowerGetBusClockFrequencyInt(); 
	extern int scePowerGetCallbackMode(); 
	extern int scePowerGetLowBatteryCapacity(); 
	extern int scePowerSetBusClockFrequency(); 
	extern int scePowerGetBatteryChargingStatus(); 
	extern int scePowerVolatileMemUnlock(); 
	extern int scePowerGetCpuClockFrequencyFloat(); 
	extern int scePowerRequestSuspend(); 
	extern int scePowerSetCallbackMode(); 
	extern int scePower_A4E93389(); 
	extern int scePowerGetBusClockFrequencyFloat(); 
	extern int scePowerIdleTimerDisable(); 
	extern int scePowerGetBatteryRemainCapacity(); 
	extern int scePowerGetBatteryLifeTime(); 
	extern int scePowerIsPowerOnline(); 
	extern int scePowerGetBatteryElec(); 
	extern int scePowerSetCpuClockFrequency(); 
	extern int scePowerIsRequest(); 
	extern int scePowerIdleTimerEnable(); 
	extern int scePowerIsSuspendRequired(); 
	extern int scePowerSetClockFrequency(); 
	extern int scePower_545A7F3C(); 
	extern int scePowerGetBatteryVolt(); 
	extern int scePowerGetBusClockFrequency(); 
	extern int scePowerGetBacklightMaximum(); 
	extern int scePowerWaitRequestCompletion(); 
	extern int scePowerGetPllClockFrequencyInt(); 
	extern int scePowerRequestStandby(); 
	extern int scePower_2B51FE2F(); 
	extern int scePowerGetBatteryTemp(); 
	extern int scePower_2875994B(); 
	extern int scePowerBatteryUpdateInfo(); 
	extern int scePowerVolatileMemLock(); 
	extern int scePowerGetInnerTemp(); 
	extern int scePowerGetBatteryLifePercent(); 
	extern int scePowerIsBatteryCharging(); 
	extern int scePowerGetPowerSwMode(); 
	extern int scePowerSetPowerSwMode(); 
	extern int scePowerIsBatteryExist(); 
	extern int scePowerRegisterCallback(); 
	extern int scePowerRequestColdReset(); 
	extern int scePowerGetResumeCount(); 
}
#endif // scePower_h__
