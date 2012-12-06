#include "stdafx.h"
#include "sceDmac.h"
#include "hle/types.h"
#include "log.h"

namespace sceDmac
{
    static bool sceDmac_ready = false;

    bool Reboot()
    {
        ShutDown();
        sceDmac_ready = true;
        return true;
    }
    
	bool ShutDown()
    {
        if (sceDmac_ready)
        {
            sceDmac_ready = false;
        }
        return true;
    }

    int sceDmacTryMemcpy(u32 a0, u32 a1, u32 a2)
	{
		void *dest   = Memory::addr< void* >(a0);
		void *source = Memory::addr< void* >(a1);
		int size		= a2;
		memcpy(dest, source, size);
		errorf(sceDmac,"This game uses sceDmacTryMemcpy, please notify devs so they can check if the code is correct!!! ");
		return 0;
	}

	int sceDmacMemcpy(u32 a0, u32 a1, u32 a2)
	{
		void *dest   = Memory::addr< void* >(a0);
		void *source = Memory::addr< void* >(a1);
		int size		= a2;
		memcpy(dest, source, size);
		return 0;
	}
}
namespace syscalls
{
	void sceDmacTryMemcpy(AlContext &context){ V0 = sceDmac::sceDmacTryMemcpy(A0, A1, A2);};
	void sceDmacMemcpy(AlContext &context){ V0 = sceDmac::sceDmacMemcpy(A0, A1, A2);};
}
