////////////////////////////////////////////////////////////////
///This file is auto - generated from NIDgenerator version 0.2
////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "sceMp3.h"
#include "hle/types.h"
#include "log.h"

namespace sceMp3
{
	static bool sceMp3_ready = false;

	bool Reboot()
	{
		ShutDown();
		sceMp3_ready = true;
		return true;
	}
	bool ShutDown()
	{
		if (sceMp3_ready)
		{
			sceMp3_ready = false;			
		}
		return true;
	}

	int sceMp3ReleaseMp3Handle()
	{
		//TODO implement me
		errorf(sceMp3,"UNIMPLEMENTED sceMp3ReleaseMp3Handle function");
		return 0;
	}
	int sceMp3GetLoopNum()
	{
		//TODO implement me
		errorf(sceMp3,"UNIMPLEMENTED sceMp3GetLoopNum function");
		return 0;
	}
	int sceMp3CheckStreamDataNeeded()
	{
		//TODO implement me
		errorf(sceMp3,"UNIMPLEMENTED sceMp3CheckStreamDataNeeded function");
		return 0;
	}
	int sceMp3Decode()
	{
		//TODO implement me
		errorf(sceMp3,"UNIMPLEMENTED sceMp3Decode function");
		return 0;
	}
	int sceMp3GetInfoToAddStreamData()
	{
		//TODO implement me
		errorf(sceMp3,"UNIMPLEMENTED sceMp3GetInfoToAddStreamData function");
		return 0;
	}
	int sceMp3GetSamplingRate()
	{
		//TODO implement me
		errorf(sceMp3,"UNIMPLEMENTED sceMp3GetSamplingRate function");
		return 0;
	}
	int sceMp3StartEntry()
	{
		//TODO implement me
		errorf(sceMp3,"UNIMPLEMENTED sceMp3StartEntry function");
		return 0;
	}
	int sceMp3GetMaxOutputSample()
	{
		//TODO implement me
		errorf(sceMp3,"UNIMPLEMENTED sceMp3GetMaxOutputSample function");
		return 0;
	}
	int sceMp3GetBitRate()
	{
		//TODO implement me
		errorf(sceMp3,"UNIMPLEMENTED sceMp3GetBitRate function");
		return 0;
	}
	int sceMp3GetMp3ChannelNum()
	{
		//TODO implement me
		errorf(sceMp3,"UNIMPLEMENTED sceMp3GetMp3ChannelNum function");
		return 0;
	}
	int sceMp3EndEntry()
	{
		//TODO implement me
		errorf(sceMp3,"UNIMPLEMENTED sceMp3EndEntry function");
		return 0;
	}
	int sceMp3Init()
	{
		//TODO implement me
		errorf(sceMp3,"UNIMPLEMENTED sceMp3Init function");
		return 0;
	}
	int sceMp3SetLoopNum()
	{
		//TODO implement me
		errorf(sceMp3,"UNIMPLEMENTED sceMp3SetLoopNum function");
		return 0;
	}
	int sceMp3TermResource()
	{
		//TODO implement me
		errorf(sceMp3,"UNIMPLEMENTED sceMp3TermResource function");
		return 0;
	}
	int sceMp3InitResource()
	{
		//TODO implement me
		errorf(sceMp3,"UNIMPLEMENTED sceMp3InitResource function");
		return 0;
	}
	int sceMp3GetSumDecodedSample()
	{
		//TODO implement me
		errorf(sceMp3,"UNIMPLEMENTED sceMp3GetSumDecodedSample function");
		return 0;
	}
	int sceMp3ResetPlayPosition()
	{
		//TODO implement me
		errorf(sceMp3,"UNIMPLEMENTED sceMp3ResetPlayPosition function");
		return 0;
	}
	int sceMp3NotifyAddStreamData()
	{
		//TODO implement me
		errorf(sceMp3,"UNIMPLEMENTED sceMp3NotifyAddStreamData function");
		return 0;
	}
	int sceMp3ReserveMp3Handle()
	{
		//TODO implement me
		errorf(sceMp3,"UNIMPLEMENTED sceMp3ReserveMp3Handle function");
		return 0;
	}
}
namespace syscalls
{
	void sceMp3ReleaseMp3Handle(AlContext &context){ V0 = sceMp3::sceMp3ReleaseMp3Handle();};
	void sceMp3GetLoopNum(AlContext &context){ V0 = sceMp3::sceMp3GetLoopNum();};
	void sceMp3CheckStreamDataNeeded(AlContext &context){ V0 = sceMp3::sceMp3CheckStreamDataNeeded();};
	void sceMp3Decode(AlContext &context){ V0 = sceMp3::sceMp3Decode();};
	void sceMp3GetInfoToAddStreamData(AlContext &context){ V0 = sceMp3::sceMp3GetInfoToAddStreamData();};
	void sceMp3GetSamplingRate(AlContext &context){ V0 = sceMp3::sceMp3GetSamplingRate();};
	void sceMp3StartEntry(AlContext &context){ V0 = sceMp3::sceMp3StartEntry();};
	void sceMp3GetMaxOutputSample(AlContext &context){ V0 = sceMp3::sceMp3GetMaxOutputSample();};
	void sceMp3GetBitRate(AlContext &context){ V0 = sceMp3::sceMp3GetBitRate();};
	void sceMp3GetMp3ChannelNum(AlContext &context){ V0 = sceMp3::sceMp3GetMp3ChannelNum();};
	void sceMp3EndEntry(AlContext &context){ V0 = sceMp3::sceMp3EndEntry();};
	void sceMp3Init(AlContext &context){ V0 = sceMp3::sceMp3Init();};
	void sceMp3SetLoopNum(AlContext &context){ V0 = sceMp3::sceMp3SetLoopNum();};
	void sceMp3TermResource(AlContext &context){ V0 = sceMp3::sceMp3TermResource();};
	void sceMp3InitResource(AlContext &context){ V0 = sceMp3::sceMp3InitResource();};
	void sceMp3GetSumDecodedSample(AlContext &context){ V0 = sceMp3::sceMp3GetSumDecodedSample();};
	void sceMp3ResetPlayPosition(AlContext &context){ V0 = sceMp3::sceMp3ResetPlayPosition();};
	void sceMp3NotifyAddStreamData(AlContext &context){ V0 = sceMp3::sceMp3NotifyAddStreamData();};
	void sceMp3ReserveMp3Handle(AlContext &context){ V0 = sceMp3::sceMp3ReserveMp3Handle();};
}
