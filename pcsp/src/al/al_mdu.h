/*
 * Multiply Divide Unit, handles accumulators.
 *
 * mdu.h
 *
 *  Created on: 15 nov. 2008
 *      Author: hli
 */

#ifndef MDU_H_
#define MDU_H_

#include "log.h"

__forceinline u32 &lo()
{
	return (reinterpret_cast< u32 * > (&hilo))[0];
}
__forceinline u32 &hi()
{
	return (reinterpret_cast< u32 * > (&hilo))[1];
}

__forceinline u32 lo() const
{
	return (reinterpret_cast< u32 const * > (&hilo))[0];
}
__forceinline u32 hi() const
{
	return (reinterpret_cast< u32 const * > (&hilo))[1];
}

__forceinline void doMFHI(u32 rd)
{
	if (rd != 0)
	{
		gpr[rd] = (u32) (hilo >> 32);
	}
}

__forceinline void doMTHI(u32 rs)
{
	hi() = gpr[rs];
}

__forceinline void doMFLO(u32 rd)
{
	if (rd != 0)
	{
		gpr[rd] = (u32) hilo;
	}
}

__forceinline void doMTLO(u32 rs)
{
	lo() = gpr[rs];
}

__forceinline void doMULT(u32 rs, u32 rt)
{
	hilo = (u64) (((s64)(s32) gpr[rs]) * ((s64)(s32) gpr[rt]));
}

__forceinline void doMULTU(u32 rs, u32 rt)
{
	hilo = ((u64) gpr[rs]) * ((u64) gpr[rt]);
}

__forceinline void doDIV(u32 rs, u32 rt)
{
  if(gpr[rt]!=0)//TODO : in a perfect emulation world that check is useless
  {
	lo() = (u32) (((s32) gpr[rs]) / ((s32) gpr[rt]));
	hi() = (u32) (((s32) gpr[rs]) % ((s32) gpr[rt]));
  }
  else
  {
	  errorf(interpreter,"DIV : WARNING! an expected zero division is detected");
  }
}

__forceinline void doDIVU(u32 rs, u32 rt)
{
  if(gpr[rt]!=0)//TODO : in a perfect emulation world that check is useless
  {
	lo() = ((u32) gpr[rs]) / ((u32) gpr[rt]);
	hi() = ((u32) gpr[rs]) % ((s32) gpr[rt]);
  }
  else
  {
    errorf(interpreter,"DIVU : WARNING! an expected zero division is detected");
  }
}

__forceinline void doMADD(u32 rs, u32 rt)
{
	hilo += (u64) (((s64)(s32) gpr[rs]) * ((s64)(s32) gpr[rt]));
}

__forceinline void doMADDU(u32 rs, u32 rt)
{
	hilo += (u64) (((u64) gpr[rs]) * ((u64) gpr[rt]));
}

__forceinline void doMSUB(u32 rs, u32 rt)
{
	hilo -= (u64) (((s64)(s32) gpr[rs]) * ((s64)(s32) gpr[rt]));
}

__forceinline void doMSUBU(u32 rs, u32 rt)
{
	hilo -= ((u64) gpr[rs]) * ((u64) gpr[rt]);
}

#endif /* MDU_H_ */
