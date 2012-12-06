#include "stdafx.h"
#include "sceUmdUser.h"
#include "hle/types.h"
#include "log.h"

namespace sceUmdUser
{
    static bool sceUmdUser_ready = false;

    bool Reboot()
    {
        ShutDown();
        sceUmdUser_ready = true;
        return true;
    }
    bool ShutDown()
    {
        if (sceUmdUser_ready)
        {
            sceUmdUser_ready = false;
        }
        return true;
    }

	int sceUmdDeactivate()
	{
		//TODO implement me
		errorf(sceUmdUser,"UNIMPLEMENTED sceUmdDeactivate instruction");
		return 0;
	}
	int sceUmdReplacePermit()
	{
		//TODO implement me
		errorf(sceUmdUser,"UNIMPLEMENTED sceUmdReplacePermit instruction");
		return 0;
	}
	int sceUmdActivate()
	{
		u32 retVal  = 1;
		infof(sceUmdUser,"PARTIAL sceUmdActivate return %i",retVal);
		return retVal;
	}
	int sceUmdUnRegisterUMDCallBack()
	{
		//TODO implement me
		errorf(sceUmdUser,"UNIMPLEMENTED sceUmdUnRegisterUMDCallBack instruction");
		return 0;
	}
	int sceUmdRegisterUMDCallBack()
	{
		//TODO implement me
		errorf(sceUmdUser,"UNIMPLEMENTED sceUmdRegisterUMDCallBack instruction");
		return 0;
	}
	int sceUmdWaitDriveStat()
	{
		//TODO implement me
		errorf(sceUmdUser,"UNIMPLEMENTED sceUmdWaitDriveStat instruction");
		return 0;
	}
	int sceUmdReplaceProhibit()
	{
		//TODO implement me
		errorf(sceUmdUser,"UNIMPLEMENTED sceUmdReplaceProhibit instruction");
		return 0;
	}
	int sceUmdGetDriveStat()
	{
		u32 retVal = 0x32;
		infof(sceUmdUser,"PARTIAL sceUmdGetDriveStat return 0x%x",retVal);
		return retVal;
	}
	int sceUmdCancelWaitDriveStat()
	{
		//TODO implement me
		errorf(sceUmdUser,"UNIMPLEMENTED sceUmdCancelWaitDriveStat instruction");
		return 0;
	}
	int sceUmdWaitDriveStatWithTimer()
	{
		//TODO implement me
		errorf(sceUmdUser,"UNIMPLEMENTED sceUmdWaitDriveStatWithTimer instruction");
		return 0;
	}
	int sceUmdWaitDriveStatCB()
	{
		//TODO implement me
		errorf(sceUmdUser,"UNIMPLEMENTED sceUmdWaitDriveStatCB instruction");
		return 0;
	}
	int sceUmdCheckMedium()
	{
		infof(sceUmdUser,"PARTIAL sceUmdCheckMedium returns 1");
		return 1; //non-zero: disc in drive
	}
	int sceUmdGetDiscInfo()
	{
		//TODO implement me
		errorf(sceUmdUser,"UNIMPLEMENTED sceUmdGetDiscInfo instruction");
		return 0;
	}
	int sceUmdGetErrorStat()
	{
		//TODO implement me
		errorf(sceUmdUser,"UNIMPLEMENTED sceUmdGetErrorStat instruction");
		return 0;
	}
}
namespace syscalls
{
	void sceUmdDeactivate(AlContext &context){ V0 = sceUmdUser::sceUmdDeactivate();};
	void sceUmdReplacePermit(AlContext &context){ V0 = sceUmdUser::sceUmdReplacePermit();};
	void sceUmdActivate(AlContext &context){ V0 = sceUmdUser::sceUmdActivate();};
	void sceUmdUnRegisterUMDCallBack(AlContext &context){ V0 = sceUmdUser::sceUmdUnRegisterUMDCallBack();};
	void sceUmdRegisterUMDCallBack(AlContext &context){ V0 = sceUmdUser::sceUmdRegisterUMDCallBack();};
	void sceUmdWaitDriveStat(AlContext &context){ V0 = sceUmdUser::sceUmdWaitDriveStat();};
	void sceUmdReplaceProhibit(AlContext &context){ V0 = sceUmdUser::sceUmdReplaceProhibit();};
	void sceUmdGetDriveStat(AlContext &context){ V0 = sceUmdUser::sceUmdGetDriveStat();};
	void sceUmdCancelWaitDriveStat(AlContext &context){ V0 = sceUmdUser::sceUmdCancelWaitDriveStat();};
	void sceUmdWaitDriveStatWithTimer(AlContext &context){ V0 = sceUmdUser::sceUmdWaitDriveStatWithTimer();};
	void sceUmdWaitDriveStatCB(AlContext &context){ V0 = sceUmdUser::sceUmdWaitDriveStatCB();};
	void sceUmdCheckMedium(AlContext &context){ V0 = sceUmdUser::sceUmdCheckMedium();};
	void sceUmdGetDiscInfo(AlContext &context){ V0 = sceUmdUser::sceUmdGetDiscInfo();};
	void sceUmdGetErrorStat(AlContext &context){ V0 = sceUmdUser::sceUmdGetErrorStat();};
}
