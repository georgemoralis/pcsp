////////////////////////////////////////////////////////////////
///This file is auto - generated pcsp NIDgenerator version 0.1
////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "ModuleMgrForUser.h"
#include "hle/types.h"
#include "hle/kernel.h"
#include "log.h"

namespace ModuleMgrForUser
{
    static bool ready = false;

    bool Reboot()
    {
        if (!ready)
        {
            if (!theKernelModuleManager.SyscallsModuleExists("ThreadManForUser"))
            {
                return false;
            }
            ready = true;
        }
        return ready;
    }
    bool ShutDown()
    {
        if (ready)
        {
            ready = false;
        }
        return true;
    }

    int ModuleMgrForUser_FEF27DC1()
	{
		//TODO implement me
		errorf(ModuleMgrForUser,"UNIMPLEMENTED ModuleMgrForUser_FEF27DC1 instruction");
		return 0;
	}
	int ModuleMgrForUser_FBE27467()
	{
		//TODO implement me
		errorf(ModuleMgrForUser,"UNIMPLEMENTED ModuleMgrForUser_FBE27467 instruction");
		return 0;
	}
	int sceKernelLoadModuleBufferUsbWlan()
	{
		//TODO implement me
		errorf(ModuleMgrForUser,"UNIMPLEMENTED sceKernelLoadModuleBufferUsbWlan instruction");
		return 0;
	}
	int ModuleMgrForUser_F2D8D1B4()
	{
		//TODO implement me
		errorf(ModuleMgrForUser,"UNIMPLEMENTED ModuleMgrForUser_F2D8D1B4 instruction");
		return 0;
	}
	int sceKernelGetModuleId()
	{
		//TODO implement me
		errorf(ModuleMgrForUser,"UNIMPLEMENTED sceKernelGetModuleId instruction");
		return 0;
	}
	int ModuleMgrForUser_E4C4211C()
	{
		//TODO implement me
		errorf(ModuleMgrForUser,"UNIMPLEMENTED ModuleMgrForUser_E4C4211C instruction");
		return 0;
	}
	int sceKernelGetModuleIdByAddress()
	{
		//TODO implement me
		errorf(ModuleMgrForUser,"UNIMPLEMENTED sceKernelGetModuleIdByAddress instruction");
		return 0;
	}
	int sceKernelSelfStopUnloadModule()
	{
		//TODO implement me
		errorf(ModuleMgrForUser,"UNIMPLEMENTED sceKernelSelfStopUnloadModule instruction");
		return 0;
	}
	int sceKernelGetModuleGPByAddress()
	{
		//TODO implement me
		errorf(ModuleMgrForUser,"UNIMPLEMENTED sceKernelGetModuleGPByAddress instruction");
		return 0;
	}
	int sceKernelStopModule()
	{
		//TODO implement me
		errorf(ModuleMgrForUser,"UNIMPLEMENTED sceKernelStopModule instruction");
		return 0;
	}
	int sceKernelStopUnloadSelfModule()
	{
		//TODO implement me
		errorf(ModuleMgrForUser,"UNIMPLEMENTED sceKernelStopUnloadSelfModule instruction");
		return 0;
	}
	int sceKernelLoadModuleByID()
	{
		//TODO implement me
		errorf(ModuleMgrForUser,"UNIMPLEMENTED sceKernelLoadModuleByID instruction");
		return 0;
	}
	int sceKernelLoadModule()
	{
		//TODO implement me
		errorf(ModuleMgrForUser,"UNIMPLEMENTED sceKernelLoadModule instruction");
		return 0;
	}
	int ModuleMgrForUser_8F2DF740()
	{
		//TODO implement me
		errorf(ModuleMgrForUser,"UNIMPLEMENTED ModuleMgrForUser_8F2DF740 instruction");
		return 0;
	}
	int sceKernelQueryModuleInfo()
	{
		//TODO implement me
		errorf(ModuleMgrForUser,"UNIMPLEMENTED sceKernelQueryModuleInfo instruction");
		return 0;
	}
	int sceKernelLoadModuleMs()
	{
		//TODO implement me
		errorf(ModuleMgrForUser,"UNIMPLEMENTED sceKernelLoadModuleMs instruction");
		return 0;
	}
	int sceKernelGetModuleIdList()
	{
		//TODO implement me
		errorf(ModuleMgrForUser,"UNIMPLEMENTED sceKernelGetModuleIdList instruction");
		return 0;
	}
	int sceKernelStartModule()
	{
		//TODO implement me
		errorf(ModuleMgrForUser,"UNIMPLEMENTED sceKernelStartModule instruction");
		return 0;
	}
	int sceKernelUnloadModule()
	{
		//TODO implement me
		errorf(ModuleMgrForUser,"UNIMPLEMENTED sceKernelUnloadModule instruction");
		return 0;
	}
	int ModuleMgrForUser_24EC0641()
	{
		//TODO implement me
		errorf(ModuleMgrForUser,"UNIMPLEMENTED ModuleMgrForUser_24EC0641 instruction");
		return 0;
	}
	int ModuleMgrForUser_1196472E()
	{
		//TODO implement me
		errorf(ModuleMgrForUser,"UNIMPLEMENTED ModuleMgrForUser_1196472E instruction");
		return 0;
	}
}
namespace syscalls
{
	void ModuleMgrForUser_FEF27DC1(AlContext &context){ V0 = ModuleMgrForUser::ModuleMgrForUser_FEF27DC1();};
	void ModuleMgrForUser_FBE27467(AlContext &context){ V0 = ModuleMgrForUser::ModuleMgrForUser_FBE27467();};
	void sceKernelLoadModuleBufferUsbWlan(AlContext &context){ V0 = ModuleMgrForUser::sceKernelLoadModuleBufferUsbWlan();};
	void ModuleMgrForUser_F2D8D1B4(AlContext &context){ V0 = ModuleMgrForUser::ModuleMgrForUser_F2D8D1B4();};
	void sceKernelGetModuleId(AlContext &context){ V0 = ModuleMgrForUser::sceKernelGetModuleId();};
	void ModuleMgrForUser_E4C4211C(AlContext &context){ V0 = ModuleMgrForUser::ModuleMgrForUser_E4C4211C();};
	void sceKernelGetModuleIdByAddress(AlContext &context){ V0 = ModuleMgrForUser::sceKernelGetModuleIdByAddress();};
	void sceKernelSelfStopUnloadModule(AlContext &context){ V0 = ModuleMgrForUser::sceKernelSelfStopUnloadModule();};
	void sceKernelGetModuleGPByAddress(AlContext &context){ V0 = ModuleMgrForUser::sceKernelGetModuleGPByAddress();};
	void sceKernelStopModule(AlContext &context){ V0 = ModuleMgrForUser::sceKernelStopModule();};
	void sceKernelStopUnloadSelfModule(AlContext &context){ V0 = ModuleMgrForUser::sceKernelStopUnloadSelfModule();};
	void sceKernelLoadModuleByID(AlContext &context){ V0 = ModuleMgrForUser::sceKernelLoadModuleByID();};
	void sceKernelLoadModule(AlContext &context){ V0 = ModuleMgrForUser::sceKernelLoadModule();};
	void ModuleMgrForUser_8F2DF740(AlContext &context){ V0 = ModuleMgrForUser::ModuleMgrForUser_8F2DF740();};
	void sceKernelQueryModuleInfo(AlContext &context){ V0 = ModuleMgrForUser::sceKernelQueryModuleInfo();};
	void sceKernelLoadModuleMs(AlContext &context){ V0 = ModuleMgrForUser::sceKernelLoadModuleMs();};
	void sceKernelGetModuleIdList(AlContext &context){ V0 = ModuleMgrForUser::sceKernelGetModuleIdList();};
	void sceKernelStartModule(AlContext &context){ V0 = ModuleMgrForUser::sceKernelStartModule();};
	void sceKernelUnloadModule(AlContext &context){ V0 = ModuleMgrForUser::sceKernelUnloadModule();};
	void ModuleMgrForUser_24EC0641(AlContext &context){ V0 = ModuleMgrForUser::ModuleMgrForUser_24EC0641();};
	void ModuleMgrForUser_1196472E(AlContext &context){ V0 = ModuleMgrForUser::ModuleMgrForUser_1196472E();};
}
