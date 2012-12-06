#include "stdafx.h"

#include "common_thread.h"

#include "hle/types.h"
#include "hle/kernel.h"

#include "log.h"
#include "sceAudio.h"

#include "wtf/core/psp/hle/sceKernelThread.h"

#include "qt4/settings.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

namespace sceAudio
{
#undef min
#undef max

    template< typename T >
    __forceinline T Min(T a, T b)
    {
        return (b < a) ? b : a;
    }

    template< typename T >
    __forceinline T Max(T a, T b)
    {
        return (a < b) ? b : a;
    }

    template< typename T >
    __forceinline T Clamp(T val, T min, T max)
    {
        return Min(Max(val, min), max);
    }

    static AudioOutputStream stream[SCE_AUDIO_CHANNEL_MAX + 1];

    QCache< u64, AudioResamplerTable > AudioResamplerTable::tables(128);

    static bool ready = false;

    bool Reboot()
    {
        ShutDown();

        if (theKernelModuleManager.SyscallsModuleExists("ThreadManForUser"))
        {
            PaError err = Pa_Initialize();
            if (err != paNoError)
            {
                errorf(sceAudio, "PortAudio error: %s", Pa_GetErrorText(err));
            }
            else
            {
                for (int channel = 0; channel <= SCE_AUDIO_CHANNEL_MAX; channel++)
                {
                    stream[channel].Initialize();
                }

                ready = true;
            }
        }

        return ready;
    }

    bool ShutDown()
    {
        if (ready)
        {
            for (int channel = 0; channel <= SCE_AUDIO_CHANNEL_MAX; channel++)
            {
                if (stream[channel].stream)
                {
                    stream[channel].Terminate();
                }
            }

            PaError err = Pa_Terminate();
            if (err != paNoError)
            {
                errorf(sceAudio, "PortAudio error: %s", Pa_GetErrorText(err));
            }

            ready = false;
        }

        return !ready;
    }

}

namespace sceAudio
{
    static int __PaCallback(void const                     *inputBuffer,
                            void                           *outputBuffer,
                            unsigned long                   framesPerBuffer,
                            PaStreamCallbackTimeInfo const *timeInfo,
                            PaStreamCallbackFlags           statusFlags,
                            void                           *userData)
    {
        return static_cast< AudioStream * >(userData)->Render((f32 *)outputBuffer, u32(framesPerBuffer));
    }

    AudioStream::AudioStream()
    :   stream(0)
    ,   frequency(0)
    ,   sample_rate(0)
    ,   reserved(false)
    {
    }

    AudioStream::~AudioStream()
    {
    }

    bool AudioStream::Initialize()
    {
        PaStreamParameters  hostApiOutputParameters;
        PaStreamParameters *hostApiOutputParametersPtr = 0;

        static PaHostApiTypeId hostApiTypeIds[] =
        {
            // Windows
            paWASAPI,       /* Win7/Vista */
            paDirectSound,  /* fallback for WinXP */
            paMME,          /* fallback if no DSOUND */

            // Linux
            paJACK,

            // Mac/OSX
            paCoreAudio
        };

        PaHostApiTypeId        hostApiTypeId;
        PaHostApiIndex         hostApiIndex;
        PaHostApiInfo const   *hostApiInfo;

        for (int j = 0; j < sizeof(hostApiTypeIds)/sizeof(PaHostApiTypeId); ++j)
        {
            PaError error;

            hostApiTypeId = hostApiTypeIds[j];
            hostApiIndex = Pa_HostApiTypeIdToHostApiIndex(hostApiTypeId);
            if (hostApiIndex >= 0)
            {
                hostApiInfo = Pa_GetHostApiInfo(hostApiIndex);
                if (hostApiInfo && hostApiInfo->deviceCount)
                {
                    hostApiOutputParameters.hostApiSpecificStreamInfo = 0;
                    hostApiOutputParameters.device                    = hostApiInfo->defaultOutputDevice;
                    hostApiOutputParameters.channelCount              = 2;
                    hostApiOutputParameters.sampleFormat              = paFloat32;
                    hostApiOutputParameters.suggestedLatency          = Pa_GetDeviceInfo(hostApiOutputParameters.device)->defaultLowOutputLatency;

                    hostApiOutputParametersPtr = &hostApiOutputParameters;

                    static u32 sample_rates[2] =
                    {
                        48000,
                        44100
                    };

                    u32 sample_rate = 0;

                    for (int i = 0; i < sizeof(sample_rates)/sizeof(*sample_rates); ++i)
                    {
                        if (frequency != sample_rates[i])
                        {
                            error = Pa_IsFormatSupported(0, hostApiOutputParametersPtr, sample_rates[i]);
                            if (error == paFormatIsSupported)
                            {
                                PaDeviceInfo const *paDeviceInfo = Pa_GetDeviceInfo(hostApiInfo->defaultOutputDevice);

                                if (paDeviceInfo)
                                {
                                    sample_rate = sample_rates[i];
                                    infof(sceAudio, "PortAudio: host: %s, device: %s, low latency: %f, %d Hz, stereo", hostApiInfo->name, paDeviceInfo->name, paDeviceInfo->defaultLowOutputLatency, sample_rate);
                                    break;
                                }
                            }                   
                        }
                    }

                    if (sample_rate)
                    {
                        this->sample_rate = sample_rate;

                        error = Pa_OpenStream(&this->stream, 0, hostApiOutputParametersPtr, sample_rate, paFramesPerBufferUnspecified, paPrimeOutputBuffersUsingStreamCallback, __PaCallback, (void *)this);
                        if (error == paNoError)
                        {
                            break;
                        }
                    }

                    this->stream = 0;

                    errorf(sceAudio, "PortAudio error: %s", Pa_GetErrorText(error));
                    return false;
                }

                hostApiInfo = 0;
            }
        }

        if (!hostApiInfo)
        {
            errorf(sceAudio, "PortAudio: no sound device found");
            return false;
        }

        return true;
    }


