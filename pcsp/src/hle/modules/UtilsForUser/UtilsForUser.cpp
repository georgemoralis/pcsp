#include "stdafx.h"
#include "UtilsForUser.h"
#include "hle/types.h"
#include "log.h"
#if defined(__win32__)
#include <Winsock2.h>
#endif
namespace UtilsForUser
{
    static bool UtilsForUser_ready = false;

    bool Reboot()
    {
        ShutDown();
        UtilsForUser_ready = true;
        return true;
    }
    bool ShutDown()
    {
        if (UtilsForUser_ready)
        {
            UtilsForUser_ready = false;
        }
        return true;
    }

    int sceKernelIcacheReadTag()
	{
		//TODO implement me
		errorf(UtilsForUser,"UNIMPLEMENTED sceKernelIcacheReadTag instruction");
		return 0;
	}
	int sceKernelUtilsSha1BlockInit()
	{
		//TODO implement me
		errorf(UtilsForUser,"UNIMPLEMENTED sceKernelUtilsSha1BlockInit instruction");
		return 0;
	}
	int UtilsForUser_F0155BCA()
	{
		//TODO implement me
		errorf(UtilsForUser,"UNIMPLEMENTED UtilsForUser_F0155BCA instruction");
		return 0;
	}
	int sceKernelUtilsMt19937Init()
	{
		//TODO implement me
		errorf(UtilsForUser,"UNIMPLEMENTED sceKernelUtilsMt19937Init instruction");
		return 0;
	}
	int UtilsForUser_DBBE9A46()
	{
		//TODO implement me
		errorf(UtilsForUser,"UNIMPLEMENTED UtilsForUser_DBBE9A46 instruction");
		return 0;
	}
	int sceKernelUtilsMd5Digest()
	{
		//TODO implement me
		errorf(UtilsForUser,"UNIMPLEMENTED sceKernelUtilsMd5Digest instruction");
		return 0;
	}
	int sceKernelIcacheInvalidateRange()
	{
		//TODO implement me
		//errorf(UtilsForUser,"UNIMPLEMENTED sceKernelIcacheInvalidateRange instruction");
		return 0;
	}
	int sceKernelDcacheInvalidateRange()
	{
		//TODO implement me
		//errorf(UtilsForUser,"UNIMPLEMENTED sceKernelDcacheInvalidateRange instruction");
		return 0;
	}
	int sceKernelUtilsMd5BlockResult()
	{
		//TODO implement me
		errorf(UtilsForUser,"UNIMPLEMENTED sceKernelUtilsMd5BlockResult instruction");
		return 0;
	}
	int UtilsForUser_B83A1E76()
	{
		//TODO implement me
		errorf(UtilsForUser,"UNIMPLEMENTED UtilsForUser_B83A1E76 instruction");
		return 0;
	}
	int sceKernelDcacheWritebackInvalidateAll()
	{
		//TODO implement me
		//errorf(UtilsForUser,"UNIMPLEMENTED sceKernelDcacheWritebackInvalidateAll instruction");
		return 0;
	}
	int UtilsForUser_AF3766BB()
	{
		//TODO implement me
		errorf(UtilsForUser,"UNIMPLEMENTED UtilsForUser_AF3766BB instruction");
		return 0;
	}
	int sceKernelUtilsMd5BlockInit()
	{
		//TODO implement me
		errorf(UtilsForUser,"UNIMPLEMENTED sceKernelUtilsMd5BlockInit instruction");
		return 0;
	}
	int UtilsForUser_99134C3F()
	{
		//TODO implement me
		errorf(UtilsForUser,"UNIMPLEMENTED UtilsForUser_99134C3F instruction");
		return 0;
	}
	int sceKernelIcacheInvalidateAll()
	{
		//TODO implement me
		//errorf(UtilsForUser,"UNIMPLEMENTED sceKernelIcacheInvalidateAll instruction");
		return 0;
	}
	int sceKernelLibcClock()
	{
		u32 retVal = clock()*1000;
        infof(hlemisc,"PARTIAL sceKernelLibcClock return %i",retVal);
		return retVal; // TODO: fix
	}
	int sceKernelPutUserLog()
	{
		//TODO implement me
		errorf(UtilsForUser,"UNIMPLEMENTED sceKernelPutUserLog instruction");
		return 0;
	}
	int sceKernelUtilsSha1Digest()
	{
		//TODO implement me
		errorf(UtilsForUser,"UNIMPLEMENTED sceKernelUtilsSha1Digest instruction");
		return 0;
	}
	int sceKernelDcacheProbe()
	{
		//TODO implement me
		errorf(UtilsForUser,"UNIMPLEMENTED sceKernelDcacheProbe instruction");
		return 0;
	}
	int sceKernelDcacheWritebackAll()
	{
		//TODO implement me
		//errorf(UtilsForUser,"UNIMPLEMENTED sceKernelDcacheWritebackAll instruction");
		return 0;
	}
	int sceKernelDcacheProbeRange()
	{
		//TODO implement me
		errorf(UtilsForUser,"UNIMPLEMENTED sceKernelDcacheProbeRange instruction");
		return 0;
	}
	int UtilsForUser_740DF7F0()
	{
		//TODO implement me
		errorf(UtilsForUser,"UNIMPLEMENTED UtilsForUser_740DF7F0 instruction");
		return 0;
	}
	int UtilsForUser_7333E539()
	{
		//TODO implement me
		errorf(UtilsForUser,"UNIMPLEMENTED UtilsForUser_7333E539 instruction");
		return 0;
	}
	int sceKernelLibcGettimeofday(u32 a0)
	{
		timeval *tv = Memory::addr< timeval >(a0);
  #ifdef _WIN32
		union
        {
			__int64 ns100; /*time since 1 Jan 1601 in 100ns units */
			FILETIME ft;
		} now;


		infof(UtilsForUser,"PARTIAL sceKernelLibcGettimeofday()");

		GetSystemTimeAsFileTime (&now.ft);
		tv->tv_usec = (long) ((now.ns100 / 10LL) % 1000000LL);
		tv->tv_sec = (long) ((now.ns100 - 116444736000000000LL) / 10000000LL);
  #else
        gettimeofday(tv, NULL);
        infof(UtilsForUser,"PARTIAL sceKernelLibcGettimeofday()");
  #endif
		return 0;
	}
	int sceKernelSetGPO()
	{
		//TODO implement me
		errorf(UtilsForUser,"UNIMPLEMENTED sceKernelSetGPO instruction");
		return 0;
	}
	int UtilsForUser_6231A71D()
	{
		//TODO implement me
		errorf(UtilsForUser,"UNIMPLEMENTED UtilsForUser_6231A71D instruction");
		return 0;
	}
	int sceKernelUtilsMd5BlockUpdate()
	{
		//TODO implement me
		errorf(UtilsForUser,"UNIMPLEMENTED sceKernelUtilsMd5BlockUpdate instruction");
		return 0;
	}
	int UtilsForUser_5C7F2B1A()
	{
		//TODO implement me
		errorf(UtilsForUser,"UNIMPLEMENTED UtilsForUser_5C7F2B1A instruction");
		return 0;
	}
	int sceKernelUtilsSha1BlockResult()
	{
		//TODO implement me
		errorf(UtilsForUser,"UNIMPLEMENTED sceKernelUtilsSha1BlockResult instruction");
		return 0;
	}
	int UtilsForUser_515B4FAF()
	{
		//TODO implement me
		errorf(UtilsForUser,"UNIMPLEMENTED UtilsForUser_515B4FAF instruction");
		return 0;
	}
	int sceKernelIcacheProbe()
	{
		//TODO implement me
		errorf(UtilsForUser,"UNIMPLEMENTED sceKernelIcacheProbe instruction");
		return 0;
	}
	int UtilsForUser_43C9A8DB()
	{
		//TODO implement me
		errorf(UtilsForUser,"UNIMPLEMENTED UtilsForUser_43C9A8DB instruction");
		return 0;
	}
	int UtilsForUser_3FD3D324()
	{
		//TODO implement me
		errorf(UtilsForUser,"UNIMPLEMENTED UtilsForUser_3FD3D324 instruction");
		return 0;
	}
	int sceKernelDcacheWritebackRange()
	{
		//TODO implement me
		//errorf(UtilsForUser,"UNIMPLEMENTED sceKernelDcacheWritebackRange instruction");
		return 0;
	}
	int UtilsForUser_39F49610()
	{
		//TODO implement me
		errorf(UtilsForUser,"UNIMPLEMENTED UtilsForUser_39F49610 instruction");
		return 0;
	}
	int sceKernelGetGPI()
	{
		//TODO implement me
		errorf(UtilsForUser,"UNIMPLEMENTED sceKernelGetGPI instruction");
		return 0;
	}
	int sceKernelDcacheWritebackInvalidateRange()
	{
		//TODO implement me
		//errorf(UtilsForUser,"UNIMPLEMENTED sceKernelDcacheWritebackInvalidateRange instruction");
		return 0;
	}
	int sceKernelUtilsSha1BlockUpdate()
	{
		//TODO implement me
		errorf(UtilsForUser,"UNIMPLEMENTED sceKernelUtilsSha1BlockUpdate instruction");
		return 0;
	}
	int sceKernelLibcTime(u32 a0)
	{
		u32 *time_addr = Memory::addr< u32 >(a0);
        
        #ifdef _WIN32
        union
        {
            __int64 ns100; /*time since 1 Jan 1601 in 100ns units */
            FILETIME ft;
        } now;
        GetSystemTimeAsFileTime (&now.ft);
        int seconds = (int)(long) ((now.ns100 - 116444736000000000LL) / 10000000LL);
        *time_addr = seconds;
        #endif
        infof(UtilsForUser,"PARTIAL sceKernelLibcTime() time_addr 0x%08X, seconds = %d",a0, seconds);
        return seconds;
	}
	int UtilsForUser_1B0592A3()
	{
		//TODO implement me
		errorf(UtilsForUser,"UNIMPLEMENTED UtilsForUser_1B0592A3 instruction");
		return 0;
	}
	int sceKernelDcacheReadTag()
	{
		//TODO implement me
		errorf(UtilsForUser,"UNIMPLEMENTED sceKernelDcacheReadTag instruction");
		return 0;
	}
	int UtilsForUser_157A383A()
	{
		//TODO implement me
		errorf(UtilsForUser,"UNIMPLEMENTED UtilsForUser_157A383A instruction");
		return 0;
	}
	int sceKernelUtilsMt19937UInt()
	{
		//TODO implement me
		errorf(UtilsForUser,"UNIMPLEMENTED sceKernelUtilsMt19937UInt instruction");
		return 0;
	}
	int UtilsForUser_004D4DEE()
	{
		//TODO implement me
		errorf(UtilsForUser,"UNIMPLEMENTED UtilsForUser_004D4DEE instruction");
		return 0;
	}
}
namespace syscalls
{
	void sceKernelIcacheReadTag(AlContext &context){ V0 = UtilsForUser::sceKernelIcacheReadTag();};
	void sceKernelUtilsSha1BlockInit(AlContext &context){ V0 = UtilsForUser::sceKernelUtilsSha1BlockInit();};
	void UtilsForUser_F0155BCA(AlContext &context){ V0 = UtilsForUser::UtilsForUser_F0155BCA();};
	void sceKernelUtilsMt19937Init(AlContext &context){ V0 = UtilsForUser::sceKernelUtilsMt19937Init();};
	void UtilsForUser_DBBE9A46(AlContext &context){ V0 = UtilsForUser::UtilsForUser_DBBE9A46();};
	void sceKernelUtilsMd5Digest(AlContext &context){ V0 = UtilsForUser::sceKernelUtilsMd5Digest();};
	void sceKernelIcacheInvalidateRange(AlContext &context){ V0 = UtilsForUser::sceKernelIcacheInvalidateRange();};
	void sceKernelDcacheInvalidateRange(AlContext &context){ V0 = UtilsForUser::sceKernelDcacheInvalidateRange();};
	void sceKernelUtilsMd5BlockResult(AlContext &context){ V0 = UtilsForUser::sceKernelUtilsMd5BlockResult();};
	void UtilsForUser_B83A1E76(AlContext &context){ V0 = UtilsForUser::UtilsForUser_B83A1E76();};
	void sceKernelDcacheWritebackInvalidateAll(AlContext &context){ V0 = UtilsForUser::sceKernelDcacheWritebackInvalidateAll();};
	void UtilsForUser_AF3766BB(AlContext &context){ V0 = UtilsForUser::UtilsForUser_AF3766BB();};
	void sceKernelUtilsMd5BlockInit(AlContext &context){ V0 = UtilsForUser::sceKernelUtilsMd5BlockInit();};
	void UtilsForUser_99134C3F(AlContext &context){ V0 = UtilsForUser::UtilsForUser_99134C3F();};
	void sceKernelIcacheInvalidateAll(AlContext &context){ V0 = UtilsForUser::sceKernelIcacheInvalidateAll();};
	void sceKernelLibcClock(AlContext &context){ V0 = UtilsForUser::sceKernelLibcClock();};
	void sceKernelPutUserLog(AlContext &context){ V0 = UtilsForUser::sceKernelPutUserLog();};
	void sceKernelUtilsSha1Digest(AlContext &context){ V0 = UtilsForUser::sceKernelUtilsSha1Digest();};
	void sceKernelDcacheProbe(AlContext &context){ V0 = UtilsForUser::sceKernelDcacheProbe();};
	void sceKernelDcacheWritebackAll(AlContext &context){ V0 = UtilsForUser::sceKernelDcacheWritebackAll();};
	void sceKernelDcacheProbeRange(AlContext &context){ V0 = UtilsForUser::sceKernelDcacheProbeRange();};
	void UtilsForUser_740DF7F0(AlContext &context){ V0 = UtilsForUser::UtilsForUser_740DF7F0();};
	void UtilsForUser_7333E539(AlContext &context){ V0 = UtilsForUser::UtilsForUser_7333E539();};
	void sceKernelLibcGettimeofday(AlContext &context)          { V0 = UtilsForUser::sceKernelLibcGettimeofday(A0);};
	void sceKernelSetGPO(AlContext &context){ V0 = UtilsForUser::sceKernelSetGPO();};
	void UtilsForUser_6231A71D(AlContext &context){ V0 = UtilsForUser::UtilsForUser_6231A71D();};
	void sceKernelUtilsMd5BlockUpdate(AlContext &context){ V0 = UtilsForUser::sceKernelUtilsMd5BlockUpdate();};
	void UtilsForUser_5C7F2B1A(AlContext &context){ V0 = UtilsForUser::UtilsForUser_5C7F2B1A();};
	void sceKernelUtilsSha1BlockResult(AlContext &context){ V0 = UtilsForUser::sceKernelUtilsSha1BlockResult();};
	void UtilsForUser_515B4FAF(AlContext &context){ V0 = UtilsForUser::UtilsForUser_515B4FAF();};
	void sceKernelIcacheProbe(AlContext &context){ V0 = UtilsForUser::sceKernelIcacheProbe();};
	void UtilsForUser_43C9A8DB(AlContext &context){ V0 = UtilsForUser::UtilsForUser_43C9A8DB();};
	void UtilsForUser_3FD3D324(AlContext &context){ V0 = UtilsForUser::UtilsForUser_3FD3D324();};
	void sceKernelDcacheWritebackRange(AlContext &context){ V0 = UtilsForUser::sceKernelDcacheWritebackRange();};
	void UtilsForUser_39F49610(AlContext &context){ V0 = UtilsForUser::UtilsForUser_39F49610();};
	void sceKernelGetGPI(AlContext &context){ V0 = UtilsForUser::sceKernelGetGPI();};
	void sceKernelDcacheWritebackInvalidateRange(AlContext &context){ V0 = UtilsForUser::sceKernelDcacheWritebackInvalidateRange();};
	void sceKernelUtilsSha1BlockUpdate(AlContext &context){ V0 = UtilsForUser::sceKernelUtilsSha1BlockUpdate();};
	void sceKernelLibcTime(AlContext &context)                 { V0 = UtilsForUser::sceKernelLibcTime(A0);};
	void UtilsForUser_1B0592A3(AlContext &context){ V0 = UtilsForUser::UtilsForUser_1B0592A3();};
	void sceKernelDcacheReadTag(AlContext &context){ V0 = UtilsForUser::sceKernelDcacheReadTag();};
	void UtilsForUser_157A383A(AlContext &context){ V0 = UtilsForUser::UtilsForUser_157A383A();};
	void sceKernelUtilsMt19937UInt(AlContext &context){ V0 = UtilsForUser::sceKernelUtilsMt19937UInt();};
	void UtilsForUser_004D4DEE(AlContext &context){ V0 = UtilsForUser::UtilsForUser_004D4DEE();};
}
