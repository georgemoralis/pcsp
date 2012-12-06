#include "stdafx.h"
#include "sceAtrac3plus.h"
#include "hle/types.h"
#include "log.h"

namespace sceAtrac3plus
{
    static bool sceAtrac3plus_ready = false;

    bool Reboot()
    {
        ShutDown();

        sceAtrac3plus_ready = true;
        return true;
    }

    bool ShutDown()
    {
        if (sceAtrac3plus_ready)
        {
            sceAtrac3plus_ready = false;
        }
        return true;
    }

    int hleGetAtracID(int codecType) 
    {
        switch (codecType) 
        {
        case PSP_MODE_AT_3:
            atracID = 1;
            break;
        case PSP_MODE_AT_3_PLUS:
            atracID = 0;
            break;
        default:
            errorf(sceAtrac3plus, "hleGetAtracID unknown codecType: 0x%08X", codecType);
            atracID = 0;
            break;
        }

        return atracID;
    }

    int sceAtracGetLoopStatus()
    {
        //TODO implement me
        errorf(sceAtrac3plus, "UNIMPLEMENTED sceAtracGetLoopStatus function");
        return 0;
    }

    int sceAtracIsSecondBufferNeeded()
    {
        //TODO implement me
        errorf(sceAtrac3plus, "UNIMPLEMENTED sceAtracIsSecondBufferNeeded function");
        return 0;
    }

    int sceAtracGetInternalErrorInfo()
    {
        //TODO implement me
        errorf(sceAtrac3plus, "UNIMPLEMENTED sceAtracGetInternalErrorInfo function");
        return 0;
    }

    int sceAtracGetNextDecodePosition(u32 a0, u32 a1)
    {
        u32 *outPos = Memory::addr< u32 >(a1);
        *outPos		= 1;

        errorf(sceAtrac3plus, "DUMMY sceAtracGetNextDecodePosition: atracID=%d, outPos=0x%08X", a0, a1);
        return 0; 
    }

    int sceAtracGetMaxSample(u32 a0, u32 a1)
    {
        int  atracID    = a0;
        int *maxSamples = Memory::addr< int >(a1);

        errorf(sceAtrac3plus, "UNIMPLEMENTED sceAtracGetMaxSample: atracID=%d, maxSamples = 0x%08X", a0, a1);
        return 0;
    }

    int sceAtracEndEntry()
    {
        //TODO implement me
        errorf(sceAtrac3plus, "UNIMPLEMENTED sceAtracEndEntry function");
        return 0;
    }

    int sceAtracStartEntry()
    {
        //TODO implement me
        errorf(sceAtrac3plus, "UNIMPLEMENTED sceAtracStartEntry function");
        return 0;
    }

    int sceAtracGetBufferInfoForReseting()
    {
        //TODO implement me
        errorf(sceAtrac3plus, "UNIMPLEMENTED sceAtracGetBufferInfoForReseting function");
        return 0;
    }

    int sceAtracGetOutputChannel()
    {
        //TODO implement me
        errorf(sceAtrac3plus,"UNIMPLEMENTED sceAtracGetOutputChannel function");
        return 0;
    }

    int sceAtracGetBitrate(u32 a0, u32 a1)
    {
        int  atID    = a0;
        int *bitRate = Memory::addr< int >(a1);

        errorf(sceAtrac3plus,"UNIMPLEMENTED sceAtracGetMaxSample: atracID=%d, bitRate=0x%08X", a0, a1);
        return 0;
    }

    int sceAtracGetSoundSample(u32 a0, u32 a1, u32 a2)
    {
        u32 *outEndSample       = Memory::addr< u32 >(a0);
        u32 *outLoopStartSample = Memory::addr< u32 >(a1);
        u32 *outLoopEndSample   = Memory::addr< u32 >(a2);

        if (a0) *outEndSample       = 0x10000;
        if (a1) *outLoopStartSample = -1;
        if (a2) *outLoopEndSample   = -1;
        
        errorf(sceAtrac3plus, "DUMMY sceAtracGetSoundSample");
        return 0;
    }

    int sceAtracSetMOutHalfwayBufferAndGetID()
    {
        //TODO implement me
        errorf(sceAtrac3plus, "UNIMPLEMENTED sceAtracSetMOutHalfwayBufferAndGetID function");
        return 0;
    }

