#ifndef __allegrex_instruction_h__
#define __allegrex_instruction_h__

#include "types.h"
#include <stdio.h>
#include <stdlib.h>

struct AllegrexInstructionBase;
struct AllegrexInstruction;
template< int signature, int mask > struct AllegrexInstructionTemplate;
struct basic_block_s;
struct super_block_s;

struct AllegrexInstructionBase
{
	typedef int index_t;

	virtual ~AllegrexInstructionBase() {}

protected:
	AllegrexInstructionBase() {}
};

class Emulator;
struct AlContext;

struct AllegrexInstruction : AllegrexInstructionBase
{
	virtual u64 infos() { return 0; }

	typedef int index_t;

	u32 opcode;
	u32 address;
#ifdef USE_DYNAREC
	basic_block_s *parent;
	index_t delayed;
	index_t prefix;
	index_t register_writes[2]; // rd, rt, hi:lo, fd, vd
	index_t register_reads[3]; // rs, rt, rd, fs, ft, vs, vt
	short branch_target : 1, count : 7;
#else
	u32 branch_target : 1;
#endif

	virtual ~AllegrexInstruction() {}

	virtual char const *OpcodeName() = 0;

	virtual void Interpret(AlContext &processor, u32 opcode) = 0;

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment) = 0;

	static insn_count_t dummy_count;

	virtual insn_count_t &GetCount() { return dummy_count; }

	virtual bool IsBranch()
	{
		return false;
	}

	virtual bool IsReturnJump()
	{
		return false;
	}

	unsigned int GetOpcode()
	{
		return (unsigned int)opcode;
	}

	bool IsBranchTarget()
	{
		return this->branch_target;
	}

	void SetBranchTarget();

	virtual bool IsNop()
	{
		return false;
	}


	static inline u32 rd(u32 opcode) { return ((((u32)opcode) >> 11)&31); }
    static inline u32 rt(u32 opcode) { return ((((u32)opcode) >> 16)&31); }
    static inline u32 rs(u32 opcode) { return ((((u32)opcode) >> 21)&31); }

	static inline u32 sa(u32 opcode) { return ((((u32)opcode) >> 6)&31); }

	static inline s32 simm16(u32 opcode) { return (s32)(s16)opcode; }
	static inline u32 uimm16(u32 opcode) { return (u32)(u16)opcode; }
	static inline u32 uimm20(u32 opcode) { return (opcode >> 6) & 0x000FFFFF; }
    static inline u32 uimm24(u32 opcode) { return opcode & 0x00FFFFFF; }
    static inline u32 uimm26(u32 opcode) { return opcode & 0x03FFFFFF; }

	static inline u32 fd(u32 opcode) { return ((((u32)opcode) >> 6)&31); }
	static inline u32 fs(u32 opcode) { return ((((u32)opcode) >> 11)&31); }
	static inline u32 ft(u32 opcode) { return ((((u32)opcode) >> 16)&31); }

	static inline u32 cconds(u32 opcode) { return ((((u32)opcode) >> 0)&15); }

	static inline u32 vsize(u32 opcode) { return (1 + ((opcode >> 7) & 1) + (((opcode >> 15) & 1) << 1)); }

    static inline u32 vt(u32 opcode) { return ((opcode >> 16) & 127); }
	static inline u32 vs(u32 opcode) { return ((opcode >>  8) & 127); }
    static inline u32 vd(u32 opcode) { return ((opcode >>  0) & 127); }

    static inline u32 vt51(u32 opcode) { return (((opcode >> 16) & 31)|(((opcode >> 0) & 1) << 5)); }
    static inline u32 vt52(u32 opcode) { return (((opcode >> 16) & 31)|(((opcode >> 0) & 3) << 5)); }

	static inline s32 simm14(u32 opcode) { return (s32)(s16)(opcode & 0x0000FFFC); }
    static inline u32 uimm8(u32 opcode) { return ((opcode >> 16) & 255); }
    static inline u32 uimm5(u32 opcode) { return ((opcode >> 16) & 31);	}
    static inline u32 uimm4(u32 opcode) { return ((opcode >>  0) & 15);	}
    static inline u32 uimm3(u32 opcode) { return ((opcode >> 16) & 7); }

