#include "stdafx.h"
#if 0
__m128 transform_vs(bool cst, int swz, __m128 v)
{
	__m128 value = v;
	if (swz == -1)
	{

	}
	else
	{
		switch (swz)
		{
		case 0:
			value = abs ? 3.0f : 0.0f;
			break;
		case 1:
			value = abs ? (1.0f / 3.0f) : 1.0f;
			break;
		case 2:
			value = abs ? (1.0f / 4.0f) : 2.0f;
			break;
		case 3:
			value = abs ? (1.0f / 6.0f) : 0.5f;
			break;
		}
	}
	return _mm_xor_ps(_mm_and_ps(value, pfxs_abs), pfxs_neg);
}


__m128 transformVr(int swz, bool abs, bool cst, bool neg, __m128 v)
{
	f32 value = 0.0f;

	if (cst)
	{
		switch (swz)
		{
		case 0:
			value = abs ? 3.0f : 0.0f;
			break;
		case 1:
			value = abs ? (1.0f / 3.0f) : 1.0f;
			break;
		case 2:
			value = abs ? (1.0f / 4.0f) : 2.0f;
			break;
		case 3:
			value = abs ? (1.0f / 6.0f) : 0.5f;
			break;
		}
	}
	else
	{
		value = v[swz];
	}

	if (abs)
	{
		value = ::fabsf(value);
	}

	return neg ? (0.0f - value) : value;
}
#endif

#define SHUFFLE1(x, v) case x: v = _mm_shuffle_ps(v, v, x)
#define SHUFFLE2(x, v) SHUFFLE1(x, v); SHUFFLE1(x+1, v)
#define SHUFFLE4(x, v) SHUFFLE2(x, v); SHUFFLE2(x+2, v)
#define SHUFFLE8(x, v) SHUFFLE4(x, v); SHUFFLE4(x+4, v)
#define SHUFFLE16(x, v) SHUFFLE8(x, v); SHUFFLE8(x+8, v)
#define SHUFFLE32(x, v) SHUFFLE16(x, v); SHUFFLE16(x+16, v)
#define SHUFFLE64(x, v) SHUFFLE32(x, v); SHUFFLE32(x+32, v)
#define SHUFFLE128(x, v) SHUFFLE64(x, v); SHUFFLE64(x+64, v)
#define SHUFFLE256(x, v) SHUFFLE128(x, v); SHUFFLE128(x+128, v)

#define _mm_shufflev_inplace(v, x) switch (x & 255) { SHUFFLE256(0, v); }

#define vpfxs_swz (vcr[0] & 0xFF)
#define vpfxt_swz (vcr[1] & 0xFF)

#define vpfxs_enabled (vcr[0] ^ 0x00|0x04|0x20|0xC0)
#define vpfxt_enabled (vcr[1] ^ 0x00|0x04|0x20|0xC0)
#define vpfxd_enabled (vcr[2] ^ 0x00|0x04|0x20|0xC0)

__forceinline __m128 transform_vs(__m128 v)
{
	__m128 zero = _mm_setzero_ps();
	__m128 cst_mask  = _mm_cmplt_ps(pfxs_cst, zero);

	_mm_shufflev_inplace(v, vcr[0]);

	v = _mm_xor_ps(_mm_and_ps(_mm_or_ps(_mm_and_ps(v, cst_mask), _mm_andnot_ps(pfxs_cst, cst_mask)), pfxs_abs), pfxs_neg);

	pfxs_neg = zero;
	pfxs_abs = zero;

	pfxs_cst = _mm_set1_ps(FLT_MIN); 

	vcr[0] = 0x00|0x04|0x20|0xC0;

	return v;
}

__forceinline __m128 transform_vt(__m128 v)
{
	__m128 zero = _mm_setzero_ps();
	__m128 cst_mask  = _mm_cmplt_ps(pfxt_cst, zero);

	_mm_shufflev_inplace(v, vcr[1]);

	v = _mm_xor_ps(_mm_and_ps(_mm_or_ps(_mm_and_ps(v, cst_mask), _mm_andnot_ps(pfxt_cst, cst_mask)), pfxt_abs), pfxt_neg);

	pfxt_neg = zero;
	pfxt_abs = zero;

	pfxt_cst = _mm_set1_ps(FLT_MIN); 

	vcr[1] = 0x00|0x04|0x20|0xC0;

	return v;
}

__forceinline __m128 transform_vd(__m128 v, __m128 o)
{

	v = _mm_or_ps(_mm_andnot_ps(_mm_min_ps(pfxd_max, _mm_max_ps(pfxd_min, v)), pfxd_msk), _mm_and_ps(o, pfxd_msk));

	pfxd_min = _mm_set1_ps(FLT_MIN);
	pfxd_max = _mm_set1_ps(FLT_MAX);
	pfxd_msk = _mm_setzero_ps();

	vcr[2] = 0;

	return v;
}

