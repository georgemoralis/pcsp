/* ADD */
template< > struct AllegrexInstructionTemplate< 0x00000020, 0xFC0007FF > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "ADD"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x00000020, 0xFC0007FF > AllegrexInstruction_ADD;

namespace Allegrex { extern AllegrexInstruction_ADD &ADD; }

/* ADDI */
template< > struct AllegrexInstructionTemplate< 0x20000000, 0xFC000000 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "ADDI"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x20000000, 0xFC000000 > AllegrexInstruction_ADDI;

namespace Allegrex { extern AllegrexInstruction_ADDI &ADDI; }

/* ADDU */
template< > struct AllegrexInstructionTemplate< 0x00000021, 0xFC0007FF > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "ADDU"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x00000021, 0xFC0007FF > AllegrexInstruction_ADDU;

namespace Allegrex { extern AllegrexInstruction_ADDU &ADDU; }

/* ADDIU */
template< > struct AllegrexInstructionTemplate< 0x24000000, 0xFC000000 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "ADDIU"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x24000000, 0xFC000000 > AllegrexInstruction_ADDIU;

namespace Allegrex { extern AllegrexInstruction_ADDIU &ADDIU; }

/* AND */
template< > struct AllegrexInstructionTemplate< 0x00000024, 0xFC0007FF > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "AND"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x00000024, 0xFC0007FF > AllegrexInstruction_AND;

namespace Allegrex { extern AllegrexInstruction_AND &AND; }

/* ANDI */
template< > struct AllegrexInstructionTemplate< 0x30000000, 0xFC000000 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "ANDI"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x30000000, 0xFC000000 > AllegrexInstruction_ANDI;

namespace Allegrex { extern AllegrexInstruction_ANDI &ANDI; }

/* NOR */
template< > struct AllegrexInstructionTemplate< 0x00000027, 0xFC0007FF > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "NOR"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x00000027, 0xFC0007FF > AllegrexInstruction_NOR;

namespace Allegrex { extern AllegrexInstruction_NOR &NOR; }

/* OR */
template< > struct AllegrexInstructionTemplate< 0x00000025, 0xFC0007FF > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "OR"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x00000025, 0xFC0007FF > AllegrexInstruction_OR;

namespace Allegrex { extern AllegrexInstruction_OR &OR; }

/* ORI */
template< > struct AllegrexInstructionTemplate< 0x34000000, 0xFC000000 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "ORI"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x34000000, 0xFC000000 > AllegrexInstruction_ORI;

namespace Allegrex { extern AllegrexInstruction_ORI &ORI; }

/* XOR */
template< > struct AllegrexInstructionTemplate< 0x00000026, 0xFC0007FF > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "XOR"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x00000026, 0xFC0007FF > AllegrexInstruction_XOR;

namespace Allegrex { extern AllegrexInstruction_XOR &XOR; }

/* XORI */
template< > struct AllegrexInstructionTemplate< 0x38000000, 0xFC000000 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "XORI"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x38000000, 0xFC000000 > AllegrexInstruction_XORI;

namespace Allegrex { extern AllegrexInstruction_XORI &XORI; }

/* SLL */
template< > struct AllegrexInstructionTemplate< 0x00000000, 0xFFE0003F > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "SLL"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x00000000, 0xFFE0003F > AllegrexInstruction_SLL;

namespace Allegrex { extern AllegrexInstruction_SLL &SLL; }

/* SLLV */
template< > struct AllegrexInstructionTemplate< 0x00000004, 0xFC0007FF > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "SLLV"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x00000004, 0xFC0007FF > AllegrexInstruction_SLLV;

namespace Allegrex { extern AllegrexInstruction_SLLV &SLLV; }

/* SRA */
template< > struct AllegrexInstructionTemplate< 0x00000003, 0xFFE0003F > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "SRA"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x00000003, 0xFFE0003F > AllegrexInstruction_SRA;

namespace Allegrex { extern AllegrexInstruction_SRA &SRA; }

/* SRAV */
template< > struct AllegrexInstructionTemplate< 0x00000007, 0xFC0007FF > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "SRAV"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x00000007, 0xFC0007FF > AllegrexInstruction_SRAV;

namespace Allegrex { extern AllegrexInstruction_SRAV &SRAV; }

/* SRL */
template< > struct AllegrexInstructionTemplate< 0x00000002, 0xFFE0003F > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "SRL"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x00000002, 0xFFE0003F > AllegrexInstruction_SRL;

namespace Allegrex { extern AllegrexInstruction_SRL &SRL; }

/* SRLV */
template< > struct AllegrexInstructionTemplate< 0x00000006, 0xFC0007FF > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "SRLV"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x00000006, 0xFC0007FF > AllegrexInstruction_SRLV;

namespace Allegrex { extern AllegrexInstruction_SRLV &SRLV; }

/* ROTR */
template< > struct AllegrexInstructionTemplate< 0x00200002, 0xFFE0003F > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "ROTR"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x00200002, 0xFFE0003F > AllegrexInstruction_ROTR;

namespace Allegrex { extern AllegrexInstruction_ROTR &ROTR; }

/* ROTRV */
template< > struct AllegrexInstructionTemplate< 0x00000046, 0xFC0007FF > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "ROTRV"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x00000046, 0xFC0007FF > AllegrexInstruction_ROTRV;

namespace Allegrex { extern AllegrexInstruction_ROTRV &ROTRV; }

/* SLT */
template< > struct AllegrexInstructionTemplate< 0x0000002A, 0xFC0007FF > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "SLT"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x0000002A, 0xFC0007FF > AllegrexInstruction_SLT;

namespace Allegrex { extern AllegrexInstruction_SLT &SLT; }

/* SLTI */
template< > struct AllegrexInstructionTemplate< 0x28000000, 0xFC000000 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "SLTI"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x28000000, 0xFC000000 > AllegrexInstruction_SLTI;

namespace Allegrex { extern AllegrexInstruction_SLTI &SLTI; }

/* SLTU */
template< > struct AllegrexInstructionTemplate< 0x0000002B, 0xFC0007FF > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "SLTU"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x0000002B, 0xFC0007FF > AllegrexInstruction_SLTU;

namespace Allegrex { extern AllegrexInstruction_SLTU &SLTU; }

/* SLTIU */
template< > struct AllegrexInstructionTemplate< 0x2C000000, 0xFC000000 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "SLTIU"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x2C000000, 0xFC000000 > AllegrexInstruction_SLTIU;

namespace Allegrex { extern AllegrexInstruction_SLTIU &SLTIU; }

/* SUB */
template< > struct AllegrexInstructionTemplate< 0x00000022, 0xFC0007FF > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "SUB"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x00000022, 0xFC0007FF > AllegrexInstruction_SUB;

namespace Allegrex { extern AllegrexInstruction_SUB &SUB; }

/* SUBU */
template< > struct AllegrexInstructionTemplate< 0x00000023, 0xFC0007FF > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "SUBU"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x00000023, 0xFC0007FF > AllegrexInstruction_SUBU;

namespace Allegrex { extern AllegrexInstruction_SUBU &SUBU; }

/* LUI */
template< > struct AllegrexInstructionTemplate< 0x3C000000, 0xFFE00000 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "LUI"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x3C000000, 0xFFE00000 > AllegrexInstruction_LUI;

namespace Allegrex { extern AllegrexInstruction_LUI &LUI; }

/* SEB */
template< > struct AllegrexInstructionTemplate< 0x7C000420, 0xFFE007FF > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "SEB"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x7C000420, 0xFFE007FF > AllegrexInstruction_SEB;

namespace Allegrex { extern AllegrexInstruction_SEB &SEB; }

/* SEH */
template< > struct AllegrexInstructionTemplate< 0x7C000620, 0xFFE007FF > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "SEH"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x7C000620, 0xFFE007FF > AllegrexInstruction_SEH;

namespace Allegrex { extern AllegrexInstruction_SEH &SEH; }

/* BITREV */
template< > struct AllegrexInstructionTemplate< 0x7C000520, 0xFFE007FF > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "BITREV"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x7C000520, 0xFFE007FF > AllegrexInstruction_BITREV;

namespace Allegrex { extern AllegrexInstruction_BITREV &BITREV; }

/* WSBH */
template< > struct AllegrexInstructionTemplate< 0x7C0000A0, 0xFFE007FF > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "WSBH"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x7C0000A0, 0xFFE007FF > AllegrexInstruction_WSBH;

namespace Allegrex { extern AllegrexInstruction_WSBH &WSBH; }

/* WSBW */
template< > struct AllegrexInstructionTemplate< 0x7C0000E0, 0xFFE007FF > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "WSBW"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x7C0000E0, 0xFFE007FF > AllegrexInstruction_WSBW;

namespace Allegrex { extern AllegrexInstruction_WSBW &WSBW; }

/* MOVZ */
template< > struct AllegrexInstructionTemplate< 0x0000000A, 0xFC0007FF > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "MOVZ"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x0000000A, 0xFC0007FF > AllegrexInstruction_MOVZ;

namespace Allegrex { extern AllegrexInstruction_MOVZ &MOVZ; }

/* MOVN */
template< > struct AllegrexInstructionTemplate< 0x0000000B, 0xFC0007FF > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "MOVN"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x0000000B, 0xFC0007FF > AllegrexInstruction_MOVN;

namespace Allegrex { extern AllegrexInstruction_MOVN &MOVN; }

/* MAX */
template< > struct AllegrexInstructionTemplate< 0x0000002C, 0xFC0007FF > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "MAX"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x0000002C, 0xFC0007FF > AllegrexInstruction_MAX;

namespace Allegrex { extern AllegrexInstruction_MAX &MAX; }

/* MIN */
template< > struct AllegrexInstructionTemplate< 0x0000002D, 0xFC0007FF > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "MIN"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x0000002D, 0xFC0007FF > AllegrexInstruction_MIN;

namespace Allegrex { extern AllegrexInstruction_MIN &MIN; }

/* CLZ */
template< > struct AllegrexInstructionTemplate< 0x00000016, 0xFC1F07FF > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "CLZ"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x00000016, 0xFC1F07FF > AllegrexInstruction_CLZ;

namespace Allegrex { extern AllegrexInstruction_CLZ &CLZ; }

/* CLO */
template< > struct AllegrexInstructionTemplate< 0x00000017, 0xFC1F07FF > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "CLO"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x00000017, 0xFC1F07FF > AllegrexInstruction_CLO;

namespace Allegrex { extern AllegrexInstruction_CLO &CLO; }

/* EXT */
template< > struct AllegrexInstructionTemplate< 0x7C000000, 0xFC00003F > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "EXT"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x7C000000, 0xFC00003F > AllegrexInstruction_EXT;

namespace Allegrex { extern AllegrexInstruction_EXT &EXT; }

/* INS */
template< > struct AllegrexInstructionTemplate< 0x7C000004, 0xFC00003F > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "INS"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x7C000004, 0xFC00003F > AllegrexInstruction_INS;

namespace Allegrex { extern AllegrexInstruction_INS &INS; }

/* MULT */
template< > struct AllegrexInstructionTemplate< 0x00000018, 0xFC00FFFF > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "MULT"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x00000018, 0xFC00FFFF > AllegrexInstruction_MULT;

namespace Allegrex { extern AllegrexInstruction_MULT &MULT; }

/* MULTU */
template< > struct AllegrexInstructionTemplate< 0x00000019, 0xFC00FFFF > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "MULTU"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x00000019, 0xFC00FFFF > AllegrexInstruction_MULTU;

namespace Allegrex { extern AllegrexInstruction_MULTU &MULTU; }

/* MADD */
template< > struct AllegrexInstructionTemplate< 0x0000001C, 0xFC00FFFF > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "MADD"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x0000001C, 0xFC00FFFF > AllegrexInstruction_MADD;

namespace Allegrex { extern AllegrexInstruction_MADD &MADD; }

/* MADDU */
template< > struct AllegrexInstructionTemplate< 0x0000001D, 0xFC00FFFF > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "MADDU"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x0000001D, 0xFC00FFFF > AllegrexInstruction_MADDU;

namespace Allegrex { extern AllegrexInstruction_MADDU &MADDU; }

/* MSUB */
template< > struct AllegrexInstructionTemplate< 0x0000002E, 0xFC00FFFF > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "MSUB"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x0000002E, 0xFC00FFFF > AllegrexInstruction_MSUB;

namespace Allegrex { extern AllegrexInstruction_MSUB &MSUB; }

/* MSUBU */
template< > struct AllegrexInstructionTemplate< 0x0000002F, 0xFC00FFFF > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "MSUBU"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x0000002F, 0xFC00FFFF > AllegrexInstruction_MSUBU;

namespace Allegrex { extern AllegrexInstruction_MSUBU &MSUBU; }

/* DIV */
template< > struct AllegrexInstructionTemplate< 0x0000001A, 0xFC00FFFF > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "DIV"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x0000001A, 0xFC00FFFF > AllegrexInstruction_DIV;

namespace Allegrex { extern AllegrexInstruction_DIV &DIV; }

/* DIVU */
template< > struct AllegrexInstructionTemplate< 0x0000001B, 0xFC00FFFF > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "DIVU"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x0000001B, 0xFC00FFFF > AllegrexInstruction_DIVU;

namespace Allegrex { extern AllegrexInstruction_DIVU &DIVU; }

/* MFHI */
template< > struct AllegrexInstructionTemplate< 0x00000010, 0xFFFF07FF > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "MFHI"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x00000010, 0xFFFF07FF > AllegrexInstruction_MFHI;

namespace Allegrex { extern AllegrexInstruction_MFHI &MFHI; }

/* MFLO */
template< > struct AllegrexInstructionTemplate< 0x00000012, 0xFFFF07FF > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "MFLO"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x00000012, 0xFFFF07FF > AllegrexInstruction_MFLO;

namespace Allegrex { extern AllegrexInstruction_MFLO &MFLO; }

/* MTHI */
template< > struct AllegrexInstructionTemplate< 0x00000011, 0xFC1FFFFF > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "MTHI"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x00000011, 0xFC1FFFFF > AllegrexInstruction_MTHI;

namespace Allegrex { extern AllegrexInstruction_MTHI &MTHI; }

/* MTLO */
template< > struct AllegrexInstructionTemplate< 0x00000013, 0xFC1FFFFF > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "MTLO"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x00000013, 0xFC1FFFFF > AllegrexInstruction_MTLO;

namespace Allegrex { extern AllegrexInstruction_MTLO &MTLO; }

/* BEQ */
template< > struct AllegrexInstructionTemplate< 0x10000000, 0xFC000000 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "BEQ"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x10000000, 0xFC000000 > AllegrexInstruction_BEQ;

namespace Allegrex { extern AllegrexInstruction_BEQ &BEQ; }

/* BEQL */
template< > struct AllegrexInstructionTemplate< 0x50000000, 0xFC000000 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "BEQL"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x50000000, 0xFC000000 > AllegrexInstruction_BEQL;

namespace Allegrex { extern AllegrexInstruction_BEQL &BEQL; }

/* BGEZ */
template< > struct AllegrexInstructionTemplate< 0x04010000, 0xFC1F0000 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "BGEZ"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x04010000, 0xFC1F0000 > AllegrexInstruction_BGEZ;

namespace Allegrex { extern AllegrexInstruction_BGEZ &BGEZ; }

/* BGEZAL */
template< > struct AllegrexInstructionTemplate< 0x04110000, 0xFC1F0000 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "BGEZAL"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x04110000, 0xFC1F0000 > AllegrexInstruction_BGEZAL;

namespace Allegrex { extern AllegrexInstruction_BGEZAL &BGEZAL; }

/* BGEZALL */
template< > struct AllegrexInstructionTemplate< 0x04130000, 0xFC1F0000 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "BGEZALL"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x04130000, 0xFC1F0000 > AllegrexInstruction_BGEZALL;

namespace Allegrex { extern AllegrexInstruction_BGEZALL &BGEZALL; }

/* BGEZL */
template< > struct AllegrexInstructionTemplate< 0x04030000, 0xFC1F0000 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "BGEZL"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x04030000, 0xFC1F0000 > AllegrexInstruction_BGEZL;

namespace Allegrex { extern AllegrexInstruction_BGEZL &BGEZL; }

/* BGTZ */
template< > struct AllegrexInstructionTemplate< 0x1C000000, 0xFC1F0000 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "BGTZ"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x1C000000, 0xFC1F0000 > AllegrexInstruction_BGTZ;

namespace Allegrex { extern AllegrexInstruction_BGTZ &BGTZ; }

/* BGTZL */
template< > struct AllegrexInstructionTemplate< 0x5C000000, 0xFC1F0000 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "BGTZL"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x5C000000, 0xFC1F0000 > AllegrexInstruction_BGTZL;

