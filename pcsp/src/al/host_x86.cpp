#include "stdafx.h"

#include "common_base.h"
#include "common_types.h"
#include "host_x86.h"

__host_cpu_info_s __host_cpu_info;

#ifndef _MSC_VER


static inline void do_cpuid(unsigned int *eax, unsigned int *ebx,
							unsigned int *ecx, unsigned int *edx)
{
#ifdef _M_IX86
    __asm__(
		"pushl  %%ebx;"
		"cpuid;"
		"movl   %%ebx,%1;"
		"popl   %%ebx;"
		: "=a" (*eax),
		"=r" (*ebx),
		"=c" (*ecx),
		"=d" (*edx)
		: "a"  (*eax)
		);
#else
__asm__("cpuid"
          : "=a" (*eax),
            "=b" (*ebx),
            "=c" (*ecx),
            "=d" (*edx)
          : "a"  (*eax)
        );
#endif
}

void __cpuid(int info[4], int x)
{
	unsigned int eax = x, ebx = 1, ecx = 0, edx = 0;
	do_cpuid(&eax, &ebx, &ecx, &edx);
	info[0] = eax;
	info[1] = ebx;
	info[2] = ecx;
	info[3] = edx;
}


#endif

__host_cpu_info_s::__host_cpu_info_s()
{
	enum { EAX, EBX, ECX, EDX };

	::memset(this, 0, sizeof(*this));
	
	num_cores = 1;

	int cpu_id[4];
	
	::memset(cpu_string, 0, sizeof(cpu_string));

	// detect CPU's CPUID capabilities, and grab cpu string
	__cpuid(cpu_id, 0x00000000);
	
	u32 max_std_fn = cpu_id[EAX];

	*((s32 *)(cpu_string + 0)) = cpu_id[EBX];
	*((s32 *)(cpu_string + 4)) = cpu_id[EDX];
	*((s32 *)(cpu_string + 8)) = cpu_id[ECX];
	
	__cpuid(cpu_id, 0x80000000);
	
	u32 max_ex_fn = cpu_id[0];
	
	if (!strcmp(cpu_string, "GenuineIntel"))
		vendor = HOST_CPU_VENDOR_INTEL;
	else if (!strcmp(cpu_string, "AuthenticAMD"))
		vendor = HOST_CPU_VENDOR_AMD;
	else
		vendor = HOST_CPU_VENDOR_OTHER;

	// set reasonable default brand string even if brand string not available.
	::strcpy(brand_string, cpu_string);

	// detect family and other misc stuff.
	int logical_cpu_count = 1;

	if (max_std_fn >= 1)
	{
		__cpuid(cpu_id, 0x00000001);

		logical_cpu_count = (cpu_id[EBX] >> 16) & 0xFF;

		has_FPU		   = !!((cpu_id[EDX] >>  0) & 1);
		has_TIMESTAMP  = !!((cpu_id[EDX] >>  4) & 1);
		has_MDSR       = !!((cpu_id[EDX] >>  5) & 1);
		has_CMPXCHG8B  = !!((cpu_id[EDX] >>  8) & 1);
		has_CMOV	   = !!((cpu_id[EDX] >> 15) & 1);
		has_MMX		   = !!((cpu_id[EDX] >> 23) & 1);
		has_FXSR	   = !!((cpu_id[EDX] >> 24) & 1);
		has_SSE        = !!((cpu_id[EDX] >> 25) & 1);
		has_SSE2       = !!((cpu_id[EDX] >> 26) & 1);
		has_HTT        = !!((cpu_id[EDX] >> 28) & 1);
		has_SSE3       = !!((cpu_id[ECX] >>  0) & 1);
		has_MWAIT      = !!((cpu_id[ECX] >>  3) & 1);
		has_SSSE3      = !!((cpu_id[ECX] >>  9) & 1);
		has_CMPXCHG16B = !!((cpu_id[ECX] >> 13) & 1);
		has_SSE4_1     = !!((cpu_id[ECX] >> 19) & 1);
		has_SSE4_2     = !!((cpu_id[ECX] >> 20) & 1);
		has_POPCNT	   = !!((cpu_id[ECX] >> 23) & 1);
	}
	if (max_ex_fn >= 0x80000004)
	{
		// extract brand string
		__cpuid(cpu_id, 0x80000002);

		::memcpy(brand_string, cpu_id, sizeof(cpu_id));
		
		__cpuid(cpu_id, 0x80000003);
		
		::memcpy(brand_string + 16, cpu_id, sizeof(cpu_id));
		
		__cpuid(cpu_id, 0x80000004);
		
		::memcpy(brand_string + 32, cpu_id, sizeof(cpu_id));
	}

	if (max_ex_fn >= 0x80000001)
	{
		// check for more features.
		__cpuid(cpu_id, 0x80000001);

		has_LAHFSAHF64 = !!((cpu_id[ECX] >>  0) & 1);
		has_CMP        = !!((cpu_id[ECX] >>  1) & 1);
		has_LZCNT      = !!((cpu_id[ECX] >>  5) & 1);
		has_SSE4A      = !!((cpu_id[ECX] >>  6) & 1);
		has_SSE5A      = !!((cpu_id[ECX] >> 11) & 1);
		has_LM         = !!((cpu_id[EDX] >> 29) & 1);
		has_3DNOWPLUS  = !!((cpu_id[EDX] >> 30) & 1);
		has_3DNOW      = !!((cpu_id[EDX] >> 31) & 1);
	}

	if (max_ex_fn >= 0x80000008)
	{
		// get number of cores. This is a bit complicated. Following AMD manual here.
		__cpuid(cpu_id, 0x80000008);

		int apic_id_core_id_size = (cpu_id[ECX] >> 12) & 0xF;
		
		if (apic_id_core_id_size == 0)
		{
			// use what AMD calls the "legacy method" to determine # of cores.
			num_cores = (has_HTT || has_CMP) ? logical_cpu_count : 1;
		}
		else
		{
			// use AMD's new method.
			num_cores = (cpu_id[ECX] & 0xFF) + 1;
		}
	}
	else
	{
		// wild guess
		if (logical_cpu_count)
			num_cores = logical_cpu_count;
	}
}

