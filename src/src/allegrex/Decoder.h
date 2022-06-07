#pragma once
#include "Instruction.h"

namespace Allegrex {

Instruction* instruction(u32 opcode) {
    switch ((opcode >> 26) & 0x0000003f) {
        case 0: /* SPECIAL */
            switch ((opcode >> 0) & 0x0000003f) {
                case 33:
                    return &InstructionADDU::Self();  // ADDIU
                default:
                    return &InstructionUnknown::Self();
            }
            break;
        case 9:
            return &InstructionADDIU::Self();// ADDIU
        case 13:
            return &InstructionORI::Self();// ORI
        case 15:
            return &InstructionLUI::Self();//LUI
        case 36:
            return &InstructionLBU::Self();// LBU
        default:
            return &InstructionUnknown::Self();
    }
}

}