namespace Allegrex { extern AllegrexInstruction_BGTZL &BGTZL; }

/* BLEZ */
template< > struct AllegrexInstructionTemplate< 0x18000000, 0xFC1F0000 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "BLEZ"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x18000000, 0xFC1F0000 > AllegrexInstruction_BLEZ;

namespace Allegrex { extern AllegrexInstruction_BLEZ &BLEZ; }

/* BLEZL */
template< > struct AllegrexInstructionTemplate< 0x58000000, 0xFC1F0000 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "BLEZL"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x58000000, 0xFC1F0000 > AllegrexInstruction_BLEZL;

namespace Allegrex { extern AllegrexInstruction_BLEZL &BLEZL; }

/* BLTZ */
template< > struct AllegrexInstructionTemplate< 0x04000000, 0xFC1F0000 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "BLTZ"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x04000000, 0xFC1F0000 > AllegrexInstruction_BLTZ;

namespace Allegrex { extern AllegrexInstruction_BLTZ &BLTZ; }

/* BLTZAL */
template< > struct AllegrexInstructionTemplate< 0x04100000, 0xFC1F0000 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "BLTZAL"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x04100000, 0xFC1F0000 > AllegrexInstruction_BLTZAL;

namespace Allegrex { extern AllegrexInstruction_BLTZAL &BLTZAL; }

/* BLTZALL */
template< > struct AllegrexInstructionTemplate< 0x04120000, 0xFC1F0000 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "BLTZALL"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x04120000, 0xFC1F0000 > AllegrexInstruction_BLTZALL;

namespace Allegrex { extern AllegrexInstruction_BLTZALL &BLTZALL; }

/* BLTZL */
template< > struct AllegrexInstructionTemplate< 0x04020000, 0xFC1F0000 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "BLTZL"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x04020000, 0xFC1F0000 > AllegrexInstruction_BLTZL;

namespace Allegrex { extern AllegrexInstruction_BLTZL &BLTZL; }

/* BNE */
template< > struct AllegrexInstructionTemplate< 0x14000000, 0xFC000000 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "BNE"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x14000000, 0xFC000000 > AllegrexInstruction_BNE;

namespace Allegrex { extern AllegrexInstruction_BNE &BNE; }

/* BNEL */
template< > struct AllegrexInstructionTemplate< 0x54000000, 0xFC000000 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "BNEL"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x54000000, 0xFC000000 > AllegrexInstruction_BNEL;

namespace Allegrex { extern AllegrexInstruction_BNEL &BNEL; }

/* J */
template< > struct AllegrexInstructionTemplate< 0x08000000, 0xFC000000 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "J"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x08000000, 0xFC000000 > AllegrexInstruction_J;

namespace Allegrex { extern AllegrexInstruction_J &J; }

/* JAL */
template< > struct AllegrexInstructionTemplate< 0x0C000000, 0xFC000000 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "JAL"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x0C000000, 0xFC000000 > AllegrexInstruction_JAL;

namespace Allegrex { extern AllegrexInstruction_JAL &JAL; }

/* JALR */
template< > struct AllegrexInstructionTemplate< 0x00000009, 0xFC1F07FF > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "JALR"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x00000009, 0xFC1F07FF > AllegrexInstruction_JALR;

namespace Allegrex { extern AllegrexInstruction_JALR &JALR; }

/* RET */
template< > struct AllegrexInstructionTemplate< 0x0000F809, 0xFC1FFFFF > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "RET"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x0000F809, 0xFC1FFFFF > AllegrexInstruction_RET;

namespace Allegrex { extern AllegrexInstruction_RET &RET; }

/* JR */
template< > struct AllegrexInstructionTemplate< 0x00000008, 0xFC1FFFFF > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "JR"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x00000008, 0xFC1FFFFF > AllegrexInstruction_JR;

namespace Allegrex { extern AllegrexInstruction_JR &JR; }

/* BC1F */
template< > struct AllegrexInstructionTemplate< 0x45000000, 0xFFFF0000 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "BC1F"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x45000000, 0xFFFF0000 > AllegrexInstruction_BC1F;

namespace Allegrex { extern AllegrexInstruction_BC1F &BC1F; }

/* BC1T */
template< > struct AllegrexInstructionTemplate< 0x45010000, 0xFFFF0000 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "BC1T"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x45010000, 0xFFFF0000 > AllegrexInstruction_BC1T;

namespace Allegrex { extern AllegrexInstruction_BC1T &BC1T; }

/* BC1FL */
template< > struct AllegrexInstructionTemplate< 0x45020000, 0xFFFF0000 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "BC1FL"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x45020000, 0xFFFF0000 > AllegrexInstruction_BC1FL;

namespace Allegrex { extern AllegrexInstruction_BC1FL &BC1FL; }

/* BC1TL */
template< > struct AllegrexInstructionTemplate< 0x45030000, 0xFFFF0000 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "BC1TL"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x45030000, 0xFFFF0000 > AllegrexInstruction_BC1TL;

namespace Allegrex { extern AllegrexInstruction_BC1TL &BC1TL; }

/* BVF */
template< > struct AllegrexInstructionTemplate< 0x49000000, 0xFFE30000 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "BVF"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x49000000, 0xFFE30000 > AllegrexInstruction_BVF;

namespace Allegrex { extern AllegrexInstruction_BVF &BVF; }

/* BVT */
template< > struct AllegrexInstructionTemplate< 0x49010000, 0xFFE30000 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "BVT"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x49010000, 0xFFE30000 > AllegrexInstruction_BVT;

namespace Allegrex { extern AllegrexInstruction_BVT &BVT; }

/* BVFL */
template< > struct AllegrexInstructionTemplate< 0x49020000, 0xFFE30000 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "BVFL"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x49020000, 0xFFE30000 > AllegrexInstruction_BVFL;

namespace Allegrex { extern AllegrexInstruction_BVFL &BVFL; }

/* BVTL */
template< > struct AllegrexInstructionTemplate< 0x49030000, 0xFFE30000 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "BVTL"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x49030000, 0xFFE30000 > AllegrexInstruction_BVTL;

namespace Allegrex { extern AllegrexInstruction_BVTL &BVTL; }

/* LB */
template< > struct AllegrexInstructionTemplate< 0x80000000, 0xFC000000 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "LB"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x80000000, 0xFC000000 > AllegrexInstruction_LB;

namespace Allegrex { extern AllegrexInstruction_LB &LB; }

/* LBU */
template< > struct AllegrexInstructionTemplate< 0x90000000, 0xFC000000 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "LBU"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x90000000, 0xFC000000 > AllegrexInstruction_LBU;

namespace Allegrex { extern AllegrexInstruction_LBU &LBU; }

/* LH */
template< > struct AllegrexInstructionTemplate< 0x84000000, 0xFC000000 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "LH"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x84000000, 0xFC000000 > AllegrexInstruction_LH;

namespace Allegrex { extern AllegrexInstruction_LH &LH; }

/* LHU */
template< > struct AllegrexInstructionTemplate< 0x94000000, 0xFC000000 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "LHU"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x94000000, 0xFC000000 > AllegrexInstruction_LHU;

namespace Allegrex { extern AllegrexInstruction_LHU &LHU; }

/* LW */
template< > struct AllegrexInstructionTemplate< 0x8C000000, 0xFC000000 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "LW"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x8C000000, 0xFC000000 > AllegrexInstruction_LW;

namespace Allegrex { extern AllegrexInstruction_LW &LW; }

/* LWL */
template< > struct AllegrexInstructionTemplate< 0x88000000, 0xFC000000 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "LWL"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x88000000, 0xFC000000 > AllegrexInstruction_LWL;

namespace Allegrex { extern AllegrexInstruction_LWL &LWL; }

/* LWR */
template< > struct AllegrexInstructionTemplate< 0x98000000, 0xFC000000 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "LWR"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x98000000, 0xFC000000 > AllegrexInstruction_LWR;

namespace Allegrex { extern AllegrexInstruction_LWR &LWR; }

/* LL */
template< > struct AllegrexInstructionTemplate< 0xC0000000, 0xFC000000 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "LL"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xC0000000, 0xFC000000 > AllegrexInstruction_LL;

namespace Allegrex { extern AllegrexInstruction_LL &LL; }

/* LWC1 */
template< > struct AllegrexInstructionTemplate< 0xC4000000, 0xFC000000 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "LWC1"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xC4000000, 0xFC000000 > AllegrexInstruction_LWC1;

namespace Allegrex { extern AllegrexInstruction_LWC1 &LWC1; }

/* LV_S */
template< > struct AllegrexInstructionTemplate< 0xC8000000, 0xFC000000 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "LV_S"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xC8000000, 0xFC000000 > AllegrexInstruction_LV_S;

namespace Allegrex { extern AllegrexInstruction_LV_S &LV_S; }

/* LVL_Q */
template< > struct AllegrexInstructionTemplate< 0xD4000000, 0xFC000002 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "LVL_Q"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD4000000, 0xFC000002 > AllegrexInstruction_LVL_Q;

namespace Allegrex { extern AllegrexInstruction_LVL_Q &LVL_Q; }

/* LVR_Q */
template< > struct AllegrexInstructionTemplate< 0xD4000002, 0xFC000002 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "LVR_Q"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD4000002, 0xFC000002 > AllegrexInstruction_LVR_Q;

namespace Allegrex { extern AllegrexInstruction_LVR_Q &LVR_Q; }

/* LV_Q */
template< > struct AllegrexInstructionTemplate< 0xD8000000, 0xFC000002 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "LV_Q"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD8000000, 0xFC000002 > AllegrexInstruction_LV_Q;

namespace Allegrex { extern AllegrexInstruction_LV_Q &LV_Q; }

/* SB */
template< > struct AllegrexInstructionTemplate< 0xA0000000, 0xFC000000 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "SB"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xA0000000, 0xFC000000 > AllegrexInstruction_SB;

namespace Allegrex { extern AllegrexInstruction_SB &SB; }

/* SH */
template< > struct AllegrexInstructionTemplate< 0xA4000000, 0xFC000000 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "SH"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xA4000000, 0xFC000000 > AllegrexInstruction_SH;

namespace Allegrex { extern AllegrexInstruction_SH &SH; }

/* SW */
template< > struct AllegrexInstructionTemplate< 0xAC000000, 0xFC000000 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "SW"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xAC000000, 0xFC000000 > AllegrexInstruction_SW;

namespace Allegrex { extern AllegrexInstruction_SW &SW; }

/* SWL */
template< > struct AllegrexInstructionTemplate< 0xA8000000, 0xFC000000 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "SWL"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xA8000000, 0xFC000000 > AllegrexInstruction_SWL;

namespace Allegrex { extern AllegrexInstruction_SWL &SWL; }

/* SWR */
template< > struct AllegrexInstructionTemplate< 0xB8000000, 0xFC000000 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "SWR"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xB8000000, 0xFC000000 > AllegrexInstruction_SWR;

namespace Allegrex { extern AllegrexInstruction_SWR &SWR; }

/* SC */
template< > struct AllegrexInstructionTemplate< 0xE0000000, 0xFC000000 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "SC"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xE0000000, 0xFC000000 > AllegrexInstruction_SC;

namespace Allegrex { extern AllegrexInstruction_SC &SC; }

/* SWC1 */
template< > struct AllegrexInstructionTemplate< 0xE4000000, 0xFC000000 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "SWC1"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xE4000000, 0xFC000000 > AllegrexInstruction_SWC1;

namespace Allegrex { extern AllegrexInstruction_SWC1 &SWC1; }

/* SV_S */
template< > struct AllegrexInstructionTemplate< 0xE8000000, 0xFC000000 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "SV_S"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xE8000000, 0xFC000000 > AllegrexInstruction_SV_S;

namespace Allegrex { extern AllegrexInstruction_SV_S &SV_S; }

/* SVL_Q */
template< > struct AllegrexInstructionTemplate< 0xF4000000, 0xFC000002 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "SVL_Q"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xF4000000, 0xFC000002 > AllegrexInstruction_SVL_Q;

namespace Allegrex { extern AllegrexInstruction_SVL_Q &SVL_Q; }

/* SVR_Q */
template< > struct AllegrexInstructionTemplate< 0xF4000002, 0xFC000002 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "SVR_Q"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xF4000002, 0xFC000002 > AllegrexInstruction_SVR_Q;

namespace Allegrex { extern AllegrexInstruction_SVR_Q &SVR_Q; }

/* SV_Q */
template< > struct AllegrexInstructionTemplate< 0xF8000000, 0xFC000000 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "SV_Q"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xF8000000, 0xFC000000 > AllegrexInstruction_SV_Q;

namespace Allegrex { extern AllegrexInstruction_SV_Q &SV_Q; }

/* ADD_S */
template< > struct AllegrexInstructionTemplate< 0x46000000, 0xFFE0003F > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "ADD_S"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x46000000, 0xFFE0003F > AllegrexInstruction_ADD_S;

namespace Allegrex { extern AllegrexInstruction_ADD_S &ADD_S; }

/* SUB_S */
template< > struct AllegrexInstructionTemplate< 0x46000001, 0xFFE0003F > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "SUB_S"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x46000001, 0xFFE0003F > AllegrexInstruction_SUB_S;

namespace Allegrex { extern AllegrexInstruction_SUB_S &SUB_S; }

/* MUL_S */
template< > struct AllegrexInstructionTemplate< 0x46000002, 0xFFE0003F > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "MUL_S"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x46000002, 0xFFE0003F > AllegrexInstruction_MUL_S;

namespace Allegrex { extern AllegrexInstruction_MUL_S &MUL_S; }

/* DIV_S */
template< > struct AllegrexInstructionTemplate< 0x46000003, 0xFFE0003F > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "DIV_S"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x46000003, 0xFFE0003F > AllegrexInstruction_DIV_S;

namespace Allegrex { extern AllegrexInstruction_DIV_S &DIV_S; }

/* SQRT_S */
template< > struct AllegrexInstructionTemplate< 0x46000004, 0xFFFF003F > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "SQRT_S"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x46000004, 0xFFFF003F > AllegrexInstruction_SQRT_S;

namespace Allegrex { extern AllegrexInstruction_SQRT_S &SQRT_S; }

/* ABS_S */
template< > struct AllegrexInstructionTemplate< 0x46000005, 0xFFFF003F > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "ABS_S"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x46000005, 0xFFFF003F > AllegrexInstruction_ABS_S;

namespace Allegrex { extern AllegrexInstruction_ABS_S &ABS_S; }

/* MOV_S */
template< > struct AllegrexInstructionTemplate< 0x46000006, 0xFFFF003F > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "MOV_S"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x46000006, 0xFFFF003F > AllegrexInstruction_MOV_S;

namespace Allegrex { extern AllegrexInstruction_MOV_S &MOV_S; }

/* NEG_S */
template< > struct AllegrexInstructionTemplate< 0x46000007, 0xFFFF003F > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "NEG_S"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x46000007, 0xFFFF003F > AllegrexInstruction_NEG_S;

namespace Allegrex { extern AllegrexInstruction_NEG_S &NEG_S; }

/* ROUND_W_S */
template< > struct AllegrexInstructionTemplate< 0x4600000C, 0xFFFF003F > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "ROUND_W_S"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x4600000C, 0xFFFF003F > AllegrexInstruction_ROUND_W_S;

namespace Allegrex { extern AllegrexInstruction_ROUND_W_S &ROUND_W_S; }

/* TRUNC_W_S */
template< > struct AllegrexInstructionTemplate< 0x4600000D, 0xFFFF003F > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "TRUNC_W_S"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x4600000D, 0xFFFF003F > AllegrexInstruction_TRUNC_W_S;

namespace Allegrex { extern AllegrexInstruction_TRUNC_W_S &TRUNC_W_S; }

/* CEIL_W_S */
template< > struct AllegrexInstructionTemplate< 0x4600000E, 0xFFFF003F > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "CEIL_W_S"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x4600000E, 0xFFFF003F > AllegrexInstruction_CEIL_W_S;

namespace Allegrex { extern AllegrexInstruction_CEIL_W_S &CEIL_W_S; }

/* FLOOR_W_S */
template< > struct AllegrexInstructionTemplate< 0x4600000F, 0xFFFF003F > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "FLOOR_W_S"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x4600000F, 0xFFFF003F > AllegrexInstruction_FLOOR_W_S;

namespace Allegrex { extern AllegrexInstruction_FLOOR_W_S &FLOOR_W_S; }

/* CVT_S_W */
template< > struct AllegrexInstructionTemplate< 0x46800020, 0xFFFF003F > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "CVT_S_W"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x46800020, 0xFFFF003F > AllegrexInstruction_CVT_S_W;

namespace Allegrex { extern AllegrexInstruction_CVT_S_W &CVT_S_W; }

