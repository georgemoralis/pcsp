#ifndef EMULATOR_ALCONTEXT_H_
#define EMULATOR_ALCONTEXT_H_

#include "memory/memory.h"
#include "log.h"

struct AlContext
{
#include "al_gpr.h"
#include "al_fpr.h"
#include "al_vpr.h"
#include "al_vcr.h"
#include "al_mdr.h"
#include "al_fcr.h"
#include "al_bcr.h"

#include "al_cpu.h"
#include "al_fpu.h"
#include "al_vpu.h"
#include "al_mdu.h"
#include "al_lsu.h"
#include "al_bcu.h"

    typedef u32 (*AlContext::execute_t)();

    u32 execute();

    static bool llbit;

    AlContext();

    void Reset();

    void doUNK(char const *reason) { warnf(interpreter, reason); }

    void Interpret();

    void InterpretDebug();

    bool Dispatch();

    void InterpretDelayslot();

    void Syscall(u32 opcode);
};

enum AllegrexGpr
{
    ALLEGREX_ZR	= 0,                 
    ALLEGREX_AT = 1,                 
    ALLEGREX_V0 = 2,                 
    ALLEGREX_V1 = 3,                 
    ALLEGREX_A0 = 4,                 
    ALLEGREX_A1 = 5,                 
    ALLEGREX_A2 = 6,                 
    ALLEGREX_A3 = 7,                 
    ALLEGREX_T0 = 8,  ALLEGREX_A4 = ALLEGREX_T0,
    ALLEGREX_T1 = 9,  ALLEGREX_A5 = ALLEGREX_T1,
    ALLEGREX_T2 = 10, ALLEGREX_A6 = ALLEGREX_T2,
    ALLEGREX_T3 = 11, ALLEGREX_A7 = ALLEGREX_T3,
    ALLEGREX_T4 = 12,                 
    ALLEGREX_T5 = 13,                 
    ALLEGREX_T6 = 14,                 
    ALLEGREX_T7 = 15,                 
    ALLEGREX_S0 = 16,
    ALLEGREX_S1 = 17,
    ALLEGREX_S2 = 18,
    ALLEGREX_S3 = 19,
    ALLEGREX_S4 = 20,
    ALLEGREX_S5 = 21,
    ALLEGREX_S6 = 22,
    ALLEGREX_S7 = 23,
    ALLEGREX_T8 = 24,
    ALLEGREX_T9 = 25,
    ALLEGREX_K0 = 26,
    ALLEGREX_K1 = 27,
    ALLEGREX_GP = 28,
    ALLEGREX_SP = 29,
    ALLEGREX_FP = 30, ALLEGREX_S8 = ALLEGREX_FP,
    ALLEGREX_RA = 31
};

enum AllegrexFpr
{
    ALLEGREX_F0	 =  0,                 
    ALLEGREX_F1  =  1,                 
    ALLEGREX_F2  =  2,                 
    ALLEGREX_F3	 =  3,                 
    ALLEGREX_F4  =  4,                 
    ALLEGREX_F5  =  5,                 
    ALLEGREX_F6	 =  6,                 
    ALLEGREX_F7  =  7,                 
    ALLEGREX_F8  =  8,                 
    ALLEGREX_F9	 =  9,                 
    ALLEGREX_F10 = 10,                 
    ALLEGREX_F11 = 11,                 
    ALLEGREX_F12 = 12,                 
    ALLEGREX_F13 = 13,                 
    ALLEGREX_F14 = 14,                 
    ALLEGREX_F15 = 15,                 
    ALLEGREX_F16 = 16,                 
    ALLEGREX_F17 = 17,                 
    ALLEGREX_F18 = 18,                 
    ALLEGREX_F19 = 19,                 
    ALLEGREX_F20 = 20,                 
    ALLEGREX_F21 = 21,                 
    ALLEGREX_F22 = 22,                 
    ALLEGREX_F23 = 23,                 
    ALLEGREX_F24 = 24,                 
    ALLEGREX_F25 = 25,                 
    ALLEGREX_F26 = 26,                 
    ALLEGREX_F27 = 27,                 
    ALLEGREX_F28 = 28,                 
    ALLEGREX_F29 = 29,                 
    ALLEGREX_F30 = 30,                 
    ALLEGREX_F31 = 31
};

#endif /* EMULATOR_ALCONTEXT_H_ */
