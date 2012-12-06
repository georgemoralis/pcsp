#ifndef common_base_h__
#define common_base_h__

#ifndef _WIN32

// Win32-style arch defs
#ifdef _LP64
#define _M_X64 1
#else
#define _M_IX86 1
#endif

typedef int64_t __int64;
// Fix win32-isns under linux

typedef unsigned char byte;
inline unsigned int _rotl(unsigned int value, int count)
{
	return (value << count) | (value >> (32 - count));
}

inline void Panic()
{
	printf("Panic!!!\n");
	exit(0);
}

inline void DebugBreak()
{
	Panic();
}

#else

#define strcasecmp  _stricmp
#define strncasecmp _strnicmp
#define unlink      _unlink
#define snprintf    _snprintf
#define vscprintf   _vscprintf

inline void Panic()
{
	throw;
}

#endif

#endif // common_base_h__
