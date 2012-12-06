#include "stdafx.h"
#include "sceSuspendForUser.h"
#include "hle/types.h"
#include "log.h"

namespace sceSuspendForUser
{
    static bool sceSuspendForUser_ready = false;

    bool Reboot()
    {
        ShutDown();
        sceSuspendForUser_ready = true;
        return true;
    }
    bool ShutDown()
    {
        if (sceSuspendForUser_ready)
        {
            sceSuspendForUser_ready = false;
        }
        return true;
    }

	int hleKernelVolatileMemLock(u32 unk1, u32 paddr, u32 psize, bool trylock) {

		if(!trylock)
			debugf(sceSuspendForUser, "PARTIAL:sceKernelVolatileMemLock: unk1=%d, paddr=0x%08X, psize=0x%08X, trylock=", unk1, paddr, psize);
		else
			debugf(sceSuspendForUser, "PARTIAL:sceKernelVolatileMemTryLock: unk1=%d, paddr=0x%08X, psize=0x%08X, trylock=", unk1, paddr, psize);

        if (unk1 != 0) 
		{
            errorf(sceSuspendForUser, "hleKernelVolatileMemLock bad param: unk1 != 0");
            return 0x80000107;//ERROR_ARGUMENT;
        } 
		else 
		{
            if (volatileMemLocked == false) 
			{
				volatileMemLocked = true;

				Memory::memw(paddr) = 0x08400000; // Volatile mem is always at 0x08400000
				Memory::memw(psize) = 0x00400000; // Volatile mem size is 4Megs

                return 0;
            } 
			else 
			{
               errorf(sceSuspendForUser, "hleKernelVolatileMemLock already locked");

                if (trylock) 
				{
                    return 0x802b0200; // unknown meaning
                } 
				else 
				{
                    errorf(sceSuspendForUser, "UNIMPLEMENTED:hleKernelVolatileMemLock blocking current thread");
                    return -1;
                }
            }
		}
    }
 
	int sceKernelVolatileMemLock(u32 a0, u32 a1, u32 a2)
	{
		volatileMemLocked = false;
		return hleKernelVolatileMemLock(a0, a1, a2, false);
	}
	int sceKernelVolatileMemTryLock(u32 a0, u32 a1, u32 a2)
	{
		volatileMemLocked = false;
		return hleKernelVolatileMemLock(a0, a1, a2, true);
	}
	int sceKernelVolatileMemUnlock(u32 a0)
	{
		u32 unk1 = a0;
		if (unk1 != 0) 
		{
            errorf(sceSuspendForUser, "sceKernelVolatileMemUnlock bad param: unk1 != 0");
            return 0x80000107;//ERROR_ARGUMENT;
        } 
		else if (volatileMemLocked == false) 
		{
            errorf(sceSuspendForUser, "sceKernelVolatileMemUnlock - Volatile Memory was not locked!");
            return 0x800201ae;//ERROR_SEMA_OVERFLOW;
        } 
		else 
		{
            volatileMemLocked = false;
            return 0;
        }
		//errorf(sceSuspendForUser,"UNIMPLEMENTED sceKernelVolatileMemUnlock instruction");
		return 0;
	}
	int sceKernelPowerLock()
	{
		//TODO implement me
		errorf(sceSuspendForUser,"UNIMPLEMENTED sceKernelPowerLock instruction");
		return 0;
	}
	int sceKernelPowerUnlock()
	{
		//TODO implement me
		errorf(sceSuspendForUser,"UNIMPLEMENTED sceKernelPowerUnlock instruction");
		return 0;
	}
	int sceKernelPowerTick()
	{
		//TODO implement me
		errorf(sceSuspendForUser,"UNIMPLEMENTED sceKernelPowerTick instruction");
		return 0;
	}
}
namespace syscalls
{
	void sceKernelVolatileMemLock(AlContext &context){ V0 = sceSuspendForUser::sceKernelVolatileMemLock(A0, A1, A2);};
	void sceKernelVolatileMemTryLock(AlContext &context){ V0 = sceSuspendForUser::sceKernelVolatileMemTryLock(A0, A1, A2);};
	void sceKernelVolatileMemUnlock(AlContext &context){ V0 = sceSuspendForUser::sceKernelVolatileMemUnlock(A0);};
	void sceKernelPowerLock(AlContext &context){ V0 = sceSuspendForUser::sceKernelPowerLock();};
	void sceKernelPowerUnlock(AlContext &context){ V0 = sceSuspendForUser::sceKernelPowerUnlock();};
	void sceKernelPowerTick(AlContext &context){ V0 = sceSuspendForUser::sceKernelPowerTick();};
}
