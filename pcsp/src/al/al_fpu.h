/*
 * fpu.h
 *
 *  Created on: 8 févr. 2009
 *      Author: hli
 */

#ifndef FPU_H_
#define FPU_H_

#if defined(_M_IX86) || defined(__i386__)
#include "al_fpu_sse.h"
#elif defined(__GNUC__)
__forceinline void doMFC1(u32 rt, u32 fs)
{
	if (rt)
	{
		gpr[rt] = *((u32 *) (fpr + fs));
	}
}

__forceinline u32 getFCR31()
{
    return fcr31;
}

__forceinline void doCFC1(u32 rt, u32 fs)
{
	if (rt)
	{
		switch (fs)
		{
		case 0:
			gpr[rt] = fcr0;
			break;

		case 31:
            gpr[rt] = fcr31;
			break;

		default:
			fatalf(interpreter, "CFC1 Unsupported for fcr%d", fs);
		}
	}
}

__forceinline void doMTC1(u32 rt, u32 fs)
{
	*((u32 *) (fpr + fs)) = gpr[rt];
}

__forceinline void setFCR31(u32 value)
{
    fcr31 = value & 0x01800003;    
}

__forceinline void doCTC1(u32 rt, u32 fs)
{
	if (rt)
	{
		switch (fs)
		{
		case 31:
            setFCR31(gpr[rt]);
			break;

		default:
			fatalf(interpreter, "CTC1 Unsupported for fcr%d", fs);
		}
	}
}

__forceinline void doCVT_S_W(u32 fd, u32 fs)
{
	fpr[fd] = f32(*((s32 *) (fpr + fs)));
}

__forceinline void doADD_S(u32 fd, u32 fs, u32 ft)
{
	fpr[fd] = fpr[fs] + fpr[ft];
}

__forceinline void doSUB_S(u32 fd, u32 fs, u32 ft)
{
	fpr[fd] = fpr[fs] - fpr[ft];
}

__forceinline void doMUL_S(u32 fd, u32 fs, u32 ft)
{
	fpr[fd] = fpr[fs] * fpr[ft];
}

__forceinline void doDIV_S(u32 fd, u32 fs, u32 ft)
{
	fpr[fd] = fpr[fs] / fpr[ft];
}

__forceinline void doSQRT_S(u32 fd, u32 fs)
{
	fpr[fd] = ::sqrtf(fpr[fs]);
}

__forceinline void doCVT_W_S(u32 fd, u32 fs)
{
	switch (fcr31 & 3)
	{
	case 1:
		*((s32 *) (fpr + fd)) = s32(fpr[fs]);
		break;
	case 2:
		*((s32 *) (fpr + fd)) = s32(::ceilf(fpr[fs]));
		break;
	case 3:
		*((s32 *) (fpr + fd)) = s32(::floorf(fpr[fs]));
		break;
	default:
		*((s32 *) (fpr + fd)) = s32(::floorf(fpr[fs] + 0.5f));
		break;
	}
}

__forceinline void doABS_S(u32 fd, u32 fs)
{
	fpr[fd] = ::fabsf(fpr[fs]);
}

__forceinline void doMOV_S(u32 fd, u32 fs)
{
	fpr[fd] = fpr[fs];
}

__forceinline void doNEG_S(u32 fd, u32 fs)
{
	fpr[fd] = 0.0f - fpr[fs];
}

__forceinline void doROUND_W_S(u32 fd, u32 fs)
{
	*((s32 *) (fpr + fd)) = s32(fpr[fs] + 0.5f);
}

__forceinline void doTRUNC_W_S(u32 fd, u32 fs)
{
	f32 f = fpr[fs];
	*((s32 *) (fpr + fd)) = s32((f < 0.0f) ? ::ceilf(f) : ::floorf(f)); 
}

__forceinline void doCEIL_W_S(u32 fd, u32 fs)
{
	*((s32 *) (fpr + fd)) = s32(::ceilf(fpr[fs]));
}

__forceinline void doFLOOR_W_S(u32 fd, u32 fs)
{
	*((s32 *) (fpr + fd)) = s32(::floorf(fpr[fs]));
}

template< u32 cond >
__forceinline void doC_COND_S(u32 fs, u32 ft)
{
	float x = fpr[fs];
	float y = fpr[ft];

	fcr31 &= ~(1 << 23);

    if (::isunordered(x, y))
	{
		if ((cond & 1) != 0)
			fcr31 |= 1 << 23;
	}
	else
	{
        if (((cond & 4) != 0) && ::isless(x, y))
		{
			fcr31 |= (1 << 23);
		}
        else if (((cond & 2) != 0) && (!::islessgreater(x, y)))
		{
			fcr31 |= (1 << 23);
		}
	}
}

#endif /* __GNUC__ */

#endif /* FPU_H_ */
