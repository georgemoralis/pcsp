#include "stdafx.h"

#include "syscalls.h"
#include "emulator.h"
#include "al/al.h"
#include "kernel/kernel_module.h"

#include "modules.h"

#include "wtf/core/psp/hle/sceKernelEventFlag.h"
#include "wtf/core/psp/hle/sceKernelCallback.h"
#include "wtf/core/psp/hle/sceKernelSemaphore.h"
#include "wtf/core/psp/hle/sceKernelThread.h"

void AlContext::Syscall(u32 opcode)
{
    u32 handlerId = (opcode >>  6) & 0x00000FFF;
    u32 moduleId  = (opcode >> 18) & 0x000000FF;

    if (moduleId >= theKernelModuleManager.m_modules_per_index.size())
    {
        errorf(hlemisc, "Unknown syscall: invalid module"); 
        return;
    }
    KernelModule *module = theKernelModuleManager.m_modules_per_index[moduleId];
    if (!module)
    {
        errorf(hlemisc, "Unknown syscall: invalid module"); 
        return;
    }
    if (module->m_syscall_count <= handlerId)
    {
        errorf(hlemisc, "Unknown syscall: Module: %s", module->m_name); 
        return;
    }

    KernelSyscall const &syscall = module->m_syscall_array[handlerId];
    SyscallHandler *handler = syscall.handler;  

    if (handler)
    {
        if (syscall.log && Log::syscalls.checkLevel(LogCategory::E_DEBUG) && syscall.log->checkLevel(LogCategory::E_DEBUG))
        {
            syscalls::sysenterf(syscall.log, syscall.name, ::strchr(syscall.format, '/') + 1);
            handler(*this);
            syscalls::sysleavef(syscall.log, syscall.format);
        }
        else
        {
            handler(*this);
        }
    }
    else
    {
        errorf(hlemisc, "Unimplemented syscall %s", syscall.name);
    }
}

#define HLE_FUNC(nid, name)            { nid, name,           #name, 0,   (LogCategory *)0          }
#define HLE_FUNC0(nid, name)           { nid, syscalls::name, #name, 0,   (LogCategory *)0          }
#define HLE_FUNC1(nid, name, fmt)      { nid, syscalls::name, #name, fmt, (LogCategory *)&Log::name }

namespace syscalls
{
    char const *sysargf_n(LogCategory *log, char const *fmt, intptr_t address, int indentation = 2);

    char const *sysargf_0(LogCategory *log, char const *fmt, intptr_t &address, int indentation = 2)
    {
        char name[1024];
        int i = 0;

        ::memset(name, 0, 1024);

        int delta;

        while (*fmt)
        {
            switch (*fmt)
            {
            case '}':
            case ',':
                return ++fmt;
            case ':':
                ++fmt;
                delta = 4;
                if (name[0])
                {
                    name[i] = '\0';
redo:
                    switch (*fmt++)
                    {
                    case '1':
                        delta = 1;
                        goto redo;
                    case '2':
                        delta = 2;
                        goto redo;
                    case '4':
                        delta = 4;
                        goto redo;
                    case '8':
                        delta = 8;
                        goto redo;
                    case '{':
                        address = (address + 3) & ~3;
                        log->debug("%*s%s : 0x%08X", indentation, "", name, *((u32 *)address));
                        log->debug("%*s{", indentation, "");
                        if (*((u32 *)address))
                        {
                            intptr_t data = (intptr_t)Memory::addr< u32 >(*((u32 *)address));
                            fmt = sysargf_n(log, fmt, data, indentation + 2);
                        }
                        else
                        {
                            while (*fmt && *fmt != '}') ++fmt;
                        }
                        log->debug("%*s}", indentation, "");
                        break;
                    case 's':
                        address = (address + 3) & ~3;
                        log->debug("%*s%s : \"%s\"", indentation, "", name, Memory::addr< char >(*((u32 *)address)));
                        address += 4;
                        break;
                    case 'f':
                        address = (address + 3) & ~3;
                        log->debug("%*s%s : %f", indentation, "", name, *((f32 *)address));
                        address += 4;
                        break;
                    case 'x':
                        address = (address + delta - 1) & -delta;
                        switch (delta)
                        {
                        case 1:
                            log->debug("%*s%s : 0x%02X", indentation, "", name, (u32)(*((u8 *)address)));
                            break;
                        case 2:
                            log->debug("%*s%s : 0x%04X", indentation, "", name, (u32)(*((u16 *)address)));
                            break;
                        case 4:
                            log->debug("%*s%s : 0x%08X", indentation, "", name, (u32)(*((u32 *)address)));
                            break;
                        case 8:
                            log->debug("%*s%s : 0x%016llX", indentation, "", name, (s64)(*((s64 *)address)));
                            break;
                        }
                        address += delta;
                        break;
                    case 'i':
                    case 'd':
                        address = (address + delta - 1) & -delta;
                        switch (delta)
                        {
                        case 1:
                            log->debug("%*s%s : %d", indentation, "", name, (s32)(*((s8 *)address)));
                            break;
                        case 2:
                            log->debug("%*s%s : %d", indentation, "", name, (s32)(*((s16 *)address)));
                            break;
                        case 4:
                            log->debug("%*s%s : %d", indentation, "", name, (s32)(*((s32 *)address)));
                            break;
                        case 8:
                            log->debug("%*s%s : %lld", indentation, "", name, (s64)(*((s64 *)address)));
                            break;
                        }
                        address += delta;
                        break;
                    case 'u':
                        address = (address + delta - 1) & -delta;
                        switch (delta)
                        {
                        case 1:
                            log->debug("%*s%s : %u", indentation, "", name, (u32)(*((u8 *)address)));
                            break;
                        case 2:
                            log->debug("%*s%s : %u", indentation, "", name, (u32)(*((u16 *)address)));
                            break;
                        case 4:
                            log->debug("%*s%s : %u", indentation, "", name, (u32)(*((u32 *)address)));
                            break;
                        case 8:
                            log->debug("%*s%s : %lld", indentation, "", name, (s64)(*((s64 *)address)));
                            break;
                        }
                        address += delta;
                        break;
                    case 'c':
                        address = (address + delta - 1) & -delta;
                        log->debug("%*s%s : '%c'", indentation, "", name, *((char *)address));
                        address += delta;
                        break;
                    }
                }
                name[0] = '\0';
                i = 0;
                return fmt;
            default:
                name[i++] = *fmt++;
            }
        }
        return fmt;
    }
    
    char const *sysargf_n(LogCategory *log, char const *fmt, intptr_t address, int indentation)
    {
        while (*fmt && *fmt != '/')
        {
            fmt = sysargf_0(log, fmt, address, indentation);
        }
        return fmt;
    }

    char const *sysargf(LogCategory *log, char const *fmt, int &r, int indentation = 2)
    {
        intptr_t address = 0;

        while (*fmt)
        {
            if (*fmt == '/')
            {
                break;
            }
            if (r == -4)
            {
                address = (intptr_t)(theEmulator.context->gpr + ALLEGREX_V0);
            }
            else if (r == -2)
            {
                address = (intptr_t)(theEmulator.context->fpr + ALLEGREX_F0);
            }
            else if (r == 0)
            {
                address = (intptr_t)(theEmulator.context->gpr + ALLEGREX_A0);
            }
            else if (r == 8)
            {
                address = (intptr_t)(theEmulator.context->fpr + ALLEGREX_F12);
            }
            else if (r > 15)
            {
                return fmt;
            }

            fmt = sysargf_0(log, fmt, address, indentation);

            ++r;
        }
        return fmt;
    }

    static const char *g_name;
    void sysenterf(LogCategory *log, char const *name, char const *fmt)
    {
        if (!log) return;
        g_name = name;
        log->debug("syscall: %s / arguments:", name);
        log->debug("[");
        int r = 0;
        sysargf(log, fmt, r);
        log->debug("]");
    }

    void sysleavef(LogCategory *log, char const *fmt)
    {
        if (!log) return;
        log->debug("syscall: %s / results:", g_name);
        log->debug("[");
        int r = -4;
        sysargf(log, fmt, r);
        log->debug("]");
    }

    KernelSyscall const sceUtility[] =
    {
        HLE_FUNC0(0xF9E0008C, sceUtility_F9E0008C),
        HLE_FUNC0(0xF88155F6, sceUtilityNetconfShutdownStart),
        HLE_FUNC0(0xF7D8D092, sceUtilityUnloadAvModule),
        HLE_FUNC0(0xF64910F0, sceUtilityUnloadUsbModule),
        HLE_FUNC0(0xF6269B82, sceUtilityOskInitStart),
        HLE_FUNC0(0xF5CE1134, sceUtilityHtmlViewerShutdownStart),
        HLE_FUNC0(0xF3FBC572, sceUtility_F3FBC572),
        HLE_FUNC0(0xF3F76017, sceUtilityOskGetStatus),
        HLE_FUNC0(0xEFC6F80F, sceUtilityGameSharingShutdownStart),
        HLE_FUNC0(0xEF3582B2, sceUtility_EF3582B2),
        HLE_FUNC0(0xED0FAD38, sceUtility_ED0FAD38),
        HLE_FUNC0(0xECE1D3E5, sceUtility_ECE1D3E5),
        HLE_FUNC0(0xE7B778D8, sceUtility_E7B778D8),
        HLE_FUNC0(0xE49BFE92, sceUtilityUnloadModule),
        HLE_FUNC0(0xE19C97D6, sceUtility_E19C97D6),
        HLE_FUNC0(0xDDE5389D, sceUtility_DDE5389D),
        HLE_FUNC0(0xDA97F1AA, sceUtility_DA97F1AA),
        HLE_FUNC0(0xD852CDCE, sceUtility_D852CDCE),
        HLE_FUNC0(0xD81957B7, sceUtility_D81957B7),
        HLE_FUNC0(0xD4B95FFB, sceUtilitySavedataUpdate),
        HLE_FUNC0(0xD17A0573, sceUtility_D17A0573),
        HLE_FUNC0(0xCDC3AA41, sceUtilityHtmlViewerInitStart),
        HLE_FUNC0(0xC629AF26, sceUtilityLoadAvModule),
        HLE_FUNC0(0xC492F751, sceUtilityGameSharingInitStart),
        HLE_FUNC0(0xC4700FA3, sceUtilityInstallGetStatus),
        HLE_FUNC0(0xBDA7D894, sceUtilityHtmlViewerGetStatus),
        HLE_FUNC0(0xBC6B6296, sceNetplayDialogShutdownStart),
        HLE_FUNC0(0xB8592D5F, sceUtility_B8592D5F),
        HLE_FUNC0(0xB6CEE597, sceNetplayDialogGetStatus),
        HLE_FUNC0(0xB62A4061, sceUtility_B62A4061),
        HLE_FUNC0(0xB0FB7FF5, sceUtility_B0FB7FF5),
        HLE_FUNC0(0xAB083EA9, sceUtility_AB083EA9),
        HLE_FUNC0(0xA5DA2406, sceUtilityGetSystemParamInt),
        HLE_FUNC0(0xA50E5B30, sceUtility_A50E5B30),
        HLE_FUNC0(0xA084E056, sceUtility_A084E056),
        HLE_FUNC0(0xA03D29BA, sceUtilityInstallUpdate),
        HLE_FUNC0(0x9A1C91D7, sceUtilityMsgDialogGetStatus),
        HLE_FUNC0(0x9790B33C, sceUtilitySavedataShutdownStart),
        HLE_FUNC0(0x95FC253B, sceUtilityMsgDialogUpdate),
        HLE_FUNC0(0x946963F3, sceUtilityGameSharingGetStatus),
        HLE_FUNC0(0x943CBA46, sceUtility_943CBA46),
        HLE_FUNC0(0x91E70E35, sceUtilityNetconfUpdate),
        HLE_FUNC0(0x89317C8F, sceUtility_89317C8F),
        HLE_FUNC0(0x88BC7406, sceUtility_88BC7406),
        HLE_FUNC0(0x8874DBE0, sceUtilitySavedataGetStatus),
        HLE_FUNC0(0x86ABDB1B, sceUtility_86ABDB1B),
        HLE_FUNC0(0x86A03A27, sceUtility_86A03A27),
        HLE_FUNC0(0x8326AB05, sceUtility_8326AB05),
        HLE_FUNC0(0x81C44706, sceUtility_81C44706),
        HLE_FUNC0(0x7853182D, sceUtilityGameSharingUpdate),
        HLE_FUNC0(0x70267ADF, sceUtility_70267ADF),
        HLE_FUNC0(0x6F56F9CF, sceUtility_6F56F9CF),
        HLE_FUNC0(0x67AF3428, sceUtilityMsgDialogShutdownStart),
        HLE_FUNC0(0x64D50C56, sceUtilityUnloadNetModule),
        HLE_FUNC0(0x6332AA39, sceUtilityNetconfGetStatus),
        HLE_FUNC0(0x5EF1C24A, sceUtilityInstallShutdownStart),
        HLE_FUNC0(0x5EEE6548, sceUtilityCheckNetParam),
        HLE_FUNC0(0x54A5C62F, sceUtility_54A5C62F),
        HLE_FUNC0(0x50C4CD57, sceUtilitySavedataInitStart),
        HLE_FUNC0(0x4FED24D8, sceUtilityGetNetParamLatestID),
        HLE_FUNC0(0x4DB1E739, sceUtilityNetconfInitStart),
        HLE_FUNC0(0x4B85C861, sceUtilityOskUpdate),
        HLE_FUNC0(0x4B0A8FE5, sceUtility_4B0A8FE5),
        HLE_FUNC0(0x4A833BA4, sceUtility_4A833BA4),
        HLE_FUNC0(0x4928BD96, sceUtilityMsgDialogAbort),
        HLE_FUNC0(0x45C18506, sceUtilitySetSystemParamInt),
        HLE_FUNC0(0x434D4B3A, sceUtilityGetNetParam),
        HLE_FUNC0(0x42071A83, sceUtility_42071A83),
        HLE_FUNC0(0x41E30674, sceUtilitySetSystemParamString),
        HLE_FUNC0(0x417BED54, sceNetplayDialogUpdate),
        HLE_FUNC0(0x3DFAEBA9, sceUtilityOskShutdownStart),
        HLE_FUNC0(0x3AD50AE7, sceNetplayDialogInitStart),
        HLE_FUNC0(0x3AAD51DC, sceUtility_3AAD51DC),
        HLE_FUNC0(0x34B78343, sceUtilityGetSystemParamString),
        HLE_FUNC0(0x2B96173B, sceUtility_2B96173B),
        HLE_FUNC0(0x2AD8E239, sceUtilityMsgDialogInitStart),
        HLE_FUNC0(0x2A2B3DE0, sceUtilityLoadModule),
        HLE_FUNC0(0x2995D020, sceUtility_2995D020),
        HLE_FUNC0(0x28D35634, sceUtility_28D35634),
        HLE_FUNC0(0x16D02AF0, sceUtility_16D02AF0),
        HLE_FUNC0(0x16A1A8D8, sceUtility_16A1A8D8),
        HLE_FUNC0(0x1579A159, sceUtilityLoadNetModule),
        HLE_FUNC0(0x149A7895, sceUtility_149A7895),
        HLE_FUNC0(0x147F7C85, sceUtility_147F7C85),
        HLE_FUNC0(0x1281DA8E, sceUtilityInstallInitStart),
        HLE_FUNC0(0x0F3EEAAC, sceUtility_0F3EEAAC),
        HLE_FUNC0(0x0D5BC6D2, sceUtilityLoadUsbModule),
        HLE_FUNC0(0x06A48659, sceUtility_06A48659),
        HLE_FUNC0(0x05AFB9E4, sceUtilityHtmlViewerUpdate),
        HLE_FUNC0(0x0251B134, sceUtility_0251B134),
    };

