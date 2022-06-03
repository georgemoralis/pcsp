/*
 *  03/06/2022 - synced with jpcsp 31/05/2022 - 9084111 (jpcsp.allegrex.Common.java) - Far from complete 
 */
#pragma once
#include "..\PCSPCommon.h"

namespace Allegrex {
/*TODO*/  // public class Common {
/*TODO*/  //
/*TODO*/  //    public static abstract class Instruction {
/*TODO*/  //    	protected static Logger log = Emulator.log;
/*TODO*/  //    	protected static Logger logCop0 = Logger.getLogger("cop0");
/*TODO*/  //    	protected static Logger logCache = Logger.getLogger("cache");
/*TODO*/  //        private int m_count = 0;
/*TODO*/  //        private int flags = 0;
/*TODO*/  //        public final static int FLAG_INTERPRETED = (1 << 0);
/*TODO*/  //        public final static int FLAG_CANNOT_BE_SPLIT = (1 << 1);
/*TODO*/  //        public final static int FLAG_HAS_DELAY_SLOT = (1 << 2);
/*TODO*/  //        public final static int FLAG_IS_BRANCHING = (1 << 3);
/*TODO*/  //        public final static int FLAG_IS_JUMPING = (1 << 4);
/*TODO*/  //        public final static int FLAG_IS_CONDITIONAL = (1 << 5);
/*TODO*/  //        public final static int FLAG_STARTS_NEW_BLOCK = (1 << 6);
/*TODO*/  //        public final static int FLAG_ENDS_BLOCK = (1 << 7);
/*TODO*/  //        public final static int FLAG_USES_VFPU_PFXS = (1 << 8);
/*TODO*/  //        public final static int FLAG_USES_VFPU_PFXT = (1 << 9);
/*TODO*/  //        public final static int FLAG_USES_VFPU_PFXD = (1 << 10);
/*TODO*/  //        public final static int FLAG_CONSUMES_VFPU_PFXT = (1 << 11);
/*TODO*/  //        public final static int FLAG_COMPILED_PFX = (1 << 12);
/*TODO*/  //        public final static int FLAG_WRITES_RT = (1 << 13);
/*TODO*/  //        public final static int FLAG_WRITES_RD = (1 << 14);
/*TODO*/  //        public final static int FLAG_SYSCALL = (1 << 15);
/*TODO*/  //        public final static int FLAG_MODIFIES_INTERRUPT_STATE = (1 << 16);
/*TODO*/  //        public final static int FLAG_TRIGGERS_EXCEPTION = (1 << 17);
/*TODO*/  //        public final static int FLAGS_BRANCH_INSTRUCTION = FLAG_CANNOT_BE_SPLIT | FLAG_HAS_DELAY_SLOT |
          //        FLAG_IS_BRANCHING | FLAG_IS_CONDITIONAL;
/*TODO*/  //        public final static int FLAGS_LINK_INSTRUCTION = FLAG_HAS_DELAY_SLOT | FLAG_STARTS_NEW_BLOCK;
/*TODO*/  //
/*TODO*/  //        public abstract void interpret(Processor processor, int insn);
/*TODO*/  //
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            flags |= FLAG_INTERPRETED;
/*TODO*/  //            context.compileInterpreterInstruction();
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        public abstract String disasm(int address, int insn);
/*TODO*/  //
/*TODO*/  //        public abstract String name();
/*TODO*/  //
/*TODO*/  //        public abstract String category();
/*TODO*/  //
/*TODO*/  //        public void resetCount() {
/*TODO*/  //            m_count = 0;
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        public void increaseCount() {
/*TODO*/  //            m_count++;
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        public int getCount() {
/*TODO*/  //            return m_count;
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        public int count() {
/*TODO*/  //            return m_count;
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        public Instruction instance(int insn) {
/*TODO*/  //            return this;
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        private void setInstance(int index) {
/*TODO*/  //            m_instances[index] = this;
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        public Instruction(int index) {
/*TODO*/  //            setInstance(index);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        public Instruction(int index, int flags) {
/*TODO*/  //            setInstance(index);
/*TODO*/  //            this.flags = flags;
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        public Instruction() {
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        public int getFlags() {
/*TODO*/  //            return flags;
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        public boolean hasFlags(int testFlags) {
/*TODO*/  //            return (flags & testFlags) == testFlags;
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        public boolean hasOneFlag(int testFlags) {
/*TODO*/  //            return (flags & testFlags) != 0;
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        private void appendFlagString(StringBuilder result, String flagString) {
/*TODO*/  //            if (result.length() > 0) {
/*TODO*/  //                result.append(" | ");
/*TODO*/  //            }
/*TODO*/  //            result.append(flagString);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        private String flagsToString() {
/*TODO*/  //            StringBuilder result = new StringBuilder();
/*TODO*/  //            if (hasFlags(FLAG_INTERPRETED)) {
/*TODO*/  //                appendFlagString(result, "FLAG_INTERPRETED");
/*TODO*/  //            }
/*TODO*/  //            if (hasFlags(FLAG_CANNOT_BE_SPLIT)) {
/*TODO*/  //                appendFlagString(result, "FLAG_CANNOT_BE_SPLIT");
/*TODO*/  //            }
/*TODO*/  //            if (hasFlags(FLAG_HAS_DELAY_SLOT)) {
/*TODO*/  //                appendFlagString(result, "FLAG_HAS_DELAY_SLOT");
/*TODO*/  //            }
/*TODO*/  //            if (hasFlags(FLAG_IS_BRANCHING)) {
/*TODO*/  //                appendFlagString(result, "FLAG_IS_BRANCHING");
/*TODO*/  //            }
/*TODO*/  //            if (hasFlags(FLAG_IS_JUMPING)) {
/*TODO*/  //                appendFlagString(result, "FLAG_IS_JUMPING");
/*TODO*/  //            }
/*TODO*/  //            if (hasFlags(FLAG_IS_CONDITIONAL)) {
/*TODO*/  //                appendFlagString(result, "FLAG_IS_CONDITIONAL");
/*TODO*/  //            }
/*TODO*/  //            if (hasFlags(FLAG_STARTS_NEW_BLOCK)) {
/*TODO*/  //                appendFlagString(result, "FLAG_STARTS_NEW_BLOCK");
/*TODO*/  //            }
/*TODO*/  //            if (hasFlags(FLAG_ENDS_BLOCK)) {
/*TODO*/  //                appendFlagString(result, "FLAG_ENDS_BLOCK");
/*TODO*/  //            }
/*TODO*/  //
/*TODO*/  //            return result.toString();
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String toString() {
/*TODO*/  //            return name() + "(" + flagsToString() + ")";
/*TODO*/  //        }
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public static abstract class STUB extends Instruction {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            instance(insn).interpret(processor, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            instance(insn).compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            return instance(insn).disasm(address, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public abstract Instruction instance(int insn);
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return null;
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return null;
/*TODO*/  //        }
/*TODO*/  //    }
/*TODO*/  //    public static final Instruction UNK = new Instruction() {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //        	Modules.log.warn(String.format("%08X %s", processor.cpu.pc, disasm(processor.cpu.pc, insn)));
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            super.compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            return String.format("Unknown instruction %32s (0x%08X)", Utilities.integerToBin(insn), insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "UNK";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "UNK";
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //
/*TODO*/  //    public static final int _zr = 0;
/*TODO*/  //    public static final int _at = 1;
/*TODO*/  //    public static final int _v0 = 2;
/*TODO*/  //    public static final int _v1 = 3;
/*TODO*/  //    public static final int _a0 = 4;
/*TODO*/  //    public static final int _a1 = 5;
/*TODO*/  //    public static final int _a2 = 6;
/*TODO*/  //    public static final int _a3 = 7;
/*TODO*/  //    public static final int _t0 = 8;
/*TODO*/  //    public static final int _t1 = 9;
/*TODO*/  //    public static final int _t2 = 10;
/*TODO*/  //    public static final int _t3 = 11;
/*TODO*/  //    public static final int _t4 = 12;
/*TODO*/  //    public static final int _t5 = 13;
/*TODO*/  //    public static final int _t6 = 14;
/*TODO*/  //    public static final int _t7 = 15;
/*TODO*/  //    public static final int _s0 = 16;
/*TODO*/  //    public static final int _s1 = 17;
/*TODO*/  //    public static final int _s2 = 18;
/*TODO*/  //    public static final int _s3 = 19;
/*TODO*/  //    public static final int _s4 = 20;
/*TODO*/  //    public static final int _s5 = 21;
/*TODO*/  //    public static final int _s6 = 22;
/*TODO*/  //    public static final int _s7 = 23;
/*TODO*/  //    public static final int _t8 = 24;
/*TODO*/  //    public static final int _t9 = 25;
/*TODO*/  //    public static final int _k0 = 26;
/*TODO*/  //    public static final int _k1 = 27;
/*TODO*/  //    public static final int _gp = 28;
/*TODO*/  //    public static final int _sp = 29;
/*TODO*/  //    public static final int _fp = 30;
/*TODO*/  //    public static final int _ra = 31;
/*TODO*/  //    public static final int _f0 = 0;
/*TODO*/  //    public static final int _f12 = 12;
/*TODO*/  //    public static final int _f31 = 31;
/*TODO*/  //
char const* gprNames[32] = {"$zr", "$at", "$v0", "$v1", "$a0", "$a1", "$a2", "$a3", "$t0", "$t1", "$t2",
                            "$t3", "$t4", "$t5", "$t6", "$t7", "$s0", "$s1", "$s2", "$s3", "$s4", "$s5",
                            "$s6", "$s7", "$t8", "$t9", "$k0", "$k1", "$gp", "$sp", "$fp", "$ra"};

/*TODO*/  //    public static String[] fprNames = {
/*TODO*/  //        "$f0", "$f1", "$f2", "$f3", "$f4", "$f5", "$f6", "$f7",
/*TODO*/  //        "$f8", "$f9", "$f10", "$f11", "$f12", "$f13", "$f14", "$f15",
/*TODO*/  //        "$f16", "$f17", "$f18", "$f19", "$f20", "$f21", "$f22", "$f23",
/*TODO*/  //        "$f24", "$f25", "$f26", "$f27", "$f28", "$f29", "$f30", "$f31"
/*TODO*/  //    };
/*TODO*/  //    public static String[][] vprNames = {
/*TODO*/  //        {
/*TODO*/  //            "S000.s", "S010.s", "S020.s", "S030.s",
/*TODO*/  //            "S100.s", "S110.s", "S120.s", "S130.s",
/*TODO*/  //            "S200.s", "S210.s", "S220.s", "S230.s",
/*TODO*/  //            "S300.s", "S310.s", "S320.s", "S330.s",
/*TODO*/  //            "S400.s", "S410.s", "S420.s", "S430.s",
/*TODO*/  //            "S500.s", "S510.s", "S520.s", "S530.s",
/*TODO*/  //            "S600.s", "S610.s", "S620.s", "S630.s",
/*TODO*/  //            "S700.s", "S710.s", "S720.s", "S730.s",
/*TODO*/  //            "S001.s", "S011.s", "S021.s", "S031.s",
/*TODO*/  //            "S101.s", "S111.s", "S121.s", "S131.s",
/*TODO*/  //            "S201.s", "S211.s", "S221.s", "S231.s",
/*TODO*/  //            "S301.s", "S311.s", "S321.s", "S331.s",
/*TODO*/  //            "S401.s", "S411.s", "S421.s", "S431.s",
/*TODO*/  //            "S501.s", "S511.s", "S521.s", "S531.s",
/*TODO*/  //            "S601.s", "S611.s", "S621.s", "S631.s",
/*TODO*/  //            "S701.s", "S711.s", "S721.s", "S731.s",
/*TODO*/  //            "S002.s", "S012.s", "S022.s", "S032.s",
/*TODO*/  //            "S102.s", "S112.s", "S122.s", "S132.s",
/*TODO*/  //            "S202.s", "S212.s", "S222.s", "S232.s",
/*TODO*/  //            "S302.s", "S312.s", "S322.s", "S332.s",
/*TODO*/  //            "S402.s", "S412.s", "S422.s", "S432.s",
/*TODO*/  //            "S502.s", "S512.s", "S522.s", "S532.s",
/*TODO*/  //            "S602.s", "S612.s", "S622.s", "S632.s",
/*TODO*/  //            "S702.s", "S712.s", "S722.s", "S732.s",
/*TODO*/  //            "S003.s", "S013.s", "S023.s", "S033.s",
/*TODO*/  //            "S103.s", "S113.s", "S123.s", "S133.s",
/*TODO*/  //            "S203.s", "S213.s", "S223.s", "S233.s",
/*TODO*/  //            "S303.s", "S313.s", "S323.s", "S333.s",
/*TODO*/  //            "S403.s", "S413.s", "S423.s", "S433.s",
/*TODO*/  //            "S503.s", "S513.s", "S523.s", "S533.s",
/*TODO*/  //            "S603.s", "S613.s", "S623.s", "S633.s",
/*TODO*/  //            "S703.s", "S713.s", "S723.s", "S733.s"
/*TODO*/  //        },
/*TODO*/  //        {
/*TODO*/  //            "C000.p", "C010.p", "C020.p", "C030.p",
/*TODO*/  //            "C100.p", "C110.p", "C120.p", "C130.p",
/*TODO*/  //            "C200.p", "C210.p", "C220.p", "C230.p",
/*TODO*/  //            "C300.p", "C310.p", "C320.p", "C330.p",
/*TODO*/  //            "C400.p", "C410.p", "C420.p", "C430.p",
/*TODO*/  //            "C500.p", "C510.p", "C520.p", "C530.p",
/*TODO*/  //            "C600.p", "C610.p", "C620.p", "C630.p",
/*TODO*/  //            "C700.p", "C710.p", "C720.p", "C730.p",
/*TODO*/  //            "R000.p", "R001.p", "R002.p", "R003.p",
/*TODO*/  //            "R100.p", "R101.p", "R102.p", "R103.p",
/*TODO*/  //            "R200.p", "R201.p", "R202.p", "R203.p",
/*TODO*/  //            "R300.p", "R301.p", "R302.p", "R303.p",
/*TODO*/  //            "R400.p", "R401.p", "R402.p", "R403.p",
/*TODO*/  //            "R500.p", "R501.p", "R502.p", "R503.p",
/*TODO*/  //            "R600.p", "R601.p", "R602.p", "R603.p",
/*TODO*/  //            "R700.p", "R701.p", "R702.p", "R703.p",
/*TODO*/  //            "C002.p", "C012.p", "C022.p", "C032.p",
/*TODO*/  //            "C102.p", "C112.p", "C122.p", "C132.p",
/*TODO*/  //            "C202.p", "C212.p", "C222.p", "C232.p",
/*TODO*/  //            "C302.p", "C312.p", "C322.p", "C332.p",
/*TODO*/  //            "C402.p", "C412.p", "C422.p", "C432.p",
/*TODO*/  //            "C502.p", "C512.p", "C522.p", "C532.p",
/*TODO*/  //            "C602.p", "C612.p", "C622.p", "C632.p",
/*TODO*/  //            "C702.p", "C712.p", "C722.p", "C732.p",
/*TODO*/  //            "R020.p", "R021.p", "R022.p", "R023.p",
/*TODO*/  //            "R120.p", "R121.p", "R122.p", "R123.p",
/*TODO*/  //            "R220.p", "R221.p", "R222.p", "R223.p",
/*TODO*/  //            "R320.p", "R321.p", "R322.p", "R323.p",
/*TODO*/  //            "R420.p", "R421.p", "R422.p", "R423.p",
/*TODO*/  //            "R520.p", "R521.p", "R522.p", "R523.p",
/*TODO*/  //            "R620.p", "R621.p", "R622.p", "R623.p",
/*TODO*/  //            "R720.p", "R721.p", "R722.p", "R723.p"
/*TODO*/  //        },
/*TODO*/  //        {
/*TODO*/  //            "C000.t", "C010.t", "C020.t", "C030.t",
/*TODO*/  //            "C100.t", "C110.t", "C120.t", "C130.t",
/*TODO*/  //            "C200.t", "C210.t", "C220.t", "C230.t",
/*TODO*/  //            "C300.t", "C310.t", "C320.t", "C330.t",
/*TODO*/  //            "C400.t", "C410.t", "C420.t", "C430.t",
/*TODO*/  //            "C500.t", "C510.t", "C520.t", "C530.t",
/*TODO*/  //            "C600.t", "C610.t", "C620.t", "C630.t",
/*TODO*/  //            "C700.t", "C710.t", "C720.t", "C730.t",
/*TODO*/  //            "R000.t", "R001.t", "R002.t", "R003.t",
/*TODO*/  //            "R100.t", "R101.t", "R102.t", "R103.t",
/*TODO*/  //            "R200.t", "R201.t", "R202.t", "R203.t",
/*TODO*/  //            "R300.t", "R301.t", "R302.t", "R303.t",
/*TODO*/  //            "R400.t", "R401.t", "R402.t", "R403.t",
/*TODO*/  //            "R500.t", "R501.t", "R502.t", "R503.t",
/*TODO*/  //            "R600.t", "R601.t", "R602.t", "R603.t",
/*TODO*/  //            "R700.t", "R701.t", "R702.t", "R703.t",
/*TODO*/  //            "C001.t", "C011.t", "C021.t", "C031.t",
/*TODO*/  //            "C101.t", "C111.t", "C121.t", "C131.t",
/*TODO*/  //            "C201.t", "C211.t", "C221.t", "C231.t",
/*TODO*/  //            "C301.t", "C311.t", "C321.t", "C331.t",
/*TODO*/  //            "C401.t", "C411.t", "C421.t", "C431.t",
/*TODO*/  //            "C501.t", "C511.t", "C521.t", "C531.t",
/*TODO*/  //            "C601.t", "C611.t", "C621.t", "C631.t",
/*TODO*/  //            "C701.t", "C711.t", "C721.t", "C731.t",
/*TODO*/  //            "R010.t", "R011.t", "R012.t", "R013.t",
/*TODO*/  //            "R110.t", "R111.t", "R112.t", "R113.t",
/*TODO*/  //            "R210.t", "R211.t", "R212.t", "R213.t",
/*TODO*/  //            "R310.t", "R311.t", "R312.t", "R313.t",
/*TODO*/  //            "R410.t", "R411.t", "R412.t", "R413.t",
/*TODO*/  //            "R510.t", "R511.t", "R512.t", "R513.t",
/*TODO*/  //            "R610.t", "R611.t", "R612.t", "R613.t",
/*TODO*/  //            "R710.t", "R711.t", "R712.t", "R713.t"
/*TODO*/  //        }, {
/*TODO*/  //            "C000.q", "C010.q", "C020.q", "C030.q",
/*TODO*/  //            "C100.q", "C110.q", "C120.q", "C130.q",
/*TODO*/  //            "C200.q", "C210.q", "C220.q", "C230.q",
/*TODO*/  //            "C300.q", "C310.q", "C320.q", "C330.q",
/*TODO*/  //            "C400.q", "C410.q", "C420.q", "C430.q",
/*TODO*/  //            "C500.q", "C510.q", "C520.q", "C530.q",
/*TODO*/  //            "C600.q", "C610.q", "C620.q", "C630.q",
/*TODO*/  //            "C700.q", "C710.q", "C720.q", "C730.q",
/*TODO*/  //            "R000.q", "R001.q", "R002.q", "R003.q",
/*TODO*/  //            "R100.q", "R101.q", "R102.q", "R103.q",
/*TODO*/  //            "R200.q", "R201.q", "R202.q", "R203.q",
/*TODO*/  //            "R300.q", "R301.q", "R302.q", "R303.q",
/*TODO*/  //            "R400.q", "R401.q", "R402.q", "R403.q",
/*TODO*/  //            "R500.q", "R501.q", "R502.q", "R503.q",
/*TODO*/  //            "R600.q", "R601.q", "R602.q", "R603.q",
/*TODO*/  //            "R700.q", "R701.q", "R702.q", "R703.q",
/*TODO*/  //            "C002.q", "C012.q", "C022.q", "C032.q",
/*TODO*/  //            "C102.q", "C112.q", "C122.q", "C132.q",
/*TODO*/  //            "C202.q", "C212.q", "C222.q", "C232.q",
/*TODO*/  //            "C302.q", "C312.q", "C322.q", "C332.q",
/*TODO*/  //            "C402.q", "C412.q", "C422.q", "C432.q",
/*TODO*/  //            "C502.q", "C512.q", "C522.q", "C532.q",
/*TODO*/  //            "C602.q", "C612.q", "C622.q", "C632.q",
/*TODO*/  //            "C702.q", "C712.q", "C722.q", "C732.q",
/*TODO*/  //            "R020.q", "R021.q", "R022.q", "R023.q",
/*TODO*/  //            "R120.q", "R121.q", "R122.q", "R123.q",
/*TODO*/  //            "R220.q", "R221.q", "R222.q", "R223.q",
/*TODO*/  //            "R320.q", "R321.q", "R322.q", "R323.q",
/*TODO*/  //            "R420.q", "R421.q", "R422.q", "R423.q",
/*TODO*/  //            "R520.q", "R521.q", "R522.q", "R523.q",
/*TODO*/  //            "R620.q", "R621.q", "R622.q", "R623.q",
/*TODO*/  //            "R720.q", "R721.q", "R722.q", "R723.q"
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static String[][] vprMatNames = {
/*TODO*/  //        {},
/*TODO*/  //        {
/*TODO*/  //            "M000.p", "", "M020.p", "",
/*TODO*/  //            "M100.p", "", "M120.p", "",
/*TODO*/  //            "M200.p", "", "M220.p", "",
/*TODO*/  //            "M300.p", "", "M320.p", "",
/*TODO*/  //            "M400.p", "", "M420.p", "",
/*TODO*/  //            "M500.p", "", "M520.p", "",
/*TODO*/  //            "M600.p", "", "M620.p", "",
/*TODO*/  //            "M700.p", "", "M720.p", "",
/*TODO*/  //            "E000.p", "", "E002.p", "",
/*TODO*/  //            "E100.p", "", "E102.p", "",
/*TODO*/  //            "E200.p", "", "E202.p", "",
/*TODO*/  //            "E300.p", "", "E302.p", "",
/*TODO*/  //            "E400.p", "", "E402.p", "",
/*TODO*/  //            "E500.p", "", "E502.p", "",
/*TODO*/  //            "E600.p", "", "E602.p", "",
/*TODO*/  //            "E700.p", "", "E702.p", "",
/*TODO*/  //            "M002.p", "", "M022.p", "",
/*TODO*/  //            "M102.p", "", "M122.p", "",
/*TODO*/  //            "M202.p", "", "M222.p", "",
/*TODO*/  //            "M302.p", "", "M322.p", "",
/*TODO*/  //            "M402.p", "", "M422.p", "",
/*TODO*/  //            "M502.p", "", "M522.p", "",
/*TODO*/  //            "M602.p", "", "M622.p", "",
/*TODO*/  //            "M702.p", "", "M722.p", "",
/*TODO*/  //            "E020.p", "", "E022.p", "",
/*TODO*/  //            "E120.p", "", "E122.p", "",
/*TODO*/  //            "E220.p", "", "E222.p", "",
/*TODO*/  //            "E320.p", "", "E322.p", "",
/*TODO*/  //            "E420.p", "", "E422.p", "",
/*TODO*/  //            "E520.p", "", "E522.p", "",
/*TODO*/  //            "E620.p", "", "E622.p", "",
/*TODO*/  //            "E720.p", "", "E722.p", ""
/*TODO*/  //        },
/*TODO*/  //        {
/*TODO*/  //            "M000.t", "M010.t", "", "",
/*TODO*/  //            "M100.t", "M110.t", "", "",
/*TODO*/  //            "M200.t", "M210.t", "", "",
/*TODO*/  //            "M300.t", "M310.t", "", "",
/*TODO*/  //            "M400.t", "M410.t", "", "",
/*TODO*/  //            "M500.t", "M510.t", "", "",
/*TODO*/  //            "M600.t", "M610.t", "", "",
/*TODO*/  //            "M700.t", "M710.t", "", "",
/*TODO*/  //            "E000.t", "E001.t", "", "",
/*TODO*/  //            "E100.t", "E101.t", "", "",
/*TODO*/  //            "E200.t", "E201.t", "", "",
/*TODO*/  //            "E300.t", "E301.t", "", "",
/*TODO*/  //            "E400.t", "E401.t", "", "",
/*TODO*/  //            "E500.t", "E501.t", "", "",
/*TODO*/  //            "E600.t", "E601.t", "", "",
/*TODO*/  //            "E700.t", "E701.t", "", "",
/*TODO*/  //            "M001.t", "M011.t", "", "",
/*TODO*/  //            "M101.t", "M111.t", "", "",
/*TODO*/  //            "M201.t", "M211.t", "", "",
/*TODO*/  //            "M301.t", "M311.t", "", "",
/*TODO*/  //            "M401.t", "M411.t", "", "",
/*TODO*/  //            "M501.t", "M511.t", "", "",
/*TODO*/  //            "M601.t", "M611.t", "", "",
/*TODO*/  //            "M701.t", "M711.t", "", "",
/*TODO*/  //            "E010.t", "E011.t", "", "",
/*TODO*/  //            "E110.t", "E111.t", "", "",
/*TODO*/  //            "E210.t", "E211.t", "", "",
/*TODO*/  //            "E310.t", "E311.t", "", "",
/*TODO*/  //            "E410.t", "E411.t", "", "",
/*TODO*/  //            "E510.t", "E511.t", "", "",
/*TODO*/  //            "E610.t", "E611.t", "", "",
/*TODO*/  //            "E710.t", "E711.t", "", ""
/*TODO*/  //        }, {
/*TODO*/  //            "M000.q", "M010.q", "M020.q", "M030.q",
/*TODO*/  //            "M100.q", "M110.q", "M120.q", "M130.q",
/*TODO*/  //            "M200.q", "M210.q", "M220.q", "M230.q",
/*TODO*/  //            "M300.q", "M310.q", "M320.q", "M330.q",
/*TODO*/  //            "M400.q", "M410.q", "M420.q", "M430.q",
/*TODO*/  //            "M500.q", "M510.q", "M520.q", "M530.q",
/*TODO*/  //            "M600.q", "M610.q", "M620.q", "M630.q",
/*TODO*/  //            "M700.q", "M710.q", "M720.q", "M730.q",
/*TODO*/  //            "E000.q", "E001.q", "E002.q", "E003.q",
/*TODO*/  //            "E100.q", "E101.q", "E102.q", "E103.q",
/*TODO*/  //            "E200.q", "E201.q", "E202.q", "E203.q",
/*TODO*/  //            "E300.q", "E301.q", "E302.q", "E303.q",
/*TODO*/  //            "E400.q", "E401.q", "E402.q", "E403.q",
/*TODO*/  //            "E500.q", "E501.q", "E502.q", "E503.q",
/*TODO*/  //            "E600.q", "E601.q", "E602.q", "E603.q",
/*TODO*/  //            "E700.q", "E701.q", "E702.q", "E703.q",
/*TODO*/  //            "M002.q", "M012.q", "M022.q", "M032.q",
/*TODO*/  //            "M102.q", "M112.q", "M122.q", "M132.q",
/*TODO*/  //            "M202.q", "M212.q", "M222.q", "M232.q",
/*TODO*/  //            "M302.q", "M312.q", "M322.q", "M332.q",
/*TODO*/  //            "M402.q", "M412.q", "M422.q", "M432.q",
/*TODO*/  //            "M502.q", "M512.q", "M522.q", "M532.q",
/*TODO*/  //            "M602.q", "M612.q", "M622.q", "M632.q",
/*TODO*/  //            "M702.q", "M712.q", "M722.q", "M732.q",
/*TODO*/  //            "E020.q", "E021.q", "E022.q", "E023.q",
/*TODO*/  //            "E120.q", "E121.q", "E122.q", "E123.q",
/*TODO*/  //            "E220.q", "E221.q", "E222.q", "E223.q",
/*TODO*/  //            "E320.q", "E321.q", "E322.q", "E323.q",
/*TODO*/  //            "E420.q", "E421.q", "E422.q", "E423.q",
/*TODO*/  //            "E520.q", "E521.q", "E522.q", "E523.q",
/*TODO*/  //            "E620.q", "E621.q", "E622.q", "E623.q",
/*TODO*/  //            "E720.q", "E721.q", "E722.q", "E723.q"
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    private static final String vfpuConstants[] = {
/*TODO*/  //        "", "VFPU_HUGE", "VFPU_SQRT2", "VFPU_SQRT1_2",
/*TODO*/  //        "VFPU_2_SQRTPI", "VFPU_2_PI", "VFPU_1_PI", "VFPU_PI_4",
/*TODO*/  //        "VFPU_PI_2", "VFPU_PI", "VFPU_E", "VFPU_LOG2E",
/*TODO*/  //        "VFPU_LOG10E", "VFPU_LN2", "VFPU_LN10", "VFPU_2PI",
/*TODO*/  //        "VFPU_PI_6", "VFPU_LOG10TWO", "VFPU_LOG2TEN", "VFPU_SQRT3_2", "", "",
/*TODO*/  //        "", "", "", "", "", "", "", "", "", ""
/*TODO*/  //    };
/*TODO*/  //    public static String[] fcrNames = {
/*TODO*/  //        "$fcsr0", "$fcsr1", "$fcsr2", "$fcsr3", "$fcsr4", "$fcsr5", "$fcsr6", "$fcsr7",
/*TODO*/  //        "$fcsr8", "$fcsr9", "$fcsr10", "$fcsr11", "$fcsr12", "$fcsr13", "$fcsr14", "$fcsr15",
/*TODO*/  //        "$fcsr16", "$fcsr17", "$fcsr18", "$fcsr19", "$fcsr20", "$fcsr21", "$fcsr22", "$fcsr23",
/*TODO*/  //        "$fcsr24", "$fcsr25", "$fcsr26", "$fcsr27", "$fcsr28", "$fcsr29", "$fcsr30", "$fcsr31"
/*TODO*/  //    };
/*TODO*/  //    public static String[] cop0Names = {
/*TODO*/  //        "Index", "Random", "EntryLo0", "EntryLo1", "Context", "PageMask", "Wired", "cop0reg7",
/*TODO*/  //        "BadVaddr", "Count", "EntryHi", "Compare", "Status", "Cause", "EPC", "PrID",
/*TODO*/  //        "Config", "LLAddr", "WatchLo", "WatchHi", "XContext", "SyscallCode", "CPUId", "cop0reg23",
/*TODO*/  //        "cop0reg24", "EBase", "ECC", "CacheErr", "TagLo", "TagHi", "ErrorPC", "cop0reg31"
/*TODO*/  //    };
/*TODO*/  //    public static final int COP0_CONTROL_SYSCALL_TABLE = 12;
/*TODO*/  //    public static final int COP0_STATE_COUNT = 9;
/*TODO*/  //    public static final int COP0_STATE_COMPARE = 11;
/*TODO*/  //    public static final int COP0_STATE_STATUS = 12;
/*TODO*/  //    public static final int COP0_STATE_CAUSE = 13;
/*TODO*/  //    public static final int COP0_STATE_EPC = 14;
/*TODO*/  //    public static final int COP0_STATE_CONFIG = 16;
/*TODO*/  //    public static final int COP0_STATE_SCCODE = 21;
/*TODO*/  //    public static final int COP0_STATE_CPUID = 22;
/*TODO*/  //    public static final int COP0_STATE_REG24 = 24;
/*TODO*/  //    public static final int COP0_STATE_EBASE = 25;
/*TODO*/  //    public static final int COP0_STATE_TAGLO = 28;
/*TODO*/  //    public static final int COP0_STATE_TAGHI = 29;
/*TODO*/  //    public static final int COP0_STATE_ERROR_EPC = 30;
/*TODO*/  //    public static String vsuffix[] = {
/*TODO*/  //        ".s",
/*TODO*/  //        ".p",
/*TODO*/  //        ".t",
/*TODO*/  //        ".q"
/*TODO*/  //    };
/*TODO*/  //    public static String[] vpfxNames = {
/*TODO*/  //        "x",
/*TODO*/  //        "y",
/*TODO*/  //        "z",
/*TODO*/  //        "w"
/*TODO*/  //    };
/*TODO*/  //    public static final String ccondsNames[] = {
/*TODO*/  //        "c.f.s",
/*TODO*/  //        "c.un.s",
/*TODO*/  //        "c.eq.s",
/*TODO*/  //        "c.ueq.s",
/*TODO*/  //        "c.olt.s",
/*TODO*/  //        "c.ult.s",
/*TODO*/  //        "c.ole.s",
/*TODO*/  //        "c.ule.s",
/*TODO*/  //        "c.sf.s",
/*TODO*/  //        "c.ngle.s",
/*TODO*/  //        "c.seq.s",
/*TODO*/  //        "c.ngl.s",
/*TODO*/  //        "c.lt.s",
/*TODO*/  //        "c.nge.s",
/*TODO*/  //        "c.le.s",
/*TODO*/  //        "c.ngt.s"
/*TODO*/  //    };
/*TODO*/  //    public static final String vcondNames[] = {
/*TODO*/  //        "FL",
/*TODO*/  //        "EQ",
/*TODO*/  //        "LT",
/*TODO*/  //        "LE",
/*TODO*/  //        "TR",
/*TODO*/  //        "NE",
/*TODO*/  //        "GE",
/*TODO*/  //        "GT",
/*TODO*/  //        "EZ",
/*TODO*/  //        "EN",
/*TODO*/  //        "EI",
/*TODO*/  //        "ES",
/*TODO*/  //        "NZ",
/*TODO*/  //        "NN",
/*TODO*/  //        "NI",
/*TODO*/  //        "NS"
/*TODO*/  //    };
/*TODO*/  //
/*TODO*/  //    public static String disasmRDRTSA(String opname, int rd, int rt, int sa) {
/*TODO*/  //        if ((rd == 0) && sa == 0) {
/*TODO*/  //            return "nop";
/*TODO*/  //        }
/*TODO*/  //		return String.format("%1$-10s %2$s, %3$s, 0x%4$04X", opname, gprNames[rd], gprNames[rt], sa);
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public static String disasmRDRTRS(String opname, int rd, int rt, int rs) {
/*TODO*/  //        return String.format("%1$-10s %2$s, %3$s, %4$s", opname, gprNames[rd], gprNames[rt], gprNames[rs]);
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public static String disasmRS(String opname, int rs) {
/*TODO*/  //        return String.format("%1$-10s %2$s", opname, gprNames[rs]);
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public static String disasmRT(String opname, int rt) {
/*TODO*/  //        return String.format("%1$-10s %2$s", opname, gprNames[rt]);
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public static String disasmRDRS(String opname, int rd, int rs) {
/*TODO*/  //        return String.format("%1$-10s %2$s, %3$s", opname, gprNames[rd], gprNames[rs]);
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public static String disasmRDRT(String opname, int rd, int rt) {
/*TODO*/  //        return String.format("%1$-10s %2$s, %3$s", opname, gprNames[rd], gprNames[rt]);
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public static String disasmRD(String opname, int rd) {
/*TODO*/  //        return String.format("%1$-10s %2$s", opname, gprNames[rd]);
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public static String disasmRSRT(String opname, int rs, int rt) {
/*TODO*/  //        return String.format("%1$-10s %2$s, %3$s", opname, gprNames[rs], gprNames[rt]);
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public static String disasmEXT(int rt, int rs, int lsb, int msb) {
/*TODO*/  //        return String.format("%1$-10s %2$s, %3$s, %4$d, %5$d", "ext", gprNames[rt], gprNames[rs], lsb, (msb
          //        + 1));
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public static String disasmINS(int rt, int rs, int lsb, int msb) {
/*TODO*/  //        return String.format("%1$-10s %2$s, %3$s, %4$d, %5$d", "ins", gprNames[rt], gprNames[rs], lsb, (msb
          //        - lsb + 1));
/*TODO*/  //    }
/*TODO*/  //
std::string disasmRDRSRT(std::string opname, int rd, int rs, int rt) {
    char tmp[128];
    sprintf(tmp, "%-10s %2s, %3s, %4s", opname.c_str(), gprNames[rd], gprNames[rs], gprNames[rt]);
    /*TODO*/  //        if (rs == 0 && rt == 0) {
/*TODO*/  //
/*TODO*/  //            if (opname.equals("xor") || opname.equals("nor")) {
/*TODO*/  //                return String.format("%2$s <=> li %1$s, -1", gprNames[rd], s);
/*TODO*/  //            }
/*TODO*/  //
/*TODO*/  //            return String.format("%2$s <=> li %1$s, 0", gprNames[rd], s);
/*TODO*/  //        } else if (rs == 0) {
/*TODO*/  //
/*TODO*/  //            if (opname.equals("and")) {
/*TODO*/  //                return String.format("%2$s <=> li %1$s, 0", gprNames[rd], s);
/*TODO*/  //            }
/*TODO*/  //
/*TODO*/  //            if (opname.equals("nor")) {
/*TODO*/  //                return String.format("%3$s <=> li %1$s, not %2$s", gprNames[rd], gprNames[rt], s);
/*TODO*/  //            }
/*TODO*/  //
/*TODO*/  //            if (opname.equals("sub")) {
/*TODO*/  //                return String.format("%3$s <=> neg %1$s, %2$s", gprNames[rd], gprNames[rt], s);
/*TODO*/  //            }
/*TODO*/  //
/*TODO*/  //            if (opname.equals("subu")) {
/*TODO*/  //                return String.format("%3$s <=> negu %1$s, %2$s", gprNames[rd], gprNames[rt], s);
/*TODO*/  //            }
/*TODO*/  //
/*TODO*/  //            return String.format("%3$s <=> move %1$s, %2$s", gprNames[rd], gprNames[rt], s);
/*TODO*/  //        } else if (rt == 0) {
/*TODO*/  //
/*TODO*/  //            if (opname.equals("and")) {
/*TODO*/  //                return String.format("%2$s <=> li %1$s, 0", gprNames[rd], s);
/*TODO*/  //            }
/*TODO*/  //
/*TODO*/  //            if (opname.equals("nor")) {
/*TODO*/  //                return String.format("%3$s <=> li %1$s, not %2$s", gprNames[rd], gprNames[rs], s);
/*TODO*/  //            }
/*TODO*/  //
/*TODO*/  //            return String.format("%3$s <=> move %1$s, %2$s", gprNames[rd], gprNames[rs], s);
/*TODO*/  //        }
/*TODO*/  //
    return std::string(tmp);
}
/*TODO*/  //
/*TODO*/  //    public static String disasmRSOFFSET(String opname, int rs, int simm16, int opcode_address) {
/*TODO*/  //        return String.format("%1$-10s %2$s, 0x%3$08X", opname, gprNames[rs], ((int) (short) simm16) * 4 +
          //        opcode_address + 4);
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public static String disasmRSRTOFFSET(String opname, int rs, int rt, int simm16, int opcode_address) {
/*TODO*/  //    	if (rs == rt && opname.equals("beq")) {
/*TODO*/  //    		return String.format("%1$-10s 0x%2$08X", "b", ((int) (short) simm16) * 4 +
          //    opcode_address + 4);
/*TODO*/  //    	}
/*TODO*/  //
/*TODO*/  //    	return String.format("%1$-10s %2$s, %3$s, 0x%4$08X", opname, gprNames[rs], gprNames[rt], ((int)
          //    (short) simm16) * 4 + opcode_address + 4);
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public static String disasmOFFSET(String opname, int simm16, int opcode_address) {
/*TODO*/  //        return String.format("%1$-10s 0x%2$08X", opname, ((int) (short) simm16) * 4 + opcode_address + 4);
/*TODO*/  //    }
/*TODO*/  //
static std::string disasmRTRSIMM(std::string opname, int rt, int rs, int imm16) {
    char tmp[128];
    sprintf(tmp, "%-10s %2s, %3s, %4d", opname.c_str(), gprNames[rt], gprNames[rs], ((int)(short)imm16));
    if (rs == 0) {
        char tmp2[128];
        if (opname.compare("andi") == 0) {
            sprintf(tmp2, "%2s <=> li %1s, 0", tmp, gprNames[rt]);
            return std::string(tmp2);
        } else if (opname.compare("slti") == 0) {
            sprintf(tmp2, "%3s <=> li %1s, %2d", tmp, gprNames[rt], ((0 < imm16) ? 1 : 0));
            return std::string(tmp2);
        } else if (opname.compare("addiu") == 0 || opname.compare("ori") == 0) {
            sprintf(tmp2, "%3s <=> li %1s, %2d", tmp, gprNames[rt], imm16);
            return std::string(tmp2);
        }
    }
    return std::string(tmp);
}
/*TODO*/  //
/*TODO*/  //    public static String disasmSYSCALL(Memory mem, int code) {
/*TODO*/  //    	String functionName = Utilities.getFunctionNameBySyscall(mem, code);
/*TODO*/  //
/*TODO*/  //    	if (functionName == null) {
/*TODO*/  //    		if (code == syscallUnmappedImport) {
/*TODO*/  //    			functionName = "Unmapped import";
/*TODO*/  //    		} else if (code == syscallLoadCoreUnmappedImport) {
/*TODO*/  //    			functionName = "Unmapped import from loadcore";
/*TODO*/  //    		} else {
/*TODO*/  //    			functionName = "unknown";
/*TODO*/  //    		}
/*TODO*/  //    	}
/*TODO*/  //
/*TODO*/  //        return String.format("%1$-10s 0x%2$05X [%3$s]", "syscall", code, functionName);
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public static String disasmBREAK(int code) {
/*TODO*/  //        return String.format("%1$-10s 0x%2$05X", "break", code);
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public static String disasmJUMP(String opname, int uimm26, int opcode_address) {
/*TODO*/  //        int jump = (opcode_address & 0xf0000000) | ((uimm26 & 0x3ffffff) << 2);
/*TODO*/  //
/*TODO*/  //        String disasm = String.format("%1$-10s 0x%2$08X", opname, jump);
/*TODO*/  //        // Try to find a human-readable name for the address
/*TODO*/  //        if (opname.equals("jal") || opname.equals("j")) {
/*TODO*/  //        	String functionName = Utilities.getFunctionNameByAddress(jump);
/*TODO*/  //        	if (functionName != null) {
/*TODO*/  //        		disasm += String.format(" [%s]", functionName);
/*TODO*/  //        	}
/*TODO*/  //        }
/*TODO*/  //        return disasm;
/*TODO*/  //    }
/*TODO*/  //
static std::string disasmRTIMM(std::string opname, int rt, int imm) {
    char tmp[128];
    sprintf(tmp, "%-10s %2s, 0x%04X <=> li %2s, 0x%04X0000", opname.c_str(), gprNames[rt], (imm & 0xFFFF), gprNames[rt],(imm & 0xFFFF));
    return std::string(tmp);
}
/*TODO*/  //
/*TODO*/  //    public static String disasmRTIMM7(String opname, int rt, int imm7) {
/*TODO*/  //        return String.format("%1$-10s 0x%2$02X, %3$s", opname, imm7, gprNames[rt]);
/*TODO*/  //    }
/*TODO*/  //
static std::string disasmRTIMMRS(std::string opname, int rt, int rs, int imm) {
    char tmp[128];
    sprintf(tmp, "%-10s %2s, %4d(%3s)", opname.c_str(), gprNames[rt], ((int)(short)imm), gprNames[rs]);
    return std::string(tmp);
}
/*TODO*/  //
/*TODO*/  //    public static String disasmCODEIMMRS(String opname, int code, int imm, int rs) {
/*TODO*/  //        return String.format("%1$-10s 0x%2$02X, %4$d(%3$s)", opname, code, gprNames[rs], ((int) (short)
          //        imm));
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public static String disasmFTIMMRS(String opname, int ft, int rs, int imm) {
/*TODO*/  //        return String.format("%1$-10s %2$s, %4$d(%3$s)", opname, fprNames[ft], gprNames[rs], ((int) (short)
          //        imm));
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public static String disasmFDFSFT(String opname, int fd, int fs, int ft) {
/*TODO*/  //        return String.format("%1$-10s %2$s, %3$s, %4$s", opname, fprNames[fd], fprNames[fs], fprNames[ft]);
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public static String disasmFDFS(String opname, int fd, int fs) {
/*TODO*/  //        return String.format("%1$-10s %2$s, %3$s", opname, fprNames[fd], fprNames[fs]);
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public static String disasmRTFS(String opname, int rt, int fs) {
/*TODO*/  //        return String.format("%1$-10s %2$s, %3$s", opname, gprNames[rt], fprNames[fs]);
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public static String disasmRTFC(String opname, int rt, int fc) {
/*TODO*/  //        return String.format("%1$-10s %2$s, %3$s", opname, gprNames[rt], fcrNames[fc]);
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public static String disasmRTC0dr(String opname, int rt, int c0dr) {
/*TODO*/  //        return String.format("%1$-10s %2$s, %3$s", opname, gprNames[rt], cop0Names[c0dr]);
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public static String disasmRTC0cr(String opname, int rt, int c0cr) {
/*TODO*/  //        return String.format("%1$-10s %2$s, %3$d", opname, gprNames[rt], c0cr);
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public static String disasmCcondS(int cconds, int fs, int ft) {
/*TODO*/  //        return String.format("%1$-10s %2$s, %3$s", ccondsNames[cconds], fprNames[fs], fprNames[ft]);
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public static String disasmFSFT(String opname, int fs, int ft) {
/*TODO*/  //        return String.format("%1$-10s %2$s, %3$s", opname, fprNames[fs], fprNames[ft]);
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public static String disasmVD(String opname, int vsize, int vd) {
/*TODO*/  //        return String.format("%1$-10s %2$s", opname + vsuffix[vsize - 1], vprNames[vsize - 1][vd]);
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public static String disasmVS(String opname, int vsize, int vs) {
/*TODO*/  //        return String.format("%1$-10s %2$s", opname + vsuffix[vsize - 1], vprNames[vsize - 1][vs]);
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public static String disasmVDVS(String opname, int vsize, int vd, int vs) {
/*TODO*/  //        return String.format("%1$-10s %2$s, %3$s", opname + vsuffix[vsize - 1], vprNames[vsize - 1][vd],
          //        vprNames[vsize - 1][vs]);
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public static String disasmVDVS(String opname, int vsize, int vsizeVd, int vd, int vs) {
/*TODO*/  //        return String.format("%1$-10s %2$s, %3$s", opname + vsuffix[vsize - 1], vprNames[vsizeVd - 1][vd],
          //        vprNames[vsize - 1][vs]);
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public static String disasmVDVSIMM(String opname, int vsize, int vd, int vs, int imm) {
/*TODO*/  //        return String.format("%1$-10s %2$s, %3$s, %4$d", opname + vsuffix[vsize - 1], vprNames[vsize -
          //        1][vd], vprNames[vsize - 1][vs], imm);
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public static String disasmVD1VS(String opname, int vsize, int vd, int vs) {
/*TODO*/  //        return String.format("%1$-10s %2$s, %3$s", opname + vsuffix[vsize - 1], vprNames[0][vd],
          //        vprNames[vsize - 1][vs]);
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public static String disasmVTIMMRS(String opname, int vsize, int vt, int rs, int imm) {
/*TODO*/  //        return String.format(
/*TODO*/  //                "%1$-10s %2$s, %4$d(%3$s)",
/*TODO*/  //                opname + vsuffix[vsize - 1],
/*TODO*/  //                vprNames[vsize - 1][vt],
/*TODO*/  //                gprNames[rs],
/*TODO*/  //                imm);
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public static String disasmVDVSVT(String opname, int vsize, int vd, int vs, int vt) {
/*TODO*/  //        return String.format("%1$-10s %2$s, %3$s, %4$s", opname + vsuffix[vsize - 1], vprNames[vsize -
          //        1][vd], vprNames[vsize - 1][vs], vprNames[vsize - 1][vt]);
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public static String disasmVDVSMVT(String opname, int vsize, int vd, int vs, int vt) {
/*TODO*/  //        return String.format("%1$-10s %2$s, %3$s, %4$s", opname + vsuffix[vsize - 1], vprNames[vsize -
          //        1][vd], vprMatNames[vsize - 1][vs], vprNames[vsize - 1][vt]);
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public static String disasmVDVSVT1(String opname, int vsize, int vd, int vs, int vt) {
/*TODO*/  //        return String.format("%1$-10s %2$s, %3$s, %4$s", opname + vsuffix[vsize - 1], vprNames[vsize -
          //        1][vd], vprNames[vsize - 1][vs], vprNames[0][vt]);
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public static String disasmVD1VSVT(String opname, int vsize, int vd, int vs, int vt) {
/*TODO*/  //        return String.format("%1$-10s %2$s, %3$s, %4$s", opname + vsuffix[vsize - 1], vprNames[0][vd],
          //        vprNames[vsize - 1][vs], vprNames[vsize - 1][vt]);
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public static String disasmVCMP(String opname, int vsize, int vcode, int vs, int vt) {
/*TODO*/  //        if ((vcode & ~4) == 0) {
/*TODO*/  //            return String.format("%1$-10s %2$s", opname + vsuffix[vsize - 1], vcondNames[vcode]);
/*TODO*/  //        } else if (vcode < 8) {
/*TODO*/  //            return String.format("%1$-10s %2$s, %3$s, %4$s", opname + vsuffix[vsize - 1], vcondNames[vcode],
          //            vprNames[vsize - 1][vs], vprNames[vsize - 1][vt]);
/*TODO*/  //        }
/*TODO*/  //        return String.format("%1$-10s %2$s, %3$s, %4$s", opname + vsuffix[vsize - 1], vcondNames[vcode],
          //        vprNames[vsize - 1][vs], vprNames[vsize - 1][vt]);
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public static String disasmVROT(String opname, int vsize, int vd, int vs, int vt) {
/*TODO*/  //        int i;
/*TODO*/  //        int si = (vt >>> 2) & 3;
/*TODO*/  //        int ci = (vt >>> 0) & 3;
/*TODO*/  //        String ca = " c", sa = " s";
/*TODO*/  //        String codes[] = new String[4];
/*TODO*/  //        if ((vt & 16) != 0) {
/*TODO*/  //            sa = "-s";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        if (si == ci) {
/*TODO*/  //            for (i = 0; i < vsize; ++i) {
/*TODO*/  //                codes[i] = (ci == i) ? ca : sa;
/*TODO*/  //            }
/*TODO*/  //        } else {
/*TODO*/  //            for (i = 0; i < vsize; ++i) {
/*TODO*/  //                codes[i] = (ci == i) ? ca : ((si == i) ? sa : " 0");
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        StringBuilder rot = new StringBuilder("[");
/*TODO*/  //
/*TODO*/  //        i = 0;
/*TODO*/  //        while (true) {
/*TODO*/  //            rot.append(codes[i++]);
/*TODO*/  //            if (i >= vsize) {
/*TODO*/  //                break;
/*TODO*/  //            }
/*TODO*/  //            rot.append(",");
/*TODO*/  //        }
/*TODO*/  //        rot.append("]");
/*TODO*/  //        return String.format("%1$-10s %2$s, %3$s, %4$s", opname + vsuffix[vsize - 1], vprNames[vsize -
          //        1][vd], vprNames[0][vs], rot);
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public static String disasmVDM(String opname, int vsize, int vd) {
/*TODO*/  //        return String.format("%1$-10s %2$s", opname + vsuffix[vsize - 1], vprMatNames[vsize - 1][vd]);
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public static String disasmVDMVSM(String opname, int vsize, int vd, int vs) {
/*TODO*/  //        return String.format("%1$-10s %2$s, %3$s", opname + vsuffix[vsize - 1], vprMatNames[vsize - 1][vd],
          //        vprMatNames[vsize - 1][vs]);
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public static String disasmVDCST(String opname, int vsize, int vd, int cst) {
/*TODO*/  //        return String.format("%1$-10s %2$s, %3$s", opname + vsuffix[vsize - 1], vprNames[vsize - 1][vd],
          //        vfpuConstants[cst]);
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public static String disasmVDIIM(String opcode, int vsize, int vd, int imm16) {
/*TODO*/  //        return String.format("%1$-10s %2$s, 0x%3$04X", opcode + vsuffix[vsize - 1], vprNames[0][vd], imm16);
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public static String disasmVDFIM(String opcode, int vsize, int vd, int imm16) {
/*TODO*/  //        float s = ((imm16 >> 15) == 0) ? 1.0f : -1.0f;
/*TODO*/  //        int e = ((imm16 >> 10) & 0x1f);
/*TODO*/  //        int m = (e == 0) ? ((imm16 & 0x3ff) << 1) : ((imm16 & 0x3ff) | 0x400);
/*TODO*/  //
/*TODO*/  //        float v = (e >= 15) ? (1 << (e - 15)) : 1.0f / (1 << (15 - e));
/*TODO*/  //        v = s * m * v / 1024f;
/*TODO*/  //        return String.format("%1$-10s %2$s, %3$1.8f", opcode + vsuffix[vsize - 1], vprNames[0][vd], v);
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public static String disasmVDMVSMVTM(String opname, int vsize, int vd, int vs, int vt) {
/*TODO*/  //        return String.format("%1$-10s %2$s, %3$s, %4$s", opname + vsuffix[vsize - 1], vprMatNames[vsize -
          //        1][vd], vprMatNames[vsize - 1][vs], vprMatNames[vsize - 1][vt]);
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public static String disasmVDRS(String opname, int vd, int rt) {
/*TODO*/  //        return String.format("%1$-10s %2$s, %3$s", opname + vsuffix[0], gprNames[rt], vprNames[0][vd]);
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public static String disasmVPFX(String opname, int[] swz, boolean[] abs, boolean[] cst, boolean[] neg) {
/*TODO*/  //        String[] values = new String[4];
/*TODO*/  //        for (int i = 0; i < 4; ++i) {
/*TODO*/  //            if (cst[i]) {
/*TODO*/  //                switch (swz[i]) {
/*TODO*/  //                    case 0:
/*TODO*/  //                        values[i] = abs[i] ? "3" : "0";
/*TODO*/  //                        break;
/*TODO*/  //                    case 1:
/*TODO*/  //                        values[i] = abs[i] ? "1/3" : "1";
/*TODO*/  //                        break;
/*TODO*/  //                    case 2:
/*TODO*/  //                        values[i] = abs[i] ? "1/4" : "2";
/*TODO*/  //                        break;
/*TODO*/  //                    case 3:
/*TODO*/  //                        values[i] = abs[i] ? "1/6" : "1/2";
/*TODO*/  //                        break;
/*TODO*/  //                }
/*TODO*/  //            } else {
/*TODO*/  //                values[i] = abs[i] ? "|" + vpfxNames[swz[i]] + "|"
/*TODO*/  //                        : vpfxNames[swz[i]];
/*TODO*/  //            }
/*TODO*/  //
/*TODO*/  //            if (neg[i]) {
/*TODO*/  //                values[i] = "-" + values[i];
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        return String.format("%1$-10s [%2$s, %3$s, %4$s, %5$s]", opname, values[0], values[1], values[2],
          //        values[3]);
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public static String disasmVPFXD(String opname, int[] sat, int[] msk) {
/*TODO*/  //        String[] values = new String[4];
/*TODO*/  //        for (int i = 0; i < 4; ++i) {
/*TODO*/  //            if (msk[i] == 0) {
/*TODO*/  //            	switch (sat[i]) {
/*TODO*/  //            		case 0: values[i] = vpfxNames[i]; break;
/*TODO*/  //            		case 1: values[i] = "0:1"; break;
/*TODO*/  //            		case 2: values[i] = "???"; break;
/*TODO*/  //            		case 3: values[i] = "-1:1"; break;
/*TODO*/  //            	}
/*TODO*/  //            } else {
/*TODO*/  //                values[i] = "M";
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //        return String.format("%1$-10s [%2$s, %3$s, %4$s, %5$s]", opname, values[0], values[1], values[2],
          //        values[3]);
/*TODO*/  //    }
/*TODO*/  //    public static String disasmVCCOFFSET(String opname, int vcc, int simm16, int opcode_address) {
/*TODO*/  //        return String.format("%1$-10s %2$d, 0x%3$08X", opname, vcc, ((int) (short) simm16) * 4 +
          //        opcode_address + 4);
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public static String disasmRTVME(String opname, int rt, int vme) {
/*TODO*/  //        return String.format("%1$-10s %2$s, 0x%3$04X", opname, gprNames[rt], vme);
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    protected static Instruction[] m_instances = new Instruction[254];
/*TODO*/  //
/*TODO*/  //    public static final Instruction[] instructions() {
/*TODO*/  //        return m_instances;
/*TODO*/  //    }
/*TODO*/  //}
/*TODO*/  //
}
