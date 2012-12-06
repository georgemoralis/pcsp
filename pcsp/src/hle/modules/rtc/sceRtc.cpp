#include "stdafx.h"
#include "common_base.h"
#include "sceRtc.h"
#include "hle/types.h"
#include "log.h"

namespace sceRtc
{
    static bool sceRtc_ready = false;

    struct ScePspDateTime 
    {
        u32 year;
        u32 month;
        u32 day;
        u32 hour;
        u32 minute;
        u32 second;
        u32 microsecond;
    };

    bool Reboot()
    {
        ShutDown();
        sceRtc_ready = true;
        return true;
    }
    bool ShutDown()
    {
        if (sceRtc_ready)
        {
            sceRtc_ready = false;
        }
        return true;
    }


    /// Current Time Acquisition Functions
    //////////////////////////////////////

    static __forceinline u64 CurrentTimeMicroSeconds()
    {
        static Timer Timer;
        return Timer.Get();
    }

    int sceRtcGetCurrentTick(u32 a0)
    {
        if (a0)
        {
            u64 *tickpos = Memory::addr< u64 >(a0);
            u64  tick    = CurrentTimeMicroSeconds();

            *tickpos = tick;

            return 0;
        }

        return SCE_ERROR_INVALID_POINTER;
    }

    int sceRtcGetCurrentClock()
    {
        //TODO implement me
        errorf(sceRtc, "UNIMPLEMENTED sceRtcGetCurrentClock function");
        return 0;
    }

    int sceRtcGetCurrentClockLocalTime()
    {
        //TODO implement me
        errorf(sceRtc, "UNIMPLEMENTED sceRtcGetCurrentClockLocalTime function");
        return 0;
    }


    /// RTC ALarm Setting Functions
    ///////////////////////////////

    int sceRtcIsAlarmed()
    {
        //TODO implement me
        errorf(sceRtc, "UNIMPLEMENTED sceRtcIsAlarmed function");
        return 0;
    }

    int sceRtcRegisterCallback()
    {
        //TODO implement me
        errorf(sceRtc, "UNIMPLEMENTED sceRtcRegisterCallback function");
        return 0;
    }

    int sceRtcUnregisterCallback()
    {
        //TODO implement me
        errorf(sceRtc, "UNIMPLEMENTED sceRtcUnregisterCallback function");
        return 0;
    }


    /// Accumulative Time Retrieval Functions
    /////////////////////////////////////////
    
    /*
        returns the time in ticks since the battery has been shut off
    */
    u64 sceRtcGetAccumulativeTime()
    {
        return CurrentTimeMicroSeconds();
    }

    int sceRtcGetLastReincarnatedTime()
    {
        //TODO implement me
        errorf(sceRtc, "UNIMPLEMENTED sceRtcGetLastReincarnatedTime function");
        return 0;
    }

    int sceRtcGetLastAdjustedTime()
    {
        //TODO implement me
        errorf(sceRtc, "UNIMPLEMENTED sceRtcGetLastAdjustedTime function");
        return 0;
    }


    /// Formatting Functions
    ////////////////////////

    int sceRtcFormatRFC2822()
    {
        //TODO implement me
        errorf(sceRtc, "UNIMPLEMENTED sceRtcFormatRFC2822 function");
        return 0;
    }

    int sceRtcFormatRFC2822LocalTime()
    {
        //TODO implement me
        errorf(sceRtc, "UNIMPLEMENTED sceRtcFormatRFC2822LocalTime function");
        return 0;
    }

    int sceRtcFormatRFC3339()
    {
        //TODO implement me
        errorf(sceRtc, "UNIMPLEMENTED sceRtcFormatRFC3339 function");
        return 0;
    }

    int sceRtcFormatRFC3339LocalTime()
    {
        //TODO implement me
        errorf(sceRtc, "UNIMPLEMENTED sceRtcFormatRFC3339LocalTime function");
        return 0;
    }

    int sceRtcParseDateTime()
    {
        //TODO implement me
        errorf(sceRtc, "UNIMPLEMENTED sceRtcParseDateTime function");
        return 0;
    }

    int sceRtcParseRFC3339()
    {
        //TODO implement me
        errorf(sceRtc, "UNIMPLEMENTED sceRtcParseRFC3339 function");
        return 0;
    }