    int sceAtracGetRemainFrame(u32 a0 /*int atracID*/, u32 a1/*int *outRemainFrame*/)
    {
        u32 *outRemainFrame = Memory::addr< u32 >(a1);
        *outRemainFrame     = 12;

        errorf(sceAtrac3plus, "DUMMY sceAtracGetRemainFrame");
        return 0; 
    }

    int sceAtracSetLoopNum(u32 a0, u32 a1)
    {
        int atracID = a0;
        int *nloop  = Memory::addr< int >(a1);
        
        errorf(sceAtrac3plus, "UNIMPLEMENTED sceAtracSetLoopNum: atracID = %i, loopNbr = 0x%08X", a0, a1);
        return 0;
    }

    int sceAtracGetSecondBufferInfo(u32 a0, u32 a1)
    {
        u32 *outPos   = Memory::addr< u32 >(a0);
        u32 *outBytes = Memory::addr< u32 >(a1);

        if (a0) *outPos		= 0;
        if (a1) *outBytes	= 0x10000;

        errorf(sceAtrac3plus, "DUMMY sceAtracGetSecondBufferInfo");
        return 0;
    }

    int sceAtracSetSecondBuffer()
    {
        //TODO implement me
        errorf(sceAtrac3plus, "UNIMPLEMENTED sceAtracSetSecondBuffer function");
        return 0;
    }

    int sceAtracAddStreamData(u32 a0, u32 a1)
    {
        int atracID    = a0;
        u32 bytesToAdd = a1;

        errorf(sceAtrac3plus, "UNIMPLEMENTED sceAtracAddStreamData: atracID=%d, bytesToAdd=%d", a0, a1);
        return 0;
    }

    int sceAtracSetDataAndGetID(u32 a0, u32 a1)
    {
        u32 buffer     = a0;
        s32 bufferSize = a1;
        s32 codecType  = 0;
        u16 at3Header  = Memory::memhu(buffer + 20);
        
        if (at3Header == PSP_AT3_HEADER)
        {
            codecType = PSP_MODE_AT_3;
        }
        else if (at3Header == PSP_AT3_PLUS_HEADER)
        {
            codecType = PSP_MODE_AT_3_PLUS;
        }

        debugf(sceAtrac3plus, "PARTIAL sceAtracSetDataAndGetID: buffer=0x%08X, bufferSize=0x%08X; at3Header=0x%04hX, codecType=0x%08X", a0, a1, at3Header, codecType);
        return hleGetAtracID(codecType);
    }

    int sceAtracGetAtracID(u32 a0)
    {
        int codecType = a0;

        debugf(sceAtrac3plus, "PARTIAL sceAtracGetAtracID: codecType=0x%08X", a0);
        return hleGetAtracID(codecType);
    }

    int sceAtracDecodeData(u32 a0/*atracID*/, u32 a1/*outSamples*/, u32 a2/*outN*/, u32 a3/*outEnd*/, u32 t0/*outRemainFrame*/)
    {
        int atracID         = a0; 
        u16 *outSamples     = Memory::addr< u16 >(a1); 
        int *outN           = Memory::addr< int >(a2); 
        int *outEnd         = Memory::addr< int >(a3);  
        int *outRemainFrame = Memory::addr< int >(t0);

        *outSamples     = 0;
        *outN           = 16;
        *outEnd         = 1;
        *outRemainFrame = -1;

        errorf(sceAtrac3plus, "UNIMPLEMENTED sceAtracDecodeData: atracID=%d, outSamples=0x%08X, outN=0x%08X, outEnd=0x%08X, outRemainFrame=0x%08X", a0, a1, a2, a3, t0);
        return 0;
    }

    int sceAtracResetPlayPosition()
    {
        //TODO implement me
        errorf(sceAtrac3plus, "UNIMPLEMENTED sceAtracResetPlayPosition instruction");
        return 0;
    }

    int sceAtracReleaseAtracID(u32 a0)
    {
        //TODO implement me
        errorf(sceAtrac3plus, "UNIMPLEMENTED sceAtracReleaseAtracID instruction: atracID=%d", a0);
        return 0;
    }

    int sceAtracSetAA3HalfwayBufferAndGetID()
    {
        //TODO implement me
        errorf(sceAtrac3plus, "UNIMPLEMENTED sceAtracSetAA3HalfwayBufferAndGetID function");
        return 0;
    }

