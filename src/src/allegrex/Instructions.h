/*
 *  07/06/2022 - synced with jpcsp 31/05/2022 - 9084111 - TODO
 */
#pragma once
#include "..\PCSPCommon.h"
#include "Common.h"
#include <bitset>
#include "Instruction.h"

namespace Allegrex {
/*TODO*/  //    public static final Instruction NOP = new Instruction(0) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "NOP";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "MIPS I";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            // Nothing to compile
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //
/*TODO*/  //            return "nop";
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction ICACHE_INDEX_INVALIDATE = new Instruction(1) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "ICACHE INDEX INVALIDATE";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "ALLEGREX";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            if (logCache.isTraceEnabled()) {
/*TODO*/  //                logCache.trace(String.format("%s 0x%08X", name(), processor.cpu.getRegister(rs) + (short)
          //                imm16));
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            super.compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmCODEIMMRS("cache", 0x04, (short) imm16, rs);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction ICACHE_INDEX_UNLOCK = new Instruction(2) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "ICACHE INDEX UNLOCK";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "ALLEGREX";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            if (logCache.isTraceEnabled()) {
/*TODO*/  //                logCache.trace(String.format("%s 0x%08X", name(), processor.cpu.getRegister(rs) + (short)
          //                imm16));
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            super.compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmCODEIMMRS("cache", 0x06, (short) imm16, rs);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction ICACHE_HIT_INVALIDATE = new Instruction(3) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "ICACHE HIT INVALIDATE";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "ALLEGREX";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            if (processor.cp0.isMainCpu()) {
/*TODO*/  //                int addr = processor.cpu.getRegister(rs) + (short) imm16;
/*TODO*/  //                int size = 64;
/*TODO*/  //                RuntimeContext.invalidateRange(addr, size);
/*TODO*/  //            }
/*TODO*/  //
/*TODO*/  //            if (logCache.isTraceEnabled()) {
/*TODO*/  //                logCache.trace(String.format("%s 0x%08X", name(), processor.cpu.getRegister(rs) + (short)
          //                imm16));
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            super.compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmCODEIMMRS("cache", 0x08, (short) imm16, rs);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction ICACHE_FILL = new Instruction(4) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "ICACHE FILL";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "ALLEGREX";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            if (logCache.isTraceEnabled()) {
/*TODO*/  //                logCache.trace(String.format("%s 0x%08X", name(), processor.cpu.getRegister(rs) + (short)
          //                imm16));
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            super.compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmCODEIMMRS("cache", 0x0A, (short) imm16, rs);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction ICACHE_FILL_WITH_LOCK = new Instruction(5) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "ICACHE FILL WITH LOCK";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "ALLEGREX";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            if (logCache.isTraceEnabled()) {
/*TODO*/  //                logCache.trace(String.format("%s 0x%08X", name(), processor.cpu.getRegister(rs) + (short)
          //                imm16));
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            super.compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmCODEIMMRS("cache", 0x0B, (short) imm16, rs);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction ICACHE = new Instruction(252) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "ICACHE";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "ALLEGREX";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //            int function = (insn >> 16) & 31;
/*TODO*/  //
/*TODO*/  //            if (processor.cp0.isMainCpu()) {
/*TODO*/  //                // The instructions icache 0x01 and icache 0x03 are used to implement
          //                sceKernelIcacheInvalidateAll().
/*TODO*/  //                // They do clear all the cache lines (16KB cache size):
/*TODO*/  //                //    icache 0x01, addr=0x0000
/*TODO*/  //                //    icache 0x03, addr=0x0000
/*TODO*/  //                //    icache 0x01, addr=0x0040
/*TODO*/  //                //    icache 0x03, addr=0x0040
/*TODO*/  //                //    icache 0x01, addr=0x0080
/*TODO*/  //                //    icache 0x03, addr=0x0080
/*TODO*/  //                //    ...
/*TODO*/  //                //    icache 0x01, addr=0x3FC0
/*TODO*/  //                //    icache 0x03, addr=0x3FC0
/*TODO*/  //                // We only react on clearing the cache line at addr=0x0000.
/*TODO*/  //                int addr = processor.cpu.getRegister(rs) + (short) imm16;
/*TODO*/  //                if (function == 0x01 && addr == 0x0000) {
/*TODO*/  //                    RuntimeContext.invalidateAll();
/*TODO*/  //                }
/*TODO*/  //            }
/*TODO*/  //
/*TODO*/  //            if (logCache.isTraceEnabled()) {
/*TODO*/  //                logCache.trace(String.format("%s 0x%08X", name(), processor.cpu.getRegister(rs) + (short)
          //                imm16));
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            super.compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //            int function = (insn >> 16) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmCODEIMMRS("icache", function, (short) imm16, rs);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction DCACHE_INDEX_WRITEBACK_INVALIDATE = new Instruction(6) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "DCACHE INDEX WRITEBACK INVALIDATE";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "ALLEGREX";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            if (logCache.isTraceEnabled()) {
/*TODO*/  //                logCache.trace(String.format("%s 0x%08X", name(), processor.cpu.getRegister(rs) + (short)
          //                imm16));
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            super.compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmCODEIMMRS("cache", 0x14, (short) imm16, rs);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction DCACHE_INDEX_UNLOCK = new Instruction(7) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "DCACHE INDEX UNLOCK";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "ALLEGREX";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            if (logCache.isTraceEnabled()) {
/*TODO*/  //                logCache.trace(String.format("%s 0x%08X", name(), processor.cpu.getRegister(rs) + (short)
          //                imm16));
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            super.compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmCODEIMMRS("cache", 0x16, (short) imm16, rs);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction DCACHE_CREATE_DIRTY_EXCLUSIVE = new Instruction(8) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "DCACHE CREATE DIRTY EXCLUSIVE";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "ALLEGREX";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            if (logCache.isTraceEnabled()) {
/*TODO*/  //                logCache.trace(String.format("%s 0x%08X", name(), processor.cpu.getRegister(rs) + (short)
          //                imm16));
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            super.compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmCODEIMMRS("cache", 0x18, (short) imm16, rs);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction DCACHE_HIT_INVALIDATE = new Instruction(9) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "DCACHE HIT INVALIDATE";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "ALLEGREX";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            if (logCache.isTraceEnabled()) {
/*TODO*/  //                logCache.trace(String.format("%s 0x%08X", name(), processor.cpu.getRegister(rs) + (short)
          //                imm16));
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            super.compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmCODEIMMRS("cache", 0x19, (short) imm16, rs);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction DCACHE_HIT_WRITEBACK = new Instruction(10) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "DCACHE HIT WRITEBACK";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "ALLEGREX";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            if (logCache.isTraceEnabled()) {
/*TODO*/  //                logCache.trace(String.format("%s 0x%08X", name(), processor.cpu.getRegister(rs) + (short)
          //                imm16));
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            super.compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmCODEIMMRS("cache", 0x1A, (short) imm16, rs);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction DCACHE_HIT_WRITEBACK_INVALIDATE = new Instruction(11) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "DCACHE HIT WRITEBACK INVALIDATE";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "ALLEGREX";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            if (processor.cp0.isMainCpu()) {
/*TODO*/  //                // This instruction is used by loadcore.prx to invalidate the cache after updating stubs for
          //                linking.
/*TODO*/  //                int addr = processor.cpu.getRegister(rs) + (short) imm16;
/*TODO*/  //                int size = 64;
/*TODO*/  //                RuntimeContext.invalidateRange(addr, size);
/*TODO*/  //            }
/*TODO*/  //
/*TODO*/  //            if (logCache.isTraceEnabled()) {
/*TODO*/  //                logCache.trace(String.format("%s 0x%08X", name(), processor.cpu.getRegister(rs) + (short)
          //                imm16));
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            super.compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmCODEIMMRS("cache", 0x1B, (short) imm16, rs);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction DCACHE_CREATE_DIRTY_EXCLUSIVE_WITH_LOCK = new Instruction(12) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "DCACHE CREATE DIRTY EXCLUSIVE WITH LOCK";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "ALLEGREX";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            if (logCache.isTraceEnabled()) {
/*TODO*/  //                logCache.trace(String.format("%s 0x%08X", name(), processor.cpu.getRegister(rs) + (short)
          //                imm16));
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            super.compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmCODEIMMRS("cache", 0x1C, (short) imm16, rs);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction DCACHE_FILL = new Instruction(13) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "DCACHE FILL";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "ALLEGREX";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            if (logCache.isTraceEnabled()) {
/*TODO*/  //                logCache.trace(String.format("%s 0x%08X", name(), processor.cpu.getRegister(rs) + (short)
          //                imm16));
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            super.compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmCODEIMMRS("cache", 0x1E, (short) imm16, rs);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction DCACHE_FILL_WITH_LOCK = new Instruction(14) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "DCACHE FILL WITH LOCK";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "ALLEGREX";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            if (logCache.isTraceEnabled()) {
/*TODO*/  //                logCache.trace(String.format("%s 0x%08X", name(), processor.cpu.getRegister(rs) + (short)
          //                imm16));
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            super.compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmCODEIMMRS("cache", 0x1F, (short) imm16, rs);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction DCACHE = new Instruction(253) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "DCACHE";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "ALLEGREX";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            if (logCache.isTraceEnabled()) {
/*TODO*/  //                logCache.trace(String.format("%s 0x%08X", name(), processor.cpu.getRegister(rs) + (short)
          //                imm16));
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            super.compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //            int function = (insn >> 16) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmCODEIMMRS("dcache", function, (short) imm16, rs);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction SYSCALL = new Instruction(15, FLAG_SYSCALL | FLAG_TRIGGERS_EXCEPTION) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "SYSCALL";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "MIPS I";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int imm20 = (insn >> 6) & 1048575;
/*TODO*/  //
/*TODO*/  //            try {
/*TODO*/  //                int continueAddress = SyscallHandler.syscall(imm20,
          //                Processor.isInstructionInDelaySlot(processor.cpu.memory, processor.cpu.pc));
/*TODO*/  //                processor.cpu.pc = continueAddress;
/*TODO*/  //            } catch (Exception e) {
/*TODO*/  //                log.error("syscall", e);
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            context.compileSyscall();
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int imm20 = (insn >> 6) & 1048575;
/*TODO*/  //
/*TODO*/  //            return Common.disasmSYSCALL(Emulator.getMemory(address), imm20);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction ERET = new Instruction(16, FLAG_CANNOT_BE_SPLIT | FLAG_ENDS_BLOCK |
          //    FLAG_MODIFIES_INTERRUPT_STATE) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "ERET";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "MIPS III";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            processor.cpu.pc = processor.cpu.doERET(processor);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            super.compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //
/*TODO*/  //            return "eret";
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction BREAK = new Instruction(17, FLAG_TRIGGERS_EXCEPTION | FLAG_ENDS_BLOCK) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "BREAK";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "MIPS I";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int imm20 = (insn >> 6) & 1048575;
/*TODO*/  //            if (RuntimeContextLLE.isLLEActive()) {
/*TODO*/  //                Memory mem = processor.cpu.memory;
/*TODO*/  //                if (processor.cp0.isMainCpu()) {
/*TODO*/  //                    mem = RuntimeContextLLE.getMMIO();
/*TODO*/  //                }
/*TODO*/  //                processor.cpu.pc = RuntimeContextLLE.triggerBreakException(processor,
          //                Processor.isInstructionInDelaySlot(mem, processor.cpu.pc));
/*TODO*/  //            } else {
/*TODO*/  //                log.error(String.format("0x%08X - Allegrex break 0x%05X", processor.cpu.pc, imm20));
/*TODO*/  //
/*TODO*/  //                // Pause the emulator only if not ignoring invalid memory accesses
/*TODO*/  //                // (I'm too lazy to introduce a new configuration flag to ignore "break" instructions).
/*TODO*/  //                if (!Processor.memory.isIgnoreInvalidMemoryAccess()) {
/*TODO*/  //                    Emulator.PauseEmuWithStatus(Emulator.EMU_STATUS_BREAK);
/*TODO*/  //                }
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            context.compileBreak();
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int imm20 = (insn >> 6) & 1048575;
/*TODO*/  //
/*TODO*/  //            return Common.disasmBREAK(imm20);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction SYNC = new Instruction(18) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "SYNC";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "ALLEGREX";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            // Nothing to compile
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //
/*TODO*/  //            return "sync";
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction HALT = new Instruction(19) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "HALT";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "ALLEGREX";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            try {
/*TODO*/  //                RuntimeContext.executeHalt(processor);
/*TODO*/  //            } catch (StopThreadException e) {
/*TODO*/  //                log.error("Exception catched while interpreting the halt instruction");
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            context.storePc();
/*TODO*/  //            context.loadProcessor();
/*TODO*/  //            context.invokeStaticMethod(runtimeContextInternalName, "executeHalt", "(" +
          //            Type.getDescriptor(Processor.class) + ")V");
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //
/*TODO*/  //            return "halt";
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction MFIC = new Instruction(20) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "MFIC";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "ALLEGREX";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //
/*TODO*/  //            boolean interruptsEnabled = hasFlag(processor.cp0.getStatus(), STATUS_IE);
/*TODO*/  //            if (log.isTraceEnabled()) {
/*TODO*/  //                log.trace(String.format("0x%08X - mfic interruptsEnabled=%b", processor.cpu.pc,
          //                interruptsEnabled));
/*TODO*/  //            }
/*TODO*/  //            processor.cpu.setRegister(rt, interruptsEnabled ? 1 : 0);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            super.compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmRT("mfic", rt);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction MTIC = new Instruction(21, FLAG_MODIFIES_INTERRUPT_STATE) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "MTIC";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "ALLEGREX";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //
/*TODO*/  //            int value = processor.cpu.getRegister(rt);
/*TODO*/  //            if (log.isTraceEnabled()) {
/*TODO*/  //                log.trace(String.format("0x%08X - mtic interruptsEnabled=%b", processor.cpu.pc, value !=
          //                0));
/*TODO*/  //            }
/*TODO*/  //            processor.setInterruptsEnabled(value != 0);
/*TODO*/  //
/*TODO*/  //            if (RuntimeContextLLE.isLLEActive()) {
/*TODO*/  //                if (processor.isInterruptsEnabled()) {
/*TODO*/  //                    reboot.setLog4jMDC(processor);
/*TODO*/  //                }
/*TODO*/  //                RuntimeContext.checkSync();
/*TODO*/  //            } else if (processor.isInterruptsEnabled()) {
/*TODO*/  //                try {
/*TODO*/  //                    RuntimeContext.sync();
/*TODO*/  //                } catch (StopThreadException e) {
/*TODO*/  //                    log.error("Catched exception while executing mtic instruction", e);
/*TODO*/  //                }
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            super.compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmRT("mtic", rt);
/*TODO*/  //        }
/*TODO*/  //    };
struct ADD : Instruction /*new Instruction(22, FLAG_WRITES_RD)*/ {
    static ADD& Self() {
        static ADD insn;
        return insn;
    }
    static Instruction* getInstance() { return &ADD::Self(); }
    virtual void interpret(u32 insn) {
        /*TODO*/  //            int rd = (insn >> 11) & 31;
        /*TODO*/  //            int rt = (insn >> 16) & 31;
        /*TODO*/  //            int rs = (insn >> 21) & 31;
        /*TODO*/  //
        /*TODO*/  //            // just ignore overflow exception as it is useless
        /*TODO*/  //            processor.cpu.doADDU(rd, rs, rt);
    }
    /*TODO*/  //        @Override
    /*TODO*/  //        public void compile(ICompilerContext context, int insn) {
    /*TODO*/  //            if (!context.isRdRegister0()) {
    /*TODO*/  //                if (context.isRsRegister0() && context.isRtRegister0()) {
    /*TODO*/  //                    context.storeRd(0);
    /*TODO*/  //                } else {
    /*TODO*/  //                    context.prepareRdForStore();
    /*TODO*/  //                    if (context.isRsRegister0()) {
    /*TODO*/  //                        context.loadRt();
    /*TODO*/  //                    } else {
    /*TODO*/  //                        context.loadRs();
    /*TODO*/  //                        if (!context.isRtRegister0()) {
    /*TODO*/  //                            context.loadRt();
    /*TODO*/  //                            context.getMethodVisitor().visitInsn(Opcodes.IADD);
    /*TODO*/  //                        }
    /*TODO*/  //                    }
    /*TODO*/  //                    context.storeRd();
    /*TODO*/  //                }
    /*TODO*/  //            }
    /*TODO*/  //        }

    virtual std::string disasm(u32 address, u32 insn) {
        int rd = (insn >> 11) & 31;
        int rt = (insn >> 16) & 31;
        int rs = (insn >> 21) & 31;
        return Allegrex::disasmRDRSRT("add", rd, rs, rt);
    }
    virtual std::string name() { return "ADD"; }
    virtual std::string category() { return "MIPS I"; }
};

struct ADDU : Instruction /*new Instruction(23, FLAG_WRITES_RD)*/ {
    static ADDU& Self() {
        static ADDU insn;
        return insn;
    }
    static Instruction* getInstance() { return &ADDU::Self(); }
    virtual void interpret(u32 insn) 
    {
        /*TODO*/  //            int rd = (insn >> 11) & 31;
        /*TODO*/  //            int rt = (insn >> 16) & 31;
        /*TODO*/  //            int rs = (insn >> 21) & 31;
        /*TODO*/  //
        /*TODO*/  //            processor.cpu.doADDU(rd, rs, rt);    
    }
    /*TODO*/  //        @Override
    /*TODO*/  //        public void compile(ICompilerContext context, int insn) {
    /*TODO*/  //            ADD.compile(context, insn);
    /*TODO*/  //        }

    virtual std::string disasm(u32 address, u32 insn) {
        int rd = (insn >> 11) & 31;
        int rt = (insn >> 16) & 31;
        int rs = (insn >> 21) & 31;
        return Allegrex::disasmRDRSRT("addu", rd, rs, rt);
    }
    virtual std::string name() { return "ADDU"; }
    virtual std::string category() { return "MIPS I"; }

};

/*TODO*/  //    public static final Instruction ADDI = new Instruction(24, FLAG_WRITES_RT) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "ADDI";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "MIPS I";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            // just ignore overflow exception as it is useless
/*TODO*/  //            processor.cpu.doADDIU(rt, rs, (short) imm16);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            ADDIU.compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmRTRSIMM("addi", rt, rs, (short) imm16);
/*TODO*/  //        }
/*TODO*/  //    };
struct ADDIU : Instruction { /*new Instruction(25, FLAG_WRITES_RT)*/
    static ADDIU& Self() {
        static ADDIU insn;
        return insn;
    }
    static Instruction* getInstance() { return &ADDIU::Self(); }
    virtual void interpret(u32 insn) 
    {
        /*TODO*/  //            int imm16 = (insn >> 0) & 65535;
        /*TODO*/  //            int rt = (insn >> 16) & 31;
        /*TODO*/  //            int rs = (insn >> 21) & 31;
        /*TODO*/  //
        /*TODO*/  //            processor.cpu.doADDIU(rt, rs, (short) imm16);   
    }
    /*TODO*/  //        @Override
    /*TODO*/  //        public void compile(ICompilerContext context, int insn) {
    /*TODO*/  //            if (!context.isRtRegister0()) {
    /*TODO*/  //                int imm = context.getImm16(true);
    /*TODO*/  //                if (context.isRsRegister0()) {
    /*TODO*/  //                    context.storeRt(imm);
    /*TODO*/  //                } else if (imm == 0 && context.getRsRegisterIndex() == context.getRtRegisterIndex()) {
    /*TODO*/  //                    // Incrementing a register by 0 is a No-OP:
    /*TODO*/  //                    // ADDIU $reg, $reg, 0
    /*TODO*/  //                } else {
    /*TODO*/  //                    context.prepareRtForStore();
    /*TODO*/  //                    context.loadRs();
    /*TODO*/  //                    if (imm != 0) {
    /*TODO*/  //                        context.loadImm(imm);
    /*TODO*/  //                        context.getMethodVisitor().visitInsn(Opcodes.IADD);
    /*TODO*/  //                    }
    /*TODO*/  //                    context.storeRt();
    /*TODO*/  //                }
    /*TODO*/  //            }
    /*TODO*/  //        }
    virtual std::string disasm(u32 address, u32 insn) {
        int imm16 = (insn >> 0) & 65535;
        int rt = (insn >> 16) & 31;
        int rs = (insn >> 21) & 31;
        return Allegrex::disasmRTRSIMM("addiu", rt, rs, (short)imm16);
    }
    virtual std::string name() { return "ADDIU"; }
    virtual std::string category() { return "MIPS I"; }
};
/*TODO*/  //    public static final Instruction ADDIU = new Instruction(25, FLAG_WRITES_RT) {
/*TODO*/  //    public static final Instruction AND = new Instruction(26, FLAG_WRITES_RD) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "AND";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "MIPS I";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int rd = (insn >> 11) & 31;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doAND(rd, rs, rt);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            if (!context.isRdRegister0()) {
/*TODO*/  //                if (context.isRsRegister0() || context.isRtRegister0()) {
/*TODO*/  //                    context.storeRd(0);
/*TODO*/  //                } else {
/*TODO*/  //                    context.prepareRdForStore();
/*TODO*/  //                    context.loadRs();
/*TODO*/  //                    context.loadRt();
/*TODO*/  //                    context.getMethodVisitor().visitInsn(Opcodes.IAND);
/*TODO*/  //                    context.storeRd();
/*TODO*/  //                }
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int rd = (insn >> 11) & 31;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmRDRSRT("and", rd, rs, rt);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction ANDI = new Instruction(27, FLAG_WRITES_RT) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "ANDI";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "MIPS I";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doANDI(rt, rs, imm16);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            if (!context.isRtRegister0()) {
/*TODO*/  //                int imm = context.getImm16(false);
/*TODO*/  //                if (imm == 0 || context.isRsRegister0()) {
/*TODO*/  //                    context.storeRt(0);
/*TODO*/  //                } else {
/*TODO*/  //                    context.prepareRtForStore();
/*TODO*/  //                    context.loadRs();
/*TODO*/  //                    context.loadImm(imm);
/*TODO*/  //                    context.getMethodVisitor().visitInsn(Opcodes.IAND);
/*TODO*/  //                    context.storeRt();
/*TODO*/  //                }
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmRTRSIMM("andi", rt, rs, imm16);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction NOR = new Instruction(28, FLAG_WRITES_RD) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "NOR";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "MIPS I";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int rd = (insn >> 11) & 31;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doNOR(rd, rs, rt);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            if (!context.isRdRegister0()) {
/*TODO*/  //                if (context.isRsRegister0() && context.isRtRegister0()) {
/*TODO*/  //                    // nor $zr, $zr is equivalent to storing -1
/*TODO*/  //                    context.storeRd(-1);
/*TODO*/  //                } else {
/*TODO*/  //                    context.prepareRdForStore();
/*TODO*/  //                    if (context.isRsRegister0()) {
/*TODO*/  //                        context.loadRt();
/*TODO*/  //                    } else {
/*TODO*/  //                        context.loadRs();
/*TODO*/  //                        if (!context.isRtRegister0()) {
/*TODO*/  //                            // OR-ing a register with itself is a simple move.
/*TODO*/  //                            if (context.getRsRegisterIndex() != context.getRtRegisterIndex()) {
/*TODO*/  //                                context.loadRt();
/*TODO*/  //                                context.getMethodVisitor().visitInsn(Opcodes.IOR);
/*TODO*/  //                            }
/*TODO*/  //                        }
/*TODO*/  //                    }
/*TODO*/  //                    context.loadImm(-1);
/*TODO*/  //                    context.getMethodVisitor().visitInsn(Opcodes.IXOR);
/*TODO*/  //                    context.storeRd();
/*TODO*/  //                }
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int rd = (insn >> 11) & 31;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmRDRSRT("nor", rd, rs, rt);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction OR = new Instruction(29, FLAG_WRITES_RD) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "OR";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "MIPS I";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int rd = (insn >> 11) & 31;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doOR(rd, rs, rt);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            if (!context.isRdRegister0()) {
/*TODO*/  //                if (context.isRsRegister0() && context.isRtRegister0()) {
/*TODO*/  //                    context.storeRd(0);
/*TODO*/  //                } else {
/*TODO*/  //                    context.prepareRdForStore();
/*TODO*/  //                    if (context.isRsRegister0()) {
/*TODO*/  //                        context.loadRt();
/*TODO*/  //                    } else {
/*TODO*/  //                        context.loadRs();
/*TODO*/  //                        if (!context.isRtRegister0()) {
/*TODO*/  //                            // OR-ing a register with itself is a simple move.
/*TODO*/  //                            if (context.getRsRegisterIndex() != context.getRtRegisterIndex()) {
/*TODO*/  //                                context.loadRt();
/*TODO*/  //                                context.getMethodVisitor().visitInsn(Opcodes.IOR);
/*TODO*/  //                            }
/*TODO*/  //                        }
/*TODO*/  //                    }
/*TODO*/  //                    context.storeRd();
/*TODO*/  //                }
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int rd = (insn >> 11) & 31;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmRDRSRT("or", rd, rs, rt);
/*TODO*/  //        }
/*TODO*/  //    };

struct ORI : Instruction /*new Instruction(30, FLAG_WRITES_RT)*/ {
    static ORI& Self() {
        static ORI insn;
        return insn;
    }
    static Instruction* getInstance() { return &ORI::Self(); }
    virtual void interpret(u32 insn) 
    {
        /*TODO*/  //            int imm16 = (insn >> 0) & 65535;
        /*TODO*/  //            int rt = (insn >> 16) & 31;
        /*TODO*/  //            int rs = (insn >> 21) & 31;
        /*TODO*/  //
        /*TODO*/  //            processor.cpu.doORI(rt, rs, imm16);    
    }
    /*TODO*/  //        @Override
    /*TODO*/  //        public void compile(ICompilerContext context, int insn) {
    /*TODO*/  //            if (!context.isRtRegister0()) {
    /*TODO*/  //                int imm = context.getImm16(false);
    /*TODO*/  //                if (context.isRsRegister0()) {
    /*TODO*/  //                    context.storeRt(imm);
    /*TODO*/  //                } else if (imm == 0 && context.getRsRegisterIndex() == context.getRtRegisterIndex()) {
    /*TODO*/  //                    // Or-ing a register with 0 and himself is a No-OP:
    /*TODO*/  //                    // ORI $reg, $reg, 0
    /*TODO*/  //                } else {
    /*TODO*/  //                    context.prepareRtForStore();
    /*TODO*/  //                    context.loadRs();
    /*TODO*/  //                    if (imm != 0) {
    /*TODO*/  //                        context.loadImm(imm);
    /*TODO*/  //                        context.getMethodVisitor().visitInsn(Opcodes.IOR);
    /*TODO*/  //                    }
    /*TODO*/  //                    context.storeRt();
    /*TODO*/  //                }
    /*TODO*/  //            }
    /*TODO*/  //        }

    virtual std::string disasm(u32 address, u32 insn) {
        int imm16 = (insn >> 0) & 65535;
        int rt = (insn >> 16) & 31;
        int rs = (insn >> 21) & 31;
        return Allegrex::disasmRTRSIMM("ori", rt, rs, imm16);
    }
    virtual std::string name() { return "ORI"; }
    virtual std::string category() { return "MIPS I"; }
};
/*TODO*/  //    public static final Instruction XOR = new Instruction(31, FLAG_WRITES_RD) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "XOR";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "MIPS I";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int rd = (insn >> 11) & 31;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doXOR(rd, rs, rt);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            if (!context.isRdRegister0()) {
/*TODO*/  //                if (context.isRsRegister0() && context.isRtRegister0()) {
/*TODO*/  //                    context.storeRd(0);
/*TODO*/  //                } else if (context.getRtRegisterIndex() == context.getRsRegisterIndex()) {
/*TODO*/  //                    // XOR-ing a register with himself is equivalent to setting to 0.
/*TODO*/  //                    // XOR $rd, $rs, $rs
/*TODO*/  //                    context.storeRd(0);
/*TODO*/  //                } else {
/*TODO*/  //                    context.prepareRdForStore();
/*TODO*/  //                    if (context.isRsRegister0()) {
/*TODO*/  //                        context.loadRt();
/*TODO*/  //                    } else {
/*TODO*/  //                        context.loadRs();
/*TODO*/  //                        if (!context.isRtRegister0()) {
/*TODO*/  //                            context.loadRt();
/*TODO*/  //                            context.getMethodVisitor().visitInsn(Opcodes.IXOR);
/*TODO*/  //                        }
/*TODO*/  //                    }
/*TODO*/  //                    context.storeRd();
/*TODO*/  //                }
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int rd = (insn >> 11) & 31;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmRDRSRT("xor", rd, rs, rt);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction XORI = new Instruction(32, FLAG_WRITES_RT) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "XORI";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "MIPS I";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doXORI(rt, rs, imm16);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            if (!context.isRtRegister0()) {
/*TODO*/  //                int imm = context.getImm16(false);
/*TODO*/  //                if (context.isRsRegister0()) {
/*TODO*/  //                    context.storeRt(imm);
/*TODO*/  //                } else if (imm == 0 && context.getRtRegisterIndex() == context.getRsRegisterIndex()) {
/*TODO*/  //                    // XOR-ing a register with 0 and storing the result in the same register is a No-OP.
/*TODO*/  //                    // XORI $reg, $reg, 0
/*TODO*/  //                } else {
/*TODO*/  //                    context.prepareRtForStore();
/*TODO*/  //                    context.loadRs();
/*TODO*/  //                    if (imm != 0) {
/*TODO*/  //                        context.loadImm(imm);
/*TODO*/  //                        context.getMethodVisitor().visitInsn(Opcodes.IXOR);
/*TODO*/  //                    }
/*TODO*/  //                    context.storeRt();
/*TODO*/  //                }
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmRTRSIMM("xori", rt, rs, imm16);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction SLL = new Instruction(33, FLAG_WRITES_RD) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "SLL";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "MIPS I";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int sa = (insn >> 6) & 31;
/*TODO*/  //            int rd = (insn >> 11) & 31;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doSLL(rd, rt, sa);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            if (!context.isRdRegister0()) {
/*TODO*/  //                if (context.isRtRegister0()) {
/*TODO*/  //                    context.storeRd(0);
/*TODO*/  //                } else {
/*TODO*/  //                    context.prepareRdForStore();
/*TODO*/  //                    context.loadRt();
/*TODO*/  //                    int sa = context.getSaValue();
/*TODO*/  //                    if (sa != 0) {
/*TODO*/  //                        context.loadImm(sa);
/*TODO*/  //                        context.getMethodVisitor().visitInsn(Opcodes.ISHL);
/*TODO*/  //                    }
/*TODO*/  //                    context.storeRd();
/*TODO*/  //                }
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int sa = (insn >> 6) & 31;
/*TODO*/  //            int rd = (insn >> 11) & 31;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmRDRTSA("sll", rd, rt, sa);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction SLLV = new Instruction(34, FLAG_WRITES_RD) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "SLLV";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "MIPS I";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int rd = (insn >> 11) & 31;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doSLLV(rd, rt, rs);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            if (!context.isRdRegister0()) {
/*TODO*/  //                if (context.isRtRegister0()) {
/*TODO*/  //                    context.storeRd(0);
/*TODO*/  //                } else {
/*TODO*/  //                    context.prepareRdForStore();
/*TODO*/  //                    context.loadRt();
/*TODO*/  //                    if (!context.isRsRegister0()) {
/*TODO*/  //                        context.loadRs();
/*TODO*/  //                        context.loadImm(31);
/*TODO*/  //                        context.getMethodVisitor().visitInsn(Opcodes.IAND);
/*TODO*/  //                        context.getMethodVisitor().visitInsn(Opcodes.ISHL);
/*TODO*/  //                    }
/*TODO*/  //                    context.storeRd();
/*TODO*/  //                }
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int rd = (insn >> 11) & 31;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmRDRTRS("sllv", rd, rt, rs);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction SRA = new Instruction(35, FLAG_WRITES_RD) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "SRA";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "MIPS I";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int sa = (insn >> 6) & 31;
/*TODO*/  //            int rd = (insn >> 11) & 31;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doSRA(rd, rt, sa);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            if (!context.isRdRegister0()) {
/*TODO*/  //                if (context.isRtRegister0()) {
/*TODO*/  //                    context.storeRd(0);
/*TODO*/  //                } else {
/*TODO*/  //                    context.prepareRdForStore();
/*TODO*/  //                    context.loadRt();
/*TODO*/  //                    int sa = context.getSaValue();
/*TODO*/  //                    if (sa != 0) {
/*TODO*/  //                        context.loadImm(sa);
/*TODO*/  //                        context.getMethodVisitor().visitInsn(Opcodes.ISHR);
/*TODO*/  //                    }
/*TODO*/  //                    context.storeRd();
/*TODO*/  //                }
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int sa = (insn >> 6) & 31;
/*TODO*/  //            int rd = (insn >> 11) & 31;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmRDRTSA("sra", rd, rt, sa);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction SRAV = new Instruction(36, FLAG_WRITES_RD) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "SRAV";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "MIPS I";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int rd = (insn >> 11) & 31;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doSRAV(rd, rt, rs);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            if (!context.isRdRegister0()) {
/*TODO*/  //                if (context.isRtRegister0()) {
/*TODO*/  //                    context.storeRd(0);
/*TODO*/  //                } else {
/*TODO*/  //                    context.prepareRdForStore();
/*TODO*/  //                    context.loadRt();
/*TODO*/  //                    if (!context.isRsRegister0()) {
/*TODO*/  //                        context.loadRs();
/*TODO*/  //                        context.loadImm(31);
/*TODO*/  //                        context.getMethodVisitor().visitInsn(Opcodes.IAND);
/*TODO*/  //                        context.getMethodVisitor().visitInsn(Opcodes.ISHR);
/*TODO*/  //                    }
/*TODO*/  //                    context.storeRd();
/*TODO*/  //                }
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int rd = (insn >> 11) & 31;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmRDRTRS("srav", rd, rt, rs);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction SRL = new Instruction(37, FLAG_WRITES_RD) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "SRL";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "MIPS I";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int sa = (insn >> 6) & 31;
/*TODO*/  //            int rd = (insn >> 11) & 31;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doSRL(rd, rt, sa);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            if (!context.isRdRegister0()) {
/*TODO*/  //                if (context.isRtRegister0()) {
/*TODO*/  //                    context.storeRd(0);
/*TODO*/  //                } else {
/*TODO*/  //                    context.prepareRdForStore();
/*TODO*/  //                    context.loadRt();
/*TODO*/  //                    int sa = context.getSaValue();
/*TODO*/  //                    if (sa != 0) {
/*TODO*/  //                        context.loadImm(sa);
/*TODO*/  //                        context.getMethodVisitor().visitInsn(Opcodes.IUSHR);
/*TODO*/  //                    }
/*TODO*/  //                    context.storeRd();
/*TODO*/  //                }
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int sa = (insn >> 6) & 31;
/*TODO*/  //            int rd = (insn >> 11) & 31;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmRDRTSA("srl", rd, rt, sa);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction SRLV = new Instruction(38, FLAG_WRITES_RD) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "SRLV";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "MIPS I";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int rd = (insn >> 11) & 31;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doSRLV(rd, rt, rs);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            if (!context.isRdRegister0()) {
/*TODO*/  //                if (context.isRtRegister0()) {
/*TODO*/  //                    context.storeRd(0);
/*TODO*/  //                } else {
/*TODO*/  //                    context.prepareRdForStore();
/*TODO*/  //                    context.loadRt();
/*TODO*/  //                    if (!context.isRsRegister0()) {
/*TODO*/  //                        context.loadRs();
/*TODO*/  //                        context.loadImm(31);
/*TODO*/  //                        context.getMethodVisitor().visitInsn(Opcodes.IAND);
/*TODO*/  //                        context.getMethodVisitor().visitInsn(Opcodes.IUSHR);
/*TODO*/  //                    }
/*TODO*/  //                    context.storeRd();
/*TODO*/  //                }
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int rd = (insn >> 11) & 31;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmRDRTRS("srlv", rd, rt, rs);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction ROTR = new Instruction(39, FLAG_WRITES_RD) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "ROTR";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "ALLEGREX";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int sa = (insn >> 6) & 31;
/*TODO*/  //            int rd = (insn >> 11) & 31;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doROTR(rd, rt, sa);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            if (!context.isRdRegister0()) {
/*TODO*/  //                if (context.isRtRegister0()) {
/*TODO*/  //                    context.storeRd(0);
/*TODO*/  //                } else {
/*TODO*/  //                    context.prepareRdForStore();
/*TODO*/  //                    context.loadRt();
/*TODO*/  //                    int sa = context.getSaValue();
/*TODO*/  //                    if (sa != 0) {
/*TODO*/  //                        // rotateRight(rt, sa) = (rt >>> sa | rt << (32-sa))
/*TODO*/  //                        context.getMethodVisitor().visitInsn(Opcodes.DUP);
/*TODO*/  //                        context.loadImm(sa);
/*TODO*/  //                        context.getMethodVisitor().visitInsn(Opcodes.IUSHR);
/*TODO*/  //                        context.getMethodVisitor().visitInsn(Opcodes.SWAP);
/*TODO*/  //                        context.loadImm(32 - sa);
/*TODO*/  //                        context.getMethodVisitor().visitInsn(Opcodes.ISHL);
/*TODO*/  //                        context.getMethodVisitor().visitInsn(Opcodes.IOR);
/*TODO*/  //                    }
/*TODO*/  //                    context.storeRd();
/*TODO*/  //                }
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int sa = (insn >> 6) & 31;
/*TODO*/  //            int rd = (insn >> 11) & 31;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmRDRTSA("rotr", rd, rt, sa);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction ROTRV = new Instruction(40, FLAG_WRITES_RD) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "ROTRV";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "ALLEGREX";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int rd = (insn >> 11) & 31;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doROTRV(rd, rt, rs);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            if (!context.isRdRegister0()) {
/*TODO*/  //                if (context.isRtRegister0()) {
/*TODO*/  //                    context.storeRd(0);
/*TODO*/  //                } else {
/*TODO*/  //                    context.prepareRdForStore();
/*TODO*/  //                    context.loadRt();
/*TODO*/  //                    if (!context.isRsRegister0()) {
/*TODO*/  //                        // rotateRight(rt, rs) = (rt >>> rs | rt << -rs)
/*TODO*/  //                        context.loadRs();
/*TODO*/  //                        context.loadImm(31);
/*TODO*/  //                        context.getMethodVisitor().visitInsn(Opcodes.IAND);
/*TODO*/  //                        context.getMethodVisitor().visitInsn(Opcodes.DUP2);
/*TODO*/  //                        context.getMethodVisitor().visitInsn(Opcodes.IUSHR);
/*TODO*/  //                        context.getMethodVisitor().visitInsn(Opcodes.DUP_X2);
/*TODO*/  //                        context.getMethodVisitor().visitInsn(Opcodes.POP);
/*TODO*/  //                        context.getMethodVisitor().visitInsn(Opcodes.INEG);
/*TODO*/  //                        context.getMethodVisitor().visitInsn(Opcodes.ISHL);
/*TODO*/  //                        context.getMethodVisitor().visitInsn(Opcodes.IOR);
/*TODO*/  //                    }
/*TODO*/  //                    context.storeRd();
/*TODO*/  //                }
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int rd = (insn >> 11) & 31;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmRDRTRS("rotrv", rd, rt, rs);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction SLT = new Instruction(41, FLAG_WRITES_RD) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "SLT";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "MIPS I";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int rd = (insn >> 11) & 31;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doSLT(rd, rs, rt);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            if (!context.isRdRegister0()) {
/*TODO*/  //                if (context.getRsRegisterIndex() == context.getRtRegisterIndex()) {
/*TODO*/  //                    context.storeRd(0);
/*TODO*/  //                } else {
/*TODO*/  //                    MethodVisitor mv = context.getMethodVisitor();
/*TODO*/  //                    Label ifLtLabel = new Label();
/*TODO*/  //                    Label continueLabel = new Label();
/*TODO*/  //                    context.prepareRdForStore();
/*TODO*/  //                    if (context.isRsRegister0()) {
/*TODO*/  //                        // rd = 0 < rt ? 1 : 0
/*TODO*/  //                        context.loadRt();
/*TODO*/  //                        mv.visitJumpInsn(Opcodes.IFGT, ifLtLabel);
/*TODO*/  //                    } else if (context.isRtRegister0()) {
/*TODO*/  //                        // rd = rs < 0 ? 1 : 0
/*TODO*/  //                        context.loadRs();
/*TODO*/  //                        mv.visitJumpInsn(Opcodes.IFLT, ifLtLabel);
/*TODO*/  //                    } else {
/*TODO*/  //                        // rd = rs < rt ? 1 : 0
/*TODO*/  //                        context.loadRs();
/*TODO*/  //                        context.loadRt();
/*TODO*/  //                        mv.visitJumpInsn(Opcodes.IF_ICMPLT, ifLtLabel);
/*TODO*/  //                    }
/*TODO*/  //                    context.loadImm(0);
/*TODO*/  //                    mv.visitJumpInsn(Opcodes.GOTO, continueLabel);
/*TODO*/  //                    mv.visitLabel(ifLtLabel);
/*TODO*/  //                    context.loadImm(1);
/*TODO*/  //                    mv.visitLabel(continueLabel);
/*TODO*/  //                    context.storeRd();
/*TODO*/  //                }
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int rd = (insn >> 11) & 31;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmRDRSRT("slt", rd, rs, rt);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction SLTI = new Instruction(42, FLAG_WRITES_RT) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "SLTI";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "MIPS I";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doSLTI(rt, rs, (int) (short) imm16);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            if (!context.isRtRegister0()) {
/*TODO*/  //                int simm16 = context.getImm16(true);
/*TODO*/  //                if (context.isRsRegister0()) {
/*TODO*/  //                    context.storeRt(simm16 > 0 ? 1 : 0);
/*TODO*/  //                } else {
/*TODO*/  //                    MethodVisitor mv = context.getMethodVisitor();
/*TODO*/  //                    Label ifLtLabel = new Label();
/*TODO*/  //                    Label continueLabel = new Label();
/*TODO*/  //                    context.prepareRtForStore();
/*TODO*/  //                    // rt = rs < simm16 ? 1 : 0
/*TODO*/  //                    context.loadRs();
/*TODO*/  //                    if (simm16 == 0) {
/*TODO*/  //                        mv.visitJumpInsn(Opcodes.IFLT, ifLtLabel);
/*TODO*/  //                    } else {
/*TODO*/  //                        context.loadImm(simm16);
/*TODO*/  //                        mv.visitJumpInsn(Opcodes.IF_ICMPLT, ifLtLabel);
/*TODO*/  //                    }
/*TODO*/  //                    context.loadImm(0);
/*TODO*/  //                    mv.visitJumpInsn(Opcodes.GOTO, continueLabel);
/*TODO*/  //                    mv.visitLabel(ifLtLabel);
/*TODO*/  //                    context.loadImm(1);
/*TODO*/  //                    mv.visitLabel(continueLabel);
/*TODO*/  //                    context.storeRt();
/*TODO*/  //                }
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmRTRSIMM("slti", rt, rs, (int) (short) imm16);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction SLTU = new Instruction(43, FLAG_WRITES_RD) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "SLTU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "MIPS I";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int rd = (insn >> 11) & 31;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doSLTU(rd, rs, rt);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            if (!context.isRdRegister0()) {
/*TODO*/  //                if (context.getRsRegisterIndex() == context.getRtRegisterIndex()) {
/*TODO*/  //                    // rd = x < x
/*TODO*/  //                    context.storeRd(0);
/*TODO*/  //                } else if (context.isRtRegister0()) {
/*TODO*/  //                    // rd = rs < 0
/*TODO*/  //                    context.storeRd(0);
/*TODO*/  //                } else {
/*TODO*/  //                    MethodVisitor mv = context.getMethodVisitor();
/*TODO*/  //                    Label ifLtLabel = new Label();
/*TODO*/  //                    Label continueLabel = new Label();
/*TODO*/  //                    context.prepareRdForStore();
/*TODO*/  //                    if (context.isRsRegister0()) {
/*TODO*/  //                        // rd = 0 < rt ? 1 : 0
/*TODO*/  //                        context.loadRt();
/*TODO*/  //                        mv.visitJumpInsn(Opcodes.IFNE, ifLtLabel);
/*TODO*/  //                    } else {
/*TODO*/  //                        // rd = rs < rt ? 1 : 0
/*TODO*/  //                        context.loadRs();
/*TODO*/  //                        context.convertUnsignedIntToLong();
/*TODO*/  //                        context.loadRt();
/*TODO*/  //                        context.convertUnsignedIntToLong();
/*TODO*/  //                        mv.visitInsn(Opcodes.LCMP); // -1 if rs < rt, 0 if rs == rt, 1 if rs > rt
/*TODO*/  //                        mv.visitJumpInsn(Opcodes.IFLT, ifLtLabel);
/*TODO*/  //                    }
/*TODO*/  //                    context.loadImm(0);
/*TODO*/  //                    mv.visitJumpInsn(Opcodes.GOTO, continueLabel);
/*TODO*/  //                    mv.visitLabel(ifLtLabel);
/*TODO*/  //                    context.loadImm(1);
/*TODO*/  //                    mv.visitLabel(continueLabel);
/*TODO*/  //                    context.storeRd();
/*TODO*/  //                }
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int rd = (insn >> 11) & 31;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmRDRSRT("sltu", rd, rs, rt);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction SLTIU = new Instruction(44, FLAG_WRITES_RT) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "SLTIU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "MIPS I";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doSLTIU(rt, rs, (int) (short) imm16);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            if (!context.isRtRegister0()) {
/*TODO*/  //                int simm16 = context.getImm16(true);
/*TODO*/  //                if (context.isRsRegister0()) {
/*TODO*/  //                    // rt = 0 < simm16 ? 1 : 0
/*TODO*/  //                    context.storeRt(0 < simm16 ? 1 : 0);
/*TODO*/  //                } else if (simm16 == 0) {
/*TODO*/  //                    // rt = rs < 0
/*TODO*/  //                    context.storeRt(0);
/*TODO*/  //                } else {
/*TODO*/  //                    MethodVisitor mv = context.getMethodVisitor();
/*TODO*/  //                    Label ifLtLabel = new Label();
/*TODO*/  //                    Label continueLabel = new Label();
/*TODO*/  //                    context.prepareRtForStore();
/*TODO*/  //                    if (simm16 == 1) {
/*TODO*/  //                        // rt = rs < 1 ? 1 : 0   <=> rt = rs == 0 ? 1 : 0
/*TODO*/  //                        context.loadRs();
/*TODO*/  //                        mv.visitJumpInsn(Opcodes.IFEQ, ifLtLabel);
/*TODO*/  //                    } else {
/*TODO*/  //                        // rt = rs < simm16 ? 1 : 0
/*TODO*/  //                        context.loadRs();
/*TODO*/  //                        context.convertUnsignedIntToLong();
/*TODO*/  //                        mv.visitLdcInsn(((long) simm16) & 0xFFFFFFFFL);
/*TODO*/  //                        mv.visitInsn(Opcodes.LCMP); // -1 if rs < rt, 0 if rs == rt, 1 if rs > rt
/*TODO*/  //                        mv.visitJumpInsn(Opcodes.IFLT, ifLtLabel);
/*TODO*/  //                    }
/*TODO*/  //                    context.loadImm(0);
/*TODO*/  //                    mv.visitJumpInsn(Opcodes.GOTO, continueLabel);
/*TODO*/  //                    mv.visitLabel(ifLtLabel);
/*TODO*/  //                    context.loadImm(1);
/*TODO*/  //                    mv.visitLabel(continueLabel);
/*TODO*/  //                    context.storeRt();
/*TODO*/  //                }
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmRTRSIMM("sltiu", rt, rs, (int) (short) imm16);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction SUB = new Instruction(45, FLAG_WRITES_RD) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "SUB";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "MIPS I";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int rd = (insn >> 11) & 31;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            // just ignore overflow exception as it is useless
/*TODO*/  //            processor.cpu.doSUBU(rd, rs, rt);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            if (!context.isRdRegister0()) {
/*TODO*/  //                // SUB $rd, $rs, $rs <=> li $rd, 0
/*TODO*/  //                if (context.getRsRegisterIndex() == context.getRtRegisterIndex()) {
/*TODO*/  //                    context.storeRd(0);
/*TODO*/  //                } else {
/*TODO*/  //                    context.prepareRdForStore();
/*TODO*/  //                    if (context.isRsRegister0()) {
/*TODO*/  //                        context.loadRt();
/*TODO*/  //                        context.getMethodVisitor().visitInsn(Opcodes.INEG);
/*TODO*/  //                    } else {
/*TODO*/  //                        context.loadRs();
/*TODO*/  //                        if (!context.isRtRegister0()) {
/*TODO*/  //                            context.loadRt();
/*TODO*/  //                            context.getMethodVisitor().visitInsn(Opcodes.ISUB);
/*TODO*/  //                        }
/*TODO*/  //                    }
/*TODO*/  //                    context.storeRd();
/*TODO*/  //                }
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int rd = (insn >> 11) & 31;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmRDRSRT("sub", rd, rs, rt);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction SUBU = new Instruction(46, FLAG_WRITES_RD) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "SUBU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "MIPS I";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int rd = (insn >> 11) & 31;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doSUBU(rd, rs, rt);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            SUB.compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int rd = (insn >> 11) & 31;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmRDRSRT("subu", rd, rs, rt);
/*TODO*/  //        }
/*TODO*/  //    };
struct LUI : Instruction {
    static LUI& Self() {
        static LUI insn;
        return insn;
    }
    static Instruction* getInstance() { return &LUI::Self(); }
    virtual void interpret(u32 insn) 
    {
        /*TODO*/  //            int imm16 = (insn >> 0) & 65535;
        /*TODO*/  //            int rt = (insn >> 16) & 31;
        /*TODO*/  //
        /*TODO*/  //            processor.cpu.doLUI(rt, imm16);    
    }

    /*TODO*/  //        @Override
    /*TODO*/  //        public void compile(ICompilerContext context, int insn) {
    /*TODO*/  //            if (!context.isRtRegister0()) {
    /*TODO*/  //                int uimm16 = context.getImm16(false);
    /*TODO*/  //                context.storeRt(uimm16 << 16);
    /*TODO*/  //            }
    /*TODO*/  //        }

    virtual std::string disasm(u32 address, u32 insn) {
        int imm16 = (insn >> 0) & 65535;
        int rt = (insn >> 16) & 31;
        return Allegrex::disasmRTIMM("lui", rt, imm16);
    }
    virtual std::string name() { return "LUI"; }
    virtual std::string category() { return "MIPS I"; }     
};
/*TODO*/  //    public static final Instruction SEB = new Instruction(48, FLAG_WRITES_RD) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "SEB";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "ALLEGREX";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int rd = (insn >> 11) & 31;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doSEB(rd, rt);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            if (!context.isRdRegister0()) {
/*TODO*/  //                context.prepareRdForStore();
/*TODO*/  //                context.loadRt();
/*TODO*/  //                context.getMethodVisitor().visitInsn(Opcodes.I2B);
/*TODO*/  //                context.storeRd();
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int rd = (insn >> 11) & 31;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmRDRT("seb", rd, rt);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction SEH = new Instruction(49, FLAG_WRITES_RD) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "SEH";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "ALLEGREX";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int rd = (insn >> 11) & 31;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doSEH(rd, rt);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            if (!context.isRdRegister0()) {
/*TODO*/  //                context.prepareRdForStore();
/*TODO*/  //                context.loadRt();
/*TODO*/  //                context.getMethodVisitor().visitInsn(Opcodes.I2S);
/*TODO*/  //                context.storeRd();
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int rd = (insn >> 11) & 31;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmRDRT("seh", rd, rt);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction BITREV = new Instruction(50, FLAG_WRITES_RD) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "BITREV";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "ALLEGREX";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int rd = (insn >> 11) & 31;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doBITREV(rd, rt);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            context.compileRDRT("doBITREV");
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int rd = (insn >> 11) & 31;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmRDRT("bitrev", rd, rt);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction WSBH = new Instruction(51, FLAG_WRITES_RD) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "WSBH";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "ALLEGREX";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int rd = (insn >> 11) & 31;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doWSBH(rd, rt);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            context.compileRDRT("doWSBH");
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int rd = (insn >> 11) & 31;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmRDRT("wsbh", rd, rt);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction WSBW = new Instruction(52, FLAG_WRITES_RD) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "WSBW";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "ALLEGREX";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int rd = (insn >> 11) & 31;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doWSBW(rd, rt);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            context.compileRDRT("doWSBW");
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int rd = (insn >> 11) & 31;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmRDRT("wsbw", rd, rt);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction MOVZ = new Instruction(53, FLAG_WRITES_RD) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "MOVZ";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "ALLEGREX";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int rd = (insn >> 11) & 31;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doMOVZ(rd, rs, rt);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            context.loadRt();
/*TODO*/  //            Label doNotChange = new Label();
/*TODO*/  //            context.getMethodVisitor().visitJumpInsn(Opcodes.IFNE, doNotChange);
/*TODO*/  //            context.prepareRdForStore();
/*TODO*/  //            context.loadRs();
/*TODO*/  //            context.storeRd();
/*TODO*/  //            context.getMethodVisitor().visitLabel(doNotChange);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int rd = (insn >> 11) & 31;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmRDRSRT("movz", rd, rs, rt);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction MOVN = new Instruction(54, FLAG_WRITES_RD) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "MOVN";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "ALLEGREX";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int rd = (insn >> 11) & 31;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doMOVN(rd, rs, rt);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            context.loadRt();
/*TODO*/  //            Label doNotChange = new Label();
/*TODO*/  //            context.getMethodVisitor().visitJumpInsn(Opcodes.IFEQ, doNotChange);
/*TODO*/  //            context.prepareRdForStore();
/*TODO*/  //            context.loadRs();
/*TODO*/  //            context.storeRd();
/*TODO*/  //            context.getMethodVisitor().visitLabel(doNotChange);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int rd = (insn >> 11) & 31;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmRDRSRT("movn", rd, rs, rt);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction MAX = new Instruction(55, FLAG_WRITES_RD) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "MAX";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "ALLEGREX";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int rd = (insn >> 11) & 31;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doMAX(rd, rs, rt);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            if (!context.isRdRegister0()) {
/*TODO*/  //                Label continueLabel = new Label();
/*TODO*/  //                if (context.getRdRegisterIndex() == context.getRtRegisterIndex()) {
/*TODO*/  //                    // When $rd==$rt:
/*TODO*/  //                    // if ($rs > $rt) {
/*TODO*/  //                    //   $rd = $rs
/*TODO*/  //                    // }
/*TODO*/  //                    context.loadRs();
/*TODO*/  //                    context.loadRt();
/*TODO*/  //                    context.getMethodVisitor().visitJumpInsn(Opcodes.IF_ICMPLE, continueLabel);
/*TODO*/  //                    context.prepareRdForStore();
/*TODO*/  //                    context.loadRs();
/*TODO*/  //                    context.storeRd();
/*TODO*/  //                    context.getMethodVisitor().visitLabel(continueLabel);
/*TODO*/  //                } else if (context.getRdRegisterIndex() == context.getRsRegisterIndex()) {
/*TODO*/  //                    // When $rd==$rs:
/*TODO*/  //                    // if ($rs < $rt) {
/*TODO*/  //                    //   $rd = $rt
/*TODO*/  //                    // }
/*TODO*/  //                    context.loadRs();
/*TODO*/  //                    context.loadRt();
/*TODO*/  //                    context.getMethodVisitor().visitJumpInsn(Opcodes.IF_ICMPGE, continueLabel);
/*TODO*/  //                    context.prepareRdForStore();
/*TODO*/  //                    context.loadRt();
/*TODO*/  //                    context.storeRd();
/*TODO*/  //                    context.getMethodVisitor().visitLabel(continueLabel);
/*TODO*/  //                } else if (context.getRsRegisterIndex() == context.getRtRegisterIndex()) {
/*TODO*/  //                    // When $rs==$rt:
/*TODO*/  //                    // $rd = $rs
/*TODO*/  //                    context.prepareRdForStore();
/*TODO*/  //                    context.loadRs();
/*TODO*/  //                    context.storeRd();
/*TODO*/  //                } else {
/*TODO*/  //                    // When $rd!=$rs and $rd!=$rt and $rs!=$rt:
/*TODO*/  //                    // if ($rs > $rt) {
/*TODO*/  //                    //   $rd = $rs
/*TODO*/  //                    // } else {
/*TODO*/  //                    //   $rd = $rt
/*TODO*/  //                    // }
/*TODO*/  //                    context.prepareRdForStore();
/*TODO*/  //                    context.loadRs();
/*TODO*/  //                    context.loadRt();
/*TODO*/  //                    Label case1Label = new Label();
/*TODO*/  //                    context.getMethodVisitor().visitJumpInsn(Opcodes.IF_ICMPLE, case1Label);
/*TODO*/  //                    context.loadRs();
/*TODO*/  //                    context.getMethodVisitor().visitJumpInsn(Opcodes.GOTO, continueLabel);
/*TODO*/  //                    context.getMethodVisitor().visitLabel(case1Label);
/*TODO*/  //                    context.loadRt();
/*TODO*/  //                    context.getMethodVisitor().visitLabel(continueLabel);
/*TODO*/  //                    context.storeRd();
/*TODO*/  //                }
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int rd = (insn >> 11) & 31;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmRDRSRT("max", rd, rs, rt);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction MIN = new Instruction(56, FLAG_WRITES_RD) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "MIN";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "ALLEGREX";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int rd = (insn >> 11) & 31;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doMIN(rd, rs, rt);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            if (!context.isRdRegister0()) {
/*TODO*/  //                Label continueLabel = new Label();
/*TODO*/  //                if (context.getRdRegisterIndex() == context.getRtRegisterIndex()) {
/*TODO*/  //                    // When $rd==$rt:
/*TODO*/  //                    // if ($rs < $rt) {
/*TODO*/  //                    //   $rd = $rs
/*TODO*/  //                    // }
/*TODO*/  //                    context.loadRs();
/*TODO*/  //                    context.loadRt();
/*TODO*/  //                    context.getMethodVisitor().visitJumpInsn(Opcodes.IF_ICMPGE, continueLabel);
/*TODO*/  //                    context.prepareRdForStore();
/*TODO*/  //                    context.loadRs();
/*TODO*/  //                    context.storeRd();
/*TODO*/  //                    context.getMethodVisitor().visitLabel(continueLabel);
/*TODO*/  //                } else if (context.getRdRegisterIndex() == context.getRsRegisterIndex()) {
/*TODO*/  //                    // When $rd==$rs:
/*TODO*/  //                    // if ($rs > $rt) {
/*TODO*/  //                    //   $rd = $rt
/*TODO*/  //                    // }
/*TODO*/  //                    context.loadRs();
/*TODO*/  //                    context.loadRt();
/*TODO*/  //                    context.getMethodVisitor().visitJumpInsn(Opcodes.IF_ICMPLE, continueLabel);
/*TODO*/  //                    context.prepareRdForStore();
/*TODO*/  //                    context.loadRt();
/*TODO*/  //                    context.storeRd();
/*TODO*/  //                    context.getMethodVisitor().visitLabel(continueLabel);
/*TODO*/  //                } else if (context.getRsRegisterIndex() == context.getRtRegisterIndex()) {
/*TODO*/  //                    // When $rs==$rt:
/*TODO*/  //                    // $rd = $rs
/*TODO*/  //                    context.prepareRdForStore();
/*TODO*/  //                    context.loadRs();
/*TODO*/  //                    context.storeRd();
/*TODO*/  //                } else {
/*TODO*/  //                    // When $rd!=$rs and $rd!=$rt and $rs!=$rt:
/*TODO*/  //                    // if ($rs < $rt) {
/*TODO*/  //                    //   $rd = $rs
/*TODO*/  //                    // } else {
/*TODO*/  //                    //   $rd = $rt
/*TODO*/  //                    // }
/*TODO*/  //                    context.prepareRdForStore();
/*TODO*/  //                    context.loadRs();
/*TODO*/  //                    context.loadRt();
/*TODO*/  //                    Label case1Label = new Label();
/*TODO*/  //                    context.getMethodVisitor().visitJumpInsn(Opcodes.IF_ICMPGE, case1Label);
/*TODO*/  //                    context.loadRs();
/*TODO*/  //                    context.getMethodVisitor().visitJumpInsn(Opcodes.GOTO, continueLabel);
/*TODO*/  //                    context.getMethodVisitor().visitLabel(case1Label);
/*TODO*/  //                    context.loadRt();
/*TODO*/  //                    context.getMethodVisitor().visitLabel(continueLabel);
/*TODO*/  //                    context.storeRd();
/*TODO*/  //                }
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int rd = (insn >> 11) & 31;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmRDRSRT("min", rd, rs, rt);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction CLZ = new Instruction(57, FLAG_WRITES_RD) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "CLZ";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "ALLEGREX";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int rd = (insn >> 11) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doCLZ(rd, rs);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            if (!context.isRdRegister0()) {
/*TODO*/  //                if (context.isRsRegister0()) {
/*TODO*/  //                    context.storeRd(32);
/*TODO*/  //                } else {
/*TODO*/  //                    context.prepareRdForStore();
/*TODO*/  //                    context.loadRs();
/*TODO*/  //                    context.invokeStaticMethod(Type.getInternalName(Integer.class), "numberOfLeadingZeros",
          //                    "(I)I");
/*TODO*/  //                    context.storeRd();
/*TODO*/  //                }
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int rd = (insn >> 11) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmRDRS("clz", rd, rs);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction CLO = new Instruction(58, FLAG_WRITES_RD) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "CLO";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "ALLEGREX";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int rd = (insn >> 11) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doCLO(rd, rs);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            if (!context.isRdRegister0()) {
/*TODO*/  //                if (context.isRsRegister0()) {
/*TODO*/  //                    context.storeRd(0);
/*TODO*/  //                } else {
/*TODO*/  //                    context.prepareRdForStore();
/*TODO*/  //                    context.loadRs();
/*TODO*/  //                    context.loadImm(-1);
/*TODO*/  //                    context.getMethodVisitor().visitInsn(Opcodes.IXOR);
/*TODO*/  //                    context.invokeStaticMethod(Type.getInternalName(Integer.class), "numberOfLeadingZeros",
          //                    "(I)I");
/*TODO*/  //                    context.storeRd();
/*TODO*/  //                }
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int rd = (insn >> 11) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmRDRS("clo", rd, rs);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction EXT = new Instruction(59, FLAG_WRITES_RT) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "EXT";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "ALLEGREX";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int lsb = (insn >> 6) & 31;
/*TODO*/  //            int msb = (insn >> 11) & 31;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doEXT(rt, rs, lsb, msb);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            if (!context.isRtRegister0()) {
/*TODO*/  //                int lsb = (insn >> 6) & 31;
/*TODO*/  //                int msb = (insn >> 11) & 31;
/*TODO*/  //                int mask = ~(~0 << (msb + 1));
/*TODO*/  //                if (context.isRsRegister0() || mask == 0) {
/*TODO*/  //                    context.storeRt(0);
/*TODO*/  //                } else {
/*TODO*/  //                    context.prepareRtForStore();
/*TODO*/  //                    context.loadRs();
/*TODO*/  //                    if (lsb != 0) {
/*TODO*/  //                        context.loadImm(lsb);
/*TODO*/  //                        context.getMethodVisitor().visitInsn(Opcodes.IUSHR);
/*TODO*/  //                    }
/*TODO*/  //                    if (mask != 0xFFFFFFFF) {
/*TODO*/  //                        context.loadImm(mask);
/*TODO*/  //                        context.getMethodVisitor().visitInsn(Opcodes.IAND);
/*TODO*/  //                    }
/*TODO*/  //                    context.storeRt();
/*TODO*/  //                }
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int lsb = (insn >> 6) & 31;
/*TODO*/  //            int msb = (insn >> 11) & 31;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmEXT(rt, rs, lsb, msb);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction INS = new Instruction(60, FLAG_WRITES_RT) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "INS";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "ALLEGREX";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int lsb = (insn >> 6) & 31;
/*TODO*/  //            int msb = (insn >> 11) & 31;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doINS(rt, rs, lsb, msb);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            if (!context.isRtRegister0()) {
/*TODO*/  //                int lsb = (insn >> 6) & 31;
/*TODO*/  //                int msb = (insn >> 11) & 31;
/*TODO*/  //                int mask = ~(~0 << (msb - lsb + 1)) << lsb;
/*TODO*/  //
/*TODO*/  //                if (mask == 0xFFFFFFFF && context.isRsRegister0()) {
/*TODO*/  //                    context.storeRt(0);
/*TODO*/  //                } else if (mask != 0) {
/*TODO*/  //                    context.prepareRtForStore();
/*TODO*/  //                    if (mask == 0xFFFFFFFF) {
/*TODO*/  //                        context.loadRs();
/*TODO*/  //                        if (lsb != 0) {
/*TODO*/  //                            context.loadImm(lsb);
/*TODO*/  //                            context.getMethodVisitor().visitInsn(Opcodes.ISHL);
/*TODO*/  //                        }
/*TODO*/  //                    } else {
/*TODO*/  //                        context.loadRt();
/*TODO*/  //                        context.loadImm(~mask);
/*TODO*/  //                        context.getMethodVisitor().visitInsn(Opcodes.IAND);
/*TODO*/  //                        if (!context.isRsRegister0()) {
/*TODO*/  //                            context.loadRs();
/*TODO*/  //                            if (lsb != 0) {
/*TODO*/  //                                context.loadImm(lsb);
/*TODO*/  //                                context.getMethodVisitor().visitInsn(Opcodes.ISHL);
/*TODO*/  //                            }
/*TODO*/  //                            if (mask != 0xFFFFFFFF) {
/*TODO*/  //                                context.loadImm(mask);
/*TODO*/  //                                context.getMethodVisitor().visitInsn(Opcodes.IAND);
/*TODO*/  //                            }
/*TODO*/  //                            context.getMethodVisitor().visitInsn(Opcodes.IOR);
/*TODO*/  //                        }
/*TODO*/  //                    }
/*TODO*/  //                    context.storeRt();
/*TODO*/  //                }
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int lsb = (insn >> 6) & 31;
/*TODO*/  //            int msb = (insn >> 11) & 31;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmINS(rt, rs, lsb, msb);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction MULT = new Instruction(61) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "MULT";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "MIPS I";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doMULT(rs, rt);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            context.prepareHiloForStore();
/*TODO*/  //            if (context.isRsRegister0() || context.isRtRegister0()) {
/*TODO*/  //                context.getMethodVisitor().visitLdcInsn(0L);
/*TODO*/  //            } else {
/*TODO*/  //                context.loadRs();
/*TODO*/  //                context.getMethodVisitor().visitInsn(Opcodes.I2L);
/*TODO*/  //                context.loadRt();
/*TODO*/  //                context.getMethodVisitor().visitInsn(Opcodes.I2L);
/*TODO*/  //                context.getMethodVisitor().visitInsn(Opcodes.LMUL);
/*TODO*/  //            }
/*TODO*/  //            context.storeHilo();
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmRSRT("mult", rs, rt);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction MULTU = new Instruction(62) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "MULTU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "MIPS I";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doMULTU(rs, rt);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            context.prepareHiloForStore();
/*TODO*/  //            if (context.isRsRegister0() || context.isRtRegister0()) {
/*TODO*/  //                context.getMethodVisitor().visitLdcInsn(0L);
/*TODO*/  //            } else {
/*TODO*/  //                context.loadRs();
/*TODO*/  //                context.convertUnsignedIntToLong();
/*TODO*/  //                context.loadRt();
/*TODO*/  //                context.convertUnsignedIntToLong();
/*TODO*/  //                context.getMethodVisitor().visitInsn(Opcodes.LMUL);
/*TODO*/  //            }
/*TODO*/  //            context.storeHilo();
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmRSRT("multu", rs, rt);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction MADD = new Instruction(63) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "MADD";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "ALLEGREX";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doMADD(rs, rt);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            if (!context.isRsRegister0() && !context.isRtRegister0()) {
/*TODO*/  //                context.prepareHiloForStore();
/*TODO*/  //                context.loadHilo();
/*TODO*/  //                context.loadRs();
/*TODO*/  //                context.getMethodVisitor().visitInsn(Opcodes.I2L);
/*TODO*/  //                context.loadRt();
/*TODO*/  //                context.getMethodVisitor().visitInsn(Opcodes.I2L);
/*TODO*/  //                context.getMethodVisitor().visitInsn(Opcodes.LMUL);
/*TODO*/  //                context.getMethodVisitor().visitInsn(Opcodes.LADD);
/*TODO*/  //                context.storeHilo();
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmRSRT("madd", rs, rt);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction MADDU = new Instruction(64) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "MADDU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "ALLEGREX";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doMADDU(rs, rt);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            if (!context.isRsRegister0() && !context.isRtRegister0()) {
/*TODO*/  //                context.prepareHiloForStore();
/*TODO*/  //                context.loadHilo();
/*TODO*/  //                context.loadRs();
/*TODO*/  //                context.convertUnsignedIntToLong();
/*TODO*/  //                context.loadRt();
/*TODO*/  //                context.convertUnsignedIntToLong();
/*TODO*/  //                context.getMethodVisitor().visitInsn(Opcodes.LMUL);
/*TODO*/  //                context.getMethodVisitor().visitInsn(Opcodes.LADD);
/*TODO*/  //                context.storeHilo();
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmRSRT("maddu", rs, rt);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction MSUB = new Instruction(65) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "MSUB";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "ALLEGREX";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doMSUB(rs, rt);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            if (!context.isRsRegister0() && !context.isRtRegister0()) {
/*TODO*/  //                context.prepareHiloForStore();
/*TODO*/  //                context.loadHilo();
/*TODO*/  //                context.loadRs();
/*TODO*/  //                context.getMethodVisitor().visitInsn(Opcodes.I2L);
/*TODO*/  //                context.loadRt();
/*TODO*/  //                context.getMethodVisitor().visitInsn(Opcodes.I2L);
/*TODO*/  //                context.getMethodVisitor().visitInsn(Opcodes.LMUL);
/*TODO*/  //                context.getMethodVisitor().visitInsn(Opcodes.LSUB);
/*TODO*/  //                context.storeHilo();
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmRSRT("msub", rs, rt);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction MSUBU = new Instruction(66) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "MSUBU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "ALLEGREX";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doMSUBU(rs, rt);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            if (!context.isRsRegister0() && !context.isRtRegister0()) {
/*TODO*/  //                context.prepareHiloForStore();
/*TODO*/  //                context.loadHilo();
/*TODO*/  //                context.loadRs();
/*TODO*/  //                context.convertUnsignedIntToLong();
/*TODO*/  //                context.loadRt();
/*TODO*/  //                context.convertUnsignedIntToLong();
/*TODO*/  //                context.getMethodVisitor().visitInsn(Opcodes.LMUL);
/*TODO*/  //                context.getMethodVisitor().visitInsn(Opcodes.LSUB);
/*TODO*/  //                context.storeHilo();
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmRSRT("msubu", rs, rt);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction DIV = new Instruction(67) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "DIV";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "MIPS I";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doDIV(rs, rt);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            Label divideByZero = new Label();
/*TODO*/  //            Label afterInstruction = new Label();
/*TODO*/  //            context.loadRt();
/*TODO*/  //            context.getMethodVisitor().visitJumpInsn(Opcodes.IFEQ, divideByZero);
/*TODO*/  //
/*TODO*/  //            context.loadRs();
/*TODO*/  //            context.loadRt();
/*TODO*/  //            context.getMethodVisitor().visitInsn(Opcodes.DUP2);
/*TODO*/  //            context.getMethodVisitor().visitInsn(Opcodes.IREM);
/*TODO*/  //            context.getMethodVisitor().visitInsn(Opcodes.I2L);
/*TODO*/  //            context.loadImm(32);
/*TODO*/  //            context.getMethodVisitor().visitInsn(Opcodes.LSHL);
/*TODO*/  //            context.getMethodVisitor().visitInsn(Opcodes.DUP2_X2);
/*TODO*/  //            context.getMethodVisitor().visitInsn(Opcodes.POP2);
/*TODO*/  //            context.getMethodVisitor().visitInsn(Opcodes.IDIV);
/*TODO*/  //            context.getMethodVisitor().visitInsn(Opcodes.I2L);
/*TODO*/  //            context.getMethodVisitor().visitLdcInsn(0x00000000FFFFFFFFL);
/*TODO*/  //            context.getMethodVisitor().visitInsn(Opcodes.LAND);
/*TODO*/  //            context.getMethodVisitor().visitInsn(Opcodes.LOR);
/*TODO*/  //            context.storeHilo();
/*TODO*/  //            context.getMethodVisitor().visitJumpInsn(Opcodes.GOTO, afterInstruction);
/*TODO*/  //
/*TODO*/  //            // Division by zero handled by the interpreted instruction
/*TODO*/  //            context.getMethodVisitor().visitLabel(divideByZero);
/*TODO*/  //            context.compileInterpreterInstruction();
/*TODO*/  //
/*TODO*/  //            context.getMethodVisitor().visitLabel(afterInstruction);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmRSRT("div", rs, rt);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction DIVU = new Instruction(68) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "DIVU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "MIPS I";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doDIVU(rs, rt);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            Label divideByZero = new Label();
/*TODO*/  //            Label afterInstruction = new Label();
/*TODO*/  //            context.loadRt();
/*TODO*/  //            context.getMethodVisitor().visitJumpInsn(Opcodes.IFEQ, divideByZero);
/*TODO*/  //
/*TODO*/  //            context.loadRs();
/*TODO*/  //            context.getMethodVisitor().visitInsn(Opcodes.I2L);
/*TODO*/  //            context.getMethodVisitor().visitLdcInsn(0x00000000FFFFFFFFL);
/*TODO*/  //            context.getMethodVisitor().visitInsn(Opcodes.LAND);
/*TODO*/  //            context.getMethodVisitor().visitInsn(Opcodes.DUP2);
/*TODO*/  //            context.loadRt();
/*TODO*/  //            context.getMethodVisitor().visitInsn(Opcodes.I2L);
/*TODO*/  //            context.getMethodVisitor().visitLdcInsn(0x00000000FFFFFFFFL);
/*TODO*/  //            context.getMethodVisitor().visitInsn(Opcodes.LAND);
/*TODO*/  //            context.getMethodVisitor().visitInsn(Opcodes.DUP2_X2);
/*TODO*/  //            context.getMethodVisitor().visitInsn(Opcodes.LREM);
/*TODO*/  //            context.loadImm(32);
/*TODO*/  //            context.getMethodVisitor().visitInsn(Opcodes.LSHL);
/*TODO*/  //            context.storeLTmp1();
/*TODO*/  //            context.getMethodVisitor().visitInsn(Opcodes.LDIV);
/*TODO*/  //            context.getMethodVisitor().visitLdcInsn(0x00000000FFFFFFFFL);
/*TODO*/  //            context.getMethodVisitor().visitInsn(Opcodes.LAND);
/*TODO*/  //            context.loadLTmp1();
/*TODO*/  //            context.getMethodVisitor().visitInsn(Opcodes.LOR);
/*TODO*/  //            context.storeHilo();
/*TODO*/  //            context.getMethodVisitor().visitJumpInsn(Opcodes.GOTO, afterInstruction);
/*TODO*/  //
/*TODO*/  //            // Division by zero handled by the interpreted instruction
/*TODO*/  //            context.getMethodVisitor().visitLabel(divideByZero);
/*TODO*/  //            context.compileInterpreterInstruction();
/*TODO*/  //
/*TODO*/  //            context.getMethodVisitor().visitLabel(afterInstruction);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmRSRT("divu", rs, rt);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction MFHI = new Instruction(69, FLAG_WRITES_RD) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "MFHI";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "MIPS I";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int rd = (insn >> 11) & 31;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doMFHI(rd);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            if (!context.isRdRegister0()) {
/*TODO*/  //                context.prepareRdForStore();
/*TODO*/  //                context.loadHilo();
/*TODO*/  //                context.loadImm(32);
/*TODO*/  //                context.getMethodVisitor().visitInsn(Opcodes.LUSHR);
/*TODO*/  //                context.getMethodVisitor().visitInsn(Opcodes.L2I);
/*TODO*/  //                context.storeRd();
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int rd = (insn >> 11) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmRD("mfhi", rd);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction MFLO = new Instruction(70, FLAG_WRITES_RD) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "MFLO";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "MIPS I";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int rd = (insn >> 11) & 31;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doMFLO(rd);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            if (!context.isRdRegister0()) {
/*TODO*/  //                context.prepareRdForStore();
/*TODO*/  //                context.loadHilo();
/*TODO*/  //                context.getMethodVisitor().visitLdcInsn(0xFFFFFFFFL);
/*TODO*/  //                context.getMethodVisitor().visitInsn(Opcodes.LAND);
/*TODO*/  //                context.getMethodVisitor().visitInsn(Opcodes.L2I);
/*TODO*/  //                context.storeRd();
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int rd = (insn >> 11) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmRD("mflo", rd);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction MTHI = new Instruction(71) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "MTHI";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "MIPS I";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doMTHI(rs);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            super.compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmRS("mthi", rs);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction MTLO = new Instruction(72) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "MTLO";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "MIPS I";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doMTLO(rs);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            context.loadHilo();
/*TODO*/  //            context.getMethodVisitor().visitLdcInsn(0xFFFFFFFF00000000L);
/*TODO*/  //            context.getMethodVisitor().visitInsn(Opcodes.LAND);
/*TODO*/  //            if (!context.isRsRegister0()) {
/*TODO*/  //                context.loadRs();
/*TODO*/  //                context.getMethodVisitor().visitInsn(Opcodes.I2L);
/*TODO*/  //                context.getMethodVisitor().visitLdcInsn(0x00000000FFFFFFFFL);
/*TODO*/  //                context.getMethodVisitor().visitInsn(Opcodes.LAND);
/*TODO*/  //                context.getMethodVisitor().visitInsn(Opcodes.LOR);
/*TODO*/  //            }
/*TODO*/  //            context.storeHilo();
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmRS("mtlo", rs);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //
/*TODO*/  ////
/*TODO*/  //// BEQ has the flag "FLAG_ENDS_BLOCK" because it can end a block when the
/*TODO*/  //// conditional branch can be reduced to an unconditional branch (rt == rs).
/*TODO*/  ////    "BEQ $xx, $xx, target"
/*TODO*/  //// is equivalent to
/*TODO*/  ////    "B target"
/*TODO*/  //// This special case is recognized in the method Compiler.analyse().
/*TODO*/  ////
/*TODO*/  //    public static final Instruction BEQ = new Instruction(73, FLAGS_BRANCH_INSTRUCTION | FLAG_ENDS_BLOCK) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "BEQ";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "MIPS I";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            if (processor.cpu.doBEQ(rs, rt, (int) (short) imm16)) {
/*TODO*/  //                processor.interpretDelayslot();
/*TODO*/  //            }
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            super.compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmRSRTOFFSET("beq", rs, rt, (int) (short) imm16, address);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction BEQL = new Instruction(74, FLAGS_BRANCH_INSTRUCTION) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "BEQL";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "MIPS II";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            if (processor.cpu.doBEQL(rs, rt, (int) (short) imm16)) {
/*TODO*/  //                processor.interpretDelayslot();
/*TODO*/  //            }
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            super.compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmRSRTOFFSET("beql", rs, rt, (int) (short) imm16, address);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction BGEZ = new Instruction(75, FLAGS_BRANCH_INSTRUCTION) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "BGEZ";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "MIPS I";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            if (processor.cpu.doBGEZ(rs, (int) (short) imm16)) {
/*TODO*/  //                processor.interpretDelayslot();
/*TODO*/  //            }
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            super.compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmRSOFFSET("bgez", rs, (int) (short) imm16, address);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction BGEZAL = new Instruction(76, FLAGS_LINK_INSTRUCTION |
          //    FLAGS_BRANCH_INSTRUCTION) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "BGEZAL";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "MIPS I";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            if (processor.cpu.doBGEZAL(rs, (int) (short) imm16)) {
/*TODO*/  //                processor.interpretDelayslot();
/*TODO*/  //            }
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            super.compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmRSOFFSET("bgezal", rs, (int) (short) imm16, address);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction BGEZALL = new Instruction(77, FLAGS_LINK_INSTRUCTION |
          //    FLAGS_BRANCH_INSTRUCTION) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "BGEZALL";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "MIPS II";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            if (processor.cpu.doBGEZALL(rs, (int) (short) imm16)) {
/*TODO*/  //                processor.interpretDelayslot();
/*TODO*/  //            }
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            super.compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmRSOFFSET("bgezall", rs, (int) (short) imm16, address);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction BGEZL = new Instruction(78, FLAGS_BRANCH_INSTRUCTION) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "BGEZL";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "MIPS II";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            if (processor.cpu.doBGEZL(rs, (int) (short) imm16)) {
/*TODO*/  //                processor.interpretDelayslot();
/*TODO*/  //            }
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            super.compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmRSOFFSET("bgezl", rs, (int) (short) imm16, address);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction BGTZ = new Instruction(79, FLAGS_BRANCH_INSTRUCTION) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "BGTZ";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "MIPS I";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            if (processor.cpu.doBGTZ(rs, (int) (short) imm16)) {
/*TODO*/  //                processor.interpretDelayslot();
/*TODO*/  //            }
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            super.compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmRSOFFSET("bgtz", rs, (int) (short) imm16, address);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction BGTZL = new Instruction(80, FLAGS_BRANCH_INSTRUCTION) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "BGTZL";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "MIPS II";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            if (processor.cpu.doBGTZL(rs, (int) (short) imm16)) {
/*TODO*/  //                processor.interpretDelayslot();
/*TODO*/  //            }
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            super.compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmRSOFFSET("bgtzl", rs, (int) (short) imm16, address);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction BLEZ = new Instruction(81, FLAGS_BRANCH_INSTRUCTION) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "BLEZ";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "MIPS I";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            if (processor.cpu.doBLEZ(rs, (int) (short) imm16)) {
/*TODO*/  //                processor.interpretDelayslot();
/*TODO*/  //            }
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            super.compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmRSOFFSET("blez", rs, (int) (short) imm16, address);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction BLEZL = new Instruction(82, FLAGS_BRANCH_INSTRUCTION) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "BLEZL";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "MIPS II";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            if (processor.cpu.doBLEZL(rs, (int) (short) imm16)) {
/*TODO*/  //                processor.interpretDelayslot();
/*TODO*/  //            }
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            super.compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmRSOFFSET("blezl", rs, (int) (short) imm16, address);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction BLTZ = new Instruction(83, FLAGS_BRANCH_INSTRUCTION) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "BLTZ";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "MIPS I";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            if (processor.cpu.doBLTZ(rs, (int) (short) imm16)) {
/*TODO*/  //                processor.interpretDelayslot();
/*TODO*/  //            }
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            super.compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmRSOFFSET("bltz", rs, (int) (short) imm16, address);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction BLTZAL = new Instruction(84, FLAGS_LINK_INSTRUCTION |
          //    FLAGS_BRANCH_INSTRUCTION) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "BLTZAL";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "MIPS I";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            if (processor.cpu.doBLTZAL(rs, (int) (short) imm16)) {
/*TODO*/  //                processor.interpretDelayslot();
/*TODO*/  //            }
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            super.compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmRSOFFSET("bltzal", rs, (int) (short) imm16, address);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction BLTZALL = new Instruction(85, FLAGS_LINK_INSTRUCTION |
          //    FLAGS_BRANCH_INSTRUCTION) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "BLTZALL";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "MIPS II";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            if (processor.cpu.doBLTZALL(rs, (int) (short) imm16)) {
/*TODO*/  //                processor.interpretDelayslot();
/*TODO*/  //            }
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            super.compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmRSOFFSET("bltzall", rs, (int) (short) imm16, address);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction BLTZL = new Instruction(86, FLAGS_BRANCH_INSTRUCTION) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "BLTZL";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "MIPS I";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            if (processor.cpu.doBLTZL(rs, (int) (short) imm16)) {
/*TODO*/  //                processor.interpretDelayslot();
/*TODO*/  //            }
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            super.compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmRSOFFSET("bltzl", rs, (int) (short) imm16, address);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction BNE = new Instruction(87, FLAGS_BRANCH_INSTRUCTION) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "BNE";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "MIPS I";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            if (processor.cpu.doBNE(rs, rt, (int) (short) imm16)) {
/*TODO*/  //                processor.interpretDelayslot();
/*TODO*/  //            }
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            super.compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmRSRTOFFSET("bne", rs, rt, (int) (short) imm16, address);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction BNEL = new Instruction(88, FLAGS_BRANCH_INSTRUCTION) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "BNEL";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "MIPS II";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            if (processor.cpu.doBNEL(rs, rt, (int) (short) imm16)) {
/*TODO*/  //                processor.interpretDelayslot();
/*TODO*/  //            }
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            super.compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmRSRTOFFSET("bnel", rs, rt, (int) (short) imm16, address);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction J = new Instruction(89, FLAG_HAS_DELAY_SLOT | FLAG_IS_JUMPING |
          //    FLAG_CANNOT_BE_SPLIT | FLAG_ENDS_BLOCK) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "J";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "MIPS I";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int imm26 = (insn >> 0) & 67108863;
/*TODO*/  //
/*TODO*/  //            if (processor.cpu.doJ(imm26)) {
/*TODO*/  //                processor.interpretDelayslot();
/*TODO*/  //            }
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            super.compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int imm26 = (insn >> 0) & 67108863;
/*TODO*/  //
/*TODO*/  //            return Common.disasmJUMP("j", imm26, address);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction JAL = new Instruction(90, FLAGS_LINK_INSTRUCTION | FLAG_IS_JUMPING) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "JAL";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "MIPS I";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int imm26 = (insn >> 0) & 67108863;
/*TODO*/  //
/*TODO*/  //            if (processor.cpu.doJAL(imm26)) {
/*TODO*/  //                processor.interpretDelayslot();
/*TODO*/  //            }
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            super.compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int imm26 = (insn >> 0) & 67108863;
/*TODO*/  //
/*TODO*/  //            return Common.disasmJUMP("jal", imm26, address);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction JALR = new Instruction(91, FLAG_HAS_DELAY_SLOT) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "JALR";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "MIPS I";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int rd = (insn >> 11) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            if (processor.cpu.doJALR(rd, rs)) {
/*TODO*/  //                processor.interpretDelayslot();
/*TODO*/  //            }
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            super.compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int rd = (insn >> 11) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmRDRS("jalr", rd, rs);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction JR = new Instruction(92, FLAG_HAS_DELAY_SLOT | FLAG_CANNOT_BE_SPLIT |
          //    FLAG_ENDS_BLOCK) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "JR";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "MIPS I";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            if (processor.cpu.doJR(rs)) {
/*TODO*/  //                processor.interpretDelayslot();
/*TODO*/  //            }
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            super.compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmRS("jr", rs);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction BC1F = new Instruction(93, FLAGS_BRANCH_INSTRUCTION) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "BC1F";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "MIPS I/FPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //
/*TODO*/  //            if (processor.cpu.doBC1F((int) (short) imm16)) {
/*TODO*/  //                processor.interpretDelayslot();
/*TODO*/  //            }
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            super.compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //
/*TODO*/  //            return Common.disasmOFFSET("bc1f", (int) (short) imm16, address);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction BC1T = new Instruction(94, FLAGS_BRANCH_INSTRUCTION) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "BC1T";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "MIPS I/FPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //
/*TODO*/  //            if (processor.cpu.doBC1T((int) (short) imm16)) {
/*TODO*/  //                processor.interpretDelayslot();
/*TODO*/  //            }
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            super.compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //
/*TODO*/  //            return Common.disasmOFFSET("bc1t", (int) (short) imm16, address);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction BC1FL = new Instruction(95, FLAGS_BRANCH_INSTRUCTION) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "BC1FL";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "MIPS II/FPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //
/*TODO*/  //            if (processor.cpu.doBC1FL((int) (short) imm16)) {
/*TODO*/  //                processor.interpretDelayslot();
/*TODO*/  //            }
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            super.compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //
/*TODO*/  //            return Common.disasmOFFSET("bc1fl", (int) (short) imm16, address);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction BC1TL = new Instruction(96, FLAGS_BRANCH_INSTRUCTION) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "BC1TL";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "MIPS II/FPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //
/*TODO*/  //            if (processor.cpu.doBC1TL((int) (short) imm16)) {
/*TODO*/  //                processor.interpretDelayslot();
/*TODO*/  //            }
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            super.compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //
/*TODO*/  //            return Common.disasmOFFSET("bc1tl", (int) (short) imm16, address);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction BVF = new Instruction(97, FLAGS_BRANCH_INSTRUCTION) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "BVF";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "MIPS I/VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int imm3 = (insn >> 18) & 7;
/*TODO*/  //
/*TODO*/  //            if (processor.cpu.doBVF(imm3, (int) (short) imm16)) {
/*TODO*/  //                processor.interpretDelayslot();
/*TODO*/  //            }
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            super.compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int imm3 = (insn >> 18) & 7;
/*TODO*/  //
/*TODO*/  //            return Common.disasmVCCOFFSET("bvf", imm3, imm16, address);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction BVT = new Instruction(98, FLAGS_BRANCH_INSTRUCTION) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "BVT";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "MIPS I/VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int imm3 = (insn >> 18) & 7;
/*TODO*/  //
/*TODO*/  //            if (processor.cpu.doBVT(imm3, (int) (short) imm16)) {
/*TODO*/  //                processor.interpretDelayslot();
/*TODO*/  //            }
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            super.compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int imm3 = (insn >> 18) & 7;
/*TODO*/  //
/*TODO*/  //            return Common.disasmVCCOFFSET("bvt", imm3, imm16, address);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction BVFL = new Instruction(99, FLAGS_BRANCH_INSTRUCTION) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "BVFL";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "MIPS II/VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int imm3 = (insn >> 18) & 7;
/*TODO*/  //
/*TODO*/  //            if (processor.cpu.doBVFL(imm3, (int) (short) imm16)) {
/*TODO*/  //                processor.interpretDelayslot();
/*TODO*/  //            }
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            super.compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int imm3 = (insn >> 18) & 7;
/*TODO*/  //
/*TODO*/  //            return Common.disasmVCCOFFSET("bvfl", imm3, imm16, address);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction BVTL = new Instruction(100, FLAGS_BRANCH_INSTRUCTION) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "BVTL";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "MIPS II/VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int imm3 = (insn >> 18) & 7;
/*TODO*/  //
/*TODO*/  //            if (processor.cpu.doBVTL(imm3, (int) (short) imm16)) {
/*TODO*/  //                processor.interpretDelayslot();
/*TODO*/  //            }
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            super.compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int imm3 = (insn >> 18) & 7;
/*TODO*/  //
/*TODO*/  //            return Common.disasmVCCOFFSET("bvtl", imm3, imm16, address);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction LB = new Instruction(101, FLAG_WRITES_RT) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "LB";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "MIPS I";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doLB(rt, rs, (int) (short) imm16);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            if (!context.isRtRegister0()) {
/*TODO*/  //                context.prepareRtForStore();
/*TODO*/  //                context.memRead8(context.getRsRegisterIndex(), context.getImm16(true));
/*TODO*/  //                context.getMethodVisitor().visitInsn(Opcodes.I2B);
/*TODO*/  //                context.storeRt();
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmRTIMMRS("lb", rt, rs, (int) (short) imm16);
/*TODO*/  //        }
/*TODO*/  //    };

struct LBU : Instruction { /*new Instruction(102, FLAG_WRITES_RT)*/
    static LBU& Self() {
        static LBU insn;
        return insn;
    }
    static Instruction* getInstance() { return &LBU::Self(); }
    virtual void interpret(u32 insn) 
    {
        /*TODO*/  //            int imm16 = (insn >> 0) & 65535;
        /*TODO*/  //            int rt = (insn >> 16) & 31;
        /*TODO*/  //            int rs = (insn >> 21) & 31;
        /*TODO*/  //
        /*TODO*/  //            processor.cpu.doLBU(rt, rs, (int) (short) imm16);    
    }
    /*TODO*/  // void compile(ICompilerContext context, int insn) {
    /*TODO*/  //    if (!context.isRtRegister0()) {
    /*TODO*/  //        context.prepareRtForStore();
    /*TODO*/  //        context.memRead8(context.getRsRegisterIndex(), context.getImm16(true));
    /*TODO*/  //        context.storeRt();
    /*TODO*/  //    }
    /*TODO*/  //}

    virtual std::string disasm(u32 address, u32 insn) {
        int imm16 = (insn >> 0) & 65535;
        int rt = (insn >> 16) & 31;
        int rs = (insn >> 21) & 31;
        return Allegrex::disasmRTIMMRS("lbu", rt, rs, (int)(short)imm16);
    }
    virtual std::string name() { return "LBU"; }
    virtual std::string category() { return "MIPS I"; }
};
/*TODO*/  //    public static final Instruction LH = new Instruction(103, FLAG_WRITES_RT) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "LH";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "MIPS I";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doLH(rt, rs, (int) (short) imm16);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            if (!context.isRtRegister0()) {
/*TODO*/  //                context.prepareRtForStore();
/*TODO*/  //                context.memRead16(context.getRsRegisterIndex(), context.getImm16(true));
/*TODO*/  //                context.getMethodVisitor().visitInsn(Opcodes.I2S);
/*TODO*/  //                context.storeRt();
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmRTIMMRS("lh", rt, rs, (int) (short) imm16);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction LHU = new Instruction(104, FLAG_WRITES_RT) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "LHU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "MIPS I";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doLHU(rt, rs, (int) (short) imm16);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            if (!context.isRtRegister0()) {
/*TODO*/  //                context.prepareRtForStore();
/*TODO*/  //                context.memRead16(context.getRsRegisterIndex(), context.getImm16(true));
/*TODO*/  //                context.storeRt();
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmRTIMMRS("lhu", rt, rs, (int) (short) imm16);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction LW = new Instruction(105, FLAG_WRITES_RT) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "LW";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "MIPS I";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doLW(rt, rs, (int) (short) imm16);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            if (!context.isRtRegister0()) {
/*TODO*/  //                int rs = context.getRsRegisterIndex();
/*TODO*/  //                int simm16 = context.getImm16(true);
/*TODO*/  //
/*TODO*/  //                int countSequence = 1;
/*TODO*/  //                int[] offsets = null;
/*TODO*/  //                int[] registers = null;
/*TODO*/  //
/*TODO*/  //                if (!context.getCodeInstruction().isDelaySlot() && context.getRtRegisterIndex() != rs) {
/*TODO*/  //                    int address = context.getCodeInstruction().getAddress() + 4;
/*TODO*/  //                    // Compare LW opcode and rs register
/*TODO*/  //                    final int opcodeMask = 0xFFE00000;
/*TODO*/  //                    for (int i = 1; true; i++, address += 4) {
/*TODO*/  //                        CodeInstruction nextCodeInstruction = context.getCodeInstruction(address);
/*TODO*/  //                        boolean isSequence = false;
/*TODO*/  //                        if (nextCodeInstruction != null && !nextCodeInstruction.isBranchTarget()) {
/*TODO*/  //                            if ((nextCodeInstruction.getOpcode() & opcodeMask) == (insn & opcodeMask)) {
/*TODO*/  //                                if (nextCodeInstruction.getRtRegisterIndex() != rs) {
/*TODO*/  //                                    if (offsets == null) {
/*TODO*/  //                                        offsets = new int[2];
/*TODO*/  //                                        registers = new int[2];
/*TODO*/  //                                        offsets[0] = simm16;
/*TODO*/  //                                        registers[0] = context.getRtRegisterIndex();
/*TODO*/  //                                    } else {
/*TODO*/  //                                        offsets = Utilities.extendArray(offsets, 1);
/*TODO*/  //                                        registers = Utilities.extendArray(registers, 1);
/*TODO*/  //                                    }
/*TODO*/  //                                    offsets[i] = nextCodeInstruction.getImm16(true);
/*TODO*/  //                                    registers[i] = nextCodeInstruction.getRtRegisterIndex();
/*TODO*/  //                                    isSequence = true;
/*TODO*/  //                                }
/*TODO*/  //                            }
/*TODO*/  //                        }
/*TODO*/  //
/*TODO*/  //                        if (!isSequence) {
/*TODO*/  //                            break;
/*TODO*/  //                        }
/*TODO*/  //                        countSequence++;
/*TODO*/  //                    }
/*TODO*/  //                }
/*TODO*/  //
/*TODO*/  //                if (countSequence > 1 && context.compileLWsequence(rs, offsets, registers)) {
/*TODO*/  //                    if (countSequence > 1) {
/*TODO*/  //                        if (Compiler.log.isDebugEnabled()) {
/*TODO*/  //                            CodeInstruction sequence = new SequenceLWCodeInstruction(rs, offsets,
          //                            registers);
/*TODO*/  //                            sequence.setAddress(context.getCodeInstruction().getAddress());
/*TODO*/  //                            Compiler.log.debug(sequence);
/*TODO*/  //                        }
/*TODO*/  //
/*TODO*/  //                        // Skip the next lw instructions
/*TODO*/  //                        context.skipInstructions(countSequence - 1, false);
/*TODO*/  //                    }
/*TODO*/  //                } else {
/*TODO*/  //                    context.prepareRtForStore();
/*TODO*/  //                    context.memRead32(rs, simm16, false);
/*TODO*/  //                    context.storeRt();
/*TODO*/  //                }
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmRTIMMRS("lw", rt, rs, (int) (short) imm16);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction LWL = new Instruction(106, FLAG_WRITES_RT) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "LWL";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "MIPS I";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doLWL(rt, rs, (int) (short) imm16);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            if (!context.isRtRegister0()) {
/*TODO*/  //                MethodVisitor mv = context.getMethodVisitor();
/*TODO*/  //                int simm16 = context.getImm16(true);
/*TODO*/  //                context.prepareRtForStore();
/*TODO*/  //                context.memRead32(context.getRsRegisterIndex(), simm16, true);
/*TODO*/  //                context.loadRs();
/*TODO*/  //                if (simm16 != 0) {
/*TODO*/  //                    context.loadImm16(true);
/*TODO*/  //                    mv.visitInsn(Opcodes.IADD);
/*TODO*/  //                }
/*TODO*/  //                context.loadImm(0x3);
/*TODO*/  //                mv.visitInsn(Opcodes.IAND);
/*TODO*/  //                context.loadImm(0x3);
/*TODO*/  //                mv.visitInsn(Opcodes.ISHL);
/*TODO*/  //                mv.visitInsn(Opcodes.DUP_X1);
/*TODO*/  //                context.loadImm(0x3 << 3);
/*TODO*/  //                mv.visitInsn(Opcodes.IXOR);
/*TODO*/  //                mv.visitInsn(Opcodes.ISHL);
/*TODO*/  //                mv.visitInsn(Opcodes.SWAP);
/*TODO*/  //                context.loadImm(0x00FFFFFF);
/*TODO*/  //                mv.visitInsn(Opcodes.SWAP);
/*TODO*/  //                mv.visitInsn(Opcodes.ISHR);
/*TODO*/  //                context.loadRt();
/*TODO*/  //                mv.visitInsn(Opcodes.IAND);
/*TODO*/  //                mv.visitInsn(Opcodes.IOR);
/*TODO*/  //                context.storeRt();
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmRTIMMRS("lwl", rt, rs, (int) (short) imm16);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction LWR = new Instruction(107, FLAG_WRITES_RT) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "LWR";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "MIPS I";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doLWR(rt, rs, (int) (short) imm16);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            if (!context.isRtRegister0()) {
/*TODO*/  //                MethodVisitor mv = context.getMethodVisitor();
/*TODO*/  //                int simm16 = context.getImm16(true);
/*TODO*/  //                context.prepareRtForStore();
/*TODO*/  //                context.memRead32(context.getRsRegisterIndex(), simm16, true);
/*TODO*/  //                context.loadRs();
/*TODO*/  //                if (simm16 != 0) {
/*TODO*/  //                    context.loadImm16(true);
/*TODO*/  //                    mv.visitInsn(Opcodes.IADD);
/*TODO*/  //                }
/*TODO*/  //                context.loadImm(0x3);
/*TODO*/  //                mv.visitInsn(Opcodes.IAND);
/*TODO*/  //                context.loadImm(0x3);
/*TODO*/  //                mv.visitInsn(Opcodes.ISHL);
/*TODO*/  //                mv.visitInsn(Opcodes.DUP_X1);
/*TODO*/  //                mv.visitInsn(Opcodes.IUSHR);
/*TODO*/  //                mv.visitInsn(Opcodes.SWAP);
/*TODO*/  //                context.loadImm(0xFFFFFF00);
/*TODO*/  //                mv.visitInsn(Opcodes.SWAP);
/*TODO*/  //                context.loadImm(0x3 << 3);
/*TODO*/  //                mv.visitInsn(Opcodes.IXOR);
/*TODO*/  //                mv.visitInsn(Opcodes.ISHL);
/*TODO*/  //                context.loadRt();
/*TODO*/  //                mv.visitInsn(Opcodes.IAND);
/*TODO*/  //                mv.visitInsn(Opcodes.IOR);
/*TODO*/  //                context.storeRt();
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmRTIMMRS("lwr", rt, rs, (int) (short) imm16);
/*TODO*/  //        }
/*TODO*/  //    };
struct SB : Instruction { /*new Instruction(108)*/
    static SB& Self() {
        static SB insn;
        return insn;
    }
    static Instruction* getInstance() { return &SB::Self(); }
    virtual void interpret(u32 insn) {
        /*TODO*/  //            int imm16 = (insn >> 0) & 65535;
        /*TODO*/  //            int rt = (insn >> 16) & 31;
        /*TODO*/  //            int rs = (insn >> 21) & 31;
        /*TODO*/  //
        /*TODO*/  //            processor.cpu.doSB(rt, rs, (int) (short) imm16);
    }
    /*TODO*/  //        public void compile(ICompilerContext context, int insn) {
    /*TODO*/  //            int rs = context.getRsRegisterIndex();
    /*TODO*/  //            int simm16 = context.getImm16(true);
    /*TODO*/  //            if (context.isRtRegister0()) {
    /*TODO*/  //                context.memWriteZero8(rs, simm16);
    /*TODO*/  //            } else {
    /*TODO*/  //                context.prepareMemWrite8(rs, simm16);
    /*TODO*/  //                context.loadRt();
    /*TODO*/  //                context.memWrite8(rs, simm16);
    /*TODO*/  //            }
    /*TODO*/  //        }

    virtual std::string disasm(u32 address, u32 insn) {
        int imm16 = (insn >> 0) & 65535;
        int rt = (insn >> 16) & 31;
        int rs = (insn >> 21) & 31;
        return Allegrex::disasmRTIMMRS("sb", rt, rs, (int) (short) imm16);
    }
    virtual std::string name() { return "SB"; }
    virtual std::string category() { return "MIPS I"; }
};

/*TODO*/  //    public static final Instruction SH = new Instruction(109) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "SH";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "MIPS I";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doSH(rt, rs, (int) (short) imm16);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            int rs = context.getRsRegisterIndex();
/*TODO*/  //            int simm16 = context.getImm16(true);
/*TODO*/  //            context.prepareMemWrite16(rs, simm16);
/*TODO*/  //            context.loadRt();
/*TODO*/  //            context.memWrite16(rs, simm16);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmRTIMMRS("sh", rt, rs, (int) (short) imm16);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction SW = new Instruction(110) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "SW";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "MIPS I";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doSW(rt, rs, (int) (short) imm16);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            int rs = context.getRsRegisterIndex();
/*TODO*/  //            int simm16 = context.getImm16(true);
/*TODO*/  //
/*TODO*/  //            int countSequence = 1;
/*TODO*/  //            int[] offsets = null;
/*TODO*/  //            int[] registers = null;
/*TODO*/  //
/*TODO*/  //            if (!context.getCodeInstruction().isDelaySlot()) {
/*TODO*/  //                int address = context.getCodeInstruction().getAddress() + 4;
/*TODO*/  //                // Compare SW opcode and rs register
/*TODO*/  //                final int opcodeMask = 0xFFE00000;
/*TODO*/  //                for (int i = 1; true; i++, address += 4) {
/*TODO*/  //                    CodeInstruction nextCodeInstruction = context.getCodeInstruction(address);
/*TODO*/  //                    boolean isSequence = false;
/*TODO*/  //                    if (nextCodeInstruction != null && !nextCodeInstruction.isBranchTarget()) {
/*TODO*/  //                        if ((nextCodeInstruction.getOpcode() & opcodeMask) == (insn & opcodeMask)) {
/*TODO*/  //                            if (offsets == null) {
/*TODO*/  //                                offsets = new int[2];
/*TODO*/  //                                registers = new int[2];
/*TODO*/  //                                offsets[0] = simm16;
/*TODO*/  //                                registers[0] = context.getRtRegisterIndex();
/*TODO*/  //                            } else {
/*TODO*/  //                                offsets = Utilities.extendArray(offsets, 1);
/*TODO*/  //                                registers = Utilities.extendArray(registers, 1);
/*TODO*/  //                            }
/*TODO*/  //                            offsets[i] = nextCodeInstruction.getImm16(true);
/*TODO*/  //                            registers[i] = nextCodeInstruction.getRtRegisterIndex();
/*TODO*/  //                            isSequence = true;
/*TODO*/  //                        }
/*TODO*/  //                    }
/*TODO*/  //
/*TODO*/  //                    if (!isSequence) {
/*TODO*/  //                        break;
/*TODO*/  //                    }
/*TODO*/  //                    countSequence++;
/*TODO*/  //                }
/*TODO*/  //            }
/*TODO*/  //
/*TODO*/  //            if (countSequence > 1 && context.compileSWsequence(rs, offsets, registers)) {
/*TODO*/  //                if (countSequence > 1) {
/*TODO*/  //                    if (Compiler.log.isDebugEnabled()) {
/*TODO*/  //                        CodeInstruction sequence = new SequenceSWCodeInstruction(rs, offsets, registers);
/*TODO*/  //                        sequence.setAddress(context.getCodeInstruction().getAddress());
/*TODO*/  //                        Compiler.log.debug(sequence);
/*TODO*/  //                    }
/*TODO*/  //
/*TODO*/  //                    // Skip the next sw instructions
/*TODO*/  //                    context.skipInstructions(countSequence - 1, false);
/*TODO*/  //                }
/*TODO*/  //            } else {
/*TODO*/  //                context.prepareMemWrite32(rs, simm16, false);
/*TODO*/  //                context.loadRt();
/*TODO*/  //                context.memWrite32(rs, simm16, false);
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmRTIMMRS("sw", rt, rs, (int) (short) imm16);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction SWL = new Instruction(111) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "SWL";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "MIPS I";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doSWL(rt, rs, (int) (short) imm16);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            MethodVisitor mv = context.getMethodVisitor();
/*TODO*/  //            int simm16 = context.getImm16(true);
/*TODO*/  //            context.prepareMemWrite32(context.getRsRegisterIndex(), simm16, true);
/*TODO*/  //            context.loadRt();
/*TODO*/  //            context.loadRs();
/*TODO*/  //            if (simm16 != 0) {
/*TODO*/  //                context.loadImm16(true);
/*TODO*/  //                mv.visitInsn(Opcodes.IADD);
/*TODO*/  //            }
/*TODO*/  //            context.loadImm(0x3);
/*TODO*/  //            mv.visitInsn(Opcodes.IAND);
/*TODO*/  //            context.loadImm(0x3);
/*TODO*/  //            mv.visitInsn(Opcodes.ISHL);
/*TODO*/  //            mv.visitInsn(Opcodes.DUP_X1);
/*TODO*/  //            context.loadImm(0x3 << 3);
/*TODO*/  //            mv.visitInsn(Opcodes.IXOR);
/*TODO*/  //            mv.visitInsn(Opcodes.IUSHR);
/*TODO*/  //            mv.visitInsn(Opcodes.SWAP);
/*TODO*/  //            context.loadImm(0xFFFFFF00);
/*TODO*/  //            mv.visitInsn(Opcodes.SWAP);
/*TODO*/  //            mv.visitInsn(Opcodes.ISHL);
/*TODO*/  //            context.memRead32(context.getRsRegisterIndex(), simm16, true);
/*TODO*/  //            mv.visitInsn(Opcodes.IAND);
/*TODO*/  //            mv.visitInsn(Opcodes.IOR);
/*TODO*/  //            context.memWrite32(context.getRsRegisterIndex(), simm16, true);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmRTIMMRS("swl", rt, rs, (int) (short) imm16);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction SWR = new Instruction(112) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "SWR";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "MIPS I";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doSWR(rt, rs, (int) (short) imm16);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            MethodVisitor mv = context.getMethodVisitor();
/*TODO*/  //            int simm16 = context.getImm16(true);
/*TODO*/  //            context.prepareMemWrite32(context.getRsRegisterIndex(), simm16, true);
/*TODO*/  //            context.loadRt();
/*TODO*/  //            context.loadRs();
/*TODO*/  //            if (simm16 != 0) {
/*TODO*/  //                context.loadImm16(true);
/*TODO*/  //                mv.visitInsn(Opcodes.IADD);
/*TODO*/  //            }
/*TODO*/  //            context.loadImm(0x3);
/*TODO*/  //            mv.visitInsn(Opcodes.IAND);
/*TODO*/  //            context.loadImm(0x3);
/*TODO*/  //            mv.visitInsn(Opcodes.ISHL);
/*TODO*/  //            mv.visitInsn(Opcodes.DUP_X1);
/*TODO*/  //            mv.visitInsn(Opcodes.ISHL);
/*TODO*/  //            mv.visitInsn(Opcodes.SWAP);
/*TODO*/  //            context.loadImm(0x3 << 3);
/*TODO*/  //            mv.visitInsn(Opcodes.IXOR);
/*TODO*/  //            context.loadImm(0x00FFFFFF);
/*TODO*/  //            mv.visitInsn(Opcodes.SWAP);
/*TODO*/  //            mv.visitInsn(Opcodes.ISHR);
/*TODO*/  //            context.memRead32(context.getRsRegisterIndex(), simm16, true);
/*TODO*/  //            mv.visitInsn(Opcodes.IAND);
/*TODO*/  //            mv.visitInsn(Opcodes.IOR);
/*TODO*/  //            context.memWrite32(context.getRsRegisterIndex(), simm16, true);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmRTIMMRS("swr", rt, rs, (int) (short) imm16);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction LL = new Instruction(113) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "LL";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "ALLEGREX";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doLL(rt, rs, (int) (short) imm16);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            context.compileRTRSIMM("doLL", true);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmRTIMMRS("ll", rt, rs, (int) (short) imm16);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction LWC1 = new Instruction(114) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "LWC1";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "MIPS I/FPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int ft = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doLWC1(ft, rs, (int) (short) imm16);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            context.prepareFtForStore();
/*TODO*/  //            context.memRead32(context.getRsRegisterIndex(), context.getImm16(true), false);
/*TODO*/  //            context.invokeStaticMethod(Type.getInternalName(Float.class), "intBitsToFloat", "(I)F");
/*TODO*/  //            context.storeFt();
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int ft = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmFTIMMRS("lwc1", ft, rs, (int) (short) imm16);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction LVS = new Instruction(115) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "LVS";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "MIPS I/VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int vt2 = (insn >> 0) & 3;
/*TODO*/  //            int imm14 = (insn >> 2) & 16383;
/*TODO*/  //            int vt5 = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doLVS((vt5 | (vt2 << 5)), rs, (int) (short) (imm14 << 2));
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            int vt2 = (insn >> 0) & 3;
/*TODO*/  //            int vt5 = (insn >> 16) & 31;
/*TODO*/  //            int vt = vt5 | (vt2 << 5);
/*TODO*/  //            int simm14 = context.getImm14(true);
/*TODO*/  //            int rs = context.getRsRegisterIndex();
/*TODO*/  //
/*TODO*/  //            context.prepareVtForStoreInt(1, vt, 0);
/*TODO*/  //            context.memRead32(rs, simm14, false);
/*TODO*/  //            context.storeVtInt(1, vt, 0);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int vt2 = (insn >> 0) & 3;
/*TODO*/  //            int imm14 = (insn >> 2) & 16383;
/*TODO*/  //            int vt5 = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmVTIMMRS("lv", 1, (vt5 | (vt2 << 5)), rs, (int) (short) (imm14 << 2));
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction LVLQ = new Instruction(116) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "LVLQ";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "MIPS I/VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int vt1 = (insn >> 0) & 1;
/*TODO*/  //            int imm14 = (insn >> 2) & 16383;
/*TODO*/  //            int vt5 = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doLVLQ((vt5 | (vt1 << 5)), rs, (int) (short) (imm14 << 2));
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            super.compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int vt1 = (insn >> 0) & 1;
/*TODO*/  //            int imm14 = (insn >> 2) & 16383;
/*TODO*/  //            int vt5 = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmVTIMMRS("lvl", 4, (vt5 | (vt1 << 5)), rs, (int) (short) (imm14 << 2));
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction LVRQ = new Instruction(117) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "LVRQ";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "MIPS I/VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int vt1 = (insn >> 0) & 1;
/*TODO*/  //            int imm14 = (insn >> 2) & 16383;
/*TODO*/  //            int vt5 = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doLVRQ((vt5 | (vt1 << 5)), rs, (int) (short) (imm14 << 2));
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            super.compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int vt1 = (insn >> 0) & 1;
/*TODO*/  //            int imm14 = (insn >> 2) & 16383;
/*TODO*/  //            int vt5 = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmVTIMMRS("lvr", 4, (vt5 | (vt1 << 5)), rs, (int) (short) (imm14 << 2));
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction LVQ = new Instruction(118) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "LVQ";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "MIPS I/VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int vt1 = (insn >> 0) & 1;
/*TODO*/  //            int imm14 = (insn >> 2) & 16383;
/*TODO*/  //            int vt5 = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doLVQ((vt5 | (vt1 << 5)), rs, (int) (short) (imm14 << 2));
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            int vt1 = (insn >> 0) & 1;
/*TODO*/  //            int vt5 = (insn >> 16) & 31;
/*TODO*/  //            int vt = vt5 | (vt1 << 5);
/*TODO*/  //            int simm14 = context.getImm14(true);
/*TODO*/  //            int rs = context.getRsRegisterIndex();
/*TODO*/  //            final int vsize = 4;
/*TODO*/  //
/*TODO*/  //            int countSequence = 1;
/*TODO*/  //            int address = context.getCodeInstruction().getAddress();
/*TODO*/  //
/*TODO*/  //            // Compare LV.Q opcode and vt1 flag
/*TODO*/  //            final int opcodeMask = 0xFFE00003;
/*TODO*/  //            for (int i = 1; true; i++) {
/*TODO*/  //                CodeInstruction nextCodeInstruction = context.getCodeInstruction(address + i * 4);
/*TODO*/  //                boolean isSequence = false;
/*TODO*/  //                if (nextCodeInstruction != null) {
/*TODO*/  //                    int nextInsn = nextCodeInstruction.getOpcode();
/*TODO*/  //                    if (nextCodeInstruction != null && (nextInsn & opcodeMask) == (insn & opcodeMask)) {
/*TODO*/  //                        int nextSimm14 = nextCodeInstruction.getImm14(true);
/*TODO*/  //                        if (nextSimm14 == simm14 + i * 16) {
/*TODO*/  //                            int nextVt5 = (nextInsn >> 16) & 31;
/*TODO*/  //                            if (nextVt5 == vt5 + i) {
/*TODO*/  //                                isSequence = true;
/*TODO*/  //                            }
/*TODO*/  //                        }
/*TODO*/  //                    }
/*TODO*/  //                }
/*TODO*/  //
/*TODO*/  //                if (!isSequence) {
/*TODO*/  //                    break;
/*TODO*/  //                }
/*TODO*/  //                countSequence++;
/*TODO*/  //            }
/*TODO*/  //
/*TODO*/  //            if (context.compileVFPULoad(context.getRsRegisterIndex(), simm14, vt, countSequence * 4)) {
/*TODO*/  //                if (countSequence > 1) {
/*TODO*/  //                    if (Compiler.log.isDebugEnabled()) {
/*TODO*/  //                        Compiler.log.debug(String.format("lv.q sequence 0x%08X-0x%08X", address, address +
          //                        countSequence * 4 - 4));
/*TODO*/  //                    }
/*TODO*/  //
/*TODO*/  //                    // Skip the next lv.q instructions
/*TODO*/  //                    context.skipInstructions(countSequence - 1, false);
/*TODO*/  //                }
/*TODO*/  //            } else {
/*TODO*/  //                for (int n = 0; n < vsize; n++) {
/*TODO*/  //                    context.prepareVtForStoreInt(vsize, vt, n);
/*TODO*/  //                    context.memRead32(rs, simm14 + n * 4, false);
/*TODO*/  //                    context.storeVtInt(vsize, vt, n);
/*TODO*/  //                }
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int vt1 = (insn >> 0) & 1;
/*TODO*/  //            int imm14 = (insn >> 2) & 16383;
/*TODO*/  //            int vt5 = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmVTIMMRS("lv", 4, (vt5 | (vt1 << 5)), rs, (int) (short) (imm14 << 2));
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction SC = new Instruction(119) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "SC";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "ALLEGREX";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doSC(rt, rs, (int) (short) imm16);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            int rs = context.getRsRegisterIndex();
/*TODO*/  //            int simm16 = context.getImm16(true);
/*TODO*/  //            context.prepareMemWrite32(rs, simm16, false);
/*TODO*/  //            context.loadRt();
/*TODO*/  //            context.memWrite32(rs, simm16, false);
/*TODO*/  //
/*TODO*/  //            if (!context.isRtRegister0()) {
/*TODO*/  //                context.storeRt(1);
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmRTIMMRS("sc", rt, rs, (int) (short) imm16);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction SWC1 = new Instruction(120) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "SWC1";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "MIPS I/FPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int ft = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doSWC1(ft, rs, (int) (short) imm16);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            int rs = context.getRsRegisterIndex();
/*TODO*/  //            int simm16 = context.getImm16(true);
/*TODO*/  //            context.prepareMemWrite32(rs, simm16, false);
/*TODO*/  //            context.loadFt();
/*TODO*/  //            context.invokeStaticMethod(Type.getInternalName(Float.class), "floatToRawIntBits", "(F)I");
/*TODO*/  //            context.memWrite32(rs, simm16, false);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int ft = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmFTIMMRS("swc1", ft, rs, (int) (short) imm16);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction SVS = new Instruction(121) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "SVS";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "MIPS I/VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int vt2 = (insn >> 0) & 3;
/*TODO*/  //            int imm14 = (insn >> 2) & 16383;
/*TODO*/  //            int vt5 = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doSVS((vt5 | (vt2 << 5)), rs, (int) (short) (imm14 << 2));
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            int vt2 = (insn >> 0) & 3;
/*TODO*/  //            int vt5 = (insn >> 16) & 31;
/*TODO*/  //            int vt = vt5 | (vt2 << 5);
/*TODO*/  //            int simm14 = context.getImm14(true);
/*TODO*/  //            int rs = context.getRsRegisterIndex();
/*TODO*/  //            context.prepareMemWrite32(rs, simm14, false);
/*TODO*/  //            context.loadVtInt(1, vt, 0);
/*TODO*/  //            context.memWrite32(rs, simm14, false);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int vt2 = (insn >> 0) & 3;
/*TODO*/  //            int imm14 = (insn >> 2) & 16383;
/*TODO*/  //            int vt5 = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmVTIMMRS("sv", 1, (vt5 | (vt2 << 5)), rs, (int) (short) (imm14 << 2));
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction SVLQ = new Instruction(122) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "SVLQ";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "MIPS I/VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int vt1 = (insn >> 0) & 1;
/*TODO*/  //            int imm14 = (insn >> 2) & 16383;
/*TODO*/  //            int vt5 = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doSVLQ((vt5 | (vt1 << 5)), rs, (int) (short) (imm14 << 2));
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            super.compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int vt1 = (insn >> 0) & 1;
/*TODO*/  //            int imm14 = (insn >> 2) & 16383;
/*TODO*/  //            int vt5 = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmVTIMMRS("svl", 4, (vt5 | (vt1 << 5)), rs, (int) (short) (imm14 << 2));
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction SVRQ = new Instruction(123) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "SVRQ";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "MIPS I/VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int vt1 = (insn >> 0) & 1;
/*TODO*/  //            int imm14 = (insn >> 2) & 16383;
/*TODO*/  //            int vt5 = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doSVRQ((vt5 | (vt1 << 5)), rs, (int) (short) (imm14 << 2));
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            super.compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int vt1 = (insn >> 0) & 1;
/*TODO*/  //            int imm14 = (insn >> 2) & 16383;
/*TODO*/  //            int vt5 = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmVTIMMRS("svr", 4, (vt5 | (vt1 << 5)), rs, (int) (short) (imm14 << 2));
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction SVQ = new Instruction(124) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "SVQ";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "MIPS I/VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int vt1 = (insn >> 0) & 1;
/*TODO*/  //            int imm14 = (insn >> 2) & 16383;
/*TODO*/  //            int vt5 = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doSVQ((vt5 | (vt1 << 5)), rs, (int) (short) (imm14 << 2));
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            int vt1 = (insn >> 0) & 1;
/*TODO*/  //            int vt5 = (insn >> 16) & 31;
/*TODO*/  //            int vt = vt5 | (vt1 << 5);
/*TODO*/  //            int simm14 = context.getImm14(true);
/*TODO*/  //            int rs = context.getRsRegisterIndex();
/*TODO*/  //            int vsize = 4;
/*TODO*/  //
/*TODO*/  //            int countSequence = 1;
/*TODO*/  //            int address = context.getCodeInstruction().getAddress();
/*TODO*/  //
/*TODO*/  //            // Compare SV.Q opcode and vt1 flag
/*TODO*/  //            final int opcodeMask = 0xFFE00001;
/*TODO*/  //            for (int i = 1; i < 4; i++) {
/*TODO*/  //                CodeInstruction nextCodeInstruction = context.getCodeInstruction(address + i * 4);
/*TODO*/  //                boolean isSequence = false;
/*TODO*/  //                if (nextCodeInstruction != null) {
/*TODO*/  //                    int nextInsn = nextCodeInstruction.getOpcode();
/*TODO*/  //                    if (nextCodeInstruction != null && (nextInsn & opcodeMask) == (insn & opcodeMask)) {
/*TODO*/  //                        int nextSimm14 = nextCodeInstruction.getImm14(true);
/*TODO*/  //                        if (nextSimm14 == simm14 + i * 16) {
/*TODO*/  //                            int nextVt5 = (nextInsn >> 16) & 31;
/*TODO*/  //                            if (nextVt5 == vt5 + i) {
/*TODO*/  //                                isSequence = true;
/*TODO*/  //                            }
/*TODO*/  //                        }
/*TODO*/  //                    }
/*TODO*/  //                }
/*TODO*/  //
/*TODO*/  //                if (!isSequence) {
/*TODO*/  //                    break;
/*TODO*/  //                }
/*TODO*/  //                countSequence++;
/*TODO*/  //            }
/*TODO*/  //
/*TODO*/  //            if (context.compileVFPUStore(context.getRsRegisterIndex(), simm14, vt, countSequence * 4)) {
/*TODO*/  //                if (countSequence > 1) {
/*TODO*/  //                    if (Compiler.log.isDebugEnabled()) {
/*TODO*/  //                        Compiler.log.debug(String.format("   sv.q sequence 0x%08X-0x%08X", address, address
          //                        + countSequence * 4 - 4));
/*TODO*/  //                    }
/*TODO*/  //
/*TODO*/  //                    // Skip the next sv.q instructions
/*TODO*/  //                    context.skipInstructions(countSequence - 1, false);
/*TODO*/  //                }
/*TODO*/  //            } else {
/*TODO*/  //                for (int n = 0; n < vsize; n++) {
/*TODO*/  //                    context.prepareMemWrite32(rs, simm14 + n * 4, false);
/*TODO*/  //                    context.loadVtInt(vsize, vt, n);
/*TODO*/  //                    context.memWrite32(rs, simm14 + n * 4, false);
/*TODO*/  //                }
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int vt1 = (insn >> 0) & 1;
/*TODO*/  //            int imm14 = (insn >> 2) & 16383;
/*TODO*/  //            int vt5 = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmVTIMMRS("sv", 4, (vt5 | (vt1 << 5)), rs, (int) (short) (imm14 << 2));
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction VWB = new Instruction(125) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "VWB";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "MIPS I/VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            // Checked using VfpuTest: VWB.Q is equivalent to SV.Q
/*TODO*/  //            SVQ.interpret(processor, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            SVQ.compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int vt1 = (insn >> 0) & 1;
/*TODO*/  //            int imm14 = (insn >> 2) & 16383;
/*TODO*/  //            int vt5 = (insn >> 16) & 31;
/*TODO*/  //            int rs = (insn >> 21) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmVTIMMRS("vwb", 4, (vt5 | (vt1 << 5)), rs, (int) (short) (imm14 << 2));
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction ADD_S = new Instruction(126) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "ADD.S";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "FPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int fd = (insn >> 6) & 31;
/*TODO*/  //            int fs = (insn >> 11) & 31;
/*TODO*/  //            int ft = (insn >> 16) & 31;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doADDS(fd, fs, ft);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            context.prepareFdForStore();
/*TODO*/  //            context.loadFs();
/*TODO*/  //            context.loadFt();
/*TODO*/  //            context.getMethodVisitor().visitInsn(Opcodes.FADD);
/*TODO*/  //            context.storeFd();
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int fd = (insn >> 6) & 31;
/*TODO*/  //            int fs = (insn >> 11) & 31;
/*TODO*/  //            int ft = (insn >> 16) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmFDFSFT("add.s", fd, fs, ft);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction SUB_S = new Instruction(127) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "SUB.S";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "FPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int fd = (insn >> 6) & 31;
/*TODO*/  //            int fs = (insn >> 11) & 31;
/*TODO*/  //            int ft = (insn >> 16) & 31;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doSUBS(fd, fs, ft);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            context.prepareFdForStore();
/*TODO*/  //            context.loadFs();
/*TODO*/  //            context.loadFt();
/*TODO*/  //            context.getMethodVisitor().visitInsn(Opcodes.FSUB);
/*TODO*/  //            context.storeFd();
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int fd = (insn >> 6) & 31;
/*TODO*/  //            int fs = (insn >> 11) & 31;
/*TODO*/  //            int ft = (insn >> 16) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmFDFSFT("sub.s", fd, fs, ft);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction MUL_S = new Instruction(128) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "MUL.S";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "FPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int fd = (insn >> 6) & 31;
/*TODO*/  //            int fs = (insn >> 11) & 31;
/*TODO*/  //            int ft = (insn >> 16) & 31;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doMULS(fd, fs, ft);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            if (IMPLEMENT_ROUNDING_MODES) {
/*TODO*/  //                context.compileFDFSFT("doMULS");
/*TODO*/  //            } else {
/*TODO*/  //                context.prepareFdForStore();
/*TODO*/  //                context.loadFs();
/*TODO*/  //                context.loadFt();
/*TODO*/  //                context.getMethodVisitor().visitInsn(Opcodes.FMUL);
/*TODO*/  //                context.storeFd();
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int fd = (insn >> 6) & 31;
/*TODO*/  //            int fs = (insn >> 11) & 31;
/*TODO*/  //            int ft = (insn >> 16) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmFDFSFT("mul.s", fd, fs, ft);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction DIV_S = new Instruction(129) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "DIV.S";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "FPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int fd = (insn >> 6) & 31;
/*TODO*/  //            int fs = (insn >> 11) & 31;
/*TODO*/  //            int ft = (insn >> 16) & 31;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doDIVS(fd, fs, ft);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            context.prepareFdForStore();
/*TODO*/  //            context.loadFs();
/*TODO*/  //            context.loadFt();
/*TODO*/  //            context.getMethodVisitor().visitInsn(Opcodes.FDIV);
/*TODO*/  //            context.storeFd();
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int fd = (insn >> 6) & 31;
/*TODO*/  //            int fs = (insn >> 11) & 31;
/*TODO*/  //            int ft = (insn >> 16) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmFDFSFT("div.s", fd, fs, ft);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction SQRT_S = new Instruction(130) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "SQRT.S";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "FPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int fd = (insn >> 6) & 31;
/*TODO*/  //            int fs = (insn >> 11) & 31;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doSQRTS(fd, fs);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            context.prepareFdForStore();
/*TODO*/  //            context.loadFs();
/*TODO*/  //            context.getMethodVisitor().visitInsn(Opcodes.F2D);
/*TODO*/  //            context.invokeStaticMethod(Type.getInternalName(Math.class), "sqrt", "(D)D");
/*TODO*/  //            context.getMethodVisitor().visitInsn(Opcodes.D2F);
/*TODO*/  //            context.storeFd();
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int fd = (insn >> 6) & 31;
/*TODO*/  //            int fs = (insn >> 11) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmFDFS("sqrt.s", fd, fs);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction ABS_S = new Instruction(131) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "ABS.S";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "FPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int fd = (insn >> 6) & 31;
/*TODO*/  //            int fs = (insn >> 11) & 31;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doABSS(fd, fs);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            context.prepareFdForStore();
/*TODO*/  //            context.loadFs();
/*TODO*/  //            context.invokeStaticMethod(Type.getInternalName(Math.class), "abs", "(F)F");
/*TODO*/  //            context.storeFd();
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int fd = (insn >> 6) & 31;
/*TODO*/  //            int fs = (insn >> 11) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmFDFS("abs.s", fd, fs);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction MOV_S = new Instruction(132) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "MOV.S";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "FPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int fd = (insn >> 6) & 31;
/*TODO*/  //            int fs = (insn >> 11) & 31;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doMOVS(fd, fs);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            context.prepareFdForStore();
/*TODO*/  //            context.loadFs();
/*TODO*/  //            context.storeFd();
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int fd = (insn >> 6) & 31;
/*TODO*/  //            int fs = (insn >> 11) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmFDFS("mov.s", fd, fs);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction NEG_S = new Instruction(133) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "NEG.S";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "FPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int fd = (insn >> 6) & 31;
/*TODO*/  //            int fs = (insn >> 11) & 31;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doNEGS(fd, fs);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            context.prepareFdForStore();
/*TODO*/  //            context.loadFs();
/*TODO*/  //            context.getMethodVisitor().visitInsn(Opcodes.FNEG);
/*TODO*/  //            context.storeFd();
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int fd = (insn >> 6) & 31;
/*TODO*/  //            int fs = (insn >> 11) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmFDFS("neg.s", fd, fs);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction ROUND_W_S = new Instruction(134) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "ROUND.W.S";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "FPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int fd = (insn >> 6) & 31;
/*TODO*/  //            int fs = (insn >> 11) & 31;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doROUNDWS(fd, fs);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            context.prepareFdForStore();
/*TODO*/  //            context.loadFs();
/*TODO*/  //            context.invokeStaticMethod(Type.getInternalName(Math.class), "round", "(F)I");
/*TODO*/  //            context.invokeStaticMethod(Type.getInternalName(Float.class), "intBitsToFloat", "(I)F");
/*TODO*/  //            context.storeFd();
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int fd = (insn >> 6) & 31;
/*TODO*/  //            int fs = (insn >> 11) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmFDFS("round.w.s", fd, fs);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction TRUNC_W_S = new Instruction(135) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "TRUNC.W.S";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "FPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int fd = (insn >> 6) & 31;
/*TODO*/  //            int fs = (insn >> 11) & 31;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doTRUNCWS(fd, fs);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            context.prepareFdForStore();
/*TODO*/  //            context.loadFs();
/*TODO*/  //            context.getMethodVisitor().visitInsn(Opcodes.F2I);
/*TODO*/  //            context.invokeStaticMethod(Type.getInternalName(Float.class), "intBitsToFloat", "(I)F");
/*TODO*/  //            context.storeFd();
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int fd = (insn >> 6) & 31;
/*TODO*/  //            int fs = (insn >> 11) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmFDFS("trunc.w.s", fd, fs);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction CEIL_W_S = new Instruction(136) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "CEIL.W.S";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "FPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int fd = (insn >> 6) & 31;
/*TODO*/  //            int fs = (insn >> 11) & 31;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doCEILWS(fd, fs);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            context.prepareFdForStore();
/*TODO*/  //            context.loadFs();
/*TODO*/  //            context.getMethodVisitor().visitInsn(Opcodes.F2D);
/*TODO*/  //            context.invokeStaticMethod(Type.getInternalName(Math.class), "ceil", "(D)D");
/*TODO*/  //            context.getMethodVisitor().visitInsn(Opcodes.D2I);
/*TODO*/  //            context.invokeStaticMethod(Type.getInternalName(Float.class), "intBitsToFloat", "(I)F");
/*TODO*/  //            context.storeFd();
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int fd = (insn >> 6) & 31;
/*TODO*/  //            int fs = (insn >> 11) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmFDFS("ceil.w.s", fd, fs);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction FLOOR_W_S = new Instruction(137) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "FLOOR.W.S";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "FPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int fd = (insn >> 6) & 31;
/*TODO*/  //            int fs = (insn >> 11) & 31;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doFLOORWS(fd, fs);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            context.prepareFdForStore();
/*TODO*/  //            context.loadFs();
/*TODO*/  //            context.getMethodVisitor().visitInsn(Opcodes.F2D);
/*TODO*/  //            context.invokeStaticMethod(Type.getInternalName(Math.class), "floor", "(D)D");
/*TODO*/  //            context.getMethodVisitor().visitInsn(Opcodes.D2I);
/*TODO*/  //            context.invokeStaticMethod(Type.getInternalName(Float.class), "intBitsToFloat", "(I)F");
/*TODO*/  //            context.storeFd();
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int fd = (insn >> 6) & 31;
/*TODO*/  //            int fs = (insn >> 11) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmFDFS("floor.w.s", fd, fs);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction CVT_S_W = new Instruction(138) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "CVT.S.W";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "FPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int fd = (insn >> 6) & 31;
/*TODO*/  //            int fs = (insn >> 11) & 31;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doCVTSW(fd, fs);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            context.prepareFdForStore();
/*TODO*/  //            context.loadFs();
/*TODO*/  //            context.invokeStaticMethod(Type.getInternalName(Float.class), "floatToRawIntBits", "(F)I");
/*TODO*/  //            context.getMethodVisitor().visitInsn(Opcodes.I2F);
/*TODO*/  //            context.storeFd();
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int fd = (insn >> 6) & 31;
/*TODO*/  //            int fs = (insn >> 11) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmFDFS("cvt.s.w", fd, fs);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction CVT_W_S = new Instruction(139) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "CVT.W.S";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "FPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int fd = (insn >> 6) & 31;
/*TODO*/  //            int fs = (insn >> 11) & 31;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doCVTWS(fd, fs);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            super.compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int fd = (insn >> 6) & 31;
/*TODO*/  //            int fs = (insn >> 11) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmFDFS("cvt.w.s", fd, fs);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction C_COND_S = new Instruction(140) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "C.COND.S";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "FPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int fcond = (insn >> 0) & 15;
/*TODO*/  //            int fs = (insn >> 11) & 31;
/*TODO*/  //            int ft = (insn >> 16) & 31;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doCCONDS(fs, ft, fcond);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            int fcond = (insn >> 0) & 15;
/*TODO*/  //
/*TODO*/  //            Label isNaN = new Label();
/*TODO*/  //            Label isNotNaN = new Label();
/*TODO*/  //            Label continueLabel = new Label();
/*TODO*/  //            Label trueLabel = new Label();
/*TODO*/  //
/*TODO*/  //            context.prepareFcr31cForStore();
/*TODO*/  //            context.loadFt();
/*TODO*/  //            context.storeFTmp2();
/*TODO*/  //            context.loadFs();
/*TODO*/  //            context.getMethodVisitor().visitInsn(Opcodes.DUP);
/*TODO*/  //            context.storeFTmp1();
/*TODO*/  //            context.invokeStaticMethod(Type.getInternalName(Float.class), "isNaN", "(F)Z");
/*TODO*/  //            context.getMethodVisitor().visitJumpInsn(Opcodes.IFNE, isNaN);
/*TODO*/  //            context.loadFTmp2();
/*TODO*/  //            context.invokeStaticMethod(Type.getInternalName(Float.class), "isNaN", "(F)Z");
/*TODO*/  //            context.getMethodVisitor().visitJumpInsn(Opcodes.IFEQ, isNotNaN);
/*TODO*/  //            context.getMethodVisitor().visitLabel(isNaN);
/*TODO*/  //            context.getMethodVisitor().visitInsn((fcond & 1) != 0 ? Opcodes.ICONST_1 : Opcodes.ICONST_0);
/*TODO*/  //            context.getMethodVisitor().visitJumpInsn(Opcodes.GOTO, continueLabel);
/*TODO*/  //            context.getMethodVisitor().visitLabel(isNotNaN);
/*TODO*/  //            boolean equal = (fcond & 2) != 0;
/*TODO*/  //            boolean less = (fcond & 4) != 0;
/*TODO*/  //            if (!equal && !less) {
/*TODO*/  //                context.getMethodVisitor().visitInsn(Opcodes.ICONST_0);
/*TODO*/  //            } else {
/*TODO*/  //                int testOpcode = (equal ? (less ? Opcodes.IFLE : Opcodes.IFEQ) : Opcodes.IFLT);
/*TODO*/  //                context.loadFTmp1();
/*TODO*/  //                context.loadFTmp2();
/*TODO*/  //                context.getMethodVisitor().visitInsn(Opcodes.FCMPL); // FCMPG and FCMPL would produce the
          //                same result as both values are not NaN
/*TODO*/  //                context.getMethodVisitor().visitJumpInsn(testOpcode, trueLabel);
/*TODO*/  //                context.getMethodVisitor().visitInsn(Opcodes.ICONST_0);
/*TODO*/  //                context.getMethodVisitor().visitJumpInsn(Opcodes.GOTO, continueLabel);
/*TODO*/  //                context.getMethodVisitor().visitLabel(trueLabel);
/*TODO*/  //                context.getMethodVisitor().visitInsn(Opcodes.ICONST_1);
/*TODO*/  //            }
/*TODO*/  //            context.getMethodVisitor().visitLabel(continueLabel);
/*TODO*/  //            context.storeFcr31c();
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int fcond = (insn >> 0) & 15;
/*TODO*/  //            int fs = (insn >> 11) & 31;
/*TODO*/  //            int ft = (insn >> 16) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmCcondS(fcond, fs, ft);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction MFC1 = new Instruction(141, FLAG_WRITES_RT) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "MFC1";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "MIPS I/FPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int c1dr = (insn >> 11) & 31;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doMFC1(rt, c1dr);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            if (!context.isRtRegister0()) {
/*TODO*/  //                context.prepareRtForStore();
/*TODO*/  //                context.loadFCr();
/*TODO*/  //                context.invokeStaticMethod(Type.getInternalName(Float.class), "floatToRawIntBits", "(F)I");
/*TODO*/  //                context.storeRt();
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int c1dr = (insn >> 11) & 31;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmRTFS("mfc1", rt, c1dr);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction CFC1 = new Instruction(142) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "CFC1";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "MIPS I/FPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int c1cr = (insn >> 11) & 31;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doCFC1(rt, c1cr);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            super.compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int c1cr = (insn >> 11) & 31;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmRTFC("cfc1", rt, c1cr);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction MTC1 = new Instruction(143) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "MTC1";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "MIPS I/FPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int c1dr = (insn >> 11) & 31;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doMTC1(rt, c1dr);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            context.prepareFCrForStore();
/*TODO*/  //            context.loadRt();
/*TODO*/  //            context.invokeStaticMethod(Type.getInternalName(Float.class), "intBitsToFloat", "(I)F");
/*TODO*/  //            context.storeFCr();
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int c1dr = (insn >> 11) & 31;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmRTFS("mtc1", rt, c1dr);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction CTC1 = new Instruction(144) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "CTC1";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "MIPS I/FPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int c1cr = (insn >> 11) & 31;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doCTC1(rt, c1cr);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            super.compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int c1cr = (insn >> 11) & 31;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmRTFC("ctc1", rt, c1cr);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction MFC0 = new Instruction(145) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "MFC0";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "MIPS I";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int c0dr = (insn >> 11) & 31;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //
/*TODO*/  //            int value = processor.cp0.getDataRegister(c0dr);
/*TODO*/  //
/*TODO*/  //            // Manipulate some special values
/*TODO*/  //            switch (c0dr) {
/*TODO*/  //                case COP0_STATE_COUNT: // System counter
/*TODO*/  //                    value = (int) Emulator.getClock().nanoTime();
/*TODO*/  //                    break;
/*TODO*/  //            }
/*TODO*/  //
/*TODO*/  //            processor.cpu.setRegister(rt, value);
/*TODO*/  //
/*TODO*/  //            if (logCop0.isTraceEnabled()) {
/*TODO*/  //                logCop0.trace(String.format("0x%08X - mfc0 reading data register#%d(%s) having value
          //                0x%08X", processor.cpu.pc, c0dr, Common.cop0Names[c0dr], value));
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            super.compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int c0dr = (insn >> 11) & 31;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmRTC0dr("mfc0", rt, c0dr);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction CFC0 = new Instruction(146) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "CFC0";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "ALLEGREX";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int c0cr = (insn >> 11) & 31;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //
/*TODO*/  //            int value = processor.cp0.getControlRegister(c0cr);
/*TODO*/  //            processor.cpu.setRegister(rt, value);
/*TODO*/  //
/*TODO*/  //            if (logCop0.isTraceEnabled()) {
/*TODO*/  //                logCop0.trace(String.format("0x%08X - cfc0 reading control register#%d having value 0x%08X",
          //                processor.cpu.pc, c0cr, value));
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            super.compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int c0cr = (insn >> 11) & 31;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmRTC0cr("cfc0", rt, c0cr);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction MTC0 = new Instruction(147, FLAG_MODIFIES_INTERRUPT_STATE) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "MTC0";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "MIPS I";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int c0dr = (insn >> 11) & 31;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //
/*TODO*/  //            int value = processor.cpu.getRegister(rt);
/*TODO*/  //
/*TODO*/  //            if (logCop0.isTraceEnabled()) {
/*TODO*/  //                logCop0.trace(String.format("0x%08X - mtc0 setting data register#%d(%s) to value 0x%08X",
          //                processor.cpu.pc, c0dr, Common.cop0Names[c0dr], value));
/*TODO*/  //            }
/*TODO*/  //
/*TODO*/  //            switch (c0dr) {
/*TODO*/  //                case COP0_STATE_COUNT:
/*TODO*/  //                    // Count is set to 0 at boot time
/*TODO*/  //                    if (value != 0) {
/*TODO*/  //                        processor.cpu.doUNK(String.format("Unsupported mtc0 instruction for c0dr=%d(%s),
          //                        value=0x%X", c0dr, Common.cop0Names[c0dr], value));
/*TODO*/  //                    }
/*TODO*/  //                    break;
/*TODO*/  //                case COP0_STATE_COMPARE:
/*TODO*/  //                    // Compare is set to 0x80000000 at boot time
/*TODO*/  //                    if (value != 0x80000000) {
/*TODO*/  //                        processor.cpu.doUNK(String.format("Unsupported mtc0 instruction for c0dr=%d(%s),
          //                        value=0x%X", c0dr, Common.cop0Names[c0dr], value));
/*TODO*/  //                    }
/*TODO*/  //                    break;
/*TODO*/  //                case COP0_STATE_CONFIG:
/*TODO*/  //                    processor.cpu.doUNK(String.format("Unsupported mtc0 instruction for c0dr=%d(%s),
          //                    value=0x%X", c0dr, Common.cop0Names[c0dr], value));
/*TODO*/  //                    break;
/*TODO*/  //            }
/*TODO*/  //            processor.cp0.setDataRegister(c0dr, value);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            super.compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int c0dr = (insn >> 11) & 31;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmRTC0dr("mtc0", rt, c0dr);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction CTC0 = new Instruction(148) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "CTC0";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "ALLEGREX";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int c0cr = (insn >> 11) & 31;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //
/*TODO*/  //            int value = processor.cpu.getRegister(rt);
/*TODO*/  //            processor.cp0.setControlRegister(c0cr, value);
/*TODO*/  //
/*TODO*/  //            if (c0cr == 13) {
/*TODO*/  //                reboot.setLog4jMDC(processor);
/*TODO*/  //            }
/*TODO*/  //
/*TODO*/  //            if (logCop0.isTraceEnabled()) {
/*TODO*/  //                logCop0.trace(String.format("0x%08X - ctc0 setting control register#%d to value 0x%08X",
          //                processor.cpu.pc, c0cr, value));
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            super.compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int c0cr = (insn >> 11) & 31;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmRTC0cr("ctc0", rt, c0cr);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction VADD = new Instruction(149, FLAG_USES_VFPU_PFXS | FLAG_USES_VFPU_PFXT |
          //    FLAG_USES_VFPU_PFXD | FLAG_COMPILED_PFX) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "VADD";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //            int vt = (insn >> 16) & 127;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doVADD(1 + one + (two << 1), vd, vs, vt);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            context.compileVFPUInstr(null, Opcodes.FADD, null);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //            int vt = (insn >> 16) & 127;
/*TODO*/  //
/*TODO*/  //            return Common.disasmVDVSVT("vadd", 1 + one + (two << 1), vd, vs, vt);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction VSUB = new Instruction(150, FLAG_USES_VFPU_PFXS | FLAG_USES_VFPU_PFXT |
          //    FLAG_USES_VFPU_PFXD | FLAG_COMPILED_PFX) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "VSUB";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //            int vt = (insn >> 16) & 127;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doVSUB(1 + one + (two << 1), vd, vs, vt);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            context.compileVFPUInstr(null, Opcodes.FSUB, null);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //            int vt = (insn >> 16) & 127;
/*TODO*/  //
/*TODO*/  //            return Common.disasmVDVSVT("vsub", 1 + one + (two << 1), vd, vs, vt);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction VSBN = new Instruction(151, FLAG_USES_VFPU_PFXS | FLAG_USES_VFPU_PFXT |
          //    FLAG_USES_VFPU_PFXD | FLAG_COMPILED_PFX) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "VSBN";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //            int vt = (insn >> 16) & 127;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doVSBN(1 + one + (two << 1), vd, vs, vt);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            int vsize = context.getVsize();
/*TODO*/  //            if (vsize == 1) {
/*TODO*/  //                context.startPfxCompiled();
/*TODO*/  //                for (int n = 0; n < vsize; n++) {
/*TODO*/  //                    context.prepareVdForStore(n);
/*TODO*/  //                    context.loadVs(n);
/*TODO*/  //                    context.loadVtInt(n);
/*TODO*/  //                    context.invokeStaticMethod(Type.getInternalName(Math.class), "scalb", "(FI)F");
/*TODO*/  //                    context.storeVd(n);
/*TODO*/  //                }
/*TODO*/  //                context.endPfxCompiled();
/*TODO*/  //            } else {
/*TODO*/  //                // Only VSBN.S is supported
/*TODO*/  //                context.compileInterpreterInstruction();
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //            int vt = (insn >> 16) & 127;
/*TODO*/  //
/*TODO*/  //            return Common.disasmVDVSVT("vsbn", 1 + one + (two << 1), vd, vs, vt);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction VDIV = new Instruction(152, FLAG_USES_VFPU_PFXS | FLAG_USES_VFPU_PFXT |
          //    FLAG_USES_VFPU_PFXD | FLAG_COMPILED_PFX) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "VDIV";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //            int vt = (insn >> 16) & 127;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doVDIV(1 + one + (two << 1), vd, vs, vt);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            context.compileVFPUInstr(null, Opcodes.FDIV, null);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //            int vt = (insn >> 16) & 127;
/*TODO*/  //
/*TODO*/  //            return Common.disasmVDVSVT("vdiv", 1 + one + (two << 1), vd, vs, vt);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction VMUL = new Instruction(153, FLAG_USES_VFPU_PFXS | FLAG_USES_VFPU_PFXT |
          //    FLAG_USES_VFPU_PFXD | FLAG_COMPILED_PFX) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "VMUL";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //            int vt = (insn >> 16) & 127;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doVMUL(1 + one + (two << 1), vd, vs, vt);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            context.compileVFPUInstr(null, Opcodes.FMUL, null);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //            int vt = (insn >> 16) & 127;
/*TODO*/  //
/*TODO*/  //            return Common.disasmVDVSVT("vmul", 1 + one + (two << 1), vd, vs, vt);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction VDOT = new Instruction(154, FLAG_USES_VFPU_PFXS | FLAG_USES_VFPU_PFXT |
          //    FLAG_USES_VFPU_PFXD | FLAG_COMPILED_PFX) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "VDOT";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //            int vt = (insn >> 16) & 127;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doVDOT(1 + one + (two << 1), vd, vs, vt);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            // Use the interpreter if we need an accurate "dot" implementation
/*TODO*/  //            if (useAccurateVfpuDot) {
/*TODO*/  //                super.compile(context, insn);
/*TODO*/  //            } else {
/*TODO*/  //                int vsize = context.getVsize();
/*TODO*/  //                if (vsize > 1) {
/*TODO*/  //                    context.startPfxCompiled();
/*TODO*/  //                    context.prepareVdForStore(1, 0);
/*TODO*/  //                    context.loadVs(0);
/*TODO*/  //                    context.loadVt(0);
/*TODO*/  //                    context.getMethodVisitor().visitInsn(Opcodes.FMUL);
/*TODO*/  //                    for (int n = 1; n < vsize; n++) {
/*TODO*/  //                        context.loadVs(n);
/*TODO*/  //                        context.loadVt(n);
/*TODO*/  //                        context.getMethodVisitor().visitInsn(Opcodes.FMUL);
/*TODO*/  //                        context.getMethodVisitor().visitInsn(Opcodes.FADD);
/*TODO*/  //                    }
/*TODO*/  //                    context.storeVd(1, 0);
/*TODO*/  //                    context.endPfxCompiled(1);
/*TODO*/  //                } else {
/*TODO*/  //                    // Unsupported VDOT.S
/*TODO*/  //                    context.compileInterpreterInstruction();
/*TODO*/  //                }
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //            int vt = (insn >> 16) & 127;
/*TODO*/  //
/*TODO*/  //            return Common.disasmVD1VSVT("vdot", 1 + one + (two << 1), vd, vs, vt);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction VSCL = new Instruction(155, FLAG_USES_VFPU_PFXS | FLAG_USES_VFPU_PFXT |
          //    FLAG_USES_VFPU_PFXD | FLAG_COMPILED_PFX) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "VSCL";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //            int vt = (insn >> 16) & 127;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doVSCL(1 + one + (two << 1), vd, vs, vt);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            int vsize = context.getVsize();
/*TODO*/  //            if (vsize > 1) {
/*TODO*/  //                context.startPfxCompiled();
/*TODO*/  //                context.loadVt(1, 0);
/*TODO*/  //                context.storeFTmp1();
/*TODO*/  //                for (int n = 0; n < vsize; n++) {
/*TODO*/  //                    context.prepareVdForStore(n);
/*TODO*/  //                    context.loadVs(n);
/*TODO*/  //                    context.loadFTmp1();
/*TODO*/  //                    context.getMethodVisitor().visitInsn(Opcodes.FMUL);
/*TODO*/  //                    context.storeVd(n);
/*TODO*/  //                }
/*TODO*/  //                context.endPfxCompiled();
/*TODO*/  //            } else {
/*TODO*/  //                // Unsupported VSCL.S
/*TODO*/  //                context.compileInterpreterInstruction();
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //            int vt = (insn >> 16) & 127;
/*TODO*/  //
/*TODO*/  //            return Common.disasmVDVSVT1("vscl", 1 + one + (two << 1), vd, vs, vt);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction VHDP = new Instruction(156, FLAG_USES_VFPU_PFXS | FLAG_USES_VFPU_PFXT |
          //    FLAG_USES_VFPU_PFXD | FLAG_COMPILED_PFX) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "VHDP";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //            int vt = (insn >> 16) & 127;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doVHDP(1 + one + (two << 1), vd, vs, vt);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            // Use the interpreter if we need an accurate "dot" implementation
/*TODO*/  //            if (useAccurateVfpuDot) {
/*TODO*/  //                super.compile(context, insn);
/*TODO*/  //            } else {
/*TODO*/  //                int vsize = context.getVsize();
/*TODO*/  //                if (vsize > 1) {
/*TODO*/  //                    context.startPfxCompiled();
/*TODO*/  //                    context.prepareVdForStore(1, 0);
/*TODO*/  //                    context.loadVs(0);
/*TODO*/  //                    context.loadVt(0);
/*TODO*/  //                    context.getMethodVisitor().visitInsn(Opcodes.FMUL);
/*TODO*/  //                    for (int n = 1; n < vsize - 1; n++) {
/*TODO*/  //                        context.loadVs(n);
/*TODO*/  //                        context.loadVt(n);
/*TODO*/  //                        context.getMethodVisitor().visitInsn(Opcodes.FMUL);
/*TODO*/  //                        context.getMethodVisitor().visitInsn(Opcodes.FADD);
/*TODO*/  //                    }
/*TODO*/  //                    context.loadVt(vsize - 1);
/*TODO*/  //                    context.getMethodVisitor().visitInsn(Opcodes.FADD);
/*TODO*/  //                    context.storeVd(1, 0);
/*TODO*/  //                    context.endPfxCompiled(1);
/*TODO*/  //                } else {
/*TODO*/  //                    // Unsupported VHDP.S
/*TODO*/  //                    context.compileInterpreterInstruction();
/*TODO*/  //                }
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //            int vt = (insn >> 16) & 127;
/*TODO*/  //
/*TODO*/  //            return Common.disasmVD1VSVT("vhdp", 1 + one + (two << 1), vd, vs, vt);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction VCRS = new Instruction(157, FLAG_USES_VFPU_PFXS | FLAG_USES_VFPU_PFXT |
          //    FLAG_USES_VFPU_PFXD) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "VCRS";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //            int vt = (insn >> 16) & 127;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doVCRS(1 + one + (two << 1), vd, vs, vt);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            super.compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //            int vt = (insn >> 16) & 127;
/*TODO*/  //
/*TODO*/  //            return Common.disasmVDVSVT("vcrs", 1 + one + (two << 1), vd, vs, vt);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction VDET = new Instruction(158, FLAG_USES_VFPU_PFXS | FLAG_USES_VFPU_PFXT |
          //    FLAG_USES_VFPU_PFXD) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "VDET";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //            int vt = (insn >> 16) & 127;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doVDET(1 + one + (two << 1), vd, vs, vt);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            super.compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //            int vt = (insn >> 16) & 127;
/*TODO*/  //
/*TODO*/  //            return Common.disasmVD1VSVT("vdet", 1 + one + (two << 1), vd, vs, vt);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction MFV = new Instruction(159, FLAG_WRITES_RT) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "MFV";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "MIPS I/VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int imm7 = (insn >> 0) & 127;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doMFV(rt, imm7);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            if (!context.isRtRegister0()) {
/*TODO*/  //                context.prepareRtForStore();
/*TODO*/  //                context.loadVdInt(1, 0);
/*TODO*/  //                context.storeRt();
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int imm7 = (insn >> 0) & 127;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmVDRS("mfv", imm7, rt);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction MFVC = new Instruction(160, FLAG_WRITES_RT) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "MFVC";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "MIPS I/VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int imm7 = (insn >> 0) & 127;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doMFVC(rt, imm7);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            if (!context.isRtRegister0()) {
/*TODO*/  //                int imm7 = context.getImm7();
/*TODO*/  //                MethodVisitor mv = context.getMethodVisitor();
/*TODO*/  //                switch (imm7) {
/*TODO*/  //                    case 3: {
/*TODO*/  //                        context.prepareRtForStore();
/*TODO*/  //                        context.loadVcrCc(5);
/*TODO*/  //                        for (int i = 4; i >= 0; i--) {
/*TODO*/  //                            context.loadImm(1);
/*TODO*/  //                            mv.visitInsn(Opcodes.ISHL);
/*TODO*/  //                            context.loadVcrCc(i);
/*TODO*/  //                            mv.visitInsn(Opcodes.IOR);
/*TODO*/  //                        }
/*TODO*/  //                        context.storeRt();
/*TODO*/  //                        break;
/*TODO*/  //                    }
/*TODO*/  //                    default:
/*TODO*/  //                        super.compile(context, insn);
/*TODO*/  //                        break;
/*TODO*/  //                }
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int imm7 = (insn >> 0) & 127;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmRTIMM7("mfvc", rt, imm7);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction MTV = new Instruction(161) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "MTV";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "MIPS I/VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int imm7 = (insn >> 0) & 127;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doMTV(rt, imm7);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            context.prepareVdForStoreInt(1, 0);
/*TODO*/  //            context.loadRt();
/*TODO*/  //            context.storeVdInt(1, 0);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int imm7 = (insn >> 0) & 127;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmVDRS("MTV", imm7, rt);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction MTVC = new Instruction(162) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "MTVC";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "MIPS I/VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int imm7 = (insn >> 0) & 127;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doMTVC(rt, imm7);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            super.compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int imm7 = (insn >> 0) & 127;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmRTIMM7("mtvc", rt, imm7);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction VCMP = new Instruction(163, FLAG_USES_VFPU_PFXS | FLAG_USES_VFPU_PFXT |
          //    FLAG_COMPILED_PFX) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "VCMP";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int imm4 = (insn >> 0) & 15;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //            int vt = (insn >> 16) & 127;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doVCMP(1 + one + (two << 1), vs, vt, imm4);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            int cond = context.getImm4();
/*TODO*/  //            int vsize = context.getVsize();
/*TODO*/  //            MethodVisitor mv = context.getMethodVisitor();
/*TODO*/  //            boolean not = (cond & 4) != 0;
/*TODO*/  //            context.startPfxCompiled();
/*TODO*/  //            if ((cond & 8) == 0) {
/*TODO*/  //                if ((cond & 3) == 0) {
/*TODO*/  //                    int value = not ? 1 : 0;
/*TODO*/  //                    for (int n = 0; n < vsize; n++) {
/*TODO*/  //                        context.prepareVcrCcForStore(n);
/*TODO*/  //                        context.loadImm(value);
/*TODO*/  //                        context.storeVcrCc(n);
/*TODO*/  //                    }
/*TODO*/  //                    context.prepareVcrCcForStore(4);
/*TODO*/  //                    context.loadImm(value);
/*TODO*/  //                    context.storeVcrCc(4);
/*TODO*/  //                    context.prepareVcrCcForStore(5);
/*TODO*/  //                    context.loadImm(value);
/*TODO*/  //                    context.storeVcrCc(5);
/*TODO*/  //                } else {
/*TODO*/  //                    if (vsize > 1) {
/*TODO*/  //                        context.loadImm(0);
/*TODO*/  //                        context.storeTmp1();
/*TODO*/  //                        context.loadImm(1);
/*TODO*/  //                        context.storeTmp2();
/*TODO*/  //                    }
/*TODO*/  //                    for (int n = 0; n < vsize; n++) {
/*TODO*/  //                        context.prepareVcrCcForStore(n);
/*TODO*/  //                        context.loadVs(n);
/*TODO*/  //                        context.loadVt(n);
/*TODO*/  //                        // In Java, the two opcodes for float comparisons (FCMPG and FCMPL) differ
/*TODO*/  //                        // only in how they handle NaN ("not a number").
/*TODO*/  //                        // If one or both of the values is NaN, the FCMPG instruction pushes a 1,
/*TODO*/  //                        // whereas the FCMPL instruction pushes a -1.
/*TODO*/  //                        // On the PSP, comparing NaN values always returns false.
/*TODO*/  //                        // - vcmp GE  => use FCMPL (-1 will be interpreted as false)
/*TODO*/  //                        // - vcmp GT  => use FCMPL (-1 will be interpreted as false)
/*TODO*/  //                        // - vcmp LE  => use FCMPG (1 will be interpreted as false)
/*TODO*/  //                        // - vcmp LT  => use FCMPG (1 will be interpreted as false)
/*TODO*/  //                        // - vcmp EQ  => use either FCMPL or FCMPG
/*TODO*/  //                        // - vcmp NE  => use either FCMPL or FCMPG
/*TODO*/  //                        mv.visitInsn(not ? Opcodes.FCMPL : Opcodes.FCMPG);
/*TODO*/  //                        int opcodeCond = Opcodes.NOP;
/*TODO*/  //                        switch (cond & 3) {
/*TODO*/  //                            case 1:
/*TODO*/  //                                opcodeCond = not ? Opcodes.IFNE : Opcodes.IFEQ;
/*TODO*/  //                                break;
/*TODO*/  //                            case 2:
/*TODO*/  //                                opcodeCond = not ? Opcodes.IFGE : Opcodes.IFLT;
/*TODO*/  //                                break;
/*TODO*/  //                            case 3:
/*TODO*/  //                                opcodeCond = not ? Opcodes.IFGT : Opcodes.IFLE;
/*TODO*/  //                                break;
/*TODO*/  //                        }
/*TODO*/  //                        Label trueLabel = new Label();
/*TODO*/  //                        Label afterLabel = new Label();
/*TODO*/  //                        mv.visitJumpInsn(opcodeCond, trueLabel);
/*TODO*/  //                        context.loadImm(0);
/*TODO*/  //                        if (vsize > 1) {
/*TODO*/  //                            context.loadImm(0);
/*TODO*/  //                            context.storeTmp2();
/*TODO*/  //                        } else {
/*TODO*/  //                            context.prepareVcrCcForStore(4);
/*TODO*/  //                            context.loadImm(0);
/*TODO*/  //                            context.storeVcrCc(4);
/*TODO*/  //                            context.prepareVcrCcForStore(5);
/*TODO*/  //                            context.loadImm(0);
/*TODO*/  //                            context.storeVcrCc(5);
/*TODO*/  //                        }
/*TODO*/  //                        mv.visitJumpInsn(Opcodes.GOTO, afterLabel);
/*TODO*/  //                        mv.visitLabel(trueLabel);
/*TODO*/  //                        context.loadImm(1);
/*TODO*/  //                        if (vsize > 1) {
/*TODO*/  //                            context.loadImm(1);
/*TODO*/  //                            context.storeTmp1();
/*TODO*/  //                        } else {
/*TODO*/  //                            context.prepareVcrCcForStore(4);
/*TODO*/  //                            context.loadImm(1);
/*TODO*/  //                            context.storeVcrCc(4);
/*TODO*/  //                            context.prepareVcrCcForStore(5);
/*TODO*/  //                            context.loadImm(1);
/*TODO*/  //                            context.storeVcrCc(5);
/*TODO*/  //                        }
/*TODO*/  //                        mv.visitLabel(afterLabel);
/*TODO*/  //                        context.storeVcrCc(n);
/*TODO*/  //                    }
/*TODO*/  //                    if (vsize > 1) {
/*TODO*/  //                        context.prepareVcrCcForStore(4);
/*TODO*/  //                        context.loadTmp1();
/*TODO*/  //                        context.storeVcrCc(4);
/*TODO*/  //                        context.prepareVcrCcForStore(5);
/*TODO*/  //                        context.loadTmp2();
/*TODO*/  //                        context.storeVcrCc(5);
/*TODO*/  //                    }
/*TODO*/  //                }
/*TODO*/  //            } else {
/*TODO*/  //                if (vsize > 1) {
/*TODO*/  //                    context.loadImm(0);
/*TODO*/  //                    context.storeTmp1();
/*TODO*/  //                    context.loadImm(1);
/*TODO*/  //                    context.storeTmp2();
/*TODO*/  //                }
/*TODO*/  //                for (int n = 0; n < vsize; n++) {
/*TODO*/  //                    context.prepareVcrCcForStore(n);
/*TODO*/  //                    context.loadVs(n);
/*TODO*/  //                    boolean updateOrAnd = false;
/*TODO*/  //                    switch (cond & 3) {
/*TODO*/  //                        case 0: {
/*TODO*/  //                            context.invokeStaticMethod(Type.getInternalName(Math.class), "abs", "(F)F");
/*TODO*/  //                            mv.visitInsn(Opcodes.FCONST_0);
/*TODO*/  //                            mv.visitInsn(Opcodes.FCMPL); // Use FCMPL or FCMPG, it doesn't matter for
          //                            testing NE or EQ
/*TODO*/  //                            Label trueLabel = new Label();
/*TODO*/  //                            Label afterLabel = new Label();
/*TODO*/  //                            mv.visitJumpInsn(not ? Opcodes.IFNE : Opcodes.IFEQ, trueLabel);
/*TODO*/  //                            context.loadImm(0);
/*TODO*/  //                            if (vsize > 1) {
/*TODO*/  //                                context.loadImm(0);
/*TODO*/  //                                context.storeTmp2();
/*TODO*/  //                            } else {
/*TODO*/  //                                context.prepareVcrCcForStore(4);
/*TODO*/  //                                context.loadImm(0);
/*TODO*/  //                                context.storeVcrCc(4);
/*TODO*/  //                                context.prepareVcrCcForStore(5);
/*TODO*/  //                                context.loadImm(0);
/*TODO*/  //                                context.storeVcrCc(5);
/*TODO*/  //                            }
/*TODO*/  //                            mv.visitJumpInsn(Opcodes.GOTO, afterLabel);
/*TODO*/  //                            mv.visitLabel(trueLabel);
/*TODO*/  //                            context.loadImm(1);
/*TODO*/  //                            if (vsize > 1) {
/*TODO*/  //                                context.loadImm(1);
/*TODO*/  //                                context.storeTmp1();
/*TODO*/  //                            } else {
/*TODO*/  //                                context.prepareVcrCcForStore(4);
/*TODO*/  //                                context.loadImm(1);
/*TODO*/  //                                context.storeVcrCc(4);
/*TODO*/  //                                context.prepareVcrCcForStore(5);
/*TODO*/  //                                context.loadImm(1);
/*TODO*/  //                                context.storeVcrCc(5);
/*TODO*/  //                            }
/*TODO*/  //                            mv.visitLabel(afterLabel);
/*TODO*/  //                            break;
/*TODO*/  //                        }
/*TODO*/  //                        case 1: {
/*TODO*/  //                            context.invokeStaticMethod(Type.getInternalName(Float.class), "isNaN", "(F)Z");
/*TODO*/  //                            updateOrAnd = true;
/*TODO*/  //                            break;
/*TODO*/  //                        }
/*TODO*/  //                        case 2: {
/*TODO*/  //                            context.invokeStaticMethod(Type.getInternalName(Float.class), "isInfinite",
          //                            "(F)Z");
/*TODO*/  //                            updateOrAnd = true;
/*TODO*/  //                            break;
/*TODO*/  //                        }
/*TODO*/  //                        case 3: {
/*TODO*/  //                            mv.visitInsn(Opcodes.DUP);
/*TODO*/  //                            context.invokeStaticMethod(Type.getInternalName(Float.class), "isNaN", "(F)Z");
/*TODO*/  //                            mv.visitInsn(Opcodes.SWAP);
/*TODO*/  //                            context.invokeStaticMethod(Type.getInternalName(Float.class), "isInfinite",
          //                            "(F)Z");
/*TODO*/  //                            mv.visitInsn(Opcodes.IOR);
/*TODO*/  //                            updateOrAnd = true;
/*TODO*/  //                            break;
/*TODO*/  //                        }
/*TODO*/  //                    }
/*TODO*/  //
/*TODO*/  //                    if (updateOrAnd) {
/*TODO*/  //                        if (not) {
/*TODO*/  //                            context.loadImm(1);
/*TODO*/  //                            mv.visitInsn(Opcodes.IXOR);
/*TODO*/  //                        }
/*TODO*/  //
/*TODO*/  //                        if (vsize > 1) {
/*TODO*/  //                            mv.visitInsn(Opcodes.DUP);
/*TODO*/  //                            context.loadTmp1();
/*TODO*/  //                            mv.visitInsn(Opcodes.IOR);
/*TODO*/  //                            context.storeTmp1();
/*TODO*/  //
/*TODO*/  //                            mv.visitInsn(Opcodes.DUP);
/*TODO*/  //                            context.loadTmp2();
/*TODO*/  //                            mv.visitInsn(Opcodes.IAND);
/*TODO*/  //                            context.storeTmp2();
/*TODO*/  //                        } else {
/*TODO*/  //                            mv.visitInsn(Opcodes.DUP);
/*TODO*/  //                            context.storeVcrCc(4);
/*TODO*/  //
/*TODO*/  //                            mv.visitInsn(Opcodes.DUP);
/*TODO*/  //                            context.storeVcrCc(5);
/*TODO*/  //                        }
/*TODO*/  //                    }
/*TODO*/  //
/*TODO*/  //                    context.storeVcrCc(n);
/*TODO*/  //                }
/*TODO*/  //                if (vsize > 1) {
/*TODO*/  //                    context.prepareVcrCcForStore(4);
/*TODO*/  //                    context.loadTmp1();
/*TODO*/  //                    context.storeVcrCc(4);
/*TODO*/  //                    context.prepareVcrCcForStore(5);
/*TODO*/  //                    context.loadTmp2();
/*TODO*/  //                    context.storeVcrCc(5);
/*TODO*/  //                }
/*TODO*/  //            }
/*TODO*/  //            context.endPfxCompiled();
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int imm4 = (insn >> 0) & 15;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //            int vt = (insn >> 16) & 127;
/*TODO*/  //
/*TODO*/  //            return Common.disasmVCMP("vcmp", 1 + one + (two << 1), imm4, vs, vt);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction VMIN = new Instruction(164, FLAG_USES_VFPU_PFXS | FLAG_USES_VFPU_PFXT |
          //    FLAG_USES_VFPU_PFXD | FLAG_COMPILED_PFX) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "VMIN";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //            int vt = (insn >> 16) & 127;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doVMIN(1 + one + (two << 1), vd, vs, vt);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            context.compileVFPUInstr(null, Opcodes.NOP, "min");
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //            int vt = (insn >> 16) & 127;
/*TODO*/  //
/*TODO*/  //            return Common.disasmVDVSVT("vmin", 1 + one + (two << 1), vd, vs, vt);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction VMAX = new Instruction(165, FLAG_USES_VFPU_PFXS | FLAG_USES_VFPU_PFXT |
          //    FLAG_USES_VFPU_PFXD | FLAG_COMPILED_PFX) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "VMAX";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //            int vt = (insn >> 16) & 127;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doVMAX(1 + one + (two << 1), vd, vs, vt);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            context.compileVFPUInstr(null, Opcodes.NOP, "max");
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //            int vt = (insn >> 16) & 127;
/*TODO*/  //
/*TODO*/  //            return Common.disasmVDVSVT("vmax", 1 + one + (two << 1), vd, vs, vt);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction VSCMP = new Instruction(166, FLAG_USES_VFPU_PFXS | FLAG_USES_VFPU_PFXT |
          //    FLAG_USES_VFPU_PFXD) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "VSCMP";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //            int vt = (insn >> 16) & 127;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doVSCMP(1 + one + (two << 1), vd, vs, vt);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            super.compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //            int vt = (insn >> 16) & 127;
/*TODO*/  //
/*TODO*/  //            return Common.disasmVDVSVT("vscmp", 1 + one + (two << 1), vd, vs, vt);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction VSGE = new Instruction(167, FLAG_USES_VFPU_PFXS | FLAG_USES_VFPU_PFXT |
          //    FLAG_USES_VFPU_PFXD | FLAG_COMPILED_PFX) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "VSGE";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //            int vt = (insn >> 16) & 127;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doVSGE(1 + one + (two << 1), vd, vs, vt);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            int vsize = context.getVsize();
/*TODO*/  //            context.startPfxCompiled();
/*TODO*/  //            MethodVisitor mv = context.getMethodVisitor();
/*TODO*/  //            for (int n = 0; n < vsize; n++) {
/*TODO*/  //                context.prepareVdForStore(n);
/*TODO*/  //                context.loadVs(n);
/*TODO*/  //                context.loadVt(n);
/*TODO*/  //                mv.visitInsn(Opcodes.FCMPL); // Use FCMPL, not FCMPG: NaN has to return false.
/*TODO*/  //                Label trueLabel = new Label();
/*TODO*/  //                Label afterLabel = new Label();
/*TODO*/  //                mv.visitJumpInsn(Opcodes.IFGE, trueLabel);
/*TODO*/  //                mv.visitInsn(Opcodes.FCONST_0);
/*TODO*/  //                mv.visitJumpInsn(Opcodes.GOTO, afterLabel);
/*TODO*/  //                mv.visitLabel(trueLabel);
/*TODO*/  //                mv.visitInsn(Opcodes.FCONST_1);
/*TODO*/  //                mv.visitLabel(afterLabel);
/*TODO*/  //                context.storeVd(n);
/*TODO*/  //            }
/*TODO*/  //            context.endPfxCompiled();
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //            int vt = (insn >> 16) & 127;
/*TODO*/  //
/*TODO*/  //            return Common.disasmVDVSVT("vsge", 1 + one + (two << 1), vd, vs, vt);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction VSLT = new Instruction(168, FLAG_USES_VFPU_PFXS | FLAG_USES_VFPU_PFXT |
          //    FLAG_USES_VFPU_PFXD | FLAG_COMPILED_PFX) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "VSLT";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //            int vt = (insn >> 16) & 127;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doVSLT(1 + one + (two << 1), vd, vs, vt);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            int vsize = context.getVsize();
/*TODO*/  //            context.startPfxCompiled();
/*TODO*/  //            MethodVisitor mv = context.getMethodVisitor();
/*TODO*/  //            for (int n = 0; n < vsize; n++) {
/*TODO*/  //                context.prepareVdForStore(n);
/*TODO*/  //                context.loadVs(n);
/*TODO*/  //                context.loadVt(n);
/*TODO*/  //                mv.visitInsn(Opcodes.FCMPG); // Use FCMPG, not FCMPL: NaN has to return false
/*TODO*/  //                Label trueLabel = new Label();
/*TODO*/  //                Label afterLabel = new Label();
/*TODO*/  //                mv.visitJumpInsn(Opcodes.IFLT, trueLabel);
/*TODO*/  //                mv.visitInsn(Opcodes.FCONST_0);
/*TODO*/  //                mv.visitJumpInsn(Opcodes.GOTO, afterLabel);
/*TODO*/  //                mv.visitLabel(trueLabel);
/*TODO*/  //                mv.visitInsn(Opcodes.FCONST_1);
/*TODO*/  //                mv.visitLabel(afterLabel);
/*TODO*/  //                context.storeVd(n);
/*TODO*/  //            }
/*TODO*/  //            context.endPfxCompiled();
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //            int vt = (insn >> 16) & 127;
/*TODO*/  //
/*TODO*/  //            return Common.disasmVDVSVT("vslt", 1 + one + (two << 1), vd, vs, vt);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction VMOV = new Instruction(169, FLAG_USES_VFPU_PFXS | FLAG_USES_VFPU_PFXD |
          //    FLAG_CONSUMES_VFPU_PFXT | FLAG_COMPILED_PFX) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "VMOV";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doVMOV(1 + one + (two << 1), vd, vs);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            context.compileVFPUInstr(null, Opcodes.NOP, null);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //
/*TODO*/  //            return Common.disasmVDVS("vmov", 1 + one + (two << 1), vd, vs);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction VABS = new Instruction(170, FLAG_USES_VFPU_PFXS | FLAG_USES_VFPU_PFXD |
          //    FLAG_COMPILED_PFX) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "VABS";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doVABS(1 + one + (two << 1), vd, vs);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            context.compileVFPUInstr(null, Opcodes.NOP, "abs");
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //
/*TODO*/  //            return Common.disasmVDVS("vabs", 1 + one + (two << 1), vd, vs);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction VNEG = new Instruction(171, FLAG_USES_VFPU_PFXS | FLAG_USES_VFPU_PFXD |
          //    FLAG_COMPILED_PFX) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "VNEG";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doVNEG(1 + one + (two << 1), vd, vs);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            context.compileVFPUInstr(null, Opcodes.FNEG, null);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //
/*TODO*/  //            return Common.disasmVDVS("vneg", 1 + one + (two << 1), vd, vs);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction VIDT = new Instruction(172, FLAG_USES_VFPU_PFXD | FLAG_COMPILED_PFX) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "VIDT";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doVIDT(1 + one + (two << 1), vd);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            context.startPfxCompiled();
/*TODO*/  //            int vsize = context.getVsize();
/*TODO*/  //            int id = context.getVdRegisterIndex() % vsize;
/*TODO*/  //            for (int n = 0; n < vsize; n++) {
/*TODO*/  //                context.prepareVdForStore(n);
/*TODO*/  //                context.getMethodVisitor().visitInsn(id == n ? Opcodes.FCONST_1 : Opcodes.FCONST_0);
/*TODO*/  //                context.storeVd(n);
/*TODO*/  //            }
/*TODO*/  //            context.endPfxCompiled();
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //
/*TODO*/  //            return Common.disasmVD("vidt", 1 + one + (two << 1), vd);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction VSAT0 = new Instruction(173, FLAG_USES_VFPU_PFXS | FLAG_USES_VFPU_PFXD |
          //    FLAG_COMPILED_PFX) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "VSAT0";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doVSAT0(1 + one + (two << 1), vd, vs);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            int vsize = context.getVsize();
/*TODO*/  //            MethodVisitor mv = context.getMethodVisitor();
/*TODO*/  //            context.startPfxCompiled();
/*TODO*/  //            for (int n = 0; n < vsize; n++) {
/*TODO*/  //                // float stackValue = vs[n];
/*TODO*/  //                // if (stackValue <= 0.f) {
/*TODO*/  //                //     stackValue = 0.f;
/*TODO*/  //                // } else if (stackValue > 1.f) {
/*TODO*/  //                //     stackValue = 1.f;
/*TODO*/  //                // }
/*TODO*/  //                // vd[n] = stackValue;
/*TODO*/  //                context.prepareVdForStore(n);
/*TODO*/  //                context.loadVs(n);
/*TODO*/  //                mv.visitInsn(Opcodes.DUP);
/*TODO*/  //                mv.visitLdcInsn(0.f);
/*TODO*/  //                mv.visitInsn(Opcodes.FCMPG); // Use FCMPG, not FCMPL: NaN has to be left unchanged
/*TODO*/  //                Label limitLabel = new Label();
/*TODO*/  //                Label afterLabel = new Label();
/*TODO*/  //                mv.visitJumpInsn(Opcodes.IFGT, limitLabel);
/*TODO*/  //                mv.visitInsn(Opcodes.POP);
/*TODO*/  //                mv.visitLdcInsn(0.f);
/*TODO*/  //                mv.visitJumpInsn(Opcodes.GOTO, afterLabel);
/*TODO*/  //                mv.visitLabel(limitLabel);
/*TODO*/  //                mv.visitInsn(Opcodes.DUP);
/*TODO*/  //                mv.visitLdcInsn(1.f);
/*TODO*/  //                mv.visitInsn(Opcodes.FCMPL); // Use FCMPL, not FCMPG: NaN has to be left unchanged
/*TODO*/  //                mv.visitJumpInsn(Opcodes.IFLE, afterLabel);
/*TODO*/  //                mv.visitInsn(Opcodes.POP);
/*TODO*/  //                mv.visitLdcInsn(1.f);
/*TODO*/  //                mv.visitLabel(afterLabel);
/*TODO*/  //                context.storeVd(n);
/*TODO*/  //            }
/*TODO*/  //            context.endPfxCompiled();
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //
/*TODO*/  //            return Common.disasmVDVS("vsat0", 1 + one + (two << 1), vd, vs);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction VSAT1 = new Instruction(174, FLAG_USES_VFPU_PFXS | FLAG_USES_VFPU_PFXD |
          //    FLAG_COMPILED_PFX) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "VSAT1";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doVSAT1(1 + one + (two << 1), vd, vs);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            int vsize = context.getVsize();
/*TODO*/  //            MethodVisitor mv = context.getMethodVisitor();
/*TODO*/  //            context.startPfxCompiled();
/*TODO*/  //            for (int n = 0; n < vsize; n++) {
/*TODO*/  //                // float stackValue = vs[n];
/*TODO*/  //                // if (stackValue <= -1.f) {
/*TODO*/  //                //     stackValue = -1.f;
/*TODO*/  //                // } else if (stackValue > 1.f) {
/*TODO*/  //                //     stackValue = 1.f;
/*TODO*/  //                // }
/*TODO*/  //                // vd[n] = stackValue;
/*TODO*/  //                context.prepareVdForStore(n);
/*TODO*/  //                context.loadVs(n);
/*TODO*/  //                mv.visitInsn(Opcodes.DUP);
/*TODO*/  //                mv.visitLdcInsn(-1.f);
/*TODO*/  //                mv.visitInsn(Opcodes.FCMPG); // Use FCMPG, not FCMPL: NaN has to be left unchanged
/*TODO*/  //                Label limitLabel = new Label();
/*TODO*/  //                Label afterLabel = new Label();
/*TODO*/  //                mv.visitJumpInsn(Opcodes.IFGT, limitLabel);
/*TODO*/  //                mv.visitInsn(Opcodes.POP);
/*TODO*/  //                mv.visitLdcInsn(-1.f);
/*TODO*/  //                mv.visitJumpInsn(Opcodes.GOTO, afterLabel);
/*TODO*/  //                mv.visitLabel(limitLabel);
/*TODO*/  //                mv.visitInsn(Opcodes.DUP);
/*TODO*/  //                mv.visitLdcInsn(1.f);
/*TODO*/  //                mv.visitInsn(Opcodes.FCMPL); // Use FCMPL, not FCMPG: NaN has to be left unchanged
/*TODO*/  //                mv.visitJumpInsn(Opcodes.IFLE, afterLabel);
/*TODO*/  //                mv.visitInsn(Opcodes.POP);
/*TODO*/  //                mv.visitLdcInsn(1.f);
/*TODO*/  //                mv.visitLabel(afterLabel);
/*TODO*/  //                context.storeVd(n);
/*TODO*/  //            }
/*TODO*/  //            context.endPfxCompiled();
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //
/*TODO*/  //            return Common.disasmVDVS("vsat1", 1 + one + (two << 1), vd, vs);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction VZERO = new Instruction(175, FLAG_USES_VFPU_PFXD | FLAG_COMPILED_PFX) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "VZERO";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doVZERO(1 + one + (two << 1), vd);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            context.startPfxCompiled();
/*TODO*/  //            int vsize = context.getVsize();
/*TODO*/  //            for (int n = 0; n < vsize; n++) {
/*TODO*/  //                context.prepareVdForStore(n);
/*TODO*/  //                context.getMethodVisitor().visitInsn(Opcodes.FCONST_0);
/*TODO*/  //                context.storeVd(n);
/*TODO*/  //            }
/*TODO*/  //            context.endPfxCompiled();
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //
/*TODO*/  //            return Common.disasmVD("vzero", 1 + one + (two << 1), vd);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction VONE = new Instruction(176, FLAG_USES_VFPU_PFXD | FLAG_COMPILED_PFX) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "VONE";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doVONE(1 + one + (two << 1), vd);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            context.startPfxCompiled();
/*TODO*/  //            int vsize = context.getVsize();
/*TODO*/  //            for (int n = 0; n < vsize; n++) {
/*TODO*/  //                context.prepareVdForStore(n);
/*TODO*/  //                context.getMethodVisitor().visitInsn(Opcodes.FCONST_1);
/*TODO*/  //                context.storeVd(n);
/*TODO*/  //            }
/*TODO*/  //            context.endPfxCompiled();
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //
/*TODO*/  //            return Common.disasmVD("vone", 1 + one + (two << 1), vd);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction VRCP = new Instruction(177, FLAG_USES_VFPU_PFXS | FLAG_USES_VFPU_PFXD |
          //    FLAG_COMPILED_PFX) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "VRCP";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doVRCP(1 + one + (two << 1), vd, vs);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            context.compileVFPUInstr(1.0f, Opcodes.FDIV, null);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //
/*TODO*/  //            return Common.disasmVDVS("vrcp", 1 + one + (two << 1), vd, vs);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction VRSQ = new Instruction(178, FLAG_USES_VFPU_PFXS | FLAG_USES_VFPU_PFXD |
          //    FLAG_COMPILED_PFX) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "VRSQ";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doVRSQ(1 + one + (two << 1), vd, vs);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            context.compileVFPUInstr(1.0f, Opcodes.FDIV, "sqrt");
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //
/*TODO*/  //            return Common.disasmVDVS("vrsq", 1 + one + (two << 1), vd, vs);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction VSIN = new Instruction(179, FLAG_USES_VFPU_PFXS | FLAG_USES_VFPU_PFXD) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "VSIN";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doVSIN(1 + one + (two << 1), vd, vs);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            super.compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //
/*TODO*/  //            return Common.disasmVDVS("vsin", 1 + one + (two << 1), vd, vs);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction VCOS = new Instruction(180, FLAG_USES_VFPU_PFXS | FLAG_USES_VFPU_PFXD) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "VCOS";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doVCOS(1 + one + (two << 1), vd, vs);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            super.compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //
/*TODO*/  //            return Common.disasmVDVS("vcos", 1 + one + (two << 1), vd, vs);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction VEXP2 = new Instruction(181, FLAG_USES_VFPU_PFXS | FLAG_USES_VFPU_PFXD)
          //    {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "VEXP2";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doVEXP2(1 + one + (two << 1), vd, vs);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            super.compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //
/*TODO*/  //            return Common.disasmVDVS("vexp2", 1 + one + (two << 1), vd, vs);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction VLOG2 = new Instruction(182, FLAG_USES_VFPU_PFXS | FLAG_USES_VFPU_PFXD)
          //    {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "VLOG2";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doVLOG2(1 + one + (two << 1), vd, vs);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            super.compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //
/*TODO*/  //            return Common.disasmVDVS("vlog2", 1 + one + (two << 1), vd, vs);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction VSQRT = new Instruction(183, FLAG_USES_VFPU_PFXS | FLAG_USES_VFPU_PFXD |
          //    FLAG_COMPILED_PFX) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "VSQRT";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doVSQRT(1 + one + (two << 1), vd, vs);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            context.compileVFPUInstr(null, Opcodes.NOP, "sqrt");
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //
/*TODO*/  //            return Common.disasmVDVS("vsqrt", 1 + one + (two << 1), vd, vs);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction VASIN = new Instruction(184, FLAG_USES_VFPU_PFXS | FLAG_USES_VFPU_PFXD)
          //    {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "VASIN";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doVASIN(1 + one + (two << 1), vd, vs);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            super.compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //
/*TODO*/  //            return Common.disasmVDVS("vasin", 1 + one + (two << 1), vd, vs);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction VNRCP = new Instruction(185, FLAG_USES_VFPU_PFXS | FLAG_USES_VFPU_PFXD)
          //    {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "VNRCP";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doVNRCP(1 + one + (two << 1), vd, vs);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            super.compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //
/*TODO*/  //            return Common.disasmVDVS("vnrcp", 1 + one + (two << 1), vd, vs);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction VNSIN = new Instruction(186, FLAG_USES_VFPU_PFXS | FLAG_USES_VFPU_PFXD)
          //    {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "VNSIN";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doVNSIN(1 + one + (two << 1), vd, vs);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            super.compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //
/*TODO*/  //            return Common.disasmVDVS("vnsin", 1 + one + (two << 1), vd, vs);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction VREXP2 = new Instruction(187, FLAG_USES_VFPU_PFXS | FLAG_USES_VFPU_PFXD)
          //    {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "VREXP2";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doVREXP2(1 + one + (two << 1), vd, vs);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            super.compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //
/*TODO*/  //            return Common.disasmVDVS("vrexp2", 1 + one + (two << 1), vd, vs);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction VRNDS = new Instruction(188, FLAG_USES_VFPU_PFXS) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "VRNDS";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doVRNDS(1 + one + (two << 1), vs);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            super.compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //
/*TODO*/  //            return Common.disasmVS("vrnds", 1 + one + (two << 1), vs);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction VRNDI = new Instruction(189, FLAG_USES_VFPU_PFXD) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "VRNDI";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doVRNDI(1 + one + (two << 1), vd);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            super.compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //
/*TODO*/  //            return Common.disasmVD("vrndi", 1 + one + (two << 1), vd);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction VRNDF1 = new Instruction(190, FLAG_USES_VFPU_PFXD) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "VRNDF1";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doVRNDF1(1 + one + (two << 1), vd);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            super.compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //
/*TODO*/  //            return Common.disasmVD("vrndf1", 1 + one + (two << 1), vd);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction VRNDF2 = new Instruction(191, FLAG_USES_VFPU_PFXD) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "VRNDF2";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doVRNDF2(1 + one + (two << 1), vd);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            super.compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //
/*TODO*/  //            return Common.disasmVD("vrndf2", 1 + one + (two << 1), vd);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction VF2H = new Instruction(192, FLAG_USES_VFPU_PFXS | FLAG_USES_VFPU_PFXD) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "VF2H";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doVF2H(1 + one + (two << 1), vd, vs);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            super.compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //
/*TODO*/  //            return Common.disasmVDVS("vf2h", 1 + one + (two << 1), vd, vs);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction VH2F = new Instruction(193, FLAG_USES_VFPU_PFXS | FLAG_USES_VFPU_PFXD) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "VH2F";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doVH2F(1 + one + (two << 1), vd, vs);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            super.compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //
/*TODO*/  //            return Common.disasmVDVS("vh2f", 1 + one + (two << 1), vd, vs);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction VSBZ = new Instruction(194) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "VSBZ";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doVSBZ(1 + one + (two << 1), vd, vs);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            super.compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //
/*TODO*/  //            return Common.disasmVDVS("VSBZ", 1 + one + (two << 1), vd, vs);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction VLGB = new Instruction(195) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "VLGB";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doVLGB(1 + one + (two << 1), vd, vs);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            super.compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //
/*TODO*/  //            return Common.disasmVDVS("vlgb", 1 + one + (two << 1), vd, vs);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction VUC2I = new Instruction(196, FLAG_USES_VFPU_PFXS | FLAG_USES_VFPU_PFXD)
          //    {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "VUC2I";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doVUC2I(1 + one + (two << 1), vd, vs);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            super.compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //
/*TODO*/  //            return Common.disasmVDVS("vuc2i", 1 + one + (two << 1), 4, vd, vs);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction VC2I = new Instruction(197, FLAG_USES_VFPU_PFXS | FLAG_USES_VFPU_PFXD) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "VC2I";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doVC2I(1 + one + (two << 1), vd, vs);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            super.compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //
/*TODO*/  //            return Common.disasmVDVS("VC2I", 1 + one + (two << 1), 4, vd, vs);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction VUS2I = new Instruction(198, FLAG_USES_VFPU_PFXS | FLAG_USES_VFPU_PFXD)
          //    {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "VUS2I";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doVUS2I(1 + one + (two << 1), vd, vs);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            super.compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //
/*TODO*/  //            return Common.disasmVDVS("vus2i", 1 + one + (two << 1), 1 + (one << 1), vd, vs);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction VS2I = new Instruction(199, FLAG_USES_VFPU_PFXS | FLAG_USES_VFPU_PFXD) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "VS2I";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doVS2I(1 + one + (two << 1), vd, vs);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            super.compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //
/*TODO*/  //            return Common.disasmVDVS("vs2i", 1 + one + (two << 1), 1 + (one << 1), vd, vs);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction VI2UC = new Instruction(200, FLAG_USES_VFPU_PFXS | FLAG_USES_VFPU_PFXD |
          //    FLAG_COMPILED_PFX) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "VI2UC";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doVI2UC(1 + one + (two << 1), vd, vs);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            final int vsize = context.getVsize();
/*TODO*/  //            if (vsize == 4) {
/*TODO*/  //                MethodVisitor mv = context.getMethodVisitor();
/*TODO*/  //                context.startPfxCompiled(false);
/*TODO*/  //                context.prepareVdForStoreInt(1, 0);
/*TODO*/  //                for (int n = 0; n < vsize; n++) {
/*TODO*/  //                    context.loadVsInt(n);
/*TODO*/  //                    mv.visitInsn(Opcodes.DUP);
/*TODO*/  //                    Label afterLabel = new Label();
/*TODO*/  //                    Label negativeLabel = new Label();
/*TODO*/  //                    mv.visitJumpInsn(Opcodes.IFLT, negativeLabel);
/*TODO*/  //                    context.loadImm(23);
/*TODO*/  //                    mv.visitInsn(Opcodes.ISHR);
/*TODO*/  //                    if (n > 0) {
/*TODO*/  //                        context.loadImm(n * 8);
/*TODO*/  //                        mv.visitInsn(Opcodes.ISHL);
/*TODO*/  //                        mv.visitInsn(Opcodes.IOR);
/*TODO*/  //                    }
/*TODO*/  //                    mv.visitJumpInsn(Opcodes.GOTO, afterLabel);
/*TODO*/  //                    mv.visitLabel(negativeLabel);
/*TODO*/  //                    mv.visitInsn(Opcodes.POP);
/*TODO*/  //                    if (n == 0) {
/*TODO*/  //                        context.loadImm(0);
/*TODO*/  //                    }
/*TODO*/  //                    mv.visitLabel(afterLabel);
/*TODO*/  //                }
/*TODO*/  //                context.storeVdInt(1, 0);
/*TODO*/  //                context.endPfxCompiled(1, false);
/*TODO*/  //            } else {
/*TODO*/  //                // Only supported VI2UC.Q
/*TODO*/  //                context.compileInterpreterInstruction();
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //
/*TODO*/  //            return Common.disasmVD1VS("vi2uc", 1 + one + (two << 1), vd, vs);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction VI2C = new Instruction(201, FLAG_USES_VFPU_PFXS | FLAG_USES_VFPU_PFXD) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "VI2C";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doVI2C(1 + one + (two << 1), vd, vs);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            super.compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //
/*TODO*/  //            return Common.disasmVD1VS("vi2c", 1 + one + (two << 1), vd, vs);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction VI2US = new Instruction(202, FLAG_USES_VFPU_PFXS | FLAG_USES_VFPU_PFXD)
          //    {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "VI2US";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doVI2US(1 + one + (two << 1), vd, vs);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            super.compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //
/*TODO*/  //            return Common.disasmVDVS("vi2us", 1 + one + (two << 1), 1 + two, vd, vs);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction VI2S = new Instruction(203, FLAG_USES_VFPU_PFXS | FLAG_USES_VFPU_PFXD) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "VI2S";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doVI2S(1 + one + (two << 1), vd, vs);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            super.compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //
/*TODO*/  //            return Common.disasmVDVS("vi2s", 1 + one + (two << 1), 1 + two, vd, vs);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction VSRT1 = new Instruction(204, FLAG_USES_VFPU_PFXS | FLAG_USES_VFPU_PFXD)
          //    {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "VSRT1";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doVSRT1(1 + one + (two << 1), vd, vs);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            super.compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //
/*TODO*/  //            return Common.disasmVDVS("vsrt1", 1 + one + (two << 1), vd, vs);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction VSRT2 = new Instruction(205, FLAG_USES_VFPU_PFXS | FLAG_USES_VFPU_PFXD)
          //    {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "VSRT2";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doVSRT2(1 + one + (two << 1), vd, vs);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            super.compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //
/*TODO*/  //            return Common.disasmVDVS("vsrt2", 1 + one + (two << 1), vd, vs);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction VBFY1 = new Instruction(206, FLAG_USES_VFPU_PFXS | FLAG_USES_VFPU_PFXD)
          //    {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "VBFY1";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doVBFY1(1 + one + (two << 1), vd, vs);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            super.compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //
/*TODO*/  //            return Common.disasmVDVS("vbfy1", 1 + one + (two << 1), vd, vs);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction VBFY2 = new Instruction(207, FLAG_USES_VFPU_PFXS | FLAG_USES_VFPU_PFXD)
          //    {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "VBFY2";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doVBFY2(1 + one + (two << 1), vd, vs);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            super.compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //
/*TODO*/  //            return Common.disasmVDVS("vbfy2", 1 + one + (two << 1), vd, vs);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction VOCP = new Instruction(208, FLAG_USES_VFPU_PFXS | FLAG_USES_VFPU_PFXD) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "VOCP";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doVOCP(1 + one + (two << 1), vd, vs);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            super.compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //
/*TODO*/  //            return Common.disasmVDVS("vocp", 1 + one + (two << 1), vd, vs);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction VSOCP = new Instruction(209, FLAG_USES_VFPU_PFXS | FLAG_USES_VFPU_PFXD)
          //    {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "VSOCP";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doVSOCP(1 + one + (two << 1), vd, vs);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            super.compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //
/*TODO*/  //            return Common.disasmVDVS("vsocp", 1 + one + (two << 1), 1 + (one << 1), vd, vs);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction VFAD = new Instruction(210, FLAG_USES_VFPU_PFXS | FLAG_USES_VFPU_PFXD) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "VFAD";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doVFAD(1 + one + (two << 1), vd, vs);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            super.compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //
/*TODO*/  //            return Common.disasmVD1VS("vfad", 1 + one + (two << 1), vd, vs);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction VAVG = new Instruction(211, FLAG_USES_VFPU_PFXS | FLAG_USES_VFPU_PFXD) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "VAVG";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doVAVG(1 + one + (two << 1), vd, vs);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            super.compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //
/*TODO*/  //            return Common.disasmVD1VS("vavg", 1 + one + (two << 1), vd, vs);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction VSRT3 = new Instruction(212, FLAG_USES_VFPU_PFXS | FLAG_USES_VFPU_PFXD)
          //    {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "VSRT3";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doVSRT3(1 + one + (two << 1), vd, vs);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            super.compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //
/*TODO*/  //            return Common.disasmVDVS("vsrt3", 1 + one + (two << 1), vd, vs);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction VSGN = new Instruction(251, FLAG_USES_VFPU_PFXS | FLAG_USES_VFPU_PFXD) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "VSGN";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doVSGN(1 + one + (two << 1), vd, vs);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            super.compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //
/*TODO*/  //            return Common.disasmVDVS("vsgn", 1 + one + (two << 1), vd, vs);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction VSRT4 = new Instruction(213, FLAG_USES_VFPU_PFXS | FLAG_USES_VFPU_PFXD)
          //    {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "VSRT4";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doVSRT4(1 + one + (two << 1), vd, vs);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            super.compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //
/*TODO*/  //            return Common.disasmVDVS("vsrt4", 1 + one + (two << 1), vd, vs);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction VMFVC = new Instruction(214, FLAG_USES_VFPU_PFXD) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "VMFVC";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int imm7 = (insn >> 8) & 127;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doVMFVC(vd, imm7);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            super.compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int imm7 = (insn >> 8) & 127;
/*TODO*/  //
/*TODO*/  //            return "Unimplemented VMFVC imm7=" + imm7 + ", vd=" + vd;
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction VMTVC = new Instruction(215) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "VMTVC";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int imm7 = (insn >> 0) & 127;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doVMTVC(vs, imm7);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            super.compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int imm7 = (insn >> 0) & 127;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //
/*TODO*/  //            return "Unimplemented VMTVC imm7=" + imm7 + ", vs=" + vs;
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction VT4444 = new Instruction(216, FLAG_USES_VFPU_PFXS | FLAG_USES_VFPU_PFXD)
          //    {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "VT4444";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doVT4444(1 + one + (two << 1), vd, vs);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            super.compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //
/*TODO*/  //            return Common.disasmVDVS("vt4444", 1 + one + (two << 1), vd, vs);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction VT5551 = new Instruction(217, FLAG_USES_VFPU_PFXS | FLAG_USES_VFPU_PFXD)
          //    {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "VT5551";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doVT5551(1 + one + (two << 1), vd, vs);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            super.compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //
/*TODO*/  //            return Common.disasmVDVS("vt5551", 1 + one + (two << 1), vd, vs);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction VT5650 = new Instruction(218, FLAG_USES_VFPU_PFXS | FLAG_USES_VFPU_PFXD)
          //    {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "VT5650";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doVT5650(1 + one + (two << 1), vd, vs);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            super.compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //
/*TODO*/  //            return Common.disasmVDVS("vt5650", 1 + one + (two << 1), vd, vs);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction VCST = new Instruction(219, FLAG_USES_VFPU_PFXD | FLAG_COMPILED_PFX) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "VCST";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //            int imm5 = (insn >> 16) & 31;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doVCST(1 + one + (two << 1), vd, imm5);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            int imm5 = (insn >> 16) & 31;
/*TODO*/  //
/*TODO*/  //            float constant = 0.0f;
/*TODO*/  //            if (imm5 < VfpuState.floatConstants.length) {
/*TODO*/  //                constant = VfpuState.floatConstants[imm5];
/*TODO*/  //            }
/*TODO*/  //
/*TODO*/  //            context.startPfxCompiled();
/*TODO*/  //            int vsize = context.getVsize();
/*TODO*/  //            for (int n = 0; n < vsize; n++) {
/*TODO*/  //                context.prepareVdForStore(n);
/*TODO*/  //                context.getMethodVisitor().visitLdcInsn(constant);
/*TODO*/  //                context.storeVd(n);
/*TODO*/  //            }
/*TODO*/  //            context.endPfxCompiled();
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //            int imm5 = (insn >> 16) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmVDCST("VCST", 1 + one + (two << 1), vd, imm5);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction VF2IN = new Instruction(220, FLAG_USES_VFPU_PFXS | FLAG_USES_VFPU_PFXD |
          //    FLAG_COMPILED_PFX) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "VF2IN";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //            int imm5 = (insn >> 16) & 31;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doVF2IN(1 + one + (two << 1), vd, vs, imm5);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            int vsize = context.getVsize();
/*TODO*/  //            int imm5 = context.getImm5();
/*TODO*/  //            MethodVisitor mv = context.getMethodVisitor();
/*TODO*/  //            context.startPfxCompiled(false);
/*TODO*/  //            for (int n = 0; n < vsize; n++) {
/*TODO*/  //                context.prepareVdForStoreInt(n);
/*TODO*/  //                context.loadVs(n);
/*TODO*/  //                if (imm5 != 0) {
/*TODO*/  //                    context.loadImm(imm5);
/*TODO*/  //                    context.invokeStaticMethod(Type.getInternalName(Math.class), "scalb", "(FI)F");
/*TODO*/  //                }
/*TODO*/  //                Label afterLabel = new Label();
/*TODO*/  //                Label notNaNValueLabel = new Label();
/*TODO*/  //                mv.visitInsn(Opcodes.DUP);
/*TODO*/  //                context.invokeStaticMethod(Type.getInternalName(Float.class), "isNaN", "(F)Z");
/*TODO*/  //                mv.visitJumpInsn(Opcodes.IFEQ, notNaNValueLabel);
/*TODO*/  //                mv.visitInsn(Opcodes.POP);
/*TODO*/  //                context.loadImm(0x7FFFFFFF);
/*TODO*/  //                mv.visitJumpInsn(Opcodes.GOTO, afterLabel);
/*TODO*/  //                mv.visitLabel(notNaNValueLabel);
/*TODO*/  //                mv.visitInsn(Opcodes.F2D);
/*TODO*/  //                context.invokeStaticMethod(Type.getInternalName(Math.class), "rint", "(D)D");
/*TODO*/  //                mv.visitInsn(Opcodes.D2I);
/*TODO*/  //                mv.visitLabel(afterLabel);
/*TODO*/  //                context.storeVdInt(n);
/*TODO*/  //            }
/*TODO*/  //            context.endPfxCompiled(false);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //            int imm5 = (insn >> 16) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmVDVSIMM("vf2in", 1 + one + (two << 1), vd, vs, imm5);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction VF2IZ = new Instruction(221, FLAG_USES_VFPU_PFXS | FLAG_USES_VFPU_PFXD |
          //    FLAG_COMPILED_PFX) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "VF2IZ";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //            int imm5 = (insn >> 16) & 31;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doVF2IZ(1 + one + (two << 1), vd, vs, imm5);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            int vsize = context.getVsize();
/*TODO*/  //            int imm5 = context.getImm5();
/*TODO*/  //            MethodVisitor mv = context.getMethodVisitor();
/*TODO*/  //            context.startPfxCompiled(false);
/*TODO*/  //            for (int n = 0; n < vsize; n++) {
/*TODO*/  //                context.prepareVdForStoreInt(n);
/*TODO*/  //                context.loadVs(n);
/*TODO*/  //                mv.visitInsn(Opcodes.DUP);
/*TODO*/  //                mv.visitLdcInsn(0.f);
/*TODO*/  //                mv.visitInsn(Opcodes.FCMPG); // Use FCMPG or FCMPL? Need to check handling of NaN value
/*TODO*/  //                Label negativeLabel = new Label();
/*TODO*/  //                Label afterSignTestLabel = new Label();
/*TODO*/  //                mv.visitJumpInsn(Opcodes.IFLT, negativeLabel);
/*TODO*/  //                if (imm5 != 0) {
/*TODO*/  //                    context.loadImm(imm5);
/*TODO*/  //                    context.invokeStaticMethod(Type.getInternalName(Math.class), "scalb", "(FI)F");
/*TODO*/  //                }
/*TODO*/  //                mv.visitInsn(Opcodes.F2D);
/*TODO*/  //                context.invokeStaticMethod(Type.getInternalName(Math.class), "floor", "(D)D");
/*TODO*/  //                mv.visitJumpInsn(Opcodes.GOTO, afterSignTestLabel);
/*TODO*/  //                mv.visitLabel(negativeLabel);
/*TODO*/  //                if (imm5 != 0) {
/*TODO*/  //                    context.loadImm(imm5);
/*TODO*/  //                    context.invokeStaticMethod(Type.getInternalName(Math.class), "scalb", "(FI)F");
/*TODO*/  //                }
/*TODO*/  //                mv.visitInsn(Opcodes.F2D);
/*TODO*/  //                context.invokeStaticMethod(Type.getInternalName(Math.class), "ceil", "(D)D");
/*TODO*/  //                mv.visitLabel(afterSignTestLabel);
/*TODO*/  //
/*TODO*/  //                Label afterLabel = new Label();
/*TODO*/  //                Label notNaNValueLabel = new Label();
/*TODO*/  //                mv.visitInsn(Opcodes.DUP2);
/*TODO*/  //                context.invokeStaticMethod(Type.getInternalName(Double.class), "isNaN", "(D)Z");
/*TODO*/  //                mv.visitJumpInsn(Opcodes.IFEQ, notNaNValueLabel);
/*TODO*/  //                mv.visitInsn(Opcodes.POP2);
/*TODO*/  //                context.loadImm(0x7FFFFFFF);
/*TODO*/  //                mv.visitJumpInsn(Opcodes.GOTO, afterLabel);
/*TODO*/  //                mv.visitLabel(notNaNValueLabel);
/*TODO*/  //                mv.visitInsn(Opcodes.D2I);
/*TODO*/  //                mv.visitLabel(afterLabel);
/*TODO*/  //                context.storeVdInt(n);
/*TODO*/  //            }
/*TODO*/  //            context.endPfxCompiled(false);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //            int imm5 = (insn >> 16) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmVDVSIMM("vf2iz", 1 + one + (two << 1), vd, vs, imm5);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction VF2IU = new Instruction(222, FLAG_USES_VFPU_PFXS | FLAG_USES_VFPU_PFXD |
          //    FLAG_COMPILED_PFX) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "VF2IU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //            int imm5 = (insn >> 16) & 31;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doVF2IU(1 + one + (two << 1), vd, vs, imm5);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            int vsize = context.getVsize();
/*TODO*/  //            int imm5 = context.getImm5();
/*TODO*/  //            MethodVisitor mv = context.getMethodVisitor();
/*TODO*/  //            context.startPfxCompiled(false);
/*TODO*/  //            for (int n = 0; n < vsize; n++) {
/*TODO*/  //                context.prepareVdForStoreInt(n);
/*TODO*/  //                context.loadVs(n);
/*TODO*/  //                if (imm5 != 0) {
/*TODO*/  //                    context.loadImm(imm5);
/*TODO*/  //                    context.invokeStaticMethod(Type.getInternalName(Math.class), "scalb", "(FI)F");
/*TODO*/  //                }
/*TODO*/  //                mv.visitInsn(Opcodes.F2D);
/*TODO*/  //                context.invokeStaticMethod(Type.getInternalName(Math.class), "ceil", "(D)D");
/*TODO*/  //                Label afterLabel = new Label();
/*TODO*/  //                Label notNaNValueLabel = new Label();
/*TODO*/  //                mv.visitInsn(Opcodes.DUP2);
/*TODO*/  //                context.invokeStaticMethod(Type.getInternalName(Double.class), "isNaN", "(D)Z");
/*TODO*/  //                mv.visitJumpInsn(Opcodes.IFEQ, notNaNValueLabel);
/*TODO*/  //                mv.visitInsn(Opcodes.POP2);
/*TODO*/  //                context.loadImm(0x7FFFFFFF);
/*TODO*/  //                mv.visitJumpInsn(Opcodes.GOTO, afterLabel);
/*TODO*/  //                mv.visitLabel(notNaNValueLabel);
/*TODO*/  //                mv.visitInsn(Opcodes.D2I);
/*TODO*/  //                mv.visitLabel(afterLabel);
/*TODO*/  //                context.storeVdInt(n);
/*TODO*/  //            }
/*TODO*/  //            context.endPfxCompiled(false);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //            int imm5 = (insn >> 16) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmVDVSIMM("vf2iu", 1 + one + (two << 1), vd, vs, imm5);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction VF2ID = new Instruction(223, FLAG_USES_VFPU_PFXS | FLAG_USES_VFPU_PFXD |
          //    FLAG_COMPILED_PFX) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "VF2ID";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //            int imm5 = (insn >> 16) & 31;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doVF2ID(1 + one + (two << 1), vd, vs, imm5);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            int vsize = context.getVsize();
/*TODO*/  //            int imm5 = context.getImm5();
/*TODO*/  //            MethodVisitor mv = context.getMethodVisitor();
/*TODO*/  //            context.startPfxCompiled(false);
/*TODO*/  //            for (int n = 0; n < vsize; n++) {
/*TODO*/  //                context.prepareVdForStoreInt(n);
/*TODO*/  //                context.loadVs(n);
/*TODO*/  //                if (imm5 != 0) {
/*TODO*/  //                    context.loadImm(imm5);
/*TODO*/  //                    context.invokeStaticMethod(Type.getInternalName(Math.class), "scalb", "(FI)F");
/*TODO*/  //                }
/*TODO*/  //                mv.visitInsn(Opcodes.F2D);
/*TODO*/  //                context.invokeStaticMethod(Type.getInternalName(Math.class), "floor", "(D)D");
/*TODO*/  //                Label afterLabel = new Label();
/*TODO*/  //                Label notNaNValueLabel = new Label();
/*TODO*/  //                mv.visitInsn(Opcodes.DUP2);
/*TODO*/  //                context.invokeStaticMethod(Type.getInternalName(Double.class), "isNaN", "(D)Z");
/*TODO*/  //                mv.visitJumpInsn(Opcodes.IFEQ, notNaNValueLabel);
/*TODO*/  //                mv.visitInsn(Opcodes.POP2);
/*TODO*/  //                context.loadImm(0x7FFFFFFF);
/*TODO*/  //                mv.visitJumpInsn(Opcodes.GOTO, afterLabel);
/*TODO*/  //                mv.visitLabel(notNaNValueLabel);
/*TODO*/  //                mv.visitInsn(Opcodes.D2I);
/*TODO*/  //                mv.visitLabel(afterLabel);
/*TODO*/  //                context.storeVdInt(n);
/*TODO*/  //            }
/*TODO*/  //            context.endPfxCompiled(false);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //            int imm5 = (insn >> 16) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmVDVSIMM("vf2id", 1 + one + (two << 1), vd, vs, imm5);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction VI2F = new Instruction(224, FLAG_USES_VFPU_PFXS | FLAG_USES_VFPU_PFXD |
          //    FLAG_COMPILED_PFX) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "VI2F";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //            int imm5 = (insn >> 16) & 31;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doVI2F(1 + one + (two << 1), vd, vs, imm5);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            int vsize = context.getVsize();
/*TODO*/  //            int imm5 = context.getImm5();
/*TODO*/  //            MethodVisitor mv = context.getMethodVisitor();
/*TODO*/  //            context.startPfxCompiled();
/*TODO*/  //            for (int n = 0; n < vsize; n++) {
/*TODO*/  //                context.prepareVdForStore(n);
/*TODO*/  //                context.loadVsInt(n);
/*TODO*/  //                mv.visitInsn(Opcodes.I2F);
/*TODO*/  //                if (imm5 != 0) {
/*TODO*/  //                    context.loadImm(-imm5);
/*TODO*/  //                    context.invokeStaticMethod(Type.getInternalName(Math.class), "scalb", "(FI)F");
/*TODO*/  //                }
/*TODO*/  //                context.storeVd(n);
/*TODO*/  //            }
/*TODO*/  //            context.endPfxCompiled();
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //            int imm5 = (insn >> 16) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmVDVSIMM("vi2f", 1 + one + (two << 1), vd, vs, imm5);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction VCMOVT = new Instruction(225, FLAG_USES_VFPU_PFXS | FLAG_USES_VFPU_PFXD
          //    | FLAG_COMPILED_PFX) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "VCMOVT";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //            int imm3 = (insn >> 16) & 7;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doVCMOVT(1 + one + (two << 1), imm3, vd, vs);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            int vsize = context.getVsize();
/*TODO*/  //            int imm3 = context.getImm3();
/*TODO*/  //            MethodVisitor mv = context.getMethodVisitor();
/*TODO*/  //            if (imm3 < 6) {
/*TODO*/  //                context.startPfxCompiled(false);
/*TODO*/  //                Label notMoveLabel = new Label();
/*TODO*/  //                Label afterLabel = new Label();
/*TODO*/  //                context.loadVcrCc(imm3);
/*TODO*/  //                mv.visitJumpInsn(Opcodes.IFEQ, notMoveLabel);
/*TODO*/  //                for (int n = 0; n < vsize; n++) {
/*TODO*/  //                    context.prepareVdForStoreInt(n);
/*TODO*/  //                    context.loadVsInt(n);
/*TODO*/  //                    context.storeVdInt(n);
/*TODO*/  //                }
/*TODO*/  //                context.endPfxCompiled(false);
/*TODO*/  //                mv.visitJumpInsn(Opcodes.GOTO, afterLabel);
/*TODO*/  //                mv.visitLabel(notMoveLabel);
/*TODO*/  //                if (context.getPfxdState().isKnown() && context.getPfxdState().pfxDst.enabled) {
/*TODO*/  //                    for (int n = 0; n < vsize; n++) {
/*TODO*/  //                        context.prepareVdForStoreInt(n);
/*TODO*/  //                        context.loadVdInt(n);
/*TODO*/  //                        context.storeVdInt(n);
/*TODO*/  //                    }
/*TODO*/  //                    context.endPfxCompiled(false);
/*TODO*/  //                }
/*TODO*/  //                mv.visitLabel(afterLabel);
/*TODO*/  //            } else if (imm3 == 6) {
/*TODO*/  //                context.startPfxCompiled(false);
/*TODO*/  //                for (int n = 0; n < vsize; n++) {
/*TODO*/  //                    Label notMoveLabel = new Label();
/*TODO*/  //                    Label afterLabel = new Label();
/*TODO*/  //                    context.loadVcrCc(n);
/*TODO*/  //                    mv.visitJumpInsn(Opcodes.IFEQ, notMoveLabel);
/*TODO*/  //                    context.prepareVdForStoreInt(n);
/*TODO*/  //                    context.loadVsInt(n);
/*TODO*/  //                    context.storeVdInt(n);
/*TODO*/  //                    mv.visitJumpInsn(Opcodes.GOTO, afterLabel);
/*TODO*/  //                    mv.visitLabel(notMoveLabel);
/*TODO*/  //                    if (context.getPfxdState().isKnown() && context.getPfxdState().pfxDst.enabled) {
/*TODO*/  //                        context.prepareVdForStoreInt(n);
/*TODO*/  //                        context.loadVdInt(n);
/*TODO*/  //                        context.storeVdInt(n);
/*TODO*/  //                    }
/*TODO*/  //                    mv.visitLabel(afterLabel);
/*TODO*/  //                }
/*TODO*/  //                context.endPfxCompiled(false);
/*TODO*/  //            } else {
/*TODO*/  //                // Never copy
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //            int imm3 = (insn >> 16) & 7;
/*TODO*/  //
/*TODO*/  //            return Common.disasmVDVSIMM("VCMOVT", 1 + one + (two << 1), vd, vs, imm3);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction VCMOVF = new Instruction(226, FLAG_USES_VFPU_PFXS | FLAG_USES_VFPU_PFXD
          //    | FLAG_COMPILED_PFX) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "VCMOVF";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //            int imm3 = (insn >> 16) & 7;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doVCMOVF(1 + one + (two << 1), imm3, vd, vs);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            int vsize = context.getVsize();
/*TODO*/  //            int imm3 = context.getImm3();
/*TODO*/  //            MethodVisitor mv = context.getMethodVisitor();
/*TODO*/  //            context.startPfxCompiled(false);
/*TODO*/  //            if (imm3 < 6) {
/*TODO*/  //                Label notMoveLabel = new Label();
/*TODO*/  //                Label afterLabel = new Label();
/*TODO*/  //                context.loadVcrCc(imm3);
/*TODO*/  //                mv.visitJumpInsn(Opcodes.IFNE, notMoveLabel);
/*TODO*/  //                for (int n = 0; n < vsize; n++) {
/*TODO*/  //                    context.prepareVdForStoreInt(n);
/*TODO*/  //                    context.loadVsInt(n);
/*TODO*/  //                    context.storeVdInt(n);
/*TODO*/  //                }
/*TODO*/  //                mv.visitJumpInsn(Opcodes.GOTO, afterLabel);
/*TODO*/  //                mv.visitLabel(notMoveLabel);
/*TODO*/  //                if (context.getPfxdState().isKnown() && context.getPfxdState().pfxDst.enabled) {
/*TODO*/  //                    for (int n = 0; n < vsize; n++) {
/*TODO*/  //                        context.prepareVdForStoreInt(n);
/*TODO*/  //                        context.loadVdInt(n);
/*TODO*/  //                        context.storeVdInt(n);
/*TODO*/  //                    }
/*TODO*/  //                }
/*TODO*/  //                mv.visitLabel(afterLabel);
/*TODO*/  //            } else if (imm3 == 6) {
/*TODO*/  //                for (int n = 0; n < vsize; n++) {
/*TODO*/  //                    Label notMoveLabel = new Label();
/*TODO*/  //                    Label afterLabel = new Label();
/*TODO*/  //                    context.loadVcrCc(n);
/*TODO*/  //                    mv.visitJumpInsn(Opcodes.IFNE, notMoveLabel);
/*TODO*/  //                    context.prepareVdForStoreInt(n);
/*TODO*/  //                    context.loadVsInt(n);
/*TODO*/  //                    context.storeVdInt(n);
/*TODO*/  //                    mv.visitJumpInsn(Opcodes.GOTO, afterLabel);
/*TODO*/  //                    mv.visitLabel(notMoveLabel);
/*TODO*/  //                    if (context.getPfxdState().isKnown() && context.getPfxdState().pfxDst.enabled) {
/*TODO*/  //                        context.prepareVdForStoreInt(n);
/*TODO*/  //                        context.loadVdInt(n);
/*TODO*/  //                        context.storeVdInt(n);
/*TODO*/  //                    }
/*TODO*/  //                    mv.visitLabel(afterLabel);
/*TODO*/  //                }
/*TODO*/  //            } else {
/*TODO*/  //                // Always copy
/*TODO*/  //                for (int n = 0; n < vsize; n++) {
/*TODO*/  //                    context.prepareVdForStoreInt(n);
/*TODO*/  //                    context.loadVsInt(n);
/*TODO*/  //                    context.storeVdInt(n);
/*TODO*/  //                }
/*TODO*/  //            }
/*TODO*/  //            context.endPfxCompiled(false);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //            int imm3 = (insn >> 16) & 7;
/*TODO*/  //
/*TODO*/  //            return Common.disasmVDVSIMM("VCMOVF", 1 + one + (two << 1), vd, vs, imm3);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction VWBN = new Instruction(227) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "VWBN";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //            int imm8 = (insn >> 16) & 255;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doVWBN(1 + one + (two << 1), vd, vs, imm8);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            super.compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //            int imm8 = (insn >> 16) & 255;
/*TODO*/  //
/*TODO*/  //            return Common.disasmVDVSIMM("VWBN", 1 + one + (two << 1), vd, vs, imm8);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction VPFXS = new Instruction(228) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "VPFXS";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int swzx = (insn >> 0) & 3;
/*TODO*/  //            int swzy = (insn >> 2) & 3;
/*TODO*/  //            int swzz = (insn >> 4) & 3;
/*TODO*/  //            int swzw = (insn >> 6) & 3;
/*TODO*/  //            int absx = (insn >> 8) & 1;
/*TODO*/  //            int absy = (insn >> 9) & 1;
/*TODO*/  //            int absz = (insn >> 10) & 1;
/*TODO*/  //            int absw = (insn >> 11) & 1;
/*TODO*/  //            int cstx = (insn >> 12) & 1;
/*TODO*/  //            int csty = (insn >> 13) & 1;
/*TODO*/  //            int cstz = (insn >> 14) & 1;
/*TODO*/  //            int cstw = (insn >> 15) & 1;
/*TODO*/  //            int negx = (insn >> 16) & 1;
/*TODO*/  //            int negy = (insn >> 17) & 1;
/*TODO*/  //            int negz = (insn >> 18) & 1;
/*TODO*/  //            int negw = (insn >> 19) & 1;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doVPFXS(
/*TODO*/  //                    negw, negz, negy, negx,
/*TODO*/  //                    cstw, cstz, csty, cstx,
/*TODO*/  //                    absw, absz, absy, absx,
/*TODO*/  //                    swzw, swzz, swzy, swzx
/*TODO*/  //            );
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            if (context.isPfxConsumed(FLAG_USES_VFPU_PFXS)) {
/*TODO*/  //                context.getPfxsState().setKnown(true);
/*TODO*/  //                PfxSrc pfxSrc = context.getPfxsState().pfxSrc;
/*TODO*/  //                pfxSrc.swz[0] = (insn >> 0) & 3;
/*TODO*/  //                pfxSrc.swz[1] = (insn >> 2) & 3;
/*TODO*/  //                pfxSrc.swz[2] = (insn >> 4) & 3;
/*TODO*/  //                pfxSrc.swz[3] = (insn >> 6) & 3;
/*TODO*/  //                pfxSrc.abs[0] = ((insn >> 8) & 1) != 0;
/*TODO*/  //                pfxSrc.abs[1] = ((insn >> 9) & 1) != 0;
/*TODO*/  //                pfxSrc.abs[2] = ((insn >> 10) & 1) != 0;
/*TODO*/  //                pfxSrc.abs[3] = ((insn >> 11) & 1) != 0;
/*TODO*/  //                pfxSrc.cst[0] = ((insn >> 12) & 1) != 0;
/*TODO*/  //                pfxSrc.cst[1] = ((insn >> 13) & 1) != 0;
/*TODO*/  //                pfxSrc.cst[2] = ((insn >> 14) & 1) != 0;
/*TODO*/  //                pfxSrc.cst[3] = ((insn >> 15) & 1) != 0;
/*TODO*/  //                pfxSrc.neg[0] = ((insn >> 16) & 1) != 0;
/*TODO*/  //                pfxSrc.neg[1] = ((insn >> 17) & 1) != 0;
/*TODO*/  //                pfxSrc.neg[2] = ((insn >> 18) & 1) != 0;
/*TODO*/  //                pfxSrc.neg[3] = ((insn >> 19) & 1) != 0;
/*TODO*/  //                pfxSrc.enabled = true;
/*TODO*/  //            } else {
/*TODO*/  //                context.getPfxsState().setKnown(false);
/*TODO*/  //                context.compileInterpreterInstruction();
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int swzx = (insn >> 0) & 3;
/*TODO*/  //            int swzy = (insn >> 2) & 3;
/*TODO*/  //            int swzz = (insn >> 4) & 3;
/*TODO*/  //            int swzw = (insn >> 6) & 3;
/*TODO*/  //            int absx = (insn >> 8) & 1;
/*TODO*/  //            int absy = (insn >> 9) & 1;
/*TODO*/  //            int absz = (insn >> 10) & 1;
/*TODO*/  //            int absw = (insn >> 11) & 1;
/*TODO*/  //            int cstx = (insn >> 12) & 1;
/*TODO*/  //            int csty = (insn >> 13) & 1;
/*TODO*/  //            int cstz = (insn >> 14) & 1;
/*TODO*/  //            int cstw = (insn >> 15) & 1;
/*TODO*/  //            int negx = (insn >> 16) & 1;
/*TODO*/  //            int negy = (insn >> 17) & 1;
/*TODO*/  //            int negz = (insn >> 18) & 1;
/*TODO*/  //            int negw = (insn >> 19) & 1;
/*TODO*/  //
/*TODO*/  //            int[] swz = new int[4];
/*TODO*/  //            boolean[] abs, cst, neg;
/*TODO*/  //            abs = new boolean[4];
/*TODO*/  //            cst = new boolean[4];
/*TODO*/  //            neg = new boolean[4];
/*TODO*/  //
/*TODO*/  //            swz[0] = swzx;
/*TODO*/  //            swz[1] = swzy;
/*TODO*/  //            swz[2] = swzz;
/*TODO*/  //            swz[3] = swzw;
/*TODO*/  //            abs[0] = absx != 0;
/*TODO*/  //            abs[1] = absy != 0;
/*TODO*/  //            abs[2] = absz != 0;
/*TODO*/  //            abs[3] = absw != 0;
/*TODO*/  //            cst[0] = cstx != 0;
/*TODO*/  //            cst[1] = csty != 0;
/*TODO*/  //            cst[2] = cstz != 0;
/*TODO*/  //            cst[3] = cstw != 0;
/*TODO*/  //            neg[0] = negx != 0;
/*TODO*/  //            neg[1] = negy != 0;
/*TODO*/  //            neg[2] = negz != 0;
/*TODO*/  //            neg[3] = negw != 0;
/*TODO*/  //
/*TODO*/  //            return Common.disasmVPFX("VPFXS", swz, abs, cst, neg);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction VPFXT = new Instruction(229) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "VPFXT";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int swzx = (insn >> 0) & 3;
/*TODO*/  //            int swzy = (insn >> 2) & 3;
/*TODO*/  //            int swzz = (insn >> 4) & 3;
/*TODO*/  //            int swzw = (insn >> 6) & 3;
/*TODO*/  //            int absx = (insn >> 8) & 1;
/*TODO*/  //            int absy = (insn >> 9) & 1;
/*TODO*/  //            int absz = (insn >> 10) & 1;
/*TODO*/  //            int absw = (insn >> 11) & 1;
/*TODO*/  //            int cstx = (insn >> 12) & 1;
/*TODO*/  //            int csty = (insn >> 13) & 1;
/*TODO*/  //            int cstz = (insn >> 14) & 1;
/*TODO*/  //            int cstw = (insn >> 15) & 1;
/*TODO*/  //            int negx = (insn >> 16) & 1;
/*TODO*/  //            int negy = (insn >> 17) & 1;
/*TODO*/  //            int negz = (insn >> 18) & 1;
/*TODO*/  //            int negw = (insn >> 19) & 1;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doVPFXT(
/*TODO*/  //                    negw, negz, negy, negx,
/*TODO*/  //                    cstw, cstz, csty, cstx,
/*TODO*/  //                    absw, absz, absy, absx,
/*TODO*/  //                    swzw, swzz, swzy, swzx
/*TODO*/  //            );
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            if (context.isPfxConsumed(FLAG_USES_VFPU_PFXT)) {
/*TODO*/  //                context.getPfxtState().setKnown(true);
/*TODO*/  //                PfxSrc pfxSrc = context.getPfxtState().pfxSrc;
/*TODO*/  //                pfxSrc.swz[0] = (insn >> 0) & 3;
/*TODO*/  //                pfxSrc.swz[1] = (insn >> 2) & 3;
/*TODO*/  //                pfxSrc.swz[2] = (insn >> 4) & 3;
/*TODO*/  //                pfxSrc.swz[3] = (insn >> 6) & 3;
/*TODO*/  //                pfxSrc.abs[0] = ((insn >> 8) & 1) != 0;
/*TODO*/  //                pfxSrc.abs[1] = ((insn >> 9) & 1) != 0;
/*TODO*/  //                pfxSrc.abs[2] = ((insn >> 10) & 1) != 0;
/*TODO*/  //                pfxSrc.abs[3] = ((insn >> 11) & 1) != 0;
/*TODO*/  //                pfxSrc.cst[0] = ((insn >> 12) & 1) != 0;
/*TODO*/  //                pfxSrc.cst[1] = ((insn >> 13) & 1) != 0;
/*TODO*/  //                pfxSrc.cst[2] = ((insn >> 14) & 1) != 0;
/*TODO*/  //                pfxSrc.cst[3] = ((insn >> 15) & 1) != 0;
/*TODO*/  //                pfxSrc.neg[0] = ((insn >> 16) & 1) != 0;
/*TODO*/  //                pfxSrc.neg[1] = ((insn >> 17) & 1) != 0;
/*TODO*/  //                pfxSrc.neg[2] = ((insn >> 18) & 1) != 0;
/*TODO*/  //                pfxSrc.neg[3] = ((insn >> 19) & 1) != 0;
/*TODO*/  //                pfxSrc.enabled = true;
/*TODO*/  //            } else {
/*TODO*/  //                context.getPfxtState().setKnown(false);
/*TODO*/  //                context.compileInterpreterInstruction();
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int swzx = (insn >> 0) & 3;
/*TODO*/  //            int swzy = (insn >> 2) & 3;
/*TODO*/  //            int swzz = (insn >> 4) & 3;
/*TODO*/  //            int swzw = (insn >> 6) & 3;
/*TODO*/  //            int absx = (insn >> 8) & 1;
/*TODO*/  //            int absy = (insn >> 9) & 1;
/*TODO*/  //            int absz = (insn >> 10) & 1;
/*TODO*/  //            int absw = (insn >> 11) & 1;
/*TODO*/  //            int cstx = (insn >> 12) & 1;
/*TODO*/  //            int csty = (insn >> 13) & 1;
/*TODO*/  //            int cstz = (insn >> 14) & 1;
/*TODO*/  //            int cstw = (insn >> 15) & 1;
/*TODO*/  //            int negx = (insn >> 16) & 1;
/*TODO*/  //            int negy = (insn >> 17) & 1;
/*TODO*/  //            int negz = (insn >> 18) & 1;
/*TODO*/  //            int negw = (insn >> 19) & 1;
/*TODO*/  //
/*TODO*/  //            int[] swz = new int[4];
/*TODO*/  //            boolean[] abs, cst, neg;
/*TODO*/  //            abs = new boolean[4];
/*TODO*/  //            cst = new boolean[4];
/*TODO*/  //            neg = new boolean[4];
/*TODO*/  //
/*TODO*/  //            swz[0] = swzx;
/*TODO*/  //            swz[1] = swzy;
/*TODO*/  //            swz[2] = swzz;
/*TODO*/  //            swz[3] = swzw;
/*TODO*/  //            abs[0] = absx != 0;
/*TODO*/  //            abs[1] = absy != 0;
/*TODO*/  //            abs[2] = absz != 0;
/*TODO*/  //            abs[3] = absw != 0;
/*TODO*/  //            cst[0] = cstx != 0;
/*TODO*/  //            cst[1] = csty != 0;
/*TODO*/  //            cst[2] = cstz != 0;
/*TODO*/  //            cst[3] = cstw != 0;
/*TODO*/  //            neg[0] = negx != 0;
/*TODO*/  //            neg[1] = negy != 0;
/*TODO*/  //            neg[2] = negz != 0;
/*TODO*/  //            neg[3] = negw != 0;
/*TODO*/  //
/*TODO*/  //            return Common.disasmVPFX("VPFXT", swz, abs, cst, neg);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction VPFXD = new Instruction(230) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "VPFXD";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int satx = (insn >> 0) & 3;
/*TODO*/  //            int saty = (insn >> 2) & 3;
/*TODO*/  //            int satz = (insn >> 4) & 3;
/*TODO*/  //            int satw = (insn >> 6) & 3;
/*TODO*/  //            int mskx = (insn >> 8) & 1;
/*TODO*/  //            int msky = (insn >> 9) & 1;
/*TODO*/  //            int mskz = (insn >> 10) & 1;
/*TODO*/  //            int mskw = (insn >> 11) & 1;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doVPFXD(
/*TODO*/  //                    mskw, mskz, msky, mskx,
/*TODO*/  //                    satw, satz, saty, satx
/*TODO*/  //            );
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            if (context.isPfxConsumed(FLAG_USES_VFPU_PFXD)) {
/*TODO*/  //                context.getPfxdState().setKnown(true);
/*TODO*/  //                PfxDst pfxDst = context.getPfxdState().pfxDst;
/*TODO*/  //                pfxDst.sat[0] = (insn >> 0) & 3;
/*TODO*/  //                pfxDst.sat[1] = (insn >> 2) & 3;
/*TODO*/  //                pfxDst.sat[2] = (insn >> 4) & 3;
/*TODO*/  //                pfxDst.sat[3] = (insn >> 6) & 3;
/*TODO*/  //                pfxDst.msk[0] = ((insn >> 8) & 1) != 0;
/*TODO*/  //                pfxDst.msk[1] = ((insn >> 9) & 1) != 0;
/*TODO*/  //                pfxDst.msk[2] = ((insn >> 10) & 1) != 0;
/*TODO*/  //                pfxDst.msk[3] = ((insn >> 11) & 1) != 0;
/*TODO*/  //                pfxDst.enabled = true;
/*TODO*/  //            } else {
/*TODO*/  //                context.getPfxdState().setKnown(false);
/*TODO*/  //                context.compileInterpreterInstruction();
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int satx = (insn >> 0) & 3;
/*TODO*/  //            int saty = (insn >> 2) & 3;
/*TODO*/  //            int satz = (insn >> 4) & 3;
/*TODO*/  //            int satw = (insn >> 6) & 3;
/*TODO*/  //            int mskx = (insn >> 8) & 1;
/*TODO*/  //            int msky = (insn >> 9) & 1;
/*TODO*/  //            int mskz = (insn >> 10) & 1;
/*TODO*/  //            int mskw = (insn >> 11) & 1;
/*TODO*/  //
/*TODO*/  //            int[] sat, msk;
/*TODO*/  //            sat = new int[4];
/*TODO*/  //            msk = new int[4];
/*TODO*/  //            sat[0] = satx;
/*TODO*/  //            sat[1] = saty;
/*TODO*/  //            sat[2] = satz;
/*TODO*/  //            sat[3] = satw;
/*TODO*/  //            msk[0] = mskx;
/*TODO*/  //            msk[1] = msky;
/*TODO*/  //            msk[2] = mskz;
/*TODO*/  //            msk[3] = mskw;
/*TODO*/  //
/*TODO*/  //            return Common.disasmVPFXD("VPFXD", sat, msk);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction VIIM = new Instruction(231, FLAG_USES_VFPU_PFXD | FLAG_COMPILED_PFX) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "VIIM";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int vd = (insn >> 16) & 127;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doVIIM(vd, (int) (short) imm16);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            final int vsize = 1;
/*TODO*/  //            final int vd = context.getVtRegisterIndex(); // vd index stored as vt
/*TODO*/  //            int simm16 = context.getImm16(true);
/*TODO*/  //            context.startPfxCompiled();
/*TODO*/  //            context.prepareVdForStore(vsize, vd, 0);
/*TODO*/  //            context.getMethodVisitor().visitLdcInsn((float) simm16);
/*TODO*/  //            context.storeVd(vsize, vd, 0);
/*TODO*/  //            context.endPfxCompiled();
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int vd = (insn >> 16) & 127;
/*TODO*/  //
/*TODO*/  //            return Common.disasmVDIIM("VIIM", 1, vd, imm16);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction VFIM = new Instruction(232, FLAG_USES_VFPU_PFXD | FLAG_COMPILED_PFX) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "VFIM";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int vd = (insn >> 16) & 127;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doVFIM(vd, imm16);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            final int vsize = 1;
/*TODO*/  //            final int vd = context.getVtRegisterIndex(); // vd index stored as vt
/*TODO*/  //            final int imm16 = context.getImm16(false);
/*TODO*/  //            int value = VfpuState.halffloatToFloat(imm16);
/*TODO*/  //            context.startPfxCompiled();
/*TODO*/  //            context.prepareVdForStoreInt(vsize, vd, 0);
/*TODO*/  //            context.loadImm(value);
/*TODO*/  //            context.storeVdInt(vsize, vd, 0);
/*TODO*/  //            context.endPfxCompiled();
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int vd = (insn >> 16) & 127;
/*TODO*/  //
/*TODO*/  //            return Common.disasmVDFIM("VFIM", 1, vd, imm16);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction VMMUL = new Instruction(233, FLAG_USES_VFPU_PFXS | FLAG_USES_VFPU_PFXT |
          //    FLAG_USES_VFPU_PFXD | FLAG_COMPILED_PFX) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "VMMUL";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //            int vt = (insn >> 16) & 127;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doVMMUL(1 + one + (two << 1), vd, vs, vt);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            // Use the interpreter if we need an accurate "dot" implementation
/*TODO*/  //            if (useAccurateVfpuDot) {
/*TODO*/  //                super.compile(context, insn);
/*TODO*/  //            } else {
/*TODO*/  //                int vsize = context.getVsize();
/*TODO*/  //                if (vsize > 1) {
/*TODO*/  //                    context.startPfxCompiled();
/*TODO*/  //                    int vs = context.getVsRegisterIndex();
/*TODO*/  //                    int vt = context.getVtRegisterIndex();
/*TODO*/  //                    int vd = context.getVdRegisterIndex();
/*TODO*/  //                    for (int i = 0; i < vsize; i++) {
/*TODO*/  //                        for (int j = 0; j < vsize; j++) {
/*TODO*/  //                            context.prepareVdForStore(vsize, vd + i, j);
/*TODO*/  //                            context.loadVs(vsize, vs + j, 0);
/*TODO*/  //                            context.loadVt(vsize, vt + i, 0);
/*TODO*/  //                            context.getMethodVisitor().visitInsn(Opcodes.FMUL);
/*TODO*/  //                            for (int n = 1; n < vsize; n++) {
/*TODO*/  //                                context.loadVs(vsize, vs + j, n);
/*TODO*/  //                                context.loadVt(vsize, vt + i, n);
/*TODO*/  //                                context.getMethodVisitor().visitInsn(Opcodes.FMUL);
/*TODO*/  //                                context.getMethodVisitor().visitInsn(Opcodes.FADD);
/*TODO*/  //                            }
/*TODO*/  //                            context.storeVd(vsize, vd + i, j);
/*TODO*/  //                        }
/*TODO*/  //                        context.flushPfxCompiled(vsize, vd + i, true);
/*TODO*/  //                    }
/*TODO*/  //                    context.endPfxCompiled(vsize, true, false);
/*TODO*/  //                } else {
/*TODO*/  //                    // Unsupported VMMUL.S
/*TODO*/  //                    context.compileInterpreterInstruction();
/*TODO*/  //                }
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //            int vt = (insn >> 16) & 127;
/*TODO*/  //
/*TODO*/  //            return Common.disasmVDMVSMVTM("VMMUL", 1 + one + (two << 1), vd, vs ^ 32, vt);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction VHTFM2 = new Instruction(234, FLAG_USES_VFPU_PFXS | FLAG_USES_VFPU_PFXT
          //    | FLAG_USES_VFPU_PFXD) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "VHTFM2";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int vt = (insn >> 16) & 127;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doVHTFM2(vd, vs, vt);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            super.compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int vt = (insn >> 16) & 127;
/*TODO*/  //
/*TODO*/  //            return Common.disasmVDVSMVT("VHTFM2", 2, vd, vs, vt);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction VTFM2 = new Instruction(235, FLAG_USES_VFPU_PFXS | FLAG_USES_VFPU_PFXT |
          //    FLAG_USES_VFPU_PFXD) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "VTFM2";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int vt = (insn >> 16) & 127;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doVTFM2(vd, vs, vt);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            super.compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int vt = (insn >> 16) & 127;
/*TODO*/  //
/*TODO*/  //            return Common.disasmVDVSMVT("VTFM2", 2, vd, vs, vt);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction VHTFM3 = new Instruction(236, FLAG_USES_VFPU_PFXS | FLAG_USES_VFPU_PFXT
          //    | FLAG_USES_VFPU_PFXD) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "VHTFM3";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int vt = (insn >> 16) & 127;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doVHTFM3(vd, vs, vt);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            super.compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int vt = (insn >> 16) & 127;
/*TODO*/  //
/*TODO*/  //            return Common.disasmVDVSMVT("VHTFM3", 3, vd, vs, vt);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction VTFM3 = new Instruction(237, FLAG_USES_VFPU_PFXS | FLAG_USES_VFPU_PFXT |
          //    FLAG_USES_VFPU_PFXD | FLAG_COMPILED_PFX) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "VTFM3";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int vt = (insn >> 16) & 127;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doVTFM3(vd, vs, vt);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            // Use the interpreter if we need an accurate "dot" implementation
/*TODO*/  //            if (useAccurateVfpuDot) {
/*TODO*/  //                super.compile(context, insn);
/*TODO*/  //            } else {
/*TODO*/  //                final int vsize = 3;
/*TODO*/  //                final int vs = context.getVsRegisterIndex();
/*TODO*/  //                MethodVisitor mv = context.getMethodVisitor();
/*TODO*/  //                context.loadVt(vsize, 0);
/*TODO*/  //                context.storeFTmp1();
/*TODO*/  //                context.loadVt(vsize, 1);
/*TODO*/  //                context.storeFTmp2();
/*TODO*/  //                context.loadVt(vsize, 2);
/*TODO*/  //                context.storeFTmp3();
/*TODO*/  //                for (int n = 0; n < vsize; n++) {
/*TODO*/  //                    context.prepareVdForStore(vsize, n);
/*TODO*/  //                    context.loadVs(vsize, vs + n, 0);
/*TODO*/  //                    context.loadFTmp1();
/*TODO*/  //                    mv.visitInsn(Opcodes.FMUL);
/*TODO*/  //                    context.loadVs(vsize, vs + n, 1);
/*TODO*/  //                    context.loadFTmp2();
/*TODO*/  //                    mv.visitInsn(Opcodes.FMUL);
/*TODO*/  //                    mv.visitInsn(Opcodes.FADD);
/*TODO*/  //                    context.loadVs(vsize, vs + n, 2);
/*TODO*/  //                    context.loadFTmp3();
/*TODO*/  //                    mv.visitInsn(Opcodes.FMUL);
/*TODO*/  //                    mv.visitInsn(Opcodes.FADD);
/*TODO*/  //                    context.storeVd(vsize, n);
/*TODO*/  //                }
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int vt = (insn >> 16) & 127;
/*TODO*/  //
/*TODO*/  //            return Common.disasmVDVSMVT("VTFM3", 3, vd, vs, vt);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction VHTFM4 = new Instruction(238, FLAG_USES_VFPU_PFXS | FLAG_USES_VFPU_PFXT
          //    | FLAG_USES_VFPU_PFXD | FLAG_COMPILED_PFX) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "VHTFM4";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int vt = (insn >> 16) & 127;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doVHTFM4(vd, vs, vt);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            // Use the interpreter if we need an accurate "dot" implementation
/*TODO*/  //            if (useAccurateVfpuDot) {
/*TODO*/  //                super.compile(context, insn);
/*TODO*/  //            } else {
/*TODO*/  //                final int vsize = 4;
/*TODO*/  //                final int vs = context.getVsRegisterIndex();
/*TODO*/  //                MethodVisitor mv = context.getMethodVisitor();
/*TODO*/  //                context.loadVt(3, 0);
/*TODO*/  //                context.storeFTmp1();
/*TODO*/  //                context.loadVt(3, 1);
/*TODO*/  //                context.storeFTmp2();
/*TODO*/  //                context.loadVt(3, 2);
/*TODO*/  //                context.storeFTmp3();
/*TODO*/  //                for (int n = 0; n < vsize; n++) {
/*TODO*/  //                    context.prepareVdForStore(vsize, n);
/*TODO*/  //                    context.loadVs(vsize, vs + n, 0);
/*TODO*/  //                    context.loadFTmp1();
/*TODO*/  //                    mv.visitInsn(Opcodes.FMUL);
/*TODO*/  //                    context.loadVs(vsize, vs + n, 1);
/*TODO*/  //                    context.loadFTmp2();
/*TODO*/  //                    mv.visitInsn(Opcodes.FMUL);
/*TODO*/  //                    mv.visitInsn(Opcodes.FADD);
/*TODO*/  //                    context.loadVs(vsize, vs + n, 2);
/*TODO*/  //                    context.loadFTmp3();
/*TODO*/  //                    mv.visitInsn(Opcodes.FMUL);
/*TODO*/  //                    mv.visitInsn(Opcodes.FADD);
/*TODO*/  //                    context.loadVs(vsize, vs + n, 3);
/*TODO*/  //                    mv.visitInsn(Opcodes.FADD);
/*TODO*/  //                    context.storeVd(vsize, n);
/*TODO*/  //                }
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int vt = (insn >> 16) & 127;
/*TODO*/  //
/*TODO*/  //            return Common.disasmVDVSMVT("VHTFM4", 4, vd, vs, vt);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction VTFM4 = new Instruction(239, FLAG_USES_VFPU_PFXS | FLAG_USES_VFPU_PFXT |
          //    FLAG_USES_VFPU_PFXD | FLAG_COMPILED_PFX) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "VTFM4";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int vt = (insn >> 16) & 127;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doVTFM4(vd, vs, vt);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            // Use the interpreter if we need an accurate "dot" implementation
/*TODO*/  //            if (useAccurateVfpuDot) {
/*TODO*/  //                super.compile(context, insn);
/*TODO*/  //            } else {
/*TODO*/  //                final int vsize = 4;
/*TODO*/  //                final int vs = context.getVsRegisterIndex();
/*TODO*/  //                MethodVisitor mv = context.getMethodVisitor();
/*TODO*/  //                context.loadVt(vsize, 0);
/*TODO*/  //                context.storeFTmp1();
/*TODO*/  //                context.loadVt(vsize, 1);
/*TODO*/  //                context.storeFTmp2();
/*TODO*/  //                context.loadVt(vsize, 2);
/*TODO*/  //                context.storeFTmp3();
/*TODO*/  //                context.loadVt(vsize, 3);
/*TODO*/  //                context.storeFTmp4();
/*TODO*/  //                for (int n = 0; n < vsize; n++) {
/*TODO*/  //                    context.prepareVdForStore(vsize, n);
/*TODO*/  //                    context.loadVs(vsize, vs + n, 0);
/*TODO*/  //                    context.loadFTmp1();
/*TODO*/  //                    mv.visitInsn(Opcodes.FMUL);
/*TODO*/  //                    context.loadVs(vsize, vs + n, 1);
/*TODO*/  //                    context.loadFTmp2();
/*TODO*/  //                    mv.visitInsn(Opcodes.FMUL);
/*TODO*/  //                    mv.visitInsn(Opcodes.FADD);
/*TODO*/  //                    context.loadVs(vsize, vs + n, 2);
/*TODO*/  //                    context.loadFTmp3();
/*TODO*/  //                    mv.visitInsn(Opcodes.FMUL);
/*TODO*/  //                    mv.visitInsn(Opcodes.FADD);
/*TODO*/  //                    context.loadVs(vsize, vs + n, 3);
/*TODO*/  //                    context.loadFTmp4();
/*TODO*/  //                    mv.visitInsn(Opcodes.FMUL);
/*TODO*/  //                    mv.visitInsn(Opcodes.FADD);
/*TODO*/  //                    context.storeVd(vsize, n);
/*TODO*/  //                }
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int vt = (insn >> 16) & 127;
/*TODO*/  //
/*TODO*/  //            return Common.disasmVDVSMVT("VTFM4", 4, vd, vs, vt);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction VMSCL = new Instruction(240, FLAG_USES_VFPU_PFXS | FLAG_USES_VFPU_PFXT |
          //    FLAG_USES_VFPU_PFXD | FLAG_COMPILED_PFX) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "VMSCL";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //            int vt = (insn >> 16) & 127;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doVMSCL(1 + one + (two << 1), vd, vs, vt);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            final int vsize = context.getVsize();
/*TODO*/  //            if (vsize > 1) {
/*TODO*/  //                final int vs = context.getVsRegisterIndex();
/*TODO*/  //                final int vd = context.getVdRegisterIndex();
/*TODO*/  //                context.startPfxCompiled();
/*TODO*/  //                context.loadVt(1, 0);
/*TODO*/  //                context.storeFTmp1();
/*TODO*/  //                for (int i = 0; i < vsize; i++) {
/*TODO*/  //                    for (int n = 0; n < vsize; n++) {
/*TODO*/  //                        context.prepareVdForStore(vsize, vd + i, n);
/*TODO*/  //                        context.loadVs(vsize, vs + i, n);
/*TODO*/  //                        context.loadFTmp1();
/*TODO*/  //                        context.getMethodVisitor().visitInsn(Opcodes.FMUL);
/*TODO*/  //                        context.storeVd(vsize, vd + i, n);
/*TODO*/  //                    }
/*TODO*/  //                    context.flushPfxCompiled(vsize, vd + i, true);
/*TODO*/  //                }
/*TODO*/  //                context.endPfxCompiled(vsize, true, false);
/*TODO*/  //            } else {
/*TODO*/  //                // Unsupported VMSCL.S
/*TODO*/  //                context.compileInterpreterInstruction();
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //            int vt = (insn >> 16) & 127;
/*TODO*/  //
/*TODO*/  //            return Common.disasmVDVSVT("vmscl", 1 + one + (two << 1), vd, vs, vt);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction VCRSP = new Instruction(241, FLAG_USES_VFPU_PFXS | FLAG_USES_VFPU_PFXT |
          //    FLAG_USES_VFPU_PFXD | FLAG_COMPILED_PFX) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "VCRSP";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int vt = (insn >> 16) & 127;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doVCRSP(vd, vs, vt);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            context.startPfxCompiled();
/*TODO*/  //            final int vsize = 3;
/*TODO*/  //            MethodVisitor mv = context.getMethodVisitor();
/*TODO*/  //
/*TODO*/  //            // v3[0] = +v1[1] * v2[2] - v1[2] * v2[1];
/*TODO*/  //            context.prepareVdForStore(vsize, 0);
/*TODO*/  //            context.loadVs(vsize, 1);
/*TODO*/  //            context.loadVt(vsize, 2);
/*TODO*/  //            mv.visitInsn(Opcodes.FMUL);
/*TODO*/  //            context.loadVs(vsize, 2);
/*TODO*/  //            context.loadVt(vsize, 1);
/*TODO*/  //            mv.visitInsn(Opcodes.FMUL);
/*TODO*/  //            mv.visitInsn(Opcodes.FSUB);
/*TODO*/  //            context.storeVd(vsize, 0);
/*TODO*/  //
/*TODO*/  //            // v3[1] = +v1[2] * v2[0] - v1[0] * v2[2];
/*TODO*/  //            context.prepareVdForStore(vsize, 1);
/*TODO*/  //            context.loadVs(vsize, 2);
/*TODO*/  //            context.loadVt(vsize, 0);
/*TODO*/  //            mv.visitInsn(Opcodes.FMUL);
/*TODO*/  //            context.loadVs(vsize, 0);
/*TODO*/  //            context.loadVt(vsize, 2);
/*TODO*/  //            mv.visitInsn(Opcodes.FMUL);
/*TODO*/  //            mv.visitInsn(Opcodes.FSUB);
/*TODO*/  //            context.storeVd(vsize, 1);
/*TODO*/  //
/*TODO*/  //            // v3[2] = +v1[0] * v2[1] - v1[1] * v2[0];
/*TODO*/  //            context.prepareVdForStore(vsize, 2);
/*TODO*/  //            context.loadVs(vsize, 0);
/*TODO*/  //            context.loadVt(vsize, 1);
/*TODO*/  //            mv.visitInsn(Opcodes.FMUL);
/*TODO*/  //            context.loadVs(vsize, 1);
/*TODO*/  //            context.loadVt(vsize, 0);
/*TODO*/  //            mv.visitInsn(Opcodes.FMUL);
/*TODO*/  //            mv.visitInsn(Opcodes.FSUB);
/*TODO*/  //            context.storeVd(vsize, 2);
/*TODO*/  //
/*TODO*/  //            context.endPfxCompiled();
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int vt = (insn >> 16) & 127;
/*TODO*/  //
/*TODO*/  //            return Common.disasmVDVSVT("vcrsp", 3, vd, vs, vt);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction VQMUL = new Instruction(242, FLAG_USES_VFPU_PFXS | FLAG_USES_VFPU_PFXT |
          //    FLAG_USES_VFPU_PFXD) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "VQMUL";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int vt = (insn >> 16) & 127;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doVQMUL(vd, vs, vt);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            super.compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int vt = (insn >> 16) & 127;
/*TODO*/  //
/*TODO*/  //            return Common.disasmVDVSVT("VQMUL", 4, vd, vs, vt);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction VMMOV = new Instruction(243, FLAG_USES_VFPU_PFXS | FLAG_USES_VFPU_PFXD |
          //    FLAG_COMPILED_PFX) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "VMMOV";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doVMMOV(1 + one + (two << 1), vd, vs);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            final int vsize = context.getVsize();
/*TODO*/  //            final int vd = context.getVdRegisterIndex();
/*TODO*/  //            final int vs = context.getVsRegisterIndex();
/*TODO*/  //            if (vsize == 4 && ((vd | vs) & (32 | 64)) == 0 && context.hasNoPfx()) {
/*TODO*/  //                // Simple case which can be implemented using an array copy.
/*TODO*/  //                int vsVprIndex = VfpuState.getVprIndex((vs >> 2) & 7, vs & 3, 0);
/*TODO*/  //                int vdVprIndex = VfpuState.getVprIndex((vd >> 2) & 7, vd & 3, 0);
/*TODO*/  //
/*TODO*/  //                context.loadVprInt();
/*TODO*/  //                context.loadImm(vsVprIndex);
/*TODO*/  //                context.loadVprInt();
/*TODO*/  //                context.loadImm(vdVprIndex);
/*TODO*/  //                context.loadImm(16);
/*TODO*/  //                context.invokeStaticMethod(Type.getInternalName(System.class), "arraycopy",
          //                arraycopyDescriptor);
/*TODO*/  //
/*TODO*/  //                context.loadVprFloat();
/*TODO*/  //                context.loadImm(vsVprIndex);
/*TODO*/  //                context.loadVprFloat();
/*TODO*/  //                context.loadImm(vdVprIndex);
/*TODO*/  //                context.loadImm(16);
/*TODO*/  //                context.invokeStaticMethod(Type.getInternalName(System.class), "arraycopy",
          //                arraycopyDescriptor);
/*TODO*/  //            } else {
/*TODO*/  //                context.startPfxCompiled(false);
/*TODO*/  //                for (int i = 0; i < vsize; i++) {
/*TODO*/  //                    for (int n = 0; n < vsize; n++) {
/*TODO*/  //                        context.prepareVdForStoreInt(vsize, vd + i, n);
/*TODO*/  //                        context.loadVsInt(vsize, vs + i, n);
/*TODO*/  //                        context.storeVdInt(vsize, vd + i, n);
/*TODO*/  //                    }
/*TODO*/  //                    context.flushPfxCompiled(vsize, vd + i, false);
/*TODO*/  //                }
/*TODO*/  //                context.endPfxCompiled(vsize, false, false);
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //
/*TODO*/  //            return Common.disasmVDMVSM("VMMOV", 1 + one + (two << 1), vd, vs);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction VMIDT = new Instruction(244, FLAG_USES_VFPU_PFXD | FLAG_COMPILED_PFX) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "VMIDT";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doVMIDT(1 + one + (two << 1), vd);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            context.startPfxCompiled();
/*TODO*/  //            int vsize = context.getVsize();
/*TODO*/  //            int vd = context.getVdRegisterIndex();
/*TODO*/  //            for (int i = 0; i < vsize; i++) {
/*TODO*/  //                for (int n = 0; n < vsize; n++) {
/*TODO*/  //                    context.prepareVdForStore(vsize, vd + i, n);
/*TODO*/  //                    context.getMethodVisitor().visitInsn(i == n ? Opcodes.FCONST_1 : Opcodes.FCONST_0);
/*TODO*/  //                    context.storeVd(vsize, vd + i, n);
/*TODO*/  //                }
/*TODO*/  //                context.flushPfxCompiled(vsize, vd + i, true);
/*TODO*/  //            }
/*TODO*/  //            context.endPfxCompiled(vsize, true, false);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //
/*TODO*/  //            return Common.disasmVDM("VMIDT", 1 + one + (two << 1), vd);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction VMZERO = new Instruction(245, FLAG_USES_VFPU_PFXD | FLAG_COMPILED_PFX) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "VMZERO";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doVMZERO(1 + one + (two << 1), vd);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            context.startPfxCompiled();
/*TODO*/  //            int vsize = context.getVsize();
/*TODO*/  //            int vd = context.getVdRegisterIndex();
/*TODO*/  //            for (int i = 0; i < vsize; i++) {
/*TODO*/  //                for (int n = 0; n < vsize; n++) {
/*TODO*/  //                    context.prepareVdForStore(vsize, vd + i, n);
/*TODO*/  //                    context.getMethodVisitor().visitInsn(Opcodes.FCONST_0);
/*TODO*/  //                    context.storeVd(vsize, vd + i, n);
/*TODO*/  //                }
/*TODO*/  //                context.flushPfxCompiled(vsize, vd + i, true);
/*TODO*/  //            }
/*TODO*/  //            context.endPfxCompiled(vsize, true, false);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //
/*TODO*/  //            return Common.disasmVDM("VMZERO", 1 + one + (two << 1), vd);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction VMONE = new Instruction(246, FLAG_USES_VFPU_PFXD | FLAG_COMPILED_PFX) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "VMONE";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doVMONE(1 + one + (two << 1), vd);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            context.startPfxCompiled();
/*TODO*/  //            int vsize = context.getVsize();
/*TODO*/  //            int vd = context.getVdRegisterIndex();
/*TODO*/  //            for (int i = 0; i < vsize; i++) {
/*TODO*/  //                for (int n = 0; n < vsize; n++) {
/*TODO*/  //                    context.prepareVdForStore(vsize, vd + i, n);
/*TODO*/  //                    context.getMethodVisitor().visitInsn(Opcodes.FCONST_1);
/*TODO*/  //                    context.storeVd(vsize, vd + i, n);
/*TODO*/  //                }
/*TODO*/  //                context.flushPfxCompiled(vsize, vd + i, true);
/*TODO*/  //            }
/*TODO*/  //            context.endPfxCompiled(vsize, true, false);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //
/*TODO*/  //            return Common.disasmVDM("VMONE", 1 + one + (two << 1), vd);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction VROT = new Instruction(247, FLAG_USES_VFPU_PFXS | FLAG_USES_VFPU_PFXD |
          //    FLAG_COMPILED_PFX) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "VROT";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //            int imm5 = (insn >> 16) & 31;
/*TODO*/  //
/*TODO*/  //            processor.cpu.doVROT(1 + one + (two << 1), vd, vs, imm5);
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            context.startPfxCompiled();
/*TODO*/  //            int vsize = context.getVsize();
/*TODO*/  //            int imm5 = context.getImm5();
/*TODO*/  //            int si = (imm5 >>> 2) & 3;
/*TODO*/  //            int ci = (imm5 >>> 0) & 3;
/*TODO*/  //            MethodVisitor mv = context.getMethodVisitor();
/*TODO*/  //
/*TODO*/  //            Label isNotZero = new Label();
/*TODO*/  //            Label isNotOne = new Label();
/*TODO*/  //            Label isNotTwo = new Label();
/*TODO*/  //            Label computeAngle = new Label();
/*TODO*/  //            Label computeResult = new Label();
/*TODO*/  //
/*TODO*/  //            context.loadVs(1, 0);
/*TODO*/  //            // Reduce the angle to [0..4[
/*TODO*/  //            mv.visitInsn(Opcodes.DUP);
/*TODO*/  //            mv.visitLdcInsn(0.25f);
/*TODO*/  //            mv.visitInsn(Opcodes.FMUL);
/*TODO*/  //            mv.visitInsn(Opcodes.F2D);
/*TODO*/  //            context.invokeStaticMethod(Type.getInternalName(Math.class), "floor", "(D)D");
/*TODO*/  //            mv.visitInsn(Opcodes.D2F);
/*TODO*/  //            mv.visitLdcInsn(4f);
/*TODO*/  //            mv.visitInsn(Opcodes.FMUL);
/*TODO*/  //            mv.visitInsn(Opcodes.FSUB);
/*TODO*/  //            // Special case 0.0
/*TODO*/  //            mv.visitInsn(Opcodes.DUP);
/*TODO*/  //            mv.visitInsn(Opcodes.FCONST_0);
/*TODO*/  //            mv.visitInsn(Opcodes.FCMPG);
/*TODO*/  //            mv.visitJumpInsn(Opcodes.IFNE, isNotZero);
/*TODO*/  //            mv.visitInsn(Opcodes.POP);
/*TODO*/  //            mv.visitInsn(Opcodes.FCONST_1);
/*TODO*/  //            context.storeFTmp1();
/*TODO*/  //            mv.visitInsn(Opcodes.FCONST_0);
/*TODO*/  //            context.storeFTmp2();
/*TODO*/  //            mv.visitJumpInsn(Opcodes.GOTO, computeResult);
/*TODO*/  //            // Special case 1.0
/*TODO*/  //            mv.visitLabel(isNotZero);
/*TODO*/  //            mv.visitInsn(Opcodes.DUP);
/*TODO*/  //            mv.visitInsn(Opcodes.FCONST_1);
/*TODO*/  //            mv.visitInsn(Opcodes.FCMPG);
/*TODO*/  //            mv.visitJumpInsn(Opcodes.IFNE, isNotOne);
/*TODO*/  //            mv.visitInsn(Opcodes.POP);
/*TODO*/  //            mv.visitInsn(Opcodes.FCONST_0);
/*TODO*/  //            context.storeFTmp1();
/*TODO*/  //            mv.visitInsn(Opcodes.FCONST_1);
/*TODO*/  //            if ((imm5 & 16) != 0) {
/*TODO*/  //                mv.visitInsn(Opcodes.FNEG);
/*TODO*/  //            }
/*TODO*/  //            context.storeFTmp2();
/*TODO*/  //            mv.visitJumpInsn(Opcodes.GOTO, computeResult);
/*TODO*/  //            // Special case 2.0
/*TODO*/  //            mv.visitLabel(isNotOne);
/*TODO*/  //            mv.visitInsn(Opcodes.DUP);
/*TODO*/  //            mv.visitInsn(Opcodes.FCONST_2);
/*TODO*/  //            mv.visitInsn(Opcodes.FCMPG);
/*TODO*/  //            mv.visitJumpInsn(Opcodes.IFNE, isNotTwo);
/*TODO*/  //            mv.visitInsn(Opcodes.POP);
/*TODO*/  //            mv.visitInsn(Opcodes.FCONST_1);
/*TODO*/  //            mv.visitInsn(Opcodes.FNEG);
/*TODO*/  //            context.storeFTmp1();
/*TODO*/  //            mv.visitInsn(Opcodes.FCONST_0);
/*TODO*/  //            context.storeFTmp2();
/*TODO*/  //            mv.visitJumpInsn(Opcodes.GOTO, computeResult);
/*TODO*/  //            // Special case 3.0
/*TODO*/  //            mv.visitLabel(isNotTwo);
/*TODO*/  //            mv.visitInsn(Opcodes.DUP);
/*TODO*/  //            mv.visitLdcInsn(3f);
/*TODO*/  //            mv.visitInsn(Opcodes.FCMPG);
/*TODO*/  //            mv.visitJumpInsn(Opcodes.IFNE, computeAngle);
/*TODO*/  //            mv.visitInsn(Opcodes.POP);
/*TODO*/  //            mv.visitInsn(Opcodes.FCONST_0);
/*TODO*/  //            context.storeFTmp1();
/*TODO*/  //            mv.visitInsn(Opcodes.FCONST_1);
/*TODO*/  //            if ((imm5 & 16) == 0) {
/*TODO*/  //                mv.visitInsn(Opcodes.FNEG);
/*TODO*/  //            }
/*TODO*/  //            context.storeFTmp2();
/*TODO*/  //            mv.visitJumpInsn(Opcodes.GOTO, computeResult);
/*TODO*/  //            // General case
/*TODO*/  //            mv.visitLabel(computeAngle);
/*TODO*/  //            mv.visitInsn(Opcodes.F2D);
/*TODO*/  //            mv.visitLdcInsn(Math.PI * 0.5);
/*TODO*/  //            mv.visitInsn(Opcodes.DMUL);
/*TODO*/  //
/*TODO*/  //            // Compute cos(angle)
/*TODO*/  //            mv.visitInsn(Opcodes.DUP2);
/*TODO*/  //            context.invokeStaticMethod(Type.getInternalName(Math.class), "cos", "(D)D");
/*TODO*/  //            mv.visitInsn(Opcodes.D2F);
/*TODO*/  //            context.storeFTmp1();
/*TODO*/  //
/*TODO*/  //            // Compute sin(angle)
/*TODO*/  //            context.invokeStaticMethod(Type.getInternalName(Math.class), "sin", "(D)D");
/*TODO*/  //            mv.visitInsn(Opcodes.D2F);
/*TODO*/  //            if ((imm5 & 16) != 0) {
/*TODO*/  //                mv.visitInsn(Opcodes.FNEG);
/*TODO*/  //            }
/*TODO*/  //            context.storeFTmp2();
/*TODO*/  //
/*TODO*/  //            mv.visitLabel(computeResult);
/*TODO*/  //            for (int n = 0; n < vsize; n++) {
/*TODO*/  //                context.prepareVdForStore(n);
/*TODO*/  //                if (n == ci) {
/*TODO*/  //                    context.loadFTmp1();
/*TODO*/  //                } else if (si == ci || n == si) {
/*TODO*/  //                    context.loadFTmp2();
/*TODO*/  //                } else {
/*TODO*/  //                    mv.visitInsn(Opcodes.FCONST_0);
/*TODO*/  //                }
/*TODO*/  //                context.storeVd(n);
/*TODO*/  //            }
/*TODO*/  //            context.endPfxCompiled();
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int vd = (insn >> 0) & 127;
/*TODO*/  //            int one = (insn >> 7) & 1;
/*TODO*/  //            int vs = (insn >> 8) & 127;
/*TODO*/  //            int two = (insn >> 15) & 1;
/*TODO*/  //            int imm5 = (insn >> 16) & 31;
/*TODO*/  //
/*TODO*/  //            return Common.disasmVROT("VROT", 1 + one + (two << 1), vd, vs, imm5);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction VNOP = new Instruction(248) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "VNOP";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //
/*TODO*/  //            return "vnop";
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction VFLUSH = new Instruction(249) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "VFLUSH";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            // Nothing to compile
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //
/*TODO*/  //            return "vflush";
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction VSYNC = new Instruction(250) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "VSYNC";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "VFPU";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            // Nothing to compile
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //
/*TODO*/  //            return "vsync";
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction DBREAK = new Instruction(251) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "DBREAK";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "ME";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            if (processor.cp0.isMainCpu()) {
/*TODO*/  //                processor.cpu.doUNK(String.format("Unsupported dbreak instruction on the main processor:
          //                0x%08X: [0x%08X]", processor.cpu.pc, insn));
/*TODO*/  //            } else {
/*TODO*/  //                processor.cpu.pc = 0xBFC01000;
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            super.compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            return "dbreak";
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction MTVME = new Instruction(252) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "MTVME";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "ME";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //            if (processor.cp0.isMainCpu()) {
/*TODO*/  //                processor.cpu.doUNK(String.format("Unsupported mtvme instruction on the main processor:
          //                0x%08X: [0x%08X]", processor.cpu.pc, insn));
/*TODO*/  //            } else if (processor instanceof MEProcessor) {
/*TODO*/  //                ((MEProcessor) processor).setVmeRegister(imm16, processor.cpu.getRegister(rt));
/*TODO*/  //            } else {
/*TODO*/  //                processor.cpu.doUNK(String.format("Unsupported processor for mtvme instruction is not an
          //                MEProcessor: 0x%08X: [0x%08X]", processor.cpu.pc, insn));
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            super.compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //            return Common.disasmRTVME("mtvme", rt, imm16);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //    public static final Instruction MFVME = new Instruction(253) {
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String name() {
/*TODO*/  //            return "MFVME";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public final String category() {
/*TODO*/  //            return "ME";
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void interpret(Processor processor, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //            if (processor.cp0.isMainCpu()) {
/*TODO*/  //                processor.cpu.doUNK(String.format("Unsupported mfvme instruction on the main processor:
          //                0x%08X: [0x%08X]", processor.cpu.pc, insn));
/*TODO*/  //            } else if (processor instanceof MEProcessor) {
/*TODO*/  //                processor.cpu.setRegister(rt, ((MEProcessor) processor).getVmeRegister(imm16));
/*TODO*/  //            } else {
/*TODO*/  //                processor.cpu.doUNK(String.format("Unsupported processor for mfvme instruction is not an
          //                MEProcessor: 0x%08X: [0x%08X]", processor.cpu.pc, insn));
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public void compile(ICompilerContext context, int insn) {
/*TODO*/  //            super.compile(context, insn);
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        @Override
/*TODO*/  //        public String disasm(int address, int insn) {
/*TODO*/  //            int imm16 = (insn >> 0) & 65535;
/*TODO*/  //            int rt = (insn >> 16) & 31;
/*TODO*/  //            return Common.disasmRTVME("mfvme", rt, imm16);
/*TODO*/  //        }
/*TODO*/  //    };
/*TODO*/  //}
/*TODO*/  //
}
