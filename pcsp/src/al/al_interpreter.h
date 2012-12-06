#ifndef __allegrex_interpreter_h__
#define __allegrex_interpreter_h__

#define COUNT_INSN count++

/* ABS_S */
__forceinline void AllegrexInstructionTemplate< 0x46000005, 0xffff003f >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doABS_S(fd(opcode), fs(opcode));
}
/* ADD */
__forceinline void AllegrexInstructionTemplate< 0x00000020, 0xfc0007ff >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doADDU(rd(opcode), rs(opcode), rt(opcode));
}
/* ADDI */
__forceinline void AllegrexInstructionTemplate< 0x20000000, 0xfc000000 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doADDIU(rt(opcode), rs(opcode), simm16(opcode));
}
/* ADDIU */
__forceinline void AllegrexInstructionTemplate< 0x24000000, 0xfc000000 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doADDIU(rt(opcode), rs(opcode), simm16(opcode));
}
/* ADDU */
__forceinline void AllegrexInstructionTemplate< 0x00000021, 0xfc0007ff >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doADDU(rd(opcode), rs(opcode), rt(opcode));
}
/* ADD_S */
__forceinline void AllegrexInstructionTemplate< 0x46000000, 0xffe0003f >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doADD_S(fd(opcode), fs(opcode), ft(opcode));
}
/* AND */
__forceinline void AllegrexInstructionTemplate< 0x00000024, 0xfc0007ff >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doAND(rd(opcode), rs(opcode), rt(opcode));
}
/* ANDI */
__forceinline void AllegrexInstructionTemplate< 0x30000000, 0xfc000000 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doANDI(rt(opcode), rs(opcode), uimm16(opcode));
}
/* BC1F */
__forceinline void AllegrexInstructionTemplate< 0x45000000, 0xffff0000 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; if (context.doBC1F(simm16(opcode))) context.InterpretDelayslot();
}
/* BC1FL */
__forceinline void AllegrexInstructionTemplate< 0x45020000, 0xffff0000 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; if (context.doBC1FL(simm16(opcode))) context.InterpretDelayslot();
}
/* BC1T */
__forceinline void AllegrexInstructionTemplate< 0x45010000, 0xffff0000 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; if (context.doBC1T(simm16(opcode))) context.InterpretDelayslot();
}
/* BC1TL */
__forceinline void AllegrexInstructionTemplate< 0x45030000, 0xffff0000 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; if (context.doBC1TL(simm16(opcode))) context.InterpretDelayslot();
}
/* BEQ */
__forceinline void AllegrexInstructionTemplate< 0x10000000, 0xfc000000 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; if (context.doBEQ(rs(opcode), rt(opcode), simm16(opcode))) context.InterpretDelayslot();
}
/* BEQL */
__forceinline void AllegrexInstructionTemplate< 0x50000000, 0xfc000000 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; if (context.doBEQL(rs(opcode), rt(opcode), simm16(opcode))) context.InterpretDelayslot();
}
/* BGEZ */
__forceinline void AllegrexInstructionTemplate< 0x04010000, 0xfc1f0000 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; if (context.doBGEZ(rs(opcode), simm16(opcode))) context.InterpretDelayslot();
}
/* BGEZAL */
__forceinline void AllegrexInstructionTemplate< 0x04110000, 0xfc1f0000 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; if (context.doBGEZAL(rs(opcode), simm16(opcode))) context.InterpretDelayslot();;
}
/* BGEZALL */
__forceinline void AllegrexInstructionTemplate< 0x04130000, 0xfc1f0000 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; if (context.doBGEZALL(rs(opcode), simm16(opcode))) context.InterpretDelayslot();
}
/* BGEZL */
__forceinline void AllegrexInstructionTemplate< 0x04030000, 0xfc1f0000 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; if (context.doBGEZL(rs(opcode), simm16(opcode))) context.InterpretDelayslot();
}
/* BGTZ */
__forceinline void AllegrexInstructionTemplate< 0x1c000000, 0xfc1f0000 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; if (context.doBGTZ(rs(opcode), simm16(opcode))) context.InterpretDelayslot();
}
/* BGTZL */
__forceinline void AllegrexInstructionTemplate< 0x5c000000, 0xfc1f0000 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; if (context.doBGTZL(rs(opcode), simm16(opcode))) context.InterpretDelayslot();
}
/* BITREV */
__forceinline void AllegrexInstructionTemplate< 0x7c000520, 0xffe007ff >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doBITREV(rd(opcode), rt(opcode));
}
/* BLEZ */
__forceinline void AllegrexInstructionTemplate< 0x18000000, 0xfc1f0000 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; if (context.doBLEZ(rs(opcode), simm16(opcode))) context.InterpretDelayslot();
}
/* BLEZL */
__forceinline void AllegrexInstructionTemplate< 0x58000000, 0xfc1f0000 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; if (context.doBLEZL(rs(opcode), simm16(opcode))) context.InterpretDelayslot();
}
/* BLTZ */
__forceinline void AllegrexInstructionTemplate< 0x04000000, 0xfc1f0000 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; if (context.doBLTZ(rs(opcode), simm16(opcode))) context.InterpretDelayslot();
}
/* BLTZAL */
__forceinline void AllegrexInstructionTemplate< 0x04100000, 0xfc1f0000 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; if (context.doBLTZAL(rs(opcode), simm16(opcode))) context.InterpretDelayslot();
}
/* BLTZALL */
__forceinline void AllegrexInstructionTemplate< 0x04120000, 0xfc1f0000 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; if (context.doBLTZALL(rs(opcode), simm16(opcode))) context.InterpretDelayslot();
}
/* BLTZL */
__forceinline void AllegrexInstructionTemplate< 0x04020000, 0xfc1f0000 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; if (context.doBLTZL(rs(opcode), simm16(opcode))) context.InterpretDelayslot();
}
/* BNE */
__forceinline void AllegrexInstructionTemplate< 0x14000000, 0xfc000000 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; if (context.doBNE(rs(opcode), rt(opcode), simm16(opcode))) context.InterpretDelayslot();
}
/* BNEL */
__forceinline void AllegrexInstructionTemplate< 0x54000000, 0xfc000000 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; if (context.doBNEL(rs(opcode), rt(opcode), simm16(opcode))) context.InterpretDelayslot();
}
/* BREAK */
__forceinline void AllegrexInstructionTemplate< 0x0000000d, 0xfc00003f >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; //warnf(interpreter, "Opcode %08X : %s is not implemented", opcode, FastOpcodeName());
}
/* CEIL_W_S */
__forceinline void AllegrexInstructionTemplate< 0x4600000e, 0xffff003f >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doCEIL_W_S(fd(opcode), fs(opcode));
}
/* CFC0 */
__forceinline void AllegrexInstructionTemplate< 0x40400000, 0xffe007ff >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; //fatalf(interpreter,"Opcode %08X : %s is not implemented", opcode, FastOpcodeName());
}
/* CFC1 */
__forceinline void AllegrexInstructionTemplate< 0x44400000, 0xffe007ff >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doCFC1(rt(opcode), fs(opcode));
}
/* CLO */
__forceinline void AllegrexInstructionTemplate< 0x00000017, 0xfc1f07ff >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doCLO(rd(opcode), rs(opcode));
}
/* CLZ */
__forceinline void AllegrexInstructionTemplate< 0x00000016, 0xfc1f07ff >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doCLZ(rd(opcode), rs(opcode));
}
/* CTC0 */
__forceinline void AllegrexInstructionTemplate< 0x40c00000, 0xffe007ff >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; //fatalf(interpreter,"Opcode %08X : %s is not implemented", opcode, FastOpcodeName());
}
/* CTC1 */
__forceinline void AllegrexInstructionTemplate< 0x44c00000, 0xffe007ff >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doCTC1(rt(opcode), fs(opcode));
}
/* CVT_S_W */
__forceinline void AllegrexInstructionTemplate< 0x46800020, 0xffff003f >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doCVT_S_W(fd(opcode), fs(opcode));
}
/* CVT_W_S */
__forceinline void AllegrexInstructionTemplate< 0x46000024, 0xffff003f >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doCVT_W_S(fd(opcode), fs(opcode));
}
/* C_COND_S */
__forceinline void AllegrexInstructionTemplate< 0x46000030, 0xffe007ff >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doC_COND_S< 0 >(fs(opcode), ft(opcode));
}
__forceinline void AllegrexInstructionTemplate< 0x46000031, 0xffe007ff >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doC_COND_S< 1 >(fs(opcode), ft(opcode));
}
__forceinline void AllegrexInstructionTemplate< 0x46000032, 0xffe007ff >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doC_COND_S< 2 >(fs(opcode), ft(opcode));
}
__forceinline void AllegrexInstructionTemplate< 0x46000033, 0xffe007ff >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doC_COND_S< 3 >(fs(opcode), ft(opcode));
}
__forceinline void AllegrexInstructionTemplate< 0x46000034, 0xffe007ff >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doC_COND_S< 4 >(fs(opcode), ft(opcode));
}
__forceinline void AllegrexInstructionTemplate< 0x46000035, 0xffe007ff >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doC_COND_S< 5 >(fs(opcode), ft(opcode));
}
__forceinline void AllegrexInstructionTemplate< 0x46000036, 0xffe007ff >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doC_COND_S< 6 >(fs(opcode), ft(opcode));
}
__forceinline void AllegrexInstructionTemplate< 0x46000037, 0xffe007ff >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doC_COND_S< 7 >(fs(opcode), ft(opcode));
}
__forceinline void AllegrexInstructionTemplate< 0x46000038, 0xffe007ff >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doC_COND_S< 8 >(fs(opcode), ft(opcode));
}
__forceinline void AllegrexInstructionTemplate< 0x46000039, 0xffe007ff >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doC_COND_S< 9 >(fs(opcode), ft(opcode));
}
__forceinline void AllegrexInstructionTemplate< 0x4600003a, 0xffe007ff >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doC_COND_S< 10 >(fs(opcode), ft(opcode));
}
__forceinline void AllegrexInstructionTemplate< 0x4600003b, 0xffe007ff >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doC_COND_S< 11 >(fs(opcode), ft(opcode));
}
__forceinline void AllegrexInstructionTemplate< 0x4600003c, 0xffe007ff >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doC_COND_S< 12 >(fs(opcode), ft(opcode));
}
__forceinline void AllegrexInstructionTemplate< 0x4600003d, 0xffe007ff >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doC_COND_S< 13 >(fs(opcode), ft(opcode));
}
__forceinline void AllegrexInstructionTemplate< 0x4600003e, 0xffe007ff >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doC_COND_S< 14 >(fs(opcode), ft(opcode));
}
__forceinline void AllegrexInstructionTemplate< 0x4600003f, 0xffe007ff >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doC_COND_S< 15 >(fs(opcode), ft(opcode));
}
/* DCACHE_CREATE_DIRTY_EXCLUSIVE */
__forceinline void AllegrexInstructionTemplate< 0xbc180000, 0xfc1f0000 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; //warnf(interpreter,"Opcode %08X : %s is not implemented", opcode, FastOpcodeName());
}
/* DCACHE_CREATE_DIRTY_EXCLUSIVE_WITH_LOCK */
__forceinline void AllegrexInstructionTemplate< 0xbc1c0000, 0xfc1f0000 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN;// warnf(interpreter,"Opcode %08X : %s is not implemented", opcode, FastOpcodeName());
}
/* DCACHE_FILL */
__forceinline void AllegrexInstructionTemplate< 0xbc1e0000, 0xfc1f0000 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN;// warnf(interpreter,"Opcode %08X : %s is not implemented", opcode, FastOpcodeName());
}
/* DCACHE_FILL_WITH_LOCK */
__forceinline void AllegrexInstructionTemplate< 0xbc1f0000, 0xfc1f0000 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN;// warnf(interpreter,"Opcode %08X : %s is not implemented", opcode, FastOpcodeName());
}
/* DCACHE_HIT_INVALIDATE */
__forceinline void AllegrexInstructionTemplate< 0xbc190000, 0xfc1f0000 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; //warnf(interpreter,"Opcode %08X : %s is not implemented", opcode, FastOpcodeName());
}
/* DCACHE_HIT_WRITEBACK */
__forceinline void AllegrexInstructionTemplate< 0xbc1a0000, 0xfc1f0000 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN;// warnf(interpreter,"Opcode %08X : %s is not implemented", opcode, FastOpcodeName());
}
/* DCACHE_HIT_WRITEBACK_INVALIDATE */
__forceinline void AllegrexInstructionTemplate< 0xbc1b0000, 0xfc1f0000 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; //warnf(interpreter,"Opcode %08X : %s is not implemented", opcode, FastOpcodeName());
}
/* DCACHE_INDEX_UNLOCK */
__forceinline void AllegrexInstructionTemplate< 0xbc160000, 0xfc1f0000 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; //warnf(interpreter,"Opcode %08X : %s is not implemented", opcode, FastOpcodeName());
}
/* DCACHE_INDEX_WRITEBACK_INVALIDATE */
__forceinline void AllegrexInstructionTemplate< 0xbc140000, 0xfc1f0000 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN;// warnf(interpreter,"Opcode %08X : %s is not implemented", opcode, FastOpcodeName());
}
/* DIV */
__forceinline void AllegrexInstructionTemplate< 0x0000001a, 0xfc00ffff >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doDIV(rs(opcode), rt(opcode));
}
/* DIVU */
__forceinline void AllegrexInstructionTemplate< 0x0000001b, 0xfc00ffff >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doDIVU(rs(opcode), rt(opcode));
}
/* DIV_S */
__forceinline void AllegrexInstructionTemplate< 0x46000003, 0xffe0003f >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doDIV_S(fd(opcode), fs(opcode), ft(opcode));
}
/* ERET */
__forceinline void AllegrexInstructionTemplate< 0x42000018, 0xffffffff >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; //fatalf(interpreter,"Opcode %08X : %s is not implemented", opcode, FastOpcodeName());
}
/* EXT */
__forceinline void AllegrexInstructionTemplate< 0x7c000000, 0xfc00003f >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doEXT(rt(opcode), rs(opcode), sa(opcode), rd(opcode));
}
/* FLOOR_W_S */
__forceinline void AllegrexInstructionTemplate< 0x4600000f, 0xffff003f >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doFLOOR_W_S(fd(opcode), fs(opcode));
}
/* HALT */
__forceinline void AllegrexInstructionTemplate< 0x70000000, 0xffffffff >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; //fatalf(interpreter,"Opcode %08X : %s is not implemented", opcode, FastOpcodeName());
}
/* ICACHE_FILL */
__forceinline void AllegrexInstructionTemplate< 0xbc0a0000, 0xfc1f0000 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; //warnf(interpreter,"Opcode %08X : %s is not implemented", opcode, FastOpcodeName());
}
/* ICACHE_FILL_WITH_LOCK */
__forceinline void AllegrexInstructionTemplate< 0xbc0b0000, 0xfc1f0000 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; //warnf(interpreter,"Opcode %08X : %s is not implemented", opcode, FastOpcodeName());
}
/* ICACHE_HIT_INVALIDATE */
__forceinline void AllegrexInstructionTemplate< 0xbc080000, 0xfc1f0000 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; //warnf(interpreter,"Opcode %08X : %s is not implemented", opcode, FastOpcodeName());
}
/* ICACHE_INDEX_INVALIDATE */
__forceinline void AllegrexInstructionTemplate< 0xbc040000, 0xfc1f0000 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; //warnf(interpreter,"Opcode %08X : %s is not implemented", opcode, FastOpcodeName());
}
/* ICACHE_INDEX_UNLOCK */
__forceinline void AllegrexInstructionTemplate< 0xbc060000, 0xfc1f0000 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN;// warnf(interpreter,"Opcode %08X : %s is not implemented", opcode, FastOpcodeName());
}
/* INS */
__forceinline void AllegrexInstructionTemplate< 0x7c000004, 0xfc00003f >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doINS(rt(opcode), rs(opcode), sa(opcode), rd(opcode));
}
/* J */
__forceinline void AllegrexInstructionTemplate< 0x08000000, 0xfc000000 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; if (context.doJ(uimm26(opcode)))
		context.InterpretDelayslot();
}
/* JAL */
__forceinline void AllegrexInstructionTemplate< 0x0c000000, 0xfc000000 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; if (context.doJAL(uimm26(opcode)))
		context.InterpretDelayslot();
}
/* RET */
__forceinline void AllegrexInstructionTemplate< 0x0000f809, 0xfc1fffff >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; if (context.doJALR(rd(opcode), rs(opcode)))
		context.InterpretDelayslot();
}
/* JALR */
__forceinline void AllegrexInstructionTemplate< 0x00000009, 0xfc1f07ff >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; if (context.doJALR(rd(opcode), rs(opcode)))
		context.InterpretDelayslot();
}

