#include "stdafx.h"
#include "InterruptManager.h"
#include "hle/types.h"
#include "log.h"

namespace InterruptManager
{
    static bool InterruptManager_ready = false;

    bool Reboot()
    {
        ShutDown();
        InterruptManager_ready = true;
        return true;
    }
    bool ShutDown()
    {
        if (InterruptManager_ready)
        {
            InterruptManager_ready = false;
        }
        return true;
    }

	int sceKernelIsSubInterruptOccurred()
	{
		//TODO implement me
		errorf(InterruptManager,"UNIMPLEMENTED sceKernelIsSubInterruptOccurred instruction");
		return 0;
	}
	int sceKernelEnableSubIntr()
	{
		//TODO implement me
		errorf(InterruptManager,"UNIMPLEMENTED sceKernelEnableSubIntr instruction");
		return 0;
	}
	int sceKernelRegisterUserSpaceIntrStack()
	{
		//TODO implement me
		errorf(InterruptManager,"UNIMPLEMENTED sceKernelRegisterUserSpaceIntrStack instruction");
		return 0;
	}
	int sceKernelReleaseSubIntrHandler()
	{
		//TODO implement me
		errorf(InterruptManager,"UNIMPLEMENTED sceKernelReleaseSubIntrHandler instruction");
		return 0;
	}
	int QueryIntrHandlerInfo()
	{
		//TODO implement me
		errorf(InterruptManager,"UNIMPLEMENTED QueryIntrHandlerInfo instruction");
		return 0;
	}
	int sceKernelRegisterSubIntrHandler()
	{
		//TODO implement me
		errorf(InterruptManager,"UNIMPLEMENTED sceKernelRegisterSubIntrHandler instruction");
		return 0;
	}
	int sceKernelDisableSubIntr()
	{
		//TODO implement me
		errorf(InterruptManager,"UNIMPLEMENTED sceKernelDisableSubIntr instruction");
		return 0;
	}
	int sceKernelResumeSubIntr()
	{
		//TODO implement me
		errorf(InterruptManager,"UNIMPLEMENTED sceKernelResumeSubIntr instruction");
		return 0;
	}
	int sceKernelSuspendSubIntr()
	{
		//TODO implement me
		errorf(InterruptManager,"UNIMPLEMENTED sceKernelSuspendSubIntr instruction");
		return 0;
	}
}

namespace syscalls
{
	void sceKernelIsSubInterruptOccurred(AlContext &context)     { V0 = InterruptManager::sceKernelIsSubInterruptOccurred(); }
	void sceKernelEnableSubIntr(AlContext &context)              { V0 = InterruptManager::sceKernelEnableSubIntr(); }
	void sceKernelRegisterUserSpaceIntrStack(AlContext &context) { V0 = InterruptManager::sceKernelRegisterUserSpaceIntrStack(); }
	void sceKernelReleaseSubIntrHandler(AlContext &context)      { V0 = InterruptManager::sceKernelReleaseSubIntrHandler(); }
	void QueryIntrHandlerInfo(AlContext &context)                { V0 = InterruptManager::QueryIntrHandlerInfo(); }
	void sceKernelRegisterSubIntrHandler(AlContext &context)     { V0 = InterruptManager::sceKernelRegisterSubIntrHandler(); }
	void sceKernelDisableSubIntr(AlContext &context)             { V0 = InterruptManager::sceKernelDisableSubIntr(); }
	void sceKernelResumeSubIntr(AlContext &context)              { V0 = InterruptManager::sceKernelResumeSubIntr(); }
	void sceKernelSuspendSubIntr(AlContext &context)             { V0 = InterruptManager::sceKernelSuspendSubIntr(); }
}