    KernelSyscall const scePower[] =
    {
        HLE_FUNC0(0xFEE03A2F, scePowerGetCpuClockFrequency),
        HLE_FUNC0(0xFDB5BFE9, scePowerGetCpuClockFrequencyInt),
        HLE_FUNC0(0xFD18A0FF, scePowerGetBatteryFullCapacity),
        HLE_FUNC0(0xFA97A599, scePowerVolatileMemTryLock),
        HLE_FUNC0(0xEFD3C963, scePowerTick),
        HLE_FUNC0(0xEDC13FE5, scePowerGetIdleTimer),
        HLE_FUNC0(0xEBD177D6, scePower_EBD177D6),
        HLE_FUNC0(0xEA382A27, scePowerGetPllClockFrequencyFloat),
        HLE_FUNC0(0xE8E4E204, scePower_E8E4E204),
        HLE_FUNC0(0xDFA8BAF8, scePowerUnregisterCallback),
        HLE_FUNC0(0xDB9D28DD, scePowerUnregitserCallback),
        HLE_FUNC0(0xDB62C9CF, scePowerCancelRequest),
        HLE_FUNC0(0xD6D016EF, scePowerLock),
        HLE_FUNC0(0xD3075926, scePowerIsLowBattery),
        HLE_FUNC0(0xCB49F5CE, scePowerGetBatteryChargeCycle),
        HLE_FUNC0(0xCA3D34C1, scePowerUnlock),
        HLE_FUNC0(0xBD681969, scePowerGetBusClockFrequencyInt),
        HLE_FUNC0(0xBAFA3DF0, scePowerGetCallbackMode),
        HLE_FUNC0(0xB999184C, scePowerGetLowBatteryCapacity),
        HLE_FUNC0(0xB8D7B3FB, scePowerSetBusClockFrequency),
        HLE_FUNC0(0xB4432BC8, scePowerGetBatteryChargingStatus),
        HLE_FUNC0(0xB3EDD801, scePowerVolatileMemUnlock),
        HLE_FUNC0(0xB1A52C83, scePowerGetCpuClockFrequencyFloat),
        HLE_FUNC0(0xAC32C9CC, scePowerRequestSuspend),
        HLE_FUNC0(0xA9D22232, scePowerSetCallbackMode),
        HLE_FUNC0(0xA4E93389, scePower_A4E93389),
        HLE_FUNC0(0x9BADB3EB, scePowerGetBusClockFrequencyFloat),
        HLE_FUNC0(0x972CE941, scePowerIdleTimerDisable),
        HLE_FUNC0(0x94F5A53F, scePowerGetBatteryRemainCapacity),
        HLE_FUNC0(0x8EFB3FA2, scePowerGetBatteryLifeTime),
        HLE_FUNC0(0x87440F5E, scePowerIsPowerOnline),
        HLE_FUNC0(0x862AE1A6, scePowerGetBatteryElec),
        HLE_FUNC0(0x843FBF43, scePowerSetCpuClockFrequency),
        HLE_FUNC0(0x7FA406DD, scePowerIsRequest),
        HLE_FUNC0(0x7F30B3B1, scePowerIdleTimerEnable),
        HLE_FUNC0(0x78A1A796, scePowerIsSuspendRequired),
        HLE_FUNC0(0x737486F2, scePowerSetClockFrequency),
        HLE_FUNC0(0x545A7F3C, scePower_545A7F3C),
        HLE_FUNC0(0x483CE86B, scePowerGetBatteryVolt),
        HLE_FUNC0(0x478FE6F5, scePowerGetBusClockFrequency),
        HLE_FUNC0(0x442BFBAC, scePowerGetBacklightMaximum),
        HLE_FUNC0(0x3951AF53, scePowerWaitRequestCompletion),
        HLE_FUNC0(0x34F9C463, scePowerGetPllClockFrequencyInt),
        HLE_FUNC0(0x2B7C7CF4, scePowerRequestStandby),
        HLE_FUNC0(0x2B51FE2F, scePower_2B51FE2F),
        HLE_FUNC0(0x28E12023, scePowerGetBatteryTemp),
        HLE_FUNC0(0x2875994B, scePower_2875994B),
        HLE_FUNC0(0x27F3292C, scePowerBatteryUpdateInfo),
        HLE_FUNC0(0x23C31FFE, scePowerVolatileMemLock),
        HLE_FUNC0(0x23436A4A, scePowerGetInnerTemp),
        HLE_FUNC0(0x2085D15D, scePowerGetBatteryLifePercent),
        HLE_FUNC0(0x1E490401, scePowerIsBatteryCharging),
        HLE_FUNC0(0x165CE085, scePowerGetPowerSwMode),
        HLE_FUNC0(0x0CD21B1F, scePowerSetPowerSwMode),
        HLE_FUNC0(0x0AFD0D8B, scePowerIsBatteryExist),
        HLE_FUNC0(0x04B7766E, scePowerRegisterCallback),
        HLE_FUNC0(0x0442D852, scePowerRequestColdReset),
        HLE_FUNC0(0x0074EF9B, scePowerGetResumeCount),
    };

    KernelSyscall const sceRtc[] =
    {
        HLE_FUNC0(0xFB3B18CD, sceRtcRegisterCallback),
        HLE_FUNC0(0xF5FCC995, sceRtc_F5FCC995),
        HLE_FUNC0(0xF2A4AFE5, sceRtcTickAddSeconds),
        HLE_FUNC0(0xF006F264, sceRtcSetDosTime),
        HLE_FUNC0(0xE7C27D1B, sceRtcGetCurrentClockLocalTime),
        HLE_FUNC0(0xE6605BCA, sceRtcTickAddMinutes),
        HLE_FUNC0(0xE51B4B7A, sceRtcTickAddDays),
        HLE_FUNC0(0xE1C93E47, sceRtcGetTime64_t),
        HLE_FUNC0(0xDFBC5F16, sceRtcParseDateTime),
        HLE_FUNC0(0xDBF74F1B, sceRtcTickAddMonths),
        HLE_FUNC0(0xCF561893, sceRtcGetWin32FileTime),
        HLE_FUNC0(0xCF3A2CA8, sceRtcTickAddWeeks),
        HLE_FUNC0(0xC663B3B9, sceRtcFormatRFC2822),
        HLE_FUNC0(0xC41C2853, sceRtcGetTickResolution),
        HLE_FUNC0(0xC2DDBEB5, sceRtc_C2DDBEB5),
        HLE_FUNC0(0xA93CF7D8, sceRtc_A93CF7D8),
        HLE_FUNC0(0x9ED0AE87, sceRtcCompareTick),
        HLE_FUNC0(0x81FCDA34, sceRtcIsAlarmed),
        HLE_FUNC0(0x7ED29E40, sceRtcSetTick),
        HLE_FUNC0(0x7DE6711B, sceRtcFormatRFC2822LocalTime),
        HLE_FUNC0(0x7D1FBED3, sceRtc_7D1FBED3),
        HLE_FUNC0(0x7ACE4C04, sceRtcSetWin32FileTime),
        HLE_FUNC0(0x779242A2, sceRtcConvertLocalTimeToUTC),
        HLE_FUNC0(0x6FF40ACC, sceRtcGetTick),
        HLE_FUNC0(0x6A676D2D, sceRtcUnregisterCallback),
        HLE_FUNC0(0x62685E98, sceRtcGetLastAdjustedTime),
        HLE_FUNC0(0x57726BC1, sceRtcGetDayOfWeek),
        HLE_FUNC0(0x4CFA57B0, sceRtcGetCurrentClock),
        HLE_FUNC0(0x4B1B5E82, sceRtcCheckValid),
        HLE_FUNC0(0x44F45E05, sceRtcTickAddTicks),
        HLE_FUNC0(0x42842C77, sceRtcTickAddYears),
        HLE_FUNC0(0x42307A17, sceRtcIsLeapYear),
        HLE_FUNC0(0x3F7AD767, sceRtcGetCurrentTick),
        HLE_FUNC0(0x3A807CC8, sceRtcSetTime_t),
        HLE_FUNC0(0x36075567, sceRtcGetDosTime),
        HLE_FUNC0(0x34885E0D, sceRtcConvertUtcToLocalTime),
        HLE_FUNC0(0x28E1E988, sceRtcParseRFC3339),
        HLE_FUNC0(0x27F98543, sceRtcFormatRFC3339LocalTime),
        HLE_FUNC0(0x27C4594C, sceRtcGetTime_t),
        HLE_FUNC0(0x26D7A24A, sceRtcTickAddHours),
        HLE_FUNC0(0x26D25A5D, sceRtcTickAddMicroseconds),
        HLE_FUNC0(0x203CEB0D, sceRtcGetLastReincarnatedTime),
        HLE_FUNC0(0x1909C99B, sceRtcSetTime64_t),
        HLE_FUNC0(0x05EF322C, sceRtcGetDaysInMonth),
        HLE_FUNC0(0x0498FB3C, sceRtcFormatRFC3339),
        HLE_FUNC0(0x029CA3B3, sceRtcGetAccumlativeTime),
        HLE_FUNC0(0x011F03C1, sceRtcGetAccumulativeTime),
    };