/* JR */
__forceinline void AllegrexInstructionTemplate< 0x00000008, 0xfc1fffff >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; if (context.doJR(rs(opcode)))
		context.InterpretDelayslot();
}
/* LB */
__forceinline void AllegrexInstructionTemplate< 0x80000000, 0xfc000000 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doLB(rt(opcode), rs(opcode),simm16(opcode));
}
/* LBU */
__forceinline void AllegrexInstructionTemplate< 0x90000000, 0xfc000000 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doLBU(rt(opcode), rs(opcode),simm16(opcode));
}
/* LH */
__forceinline void AllegrexInstructionTemplate< 0x84000000, 0xfc000000 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doLH(rt(opcode), rs(opcode),simm16(opcode));
}
/* LHU */
__forceinline void AllegrexInstructionTemplate< 0x94000000, 0xfc000000 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doLHU(rt(opcode), rs(opcode),simm16(opcode));
}
/* LL */
__forceinline void AllegrexInstructionTemplate< 0xc0000000, 0xfc000000 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doLL(rt(opcode), rs(opcode),simm16(opcode));
}
/* LUI */
__forceinline void AllegrexInstructionTemplate< 0x3c000000, 0xffe00000 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doLUI(rt(opcode), uimm16(opcode));
}
/* LVLQ */
__forceinline void AllegrexInstructionTemplate< 0xd4000000, 0xfc000002 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doLVLQ(vt51(opcode), rs(opcode), simm14(opcode));
}
/* LVQ */
__forceinline void AllegrexInstructionTemplate< 0xd8000000, 0xfc000002 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doLVQ(vt51(opcode), rs(opcode), simm14(opcode));
}
/* LVRQ */
__forceinline void AllegrexInstructionTemplate< 0xd4000002, 0xfc000002 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doLVRQ(vt51(opcode), rs(opcode), simm14(opcode));
}
/* LVS */
__forceinline void AllegrexInstructionTemplate< 0xc8000000, 0xfc000000 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doLVS(vt52(opcode), rs(opcode), simm14(opcode));
}
/* LW */
__forceinline void AllegrexInstructionTemplate< 0x8c000000, 0xfc000000 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doLW(rt(opcode), rs(opcode), simm16(opcode));
}
/* LWC1 */
__forceinline void AllegrexInstructionTemplate< 0xc4000000, 0xfc000000 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doLWC1(ft(opcode), rs(opcode), simm16(opcode));
}
/* LWL */
__forceinline void AllegrexInstructionTemplate< 0x88000000, 0xfc000000 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doLWL(rt(opcode), rs(opcode), simm16(opcode));
}
/* LWR */
__forceinline void AllegrexInstructionTemplate< 0x98000000, 0xfc000000 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doLWR(rt(opcode), rs(opcode), simm16(opcode));
}
/* MADD */
__forceinline void AllegrexInstructionTemplate< 0x0000001c, 0xfc00ffff >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doMADD(rs(opcode), rt(opcode));
}
/* MADDU */
__forceinline void AllegrexInstructionTemplate< 0x0000001d, 0xfc00ffff >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doMADDU(rs(opcode), rt(opcode));
}
/* MAX */
__forceinline void AllegrexInstructionTemplate< 0x0000002c, 0xfc0007ff >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doMAX(rd(opcode), rs(opcode), rt(opcode));
}

