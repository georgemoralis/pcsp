////////////////////////////////////////////////////////////////
///This file is auto - generated from NIDgenerator version 0.2
////////////////////////////////////////////////////////////////
#ifndef scePsmf_h__
#define scePsmf_h__

namespace scePsmf
{
	extern bool Reboot();
	extern bool ShutDown();

	extern int scePsmfGetNumberOfStreams(); 
	extern int scePsmfGetCurrentStreamType(); 
	extern int scePsmfSetPsmf(); 
	extern int scePsmfGetPresentationEndTime(); 
	extern int scePsmfGetHeaderSize(); 
	extern int scePsmfGetAudioInfo(); 
	extern int scePsmfGetStreamSize(); 
	extern int scePsmfCheckEPmap(); 
	extern int scePsmfQueryStreamSize(); 
	extern int scePsmfGetEPWithTimestamp(); 
	extern int scePsmfGetPresentationStartTime(); 
	extern int scePsmfGetNumberOfEPentries(); 
	extern int scePsmfGetNumberOfSpecificStreams(); 
	extern int scePsmfGetEPidWithTimestamp(); 
	extern int scePsmfQueryStreamOffset(); 
	extern int scePsmfGetEPWithId(); 
	extern int scePsmfSpecifyStream(); 
	extern int scePsmfGetCurrentStreamNumber(); 
	extern int scePsmfVerifyPsmf(); 
	extern int scePsmfSpecifyStreamWithStreamType(); 
	extern int scePsmfSpecifyStreamWithStreamTypeNumber(); 
	extern int scePsmfGetVideoInfo(); 
}

#endif