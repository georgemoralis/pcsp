#include "stdafx.h"
#include "al.h"

#if 0

void generate_allegrex() {}

#else

#define IDEF(a0, a1, a2, a3, a4) { #a0, a1, a2, a3, a4 },

using namespace Allegrex;

struct { char const *name; char const *fmt; unsigned mask; unsigned signature; unsigned long long infos; } al_table[] =
{
#include "al.def"
	{
		0, 0, 0, 0, 0
	}
};

template< u64 infos, u32 signature, u32 mask >
static inline void output_operands(u32 opcode, char *operands)
{
	using namespace Allegrex;

	if (!operands) return;

	if ((signature != 0x00000000) || opcode)
	{
		switch (infos & IS_VFPU)
		{
		case IS_VFPU0:
			{
			}
			break;
		case IS_VFPU1:
			{
			}
			break;
		case IS_VFPU2:
			{
			}
			break;
		case IS_VFPU3:
			{
			}
			break;
		case IS_VFPU4:
			{
			}
			break;
		case IS_VFPU5:
			{
			}
			break;
		case IS_VFPU6:
			{
			}
			break;
		case IS_VFPU7:
			{
			}
			break;
			
		//case -1: ::sprintf(operands, "<%d>(vd(opcode), vs(opcode))", vsize(opcode)); // VABS
		//case -2: ::sprintf(operands, "<%d>(vd(opcode), vs(opcode), vt(opcode))", vsize(opcode)); // VADD,VSUB,VMUL,VDIV,...
		//case -3: ::sprintf(operands, "<%d>((opcode>>16)&7, vd(opcode), vs(opcode))", vsize(opcode)); // VCMOVx
		//case -4: ::sprintf(operands, "<%d>(vs(opcode), vt(opcode), (opcode>>0)&15)", vsize(opcode)); // VCMP
		//case -5: ::sprintf(operands, "<%d>(vd(opcode), vs(opcode), (opcode>>16)&31)", vsize(opcode)); // VI2F, VF2I
		//case -6: ::sprintf(operands, "(vt(opcode), uimm16(opcode))"); // VIIM, VFIM
		//case -7: ::sprintf(operands, "<%d>(vd(opcode), vs(opcode), (opcode>>16)&31)", vsize(opcode)); // VI2F, VF2I
		}
	}

	::strcpy(operands, "");
        //::strcpy(comment, "");
}


void generate_allegrex()
{

	FILE *out = 0;
	
#if 1
	out = ::fopen("..\\..\\src\\al\\instructions2.h", "w");

	if (out)
	{
		for (int i = 0; al_table[i].name; ++i)
		{
			::fprintf(out,
				"/* %s */\n"
				"template< > struct AllegrexInstructionTemplate< 0x%08X, 0x%08X > : AllegrexInstructionUnknown\n"
				"{\n"
				"	static AllegrexInstructionTemplate &Self()\n"
				"	{\n"
				"		static AllegrexInstructionTemplate insn;\n"	
				"		return insn;\n"
				"	}\n"
				"\n"
				"	static __forceinline char const *FastOpcodeName();\n"
				"	virtual char const *OpcodeName() { return \"%s\"; }\n"
				"\n"
				"	static __forceinline void FastInterpret(AlProcessor &processor, u32 opcode);\n"
				"	virtual void Interpret(AlProcessor &processor, u32 opcode);\n"
				"\n"
				"	virtual void Disassemble(u32 address, u32 opcode, char *opcode_name, char *operands, char *comment);"
				"\n"
				"	virtual u64 Infos();\n"
				"\n"
				"	static insn_count_t count;\n"
				"\n"
				"	virtual insn_count_t &GetCount() { return count; }\n"
				"\n"
				"protected:\n"
				"	AllegrexInstructionTemplate() {}\n"
				"};\n"
				"\n"
				"typedef AllegrexInstructionTemplate< 0x%08X, 0x%08X > AllegrexInstruction_%s;\n"
				"\n"
				"namespace Allegrex { extern AllegrexInstruction_%s &%s; }\n"
				"\n",
				al_table[i].name,
				al_table[i].signature,
				al_table[i].mask,
				al_table[i].name,
				al_table[i].signature,
				al_table[i].mask,
				al_table[i].name,
				al_table[i].name,
				al_table[i].name);
		}

		::fclose(out);

		out = 0;
	}
#endif

#if 0
	out = ::fopen("..\\Emulator\\GraphicsEngine\\commands.cpp", "w");

	if (out)
	{
		::fprintf(out,
			"#include \"StdAfx.h\"\n"
			"#include \"command.h\"\n"
			"\n"
			"namespace GraphicsEngine\n"
			"{\n");

		for (int i = 0; cmd[i].name; ++i)
		{
			::fprintf(out,
				"	/* %s */\n"
				"	GeCommand_%s &%s = GeCommandTemplate< 0x%08X, 0x%08X >::self();\n"
				"\n", cmd[i].name, cmd[i].name, cmd[i].name, cmd[i].signature, cmd[i].mask);
		}

		::fprintf(out,
			"}\n");

		::fclose(out);

		out = 0;
	}
#endif

#if 0
	out = ::fopen("..\\Emulator\\GraphicsEngine\\disassembler.cpp", "w");

	if (out)
	{
		::fprintf(out,
			"#include \"StdAfx.h\"\n"
			"#include \"command.h\"\n"
			"#include <string.h>\n"
			"\n");

		for (int i = 0; cmd[i].name; ++i)
		{
			::fprintf(out,
				"/* %s */\n"
				"template< >\n"
				"void GeCommandTemplate< 0x%08X, 0x%08X >::disassemble(u32 address, u32 command, char *opcode_name, char *operands, char *comment)\n"
				"{\n"
				"	using namespace GraphicsEngine;\n"
				"	::strcpy(opcode_name, \"%s\");\n"			
				"	::strcpy(operands, \"\");\n"
				"	::strcpy(comment, \"\");\n"
				"}\n"
				"\n", cmd[i].name, cmd[i].signature, cmd[i].mask, cmd[i].name);
		}

		::fclose(out);

		out = 0;
	}
#endif

#if 0
	out = ::fopen("..\\src\\Emulator\\GraphicsEngine\\interpreter.h", "w");

	if (out)
	{
		for (int i = 0; cmd[i].name; ++i)
		{
			::fprintf(out,
				"/* %s */\n"
				"__forceinline void GeCommandTemplate< 0x%08X, 0x%08X >::FastInterpret(GeProcessor &ge, u32 command)\n"
				"{\n"
				"	using namespace GraphicsEngine;\n"
				"	// ge.do%s();\n"
				"}\n"
				"\n", cmd[i].name, cmd[i].signature, cmd[i].mask, cmd[i].name);
		}

		::fclose(out);

		out = 0;
	}
#endif


#if 0
	out = ::fopen("..\\Emulator\\GraphicsEngine\\analyzer.cpp", "w");

	if (out)
	{
		::fprintf(out,
			"#include \"StdAfx.h\"\n"
			"#include \"command.h\"\n"
			"\n");

		for (int i = 0; cmd[i].name; ++i)
		{
			::fprintf(out,
				"/* %s */\n"
				"template< > u32 GeCommandTemplate< 0x%08X, 0x%08X >::Infos()\n"
				"{\n"
				"	return 0;\n"
				"}\n"
				"\n", cmd[i].name, cmd[i].signature, cmd[i].mask);
		}

		::fclose(out);
	}
#endif

}
#endif
