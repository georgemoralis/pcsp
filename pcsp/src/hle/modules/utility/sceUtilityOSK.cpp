#include "stdafx.h"
#include "sceUtilityOSK.h"
#include "hle/types.h"
#include "log.h"

/*
*  BASIC OSK stuff , it probably needs more work to consider finished
*/
namespace sceUtilityOSK
{
    static int utf16cpy(u16 *target, u16 const *source, int max)
    {
        int size = 0;
        if (!max)
        {
            max = SCE_UTILITY_OSK_MAX_LENGTH;
        }
        for (; *source && size < max; ++source)
        {
            *target++ = *source;
            size++;
        }
        if (size < max)
        {
            *target = 0;
        }
        return size;
    }

    static int utf16len(u16 const *source)
    {
        int size = 0;
        for (; *source && size < SCE_UTILITY_OSK_MAX_LENGTH; ++source)
        {
            size++;
        }
        return size;
    }

    static UtilityState oskState;

    static SceUtilityOskParam *param;

    int sceUtilityOskInitStart(u32 a0)
    {
        param = Memory::addr< SceUtilityOskParam >(a0);
        oskState.status = SCE_UTILITY_STATUS_INITIALIZE;
        return 0;
    }

    int sceUtilityOskShutdownStart()
    {
        param = 0;
        oskState.status = SCE_UTILITY_STATUS_SHUTDOWN;
        return 0;
    }

    int sceUtilityOskUpdate()
    {
        switch (oskState.status)
        {
        case SCE_UTILITY_STATUS_INITIALIZE:
            oskState.status =  SCE_UTILITY_STATUS_RUNNING;
            break;

        case SCE_UTILITY_STATUS_RUNNING:
            theEmulator.Sc().Osk(param); 
            param->base.result = 0;
            oskState.status = SCE_UTILITY_STATUS_FINISHED;
            break;
        }
        return 0;
    }

    int sceUtilityOskGetStatus()
    {
		int currentStatus = oskState.status;
        switch (oskState.status)
        {
        case SCE_UTILITY_STATUS_SHUTDOWN: // after returning FINISHED once, return NONE on following calls
            oskState.status = SCE_UTILITY_STATUS_NONE;
            break;
        case SCE_UTILITY_STATUS_INITIALIZE: 
            oskState.status = SCE_UTILITY_STATUS_RUNNING;
            break;
        }
        return currentStatus;
    }
}