/* CVT_W_S */
template< > struct AllegrexInstructionTemplate< 0x46000024, 0xFFFF003F > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "CVT_W_S"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x46000024, 0xFFFF003F > AllegrexInstruction_CVT_W_S;

namespace Allegrex { extern AllegrexInstruction_CVT_W_S &CVT_W_S; }

/* C_F_S */
template< > struct AllegrexInstructionTemplate< 0x46000030, 0xFFE007FF > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "C_F_S"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x46000030, 0xFFE007FF > AllegrexInstruction_C_F_S;

namespace Allegrex { extern AllegrexInstruction_C_F_S &C_F_S; }

/* C_UN_S */
template< > struct AllegrexInstructionTemplate< 0x46000031, 0xFFE007FF > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "C_UN_S"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x46000031, 0xFFE007FF > AllegrexInstruction_C_UN_S;

namespace Allegrex { extern AllegrexInstruction_C_UN_S &C_UN_S; }

/* C_EQ_S */
template< > struct AllegrexInstructionTemplate< 0x46000032, 0xFFE007FF > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "C_EQ_S"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x46000032, 0xFFE007FF > AllegrexInstruction_C_EQ_S;

namespace Allegrex { extern AllegrexInstruction_C_EQ_S &C_EQ_S; }

/* C_UEQ_S */
template< > struct AllegrexInstructionTemplate< 0x46000033, 0xFFE007FF > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "C_UEQ_S"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x46000033, 0xFFE007FF > AllegrexInstruction_C_UEQ_S;

namespace Allegrex { extern AllegrexInstruction_C_UEQ_S &C_UEQ_S; }

/* C_OLT_S */
template< > struct AllegrexInstructionTemplate< 0x46000034, 0xFFE007FF > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "C_OLT_S"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x46000034, 0xFFE007FF > AllegrexInstruction_C_OLT_S;

namespace Allegrex { extern AllegrexInstruction_C_OLT_S &C_OLT_S; }

/* C_ULT_S */
template< > struct AllegrexInstructionTemplate< 0x46000035, 0xFFE007FF > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "C_ULT_S"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x46000035, 0xFFE007FF > AllegrexInstruction_C_ULT_S;

namespace Allegrex { extern AllegrexInstruction_C_ULT_S &C_ULT_S; }

/* C_OLE_S */
template< > struct AllegrexInstructionTemplate< 0x46000036, 0xFFE007FF > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "C_OLE_S"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x46000036, 0xFFE007FF > AllegrexInstruction_C_OLE_S;

namespace Allegrex { extern AllegrexInstruction_C_OLE_S &C_OLE_S; }

/* C_ULE_S */
template< > struct AllegrexInstructionTemplate< 0x46000037, 0xFFE007FF > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "C_ULE_S"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x46000037, 0xFFE007FF > AllegrexInstruction_C_ULE_S;

namespace Allegrex { extern AllegrexInstruction_C_ULE_S &C_ULE_S; }

/* C_SF_S */
template< > struct AllegrexInstructionTemplate< 0x46000038, 0xFFE007FF > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "C_SF_S"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x46000038, 0xFFE007FF > AllegrexInstruction_C_SF_S;

namespace Allegrex { extern AllegrexInstruction_C_SF_S &C_SF_S; }

/* C_NGLE_S */
template< > struct AllegrexInstructionTemplate< 0x46000039, 0xFFE007FF > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "C_NGLE_S"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x46000039, 0xFFE007FF > AllegrexInstruction_C_NGLE_S;

namespace Allegrex { extern AllegrexInstruction_C_NGLE_S &C_NGLE_S; }

/* C_SEQ_S */
template< > struct AllegrexInstructionTemplate< 0x4600003A, 0xFFE007FF > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "C_SEQ_S"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x4600003A, 0xFFE007FF > AllegrexInstruction_C_SEQ_S;

namespace Allegrex { extern AllegrexInstruction_C_SEQ_S &C_SEQ_S; }

/* C_NGL_S */
template< > struct AllegrexInstructionTemplate< 0x4600003B, 0xFFE007FF > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "C_NGL_S"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x4600003B, 0xFFE007FF > AllegrexInstruction_C_NGL_S;

namespace Allegrex { extern AllegrexInstruction_C_NGL_S &C_NGL_S; }

/* C_LT_S */
template< > struct AllegrexInstructionTemplate< 0x4600003C, 0xFFE007FF > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "C_LT_S"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x4600003C, 0xFFE007FF > AllegrexInstruction_C_LT_S;

namespace Allegrex { extern AllegrexInstruction_C_LT_S &C_LT_S; }

/* C_NGE_S */
template< > struct AllegrexInstructionTemplate< 0x4600003D, 0xFFE007FF > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "C_NGE_S"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x4600003D, 0xFFE007FF > AllegrexInstruction_C_NGE_S;

namespace Allegrex { extern AllegrexInstruction_C_NGE_S &C_NGE_S; }

/* C_LE_S */
template< > struct AllegrexInstructionTemplate< 0x4600003E, 0xFFE007FF > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "C_LE_S"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x4600003E, 0xFFE007FF > AllegrexInstruction_C_LE_S;

namespace Allegrex { extern AllegrexInstruction_C_LE_S &C_LE_S; }

/* C_NGT_S */
template< > struct AllegrexInstructionTemplate< 0x4600003F, 0xFFE007FF > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "C_NGT_S"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x4600003F, 0xFFE007FF > AllegrexInstruction_C_NGT_S;

namespace Allegrex { extern AllegrexInstruction_C_NGT_S &C_NGT_S; }

/* MFC1 */
template< > struct AllegrexInstructionTemplate< 0x44000000, 0xFFE007FF > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "MFC1"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x44000000, 0xFFE007FF > AllegrexInstruction_MFC1;

namespace Allegrex { extern AllegrexInstruction_MFC1 &MFC1; }

/* CFC1 */
template< > struct AllegrexInstructionTemplate< 0x44400000, 0xFFE007FF > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "CFC1"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x44400000, 0xFFE007FF > AllegrexInstruction_CFC1;

namespace Allegrex { extern AllegrexInstruction_CFC1 &CFC1; }

/* MTC1 */
template< > struct AllegrexInstructionTemplate< 0x44800000, 0xFFE007FF > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "MTC1"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x44800000, 0xFFE007FF > AllegrexInstruction_MTC1;

namespace Allegrex { extern AllegrexInstruction_MTC1 &MTC1; }

/* CTC1 */
template< > struct AllegrexInstructionTemplate< 0x44C00000, 0xFFE007FF > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "CTC1"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x44C00000, 0xFFE007FF > AllegrexInstruction_CTC1;

namespace Allegrex { extern AllegrexInstruction_CTC1 &CTC1; }

/* MFDR */
template< > struct AllegrexInstructionTemplate< 0x7000003D, 0xFFE007FF > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "MFDR"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x7000003D, 0xFFE007FF > AllegrexInstruction_MFDR;

namespace Allegrex { extern AllegrexInstruction_MFDR &MFDR; }

/* MTDR */
template< > struct AllegrexInstructionTemplate< 0x7080003D, 0xFFE007FF > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "MTDR"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x7080003D, 0xFFE007FF > AllegrexInstruction_MTDR;

namespace Allegrex { extern AllegrexInstruction_MTDR &MTDR; }

/* DBREAK */
template< > struct AllegrexInstructionTemplate< 0x7000003F, 0xFC00003F > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "DBREAK"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x7000003F, 0xFC00003F > AllegrexInstruction_DBREAK;

namespace Allegrex { extern AllegrexInstruction_DBREAK &DBREAK; }

/* DRET */
template< > struct AllegrexInstructionTemplate< 0x7000003E, 0xFFFFFFFF > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "DRET"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x7000003E, 0xFFFFFFFF > AllegrexInstruction_DRET;

namespace Allegrex { extern AllegrexInstruction_DRET &DRET; }

/* MFC0 */
template< > struct AllegrexInstructionTemplate< 0x40000000, 0xFFE007FF > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "MFC0"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x40000000, 0xFFE007FF > AllegrexInstruction_MFC0;

namespace Allegrex { extern AllegrexInstruction_MFC0 &MFC0; }

/* CFC0 */
template< > struct AllegrexInstructionTemplate< 0x40400000, 0xFFE007FF > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "CFC0"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x40400000, 0xFFE007FF > AllegrexInstruction_CFC0;

namespace Allegrex { extern AllegrexInstruction_CFC0 &CFC0; }

/* MTC0 */
template< > struct AllegrexInstructionTemplate< 0x40800000, 0xFFE007FF > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "MTC0"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x40800000, 0xFFE007FF > AllegrexInstruction_MTC0;

namespace Allegrex { extern AllegrexInstruction_MTC0 &MTC0; }

/* CTC0 */
template< > struct AllegrexInstructionTemplate< 0x40C00000, 0xFFE007FF > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "CTC0"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x40C00000, 0xFFE007FF > AllegrexInstruction_CTC0;

namespace Allegrex { extern AllegrexInstruction_CTC0 &CTC0; }

/* SYSCALL */
template< > struct AllegrexInstructionTemplate< 0x0000000C, 0xFC00003F > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "SYSCALL"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x0000000C, 0xFC00003F > AllegrexInstruction_SYSCALL;

namespace Allegrex { extern AllegrexInstruction_SYSCALL &SYSCALL; }

/* BREAK */
template< > struct AllegrexInstructionTemplate< 0x0000000D, 0xFC00003F > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "BREAK"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x0000000D, 0xFC00003F > AllegrexInstruction_BREAK;

namespace Allegrex { extern AllegrexInstruction_BREAK &BREAK; }

/* ERET */
template< > struct AllegrexInstructionTemplate< 0x42000018, 0xFFFFFFFF > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "ERET"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x42000018, 0xFFFFFFFF > AllegrexInstruction_ERET;

namespace Allegrex { extern AllegrexInstruction_ERET &ERET; }

/* HALT */
template< > struct AllegrexInstructionTemplate< 0x70000000, 0xFFFFFFFF > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "HALT"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x70000000, 0xFFFFFFFF > AllegrexInstruction_HALT;

namespace Allegrex { extern AllegrexInstruction_HALT &HALT; }

/* MFIC */
template< > struct AllegrexInstructionTemplate< 0x70000024, 0xFC1FFFFF > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "MFIC"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x70000024, 0xFC1FFFFF > AllegrexInstruction_MFIC;

namespace Allegrex { extern AllegrexInstruction_MFIC &MFIC; }

/* MTIC */
template< > struct AllegrexInstructionTemplate< 0x70000026, 0xFC1FFFFF > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "MTIC"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x70000026, 0xFC1FFFFF > AllegrexInstruction_MTIC;

namespace Allegrex { extern AllegrexInstruction_MTIC &MTIC; }

/* ICACHE_INDEX_INVALIDATE */
template< > struct AllegrexInstructionTemplate< 0xBC040000, 0xFC1F0000 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "ICACHE_INDEX_INVALIDATE"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xBC040000, 0xFC1F0000 > AllegrexInstruction_ICACHE_INDEX_INVALIDATE;

namespace Allegrex { extern AllegrexInstruction_ICACHE_INDEX_INVALIDATE &ICACHE_INDEX_INVALIDATE; }

/* ICACHE_INDEX_UNLOCK */
template< > struct AllegrexInstructionTemplate< 0xBC060000, 0xFC1F0000 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "ICACHE_INDEX_UNLOCK"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xBC060000, 0xFC1F0000 > AllegrexInstruction_ICACHE_INDEX_UNLOCK;

namespace Allegrex { extern AllegrexInstruction_ICACHE_INDEX_UNLOCK &ICACHE_INDEX_UNLOCK; }

/* ICACHE_HIT_INVALIDATE */
template< > struct AllegrexInstructionTemplate< 0xBC080000, 0xFC1F0000 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "ICACHE_HIT_INVALIDATE"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xBC080000, 0xFC1F0000 > AllegrexInstruction_ICACHE_HIT_INVALIDATE;

namespace Allegrex { extern AllegrexInstruction_ICACHE_HIT_INVALIDATE &ICACHE_HIT_INVALIDATE; }

/* ICACHE_FILL */
template< > struct AllegrexInstructionTemplate< 0xBC0A0000, 0xFC1F0000 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "ICACHE_FILL"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xBC0A0000, 0xFC1F0000 > AllegrexInstruction_ICACHE_FILL;

namespace Allegrex { extern AllegrexInstruction_ICACHE_FILL &ICACHE_FILL; }

/* ICACHE_FILL_WITH_LOCK */
template< > struct AllegrexInstructionTemplate< 0xBC0B0000, 0xFC1F0000 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "ICACHE_FILL_WITH_LOCK"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xBC0B0000, 0xFC1F0000 > AllegrexInstruction_ICACHE_FILL_WITH_LOCK;

namespace Allegrex { extern AllegrexInstruction_ICACHE_FILL_WITH_LOCK &ICACHE_FILL_WITH_LOCK; }

/* DCACHE_INDEX_WRITEBACK_INVALIDATE */
template< > struct AllegrexInstructionTemplate< 0xBC140000, 0xFC1F0000 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "DCACHE_INDEX_WRITEBACK_INVALIDATE"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xBC140000, 0xFC1F0000 > AllegrexInstruction_DCACHE_INDEX_WRITEBACK_INVALIDATE;

namespace Allegrex { extern AllegrexInstruction_DCACHE_INDEX_WRITEBACK_INVALIDATE &DCACHE_INDEX_WRITEBACK_INVALIDATE; }

/* DCACHE_INDEX_UNLOCK */
template< > struct AllegrexInstructionTemplate< 0xBC160000, 0xFC1F0000 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "DCACHE_INDEX_UNLOCK"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xBC160000, 0xFC1F0000 > AllegrexInstruction_DCACHE_INDEX_UNLOCK;

namespace Allegrex { extern AllegrexInstruction_DCACHE_INDEX_UNLOCK &DCACHE_INDEX_UNLOCK; }

/* DCACHE_CREATE_DIRTY_EXCLUSIVE */
template< > struct AllegrexInstructionTemplate< 0xBC180000, 0xFC1F0000 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "DCACHE_CREATE_DIRTY_EXCLUSIVE"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xBC180000, 0xFC1F0000 > AllegrexInstruction_DCACHE_CREATE_DIRTY_EXCLUSIVE;

namespace Allegrex { extern AllegrexInstruction_DCACHE_CREATE_DIRTY_EXCLUSIVE &DCACHE_CREATE_DIRTY_EXCLUSIVE; }

/* DCACHE_HIT_INVALIDATE */
template< > struct AllegrexInstructionTemplate< 0xBC190000, 0xFC1F0000 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "DCACHE_HIT_INVALIDATE"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xBC190000, 0xFC1F0000 > AllegrexInstruction_DCACHE_HIT_INVALIDATE;

namespace Allegrex { extern AllegrexInstruction_DCACHE_HIT_INVALIDATE &DCACHE_HIT_INVALIDATE; }

/* DCACHE_HIT_WRITEBACK */
template< > struct AllegrexInstructionTemplate< 0xBC1A0000, 0xFC1F0000 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "DCACHE_HIT_WRITEBACK"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xBC1A0000, 0xFC1F0000 > AllegrexInstruction_DCACHE_HIT_WRITEBACK;

namespace Allegrex { extern AllegrexInstruction_DCACHE_HIT_WRITEBACK &DCACHE_HIT_WRITEBACK; }

/* DCACHE_HIT_WRITEBACK_INVALIDATE */
template< > struct AllegrexInstructionTemplate< 0xBC1B0000, 0xFC1F0000 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "DCACHE_HIT_WRITEBACK_INVALIDATE"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xBC1B0000, 0xFC1F0000 > AllegrexInstruction_DCACHE_HIT_WRITEBACK_INVALIDATE;

namespace Allegrex { extern AllegrexInstruction_DCACHE_HIT_WRITEBACK_INVALIDATE &DCACHE_HIT_WRITEBACK_INVALIDATE; }

/* DCACHE_CREATE_DIRTY_EXCLUSIVE_WITH_LOCK */
template< > struct AllegrexInstructionTemplate< 0xBC1C0000, 0xFC1F0000 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "DCACHE_CREATE_DIRTY_EXCLUSIVE_WITH_LOCK"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xBC1C0000, 0xFC1F0000 > AllegrexInstruction_DCACHE_CREATE_DIRTY_EXCLUSIVE_WITH_LOCK;

namespace Allegrex { extern AllegrexInstruction_DCACHE_CREATE_DIRTY_EXCLUSIVE_WITH_LOCK &DCACHE_CREATE_DIRTY_EXCLUSIVE_WITH_LOCK; }

/* DCACHE_FILL */
template< > struct AllegrexInstructionTemplate< 0xBC1E0000, 0xFC1F0000 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "DCACHE_FILL"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xBC1E0000, 0xFC1F0000 > AllegrexInstruction_DCACHE_FILL;

