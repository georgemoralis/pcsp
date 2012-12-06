#ifndef sceSasCore_h__
#define sceSasCore_h__

#include "hle/modules/sceAudio/sceAudio.h"

typedef enum SceSasErrorCode
{
    SCE_SAS_ERROR_GRAIN_SAMPLES  = 0x80420001, // Granularity specification is invalid
    SCE_SAS_ERROR_VOICES         = 0x80420002, // Voice count specification is invalid
    SCE_SAS_ERROR_OUTPUT_MODE    = 0x80420003, // Output mode specification is invalid
    SCE_SAS_ERROR_FREQUENCY      = 0x80420004, // Frequency specification is invalid
    SCE_SAS_ERROR_ADDRESS        = 0x80420005, // Address alignment is invalid
    SCE_SAS_ERROR_VOICE_INDEX    = 0x80420010, // Voice number is invalid
    SCE_SAS_ERROR_NOISE_CLOCK    = 0x80420011, // Noise clock is invalid
    SCE_SAS_ERROR_PITCH          = 0x80420012, // Pitch specification is invalid
    SCE_SAS_ERROR_ADSR_MODE      = 0x80420013, // ADSR mode is invalid
    SCE_SAS_ERROR_ADPCM_SIZE     = 0x80420014, // ADPCM waveform data size is invalid
    SCE_SAS_ERROR_LOOP_MODE      = 0x80420015, // Loop mode or loop position specification is invalid
    SCE_SAS_ERROR_INVALID_STATE  = 0x80420016, // Cannot be executed in the current state (keyed-on, keyed-off, paused, etc.)
    SCE_SAS_ERROR_VOLUME         = 0x80420018, // Volume value for the voice is invalid
    SCE_SAS_ERROR_ADSR           = 0x80420019, // Either the ADSR value or the SustainLevel value is invalid
    SCE_SAS_ERROR_PCM_SIZE       = 0x8042001a, // PCM size specification is invalid
    SCE_SAS_ERROR_FX_TYPE        = 0x80420020, // Effect type is invalid
    SCE_SAS_ERROR_FX_FEEDBACK    = 0x80420021, // Effect feedback value is invalid
    SCE_SAS_ERROR_FX_DELAY       = 0x80420022, // Effect delay value is invalid
    SCE_SAS_ERROR_FX_VOLUME      = 0x80420023, // Effect volume value is invalid
    SCE_SAS_ERROR_FX_UNAVAILABLE = 0x80420024, // Effects setting function is unavailable in multichannel mode
    SCE_SAS_ERROR_BUSY           = 0x80420030, // sceSasCore() was called multiple times
    SCE_SAS_ERROR_NOTINITED      = 0x80420100, // Initialization has not been performed
    SCE_SAS_ERROR_ALREADYINITED  = 0x80420101, // Initialization has already been performed
} SceSasErrorCode;

enum { SCE_SAS_VOICE_MAX = 32 };

enum { SCE_SAS_GRAIN_SAMPLES = 256 };

enum { SCE_SAS_VOLUME_MAX = 4096 };

namespace sceSasCore
{
    using namespace sceAudio;

    struct SasCore;

#if 0
    struct SasEnvelope
    {
        s32     value;     // Ranges from 0 to 0x7fffffff (signed values are clamped to 0)

        SasEnvelope() : value(0) {}
        operator s32 () const { return value; }
    };

    struct SasADSR : SasEnvelope
    {
        u32     SL : 4;
        u32     DR : 4;
        u32     AR : 7;
        u32     AM : 1; // 0 for linear (+lin), 1 for pseudo exponential (+exp)
        u32     RR : 5;
        u32     RM : 1; // 0 for linear (-lin), 1 for exponential (-exp)
        u32     SR : 7;
        u32     SM : 3; // 0 = +lin, 1 = -lin, 2 = +exp, 3 = -exp

        u8      phase;     // monitors current phase of ADSR envelope
        bool    releasing; // Ready To Release, triggered by Voice.Stop();

        SasADSR() : SL(0), DR(0), AR(0), AM(0), RR(0), RM(0), RM(0), SR(0), SM(0), phase(0), releasing(false)
        {}

