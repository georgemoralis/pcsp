////////////////////////////////////////////////////////////////
///This file is auto - generated from NIDgenerator version 0.2
////////////////////////////////////////////////////////////////
#ifndef scePsmfPlayer_h__
#define scePsmfPlayer_h__

namespace scePsmfPlayer
{
	extern bool Reboot();
	extern bool ShutDown();

	extern int scePsmfPlayerGetCurrentStatus(); 
	extern int scePsmfPlayerGetCurrentPlayMode(); 
	extern int scePsmfPlayerReleasePsmf(); 
	extern int scePsmfPlayerGetPsmfInfo(); 
	extern int scePsmfPlayerGetAudioData(); 
	extern int scePsmfPlayer_B8D10C56(); 
	extern int scePsmfPlayerChangePlayMode(); 
	extern int scePsmfPlayerUpdate(); 
	extern int scePsmfPlayerGetCurrentVideoStream(); 
	extern int scePsmfPlayerDelete(); 
	extern int scePsmfPlayerStart(); 
	extern int scePsmfPlayer_8A9EBDCD(); 
	extern int scePsmfPlayer_85461EFF(); 
	extern int scePsmfPlayer_75F03FA2(); 
	extern int scePsmfPlayerGetCurrentAudioStream(); 
	extern int scePsmfPlayerGetVideoData(); 
	extern int scePsmfPlayerGetCurrentPts(); 
	extern int scePsmfPlayerGetAudioOutSize(); 
	extern int scePsmfPlayerSetPsmf(); 
	extern int scePsmfPlayer_2BEB1569(); 
	extern int scePsmfPlayerCreate(); 
	extern int scePsmfPlayer_1E57A8E7(); 
	extern int scePsmfPlayerStop(); 
}

#endif