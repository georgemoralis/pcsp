#include "stdafx.h"
#include "Kernel_Library.h"
#include "hle/types.h"
#include "log.h"

namespace Kernel_Library
{
    static bool Kernel_Library_ready = false;

    bool Reboot()
    {
        ShutDown();
        Kernel_Library_ready = true;
        return true;
    }
    bool ShutDown()
    {
        if (Kernel_Library_ready)
        {
            Kernel_Library_ready = false;
        }
        return true;
    }

    int sceKernelTryLockLwMutex()
	{
		//TODO implement me
		errorf(Kernel_Library,"UNIMPLEMENTED sceKernelTryLockLwMutex instruction");
		return 0;
	}
	int sceKernelReferLwMutexStatus()
	{
		//TODO implement me
		errorf(Kernel_Library,"UNIMPLEMENTED sceKernelReferLwMutexStatus instruction");
		return 0;
	}
	int sceKernelLockLwMutex()
	{
		//TODO implement me
		errorf(Kernel_Library,"UNIMPLEMENTED sceKernelLockLwMutex instruction");
		return 0;
	}
	int sceKernelIsCpuIntrEnable()
	{
		int ret_val = 0;
		if (interruptsEnabled == true) 
        	ret_val = 1;
		else
			ret_val = 0;
		return ret_val;
	}
	int sceKernelCpuResumeIntr(u32 a0)
	{
		u32 flags = a0;
		if (flags == FLAG_INTERRUPTS_ENABLED) 
			interruptsEnabled = true;
		else if (flags == FLAG_INTERRUPTS_DISABLED)
 			interruptsEnabled = false;
		else 
			warnf(Kernel_Library,"sceKernelCpuResumeIntr: unknown flag value %i", flags);
		return 0;
	}
	int sceKernelIsCpuIntrSuspended(u32 a0)
	{
		u32 flags = a0;
		int ret_val = 0; 
		if (flags == FLAG_INTERRUPTS_DISABLED) 
    		ret_val = 1;
    	else
    		ret_val = 0;
		return ret_val;
	}
	int sceKernelCpuResumeIntrWithSync(u32 a0)
	{
		sceKernelCpuResumeIntr(a0);
		return 0;
	}
	int sceKernelLockLwMutexCB()
	{
		//TODO implement me
		errorf(Kernel_Library,"UNIMPLEMENTED sceKernelLockLwMutexCB instruction");
		return 0;
	}
	int sceKernelUnlockLwMutex()
	{
		//TODO implement me
		errorf(Kernel_Library,"UNIMPLEMENTED sceKernelUnlockLwMutex instruction");
		return 0;
	}
	int sceKernelCpuSuspendIntr()
	{
		int ret_val = 0;
		if (interruptsEnabled == true) 
		{
        	ret_val = FLAG_INTERRUPTS_ENABLED;
			interruptsEnabled = false;
        } 
		else 
        	ret_val = FLAG_INTERRUPTS_DISABLED;
		debugf(Kernel_Library,"sceKernelCpuSuspendIntr return:%02x",ret_val);
		return ret_val;
	}
}
namespace syscalls
{
	void sceKernelTryLockLwMutex(AlContext &context)          { V0 = Kernel_Library::sceKernelTryLockLwMutex();           }
	void sceKernelReferLwMutexStatus(AlContext &context)      { V0 = Kernel_Library::sceKernelReferLwMutexStatus();       }
	void sceKernelLockLwMutex(AlContext &context)             { V0 = Kernel_Library::sceKernelLockLwMutex();              }
	void sceKernelIsCpuIntrEnable(AlContext &context)         { V0 = Kernel_Library::sceKernelIsCpuIntrEnable();          }
	void sceKernelCpuResumeIntr(AlContext &context)           { V0 = Kernel_Library::sceKernelCpuResumeIntr(A0);            }
	void sceKernelIsCpuIntrSuspended(AlContext &context)      { V0 = Kernel_Library::sceKernelIsCpuIntrSuspended(A0);       }
	void sceKernelCpuResumeIntrWithSync(AlContext &context)   { V0 = Kernel_Library::sceKernelCpuResumeIntrWithSync(A0);    }
	void sceKernelLockLwMutexCB(AlContext &context)           { V0 = Kernel_Library::sceKernelLockLwMutexCB();            }
	void sceKernelUnlockLwMutex(AlContext &context)           { V0 = Kernel_Library::sceKernelUnlockLwMutex();            }
	void sceKernelCpuSuspendIntr(AlContext &context)          { V0 = Kernel_Library::sceKernelCpuSuspendIntr();           }
}
