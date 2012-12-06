////////////////////////////////////////////////////////////////
///This file is auto - generated from NIDgenerator version 0.2
////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "scePsmf.h"
#include "hle/types.h"
#include "log.h"

namespace scePsmf
{
	static bool scePsmf_ready = false;

	bool Reboot()
	{
		ShutDown();
		scePsmf_ready = true;
		return true;
	}
	bool ShutDown()
	{
		if (scePsmf_ready)
		{
			scePsmf_ready = false;
			
		}
		return true;
	}

	int scePsmfGetNumberOfStreams()
	{
		errorf(scePsmf,"UNIMPLEMENTED scePsmfGetNumberOfStreams function");
		return 2; //Faking
	}
	int scePsmfGetCurrentStreamType()
	{
		//TODO implement me
		errorf(scePsmf,"UNIMPLEMENTED scePsmfGetCurrentStreamType function");
		return 0;
	}
	int scePsmfSetPsmf()
	{
		//TODO implement me
		errorf(scePsmf,"UNIMPLEMENTED scePsmfSetPsmf function");
		return 0;
	}
	int scePsmfGetPresentationEndTime()
	{
		//TODO implement me
		errorf(scePsmf,"UNIMPLEMENTED scePsmfGetPresentationEndTime function");
		return 0;
	}
	int scePsmfGetHeaderSize()
	{
		//TODO implement me
		errorf(scePsmf,"UNIMPLEMENTED scePsmfGetHeaderSize function");
		return 0;
	}
	int scePsmfGetAudioInfo()
	{
		//TODO implement me
		errorf(scePsmf,"UNIMPLEMENTED scePsmfGetAudioInfo function");
		return 0;
	}
	int scePsmfGetStreamSize()
	{
		//TODO implement me
		errorf(scePsmf,"UNIMPLEMENTED scePsmfGetStreamSize function");
		return 0;
	}
	int scePsmfCheckEPmap()
	{
		//TODO implement me
		errorf(scePsmf,"UNIMPLEMENTED scePsmfCheckEPmap function");
		return 0;
	}
	int scePsmfQueryStreamSize()
	{
		//TODO implement me
		errorf(scePsmf,"UNIMPLEMENTED scePsmfQueryStreamSize function");
		return 0;
	}
	int scePsmfGetEPWithTimestamp()
	{
		//TODO implement me
		errorf(scePsmf,"UNIMPLEMENTED scePsmfGetEPWithTimestamp function");
		return 0;
	}
	int scePsmfGetPresentationStartTime()
	{
		//TODO implement me
		errorf(scePsmf,"UNIMPLEMENTED scePsmfGetPresentationStartTime function");
		return 0;
	}
	int scePsmfGetNumberOfEPentries()
	{
		//TODO implement me
		errorf(scePsmf,"UNIMPLEMENTED scePsmfGetNumberOfEPentries function");
		return 0;
	}
	int scePsmfGetNumberOfSpecificStreams()
	{
		errorf(scePsmf,"UNIMPLEMENTED scePsmfGetNumberOfSpecificStreams function");
		return 1; //Faking.
	}
	int scePsmfGetEPidWithTimestamp()
	{
		//TODO implement me
		errorf(scePsmf,"UNIMPLEMENTED scePsmfGetEPidWithTimestamp function");
		return 0;
	}
	int scePsmfQueryStreamOffset()
	{
		//TODO implement me
		errorf(scePsmf,"UNIMPLEMENTED scePsmfQueryStreamOffset function");
		return 0;
	}
	int scePsmfGetEPWithId()
	{
		//TODO implement me
		errorf(scePsmf,"UNIMPLEMENTED scePsmfGetEPWithId function");
		return 0;
	}
	int scePsmfSpecifyStream()
	{
		//TODO implement me
		errorf(scePsmf,"UNIMPLEMENTED scePsmfSpecifyStream function");
		return 0;
	}
	int scePsmfGetCurrentStreamNumber()
	{
		//TODO implement me
		errorf(scePsmf,"UNIMPLEMENTED scePsmfGetCurrentStreamNumber function");
		return 0;
	}
	int scePsmfVerifyPsmf()
	{
		//TODO implement me
		errorf(scePsmf,"UNIMPLEMENTED scePsmfVerifyPsmf function");
		return 0;
	}
	int scePsmfSpecifyStreamWithStreamType()
	{
		//TODO implement me
		errorf(scePsmf,"UNIMPLEMENTED scePsmfSpecifyStreamWithStreamType function");
		return 0;
	}
	int scePsmfSpecifyStreamWithStreamTypeNumber()
	{
		//TODO implement me
		errorf(scePsmf,"UNIMPLEMENTED scePsmfSpecifyStreamWithStreamTypeNumber function");
		return 0;
	}
	int scePsmfGetVideoInfo()
	{
		//TODO implement me
		errorf(scePsmf,"UNIMPLEMENTED scePsmfGetVideoInfo function");
		return 0;
	}
}
namespace syscalls
{
	void scePsmfGetNumberOfStreams(AlContext &context){ V0 = scePsmf::scePsmfGetNumberOfStreams();};
	void scePsmfGetCurrentStreamType(AlContext &context){ V0 = scePsmf::scePsmfGetCurrentStreamType();};
	void scePsmfSetPsmf(AlContext &context){ V0 = scePsmf::scePsmfSetPsmf();};
	void scePsmfGetPresentationEndTime(AlContext &context){ V0 = scePsmf::scePsmfGetPresentationEndTime();};
	void scePsmfGetHeaderSize(AlContext &context){ V0 = scePsmf::scePsmfGetHeaderSize();};
	void scePsmfGetAudioInfo(AlContext &context){ V0 = scePsmf::scePsmfGetAudioInfo();};
	void scePsmfGetStreamSize(AlContext &context){ V0 = scePsmf::scePsmfGetStreamSize();};
	void scePsmfCheckEPmap(AlContext &context){ V0 = scePsmf::scePsmfCheckEPmap();};
	void scePsmfQueryStreamSize(AlContext &context){ V0 = scePsmf::scePsmfQueryStreamSize();};
	void scePsmfGetEPWithTimestamp(AlContext &context){ V0 = scePsmf::scePsmfGetEPWithTimestamp();};
	void scePsmfGetPresentationStartTime(AlContext &context){ V0 = scePsmf::scePsmfGetPresentationStartTime();};
	void scePsmfGetNumberOfEPentries(AlContext &context){ V0 = scePsmf::scePsmfGetNumberOfEPentries();};
	void scePsmfGetNumberOfSpecificStreams(AlContext &context){ V0 = scePsmf::scePsmfGetNumberOfSpecificStreams();};
	void scePsmfGetEPidWithTimestamp(AlContext &context){ V0 = scePsmf::scePsmfGetEPidWithTimestamp();};
	void scePsmfQueryStreamOffset(AlContext &context){ V0 = scePsmf::scePsmfQueryStreamOffset();};
	void scePsmfGetEPWithId(AlContext &context){ V0 = scePsmf::scePsmfGetEPWithId();};
	void scePsmfSpecifyStream(AlContext &context){ V0 = scePsmf::scePsmfSpecifyStream();};
	void scePsmfGetCurrentStreamNumber(AlContext &context){ V0 = scePsmf::scePsmfGetCurrentStreamNumber();};
	void scePsmfVerifyPsmf(AlContext &context){ V0 = scePsmf::scePsmfVerifyPsmf();};
	void scePsmfSpecifyStreamWithStreamType(AlContext &context){ V0 = scePsmf::scePsmfSpecifyStreamWithStreamType();};
	void scePsmfSpecifyStreamWithStreamTypeNumber(AlContext &context){ V0 = scePsmf::scePsmfSpecifyStreamWithStreamTypeNumber();};
	void scePsmfGetVideoInfo(AlContext &context){ V0 = scePsmf::scePsmfGetVideoInfo();};
}
