#ifndef CPU_H_
#define CPU_H_

__forceinline void doSLL(u32 rd, u32 rt, u32 sa)
{
	if (rd != 0)
	{
		gpr[rd] = (u32(gpr[rt]) << sa);
	}
}

__forceinline void doSRL(u32 rd, u32 rt, u32 sa)
{
	if (rd != 0)
	{
		gpr[rd] = (u32(gpr[rt]) >> sa);
	}
}

__forceinline void doSRA(u32 rd, u32 rt, u32 sa)
{
	if (rd != 0)
	{
		gpr[rd] = (s32(gpr[rt]) >> sa);
	}
}

__forceinline void doSLLV(u32 rd, u32 rt, u32 rs)
{
	if (rd != 0)
	{
		gpr[rd] = (u32(gpr[rt]) << (gpr[rs] & 31));
	}
}

__forceinline void doSRLV(u32 rd, u32 rt, u32 rs)
{
	if (rd != 0)
	{
		gpr[rd] = (u32(gpr[rt]) >> (gpr[rs] & 31));
	}
}

__forceinline void doSRAV(u32 rd, u32 rt, u32 rs)
{
	if (rd != 0)
	{
		gpr[rd] = (s32(gpr[rt]) >> (gpr[rs] & 31));
	}
}

__forceinline void doADDU(u32 rd, u32 rs, u32 rt)
{
	if (rd != 0)
	{
		gpr[rd] = gpr[rs] + gpr[rt];
	}
}

__forceinline void doSUBU(u32 rd, u32 rs, u32 rt)
{
	if (rd != 0)
	{
		gpr[rd] = gpr[rs] - gpr[rt];
	}
}

__forceinline void doAND(u32 rd, u32 rs, u32 rt)
{
	if (rd != 0)
	{
		gpr[rd] = gpr[rs] & gpr[rt];
	}
}

__forceinline void doOR(u32 rd, u32 rs, u32 rt)
{
	if (rd != 0)
	{
		gpr[rd] = gpr[rs] | gpr[rt];
	}
}

__forceinline void doXOR(u32 rd, u32 rs, u32 rt)
{
	if (rd != 0)
	{
		gpr[rd] = gpr[rs] ^ gpr[rt];
	}
}

__forceinline void doNOR(u32 rd, u32 rs, u32 rt)
{
	if (rd != 0)
	{
		gpr[rd] = ~(gpr[rs] | gpr[rt]);
	}
}

__forceinline void doSLT(u32 rd, u32 rs, u32 rt)
{
	if (rd != 0)
	{
		gpr[rd] = (s32(gpr[rs]) < s32(gpr[rt]));
	}
}

__forceinline void doSLTU(u32 rd, u32 rs, u32 rt)
{
	if (rd != 0)
	{
		gpr[rd] = (u32(gpr[rs]) < u32(gpr[rt]));
	}
}

__forceinline void doADDIU(u32 rt, u32 rs, s32 simm16)
{
	if (rt != 0)
	{
		gpr[rt] = gpr[rs] + simm16;
	}
}

__forceinline void doSLTI(u32 rt, u32 rs, s32 simm16)
{
	if (rt != 0)
	{
		gpr[rt] = (s32(gpr[rs]) < simm16);
	}
}

__forceinline void doSLTIU(u32 rt, u32 rs, s32 simm16)
{
	if (rt != 0)
	{
		gpr[rt] = (u32(gpr[rs]) < u32(simm16));
	}
}

__forceinline void doANDI(u32 rt, u32 rs, u32 uimm16)
{
	if (rt != 0)
	{
		gpr[rt] = gpr[rs] & uimm16;
	}
}

__forceinline void doORI(u32 rt, u32 rs, u32 uimm16)
{
	if (rt != 0)
	{
		gpr[rt] = gpr[rs] | uimm16;
	}
}

__forceinline void doXORI(u32 rt, u32 rs, u32 uimm16)
{
	if (rt != 0)
	{
		gpr[rt] = gpr[rs] ^ uimm16;
	}
}

