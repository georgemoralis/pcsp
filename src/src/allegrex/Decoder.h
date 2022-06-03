#pragma once
#include "Instruction.h"

namespace Allegrex {

    Instruction* table_0[] = 
    {
        &InstructionUnknown::Self(), &InstructionUnknown::Self(),&InstructionUnknown::Self(),&InstructionUnknown::Self(), 
        &InstructionUnknown::Self(), &InstructionUnknown::Self(),&InstructionUnknown::Self(),&InstructionUnknown::Self(), 
        &InstructionUnknown::Self(), 
        &InstructionADDIU::Self(), //ADDIU
        &InstructionUnknown::Self(),
        &InstructionUnknown::Self(),
        &InstructionUnknown::Self(), 
        &InstructionORI::Self(),  //ORI
        &InstructionUnknown::Self(), 
        &InstructionLUI::Self(),  //LUI
        &InstructionUnknown::Self(), &InstructionUnknown::Self(), &InstructionUnknown::Self(), &InstructionUnknown::Self(), 
        &InstructionUnknown::Self(), &InstructionUnknown::Self(), &InstructionUnknown::Self(), &InstructionUnknown::Self(),
        &InstructionUnknown::Self(), &InstructionUnknown::Self(), &InstructionUnknown::Self(), &InstructionUnknown::Self(),
        &InstructionUnknown::Self(), &InstructionUnknown::Self(), &InstructionUnknown::Self(), &InstructionUnknown::Self(),
        &InstructionUnknown::Self(), &InstructionUnknown::Self(), &InstructionUnknown::Self(), &InstructionUnknown::Self(),
        &InstructionLBU::Self(), //LBU
        &InstructionUnknown::Self(), &InstructionUnknown::Self(), &InstructionUnknown::Self(),
        &InstructionUnknown::Self(), &InstructionUnknown::Self(), &InstructionUnknown::Self(), &InstructionUnknown::Self(),
        &InstructionUnknown::Self(), &InstructionUnknown::Self(), &InstructionUnknown::Self(), &InstructionUnknown::Self(),
        &InstructionUnknown::Self(), &InstructionUnknown::Self(), &InstructionUnknown::Self(), &InstructionUnknown::Self(),
        &InstructionUnknown::Self(), &InstructionUnknown::Self(), &InstructionUnknown::Self(), &InstructionUnknown::Self(),
        &InstructionUnknown::Self(), &InstructionUnknown::Self(), &InstructionUnknown::Self(), &InstructionUnknown::Self(),
        &InstructionUnknown::Self(), &InstructionUnknown::Self(), &InstructionUnknown::Self(), &InstructionUnknown::Self()
    };

    static Instruction* instruction(int insn) 
    { 
        return table_0[(insn >> 26) & 0x0000003f];
    }
}
