#pragma once
#include "Instruction.h"
#include "Instructions.h"

namespace Allegrex {

Instruction* instruction(u32 opcode) {
    switch ((opcode >> 26) & 0x0000003f) {
        case 0: /* SPECIAL */
            switch ((opcode >> 0) & 0x0000003f) {
                case 0: /*SPECIAL*/
                    if ((opcode & 0x001fffc0) == 0x00000000) {
                        return &NOP::Self();//NOP
                    }
                    return &SLL::Self();//SLL
                case 2:
                    if ((opcode & 0x00200000) == 0x00000000) {
                        return &SRL::Self();//SRL
                    }
                    return &InstructionUnknown::Self();
                case 12:
                    return &SYSCALL::Self();//SYSCALL
                case 13:
                    return &BREAK::Self();//BREAK;
                case 16:
                    return &MFHI::Self();//MFHI
                case 18:
                    return &MFLO::Self();//MFLO
                case 27:
                    return &DIVU::Self();  // DIVU
                case 32:
                    return &ADD::Self();  //ADD
                case 33:
                    return &ADDU::Self();  //ADDU
                case 36:
                    return &AND::Self();//AND
                case 38:
                    return &XOR::Self();//XOR
                case 43:
                    return &SLTU::Self();  // SLTU
                default:
                    return &InstructionUnknown::Self();
            }
            break;
        case 1: /* REGIMM */
            switch ((opcode >> 16) & 0x00000003) {
                case 1:
                    if ((opcode & 0x00100000) == 0x00000000) {
                        return &BGEZ::Self();//BGEZ
                    }
                    return &InstructionUnknown::Self();
                default:
                    return &InstructionUnknown::Self();
            }
            break;
        case 2:
            return &J::Self();  // J
        case 5:
            return &BNE::Self();//BNE
        case 7:
            return &BGTZ::Self();//BGTZ
        case 9:
            return &ADDIU::Self();//ADDIU
        case 11:
            return &SLTIU::Self();//SLTIU
        case 13:
            return &ORI::Self();//ORI
        case 15:
            return &LUI::Self();//LUI
        case 21:
            return &BNEL::Self();//BNEL
        case 23:
            return &BGTZL::Self();//BGTZL
        case 35:
            return &LW::Self();//LW
        case 36:
            return &LBU::Self();//LBU
        case 40:
            return &SB::Self();//SB
        case 43:
            return &SW::Self();//SW
        default:
            return &InstructionUnknown::Self();
    }
}

}
