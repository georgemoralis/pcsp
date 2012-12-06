#ifndef kernel_audio_h__
#define kernel_audio_h__

#if 0
#include <QtCore>
#include "common/linkedlist.h"
#include "common/threads.h"
#include "common/common_timer.h"

#include "../../../3rdparty/src/portaudio/include/portaudio.h"
#include "../../../3rdparty/src/portaudio/include/pa_win_wasapi.h"
#pragma comment(lib, "../../../3rdparty/src/portaudio/build/msvc/win32/debug WASAPI/portaudio_x86.lib")

class KernelAudioOutputChannel
{
public:
    KernelAudioOutputChannel();
    ~KernelAudioOutputChannel();

protected:
    PaStream   *m_stream;
    u32         m_frames;

    u32         m_sample_rate;
    u32         m_channel;
    u32         m_stereo;
    s16         m_volume[2];

    u32        *m_buffer[2];
    u32         m_buffer_toggle;

    static QAtomicPointer<KernelAudioOutputChannel> m_used_channels[9];
    static QAtomicPointer<KernelAudioOutputChannel> m_free_channels;
};


class KernelAudioPCMOutputChannel
:   public KernelAudioOutputChannel
{
public:
    KernelAudioPCMOutputChannel() {}
    ~KernelAudioPCMOutputChannel() {}

    int Reserve(int frames, int format);
    int Release() {}
};


class KernelAudioSRCOutputChannel
:   public KernelAudioOutputChannel
{
public:
    KernelAudioSRCOutputChannel() {}
    ~KernelAudioSRCOutputChannel() {}

    int Reserve(int frames, int format) {}
    int Release() {}
};
#endif

#endif // kernel_audio_h__