namespace Allegrex { extern AllegrexInstruction_DCACHE_FILL &DCACHE_FILL; }

/* DCACHE_FILL_WITH_LOCK */
template< > struct AllegrexInstructionTemplate< 0xBC1F0000, 0xFC1F0000 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "DCACHE_FILL_WITH_LOCK"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xBC1F0000, 0xFC1F0000 > AllegrexInstruction_DCACHE_FILL_WITH_LOCK;

namespace Allegrex { extern AllegrexInstruction_DCACHE_FILL_WITH_LOCK &DCACHE_FILL_WITH_LOCK; }

/* SYNC */
template< > struct AllegrexInstructionTemplate< 0x0000000F, 0xFFFFFFFF > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "SYNC"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x0000000F, 0xFFFFFFFF > AllegrexInstruction_SYNC;

namespace Allegrex { extern AllegrexInstruction_SYNC &SYNC; }

/* VADD_S */
template< > struct AllegrexInstructionTemplate< 0x60000000, 0xFF808080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VADD_S"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x60000000, 0xFF808080 > AllegrexInstruction_VADD_S;

namespace Allegrex { extern AllegrexInstruction_VADD_S &VADD_S; }

/* VADD_P */
template< > struct AllegrexInstructionTemplate< 0x60000080, 0xFF808080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VADD_P"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x60000080, 0xFF808080 > AllegrexInstruction_VADD_P;

namespace Allegrex { extern AllegrexInstruction_VADD_P &VADD_P; }

/* VADD_T */
template< > struct AllegrexInstructionTemplate< 0x60008000, 0xFF808080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VADD_T"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x60008000, 0xFF808080 > AllegrexInstruction_VADD_T;

namespace Allegrex { extern AllegrexInstruction_VADD_T &VADD_T; }

/* VADD_Q */
template< > struct AllegrexInstructionTemplate< 0x60008080, 0xFF808080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VADD_Q"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x60008080, 0xFF808080 > AllegrexInstruction_VADD_Q;

namespace Allegrex { extern AllegrexInstruction_VADD_Q &VADD_Q; }

/* VSUB_S */
template< > struct AllegrexInstructionTemplate< 0x60800000, 0xFF808080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VSUB_S"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x60800000, 0xFF808080 > AllegrexInstruction_VSUB_S;

namespace Allegrex { extern AllegrexInstruction_VSUB_S &VSUB_S; }

/* VSUB_P */
template< > struct AllegrexInstructionTemplate< 0x60800080, 0xFF808080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VSUB_P"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x60800080, 0xFF808080 > AllegrexInstruction_VSUB_P;

namespace Allegrex { extern AllegrexInstruction_VSUB_P &VSUB_P; }

/* VSUB_T */
template< > struct AllegrexInstructionTemplate< 0x60808000, 0xFF808080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VSUB_T"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x60808000, 0xFF808080 > AllegrexInstruction_VSUB_T;

namespace Allegrex { extern AllegrexInstruction_VSUB_T &VSUB_T; }

/* VSUB_Q */
template< > struct AllegrexInstructionTemplate< 0x60808080, 0xFF808080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VSUB_Q"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x60808080, 0xFF808080 > AllegrexInstruction_VSUB_Q;

namespace Allegrex { extern AllegrexInstruction_VSUB_Q &VSUB_Q; }

/* VSBN_S */
template< > struct AllegrexInstructionTemplate< 0x61000000, 0xFF808080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VSBN_S"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x61000000, 0xFF808080 > AllegrexInstruction_VSBN_S;

namespace Allegrex { extern AllegrexInstruction_VSBN_S &VSBN_S; }

/* VDIV_S */
template< > struct AllegrexInstructionTemplate< 0x63800000, 0xFF808080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VDIV_S"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x63800000, 0xFF808080 > AllegrexInstruction_VDIV_S;

namespace Allegrex { extern AllegrexInstruction_VDIV_S &VDIV_S; }

/* VDIV_P */
template< > struct AllegrexInstructionTemplate< 0x63800080, 0xFF808080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VDIV_P"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x63800080, 0xFF808080 > AllegrexInstruction_VDIV_P;

namespace Allegrex { extern AllegrexInstruction_VDIV_P &VDIV_P; }

/* VDIV_T */
template< > struct AllegrexInstructionTemplate< 0x63808000, 0xFF808080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VDIV_T"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x63808000, 0xFF808080 > AllegrexInstruction_VDIV_T;

namespace Allegrex { extern AllegrexInstruction_VDIV_T &VDIV_T; }

/* VDIV_Q */
template< > struct AllegrexInstructionTemplate< 0x63808080, 0xFF808080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VDIV_Q"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x63808080, 0xFF808080 > AllegrexInstruction_VDIV_Q;

namespace Allegrex { extern AllegrexInstruction_VDIV_Q &VDIV_Q; }

/* VMUL_S */
template< > struct AllegrexInstructionTemplate< 0x64000000, 0xFF808080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VMUL_S"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x64000000, 0xFF808080 > AllegrexInstruction_VMUL_S;

namespace Allegrex { extern AllegrexInstruction_VMUL_S &VMUL_S; }

/* VMUL_P */
template< > struct AllegrexInstructionTemplate< 0x64000080, 0xFF808080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VMUL_P"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x64000080, 0xFF808080 > AllegrexInstruction_VMUL_P;

namespace Allegrex { extern AllegrexInstruction_VMUL_P &VMUL_P; }

/* VMUL_T */
template< > struct AllegrexInstructionTemplate< 0x64008000, 0xFF808080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VMUL_T"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x64008000, 0xFF808080 > AllegrexInstruction_VMUL_T;

namespace Allegrex { extern AllegrexInstruction_VMUL_T &VMUL_T; }

/* VMUL_Q */
template< > struct AllegrexInstructionTemplate< 0x64008080, 0xFF808080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VMUL_Q"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x64008080, 0xFF808080 > AllegrexInstruction_VMUL_Q;

namespace Allegrex { extern AllegrexInstruction_VMUL_Q &VMUL_Q; }

/* VDOT_P */
template< > struct AllegrexInstructionTemplate< 0x64800080, 0xFF808080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VDOT_P"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x64800080, 0xFF808080 > AllegrexInstruction_VDOT_P;

namespace Allegrex { extern AllegrexInstruction_VDOT_P &VDOT_P; }

/* VDOT_T */
template< > struct AllegrexInstructionTemplate< 0x64808000, 0xFF808080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VDOT_T"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x64808000, 0xFF808080 > AllegrexInstruction_VDOT_T;

namespace Allegrex { extern AllegrexInstruction_VDOT_T &VDOT_T; }

/* VDOT_Q */
template< > struct AllegrexInstructionTemplate< 0x64808080, 0xFF808080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VDOT_Q"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x64808080, 0xFF808080 > AllegrexInstruction_VDOT_Q;

namespace Allegrex { extern AllegrexInstruction_VDOT_Q &VDOT_Q; }

/* VSCL_P */
template< > struct AllegrexInstructionTemplate< 0x65000080, 0xFF808080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VSCL_P"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x65000080, 0xFF808080 > AllegrexInstruction_VSCL_P;

namespace Allegrex { extern AllegrexInstruction_VSCL_P &VSCL_P; }

/* VSCL_T */
template< > struct AllegrexInstructionTemplate< 0x65008000, 0xFF808080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VSCL_T"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x65008000, 0xFF808080 > AllegrexInstruction_VSCL_T;

namespace Allegrex { extern AllegrexInstruction_VSCL_T &VSCL_T; }

/* VSCL_Q */
template< > struct AllegrexInstructionTemplate< 0x65008080, 0xFF808080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VSCL_Q"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x65008080, 0xFF808080 > AllegrexInstruction_VSCL_Q;

namespace Allegrex { extern AllegrexInstruction_VSCL_Q &VSCL_Q; }

/* VHDP_P */
template< > struct AllegrexInstructionTemplate< 0x66000080, 0xFF808080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VHDP_P"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x66000080, 0xFF808080 > AllegrexInstruction_VHDP_P;

namespace Allegrex { extern AllegrexInstruction_VHDP_P &VHDP_P; }

/* VHDP_T */
template< > struct AllegrexInstructionTemplate< 0x66008000, 0xFF808080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VHDP_T"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x66008000, 0xFF808080 > AllegrexInstruction_VHDP_T;

namespace Allegrex { extern AllegrexInstruction_VHDP_T &VHDP_T; }

/* VHDP_Q */
template< > struct AllegrexInstructionTemplate< 0x66008080, 0xFF808080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VHDP_Q"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x66008080, 0xFF808080 > AllegrexInstruction_VHDP_Q;

namespace Allegrex { extern AllegrexInstruction_VHDP_Q &VHDP_Q; }

/* VCRS_T */
template< > struct AllegrexInstructionTemplate< 0x66808000, 0xFF808080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VCRS_T"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x66808000, 0xFF808080 > AllegrexInstruction_VCRS_T;

namespace Allegrex { extern AllegrexInstruction_VCRS_T &VCRS_T; }

/* VDET_P */
template< > struct AllegrexInstructionTemplate< 0x67000080, 0xFF808080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VDET_P"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x67000080, 0xFF808080 > AllegrexInstruction_VDET_P;

namespace Allegrex { extern AllegrexInstruction_VDET_P &VDET_P; }

/* MFV */
template< > struct AllegrexInstructionTemplate< 0x48600000, 0xFFE0FF80 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "MFV"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x48600000, 0xFFE0FF80 > AllegrexInstruction_MFV;

namespace Allegrex { extern AllegrexInstruction_MFV &MFV; }

/* MFVC */
template< > struct AllegrexInstructionTemplate< 0x48600080, 0xFFE0FF80 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "MFVC"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x48600080, 0xFFE0FF80 > AllegrexInstruction_MFVC;

namespace Allegrex { extern AllegrexInstruction_MFVC &MFVC; }

/* MTV */
template< > struct AllegrexInstructionTemplate< 0x48E00000, 0xFFE0FF80 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "MTV"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x48E00000, 0xFFE0FF80 > AllegrexInstruction_MTV;

namespace Allegrex { extern AllegrexInstruction_MTV &MTV; }

/* MTVC */
template< > struct AllegrexInstructionTemplate< 0x48E00080, 0xFFE0FF80 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "MTVC"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x48E00080, 0xFFE0FF80 > AllegrexInstruction_MTVC;

namespace Allegrex { extern AllegrexInstruction_MTVC &MTVC; }

/* VCMP_S */
template< > struct AllegrexInstructionTemplate< 0x6C000000, 0xFF808088 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VCMP_S"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x6C000000, 0xFF808088 > AllegrexInstruction_VCMP_S;

namespace Allegrex { extern AllegrexInstruction_VCMP_S &VCMP_S; }

/* VCMP_P */
template< > struct AllegrexInstructionTemplate< 0x6C000080, 0xFF808088 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VCMP_P"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x6C000080, 0xFF808088 > AllegrexInstruction_VCMP_P;

namespace Allegrex { extern AllegrexInstruction_VCMP_P &VCMP_P; }

/* VCMP_T */
template< > struct AllegrexInstructionTemplate< 0x6C008000, 0xFF808088 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VCMP_T"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x6C008000, 0xFF808088 > AllegrexInstruction_VCMP_T;

namespace Allegrex { extern AllegrexInstruction_VCMP_T &VCMP_T; }

/* VCMP_Q */
template< > struct AllegrexInstructionTemplate< 0x6C008080, 0xFF808088 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VCMP_Q"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x6C008080, 0xFF808088 > AllegrexInstruction_VCMP_Q;

namespace Allegrex { extern AllegrexInstruction_VCMP_Q &VCMP_Q; }

/* VMIN_S */
template< > struct AllegrexInstructionTemplate< 0x6D000000, 0xFF808088 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VMIN_S"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x6D000000, 0xFF808088 > AllegrexInstruction_VMIN_S;

namespace Allegrex { extern AllegrexInstruction_VMIN_S &VMIN_S; }

/* VMIN_P */
template< > struct AllegrexInstructionTemplate< 0x6D000080, 0xFF808088 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VMIN_P"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x6D000080, 0xFF808088 > AllegrexInstruction_VMIN_P;

namespace Allegrex { extern AllegrexInstruction_VMIN_P &VMIN_P; }

/* VMIN_T */
template< > struct AllegrexInstructionTemplate< 0x6D008000, 0xFF808088 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VMIN_T"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x6D008000, 0xFF808088 > AllegrexInstruction_VMIN_T;

namespace Allegrex { extern AllegrexInstruction_VMIN_T &VMIN_T; }

/* VMIN_Q */
template< > struct AllegrexInstructionTemplate< 0x6D008080, 0xFF808088 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VMIN_Q"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x6D008080, 0xFF808088 > AllegrexInstruction_VMIN_Q;

namespace Allegrex { extern AllegrexInstruction_VMIN_Q &VMIN_Q; }

/* VMAX_S */
template< > struct AllegrexInstructionTemplate< 0x6D800000, 0xFF808080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VMAX_S"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x6D800000, 0xFF808080 > AllegrexInstruction_VMAX_S;

namespace Allegrex { extern AllegrexInstruction_VMAX_S &VMAX_S; }

/* VMAX_P */
template< > struct AllegrexInstructionTemplate< 0x6D800080, 0xFF808080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VMAX_P"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x6D800080, 0xFF808080 > AllegrexInstruction_VMAX_P;

namespace Allegrex { extern AllegrexInstruction_VMAX_P &VMAX_P; }

/* VMAX_T */
template< > struct AllegrexInstructionTemplate< 0x6D808000, 0xFF808080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VMAX_T"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x6D808000, 0xFF808080 > AllegrexInstruction_VMAX_T;

namespace Allegrex { extern AllegrexInstruction_VMAX_T &VMAX_T; }

/* VMAX_Q */
template< > struct AllegrexInstructionTemplate< 0x6D808080, 0xFF808080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VMAX_Q"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x6D808080, 0xFF808080 > AllegrexInstruction_VMAX_Q;

namespace Allegrex { extern AllegrexInstruction_VMAX_Q &VMAX_Q; }

/* VSCMP_S */
template< > struct AllegrexInstructionTemplate< 0x6E800000, 0xFF808080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VSCMP_S"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x6E800000, 0xFF808080 > AllegrexInstruction_VSCMP_S;

namespace Allegrex { extern AllegrexInstruction_VSCMP_S &VSCMP_S; }

/* VSCMP_P */
template< > struct AllegrexInstructionTemplate< 0x6E800080, 0xFF808080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VSCMP_P"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x6E800080, 0xFF808080 > AllegrexInstruction_VSCMP_P;

namespace Allegrex { extern AllegrexInstruction_VSCMP_P &VSCMP_P; }

/* VSCMP_T */
template< > struct AllegrexInstructionTemplate< 0x6E808000, 0xFF808080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VSCMP_T"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x6E808000, 0xFF808080 > AllegrexInstruction_VSCMP_T;

namespace Allegrex { extern AllegrexInstruction_VSCMP_T &VSCMP_T; }

/* VSCMP_Q */
template< > struct AllegrexInstructionTemplate< 0x6E808080, 0xFF808080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VSCMP_Q"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x6E808080, 0xFF808080 > AllegrexInstruction_VSCMP_Q;

namespace Allegrex { extern AllegrexInstruction_VSCMP_Q &VSCMP_Q; }

/* VSGE_S */
template< > struct AllegrexInstructionTemplate< 0x6F000000, 0xFF808080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VSGE_S"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x6F000000, 0xFF808080 > AllegrexInstruction_VSGE_S;

namespace Allegrex { extern AllegrexInstruction_VSGE_S &VSGE_S; }

/* VSGE_P */
template< > struct AllegrexInstructionTemplate< 0x6F000080, 0xFF808080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VSGE_P"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x6F000080, 0xFF808080 > AllegrexInstruction_VSGE_P;

namespace Allegrex { extern AllegrexInstruction_VSGE_P &VSGE_P; }

/* VSGE_T */
template< > struct AllegrexInstructionTemplate< 0x6F008000, 0xFF808080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VSGE_T"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x6F008000, 0xFF808080 > AllegrexInstruction_VSGE_T;

namespace Allegrex { extern AllegrexInstruction_VSGE_T &VSGE_T; }

/* VSGE_Q */
template< > struct AllegrexInstructionTemplate< 0x6F008080, 0xFF808080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VSGE_Q"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x6F008080, 0xFF808080 > AllegrexInstruction_VSGE_Q;

namespace Allegrex { extern AllegrexInstruction_VSGE_Q &VSGE_Q; }

/* VSLT_S */
template< > struct AllegrexInstructionTemplate< 0x6E000000, 0xFF808080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VSLT_S"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x6E000000, 0xFF808080 > AllegrexInstruction_VSLT_S;