    /// Tick Manipulation Functions
    ///////////////////////////////

#define PSP_TIME_SECONDS_IN_MICROSECOND 1ULL
#define PSP_TIME_SECONDS_IN_SECOND      1000000ULL  * PSP_TIME_SECONDS_IN_MICROSECOND
#define PSP_TIME_SECONDS_IN_MINUTE      60ULL       * PSP_TIME_SECONDS_IN_SECOND
#define PSP_TIME_SECONDS_IN_HOUR        60ULL       * PSP_TIME_SECONDS_IN_MINUTE
#define PSP_TIME_SECONDS_IN_DAY         24ULL       * PSP_TIME_SECONDS_IN_HOUR
#define PSP_TIME_SECONDS_IN_WEEK        7ULL        * PSP_TIME_SECONDS_IN_DAY
#define PSP_TIME_SECONDS_IN_MONTH       2629743ULL  * PSP_TIME_SECONDS_IN_SECOND
#define PSP_TIME_SECONDS_IN_YEAR        31556926ULL * PSP_TIME_SECONDS_IN_SECOND

    template< u64 unit >
    static __forceinline u32 RtcTickAdd64(u64 multiplier, u32 src_addr, u32 dst_addr) 
    {		
        if (src_addr && dst_addr) 
        {
            u64 *src = Memory::addr< u64 >(src_addr);
            u64 *dst = Memory::addr< u64 >(dst_addr);
            *dst = *src + multiplier * unit;
            return SCE_OK;
        } 
        else 
        {
            return SCE_ERROR_INVALID_POINTER;
        }
    }

    int sceRtcGetTick()
    {
        //TODO implement me
        errorf(sceRtc, "UNIMPLEMENTED sceRtcGetTick function");
        return 0;
    }

    int sceRtcSetTick()
    {
        //TODO implement me
        errorf(sceRtc, "UNIMPLEMENTED sceRtcSetTick function");
        return 0;
    }

    int sceRtcTickAddTicks(u32 a0, u32 a1, u64 a3a2)
    {
        return RtcTickAdd64< PSP_TIME_SECONDS_IN_MICROSECOND >(a3a2, a0, a1);
    }

    int sceRtcTickAddMicroseconds(u32 a0, u32 a1, u64 a3a2)
    {
        return RtcTickAdd64< PSP_TIME_SECONDS_IN_MICROSECOND >(a3a2, a0, a1);
    }

    int sceRtcTickAddSeconds(u32 a0, u32 a1, u64 a3a2)
    {
        return RtcTickAdd64< PSP_TIME_SECONDS_IN_SECOND >(a3a2, a0, a1);
    }
    
    int sceRtcTickAddMinutes(u32 a0, u32 a1, u64 a3a2)
    {
        return RtcTickAdd64< PSP_TIME_SECONDS_IN_MINUTE >(a3a2, a0, a1);
    }

    int sceRtcTickAddHours(u32 a0, u32 a1, u64 a3a2)
    {
        return RtcTickAdd64< PSP_TIME_SECONDS_IN_HOUR >(a3a2, a0, a1);
    }

    int sceRtcTickAddDays(u32 a0, u32 a1, u64 a3a2)
    {
        return RtcTickAdd64< PSP_TIME_SECONDS_IN_DAY >(a3a2, a0, a1);
    }

    int sceRtcTickAddWeeks(u32 a0, u32 a1, u64 a3a2)
    {
        return RtcTickAdd64< PSP_TIME_SECONDS_IN_WEEK >(a3a2, a0, a1);
    }

    int sceRtcTickAddMonths(u32 a0, u32 a1, u64 a3a2)
    {
        return RtcTickAdd64< PSP_TIME_SECONDS_IN_MONTH >(a3a2, a0, a1);
    }

    int sceRtcTickAddYears(u32 a0, u32 a1, u64 a3a2)
    {
        return RtcTickAdd64< PSP_TIME_SECONDS_IN_YEAR >(a3a2, a0, a1);
    }

    int sceRtcConvertUtcToLocalTime()
    {
        //TODO implement me
        errorf(sceRtc, "UNIMPLEMENTED sceRtcConvertUtcToLocalTime function");
        return 0;
    }