    bool AudioStream::Terminate()
    {
        if (this->stream)
        {
            Pa_CloseStream(this->stream);

            this->stream = 0;

            return true;
        }

        return false;
    }

    int AudioStream::Render(f32 *target, u32 count)
    {
        ::memset(target, 0, 2 * sizeof(*target) * count);

        return paContinue;
    }
}

namespace sceAudio
{
    u32 AudioOutputStream::buffer_factor = 2;

    AudioOutputStream::AudioOutputStream()
    :   thread_status(0)
    ,   channels(0)
    ,   frames(0)
    ,   buffer_data(0)
    ,   buffer_size(0)
    ,   buffer_wpos(0)
    ,   buffer_rpos(0)
    ,   buffer_used(0)
    {
        volume[0] = 0;
        volume[1] = 0;
    }


    AudioOutputStream::~AudioOutputStream()
    {
    }

    int AudioOutputStream::Output(int volume_l, int volume_r, s16 *buffer, bool blocking)
	{
        this->volume[0] = min(max(0, volume_l), 32767);
        this->volume[1] = min(max(0, volume_r), 32767);

        bool active = Pa_IsStreamActive(this->stream);

        if (this->reserved)
        {
            u32 frames = buffer ? this->frames : 0;
            u32 used   = 2 * frames;

            do
            {
                u32 buffer_size = this->buffer_size * 16;

                this->Lock();
                u32 written = this->buffer_used;
                this->Unlock();

                u32 factor = this->buffer_factor;
                u32 left   = this->buffer_size * factor - written;

                if (settings.mSoundBufferCount)
                {
                    if (factor != settings.mSoundBufferCount)
                    {
                        factor = u32(settings.mSoundBufferCount);
                        
                        this->buffer_factor = factor;
                    }
                    
                    left = this->buffer_size * factor - written;
                }
                else
                {
                    if (written > left)
                    {
                        factor = Max(factor - 1, 2U);
                        this->buffer_factor = factor;
                    }
                    else if (written < left)
                    {
                        factor = Min(factor + 1, 16U);
                        this->buffer_factor = factor;
                    }

                    left = this->buffer_size * factor - written;
                }

                if (buffer && written + used <= this->buffer_size * factor)
                {

                    s16 *target  = this->buffer_data + this->buffer_wpos;
                    bool stereo  = this->channels == 2;

                    u32 left = buffer_size - this->buffer_wpos;
                    this->buffer_wpos += used;

                    if (left <= used)
                    {
                        this->buffer_wpos -= buffer_size;
                    }

                    u32 i = 0;
                    if (stereo)
                    {
                        if (left <= used)
                        {
                            for (left /= 2; i < left; i++)
                            {
                                *target++ = *buffer++;
                                *target++ = *buffer++;
                            }
                            target -= buffer_size;
                        }

                        for (; i < frames; i++)
                        {
                            *target++ = *buffer++;
                            *target++ = *buffer++;
                        }
                    }
                    else
                    {
                        if (left <= used)
                        {
                            for (left /= 2; i < left; i++)
                            {
                                s16 sample = *buffer++;
                                *target++ = sample;
                                *target++ = sample;
                            }
                            target -= buffer_size;
                        }

                        for (; i < frames; i++)
                        {
                            s16 sample = *buffer++;
                            *target++ = sample;
                            *target++ = sample;
                        }
                    }

                    this->Lock();
                    this->buffer_used += used;
                    this->Unlock();

                    if (!active)
                    {
                        PaError err = Pa_StartStream(stream);
                        if (err != paNoError)
                        {
                            errorf(sceAudio, "PortAudio error: %s", Pa_GetErrorText(err));

                            return -1;
                        }
                    }

                    return frames;
                }
                else if (blocking)
                {
                    if (active)
                    {
                        infof(sceAudio, "%s : total buffer size = %d X %d", "sceAudioStream::Output", this->buffer_factor, this->buffer_size);

                        this->Lock();
                        this->thread_status = hle::__KernelGetCurThreadStatus();
                        hle::__KernelWaitCurThread(*this, hle::WAITTYPE_AUDIOCHANNEL, this - sceAudio::stream);
                    }
                }
                else if (!buffer)
                {
                    Pa_StopStream(stream);

                    return frames;
                }
            }
            while (blocking);

            return SCE_AUDIO_ERROR_OUTPUT_BUSY;
        }

        return SCE_AUDIO_ERROR_NOT_RESERVED;
    }