namespace Allegrex { extern AllegrexInstruction_VSLT_S &VSLT_S; }

/* VSLT_P */
template< > struct AllegrexInstructionTemplate< 0x6E000080, 0xFF808080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VSLT_P"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x6E000080, 0xFF808080 > AllegrexInstruction_VSLT_P;

namespace Allegrex { extern AllegrexInstruction_VSLT_P &VSLT_P; }

/* VSLT_T */
template< > struct AllegrexInstructionTemplate< 0x6E008000, 0xFF808080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VSLT_T"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x6E008000, 0xFF808080 > AllegrexInstruction_VSLT_T;

namespace Allegrex { extern AllegrexInstruction_VSLT_T &VSLT_T; }

/* VSLT_Q */
template< > struct AllegrexInstructionTemplate< 0x6E008080, 0xFF808080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VSLT_Q"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0x6E008080, 0xFF808080 > AllegrexInstruction_VSLT_Q;

namespace Allegrex { extern AllegrexInstruction_VSLT_Q &VSLT_Q; }

/* VMOV_S */
template< > struct AllegrexInstructionTemplate< 0xD0000000, 0xFFFF8080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VMOV_S"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0000000, 0xFFFF8080 > AllegrexInstruction_VMOV_S;

namespace Allegrex { extern AllegrexInstruction_VMOV_S &VMOV_S; }

/* VMOV_P */
template< > struct AllegrexInstructionTemplate< 0xD0000080, 0xFFFF8080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VMOV_P"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0000080, 0xFFFF8080 > AllegrexInstruction_VMOV_P;

namespace Allegrex { extern AllegrexInstruction_VMOV_P &VMOV_P; }

/* VMOV_T */
template< > struct AllegrexInstructionTemplate< 0xD0008000, 0xFFFF8080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VMOV_T"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0008000, 0xFFFF8080 > AllegrexInstruction_VMOV_T;

namespace Allegrex { extern AllegrexInstruction_VMOV_T &VMOV_T; }

/* VMOV_Q */
template< > struct AllegrexInstructionTemplate< 0xD0008080, 0xFFFF8080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VMOV_Q"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0008080, 0xFFFF8080 > AllegrexInstruction_VMOV_Q;

namespace Allegrex { extern AllegrexInstruction_VMOV_Q &VMOV_Q; }

/* VABS_S */
template< > struct AllegrexInstructionTemplate< 0xD0010000, 0xFFFF8080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VABS_S"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0010000, 0xFFFF8080 > AllegrexInstruction_VABS_S;

namespace Allegrex { extern AllegrexInstruction_VABS_S &VABS_S; }

/* VABS_P */
template< > struct AllegrexInstructionTemplate< 0xD0010080, 0xFFFF8080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VABS_P"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0010080, 0xFFFF8080 > AllegrexInstruction_VABS_P;

namespace Allegrex { extern AllegrexInstruction_VABS_P &VABS_P; }

/* VABS_T */
template< > struct AllegrexInstructionTemplate< 0xD0018000, 0xFFFF8080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VABS_T"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0018000, 0xFFFF8080 > AllegrexInstruction_VABS_T;

namespace Allegrex { extern AllegrexInstruction_VABS_T &VABS_T; }

/* VABS_Q */
template< > struct AllegrexInstructionTemplate< 0xD0018080, 0xFFFF8080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VABS_Q"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0018080, 0xFFFF8080 > AllegrexInstruction_VABS_Q;

namespace Allegrex { extern AllegrexInstruction_VABS_Q &VABS_Q; }

/* VNEG_S */
template< > struct AllegrexInstructionTemplate< 0xD0020000, 0xFFFF8080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VNEG_S"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0020000, 0xFFFF8080 > AllegrexInstruction_VNEG_S;

namespace Allegrex { extern AllegrexInstruction_VNEG_S &VNEG_S; }

/* VNEG_P */
template< > struct AllegrexInstructionTemplate< 0xD0020080, 0xFFFF8080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VNEG_P"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0020080, 0xFFFF8080 > AllegrexInstruction_VNEG_P;

namespace Allegrex { extern AllegrexInstruction_VNEG_P &VNEG_P; }

/* VNEG_T */
template< > struct AllegrexInstructionTemplate< 0xD0028000, 0xFFFF8080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VNEG_T"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0028000, 0xFFFF8080 > AllegrexInstruction_VNEG_T;

namespace Allegrex { extern AllegrexInstruction_VNEG_T &VNEG_T; }

/* VNEG_Q */
template< > struct AllegrexInstructionTemplate< 0xD0028080, 0xFFFF8080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VNEG_Q"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0028080, 0xFFFF8080 > AllegrexInstruction_VNEG_Q;

namespace Allegrex { extern AllegrexInstruction_VNEG_Q &VNEG_Q; }

/* VIDT_S */
template< > struct AllegrexInstructionTemplate< 0xD0030000, 0xFFFF8F80 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VIDT_S"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0030000, 0xFFFF8F80 > AllegrexInstruction_VIDT_S;

namespace Allegrex { extern AllegrexInstruction_VIDT_S &VIDT_S; }

/* VIDT_P */
template< > struct AllegrexInstructionTemplate< 0xD0030080, 0xFFFF8F80 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VIDT_P"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0030080, 0xFFFF8F80 > AllegrexInstruction_VIDT_P;

namespace Allegrex { extern AllegrexInstruction_VIDT_P &VIDT_P; }

/* VIDT_T */
template< > struct AllegrexInstructionTemplate< 0xD0038000, 0xFFFF8F80 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VIDT_T"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0038000, 0xFFFF8F80 > AllegrexInstruction_VIDT_T;

namespace Allegrex { extern AllegrexInstruction_VIDT_T &VIDT_T; }

/* VIDT_Q */
template< > struct AllegrexInstructionTemplate< 0xD0038080, 0xFFFF8F80 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VIDT_Q"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0038080, 0xFFFF8F80 > AllegrexInstruction_VIDT_Q;

namespace Allegrex { extern AllegrexInstruction_VIDT_Q &VIDT_Q; }

/* VSAT0_S */
template< > struct AllegrexInstructionTemplate< 0xD0040000, 0xFFFF8080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VSAT0_S"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0040000, 0xFFFF8080 > AllegrexInstruction_VSAT0_S;

namespace Allegrex { extern AllegrexInstruction_VSAT0_S &VSAT0_S; }

/* VSAT0_P */
template< > struct AllegrexInstructionTemplate< 0xD0040080, 0xFFFF8080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VSAT0_P"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0040080, 0xFFFF8080 > AllegrexInstruction_VSAT0_P;

namespace Allegrex { extern AllegrexInstruction_VSAT0_P &VSAT0_P; }

/* VSAT0_T */
template< > struct AllegrexInstructionTemplate< 0xD0048000, 0xFFFF8080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VSAT0_T"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0048000, 0xFFFF8080 > AllegrexInstruction_VSAT0_T;

namespace Allegrex { extern AllegrexInstruction_VSAT0_T &VSAT0_T; }

/* VSAT0_Q */
template< > struct AllegrexInstructionTemplate< 0xD0048080, 0xFFFF8080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VSAT0_Q"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0048080, 0xFFFF8080 > AllegrexInstruction_VSAT0_Q;

namespace Allegrex { extern AllegrexInstruction_VSAT0_Q &VSAT0_Q; }

/* VSAT1_S */
template< > struct AllegrexInstructionTemplate< 0xD0050000, 0xFFFF8080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VSAT1_S"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0050000, 0xFFFF8080 > AllegrexInstruction_VSAT1_S;

namespace Allegrex { extern AllegrexInstruction_VSAT1_S &VSAT1_S; }

/* VSAT1_P */
template< > struct AllegrexInstructionTemplate< 0xD0050080, 0xFFFF8080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VSAT1_P"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0050080, 0xFFFF8080 > AllegrexInstruction_VSAT1_P;

namespace Allegrex { extern AllegrexInstruction_VSAT1_P &VSAT1_P; }

/* VSAT1_T */
template< > struct AllegrexInstructionTemplate< 0xD0058000, 0xFFFF8080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VSAT1_T"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0058000, 0xFFFF8080 > AllegrexInstruction_VSAT1_T;

namespace Allegrex { extern AllegrexInstruction_VSAT1_T &VSAT1_T; }

/* VSAT1_Q */
template< > struct AllegrexInstructionTemplate< 0xD0058080, 0xFFFF8080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VSAT1_Q"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0058080, 0xFFFF8080 > AllegrexInstruction_VSAT1_Q;

namespace Allegrex { extern AllegrexInstruction_VSAT1_Q &VSAT1_Q; }

/* VZERO_S */
template< > struct AllegrexInstructionTemplate< 0xD0060000, 0xFFFF8F80 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VZERO_S"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0060000, 0xFFFF8F80 > AllegrexInstruction_VZERO_S;

namespace Allegrex { extern AllegrexInstruction_VZERO_S &VZERO_S; }

/* VZERO_P */
template< > struct AllegrexInstructionTemplate< 0xD0060080, 0xFFFF8F80 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VZERO_P"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0060080, 0xFFFF8F80 > AllegrexInstruction_VZERO_P;

namespace Allegrex { extern AllegrexInstruction_VZERO_P &VZERO_P; }

/* VZERO_T */
template< > struct AllegrexInstructionTemplate< 0xD0068000, 0xFFFF8F80 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VZERO_T"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0068000, 0xFFFF8F80 > AllegrexInstruction_VZERO_T;

namespace Allegrex { extern AllegrexInstruction_VZERO_T &VZERO_T; }

/* VZERO_Q */
template< > struct AllegrexInstructionTemplate< 0xD0068080, 0xFFFF8F80 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VZERO_Q"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0068080, 0xFFFF8F80 > AllegrexInstruction_VZERO_Q;

namespace Allegrex { extern AllegrexInstruction_VZERO_Q &VZERO_Q; }

/* VONE_S */
template< > struct AllegrexInstructionTemplate< 0xD0070000, 0xFFFF8F80 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VONE_S"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0070000, 0xFFFF8F80 > AllegrexInstruction_VONE_S;

namespace Allegrex { extern AllegrexInstruction_VONE_S &VONE_S; }

/* VONE_P */
template< > struct AllegrexInstructionTemplate< 0xD0070080, 0xFFFF8F80 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VONE_P"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0070080, 0xFFFF8F80 > AllegrexInstruction_VONE_P;

namespace Allegrex { extern AllegrexInstruction_VONE_P &VONE_P; }

/* VONE_T */
template< > struct AllegrexInstructionTemplate< 0xD0078000, 0xFFFF8F80 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VONE_T"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0078000, 0xFFFF8F80 > AllegrexInstruction_VONE_T;

namespace Allegrex { extern AllegrexInstruction_VONE_T &VONE_T; }

/* VONE_Q */
template< > struct AllegrexInstructionTemplate< 0xD0078080, 0xFFFF8F80 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VONE_Q"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0078080, 0xFFFF8F80 > AllegrexInstruction_VONE_Q;

namespace Allegrex { extern AllegrexInstruction_VONE_Q &VONE_Q; }

/* VRCP_S */
template< > struct AllegrexInstructionTemplate< 0xD0100000, 0xFFFF8080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VRCP_S"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0100000, 0xFFFF8080 > AllegrexInstruction_VRCP_S;

namespace Allegrex { extern AllegrexInstruction_VRCP_S &VRCP_S; }

/* VRCP_P */
template< > struct AllegrexInstructionTemplate< 0xD0100080, 0xFFFF8080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VRCP_P"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0100080, 0xFFFF8080 > AllegrexInstruction_VRCP_P;

namespace Allegrex { extern AllegrexInstruction_VRCP_P &VRCP_P; }

/* VRCP_T */
template< > struct AllegrexInstructionTemplate< 0xD0108000, 0xFFFF8080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VRCP_T"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0108000, 0xFFFF8080 > AllegrexInstruction_VRCP_T;

namespace Allegrex { extern AllegrexInstruction_VRCP_T &VRCP_T; }

/* VRCP_Q */
template< > struct AllegrexInstructionTemplate< 0xD0108080, 0xFFFF8080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VRCP_Q"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0108080, 0xFFFF8080 > AllegrexInstruction_VRCP_Q;

namespace Allegrex { extern AllegrexInstruction_VRCP_Q &VRCP_Q; }

/* VRSQ_S */
template< > struct AllegrexInstructionTemplate< 0xD0110000, 0xFFFF8080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VRSQ_S"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0110000, 0xFFFF8080 > AllegrexInstruction_VRSQ_S;

namespace Allegrex { extern AllegrexInstruction_VRSQ_S &VRSQ_S; }

/* VRSQ_P */
template< > struct AllegrexInstructionTemplate< 0xD0110080, 0xFFFF8080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VRSQ_P"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0110080, 0xFFFF8080 > AllegrexInstruction_VRSQ_P;

namespace Allegrex { extern AllegrexInstruction_VRSQ_P &VRSQ_P; }

/* VRSQ_T */
template< > struct AllegrexInstructionTemplate< 0xD0118000, 0xFFFF8080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VRSQ_T"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0118000, 0xFFFF8080 > AllegrexInstruction_VRSQ_T;

namespace Allegrex { extern AllegrexInstruction_VRSQ_T &VRSQ_T; }

/* VRSQ_Q */
template< > struct AllegrexInstructionTemplate< 0xD0118080, 0xFFFF8080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VRSQ_Q"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0118080, 0xFFFF8080 > AllegrexInstruction_VRSQ_Q;

namespace Allegrex { extern AllegrexInstruction_VRSQ_Q &VRSQ_Q; }

/* VSIN_S */
template< > struct AllegrexInstructionTemplate< 0xD0120000, 0xFFFF8080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VSIN_S"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0120000, 0xFFFF8080 > AllegrexInstruction_VSIN_S;

namespace Allegrex { extern AllegrexInstruction_VSIN_S &VSIN_S; }

/* VSIN_P */
template< > struct AllegrexInstructionTemplate< 0xD0120080, 0xFFFF8080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VSIN_P"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0120080, 0xFFFF8080 > AllegrexInstruction_VSIN_P;

namespace Allegrex { extern AllegrexInstruction_VSIN_P &VSIN_P; }

/* VSIN_T */
template< > struct AllegrexInstructionTemplate< 0xD0128000, 0xFFFF8080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VSIN_T"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0128000, 0xFFFF8080 > AllegrexInstruction_VSIN_T;

namespace Allegrex { extern AllegrexInstruction_VSIN_T &VSIN_T; }

/* VSIN_Q */
template< > struct AllegrexInstructionTemplate< 0xD0128080, 0xFFFF8080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VSIN_Q"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0128080, 0xFFFF8080 > AllegrexInstruction_VSIN_Q;

namespace Allegrex { extern AllegrexInstruction_VSIN_Q &VSIN_Q; }

/* VCOS_S */
template< > struct AllegrexInstructionTemplate< 0xD0130000, 0xFFFF8080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VCOS_S"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0130000, 0xFFFF8080 > AllegrexInstruction_VCOS_S;

namespace Allegrex { extern AllegrexInstruction_VCOS_S &VCOS_S; }

/* VCOS_P */
template< > struct AllegrexInstructionTemplate< 0xD0130080, 0xFFFF8080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VCOS_P"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0130080, 0xFFFF8080 > AllegrexInstruction_VCOS_P;

namespace Allegrex { extern AllegrexInstruction_VCOS_P &VCOS_P; }

/* VCOS_T */
template< > struct AllegrexInstructionTemplate< 0xD0138000, 0xFFFF8080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VCOS_T"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0138000, 0xFFFF8080 > AllegrexInstruction_VCOS_T;

namespace Allegrex { extern AllegrexInstruction_VCOS_T &VCOS_T; }

/* VCOS_Q */
template< > struct AllegrexInstructionTemplate< 0xD0138080, 0xFFFF8080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VCOS_Q"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0138080, 0xFFFF8080 > AllegrexInstruction_VCOS_Q;

namespace Allegrex { extern AllegrexInstruction_VCOS_Q &VCOS_Q; }

/* VEXP2_S */
template< > struct AllegrexInstructionTemplate< 0xD0140000, 0xFFFF8080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VEXP2_S"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0140000, 0xFFFF8080 > AllegrexInstruction_VEXP2_S;

namespace Allegrex { extern AllegrexInstruction_VEXP2_S &VEXP2_S; }

/* VEXP2_P */
template< > struct AllegrexInstructionTemplate< 0xD0140080, 0xFFFF8080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VEXP2_P"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0140080, 0xFFFF8080 > AllegrexInstruction_VEXP2_P;

namespace Allegrex { extern AllegrexInstruction_VEXP2_P &VEXP2_P; }

