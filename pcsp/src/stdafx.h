#pragma once

#if defined(_WIN32) || defined(__WIN32__)
#   define __win32__
#elif defined(__APPLE__)
#   define __macosx__
#else
#   define __linux__
#endif

#if defined(__win32__)
#   if defined(__CYGWIN__)
#       define __cygwin__
#       define __gnuc__
#   elif defined(_MSC_VER)
#       define __msvc__
#   elif defined(__GNUC__)
#       define __mingw__
#       define __gnuc__
#   endif
#elif defined(__GNUC__)
#   define __gnuc__
#endif

#if defined(__msvc__)
#   pragma warning(disable:4996;disable:4200)
#   define weaksymbol __declspec(selectany)
#elif defined(__gnuc__)
#   define weaksymbol __attribute__((weak))
#endif

#if defined(__msvc__) || defined(__mingw__)
#   define _WIN32_WINNT 0x501
#   define WINVER 0x0500
#   ifndef _WIN32_IE
#       define _WIN32_IE 0x0501       // Default value is 0x0400
#   endif
#   define _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES 1
#   define WIN32_LEAN_AND_MEAN
#   include <windows.h>
#	include <intrin.h>
#	include <xmmintrin.h>
#	include <smmintrin.h>
#   define HAS_NATIVE_FIBERS 1
#   include <tchar.h>
#   include <process.h>
#   include <mmsystem.h>
#else
#   include <sys/time.h>
#   include <sys/mman.h>
#   include <sys/stat.h>
#   include <fcntl.h>
#   include <unistd.h>
#   include <cerrno>
#   include <cstring>
#   if !defined(MAP_ANONYMOUS) && defined(MAP_ANON)
#       define MAP_ANONYMOUS MAP_ANON
#   endif 
#endif

#include <float.h>
#include <stdio.h>

#ifdef __msvc__
// use instrinsic for byteswapping
#   pragma intrinsic(_byteswap_ulong)
#endif

#include <xmmintrin.h>

#define bswap16(x) ((x)>>8 | ((x)&255)<<8)
#define bswap32(x) ((bswap16((x)>>16)&65535)|(bswap16((x)&65535)<<16))

#define _USE_MATH_DEFINES
#include <math.h>
#include <time.h>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <algorithm>
#include <stdio.h>
#include <queue>




#define USE_QT

#ifdef USE_QT
#include <QtCore>
#include <QtGui>

using namespace std;
#endif



#include "common_defines.h"
#include "types.h"
#include "common/common_timer.h"
#include "al/host_any.h"
#include "emulator.h"

#include "symbolmap.h"
//#include <QtOpenGL>

#include <GL/glew.h>

#if defined(__win32__)
#include <GL/wglew.h>
#elif defined(__macosx__)
#else // GLX
#include <GL/glxew.h>
#endif
#include <QGLWidget>
#include <assert.h>
//#define USE_SHADERS