    int sceRtcConvertLocalTimeToUTC()
    {
        //TODO implement me
        errorf(sceRtc, "UNIMPLEMENTED sceRtcConvertLocalTimeToUTC function");
        return 0;
    }

    /// Format Conversion Functions
    ///////////////////////////////

    static __forceinline ScePspDateTime Dos2PspDateTime(u32 in_time) 
    {
        ScePspDateTime time;

        u64 milliseconds = in_time / 10000;

        u64 years = milliseconds / (365 * 60 * 60 * 1000);
        milliseconds -= years * (365 * 60 * 60 * 1000);

        u64 days = milliseconds / (24 * 60 * 60 * 1000);
        milliseconds -= days * (24 * 60 * 60 * 1000);

        u64 hours = milliseconds / (60 * 60 * 1000);
        milliseconds -= hours * (60 * 60 * 1000);

        u64 minutes = milliseconds / (60 * 1000);
        milliseconds -= minutes * (60 * 1000);

        u64 seconds = milliseconds / 1000;
        milliseconds -= seconds * 1000;

        time.microsecond = milliseconds * 1000;
        time.second      = seconds;
        time.minute      = minutes;
        time.hour        = hours;
        time.day         = days;
        time.year        = 1980 + years;

        return time;
    }

    inline void WritePspDateTime(ScePspDateTime pdt, u32 address) 
    {
        Memory::mem< u16 >(address +  0) = u16(pdt.year   & 0xFFFF);
        Memory::mem< u16 >(address +  2) = u16(pdt.month  & 0xFFFF);
        Memory::mem< u16 >(address +  4) = u16(pdt.day    & 0xFFFF);
        Memory::mem< u16 >(address +  8) = u16(pdt.hour   & 0xFFFF);
        Memory::mem< u16 >(address + 10) = u16(pdt.minute & 0xFFFF);
        Memory::mem< u16 >(address + 12) = u16(pdt.second & 0xFFFF);
    }

    int sceRtcGetDosTime()
    {
        //TODO implement me
        errorf(sceRtc, "UNIMPLEMENTED sceRtcGetDosTime function");
        return 0;
    }

    int sceRtcGetTime_t()
    {
        //TODO implement me
        errorf(sceRtc, "UNIMPLEMENTED sceRtcGetTime_t function");
        return 0;
    }

    int sceRtcGetTime64_t()
    {
        //TODO implement me
        errorf(sceRtc, "UNIMPLEMENTED sceRtcGetTime64_t function");
        return 0;
    }

    int sceRtcGetWin32FileTime()
    {
        //TODO implement me
        errorf(sceRtc, "UNIMPLEMENTED sceRtcGetWin32FileTime function");
        return 0;
    }

    int sceRtcSetDosTime(u32 a0, u32 a1)
    {
        /*
            Any game that uses this ??
        */
        
        u32 date_addr = a0;
        u32 time      = a1;

        if (date_addr) 
        {	
            ScePspDateTime t = Dos2PspDateTime(time);
            WritePspDateTime(t, date_addr);
            return 0;
        } 
        else 
        {
            errorf(sceRtc, "sceRtcSetDosTime bad address");
            return -1;
        }
    }

    int sceRtcSetTime_t()
    {
        //TODO implement me
        errorf(sceRtc, "UNIMPLEMENTED sceRtcSetTime_t function");
        return 0;
    }

    int sceRtcSetTime64_t()
    {
        //TODO implement me
        errorf(sceRtc, "UNIMPLEMENTED sceRtcSetTime64_t function");
        return 0;
    }

    int sceRtcSetWin32FileTime()
    {
        //TODO implement me
        errorf(sceRtc, "UNIMPLEMENTED sceRtcSetWin32FileTime function");
        return 0;
    }


    /// Miscellaneous functions
    ///////////////////////////

    int sceRtcIsLeapYear(u32 a0)
    {
        int year = a0;
        return ((year % 4 == 0) && (year % 100 != 0) || (year % 400 == 0));
    }

    int sceRtcGetDaysInMonth()
    {
        //TODO implement me
        errorf(sceRtc, "UNIMPLEMENTED sceRtcGetDaysInMonth function");
        return 0;
    }

    int sceRtcGetDayOfWeek()
    {
        //TODO implement me
        errorf(sceRtc, "UNIMPLEMENTED sceRtcGetDayOfWeek function");
        return 0;
    }