    KernelSyscall const sceSuspendForUser[] =
    {
        HLE_FUNC0(0xEADB1BD7, sceKernelPowerLock),
        HLE_FUNC0(0xA569E425, sceKernelVolatileMemUnlock),
        HLE_FUNC0(0xA14F40B2, sceKernelVolatileMemTryLock),
        HLE_FUNC0(0x3E0271D3, sceKernelVolatileMemLock),
        HLE_FUNC0(0x3AEE7261, sceKernelPowerUnlock),
        HLE_FUNC0(0x090CCB3F, sceKernelPowerTick),
    };

    KernelSyscall const sceImpose[] =
    {
        HLE_FUNC0(0xFF1A2F07, sceImpose_FF1A2F07),
        HLE_FUNC0(0xFCD44963, sceImpose_FCD44963),
        HLE_FUNC0(0xE0887BC8, sceImposeGetUMDPopup),
        HLE_FUNC0(0xBB3F5DEC, sceImpose_BB3F5DEC),
        HLE_FUNC0(0xA9884B00, sceImpose_A9884B00),
        HLE_FUNC0(0x9BA61B49, sceImpose_9BA61B49),
        HLE_FUNC0(0x967F6D4A, sceImposeSetBacklightOffTime),
        HLE_FUNC0(0x8F6E3518, sceImposeGetBacklightOffTime),
        HLE_FUNC0(0x8C943191, sceImposeGetBatteryIconStatus),
        HLE_FUNC0(0x72189C48, sceImposeSetUMDPopup),
        HLE_FUNC0(0x5595A71A, sceImposeSetHomePopup),
        HLE_FUNC0(0x381BD9E7, sceImposeHomeButton),
        HLE_FUNC0(0x36AA6E91, sceImposeSetLanguageMode),
        HLE_FUNC0(0x24FD7BCF, sceImposeGetLanguageMode),
        HLE_FUNC0(0x0F341BE4, sceImposeGetHomePopup),
    };

    KernelSyscall const sceMpeg[] =
    {
        HLE_FUNC0(0xFE246728, sceMpegGetAvcAu),
        HLE_FUNC0(0xF8DCB679, sceMpegQueryAtracEsSize),
        HLE_FUNC0(0xF2930C9C, sceMpegAvcDecodeStopYCbCr),
        HLE_FUNC0(0xF0EB1125, sceMpegAvcDecodeYCbCr),
        HLE_FUNC0(0xE1CE83A7, sceMpegGetAtracAu),
        HLE_FUNC0(0xD8C5F121, sceMpegCreate),
        HLE_FUNC0(0xD7A29F46, sceMpegRingbufferQueryMemSize),
        HLE_FUNC0(0xCEB870B1, sceMpegFreeAvcEsBuf),
        HLE_FUNC0(0xC45C99CC, sceMpegQueryUserdataEsSize),
        HLE_FUNC0(0xC132E22F, sceMpegQueryMemSize),
        HLE_FUNC0(0xC02CF6B5, sceMpegQueryPcmEsSize),
        HLE_FUNC0(0xB5F6DC87, sceMpegRingbufferAvailableSize),
        HLE_FUNC0(0xB240A59E, sceMpegRingbufferPut),
        HLE_FUNC0(0xA780CF7E, sceMpegMallocAvcEsBuf),
        HLE_FUNC0(0xA11C7026, sceMpegAvcDecodeMode),
        HLE_FUNC0(0x9DCFB7EA, sceMpegChangeGetAuMode),
        HLE_FUNC0(0x921FCCCF, sceMpegGetAvcEsAu),
        HLE_FUNC0(0x8C1E027D, sceMpegGetPcmAu),
        HLE_FUNC0(0x874624D6, sceMpegFinish),
        HLE_FUNC0(0x800C44DF, sceMpegAtracDecode),
        HLE_FUNC0(0x769BEBB6, sceMpegRingbufferQueryPackNum),
        HLE_FUNC0(0x75E21135, sceMpeg_75E21135),
        HLE_FUNC0(0x740FCCD1, sceMpegAvcDecodeStop),
        HLE_FUNC0(0x707B7629, sceMpegFlushAllStream),
        HLE_FUNC0(0x682A619B, sceMpegInit),
        HLE_FUNC0(0x67179B1B, sceMpegAvcInitYCbCr),
        HLE_FUNC0(0x611E9E11, sceMpegQueryStreamSize),
        HLE_FUNC0(0x606A4649, sceMpegDelete),
        HLE_FUNC0(0x591A4AA2, sceMpegUnRegistStream),
        HLE_FUNC0(0x500F0429, sceMpegFlushStream),
        HLE_FUNC0(0x4571CC64, sceMpegAvcDecodeFlush),
        HLE_FUNC0(0x42C679F6, sceMpeg_42C679F6),
        HLE_FUNC0(0x42560F23, sceMpegRegistStream),
        HLE_FUNC0(0x3C37A7A6, sceMpegNextAvcRpAu),
        HLE_FUNC0(0x37295ED8, sceMpegRingbufferConstruct),
        HLE_FUNC0(0x31BD0272, sceMpegAvcCsc),
        HLE_FUNC0(0x234586AE, sceMpegChangeGetAvcAuMode),
        HLE_FUNC0(0x21FF80E4, sceMpegQueryStreamOffset),
        HLE_FUNC0(0x211A057C, sceMpegAvcQueryYCbCrSize),
        HLE_FUNC0(0x167AFD9E, sceMpegInitAu),
        HLE_FUNC0(0x13407F13, sceMpegRingbufferDestruct),
        HLE_FUNC0(0x11F95CF1, sceMpegGetAvcNalAu),
        HLE_FUNC0(0x0F6C18D7, sceMpegAvcDecodeDetail),
        HLE_FUNC0(0x0E3C2E9D, sceMpegAvcDecode),
        HLE_FUNC0(0x0558B075, sceMpegAvcCopyYCbCr),
        HLE_FUNC0(0x01977054, sceMpegGetUserdataAu),
    };

    KernelSyscall const InterruptManager[] =
    {
        HLE_FUNC0(0xFC4374B8, sceKernelIsSubInterruptOccurred),
        HLE_FUNC0(0xFB8E22EC, sceKernelEnableSubIntr),
        HLE_FUNC0(0xEEE43F47, sceKernelRegisterUserSpaceIntrStack),
        HLE_FUNC0(0xD61E6961, sceKernelReleaseSubIntrHandler),
        HLE_FUNC0(0xD2E8363F, QueryIntrHandlerInfo),
        HLE_FUNC0(0xCA04A2B9, sceKernelRegisterSubIntrHandler),
        HLE_FUNC0(0x8A389411, sceKernelDisableSubIntr),
        HLE_FUNC0(0x7860E0DC, sceKernelResumeSubIntr),
        HLE_FUNC0(0x5CB5A78B, sceKernelSuspendSubIntr),
    };

    KernelSyscall const StdioForUser[] =
    {
        HLE_FUNC0(0xF78BA90A, sceKernelStderr),
        HLE_FUNC0(0xA6BAB2E9, sceKernelStdout),
        HLE_FUNC0(0xA46785C9, sceKernelStdioSendChar),
        HLE_FUNC0(0xA3B931DB, sceKernelStdioWrite),
        HLE_FUNC0(0x9D061C19, sceKernelStdioClose),
        HLE_FUNC0(0x924ABA61, sceKernelStdioOpen),
        HLE_FUNC0(0x6F797E03, sceKernelRegisterStderrPipe),
        HLE_FUNC0(0x432D8F5C, sceKernelRegisterStdoutPipe),
        HLE_FUNC0(0x3054D478, sceKernelStdioRead),
        HLE_FUNC0(0x172D316E, sceKernelStdin),
        HLE_FUNC0(0x0CBB0571, sceKernelStdioLseek),
    };

    KernelSyscall const sceUmdUser[] =
    {
        HLE_FUNC0(0xE83742BA, sceUmdDeactivate),
        HLE_FUNC0(0xCBE9F02A, sceUmdReplacePermit),
        HLE_FUNC0(0xC6183D47, sceUmdActivate),
        HLE_FUNC0(0xBD2BDE07, sceUmdUnRegisterUMDCallBack),
        HLE_FUNC0(0xAEE7404D, sceUmdRegisterUMDCallBack),
        HLE_FUNC0(0x8EF08FCE, sceUmdWaitDriveStat),
        HLE_FUNC0(0x87533940, sceUmdReplaceProhibit),
        HLE_FUNC0(0x6B4A146C, sceUmdGetDriveStat),
        HLE_FUNC0(0x6AF9B50A, sceUmdCancelWaitDriveStat),
        HLE_FUNC0(0x56202973, sceUmdWaitDriveStatWithTimer),
        HLE_FUNC0(0x4A9E5E29, sceUmdWaitDriveStatCB),
        HLE_FUNC0(0x46EBB729, sceUmdCheckMedium),
        HLE_FUNC0(0x340B7686, sceUmdGetDiscInfo),
        HLE_FUNC0(0x20628E6F, sceUmdGetErrorStat),
    };

    KernelSyscall const sceAtrac3plus[] =
    {
        HLE_FUNC0(0xFAA4F89B, sceAtracGetLoopStatus),
        HLE_FUNC0(0xECA32A99, sceAtracIsSecondBufferNeeded),
        HLE_FUNC0(0xE88F759B, sceAtracGetInternalErrorInfo),
        HLE_FUNC0(0xE23E3A35, sceAtracGetNextDecodePosition),
        HLE_FUNC0(0xD6A5F2F7, sceAtracGetMaxSample),
        HLE_FUNC0(0xD5C28CC0, sceAtracEndEntry),
        HLE_FUNC0(0xD1F59FDB, sceAtracStartEntry),
        HLE_FUNC0(0xCA3CA3D2, sceAtracGetBufferInfoForReseting),
        HLE_FUNC0(0xB3B5D042, sceAtracGetOutputChannel),
        HLE_FUNC0(0xA554A158, sceAtracGetBitrate),
        HLE_FUNC0(0xA2BBA8BE, sceAtracGetSoundSample),
        HLE_FUNC0(0x9CD7DE03, sceAtracSetMOutHalfwayBufferAndGetID),
        HLE_FUNC0(0x9AE849A7, sceAtracGetRemainFrame),
        HLE_FUNC0(0x868120B5, sceAtracSetLoopNum),
        HLE_FUNC0(0x83E85EA0, sceAtracGetSecondBufferInfo),
        HLE_FUNC0(0x83BF7AFD, sceAtracSetSecondBuffer),
        HLE_FUNC0(0x7DB31251, sceAtracAddStreamData),
        HLE_FUNC0(0x7A20E7AF, sceAtracSetDataAndGetID),
        HLE_FUNC0(0x780F88D1, sceAtracGetAtracID),
        HLE_FUNC0(0x6A8C3CD5, sceAtracDecodeData),
        HLE_FUNC0(0x644E5607, sceAtracResetPlayPosition),
        HLE_FUNC0(0x61EB33F5, sceAtracReleaseAtracID),
        HLE_FUNC0(0x5DD66588, sceAtracSetAA3HalfwayBufferAndGetID),
        HLE_FUNC0(0x5D268707, sceAtracGetStreamDataInfo),
        HLE_FUNC0(0x5CF9D852, sceAtracSetMOutHalfwayBuffer),
        HLE_FUNC0(0x5622B7C1, sceAtracSetAA3DataAndGetID),
        HLE_FUNC0(0x3F6E26B5, sceAtracSetHalfwayBuffer),
        HLE_FUNC0(0x36FAABFB, sceAtracGetNextSample),
        HLE_FUNC0(0x31668BAA, sceAtracGetChannel),
        HLE_FUNC0(0x2DD3E298, sceAtracGetBufferInfoForResetting),
        HLE_FUNC0(0x132F1ECA, sceAtracReinit),
        HLE_FUNC0(0x0FAE370E, sceAtracSetHalfwayBufferAndGetID),
        HLE_FUNC0(0x0E2A73AB, sceAtracSetData),
    };

