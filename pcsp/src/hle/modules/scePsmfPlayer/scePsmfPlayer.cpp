////////////////////////////////////////////////////////////////
///This file is auto - generated from NIDgenerator version 0.2
////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "scePsmfPlayer.h"
#include "hle/types.h"
#include "log.h"

namespace scePsmfPlayer
{
	static bool scePsmfPlayer_ready = false;

	bool Reboot()
	{
		ShutDown();
		scePsmfPlayer_ready = true;
		return true;
	}
	bool ShutDown()
	{
		if (scePsmfPlayer_ready)
		{
			scePsmfPlayer_ready = false;	
		}
		return true;
	}

	int scePsmfPlayerGetCurrentStatus()
	{
		errorf(scePsmfPlayer,"UNIMPLEMENTED scePsmfPlayerGetCurrentStatus function");
		return 2; // Faking
	}
	int scePsmfPlayerGetCurrentPlayMode()
	{
		//TODO implement me
		errorf(scePsmfPlayer,"UNIMPLEMENTED scePsmfPlayerGetCurrentPlayMode function");
		return 0;
	}
	int scePsmfPlayerReleasePsmf()
	{
		//TODO implement me
		errorf(scePsmfPlayer,"UNIMPLEMENTED scePsmfPlayerReleasePsmf function");
		return 0;
	}
	int scePsmfPlayerGetPsmfInfo()
	{
		//TODO implement me
		errorf(scePsmfPlayer,"UNIMPLEMENTED scePsmfPlayerGetPsmfInfo function");
		return 0;
	}
	int scePsmfPlayerGetAudioData()
	{
		//TODO implement me
		errorf(scePsmfPlayer,"UNIMPLEMENTED scePsmfPlayerGetAudioData function");
		return 0;
	}
	int scePsmfPlayer_B8D10C56()
	{
		//TODO implement me
		errorf(scePsmfPlayer,"UNIMPLEMENTED scePsmfPlayer_B8D10C56 function");
		return 0;
	}
	int scePsmfPlayerChangePlayMode()
	{
		//TODO implement me
		errorf(scePsmfPlayer,"UNIMPLEMENTED scePsmfPlayerChangePlayMode function");
		return 0;
	}
	int scePsmfPlayerUpdate()
	{
		//TODO implement me
		errorf(scePsmfPlayer,"UNIMPLEMENTED scePsmfPlayerUpdate function");
		return 0;
	}
	int scePsmfPlayerGetCurrentVideoStream()
	{
		//TODO implement me
		errorf(scePsmfPlayer,"UNIMPLEMENTED scePsmfPlayerGetCurrentVideoStream function");
		return 0;
	}
	int scePsmfPlayerDelete()
	{
		//TODO implement me
		errorf(scePsmfPlayer,"UNIMPLEMENTED scePsmfPlayerDelete function");
		return 0;
	}
	int scePsmfPlayerStart()
	{
		//TODO implement me
		errorf(scePsmfPlayer,"UNIMPLEMENTED scePsmfPlayerStart function");
		return 0;
	}
	int scePsmfPlayer_8A9EBDCD()
	{
		//TODO implement me
		errorf(scePsmfPlayer,"UNIMPLEMENTED scePsmfPlayer_8A9EBDCD function");
		return 0;
	}
	int scePsmfPlayer_85461EFF()
	{
		//TODO implement me
		errorf(scePsmfPlayer,"UNIMPLEMENTED scePsmfPlayer_85461EFF function");
		return 0;
	}
	int scePsmfPlayer_75F03FA2()
	{
		//TODO implement me
		errorf(scePsmfPlayer,"UNIMPLEMENTED scePsmfPlayer_75F03FA2 function");
		return 0;
	}
	int scePsmfPlayerGetCurrentAudioStream()
	{
		//TODO implement me
		errorf(scePsmfPlayer,"UNIMPLEMENTED scePsmfPlayerGetCurrentAudioStream function");
		return 0;
	}
	int scePsmfPlayerGetVideoData()
	{
		//TODO implement me
		errorf(scePsmfPlayer,"UNIMPLEMENTED scePsmfPlayerGetVideoData function");
		return 0;
	}
	int scePsmfPlayerGetCurrentPts()
	{
		//TODO implement me
		errorf(scePsmfPlayer,"UNIMPLEMENTED scePsmfPlayerGetCurrentPts function");
		return 0;
	}
	int scePsmfPlayerGetAudioOutSize()
	{
		errorf(scePsmfPlayer,"UNIMPLEMENTED scePsmfPlayerGetAudioOutSize function");
		return 2048; //Faking
	}
	int scePsmfPlayerSetPsmf()
	{
		//TODO implement me
		errorf(scePsmfPlayer,"UNIMPLEMENTED scePsmfPlayerSetPsmf function");
		return 0;
	}
	int scePsmfPlayer_2BEB1569()
	{
		//TODO implement me
		errorf(scePsmfPlayer,"UNIMPLEMENTED scePsmfPlayer_2BEB1569 function");
		return 0;
	}
	int scePsmfPlayerCreate()
	{
		//TODO implement me
		errorf(scePsmfPlayer,"UNIMPLEMENTED scePsmfPlayerCreate function");
		return 0;
	}
	int scePsmfPlayer_1E57A8E7()
	{
		//TODO implement me
		errorf(scePsmfPlayer,"UNIMPLEMENTED scePsmfPlayer_1E57A8E7 function");
		return 0;
	}
	int scePsmfPlayerStop()
	{
		//TODO implement me
		errorf(scePsmfPlayer,"UNIMPLEMENTED scePsmfPlayerStop function");
		return 0;
	}
}
namespace syscalls
{
	void scePsmfPlayerGetCurrentStatus(AlContext &context){ V0 = scePsmfPlayer::scePsmfPlayerGetCurrentStatus();};
	void scePsmfPlayerGetCurrentPlayMode(AlContext &context){ V0 = scePsmfPlayer::scePsmfPlayerGetCurrentPlayMode();};
	void scePsmfPlayerReleasePsmf(AlContext &context){ V0 = scePsmfPlayer::scePsmfPlayerReleasePsmf();};
	void scePsmfPlayerGetPsmfInfo(AlContext &context){ V0 = scePsmfPlayer::scePsmfPlayerGetPsmfInfo();};
	void scePsmfPlayerGetAudioData(AlContext &context){ V0 = scePsmfPlayer::scePsmfPlayerGetAudioData();};
	void scePsmfPlayer_B8D10C56(AlContext &context){ V0 = scePsmfPlayer::scePsmfPlayer_B8D10C56();};
	void scePsmfPlayerChangePlayMode(AlContext &context){ V0 = scePsmfPlayer::scePsmfPlayerChangePlayMode();};
	void scePsmfPlayerUpdate(AlContext &context){ V0 = scePsmfPlayer::scePsmfPlayerUpdate();};
	void scePsmfPlayerGetCurrentVideoStream(AlContext &context){ V0 = scePsmfPlayer::scePsmfPlayerGetCurrentVideoStream();};
	void scePsmfPlayerDelete(AlContext &context){ V0 = scePsmfPlayer::scePsmfPlayerDelete();};
	void scePsmfPlayerStart(AlContext &context){ V0 = scePsmfPlayer::scePsmfPlayerStart();};
	void scePsmfPlayer_8A9EBDCD(AlContext &context){ V0 = scePsmfPlayer::scePsmfPlayer_8A9EBDCD();};
	void scePsmfPlayer_85461EFF(AlContext &context){ V0 = scePsmfPlayer::scePsmfPlayer_85461EFF();};
	void scePsmfPlayer_75F03FA2(AlContext &context){ V0 = scePsmfPlayer::scePsmfPlayer_75F03FA2();};
	void scePsmfPlayerGetCurrentAudioStream(AlContext &context){ V0 = scePsmfPlayer::scePsmfPlayerGetCurrentAudioStream();};
	void scePsmfPlayerGetVideoData(AlContext &context){ V0 = scePsmfPlayer::scePsmfPlayerGetVideoData();};
	void scePsmfPlayerGetCurrentPts(AlContext &context){ V0 = scePsmfPlayer::scePsmfPlayerGetCurrentPts();};
	void scePsmfPlayerGetAudioOutSize(AlContext &context){ V0 = scePsmfPlayer::scePsmfPlayerGetAudioOutSize();};
	void scePsmfPlayerSetPsmf(AlContext &context){ V0 = scePsmfPlayer::scePsmfPlayerSetPsmf();};
	void scePsmfPlayer_2BEB1569(AlContext &context){ V0 = scePsmfPlayer::scePsmfPlayer_2BEB1569();};
	void scePsmfPlayerCreate(AlContext &context){ V0 = scePsmfPlayer::scePsmfPlayerCreate();};
	void scePsmfPlayer_1E57A8E7(AlContext &context){ V0 = scePsmfPlayer::scePsmfPlayer_1E57A8E7();};
	void scePsmfPlayerStop(AlContext &context){ V0 = scePsmfPlayer::scePsmfPlayerStop();};
}
