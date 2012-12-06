#ifndef sceRtc_h__
#define sceRtc_h__

namespace sceRtc
{
    extern bool Reboot();
    extern bool ShutDown();

    u64 CurrentTimeMicroSeconds();

	extern int sceRtcRegisterCallback(); 
	extern int sceRtc_F5FCC995(); 
	extern int sceRtcTickAddSeconds(); 
	extern int sceRtcSetDosTime(); 
	extern int sceRtcGetCurrentClockLocalTime(); 
	extern int sceRtcTickAddMinutes(); 
	extern int sceRtcTickAddDays(); 
	extern int sceRtcGetTime64_t(); 
	extern int sceRtcParseDateTime(); 
	extern int sceRtcTickAddMonths(); 
	extern int sceRtcGetWin32FileTime(); 
	extern int sceRtcTickAddWeeks(); 
	extern int sceRtcFormatRFC2822(); 
	extern int sceRtcGetTickResolution(); 
	extern int sceRtc_C2DDBEB5(); 
	extern int sceRtc_A93CF7D8(); 
	extern int sceRtcCompareTick(); 
	extern int sceRtcIsAlarmed(); 
	extern int sceRtcSetTick(); 
	extern int sceRtcFormatRFC2822LocalTime(); 
	extern int sceRtc_7D1FBED3(); 
	extern int sceRtcSetWin32FileTime(); 
	extern int sceRtcConvertLocalTimeToUTC(); 
	extern int sceRtcGetTick(); 
	extern int sceRtcUnregisterCallback(); 
	extern int sceRtcGetLastAdjustedTime(); 
	extern int sceRtcGetDayOfWeek(); 
	extern int sceRtcGetCurrentClock(); 
	extern int sceRtcCheckValid(); 
	extern int sceRtcTickAddTicks(); 
	extern int sceRtcTickAddYears(); 
	extern int sceRtcIsLeapYear(); 
	extern int sceRtcGetCurrentTick(); 
	extern int sceRtcSetTime_t(); 
	extern int sceRtcGetDosTime(); 
	extern int sceRtcConvertUtcToLocalTime(); 
	extern int sceRtcParseRFC3339(); 
	extern int sceRtcFormatRFC3339LocalTime(); 
	extern int sceRtcGetTime_t(); 
	extern int sceRtcTickAddHours(); 
	extern int sceRtcTickAddMicroseconds(); 
	extern int sceRtcGetLastReincarnatedTime(); 
	extern int sceRtcSetTime64_t(); 
	extern int sceRtcGetDaysInMonth(); 
	extern int sceRtcFormatRFC3339(); 
	extern int sceRtcGetAccumlativeTime(); 
	extern u64 sceRtcGetAccumulativeTime(); 
}
#endif // sceRtc_h__
