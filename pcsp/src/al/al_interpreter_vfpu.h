/* BVF */
__forceinline void AllegrexInstructionTemplate< 0x49000000, 0xFFE30000 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; if (context.doBVF((opcode>>18)&7, simm16(opcode))) context.InterpretDelayslot();
}
/* BVT */
__forceinline void AllegrexInstructionTemplate< 0x49010000, 0xFFE30000 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; if (context.doBVT((opcode>>18)&7, simm16(opcode))) context.InterpretDelayslot();
}
/* BVFL */
__forceinline void AllegrexInstructionTemplate< 0x49020000, 0xFFE30000 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; if (context.doBVFL((opcode>>18)&7, simm16(opcode))) context.InterpretDelayslot();
}
/* BVTL */
__forceinline void AllegrexInstructionTemplate< 0x49030000, 0xFFE30000 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; if (context.doBVTL((opcode>>18)&7, simm16(opcode))) context.InterpretDelayslot();
}
/* VADD_S */
__forceinline void AllegrexInstructionTemplate< 0x60000000, 0xFF808080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVADD<1>(vd(opcode), vs(opcode), vt(opcode));
}
/* VADD_P */
__forceinline void AllegrexInstructionTemplate< 0x60000080, 0xFF808080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVADD<2>(vd(opcode), vs(opcode), vt(opcode));
}
/* VADD_T */
__forceinline void AllegrexInstructionTemplate< 0x60008000, 0xFF808080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVADD<3>(vd(opcode), vs(opcode), vt(opcode));
}
/* VADD_Q */
__forceinline void AllegrexInstructionTemplate< 0x60008080, 0xFF808080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVADD<4>(vd(opcode), vs(opcode), vt(opcode));
}
/* VSUB_S */
__forceinline void AllegrexInstructionTemplate< 0x60800000, 0xFF808080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVSUB<1>(vd(opcode), vs(opcode), vt(opcode));
}
/* VSUB_P */
__forceinline void AllegrexInstructionTemplate< 0x60800080, 0xFF808080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVSUB<2>(vd(opcode), vs(opcode), vt(opcode));
}
/* VSUB_T */
__forceinline void AllegrexInstructionTemplate< 0x60808000, 0xFF808080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVSUB<3>(vd(opcode), vs(opcode), vt(opcode));
}
/* VSUB_Q */
__forceinline void AllegrexInstructionTemplate< 0x60808080, 0xFF808080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVSUB<4>(vd(opcode), vs(opcode), vt(opcode));
}
/* VSBN_S */
__forceinline void AllegrexInstructionTemplate< 0x61000000, 0xFF808080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVSBN<1>(vd(opcode), vs(opcode), vt(opcode));
}
/* VDIV_S */
__forceinline void AllegrexInstructionTemplate< 0x63800000, 0xFF808080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVDIV<1>(vd(opcode), vs(opcode), vt(opcode));
}
/* VDIV_P */
__forceinline void AllegrexInstructionTemplate< 0x63800080, 0xFF808080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVDIV<2>(vd(opcode), vs(opcode), vt(opcode));
}
/* VDIV_T */
__forceinline void AllegrexInstructionTemplate< 0x63808000, 0xFF808080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVDIV<3>(vd(opcode), vs(opcode), vt(opcode));
}
/* VDIV_Q */
__forceinline void AllegrexInstructionTemplate< 0x63808080, 0xFF808080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVDIV<4>(vd(opcode), vs(opcode), vt(opcode));
}
/* VMUL_S */
__forceinline void AllegrexInstructionTemplate< 0x64000000, 0xFF808080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVMUL<1>(vd(opcode), vs(opcode), vt(opcode));
}
/* VMUL_P */
__forceinline void AllegrexInstructionTemplate< 0x64000080, 0xFF808080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVMUL<2>(vd(opcode), vs(opcode), vt(opcode));
}
/* VMUL_T */
__forceinline void AllegrexInstructionTemplate< 0x64008000, 0xFF808080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVMUL<3>(vd(opcode), vs(opcode), vt(opcode));
}
/* VMUL_Q */
__forceinline void AllegrexInstructionTemplate< 0x64008080, 0xFF808080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVMUL<4>(vd(opcode), vs(opcode), vt(opcode));
}
/* VDOT_P */
__forceinline void AllegrexInstructionTemplate< 0x64800080, 0xFF808080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVDOT<2>(vd(opcode), vs(opcode), vt(opcode));
}
/* VDOT_T */
__forceinline void AllegrexInstructionTemplate< 0x64808000, 0xFF808080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVDOT<3>(vd(opcode), vs(opcode), vt(opcode));
}
/* VDOT_Q */
__forceinline void AllegrexInstructionTemplate< 0x64808080, 0xFF808080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVDOT<4>(vd(opcode), vs(opcode), vt(opcode));
}
/* VSCL_P */
__forceinline void AllegrexInstructionTemplate< 0x65000080, 0xFF808080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVSCL<2>(vd(opcode), vs(opcode), vt(opcode));
}
/* VSCL_T */
__forceinline void AllegrexInstructionTemplate< 0x65008000, 0xFF808080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVSCL<3>(vd(opcode), vs(opcode), vt(opcode));
}
/* VSCL_Q */
__forceinline void AllegrexInstructionTemplate< 0x65008080, 0xFF808080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVSCL<4>(vd(opcode), vs(opcode), vt(opcode));
}
/* VHDP_P */
__forceinline void AllegrexInstructionTemplate< 0x66000080, 0xFF808080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVHDP<2>(vd(opcode), vs(opcode), vt(opcode));
}
/* VHDP_T */
__forceinline void AllegrexInstructionTemplate< 0x66008000, 0xFF808080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVHDP<3>(vd(opcode), vs(opcode), vt(opcode));
}
/* VHDP_Q */
__forceinline void AllegrexInstructionTemplate< 0x66008080, 0xFF808080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVHDP<4>(vd(opcode), vs(opcode), vt(opcode));
}
/* VCRS_T */
__forceinline void AllegrexInstructionTemplate< 0x66808000, 0xFF808080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVCRS<3>(vd(opcode), vs(opcode), vt(opcode));
}
/* VDET_P */
__forceinline void AllegrexInstructionTemplate< 0x67000080, 0xFF808080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVDET<2>(vd(opcode), vs(opcode), vt(opcode));
}
/* MFV */
__forceinline void AllegrexInstructionTemplate< 0x48600000, 0xFFE0FF80 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doMFV(rt(opcode), vd(opcode));
}
/* MFVC */
__forceinline void AllegrexInstructionTemplate< 0x48600080, 0xFFE0FF80 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doMFVC(rt(opcode), vd(opcode));
}
/* MTV */
__forceinline void AllegrexInstructionTemplate< 0x48E00000, 0xFFE0FF80 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doMTV(rt(opcode), vd(opcode));
}
/* MTVC */
__forceinline void AllegrexInstructionTemplate< 0x48E00080, 0xFFE0FF80 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doMTVC(rt(opcode), vd(opcode));
}
/* VCMP_S */
__forceinline void AllegrexInstructionTemplate< 0x6C000000, 0xFF808088 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVCMP<1>(vs(opcode), vt(opcode), (opcode>>0)&15);
}
/* VCMP_P */
__forceinline void AllegrexInstructionTemplate< 0x6C000080, 0xFF808088 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVCMP<2>(vs(opcode), vt(opcode), (opcode>>0)&15);
}
/* VCMP_T */
__forceinline void AllegrexInstructionTemplate< 0x6C008000, 0xFF808088 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVCMP<3>(vs(opcode), vt(opcode), (opcode>>0)&15);
}
/* VCMP_Q */
__forceinline void AllegrexInstructionTemplate< 0x6C008080, 0xFF808088 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVCMP<4>(vs(opcode), vt(opcode), (opcode>>0)&15);
}
/* VMIN_S */
__forceinline void AllegrexInstructionTemplate< 0x6D000000, 0xFF808088 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVMIN<1>(vd(opcode), vs(opcode), vt(opcode));
}
/* VMIN_P */
__forceinline void AllegrexInstructionTemplate< 0x6D000080, 0xFF808088 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVMIN<2>(vd(opcode), vs(opcode), vt(opcode));
}
/* VMIN_T */
__forceinline void AllegrexInstructionTemplate< 0x6D008000, 0xFF808088 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVMIN<3>(vd(opcode), vs(opcode), vt(opcode));
}
/* VMIN_Q */
__forceinline void AllegrexInstructionTemplate< 0x6D008080, 0xFF808088 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVMIN<4>(vd(opcode), vs(opcode), vt(opcode));
}
/* VMAX_S */
__forceinline void AllegrexInstructionTemplate< 0x6D800000, 0xFF808080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVMAX<1>(vd(opcode), vs(opcode), vt(opcode));
}
/* VMAX_P */
__forceinline void AllegrexInstructionTemplate< 0x6D800080, 0xFF808080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVMAX<2>(vd(opcode), vs(opcode), vt(opcode));
}
/* VMAX_T */
__forceinline void AllegrexInstructionTemplate< 0x6D808000, 0xFF808080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVMAX<3>(vd(opcode), vs(opcode), vt(opcode));
}
/* VMAX_Q */
__forceinline void AllegrexInstructionTemplate< 0x6D808080, 0xFF808080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVMAX<4>(vd(opcode), vs(opcode), vt(opcode));
}
/* VSCMP_S */
__forceinline void AllegrexInstructionTemplate< 0x6E800000, 0xFF808080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVSCMP<1>(vd(opcode), vs(opcode), vt(opcode));
}
/* VSCMP_P */
__forceinline void AllegrexInstructionTemplate< 0x6E800080, 0xFF808080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVSCMP<2>(vd(opcode), vs(opcode), vt(opcode));
}
/* VSCMP_T */
__forceinline void AllegrexInstructionTemplate< 0x6E808000, 0xFF808080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVSCMP<3>(vd(opcode), vs(opcode), vt(opcode));
}
/* VSCMP_Q */
__forceinline void AllegrexInstructionTemplate< 0x6E808080, 0xFF808080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVSCMP<4>(vd(opcode), vs(opcode), vt(opcode));
}
/* VSGE_S */
__forceinline void AllegrexInstructionTemplate< 0x6F000000, 0xFF808080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVSGE<1>(vd(opcode), vs(opcode), vt(opcode));
}
/* VSGE_P */
__forceinline void AllegrexInstructionTemplate< 0x6F000080, 0xFF808080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVSGE<2>(vd(opcode), vs(opcode), vt(opcode));
}
/* VSGE_T */
__forceinline void AllegrexInstructionTemplate< 0x6F008000, 0xFF808080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVSGE<3>(vd(opcode), vs(opcode), vt(opcode));
}
/* VSGE_Q */
__forceinline void AllegrexInstructionTemplate< 0x6F008080, 0xFF808080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVSGE<4>(vd(opcode), vs(opcode), vt(opcode));
}
/* VSLT_S */
__forceinline void AllegrexInstructionTemplate< 0x6E000000, 0xFF808080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVSLT<1>(vd(opcode), vs(opcode), vt(opcode));
}
/* VSLT_P */
__forceinline void AllegrexInstructionTemplate< 0x6E000080, 0xFF808080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVSLT<2>(vd(opcode), vs(opcode), vt(opcode));
}
/* VSLT_T */
__forceinline void AllegrexInstructionTemplate< 0x6E008000, 0xFF808080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVSLT<3>(vd(opcode), vs(opcode), vt(opcode));
}
/* VSLT_Q */
__forceinline void AllegrexInstructionTemplate< 0x6E008080, 0xFF808080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVSLT<4>(vd(opcode), vs(opcode), vt(opcode));
}
/* VMOV_S */
__forceinline void AllegrexInstructionTemplate< 0xD0000000, 0xFFFF8080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVMOV<1>(vd(opcode), vs(opcode));
}
/* VMOV_P */
__forceinline void AllegrexInstructionTemplate< 0xD0000080, 0xFFFF8080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVMOV<2>(vd(opcode), vs(opcode));
}
/* VMOV_T */
__forceinline void AllegrexInstructionTemplate< 0xD0008000, 0xFFFF8080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVMOV<3>(vd(opcode), vs(opcode));
}
/* VMOV_Q */
__forceinline void AllegrexInstructionTemplate< 0xD0008080, 0xFFFF8080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVMOV<4>(vd(opcode), vs(opcode));
}
/* VABS_S */
__forceinline void AllegrexInstructionTemplate< 0xD0010000, 0xFFFF8080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVABS<1>(vd(opcode), vs(opcode));
}
/* VABS_P */
__forceinline void AllegrexInstructionTemplate< 0xD0010080, 0xFFFF8080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVABS<2>(vd(opcode), vs(opcode));
}
/* VABS_T */
__forceinline void AllegrexInstructionTemplate< 0xD0018000, 0xFFFF8080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVABS<3>(vd(opcode), vs(opcode));
}
/* VABS_Q */
__forceinline void AllegrexInstructionTemplate< 0xD0018080, 0xFFFF8080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVABS<4>(vd(opcode), vs(opcode));
}
/* VNEG_S */
__forceinline void AllegrexInstructionTemplate< 0xD0020000, 0xFFFF8080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVNEG<1>(vd(opcode), vs(opcode));
}
/* VNEG_P */
__forceinline void AllegrexInstructionTemplate< 0xD0020080, 0xFFFF8080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVNEG<2>(vd(opcode), vs(opcode));
}
/* VNEG_T */
__forceinline void AllegrexInstructionTemplate< 0xD0028000, 0xFFFF8080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVNEG<3>(vd(opcode), vs(opcode));
}
/* VNEG_Q */
__forceinline void AllegrexInstructionTemplate< 0xD0028080, 0xFFFF8080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVNEG<4>(vd(opcode), vs(opcode));
}
/* VIDT_S */
__forceinline void AllegrexInstructionTemplate< 0xD0030000, 0xFFFF8F80 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVIDT<1>(vd(opcode));
}
/* VIDT_P */
__forceinline void AllegrexInstructionTemplate< 0xD0030080, 0xFFFF8F80 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVIDT<2>(vd(opcode));
}
/* VIDT_T */
__forceinline void AllegrexInstructionTemplate< 0xD0038000, 0xFFFF8F80 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVIDT<3>(vd(opcode));
}
/* VIDT_Q */
__forceinline void AllegrexInstructionTemplate< 0xD0038080, 0xFFFF8F80 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVIDT<4>(vd(opcode));
}
/* VSAT0_S */
__forceinline void AllegrexInstructionTemplate< 0xD0040000, 0xFFFF8080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVSAT0<1>(vd(opcode), vs(opcode));
}
/* VSAT0_P */
__forceinline void AllegrexInstructionTemplate< 0xD0040080, 0xFFFF8080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVSAT0<2>(vd(opcode), vs(opcode));
}
/* VSAT0_T */
__forceinline void AllegrexInstructionTemplate< 0xD0048000, 0xFFFF8080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVSAT0<3>(vd(opcode), vs(opcode));
}
/* VSAT0_Q */
__forceinline void AllegrexInstructionTemplate< 0xD0048080, 0xFFFF8080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVSAT0<4>(vd(opcode), vs(opcode));
}
/* VSAT1_S */
__forceinline void AllegrexInstructionTemplate< 0xD0050000, 0xFFFF8080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVSAT1<1>(vd(opcode), vs(opcode));
}
/* VSAT1_P */
__forceinline void AllegrexInstructionTemplate< 0xD0050080, 0xFFFF8080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVSAT1<2>(vd(opcode), vs(opcode));
}
/* VSAT1_T */
__forceinline void AllegrexInstructionTemplate< 0xD0058000, 0xFFFF8080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVSAT1<3>(vd(opcode), vs(opcode));
}
/* VSAT1_Q */
__forceinline void AllegrexInstructionTemplate< 0xD0058080, 0xFFFF8080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVSAT1<4>(vd(opcode), vs(opcode));
}
/* VZERO_S */
__forceinline void AllegrexInstructionTemplate< 0xD0060000, 0xFFFF8F80 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVZERO<1>(vd(opcode));
}
/* VZERO_P */
__forceinline void AllegrexInstructionTemplate< 0xD0060080, 0xFFFF8F80 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVZERO<2>(vd(opcode));
}
/* VZERO_T */
__forceinline void AllegrexInstructionTemplate< 0xD0068000, 0xFFFF8F80 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVZERO<3>(vd(opcode));
}
/* VZERO_Q */
__forceinline void AllegrexInstructionTemplate< 0xD0068080, 0xFFFF8F80 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVZERO<4>(vd(opcode));
}
/* VONE_S */
__forceinline void AllegrexInstructionTemplate< 0xD0070000, 0xFFFF8F80 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVONE<1>(vd(opcode));
}
/* VONE_P */
__forceinline void AllegrexInstructionTemplate< 0xD0070080, 0xFFFF8F80 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVONE<2>(vd(opcode));
}
/* VONE_T */
__forceinline void AllegrexInstructionTemplate< 0xD0078000, 0xFFFF8F80 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVONE<3>(vd(opcode));
}
/* VONE_Q */
__forceinline void AllegrexInstructionTemplate< 0xD0078080, 0xFFFF8F80 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVONE<4>(vd(opcode));
}
/* VRCP_S */
__forceinline void AllegrexInstructionTemplate< 0xD0100000, 0xFFFF8080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVRCP<1>(vd(opcode), vs(opcode));
}
/* VRCP_P */
__forceinline void AllegrexInstructionTemplate< 0xD0100080, 0xFFFF8080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVRCP<2>(vd(opcode), vs(opcode));
}
/* VRCP_T */
__forceinline void AllegrexInstructionTemplate< 0xD0108000, 0xFFFF8080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVRCP<3>(vd(opcode), vs(opcode));
}
/* VRCP_Q */
__forceinline void AllegrexInstructionTemplate< 0xD0108080, 0xFFFF8080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVRCP<4>(vd(opcode), vs(opcode));
}
/* VRSQ_S */
__forceinline void AllegrexInstructionTemplate< 0xD0110000, 0xFFFF8080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVRSQ<1>(vd(opcode), vs(opcode));
}
/* VRSQ_P */
__forceinline void AllegrexInstructionTemplate< 0xD0110080, 0xFFFF8080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVRSQ<2>(vd(opcode), vs(opcode));
}
/* VRSQ_T */
__forceinline void AllegrexInstructionTemplate< 0xD0118000, 0xFFFF8080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVRSQ<3>(vd(opcode), vs(opcode));
}
/* VRSQ_Q */
__forceinline void AllegrexInstructionTemplate< 0xD0118080, 0xFFFF8080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVRSQ<4>(vd(opcode), vs(opcode));
}
/* VSIN_S */
__forceinline void AllegrexInstructionTemplate< 0xD0120000, 0xFFFF8080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVSIN<1>(vd(opcode), vs(opcode));
}
/* VSIN_P */
__forceinline void AllegrexInstructionTemplate< 0xD0120080, 0xFFFF8080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVSIN<2>(vd(opcode), vs(opcode));
}
/* VSIN_T */
__forceinline void AllegrexInstructionTemplate< 0xD0128000, 0xFFFF8080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVSIN<3>(vd(opcode), vs(opcode));
}
/* VSIN_Q */
__forceinline void AllegrexInstructionTemplate< 0xD0128080, 0xFFFF8080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVSIN<4>(vd(opcode), vs(opcode));
}
/* VCOS_S */
__forceinline void AllegrexInstructionTemplate< 0xD0130000, 0xFFFF8080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVCOS<1>(vd(opcode), vs(opcode));
}
/* VCOS_P */
__forceinline void AllegrexInstructionTemplate< 0xD0130080, 0xFFFF8080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVCOS<2>(vd(opcode), vs(opcode));
}
/* VCOS_T */
__forceinline void AllegrexInstructionTemplate< 0xD0138000, 0xFFFF8080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVCOS<3>(vd(opcode), vs(opcode));
}
/* VCOS_Q */
__forceinline void AllegrexInstructionTemplate< 0xD0138080, 0xFFFF8080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVCOS<4>(vd(opcode), vs(opcode));
}
/* VEXP2_S */
__forceinline void AllegrexInstructionTemplate< 0xD0140000, 0xFFFF8080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVEXP2<1>(vd(opcode), vs(opcode));
}
/* VEXP2_P */
__forceinline void AllegrexInstructionTemplate< 0xD0140080, 0xFFFF8080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVEXP2<2>(vd(opcode), vs(opcode));
}
/* VEXP2_T */
__forceinline void AllegrexInstructionTemplate< 0xD0148000, 0xFFFF8080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVEXP2<3>(vd(opcode), vs(opcode));
}
/* VEXP2_Q */
__forceinline void AllegrexInstructionTemplate< 0xD0148080, 0xFFFF8080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVEXP2<4>(vd(opcode), vs(opcode));
}
/* VLOG2_S */
__forceinline void AllegrexInstructionTemplate< 0xD0150000, 0xFFFF8080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVLOG2<1>(vd(opcode), vs(opcode));
}
/* VLOG2_P */
__forceinline void AllegrexInstructionTemplate< 0xD0150080, 0xFFFF8080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVLOG2<2>(vd(opcode), vs(opcode));
}
/* VLOG2_T */
__forceinline void AllegrexInstructionTemplate< 0xD0158000, 0xFFFF8080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVLOG2<3>(vd(opcode), vs(opcode));
}
/* VLOG2_Q */
__forceinline void AllegrexInstructionTemplate< 0xD0158080, 0xFFFF8080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVLOG2<4>(vd(opcode), vs(opcode));
}
/* VSQRT_S */
__forceinline void AllegrexInstructionTemplate< 0xD0160000, 0xFFFF8080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVSQRT<1>(vd(opcode), vs(opcode));
}
/* VSQRT_P */
__forceinline void AllegrexInstructionTemplate< 0xD0160080, 0xFFFF8080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVSQRT<2>(vd(opcode), vs(opcode));
}
/* VSQRT_T */
__forceinline void AllegrexInstructionTemplate< 0xD0168000, 0xFFFF8080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVSQRT<3>(vd(opcode), vs(opcode));
}
/* VSQRT_Q */
__forceinline void AllegrexInstructionTemplate< 0xD0168080, 0xFFFF8080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVSQRT<4>(vd(opcode), vs(opcode));
}
/* VASIN_S */
__forceinline void AllegrexInstructionTemplate< 0xD0170000, 0xFFFF8080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVASIN<1>(vd(opcode), vs(opcode));
}
/* VASIN_P */
__forceinline void AllegrexInstructionTemplate< 0xD0170080, 0xFFFF8080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVASIN<2>(vd(opcode), vs(opcode));
}
/* VASIN_T */
__forceinline void AllegrexInstructionTemplate< 0xD0178000, 0xFFFF8080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVASIN<3>(vd(opcode), vs(opcode));
}
/* VASIN_Q */
__forceinline void AllegrexInstructionTemplate< 0xD0178080, 0xFFFF8080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVASIN<4>(vd(opcode), vs(opcode));
}
/* VNRCP_S */
__forceinline void AllegrexInstructionTemplate< 0xD0180000, 0xFFFF8080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVNRCP<1>(vd(opcode), vs(opcode));
}
/* VNRCP_P */
__forceinline void AllegrexInstructionTemplate< 0xD0180080, 0xFFFF8080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVNRCP<2>(vd(opcode), vs(opcode));
}
/* VNRCP_T */
__forceinline void AllegrexInstructionTemplate< 0xD0188000, 0xFFFF8080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVNRCP<3>(vd(opcode), vs(opcode));
}
/* VNRCP_Q */
__forceinline void AllegrexInstructionTemplate< 0xD0188080, 0xFFFF8080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVNRCP<4>(vd(opcode), vs(opcode));
}
/* VNSIN_S */
__forceinline void AllegrexInstructionTemplate< 0xD01A0000, 0xFFFF8080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVNSIN<1>(vd(opcode), vs(opcode));
}
/* VNSIN_P */
__forceinline void AllegrexInstructionTemplate< 0xD01A0080, 0xFFFF8080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVNSIN<2>(vd(opcode), vs(opcode));
}
/* VNSIN_T */
__forceinline void AllegrexInstructionTemplate< 0xD01A8000, 0xFFFF8080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVNSIN<3>(vd(opcode), vs(opcode));
}
/* VNSIN_Q */
__forceinline void AllegrexInstructionTemplate< 0xD01A8080, 0xFFFF8080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVNSIN<4>(vd(opcode), vs(opcode));
}
/* VREXP2_S */
__forceinline void AllegrexInstructionTemplate< 0xD01C0000, 0xFFFF8080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVREXP2<1>(vd(opcode), vs(opcode));
}
/* VREXP2_P */
__forceinline void AllegrexInstructionTemplate< 0xD01C0080, 0xFFFF8080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVREXP2<2>(vd(opcode), vs(opcode));
}
/* VREXP2_T */
__forceinline void AllegrexInstructionTemplate< 0xD01C8000, 0xFFFF8080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVREXP2<3>(vd(opcode), vs(opcode));
}
/* VREXP2_Q */
__forceinline void AllegrexInstructionTemplate< 0xD01C8080, 0xFFFF8080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVREXP2<4>(vd(opcode), vs(opcode));
}
/* VRNDS_S */
__forceinline void AllegrexInstructionTemplate< 0xD0200000, 0xFFFF808F >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doUNK("Unimplemented vrnds.s instruction");
}
/* VRNDI_S */
__forceinline void AllegrexInstructionTemplate< 0xD0210000, 0xFFFF8F80 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVRNDI<1>(vd(opcode));
}
/* VRNDI_P */
__forceinline void AllegrexInstructionTemplate< 0xD0210080, 0xFFFF8F80 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVRNDI<2>(vd(opcode));
}
/* VRNDI_T */
__forceinline void AllegrexInstructionTemplate< 0xD0218000, 0xFFFF8F80 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVRNDI<3>(vd(opcode));
}
/* VRNDI_Q */
__forceinline void AllegrexInstructionTemplate< 0xD0218080, 0xFFFF8F80 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVRNDI<4>(vd(opcode));
}
/* VRNDF1_S */
__forceinline void AllegrexInstructionTemplate< 0xD0220000, 0xFFFF8F80 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVRNDF1<1>(vd(opcode));
}
/* VRNDF1_P */
__forceinline void AllegrexInstructionTemplate< 0xD0220080, 0xFFFF8F80 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVRNDF1<2>(vd(opcode));
}
/* VRNDF1_T */
__forceinline void AllegrexInstructionTemplate< 0xD0228000, 0xFFFF8F80 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVRNDF1<3>(vd(opcode));
}
/* VRNDF1_Q */
__forceinline void AllegrexInstructionTemplate< 0xD0228080, 0xFFFF8F80 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVRNDF1<4>(vd(opcode));
}
/* VRNDF2_S */
__forceinline void AllegrexInstructionTemplate< 0xD0230000, 0xFFFF8F80 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVRNDF2<1>(vd(opcode));
}
/* VRNDF2_P */
__forceinline void AllegrexInstructionTemplate< 0xD0230080, 0xFFFF8F80 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVRNDF2<2>(vd(opcode));
}
/* VRNDF2_T */
__forceinline void AllegrexInstructionTemplate< 0xD0238000, 0xFFFF8F80 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVRNDF2<3>(vd(opcode));
}
/* VRNDF2_Q */
__forceinline void AllegrexInstructionTemplate< 0xD0238080, 0xFFFF8F80 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVRNDF2<4>(vd(opcode));
}
/* VF2H_P */
__forceinline void AllegrexInstructionTemplate< 0xD0320080, 0xFFFF8080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVF2H<2>(vd(opcode), vs(opcode));
}
/* VF2H_Q */
__forceinline void AllegrexInstructionTemplate< 0xD0328080, 0xFFFF8080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVF2H<4>(vd(opcode), vs(opcode));
}
/* VH2F_S */
__forceinline void AllegrexInstructionTemplate< 0xD0330000, 0xFFFF8080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVH2F<1>(vd(opcode), vs(opcode));
}
/* VH2F_P */
__forceinline void AllegrexInstructionTemplate< 0xD0330080, 0xFFFF8080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVH2F<2>(vd(opcode), vs(opcode));
}
/* VSBZ_P */
__forceinline void AllegrexInstructionTemplate< 0xD0360000, 0xFFFF8080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doUNK("Unimplemented vsbz.s instruction");
}
/* VLGB_S */
__forceinline void AllegrexInstructionTemplate< 0xD0370000, 0xFFFF8080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doUNK("Unimplemented vlgb.s instruction");
}
/* VUC2I_S */
__forceinline void AllegrexInstructionTemplate< 0xD0380000, 0xFFFF8080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVUC2I<1>(vd(opcode), vs(opcode));
}
/* VC2I_S */
__forceinline void AllegrexInstructionTemplate< 0xD0390000, 0xFFFF8080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVC2I<1>(vd(opcode), vs(opcode));
}
/* VUS2I_S */
__forceinline void AllegrexInstructionTemplate< 0xD03A0000, 0xFFFF8080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVUS2I<1>(vd(opcode), vs(opcode));
}
/* VUS2I_P */
__forceinline void AllegrexInstructionTemplate< 0xD03A0080, 0xFFFF8080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVUS2I<2>(vd(opcode), vs(opcode));
}
/* VS2I_S */
__forceinline void AllegrexInstructionTemplate< 0xD03B0000, 0xFFFF8080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVS2I<1>(vd(opcode), vs(opcode));
}
/* VS2I_P */
__forceinline void AllegrexInstructionTemplate< 0xD03B0080, 0xFFFF8080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVS2I<2>(vd(opcode), vs(opcode));
}
/* VI2UC_Q */
__forceinline void AllegrexInstructionTemplate< 0xD03C8080, 0xFFFF8080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVI2UC<4>(vd(opcode), vs(opcode));
}
/* VI2C_Q */
__forceinline void AllegrexInstructionTemplate< 0xD03D8080, 0xFFFF8080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVI2C<4>(vd(opcode), vs(opcode));
}
/* VI2US_P */
__forceinline void AllegrexInstructionTemplate< 0xD03E0080, 0xFFFF8080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVI2US<2>(vd(opcode), vs(opcode));
}
/* VI2US_Q */
__forceinline void AllegrexInstructionTemplate< 0xD03E8080, 0xFFFF8080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVI2US<4>(vd(opcode), vs(opcode));
}
/* VI2S_P */
__forceinline void AllegrexInstructionTemplate< 0xD03F0080, 0xFFFF8080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVI2S<2>(vd(opcode), vs(opcode));
}
/* VI2S_Q */
__forceinline void AllegrexInstructionTemplate< 0xD03F8080, 0xFFFF8080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVI2S<4>(vd(opcode), vs(opcode));
}
/* VSRT1_Q */
__forceinline void AllegrexInstructionTemplate< 0xD0408080, 0xFFFF8080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVSRT1<4>(vd(opcode), vs(opcode));
}
/* VSRT2_Q */
__forceinline void AllegrexInstructionTemplate< 0xD0418080, 0xFFFF8080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVSRT2<4>(vd(opcode), vs(opcode));
}
/* VBFY1_P */
__forceinline void AllegrexInstructionTemplate< 0xD0420080, 0xFFFF8080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVBFY1<2>(vd(opcode), vs(opcode));
}
/* VBFY1_Q */
__forceinline void AllegrexInstructionTemplate< 0xD0428080, 0xFFFF8080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVBFY1<4>(vd(opcode), vs(opcode));
}
/* VBFY2_Q */
__forceinline void AllegrexInstructionTemplate< 0xD0438080, 0xFFFF8080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVBFY2<4>(vd(opcode), vs(opcode));
}
/* VOCP_S */
__forceinline void AllegrexInstructionTemplate< 0xD0440000, 0xFFFF8080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVOCP<1>(vd(opcode), vs(opcode));
}
/* VOCP_P */
__forceinline void AllegrexInstructionTemplate< 0xD0440080, 0xFFFF8080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVOCP<2>(vd(opcode), vs(opcode));
}
/* VOCP_T */
__forceinline void AllegrexInstructionTemplate< 0xD0448000, 0xFFFF8080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVOCP<3>(vd(opcode), vs(opcode));
}
/* VOCP_Q */
__forceinline void AllegrexInstructionTemplate< 0xD0448080, 0xFFFF8080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVOCP<4>(vd(opcode), vs(opcode));
}
/* VSOCP_S */
__forceinline void AllegrexInstructionTemplate< 0xD0450000, 0xFFFF8080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVSOCP<1>(vd(opcode), vs(opcode));
}
/* VSOCP_P */
__forceinline void AllegrexInstructionTemplate< 0xD0450080, 0xFFFF8080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVSOCP<2>(vd(opcode), vs(opcode));
}
/* VFAD_P */
__forceinline void AllegrexInstructionTemplate< 0xD0460080, 0xFFFF8080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVFAD<2>(vd(opcode), vs(opcode));
}
/* VFAD_T */
__forceinline void AllegrexInstructionTemplate< 0xD0468000, 0xFFFF8080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVFAD<3>(vd(opcode), vs(opcode));
}
/* VFAD_Q */
__forceinline void AllegrexInstructionTemplate< 0xD0468080, 0xFFFF8080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVFAD<4>(vd(opcode), vs(opcode));
}
/* VAVG_P */
__forceinline void AllegrexInstructionTemplate< 0xD0470080, 0xFFFF8080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVAVG<2>(vd(opcode), vs(opcode));
}
/* VAVG_T */
__forceinline void AllegrexInstructionTemplate< 0xD0478000, 0xFFFF8080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVAVG<3>(vd(opcode), vs(opcode));
}
/* VAVG_Q */
__forceinline void AllegrexInstructionTemplate< 0xD0478080, 0xFFFF8080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVAVG<4>(vd(opcode), vs(opcode));
}
/* VSRT3_Q */
__forceinline void AllegrexInstructionTemplate< 0xD0488080, 0xFFFF8080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVSRT3<4>(vd(opcode), vs(opcode));
}
/* VSRT4_Q */
__forceinline void AllegrexInstructionTemplate< 0xD0498080, 0xFFFF8080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVSRT4<4>(vd(opcode), vs(opcode));
}
/* VSGN_S */
__forceinline void AllegrexInstructionTemplate< 0xD04A0000, 0xFFFF8080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVSGN<1>(vd(opcode), vs(opcode));
}
/* VSGN_P */
__forceinline void AllegrexInstructionTemplate< 0xD04A0080, 0xFFFF8080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVSGN<2>(vd(opcode), vs(opcode));
}
/* VSGN_T */
__forceinline void AllegrexInstructionTemplate< 0xD04A8000, 0xFFFF8080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVSGN<3>(vd(opcode), vs(opcode));
}
/* VSGN_Q */
__forceinline void AllegrexInstructionTemplate< 0xD04A8080, 0xFFFF8080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVSGN<4>(vd(opcode), vs(opcode));
}
/* VMFVC */
__forceinline void AllegrexInstructionTemplate< 0xD0508000, 0xFFFF8080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVMFVC(vd(opcode), vs(opcode));
}
/* VMTVC */
__forceinline void AllegrexInstructionTemplate< 0xD0510080, 0xFFFF8080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVMTVC(vd(opcode), vs(opcode));
}
/* VT4444_Q */
__forceinline void AllegrexInstructionTemplate< 0xD0598080, 0xFFFF8080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVT4444<4>(vd(opcode), vs(opcode));
}
/* VT5551_Q */
__forceinline void AllegrexInstructionTemplate< 0xD05A8080, 0xFFFF8080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVT5551<4>(vd(opcode), vs(opcode));
}
/* VT5650_Q */
__forceinline void AllegrexInstructionTemplate< 0xD05B8080, 0xFFFF8080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVT5650<4>(vd(opcode), vs(opcode));
}
/* VCST_S */
__forceinline void AllegrexInstructionTemplate< 0xD0600000, 0xFFE08F80 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVCST<1>(vd(opcode), uimm5(opcode));
}
/* VCST_P */
__forceinline void AllegrexInstructionTemplate< 0xD0600080, 0xFFE08F80 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVCST<2>(vd(opcode), uimm5(opcode));
}
/* VCST_T */
__forceinline void AllegrexInstructionTemplate< 0xD0608000, 0xFFE08F80 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVCST<3>(vd(opcode), uimm5(opcode));
}
/* VCST_Q */
__forceinline void AllegrexInstructionTemplate< 0xD0608080, 0xFFE08F80 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVCST<4>(vd(opcode), uimm5(opcode));
}
/* VF2IN_S */
__forceinline void AllegrexInstructionTemplate< 0xD2000000, 0xFFE08080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVF2IN<1>(vd(opcode), vs(opcode), uimm5(opcode));
}
/* VF2IN_P */
__forceinline void AllegrexInstructionTemplate< 0xD2000080, 0xFFE08080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVF2IN<2>(vd(opcode), vs(opcode), uimm5(opcode));
}
/* VF2IN_T */
__forceinline void AllegrexInstructionTemplate< 0xD2008000, 0xFFE08080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVF2IN<3>(vd(opcode), vs(opcode), uimm5(opcode));
}
/* VF2IN_Q */
__forceinline void AllegrexInstructionTemplate< 0xD2008080, 0xFFE08080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVF2IN<4>(vd(opcode), vs(opcode), uimm5(opcode));
}
/* VF2IZ_S */
__forceinline void AllegrexInstructionTemplate< 0xD2200000, 0xFFE08080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVF2IZ<1>(vd(opcode), vs(opcode), uimm5(opcode));
}
/* VF2IZ_P */
__forceinline void AllegrexInstructionTemplate< 0xD2200080, 0xFFE08080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVF2IZ<2>(vd(opcode), vs(opcode), uimm5(opcode));
}
/* VF2IZ_T */
__forceinline void AllegrexInstructionTemplate< 0xD2208000, 0xFFE08080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVF2IZ<3>(vd(opcode), vs(opcode), uimm5(opcode));
}
/* VF2IZ_Q */
__forceinline void AllegrexInstructionTemplate< 0xD2208080, 0xFFE08080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVF2IZ<4>(vd(opcode), vs(opcode), uimm5(opcode));
}
/* VF2IU_S */
__forceinline void AllegrexInstructionTemplate< 0xD2400000, 0xFFE08080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVF2IU<1>(vd(opcode), vs(opcode), uimm5(opcode));
}
/* VF2IU_P */
__forceinline void AllegrexInstructionTemplate< 0xD2400080, 0xFFE08080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVF2IU<2>(vd(opcode), vs(opcode), uimm5(opcode));
}
/* VF2IU_T */
__forceinline void AllegrexInstructionTemplate< 0xD2408000, 0xFFE08080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVF2IU<3>(vd(opcode), vs(opcode), uimm5(opcode));
}
/* VF2IU_Q */
__forceinline void AllegrexInstructionTemplate< 0xD2408080, 0xFFE08080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVF2IU<4>(vd(opcode), vs(opcode), uimm5(opcode));
}
/* VF2ID_S */
__forceinline void AllegrexInstructionTemplate< 0xD2600000, 0xFFE08080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVF2ID<1>(vd(opcode), vs(opcode), uimm5(opcode));
}
/* VF2ID_P */
__forceinline void AllegrexInstructionTemplate< 0xD2600080, 0xFFE08080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVF2ID<2>(vd(opcode), vs(opcode), uimm5(opcode));
}
/* VF2ID_T */
__forceinline void AllegrexInstructionTemplate< 0xD2608000, 0xFFE08080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVF2ID<3>(vd(opcode), vs(opcode), uimm5(opcode));
}
/* VF2ID_Q */
__forceinline void AllegrexInstructionTemplate< 0xD2608080, 0xFFE08080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVF2ID<4>(vd(opcode), vs(opcode), uimm5(opcode));
}
/* VI2F_S */
__forceinline void AllegrexInstructionTemplate< 0xD2800000, 0xFFE08080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVI2F<1>(vd(opcode), vs(opcode), uimm5(opcode));
}
/* VI2F_P */
__forceinline void AllegrexInstructionTemplate< 0xD2800080, 0xFFE08080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVI2F<2>(vd(opcode), vs(opcode), uimm5(opcode));
}
/* VI2F_T */
__forceinline void AllegrexInstructionTemplate< 0xD2808000, 0xFFE08080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVI2F<3>(vd(opcode), vs(opcode), uimm5(opcode));
}
/* VI2F_Q */
__forceinline void AllegrexInstructionTemplate< 0xD2808080, 0xFFE08080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVI2F<4>(vd(opcode), vs(opcode), uimm5(opcode));
}
/* VCMOVT_S */
__forceinline void AllegrexInstructionTemplate< 0xD2A00000, 0xFFF88080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVCMOVT<1>(vd(opcode), vs(opcode), uimm3(opcode));
}
/* VCMOVT_P */
__forceinline void AllegrexInstructionTemplate< 0xD2A00080, 0xFFF88080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVCMOVT<2>(vd(opcode), vs(opcode), uimm3(opcode));
}
/* VCMOVT_T */
__forceinline void AllegrexInstructionTemplate< 0xD2A08000, 0xFFF88080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVCMOVT<3>(vd(opcode), vs(opcode), uimm3(opcode));
}
/* VCMOVT_Q */
__forceinline void AllegrexInstructionTemplate< 0xD2A08080, 0xFFF88080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVCMOVT<4>(vd(opcode), vs(opcode), uimm3(opcode));
}
/* VCMOVF_S */
__forceinline void AllegrexInstructionTemplate< 0xD2A80000, 0xFFF88080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVCMOVF<1>(vd(opcode), vs(opcode), uimm3(opcode));
}
/* VCMOVF_P */
__forceinline void AllegrexInstructionTemplate< 0xD2A80080, 0xFFF88080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVCMOVF<2>(vd(opcode), vs(opcode), uimm3(opcode));
}
/* VCMOVF_T */
__forceinline void AllegrexInstructionTemplate< 0xD2A88000, 0xFFF88080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVCMOVF<3>(vd(opcode), vs(opcode), uimm3(opcode));
}
/* VCMOVF_Q */
__forceinline void AllegrexInstructionTemplate< 0xD2A88080, 0xFFF88080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVCMOVF<4>(vd(opcode), vs(opcode), uimm3(opcode));
}
/* VWBN_S */
__forceinline void AllegrexInstructionTemplate< 0xD3000000, 0xFF008080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVWBN<1>(vd(opcode), vs(opcode), uimm8(opcode));
}
/* VPFXS */
__forceinline void AllegrexInstructionTemplate< 0xDC000000, 0xFF000000 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVPFXS(uimm24(opcode));
}
/* VPFXT */
__forceinline void AllegrexInstructionTemplate< 0xDD000000, 0xFF000000 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVPFXT(uimm24(opcode));
}
/* VPFXD */
__forceinline void AllegrexInstructionTemplate< 0xDE000000, 0xFF000000 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVPFXD(uimm24(opcode));
}
/* VIIM */
__forceinline void AllegrexInstructionTemplate< 0xDF000000, 0xFF800000 >::FastInterpret(AlContext &context, u32 opcode)
{
    COUNT_INSN; context.doVIIM(vt(opcode), uimm16(opcode));
}
/* VFIM */
__forceinline void AllegrexInstructionTemplate< 0xDF800000, 0xFF800000 >::FastInterpret(AlContext &context, u32 opcode)
{
    COUNT_INSN; context.doVFIM(vt(opcode), uimm16(opcode));
}
/* VMMUL_P */
__forceinline void AllegrexInstructionTemplate< 0xF0000080, 0xFF808080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVMMUL<2>(vd(opcode), vs(opcode), vt(opcode));
}
/* VMMUL_T */
__forceinline void AllegrexInstructionTemplate< 0xF0008000, 0xFF808080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVMMUL<3>(vd(opcode), vs(opcode), vt(opcode));
}
/* VMMUL_Q */
__forceinline void AllegrexInstructionTemplate< 0xF0008080, 0xFF808080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVMMUL<4>(vd(opcode), vs(opcode), vt(opcode));
}
/* VHTFM2_P */
__forceinline void AllegrexInstructionTemplate< 0xF0800000, 0xFF808080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVHTFM2<1>(vd(opcode), vs(opcode), vt(opcode));
}
/* VTFM2_P */
__forceinline void AllegrexInstructionTemplate< 0xF0800080, 0xFF808080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVTFM2<2>(vd(opcode), vs(opcode), vt(opcode));
}
/* VHTFM3_T */
__forceinline void AllegrexInstructionTemplate< 0xF1000080, 0xFF808080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVHTFM3<2>(vd(opcode), vs(opcode), vt(opcode));
}
/* VTFM3_T */
__forceinline void AllegrexInstructionTemplate< 0xF1008000, 0xFF808080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVTFM3<3>(vd(opcode), vs(opcode), vt(opcode));
}
/* VHTFM4_Q */
__forceinline void AllegrexInstructionTemplate< 0xF1808000, 0xFF808080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVHTFM4<3>(vd(opcode), vs(opcode), vt(opcode));
}
/* VTFM4_Q */
__forceinline void AllegrexInstructionTemplate< 0xF1808080, 0xFF808080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVTFM4<4>(vd(opcode), vs(opcode), vt(opcode));
}
/* VMSCL_P */
__forceinline void AllegrexInstructionTemplate< 0xF2000080, 0xFF808080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVMSCL<2>(vd(opcode), vs(opcode), vt(opcode));
}
/* VMSCL_T */
__forceinline void AllegrexInstructionTemplate< 0xF2008000, 0xFF808080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVMSCL<3>(vd(opcode), vs(opcode), vt(opcode));
}
/* VMSCL_Q */
__forceinline void AllegrexInstructionTemplate< 0xF2008080, 0xFF808080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVMSCL<4>(vd(opcode), vs(opcode), vt(opcode));
}
/* VCRSP_T */
__forceinline void AllegrexInstructionTemplate< 0xF2808000, 0xFF808080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVCRSP<3>(vd(opcode), vs(opcode), vt(opcode));
}
/* VQMUL_Q */
__forceinline void AllegrexInstructionTemplate< 0xF2808080, 0xFF808080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVQMUL<4>(vd(opcode), vs(opcode), vt(opcode));
}
/* VMMOV_P */
__forceinline void AllegrexInstructionTemplate< 0xF3800080, 0xFFFF8080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVMMOV<2>(vd(opcode), vs(opcode));
}
/* VMMOV_T */
__forceinline void AllegrexInstructionTemplate< 0xF3808000, 0xFFFF8080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVMMOV<3>(vd(opcode), vs(opcode));
}
/* VMMOV_Q */
__forceinline void AllegrexInstructionTemplate< 0xF3808080, 0xFFFF8080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVMMOV<4>(vd(opcode), vs(opcode));
}
/* VMIDT_P */
__forceinline void AllegrexInstructionTemplate< 0xF3830080, 0xFFFF8F80 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVMIDT<2>(vd(opcode));
}
/* VMIDT_T */
__forceinline void AllegrexInstructionTemplate< 0xF3838000, 0xFFFF8F80 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVMIDT<3>(vd(opcode));
}
/* VMIDT_Q */
__forceinline void AllegrexInstructionTemplate< 0xF3838080, 0xFFFF8F80 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVMIDT<4>(vd(opcode));
}
/* VMZERO_P */
__forceinline void AllegrexInstructionTemplate< 0xF3860080, 0xFFFF8F80 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVMZERO<2>(vd(opcode));
}
/* VMZERO_T */
__forceinline void AllegrexInstructionTemplate< 0xF3868000, 0xFFFF8F80 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVMZERO<3>(vd(opcode));
}
/* VMZERO_Q */
__forceinline void AllegrexInstructionTemplate< 0xF3868080, 0xFFFF8F80 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVMZERO<4>(vd(opcode));
}
/* VMONE_P */
__forceinline void AllegrexInstructionTemplate< 0xF3870080, 0xFFFF8F80 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVMONE<2>(vd(opcode));
}
/* VMONE_T */
__forceinline void AllegrexInstructionTemplate< 0xF3878000, 0xFFFF8F80 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVMONE<3>(vd(opcode));
}
/* VMONE_Q */
__forceinline void AllegrexInstructionTemplate< 0xF3878080, 0xFFFF8F80 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVMONE<4>(vd(opcode));
}
/* VROT_P */
__forceinline void AllegrexInstructionTemplate< 0xF3A00080, 0xFFE08080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVROT<2>(vd(opcode), vs(opcode), uimm5(opcode));
}
/* VROT_T */
__forceinline void AllegrexInstructionTemplate< 0xF3A08000, 0xFFE08080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVROT<3>(vd(opcode), vs(opcode), uimm5(opcode));
}
/* VROT_Q */
__forceinline void AllegrexInstructionTemplate< 0xF3A08080, 0xFFE08080 >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doVROT<4>(vd(opcode), vs(opcode), uimm5(opcode));
}
/* VNOP */
__forceinline void AllegrexInstructionTemplate< 0xFFFF0000, 0xFFFFFFFF >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doUNK("Unimplemented vnop instruction");
}
/* VFLUSH */
__forceinline void AllegrexInstructionTemplate< 0xFFFF040D, 0xFFFFFFFF >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doUNK("Unimplemented vflush instruction");
}
/* VSYNC */
__forceinline void AllegrexInstructionTemplate< 0xFFFF0320, 0xFFFFFFFF >::FastInterpret(AlContext &context, u32 opcode)
{
	COUNT_INSN; context.doUNK("Unimplemented vsync instruction");
}