    int sceAtracGetStreamDataInfo(u32 a0, u32 a1, u32 a2, u32 a3)
    {
        int  atracID        = a0;
        u8 **writePointer   = Memory::addr< u8* >(a1);
        u32 *availableBytes = Memory::addr< u32 >(a2);
        u32 *readOffset     = Memory::addr< u32 >(a3);
        
        //TODO implement me
        errorf(sceAtrac3plus, "UNIMPLEMENTED sceAtracGetStreamDataInfo: atracID=%d, writePointer=0x%08X, availableBytes=0x%08X, readOffset=0x%08X", a0, a1, a2, a3);
        return 0;
    }

    int sceAtracSetMOutHalfwayBuffer()
    {
        //TODO implement me
        errorf(sceAtrac3plus, "UNIMPLEMENTED sceAtracSetMOutHalfwayBuffer function");
        return 0;
    }

    int sceAtracSetAA3DataAndGetID()
    {
        //TODO implement me
        errorf(sceAtrac3plus, "UNIMPLEMENTED sceAtracSetAA3DataAndGetID function");
        return 0;
    }

    int sceAtracSetHalfwayBuffer()
    {
        //TODO implement me
        errorf(sceAtrac3plus, "UNIMPLEMENTED sceAtracSetHalfwayBuffer function");
        return 0;
    }

    int sceAtracGetNextSample(u32 a0, u32 a1)
    {
        int  atID = a0;
        int *outN = Memory::addr< int >(a1);

        //TODO implement me
        errorf(sceAtrac3plus, "UNIMPLEMENTED sceAtracGetNextSample: atracID=%d, outN=0x%08X", a0, a1);
        return 0;
    }

    int sceAtracGetChannel()
    {
        //TODO implement me
        errorf(sceAtrac3plus, "UNIMPLEMENTED sceAtracGetChannel function");
        return 0;
    }

    int sceAtracGetBufferInfoForResetting()
    {
        //TODO implement me
        errorf(sceAtrac3plus, "UNIMPLEMENTED sceAtracGetBufferInfoForResetting function");
        return 0;
    }

    int sceAtracReinit()
    {
        //TODO implement me
        errorf(sceAtrac3plus, "UNIMPLEMENTED sceAtracReinit function");
        return atracID;
    }

    int sceAtracSetHalfwayBufferAndGetID()
    {
        //TODO implement me
        errorf(sceAtrac3plus, "UNIMPLEMENTED sceAtracSetHalfwayBufferAndGetID function");
        return 0;
    }

    int sceAtracSetData(u32 a0, u32 a1, u32 a2)
    {
        s32 atracID = a0;
        u32 bufAddr = a1;
        u32 bufSize = a2;//16384
        
        u32 codecType = 0;
        u16 at3Header = Memory::memhu(bufAddr + 20);

        if (at3Header == PSP_AT3_HEADER)
        {
            codecType = PSP_MODE_AT_3;
        }
        else if (at3Header == PSP_AT3_PLUS_HEADER)
        {
            codecType = PSP_MODE_AT_3_PLUS;
        }

        debugf(sceAtrac3plus, "PARTIAL sceAtracSetData: atracID=%d, bufAddr=0x%08X, bufSize=0x%08X, at3Header=0x%04hX, codecType=0x%08X", a0, a1, a2, at3Header, codecType);
        return hleGetAtracID(codecType);
    }
}

