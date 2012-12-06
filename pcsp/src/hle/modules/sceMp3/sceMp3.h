////////////////////////////////////////////////////////////////
///This file is auto - generated from NIDgenerator version 0.2
////////////////////////////////////////////////////////////////
#ifndef sceMp3_h__
#define sceMp3_h__

namespace sceMp3
{
	extern bool Reboot();
	extern bool ShutDown();

	extern int sceMp3ReleaseMp3Handle(); 
	extern int sceMp3GetLoopNum(); 
	extern int sceMp3CheckStreamDataNeeded(); 
	extern int sceMp3Decode(); 
	extern int sceMp3GetInfoToAddStreamData(); 
	extern int sceMp3GetSamplingRate(); 
	extern int sceMp3StartEntry(); 
	extern int sceMp3GetMaxOutputSample(); 
	extern int sceMp3GetBitRate(); 
	extern int sceMp3GetMp3ChannelNum(); 
	extern int sceMp3EndEntry(); 
	extern int sceMp3Init(); 
	extern int sceMp3SetLoopNum(); 
	extern int sceMp3TermResource(); 
	extern int sceMp3InitResource(); 
	extern int sceMp3GetSumDecodedSample(); 
	extern int sceMp3ResetPlayPosition(); 
	extern int sceMp3NotifyAddStreamData(); 
	extern int sceMp3ReserveMp3Handle(); 
}

#endif