    KernelSyscall const sceAudio[] =
    {
        HLE_FUNC0(0xE9D97901, sceAudioGetChannelRestLen),
        HLE_FUNC0(0xE926D3FB, sceAudioInputInitEx),
        HLE_FUNC0(0xE2D56B2D, sceAudioOutputPanned),
        HLE_FUNC0(0xE0727056, sceAudioSRCOutputBlocking),
        HLE_FUNC0(0xCB2E439E, sceAudioSetChannelDataLen),
        HLE_FUNC0(0xB7E1D8E7, sceAudioChangeChannelVolume),
        HLE_FUNC0(0xB011922F, sceAudioGetChannelRestLength),
        HLE_FUNC0(0xA708C6A6, sceAudioGetInputLength),
        HLE_FUNC0(0xA633048E, sceAudioPollInputEnd),
        HLE_FUNC0(0x95FD0C2D, sceAudioChangeChannelConfig),
        HLE_FUNC0(0x8C1009B2, sceAudioOutput),
        HLE_FUNC0(0x87B2E651, sceAudioWaitInputEnd),
        HLE_FUNC0(0x7DE61688, sceAudioInputInit),
        HLE_FUNC0(0x6FC46853, sceAudioChRelease),
        HLE_FUNC0(0x6D4BEC68, sceAudioInput),
        HLE_FUNC0(0x647CEF33, sceAudioOutput2GetRestSample),
        HLE_FUNC0(0x63F2889C, sceAudioOutput2ChangeLength),
        HLE_FUNC0(0x5EC81C55, sceAudioChReserve),
        HLE_FUNC0(0x5C37C0AE, sceAudioSRCChRelease),
        HLE_FUNC0(0x43196845, sceAudioOutput2Release),
        HLE_FUNC0(0x41EFADE7, sceAudioOneshotOutput),
        HLE_FUNC0(0x38553111, sceAudioSRCChReserve),
        HLE_FUNC0(0x2D53F36E, sceAudioOutput2OutputBlocking),
        HLE_FUNC0(0x13F592BC, sceAudioOutputPannedBlocking),
        HLE_FUNC0(0x136CAF51, sceAudioOutputBlocking),
        HLE_FUNC0(0x086E5895, sceAudioInputBlocking),
        HLE_FUNC0(0x01562BA3, sceAudioOutput2Reserve),
    };

    KernelSyscall const sceSasCore[] =
    {
        HLE_FUNC0(0xF983B186, __sceSasRevVON),
        HLE_FUNC0(0xE855BF76, __sceSasSetOutputmode),
        HLE_FUNC0(0xE1CD9561, __sceSasSetVoicePCM),
        HLE_FUNC0(0xE175EF66, __sceSasGetOutputmode),
        HLE_FUNC0(0xD5EBBBCD, __sceSasSetSteepWave),
        HLE_FUNC0(0xD5A229C9, __sceSasRevEVOL),
        HLE_FUNC0(0xD1E0A01E, __sceSasSetGrain),
        HLE_FUNC0(0xCBCD4F79, __sceSasSetSimpleADSR),
        HLE_FUNC0(0xBD11B7C2, __sceSasGetGrain),
        HLE_FUNC0(0xB7660A23, __sceSasSetNoise),
        HLE_FUNC0(0xAD84D37F, __sceSasSetPitch),
        HLE_FUNC0(0xA3589D81, __sceSasCore),
        HLE_FUNC0(0xA232CBE6, __sceSasSetTrianglarWave),
        HLE_FUNC0(0xA0CF2FA4, __sceSasSetKeyOff),
        HLE_FUNC0(0x9EC3676A, __sceSasSetADSRmode),
        HLE_FUNC0(0x99944089, __sceSasSetVoice),
        HLE_FUNC0(0x787D04D5, __sceSasSetPause),
        HLE_FUNC0(0x76F01ACA, __sceSasSetKeyOn),
        HLE_FUNC0(0x74AE582A, __sceSasGetEnvelopeHeight),
        HLE_FUNC0(0x68A46B95, __sceSasGetEndFlag),
        HLE_FUNC0(0x5F9529F6, __sceSasSetSL),
        HLE_FUNC0(0x50A14DFC, __sceSasCoreWithMix),
        HLE_FUNC0(0x440CA7D8, __sceSasSetVolume),
        HLE_FUNC0(0x42778A9F, __sceSasInit),
        HLE_FUNC0(0x33D4AB37, __sceSasRevType),
        HLE_FUNC0(0x2C8E6AB3, __sceSasGetPauseFlag),
        HLE_FUNC0(0x267A6DD2, __sceSasRevParam),
        HLE_FUNC0(0x07F58C24, __sceSasGetAllEnvelopeHeights),
        HLE_FUNC0(0x019B25EB, __sceSasSetADSR),
    };
    KernelSyscall const sceDisplay[] =
    {
        HLE_FUNC0(0xEEDA2E54, sceDisplayGetFrameBuf),
        HLE_FUNC0(0xDEA197D4, sceDisplayGetMode),
        HLE_FUNC0(0xDBA6C4C4, sceDisplayGetFramePerSec),
        HLE_FUNC0(0xBF79F646, sceDisplayGetResumeMode),
        HLE_FUNC0(0xB4F378FA, sceDisplayIsForeground),
        HLE_FUNC0(0xA83EF139, sceDisplayAdjustAccumulatedHcount),
        HLE_FUNC0(0xA544C486, sceDisplaySetResumeMode),
        HLE_FUNC0(0x9C6EAAD7, sceDisplayGetVcount),
        HLE_FUNC0(0x984C27E7, sceDisplayWaitVblankStart),
        HLE_FUNC0(0x8EB9EC49, sceDisplayWaitVblankCB),
        HLE_FUNC0(0x7ED59BC4, sceDisplaySetHoldMode),
        HLE_FUNC0(0x77ED8B3A, sceDisplay_77ED8B3A),
        HLE_FUNC0(0x773DD3A3, sceDisplayGetCurrentHcount),
        HLE_FUNC0(0x69B53541, sceDisplayGetVblankRest),
        HLE_FUNC0(0x4D4E10EC, sceDisplayIsVblank),
        HLE_FUNC0(0x46F186C3, sceDisplayWaitVblankStartCB),
        HLE_FUNC0(0x40F1469C, sceDisplay_40F1469C),
        HLE_FUNC0(0x36CDFADE, sceDisplayWaitVblank),
        HLE_FUNC0(0x31C4BAA8, sceDisplayGetBrightness),
        HLE_FUNC0(0x289D82FE, sceDisplaySetFrameBuf),
        HLE_FUNC0(0x210EAB3A, sceDisplayGetAccumulatedHcount),
        HLE_FUNC0(0x21038913, sceDisplayIsVsync),
        HLE_FUNC0(0x0E20F177, sceDisplaySetMode),
    };

    KernelSyscall const sceGe_user[] =
    {
        HLE_FUNC0(0xE66CB92E, sceGeGetStack),
        HLE_FUNC0(0xE47E40E4, sceGeEdramGetAddr),
        HLE_FUNC0(0xE0D68148, sceGeListUpdateStallAddr),
        HLE_FUNC0(0xDC93CFEF, sceGeGetCmd),
        HLE_FUNC0(0xB77905EA, sceGeEdramSetAddrTranslation),
        HLE_FUNC0(0xB448EC0D, sceGeBreak),
        HLE_FUNC0(0xB287BD61, sceGeDrawSync),
        HLE_FUNC0(0xAB49E76A, sceGeListEnQueue),
        HLE_FUNC0(0xA4FC06A4, sceGeSetCallback),
        HLE_FUNC0(0x5FB86AB0, sceGeListDeQueue),
        HLE_FUNC0(0x57C8945B, sceGeGetMtx),
        HLE_FUNC0(0x4C06E472, sceGeContinue),
        HLE_FUNC0(0x438A385A, sceGeSaveContext),
        HLE_FUNC0(0x1F6752AD, sceGeEdramGetSize),
        HLE_FUNC0(0x1C0D95A6, sceGeListEnQueueHead),
        HLE_FUNC0(0x0BF608FB, sceGeRestoreContext),
        HLE_FUNC0(0x05DB22CE, sceGeUnsetCallback),
        HLE_FUNC0(0x03444EB4, sceGeListSync),
    };	

    KernelSyscall const sceCtrl[] =
    {
        HLE_FUNC0(0xDA6B76A1, sceCtrlGetSamplingMode),
        HLE_FUNC0(0xC152080A, sceCtrlPeekBufferNegative),
        HLE_FUNC0(0xB1D0E5CD, sceCtrlPeekLatch),
        HLE_FUNC0(0xAF5960F3, sceCtrl_AF5960F3),
        HLE_FUNC0(0xA7144800, sceCtrlSetIdleCancelThreshold),
        HLE_FUNC0(0xA68FD260, sceCtrlClearRapidFire),
        HLE_FUNC0(0x6A2774F3, sceCtrlSetSamplingCycle),
        HLE_FUNC0(0x687660FA, sceCtrlGetIdleCancelThreshold),
        HLE_FUNC0(0x6841BE1A, sceCtrlSetRapidFire),
        HLE_FUNC0(0x60B81F86, sceCtrlReadBufferNegative),
        HLE_FUNC0(0x3A622550, sceCtrlPeekBufferPositive),
        HLE_FUNC0(0x348D99D4, sceCtrl_348D99D4),
        HLE_FUNC0(0x1F803938, sceCtrlReadBufferPositive/*, "nbufread:i/buf:{TimeStamp:u,Buttons:x,Lx:1i,Ly:1i},nbuf:u"*/ ),
        HLE_FUNC0(0x1F4011E6, sceCtrlSetSamplingMode),
        HLE_FUNC0(0x0B588501, sceCtrlReadLatch),
        HLE_FUNC0(0x02BAAD91, sceCtrlGetSamplingCycle),
    };

    KernelSyscall const sceDmac[] =
    {
        HLE_FUNC0(0xD97F94D8, sceDmacTryMemcpy),
        HLE_FUNC0(0x617F3FE6, sceDmacMemcpy),
    };

    KernelSyscall const UtilsForUser[] =
    {
        HLE_FUNC0(0xFB05FAD0, sceKernelIcacheReadTag),
        HLE_FUNC0(0xF8FCD5BA, sceKernelUtilsSha1BlockInit),
        HLE_FUNC0(0xF0155BCA, UtilsForUser_F0155BCA),
        HLE_FUNC0(0xE860E75E, sceKernelUtilsMt19937Init),
        HLE_FUNC0(0xDBBE9A46, UtilsForUser_DBBE9A46),
        HLE_FUNC0(0xC8186A58, sceKernelUtilsMd5Digest),
        HLE_FUNC0(0xC2DF770E, sceKernelIcacheInvalidateRange),
        HLE_FUNC0(0xBFA98062, sceKernelDcacheInvalidateRange),
        HLE_FUNC0(0xB8D24E78, sceKernelUtilsMd5BlockResult),
        HLE_FUNC0(0xB83A1E76, UtilsForUser_B83A1E76),
        HLE_FUNC0(0xB435DEC5, sceKernelDcacheWritebackInvalidateAll),
        HLE_FUNC0(0xAF3766BB, UtilsForUser_AF3766BB),
        HLE_FUNC0(0x9E5C5086, sceKernelUtilsMd5BlockInit),
        HLE_FUNC0(0x99134C3F, UtilsForUser_99134C3F),
        HLE_FUNC0(0x920F104A, sceKernelIcacheInvalidateAll),
        HLE_FUNC0(0x91E4F6A7, sceKernelLibcClock),
        HLE_FUNC0(0x87E81561, sceKernelPutUserLog),
        HLE_FUNC0(0x840259F1, sceKernelUtilsSha1Digest),
        HLE_FUNC0(0x80001C4C, sceKernelDcacheProbe),
        HLE_FUNC0(0x79D1C3FA, sceKernelDcacheWritebackAll),
        HLE_FUNC0(0x77DFF087, sceKernelDcacheProbeRange),
        HLE_FUNC0(0x740DF7F0, UtilsForUser_740DF7F0),
        HLE_FUNC0(0x7333E539, UtilsForUser_7333E539),
        HLE_FUNC0(0x71EC4271, sceKernelLibcGettimeofday),
        HLE_FUNC0(0x6AD345D7, sceKernelSetGPO),
        HLE_FUNC0(0x6231A71D, UtilsForUser_6231A71D),
        HLE_FUNC0(0x61E1E525, sceKernelUtilsMd5BlockUpdate),
        HLE_FUNC0(0x5C7F2B1A, UtilsForUser_5C7F2B1A),
        HLE_FUNC0(0x585F1C09, sceKernelUtilsSha1BlockResult),
        HLE_FUNC0(0x515B4FAF, UtilsForUser_515B4FAF),
        HLE_FUNC0(0x4FD31C9D, sceKernelIcacheProbe),
        HLE_FUNC0(0x43C9A8DB, UtilsForUser_43C9A8DB),
        HLE_FUNC0(0x3FD3D324, UtilsForUser_3FD3D324),
        HLE_FUNC0(0x3EE30821, sceKernelDcacheWritebackRange),
        HLE_FUNC0(0x39F49610, UtilsForUser_39F49610),
        HLE_FUNC0(0x37FB5C42, sceKernelGetGPI),
        HLE_FUNC0(0x34B9FA9E, sceKernelDcacheWritebackInvalidateRange),
        HLE_FUNC0(0x346F6DA8, sceKernelUtilsSha1BlockUpdate),
        HLE_FUNC0(0x27CC57F0, sceKernelLibcTime),
        HLE_FUNC0(0x1B0592A3, UtilsForUser_1B0592A3),
        HLE_FUNC0(0x16641D70, sceKernelDcacheReadTag),
        HLE_FUNC0(0x157A383A, UtilsForUser_157A383A),
        HLE_FUNC0(0x06FB8A63, sceKernelUtilsMt19937UInt),
        HLE_FUNC0(0x004D4DEE, UtilsForUser_004D4DEE),
    };

