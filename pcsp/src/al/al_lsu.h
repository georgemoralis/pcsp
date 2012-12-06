#ifndef LSU_H_
#define LSU_H_

#include "memory/memory.h"

static bool const CHECK_ALIGNMENT = true;

__forceinline void doLB(u32 rt, u32 rs, s32 simm16)
{
	if (rt != 0)
	{
		gpr[rt] = (u32) (s32) Memory::memb(gpr[rs] + simm16);
	}
}

__forceinline void doLBU(u32 rt, u32 rs, s32 simm16)
{
	if (rt != 0)
	{
		gpr[rt] = (u32) Memory::membu(gpr[rs] + simm16);
	}
}

__forceinline void doLH(u32 rt, u32 rs, s32 simm16)
{
	u32 address = gpr[rs] + simm16;
	if (CHECK_ALIGNMENT && (address & 1) != 0)
	{
//		errorf(memory, "LH unaligned addr:0x%08x pc:0x%08x", address, pc);
	}
	else
	{
		if (rt != 0)
		{
			gpr[rt] = (u32) Memory::memh(address);
		}
	}
}

__forceinline void doLHU(u32 rt, u32 rs, s32 simm16)
{
	u32 address = gpr[rs] + simm16;
	if (CHECK_ALIGNMENT && (address & 1) != 0)
	{
//		errorf(memory, "LHU unaligned addr:0x%08x pc:0x%08x", address, pc);
	}
	else
	{
		if (rt != 0)
		{
			gpr[rt] = (u32) Memory::memhu(address);
		}
	}
}

__forceinline void doLWL(u32 rt, u32 rs, s32 simm16)
{
	static u32 const lwl_mask[4] =
	{ 0xffffff, 0xffff, 0xff, 0 };
	static u32 const lwl_shift[4] =
	{ 24, 16, 8, 0 };
	if (rt != 0)
	{
		u32 address = gpr[rs] + simm16;
		u32 offset = address & 0x3;
		u32 data = Memory::memw(address & 0xfffffffc);
		gpr[rt] = (data << lwl_shift[offset]) | (gpr[rt] & lwl_mask[offset]);
	}
}

__forceinline void doLW(u32 rt, u32 rs, s32 simm16)
{
	u32 address = gpr[rs] + simm16;
	if (CHECK_ALIGNMENT && (address & 3) != 0)
	{
//		errorf(memory, "LW unaligned addr:0x%08x pc:0x%08x", address, pc);
	}
	else
	{
		if (rt != 0)
		{
			gpr[rt] = (u32) Memory::memw(address);
		}
	}
}

__forceinline void doLWR(u32 rt, u32 rs, s32 simm16)
{
	static u32 const lwr_mask[4] =
	{ 0, 0xff000000, 0xffff0000, 0xffffff00 };
	static u32 const lwr_shift[4] =
	{ 0, 8, 16, 24 };
	if (rt != 0)
	{
		u32 address = gpr[rs] + simm16;
		u32 offset = address & 0x3;
		u32 data = Memory::memw(address & 0xfffffffc);
		gpr[rt] = (data >> lwr_shift[offset]) | (gpr[rt] & lwr_mask[offset]);
	}
}

__forceinline void doSB(u32 rt, u32 rs, u32 simm16)
{
	Memory::memb(gpr[rs] + simm16) = (u8) gpr[rt];
}

__forceinline void doSH(u32 rt, u32 rs, u32 simm16)
{
	u32 address = gpr[rs] + simm16;
	if (CHECK_ALIGNMENT && (address & 1) != 0)
	{
//		errorf(memory, "SH unaligned addr:0x%08x pc:0x%08x", address, pc);
	}
	else
	{
		Memory::memh(address) = (u16) gpr[rt];
	}
}

__forceinline void doSWL(u32 rt, u32 rs, s32 simm16)
{
	static u32 const swl_mask[4] =
	{ 0xffffff00, 0xffff0000, 0xff000000, 0 };
	static u32 const swl_shift[4] =
	{ 24, 16, 8, 0 };
	u32 address = gpr[rs] + simm16;
	u32 offset = address & 0x3;
	address &= 0xfffffffc;
	Memory::memw(address) = (gpr[rt] >> swl_shift[offset]) | (Memory::memw(address) & swl_mask[offset]);
}

__forceinline void doSW(u32 rt, u32 rs, u32 simm16)
{
	u32 address = gpr[rs] + simm16;
	if (CHECK_ALIGNMENT && (address & 3) != 0)
	{
//		errorf(memory, "SW unaligned addr:0x%08x pc:0x%08x", address, pc);
	}
	else
	{
		Memory::memw(address) = gpr[rt];
	}
}

__forceinline void doSWR(u32 rt, u32 rs, s32 simm16)
{
	static u32 const swl_mask[4] =
	{ 0, 0xff, 0xffff, 0xffffff };
	static u32 const swl_shift[4] =
	{ 0, 8, 16, 24 };
	u32 address = gpr[rs] + simm16;
	u32 offset = address & 0x3;
	address &= 0xfffffffc;
	Memory::memw( address) = (gpr[rt] << swl_shift[offset]) | (Memory::memw(address) & swl_mask[offset]);
}

__forceinline void doLL(u32 rt, u32 rs, s32 simm16)
{
	u32 address = gpr[rs] + simm16;
	if (CHECK_ALIGNMENT && (address & 3) != 0)
	{
//		errorf(memory, "LL unaligned addr:0x%08x pc:0x%08x", address, pc);
	}
	else
	{
		if (rt != 0)
		{
			gpr[rt] = (u32) Memory::memw(address);
		}
		// llbit = 1;
	}
}

__forceinline void doSC(u32 rt, u32 rs, u32 simm16)
{
	u32 address = gpr[rs] + simm16;
	if (CHECK_ALIGNMENT && (address & 3) != 0)
	{
		//errorf(memory, "SC unaligned addr:0x%08x pc:0x%08x", address, pc);
	}
	else
	{
		Memory::memw( address) = gpr[rt];
		gpr[rt] = 1; // = ll_bit;
	}
}

__forceinline void doLWC1(u32 ft, u32 rs, u32 simm16)
{
	u32 address = gpr[rs] + simm16;
	if (CHECK_ALIGNMENT && (address & 3) != 0)
	{
		//errorf(memory, "LWC1 unaligned addr:0x%08x pc:0x%08x", address, pc);
	}
	else
	{
		fpr[ft] = Memory::memf(address);
	}
}

__forceinline void doSWC1(u32 ft, u32 rs, u32 simm16)
{
	u32 address = gpr[rs] + simm16;
	if (CHECK_ALIGNMENT && (address & 3) != 0)
	{
		//errorf(memory, "SWC1 unaligned addr:0x%08x pc:0x%08x", address, pc);
	}
	else
	{
		Memory::memf(address) = fpr[ft];
	}
}

#endif /* LSU_H_ */