        bool    Calculate();
    };
#endif

    struct SasVoice
    :   AudioStream
    {
        SasVoice();
        ~SasVoice();

        u32      frames;
        u32      frequency;
        u32      pitch;

        s16     *data;
        s16     *start;
        s16     *end;
        s16     *loop;

        s32      dry_volume[2];
        s32      wet_volume[2];

        //SasADSR  ADSR;
        SasCore *core;

        std::vector< s16 > m_pcm_buffer;

        int          Setup(int frames, int frequency);
        int          Reserve(int frames, int frequency);
        int          Release();

        int          KeyOn();
        int          KeyOff();

        int          SetPause(bool pause);
        
        int          SetVolume(s32 dl, s32 dr, s32 wl, s32 wr);
        int          SetPitch(u32 pitch);
        int          SetADPCMData(u32 data, u32 size, bool loop);
        int          SetPCMData(u32 data, u32 size, s32 loop_size);

        void         Output();
        virtual int  Render(f32 *target, u32 count);

        void DecodeADPCM(u8 const *source, s16 *target, u32 size);
    };

    struct SasCore
    :   KernelObject
    ,   Mutex
    {
        declare_kernel_type(SasCore, KernelObject);

        SasCore();
        ~SasCore();

        u32          key;
        u32          pause;
        u32          ended;

        u32          frames;
        u32          frequency;
        u32          voices;
        u32          output_mode;

        SasVoice     voice[SCE_SAS_VOICE_MAX];

        static s32   rate_value[160];
        static u32   rate_offset[];
        static void  Reboot();

        int          SetVolume(u32 voice, s32 voll, s32 volr);
        int          SetPitch(u32 voice, u32 pitch);
        int          SetADPCMData(u32 voice, u32 data, u32 size, bool loop);
        int          SetPCMData(u32 voice, u32 data, u32 size, s32 loop_size);

        void         Core();        
    };

    extern bool Reboot();
    extern bool ShutDown();


    extern int __sceSasInit(u32 a0, u32 a1, u32 a2, u32 a3, u32 t0); 

    extern int __sceSasCore(u32 a0, u32 a1); 
    extern int __sceSasCoreWithMix(u32 a0, u32 a1, u32 a2, u32 a3); 

    extern int __sceSasSetKeyOn(u32 a0, u32 a1); 
    extern int __sceSasSetKeyOff(u32 a0, u32 a1); 

    extern int __sceSasSetPause(u32 a0, u32 a1, u32 a2); 
    extern int __sceSasGetPauseFlag(u32 a0); 

    extern int __sceSasSetVolume(u32 a0, u32 a1, u32 a2, u32 a3, u32 t0, u32 t1); 
    extern int __sceSasSetPitch(u32 a0, u32 a1, u32 a2); 
    extern int __sceSasSetVoice(u32 a0, u32 a1, u32 a2, u32 a3, u32 t0); 
    extern int __sceSasSetVoicePCM(u32 a0, u32 a1, u32 a2, u32 a3, u32 t0); 
    extern int __sceSasSetNoise(); 
	extern int __sceSasSetADSR(); 
    extern int __sceSasSetADSRmode(); 
    extern int __sceSasSetSL(); 
    extern int __sceSasSetSimpleADSR(); 
    extern int __sceSasGetEndFlag(u32 a0); 

    extern int __sceSasGetEnvelopeHeight(); 
    extern int __sceSasGetAllEnvelopeHeights(); 

    extern int __sceSasSetGrain(u32 a0, u32 a1); 
    extern int __sceSasGetGrain(u32 a0); 

    extern int __sceSasSetOutputmode(); 
    extern int __sceSasGetOutputmode(u32 a0); 

    extern int __sceSasRevType(); 
    extern int __sceSasRevParam(); 
    extern int __sceSasRevEVOL(); 
    extern int __sceSasRevVON(); 

    extern int __sceSasSetSteepWave(); 
    extern int __sceSasSetTrianglarWave(); 
}


#endif // sceSasCore_h__