/* MFC0 */
__forceinline void AllegrexInstructionTemplate< 0x40000000, 0xffe007ff >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN;// fatalf(interpreter,"Opcode %08X : %s is not implemented", opcode, FastOpcodeName());
}
/* MFC1 */
__forceinline void AllegrexInstructionTemplate< 0x44000000, 0xffe007ff >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doMFC1(rt(opcode), fs(opcode));
}
/* MFHI */
__forceinline void AllegrexInstructionTemplate< 0x00000010, 0xffff07ff >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doMFHI(rd(opcode));
}
/* MFIC */
__forceinline void AllegrexInstructionTemplate< 0x70000024, 0xfc1fffff >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; //fatalf(interpreter,"Opcode %08X : %s is not implemented", opcode, FastOpcodeName());
}
/* MFLO */
__forceinline void AllegrexInstructionTemplate< 0x00000012, 0xffff07ff >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doMFLO(rd(opcode));
}
/* MIN */
__forceinline void AllegrexInstructionTemplate< 0x0000002d, 0xfc0007ff >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doMIN(rd(opcode), rs(opcode), rt(opcode));
}
/* MOVN */
__forceinline void AllegrexInstructionTemplate< 0x0000000b, 0xfc0007ff >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doMOVN(rd(opcode), rs(opcode), rt(opcode));
}
/* MOVZ */
__forceinline void AllegrexInstructionTemplate< 0x0000000a, 0xfc0007ff >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doMOVZ(rd(opcode), rs(opcode), rt(opcode));
}
/* MOV_S */
__forceinline void AllegrexInstructionTemplate< 0x46000006, 0xffff003f >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doMOV_S(fd(opcode), fs(opcode));
}
/* MSUB */
__forceinline void AllegrexInstructionTemplate< 0x0000002e, 0xfc00ffff >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doMSUB(rs(opcode), rt(opcode));
}
/* MSUBU */
__forceinline void AllegrexInstructionTemplate< 0x0000002f, 0xfc00ffff >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doMSUBU(rs(opcode), rt(opcode));
}
/* MTC0 */
__forceinline void AllegrexInstructionTemplate< 0x40800000, 0xffe007ff >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; //fatalf(interpreter,"Opcode %08X : %s is not implemented", opcode, FastOpcodeName());
}
/* MTC1 */
__forceinline void AllegrexInstructionTemplate< 0x44800000, 0xffe007ff >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doMTC1(rt(opcode), fs(opcode));
}
/* MTHI */
__forceinline void AllegrexInstructionTemplate< 0x00000011, 0xfc1fffff >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doMTHI(rs(opcode));
}
/* MTIC */
__forceinline void AllegrexInstructionTemplate< 0x70000026, 0xfc1fffff >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN;// fatalf(interpreter,"Opcode %08X : %s is not implemented", opcode, FastOpcodeName());
}
/* MTLO */
__forceinline void AllegrexInstructionTemplate< 0x00000013, 0xfc1fffff >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doMTLO(rs(opcode));
}
/* MULT */
__forceinline void AllegrexInstructionTemplate< 0x00000018, 0xfc00ffff >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doMULT(rs(opcode), rt(opcode));
}
/* MULTU */
__forceinline void AllegrexInstructionTemplate< 0x00000019, 0xfc00ffff >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doMULTU(rs(opcode), rt(opcode));
}
/* MUL_S */
__forceinline void AllegrexInstructionTemplate< 0x46000002, 0xffe0003f >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doMUL_S(fd(opcode), fs(opcode), ft(opcode));
}
/* NEG_S */
__forceinline void AllegrexInstructionTemplate< 0x46000007, 0xffff003f >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doNEG_S(fd(opcode), fs(opcode));
}
/* NOR */
__forceinline void AllegrexInstructionTemplate< 0x00000027, 0xfc0007ff >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doNOR(rd(opcode), rs(opcode), rt(opcode));
}
/* OR */
__forceinline void AllegrexInstructionTemplate< 0x00000025, 0xfc0007ff >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doOR(rd(opcode), rs(opcode), rt(opcode));
}
/* ORI */
__forceinline void AllegrexInstructionTemplate< 0x34000000, 0xfc000000 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doORI(rt(opcode), rs(opcode), uimm16(opcode));
}
/* ROTR */
__forceinline void AllegrexInstructionTemplate< 0x00200002, 0xffe0003f >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doROTR(rd(opcode), rt(opcode), sa(opcode));
}
/* ROTRV */
__forceinline void AllegrexInstructionTemplate< 0x00000046, 0xfc0007ff >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doROTRV(rd(opcode), rt(opcode), rs(opcode));
}
/* ROUND_W_S */
__forceinline void AllegrexInstructionTemplate< 0x4600000c, 0xffff003f >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doROUND_W_S(fd(opcode), fs(opcode));
}
/* SB */
__forceinline void AllegrexInstructionTemplate< 0xa0000000, 0xfc000000 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doSB(rt(opcode), rs(opcode),simm16(opcode));
}
/* SC */
__forceinline void AllegrexInstructionTemplate< 0xe0000000, 0xfc000000 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doSC(rt(opcode), rs(opcode),simm16(opcode));
}
/* SEB */
__forceinline void AllegrexInstructionTemplate< 0x7c000420, 0xffe007ff >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doSEB(rd(opcode), rt(opcode));
}
/* SEH */
__forceinline void AllegrexInstructionTemplate< 0x7c000620, 0xffe007ff >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doSEH(rd(opcode), rt(opcode));
}
/* SH */
__forceinline void AllegrexInstructionTemplate< 0xa4000000, 0xfc000000 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doSH(rt(opcode), rs(opcode),simm16(opcode));
}
/* SLL */
__forceinline void AllegrexInstructionTemplate< 0x00000000, 0xffe0003f >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doSLL(rd(opcode), rt(opcode), sa(opcode));
}
/* SLLV */
__forceinline void AllegrexInstructionTemplate< 0x00000004, 0xfc0007ff >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doSLLV(rd(opcode), rt(opcode), rs(opcode));
}
/* SLT */
__forceinline void AllegrexInstructionTemplate< 0x0000002a, 0xfc0007ff >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doSLT(rd(opcode), rs(opcode), rt(opcode));
}
/* SLTI */
__forceinline void AllegrexInstructionTemplate< 0x28000000, 0xfc000000 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doSLTI(rt(opcode), rs(opcode), simm16(opcode));
}
/* SLTIU */
__forceinline void AllegrexInstructionTemplate< 0x2c000000, 0xfc000000 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doSLTIU(rt(opcode), rs(opcode), simm16(opcode));
}
/* SLTU */
__forceinline void AllegrexInstructionTemplate< 0x0000002b, 0xfc0007ff >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doSLTU(rd(opcode), rs(opcode), rt(opcode));
}
/* SQRT_S */
__forceinline void AllegrexInstructionTemplate< 0x46000004, 0xffff003f >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doSQRT_S(fd(opcode), fs(opcode));
}
/* SRA */
__forceinline void AllegrexInstructionTemplate< 0x00000003, 0xffe0003f >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doSRA(rd(opcode), rt(opcode), sa(opcode));
}
/* SRAV */
__forceinline void AllegrexInstructionTemplate< 0x00000007, 0xfc0007ff >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doSRAV(rd(opcode), rt(opcode), rs(opcode));
}
/* SRL */
__forceinline void AllegrexInstructionTemplate< 0x00000002, 0xffe0003f >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doSRL(rd(opcode), rt(opcode), sa(opcode));
}
/* SRLV */
__forceinline void AllegrexInstructionTemplate< 0x00000006, 0xfc0007ff >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doSRLV(rd(opcode), rt(opcode), rs(opcode));
}
/* SUB */
__forceinline void AllegrexInstructionTemplate< 0x00000022, 0xfc0007ff >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doSUBU(rd(opcode), rs(opcode), rt(opcode));
}
/* SUBU */
__forceinline void AllegrexInstructionTemplate< 0x00000023, 0xfc0007ff >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doSUBU(rd(opcode), rs(opcode), rt(opcode));
}
/* SUB_S */
__forceinline void AllegrexInstructionTemplate< 0x46000001, 0xffe0003f >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doSUB_S(fd(opcode), fs(opcode), ft(opcode));
}
/* SVLQ */
__forceinline void AllegrexInstructionTemplate< 0xf4000000, 0xfc000002 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doSVLQ(vt51(opcode), rs(opcode), simm14(opcode));
}
/* SVQ */
__forceinline void AllegrexInstructionTemplate< 0xf8000000, 0xfc000000 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doSVQ(vt51(opcode), rs(opcode), simm14(opcode));
}
/* SVRQ */
__forceinline void AllegrexInstructionTemplate< 0xf4000002, 0xfc000002 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doSVRQ(vt51(opcode), rs(opcode), simm14(opcode));
}
/* SVS */
__forceinline void AllegrexInstructionTemplate< 0xe8000000, 0xfc000000 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doSVS(vt52(opcode), rs(opcode), simm14(opcode));
}
/* SW */
__forceinline void AllegrexInstructionTemplate< 0xac000000, 0xfc000000 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doSW(rt(opcode), rs(opcode), simm16(opcode));
}
/* SWC1 */
__forceinline void AllegrexInstructionTemplate< 0xe4000000, 0xfc000000 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doSWC1(ft(opcode), rs(opcode), simm16(opcode));
}
/* SWL */
__forceinline void AllegrexInstructionTemplate< 0xa8000000, 0xfc000000 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doSWL(rt(opcode), rs(opcode), simm16(opcode));
}
/* SWR */
__forceinline void AllegrexInstructionTemplate< 0xb8000000, 0xfc000000 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doSWR(rt(opcode), rs(opcode), simm16(opcode));
}
/* SYNC */
__forceinline void AllegrexInstructionTemplate< 0x0000000f, 0xffffffff >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; /* SYNC is ignored */
}
/* SYSCALL */
__forceinline void AllegrexInstructionTemplate< 0x0000000c, 0xfc00003f >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.Syscall(opcode);
}
/* TRUNC_W_S */
__forceinline void AllegrexInstructionTemplate< 0x4600000d, 0xffff003f >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doTRUNC_W_S(fd(opcode), fs(opcode));
}

