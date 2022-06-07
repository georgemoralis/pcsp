#pragma once
#include "Instruction.h"
#include "Instructions.h"

namespace Allegrex {

Instruction* instruction(u32 opcode) {
    switch ((opcode >> 26) & 0x0000003f) {
        case 0: /* SPECIAL */
            switch ((opcode >> 0) & 0x0000003f) {
                case 33:
                    return &ADDU::Self();  // ADDIU
                default:
                    return &InstructionUnknown::Self();
            }
            break;
        case 9:
            return &ADDIU::Self();// ADDIU
        case 13:
            return &ORI::Self();// ORI
        case 15:
            return &LUI::Self();//LUI
        case 36:
            return &LBU::Self();// LBU
        default:
            return &InstructionUnknown::Self();
    }
}

}