/* VEXP2_T */
template< > struct AllegrexInstructionTemplate< 0xD0148000, 0xFFFF8080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VEXP2_T"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0148000, 0xFFFF8080 > AllegrexInstruction_VEXP2_T;

namespace Allegrex { extern AllegrexInstruction_VEXP2_T &VEXP2_T; }

/* VEXP2_Q */
template< > struct AllegrexInstructionTemplate< 0xD0148080, 0xFFFF8080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VEXP2_Q"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0148080, 0xFFFF8080 > AllegrexInstruction_VEXP2_Q;

namespace Allegrex { extern AllegrexInstruction_VEXP2_Q &VEXP2_Q; }

/* VLOG2_S */
template< > struct AllegrexInstructionTemplate< 0xD0150000, 0xFFFF8080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VLOG2_S"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0150000, 0xFFFF8080 > AllegrexInstruction_VLOG2_S;

namespace Allegrex { extern AllegrexInstruction_VLOG2_S &VLOG2_S; }

/* VLOG2_P */
template< > struct AllegrexInstructionTemplate< 0xD0150080, 0xFFFF8080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VLOG2_P"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0150080, 0xFFFF8080 > AllegrexInstruction_VLOG2_P;

namespace Allegrex { extern AllegrexInstruction_VLOG2_P &VLOG2_P; }

/* VLOG2_T */
template< > struct AllegrexInstructionTemplate< 0xD0158000, 0xFFFF8080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VLOG2_T"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0158000, 0xFFFF8080 > AllegrexInstruction_VLOG2_T;

namespace Allegrex { extern AllegrexInstruction_VLOG2_T &VLOG2_T; }

/* VLOG2_Q */
template< > struct AllegrexInstructionTemplate< 0xD0158080, 0xFFFF8080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VLOG2_Q"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0158080, 0xFFFF8080 > AllegrexInstruction_VLOG2_Q;

namespace Allegrex { extern AllegrexInstruction_VLOG2_Q &VLOG2_Q; }

/* VSQRT_S */
template< > struct AllegrexInstructionTemplate< 0xD0160000, 0xFFFF8080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VSQRT_S"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0160000, 0xFFFF8080 > AllegrexInstruction_VSQRT_S;

namespace Allegrex { extern AllegrexInstruction_VSQRT_S &VSQRT_S; }

/* VSQRT_P */
template< > struct AllegrexInstructionTemplate< 0xD0160080, 0xFFFF8080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VSQRT_P"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0160080, 0xFFFF8080 > AllegrexInstruction_VSQRT_P;

namespace Allegrex { extern AllegrexInstruction_VSQRT_P &VSQRT_P; }

/* VSQRT_T */
template< > struct AllegrexInstructionTemplate< 0xD0168000, 0xFFFF8080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VSQRT_T"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0168000, 0xFFFF8080 > AllegrexInstruction_VSQRT_T;

namespace Allegrex { extern AllegrexInstruction_VSQRT_T &VSQRT_T; }

/* VSQRT_Q */
template< > struct AllegrexInstructionTemplate< 0xD0168080, 0xFFFF8080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VSQRT_Q"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0168080, 0xFFFF8080 > AllegrexInstruction_VSQRT_Q;

namespace Allegrex { extern AllegrexInstruction_VSQRT_Q &VSQRT_Q; }

/* VASIN_S */
template< > struct AllegrexInstructionTemplate< 0xD0170000, 0xFFFF8080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VASIN_S"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0170000, 0xFFFF8080 > AllegrexInstruction_VASIN_S;

namespace Allegrex { extern AllegrexInstruction_VASIN_S &VASIN_S; }

/* VASIN_P */
template< > struct AllegrexInstructionTemplate< 0xD0170080, 0xFFFF8080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VASIN_P"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0170080, 0xFFFF8080 > AllegrexInstruction_VASIN_P;

namespace Allegrex { extern AllegrexInstruction_VASIN_P &VASIN_P; }

/* VASIN_T */
template< > struct AllegrexInstructionTemplate< 0xD0178000, 0xFFFF8080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VASIN_T"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0178000, 0xFFFF8080 > AllegrexInstruction_VASIN_T;

namespace Allegrex { extern AllegrexInstruction_VASIN_T &VASIN_T; }

/* VASIN_Q */
template< > struct AllegrexInstructionTemplate< 0xD0178080, 0xFFFF8080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VASIN_Q"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0178080, 0xFFFF8080 > AllegrexInstruction_VASIN_Q;

namespace Allegrex { extern AllegrexInstruction_VASIN_Q &VASIN_Q; }

/* VNRCP_S */
template< > struct AllegrexInstructionTemplate< 0xD0180000, 0xFFFF8080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VNRCP_S"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0180000, 0xFFFF8080 > AllegrexInstruction_VNRCP_S;

namespace Allegrex { extern AllegrexInstruction_VNRCP_S &VNRCP_S; }

/* VNRCP_P */
template< > struct AllegrexInstructionTemplate< 0xD0180080, 0xFFFF8080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VNRCP_P"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0180080, 0xFFFF8080 > AllegrexInstruction_VNRCP_P;

namespace Allegrex { extern AllegrexInstruction_VNRCP_P &VNRCP_P; }

/* VNRCP_T */
template< > struct AllegrexInstructionTemplate< 0xD0188000, 0xFFFF8080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VNRCP_T"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0188000, 0xFFFF8080 > AllegrexInstruction_VNRCP_T;

namespace Allegrex { extern AllegrexInstruction_VNRCP_T &VNRCP_T; }

/* VNRCP_Q */
template< > struct AllegrexInstructionTemplate< 0xD0188080, 0xFFFF8080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VNRCP_Q"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0188080, 0xFFFF8080 > AllegrexInstruction_VNRCP_Q;

namespace Allegrex { extern AllegrexInstruction_VNRCP_Q &VNRCP_Q; }

/* VNSIN_S */
template< > struct AllegrexInstructionTemplate< 0xD01A0000, 0xFFFF8080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VNSIN_S"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD01A0000, 0xFFFF8080 > AllegrexInstruction_VNSIN_S;

namespace Allegrex { extern AllegrexInstruction_VNSIN_S &VNSIN_S; }

/* VNSIN_P */
template< > struct AllegrexInstructionTemplate< 0xD01A0080, 0xFFFF8080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VNSIN_P"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD01A0080, 0xFFFF8080 > AllegrexInstruction_VNSIN_P;

namespace Allegrex { extern AllegrexInstruction_VNSIN_P &VNSIN_P; }

/* VNSIN_T */
template< > struct AllegrexInstructionTemplate< 0xD01A8000, 0xFFFF8080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VNSIN_T"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD01A8000, 0xFFFF8080 > AllegrexInstruction_VNSIN_T;

namespace Allegrex { extern AllegrexInstruction_VNSIN_T &VNSIN_T; }

/* VNSIN_Q */
template< > struct AllegrexInstructionTemplate< 0xD01A8080, 0xFFFF8080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VNSIN_Q"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD01A8080, 0xFFFF8080 > AllegrexInstruction_VNSIN_Q;

namespace Allegrex { extern AllegrexInstruction_VNSIN_Q &VNSIN_Q; }

/* VREXP2_S */
template< > struct AllegrexInstructionTemplate< 0xD01C0000, 0xFFFF8080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VREXP2_S"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD01C0000, 0xFFFF8080 > AllegrexInstruction_VREXP2_S;

namespace Allegrex { extern AllegrexInstruction_VREXP2_S &VREXP2_S; }

/* VREXP2_P */
template< > struct AllegrexInstructionTemplate< 0xD01C0080, 0xFFFF8080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VREXP2_P"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD01C0080, 0xFFFF8080 > AllegrexInstruction_VREXP2_P;

namespace Allegrex { extern AllegrexInstruction_VREXP2_P &VREXP2_P; }

/* VREXP2_T */
template< > struct AllegrexInstructionTemplate< 0xD01C8000, 0xFFFF8080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VREXP2_T"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD01C8000, 0xFFFF8080 > AllegrexInstruction_VREXP2_T;

namespace Allegrex { extern AllegrexInstruction_VREXP2_T &VREXP2_T; }

/* VREXP2_Q */
template< > struct AllegrexInstructionTemplate< 0xD01C8080, 0xFFFF8080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VREXP2_Q"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD01C8080, 0xFFFF8080 > AllegrexInstruction_VREXP2_Q;

namespace Allegrex { extern AllegrexInstruction_VREXP2_Q &VREXP2_Q; }

/* VRNDS_S */
template< > struct AllegrexInstructionTemplate< 0xD0200000, 0xFFFF808F > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VRNDS_S"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0200000, 0xFFFF808F > AllegrexInstruction_VRNDS_S;

namespace Allegrex { extern AllegrexInstruction_VRNDS_S &VRNDS_S; }

/* VRNDI_S */
template< > struct AllegrexInstructionTemplate< 0xD0210000, 0xFFFF8F80 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VRNDI_S"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0210000, 0xFFFF8F80 > AllegrexInstruction_VRNDI_S;

namespace Allegrex { extern AllegrexInstruction_VRNDI_S &VRNDI_S; }

/* VRNDI_P */
template< > struct AllegrexInstructionTemplate< 0xD0210080, 0xFFFF8F80 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VRNDI_P"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0210080, 0xFFFF8F80 > AllegrexInstruction_VRNDI_P;

namespace Allegrex { extern AllegrexInstruction_VRNDI_P &VRNDI_P; }

/* VRNDI_T */
template< > struct AllegrexInstructionTemplate< 0xD0218000, 0xFFFF8F80 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VRNDI_T"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0218000, 0xFFFF8F80 > AllegrexInstruction_VRNDI_T;

namespace Allegrex { extern AllegrexInstruction_VRNDI_T &VRNDI_T; }

/* VRNDI_Q */
template< > struct AllegrexInstructionTemplate< 0xD0218080, 0xFFFF8F80 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VRNDI_Q"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0218080, 0xFFFF8F80 > AllegrexInstruction_VRNDI_Q;

namespace Allegrex { extern AllegrexInstruction_VRNDI_Q &VRNDI_Q; }

/* VRNDF1_S */
template< > struct AllegrexInstructionTemplate< 0xD0220000, 0xFFFF8F80 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VRNDF1_S"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0220000, 0xFFFF8F80 > AllegrexInstruction_VRNDF1_S;

namespace Allegrex { extern AllegrexInstruction_VRNDF1_S &VRNDF1_S; }

/* VRNDF1_P */
template< > struct AllegrexInstructionTemplate< 0xD0220080, 0xFFFF8F80 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VRNDF1_P"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0220080, 0xFFFF8F80 > AllegrexInstruction_VRNDF1_P;

namespace Allegrex { extern AllegrexInstruction_VRNDF1_P &VRNDF1_P; }

/* VRNDF1_T */
template< > struct AllegrexInstructionTemplate< 0xD0228000, 0xFFFF8F80 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VRNDF1_T"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0228000, 0xFFFF8F80 > AllegrexInstruction_VRNDF1_T;

namespace Allegrex { extern AllegrexInstruction_VRNDF1_T &VRNDF1_T; }

/* VRNDF1_Q */
template< > struct AllegrexInstructionTemplate< 0xD0228080, 0xFFFF8F80 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VRNDF1_Q"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0228080, 0xFFFF8F80 > AllegrexInstruction_VRNDF1_Q;

namespace Allegrex { extern AllegrexInstruction_VRNDF1_Q &VRNDF1_Q; }

/* VRNDF2_S */
template< > struct AllegrexInstructionTemplate< 0xD0230000, 0xFFFF8F80 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VRNDF2_S"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0230000, 0xFFFF8F80 > AllegrexInstruction_VRNDF2_S;

namespace Allegrex { extern AllegrexInstruction_VRNDF2_S &VRNDF2_S; }

/* VRNDF2_P */
template< > struct AllegrexInstructionTemplate< 0xD0230080, 0xFFFF8F80 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VRNDF2_P"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0230080, 0xFFFF8F80 > AllegrexInstruction_VRNDF2_P;

namespace Allegrex { extern AllegrexInstruction_VRNDF2_P &VRNDF2_P; }

/* VRNDF2_T */
template< > struct AllegrexInstructionTemplate< 0xD0238000, 0xFFFF8F80 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VRNDF2_T"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0238000, 0xFFFF8F80 > AllegrexInstruction_VRNDF2_T;

namespace Allegrex { extern AllegrexInstruction_VRNDF2_T &VRNDF2_T; }

/* VRNDF2_Q */
template< > struct AllegrexInstructionTemplate< 0xD0238080, 0xFFFF8F80 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VRNDF2_Q"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0238080, 0xFFFF8F80 > AllegrexInstruction_VRNDF2_Q;

namespace Allegrex { extern AllegrexInstruction_VRNDF2_Q &VRNDF2_Q; }

/* VF2H_P */
template< > struct AllegrexInstructionTemplate< 0xD0320080, 0xFFFF8080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VF2H_P"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0320080, 0xFFFF8080 > AllegrexInstruction_VF2H_P;

namespace Allegrex { extern AllegrexInstruction_VF2H_P &VF2H_P; }

/* VF2H_Q */
template< > struct AllegrexInstructionTemplate< 0xD0328080, 0xFFFF8080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VF2H_Q"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0328080, 0xFFFF8080 > AllegrexInstruction_VF2H_Q;

namespace Allegrex { extern AllegrexInstruction_VF2H_Q &VF2H_Q; }

/* VH2F_S */
template< > struct AllegrexInstructionTemplate< 0xD0330000, 0xFFFF8080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VH2F_S"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0330000, 0xFFFF8080 > AllegrexInstruction_VH2F_S;

namespace Allegrex { extern AllegrexInstruction_VH2F_S &VH2F_S; }

/* VH2F_P */
template< > struct AllegrexInstructionTemplate< 0xD0330080, 0xFFFF8080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VH2F_P"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0330080, 0xFFFF8080 > AllegrexInstruction_VH2F_P;

namespace Allegrex { extern AllegrexInstruction_VH2F_P &VH2F_P; }

/* VSBZ_P */
template< > struct AllegrexInstructionTemplate< 0xD0360000, 0xFFFF8080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VSBZ_P"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0360000, 0xFFFF8080 > AllegrexInstruction_VSBZ_P;

namespace Allegrex { extern AllegrexInstruction_VSBZ_P &VSBZ_P; }

/* VLGB_S */
template< > struct AllegrexInstructionTemplate< 0xD0370000, 0xFFFF8080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VLGB_S"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0370000, 0xFFFF8080 > AllegrexInstruction_VLGB_S;

namespace Allegrex { extern AllegrexInstruction_VLGB_S &VLGB_S; }

/* VUC2I_S */
template< > struct AllegrexInstructionTemplate< 0xD0380000, 0xFFFF8080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VUC2I_S"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0380000, 0xFFFF8080 > AllegrexInstruction_VUC2I_S;

namespace Allegrex { extern AllegrexInstruction_VUC2I_S &VUC2I_S; }

/* VC2I_S */
template< > struct AllegrexInstructionTemplate< 0xD0390000, 0xFFFF8080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VC2I_S"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0390000, 0xFFFF8080 > AllegrexInstruction_VC2I_S;

namespace Allegrex { extern AllegrexInstruction_VC2I_S &VC2I_S; }

/* VUS2I_S */
template< > struct AllegrexInstructionTemplate< 0xD03A0000, 0xFFFF8080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VUS2I_S"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD03A0000, 0xFFFF8080 > AllegrexInstruction_VUS2I_S;

namespace Allegrex { extern AllegrexInstruction_VUS2I_S &VUS2I_S; }

/* VUS2I_P */
template< > struct AllegrexInstructionTemplate< 0xD03A0080, 0xFFFF8080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VUS2I_P"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD03A0080, 0xFFFF8080 > AllegrexInstruction_VUS2I_P;

namespace Allegrex { extern AllegrexInstruction_VUS2I_P &VUS2I_P; }

/* VS2I_S */
template< > struct AllegrexInstructionTemplate< 0xD03B0000, 0xFFFF8080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VS2I_S"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD03B0000, 0xFFFF8080 > AllegrexInstruction_VS2I_S;

namespace Allegrex { extern AllegrexInstruction_VS2I_S &VS2I_S; }

/* VS2I_P */
template< > struct AllegrexInstructionTemplate< 0xD03B0080, 0xFFFF8080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VS2I_P"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD03B0080, 0xFFFF8080 > AllegrexInstruction_VS2I_P;

namespace Allegrex { extern AllegrexInstruction_VS2I_P &VS2I_P; }

/* VI2UC_Q */
template< > struct AllegrexInstructionTemplate< 0xD03C8080, 0xFFFF8080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VI2UC_Q"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD03C8080, 0xFFFF8080 > AllegrexInstruction_VI2UC_Q;