namespace syscalls
{
    void sceAtracGetLoopStatus(AlContext &context)                { V0 = sceAtrac3plus::sceAtracGetLoopStatus(); }
    void sceAtracIsSecondBufferNeeded(AlContext &context)         { V0 = sceAtrac3plus::sceAtracIsSecondBufferNeeded(); }
    void sceAtracGetInternalErrorInfo(AlContext &context)         { V0 = sceAtrac3plus::sceAtracGetInternalErrorInfo(); }
    void sceAtracGetNextDecodePosition(AlContext &context)        { V0 = sceAtrac3plus::sceAtracGetNextDecodePosition(A0, A1); }
    void sceAtracGetMaxSample(AlContext &context)                 { V0 = sceAtrac3plus::sceAtracGetMaxSample(A0, A1); }
    void sceAtracEndEntry(AlContext &context)                     { V0 = sceAtrac3plus::sceAtracEndEntry(); }
    void sceAtracStartEntry(AlContext &context)                   { V0 = sceAtrac3plus::sceAtracStartEntry(); }
    void sceAtracGetBufferInfoForReseting(AlContext &context)     { V0 = sceAtrac3plus::sceAtracGetBufferInfoForReseting(); }
    void sceAtracGetOutputChannel(AlContext &context)             { V0 = sceAtrac3plus::sceAtracGetOutputChannel(); }
    void sceAtracGetBitrate(AlContext &context)                   { V0 = sceAtrac3plus::sceAtracGetBitrate(A0, A1); }
    void sceAtracGetSoundSample(AlContext &context)               { V0 = sceAtrac3plus::sceAtracGetSoundSample(A0,A1,A2); }
    void sceAtracSetMOutHalfwayBufferAndGetID(AlContext &context) { V0 = sceAtrac3plus::sceAtracSetMOutHalfwayBufferAndGetID(); }
    void sceAtracGetRemainFrame(AlContext &context)               { V0 = sceAtrac3plus::sceAtracGetRemainFrame(A0, A1); }
    void sceAtracSetLoopNum(AlContext &context)                   { V0 = sceAtrac3plus::sceAtracSetLoopNum(A0, A1); }
    void sceAtracGetSecondBufferInfo(AlContext &context)          { V0 = sceAtrac3plus::sceAtracGetSecondBufferInfo(A0,A1); }
    void sceAtracSetSecondBuffer(AlContext &context)              { V0 = sceAtrac3plus::sceAtracSetSecondBuffer(); }
    void sceAtracAddStreamData(AlContext &context)                { V0 = sceAtrac3plus::sceAtracAddStreamData(A0, A1); }
    void sceAtracSetDataAndGetID(AlContext &context)              { V0 = sceAtrac3plus::sceAtracSetDataAndGetID(A0, A1); }
    void sceAtracGetAtracID(AlContext &context)                   { V0 = sceAtrac3plus::sceAtracGetAtracID(A0); }
    void sceAtracDecodeData(AlContext &context)                   { V0 = sceAtrac3plus::sceAtracDecodeData(A0, A1, A2, A3, T0); }
    void sceAtracResetPlayPosition(AlContext &context)            { V0 = sceAtrac3plus::sceAtracResetPlayPosition(); }
    void sceAtracReleaseAtracID(AlContext &context)               { V0 = sceAtrac3plus::sceAtracReleaseAtracID(A0); }
    void sceAtracSetAA3HalfwayBufferAndGetID(AlContext &context)  { V0 = sceAtrac3plus::sceAtracSetAA3HalfwayBufferAndGetID(); }
    void sceAtracGetStreamDataInfo(AlContext &context)            { V0 = sceAtrac3plus::sceAtracGetStreamDataInfo(A0, A1, A2, A3); }
    void sceAtracSetMOutHalfwayBuffer(AlContext &context)         { V0 = sceAtrac3plus::sceAtracSetMOutHalfwayBuffer(); }
    void sceAtracSetAA3DataAndGetID(AlContext &context)           { V0 = sceAtrac3plus::sceAtracSetAA3DataAndGetID(); }
    void sceAtracSetHalfwayBuffer(AlContext &context)             { V0 = sceAtrac3plus::sceAtracSetHalfwayBuffer(); }
    void sceAtracGetNextSample(AlContext &context)                { V0 = sceAtrac3plus::sceAtracGetNextSample(A0, A1); }
    void sceAtracGetChannel(AlContext &context)                   { V0 = sceAtrac3plus::sceAtracGetChannel(); }
    void sceAtracGetBufferInfoForResetting(AlContext &context)    { V0 = sceAtrac3plus::sceAtracGetBufferInfoForResetting(); }
    void sceAtracReinit(AlContext &context)                       { V0 = sceAtrac3plus::sceAtracReinit(); }
    void sceAtracSetHalfwayBufferAndGetID(AlContext &context)     { V0 = sceAtrac3plus::sceAtracSetHalfwayBufferAndGetID(); }
    void sceAtracSetData(AlContext &context)                      { V0 = sceAtrac3plus::sceAtracSetData(A0, A1, A2); }
}