    int sceRtcCheckValid(u32 a0)
    {
        //TODO implement me
        errorf(sceRtc, "UNIMPLEMENTED sceRtcCheckValid function");
        return 0;
    }


    /// where did they come from ???
    ////////////////////////////////

    int sceRtcGetTickResolution()
    {
        // the resolution is microseconds
        return 1000000; 
    }

    int sceRtcCompareTick(u32 a0, u32 a1)
    {
        if (a0 && a1) 
        {
            u64 *tick1 = Memory::addr< u64 >(a0);
            u64 *tick2 = Memory::addr< u64 >(a1);

            return (*tick1 == *tick2) ? 0 : (*tick1 < *tick2) ? -1 : +1;
        } 
        else 
        {
            return SCE_ERROR_INVALID_POINTER;
        }
    }

    /*
        returns the time in ticks since the battery has been shut off
    */
    int sceRtcGetAccumlativeTime()
    {
        return CurrentTimeMicroSeconds();
    }

    /// Which Category ???
    //////////////////////

    int sceRtc_C2DDBEB5()
    {
        //TODO implement me
        errorf(sceRtc, "UNIMPLEMENTED sceRtc_C2DDBEB5 function");
        return 0;
    }

    int sceRtc_A93CF7D8()
    {
        //TODO implement me
        errorf(sceRtc, "UNIMPLEMENTED sceRtc_A93CF7D8 function");
        return 0;
    }

    int sceRtc_7D1FBED3()
    {
        //TODO implement me
        errorf(sceRtc, "UNIMPLEMENTED sceRtc_7D1FBED3 function");
        return 0;
    }
    
    int sceRtc_F5FCC995()
    {
        //TODO implement me
        errorf(sceRtc, "UNIMPLEMENTED sceRtc_F5FCC995 function");
        return 0;
    }
}

