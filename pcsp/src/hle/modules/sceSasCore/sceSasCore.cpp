#include "stdafx.h"
#include "sceSasCore.h"
#include "hle/types.h"
#include "hle/kernel.h"
#include "log.h"

#include "qt4/settings.h"

#include <QtConcurrentMap>

#include <vector>

#include "sceSasCore.h"

namespace sceSasCore
{
    static bool ready = false;

    SasCore *sas_core = 0;

    bool Reboot()
    {
        if (!ready || ShutDown())
        {
            if (theKernelModuleManager.SyscallsModuleExists("sceAudio"))
            {
                SasCore::Reboot();
                ready = true;
                return true;
            }
        }

        return false;
    }

    bool ShutDown()
    {
        if (ready)
        {
            delete sas_core;

            sas_core = 0;

            ready = false;
            return true;
        }
        return !ready;
    }
}

namespace sceSasCore
{
#if 0
    bool SasADSR::Calculate()
    {
        if (releasing && (phase < 5))
        {
            phase = 5;
        }

        switch (phase)
        {
        case 1: // attack
            if (value == 0x7FFFFFFF)
            {
                ++phase;
                break;
            }

            if (AM && (value >= 0x60000000))
            {
                value += SasCore::rate_value[(AR ^ 0x7F) - 0x18 + 32];
            }
            else
            {
                value += SasCore::rate_value[(AR ^ 0x7F) - 0x10 + 32];
            }

            if (value < 0)
            {
                ++phase;
                value = 0x7FFFFFFF;
            }
            break;

        case 2: // decay
            {
                u32 offset = SasCore::rate_offset[(value >> 28) & 7];
                value -= SasCore::rate_value[((DR ^ 0x1F)*4) - 0x18 + offset + 32];

                s32 sustain_level = ((0x80000000 / 0x10) * (SL + 1)) - 1;

                if (value <= sustain_level)
                {
                    if (value < 0)
                    {
                        value = 0;
                    }
                    ++phase;
                }
            }
            break;

        case 3: // sustain
            {
                if (SR == 0x7F)
                {
                    return true;
                }

                if (SM & 2) // decreasing
                {
                    if (SM & 4) // exponential
                    {
                        u32 offset = SasCore::rate_offset[(value >> 28) & 7];
                        value -= SasCore::rate_value[(SR ^ 0x7F) - 0x1B + offset + 32];
                    }
                    else // linear
                    {
                        value -= SasCore::rate_value[(SR ^ 0x7F) - 0x0F + 32];
                    }

                    if (value <= 0)
                    {
                        value = 0;
                        ++phase;
                    }
                }
                else // increasing
                {
                    value += SasCore::rate_value[(SR ^ 0x7F) - (((SM & 4) && (value >= 0x60000000)) ? 0x18 : 0x10) + 32];

                    if (value < 0)
                    {
                        value = 0x7FFFFFFF;
                        ++phase;
                    }
                }
            }
            break;

        case 4: // sustain end
            value = (SM & 2) ? 0 : 0x7FFFFFFF;
            if (value == 0)
            {
                phase = 6;
            }
            break;

        case 5: // release
            if (RM) // exponential
            {
                u32 offset = SasCore::rate_offset[(value >> 28) & 7];
                value -= SasCore::rate_value[((RR ^ 0x1F)*4) - 0x18 + offset + 32];
            }
            else // linear
            {
                if (RR != 0x1F)
                {
                    value -= (1 << (0x1F - RR));
                }
            }

            if (value <= 0)
            {
                value = 0;
                ++phase;
            }
            break;

        case 6: // release end
        default:
            value = 0;
            break;
        }

        // returns true if the voice is active, or false if it's stopping.
        return phase != 6;
    }
#endif
}

namespace sceSasCore
{
    char const *SasCore::m_object_type = "SasCore";

    void SasCore::GetQuickInfos(char *data, size_t size)
    {
        ::snprintf(data, size, "{ frames: %d, frequency:%d, voices:%d }", frames, frequency, voices);
    }

    __forceinline SasCore::SasCore()
    :   KernelObject("SceSasCore")
    {
    }

    __forceinline SasCore::~SasCore()
    {
        Mutex::Lock();

        for (u32 i = 0; i < voices; ++i)
        {
            voice[i].Release();
        }

        Mutex::Unlock();
    }

