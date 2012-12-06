#include "stdafx.h"
#include "sceUtility.h"
#include "sceUtilityMsgDialog.h"
#include "hle/types.h"
#include "log.h"

namespace sceUtilityMsgDialog
{
    static UtilityState msgState;

    static SceUtilityMsgDialogParam *param;

    int sceUtilityMsgDialogInitStart(u32 a0)
    {
        param = Memory::addr< SceUtilityMsgDialogParam >(a0);
        msgState.status = SCE_UTILITY_STATUS_INITIALIZE;
        return 0;
    }

    int sceUtilityMsgDialogGetStatus()
    {
        int currentStatus = msgState.status;
        switch (msgState.status)
        {
        case SCE_UTILITY_STATUS_SHUTDOWN: // after returning FINISHED once, return NONE on following calls
            msgState.status = SCE_UTILITY_STATUS_NONE;
            break;
        case SCE_UTILITY_STATUS_INITIALIZE: 
            msgState.status = SCE_UTILITY_STATUS_RUNNING;
            break;
        }
        return currentStatus;
    }

    int sceUtilityMsgDialogUpdate()
    {
        switch (msgState.status)
        {
        case SCE_UTILITY_STATUS_INITIALIZE:
            msgState.status =  SCE_UTILITY_STATUS_RUNNING;
            break;

        case SCE_UTILITY_STATUS_RUNNING:
            theEmulator.Sc().MsgDialog(param); 
            param->base.result = 0;
            msgState.status = SCE_UTILITY_STATUS_FINISHED;
            break;
        }
        return 0;
    }

    int sceUtilityMsgDialogShutdownStart()
    {
        param = 0;
        msgState.status = SCE_UTILITY_STATUS_SHUTDOWN;
        return 0;
    }

    int sceUtilityMsgDialogAbort()
    {
        param->result = SCE_UTILITY_RESULT_ABORTED;
        msgState.status = SCE_UTILITY_STATUS_FINISHED;
        return 0;
    }
}