namespace syscalls
{
    void sceRtcRegisterCallback(AlContext &context)			{ V0   = sceRtc::sceRtcRegisterCallback();                }
    void sceRtc_F5FCC995(AlContext &context)				{ V0   = sceRtc::sceRtc_F5FCC995();                       }
    void sceRtcTickAddSeconds(AlContext &context)			{ V0   = sceRtc::sceRtcTickAddSeconds(A0, A1, A3A2);      }
    void sceRtcSetDosTime(AlContext &context)				{ V0   = sceRtc::sceRtcSetDosTime(A0, A1);                }
    void sceRtcGetCurrentClockLocalTime(AlContext &context)	{ V0   = sceRtc::sceRtcGetCurrentClockLocalTime();        }
    void sceRtcTickAddMinutes(AlContext &context)			{ V0   = sceRtc::sceRtcTickAddMinutes(A0, A1, A3A2);      }
    void sceRtcTickAddDays(AlContext &context)				{ V0   = sceRtc::sceRtcTickAddDays(A0, A1, A3A2);         }
    void sceRtcGetTime64_t(AlContext &context)				{ V0   = sceRtc::sceRtcGetTime64_t();                     }
    void sceRtcParseDateTime(AlContext &context)			{ V0   = sceRtc::sceRtcParseDateTime();                   }
    void sceRtcTickAddMonths(AlContext &context)			{ V0   = sceRtc::sceRtcTickAddMonths(A0, A1, A3A2);       }
    void sceRtcGetWin32FileTime(AlContext &context)			{ V0   = sceRtc::sceRtcGetWin32FileTime();                }
    void sceRtcTickAddWeeks(AlContext &context)				{ V0   = sceRtc::sceRtcTickAddWeeks(A0, A1, A3A2);        }
    void sceRtcFormatRFC2822(AlContext &context)			{ V0   = sceRtc::sceRtcFormatRFC2822();                   }
    void sceRtcGetTickResolution(AlContext &context)        { V0   = sceRtc::sceRtcGetTickResolution();               }
    void sceRtc_C2DDBEB5(AlContext &context)				{ V0   = sceRtc::sceRtc_C2DDBEB5();                       }
    void sceRtc_A93CF7D8(AlContext &context)				{ V0   = sceRtc::sceRtc_A93CF7D8();                       }
    void sceRtcCompareTick(AlContext &context)				{ V0   = sceRtc::sceRtcCompareTick(A0, A1);               }
    void sceRtcIsAlarmed(AlContext &context)				{ V0   = sceRtc::sceRtcIsAlarmed();                       }
    void sceRtcSetTick(AlContext &context)					{ V0   = sceRtc::sceRtcSetTick();                         }
    void sceRtcFormatRFC2822LocalTime(AlContext &context)	{ V0   = sceRtc::sceRtcFormatRFC2822LocalTime();          }
    void sceRtc_7D1FBED3(AlContext &context)				{ V0   = sceRtc::sceRtc_7D1FBED3();                       }
    void sceRtcSetWin32FileTime(AlContext &context)			{ V0   = sceRtc::sceRtcSetWin32FileTime();                }
    void sceRtcConvertLocalTimeToUTC(AlContext &context)	{ V0   = sceRtc::sceRtcConvertLocalTimeToUTC();           }
    void sceRtcGetTick(AlContext &context)					{ V0   = sceRtc::sceRtcGetTick();                         }
    void sceRtcUnregisterCallback(AlContext &context)		{ V0   = sceRtc::sceRtcUnregisterCallback();              }
    void sceRtcGetLastAdjustedTime(AlContext &context)		{ V0   = sceRtc::sceRtcGetLastAdjustedTime();             }
    void sceRtcGetDayOfWeek(AlContext &context)				{ V0   = sceRtc::sceRtcGetDayOfWeek();                    }
    void sceRtcGetCurrentClock(AlContext &context)			{ V0   = sceRtc::sceRtcGetCurrentClock();                 }
    void sceRtcCheckValid(AlContext &context)				{ V0   = sceRtc::sceRtcCheckValid(A0);                    }
    void sceRtcTickAddTicks(AlContext &context)				{ V0   = sceRtc::sceRtcTickAddTicks(A0, A1, A3A2);        }
    void sceRtcTickAddYears(AlContext &context)				{ V0   = sceRtc::sceRtcTickAddYears(A0, A1, A3A2);        }
    void sceRtcIsLeapYear(AlContext &context)				{ V0   = sceRtc::sceRtcIsLeapYear(A0);                    }
    void sceRtcGetCurrentTick(AlContext &context)           { V0   = sceRtc::sceRtcGetCurrentTick(A0);                }
    void sceRtcSetTime_t(AlContext &context)				{ V0   = sceRtc::sceRtcSetTime_t();                       }
    void sceRtcGetDosTime(AlContext &context)				{ V0   = sceRtc::sceRtcGetDosTime();                      }
    void sceRtcConvertUtcToLocalTime(AlContext &context)	{ V0   = sceRtc::sceRtcConvertUtcToLocalTime();           }
    void sceRtcParseRFC3339(AlContext &context)				{ V0   = sceRtc::sceRtcParseRFC3339();                    }
    void sceRtcFormatRFC3339LocalTime(AlContext &context)	{ V0   = sceRtc::sceRtcFormatRFC3339LocalTime();          }
    void sceRtcGetTime_t(AlContext &context)				{ V0   = sceRtc::sceRtcGetTime_t();                       }
    void sceRtcTickAddHours(AlContext &context)				{ V0   = sceRtc::sceRtcTickAddHours(A0, A1, A3A2);        }
    void sceRtcTickAddMicroseconds(AlContext &context)		{ V0   = sceRtc::sceRtcTickAddMicroseconds(A0, A1, A3A2); }
    void sceRtcGetLastReincarnatedTime(AlContext &context)	{ V0   = sceRtc::sceRtcGetLastReincarnatedTime();         }
    void sceRtcSetTime64_t(AlContext &context)				{ V0   = sceRtc::sceRtcSetTime64_t();                     }
    void sceRtcGetDaysInMonth(AlContext &context)			{ V0   = sceRtc::sceRtcGetDaysInMonth();                  }
    void sceRtcFormatRFC3339(AlContext &context)			{ V0   = sceRtc::sceRtcFormatRFC3339();                   }
    void sceRtcGetAccumlativeTime(AlContext &context)		{ V0   = sceRtc::sceRtcGetAccumlativeTime();              }
    void sceRtcGetAccumulativeTime(AlContext &context)		{ V1V0 = sceRtc::sceRtcGetAccumulativeTime();             }
}
