#ifndef X86_CPU_H_
#define X86_CPU_H_

#include "host_any.h"

#ifdef _WIN32
#include "windows.h"
#endif

enum __host_cpu_vendor_e
{
	HOST_CPU_VENDOR_INTEL = 0,
	HOST_CPU_VENDOR_AMD = 1,
	HOST_CPU_VENDOR_OTHER = 2,
};

struct __host_cpu_info_s
{
	__host_cpu_vendor_e vendor;

	char cpu_string[0x21];
	char brand_string[0x41];

	bool hyper_threaded;
	int num_cores;

	bool has_FPU;
	bool has_TIMESTAMP;
	bool has_MDSR;
	bool has_CMPXCHG8B;
	bool has_CMOV;
	bool has_MMX;
	bool has_FXSR;
	bool has_SSE;
	bool has_SSE2;
	bool has_HTT;
	bool has_SSE3;
	bool has_SSSE3;
	bool has_SSE4_1;
	bool has_SSE4_2;
	bool has_SSE5A;
	bool has_POPCNT;
	bool has_LZCNT;
	bool has_SSE4A;
	bool has_3DNOW;
	bool has_3DNOWPLUS;
	bool has_LAHFSAHF64;
	bool has_LM;
	bool has_MWAIT;
	bool has_CMPXCHG16B;
	bool has_CMP;

	__host_cpu_info_s();
};

extern __host_cpu_info_s __host_cpu_info;

#include <math.h>
#include <float.h>
#include <stdlib.h>

#ifndef __GNUC__
/* MSVC is really a mess */
#include <intrin.h>
#include <xmmintrin.h>
#include <smmintrin.h>

#pragma intrinsic(__emul)
#pragma intrinsic(__emulu)
#pragma intrinsic(_BitScanReverse)

static __forceinline u32 __msvc_lzcnt(u32 rt)
{
	DWORD rd;
	_BitScanReverse(&rd, rt);
	return (rd^31);
}

static __forceinline u32 __msvc_rotr(u32 rt, u32 sa) { return _rotr(rt, sa); }
static __forceinline u32 __msvc_rotrv(u32 rt, u32 rs) { return __msvc_rotr(rt, rs & 31); }
static __forceinline u32 __msvc_clz(u32 rt) { return (rt) ? __msvc_lzcnt(rt) : 32; }
static __forceinline u32 __msvc_clo(u32 rt) { return __msvc_clz(~rt); }
static __forceinline u32 __msvc_wsbw(u32 rt) { return _byteswap_ulong(rt); }
static __forceinline u32 __msvc_wsbh(u32 rt) { return  _rotr(__msvc_wsbw(rt), 16); }
static __forceinline u32 __msvc_bitrev(u32 rt)
{
	rt = ((rt >> 1) & 0x55555555) | ((rt & 0x55555555) << 1);
	rt = ((rt >> 2) & 0x33333333) | ((rt & 0x33333333) << 2);
	rt = ((rt >> 4) & 0x0F0F0F0F) | ((rt & 0x0F0F0F0F) << 4);
	rt = ((rt >> 8) & 0x00FF00FF) | ((rt & 0x00FF00FF) << 8);
	rt = ( rt >> 16             ) | ( rt               << 16);
	return rt;
}
static __forceinline s64 __msvc_mult(u32 x, u32 y) { return __emul(s32(x), s32(y)); }
static __forceinline u64 __msvc_multu(u32 x, u32 y) { return __emulu(u32(x), u32(y)); }
static __forceinline s64 __msvc_madd(u32 x, u32 y, u64 hilo) { return ((s64) hilo) + __msvc_mult(x, y); }
static __forceinline u64 __msvc_maddu(u32 x, u32 y, u64 hilo) { return ((u64) hilo) + __msvc_multu(x, y); }
static __forceinline s64 __msvc_msub(u32 x, u32 y, u64 hilo) { return ((s64) hilo) - __msvc_mult(x, y); }
static __forceinline u64 __msvc_msubu(u32 x, u32 y, u64 hilo) { return ((u64) hilo) - __msvc_multu(x, y); }

