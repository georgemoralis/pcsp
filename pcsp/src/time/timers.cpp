#include "stdafx.h"
#include "time.h"

#ifdef _WIN32
int Timer::m_instances = 0;
#endif

//-----------------------------------------------------------------------------
// Description: Constructor
//-----------------------------------------------------------------------------
Timer::Timer()
{
#ifdef _WIN32

    QueryPerformanceFrequency(&m_yo);

	HANDLE proc = GetCurrentProcess();

#if _MSC_VER >= 1400 && defined (_M_X64)
	GetProcessAffinityMask(proc, (PDWORD_PTR)&m_proc_mask, (PDWORD_PTR)&m_sys_mask);
#else
	GetProcessAffinityMask(proc, &m_proc_mask, &m_sys_mask);
#endif

	m_thread = GetCurrentThread();

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
	u64	cur_time = 0;

#ifdef _WIN32

	static u64 last_query_value = (u64)0;
	static u64 last_tick_count_value = (u64)timeGetTime();

	LARGE_INTEGER perf_value;

	SetThreadAffinityMask(m_thread, 1);

	QueryPerformanceCounter(&perf_value);

	SetThreadAffinityMask(m_thread, m_proc_mask);

	__int64 quotient, remainder;
	quotient  = ((perf_value.QuadPart) / m_yo.QuadPart);
	remainder = ((perf_value.QuadPart) % m_yo.QuadPart);
	cur_time   = (u64) quotient * (u64)1000000 + (remainder*(u64)1000000 / m_yo.QuadPart);

	if (last_query_value == 0)
	{
		last_query_value = cur_time;
		return cur_time;
	}

	u64 cur_tick_count = (u64)timeGetTime();
	u64 elapsed_tick_count = cur_tick_count + (u64(cur_tick_count < last_tick_count_value) << 32) - last_tick_count_value;

	u64 elapsed_query_value = cur_time - last_query_value;
	if (elapsed_query_value/1000ULL > elapsed_tick_count + 100ULL)
	{
		cur_time = last_query_value + elapsed_tick_count * 1000ULL;
	}
	
	last_tick_count_value = cur_tick_count;
	last_query_value      = cur_time;

#else //!_WIN32

    gettimeofday(&m_tp, 0);

	cur_time = (m_tp.tv_sec - m_initial_time.tv_sec) * (u64)1000000 + (m_tp.tv_usec - m_initial_time.tv_usec);

#endif

	return cur_time;
}
