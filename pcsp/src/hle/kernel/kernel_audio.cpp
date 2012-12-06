#include "stdafx.h"

#if 0
#include "kernel_audio.h"
#include "kernel_thread.h"

KernelAudioOutputChannel::KernelAudioOutputChannel()
:   m_stream(0)
,   m_frames(0)
,   m_channel(this - KernelAudioOutputChannel::m_used_channels)
,   m_sample_rate(0)
,   m_buffer_toggle(0)
,   m_stereo(true)
{
    m_buffer[0] = 0;
    m_buffer[1] = 0;
    m_volume[0] = 0;
    m_volume[1] = 0;
}

KernelAudioOutputChannel::~KernelAudioOutputChannel()
{

}

int KernelAudioPCMOutputChannel::Reserve(int frames, int format)
{
    if (u32(frames - 17) > 4111)
    {
        return SCE_AUDIO_ERROR_INVALID_SIZE;
    }

    if (m_used_channels[this->m_channel].testAndSetAcquire())
    {
        return -1;
    }

    int size = 4*samplecount;
    //while (size < settings.mSoundBuffer)//default is 8192
    //{
    //    size += samplecount * 2;
    //}

    chans[channel].sampleBuffer = new s16[size];
    chans[channel].bufferSize   = size;
    chans[channel].channels     = channels;
    chans[channel].sampleCount  = samplecount;
    chans[channel].sampleRate   = 48000;
    chans[channel].readPos      = 0;
    chans[channel].writePos     = 0;
    chans[channel].used         = 0;
    chans[channel].volL         = 0;
    chans[channel].volR         = 0;
    chans[channel].isRunning    = false;
    chans[channel].threadStatus = 0;
    chans[channel].stream       = 0;

    PaStreamParameters  hostApiOutputParameters;
    PaStreamParameters *hostApiOutputParametersPtr;

    PaWasapiStreamInfo info =
    {
        sizeof(PaWasapiStreamInfo),
        paWASAPI,
        1,
        0 /*paWinWasapiExclusive*/
    };

    hostApiOutputParameters.device                    = Pa_GetDefaultOutputDevice();
    hostApiOutputParameters.channelCount              = 2;
    hostApiOutputParameters.sampleFormat              = paInt16;
    hostApiOutputParameters.suggestedLatency          = Pa_GetDeviceInfo(hostApiOutputParameters.device)->defaultLowOutputLatency;
    hostApiOutputParameters.hostApiSpecificStreamInfo = &info;

    hostApiOutputParametersPtr = &hostApiOutputParameters;

    static u32 streams = 0;

    if (true || streams++ == 1)
    {
        PaError err = Pa_OpenStream(&chans[channel].stream, 0, hostApiOutputParametersPtr, 48000, samplecount, paNoFlag, __AudioPaCallback, (void *)channel);

        if (err != paNoError)
        {
            errorf(sceAudio, "PortAudio error: %s\n", Pa_GetErrorText(err));
            return SCE_AUDIO_ERROR_INVALID_CH;
        }
    }

    chans[channel].reserved = true;

    memset(chans[channel].sampleBuffer, 0, size*sizeof(s16));

    return channel;
}
#endif