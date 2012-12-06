#include "stdafx.h"
#include "time.h"

#ifdef _WIN32
int EmuTimer::m_Instances = 0;
#endif

//-----------------------------------------------------------------------------
// Description: Constructor
//-----------------------------------------------------------------------------
EmuTimer::EmuTimer()
{
#ifdef _WIN32

    QueryPerformanceFrequency( &m_yo );

	HANDLE mProc = GetCurrentProcess();

#if _MSC_VER >= 1400 && defined (_M_X64)
	GetProcessAffinityMask(mProc, (PDWORD_PTR)&mProcMask, (PDWORD_PTR)&mSysMask);
#else
	GetProcessAffinityMask(mProc, &m_ProcMask, &m_SysMask);
#endif

	m_Thread = GetCurrentThread();

    if (m_Instances++ == 0)
    {
        timeBeginPeriod(1);
    }
#else //!_WIN32

    gettimeofday( &m_initialTime, 0 );

#endif
}

//-----------------------------------------------------------------------------
// Description: Destructor
//-----------------------------------------------------------------------------
EmuTimer::~EmuTimer()
{
#ifdef _WIN32
    if (m_Instances++ == 0)
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
EmuTime EmuTimer::get_time()
{
	EmuTime	curTime = 0;

#ifdef _WIN32

	static EmuTime lastQueryVal = (EmuTime)0;
	static unsigned long lastTickCountVal = timeGetTime()/*GetTickCount()*/;

	LARGE_INTEGER PerfVal;

	SetThreadAffinityMask(m_Thread, 1);

	QueryPerformanceCounter(&PerfVal);

	SetThreadAffinityMask(m_Thread, m_ProcMask);

	__int64 quotient, remainder;
	quotient  = ((PerfVal.QuadPart) / m_yo.QuadPart);
	remainder = ((PerfVal.QuadPart) % m_yo.QuadPart);
	curTime   = (EmuTime) quotient * (EmuTime)1000000 + (remainder*(EmuTime)1000000 / m_yo.QuadPart);

	if (lastQueryVal == 0)
	{
		lastQueryVal = curTime;
		return curTime;
	}

	unsigned long curTickCount = timeGetTime()/*GetTickCount()*/;
	unsigned elapsedTickCount  = curTickCount - lastTickCountVal;

	EmuTime elapsedQueryVal = curTime - lastQueryVal;

	if (elapsedQueryVal/1000 > elapsedTickCount + 100)
	{
		curTime = lastQueryVal + elapsedTickCount * 1000;
	}
	
	lastTickCountVal = curTickCount;
	lastQueryVal     = curTime;

#else //!_WIN32

    gettimeofday( &m_Tp, 0 );

	curTime = ( m_Tp.tv_sec - m_initialTime.tv_sec ) * (EmuTime) 1000000 + ( m_Tp.tv_usec - m_initialTime.tv_usec );

#endif

	return curTime;
}