    int AudioOutputStream::Setup(int frames, int frequency, int stereo)
    {
        PaStream *stream = this->stream;

        if (!this->reserved)
        {
            if (sample_rate)
            {
                this->resampler.Setup(frequency, sample_rate, stereo ? 2 : 1);

                int size = frames * 2;

                this->buffer_array.resize(size * 16);

                this->buffer_data   = &(*this->buffer_array.begin());
                this->buffer_size   = size;
                this->buffer_rpos   = 0;
                this->buffer_wpos   = 0;
                this->buffer_used   = 0;
                this->volume[0]     = 0;
                this->volume[1]     = 0;
                this->thread_status = 0;
                this->frequency     = frequency;
                this->channels      = stereo ? 2 : 1;
                this->frames        = frames;
                this->reserved      = true;

                return 0;
            }
        }

        return -1;
    }

    int AudioOutputStream::Reserve(int frames, int frequency, int format)
    {
        if (u32(frames - 17) > 4111)
        {
            return SCE_AUDIO_ERROR_INVALID_SIZE;
        }

        return this->Setup(frames, frequency, !format);
    }

    int AudioOutputStream::Release()
    {
        if (this->reserved)
        {
            Pa_CloseStream(this->stream);

            this->buffer_array.clear();
            this->reserved = 0;
        }

        return 0;
    }

    int AudioOutputStream::ChangeVolume(int l, int r)
    {
        if (!this->reserved)
        {
            return SCE_AUDIO_ERROR_NOT_RESERVED;
        }

        this->Lock();
        while (this->buffer_used)
        {
            this->thread_status = hle::__KernelGetCurThreadStatus();
            hle::__KernelWaitCurThread(*this, hle::WAITTYPE_AUDIOCHANNEL, this - sceAudio::stream);
            this->Lock();
        }
        this->Unlock();

        this->volume[0] = l;
        this->volume[1] = r;

        return 0;
    }


    int AudioOutputStream::ChangeConfig(int format)
    {
        if (!this->reserved)
        {
            return SCE_AUDIO_ERROR_NOT_RESERVED;
        }

        this->Lock();
        while (this->buffer_used)
        {
            this->thread_status = hle::__KernelGetCurThreadStatus();
            hle::__KernelWaitCurThread(*this, hle::WAITTYPE_AUDIOCHANNEL, this - sceAudio::stream);
            this->Lock();
        }
        this->Unlock();

        this->channels = (format & SCE_AUDIO_FORMAT_MONO) ? 1 : 2;

        return 0;
    }

    int AudioOutputStream::SetDataLength(int frames)
    {
        if (!this->reserved)
        {
            return SCE_AUDIO_ERROR_NOT_RESERVED;
        }

        this->Lock();
        while (this->buffer_used)
        {
            this->thread_status = hle::__KernelGetCurThreadStatus();
            hle::__KernelWaitCurThread(*this, hle::WAITTYPE_AUDIOCHANNEL, this - sceAudio::stream);
            this->Lock();
        }
        this->Unlock();

        u32 size = 2 * frames;

        this->buffer_array.resize(size * 16);

        this->buffer_data   = &(*this->buffer_array.begin());
        this->buffer_size   = size;
        this->buffer_rpos   = 0;
        this->buffer_wpos   = 0;

        return 0;
    }

    int AudioOutputStream::GetRestLength()
    {
        if (!this->reserved)
        {
            return SCE_AUDIO_ERROR_NOT_RESERVED;
        }

        return this->buffer_used;
    }

    static __forceinline f32 CatMullRomInterpolate(f32 y0, f32 y1, f32 y2, f32 y3, f32 mu)
    {
        f32 a0, a1, a2, a3, mu2;

        mu2 = mu * mu;
        a0 = -0.5f * y0 + 1.5f * y1 - 1.5f * y2 + 0.5f * y3;
        a1 =         y0 - 2.5f * y1 + 2 *    y2 - 0.5f * y3;
        a2 = -0.5f * y0             + 0.5f * y2;
        a3 =                     y1;

        return (a0 * mu * mu2 + a1 * mu2 + a2 * mu + a3);
    }

