/*
 *  01/06/2022 - synced with jpcsp 31/05/2022 - 9084111 - TODO 
 */
#pragma once
#include "..\PCSPCommon.h"

class Instruction : public std::enable_shared_from_this<Instruction> {
    /*TODO*/  //    	protected static Logger log = Emulator.log;
    /*TODO*/  //    	protected static Logger logCop0 = Logger.getLogger("cop0");
    /*TODO*/  //    	protected static Logger logCache = Logger.getLogger("cache");
  private:
    int m_count = 0;
    int flags = 0;
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
  public:
    virtual void interpret(int insn) = 0;
    /*TODO*/  //        public void compile(ICompilerContext context, int insn) {
    /*TODO*/  //            flags |= FLAG_INTERPRETED;
    /*TODO*/  //            context.compileInterpreterInstruction();
    /*TODO*/  //        }
    /*TODO*/  //
    virtual std::string disasm(int address, int insn) = 0;
    virtual std::string name() = 0;
    virtual std::string name() = 0;
    void resetCount() {
        m_count = 0;
    }
    void increaseCount() {
        m_count++;
    }
    int getCount() {
        return m_count;
    }
    int count() {
        return m_count;
    }
    std::shared_ptr<Instruction> instance(int insn) 
    { 
        return shared_from_this(); 
    }
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
}
