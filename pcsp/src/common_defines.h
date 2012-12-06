#pragma once

/////////////////////////////////////////////////////////////////////////////////////////////////////
// D E F I N E S ////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////

#define safe_delete(p)       { if (p) { delete   (p); (p)=0; } }
#define safe_delete_array(p) { if (p) { delete[] (p); (p)=0; } }
#define safe_release(p)      { if (p) { p->Release();        } }

#if !defined(_TRUNCATE)
#define _TRUNCATE ((size_t)-1)
#endif

#ifndef min
#define min(x, y) ({ typeof(x) xx = x; typeof(y) yy = y; (xx < yy) ? xx : yy; }) 
#endif
#ifndef max
#define max(x, y) ({ typeof(x) xx = x; typeof(y) yy = y; (xx > yy) ? xx : yy; })
#endif

// HLE Defines
#define HLE_PARAM(index) theEmulator.context->gpr[4 + (index)]
#define HLE_RETURN(value) theEmulator.context->gpr[2] = (u32)(value)
#define HLE_RETURN64(value) *((u64 *)(&theEmulator.context->gpr[2])) = (u64)(value)

#ifdef _WIN32
#define HLEDECL __cdecl
#else
#define HLEDECL
#endif

#undef UNUSED
#if defined(__GNUC__)
# define UNUSED(x) x __attribute__((unused))
#else
# define UNUSED(x)
#endif
