#include "stdafx.h"
#include "sceMpeg.h"
#include "hle/types.h"
#include "log.h"

namespace sceMpeg
{
    static bool sceMpeg_ready = false;

    bool Reboot()
    {
        ShutDown();
        sceMpeg_ready = true;
        return true;
    }
    bool ShutDown()
    {
        if (sceMpeg_ready)
        {
            sceMpeg_ready = false;
        }
        return true;
    }

	int sceMpegGetAvcAu()
	{
		//TODO implement me
		errorf(sceMpeg,"UNIMPLEMENTED sceMpegGetAvcAu instruction");
		return 0;
	}
	int sceMpegQueryAtracEsSize()
	{
		//TODO implement me
		errorf(sceMpeg,"UNIMPLEMENTED sceMpegQueryAtracEsSize instruction");
		return 0;
	}
	int sceMpegAvcDecodeStopYCbCr()
	{
		//TODO implement me
		errorf(sceMpeg,"UNIMPLEMENTED sceMpegAvcDecodeStopYCbCr instruction");
		return 0;
	}
	int sceMpegAvcDecodeYCbCr()
	{
		//TODO implement me
		errorf(sceMpeg,"UNIMPLEMENTED sceMpegAvcDecodeYCbCr instruction");
		return 0;
	}
	int sceMpegGetAtracAu()
	{
		//TODO implement me
		errorf(sceMpeg,"UNIMPLEMENTED sceMpegGetAtracAu instruction");
		return 0;
	}
	int sceMpegCreate()
	{
		//TODO implement me
		errorf(sceMpeg,"UNIMPLEMENTED sceMpegCreate instruction");
		return 0;
	}
	int sceMpegRingbufferQueryMemSize()
	{
		//TODO implement me
		errorf(sceMpeg,"UNIMPLEMENTED sceMpegRingbufferQueryMemSize instruction");
		return 0;
	}
	int sceMpegFreeAvcEsBuf()
	{
		//TODO implement me
		errorf(sceMpeg,"UNIMPLEMENTED sceMpegFreeAvcEsBuf instruction");
		return 0;
	}
	int sceMpegQueryUserdataEsSize()
	{
		//TODO implement me
		errorf(sceMpeg,"UNIMPLEMENTED sceMpegQueryUserdataEsSize instruction");
		return 0;
	}
	int sceMpegQueryMemSize()
	{
		//TODO implement me
		errorf(sceMpeg,"UNIMPLEMENTED sceMpegQueryMemSize instruction");
		return 0;
	}
	int sceMpegQueryPcmEsSize()
	{
		//TODO implement me
		errorf(sceMpeg,"UNIMPLEMENTED sceMpegQueryPcmEsSize instruction");
		return 0;
	}
	int sceMpegRingbufferAvailableSize()
	{
		//TODO implement me
		errorf(sceMpeg,"UNIMPLEMENTED sceMpegRingbufferAvailableSize instruction");
		return 0;
	}
	int sceMpegRingbufferPut()
	{
		//TODO implement me
		errorf(sceMpeg,"UNIMPLEMENTED sceMpegRingbufferPut instruction");
		return 0;
	}
	int sceMpegMallocAvcEsBuf()
	{
		//TODO implement me
		errorf(sceMpeg,"UNIMPLEMENTED sceMpegMallocAvcEsBuf instruction");
		return 0;
	}
	int sceMpegAvcDecodeMode()
	{
		//TODO implement me
		errorf(sceMpeg,"UNIMPLEMENTED sceMpegAvcDecodeMode instruction");
		return 0;
	}
	int sceMpegChangeGetAuMode()
	{
		//TODO implement me
		errorf(sceMpeg,"UNIMPLEMENTED sceMpegChangeGetAuMode instruction");
		return 0;
	}
	int sceMpegGetAvcEsAu()
	{
		//TODO implement me
		errorf(sceMpeg,"UNIMPLEMENTED sceMpegGetAvcEsAu instruction");
		return 0;
	}
	int sceMpegGetPcmAu()
	{
		//TODO implement me
		errorf(sceMpeg,"UNIMPLEMENTED sceMpegGetPcmAu instruction");
		return 0;
	}
	int sceMpegFinish()
	{
		//TODO implement me
		errorf(sceMpeg,"UNIMPLEMENTED sceMpegFinish instruction");
		return 0;
	}
	int sceMpegAtracDecode()
	{
		//TODO implement me
		errorf(sceMpeg,"UNIMPLEMENTED sceMpegAtracDecode instruction");
		return 0;
	}
	int sceMpegRingbufferQueryPackNum()
	{
		//TODO implement me
		errorf(sceMpeg,"UNIMPLEMENTED sceMpegRingbufferQueryPackNum instruction");
		return 0;
	}
	int sceMpeg_75E21135()
	{
		//TODO implement me
		errorf(sceMpeg,"UNIMPLEMENTED sceMpeg_75E21135 instruction");
		return 0;
	}
	int sceMpegAvcDecodeStop()
	{
		//TODO implement me
		errorf(sceMpeg,"UNIMPLEMENTED sceMpegAvcDecodeStop instruction");
		return 0;
	}
	int sceMpegFlushAllStream()
	{
		//TODO implement me
		errorf(sceMpeg,"UNIMPLEMENTED sceMpegFlushAllStream instruction");
		return 0;
	}
	int sceMpegInit()
	{
		//TODO implement me
		errorf(sceMpeg,"UNIMPLEMENTED sceMpegInit instruction");
		return 0;
	}
	int sceMpegAvcInitYCbCr()
	{
		//TODO implement me
		errorf(sceMpeg,"UNIMPLEMENTED sceMpegAvcInitYCbCr instruction");
		return 0;
	}
	int sceMpegQueryStreamSize()
	{
		//TODO implement me
		errorf(sceMpeg,"UNIMPLEMENTED sceMpegQueryStreamSize instruction");
		return 0;
	}
	int sceMpegDelete()
	{
		//TODO implement me
		errorf(sceMpeg,"UNIMPLEMENTED sceMpegDelete instruction");
		return 0;
	}
	int sceMpegUnRegistStream()
	{
		//TODO implement me
		errorf(sceMpeg,"UNIMPLEMENTED sceMpegUnRegistStream instruction");
		return 0;
	}
	int sceMpegFlushStream()
	{
		//TODO implement me
		errorf(sceMpeg,"UNIMPLEMENTED sceMpegFlushStream instruction");
		return 0;
	}
	int sceMpegAvcDecodeFlush()
	{
		//TODO implement me
		errorf(sceMpeg,"UNIMPLEMENTED sceMpegAvcDecodeFlush instruction");
		return 0;
	}
	int sceMpeg_42C679F6()
	{
		//TODO implement me
		errorf(sceMpeg,"UNIMPLEMENTED sceMpeg_42C679F6 instruction");
		return 0;
	}
	int sceMpegRegistStream()
	{
		//TODO implement me
		errorf(sceMpeg,"UNIMPLEMENTED sceMpegRegistStream instruction");
		return 0;
	}
	int sceMpegNextAvcRpAu()
	{
		//TODO implement me
		errorf(sceMpeg,"UNIMPLEMENTED sceMpegNextAvcRpAu instruction");
		return 0;
	}
	int sceMpegRingbufferConstruct()
	{
		//TODO implement me
		errorf(sceMpeg,"UNIMPLEMENTED sceMpegRingbufferConstruct instruction");
		return 0;
	}
	int sceMpegAvcCsc()
	{
		//TODO implement me
		errorf(sceMpeg,"UNIMPLEMENTED sceMpegAvcCsc instruction");
		return 0;
	}
	int sceMpegChangeGetAvcAuMode()
	{
		//TODO implement me
		errorf(sceMpeg,"UNIMPLEMENTED sceMpegChangeGetAvcAuMode instruction");
		return 0;
	}
	int sceMpegQueryStreamOffset()
	{
		//TODO implement me
		errorf(sceMpeg,"UNIMPLEMENTED sceMpegQueryStreamOffset instruction");
		return 0;
	}
	int sceMpegAvcQueryYCbCrSize()
	{
		//TODO implement me
		errorf(sceMpeg,"UNIMPLEMENTED sceMpegAvcQueryYCbCrSize instruction");
		return 0;
	}
	int sceMpegInitAu()
	{
		//TODO implement me
		errorf(sceMpeg,"UNIMPLEMENTED sceMpegInitAu instruction");
		return 0;
	}
	int sceMpegRingbufferDestruct()
	{
		//TODO implement me
		errorf(sceMpeg,"UNIMPLEMENTED sceMpegRingbufferDestruct instruction");
		return 0;
	}
	int sceMpegGetAvcNalAu()
	{
		//TODO implement me
		errorf(sceMpeg,"UNIMPLEMENTED sceMpegGetAvcNalAu instruction");
		return 0;
	}
	int sceMpegAvcDecodeDetail()
	{
		//TODO implement me
		errorf(sceMpeg,"UNIMPLEMENTED sceMpegAvcDecodeDetail instruction");
		return 0;
	}
	int sceMpegAvcDecode()
	{
		//TODO implement me
		errorf(sceMpeg,"UNIMPLEMENTED sceMpegAvcDecode instruction");
		return 0;
	}
	int sceMpegAvcCopyYCbCr()
	{
		//TODO implement me
		errorf(sceMpeg,"UNIMPLEMENTED sceMpegAvcCopyYCbCr instruction");
		return 0;
	}
	int sceMpegGetUserdataAu()
	{
		//TODO implement me
		errorf(sceMpeg,"UNIMPLEMENTED sceMpegGetUserdataAu instruction");
		return 0;
	}
}
namespace syscalls
{
	void sceMpegGetAvcAu(AlContext &context){ V0 = sceMpeg::sceMpegGetAvcAu();};
	void sceMpegQueryAtracEsSize(AlContext &context){ V0 = sceMpeg::sceMpegQueryAtracEsSize();};
	void sceMpegAvcDecodeStopYCbCr(AlContext &context){ V0 = sceMpeg::sceMpegAvcDecodeStopYCbCr();};
	void sceMpegAvcDecodeYCbCr(AlContext &context){ V0 = sceMpeg::sceMpegAvcDecodeYCbCr();};
	void sceMpegGetAtracAu(AlContext &context){ V0 = sceMpeg::sceMpegGetAtracAu();};
	void sceMpegCreate(AlContext &context){ V0 = sceMpeg::sceMpegCreate();};
	void sceMpegRingbufferQueryMemSize(AlContext &context){ V0 = sceMpeg::sceMpegRingbufferQueryMemSize();};
	void sceMpegFreeAvcEsBuf(AlContext &context){ V0 = sceMpeg::sceMpegFreeAvcEsBuf();};
	void sceMpegQueryUserdataEsSize(AlContext &context){ V0 = sceMpeg::sceMpegQueryUserdataEsSize();};
	void sceMpegQueryMemSize(AlContext &context){ V0 = sceMpeg::sceMpegQueryMemSize();};
	void sceMpegQueryPcmEsSize(AlContext &context){ V0 = sceMpeg::sceMpegQueryPcmEsSize();};
	void sceMpegRingbufferAvailableSize(AlContext &context){ V0 = sceMpeg::sceMpegRingbufferAvailableSize();};
	void sceMpegRingbufferPut(AlContext &context){ V0 = sceMpeg::sceMpegRingbufferPut();};
	void sceMpegMallocAvcEsBuf(AlContext &context){ V0 = sceMpeg::sceMpegMallocAvcEsBuf();};
	void sceMpegAvcDecodeMode(AlContext &context){ V0 = sceMpeg::sceMpegAvcDecodeMode();};
	void sceMpegChangeGetAuMode(AlContext &context){ V0 = sceMpeg::sceMpegChangeGetAuMode();};
	void sceMpegGetAvcEsAu(AlContext &context){ V0 = sceMpeg::sceMpegGetAvcEsAu();};
	void sceMpegGetPcmAu(AlContext &context){ V0 = sceMpeg::sceMpegGetPcmAu();};
	void sceMpegFinish(AlContext &context){ V0 = sceMpeg::sceMpegFinish();};
	void sceMpegAtracDecode(AlContext &context){ V0 = sceMpeg::sceMpegAtracDecode();};
	void sceMpegRingbufferQueryPackNum(AlContext &context){ V0 = sceMpeg::sceMpegRingbufferQueryPackNum();};
	void sceMpeg_75E21135(AlContext &context){ V0 = sceMpeg::sceMpeg_75E21135();};
	void sceMpegAvcDecodeStop(AlContext &context){ V0 = sceMpeg::sceMpegAvcDecodeStop();};
	void sceMpegFlushAllStream(AlContext &context){ V0 = sceMpeg::sceMpegFlushAllStream();};
	void sceMpegInit(AlContext &context){ V0 = sceMpeg::sceMpegInit();};
	void sceMpegAvcInitYCbCr(AlContext &context){ V0 = sceMpeg::sceMpegAvcInitYCbCr();};
	void sceMpegQueryStreamSize(AlContext &context){ V0 = sceMpeg::sceMpegQueryStreamSize();};
	void sceMpegDelete(AlContext &context){ V0 = sceMpeg::sceMpegDelete();};
	void sceMpegUnRegistStream(AlContext &context){ V0 = sceMpeg::sceMpegUnRegistStream();};
	void sceMpegFlushStream(AlContext &context){ V0 = sceMpeg::sceMpegFlushStream();};
	void sceMpegAvcDecodeFlush(AlContext &context){ V0 = sceMpeg::sceMpegAvcDecodeFlush();};
	void sceMpeg_42C679F6(AlContext &context){ V0 = sceMpeg::sceMpeg_42C679F6();};
	void sceMpegRegistStream(AlContext &context){ V0 = sceMpeg::sceMpegRegistStream();};
	void sceMpegNextAvcRpAu(AlContext &context){ V0 = sceMpeg::sceMpegNextAvcRpAu();};
	void sceMpegRingbufferConstruct(AlContext &context){ V0 = sceMpeg::sceMpegRingbufferConstruct();};
	void sceMpegAvcCsc(AlContext &context){ V0 = sceMpeg::sceMpegAvcCsc();};
	void sceMpegChangeGetAvcAuMode(AlContext &context){ V0 = sceMpeg::sceMpegChangeGetAvcAuMode();};
	void sceMpegQueryStreamOffset(AlContext &context){ V0 = sceMpeg::sceMpegQueryStreamOffset();};
	void sceMpegAvcQueryYCbCrSize(AlContext &context){ V0 = sceMpeg::sceMpegAvcQueryYCbCrSize();};
	void sceMpegInitAu(AlContext &context){ V0 = sceMpeg::sceMpegInitAu();};
	void sceMpegRingbufferDestruct(AlContext &context){ V0 = sceMpeg::sceMpegRingbufferDestruct();};
	void sceMpegGetAvcNalAu(AlContext &context){ V0 = sceMpeg::sceMpegGetAvcNalAu();};
	void sceMpegAvcDecodeDetail(AlContext &context){ V0 = sceMpeg::sceMpegAvcDecodeDetail();};
	void sceMpegAvcDecode(AlContext &context){ V0 = sceMpeg::sceMpegAvcDecode();};
	void sceMpegAvcCopyYCbCr(AlContext &context){ V0 = sceMpeg::sceMpegAvcCopyYCbCr();};
	void sceMpegGetUserdataAu(AlContext &context){ V0 = sceMpeg::sceMpegGetUserdataAu();};
}