namespace Allegrex { extern AllegrexInstruction_VI2UC_Q &VI2UC_Q; }

/* VI2C_Q */
template< > struct AllegrexInstructionTemplate< 0xD03D8080, 0xFFFF8080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VI2C_Q"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD03D8080, 0xFFFF8080 > AllegrexInstruction_VI2C_Q;

namespace Allegrex { extern AllegrexInstruction_VI2C_Q &VI2C_Q; }

/* VI2US_P */
template< > struct AllegrexInstructionTemplate< 0xD03E0080, 0xFFFF8080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VI2US_P"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD03E0080, 0xFFFF8080 > AllegrexInstruction_VI2US_P;

namespace Allegrex { extern AllegrexInstruction_VI2US_P &VI2US_P; }

/* VI2US_Q */
template< > struct AllegrexInstructionTemplate< 0xD03E8080, 0xFFFF8080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VI2US_Q"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD03E8080, 0xFFFF8080 > AllegrexInstruction_VI2US_Q;

namespace Allegrex { extern AllegrexInstruction_VI2US_Q &VI2US_Q; }

/* VI2S_P */
template< > struct AllegrexInstructionTemplate< 0xD03F0080, 0xFFFF8080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VI2S_P"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD03F0080, 0xFFFF8080 > AllegrexInstruction_VI2S_P;

namespace Allegrex { extern AllegrexInstruction_VI2S_P &VI2S_P; }

/* VI2S_Q */
template< > struct AllegrexInstructionTemplate< 0xD03F8080, 0xFFFF8080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VI2S_Q"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD03F8080, 0xFFFF8080 > AllegrexInstruction_VI2S_Q;

namespace Allegrex { extern AllegrexInstruction_VI2S_Q &VI2S_Q; }

/* VSRT1_Q */
template< > struct AllegrexInstructionTemplate< 0xD0408080, 0xFFFF8080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VSRT1_Q"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0408080, 0xFFFF8080 > AllegrexInstruction_VSRT1_Q;

namespace Allegrex { extern AllegrexInstruction_VSRT1_Q &VSRT1_Q; }

/* VSRT2_Q */
template< > struct AllegrexInstructionTemplate< 0xD0418080, 0xFFFF8080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VSRT2_Q"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0418080, 0xFFFF8080 > AllegrexInstruction_VSRT2_Q;

namespace Allegrex { extern AllegrexInstruction_VSRT2_Q &VSRT2_Q; }

/* VBFY1_P */
template< > struct AllegrexInstructionTemplate< 0xD0420080, 0xFFFF8080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VBFY1_P"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0420080, 0xFFFF8080 > AllegrexInstruction_VBFY1_P;

namespace Allegrex { extern AllegrexInstruction_VBFY1_P &VBFY1_P; }

/* VBFY1_Q */
template< > struct AllegrexInstructionTemplate< 0xD0428080, 0xFFFF8080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VBFY1_Q"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0428080, 0xFFFF8080 > AllegrexInstruction_VBFY1_Q;

namespace Allegrex { extern AllegrexInstruction_VBFY1_Q &VBFY1_Q; }

/* VBFY2_Q */
template< > struct AllegrexInstructionTemplate< 0xD0438080, 0xFFFF8080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VBFY2_Q"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0438080, 0xFFFF8080 > AllegrexInstruction_VBFY2_Q;

namespace Allegrex { extern AllegrexInstruction_VBFY2_Q &VBFY2_Q; }

/* VOCP_S */
template< > struct AllegrexInstructionTemplate< 0xD0440000, 0xFFFF8080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VOCP_S"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0440000, 0xFFFF8080 > AllegrexInstruction_VOCP_S;

namespace Allegrex { extern AllegrexInstruction_VOCP_S &VOCP_S; }

/* VOCP_P */
template< > struct AllegrexInstructionTemplate< 0xD0440080, 0xFFFF8080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VOCP_P"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0440080, 0xFFFF8080 > AllegrexInstruction_VOCP_P;

namespace Allegrex { extern AllegrexInstruction_VOCP_P &VOCP_P; }

/* VOCP_T */
template< > struct AllegrexInstructionTemplate< 0xD0448000, 0xFFFF8080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VOCP_T"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0448000, 0xFFFF8080 > AllegrexInstruction_VOCP_T;

namespace Allegrex { extern AllegrexInstruction_VOCP_T &VOCP_T; }

/* VOCP_Q */
template< > struct AllegrexInstructionTemplate< 0xD0448080, 0xFFFF8080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VOCP_Q"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0448080, 0xFFFF8080 > AllegrexInstruction_VOCP_Q;

namespace Allegrex { extern AllegrexInstruction_VOCP_Q &VOCP_Q; }

/* VSOCP_S */
template< > struct AllegrexInstructionTemplate< 0xD0450000, 0xFFFF8080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VSOCP_S"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0450000, 0xFFFF8080 > AllegrexInstruction_VSOCP_S;

namespace Allegrex { extern AllegrexInstruction_VSOCP_S &VSOCP_S; }

/* VSOCP_P */
template< > struct AllegrexInstructionTemplate< 0xD0450080, 0xFFFF8080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VSOCP_P"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0450080, 0xFFFF8080 > AllegrexInstruction_VSOCP_P;

namespace Allegrex { extern AllegrexInstruction_VSOCP_P &VSOCP_P; }

/* VFAD_P */
template< > struct AllegrexInstructionTemplate< 0xD0460080, 0xFFFF8080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VFAD_P"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0460080, 0xFFFF8080 > AllegrexInstruction_VFAD_P;

namespace Allegrex { extern AllegrexInstruction_VFAD_P &VFAD_P; }

/* VFAD_T */
template< > struct AllegrexInstructionTemplate< 0xD0468000, 0xFFFF8080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VFAD_T"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0468000, 0xFFFF8080 > AllegrexInstruction_VFAD_T;

namespace Allegrex { extern AllegrexInstruction_VFAD_T &VFAD_T; }

/* VFAD_Q */
template< > struct AllegrexInstructionTemplate< 0xD0468080, 0xFFFF8080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VFAD_Q"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0468080, 0xFFFF8080 > AllegrexInstruction_VFAD_Q;

namespace Allegrex { extern AllegrexInstruction_VFAD_Q &VFAD_Q; }

/* VAVG_P */
template< > struct AllegrexInstructionTemplate< 0xD0470080, 0xFFFF8080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VAVG_P"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0470080, 0xFFFF8080 > AllegrexInstruction_VAVG_P;

namespace Allegrex { extern AllegrexInstruction_VAVG_P &VAVG_P; }

/* VAVG_T */
template< > struct AllegrexInstructionTemplate< 0xD0478000, 0xFFFF8080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VAVG_T"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0478000, 0xFFFF8080 > AllegrexInstruction_VAVG_T;

namespace Allegrex { extern AllegrexInstruction_VAVG_T &VAVG_T; }

/* VAVG_Q */
template< > struct AllegrexInstructionTemplate< 0xD0478080, 0xFFFF8080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VAVG_Q"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0478080, 0xFFFF8080 > AllegrexInstruction_VAVG_Q;

namespace Allegrex { extern AllegrexInstruction_VAVG_Q &VAVG_Q; }

/* VSRT3_Q */
template< > struct AllegrexInstructionTemplate< 0xD0488080, 0xFFFF8080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VSRT3_Q"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0488080, 0xFFFF8080 > AllegrexInstruction_VSRT3_Q;

namespace Allegrex { extern AllegrexInstruction_VSRT3_Q &VSRT3_Q; }

/* VSRT4_Q */
template< > struct AllegrexInstructionTemplate< 0xD0498080, 0xFFFF8080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VSRT4_Q"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0498080, 0xFFFF8080 > AllegrexInstruction_VSRT4_Q;

namespace Allegrex { extern AllegrexInstruction_VSRT4_Q &VSRT4_Q; }

/* VSGN_S */
template< > struct AllegrexInstructionTemplate< 0xD04A0000, 0xFFFF8080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VSGN_S"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD04A0000, 0xFFFF8080 > AllegrexInstruction_VSGN_S;

namespace Allegrex { extern AllegrexInstruction_VSGN_S &VSGN_S; }

/* VSGN_P */
template< > struct AllegrexInstructionTemplate< 0xD04A0080, 0xFFFF8080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VSGN_P"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD04A0080, 0xFFFF8080 > AllegrexInstruction_VSGN_P;

namespace Allegrex { extern AllegrexInstruction_VSGN_P &VSGN_P; }

/* VSGN_T */
template< > struct AllegrexInstructionTemplate< 0xD04A8000, 0xFFFF8080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VSGN_T"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD04A8000, 0xFFFF8080 > AllegrexInstruction_VSGN_T;

namespace Allegrex { extern AllegrexInstruction_VSGN_T &VSGN_T; }

/* VSGN_Q */
template< > struct AllegrexInstructionTemplate< 0xD04A8080, 0xFFFF8080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VSGN_Q"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD04A8080, 0xFFFF8080 > AllegrexInstruction_VSGN_Q;

namespace Allegrex { extern AllegrexInstruction_VSGN_Q &VSGN_Q; }

/* VMFVC */
template< > struct AllegrexInstructionTemplate< 0xD0508000, 0xFFFF8080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VMFVC"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0508000, 0xFFFF8080 > AllegrexInstruction_VMFVC;

namespace Allegrex { extern AllegrexInstruction_VMFVC &VMFVC; }

/* VMTVC */
template< > struct AllegrexInstructionTemplate< 0xD0510080, 0xFFFF8080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VMTVC"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0510080, 0xFFFF8080 > AllegrexInstruction_VMTVC;

namespace Allegrex { extern AllegrexInstruction_VMTVC &VMTVC; }

/* VT4444_Q */
template< > struct AllegrexInstructionTemplate< 0xD0598080, 0xFFFF8080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VT4444_Q"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0598080, 0xFFFF8080 > AllegrexInstruction_VT4444_Q;

namespace Allegrex { extern AllegrexInstruction_VT4444_Q &VT4444_Q; }

/* VT5551_Q */
template< > struct AllegrexInstructionTemplate< 0xD05A8080, 0xFFFF8080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VT5551_Q"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD05A8080, 0xFFFF8080 > AllegrexInstruction_VT5551_Q;

namespace Allegrex { extern AllegrexInstruction_VT5551_Q &VT5551_Q; }

/* VT5650_Q */
template< > struct AllegrexInstructionTemplate< 0xD05B8080, 0xFFFF8080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VT5650_Q"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD05B8080, 0xFFFF8080 > AllegrexInstruction_VT5650_Q;

namespace Allegrex { extern AllegrexInstruction_VT5650_Q &VT5650_Q; }

/* VCST_S */
template< > struct AllegrexInstructionTemplate< 0xD0600000, 0xFFE08F80 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VCST_S"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0600000, 0xFFE08F80 > AllegrexInstruction_VCST_S;

namespace Allegrex { extern AllegrexInstruction_VCST_S &VCST_S; }

/* VCST_P */
template< > struct AllegrexInstructionTemplate< 0xD0600080, 0xFFE08F80 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VCST_P"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0600080, 0xFFE08F80 > AllegrexInstruction_VCST_P;

namespace Allegrex { extern AllegrexInstruction_VCST_P &VCST_P; }

/* VCST_T */
template< > struct AllegrexInstructionTemplate< 0xD0608000, 0xFFE08F80 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VCST_T"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0608000, 0xFFE08F80 > AllegrexInstruction_VCST_T;

namespace Allegrex { extern AllegrexInstruction_VCST_T &VCST_T; }

/* VCST_Q */
template< > struct AllegrexInstructionTemplate< 0xD0608080, 0xFFE08F80 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VCST_Q"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD0608080, 0xFFE08F80 > AllegrexInstruction_VCST_Q;

namespace Allegrex { extern AllegrexInstruction_VCST_Q &VCST_Q; }

/* VF2IN_S */
template< > struct AllegrexInstructionTemplate< 0xD2000000, 0xFFE08080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VF2IN_S"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD2000000, 0xFFE08080 > AllegrexInstruction_VF2IN_S;

namespace Allegrex { extern AllegrexInstruction_VF2IN_S &VF2IN_S; }

/* VF2IN_P */
template< > struct AllegrexInstructionTemplate< 0xD2000080, 0xFFE08080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VF2IN_P"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD2000080, 0xFFE08080 > AllegrexInstruction_VF2IN_P;

namespace Allegrex { extern AllegrexInstruction_VF2IN_P &VF2IN_P; }

/* VF2IN_T */
template< > struct AllegrexInstructionTemplate< 0xD2008000, 0xFFE08080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VF2IN_T"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD2008000, 0xFFE08080 > AllegrexInstruction_VF2IN_T;

namespace Allegrex { extern AllegrexInstruction_VF2IN_T &VF2IN_T; }

/* VF2IN_Q */
template< > struct AllegrexInstructionTemplate< 0xD2008080, 0xFFE08080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VF2IN_Q"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD2008080, 0xFFE08080 > AllegrexInstruction_VF2IN_Q;

namespace Allegrex { extern AllegrexInstruction_VF2IN_Q &VF2IN_Q; }

/* VF2IZ_S */
template< > struct AllegrexInstructionTemplate< 0xD2200000, 0xFFE08080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VF2IZ_S"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD2200000, 0xFFE08080 > AllegrexInstruction_VF2IZ_S;

namespace Allegrex { extern AllegrexInstruction_VF2IZ_S &VF2IZ_S; }

/* VF2IZ_P */
template< > struct AllegrexInstructionTemplate< 0xD2200080, 0xFFE08080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VF2IZ_P"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD2200080, 0xFFE08080 > AllegrexInstruction_VF2IZ_P;

namespace Allegrex { extern AllegrexInstruction_VF2IZ_P &VF2IZ_P; }

/* VF2IZ_T */
template< > struct AllegrexInstructionTemplate< 0xD2208000, 0xFFE08080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VF2IZ_T"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD2208000, 0xFFE08080 > AllegrexInstruction_VF2IZ_T;

namespace Allegrex { extern AllegrexInstruction_VF2IZ_T &VF2IZ_T; }

/* VF2IZ_Q */
template< > struct AllegrexInstructionTemplate< 0xD2208080, 0xFFE08080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VF2IZ_Q"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD2208080, 0xFFE08080 > AllegrexInstruction_VF2IZ_Q;

namespace Allegrex { extern AllegrexInstruction_VF2IZ_Q &VF2IZ_Q; }

/* VF2IU_S */
template< > struct AllegrexInstructionTemplate< 0xD2400000, 0xFFE08080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VF2IU_S"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD2400000, 0xFFE08080 > AllegrexInstruction_VF2IU_S;

namespace Allegrex { extern AllegrexInstruction_VF2IU_S &VF2IU_S; }

/* VF2IU_P */
template< > struct AllegrexInstructionTemplate< 0xD2400080, 0xFFE08080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VF2IU_P"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD2400080, 0xFFE08080 > AllegrexInstruction_VF2IU_P;

namespace Allegrex { extern AllegrexInstruction_VF2IU_P &VF2IU_P; }

/* VF2IU_T */
template< > struct AllegrexInstructionTemplate< 0xD2408000, 0xFFE08080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VF2IU_T"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD2408000, 0xFFE08080 > AllegrexInstruction_VF2IU_T;

namespace Allegrex { extern AllegrexInstruction_VF2IU_T &VF2IU_T; }

/* VF2IU_Q */
template< > struct AllegrexInstructionTemplate< 0xD2408080, 0xFFE08080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VF2IU_Q"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD2408080, 0xFFE08080 > AllegrexInstruction_VF2IU_Q;

namespace Allegrex { extern AllegrexInstruction_VF2IU_Q &VF2IU_Q; }

/* VF2ID_S */
template< > struct AllegrexInstructionTemplate< 0xD2600000, 0xFFE08080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VF2ID_S"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD2600000, 0xFFE08080 > AllegrexInstruction_VF2ID_S;

namespace Allegrex { extern AllegrexInstruction_VF2ID_S &VF2ID_S; }

/* VF2ID_P */
template< > struct AllegrexInstructionTemplate< 0xD2600080, 0xFFE08080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VF2ID_P"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD2600080, 0xFFE08080 > AllegrexInstruction_VF2ID_P;

namespace Allegrex { extern AllegrexInstruction_VF2ID_P &VF2ID_P; }

/* VF2ID_T */
template< > struct AllegrexInstructionTemplate< 0xD2608000, 0xFFE08080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VF2ID_T"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD2608000, 0xFFE08080 > AllegrexInstruction_VF2ID_T;

namespace Allegrex { extern AllegrexInstruction_VF2ID_T &VF2ID_T; }

/* VF2ID_Q */
template< > struct AllegrexInstructionTemplate< 0xD2608080, 0xFFE08080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VF2ID_Q"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD2608080, 0xFFE08080 > AllegrexInstruction_VF2ID_Q;