    void SasCore::Reboot()
    {
        //for (u32 i = 0; i < (32+128); ++i)
        //{
        //    s32 shift = (i - 32) >> 2;
        //    s64 rate  = (i & 3) + 4;
        //    
        //    if (shift < 0)
        //    {
        //        rate >>= -shift;
        //    }
        //    else
        //    {
        //        rate <<= shift;
        //    }

        //    this->rate_value[i] = Min(rate, 0x3FFFFFFFLL);
        //}
    }
}

namespace sceSasCore
{
    __forceinline SasVoice::SasVoice()
    :   AudioStream()
    ,   data(0)
    ,   start(0)
    ,   end(0)
    ,   loop(0)
    ,   pitch(4096)
    ,   core(0)
    {
        dry_volume[0] = SCE_SAS_VOLUME_MAX;
        dry_volume[1] = SCE_SAS_VOLUME_MAX;
        wet_volume[0] = SCE_SAS_VOLUME_MAX;
        wet_volume[1] = SCE_SAS_VOLUME_MAX;
    }

    __forceinline SasVoice::~SasVoice()
    {
    }

    __forceinline int SasVoice::Setup(int frames, int frequency)
    {
        if (!this->reserved)
        {
            if (sample_rate)
            {
                this->resampler.Setup(frequency, sample_rate, 2);

                this->frequency     = frequency;
                this->frames        = frames;
                this->reserved      = true;

                return 0;
            }
        }

        return -1;
    }

    __forceinline int SasVoice::Reserve(int frames, int frequency)
    {
        if (u32(frames - 17) > 4111)
        {
            return SCE_AUDIO_ERROR_INVALID_SIZE;
        }

        return this->Setup(frames, frequency);
    }

    __forceinline int SasVoice::Release()
    {
        if (this->reserved)
        {
            Pa_CloseStream(this->stream);

            this->reserved = 0;
        }

        return 0;
    }

    __forceinline int SasVoice::KeyOn()
    {
        data = start;

        Output();

        return 0;
    }

    __forceinline int SasVoice::KeyOff()
    {
        return 0;
    }

    __forceinline int SasVoice::SetVolume(s32 dl, s32 dr, s32 wl, s32 wr)
    {
        if ((u32(dl + SCE_SAS_VOLUME_MAX) <= 2 * SCE_SAS_VOLUME_MAX) &&
            (u32(dr + SCE_SAS_VOLUME_MAX) <= 2 * SCE_SAS_VOLUME_MAX) &&
            (u32(wl + SCE_SAS_VOLUME_MAX) <= 2 * SCE_SAS_VOLUME_MAX) &&
            (u32(wr + SCE_SAS_VOLUME_MAX) <= 2 * SCE_SAS_VOLUME_MAX))
        {
            dry_volume[0] = dl;
            dry_volume[1] = dr;
            wet_volume[0] = wl;
            wet_volume[1] = wr;

            return 0;
        }
        return SCE_SAS_ERROR_VOLUME;
    }

    __forceinline int SasVoice::SetPitch(u32 pitch)
    {
        resampler.Setup((pitch * this->frequency) / 4096, this->sample_rate, 2);

        return 0;
    }

    __forceinline int SasVoice::SetADPCMData(u32 data, u32 size, bool loop_mode)
    {
        m_pcm_buffer.resize(2 * 28 * ((size + 15)/16));

        DecodeADPCM(Memory::addr< u8 >(data), &(*m_pcm_buffer.begin()), size);

        if (!loop_mode)
        {
            loop = 0;
        }
        
        return 0;
    }

    __forceinline int SasVoice::SetPCMData(u32 data, u32 size, s32 loop_size)
    {
        m_pcm_buffer.resize(2 * size);

        start = &(*m_pcm_buffer.begin());
        end   = start + 2 * size;
        loop  = (loop_size >= 0) ? (start + 2 * loop_size) : 0;

        s16 *target = start;
        s16 *source = Memory::addr< s16 >(data);

        for (u32 i = 0; i < size; ++i)
        {
            *(target++) = *(source+0);
            *(target++) = *(source++);
        }

        return 0;
    }