/* WSBH */
__forceinline void AllegrexInstructionTemplate< 0x7c0000a0, 0xffe007ff >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doWSBH(rd(opcode), rt(opcode));
}

/* WSBW */
__forceinline void AllegrexInstructionTemplate< 0x7c0000e0, 0xffe007ff >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doWSBW(rd(opcode), rt(opcode));
}

/* XOR */
__forceinline void AllegrexInstructionTemplate< 0x00000026, 0xfc0007ff >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doXOR(rd(opcode), rs(opcode), rt(opcode));
}
/* XORI */
__forceinline void AllegrexInstructionTemplate< 0x38000000, 0xfc000000 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doXORI(rt(opcode), rs(opcode), uimm16(opcode));
}

/* MFDR */
__forceinline void AllegrexInstructionTemplate< 0x7000003d, 0xffe007ff >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; //errorf(interpreter,"Opcode %08X : %s is not implemented", opcode, FastOpcodeName());
}
/* MTDR */
__forceinline void AllegrexInstructionTemplate< 0x7080003d, 0xffe007ff >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; //errorf(interpreter,"Opcode %08X : %s is not implemented", opcode, FastOpcodeName());
}
/* DBREAK */
__forceinline void AllegrexInstructionTemplate< 0x7000003f, 0xfc00003f >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; //errorf(interpreter,"Opcode %08X : %s is not implemented", opcode, FastOpcodeName());
}
/* DRET */
__forceinline void AllegrexInstructionTemplate< 0x7000003e, 0xffffffff >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; //errorf(interpreter,"Opcode %08X : %s is not implemented", opcode, FastOpcodeName());
}

#include "al_interpreter_vfpu.h"

#endif // __allegrex_interpreter_h__