// group VFPU5
// VFPU5:VPFXS
__forceinline void doVPFXS(u32 imm24)
{
	union
	{
		u32 value;
		struct
		{
			u32 swzx : 2, swzy : 2, swzz : 2, swzw : 2;
			u32 absx : 1, absy : 1, absz : 1, absw : 1;
			u32 cstx : 1, csty : 1, cstz : 1, cstw : 1;
			u32 negx : 1, negy : 1, negz : 1, negw : 1;
		};
	} vcr_0;

	vcr[0] = imm24;

	vcr_0.value = imm24;

	static f32 cst_val[4][2][2] =
	{
		{ { FLT_MIN, 0.0f }, { FLT_MIN, (3.0f / 1.0f) } },
		{ { FLT_MIN, 1.0f }, { FLT_MIN, (1.0f / 3.0f) } },
		{ { FLT_MIN, 2.0f }, { FLT_MIN, (1.0f / 4.0f) } },
		{ { FLT_MIN, 0.5f }, { FLT_MIN, (1.0f / 6.0f) } }
	};

	pfxs_cst = _mm_set_ps(
		cst_val[vcr_0.swzx][vcr_0.absx][vcr_0.cstx],
		cst_val[vcr_0.swzy][vcr_0.absy][vcr_0.csty],
		cst_val[vcr_0.swzz][vcr_0.absz][vcr_0.cstz],
		cst_val[vcr_0.swzw][vcr_0.absw][vcr_0.cstw]
	);

	*((__m128i *)&pfxs_abs) = _mm_srli_epi32(_mm_set_epi32(~vcr_0.absx, ~vcr_0.absy, ~vcr_0.absz, ~vcr_0.absw), 1); 

	*((__m128i *)&pfxs_neg) = _mm_slli_epi32(_mm_set_epi32(vcr_0.negx, vcr_0.negy, vcr_0.negz, vcr_0.negw), 31);
}

// group VFPU5
// VFPU5:VPFXT
__forceinline void doVPFXT(u32 imm24)
{
	union
	{
		u32 value;
		struct
		{
			u32 swzx : 2, swzy : 2, swzz : 2, swzw : 2;
			u32 absx : 1, absy : 1, absz : 1, absw : 1;
			u32 cstx : 1, csty : 1, cstz : 1, cstw : 1;
			u32 negx : 1, negy : 1, negz : 1, negw : 1;
		};
	} vcr_1;

	vcr[1] = imm24;

	vcr_1.value = imm24;

	static f32 cst_val[4][2][2] =
	{
		{ { FLT_MIN, 0.0f }, { FLT_MIN, (3.0f / 1.0f) } },
		{ { FLT_MIN, 1.0f }, { FLT_MIN, (1.0f / 3.0f) } },
		{ { FLT_MIN, 2.0f }, { FLT_MIN, (1.0f / 4.0f) } },
		{ { FLT_MIN, 0.5f }, { FLT_MIN, (1.0f / 6.0f) } }
	};

	pfxs_cst = _mm_set_ps(
		cst_val[vcr_1.swzx][vcr_1.absx][vcr_1.cstx],
		cst_val[vcr_1.swzy][vcr_1.absy][vcr_1.csty],
		cst_val[vcr_1.swzz][vcr_1.absz][vcr_1.cstz],
		cst_val[vcr_1.swzw][vcr_1.absw][vcr_1.cstw]
	);

	*((__m128i *)&pfxs_abs) = _mm_srli_epi32(_mm_set_epi32(~vcr_1.absx, ~vcr_1.absy, ~vcr_1.absz, ~vcr_1.absw), 1); 

	*((__m128i *)&pfxs_neg) = _mm_slli_epi32(_mm_set_epi32(vcr_1.negx, vcr_1.negy, vcr_1.negz, vcr_1.negw), 31);
}

// VFPU5:VPFXD
__forceinline void doVPFXD(u32 imm24)
{
	union
	{
		u32 value;
		struct
		{
			u32 satx : 2, saty : 2, satz : 2, satw : 2;
			u32 mskx : 1, msky : 1, mskz : 1, mskw : 1;
		};
	} vcr_2;

	vcr[2] = imm24;

	vcr_2.value = imm24;


	static f32 min_val[4] = { FLT_MIN, 0.0f, FLT_MIN, -1.0f };
	static f32 max_val[4] = { FLT_MAX, 1.0f, FLT_MAX, +1.0f };

	pfxd_min = _mm_set_ps(min_val[vcr_2.satx], min_val[vcr_2.saty], min_val[vcr_2.satz], min_val[vcr_2.satw]);
	pfxd_max = _mm_set_ps(max_val[vcr_2.satx], max_val[vcr_2.saty], max_val[vcr_2.satz], max_val[vcr_2.satw]);
	
	*((__m128i *)&pfxd_msk) = _mm_srai_epi32(_mm_set_epi32(~vcr_2.mskx, ~vcr_2.msky, ~vcr_2.mskz, ~vcr_2.mskw), 1); 
}


