#ifndef common_timer_h__
#define common_timer_h__

#include "types.h"

class Timer
{
public:
    Timer();
    ~Timer();

    u64	Get();

private:

#ifdef _WIN32
    //DWORD           m_proc_mask;
    //DWORD           m_sys_mask;
    HANDLE          m_thread;
    LARGE_INTEGER   m_yo;
    u64             m_last_perf_count;
    u64             m_last_tick_count;

    static int      m_instances;
#else
    timeval         m_tp;
    timeval         m_initial_time;
#endif
};

#endif // common_timer_h__

