#ifndef emutime_h__
#define emutime_h__

#include "types.h"

class Timer
{
public:
    Timer();
    ~Timer();

    u64	Get();

private:

#ifdef _WIN32
    DWORD           m_proc_mask;
    DWORD           m_sys_mask;
    HANDLE          m_thread;
    LARGE_INTEGER   m_yo;
    static int      m_instances;
#else
    timeval         m_tp;
    timeval         m_initial_time;
#endif
};

#endif // emutime_h__

