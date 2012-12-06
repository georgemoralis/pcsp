#ifndef BCU_H_
#define BCU_H_

__forceinline static u32 branch_target(u32 npc, s32 simm16)
{
	return npc + (simm16 << 2);
}

__forceinline static u32 jump_target(u32 npc, u32 uimm26)
{
	return (npc & 0xf0000000) | (uimm26 << 2);
}

__forceinline u32 FetchOpcode()
{
	npc = pc + 4;

	u32 opcode = Memory::memw(pc);

	// by default, the next instruction to emulate is at the next address
	pc = npc;

	return opcode;
}

__forceinline u32 FetchDelayslotOpcode()
{
	u32 opcode = Memory::memw(pc);

	// by default, the next instruction to emulate is at the next address
	pc += 4;

	return opcode;
}

__forceinline void NextPC()
{
	pc = npc;
	npc = pc + 4;
}

__forceinline bool doJR(u32 rs)
{
	npc = gpr[rs];
	return true;
}

__forceinline bool doJALR(u32 rd, u32 rs)
{
	if (rd != 0)
	{
		gpr[rd] = pc + 4;
	}
	npc = gpr[rs];
	return true;
}

__forceinline bool doBLTZ(u32 rs, s32 simm16)
{
    npc = (s32(gpr[rs]) < 0) ? branch_target(pc, simm16) : (pc + 4);
    return true;
}

__forceinline bool doBGEZ(u32 rs, s32 simm16)
{
	npc = (s32(gpr[rs]) >= 0) ? branch_target(pc, simm16) : (pc + 4);
	return true;
}

__forceinline bool doBLTZL(u32 rs, s32 simm16)
{
	if (s32(gpr[rs]) < 0)
	{
		npc = branch_target(pc, simm16);
		return true;
	}
	else
	{
		pc += 4;
	}
	return false;
}

__forceinline bool doBGEZL(u32 rs, s32 simm16)
{
	if (s32(gpr[rs]) >= 0)
	{
		npc = branch_target(pc, simm16);
		return true;
	}
	else
	{
		pc += 4;
	}
	return false;
}

__forceinline bool doBLTZAL(u32 rs, u32 simm16)
{
	u32 target = pc + 4;
	bool t = (s32(gpr[rs]) < 0);
	gpr[31] = target;
	npc = t ? branch_target(pc, simm16) : target;
	return true;
}

__forceinline bool doBGEZAL(u32 rs, u32 simm16)
{
	u32 target = pc + 4;
	bool t = (s32(gpr[rs]) >= 0);
	gpr[31] = target;
	npc = t ? branch_target(pc, simm16) : target;
	return true;
}

__forceinline bool doBLTZALL(u32 rs, s32 simm16)
{
	bool t = (s32(gpr[rs]) < 0);
	gpr[31] = pc + 4;
	if (t)
	{
		npc = branch_target(pc, simm16);
	}
	else
	{
		pc += 4;
	}
	return t;
}

__forceinline bool doBGEZALL(u32 rs, s32 simm16)
{
	bool t = (s32(gpr[rs]) >= 0);
	gpr[31] = pc + 4;
	if (t)
	{
		npc = branch_target(pc, simm16);
	}
	else
	{
		pc += 4;
	}
	return t;
}

__forceinline bool doJ(u32 uimm26)
{
	npc = jump_target(pc, uimm26);
	if (npc == pc - 4)
	{
		//Processor.log.info("Pausing emulator - jump to self (death loop)");
		//Emulator.PauseEmuWithStatus(Emulator.EMU_STATUS_JUMPSELF);
	}
	return true;
}

__forceinline bool doJAL(u32 uimm26)
{
	gpr[31] = pc + 4;
	npc = jump_target(pc, uimm26);
	return true;
}

__forceinline bool doBEQ(u32 rs, u32 rt, s32 simm16)
{
	npc = (gpr[rs] == gpr[rt]) ? branch_target(pc, simm16) : (pc + 4);
	return true;
}

__forceinline bool doBNE(u32 rs, u32 rt, u32 simm16)
{
	npc = (gpr[rs] != gpr[rt]) ? branch_target(pc, simm16) : (pc + 4);
	return true;
}

__forceinline bool doBLEZ(u32 rs, u32 simm16)
{
	npc = (s32(gpr[rs]) <= 0) ? branch_target(pc, simm16) : (pc + 4);
	return true;
}

__forceinline bool doBGTZ(u32 rs, u32 simm16)
{
	npc = (s32(gpr[rs]) > 0) ? branch_target(pc, simm16) : (pc + 4);
	return true;
}

