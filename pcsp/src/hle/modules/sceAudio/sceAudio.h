#ifndef sceAudio_h__
#define sceAudio_h__

#include "portaudio.h"

#include <QCache>

typedef enum SceAudioErrorCode
{
    SCE_AUDIO_ERROR_NOT_INITIALIZED	= 0x80260001,
    SCE_AUDIO_ERROR_OUTPUT_BUSY		= 0x80260002,
    SCE_AUDIO_ERROR_INVALID_CH		= 0x80260003,
    SCE_AUDIO_ERROR_PRIV_REQUIRED	= 0x80260004,
    SCE_AUDIO_ERROR_NOT_FOUND		= 0x80260005,
    SCE_AUDIO_ERROR_INVALID_SIZE	= 0x80260006,
    SCE_AUDIO_ERROR_INVALID_FORMAT	= 0x80260007,
    SCE_AUDIO_ERROR_NOT_RESERVED	= 0x80260008,
    SCE_AUDIO_ERROR_NOT_OUTPUT		= 0x80260009,
    SCE_AUDIO_ERROR_INVALID_VOLUME	= 0x8026000B
} SceAudioErrorCode;

/** The maximum output volume. */
enum { PSP_AUDIO_VOLUME_MAX = 0x8000 };

/** The maximum number of hardware channels. */
enum { SCE_AUDIO_CHANNEL_MAX = 8 };

/** Used to request the next available hardware channel. */
enum { SCE_AUDIO_NEXT_CHANNEL = -1 };

enum SceAudioFormat
{
	SCE_AUDIO_FORMAT_STEREO = 0,
	SCE_AUDIO_FORMAT_MONO   = 0x10
};

typedef struct
{
	/** Unknown. Pass 0 */
	int unknown1;
	int gain;
	/** Unknown. Pass 0 */
	int unknown2;
	/** Unknown. Pass 0 */
	int unknown3;
	/** Unknown. Pass 0 */
	int unknown4;
	/** Unknown. Pass 0 */
	int unknown5;

} pspAudioInputParams;

/** The minimum number of samples that can be allocated to a channel. */
#define PSP_AUDIO_SAMPLE_MIN    64
/** The maximum number of samples that can be allocated to a channel. */
#define PSP_AUDIO_SAMPLE_MAX    65472
/** Make the given sample count a multiple of 64. */
#define PSP_AUDIO_SAMPLE_ALIGN(s) (((s) + 63) & ~63)

namespace sceAudio
{
    class AudioResamplerTable
    {     
        friend class AudioResampler;

    public:
        AudioResamplerTable(u32 ra, u32 rb, u32 hl, u32 fr);
        ~AudioResamplerTable();

    private:
        f32 *m_ctab;
        u32  m_ra;
        u32  m_rb;
        u32  m_hl;
        u32  m_fr;

        static AudioResamplerTable *Create(u32 ra, u32 rb, u32 hl, u32 fr);

        static QCache< u64, AudioResamplerTable > tables;
    };

    class AudioResampler
    {
    public:

        AudioResampler();
        ~AudioResampler();

        bool Setup(u32 fs_inp, u32 fs_out, u32 nchan);
        bool Setup(u32 fs_inp, u32 fs_out, u32 nchan, u32 hlen, u32 freq);
        void Clear();
        bool Reset();

        bool Active() { return m_table != 0;                }
        u32  RatioA() { return m_table ? m_table->m_ra : 0; }
        u32  RatioB() { return m_table ? m_table->m_rb : 0; }

        bool Process(s32 l, s32 r);

        u32  inp_count;
        u32  out_count;
        s16 *inp_data;
        f32 *out_data;
        s16 *inp_loop;
        s16 *inp_stop;

    private:

        AudioResamplerTable *m_table;
        f32                 *m_buff;
        u32                  m_nchan;
        u32                  m_inmax;
        u32                  m_index;
        u32                  m_nread;
        u32                  m_phase;
    };

    struct AudioStream
    :   Mutex
    {
        PaStream       *stream;
        u32             sample_rate;
        u32             frequency;
        AudioResampler  resampler;
        bool            reserved;

        AudioStream();
        ~AudioStream();

        bool Initialize();
        bool Terminate();

        virtual int Render(f32 *target, u32 count);
    };

    struct AudioOutputStream
    :   AudioStream 
    {
        u32            *thread_status;

        int             channels;
        u32             frequency;
        u32             frames;
        int             volume[2];

        std::vector< s16 > buffer_array;

        s16            *buffer_data;
        u32             buffer_size;
        u32             buffer_wpos;
        u32             buffer_rpos;
        u32             buffer_used;

        static u32      buffer_factor;

        AudioOutputStream();
        ~AudioOutputStream();

        int Output(int volume_l, int volume_r, s16 *buffer, bool blocking);
        int Setup(int frames, int frequency, int stereo);
        int Reserve(int frames, int frequency, int format);
        int Release();
        int ChangeVolume(int l, int r);
        int ChangeConfig(int format);
        int SetDataLength(int frames);
        int GetRestLength();

        virtual int Render(f32 *target, u32 count);
    };

    extern bool Reboot();
    extern bool ShutDown();

    extern int sceAudioChReserve(u32 a0, u32 a1, u32 a2); 
    extern int sceAudioChRelease(u32 a0); 
    extern int sceAudioOutput(u32 a0, u32 a1, u32 a2); 
    extern int sceAudioOutputBlocking(u32 a0, u32 a1, u32 a2); 
    extern int sceAudioOutputPanned(u32 a0, u32 a1, u32 a2, u32 a3); 
    extern int sceAudioOutputPannedBlocking(u32 a0, u32 a1, u32 a2, u32 a3); 
    extern int sceAudioChangeChannelVolume(u32 a0, u32 a1, u32 a2);
    extern int sceAudioChangeChannelConfig(u32 a0, u32 a1); 
    extern int sceAudioSetChannelDataLen(u32 a0, u32 a1); 
    extern int sceAudioGetChannelRestLen(u32 a0); 
	extern int sceAudioGetChannelRestLength(u32 a0); 

    extern int sceAudioSRCChReserve(u32 a0, u32 a1, u32 a2); 
    extern int sceAudioSRCChRelease(); 
    extern int sceAudioSRCOutputBlocking(u32 a0, u32 a1); 

    extern int sceAudioOutput2Release(u32 a0); 
    extern int sceAudioOutput2Reserve(); 
    extern int sceAudioOutput2OutputBlocking(u32 a0, u32 a1); 
    extern int sceAudioOutput2ChangeLength(u32 a0); 
    extern int sceAudioOutput2GetRestSample(); 

    extern int sceAudioOneshotOutput(u32 a0, u32 a1, u32 a2, u32 a3, u32 t0, u32 t1); 

    extern int sceAudioInputInit(); 
    extern int sceAudioInputInitEx(); 
    extern int sceAudioInput(); 
    extern int sceAudioInputBlocking(); 
    extern int sceAudioPollInputEnd(); 
    extern int sceAudioWaitInputEnd(); 
    extern int sceAudioGetInputLength(); 
}
#endif // sceAudio_h__
