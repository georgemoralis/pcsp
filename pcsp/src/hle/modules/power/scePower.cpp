#include "stdafx.h"
#include "scePower.h"
#include "hle/types.h"
#include "log.h"

namespace scePower
{
    static bool scePower_ready = false;

    bool Reboot()
    {
        ShutDown();
        scePower_ready = true;
        return true;
    }
    bool ShutDown()
    {
        if (scePower_ready)
        {
            scePower_ready = false;
        }
        return true;
    }

	int scePowerGetCpuClockFrequency()
	{
		debugf(scePower,"scePowerGetCpuClockFrequency: Freq = %i", cpuClock);
		return cpuClock;
	}
	int scePowerGetCpuClockFrequencyInt()
	{
		debugf(scePower,"scePowerGetCpuClockFrequencyInt: Freq = %i", cpuClock);
		return cpuClock;
	}
	int scePowerGetBatteryFullCapacity()
	{
		errorf(scePower,"UNIMPLEMENTED scePowerGetBatteryFullCapacity: fullCap = %i", fullCapacity);
		return fullCapacity;
	}
	int scePowerVolatileMemTryLock()
	{
		//TODO implement me
		errorf(scePower,"UNIMPLEMENTED scePowerVolatileMemTryLock instruction");
		return 0;
	}
	int scePowerTick()
	{
		//TODO implement me
		errorf(scePower,"UNIMPLEMENTED scePowerTick instruction");
		return 0;
	}
	int scePowerGetIdleTimer()
	{
		//TODO implement me
		errorf(scePower,"UNIMPLEMENTED scePowerGetIdleTimer instruction");
		return 0;
	}
	int scePower_EBD177D6()
	{
		//TODO implement me
		errorf(scePower,"UNIMPLEMENTED scePower_EBD177D6 instruction");
		return 0;
	}
	int scePowerGetPllClockFrequencyFloat()
	{
		//TODO implement me
		errorf(scePower,"UNIMPLEMENTED scePowerGetPllClockFrequencyFloat instruction");
		return 0;
	}
	int scePower_E8E4E204()
	{
		//TODO implement me
		errorf(scePower,"UNIMPLEMENTED scePower_E8E4E204 instruction");
		return 0;
	}
	int scePowerUnregisterCallback()
	{
		//TODO implement me
		errorf(scePower,"UNIMPLEMENTED scePowerUnregisterCallback instruction");
		return 0;
	}
	int scePowerUnregitserCallback()
	{
		//TODO implement me
		errorf(scePower,"UNIMPLEMENTED scePowerUnregitserCallback instruction");
		return 0;
	}
	int scePowerCancelRequest()
	{
		//TODO implement me
		errorf(scePower,"UNIMPLEMENTED scePowerCancelRequest instruction");
		return 0;
	}
	int scePowerLock()
	{
		//TODO implement me
		errorf(scePower,"UNIMPLEMENTED scePowerLock instruction");
		return 0;
	}
	int scePowerIsLowBattery()
	{
		debugf(scePower,"scePowerIsLowBattery return: 0");
		return 0;
	}
	int scePowerGetBatteryChargeCycle()
	{
		//TODO implement me
		errorf(scePower,"UNIMPLEMENTED scePowerGetBatteryChargeCycle instruction");
		return 0;
	}
	int scePowerUnlock()
	{
		//TODO implement me
		errorf(scePower,"UNIMPLEMENTED scePowerUnlock instruction");
		return 0;
	}
	int scePowerGetBusClockFrequencyInt()
	{
		debugf(scePower,"scePowerGetBusClockFrequencyInt bus_freq = %i", busClock);
		return busClock;
	}
	int scePowerGetCallbackMode()
	{
		//TODO implement me
		errorf(scePower,"UNIMPLEMENTED scePowerGetCallbackMode instruction");
		return 0;
	}
	int scePowerGetLowBatteryCapacity()
	{
		int low = ((lowPercent * fullCapacity) / 100);
        debugf(scePower,"scePowerGetLowBatteryCapacity: %i %s", low, "mAh");
		return low;
	}
	int scePowerSetBusClockFrequency(u32 a0)
	{
		busClock = a0;
		debugf(scePower,"scePowerSetBusClockFrequency: %i", busClock);
		return 0;
	}
	int scePowerGetBatteryChargingStatus()
	{
		int status = 0;
		if (pluggedIn) 
		{
			status |= PSP_POWER_CB_BATTERY_EXIST;
		}
		if (present) 
		{
			status |= PSP_POWER_CB_AC_POWER;
		}
		if (!charging) 
		{
			// I don't know exactly what to return under PSP_POWER_CB_BATTPOWER
			status |= PSP_POWER_CB_BATTPOWER;
		}

		debugf(scePower,"scePowerGetBatteryChargingStatus: statu = %i", status);

		return status;
	}
	int scePowerVolatileMemUnlock()
	{
		//TODO implement me
		errorf(scePower,"UNIMPLEMENTED scePowerVolatileMemUnlock instruction");
		return 0;
	}
	int scePowerGetCpuClockFrequencyFloat()
	{
		//TODO implement me
		errorf(scePower,"UNIMPLEMENTED scePowerGetCpuClockFrequencyFloat instruction");
		return 0;
	}
	int scePowerRequestSuspend()
	{
		//TODO implement me
		errorf(scePower,"UNIMPLEMENTED scePowerRequestSuspend instruction");
		return 0;
	}
	int scePowerSetCallbackMode()
	{
		//TODO implement me
		errorf(scePower,"UNIMPLEMENTED scePowerSetCallbackMode instruction");
		return 0;
	}
	int scePower_A4E93389()
	{
		//TODO implement me
		errorf(scePower,"UNIMPLEMENTED scePower_A4E93389 instruction");
		return 0;
	}
	int scePowerGetBusClockFrequencyFloat()
	{
		//TODO implement me
		errorf(scePower,"UNIMPLEMENTED scePowerGetBusClockFrequencyFloat instruction");
		return 0;
	}
	int scePowerIdleTimerDisable()
	{
		//TODO implement me
		errorf(scePower,"UNIMPLEMENTED scePowerIdleTimerDisable instruction");
		return 0;
	}
	int scePowerGetBatteryRemainCapacity()
	{
		int RemainCapacity = (currentPowerPercent * fullCapacity) / 100; 
		debugf(scePower,"scePowerGetBatteryRemainCapacity: RemainCapacity = %i", RemainCapacity);
		return RemainCapacity;
	}
	int scePowerGetBatteryLifeTime()
	{
		//TODO implement me
		debugf(scePower,"scePowerGetBatteryLifeTime: lifTime = %i", lifeTime);
		return lifeTime;
	}
	int scePowerIsPowerOnline()
	{
		return 1;//Power is supplied from an external power supply (AC adapter)
	}
	int scePowerGetBatteryElec()
	{
		//TODO implement me
		errorf(scePower,"UNIMPLEMENTED scePowerGetBatteryElec instruction");
		return 0;
	}
	int scePowerSetCpuClockFrequency(u32 a0)
	{
		cpuClock = a0;
		debugf(scePower,"scePowerSetCpuClockFrequency: cpu_freq = %i", cpuClock);
		return 0;
	}
	int scePowerIsRequest()
	{
		//TODO implement me
		errorf(scePower,"UNIMPLEMENTED scePowerIsRequest instruction");
		return 0;
	}
	int scePowerIdleTimerEnable()
	{
		//TODO implement me
		errorf(scePower,"UNIMPLEMENTED scePowerIdleTimerEnable instruction");
		return 0;
	}
	int scePowerIsSuspendRequired()
	{
		//TODO implement me
		errorf(scePower,"UNIMPLEMENTED scePowerIsSuspendRequired instruction");
		return 0;
	}
	int scePowerSetClockFrequency(u32 a0, u32 a1, u32 a2)
	{
		int pplClock = a0;
		cpuClock = a1;
		busClock = a2;
		debugf(scePower,"scePowerSetClockFrequency: pplClock =%i, cpuClock =%i, busClock =%i", pplClock, cpuClock, busClock);
		return 0;
	}
	int scePower_545A7F3C()
	{
		//TODO implement me
		errorf(scePower,"UNIMPLEMENTED scePower_545A7F3C instruction");
		return 0;
	}
	int scePowerGetBatteryVolt()
	{
		debugf(scePower,"scePowerGetBatteryVolt: voltage = %i", voltage);
		return voltage;
	}
	int scePowerGetBusClockFrequency()
	{
		debugf(scePower,"scePowerGetBusClockFrequency: busClock = %i", busClock);
		return busClock;
	}
	int scePowerGetBacklightMaximum()
	{
		debugf(scePower,"UNIMPLEMENTED scePowerGetBacklightMaximum: backlightMaximum = %i", backlightMaximum);
		return backlightMaximum;
	}
	int scePowerWaitRequestCompletion()
	{
		//TODO implement me
		errorf(scePower,"UNIMPLEMENTED scePowerWaitRequestCompletion instruction");
		return 0;
	}
	int scePowerGetPllClockFrequencyInt()
	{
		//TODO implement me
		errorf(scePower,"UNIMPLEMENTED scePowerGetPllClockFrequencyInt instruction");
		return 0;
	}
	int scePowerRequestStandby()
	{
		//TODO implement me
		errorf(scePower,"UNIMPLEMENTED scePowerRequestStandby instruction");
		return 0;
	}
	int scePower_2B51FE2F()
	{
		//TODO implement me
		errorf(scePower,"UNIMPLEMENTED scePower_2B51FE2F instruction");
		return 0;
	}
	int scePowerGetBatteryTemp()
	{
		errorf(scePower,"scePowerGetBatteryTemp: battery_temp = %i", temperature);
		return temperature;
	}
	int scePower_2875994B()
	{
		//TODO implement me
		errorf(scePower,"UNIMPLEMENTED scePower_2875994B instruction");
		return 0;
	}
	int scePowerBatteryUpdateInfo()
	{
		//TODO implement me
		errorf(scePower,"UNIMPLEMENTED scePowerBatteryUpdateInfo instruction");
		return 0;
	}
	int scePowerVolatileMemLock()
	{
		//TODO implement me
		errorf(scePower,"UNIMPLEMENTED scePowerVolatileMemLock instruction");
		return 0;
	}
	int scePowerGetInnerTemp()
	{
		//TODO implement me
		errorf(scePower,"UNIMPLEMENTED scePowerGetInnerTemp instruction");
		return 0;
	}
	int scePowerGetBatteryLifePercent()
	{
		return currentPowerPercent; 
	}
	int scePowerIsBatteryCharging()
	{
		//TODO implement me
		errorf(scePower,"UNIMPLEMENTED scePowerIsBatteryCharging instruction");
		return 0;
	}
	int scePowerGetPowerSwMode()
	{
		//TODO implement me
		errorf(scePower,"UNIMPLEMENTED scePowerGetPowerSwMode instruction");
		return 0;
	}
	int scePowerSetPowerSwMode()
	{
		//TODO implement me
		errorf(scePower,"UNIMPLEMENTED scePowerSetPowerSwMode instruction");
		return 0;
	}
	int scePowerIsBatteryExist()
	{
        return 1; //a battery is installed
	}
	int scePowerRegisterCallback()
	{
		//TODO implement me
		errorf(scePower,"UNIMPLEMENTED scePowerRegisterCallback instruction");
		return 0;
	}
	int scePowerRequestColdReset()
	{
		//TODO implement me
		errorf(scePower,"UNIMPLEMENTED scePowerRequestColdReset instruction");
		return 0;
	}
	int scePowerGetResumeCount()
	{
		//TODO implement me
		errorf(scePower,"UNIMPLEMENTED scePowerGetResumeCount instruction");
		return 0;
	}
}
namespace syscalls
{
	void scePowerGetCpuClockFrequency(AlContext &context){ V0 = scePower::scePowerGetCpuClockFrequency();};
	void scePowerGetCpuClockFrequencyInt(AlContext &context){ V0 = scePower::scePowerGetCpuClockFrequencyInt();};
	void scePowerGetBatteryFullCapacity(AlContext &context){ V0 = scePower::scePowerGetBatteryFullCapacity();};
	void scePowerVolatileMemTryLock(AlContext &context){ V0 = scePower::scePowerVolatileMemTryLock();};
	void scePowerTick(AlContext &context){ V0 = scePower::scePowerTick();};
	void scePowerGetIdleTimer(AlContext &context){ V0 = scePower::scePowerGetIdleTimer();};
	void scePower_EBD177D6(AlContext &context){ V0 = scePower::scePower_EBD177D6();};
	void scePowerGetPllClockFrequencyFloat(AlContext &context){ V0 = scePower::scePowerGetPllClockFrequencyFloat();};
	void scePower_E8E4E204(AlContext &context){ V0 = scePower::scePower_E8E4E204();};
	void scePowerUnregisterCallback(AlContext &context){ V0 = scePower::scePowerUnregisterCallback();};
	void scePowerUnregitserCallback(AlContext &context){ V0 = scePower::scePowerUnregitserCallback();};
	void scePowerCancelRequest(AlContext &context){ V0 = scePower::scePowerCancelRequest();};
	void scePowerLock(AlContext &context){ V0 = scePower::scePowerLock();};
	void scePowerIsLowBattery(AlContext &context){ V0 = scePower::scePowerIsLowBattery();};
	void scePowerGetBatteryChargeCycle(AlContext &context){ V0 = scePower::scePowerGetBatteryChargeCycle();};
	void scePowerUnlock(AlContext &context){ V0 = scePower::scePowerUnlock();};
	void scePowerGetBusClockFrequencyInt(AlContext &context){ V0 = scePower::scePowerGetBusClockFrequencyInt();};
	void scePowerGetCallbackMode(AlContext &context){ V0 = scePower::scePowerGetCallbackMode();};
	void scePowerGetLowBatteryCapacity(AlContext &context){ V0 = scePower::scePowerGetLowBatteryCapacity();};
	void scePowerSetBusClockFrequency(AlContext &context){ V0 = scePower::scePowerSetBusClockFrequency(A0);};
	void scePowerGetBatteryChargingStatus(AlContext &context){ V0 = scePower::scePowerGetBatteryChargingStatus();};
	void scePowerVolatileMemUnlock(AlContext &context){ V0 = scePower::scePowerVolatileMemUnlock();};
	void scePowerGetCpuClockFrequencyFloat(AlContext &context){ V0 = scePower::scePowerGetCpuClockFrequencyFloat();};
	void scePowerRequestSuspend(AlContext &context){ V0 = scePower::scePowerRequestSuspend();};
	void scePowerSetCallbackMode(AlContext &context){ V0 = scePower::scePowerSetCallbackMode();};
	void scePower_A4E93389(AlContext &context){ V0 = scePower::scePower_A4E93389();};
	void scePowerGetBusClockFrequencyFloat(AlContext &context){ V0 = scePower::scePowerGetBusClockFrequencyFloat();};
	void scePowerIdleTimerDisable(AlContext &context){ V0 = scePower::scePowerIdleTimerDisable();};
	void scePowerGetBatteryRemainCapacity(AlContext &context){ V0 = scePower::scePowerGetBatteryRemainCapacity();};
	void scePowerGetBatteryLifeTime(AlContext &context){ V0 = scePower::scePowerGetBatteryLifeTime();};
	void scePowerIsPowerOnline(AlContext &context){ V0 = scePower::scePowerIsPowerOnline();};
	void scePowerGetBatteryElec(AlContext &context){ V0 = scePower::scePowerGetBatteryElec();};
	void scePowerSetCpuClockFrequency(AlContext &context){ V0 = scePower::scePowerSetCpuClockFrequency(A0);};
	void scePowerIsRequest(AlContext &context){ V0 = scePower::scePowerIsRequest();};
	void scePowerIdleTimerEnable(AlContext &context){ V0 = scePower::scePowerIdleTimerEnable();};
	void scePowerIsSuspendRequired(AlContext &context){ V0 = scePower::scePowerIsSuspendRequired();};
	void scePowerSetClockFrequency(AlContext &context){ V0 = scePower::scePowerSetClockFrequency(A0,A1,A2);};
	void scePower_545A7F3C(AlContext &context){ V0 = scePower::scePower_545A7F3C();};
	void scePowerGetBatteryVolt(AlContext &context){ V0 = scePower::scePowerGetBatteryVolt();};
	void scePowerGetBusClockFrequency(AlContext &context){ V0 = scePower::scePowerGetBusClockFrequency();};
	void scePowerGetBacklightMaximum(AlContext &context){ V0 = scePower::scePowerGetBacklightMaximum();};
	void scePowerWaitRequestCompletion(AlContext &context){ V0 = scePower::scePowerWaitRequestCompletion();};
	void scePowerGetPllClockFrequencyInt(AlContext &context){ V0 = scePower::scePowerGetPllClockFrequencyInt();};
	void scePowerRequestStandby(AlContext &context){ V0 = scePower::scePowerRequestStandby();};
	void scePower_2B51FE2F(AlContext &context){ V0 = scePower::scePower_2B51FE2F();};
	void scePowerGetBatteryTemp(AlContext &context){ V0 = scePower::scePowerGetBatteryTemp();};
	void scePower_2875994B(AlContext &context){ V0 = scePower::scePower_2875994B();};
	void scePowerBatteryUpdateInfo(AlContext &context){ V0 = scePower::scePowerBatteryUpdateInfo();};
	void scePowerVolatileMemLock(AlContext &context){ V0 = scePower::scePowerVolatileMemLock();};
	void scePowerGetInnerTemp(AlContext &context){ V0 = scePower::scePowerGetInnerTemp();};
	void scePowerGetBatteryLifePercent(AlContext &context){ V0 = scePower::scePowerGetBatteryLifePercent();};
	void scePowerIsBatteryCharging(AlContext &context){ V0 = scePower::scePowerIsBatteryCharging();};
	void scePowerGetPowerSwMode(AlContext &context){ V0 = scePower::scePowerGetPowerSwMode();};
	void scePowerSetPowerSwMode(AlContext &context){ V0 = scePower::scePowerSetPowerSwMode();};
	void scePowerIsBatteryExist(AlContext &context){ V0 = scePower::scePowerIsBatteryExist();};
	void scePowerRegisterCallback(AlContext &context){ V0 = scePower::scePowerRegisterCallback();};
	void scePowerRequestColdReset(AlContext &context){ V0 = scePower::scePowerRequestColdReset();};
	void scePowerGetResumeCount(AlContext &context){ V0 = scePower::scePowerGetResumeCount();};
}