#ifdef USE_DYNAREC
	virtual AllegrexInstruction *clone() = 0;

	virtual bool pass1() = 0;

	virtual bool pass2() = 0;

	virtual int get_max_stack_height()
	{
		return 2;
	}

	virtual bool has_delay_slot()
	{
		return this->IsBranch();
	}

	virtual bool is_delay_slot_nop()
	{
		return false;
	}

	virtual int fill_outputs(int *p) { return 0; };

	virtual int fill_inputs(int *p) { return 0; };

	typedef struct factory_s
	{
		static AllegrexInstruction *create(unsigned int address, unsigned int opcode);

		static AllegrexInstruction *create_nop(unsigned int address);

		static AllegrexInstruction *create_delay_slot_nop(unsigned int address);

		static AllegrexInstruction *create_tail_call_jump(unsigned int address, int extra);

		static AllegrexInstruction __attribute__((aligned(32))) instructions[32768];

		static AllegrexInstruction *free_instructions;

		factory_s()
		{
			::memset(instructions, 0, sizeof(instructions));

			AllegrexInstruction *free_instruction = 0;

			for (AllegrexInstruction *i = instructions + 32767; i >= instructions; --i)
			{
				*((AllegrexInstruction **)i) = free_instruction;
				free_instruction = i;
			}
			free_instructions = free_instruction;
		}
	} factory_t;

	void set_delayed(AllegrexInstruction *delayed)
	{
		this->delayed = delayed - &(factory_t::instructions[0]);
	}

	AllegrexInstruction *get_delayed()
	{
		return &factory_t::instructions[this->delayed];
	}

	bool has_delayed()
	{
		return this->delayed != 0;
	}

	void set_prefix(AllegrexInstruction *prefix)
	{
		this->prefix = prefix - &(factory_t::instructions[0]);
	}

	bool has_prefix()
	{
		return this->prefix != 0;
	}

	AllegrexInstruction *get_prefix()
	{
		return &factory_t::instructions[this->prefix];
	}

	AllegrexInstruction *get_previous_register_write(int which)
	{
		return &factory_t::instructions[this->register_writes[which]];
	}

	AllegrexInstruction *get_previous_register_read(int which)
	{
		return &factory_t::instructions[this->register_reads[which]];
	}

	void set_previous_register_read(AllegrexInstruction *insn, int which)
	{
		this->register_reads[which] = insn - &(factory_t::instructions[0]);
	}

	void set_previous_register_write(AllegrexInstruction *insn, int which)
	{
		this->register_writes[which] = insn - &(factory_t::instructions[0]);
	}
#endif
};

struct AllegrexInstructionUnknown : AllegrexInstruction
{
	static AllegrexInstructionUnknown &Self()
	{
		static AllegrexInstructionUnknown insn;
		return insn;
	}

	static AllegrexInstruction *GetInstance()
	{
		return &AllegrexInstructionUnknown::Self();
	}

	virtual char const *OpcodeName()
	{
		return "???";
	}

    virtual void Interpret(AlContext &UNUSED(processor), u32 UNUSED(opcode))
	{
	}

    virtual void Disassemble(u32 UNUSED(address), u32 opcode, char *opcode_name, char *operands, char *comment)
	{
		::strcpy(opcode_name, this->OpcodeName());
		::strcpy(operands, "");
		::sprintf(comment, "unknown or reserved instruction 0x%08X", opcode);
	}

	virtual u64 Infos() { return 0LL; }

#ifdef USE_DYNAREC
	virtual AllegrexInstruction *clone()
	{
		//  return (instruction_s *)instruction_s::new(this) allegrex_n::intruction_template_s< opcode, mask >(opcode);
		return (AllegrexInstruction *)new Allegrex::instruction_template_s(opcode);
	}

	virtual bool pass1()
	{
		return false;
	}

	virtual bool pass2()
	{
		return false;
	}

#endif
};

struct AllegrexBreakpoint : AllegrexInstruction
{
	u32					 count;
	AllegrexInstruction *insn;
	bool				 temporary;

	static AllegrexBreakpoint *DecodeOpcode(u32 opcode);

	static AllegrexBreakpoint &self()
	{
		static AllegrexBreakpoint insn;
		return insn;
	}

	AllegrexBreakpoint() : count(1), insn(0), temporary(true)
	{
		this->opcode = 0x9FFFFFFF;
		this->address = 0;
	}

	AllegrexBreakpoint(u32 opcode, u32 address, AllegrexInstruction *insn, bool temporary) : count(1), insn(insn), temporary(temporary)
	{
		this->opcode = opcode;
		this->address = address;
	}

	virtual char const *OpcodeName()
	{
		return "brkpt";
	}

	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);

	virtual u64 infos();
};

template< int signature, int mask > struct AllegrexInstructionTemplate : AllegrexInstructionUnknown
{
};

namespace Allegrex
{
	extern AllegrexInstructionUnknown &reserved_instruction;

	extern char const * gpr_name[32];

	extern char const * fpr_name[32];

	extern char const * vpr_name[4][128];

	extern char const * mpr_name[4][128];

	extern char const * vfpu_constant[32];

	extern char const * fcr_name[32];

	extern char const * cop0_name[32];

	extern char const * vsuffix[4];

	extern char const * vpfx_name[4];

	extern char const * cconds_name[16];

	extern char const * vcond_name[16];
}

#include "al_instructions.h"

#endif // __allegrex_instruction_h__
