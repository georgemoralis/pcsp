#include "stdafx.h"
#include "StdioForUser.h"
#include "hle/types.h"
#include "log.h"

namespace StdioForUser
{
    static bool StdioForUser_ready = false;

    bool Reboot()
    {
        ShutDown();
        StdioForUser_ready = true;
        return true;
    }
    bool ShutDown()
    {
        if (StdioForUser_ready)
        {
            StdioForUser_ready = false;
        }
        return true;
    }

	int sceKernelStderr()
	{
		return 2;
	}
	int sceKernelStdout()
	{
		return 1;
	}
	int sceKernelStdioSendChar()
	{
		//TODO implement me
		errorf(StdioForUser,"UNIMPLEMENTED sceKernelStdioSendChar instruction");
		return 0;
	}
	int sceKernelStdioWrite()
	{
		//TODO implement me
		errorf(StdioForUser,"UNIMPLEMENTED sceKernelStdioWrite instruction");
		return 0;
	}
	int sceKernelStdioClose()
	{
		//TODO implement me
		errorf(StdioForUser,"UNIMPLEMENTED sceKernelStdioClose instruction");
		return 0;
	}
	int sceKernelStdioOpen()
	{
		//TODO implement me
		errorf(StdioForUser,"UNIMPLEMENTED sceKernelStdioOpen instruction");
		return 0;
	}
	int sceKernelRegisterStderrPipe()
	{
		//TODO implement me
		errorf(StdioForUser,"UNIMPLEMENTED sceKernelRegisterStderrPipe instruction");
		return 0;
	}
	int sceKernelRegisterStdoutPipe()
	{
		//TODO implement me
		errorf(StdioForUser,"UNIMPLEMENTED sceKernelRegisterStdoutPipe instruction");
		return 0;
	}
	int sceKernelStdioRead()
	{
		//TODO implement me
		errorf(StdioForUser,"UNIMPLEMENTED sceKernelStdioRead instruction");
		return 0;
	}
	int sceKernelStdin()
	{
		return 3;
	}
	int sceKernelStdioLseek()
	{
		//TODO implement me
		errorf(StdioForUser,"UNIMPLEMENTED sceKernelStdioLseek instruction");
		return 0;
	}
}
namespace syscalls
{
	void sceKernelStderr(AlContext &context){ V0 = StdioForUser::sceKernelStderr();};
	void sceKernelStdout(AlContext &context){ V0 = StdioForUser::sceKernelStdout();};
	void sceKernelStdioSendChar(AlContext &context){ V0 = StdioForUser::sceKernelStdioSendChar();};
	void sceKernelStdioWrite(AlContext &context){ V0 = StdioForUser::sceKernelStdioWrite();};
	void sceKernelStdioClose(AlContext &context){ V0 = StdioForUser::sceKernelStdioClose();};
	void sceKernelStdioOpen(AlContext &context){ V0 = StdioForUser::sceKernelStdioOpen();};
	void sceKernelRegisterStderrPipe(AlContext &context){ V0 = StdioForUser::sceKernelRegisterStderrPipe();};
	void sceKernelRegisterStdoutPipe(AlContext &context){ V0 = StdioForUser::sceKernelRegisterStdoutPipe();};
	void sceKernelStdioRead(AlContext &context){ V0 = StdioForUser::sceKernelStdioRead();};
	void sceKernelStdin(AlContext &context){ V0 = StdioForUser::sceKernelStdin();};
	void sceKernelStdioLseek(AlContext &context){ V0 = StdioForUser::sceKernelStdioLseek();};
}