    __forceinline void SasVoice::DecodeADPCM(u8 const *source, s16 *target, u32 size)
    {
        if (source)
        {
            s32 h1 = 0;
            s32 h2 = 0;

            static s32 vag_f[5][2] =
            {
                {   0,     },
                {  60,     },
                { 115, -52 },
                {  98, -55 },
                { 122, -60 }
            };

            this->start = target;

            for (u32 i = 0; i <= (size - 16); i += 16)
            {
                u32 n = *source++;
                u32 predict_nr = n >> 4;
                if (predict_nr >= 5)
                {
                    if (predict_nr == 7)
                    {
                        break; // A predict_nr of 7 indicates the end of audio data.
                    }
                    predict_nr = 0;
                }
                u32 shift_factor = n & 0x0F;
                u32 flag = *source++;

                if (flag & 1)
                {
                    break;
                }
                else if (flag & 4)
                {
                    this->loop = target;
                }

                s32 vag_f1 = vag_f[predict_nr][0];
                s32 vag_f2 = vag_f[predict_nr][1];

                for (int j = 0; j < 28; j += 2)
                {
                    u32 d     = *source++;
                    s32 s1    = s16((d >> 0) << 12) >> shift_factor;
                    s32 s2    = s16((d >> 4) << 12) >> shift_factor;
                    s1       += ((h1 * vag_f1) + (h2 * vag_f2)) >> 6;
                    s2       += ((s1 * vag_f1) + (h1 * vag_f2)) >> 6;
                    h2        = s1;
                    h1        = s2;
                    *target++ = s16(h2);
                    *target++ = s16(h2);
                    *target++ = s16(h1);
                    *target++ = s16(h1);
                }

            }

            this->end = target;
        }
    }

    void SasVoice::Output()
    {
        if (reserved)
        {
            if (data)
            {
                resampler.inp_data  = start;
                resampler.inp_count = u32(-1);
                resampler.inp_loop  = loop;
                resampler.inp_stop  = end;

                sas_core->ended &= ~(1 << (this - core->voice)); 

                if (!Pa_IsStreamActive(stream))
                {
                    PaError err = Pa_StartStream(stream);
                    if (err != paNoError)
                    {
                        errorf(sceAudio, "PortAudio error: %s", Pa_GetErrorText(err));
                    }
                }

                return;
            }
        }
    }