    int AudioOutputStream::Render(f32 *target, u32 count)
    {
        u32  i = 0;
        int  result = paContinue;

        if (!theEmulator.IsRunning())
        {
            return AudioStream::Render(target, count);
        }

        if (!settings.mMuteSound)
        {
            if (this->reserved)
            {
                u32  buffer_size = this->buffer_size * 16;
                u32  frames;
                s16 *source      = this->buffer_data + this->buffer_rpos;
                s32  volume_l    = this->volume[0];
                s32  volume_r    = this->volume[1];
                
                this->Lock();
                frames = this->buffer_used / 2;
                this->Unlock();

                if (frames > 0)
                {
                    if (count < frames)
                    {
                        frames = count;
                    }
                }

                u32 used = frames * 2;
                u32 left = buffer_size - this->buffer_rpos;

                if (frames > 0)
                {
                    if (this->resampler.Active())
                    {
                        this->resampler.inp_data  = source;
                        this->resampler.out_count = u32(count);
                        this->resampler.out_data  = target;
                        this->resampler.inp_count = used / 2;
                        this->resampler.inp_loop  = this->buffer_data;
                        this->resampler.inp_stop  = this->buffer_data + buffer_size;

                        this->resampler.Process(volume_l, volume_r);

                        used -= this->resampler.inp_count * 2;
                        count = this->resampler.out_count;

                        if (left <= used)
                        { 
                            this->buffer_rpos += used - buffer_size;
                        }
                        else
                        {
                            this->buffer_rpos += used;
                        }

                    }
                    else
                    {
                        if (left <= used)
                        { 
                            this->buffer_rpos += used - buffer_size;
                        }
                        else
                        {
                            this->buffer_rpos += used;
                        }

                        if (left <= used)
                        { 
                            for (left /= 2; i < left; ++i)
                            {
                                *target++ = (s32(*(source++) * volume_l) >> 15) / 32767.0f;
                                *target++ = (s32(*(source++) * volume_r) >> 15) / 32767.0f;
                            }
                            source -= buffer_size;
                        }
                        for (; i < frames; ++i)
                        {
                            *target++ = (s32(*(source++) * volume_l) >> 15) / 32767.0f;
                            *target++ = (s32(*(source++) * volume_r) >> 15) / 32767.0f;
                        }
                    }

                    this->Lock();
                    this->buffer_used -= used;
                    this->Unlock();
                }

                if (this->thread_status && (*this->thread_status == 4))
                {
                    theEmulator.AudioEvent(this - sceAudio::stream);
                }
            }
            else
            {
                result = paComplete;
            }
        }

        for (; i < u32(count); ++i)
        {
            *target++ = 0.0f;
            *target++ = 0.0f;
        }

        return result;
    }
}



namespace sceAudio
{
    int sceAudioChReserve(u32 a0, u32 a1, u32 a2)
    {		
        int result;

        int channel = int(a0); 

        if (channel == SCE_AUDIO_NEXT_CHANNEL)
        {
            for (channel = 0; channel < SCE_AUDIO_CHANNEL_MAX; channel++)
            {
                result = stream[channel].Reserve(int(a1), 44100, int(a2));
                
                if (result == 0)
                {
                    result = channel;
                    break;
                }
            }
        }
        else
        {
            if (u32(channel) >= SCE_AUDIO_CHANNEL_MAX)
            {
                result = SCE_AUDIO_ERROR_INVALID_CH;
            }
            else
            {
                result = stream[channel].Reserve(int(a1), 44100, int(a2));
                if (result == 0)
                {
                    result = channel;
                }
            }
        }

        infof(sceAudio, (result < 0 ? "%s(%d, %d, 0x%02X) = 0x%08X" : "%s(%d, %d, 0x%02X) = %d"), "sceAudioChReserve", a0, a1, a2, result);

        return result;
    }

    int sceAudioChRelease(u32 a0)
    {
        int result;

        int channel = int(a0);

        if (u32(channel) >= SCE_AUDIO_CHANNEL_MAX)
        {
            result = SCE_AUDIO_ERROR_INVALID_CH;
        }
        else
        {
            result = stream[channel].Release();
        }

        infof(sceAudio, "%s(%d) = 0x%08X", "sceAudioChRelease", a0, result);

        return result;
    }

    int sceAudioOutput(u32 a0, u32 a1, u32 a2)
    {
        int result;

        int channel = int(a0);

        if (u32(channel) >= SCE_AUDIO_CHANNEL_MAX)
        {
            result = SCE_AUDIO_ERROR_INVALID_CH;
        }
        else
        {
            if (a1 > 0xFFFF)
            {
                result = SCE_AUDIO_ERROR_INVALID_VOLUME;
            }
            else
            {
                result = stream[channel].Output(int(a1), int(a1), a2 ? Memory::addr< s16 >(a2) : 0, false);
            }
        }

        infof(sceAudio, (result < 0 ? "%s(%d, %d, 0x%08X) = 0x%08X" : "%s(%d, %d, 0x%08X) = %d"), "sceAudioOutput", a0, a1, a2, result);

        return result;
    }

    int sceAudioOutputBlocking(u32 a0, u32 a1, u32 a2)
    {
        int result;

        int channel = int(a0);

        if (u32(channel) >= SCE_AUDIO_CHANNEL_MAX)
        {
            result = SCE_AUDIO_ERROR_INVALID_CH;
        }
        else
        {
            if (a1 > 0xFFFF)
            {
                result = SCE_AUDIO_ERROR_INVALID_VOLUME;
            }
            else
            {
                result = stream[channel].Output(int(a1), int(a1), a2 ? Memory::addr< s16 >(a2) : 0, true);
            }
        }

        infof(sceAudio, (result < 0 ? "%s(%d, %d, 0x%08X) = 0x%08X" : "%s(%d, %d, 0x%08X) = %d"), "sceAudioOutputBlocking", a0, a1, a2, result);

        return result;
    }

    int sceAudioOutputPanned(u32 a0, u32 a1, u32 a2, u32 a3)
    {
        int result;

        int channel  = int(a0);

        if (u32(channel) >= SCE_AUDIO_CHANNEL_MAX)
        {
            return SCE_AUDIO_ERROR_INVALID_CH;
        }
        else
        {
            if ((a1|a2) > 0xFFFF)
            {
                return SCE_AUDIO_ERROR_INVALID_VOLUME;
            }
            else
            {
                return stream[channel].Output(int(a1), int(a2), a3 ? Memory::addr< s16 >(a3) : 0, false);
            }
        }

        infof(sceAudio, (result < 0 ? "%s(%d, %d, %d, 0x%08X) = 0x%08X" : "%s(%d, %d, %d, 0x%08X) = %d"), "sceAudioOutputPanned", a0, a1, a2, a3, result);

        return result;
    }