namespace Allegrex { extern AllegrexInstruction_VF2ID_Q &VF2ID_Q; }

/* VI2F_S */
template< > struct AllegrexInstructionTemplate< 0xD2800000, 0xFFE08080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VI2F_S"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD2800000, 0xFFE08080 > AllegrexInstruction_VI2F_S;

namespace Allegrex { extern AllegrexInstruction_VI2F_S &VI2F_S; }

/* VI2F_P */
template< > struct AllegrexInstructionTemplate< 0xD2800080, 0xFFE08080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VI2F_P"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD2800080, 0xFFE08080 > AllegrexInstruction_VI2F_P;

namespace Allegrex { extern AllegrexInstruction_VI2F_P &VI2F_P; }

/* VI2F_T */
template< > struct AllegrexInstructionTemplate< 0xD2808000, 0xFFE08080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VI2F_T"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD2808000, 0xFFE08080 > AllegrexInstruction_VI2F_T;

namespace Allegrex { extern AllegrexInstruction_VI2F_T &VI2F_T; }

/* VI2F_Q */
template< > struct AllegrexInstructionTemplate< 0xD2808080, 0xFFE08080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VI2F_Q"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD2808080, 0xFFE08080 > AllegrexInstruction_VI2F_Q;

namespace Allegrex { extern AllegrexInstruction_VI2F_Q &VI2F_Q; }

/* VCMOVT_S */
template< > struct AllegrexInstructionTemplate< 0xD2A00000, 0xFFF88080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VCMOVT_S"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD2A00000, 0xFFF88080 > AllegrexInstruction_VCMOVT_S;

namespace Allegrex { extern AllegrexInstruction_VCMOVT_S &VCMOVT_S; }

/* VCMOVT_P */
template< > struct AllegrexInstructionTemplate< 0xD2A00080, 0xFFF88080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VCMOVT_P"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD2A00080, 0xFFF88080 > AllegrexInstruction_VCMOVT_P;

namespace Allegrex { extern AllegrexInstruction_VCMOVT_P &VCMOVT_P; }

/* VCMOVT_T */
template< > struct AllegrexInstructionTemplate< 0xD2A08000, 0xFFF88080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VCMOVT_T"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD2A08000, 0xFFF88080 > AllegrexInstruction_VCMOVT_T;

namespace Allegrex { extern AllegrexInstruction_VCMOVT_T &VCMOVT_T; }

/* VCMOVT_Q */
template< > struct AllegrexInstructionTemplate< 0xD2A08080, 0xFFF88080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VCMOVT_Q"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD2A08080, 0xFFF88080 > AllegrexInstruction_VCMOVT_Q;

namespace Allegrex { extern AllegrexInstruction_VCMOVT_Q &VCMOVT_Q; }

/* VCMOVF_S */
template< > struct AllegrexInstructionTemplate< 0xD2A80000, 0xFFF88080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VCMOVF_S"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD2A80000, 0xFFF88080 > AllegrexInstruction_VCMOVF_S;

namespace Allegrex { extern AllegrexInstruction_VCMOVF_S &VCMOVF_S; }

/* VCMOVF_P */
template< > struct AllegrexInstructionTemplate< 0xD2A80080, 0xFFF88080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VCMOVF_P"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD2A80080, 0xFFF88080 > AllegrexInstruction_VCMOVF_P;

namespace Allegrex { extern AllegrexInstruction_VCMOVF_P &VCMOVF_P; }

/* VCMOVF_T */
template< > struct AllegrexInstructionTemplate< 0xD2A88000, 0xFFF88080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VCMOVF_T"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD2A88000, 0xFFF88080 > AllegrexInstruction_VCMOVF_T;

namespace Allegrex { extern AllegrexInstruction_VCMOVF_T &VCMOVF_T; }

/* VCMOVF_Q */
template< > struct AllegrexInstructionTemplate< 0xD2A88080, 0xFFF88080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VCMOVF_Q"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD2A88080, 0xFFF88080 > AllegrexInstruction_VCMOVF_Q;

namespace Allegrex { extern AllegrexInstruction_VCMOVF_Q &VCMOVF_Q; }

/* VWBN_S */
template< > struct AllegrexInstructionTemplate< 0xD3000000, 0xFF008080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VWBN_S"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xD3000000, 0xFF008080 > AllegrexInstruction_VWBN_S;

namespace Allegrex { extern AllegrexInstruction_VWBN_S &VWBN_S; }

/* VPFXS */
template< > struct AllegrexInstructionTemplate< 0xDC000000, 0xFF000000 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VPFXS"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xDC000000, 0xFF000000 > AllegrexInstruction_VPFXS;

namespace Allegrex { extern AllegrexInstruction_VPFXS &VPFXS; }

/* VPFXT */
template< > struct AllegrexInstructionTemplate< 0xDD000000, 0xFF000000 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VPFXT"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xDD000000, 0xFF000000 > AllegrexInstruction_VPFXT;

namespace Allegrex { extern AllegrexInstruction_VPFXT &VPFXT; }

/* VPFXD */
template< > struct AllegrexInstructionTemplate< 0xDE000000, 0xFF000000 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VPFXD"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xDE000000, 0xFF000000 > AllegrexInstruction_VPFXD;

namespace Allegrex { extern AllegrexInstruction_VPFXD &VPFXD; }

/* VIIM */
template< > struct AllegrexInstructionTemplate< 0xDF000000, 0xFF800000 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VIIM"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xDF000000, 0xFF800000 > AllegrexInstruction_VIIM;

namespace Allegrex { extern AllegrexInstruction_VIIM &VIIM; }

/* VFIM */
template< > struct AllegrexInstructionTemplate< 0xDF800000, 0xFF800000 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VFIM"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xDF800000, 0xFF800000 > AllegrexInstruction_VFIM;

namespace Allegrex { extern AllegrexInstruction_VFIM &VFIM; }

/* VMMUL_P */
template< > struct AllegrexInstructionTemplate< 0xF0000080, 0xFF808080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VMMUL_P"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xF0000080, 0xFF808080 > AllegrexInstruction_VMMUL_P;

namespace Allegrex { extern AllegrexInstruction_VMMUL_P &VMMUL_P; }

/* VMMUL_T */
template< > struct AllegrexInstructionTemplate< 0xF0008000, 0xFF808080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VMMUL_T"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xF0008000, 0xFF808080 > AllegrexInstruction_VMMUL_T;

namespace Allegrex { extern AllegrexInstruction_VMMUL_T &VMMUL_T; }

/* VMMUL_Q */
template< > struct AllegrexInstructionTemplate< 0xF0008080, 0xFF808080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VMMUL_Q"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xF0008080, 0xFF808080 > AllegrexInstruction_VMMUL_Q;

namespace Allegrex { extern AllegrexInstruction_VMMUL_Q &VMMUL_Q; }

/* VHTFM2_P */
template< > struct AllegrexInstructionTemplate< 0xF0800000, 0xFF808080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VHTFM2_P"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xF0800000, 0xFF808080 > AllegrexInstruction_VHTFM2_P;

namespace Allegrex { extern AllegrexInstruction_VHTFM2_P &VHTFM2_P; }

/* VTFM2_P */
template< > struct AllegrexInstructionTemplate< 0xF0800080, 0xFF808080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VTFM2_P"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xF0800080, 0xFF808080 > AllegrexInstruction_VTFM2_P;

namespace Allegrex { extern AllegrexInstruction_VTFM2_P &VTFM2_P; }

/* VHTFM3_T */
template< > struct AllegrexInstructionTemplate< 0xF1000080, 0xFF808080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VHTFM3_T"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xF1000080, 0xFF808080 > AllegrexInstruction_VHTFM3_T;

namespace Allegrex { extern AllegrexInstruction_VHTFM3_T &VHTFM3_T; }

/* VTFM3_T */
template< > struct AllegrexInstructionTemplate< 0xF1008000, 0xFF808080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VTFM3_T"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xF1008000, 0xFF808080 > AllegrexInstruction_VTFM3_T;

namespace Allegrex { extern AllegrexInstruction_VTFM3_T &VTFM3_T; }

/* VHTFM4_Q */
template< > struct AllegrexInstructionTemplate< 0xF1808000, 0xFF808080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VHTFM4_Q"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xF1808000, 0xFF808080 > AllegrexInstruction_VHTFM4_Q;

namespace Allegrex { extern AllegrexInstruction_VHTFM4_Q &VHTFM4_Q; }

/* VTFM4_Q */
template< > struct AllegrexInstructionTemplate< 0xF1808080, 0xFF808080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VTFM4_Q"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xF1808080, 0xFF808080 > AllegrexInstruction_VTFM4_Q;

namespace Allegrex { extern AllegrexInstruction_VTFM4_Q &VTFM4_Q; }

/* VMSCL_P */
template< > struct AllegrexInstructionTemplate< 0xF2000080, 0xFF808080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VMSCL_P"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xF2000080, 0xFF808080 > AllegrexInstruction_VMSCL_P;

namespace Allegrex { extern AllegrexInstruction_VMSCL_P &VMSCL_P; }

/* VMSCL_T */
template< > struct AllegrexInstructionTemplate< 0xF2008000, 0xFF808080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VMSCL_T"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xF2008000, 0xFF808080 > AllegrexInstruction_VMSCL_T;

namespace Allegrex { extern AllegrexInstruction_VMSCL_T &VMSCL_T; }

/* VMSCL_Q */
template< > struct AllegrexInstructionTemplate< 0xF2008080, 0xFF808080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VMSCL_Q"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xF2008080, 0xFF808080 > AllegrexInstruction_VMSCL_Q;

namespace Allegrex { extern AllegrexInstruction_VMSCL_Q &VMSCL_Q; }

/* VCRSP_T */
template< > struct AllegrexInstructionTemplate< 0xF2808000, 0xFF808080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VCRSP_T"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xF2808000, 0xFF808080 > AllegrexInstruction_VCRSP_T;

namespace Allegrex { extern AllegrexInstruction_VCRSP_T &VCRSP_T; }

/* VQMUL_Q */
template< > struct AllegrexInstructionTemplate< 0xF2808080, 0xFF808080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VQMUL_Q"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xF2808080, 0xFF808080 > AllegrexInstruction_VQMUL_Q;

namespace Allegrex { extern AllegrexInstruction_VQMUL_Q &VQMUL_Q; }

/* VMMOV_P */
template< > struct AllegrexInstructionTemplate< 0xF3800080, 0xFFFF8080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VMMOV_P"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xF3800080, 0xFFFF8080 > AllegrexInstruction_VMMOV_P;

namespace Allegrex { extern AllegrexInstruction_VMMOV_P &VMMOV_P; }

/* VMMOV_T */
template< > struct AllegrexInstructionTemplate< 0xF3808000, 0xFFFF8080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VMMOV_T"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xF3808000, 0xFFFF8080 > AllegrexInstruction_VMMOV_T;

namespace Allegrex { extern AllegrexInstruction_VMMOV_T &VMMOV_T; }

/* VMMOV_Q */
template< > struct AllegrexInstructionTemplate< 0xF3808080, 0xFFFF8080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VMMOV_Q"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xF3808080, 0xFFFF8080 > AllegrexInstruction_VMMOV_Q;

namespace Allegrex { extern AllegrexInstruction_VMMOV_Q &VMMOV_Q; }

/* VMIDT_P */
template< > struct AllegrexInstructionTemplate< 0xF3830080, 0xFFFF8F80 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VMIDT_P"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xF3830080, 0xFFFF8F80 > AllegrexInstruction_VMIDT_P;

namespace Allegrex { extern AllegrexInstruction_VMIDT_P &VMIDT_P; }

/* VMIDT_T */
template< > struct AllegrexInstructionTemplate< 0xF3838000, 0xFFFF8F80 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VMIDT_T"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xF3838000, 0xFFFF8F80 > AllegrexInstruction_VMIDT_T;

namespace Allegrex { extern AllegrexInstruction_VMIDT_T &VMIDT_T; }

/* VMIDT_Q */
template< > struct AllegrexInstructionTemplate< 0xF3838080, 0xFFFF8F80 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VMIDT_Q"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xF3838080, 0xFFFF8F80 > AllegrexInstruction_VMIDT_Q;

namespace Allegrex { extern AllegrexInstruction_VMIDT_Q &VMIDT_Q; }

/* VMZERO_P */
template< > struct AllegrexInstructionTemplate< 0xF3860080, 0xFFFF8F80 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VMZERO_P"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xF3860080, 0xFFFF8F80 > AllegrexInstruction_VMZERO_P;

namespace Allegrex { extern AllegrexInstruction_VMZERO_P &VMZERO_P; }

/* VMZERO_T */
template< > struct AllegrexInstructionTemplate< 0xF3868000, 0xFFFF8F80 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VMZERO_T"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xF3868000, 0xFFFF8F80 > AllegrexInstruction_VMZERO_T;

namespace Allegrex { extern AllegrexInstruction_VMZERO_T &VMZERO_T; }

/* VMZERO_Q */
template< > struct AllegrexInstructionTemplate< 0xF3868080, 0xFFFF8F80 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VMZERO_Q"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xF3868080, 0xFFFF8F80 > AllegrexInstruction_VMZERO_Q;

namespace Allegrex { extern AllegrexInstruction_VMZERO_Q &VMZERO_Q; }

/* VMONE_P */
template< > struct AllegrexInstructionTemplate< 0xF3870080, 0xFFFF8F80 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VMONE_P"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xF3870080, 0xFFFF8F80 > AllegrexInstruction_VMONE_P;

namespace Allegrex { extern AllegrexInstruction_VMONE_P &VMONE_P; }

/* VMONE_T */
template< > struct AllegrexInstructionTemplate< 0xF3878000, 0xFFFF8F80 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VMONE_T"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xF3878000, 0xFFFF8F80 > AllegrexInstruction_VMONE_T;

namespace Allegrex { extern AllegrexInstruction_VMONE_T &VMONE_T; }

/* VMONE_Q */
template< > struct AllegrexInstructionTemplate< 0xF3878080, 0xFFFF8F80 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VMONE_Q"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xF3878080, 0xFFFF8F80 > AllegrexInstruction_VMONE_Q;

namespace Allegrex { extern AllegrexInstruction_VMONE_Q &VMONE_Q; }

/* VROT_P */
template< > struct AllegrexInstructionTemplate< 0xF3A00080, 0xFFE08080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VROT_P"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xF3A00080, 0xFFE08080 > AllegrexInstruction_VROT_P;

namespace Allegrex { extern AllegrexInstruction_VROT_P &VROT_P; }

/* VROT_T */
template< > struct AllegrexInstructionTemplate< 0xF3A08000, 0xFFE08080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VROT_T"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xF3A08000, 0xFFE08080 > AllegrexInstruction_VROT_T;

namespace Allegrex { extern AllegrexInstruction_VROT_T &VROT_T; }

/* VROT_Q */
template< > struct AllegrexInstructionTemplate< 0xF3A08080, 0xFFE08080 > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VROT_Q"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xF3A08080, 0xFFE08080 > AllegrexInstruction_VROT_Q;

namespace Allegrex { extern AllegrexInstruction_VROT_Q &VROT_Q; }

/* VNOP */
template< > struct AllegrexInstructionTemplate< 0xFFFF0000, 0xFFFFFFFF > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VNOP"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xFFFF0000, 0xFFFFFFFF > AllegrexInstruction_VNOP;

namespace Allegrex { extern AllegrexInstruction_VNOP &VNOP; }

/* VFLUSH */
template< > struct AllegrexInstructionTemplate< 0xFFFF040D, 0xFFFFFFFF > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VFLUSH"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xFFFF040D, 0xFFFFFFFF > AllegrexInstruction_VFLUSH;

namespace Allegrex { extern AllegrexInstruction_VFLUSH &VFLUSH; }

/* VSYNC */
template< > struct AllegrexInstructionTemplate< 0xFFFF0320, 0xFFFFFFFF > : AllegrexInstructionUnknown
{
	static AllegrexInstructionTemplate &Self()
	{
		static AllegrexInstructionTemplate insn;
		return insn;
	}

	static __forceinline char const *FastOpcodeName();
	virtual char const *OpcodeName() { return "VSYNC"; }

	static __forceinline void FastInterpret(AlContext &processor, u32 opcode);
	virtual void Interpret(AlContext &processor, u32 opcode);

	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);
	virtual u64 Infos();

	static insn_count_t count;

	virtual insn_count_t &GetCount() { return count; }

protected:
	AllegrexInstructionTemplate() {}
};

typedef AllegrexInstructionTemplate< 0xFFFF0320, 0xFFFFFFFF > AllegrexInstruction_VSYNC;

namespace Allegrex { extern AllegrexInstruction_VSYNC &VSYNC; }