#undef __host_rotr
#define __host_rotr(_rt, _sa) __msvc_rotr(_rt, _sa)

#undef __host_rotrv
#define __host_rotrv(_rt, _rs) __msvc_rotrv(_rt, _rs)

#undef __host_clz
#define __host_clz(_rs) __msvc_clz(_rs)

#undef __host_clo
#define __host_clo(_rs) __msvc_clo(_rs)

#undef __host_wsbh
#define __host_wsbh(_rt) __msvc_wsbh(_rt)

#undef __host_wsbw
#define __host_wsbw(_rt) __msvc_wsbw(_rt)

#undef __host_bitrev
#define __host_bitrev(_rt) __msvc_bitrev(_rt)

#undef __host_mult
#define __host_mult(x, y) __msvc_mult(x, y)

#undef __host_multu
#define __host_multu(x, y) __msvc_multu(x, y)

#undef __host_madd
#define __host_madd(x, y, hilo) __msvc_madd(x, y, hilo)

#undef __host_maddu
#define __host_maddu(x, y, hilo) __msvc_maddu(x, y, hilo)

#undef __host_msub
#define __host_msub(x, y, hilo) __msvc_msub(x, y, hilo)

#undef __host_msubu
#define __host_msubu(x, y) __msvc_msubu(x, y)

#else /* __GNUC__ */

#ifndef __APPLE__
#include <x86intrin.h>
#endif

#undef __host_rotr
#define __host_rotr(_rt, sa) \
  ({ u32 v = _rt; __asm__ __volatile__ ("rorl %%cl, %0" : "+r"(v) : "c"(sa)); v; })

#undef __host_rotrv
#define __host_rotrv(_rt, _rs) \
  ({ u32 v = _rt; __asm__ __volatile__ ("rorl %%cl, %0" : "+r"(v) : "c"(_rs&31)); v; })

#undef __host_clz
#define __host_clz(_rs) \
  ({ _rs ? u32(__builtin_clz(s32(_rs))) : u32(32); })

#undef __host_clo
#define __host_clo(_rs) \
  ({ u32 x = ~_rs; __host_clz(x); })

#undef __host_min
#define __host_min(_rs, _rt) \
  ({ u32 x = _rs, y = _rt; (s32(x) < s32(y)) ? x : y; })

#undef __host_max
#define __host_max(_rs, _rt) \
  ({ u32 x = _rs, y = _rt; (s32(x) > s32(y)) ? x : y; })

#undef __host_wsbw
#define __host_wsbw(_rt) \
  ({ u32 v = _rt; __asm__ __volatile__ ("bswapl %0" : "+r" (v)); v; })

#undef __host_wsbh
#define __host_wsbh(_rt) \
  __host_rotr(__host_wsbw(_rt), 16)

#undef __host_bitrev
#define __host_bitrev(_rt) \
  ({ \
    u32 x = _rt; \
	x = ((x >> 1) & 0x55555555) | ((x & 0x55555555) << 1); \
	x = ((x >> 2) & 0x33333333) | ((x & 0x33333333) << 2); \
	x = ((x >> 4) & 0x0F0F0F0F) | ((x & 0x0F0F0F0F) << 4); \
	x = ((x >> 8) & 0x00FF00FF) | ((x & 0x00FF00FF) << 8); \
	    ( x >> 16             ) | ( x               << 16); \
  })

#undef __host_ext
#define __host_ext(_rs, pos, len) \
  ({ (_rs >> pos) & ~(~0 << len); })

#undef __host_ins
#define __host_ins(_rt, _rs, pos, len) \
  ({ u32 x = ~(~0 << len) << pos;  (_rt & ~x) | ((_rs << pos) & x); })
#endif /* __GNUC__ */

#endif /* X86_CPU_H_ */