    int sceAudioOutputPannedBlocking(u32 a0, u32 a1, u32 a2, u32 a3)
    {
        int result;

        int channel = int(a0);

        if (u32(channel) >= SCE_AUDIO_CHANNEL_MAX)
        {
            result = SCE_AUDIO_ERROR_INVALID_CH;
        }
        else
        {
            if ((a1|a2) > 0xFFFF)
            {
                result = SCE_AUDIO_ERROR_INVALID_VOLUME;
            }
            else
            {
                result = stream[channel].Output(int(a1), int(a2), a3 ? Memory::addr< s16 >(a3) : 0, true);
            }
        }

        infof(sceAudio, (result < 0 ? "%s(%d, %d, %d, 0x%08X) = 0x%08X" : "%s(%d, %d, %d, 0x%08X) = %d"), "sceAudioOutputPannedBlocking", a0, a1, a2, a3, result);

        return result;
    }

    int sceAudioChangeChannelVolume(u32 a0, u32 a1, u32 a2)
    {
        int result;

        int channel = int(a0);

        if (u32(channel) >= SCE_AUDIO_CHANNEL_MAX)
        {
            result = SCE_AUDIO_ERROR_INVALID_CH;
        }
        else
        {
            if ((a1|a2) > 0xFFFF)
            {
                result = SCE_AUDIO_ERROR_INVALID_VOLUME;
            }
            else
            {
                return stream[channel].ChangeVolume(int(a1), int(a2));
            }

        }

        infof(sceAudio, "%s(%d, %d, %d) = 0x%08X", "sceAudioChangeChannelVolume", a0, a1, a2, result);

        return result;
    }

    int sceAudioChangeChannelConfig(u32 a0, u32 a1)
    {
        int result;

        int channel = int(a0);
        int format  = int(a1);

        if (u32(channel) >= SCE_AUDIO_CHANNEL_MAX)
        {
            result = SCE_AUDIO_ERROR_INVALID_CH;
        }
        else
        {
            result = stream[channel].ChangeConfig(int(a1));
        }

        infof(sceAudio, "%s(%d, 0x%02X) = 0x%08X", "sceAudioChangeChannelConfig", a0, a1, result);

        return result;
    }

    int sceAudioSetChannelDataLen(u32 a0, u32 a1)
    {
        if (settings.mHackDisableAudioFunctions)//TODO bad hack!!! to be removed (needed for gripshift)
        {
            return -1;
        }

        int channel = int(a0);
        int frames  = int(a1);

        int result = SCE_KERNEL_ERROR_OK;

        if (u32(channel) >= SCE_AUDIO_CHANNEL_MAX)
        {
            result = SCE_AUDIO_ERROR_INVALID_CH;
        }
        else
        {
            AudioOutputStream &chan = stream[channel];

            MutexLocker locker(chan);

            if (chan.stream)
            {
                chan.frames = frames;

                result = SCE_KERNEL_ERROR_OK;
            }
            else
            {
                result = SCE_AUDIO_ERROR_NOT_RESERVED;
            }
        }

        infof(sceAudio, "%s(%d, %d) = 0x%08X", "sceAudioSetChannelDataLen", a0, a1, result);

        return result;
    }

    int sceAudioGetChannelRestLen(u32 a0)
    {
        int channel = int(a0);

        int result;

        if (u32(channel) >= SCE_AUDIO_CHANNEL_MAX)
        {
            result = SCE_AUDIO_ERROR_INVALID_CH;
        }
        else
        {
            AudioOutputStream &chan = stream[channel];

            MutexLocker locker(chan);

            if (chan.stream)
            {
                result = (chan.buffer_size - chan.buffer_used) / 2; 
            }
            else
            {
                result = SCE_AUDIO_ERROR_NOT_RESERVED;
            }
        }

        infof(sceAudio, (result < 0 ? "%s(%d) = 0x%08X" : "%s(%d) = %d"), "sceAudioGetChannelRestLen", a0, result);

        return result;
    }

    int sceAudioGetChannelRestLength(u32 a0)
    {
        int channel = int(a0);

        int result;

        if (u32(channel) >= SCE_AUDIO_CHANNEL_MAX)
        {
            result = SCE_AUDIO_ERROR_INVALID_CH;
        }
        else
        {
            AudioOutputStream &chan = stream[channel];

            MutexLocker locker(chan);

            if (chan.stream)
            {
                result = (chan.buffer_size - chan.buffer_used) / 2; 
            }
            else
            {
                result = SCE_AUDIO_ERROR_NOT_RESERVED;
            }
        }

        infof(sceAudio, (result < 0 ? "%s(%d) = 0x%08X" : "%s(%d) = %d"), "sceAudioGetChannelRestLength", a0, result);

        return result;
    }


    int sceAudioOneshotOutput(u32 a0, u32 a1, u32 a2, u32 a3, u32 t0, u32 t1)
    {
        int channel = int(a0);
        int frames  = int(a1);
        int format  = int(a2);
        int volL    = int(a3);
        int volR    = int(t0);
        int addr    = int(t1);

        //TODO implement me
        errorf(sceAudio, "UNIMPLEMENTED sceAudioOneshotOutput function");
        return -1;
    }



