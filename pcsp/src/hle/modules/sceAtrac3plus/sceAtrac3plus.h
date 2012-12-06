#ifndef sceAtrac3plus_h__
#define sceAtrac3plus_h__

namespace sceAtrac3plus
{
    enum
    {
        PSP_MODE_AT_3_PLUS = 0x00001000,
        PSP_MODE_AT_3      = 0x00001001
    };

    static int atracID;
	static int maxSamples = 1024;

    enum
    {
	    PSP_AT3_HEADER      = 0x00000270,
        PSP_AT3_PLUS_HEADER = 0x0000FFFE,
        PSP_RIFF_HEADER     = 0x46464952,
        PSP_WAVE_HEADER     = 0x45564157
    };

    extern bool Reboot();
    extern bool ShutDown();

    extern int sceAtracGetLoopStatus();
    extern int sceAtracIsSecondBufferNeeded();
    extern int sceAtracGetInternalErrorInfo();
    extern int sceAtracGetNextDecodePosition(u32 a0, u32 a1);
    extern int sceAtracGetMaxSample(u32 a0, u32 a1);
    extern int sceAtracEndEntry();
    extern int sceAtracStartEntry();
    extern int sceAtracGetBufferInfoForReseting();
    extern int sceAtracGetOutputChannel();
    extern int sceAtracGetBitrate(u32 a0, u32 a1);
    extern int sceAtracGetSoundSample(u32 a0, u32 a1, u32 a2);
    extern int sceAtracSetMOutHalfwayBufferAndGetID();
    extern int sceAtracGetRemainFrame(u32 a0, u32 a1);
    extern int sceAtracSetLoopNum(u32 a0, u32 a1);
    extern int sceAtracGetSecondBufferInfo(u32 a0, u32 a1);
    extern int sceAtracSetSecondBuffer();
    extern int sceAtracAddStreamData(u32 a0, u32 a1);
    extern int sceAtracSetDataAndGetID(u32 a0, u32 a1);
    extern int sceAtracGetAtracID(u32 a0);
    extern int sceAtracDecodeData(u32 a0, u32 a1, u32 a2, u32 a3, u32 t0);
    extern int sceAtracResetPlayPosition();
    extern int sceAtracReleaseAtracID(u32 a0);
    extern int sceAtracSetAA3HalfwayBufferAndGetID();
    extern int sceAtracGetStreamDataInfo(u32 a0, u32 a1, u32 a2, u32 a3);
    extern int sceAtracSetMOutHalfwayBuffer();
    extern int sceAtracSetAA3DataAndGetID();
    extern int sceAtracSetHalfwayBuffer();
    extern int sceAtracGetNextSample(u32 a0, u32 a1);
    extern int sceAtracGetChannel();
    extern int sceAtracGetBufferInfoForResetting();
    extern int sceAtracReinit();
    extern int sceAtracSetHalfwayBufferAndGetID();
    extern int sceAtracSetData(u32 a0, u32 a1, u32 a2);
}
#endif // sceAtrac3plus_h__