    KernelSyscall const IoFileMgrForUser[] =
    {
        HLE_FUNC0(0xFF5940B6, sceIoCloseAsync),
        HLE_FUNC0(0xF27A9C51, sceIoRemove),
        HLE_FUNC0(0xEB092469, sceIoDclose),
        HLE_FUNC0(0xE95A012B, sceIoIoctlAsync),
        HLE_FUNC0(0xE8BC6571, sceIoCancel),
        HLE_FUNC0(0xE3EB004C, sceIoDread),
        HLE_FUNC0(0xE23EEC33, sceIoWaitAsync),
        HLE_FUNC0(0xCB05F8D6, sceIoGetAsyncStat),
        HLE_FUNC0(0xB8A740F4, sceIoChstat),
        HLE_FUNC0(0xB2A628C1, sceIoAssign),
        HLE_FUNC0(0xB29DDF9C, sceIoDopen),
        HLE_FUNC0(0xB293727F, sceIoChangeAsyncPriority),
        HLE_FUNC0(0xACE946E8, sceIoGetstat),
        HLE_FUNC0(0xAB96437F, sceIoSync),
        HLE_FUNC0(0xA12A0514, sceIoSetAsyncCallback),
        HLE_FUNC0(0xA0B5A7C2, sceIoReadAsync),
        HLE_FUNC0(0x89AA9906, sceIoOpenAsync),
        HLE_FUNC0(0x810C4BC3, sceIoClose),
        HLE_FUNC0(0x779103A0, sceIoRename),
        HLE_FUNC0(0x71B19E77, sceIoLseekAsync),
        HLE_FUNC0(0x6D08A871, sceIoUnassign),
        HLE_FUNC0(0x6A638D83, sceIoRead),
        HLE_FUNC0(0x68963324, sceIoLseek32),
        HLE_FUNC0(0x63632449, sceIoIoctl),
        HLE_FUNC0(0x5C2BE2CC, sceIoGetFdList),
        HLE_FUNC0(0x55F4717D, sceIoChdir),
        HLE_FUNC0(0x54F5FB11, sceIoDevctl),
        HLE_FUNC0(0x42EC03AC, sceIoWrite),
        HLE_FUNC0(0x35DBD746, sceIoWaitAsyncCB),
        HLE_FUNC0(0x3251EA56, sceIoPollAsync),
        HLE_FUNC0(0x27EB27B8, sceIoLseek),
        HLE_FUNC0(0x1B385D8F, sceIoLseek32Async),
        HLE_FUNC0(0x1117C65F, sceIoRmdir),
        HLE_FUNC0(0x109F50BC, sceIoOpen),
        HLE_FUNC0(0x0FACAB19, sceIoWriteAsync),
        HLE_FUNC0(0x08BD7374, sceIoGetDevType),
        HLE_FUNC0(0x06A70004, sceIoMkdir),
    };

#if 0
	KernelSyscall const ThreadManForUser[] =
	{
		HLE_FUNC0(0xFFC36A14, sceKernelReferThreadRunStatus),
		HLE_FUNC0(0xFCCFAD26, sceKernelCancelWakeupThread),
		HLE_FUNC0(0xFBFA697D, sceKernelReceiveMsgPipeCB),
		HLE_FUNC0(0xFB6425C3, sceKernelSetVTimerTimeWide),
		HLE_FUNC0(0xF8170FBE, sceKernelDeleteMutex),
		HLE_FUNC0(0xF6414A71, sceKernelFreeFpl),
		HLE_FUNC0(0xF475845D, sceKernelStartThread),
		HLE_FUNC0(0xF3986382, sceKernelReceiveMbxCB),
		HLE_FUNC0(0xF0B7DA1C, sceKernelDeleteMsgPipe),
		HLE_FUNC0(0xEF9E4C70, sceKernelDeleteEventFlag),
		HLE_FUNC0(0xEDBA5844, sceKernelDeleteCallback),
		HLE_FUNC0(0xED1410E0, sceKernelDeleteFpl),
		HLE_FUNC0(0xEC0A693F, sceKernelAllocateVplCB),
		HLE_FUNC0(0xEA748E31, sceKernelChangeCurrentThreadAttr),
		HLE_FUNC0(0xE9B3061E, sceKernelSendMbx),
		HLE_FUNC0(0xE81CAF8F, sceKernelCreateCallback),
		HLE_FUNC0(0xE7282CB6, sceKernelAllocateFplCB),
		HLE_FUNC0(0xE1619D7C, sceKernelSysClock2USecWide),
		HLE_FUNC0(0xDF52098F, sceKernelTryReceiveMsgPipe),
		HLE_FUNC0(0xDB738F35, sceKernelGetSystemTime),
		HLE_FUNC0(0xDAA3F564, sceKernelReferAlarmStatus),
		HLE_FUNC0(0xD979E9BF, sceKernelAllocateFpl),
		HLE_FUNC0(0xD8B299AE, sceKernelSetVTimerHandler),
		HLE_FUNC0(0xD8199E4C, sceKernelReferFplStatus),
		HLE_FUNC0(0xD6DA4BA1, sceKernelCreateSema),
		HLE_FUNC0(0xD59EAD2F, sceKernelWakeupThread),
		HLE_FUNC0(0xD2D615EF, sceKernelCancelVTimerHandler),
		HLE_FUNC0(0xD13BDE95, sceKernelCheckThreadStack),
		HLE_FUNC0(0xD0AEEE87, sceKernelStopVTimer),
		HLE_FUNC0(0xCEADEB47, sceKernelDelayThread),
		HLE_FUNC0(0xCD203292, sceKernelCancelEventFlag),
		HLE_FUNC0(0xC8CD158C, sceKernelUSec2SysClockWide),
		HLE_FUNC0(0xC68D9437, sceKernelStartVTimer),
		HLE_FUNC0(0xC11BA8C4, sceKernelNotifyCallback),
		HLE_FUNC0(0xC0B3FFD2, sceKernelGetVTimerTimeWide),
		HLE_FUNC0(0xC07BB470, sceKernelCreateFpl),
		HLE_FUNC0(0xBEED3A47, ThreadManForUser_BEED3A47),
		HLE_FUNC0(0xBED27435, sceKernelAllocateVpl),
		HLE_FUNC0(0xBD123D9E, sceKernelDelaySysClockThread),
		HLE_FUNC0(0xBC6FEBC5, sceKernelReferSemaStatus),
		HLE_FUNC0(0xBA6B92E2, sceKernelSysClock2USec),
		HLE_FUNC0(0xBA4051D6, sceKernelCancelCallback),
		HLE_FUNC0(0xB7D098C6, sceKernelCreateMutex),
		HLE_FUNC0(0xB7C18B77, sceKernelGetVTimerBaseWide),
		HLE_FUNC0(0xB736E9FF, sceKernelFreeVpl),
		HLE_FUNC0(0xB3A59970, sceKernelGetVTimerBase),
		HLE_FUNC0(0xB2C25152, sceKernelSetSysClockAlarm),
		HLE_FUNC0(0xB011B11F, sceKernelLockMutex),
		HLE_FUNC0(0xAF36D708, sceKernelTryAllocateVpl),
		HLE_FUNC0(0xAA73C935, sceKernelExitThread),
		HLE_FUNC0(0xA9C2CB9A, sceKernelReferMutexStatus),
		HLE_FUNC0(0xA8E8C846, sceKernelReferMbxStatus),
		HLE_FUNC0(0xA8AA591F, sceKernelCancelFpl),
		HLE_FUNC0(0xA66B0120, sceKernelReferEventFlagStatus),
		HLE_FUNC0(0x9FA03CD3, sceKernelDeleteThread),
		HLE_FUNC0(0x9ACE131E, sceKernelSleepThread),
		HLE_FUNC0(0x9944F31F, sceKernelSuspendThread),
		HLE_FUNC0(0x94AA61EE, sceKernelGetThreadCurrentPriority),
		HLE_FUNC0(0x94416130, sceKernelGetThreadmanIdList),
		HLE_FUNC0(0x912354A7, sceKernelRotateThreadReadyQueue),
		HLE_FUNC0(0x8FFDF9A2, sceKernelCancelSema),
		HLE_FUNC0(0x89B3D48C, sceKernelDeleteVpl),
		HLE_FUNC0(0x884C9F90, sceKernelTrySendMsgPipe),
		HLE_FUNC0(0x87D9223C, sceKernelCancelMutex),
		HLE_FUNC0(0x87D4DD36, sceKernelCancelReceiveMbx),
		HLE_FUNC0(0x876DBFAD, sceKernelSendMsgPipe),
		HLE_FUNC0(0x8672E3D0, ThreadManForUser_8672E3D0),
		HLE_FUNC0(0x86255ADA, sceKernelDeleteMbx),
		HLE_FUNC0(0x840E8133, sceKernelWaitThreadEndCB),
		HLE_FUNC0(0x82BC5777, sceKernelGetSystemTimeWide),
		HLE_FUNC0(0x82826F70, sceKernelSleepThreadCB),
		HLE_FUNC0(0x8218B4DD, sceKernelReferGlobalProfiler),
		HLE_FUNC0(0x8125221D, sceKernelCreateMbx),
		HLE_FUNC0(0x812346E4, sceKernelClearEventFlag),
		HLE_FUNC0(0x809CE29B, sceKernelExitDeleteThread),
		HLE_FUNC0(0x7E65B999, sceKernelCancelAlarm),
		HLE_FUNC0(0x7CFF8CF3, ThreadManForUser_7CFF8CF3),
		HLE_FUNC0(0x7C41F2C2, sceKernelSendMsgPipeCB),
		HLE_FUNC0(0x7C0DC2A0, sceKernelCreateMsgPipe),
		HLE_FUNC0(0x75156E8F, sceKernelResumeThread),
		HLE_FUNC0(0x74829B76, sceKernelReceiveMsgPipe),
		HLE_FUNC0(0x730ED8BC, sceKernelReferCallbackStatus),
		HLE_FUNC0(0x72F3C145, sceKernelReleaseThreadEventHandler),
		HLE_FUNC0(0x71BC9871, sceKernelChangeThreadPriority),
		HLE_FUNC0(0x71040D5C, ThreadManForUser_71040D5C),
		HLE_FUNC0(0x6E9EA350, _sceKernelReturnFromCallback),
		HLE_FUNC0(0x6D212BAC, sceKernelWaitSemaCB),
		HLE_FUNC0(0x6B30100F, sceKernelUnlockMutex),
		HLE_FUNC0(0x68DA9E36, sceKernelDelayThreadCB),
		HLE_FUNC0(0x6652B8CA, sceKernelSetAlarm),
		HLE_FUNC0(0x64D4540E, sceKernelReferThreadProfiler),
		HLE_FUNC0(0x627E6F3A, sceKernelReferSystemStatus),
		HLE_FUNC0(0x623AE665, sceKernelTryAllocateFpl),
		HLE_FUNC0(0x616403BA, sceKernelTerminateThread),
		HLE_FUNC0(0x60107536, sceKernelDeleteLwMutex),
		HLE_FUNC0(0x5F32BEAA, sceKernelReferVTimerStatus),
		HLE_FUNC0(0x5BF4DD27, sceKernelLockMutexCB),
		HLE_FUNC0(0x58B1F937, sceKernelPollSema),
		HLE_FUNC0(0x57CF62DD, sceKernelGetThreadmanIdType),
		HLE_FUNC0(0x56C039B5, sceKernelCreateVpl),
		HLE_FUNC0(0x55C20A00, sceKernelCreateEventFlag),
		HLE_FUNC0(0x542AD630, sceKernelSetVTimerTime),
		HLE_FUNC0(0x53B00E9A, sceKernelSetVTimerHandlerWide),
		HLE_FUNC0(0x532A522E, _sceKernelExitThread),
		HLE_FUNC0(0x52089CA1, sceKernelGetThreadStackFreeSize),
		HLE_FUNC0(0x4E3A1105, sceKernelWaitSema),
		HLE_FUNC0(0x4C145944, sceKernelReferLwMutexStatusByID),
		HLE_FUNC0(0x446D8DE6, sceKernelCreateThread),
		HLE_FUNC0(0x402FCF22, sceKernelWaitEventFlag),
		HLE_FUNC0(0x3F53E640, sceKernelSignalSema),
		HLE_FUNC0(0x3B183E26, sceKernelGetThreadExitStatus),
		HLE_FUNC0(0x3AD58B8C, sceKernelSuspendDispatchThread),
		HLE_FUNC0(0x39810265, sceKernelReferVplStatus),
		HLE_FUNC0(0x383F7BCC, sceKernelTerminateDeleteThread),
		HLE_FUNC0(0x369EEB6B, sceKernelReferThreadEventHandlerStatus),
		HLE_FUNC0(0x369ED59D, sceKernelGetSystemTimeLow),
		HLE_FUNC0(0x349D6D6C, sceKernelCheckCallback),
		HLE_FUNC0(0x349B864D, sceKernelCancelMsgPipe),
		HLE_FUNC0(0x33BE4024, sceKernelReferMsgPipeStatus),
		HLE_FUNC0(0x328F9E52, sceKernelDeleteVTimer),
		HLE_FUNC0(0x328C546A, sceKernelWaitEventFlagCB),
		HLE_FUNC0(0x31327F19, ThreadManForUser_31327F19),
		HLE_FUNC0(0x30FD48F0, sceKernelPollEventFlag),
		HLE_FUNC0(0x2C34E053, sceKernelReleaseWaitThread),
		HLE_FUNC0(0x2A3D44FF, sceKernelGetCallbackCount),
		HLE_FUNC0(0x293B45B8, sceKernelGetThreadId),
		HLE_FUNC0(0x28B6489C, sceKernelDeleteSema),
		HLE_FUNC0(0x27E22EC2, sceKernelResumeDispatchThread),
		HLE_FUNC0(0x278C0DF5, sceKernelWaitThreadEnd),
		HLE_FUNC0(0x20FFF560, sceKernelCreateVTimer),
		HLE_FUNC0(0x1FB15A32, sceKernelSetEventFlag),
		HLE_FUNC0(0x1D371B8A, sceKernelCancelVpl),
		HLE_FUNC0(0x1AF94D03, sceKernelDonateWakeupThread),
		HLE_FUNC0(0x19CFF145, sceKernelCreateLwMutex),
		HLE_FUNC0(0x18260574, sceKernelReceiveMbx),
		HLE_FUNC0(0x17C1684E, sceKernelReferThreadStatus),
		HLE_FUNC0(0x1181E963, sceKernelDelaySysClockThreadCB),
		HLE_FUNC0(0x110DEC9A, sceKernelUSec2SysClock),
		HLE_FUNC0(0x0E927AED, _sceKernelReturnFromTimerHandler),
		HLE_FUNC0(0x0DDCD2C9, sceKernelTryLockMutex),
		HLE_FUNC0(0x0D81716A, sceKernelPollMbx),
		HLE_FUNC0(0x0C106E53, sceKernelRegisterThreadEventHandler),
		HLE_FUNC0(0x034A921F, sceKernelGetVTimerTime),
	};
#endif

