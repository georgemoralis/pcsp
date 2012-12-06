#if 0/*defined(_M_IX86) || defined(__i386__)*/

/* VPR */
__m128 vpr[8][4];

#else

/* VPR */
f32 vpr[8][4][4];

#endif

__forceinline void reset_vpr()
{
	::memset(vpr, 0, sizeof(vpr));
}