__forceinline bool doBEQL(u32 rs, u32 rt, s32 simm16)
{
	if (gpr[rs] == gpr[rt])
	{
		npc = branch_target(pc, simm16);
		return true;
	}
	else
	{
		pc += 4;
	}
	return false;
}

__forceinline bool doBNEL(u32 rs, u32 rt, s32 simm16)
{
	if (gpr[rs] != gpr[rt])
	{
		npc = branch_target(pc, simm16);
		return true;
	}
	else
	{
		pc += 4;
	}
	return false;
}

__forceinline bool doBLEZL(u32 rs, s32 simm16)
{
	if (s32(gpr[rs]) <= 0)
	{
		npc = branch_target(pc, simm16);
		return true;
	}
	else
	{
		pc += 4;
	}
	return false;
}

__forceinline bool doBGTZL(u32 rs, s32 simm16)
{
	if (s32(gpr[rs]) > 0)
	{
		npc = branch_target(pc, simm16);
		return true;
	}
	else
	{
		pc += 4;
	}
	return false;
}

__forceinline bool doBC1F(s32 simm16)
{
	npc = ((fcr31 & (1 << 23)) == 0) ? branch_target(pc, simm16) : (pc + 4);
	return true;
}

__forceinline bool doBC1T(s32 simm16)
{
	npc = ((fcr31 & (1 << 23)) != 0) ? branch_target(pc, simm16) : (pc + 4);
	return true;
}

__forceinline bool doBC1FL(s32 simm16)
{
	if ((fcr31 & (1 << 23)) == 0)
	{
		npc = branch_target(pc, simm16);
		return true;
	}
	else
	{
		pc += 4;
	}
	return false;
}

__forceinline bool doBC1TL(s32 simm16)
{
	if ((fcr31 & (1 << 23)) != 0)
	{
		npc = branch_target(pc, simm16);
		return true;
	}
	else
	{
		pc += 4;
	}
	return false;
}

//////////////////////////////////////////////////////////////////////////

__forceinline bool doBEQ(u32 rs, u32 rt, s32 UNUSED(simm16), bool &t)
{
    t = gpr[rs] == gpr[rt];
    return true;
}

__forceinline bool doBNE(u32 rs, u32 rt, u32 UNUSED(simm16), bool &t)
{
    t = gpr[rs] != gpr[rt];
    return true;
}

__forceinline bool doBLTZ(u32 rs, s32 UNUSED(simm16), bool &t)
{
    t = s32(gpr[rs]) < 0;
    return true;
}

__forceinline bool doBGEZ(u32 rs, s32 UNUSED(simm16), bool &t)
{
    t = s32(gpr[rs]) >= 0;
    return true;
}

__forceinline bool doBLTZL(u32 rs, s32 UNUSED(simm16), bool &t)
{
    t = s32(gpr[rs]) < 0;
    return t;
}

__forceinline bool doBGEZL(u32 rs, s32 UNUSED(simm16), bool &t)
{
    t = s32(gpr[rs]) >= 0;
    return t;
}

__forceinline bool doBLEZ(u32 rs, u32 UNUSED(simm16), bool &t)
{
    t = s32(gpr[rs]) <= 0;
    return true;
}

__forceinline bool doBGTZ(u32 rs, u32 UNUSED(simm16), bool &t)
{
    t = s32(gpr[rs]) > 0;
    return true;
}

__forceinline bool doBEQL(u32 rs, u32 rt, s32 UNUSED(simm16), bool &t)
{
    t = gpr[rs] == gpr[rt];
    return t;
}

__forceinline bool doBNEL(u32 rs, u32 rt, s32 UNUSED(simm16), bool &t)
{
    t = gpr[rs] != gpr[rt];
    return t;
}

__forceinline bool doBLEZL(u32 rs, s32 UNUSED(simm16), bool &t)
{
    t = s32(gpr[rs]) <= 0;
    return t;
}

__forceinline bool doBGTZL(u32 rs, s32 UNUSED(simm16), bool &t)
{
    t = s32(gpr[rs]) > 0;
    return t;
}

__forceinline bool doBC1F(s32 UNUSED(simm16), bool &t)
{
    t = (fcr31 & (1 << 23)) == 0;
    return true;
}

__forceinline bool doBC1T(s32 UNUSED(simm16), bool &t)
{
    t = (fcr31 & (1 << 23)) != 0;
    return true;
}

__forceinline bool doBC1FL(s32 UNUSED(simm16), bool &t)
{
    t = (fcr31 & (1 << 23)) == 0;
    return t;
}

__forceinline bool doBC1TL(s32 UNUSED(simm16), bool &t)
{
    t = (fcr31 & (1 << 23)) != 0;
    return t;
}

#endif /* BCU_H_ */