    KernelSyscall const SysMemUserForUser[] =
	{
		HLE_FUNC0(0xFE707FDF, SysMemUserForUser_FE707FDF),
		HLE_FUNC0(0xFC114573, sceKernelGetCompiledSdkVersion),
		HLE_FUNC1(0xF919F628, sceKernelTotalFreeMemSize,      "size:x/" ),
		HLE_FUNC1(0xF77D77CB, sceKernelSetCompilerVersion,    "err:x/version:x" ), 
		HLE_FUNC0(0xEBD5C3E6, SysMemUserForUser_EBD5C3E6),
		HLE_FUNC0(0xDB83A952, SysMemUserForUser_DB83A952),
		HLE_FUNC0(0xD8DE5C1E, SysMemUserForUser_D8DE5C1E),
		HLE_FUNC1(0xB6D61D02, sceKernelFreePartitionMemory,   "err:x/id:x" ),
		HLE_FUNC0(0xACBD88CA, SysMemUserForUser_ACBD88CA),
		HLE_FUNC0(0xA6848DF8, SysMemUserForUser_A6848DF8),
		HLE_FUNC1(0xA291F107, sceKernelMaxFreeMemSize,        "size:x/" ),
		HLE_FUNC1(0x9D9A5BA1, sceKernelGetBlockHeadAddr,      "addr:x/id:x" ),
		HLE_FUNC0(0x91DE343C, SysMemUserForUser_91DE343C),
		HLE_FUNC1(0x7591C7DB, sceKernelSetCompiledSdkVersion, "err:x/version:x" ),
		HLE_FUNC0(0x50F61D8A, SysMemUserForUser_50F61D8A),
		HLE_FUNC1(0x3FC9AE6A, sceKernelDevkitVersion,         "version:x/" ),
		HLE_FUNC0(0x342061E5, SysMemUserForUser_342061E5),
		HLE_FUNC0(0x315AD3A0, SysMemUserForUser_315AD3A0),
		HLE_FUNC0(0x2A3E5280, sceKernelQueryMemoryInfo),
		HLE_FUNC1(0x237DBD4F, sceKernelAllocPartitionMemory,  "id:x/pid:x,name:s,mode:i,size:u,addr:x" ),
		HLE_FUNC1(0x13A5ABEF, sceKernelPrintf,                "err:x/fmt:s" ),
		HLE_FUNC0(0x057E7380, SysMemUserForUser_057E7380),
	};

	KernelSyscall const Kernel_Library[] =
	{
		HLE_FUNC0(0xDC692EE3, sceKernelTryLockLwMutex),
		HLE_FUNC0(0xC1734599, sceKernelReferLwMutexStatus),
		HLE_FUNC0(0xBEA46419, sceKernelLockLwMutex),
		HLE_FUNC0(0xB55249D2, sceKernelIsCpuIntrEnable),
		HLE_FUNC0(0x5F10D406, sceKernelCpuResumeIntr),
		HLE_FUNC0(0x47A0B729, sceKernelIsCpuIntrSuspended),
		HLE_FUNC0(0x3B84732D, sceKernelCpuResumeIntrWithSync),
		HLE_FUNC0(0x1FC64E09, sceKernelLockLwMutexCB),
		HLE_FUNC0(0x15B6446B, sceKernelUnlockLwMutex),
		HLE_FUNC0(0x092968F4, sceKernelCpuSuspendIntr),
	};

	KernelSyscall const LoadExecForUser[] =
	{
		HLE_FUNC0(0xD1FB50DC, LoadExecForUser_D1FB50DC),
		HLE_FUNC0(0xBD2F1094, sceKernelLoadExec),
		HLE_FUNC0(0x8ADA38D3, LoadExecForUser_8ADA38D3),
		HLE_FUNC0(0x4AC57943, sceKernelRegisterExitCallback),
		HLE_FUNC0(0x362A956B, LoadExecForUser_362A956B),
		HLE_FUNC0(0x2AC9954B, sceKernelExitGameWithStatus),
		HLE_FUNC0(0x05572A5F, sceKernelExitGame),
	};


	KernelSyscall const ModuleMgrForUser[] =
	{
		HLE_FUNC0(0xFEF27DC1, ModuleMgrForUser_FEF27DC1),
		HLE_FUNC0(0xFBE27467, ModuleMgrForUser_FBE27467),
		HLE_FUNC0(0xF9275D98, sceKernelLoadModuleBufferUsbWlan),
		HLE_FUNC0(0xF2D8D1B4, ModuleMgrForUser_F2D8D1B4),
		HLE_FUNC0(0xF0A26395, sceKernelGetModuleId),
		HLE_FUNC0(0xE4C4211C, ModuleMgrForUser_E4C4211C),
		HLE_FUNC0(0xD8B73127, sceKernelGetModuleIdByAddress),
		HLE_FUNC0(0xD675EBB8, sceKernelSelfStopUnloadModule),
		HLE_FUNC0(0xD2FBC957, sceKernelGetModuleGPByAddress),
		HLE_FUNC0(0xD1FF982A, sceKernelStopModule),
		HLE_FUNC0(0xCC1D3699, sceKernelStopUnloadSelfModule),
		HLE_FUNC0(0xB7F46618, sceKernelLoadModuleByID),
		HLE_FUNC0(0x977DE386, sceKernelLoadModule),
		HLE_FUNC0(0x8F2DF740, ModuleMgrForUser_8F2DF740),
		HLE_FUNC0(0x748CBED9, sceKernelQueryModuleInfo),
		HLE_FUNC0(0x710F61B5, sceKernelLoadModuleMs),
		HLE_FUNC0(0x644395E2, sceKernelGetModuleIdList),
		HLE_FUNC0(0x50F0C1EC, sceKernelStartModule),
		HLE_FUNC0(0x2E0911AA, sceKernelUnloadModule),
		HLE_FUNC0(0x24EC0641, ModuleMgrForUser_24EC0641),
		HLE_FUNC0(0x1196472E, ModuleMgrForUser_1196472E),
	};

	KernelSyscall const scePsmf[] =
	{
		HLE_FUNC0(0xEAED89CD, scePsmfGetNumberOfStreams),
		HLE_FUNC0(0xC7DB3A5B, scePsmfGetCurrentStreamType),
		HLE_FUNC0(0xC22C8327, scePsmfSetPsmf),
		HLE_FUNC0(0xBD8AE0D8, scePsmfGetPresentationEndTime),
		HLE_FUNC0(0xB78EB9E9, scePsmfGetHeaderSize),
		HLE_FUNC0(0xA83F7113, scePsmfGetAudioInfo),
		HLE_FUNC0(0xA5EBFE81, scePsmfGetStreamSize),
		HLE_FUNC0(0x971A3A90, scePsmfCheckEPmap),
		HLE_FUNC0(0x9553CC91, scePsmfQueryStreamSize),
		HLE_FUNC0(0x7C0E7AC3, scePsmfGetEPWithTimestamp),
		HLE_FUNC0(0x76D3AEBA, scePsmfGetPresentationStartTime),
		HLE_FUNC0(0x7491C438, scePsmfGetNumberOfEPentries),
		HLE_FUNC0(0x68D42328, scePsmfGetNumberOfSpecificStreams),
		HLE_FUNC0(0x5F457515, scePsmfGetEPidWithTimestamp),
		HLE_FUNC0(0x5B70FCC1, scePsmfQueryStreamOffset),
		HLE_FUNC0(0x4E624A34, scePsmfGetEPWithId),
		HLE_FUNC0(0x4BC9BDE0, scePsmfSpecifyStream),
		HLE_FUNC0(0x28240568, scePsmfGetCurrentStreamNumber),
		HLE_FUNC0(0x2673646B, scePsmfVerifyPsmf),
		HLE_FUNC0(0x1E6D9013, scePsmfSpecifyStreamWithStreamType),
		HLE_FUNC0(0x0C120E1D, scePsmfSpecifyStreamWithStreamTypeNumber),
		HLE_FUNC0(0x0BA514E5, scePsmfGetVideoInfo),
	};

	KernelSyscall const sceDeflt[] =
	{
		HLE_FUNC0(0xE46EB986, sceZlibIsValid),
		HLE_FUNC0(0xAFE01FD3, sceZlibGetInfo),
		HLE_FUNC0(0x6A548477, sceZlibGetCompressedData),
		HLE_FUNC0(0xA9E4FB28, sceZlibDecompress),
		HLE_FUNC0(0x1B5B82BC, sceGzipIsValid),
		HLE_FUNC0(0x106A3552, sceGzipGetName),
		HLE_FUNC0(0x8AA82C92, sceGzipGetInfo),
		HLE_FUNC0(0x0BA3B9CC, sceGzipGetCompressedData),
		HLE_FUNC0(0xB767F9A0, sceGzipGetComment),
		HLE_FUNC0(0x6DBCF897, sceGzipDecompress),
		HLE_FUNC0(0x44054E03, sceDeflateDecompress),
		HLE_FUNC0(0x2EE39A64, sceZlibAdler32),
	};