    int sceAudioSRCChReserve(u32 a0, u32 a1, u32 a2)
    {
        int result = stream[8].Reserve(int(a0), int(a1), int(a2 != 2));
        if (result == 0)
        {
            result = 8;
        }

        infof(sceAudio, (result < 0 ? "%s(%d, %d, %d) = 0x%08X" : "%s(%d, %d, %d) = %d"), "sceAudioSRCChReserve", a0, a1, a2, result);

        return result < 0 ? result : SCE_KERNEL_ERROR_OK;
    }

    int sceAudioSRCChRelease()
    {
        int result = stream[8].Release();

        infof(sceAudio, (result < 0 ? "%s() = 0x%08X" : "%s() = %d"), "sceAudioSRCChRelease", result);

        return result;
    }

    int sceAudioSRCOutputBlocking(u32 a0, u32 a1)
    {
        int result = stream[8].Output(int(a0), int(a0), a1 ? Memory::addr< s16 >(a1) : 0, true);

        infof(sceAudio, (result < 0 ? "%s(%d, 0x%08X) = 0x%08X" : "%s(%d, 0x%08X) = %d"), "sceAudioSRCOutputBlocking", a0, a1, result);

        return result < 0 ? result : SCE_KERNEL_ERROR_OK;
    }


    int sceAudioOutput2Reserve(u32 a0 /* frames */)
    {
        int result = stream[8].Reserve(int(a0), 44100, 0);
        if (result == 0)
        {
            result = 8;
        }

        infof(sceAudio, (result < 0 ? "%s(%d) = 0x%08X" : "%s(%d) = %d"), "sceAudioOutput2Reserve", a0, result);

        return result < 0 ? result : SCE_KERNEL_ERROR_OK;
    }

    int sceAudioOutput2Release()
    {
        int result = stream[8].Release();

        infof(sceAudio, (result < 0 ? "%s() = 0x%08X" : "%s() = %d"), "sceAudioOutput2Release", result);

        return result;
    }

    int sceAudioOutput2OutputBlocking(u32 a0, u32 a1)
    {       
        int result = stream[8].Output(int(a0), int(a0), a1 ? Memory::addr< s16 >(a1) : 0, true);

        infof(sceAudio, (result < 0 ? "%s(%d, 0x%08X) = 0x%08X" : "%s(%d, 0x%08X) = %d"), "sceAudioOutput2OutputBlocking", a0, a1, result);

        return result < 0 ? result : SCE_KERNEL_ERROR_OK;
    }

    int sceAudioOutput2ChangeLength(u32 a0)
	{
        if (settings.mHackDisableAudioFunctions)//TODO bad hack to be removed!!!!
        {
            return -1;
        }

        int frames  = int(a0);

        int result;

        AudioOutputStream &chan = stream[8];

        MutexLocker locker(chan);

        if (chan.stream)
        {
            if (chan.buffer_used)
            {
                return SCE_AUDIO_ERROR_OUTPUT_BUSY;
            }

            stream[8].frames = frames;

            result = SCE_KERNEL_ERROR_OK;
        }
        else
        {
            result = SCE_AUDIO_ERROR_NOT_RESERVED;
        }

        infof(sceAudio, "%s(%d) = 0x%08X", "sceAudioOutput2ChangeLength", a0, result);

        return result;
	}
	
    int sceAudioOutput2GetRestSample()
    {
        int result;

        AudioOutputStream &chan = stream[8];

        MutexLocker locker(chan);

        if (chan.stream)
        {
            result = (chan.buffer_size - chan.buffer_used) / 2; 
        }
        else
        {
            result = SCE_AUDIO_ERROR_NOT_RESERVED;
        }

        infof(sceAudio, (result < 0 ? "%s() = 0x%08X" : "%s() = %d"), "sceAudioOutput2GetRestSample", result);

        return result;
    }



    int sceAudioInputInit()
    {
        //TODO implement me
        errorf(sceAudio,"UNIMPLEMENTED sceAudioInputInit function");
        return -1;
    }

    int sceAudioInputInitEx()
    {
        //TODO implement me
        errorf(sceAudio,"UNIMPLEMENTED sceAudioInputInitEx function");
        return -1;
    }

    int sceAudioInput()
    {
        //TODO implement me
        errorf(sceAudio,"UNIMPLEMENTED sceAudioInput function");
        return -1;
    }

    int sceAudioInputBlocking()
    {
        //TODO implement me
        errorf(sceAudio,"UNIMPLEMENTED sceAudioInputBlocking function");
        return -1;
    }

    int sceAudioPollInputEnd()
    {
        //TODO implement me
        errorf(sceAudio,"UNIMPLEMENTED sceAudioPollInputEnd function");
        return -1;
    }

    int sceAudioWaitInputEnd()
    {
        //TODO implement me
        errorf(sceAudio,"UNIMPLEMENTED sceAudioWaitInputEnd function");
        return -1;
    }

    int sceAudioGetInputLength()
    {
        //TODO implement me
        errorf(sceAudio,"UNIMPLEMENTED sceAudioGetInputLength function");
        return -1;
    }


