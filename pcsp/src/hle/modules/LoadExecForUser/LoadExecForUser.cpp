////////////////////////////////////////////////////////////////
///This file is auto - generated pcsp NIDgenerator version 0.1
////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "LoadExecForUser.h"
#include "wtf/core/psp/hle/sceKernelModule.h"
#include "log.h"
#include "system.h"
#include "Loaders/loaders.h"
#include <string.h>

namespace LoadExecForUser
{
    static bool ready = false;

    bool Reboot()
    {
        if (!ready)
        {
            if (!theKernelModuleManager.SyscallsModuleExists("ModuleMgrForUser"))
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

    int LoadExecForUser_D1FB50DC()
	{
		//TODO implement me
		errorf(LoadExecForUser,"UNIMPLEMENTED LoadExecForUser_D1FB50DC");
		return 0;
	}

	int sceKernelLoadExec(u32 a0, u32 a1)
	{
		const char *filename = Memory::addr< const char >(a0);

		infof(LoadExecForUser, "sceKernelLoadExec: %s", filename);

		std::string module(filename);

		theEmulator.SetNewGame(filename);
		theEmulator.SetLoadExecEvent();
		
		return 0;
	}

	int LoadExecForUser_8ADA38D3()
	{
		//TODO implement me
		errorf(LoadExecForUser,"UNIMPLEMENTED LoadExecForUser_8ADA38D3");
		return 0;
	}
	int sceKernelRegisterExitCallback()
	{
		//TODO implement me
		errorf(LoadExecForUser,"UNIMPLEMENTED sceKernelRegisterExitCallback");
		return 0;
	}
	int LoadExecForUser_362A956B()
	{
		//TODO implement me
		errorf(LoadExecForUser,"UNIMPLEMENTED LoadExecForUser_362A956B");
		return 0;
	}

	int sceKernelExitGameWithStatus()
	{
		//TODO implement me
		errorf(LoadExecForUser,"UNIMPLEMENTED sceKernelExitGameWithStatus");
		return 0;
	}

	int sceKernelExitGame()
	{
		//TODO implement me
		errorf(LoadExecForUser,"UNIMPLEMENTED sceKernelExitGame");
		return 0;
	}
}

namespace syscalls
{
	void LoadExecForUser_D1FB50DC(AlContext &context)         { V0 = LoadExecForUser::LoadExecForUser_D1FB50DC();      }
	void sceKernelLoadExec(AlContext &context)                { V0 = LoadExecForUser::sceKernelLoadExec(A0, A1);       }
	void LoadExecForUser_8ADA38D3(AlContext &context)         { V0 = LoadExecForUser::LoadExecForUser_8ADA38D3();      }
	void sceKernelRegisterExitCallback(AlContext &context)    { V0 = LoadExecForUser::sceKernelRegisterExitCallback(); }
	void LoadExecForUser_362A956B(AlContext &context)         { V0 = LoadExecForUser::LoadExecForUser_362A956B();      }
	void sceKernelExitGameWithStatus(AlContext &context)      { V0 = LoadExecForUser::sceKernelExitGameWithStatus();   }
	void sceKernelExitGame(AlContext &context)                { V0 = LoadExecForUser::sceKernelExitGame();             }
}