	KernelSyscall const scePsmfPlayer[] =
	{
		HLE_FUNC0(0xF8EF08A6, scePsmfPlayerGetCurrentStatus),
		HLE_FUNC0(0xF3EFAA91, scePsmfPlayerGetCurrentPlayMode),
		HLE_FUNC0(0xE792CD94, scePsmfPlayerReleasePsmf),
		HLE_FUNC0(0xDF089680, scePsmfPlayerGetPsmfInfo),
		HLE_FUNC0(0xB9848A74, scePsmfPlayerGetAudioData),
		HLE_FUNC0(0xB8D10C56, scePsmfPlayer_B8D10C56),
		HLE_FUNC0(0xA3D81169, scePsmfPlayerChangePlayMode),
		HLE_FUNC0(0xA0B8CA55, scePsmfPlayerUpdate),
		HLE_FUNC0(0x9FF2B2E7, scePsmfPlayerGetCurrentVideoStream),
		HLE_FUNC0(0x9B71A274, scePsmfPlayerDelete),
		HLE_FUNC0(0x95A84EE5, scePsmfPlayerStart),
		HLE_FUNC0(0x8A9EBDCD, scePsmfPlayer_8A9EBDCD),
		HLE_FUNC0(0x85461EFF, scePsmfPlayer_85461EFF),
		HLE_FUNC0(0x75F03FA2, scePsmfPlayer_75F03FA2),
		HLE_FUNC0(0x68F07175, scePsmfPlayerGetCurrentAudioStream),
		HLE_FUNC0(0x46F61F8B, scePsmfPlayerGetVideoData),
		HLE_FUNC0(0x3ED62233, scePsmfPlayerGetCurrentPts),
		HLE_FUNC0(0x3EA82A4B, scePsmfPlayerGetAudioOutSize),
		HLE_FUNC0(0x3D6D25A9, scePsmfPlayerSetPsmf),
		HLE_FUNC0(0x2BEB1569, scePsmfPlayer_2BEB1569),
		HLE_FUNC0(0x235D8787, scePsmfPlayerCreate),
		HLE_FUNC0(0x1E57A8E7, scePsmfPlayer_1E57A8E7),
		HLE_FUNC0(0x1078C008, scePsmfPlayerStop),
	};

	KernelSyscall const sceLibFont[] =
	{
		HLE_FUNC0(0xF8F0752E, sceFontPixelToPointVFunction),
		HLE_FUNC0(0x74B21701, sceFontPixelToPointHFunction),
		HLE_FUNC0(0x3C4B7E82, sceFontPointToPixelVFunction),
		HLE_FUNC0(0x681E61A7, sceFontFindFontFunction),
		HLE_FUNC0(0x57FCB733, sceFontOpenUserFileFunction),
		HLE_FUNC0(0x02D7F94B, sceFontFlushFunction),
		HLE_FUNC0(0x48293280, sceFontSetResolutionFunction),
		HLE_FUNC0(0x5333322D, sceFontGetFontInfoByIndexNumberFunction),
		HLE_FUNC0(0x472694CD, sceFontPointToPixelHFunction),
		HLE_FUNC0(0x5C3E4A9E, sceFontGetCharImageRectFunction),
		HLE_FUNC0(0xEE232411, sceFontSetAltCharacterCodeFunction),
		HLE_FUNC0(0xBB8E7FE6, sceFontOpenUserMemoryFunction),
		HLE_FUNC0(0xBC75D85B, sceFontGetFontListFunction),
		HLE_FUNC0(0x27F6E642, sceFontGetNumFontListFunction),
		HLE_FUNC0(0x980F4895, sceFontGetCharGlyphImageFunction),
		HLE_FUNC0(0xDCC80C2F, sceFontGetCharInfoFunction),
		HLE_FUNC0(0xCA1E6945, sceFontGetCharGlyphImage_ClipFunction),
		HLE_FUNC0(0xA834319D, sceFontOpenFunction),
		HLE_FUNC0(0x67F17ED7, sceFontNewLibFunction),
		HLE_FUNC0(0x574B6FBC, sceFontDoneLibFunction),
		HLE_FUNC0(0x3AEA8CB6, sceFontCloseFunction),
		HLE_FUNC0(0xDA7535E, sceFontGetFontInfoFunction),
		HLE_FUNC0(0x99EF33C, sceFontFindOptimumFontFunction),
	};

	KernelSyscall const sceMp3[] =
	{
		HLE_FUNC0(0xF5478233, sceMp3ReleaseMp3Handle),
		HLE_FUNC0(0xD8F54A51, sceMp3GetLoopNum),
		HLE_FUNC0(0xD0A56296, sceMp3CheckStreamDataNeeded),
		HLE_FUNC0(0xD021C0FB, sceMp3Decode),
		HLE_FUNC0(0xA703FE0F, sceMp3GetInfoToAddStreamData),
		HLE_FUNC0(0x8F450998, sceMp3GetSamplingRate),
		HLE_FUNC0(0x8AB81558, sceMp3StartEntry),
		HLE_FUNC0(0x87C263D1, sceMp3GetMaxOutputSample),
		HLE_FUNC0(0x87677E40, sceMp3GetBitRate),
		HLE_FUNC0(0x7F696782, sceMp3GetMp3ChannelNum),
		HLE_FUNC0(0x732B042A, sceMp3EndEntry),
		HLE_FUNC0(0x44E07129, sceMp3Init),
		HLE_FUNC0(0x3CEF484F, sceMp3SetLoopNum),
		HLE_FUNC0(0x3C2FA058, sceMp3TermResource),
		HLE_FUNC0(0x35750070, sceMp3InitResource),
		HLE_FUNC0(0x354D27EA, sceMp3GetSumDecodedSample),
		HLE_FUNC0(0x2A368661, sceMp3ResetPlayPosition),
		HLE_FUNC0(0x0DB149F4, sceMp3NotifyAddStreamData),
		HLE_FUNC0(0x07EC321A, sceMp3ReserveMp3Handle),
	};


///////////////ABOVE HERE EVERYTHING NEEDS TO BE RECHECKED!!! (shadow)///////////////////////////////////
    using namespace hle;