    static u32 gcd(u32 a, u32 b)
    {
        if (a == 0)
        {
            return b;
        }
        if (b == 0)
        {
            return a;
        }
        while (1)
        {
            if (a > b)
            {
                a = a % b;
                if (a == 0)
                {
                    return b;
                }
                if (a == 1)
                {
                    return 1;
                }
            }
            else
            {
                b = b % a;
                if (b == 0)
                {
                    return a;
                }
                if (b == 1)
                {
                    return 1;
                }
            }
        }    
        return 1; 
    }

    static double sinc(double x)
    {
        x = fabs(x);
        if (x < 1e-6)
        {
            return 1.0;
        }
        x *= M_PI;
        return sin(x) / x;
    }


    static double wind(double x)
    {
        x = fabs(x);
        if (x >= 1.0)
        {
            return 0.0f;
        }
        x *= M_PI;
        return 0.384 + 0.500 * cos(x) + 0.116 * cos(2 * x);
    }



    AudioResamplerTable::AudioResamplerTable(u32 ra, u32 rb, u32 hl, u32 fr)
    :   m_ra(ra)
    ,   m_rb(rb)
    ,   m_hl(hl)
    ,   m_fr(fr)
    {
        u32    i, j;
        double s, t, w;
        f32   *p;

        m_ctab = new f32[m_hl * (rb + 1)];
        p = m_ctab;
        s = double(rb) / double(ra);
        w = 1e-4 * m_fr;
        if (s < 1.0)
        {
            w *= s;
        }
        for (j = 0; j <= rb; j++)
        {
            t = double(j) / double(rb);
            for (i = 0; i < m_hl; i++)
            {
                p[m_hl - i - 1] = f32(w * sinc(t * w) * wind(t / m_hl));
                t += 1;
            }
            p += m_hl;
        }
    }


    AudioResamplerTable::~AudioResamplerTable()
    {
        delete[] m_ctab;
    }


    AudioResamplerTable *AudioResamplerTable::Create(u32 ra, u32 rb, u32 hl, u32 fr)
    {
        u64                  key = (u64(ra)<<32)|rb;
        AudioResamplerTable *tab = tables.object(key);

        if (!tab)
        {
            tab = new AudioResamplerTable(ra, rb, hl, fr);
            tables.insert(key, tab);
        }
        return tab;
    }

    AudioResampler::AudioResampler()
    :   m_table(0)
    ,   m_buff(0)
    ,   m_nchan(0)
    {
        Reset();
    }


    AudioResampler::~AudioResampler()
    {
        Clear();
    }


    void AudioResampler::Clear()
    {
        delete[] m_buff;
        m_buff = 0;
        m_table = 0;
        m_nchan = 0;
        Reset();
    }


    bool AudioResampler::Setup(u32 fs_inp, u32 fs_out, u32 nchan)
    {
        if (fs_inp == fs_out)
        {
            Clear();
            return true;
        }
            
        u32                  a, b, h, k = 0;
        f32                 *buf        = 0;
        AudioResamplerTable *tab        = 0;

        if (fs_inp && fs_out && nchan)
        {
            k = gcd(fs_inp, fs_out);
            a = fs_inp / k;
            b = fs_out / k;
            if ((16 * a >= b) && (b <= 1000))
            {
                h = 32;
                k = 250;
                if (a > b) 
                {
                    h = (h * a + b - 1) / b;
                    k = (k * a + b - 1) / b;
                }
                tab = AudioResamplerTable::Create(a, b, h, 10000 - 26000 / 32);
                buf = new f32[nchan * (2 * h - 1 + k)];
            }
        }

        Clear();
        
        if (tab)
        {
            m_table = tab;
            m_buff  = buf;
            m_nchan = nchan;
            m_inmax = k;
            return Reset();
        }

        return false;
    }


    bool AudioResampler::Reset()
    {
        if (m_table)
        {
            inp_count = 0;
            out_count = 0;
            inp_data = 0;
            out_data = 0;
            m_index = 0;
            m_phase = 0; 
            m_nread = 2 * m_table->m_hl;

            return true;
        }

        return false;
    }

