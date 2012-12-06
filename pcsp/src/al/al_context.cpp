#include "stdafx.h"
#define BUILD_AL_PROCESSOR


#include "memory/memory.h"
#include "emulator.h"
#include "al.h"

bool AlContext::llbit = false;

AlContext::AlContext()
{
    Reset();
}

#if 1
void AlContext::Interpret()
{
    if (!Dispatch())
    {
        u32 opcode = FetchOpcode();
        Allegrex::FastInterpret(*this, opcode);
    }
}

void AlContext::InterpretDelayslot()
{
    u32 opcode = FetchDelayslotOpcode();

    Allegrex::FastInterpret(*this, opcode);

    NextPC();
}
#else
void AlContext::Interpret()
{
    static char line[4096];

    if (!Dispatch())
    {
        u32 address = pc;
        u32 opcode = FetchOpcode();
        Allegrex::Disassemble(address, opcode, line);
        tracef(interpreter, "%08X --- %s", address, line);
        Allegrex::FastInterpret(*this, opcode);
    }
}

void AlContext::InterpretDelayslot()
{
    static char line[4096];

    u32 address = pc;
	u32 opcode = FetchDelayslotOpcode();
    Allegrex::Disassemble(address, opcode, line);
    tracef(interpreter, "%08X -*- %s", address, line);
	Allegrex::FastInterpret(*this, opcode);

	NextPC();
}
#endif


void AlContext::Reset()
{
    reset_gpr();
    reset_fpr();
    reset_vpr();
    reset_mdr();
    reset_fcr();
    reset_vcr();
    reset_bcr();
}

#ifndef BUILDING_SPECIFIC_GAME_EMULATOR
bool AlContext::Dispatch()
{
    return false;
}

#endif
