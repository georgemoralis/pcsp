#pragma once

typedef long long EmuTime;

class EmuTimer
{
public:
	EmuTimer();
	~EmuTimer();

	EmuTime	get_time();

private:

#ifdef _WIN32
	DWORD           m_ProcMask;
	DWORD           m_SysMask;
	HANDLE          m_Thread;
	LARGE_INTEGER   m_yo;
  static int      m_Instances;
#else
	timeval         m_Tp;
	timeval         m_initialTime;
#endif
};