    bool AudioResampler::Process(s32 volume_l, s32 volume_r)
    {
        u32  hl, ra, rb, in, nr, ph, i, n, c;
        f32 *p1, *p2;

        if (!m_table)
        {
            return false;
        }

        hl = m_table->m_hl;
        ra = m_table->m_ra * hl;
        rb = m_table->m_rb * hl;
        in = m_index;
        nr = m_nread;
        ph = m_phase;
        n = (2 * hl - nr) * 2;
        p1 = m_buff + in * 2;
        p2 = p1 + n;

        while (out_count)
        {
            if (nr)
            {
                if (inp_count == 0)
                {
                    break;
                }
                if (inp_stop <= inp_data)
                {
                    inp_data = inp_loop;
                }
                if (inp_data)
                {
                    if (m_nchan == 2)
                    {
                        p2[0] = ((s32(*inp_data++) * volume_l) >> 15) / 32767.0f;
                        p2[1] = ((s32(*inp_data++) * volume_r) >> 15) / 32767.0f;
                    }
                    else
                    {
                        p2[0] = ((s32(*inp_data+0) * volume_l) >> 15) / 32767.0f;
                        p2[1] = ((s32(*inp_data++) * volume_r) >> 15) / 32767.0f;
                    }
                }
                else
                {
                    p2[0] = 0.0f;
                    p2[1] = 0.0f;
                }
                nr--;
                p2 += 2;
                inp_count--;
            }
            else
            {
                if (out_data)
                {
                    f32 *c1 = m_table->m_ctab + ph;
                    f32 *c2 = m_table->m_ctab + rb - ph;
                    f32 s;
                    for (c = 0; c < m_nchan; c++)
                    {
                        f32 *q1 = p1 + c;
                        f32 *q2 = p2 + c;
                        for (i = 0; i < hl; i++)
                        {
                            s = 1e-20f;
                            q2 -= 2;
                            s += *q1 * c1[i] + *q2 * c2[i];
                            q1 += 2;
                        }
                        s -= 1e-20f;
                        *out_data++ = s;
                    }
                    if (c == 1)
                    {
                        *out_data++ = s;        
                    }
                }
                out_count--;
                ph += ra;
                if (ph >= rb)
                {
                    nr = ph / rb;
                    ph -= nr * rb;
                    in += nr;
                    p1 += nr * 2;
                    if (in >= m_inmax)
                    {
                        n = (2 * hl - nr) * 2;
                        ::memcpy(m_buff, p1, n * sizeof(f32));
                        in = 0;
                        p1 = m_buff;
                        p2 = p1 + n;
                    }
                }
            }
        }

        m_index = in;
        m_nread = nr;
        m_phase = ph;

        return true;
    }
}

namespace syscalls
{
    void sceAudioChReserve(AlContext &context)             { V0 = sceAudio::sceAudioChReserve(A0, A1, A2);                 }
    void sceAudioChRelease(AlContext &context)             { V0 = sceAudio::sceAudioChRelease(A0);                         }
    void sceAudioOutput(AlContext &context)                { V0 = sceAudio::sceAudioOutput(A0, A1, A2);                    }
    void sceAudioOutputBlocking(AlContext &context)        { V0 = sceAudio::sceAudioOutputBlocking(A0, A1, A2);            }
    void sceAudioOutputPanned(AlContext &context)          { V0 = sceAudio::sceAudioOutputPanned(A0, A1, A2, A3);          }
    void sceAudioOutputPannedBlocking(AlContext &context)  { V0 = sceAudio::sceAudioOutputPannedBlocking(A0, A1, A2, A3);  }
    void sceAudioChangeChannelVolume(AlContext &context)   { V0 = sceAudio::sceAudioChangeChannelVolume(A0, A1, A2);       }
    void sceAudioChangeChannelConfig(AlContext &context)   { V0 = sceAudio::sceAudioChangeChannelConfig(A0, A1);           }
	void sceAudioSetChannelDataLen(AlContext &context)     { V0 = sceAudio::sceAudioSetChannelDataLen(A0, A1);             }
    void sceAudioGetChannelRestLen(AlContext &context)     { V0 = sceAudio::sceAudioGetChannelRestLen(A0);                 }
	void sceAudioGetChannelRestLength(AlContext &context)  { V0 = sceAudio::sceAudioGetChannelRestLength(A0);              }

    void sceAudioOneshotOutput(AlContext &context)         { V0 = sceAudio::sceAudioOneshotOutput(A0, A1, A2, A3, T0, T1); }

    void sceAudioSRCChReserve(AlContext &context)          { V0 = sceAudio::sceAudioSRCChReserve(A0, A1, A2);              }
    void sceAudioSRCChRelease(AlContext &context)          { V0 = sceAudio::sceAudioSRCChRelease();                        }
    void sceAudioSRCOutputBlocking(AlContext &context)     { V0 = sceAudio::sceAudioSRCOutputBlocking(A0, A1);             }

    void sceAudioOutput2Reserve(AlContext &context)        { V0 = sceAudio::sceAudioOutput2Reserve(A0);                    }
    void sceAudioOutput2Release(AlContext &context)        { V0 = sceAudio::sceAudioOutput2Release();                      }
    void sceAudioOutput2OutputBlocking(AlContext &context) { V0 = sceAudio::sceAudioOutput2OutputBlocking(A0, A1);         }
	void sceAudioOutput2ChangeLength(AlContext &context)   { V0 = sceAudio::sceAudioOutput2ChangeLength(A0);               }
    void sceAudioOutput2GetRestSample(AlContext &context)  { V0 = sceAudio::sceAudioOutput2GetRestSample();                }

    void sceAudioInputInit(AlContext &context)             { V0 = sceAudio::sceAudioInputInit();                           }
    void sceAudioInputInitEx(AlContext &context)           { V0 = sceAudio::sceAudioInputInitEx();                         }
    void sceAudioInput(AlContext &context)                 { V0 = sceAudio::sceAudioInput();                               }
    void sceAudioInputBlocking(AlContext &context)         { V0 = sceAudio::sceAudioInputBlocking();                       }
    void sceAudioPollInputEnd(AlContext &context)          { V0 = sceAudio::sceAudioPollInputEnd();                        }
    void sceAudioWaitInputEnd(AlContext &context)          { V0 = sceAudio::sceAudioWaitInputEnd();                        }
    void sceAudioGetInputLength(AlContext &context)        { V0 = sceAudio::sceAudioGetInputLength();                      }
}