	KernelSyscall const ThreadManForUser[] = 
	{
		{0x55C20A00, hle::sceKernelCreateEventFlag, "sceKernelCreateEventFlag"},
		{0x812346E4, hle::sceKernelClearEventFlag,  "sceKernelClearEventFlag"},
		{0xEF9E4C70, hle::sceKernelDeleteEventFlag, "sceKernelDeleteEventFlag"},
		{0x1FB15A32, hle::sceKernelSetEventFlag,    "sceKernelSetEventFlag"},
		{0x402FCF22, hle::sceKernelWaitEventFlag,   "sceKernelWaitEventFlag"},
		{0x328C546A, hle::sceKernelWaitEventFlagCB, "sceKernelWaitEventFlagCB"},
		{0x30FD48F0, hle::sceKernelPollEventFlag,   "sceKernelPollEventFlag"},
		{0xCD203292, hle::sceKernelCancelEventFlag, "sceKernelCancelEventFlag"},
		{0xA66B0120, hle::sceKernelReferEventFlagStatus,"sceKernelReferEventFlagStatus"},

		{0x8FFDF9A2, hle::sceKernelCancelSema,    "sceKernelCancelSema"},
		{0xD6DA4BA1, hle::sceKernelCreateSema,    "sceKernelCreateSema"}, //(const char *s, int flg, int val, int max, const void *p); 
		{0x28B6489C, hle::sceKernelDeleteSema,    "sceKernelDeleteSema"}, //(int id)	
		{0x58B1F937, hle::sceKernelPollSema,      "sceKernelPollSema"}, //(int id, int count); 
		{0xBC6FEBC5, hle::sceKernelReferSemaStatus,"sceKernelReferSemaStatus"},
		{0x3F53E640, hle::sceKernelSignalSema,    "sceKernelSignalSema"},
		{0x4E3A1105, hle::sceKernelWaitSema,      "sceKernelWaitSema"},
		{0x6D212BAC, hle::sceKernelWaitSemaCB,     "sceKernelWaitSemaCB"},

		{0x7e65b999,0,"sceKernelCancelAlarm"},

		{0xFCCFAD26,0,"sceKernelCancelWakeupThread"},
		{0xea748e31,hle::sceKernelChangeCurrentThreadAttr,"sceKernelChangeCurrentThreadAttr"},
		{0x71bc9871,hle::sceKernelChangeThreadPriority,"sceKernelChangeThreadPriority"},
		{0x446D8DE6,hle::sceKernelCreateThread,"sceKernelCreateThread"},
		{0x9fa03cd3,hle::sceKernelDeleteThread,"sceKernelDeleteThread"},
		{0xBD123D9E,0,"sceKernelDelaySysClockThread"},
		{0x1181E963,0,"sceKernelDelaySysClockThreadCB"},
		{0xceadeb47,hle::sceKernelDelayThread,"sceKernelDelayThread"},
		{0x68da9e36,hle::sceKernelDelayThreadCB,"sceKernelDelayThreadCB"},
		{0xaa73c935,hle::sceKernelExitThread,"sceKernelExitThread"},
		{0x809ce29b,hle::sceKernelExitDeleteThread,"sceKernelExitDeleteThread"},
		{0x94aa61ee,0,"sceKernelGetThreadCurrentPriority"},
		{0x293b45b8,hle::sceKernelGetThreadId,"sceKernelGetThreadId"},
		{0x3B183E26,0,"sceKernelGetThreadExitStatus"},
		{0x52089CA1,0,"sceKernelGetThreadStackFreeSize"},
		{0xFFC36A14,0,"sceKernelReferThreadRunStatus"},
		{0x17c1684e,hle::sceKernelReferThreadStatus,"sceKernelReferThreadStatus"},
		{0x2C34E053,0,"sceKernelReleaseWaitThread"},
		{0x75156e8f,hle::sceKernelResumeThread,"sceKernelResumeThread"},
		{0x27e22ec2,0,"sceKernelResumeDispatchThread"},
		{0x912354a7,hle::sceKernelRotateThreadReadyQueue,"sceKernelRotateThreadReadyQueue"},
		{0x9ACE131E,hle::sceKernelSleepThread,"sceKernelSleepThread"},
		{0x82826f70,hle::sceKernelSleepThreadCB,"sceKernelSleepThreadCB"},
		{0xF475845D,hle::sceKernelStartThread,"sceKernelStartThread"},
		{0x9944f31f,hle::sceKernelSuspendThread,"sceKernelSuspendThread"},
		{0x3ad58b8c,0,"sceKernelSuspendDispatchThread"},
		{0x616403ba,hle::sceKernelTerminateThread,"sceKernelTerminateThread"},
		{0x383f7bcc,hle::sceKernelTerminateDeleteThread,"sceKernelTerminateDeleteThread"},
		{0x840E8133,0,"sceKernelWaitThreadEndCB"},


		{0x94416130,0,"sceKernelGetThreadmanIdList"},
		{0x57CF62DD,0,"sceKernelGetThreadmanIdType"},

		{0xD2D615EF,0,"sceKernelCancelVTimerHandler"},
		{0x20fff560,0,"sceKernelCreateVTimer"},
		{0x328F9E52,0,"sceKernelDeleteVTimer"},
		{0xB3A59970,0,"sceKernelGetVTimerBase"},
		{0xB7C18B77,0,"sceKernelGetVTimerBaseWide"},
		{0x034A921F,0,"sceKernelGetVTimerTime"},
		{0xC0B3FFD2,0,"sceKernelGetVTimerTimeWide"},
		{0x5F32BEAA,0,"sceKernelReferVTimerStatus"},
		{0x542AD630,0,"sceKernelSetVTimerTime"},
		{0xFB6425C3,0,"sceKernelSetVTimerTimeWide"},
		{0xd8b299ae,0,"sceKernelSetVTimerHandler"},
		{0x53B00E9A,0,"sceKernelSetVTimerHandlerWide"},
		{0xc68d9437,0,"sceKernelStartVTimer"},

		{0xd13bde95,hle::sceKernelCheckThreadStack,"sceKernelCheckThreadStack"},
		{0x349d6d6c,hle::sceKernelCheckCallback,"sceKernelCheckCallback"},
		{0xE81CAF8F,hle::sceKernelCreateCallback,"sceKernelCreateCallback"},

        HLE_FUNC1(0xDB738F35, sceKernelGetSystemTime, "err:x,,,,sysclk:{val:8u}/sysclk:x"),
        HLE_FUNC1(0x82BC5777, sceKernelGetSystemTimeWide, "err:x/sysclk.lo:x, sysclk.hi:x,usec:x,sec:x"),
		HLE_FUNC1(0x369ED59D, sceKernelGetSystemTimeLow, "usec:u/"),
		HLE_FUNC0(0xBA6B92E2, sceKernelSysClock2USec),
		HLE_FUNC0(0xE1619D7C, sceKernelSysClock2USecWide),
		HLE_FUNC0(0x110DEC9A, sceKernelUSec2SysClock),
		HLE_FUNC0(0xC8CD158C, sceKernelUSec2SysClockWide),

		{0xDAA3F564,0,"sceKernelReferAlarmStatus"},
		{0x8218B4DD,0,"sceKernelReferGlobalProfiler"},
		{0x627E6F3A,0,"sceKernelReferSystemStatus"},
		{0x64D4540E,0,"sceKernelReferThreadProfiler"},

		{0x6652b8ca,0,"sceKernelSetAlarm"},
		{0xD0AEEE87,0,"sceKernelStopVTimer"},
		{0xB2C25152,0,"sceKernelSetSysClockAlarm"},

		{0x278C0DF5,hle::sceKernelWaitThreadEnd,"sceKernelWaitThreadEnd"},
		{0xd59ead2f,hle::sceKernelWakeupThread,"sceKernelWakeupThread"}, //AI Go, audio?

		{0x0C106E53,0,"sceKernelRegisterThreadEventHandler"},
		{0x72F3C145,0,"sceKernelReleaseThreadEventHandler"},
		{0x369EEB6B,0,"sceKernelReferThreadEventHandlerStatus"},

		{0xEDBA5844,hle::sceKernelDeleteCallback,"sceKernelDeleteCallback"},
		{0xC11BA8C4,hle::sceKernelNotifyCallback,"sceKernelNotifyCallback"},
		{0xBA4051D6,0,"sceKernelCancelCallback"},
		{0x2A3D44FF,0,"sceKernelGetCallbackCount"},
		{0x349D6D6C,0,"sceKernelCheckCallback"},
		{0x730ED8BC,0,"sceKernelReferCallbackStatus"},

		{0x8125221D,0,"sceKernelCreateMbx"},
		{0x86255ADA,0,"sceKernelDeleteMbx"},
		{0xE9B3061E,0,"sceKernelSendMbx"},
		{0x18260574,0,"sceKernelReceiveMbx"},
		{0xF3986382,0,"sceKernelReceiveMbxCB"},
		{0x0D81716A,0,"sceKernelPollMbx"},
		{0x87D4DD36,0,"sceKernelCancelReceiveMbx"},
		{0xA8E8C846,0,"sceKernelReferMbxStatus"},

		{0x7C0DC2A0,0,"sceKernelCreateMsgPipe"},
		{0xF0B7DA1C,0,"sceKernelDeleteMsgPipe"},
		{0x876DBFAD,0,"sceKernelSendMsgPipe"},
		{0x7C41F2C2,0,"sceKernelSendMsgPipeCB"},
		{0x884C9F90,0,"sceKernelTrySendMsgPipe"},
		{0x74829B76,0,"sceKernelReceiveMsgPipe"},
		{0xFBFA697D,0,"sceKernelReceiveMsgPipeCB"},
		{0xDF52098F,0,"sceKernelTryReceiveMsgPipe"},
		{0x349B864D,0,"sceKernelCancelMsgPipe"},
		{0x33BE4024,0,"sceKernelReferMsgPipeStatus"},

        HLE_FUNC1(0x56C039B5, sceKernelCreateVpl, "id:x,,,,,,,,param:{align:x}/name:s,pid:x,attr:x,size:u,param:x"),
        HLE_FUNC1(0x89B3D48C, sceKernelDeleteVpl, "err:x/id:x"),
        HLE_FUNC1(0xBED27435, sceKernelAllocateVpl, "err:x,,,,,,addr:{val:x},timeout:{val:8u}/id:x,size:u,ptr:x,timeout:x"),
		HLE_FUNC1(0xEC0A693F, sceKernelAllocateVplCB, "err:x,,,,,,addr:{val:x},timeout:{val:8u}/id:x,size:u,addr:x,timeout:x"),
		HLE_FUNC1(0xAF36D708, sceKernelTryAllocateVpl, "err:x,,,,,,addr:{val:x}/id:x,size:u,addr:x"),
        HLE_FUNC1(0xB736E9FF, sceKernelFreeVpl, "err:x/id:x,addr:x"),
		HLE_FUNC1(0x1D371B8A, sceKernelCancelVpl, "err:x/id:x,waiting:u"),
        HLE_FUNC1(0x39810265, sceKernelReferVplStatus, "err:x,,,, info:{}/id:x,info:x"),

        HLE_FUNC1(0xC07BB470, sceKernelCreateFpl, "id:x,,,,,,,,,,param:{align:x}/name:s,pid:x,attr:x,size:u,count:u,param:x"),
		HLE_FUNC1(0xED1410E0, sceKernelDeleteFpl, "err:x/id:x"),
		HLE_FUNC1(0xD979E9BF, sceKernelAllocateFpl, "err:x,,,,,addr:{val:x},timeout:{val:8u}/id:x,addr:x,timeout:x"),
		HLE_FUNC1(0xE7282CB6, sceKernelAllocateFplCB, "err:x,,,,,addr:{val:x},timeout:{val:8u}/id:x,addr:x,timeout:x"),
		HLE_FUNC1(0x623AE665, sceKernelTryAllocateFpl, "err:x,,,,,addr:{val:x}/id:x,addr:x"),
        HLE_FUNC1(0xF6414A71, sceKernelFreeFpl, "err:x/id:x,addr:x"),
		HLE_FUNC1(0xA8AA591F, sceKernelCancelFpl, "err:x/id:x,waiting:u"),
		HLE_FUNC1(0xD8199E4C, sceKernelReferFplStatus, "err:x/id:x,info:x"),

		{0x0E927AED, 0, "_sceKernelReturnFromTimerHandler"},
		{0x532A522E, hle::_sceKernelExitThread, "_sceKernelExitThread"},
		{0x6E9EA350, hle::_sceKernelReturnFromCallback, "_sceKernelReturnFromCallback"},
		{0xf8170fbe, 0, "sceKernelThreadMan_f8170fbe"},
		{0x5bf4dd27, 0, "sceKernelThreadMan_5bf4dd27"}, //f(ptr, 1)
		{0x6b30100f, 0, "sceKernelThreadMan_6b30100f"}, //f(ptr)
		{0xb7d098c6, 0, "sceKernelThreadMan_b7d098c6"}, //x=f("GlobalHeaps Main Lock",0,0,0)

        HLE_FUNC0(0xC0DE0000, _sceKernelStartThread),
        HLE_FUNC0(0xC0DE0001, _sceKernelExitThread),
	};

    KernelSyscall const FakeSysCalls[] =
    {
        {0xC0DEBABE, hle::_sceKernelReturnFromThread, "_sceKernelReturnFromThread"},
        {0xC1DEBABE, hle::_sceKernelIdleThread,       "_sceKernelIdleThread"}
    };

    KernelSyscall const sceNet[] =
    {
        //{0x39AF39A6, hle::_sceKernelReturnFromThread, "sceNetInitFunction"             },
        //{0x281928A9, hle::_sceKernelReturnFromThread, "sceNetTermFunction"             },
        {0x50647530, hle::_sceKernelReturnFromThread, "sceNetFreeThreadinfoFunction"   },
        {0xAD6844c6, hle::_sceKernelReturnFromThread, "sceNetThreadAbortFunction"      },
        {0x89360950, hle::_sceKernelReturnFromThread, "sceNetEtherNtostrFunction"      },
        {0xD27961C9, hle::_sceKernelReturnFromThread, "sceNetEtherStrtonFunction"      },
        {0xF5805EFE, hle::_sceKernelReturnFromThread, "sceNetHtonlFunction"            },
        {0x39C1BF02, hle::_sceKernelReturnFromThread, "sceNetHtonsFunction"            },
        {0x93C4AF7E, hle::_sceKernelReturnFromThread, "sceNetNtohlFunction"            },
        {0x4CE03207, hle::_sceKernelReturnFromThread, "sceNetNtohsFunction"            },
        {0x0BF0A3AE, hle::_sceKernelReturnFromThread, "sceNetGetLocalEtherAddrFunction"},
        {0xCC393E48, hle::_sceKernelReturnFromThread, "sceNetGetMallocStatFunction"    }
    };


    typedef struct { char const *name; u16 version; KernelSyscall const *syscall_array; u32 syscall_count; bool (*reboot)(); bool (*shutdown)(); } KernelSyscallsEntry;

#define HLE_MOD(n) { #n, 0x8FFF, syscalls::n, sizeof(syscalls::n)/sizeof(KernelSyscall), &n::Reboot, &n::ShutDown }  
    KernelSyscallsEntry theKernelSyscalls[] =
    {
        HLE_MOD(SysMemUserForUser),
        HLE_MOD(InterruptManager),
        HLE_MOD(ThreadManForUser),
        HLE_MOD(Kernel_Library),
        HLE_MOD(LoadExecForUser),
        HLE_MOD(ModuleMgrForUser),
        HLE_MOD(IoFileMgrForUser),
        HLE_MOD(sceCtrl),
        HLE_MOD(sceDmac),
        HLE_MOD(sceDisplay),
        HLE_MOD(sceGe_user),
        HLE_MOD(sceUtility),
        HLE_MOD(scePower),
        HLE_MOD(sceRtc),
        HLE_MOD(sceSuspendForUser),
        HLE_MOD(sceImpose),
        HLE_MOD(sceMpeg),
        HLE_MOD(StdioForUser),
        HLE_MOD(sceUmdUser),
        HLE_MOD(sceAtrac3plus),
        HLE_MOD(sceAudio),
        HLE_MOD(sceSasCore),
        HLE_MOD(UtilsForUser),
        //{ "sceNet", 0x8FFF, syscalls::sceNet, sizeof(syscalls::sceNet)/sizeof(KernelSyscall), 0, 0 },
        HLE_MOD(scePsmf),
		//HLE_MOD(sceDeflt), 
#if 0
		HLE_MOD(sceLibFont),
#endif
		HLE_MOD(scePsmfPlayer)
		//HLE_MOD(sceMp3)
    };
#undef HLE_MOD

    bool Reboot()
    {
        theKernelModuleManager.CreateSyscallsModule("FakeSysCalls", 0x8FFF, syscalls::FakeSysCalls, sizeof(syscalls::FakeSysCalls)/sizeof(KernelSyscall));

        u64 mask = (1 << sizeof(theKernelSyscalls)/sizeof(*theKernelSyscalls)) - 1;

        while (mask)
        {
            
            for (u32 n = sizeof(theKernelSyscalls)/sizeof(*theKernelSyscalls), i = 0; i < n; ++i)
            {
                if (mask & (1ULL << i))
                {
                    if (!theKernelSyscalls[i].reboot || (*theKernelSyscalls[i].reboot)())
                    {
                        theKernelModuleManager.CreateSyscallsModule(
                            theKernelSyscalls[i].name,
                            theKernelSyscalls[i].version,
                            theKernelSyscalls[i].syscall_array,
                            theKernelSyscalls[i].syscall_count);
                        mask &= ~(1ULL << i);
                    }
                    else
                    {
                        struct { char const *name; u16 version; KernelSyscall const *syscall_array; u32 syscall_count; bool (*reboot)(); bool (*shutdown)(); } temp;
                        ::memcpy(&temp, &theKernelSyscalls[i], sizeof(*theKernelSyscalls));
                        if (i < n - 1)
                        {
                            ::memcpy(&theKernelSyscalls[i], &theKernelSyscalls[i + 1], (n - 1 - i)*sizeof(*theKernelSyscalls));
                            ::memcpy(&theKernelSyscalls[n - 1], &temp, sizeof(*theKernelSyscalls));
                        }
                    }
                }
            }
        }
        return true;
    };

    bool ShutDown()
    {
        for (u32 n = sizeof(theKernelSyscalls)/sizeof(*theKernelSyscalls), i = 0; i < n; ++i)
        {
            if (!theKernelSyscalls[n - 1 - i].shutdown || (*theKernelSyscalls[n - 1 - i].shutdown)())
            {
                theKernelModuleManager.DeleteSyscallsModule(theKernelSyscalls[n - 1 - i].name);
            }
        }
        theKernelModuleManager.Clear();
        return true;
    };
}