/* load upper 16-bit immediate */
__forceinline void doLUI(u32 rt, u32 uimm16)
{
	if (rt != 0)
	{
		gpr[rt] = uimm16 << 16;
	}
}

/* bitwise right rotation */
__forceinline void doROTR(u32 rd, u32 rt, u32 sa)
{
	if (rd != 0)
	{
		gpr[rd] = __host_rotr(gpr[rt], sa);
	}
}

/* bitwise right rotation */
__forceinline void doROTRV(u32 rd, u32 rt, u32 rs)
{
	if (rd != 0)
	{
		gpr[rd] = __host_rotr(gpr[rt], gpr[rs]);
	}
}

/* move if zero */
__forceinline void doMOVZ(u32 rd, u32 rs, u32 rt)
{
	if ((rd != 0) && (gpr[rt] == 0))
	{
		gpr[rd] = gpr[rs];
	}
}

/* move if non-zero */
__forceinline void doMOVN(u32 rd, u32 rs, u32 rt)
{
	if ((rd != 0) && (gpr[rt] != 0))
	{
		gpr[rd] = gpr[rs];
	}
}

/* count leading zeroes */
__forceinline void doCLZ(u32 rd, u32 rs)
{
	if (rd != 0)
	{
		gpr[rd] = __host_clz(gpr[rs]);
	}
}

/* count leading ones */
__forceinline void doCLO(u32 rd, u32 rs)
{
	if (rd != 0)
	{
		gpr[rd] = __host_clo(gpr[rs]);
	}
}

/* maximal value between two signed integers */
__forceinline void doMAX(u32 rd, u32 rs, u32 rt)
{
	if (rd != 0)
	{
		gpr[rd] = __host_max(gpr[rs], gpr[rt]);
	}
}

/* minimal value between two signed integers */
__forceinline void doMIN(u32 rd, u32 rs, u32 rt)
{
	if (rd != 0)
	{
		gpr[rd] = __host_min(gpr[rs], gpr[rt]);
	}
}

/* bitwise extraction */
__forceinline void doEXT(u32 rt, u32 rs, u32 lsb, u32 dbmalsb)
{
	if (rt != 0)
	{
		// lsb = least significant bit for bitwise extraction
		// dbmalsb = distance between most and least significant bits for bitwise extraction
		gpr[rt] = __host_ext(gpr[rs], lsb, (dbmalsb + 1));
	}
}

/* bitwise insertion */
__forceinline void doINS(u32 rt, u32 rs, u32 lsb, u32 msb)
{
	if (rt != 0)
	{
		// lsb = least significant bit for bitwise insertion
		// msb = most significant bit for bitwise insertion
		gpr[rt] = __host_ins(gpr[rt], gpr[rs], lsb, (msb - lsb + 1));
	}
}

/* word swap byte within halfword : XYZW -> YXWZ */
__forceinline void doWSBH(u32 rd, u32 rt)
{
	if (rd != 0)
	{
		gpr[rd] = __host_wsbh(gpr[rt]);
	}
}

/* word swap byte within word : XYZW -> ZWYX */
__forceinline void doWSBW(u32 rd, u32 rt)
{
	if (rd != 0)
	{
		gpr[rd] = __host_wsbw(gpr[rt]);
	}
}

/* sign-extend byte */
__forceinline void doSEB(u32 rd, u32 rt)
{
	if (rd != 0)
	{
		gpr[rd] = u32((s32) (s8) gpr[rt]);
	}
}

/* bit reverse */
__forceinline void doBITREV(u32 rd, u32 rt)
{
	if (rd != 0)
	{
		gpr[rd] = __host_bitrev(gpr[rt]);
	}
}

/* sign-extend halfword */
__forceinline void doSEH(u32 rd, u32 rt)
{
	if (rd != 0)
	{
		gpr[rd] = u32((s32) (s16) gpr[rt]);
	}
}

#endif /* CPU_H_ */
