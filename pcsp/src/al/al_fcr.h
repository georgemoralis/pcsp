u32 fcr0;
u32 fcr31;

#if defined(_M_IX86) || defined(__i386__)

u32 mxcsr;

__forceinline void reset_fcr()
{
	fcr0 = fcr31 = 0;

	mxcsr = _mm_getcsr() | _MM_MASK_MASK;
	_mm_setcsr(mxcsr);
}

#else

__forceinline void reset_fcr()
{
	fcr0  = 0;
	fcr31 = 0;
}

#endif
