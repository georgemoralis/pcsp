#ifndef kernel_vsync_h__
#define kernel_vsync_h__

#include "common_thread.h"
#include "common_timer.h"

struct KernelVsync
:   public    DetachedThread
,   public    Timer
,   protected Trigger
{
public:
    KernelVsync()
    :   DetachedThread()
    ,   Timer()
    ,   Trigger(true, false)
    ,   m_frames_count(0)
    ,   m_current_time(0ULL)
    {
        m_current_time = Timer::Get();
    }

    static void NextFrame();

    void Run();

private: // methods
    static KernelVsync &Instance();

    u32 m_frames_count;
    u64 m_current_time;
};

#endif // kernel_vsync_h__