    int SasVoice::Render(f32 *target, u32 count)
    {
        int  result = paContinue;
        u32  i      = 0;
        u32  mask   = u32(1) << (this - core->voice);

        if (!settings.mMuteSound)
        {
            if (reserved && data)
            {
                if (resampler.Active())
                {
                    resampler.out_count  = count;
                    resampler.out_data   = target;
                    resampler.inp_loop = loop;

                    if (~core->key & mask)
                    {
                        resampler.inp_loop = 0;
                    }

                    resampler.Process(min(max(-32768, (dry_volume[0] << 3)), 32767), min(max(-32768, (dry_volume[1] << 3)), 32767));

                    if (!resampler.inp_data)
                    {
                        core->Lock();

                        core->key   &= ~mask;
                        core->ended |=  mask;

                        data = 0;

                        core->Unlock();

                        result = paComplete;
                    }

                    count = resampler.out_count;
                }
                else
                {
                    s16  volume_l = min(max(-32768, (dry_volume[0] << 3)), 32767); 
                    s16  volume_r = max(max(-32768, (dry_volume[1] << 3)), 32767); 
                    s16 *source   = resampler.inp_data;
                    s16 *limit    = resampler.inp_stop;
                    s16 *loop     = resampler.inp_loop;

                    for (; i < count; ++i)
                    {
                        if (limit <= source)
                        {
                            source = loop;

                            if (!loop)
                            {
                                core->Lock();

                                core->key   &= ~mask;
                                core->ended |=  mask;

                                data = 0;

                                core->Unlock();

                                result = paComplete;

                                break;
                            }
                        }

                        *target++ = (s32(*(source++) * volume_l) >> 15) / 32767.0f;
                        *target++ = (s32(*(source++) * volume_r) >> 15) / 32767.0f;

                        --resampler.inp_count;
                        --resampler.out_count;
                    }

                    resampler.inp_data = source;
                    resampler.out_data = target;
                }
            }
            else
            {
                core->Lock();

                core->key   &= ~mask;
                core->ended |=  mask;

                core->Unlock();

                result = paAbort;
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


namespace sceSasCore
{
    int __sceSasInit(u32 a0, u32 a1, u32 a2, u32 a3, u32 t0)
    {
        int result;

        if ((a1 & 31) || (2048 < a1) || (a1 < 64))
        {
            result = SCE_SAS_ERROR_GRAIN_SAMPLES;
        }
        else if (32 < a2)
        {
            result = SCE_SAS_ERROR_VOICES;
        }
        else if (1 < a3)
        {
            result = SCE_SAS_ERROR_OUTPUT_MODE;
        }
        else if (t0 != 44100)
        {
            result = SCE_SAS_ERROR_FREQUENCY;
        }
        else if (sas_core)
        {
            result = SCE_SAS_ERROR_ALREADYINITED;
        }
        else
        {
            sas_core = new SasCore;

            sas_core->frames      = a1;
            sas_core->voices      = a2;
            sas_core->output_mode = a3;
            sas_core->frequency   = t0;

            sas_core->key         = 0;
            sas_core->pause       = 0;
            sas_core->ended       = 0xFFFFFFFF;

            for (u32 i = 0; i < a2; ++i)
            {
                if (sas_core->voice[i].Initialize())
                {
                    if (!sas_core->voice[i].Reserve(int(a1), int(t0)))
                    {
                        sas_core->voice[i].core = sas_core;
                    }
                }
            }

            Memory::mem< SasCore * >(a0) = sas_core;

            result = 0;
        }

        infof(sceAudio, "%s(0x%08X, %d, %d, %d, %d) = 0x%08X", "__sceSasInit", a0, a1, a2, a3, t0, result);

        return result;
    }

    int __sceSasCore(u32 a0, u32 a1)
    {
        int result;

        SasCore &core = **(Memory::addr< SasCore * >(a0));

        if (a1 & 31)
        {
            result = SCE_SAS_ERROR_ADDRESS;
        }
        else
        {
#if 0
            core.Lock();

            u32 mask = core.ended & ~core.pause & core.key;

            for (u32 i = 0; i < core.voices; ++i)
            {
                if ((1 << i) & mask)
                {
                    core.voice[i].Output();
                }
            }

            core.Unlock();
#endif

            // some games are not zeroing the output buffer out, so we need to do it to avoid garbage in sound
            ::memset(Memory::addr< void >(a1), 0, 2 * sizeof(s16) * core.frames);
        }

        infof(sceAudio, "%s(0x%08X, 0x%08X) = 0", "__sceSasCore", a0, a1);

        return 0;
    }

    int __sceSasCoreWithMix(u32 a0, u32 a1, u32 a2, u32 a3)
    {
        int result;

        SasCore &core = **(Memory::addr< SasCore * >(a0));

        if (a1 & 31)
        {
            result = SCE_SAS_ERROR_ADDRESS;
        }
        else
        {
#if 0
            core.Lock();

            u32 mask = core.ended & ~core.pause & core.key;

            for (u32 i = 0; i < core.voices; ++i)
            {
                if ((1 << i) & mask)
                {
                    core.voice[i].Output();
                }
            }

            core.Unlock();
#endif
            s16 *target = Memory::addr< s16 >(a1);
            s16 *source = target;
            s32 volume_l = s16(min(max(0, (a2 << 3)), 32767));
            s32 volume_r = s16(min(max(0, (a3 << 3)), 32767));
            for (u32 i = 0; i < core.frames; ++i)
            {
                *target++ = (volume_l * *(source++)) >> 15;
                *target++ = (volume_r * *(source++)) >> 15;
            }
        }

        infof(sceAudio, "%s(0x%08X, 0x%08X, %d, %d) = 0", "__sceSasCoreWithMix", a0, a1, a2, a3);

        return 0;
    }


    int __sceSasSetKeyOn(u32 a0, u32 a1)
    {
        int result;

        SasCore &core = **(Memory::addr< SasCore * >(a0));

        if (a1 < SCE_SAS_VOICE_MAX)
        {
            core.Lock();

            result = core.voice[a1].KeyOn();

            core.key |= (1 << a1);

            core.Unlock();

        }
        else
        {
            result = SCE_SAS_ERROR_VOICE_INDEX;
        }

        infof(sceAudio, "%s(0x%08X, %d) = 0x%08X", "__sceSasSetKeyOn", a0, a1, result);

        return result; 
    }

    int __sceSasSetKeyOff(u32 a0, u32 a1)
    {
        int result;

        SasCore &core = **(Memory::addr< SasCore * >(a0));

        if (a1 < SCE_SAS_VOICE_MAX)
        {
            core.Lock();

            result = core.voice[a1].KeyOff();

            core.key &= ~(1 << a1);

            core.Unlock();
        }
        else
        {
            result = SCE_SAS_ERROR_VOICE_INDEX;
        }

        infof(sceAudio, "%s(0x%08X, %d) = 0x%08X", "__sceSasSetKeyOff", a0, a1, result);

        return result;
    }



    int __sceSasSetPause(u32 a0, u32 a1, u32 a2)
    {
        int result = 0;

        SasCore &core = **(Memory::addr< SasCore * >(a0));

        core.Lock();

        if (a2)
        {
            core.pause |= a1 & ~(0xFFFFFFFF << core.voices);
        }
        else
        {
            core.pause &= ~a1 | (0xFFFFFFFF << core.voices);
        }

        core.Unlock();

        infof(sceAudio, "%s(0x%08X, 0x%02X, %d) = 0x%08X", "__sceSasSetPause", a0, a1, a2, result);

        return result;
    }

    int __sceSasGetPauseFlag(u32 a0)
    {
        SasCore &core = **(Memory::addr< SasCore * >(a0));

        int result = core.pause & ~(0xFFFFFFFF << core.voices);

        infof(sceAudio, "%s(0x%08X) = 0x%02X", "__sceSasGetPauseFlag", a0, result);

        return result;
    }



    int __sceSasSetVolume(u32 a0, u32 a1, u32 a2, u32 a3, u32 t0, u32 t1)
    {
        int result;

        SasCore &core = **(Memory::addr< SasCore * >(a0));

        if (a1 < SCE_SAS_VOICE_MAX)
        {
            result = core.voice[a1].SetVolume(s32(a2), s32(a3), s32(t0), s32(t1));
        }
        else
        {
            result = SCE_SAS_ERROR_VOICE_INDEX;
        }

        infof(sceAudio, "%s(0x%08X, %d, %d, %d, %d, %d) = 0x%08X", "__sceSasSetVolume", a0, a1, a2, a3, t0, t1, result);

        return result;
    }

    int __sceSasSetPitch(u32 a0, u32 a1, u32 a2)
    {
        int result;

        SasCore &core = **(Memory::addr< SasCore * >(a0));

        if (a1 < SCE_SAS_VOICE_MAX)
        {
            SasVoice &voice = core.voice[a1];

            MutexLocker locker(voice);

            result = voice.SetPitch(a2);            
        }
        else
        {
            result = SCE_SAS_ERROR_VOICE_INDEX;
        }

        infof(sceAudio, "%s(0x%08X, %d, %d) = 0x%08X", "__sceSasSetPitch", a0, a1, a2, result);

        return result;
    }

    int __sceSasSetVoice(u32 a0, u32 a1, u32 a2, u32 a3, u32 t0)
    {
        int result;

        SasCore &core = **(Memory::addr< SasCore * >(a0));

        if (a1 < SCE_SAS_VOICE_MAX)
        {
            SasVoice &voice = core.voice[a1];

            MutexLocker locker(voice);

            result = voice.SetADPCMData(a2, a3, t0);
        }
        else
        {
            result = SCE_SAS_ERROR_VOICE_INDEX;
        }

        infof(sceAudio, "%s(0x%08X, %d, 0x%08X, %d, %d) = 0x%08X", "__sceSasSetVoice", a0, a1, a2, a3, t0, result);

        return result;
    }

    int __sceSasSetVoicePCM(u32 a0, u32 a1, u32 a2, u32 a3, u32 t0)
	{
        int result;

        SasCore &core = **(Memory::addr< SasCore * >(a0));

        if (a1 < SCE_SAS_VOICE_MAX)
        {
            SasVoice &voice = core.voice[a1];

            MutexLocker locker(voice);

            result = voice.SetPCMData(a2, a3, t0);
        }
        else
        {
            result = SCE_SAS_ERROR_VOICE_INDEX;
        }

        infof(sceAudio, "%s(0x%08X, %d, 0x%08X, %d, %d) = 0x%08X", "__sceSasSetVoicePCM", a0, a1, a2, a3, t0, result);

        return result;
	}

    int __sceSasSetNoise()
    {
        //TODO implement me
        errorf(sceSasCore,"UNIMPLEMENTED __sceSasSetNoise function");
        return 0;
    }

    int __sceSasSetADSR()
    {
        //TODO implement me
        errorf(sceSasCore,"UNIMPLEMENTED __sceSasSetADSR function");
        return 0;
    }

    int __sceSasSetADSRmode()
    {
        //TODO implement me
        errorf(sceSasCore,"UNIMPLEMENTED __sceSasSetADSRmode function");
        return 0;
    }

    int __sceSasSetSL()
    {
        //TODO implement me
        errorf(sceSasCore,"UNIMPLEMENTED __sceSasSetSL function");
        return 0;
    }

    int __sceSasSetSimpleADSR()
    {
        //TODO implement me
        errorf(sceSasCore,"UNIMPLEMENTED __sceSasSetSimpleADSR function");
        return 0;
    }

    int __sceSasGetEndFlag(u32 a0)
    {
        SasCore &core = **(Memory::addr< SasCore * >(a0));

        int result = core.ended & ~(0xFFFFFFFF << core.voices);

        infof(sceAudio, "%s(0x%08X) = 0x%02X", "__sceSasGetEndFlag", a0, result);

        return result;
    }



    int __sceSasGetEnvelopeHeight()
    {
        //TODO implement me
        errorf(sceSasCore,"UNIMPLEMENTED __sceSasGetEnvelopeHeight function");
        return -1;
    }

    int __sceSasGetAllEnvelopeHeights()
    {
        //TODO implement me
        errorf(sceSasCore,"UNIMPLEMENTED __sceSasGetAllEnvelopeHeights function");
        return -1;
    }



    int __sceSasSetGrain(u32 a0, u32 a1)
    {
        int result;

        SasCore &core = **(Memory::addr< SasCore * >(a0));

        if ((a1 - 64) < 2048 && (a1 & 31) == 0)
        {
            core.frames = a1;

            result = 0;
        }
        else
        {
            result = SCE_SAS_ERROR_GRAIN_SAMPLES;
        }

        infof(sceAudio, "%s(0x%08X, %d) = 0x%08X", "__sceSasSetGrain", a0, a1, result);

        return result;
    }

    int __sceSasGetGrain(u32 a0)
    {
        SasCore &core = **(Memory::addr< SasCore * >(a0));

        int result = core.frames;

        infof(sceAudio, "%s(0x%08X) = %d", "__sceSasGetGrain", a0, result);

        return result;
    }



    int __sceSasSetOutputmode(u32 a0, u32 a1)
    {
        int result;

        SasCore &core = **(Memory::addr< SasCore * >(a0));

        if (a1 < 2)
        {
            core.output_mode = a0;

            result = 0;
        }
        else
        {
            result = SCE_SAS_ERROR_GRAIN_SAMPLES;
        }

        infof(sceAudio, "%s(0x%08X, %d) = 0x%08X", "__sceSasSetOutputmode", a0, a1, result);

        return result;
    }

    int __sceSasGetOutputmode(u32 a0)
	{
        SasCore &core = **(Memory::addr< SasCore * >(a0));

        int result = core.output_mode;

        infof(sceAudio, "%s(0x%08X) = %d", "__sceSasGetOutputmode", a0, result);

        return result;
	}



    int __sceSasRevType()
    {
        //TODO implement me
        errorf(sceSasCore,"UNIMPLEMENTED __sceSasRevType function");
        return 0;
    }

    int __sceSasRevParam()
    {
        //TODO implement me
        errorf(sceSasCore,"UNIMPLEMENTED __sceSasRevParam function");
        return 0;
    }

    int __sceSasRevEVOL()
    {
        //TODO implement me
        errorf(sceSasCore,"UNIMPLEMENTED __sceSasRevEVOL function");
        return 0;
    }

    int __sceSasRevVON()
    {
        //TODO implement me
        errorf(sceSasCore,"UNIMPLEMENTED __sceSasRevVON function");
        return 0;
    }



    int __sceSasSetSteepWave()
	{
		//TODO implement me
		errorf(sceSasCore,"UNIMPLEMENTED __sceSasSetSteepWave function");
		return 0;
	}

    int __sceSasSetTrianglarWave()
    {
        //TODO implement me
        errorf(sceSasCore,"UNIMPLEMENTED __sceSasSetTrianglarWave function");
        return 0;
    }

}

namespace syscalls
{
    void __sceSasInit(AlContext &context)                  { V0 = sceSasCore::__sceSasInit(A0, A1, A2, A3, T0);          }
	
    void __sceSasCore(AlContext &context)                  { V0 = sceSasCore::__sceSasCore(A0, A1);                      }
    void __sceSasCoreWithMix(AlContext &context)           { V0 = sceSasCore::__sceSasCoreWithMix(A0, A1, A2, A3);       }

    void __sceSasSetKeyOn(AlContext &context)              { V0 = sceSasCore::__sceSasSetKeyOn(A0, A1);                  }
    void __sceSasSetKeyOff(AlContext &context)             { V0 = sceSasCore::__sceSasSetKeyOff(A0, A1);                 }

    void __sceSasSetPause(AlContext &context)              { V0 = sceSasCore::__sceSasSetPause(A0, A1, A2);              }
    void __sceSasGetPauseFlag(AlContext &context)          { V0 = sceSasCore::__sceSasGetPauseFlag(A0);                  }

    void __sceSasSetVolume(AlContext &context)             { V0 = sceSasCore::__sceSasSetVolume(A0, A1, A2, A3, T0, T1); }
    void __sceSasSetPitch(AlContext &context)              { V0 = sceSasCore::__sceSasSetPitch(A0, A1, A2);              }
    void __sceSasSetVoice(AlContext &context)              { V0 = sceSasCore::__sceSasSetVoice(A0, A1, A2, A3, T0);      }
    void __sceSasSetVoicePCM(AlContext &context)           { V0 = sceSasCore::__sceSasSetVoicePCM(A0, A1, A2, A3, T0);   }
    void __sceSasSetNoise(AlContext &context)              { V0 = sceSasCore::__sceSasSetNoise();                        }
    void __sceSasSetADSR(AlContext &context)               { V0 = sceSasCore::__sceSasSetADSR();                         }
    void __sceSasSetADSRmode(AlContext &context)           { V0 = sceSasCore::__sceSasSetADSRmode();                     }
    void __sceSasSetSL(AlContext &context)                 { V0 = sceSasCore::__sceSasSetSL();                           }
    void __sceSasSetSimpleADSR(AlContext &context)         { V0 = sceSasCore::__sceSasSetSimpleADSR();                   }

    void __sceSasGetEndFlag(AlContext &context)            { V0 = sceSasCore::__sceSasGetEndFlag(A0);                    }

    void __sceSasGetEnvelopeHeight(AlContext &context)     { V0 = sceSasCore::__sceSasGetEnvelopeHeight();               }
    void __sceSasGetAllEnvelopeHeights(AlContext &context) { V0 = sceSasCore::__sceSasGetAllEnvelopeHeights();           }

    void __sceSasSetGrain(AlContext &context)              { V0 = sceSasCore::__sceSasSetGrain(A0, A1);                  }
    void __sceSasGetGrain(AlContext &context)              { V0 = sceSasCore::__sceSasGetGrain(A0);                      }

    void __sceSasSetOutputmode(AlContext &context)         { V0 = sceSasCore::__sceSasSetOutputmode(A0, A1);             }
    void __sceSasGetOutputmode(AlContext &context)         { V0 = sceSasCore::__sceSasGetOutputmode(A0);                 }

    void __sceSasRevType(AlContext &context)               { V0 = sceSasCore::__sceSasRevType();                         }
    void __sceSasRevParam(AlContext &context)              { V0 = sceSasCore::__sceSasRevParam();                        }
    void __sceSasRevEVOL(AlContext &context)               { V0 = sceSasCore::__sceSasRevEVOL();                         }
    void __sceSasRevVON(AlContext &context)                { V0 = sceSasCore::__sceSasRevVON();                          }

    void __sceSasSetSteepWave(AlContext &context)          { V0 = sceSasCore::__sceSasSetSteepWave();                    }
	void __sceSasSetTrianglarWave(AlContext &context)      { V0 = sceSasCore::__sceSasSetTrianglarWave();                }
}
