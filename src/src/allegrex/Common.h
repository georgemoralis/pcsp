#pragma once
#include "..\PCSPCommon.h"

namespace Allegrex {

        char const* gprNames[32] = {"$zr", "$at", "$v0", "$v1", "$a0", "$a1", "$a2", "$a3", "$t0", "$t1", "$t2",
                            "$t3", "$t4", "$t5", "$t6", "$t7", "$s0", "$s1", "$s2", "$s3", "$s4", "$s5",
                            "$s6", "$s7", "$t8", "$t9", "$k0", "$k1", "$gp", "$sp", "$fp", "$ra"};

    static std::string disasmRTRSIMM(std::string opname, int rt, int rs, int imm16) {
        char tmp[128];
        sprintf(tmp, "%-10s %2s, %3s, %4d", opname.c_str(), gprNames[rt], gprNames[rs], ((int)(short)imm16));
        if (rs == 0) {
            char tmp2[128];
            if (opname.compare("andi") == 0) {
                sprintf(tmp2, "%2s <=> li %1s, 0", tmp,gprNames[rt]);
                return std::string(tmp2);
            } else if (opname.compare("slti")==0) {
                sprintf(tmp2, "%3s <=> li %1s, %2d", tmp,gprNames[rt], ((0 < imm16) ? 1 : 0));
                return std::string(tmp2);
            } else if (opname.compare("addiu")==0 || opname.compare("ori")==0) {               
                sprintf(tmp2, "%3s <=> li %1s, %2d", tmp,gprNames[rt], imm16);
                return std::string(tmp2);
            }
        }
        return std::string(tmp);
    }
    static std::string disasmRTIMM(std::string opname, int rt, int imm) {
        char tmp[128];
        sprintf(tmp, "%-10s %2s, 0x%04X <=> li %2s, 0x%04X0000", opname.c_str(), gprNames[rt], (imm & 0xFFFF),
            gprNames[rt], (imm & 0xFFFF));
        return std::string(tmp);
    }
}
