#include "stdafx.h"

#include "kernel_timer.h"
#include "kernel_thread.h"
#include "kernel_vsync.h"

#include "wtf/core/psp/hle/sceKernelThread.h"

extern int framerate_limit;

/// KernelVsync //////////////////////////////////////////////////////////

KernelVsync &KernelVsync::Instance()
{
    static KernelVsync instance;
    return instance;
}

void KernelVsync::Run()
{
    MutexLocker locker(*this); 

restart:
    u64 last_time_sleep = 0ULL;
    u64 last_time       = 0ULL;
    f32 delta           = 0.0f;
    f32 accumulated_ms  = 0.0f;
    f32 elapsed_ms      = 0.0f;
    f32 last_frame_time;

loop:
    switch (theEmulator.State())
    {
    case EmuLeaving:
        break;

    case EmuLoadExecEvent:
    case EmuPausing:
        this->Sleep(1000/60);

        goto restart;

    default:
        m_current_time = Timer::Get();

        last_frame_time = f32(m_current_time - last_time);
        elapsed_ms      = f32(m_current_time - last_time_sleep)*0.001;
        delta          += last_frame_time * 0.001f;

        if (delta >= (1000.0f/60.0f))
        {
            delta -= (1000.0f/60.0f);

            theEmulator.VsyncEvent();
        }

        if (elapsed_ms <= (1000.0f/60.0f))
        {
            accumulated_ms += (1000.0f/60.0f) - elapsed_ms;
        }

        if (accumulated_ms >= 5.5f)
        {
            u32 ms = (int)accumulated_ms;
            accumulated_ms -= ms;
            if (Trigger::Wait(ms))
            {
                goto loop;
            }
            last_time_sleep = Timer::Get();
        }
        else
        {
            last_time_sleep = m_current_time; 
        }

        last_time = m_current_time;

        goto loop;
    }
}

void KernelVsync::NextFrame()
{
    KernelVsync &instance = Instance();
    instance.Lock();
    if (!instance.isRunning())
    {
        instance.DetachedThread::TimeCriticalStart();
        instance.Trigger::Signal();
    }
    hle::__KernelWaitCurThread(instance, hle::WAITTYPE_VSYNC, 0);
}
