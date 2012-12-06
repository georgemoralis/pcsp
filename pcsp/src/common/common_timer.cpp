#include "stdafx.h"
#include "time.h"

#ifdef _WIN32
int Timer::m_instances = 0;
#endif

//-----------------------------------------------------------------------------
// Description: Constructor
//-----------------------------------------------------------------------------
Timer::Timer()
#ifdef _WIN32
:   m_last_perf_count(0ULL)
,   m_last_tick_count((u64)timeGetTime())
#endif
{
#ifdef _WIN32

    QueryPerformanceFrequency(&m_yo);

	//HANDLE proc = GetCurrentProcess();

#if _MSC_VER >= 1400 && defined (_M_X64)
	//GetProcessAffinityMask(proc, (PDWORD_PTR)&m_proc_mask, (PDWORD_PTR)&m_sys_mask);
#else
	//GetProcessAffinityMask(proc, &m_proc_mask, &m_sys_mask);
#endif

	//m_thread = GetCurrentThread();

    if (m_instances++ == 0)
    {
        timeBeginPeriod(1);
    }
#else //!_WIN32

    gettimeofday(&m_initial_time, 0);

#endif
}

//-----------------------------------------------------------------------------
// Description: Destructor
//-----------------------------------------------------------------------------
Timer::~Timer()
{
#ifdef _WIN32
    if (--m_instances == 0)
    {
        timeEndPeriod(1);
    }
#endif
}

//-----------------------------------------------------------------------------
// Description: Get the current time of the system
//-----------------------------------------------------------------------------
// [hlide] http://www.geisswerks.com/ryan/FAQS/timing.html
//         "You could use  GetTickCount() instead, which doesn't require linking to winmm.lib,
//          but it tends to not have as good of a timer resolution... so I would recommend
//          sticking with timeGetTime()."
//         "However, if you call timeBeginPeriod(1) at the beginning of your program (and 
//          timeEndPeriod(1) at the end), timeGetTime() will usually become accurate to 1-2 
//          milliseconds, and will provide you with extremely accurate timing information."
u64 Timer::Get()
{
	u64	current_time = 0;

#ifdef _WIN32

	LARGE_INTEGER perf_count;

	//SetThreadAffinityMask(m_thread, 1);

	QueryPerformanceCounter(&perf_count);

	//SetThreadAffinityMask(m_thread, m_proc_mask);

	__int64 quotient, remainder;
	quotient     = ((perf_count.QuadPart) / m_yo.QuadPart);
	remainder    = ((perf_count.QuadPart) % m_yo.QuadPart);
	current_time = (u64) quotient * (u64)1000000 + (remainder*(u64)1000000 / m_yo.QuadPart);

	if (m_last_perf_count == 0)
	{
		m_last_perf_count = current_time;
		return current_time;
	}

	u64 current_tick_count  = (u64)timeGetTime();

    while (current_tick_count < m_last_tick_count)
    {
        current_tick_count += 1ULL << 32;
    }

    u64 elapsed_tick_count = current_tick_count - m_last_tick_count;
	u64 elapsed_perf_count = current_time - m_last_perf_count;
	
    if (elapsed_perf_count/1000ULL > elapsed_tick_count + 100ULL)
	{
		current_time = m_last_perf_count + elapsed_tick_count * 1000ULL;
	}
	
	m_last_tick_count = current_tick_count;
	m_last_perf_count = current_time;

#else //!_WIN32

    gettimeofday(&m_tp, 0);

	current_time = (m_tp.tv_sec - m_initial_time.tv_sec) * (u64)1000000 + (m_tp.tv_usec - m_initial_time.tv_usec);

#endif

	return current_time;
}
