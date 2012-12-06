
__forceinline void doMFC1(u32 rt, u32 fs)
{
	if (rt)
	{
		gpr[rt] = *((u32 *) (fpr + fs));
	}
}

__forceinline u32 getFCR31()
{
    switch (mxcsr & _MM_ROUND_MASK)
    {
    case _MM_ROUND_UP:			fcr31 = (fcr31 & ~3) | 2; break; 
    case _MM_ROUND_DOWN:		fcr31 = (fcr31 & ~3) | 3; break; 
    case _MM_ROUND_TOWARD_ZERO: fcr31 = (fcr31 & ~3) | 1; break; 
    default:					fcr31 = (fcr31 & ~3) | 0; break;
    }
    fcr31 &= ~(1<<24);
    if (mxcsr & _MM_FLUSH_ZERO_ON)
    {
        fcr31 |= (1<<24);
    }
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
			gpr[rt] = getFCR31();
			break;

		default:

			break;
			//fatalf(interpreter, "CFC1 Unsupported for fcr%d", fs);
		}
	}
}

__forceinline void doMTC1(u32 rt, u32 fs)
{
	*((u32 *) (fpr + fs)) = gpr[rt];
}

__forceinline void setFCR31(u32 value)
{
    mxcsr = _mm_getcsr() | _MM_MASK_MASK; // no FPU exception
    {
        fcr31 = value & 0x01800003;
        switch (value & 3)
        {
        case 2:  mxcsr = (mxcsr & ~_MM_ROUND_MASK) | _MM_ROUND_UP; break; 
        case 3:	 mxcsr = (mxcsr & ~_MM_ROUND_MASK) | _MM_ROUND_DOWN; break; 
        case 1:  mxcsr = (mxcsr & ~_MM_ROUND_MASK) | _MM_ROUND_TOWARD_ZERO; break; 
        default: mxcsr = (mxcsr & ~_MM_ROUND_MASK) | _MM_ROUND_NEAREST; break;
        }
        if (value & (1<<24))
        {
            mxcsr = (mxcsr & ~_MM_FLUSH_ZERO_MASK) | _MM_FLUSH_ZERO_ON;
        }
    }
    _mm_setcsr(mxcsr);
}

__forceinline void doCTC1(u32 rt, u32 fs)
{
	switch (fs)
	{
	case 31:
        setFCR31(gpr[rt]);
		break;

	default:
//		fatalf(interpreter, "CTC1 Unsupported for fcr%d", fs);
		break;
	}
}

__forceinline void doCVT_S_W(u32 fd, u32 fs)
{
	_mm_store_ss(&fpr[fd], _mm_cvt_si2ss(_mm_setzero_ps(), *((s32 *) (fpr + fs))));
}

__forceinline void doADD_S(u32 fd, u32 fs, u32 ft)
{
	_mm_store_ss(&fpr[fd], _mm_add_ss(_mm_load_ss(&fpr[fs]), _mm_load_ss(&fpr[ft])));
}

__forceinline void doSUB_S(u32 fd, u32 fs, u32 ft)
{
	_mm_store_ss(&fpr[fd], _mm_sub_ss(_mm_load_ss(&fpr[fs]), _mm_load_ss(&fpr[ft])));
}

__forceinline void doMUL_S(u32 fd, u32 fs, u32 ft)
{
	_mm_store_ss(&fpr[fd], _mm_mul_ss(_mm_load_ss(&fpr[fs]), _mm_load_ss(&fpr[ft])));
}

__forceinline void doDIV_S(u32 fd, u32 fs, u32 ft)
{
	_mm_store_ss(&fpr[fd], _mm_div_ss(_mm_load_ss(&fpr[fs]), _mm_load_ss(&fpr[ft])));
}

__forceinline void doSQRT_S(u32 fd, u32 fs)
{
	_mm_store_ss(&fpr[fd], _mm_sqrt_ss(_mm_load_ss(&fpr[fs])));
}

__forceinline void doCVT_W_S(u32 fd, u32 fs)
{
	*((s32 *) (fpr + fd)) = _mm_cvt_ss2si(_mm_load_ss(&fpr[fs]));
}

__forceinline void doABS_S(u32 fd, u32 fs)
{
	((u32 *)fpr)[fd] = ((u32 *)fpr)[fs] & 0x7FFFFFFF;
}

__forceinline void doMOV_S(u32 fd, u32 fs)
{
	((u32 *)fpr)[fd] = ((u32 *)fpr)[fs];
}

__forceinline void doNEG_S(u32 fd, u32 fs)
{
	((u32 *)fpr)[fd] = ((u32 *)fpr)[fs] ^ 0x80000000;
}

__forceinline void doROUND_W_S(u32 fd, u32 fs)
{
    _mm_setcsr((mxcsr & ~_MM_ROUND_MASK)|_MM_ROUND_NEAREST);
	*((s32 *) (fpr + fd)) = _mm_cvt_ss2si(_mm_load_ss(&fpr[fs]));
    _mm_setcsr(mxcsr);
}

__forceinline void doTRUNC_W_S(u32 fd, u32 fs)
{
    _mm_setcsr((mxcsr & ~_MM_ROUND_MASK)|_MM_ROUND_TOWARD_ZERO);
	*((s32 *) (fpr + fd)) = _mm_cvtt_ss2si(_mm_load_ss(&fpr[fs]));
    _mm_setcsr(mxcsr);
}

__forceinline void doCEIL_W_S(u32 fd, u32 fs)
{
	_mm_setcsr((mxcsr & ~_MM_ROUND_MASK)|_MM_ROUND_UP);
	*((s32 *) (fpr + fd)) = _mm_cvt_ss2si(_mm_load_ss(&fpr[fs]));
	_mm_setcsr(mxcsr);
}

__forceinline void doFLOOR_W_S(u32 fd, u32 fs)
{
	_mm_setcsr((mxcsr & ~_MM_ROUND_MASK)|_MM_ROUND_DOWN);
	*((s32 *) (fpr + fd)) = _mm_cvt_ss2si(_mm_load_ss(&fpr[fs]));
	_mm_setcsr(mxcsr);
}

template< u32 cond >
__forceinline void doC_COND_S(u32 const fs, u32 const ft)
{
	__m128 x = _mm_load_ss(&fpr[fs]);
	__m128 y = _mm_load_ss(&fpr[ft]);

	fcr31 &= ~(1 << 23);

	if (_mm_movemask_ps(_mm_cmpunord_ss(x, y)) & 1)
	{
		if (cond & 1)
        {
            fcr31 |= 1 << 23;
        }
	}
	else if ((cond & 4) && (_mm_movemask_ps(_mm_cmplt_ss(x, y)) & 1))
	{
		fcr31 |= 1 << 23;
	}
	else if ((cond & 2) && (_mm_movemask_ps(_mm_cmpeq_ss(x, y)) & 1))
	{
		fcr31 |= 1 << 23;
	}
}
