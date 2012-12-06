#include "stdafx.h"

#if 0
#include "memory/memory.h"
#include "emulator.h"
#include "al.h"
#include "al_emitter.h"

AlContext *al_Emitter::context = 0;
u8        *al_Emitter::pointer = 0;
u8         al_Emitter::delayslot_stack[4];
u32        al_Emitter::delayslot = 0;

class al_Recompiler : public al_Emitter
{
    struct Gpr
    {
        Gpr() {}

        __forceinline M32 operator [](int const reg) const { return M32(-1, EBP, 0, int(((AlContext*)0)->gpr + reg)); }
    };

    struct Fpr
    {
        Fpr() {}

        __forceinline M32 operator [](int const reg) const { return M32(-1, EBP, 0, int(((AlContext*)0)->fpr + reg)); }
    };

    struct Fcr
    {
        Fcr() {}

        __forceinline M32 operator [](int const reg) const { return M32(-1, EBP, 0, int(((u32 *)(reg == 0 ? &(((AlContext*)0)->fcr0) : &(((AlContext*)0)->fcr31))))); }
    };

    struct Mdr
    {
        Mdr() {}

        __forceinline M32 operator [](int const reg) const { return M32(-1, EBP, 0, int(((u32 *)(&((AlContext*)0)->hilo)) + reg)); }
    };

    struct Pc
    {
        Pc() {}

        __forceinline operator M32 () const { return M32(-1, EBP, 0, int(((u32 *)(&((AlContext*)0)->pc)))); }
    };

public:
    al_Recompiler() {}
    al_Recompiler(u8 *pointer) { al_Emitter::pointer = pointer; }

    /// CPU ///

    template< int op >
    __forceinline void doSHIFT(u32 rd, u32 rt, u32 sa)
    {
        R32 eax(EAX);
        Gpr gpr;
        Mov mov;
        Rsu rsu(op);

        if (rd)
        {
            if (rt)
            {
                if (rd == rt)
                {
                    rsu     (gpr[rd], sa     );
                }
                else
                {
                    mov     (eax,     gpr[rt]);
                    rsu     (eax,     sa     );
                    mov     (gpr[rd], eax    );
                }
            }
            else
            {
                mov         (gpr[rd], 0);
            }
        }
    }

    __forceinline void doSLL(u32 rd, u32 rt, u32 sa)
    {
        doSHIFT< SHL >(rd, rt, sa);
    }

    __forceinline void doSRL(u32 rd, u32 rt, u32 sa)
    {
        doSHIFT< SHR >(rd, rt, sa);
    }

    __forceinline void doSRA(u32 rd, u32 rt, u32 sa)
    {
        doSHIFT< SAR >(rd, rt, sa);
    }

    template< int op >
    __forceinline void doSHIFTV(u32 rd, u32 rt, u32 rs)
    {
        R32 eax(EAX);
        R32 ecx(ECX);
        Gpr gpr;
        Mov mov;
        Rsu rsu(op); // ecx is shift amount

        if (rs & 31)
        {
            if (rd)
            {
                if (rt)
                {
                    if (rd == rt)
                    {
                        mov     (ecx,     gpr[rs]);
                        rsu     (gpr[rd]         );
                    }
                    else
                    {
                        mov     (ecx,     gpr[rs]);
                        mov     (eax,     gpr[rt]);
                        rsu     (eax             );
                        mov     (gpr[rd], eax    );
                    }
                }
                else
                {
                    mov         (gpr[rd], 0);
                }
            }
        }
    }

    __forceinline void doSLLV(u32 rd, u32 rt, u32 rs)
    {
        doSHIFTV< SHL >(rd, rt, rs);
    }

    __forceinline void doSRLV(u32 rd, u32 rt, u32 rs)
    {
        doSHIFTV< SHR >(rd, rt, rs);
    }

    __forceinline void doSRAV(u32 rd, u32 rt, u32 rs)
    {
        doSHIFTV< SAR >(rd, rt, rs);
    }

    __forceinline void doADDU(u32 rd, u32 rs, u32 rt)
    {
        R32 eax(EAX);
        Gpr gpr;
        Add add;
        Sal sal;
        Mov mov;

        if (rd)
        {
            if (rs == rt) // ADDU rd, rs|0, rs|0
            {
                if (rd == rs) // ADDU rd, rd, rd -> rd = 2*rd
                {
                    sal         (gpr[rd], 1);
                }
                else if (rs) // ADDU rd, rs, rs -> rd = 2*rs
                {
                    mov         (eax,     gpr[rs]);
                    sal         (eax,     1      );
                    mov         (gpr[rd], eax    );
                }
                else // ADDU rd, 0, 0 -> rd = 0
                {
                    mov         (gpr[rd], 0);
                }
            }
            else
            {
                if (rt && rs) // ADDU rd, rs, rt
                {
                    mov         (eax,     gpr[rs]);
                    add         (eax,     gpr[rt]);
                    mov         (gpr[rd], eax    );
                }
                else // ADDU rd, rs|0, 0|rt
                {
                    mov         (eax,     gpr[rt ? rt : rs]);
                    mov         (gpr[rd], eax              );
                }
            }
        }
    }

    __forceinline void doSUBU(u32 rd, u32 rs, u32 rt)
    {
        R32 eax(EAX);
        Gpr gpr;
        Sub sub;
        Neg neg;
        Mov mov;

        if (rd)
        {
            if (rs == rt) // SUBU rd, rs|0, rs|0
            {
                mov             (gpr[rd], 0);
            }
            else
            {
                if (rt && rs) // SUBU rd, rs, rt
                {
                    mov         (eax,     gpr[rs]);
                    sub         (eax,     gpr[rt]);
                    mov         (gpr[rd], eax    );
                }
                else if (rs) // SUBU rd, rs|0, 0|rt
                {
                    mov         (eax,     gpr[rs]);
                    mov         (gpr[rd], eax    );
                }
                else
                {
                    mov         (eax,     gpr[rt]);
                    neg         (eax             );
                    mov         (gpr[rd], eax    );
                }
            }
        }
    }

    __forceinline void doAND(u32 rd, u32 rs, u32 rt)
    {
        R32 eax(EAX);
        Gpr gpr;
        And and;
        Mov mov;

        if (rd)
        {
            if (rs == rt) // AND rd, rs|0, rs|0
            {
                if (rd != rs)
                {
                    if (rs) // AND rd, rs, rs -> rd = rs
                    {
                                mov (eax,     gpr[rs]);
                                mov (gpr[rd], eax    );
                    }
                    else // AND rd, 0, 0 -> rd = 0
                    {
                                mov (gpr[rd], 0);
                    }
                }
                else // AND rd, rd, rd -> rd = rd
                {
                }
            }
            else
            {
                if (rt && rs) // AND rd, rs, rt
                {
                    mov         (eax,     gpr[rs]);
                    and         (eax,     gpr[rt]);
                    mov         (gpr[rd], eax    );
                }
                else // AND rd, rs|0, 0|rt
                {
                    mov         (gpr[rd], 0);
                }
            }
        }
    }

    __forceinline void doOR(u32 rd, u32 rs, u32 rt)
    {
        R32 eax(EAX);
        Gpr gpr;
        Or  or;
        Mov mov;

        if (rd)
        {
            if (rs == rt) // OR rd, rs|0, rs|0
            {
                if (rd != rs)
                {
                    if (rs) // OR rd, rs, rs -> rd = rs
                    {
                        mov     (eax,     gpr[rs]);
                        mov     (gpr[rd], eax    );
                    }
                    else // OR rd, 0, 0 -> rd = 0
                    {
                        mov     (gpr[rd], 0);
                    }
                }
                else // OR rd, rd, rd -> rd = rd
                {
                }
            }
            else
            {
                if (rt && rs) // OR rd, rs, rt
                {
                    mov         (eax,     gpr[rs]);
                    or          (eax,     gpr[rt]);
                    mov         (gpr[rd], eax    );
                }
                else // OR rd, rs|0, 0|rt
                {
                    mov         (eax,     gpr[rt ? rt : rs]);
                    mov         (gpr[rd], eax              );
                }
            }
        }
    }

    __forceinline void doXOR(u32 rd, u32 rs, u32 rt)
    {
        R32 eax(EAX);
        Gpr gpr;
        Xor xor;
        Mov mov;

        if (rd)
        {
            if (rs == rt) // XOR rd, rs|0, rs|0
            {
                mov             (gpr[rd], 0);
            }
            else
            {
                if (rt && rs) // XOR rd, rs, rt
                {
                    mov         (eax,     gpr[rs]);
                    xor         (eax,     gpr[rt]);
                    mov         (gpr[rd], eax    );
                }
                else // XOR rd, rs|0, 0|rt
                {
                    mov         (eax,     gpr[rt ? rt : rs]);
                    mov         (gpr[rd], eax              );
                }
            }
        }
    }

    __forceinline void doNOR(u32 rd, u32 rs, u32 rt)
    {
        R32 eax(EAX);
        Gpr gpr;
        Or  or;
        Not not;
        Mov mov;

        if (rd)
        {
            if (rt == rs) // NOR rd, rs|0, rs|0
            {
                if (rd == rs) // NOR rd, rd, rd -> rd = ~rd
                {
                    not         (gpr[rd]);
                }
                else if (rs) // NOR rd, rs, rs -> rd = ~rs
                {
                    mov         (eax,     gpr[rs]);
                    not         (eax             );
                    mov         (gpr[rd], eax    );
                }
                else // NOR rd, 0, 0 -> rd = ~0
                {
                    mov         (gpr[rd], -1);
                }
            }
            else
            {
                if (rt && rs) // NOR rd, rs, rt
                {
                    mov         (eax,     gpr[rs]);
                    or          (eax,     gpr[rt]);
                    not         (eax             );
                    mov         (gpr[rd], eax    );
                }
                else // NOR rd, rs|0, 0|rt
                {
                    mov         (eax,     gpr[rt ? rt : rs]);
                    not         (eax                       );
                    mov         (gpr[rd], eax              );
                }
            }
        }
    }

    template< int cc >
    __forceinline void doScc(u32 rd, u32 rs, u32 rt)
    {
        R32   eax(EAX);
        Gpr   gpr;
        Cmp   cmp;
        And   and;
        Xor   xor;
        SetXX setcc(cc);
        Mov   mov;

        if (rd)
        {
            if (rt == rs) // SLT rd, rs|0, rs|0
            {
                mov             (gpr[rd], 0);
            }
            else
            {
                if (rt && rs) // SLT rd, rs, rt
                {
                    mov         (eax,     gpr[rs]);
                    cmp         (eax,     gpr[rt]);
                    setcc       (R8(eax)         );
                    and         (eax,     1      );
                    mov         (gpr[rd], eax    );
                }
                else if (rs) // SLT rd, rs, 0
                {
                    mov         (eax,     gpr[rs]);
                    cmp         (eax,     0      );
                    setcc       (R8(eax)         );
                    and         (eax,     1      );
                    mov         (gpr[rd], eax    );
                }
                else if (rs) // SLT rd, 0, rt
                {
                    xor         (eax,     eax    );
                    cmp         (eax,     gpr[rt]);
                    setcc       (R8(eax)         );
                    and         (eax,           1);
                    mov         (gpr[rd], eax    );
                }
            }
        }
    }

    __forceinline void doSLT(u32 rd, u32 rs, u32 rt)
    {
        doScc< L >(rd, rs, rt);
    }

    __forceinline void doSLTU(u32 rd, u32 rs, u32 rt)
    {
        doScc< B >(rd, rs, rt);
    }

    __forceinline void doADDIU(u32 rt, u32 rs, s32 simm16)
    {
        R32 eax(EAX);
        Gpr gpr;
        Add add;
        Sal sal;
        Mov mov;

        if (rt)
        {
            if (rs) // ADDIU rt, rs, simm16
            {
                if (rt == rs) // ADDIU rt, rt, simm16 -> rt += simm16
                {
                    if (simm16)
                    {
                        add     (gpr[rt], simm16);
                    }
                }
                else // ADDIU rt, rs, simm16 -> rt = rs + simm16
                {
                    mov         (eax, gpr[rs]);
                    if (simm16)
                    {
                        add     (eax, simm16);
                    }
                    mov         (gpr[rt], eax);
                }
            }
            else // ADDIU rt, 0, simm16 -> rt = simm16
            {
                mov             (gpr[rt], simm16);
            }
        }
    }

    template< int cc >
    __forceinline void doScc(u32 rt, u32 rs, s32 simm16)
    {
        R32   eax(EAX);
        Gpr   gpr;
        Cmp   cmp;
        And   and;
        SetXX setcc(cc);
        Mov   mov;

        if (rt)
        {
            if (rs) // SLTI(U) rd, rs, simm16
            {
                mov     (eax,     gpr[rs]);
                cmp     (eax,     simm16 );
                setcc   (R8(eax)         );
                and     (eax,     1      );
                mov     (gpr[rt], eax    );
            }
            else if (cc == L) // SLTI rd, 0, simm16
            {
                mov     (gpr[rt], int(s32(0) < s32(simm16)));
            }
            else if (cc == B) // SLTIU rd, 0, simm16
            {
                mov     (gpr[rt], int(u32(0) < u32(simm16)));
            }
        }
    }

    __forceinline void doSLTI(u32 rt, u32 rs, s32 simm16)
    {
        doScc< L >(rt, rs, simm16);
    }

    __forceinline void doSLTIU(u32 rt, u32 rs, s32 simm16)
    {
        doScc< B >(rt, rs, simm16);
    }

    __forceinline void doANDI(u32 rt, u32 rs, u32 uimm16)
    {
        R32 eax(EAX);
        Gpr gpr;
        And and;
        Mov mov;

        if (rt)
        {
            if (rs) // ANDI rt, rs, uimm16
            {
                if (rt == rs) // ANDI rt, rt, uimm16 -> rt &= uimm16
                {
                    if (uimm16)
                    {
                        and     (gpr[rt], uimm16);
                    }
                    else // ANDI rt, rt, 0 -> rt = 0
                    {
                        mov     (gpr[rt], 0);
                    }
                }
                else // ANDI rt, rs, uimm16 -> rt = rs & uimm16
                {
                    if (uimm16)
                    {
                        mov     (eax, gpr[rs]);
                        and     (eax, uimm16);
                        mov     (gpr[rt], eax);
                    }
                    else  // ANDI rt, rs, 0 -> rt = 0
                    {
                        mov     (gpr[rt], 0);
                    }
                }
            }
            else // ANDI rt, 0, uimm16 -> rt = 0
            {
                mov             (gpr[rt], 0);
            }
        }
    }

    __forceinline void doORI(u32 rt, u32 rs, u32 uimm16)
    {
        R32 eax(EAX);
        Gpr gpr;
        Or  or;
        Mov mov;

        if (rt)
        {
            if (rs) // ORI rt, rs, uimm16
            {
                if (rt == rs) // ORI rt, rt, uimm16 -> rt |= uimm16
                {
                    if (uimm16)
                    {
                        or      (gpr[rt], uimm16);
                    }
                    else // ORI rt, rt, 0 -> rt = rt
                    {
                    }
                }
                else // ORI rt, rs, uimm16 -> rt = rs & uimm16
                {
                    mov         (eax, gpr[rs]);
                    if (uimm16)
                    {
                        or      (eax, uimm16);
                    }
                    mov         (gpr[rt], eax);
                }
            }
            else // ORI rt, 0, uimm16 -> rt = uimm16
            {
                mov             (gpr[rt], uimm16);
            }
        }
    }

    __forceinline void doXORI(u32 rt, u32 rs, u32 uimm16)
    {
        R32 eax(EAX);
        Gpr gpr;
        Xor xor;
        Not not;
        Mov mov;

        if (rt)
        {
            if (rs) // XORI rt, rs, uimm16
            {
                if (rt == rs) // XORI rt, rt, uimm16 -> rt ^= uimm16
                {
                    if (uimm16)
                    {
                        xor     (gpr[rt], uimm16);
                    }
                    else // XORI rt, rt, 0 -> rt = rt
                    {
                        not     (gpr[rt]);
                    }
                }
                else // XORI rt, rs, uimm16 -> rt = rs ^ uimm16
                {
                    mov         (eax, gpr[rs]);
                    if (uimm16)
                    {
                        xor     (eax, uimm16);
                    }
                    else // XORI rt, rs, 0 -> rt = ~rs
                    {
                        not     (eax);
                    }
                    mov         (gpr[rt], eax);
                }
            }
            else // XORI rt, 0, uimm16 -> rt = ~uimm16
            {
                mov             (gpr[rt], ~uimm16);
            }
        }
    }

    /* load upper 16-bit immediate */
    __forceinline void doLUI(u32 rt, u32 uimm16)
    {
        Gpr gpr;
        Mov mov;

        if (rt)
        {
            mov         (gpr[rt], uimm16<<16);
        }
    }

    /* bitwise right rotation */
    __forceinline void doROTR(u32 rd, u32 rt, u32 sa)
    {
        doSHIFT< ROR >(rd, rt, sa);
    }

    /* bitwise right rotation */
    __forceinline void doROTRV(u32 rd, u32 rt, u32 rs)
    {
        doSHIFTV< ROR >(rd, rt, rs);
    }

    /* move if zero */
    __forceinline void doMOVZ(u32 rd, u32 rs, u32 rt)
    {
        R32    eax(EAX);
        Gpr    gpr;
        Xor    xor;
        Mov    mov;
        Test   test;
        Cmovnz cmovnz;

        if (rd)
        {
            if (rt == rs) // MOVZ rd, rs|0, rs|0
            {
                if (rd == rs) // MOVZ rd, rd, rd -> rd = rd
                {
                }
                else if (rs) // MOVZ rd, rs, rs -> rd = rs ? rs : rd
                {
                    mov         (eax,     gpr[rs]);
                    test        (eax,     eax    );
                    cmovnz      (eax,     gpr[rd]);
                    mov         (gpr[rd], eax    );
                }
                else // MOVZ rd, 0, 0 -> rd = 0
                {
                    mov         (gpr[rd], 0);
                }
            }
            else
            {
                if (rt && rs) // MOVZ rd, rs, rt
                {
                    mov         (eax,     gpr[rt]);
                    test        (gpr[rs], -1     );
                    cmovnz      (eax,     gpr[rd]);
                    mov         (gpr[rd], eax    );
                }
                else if (rs) // MOVZ rd, rs, 0
                {
                    xor         (eax,     eax    );
                    test        (gpr[rs], -1     );
                    cmovnz      (eax,     gpr[rd]);
                    mov         (gpr[rd], eax    );
                }
                else // MOVZ rd, 0, rt -> rd = rt
                {
                    mov         (eax,     gpr[rt]);
                    mov         (gpr[rd], eax    );
                }
            }
        }
    }

    /* move if non-zero */
    __forceinline void doMOVN(u32 rd, u32 rs, u32 rt)
    {
        R32   eax(EAX);
        R32   ecx(ECX);
        Gpr   gpr;
        Xor   xor;
        Mov   mov;
        Test  test;
        Cmovz cmovz;

        if (rd)
        {
            if (rt == rs) // MOVN rd, rs|0, rs|0
            {
                if (rd == rs) // MOVN rd, rd, rd -> rd = rd
                {
                }
                else if (rs) // MOVN rd, rs, rs -> rd = !rs ? rs : rd
                {
                    mov         (eax,     gpr[rs]);
                    test        (eax,     eax    );
                    cmovz       (eax,     gpr[rd]);
                    mov         (gpr[rd], eax    );
                }
                else // MOVN rd, 0, 0 -> rd = rd
                {
                }
            }
            else
            {
                if (rt && rs) // MOVN rd, rs, rt
                {
                    mov         (eax,     gpr[rd]);
                    test        (gpr[rs], -1     );
                    cmovz       (eax,     gpr[rt]);
                    mov         (gpr[rd], eax    );
                }
                else if (rs) // MOVN rd, rs, 0
                {
                    xor         (eax,     eax    );
                    test        (gpr[rs], -1     );
                    cmovz       (eax,     gpr[rd]);
                    mov         (gpr[rd], eax    );
                }
                else // MOVN rd, 0, rt -> rd = rd
                {
                }
            }
        }
    }

    /* count leading zeroes */
    __forceinline void doCLZ(u32 rd, u32 rs)
    {
        R32    eax(EAX);
        R32    edx(EDX);
        Gpr    gpr;
        Bsr    bsr;
        Mov    mov;
        Not    not;
        Cmovnz cmovnz;

        if (rd)
        {
            if (rs)
            {
                mov         (edx,     gpr[rs]);
                mov         (eax,     32     );
                not         (edx             );
                bsr         (edx,     gpr[rs]);
                cmovnz      (eax,     edx    );
                mov         (gpr[rd], eax    );
            }
            else
            {
                mov         (gpr[rd], 0);
            }
        }
    }

    /* count leading ones */
    __forceinline void doCLO(u32 rd, u32 rs)
    {
        R32    eax(EAX);
        R32    edx(EDX);
        Gpr    gpr;
        Bsr    bsr;
        Mov    mov;
        Cmovnz cmovnz;

        if (rd)
        {
            if (rs)
            {
                bsr         (edx,     gpr[rs]);
                mov         (eax,     32     );
                cmovnz      (eax,     edx    );
                mov         (gpr[rd], eax    );
            }
            else
            {
                mov         (gpr[rd], 32);
            }
        }
    }

    template< int cc >
    __forceinline void doMINMAX(u32 rd, u32 rs, u32 rt)
    {
        R32    eax(EAX);
        R32    edx(EDX);
        Gpr    gpr;
        Mov    mov;
        Cmp    cmp;
        CmovXX cmovcc(cc);

        if (rd)
        {
            if (rs)
            {
                if (rt)
                {
                    mov         (edx,     gpr[rs]);
                    mov         (eax,     gpr[rt]);
                    cmp         (edx,     eax    );
                    cmovcc      (eax,     edx    );
                    mov         (gpr[rd], eax    );
                }
                else
                {
                    mov         (edx,     gpr[rs]);
                    mov         (eax,     0      );
                    cmp         (edx,     eax    );
                    cmovcc      (eax,     edx    );
                    mov         (gpr[rd], eax    );
                }
            }
            else if (rt)
            {
                mov             (edx,     0      );
                mov             (eax,     gpr[rt]);
                cmp             (edx,     eax    );
                cmovcc          (eax,     edx    );
                mov             (gpr[rd], eax    );
            }
            else
            {
                mov             (gpr[rd], 0);
            }
        }
    }

    /* maximal value between two signed integers */
    __forceinline void doMAX(u32 rd, u32 rs, u32 rt)
    {
        doMINMAX< G >(rd, rs, rt);
    }

    /* minimal value between two signed integers */
    __forceinline void doMIN(u32 rd, u32 rs, u32 rt)
    {
        doMINMAX< L >(rd, rs, rt);
    }

    /* bitwise extraction */
    __forceinline void doEXT(u32 rt, u32 rs, u32 lsb, u32 dbmalsb)
    {
        R32 eax(EAX);
        Gpr gpr;
        And and;
        Shr shr;
        Mov mov;

        if (rt)
        {
            // lsb     = least significant bit for bitwise extraction
            // dbmalsb = distance between most and least significant bits for bitwise extraction
            u32 mask = ((1<<(dbmalsb+1))-1)<<lsb;

            if (rs)
            {
                mov     (eax,     gpr[rs]);
                and     (eax,     mask   );
                shr     (eax,     lsb    );
                mov     (gpr[rt], eax    );
            }
            else
            {
                mov     (gpr[rt], 0);
            }
        }
    }

    /* bitwise insertion */
    __forceinline void doINS(u32 rt, u32 rs, u32 lsb, u32 msb)
    {
        R32 eax(EAX);
        R32 edx(EDX);
        Gpr gpr;
        And and;
        Or  or;
        Shl shl;
        Mov mov;

        if (rt)
        {
            // lsb = least significant bit for bitwise insertion
            // msb = most significant bit for bitwise insertion
            u32 mask = ((1<<(msb-lsb+1))-1)<<lsb;

            if (rs == rt)
            {
                mov     (edx,     gpr[rs]);
                mov     (eax,     edx    );
                shl     (edx,     lsb    );
                and     (eax,     ~mask  );
                and     (edx,     mask   );
                or      (eax,     edx    );
                mov     (gpr[rt], eax    );
            }
            else if (rs)
            {
                mov     (edx,     gpr[rs]);
                mov     (eax,     gpr[rt]);
                shl     (edx,     lsb    );
                and     (eax,     ~mask  );
                and     (edx,     mask   );
                or      (eax,     edx    );
                mov     (gpr[rt], eax    );
            }
            else
            {
                and     (gpr[rt], ~mask);
            }
        }
    }

    /* word swap byte within halfword : XYZW -> YXWZ */
    __forceinline void doWSBH(u32 rd, u32 rt)
    {
        R32   eax(EAX);
        Gpr   gpr;
        Bswap bswap;
        Rol   rol;
        Mov   mov;

        if (rd)
        {
            if (rt)
            {
                mov   (eax,     gpr[rt]);
                rol   (eax,     16     );
                bswap (eax             );
                mov   (gpr[rd], eax    );
            }
            else
            {
                mov (gpr[rt], 0);
            }
        }
    }

    /* word swap byte within word : XYZW -> ZWYX */
    __forceinline void doWSBW(u32 rd, u32 rt)
    {
        R32   eax(EAX);
        Gpr   gpr;
        Bswap bswap;
        Mov   mov;

        if (rd)
        {
            if (rt)
            {
                mov   (eax,     gpr[rt]);
                bswap (eax             );
                mov   (gpr[rd], eax    );
            }
            else
            {
                mov (gpr[rt], 0);
            }
        }
    }

    /* sign-extend byte */
    __forceinline void doSEB(u32 rd, u32 rt)
    {
        R32   eax(EAX);
        Gpr   gpr;
        Mov   mov;
        Movsx movsx;

        if (rd)
        {
            if (rt)
            {
                movsx (eax,     M8(gpr[rt]));
                mov   (gpr[rd], eax        );
            }
            else
            {
                mov   (gpr[rd], 0);
            }
        }
    }

    /* bit reverse */
    __forceinline void doBITREV(u32 rd, u32 rt)
    {
        static const u8 bit_reverse_table_256[] = 
        {
            0x00, 0x80, 0x40, 0xC0, 0x20, 0xA0, 0x60, 0xE0, 0x10, 0x90, 0x50, 0xD0, 0x30, 0xB0, 0x70, 0xF0, 
            0x08, 0x88, 0x48, 0xC8, 0x28, 0xA8, 0x68, 0xE8, 0x18, 0x98, 0x58, 0xD8, 0x38, 0xB8, 0x78, 0xF8, 
            0x04, 0x84, 0x44, 0xC4, 0x24, 0xA4, 0x64, 0xE4, 0x14, 0x94, 0x54, 0xD4, 0x34, 0xB4, 0x74, 0xF4, 
            0x0C, 0x8C, 0x4C, 0xCC, 0x2C, 0xAC, 0x6C, 0xEC, 0x1C, 0x9C, 0x5C, 0xDC, 0x3C, 0xBC, 0x7C, 0xFC, 
            0x02, 0x82, 0x42, 0xC2, 0x22, 0xA2, 0x62, 0xE2, 0x12, 0x92, 0x52, 0xD2, 0x32, 0xB2, 0x72, 0xF2, 
            0x0A, 0x8A, 0x4A, 0xCA, 0x2A, 0xAA, 0x6A, 0xEA, 0x1A, 0x9A, 0x5A, 0xDA, 0x3A, 0xBA, 0x7A, 0xFA,
            0x06, 0x86, 0x46, 0xC6, 0x26, 0xA6, 0x66, 0xE6, 0x16, 0x96, 0x56, 0xD6, 0x36, 0xB6, 0x76, 0xF6, 
            0x0E, 0x8E, 0x4E, 0xCE, 0x2E, 0xAE, 0x6E, 0xEE, 0x1E, 0x9E, 0x5E, 0xDE, 0x3E, 0xBE, 0x7E, 0xFE,
            0x01, 0x81, 0x41, 0xC1, 0x21, 0xA1, 0x61, 0xE1, 0x11, 0x91, 0x51, 0xD1, 0x31, 0xB1, 0x71, 0xF1,
            0x09, 0x89, 0x49, 0xC9, 0x29, 0xA9, 0x69, 0xE9, 0x19, 0x99, 0x59, 0xD9, 0x39, 0xB9, 0x79, 0xF9, 
            0x05, 0x85, 0x45, 0xC5, 0x25, 0xA5, 0x65, 0xE5, 0x15, 0x95, 0x55, 0xD5, 0x35, 0xB5, 0x75, 0xF5,
            0x0D, 0x8D, 0x4D, 0xCD, 0x2D, 0xAD, 0x6D, 0xED, 0x1D, 0x9D, 0x5D, 0xDD, 0x3D, 0xBD, 0x7D, 0xFD,
            0x03, 0x83, 0x43, 0xC3, 0x23, 0xA3, 0x63, 0xE3, 0x13, 0x93, 0x53, 0xD3, 0x33, 0xB3, 0x73, 0xF3, 
            0x0B, 0x8B, 0x4B, 0xCB, 0x2B, 0xAB, 0x6B, 0xEB, 0x1B, 0x9B, 0x5B, 0xDB, 0x3B, 0xBB, 0x7B, 0xFB,
            0x07, 0x87, 0x47, 0xC7, 0x27, 0xA7, 0x67, 0xE7, 0x17, 0x97, 0x57, 0xD7, 0x37, 0xB7, 0x77, 0xF7, 
            0x0F, 0x8F, 0x4F, 0xCF, 0x2F, 0xAF, 0x6F, 0xEF, 0x1F, 0x9F, 0x5F, 0xDF, 0x3F, 0xBF, 0x7F, 0xFF
        };

        R32   eax(EAX);
        R32   edx(EDX);
        R8    al(AL);
        R8    ah(AH);
        M8    lut(bit_reverse_table_256);
        Gpr   gpr;
        Rol   rol;
        Mov   mov;
        Movzx movzx;
        Bswap bswap;

        if (rd)
        {
            if (rt)
            {
                mov         (eax,     gpr[rt] ); // A  B  C  D
                bswap       (eax              ); // D  C  B  A
                movzx       (edx,     al      );
                mov         (al,      lut[edx]); // D  C  B  A'
                movzx       (edx,     ah      );
                mov         (ah,      lut[edx]); // D  C  B' A'
                rol         (eax,     16      ); // B' A' D  C 
                movzx       (edx,     al      );
                mov         (al,      lut[edx]); // B' A' D  C'
                movzx       (edx,     ah      );
                mov         (ah,      lut[edx]); // B' A' D' C'
                rol         (eax,     16      ); // D' C' B' A' 
                mov         (gpr[rd], eax     );
            }
            else
            {
                mov         (gpr[rd], 0);
            }
        }
    }

    /* sign-extend halfword */
    __forceinline void doSEH(u32 rd, u32 rt)
    {
        R32   eax(EAX);
        Gpr   gpr;
        Mov   mov;
        Movsx movsx;

        if (rd)
        {
            if (rt)
            {
                movsx       (eax,     M16(gpr[rt]));
                mov         (gpr[rd], eax         );
            }
            else
            {
                mov         (gpr[rd], 0);
            }
        }
    }

    __forceinline void doMFHI(u32 rd)
    {
        R32 eax(EAX);
        Gpr gpr;
        Mdr mdr;
        Mov mov;

        if (rd)
        {
            mov         (eax,     mdr[1]);
            mov         (gpr[rd], eax   );
        }
    }

    __forceinline void doMTHI(u32 rs)
    {
        R32 eax(EAX);
        Gpr gpr;
        Mdr mdr;
        Mov mov;

        if (rs)
        {
            mov         (eax,    gpr[rs]);
            mov         (mdr[1], eax    );
        }
        else
        {
            mov         (mdr[1], 0);
        }
    }

    __forceinline void doMFLO(u32 rd)
    {
        R32 eax(EAX);
        Gpr gpr;
        Mdr mdr;
        Mov mov;

        if (rd)
        {
            mov         (eax,     mdr[0]);
            mov         (gpr[rd], eax   );
        }
    }

    __forceinline void doMTLO(u32 rs)
    {
        R32 eax(EAX);
        Gpr gpr;
        Mdr mdr;
        Mov mov;

        if (rs)
        {
            mov         (eax,    gpr[rs]);
            mov         (mdr[0], eax    );
        }
        else
        {
            mov         (mdr[0], 0);
        }
    }

    /// MDU ///

    __forceinline void doMULT(u32 rs, u32 rt)
    {
        R32  eax(EAX);
        R32  edx(EDX);
        Gpr  gpr;
        Mdr  mdr;
        Imul imul;
        Mov  mov;

        if (rs && rt)
        {
            mov         (eax,    gpr[rs]);
            imul        (gpr[rt]        );
            mov         (mdr[0], eax    );
            mov         (mdr[1], edx    );
        }
        else
        {
            mov         (mdr[0], 0);            
            mov         (mdr[1], 0);            
        }
    }

    __forceinline void doMULTU(u32 rs, u32 rt)
    {
        R32 eax(EAX);
        R32 edx(EDX);
        Gpr gpr;
        Mdr mdr;
        Mul mul;
        Mov mov;

        if (rs && rt)
        {
            mov         (eax,    gpr[rs]);
            mul         (gpr[rt]        );
            mov         (mdr[0], eax    );
            mov         (mdr[1], edx    );
        }
        else
        {
            mov         (mdr[0], 0);            
            mov         (mdr[1], 0);            
        }
    }

    __forceinline void doDIV(u32 rs, u32 rt)
    {
        R32  eax(EAX);
        R32  edx(EDX);
        Gpr  gpr;
        Mdr  mdr;
        Idiv idiv;
        Sar  sar;
        Mov  mov;

        mov             (edx,    gpr[rs]);
        mov             (eax,    edx    );
        sar             (edx,    31     );
        idiv            (gpr[rt]        );
        mov             (mdr[0], eax    );
        mov             (mdr[1], edx    );
    }

    __forceinline void doDIVU(u32 rs, u32 rt)
    {
        R32 eax(EAX);
        R32 edx(EDX);
        Gpr gpr;
        Mdr mdr;
        Div div;
        Xor xor;
        Mov mov;

        mov             (eax,    gpr[rs]);
        xor             (edx,    edx    );
        div             (gpr[rt]        );
        mov             (mdr[0], eax    );
        mov             (mdr[1], edx    );
    }

    __forceinline void doMADD(u32 rs, u32 rt)
    {
        R32  eax(EAX);
        R32  edx(EDX);
        Gpr  gpr;
        Mdr  mdr;
        Add  add;
        Adc  adc;
        Imul imul;
        Mov  mov;

        if (rs && rt)
        {
            mov         (eax,    gpr[rs]);
            imul        (gpr[rt]        );
            add         (mdr[0], eax    );
            adc         (mdr[1], edx    );
        }
    }

    __forceinline void doMADDU(u32 rs, u32 rt)
    {
        R32 eax(EAX);
        R32 edx(EDX);
        Gpr gpr;
        Mdr mdr;
        Add add;
        Adc adc;
        Mul mul;
        Mov mov;

        if (rs && rt)
        {
            mov         (eax,    gpr[rs]);
            mul         (gpr[rt]        );
            add         (mdr[0], eax    );
            adc         (mdr[1], edx    );
        }
    }

    __forceinline void doMSUB(u32 rs, u32 rt)
    {
        R32  eax(EAX);
        R32  edx(EDX);
        Gpr  gpr;
        Mdr  mdr;
        Sub  sub;
        Sbb  sbb;
        Imul imul;
        Mov  mov;

        if (rs && rt)
        {
            mov         (eax,    gpr[rs]);
            imul        (gpr[rt]        );
            sub         (mdr[0], eax    );
            sbb         (mdr[1], edx    );
        }
    }

    __forceinline void doMSUBU(u32 rs, u32 rt)
    {
        R32 eax(EAX);
        R32 edx(EDX);
        Gpr gpr;
        Mdr mdr;
        Sub sub;
        Sbb sbb;
        Mul mul;
        Mov mov;

        if (rs && rt)
        {
            mov         (eax,    gpr[rs]);
            mul         (gpr[rt]        );
            sub         (mdr[0], eax    );
            sbb         (mdr[1], edx    );
        }
    }

    /// LSU ///

    __forceinline void doLB(u32 rt, u32 rs, s32 simm16)
    {
        R32   eax(EAX);
        Gpr   gpr;
        M8    mem((u8 const *)Memory::pointer);
        And   and;
        Mov   mov;
        Movsx movsx;

        if (rt)
        {
            mov   (eax,     gpr[rs]         );
            and   (eax,     (VMEM_SIZE-1)   );
            movsx (eax,     mem[eax][simm16]);
            mov   (gpr[rt], eax             );
        }
    }

    __forceinline void doLBU(u32 rt, u32 rs, s32 simm16)
    {
        R32   eax(EAX);
        Gpr   gpr;
        M8    mem((u8 const *)Memory::pointer);
        And   and;
        Mov   mov;
        Movzx movzx;

        if (rt)
        {
            mov   (eax,     gpr[rs]         );
            and   (eax,     (VMEM_SIZE-1)   );
            movzx (eax,     mem[eax][simm16]);
            mov   (gpr[rt], eax             );
        }
    }

    __forceinline void doLH(u32 rt, u32 rs, s32 simm16)
    {
        R32   eax(EAX);
        Gpr   gpr;
        M16   mem((u16 const *)Memory::pointer);
        And   and;
        Mov   mov;
        Movsx movsx;

        if (rt)
        {
            mov   (eax,     gpr[rs]         );
            and   (eax,     (VMEM_SIZE-1)   );
            movsx (eax,     mem[eax][simm16]);
            mov   (gpr[rt], eax             );
        }
    }

    __forceinline void doLHU(u32 rt, u32 rs, s32 simm16)
    {
        R32   eax(EAX);
        Gpr   gpr;
        M16   mem((u16 const *)Memory::pointer);
        And   and;
        Mov   mov;
        Movzx movzx;

        if (rt)
        {
            mov   (eax,     gpr[rs]         );
            and   (eax,     (VMEM_SIZE-1)   );
            movzx (eax,     mem[eax][simm16]);
            mov   (gpr[rt], eax             );
        }
    }

    __forceinline void doLWL(u32 rt, u32 rs, s32 simm16)
    {
        R32  eax(EAX);
        R32  ecx(ECX);
        R32  edx(EDX);
        Gpr  gpr;
        M32  mem((u32 const *)Memory::pointer);
        Add  add;
        Sub  sub;
        And  and;
        Shl  shl;
        Ror  ror;
        Shld shld;
        Mov  mov;

        // 0: M3 M2 M1|M0  R3|R2 R1 R0 ==> M0|R2 R1 R0
        // 1: M3 M2|M1 M0  R3 R2|R1 R0 ==> M1 M0|R1 R0
        // 2: M3|M2 M1 M0  R3 R2 R1|R0 ==> M2 M1 M0|R0
        // 3: M3 M2 M1 M0  R3 R2 R1 R0 ==> M3 M2 M1 M0
        if (rt)
        {
            mov         (ecx,     3                  );
            mov         (edx,     gpr[rs]            );
            add         (edx,     simm16             );
            sub         (ecx,     edx                );
            and         (edx,     (VMEM_SIZE-1)&~3   );
            and         (ecx,     3                  );
            mov         (eax,     gpr[rt]            );
            shl         (ecx,     3                  );
            mov         (edx,     mem[edx]           );
            ror         (eax                         );
            shld        (edx,     eax                );
            mov         (gpr[rt], edx                );
        }
        //static u32 const lwl_mask[4] =
        //{ 0xffffff, 0xffff, 0xff, 0 };
        //static u32 const lwl_shift[4] =
        //{ 24, 16, 8, 0 };
        //if (rt != 0)
        //{
        //    u32 address = gpr[rs] + simm16;
        //    u32 offset = address & 0x3;
        //    u32 data = Memory::memw(address & 0xfffffffc);
        //    gpr[rt] = (data << lwl_shift[offset]) | (gpr[rt] & lwl_mask[offset]);
        //}
    }

    __forceinline void doLW(u32 rt, u32 rs, s32 simm16)
    {
        R32 eax(EAX);
        Gpr gpr;
        M32 mem((u32 const *)Memory::pointer);
        And and;
        Mov mov;

        if (rt)
        {
            mov         (eax,     gpr[rs]         );
            and         (eax,     (VMEM_SIZE-1)   );
            mov         (eax,     mem[eax][simm16]);
            mov         (gpr[rt], eax             );
        }
    }

    __forceinline void doLWR(u32 rt, u32 rs, s32 simm16)
    {
        R32  eax(EAX);
        R32  ecx(ECX);
        R32  edx(EDX);
        Gpr  gpr;
        M32  mem((u32 const *)Memory::pointer);
        Add  add;
        And  and;
        Shl  shl;
        Rol  rol;
        Shrd shrd;
        Mov  mov;

        // 0: M3 M2 M1 M0  R3 R2 R1 R0 ==> M3 M2 M1 M0
        // 1: M3 M2 M1|M0  R3|R2 R1 R0 ==> R3|M3 M2 M1
        // 2: M3 M2|M1 M0  R3 R2|R1 R0 ==> R3 R2|M3 M2
        // 3: M3|M2 M1 M0  R3 R2 R1|R0 ==> R3 R2 R1|M3
        if (rt)
        {
            mov         (edx,     gpr[rs]            );
            add         (edx,     simm16             );
            mov         (ecx,     edx                );
            and         (edx,     (VMEM_SIZE-1)&~3   );
            and         (ecx,     3                  );
            mov         (eax,     gpr[rt]            );
            shl         (ecx,     3                  );
            mov         (edx,     mem[edx]           );
            rol         (eax                         );
            shrd        (edx,     eax                );
            mov         (gpr[rt], edx                );
        }
        //static u32 const lwr_mask[4] =
        //{ 0, 0xff000000, 0xffff0000, 0xffffff00 };
        //static u32 const lwr_shift[4] =
        //{ 0, 8, 16, 24 };
        //if (rt != 0)
        //{
        //    u32 address = gpr[rs] + simm16;
        //    u32 offset = address & 0x3;
        //    u32 data = Memory::memw(address & 0xfffffffc);
        //    gpr[rt] = (data >> lwr_shift[offset]) | (gpr[rt] & lwr_mask[offset]);
        //}
    }

    __forceinline void doSB(u32 rt, u32 rs, u32 simm16)
    {
        R32 eax(EAX);
        R32 edx(EDX);
        Gpr gpr;
        M8  mem((u8 const *)Memory::pointer);
        And and;
        Mov mov;

        if (rt)
        {
            mov         (edx,              gpr[rs]      );
            mov         (eax,              gpr[rt]      );
            and         (edx,              (VMEM_SIZE-1));
            mov         (mem[edx][simm16], R8(eax)      );
        }
    }

    __forceinline void doSH(u32 rt, u32 rs, u32 simm16)
    {
        R32 eax(EAX);
        R32 edx(EDX);
        Gpr gpr;
        M16 mem((u16 const *)Memory::pointer);
        And and;
        Mov mov;

        if (rt)
        {
            mov         (edx,              gpr[rs]      );
            mov         (eax,              gpr[rt]      );
            and         (edx,              (VMEM_SIZE-1));
            mov         (mem[edx][simm16], R16(eax)     );
        }
    }

    __forceinline void doSWL(u32 rt, u32 rs, s32 simm16)
    {
        R32  eax(EAX);
        R32  ecx(ECX);
        Gpr  gpr;
        M32  mem((u32 const *)Memory::pointer);
        Add  add;
        Sub  sub;
        And  and;
        Shl  shl;
        Rol  rol;
        Mov  mov;
        Shrd shrd;

        // 0: M3 M2 M1|M0  R3|R2 R1 R0 ==> M3 M2 M1|R3
        // 1: M3 M2|M1 M0  R3 R2|R1 R0 ==> M3 M2|R3 R2
        // 2: M3|M2 M1 M0  R3 R2 R1|R0 ==> M3|R3 R2 R1
        // 3: M3 M2 M1 M0  R3 R2 R1 R0 ==> R3 R2 R1 R0
        if (rt)
        {
            mov         (ecx,     3                  );
            mov         (eax,     gpr[rs]            );
            add         (eax,     simm16             );
            sub         (ecx,     eax                );
            and         (eax,     (VMEM_SIZE-1)&~3   );
            and         (ecx,     3                  );
            mov         (eax,     mem[eax]           );
            shl         (ecx,     3                  );
            rol         (eax                         );
            shrd        (gpr[rt], eax                );
        }
        //static u32 const swl_mask[4] =
        //{ 0xffffff00, 0xffff0000, 0xff000000, 0 };
        //static u32 const swl_shift[4] =
        //{ 24, 16, 8, 0 };
        //u32 address = gpr[rs] + simm16;
        //u32 offset = address & 0x3;
        //address &= 0xfffffffc;
        //Memory::memw(address) = (gpr[rt] >> swl_shift[offset]) | (Memory::memw(address) & swl_mask[offset]);
    }

    __forceinline void doSW(u32 rt, u32 rs, u32 simm16)
    {
        R32 eax(EAX);
        R32 edx(EDX);
        Gpr gpr;
        M32 mem((u32 const *)Memory::pointer);
        And and;
        Mov mov;

        if (rt)
        {
            mov         (edx,              gpr[rs]      );
            mov         (eax,              gpr[rt]      );
            and         (edx,              (VMEM_SIZE-1));
            mov         (mem[edx][simm16], eax          );
        }
    }

    __forceinline void doSWR(u32 rt, u32 rs, s32 simm16)
    {
        R32  eax(EAX);
        R32  ecx(ECX);
        Gpr  gpr;
        M32  mem((u32 const *)Memory::pointer);
        Add  add;
        And  and;
        Shl  shl;
        Ror  ror;
        Mov  mov;
        Shld shld;

        // 0: M3 M2 M1 M0  R3 R2 R1 R0 ==> R3 R2 R1 R0
        // 1: M3 M2 M1|M0  R3|R2 R1 R0 ==> R2 R1 R0|M0
        // 2: M3 M2|M1 M0  R3 R2|R1 R0 ==> R1 R0|M1 M0
        // 3: M3|M2 M1 M0  R3 R2 R1|R0 ==> R0|M2 M1 R0
        if (rt)
        {
            mov         (eax,     gpr[rs]            );
            add         (eax,     simm16             );
            mov         (ecx,     eax                );
            and         (eax,     (VMEM_SIZE-1)&~3   );
            and         (ecx,     3                  );
            mov         (eax,     mem[eax]           );
            shl         (ecx,     3                  );
            ror         (eax                         );
            shld        (gpr[rt], eax                );
        }
        //static u32 const swl_mask[4] =
        //{ 0, 0xff, 0xffff, 0xffffff };
        //static u32 const swl_shift[4] =
        //{ 0, 8, 16, 24 };
        //u32 address = gpr[rs] + simm16;
        //u32 offset = address & 0x3;
        //address &= 0xfffffffc;
        //Memory::memw( address) = (gpr[rt] << swl_shift[offset]) | (Memory::memw(address) & swl_mask[offset]);
    }

    __forceinline void doLL(u32 rt, u32 rs, s32 simm16)
    {
        R32 eax(EAX);
        Gpr gpr;
        M32 mem((u32 const *)Memory::pointer);
        M8  llbit((u8 const *)&AlContext::llbit);
        And and;
        Mov mov;

        if (rt)
        {
            mov     (eax,     gpr[rs]         );
            and     (eax,     (VMEM_SIZE-1)   );
            mov     (eax,     mem[eax][simm16]);
            mov     (gpr[rt], eax             );
            mov     (llbit,   1               );
        }
    }

    __forceinline void doSC(u32 rt, u32 rs, u32 simm16)
    {
        R32   eax(EAX);
        R32   edx(EDX);
        Gpr   gpr;
        M32   mem((u32 const *)Memory::pointer);
        M8    llbit((u8 const *)&AlContext::llbit);
        And   and;
        Mov   mov;
        Movzx movzx;

        if (rt)
        {
            mov     (edx,              gpr[rs]      );
            mov     (eax,              gpr[rt]      );
            and     (edx,              (VMEM_SIZE-1));
            mov     (mem[edx][simm16], eax          );
            movzx   (edx,              llbit        );
            mov     (gpr[rt]         , edx          );
        }
    }

    __forceinline void doLWC1(u32 ft, u32 rs, u32 simm16)
    {
        R32 eax(EAX);
        Gpr gpr;
        Fpr fpr;
        M32 mem((u32 const *)Memory::pointer);
        And and;
        Mov mov;

        mov         (eax,     gpr[rs]         );
        and         (eax,     (VMEM_SIZE-1)   );
        mov         (eax,     mem[eax][simm16]);
        mov         (fpr[ft], eax             );
    }

    __forceinline void doSWC1(u32 ft, u32 rs, u32 simm16)
    {
        R32 eax(EAX);
        R32 edx(EDX);
        Gpr gpr;
        Fpr fpr;
        M32 mem((u32 const *)Memory::pointer);
        And and;
        Mov mov;

        mov         (edx,              gpr[rs]      );
        mov         (eax,              fpr[ft]      );
        and         (edx,              (VMEM_SIZE-1));
        mov         (mem[edx][simm16], eax          );
    }

    /// FPU

    __forceinline void doMFC1(u32 rt, u32 fs)
    {
        R32 eax(EAX);
        Gpr gpr;
        Fpr fpr;
        Mov mov;

        if (rt)
        {
            mov         (eax,     fpr[fs]);
            mov         (gpr[rt], eax    );
        }
    }

    __forceinline void doCFC1(u32 rt, u32 fs)
    {
        R32 eax(EAX);
        R32 ecx(ECX);
        R32 edx(EDX);
        M32 mxcsr;
        M32 ea;
        Gpr gpr;
        Fcr fcr;
        And and;
        Or  or;
        Xor xor;
        Shl shl;
        Shr shr;
        Mov mov;
        Lea lea;

        if (rt)
        {
            switch (fs)
            {
            case 0:
                mov         (eax,     fcr[0]);
                mov         (gpr[rt], eax   );
                break;

            case 31:
                // mxcsr          fcr31
                // 00    -> N  -> 00     ===> fcr31[1..0] = mxcsr[14..13] ^ (mxcsr[13]<<1);
                // 01    -> D  -> 11     ===> fcr31[1..0] = mxcsr[14..13] ^ (mxcsr[13]<<1);
                // 10    -> U  -> 10     ===> fcr31[1..0] = mxcsr[14..13] ^ (mxcsr[13]<<1);
                // 11    -> T  -> 01     ===> fcr31[1..0] = mxcsr[14..13] ^ (mxcsr[13]<<1);
                //
                // 1     -> FZ -> 1      ===> fcr31[24]   = mxcsr[15];

                mov         (edx, mxcsr      );
                mov         (ecx, fcr[31]    );
                shr         (edx, 13         );
                and         (ecx, ~0x01000003);
                lea         (eax, ea[edx*2]  );
                and         (edx, 4          );
                and         (eax, 3          );
                shl         (edx, 22         );
                xor         (ecx, eax        );
                or          (ecx, edx        );
                mov         (fcr[31], ecx    );
                break;

            default:
                break;
            }
        }
    }

    __forceinline void doMTC1(u32 rt, u32 fs)
    {
        R32 eax(EAX);
        Gpr gpr;
        Fpr fpr;
        Mov mov;

        if (rt)
        {
            mov         (eax,     gpr[rt]);
            mov         (fpr[fs], eax    );
        }
        else
        {
            mov         (fpr[fs], 0);
        }
    }

    __forceinline void doCTC1(u32 rt, u32 fs)
    {
        R32  eax(EAX);
        R32  ecx(ECX);
        R32  edx(EDX);
        M32  mxcsr;
        Gpr  gpr;
        Fcr  fcr;
        And  and;
        Or   or;
        Xor  xor;
        Shl  shl;
        Shr  shr;
        Shld shld;
        Mov  mov;

        switch (fs)
        {
        case 31:
            // mxcsr          fcr31
            // 00    <- N  <- 00     ===> mxcsr[14..13] = fcr31[1..0] ^ (fcr31[0]<<1);
            // 01    <- D  <- 11     ===> mxcsr[14..13] = fcr31[1..0] ^ (fcr31[0]<<1);
            // 10    <- U  <- 10     ===> mxcsr[14..13] = fcr31[1..0] ^ (fcr31[0]<<1);
            // 11    <- T  <- 01     ===> mxcsr[14..13] = fcr31[1..0] ^ (fcr31[0]<<1);
            //
            // 1     -> FZ -> 1      ===> mxcsr[15]   = fcr31[24];

            mov         (edx,     fcr[31]        );
            mov         (ecx,     mxcsr          );
            and         (edx,     0x01800003     );
            mov         (fcr[31], edx            );
            and         (ecx,     ~mxcsr_all_mask);
            shl         (edx,     31-24          ); // bits 24, 1 and 0 respectively move to bits 31, 8 and 7
            or          (ecx,     0x00001f80     ); // no FPU exception
            shld        (eax,     edx,         1 );        
            shl         (edx,     31-8           ); // bits 8 and 7 respectively move to bits 31 and 30
            shld        (eax,     edx,         2 );        
            and         (edx,     0x40000000     ); // bits else 30 are 0
            shl         (eax,     31-2           ); // bits 2, 1 and 0 respectively move to bits 31, 30 and 29
            xor         (eax,     edx            );
            shr         (eax,     31-15          ); // bits 31, 30, 29 respectively move to bits 15, 14 and 13 
            or          (ecx,     eax            );
            mov         (mxcsr,   ecx            );
            break;

        default:
            break;
        }
    }

    __forceinline void doCVT_S_W(u32 fd, u32 fs)
    {
        Fpr      fpr;
        Xmm      xmm;
        Cvtsi2ss cvtsi2ss;
        Movss    movss;

        cvtsi2ss        (xmm(0), fpr[fs]);
        movss           (fpr[fd], xmm(0));
    }

    __forceinline void doADD_S(u32 fd, u32 fs, u32 ft)
    {
        Fpr   fpr;
        Xmm   xmm;
        Addss addss;
        Movss movss;

        movss           (xmm(0), fpr[fs]);
        addss           (xmm(0), fpr[ft]);
        movss           (fpr[fd], xmm(0));
    }

    __forceinline void doSUB_S(u32 fd, u32 fs, u32 ft)
    {
        Fpr   fpr;
        Xmm   xmm;
        Subss subss;
        Movss movss;

        movss           (xmm(0), fpr[fs]);
        subss           (xmm(0), fpr[ft]);
        movss           (fpr[fd], xmm(0));
    }

    __forceinline void doMUL_S(u32 fd, u32 fs, u32 ft)
    {
        Fpr   fpr;
        Xmm   xmm;
        Mulss mulss;
        Movss movss;

        movss           (xmm(0), fpr[fs]);
        mulss           (xmm(0), fpr[ft]);
        movss           (fpr[fd], xmm(0));
    }

    __forceinline void doDIV_S(u32 fd, u32 fs, u32 ft)
    {
        Fpr   fpr;
        Xmm   xmm;
        Divss divss;
        Movss movss;

        movss           (xmm(0), fpr[fs]);
        divss           (xmm(0), fpr[ft]);
        movss           (fpr[fd], xmm(0));
    }

    __forceinline void doSQRT_S(u32 fd, u32 fs)
    {
        Fpr    fpr;
        Xmm    xmm;
        Sqrtss sqrtss;
        Movss  movss;

        sqrtss          (xmm(0), fpr[fs]);
        movss           (fpr[fd], xmm(0));
    }

    __forceinline void doCVT_W_S(u32 fd, u32 fs)
    {
        Fpr      fpr;
        Xmm      xmm;
        Cvtss2si cvtss2si;
        Movss    movss;

        movss           (xmm(0), fpr[fs]);
        cvtss2si        (fpr[fd], xmm(0));
    }

    __forceinline void doABS_S(u32 fd, u32 fs)
    {
        R32 eax(EAX);
        Fpr fpr;
        And and;
        Mov mov;

        if (fd == fs)
        {
            and         (fpr[fd], 0x7FFFFFFF);
        }
        else
        {
            mov         (eax,     fpr[fs]   );
            and         (eax,     0x7FFFFFFF);
            mov         (fpr[fd], eax       );
        }
    }

    __forceinline void doMOV_S(u32 fd, u32 fs)
    {
        R32 eax(EAX);
        Fpr fpr;
        Mov mov;

        if (fd != fs)
        {
            mov         (eax, fpr[fs]);
            mov         (fpr[fd], eax);
        }
    }

    __forceinline void doNEG_S(u32 fd, u32 fs)
    {
        R32 eax(EAX);
        Fpr fpr;
        Xor xor;
        Mov mov;

        if (fd == fs)
        {
            xor         (fpr[fd], 0x80000000);
        }
        else
        {
            mov         (eax,     fpr[fs]   );
            xor         (eax,     0x80000000);
            mov         (fpr[fd], eax       );
        }
    }

    __forceinline void doROUND_W_S(u32 fd, u32 fs)
    {
        R32      eax(EAX);
        R32      esp(ESP);
        Fpr      fpr;
        Xmm      xmm;
        M32      mxcsr;
        M32      mem;
        And      and;
        Push     push;
        Pop      pop;
        Mov      mov;
        Movss    movss;
        Cvtss2si cvtss2si;
        Ldmxcsr  ldmxcsr;

        mov             (eax,     mxcsr            );
        and             (eax,     ~mxcsr_round_mask);
        push            (eax                       );
        movss           (xmm(0),  fpr[fs]          );
        ldmxcsr         (mem[esp]                  );
        pop             (eax                       );
        cvtss2si        (fpr[fd], xmm(0)           );
        ldmxcsr         (mxcsr                     );
    }

    __forceinline void doTRUNC_W_S(u32 fd, u32 fs)
    {
        R32      eax(EAX);
        R32      esp(ESP);
        Fpr      fpr;
        Xmm      xmm;
        M32      mxcsr;
        M32      mem;
        And      and;
        Or       or;
        Push     push;
        Pop      pop;
        Mov      mov;
        Movss    movss;
        Cvtss2si cvtss2si;
        Ldmxcsr  ldmxcsr;

        mov             (eax,     mxcsr                  );
        and             (eax,     ~mxcsr_round_mask      );
        or              (eax,     mxcsr_round_toward_zero);
        push            (eax                             );
        movss           (xmm(0),  fpr[fs]                );
        ldmxcsr         (mem[esp]                        );
        pop             (eax                             );
        cvtss2si        (fpr[fd], xmm(0)                 );
        ldmxcsr         (mxcsr                           );
    }

    __forceinline void doCEIL_W_S(u32 fd, u32 fs)
    {
        R32      eax(EAX);
        R32      esp(ESP);
        Fpr      fpr;
        Xmm      xmm;
        M32      mxcsr;
        M32      mem;
        And      and;
        Or       or;
        Push     push;
        Pop      pop;
        Mov      mov;
        Movss    movss;
        Cvtss2si cvtss2si;
        Ldmxcsr  ldmxcsr;

        mov             (eax,     mxcsr            );
        and             (eax,     ~mxcsr_round_mask);
        or              (eax,     mxcsr_round_up   );
        push            (eax                       );
        movss           (xmm(0),  fpr[fs]          );
        ldmxcsr         (mem[esp]                  );
        pop             (eax                       );
        cvtss2si        (fpr[fd], xmm(0)           );
        ldmxcsr         (mxcsr                     );
    }

    __forceinline void doFLOOR_W_S(u32 fd, u32 fs)
    {
        R32      eax(EAX);
        R32      esp(ESP);
        Fpr      fpr;
        Xmm      xmm;
        M32      mxcsr;
        M32      mem;
        And      and;
        Or       or;
        Push     push;
        Pop      pop;
        Mov      mov;
        Movss    movss;
        Cvtss2si cvtss2si;
        Ldmxcsr  ldmxcsr;

        mov             (eax,     mxcsr            );
        and             (eax,     ~mxcsr_round_mask);
        or              (eax,     mxcsr_round_down );
        push            (eax                       );
        movss           (xmm(0),  fpr[fs]          );
        ldmxcsr         (mem[esp]                  );
        pop             (eax                       );
        cvtss2si        (fpr[fd], xmm(0)           );
        ldmxcsr         (mxcsr                     );
    }

    template< u32 cond >
    __forceinline void doC_COND_S(u32 const fs, u32 const ft)
    {
        R32    eax(EAX);
        R32    edx(EDX);
        Fpr    fpr;
        Fcr    fcr;
        Xmm    xmm;
        And    and;
        Or     or;
        Mov    mov;
        Movss  movss;
        Comiss comiss;
        Cmovp  cmovp;
        Cmove  cmove; 
        Cmovb  cmovb;
        Cmovbe cmovbe;

        mov                 (eax,    fcr[31]   );
        mov                 (edx,    0x00800000);
        movss               (xmm(0), fpr[fs]   );
        or                  (edx,    eax       );
        and                 (eax,    0xFF7FFFFF);
        if (ft == fs)
        {
            comiss          (xmm(0), xmm(0)    );
        }
        else
        {
            comiss          (xmm(0), fpr[ft]   );
        }
        if (cond & 1) // unordered ?
        {
            cmovp           (eax,    edx       );
        }
        else
        {
            cmovp           (edx,    eax       );
        }
        switch ((cond>>1)&3)
        {
        case 0:                                   break;

        case 1:
            cmove           (eax,    edx       ); break;
        case 2:
            cmovb           (eax,    edx       ); break;
        case 3:
            cmovbe          (eax,    edx       ); break;
        }
        mov                 (fcr[31], eax      );
    }

    /// BCU ///

    __forceinline void doBEQ(u32 rs, u32 rt, s32 simm16)
    {
        R32   eax(EAX);
        R32   ebp(EBP);
        R8    ah(AH);
        M8    dslot(delayslot_stack);
        M32   state(&theEmulator.CurrentState());
        Pc    pc;
        Gpr   gpr;
        Cmp   cmp;
        Mov   mov;
        Lahf  lahf;
        Sahf  sahf;
        Je    je;
        Pop   pop;
        Ret   ret;
        Label goon;

        cmp         (state,              1                 );
        je.s        (goon                                  );

        // if state is not running, we must leave this fragment
        mov         (eax,                pc                );
        pop         (ebp                                   );
        ret         (                                      );

        goon.Bind();

        mov         (eax,                gpr[rs]           );
        cmp         (eax,                gpr[rt]           );
        lahf        (                                      );
        mov         (dslot[delayslot++], ah                );

        // recompile next instruction

        mov         (ah,                 dslot[--delayslot]);
        sahf        (                                      );
        je          (                                      ); // TODO
    }

    __forceinline void doBNE(u32 rs, u32 rt, u32 simm16)
    {
        R32  eax(EAX);
        R8   ah(AH);
        M8   dslot(delayslot_stack);
        Gpr  gpr;
        Cmp  cmp;
        Mov  mov;
        Lahf lahf;
        Sahf sahf;
        Jne  jne;

        mov         (eax,                gpr[rs]           );
        cmp         (eax,                gpr[rt]           );
        lahf        (                                      );
        mov         (dslot[delayslot++], ah                );

        // recompile next instruction

        mov         (ah,                 dslot[--delayslot]);
        sahf        (                                      );
        jne         (                                      ); // TODO
    }

    __forceinline void doBLTZ(u32 rs, s32 simm16)
    {
        R32  eax(EAX);
        R8   ah(AH);
        M8   dslot(delayslot_stack);
        Gpr  gpr;
        Cmp  cmp;
        Mov  mov;
        Lahf lahf;
        Sahf sahf;
        Jl   jl;

        cmp         (gpr[rs],            0                 );
        lahf        (                                      );
        mov         (dslot[delayslot++], ah                );

        // recompile next instruction

        mov         (ah,                 dslot[--delayslot]);
        sahf        (                                      );
        jl          (                                      ); // TODO
    }

    __forceinline void doBGEZ(u32 rs, s32 simm16)
    {
        R32  eax(EAX);
        R8   ah(AH);
        M8   dslot(delayslot_stack);
        Gpr  gpr;
        Cmp  cmp;
        Mov  mov;
        Lahf lahf;
        Sahf sahf;
        Jge  jge;

        cmp         (gpr[rs],            0                 );
        lahf        (                                      );
        mov         (dslot[delayslot++], ah                );

        // recompile next instruction

        mov         (ah,                 dslot[--delayslot]);
        sahf        (                                      );
        jge         (                                      ); // TODO
    }

    __forceinline void doBLTZL(u32 rs, s32 simm16)
    {
        R32   eax(EAX);
        R8    ah(AH);
        M8    dslot(delayslot_stack);
        Gpr   gpr;
        Cmp   cmp;
        Mov   mov;
        Lahf  lahf;
        Sahf  sahf;
        Jl    jl;
        Jge   jge;
        Label skip;

        cmp         (gpr[rs],            0                 );
        jge.s       (skip                                  );
        lahf        (                                      );
        mov         (dslot[delayslot++], ah                );

        // recompile next instruction

        mov         (ah,                 dslot[--delayslot]);
        sahf        (                                      );
        jl          (                                      ); // TODO

        skip.Bind();
    }

    __forceinline void doBGEZL(u32 rs, s32 simm16)
    {
        R32   eax(EAX);
        R8    ah(AH);
        M8    dslot(delayslot_stack);
        Gpr   gpr;
        Cmp   cmp;
        Mov   mov;
        Lahf  lahf;
        Sahf  sahf;
        Jge   jge;
        Jl    jl;
        Label skip;

        cmp         (gpr[rs],            0                 );
        jl.s        (skip                                  );
        lahf        (                                      );
        mov         (dslot[delayslot++], ah                );

        // recompile next instruction

        mov         (ah,                 dslot[--delayslot]);
        sahf        (                                      );
        jge         (                                      ); // TODO

        skip.Bind();
    }

    __forceinline void doBLEZ(u32 rs, u32 simm16)
    {
        R32  eax(EAX);
        R8   ah(AH);
        M8   dslot(delayslot_stack);
        Gpr  gpr;
        Cmp  cmp;
        Mov  mov;
        Lahf lahf;
        Sahf sahf;
        Jle  jle;

        cmp         (gpr[rs],            0                 );
        lahf        (                                      );
        mov         (dslot[delayslot++], ah                );

        // recompile next instruction

        mov         (ah,                 dslot[--delayslot]);
        sahf        (                                      );
        jle         (                                      ); // TODO
    }

    __forceinline void doBGTZ(u32 rs, u32 simm16)
    {
        R32  eax(EAX);
        R8   ah(AH);
        M8   dslot(delayslot_stack);
        Gpr  gpr;
        Cmp  cmp;
        Mov  mov;
        Lahf lahf;
        Sahf sahf;
        Jg   jg;

        cmp         (gpr[rs],            0                 );
        lahf        (                                      );
        mov         (dslot[delayslot++], ah                );

        // recompile next instruction

        mov         (ah,                 dslot[--delayslot]);
        sahf        (                                      );
        jg          (                                      ); // TODO
    }

    __forceinline void doBEQL(u32 rs, u32 rt, s32 simm16)
    {
        R32   eax(EAX);
        R8    ah(AH);
        M8    dslot(delayslot_stack);
        Gpr   gpr;
        Cmp   cmp;
        Mov   mov;
        Lahf  lahf;
        Sahf  sahf;
        Je    je;
        Jne   jne;
        Label skip;

        mov         (eax,                gpr[rs]           );
        cmp         (eax,                gpr[rt]           );
        jne.s       (skip                                  );
        lahf        (                                      );
        mov         (dslot[delayslot++], ah                );

        // recompile next instruction

        mov         (ah,                 dslot[--delayslot]);
        sahf        (                                      );
        je          (                                      ); // TODO

        skip.Bind();
    }

    __forceinline void doBNEL(u32 rs, u32 rt, s32 simm16)
    {
        R32   eax(EAX);
        R8    ah(AH);
        M8    dslot(delayslot_stack);
        Gpr   gpr;
        Cmp   cmp;
        Mov   mov;
        Lahf  lahf;
        Sahf  sahf;
        Jne   jne;
        Je    je;
        Label skip;

        mov         (eax, gpr[rs]                          );
        cmp         (eax, gpr[rt]                          );
        je.s        (skip                                  );
        lahf        (                                      );
        mov         (dslot[delayslot++], ah                );

        // recompile next instruction

        mov         (ah,                 dslot[--delayslot]);
        sahf        (                                      );
        jne         (                                      ); // TODO

        skip.Bind();
    }

    __forceinline void doBLEZL(u32 rs, s32 simm16)
    {
        R32   eax(EAX);
        R8    ah(AH);
        M8    dslot(delayslot_stack);
        Gpr   gpr;
        Cmp   cmp;
        Mov   mov;
        Lahf  lahf;
        Sahf  sahf;
        Jle   jle;
        Jg    jg;
        Label skip;

        cmp         (gpr[rs], 0                            );
        jg.s        (skip                                  );
        lahf        (                                      );
        mov         (dslot[delayslot++], ah                );

        // recompile next instruction

        mov         (ah,                 dslot[--delayslot]);
        sahf        (                                      );
        jle         (                                      ); // TODO

        skip.Bind();
    }

    __forceinline void doBGTZL(u32 rs, s32 simm16)
    {
        R32   eax(EAX);
        R8    ah(AH);
        M8    dslot(delayslot_stack);
        Gpr   gpr;
        Cmp   cmp;
        Mov   mov;
        Lahf  lahf;
        Sahf  sahf;
        Jg    jg;
        Jle   jle;
        Label skip;

        cmp         (gpr[rs], 0                            );
        jle.s       (skip                                  );
        lahf        (                                      );
        mov         (dslot[delayslot++], ah                );

        // recompile next instruction

        mov         (ah,                 dslot[--delayslot]);
        sahf        (                                      );
        jg          (                                      ); // TODO

        skip.Bind();
    }

    __forceinline bool doBC1F(s32 simm16)
    {
        R32  eax(EAX);
        R8   ah(AH);
        M8   dslot(delayslot_stack);
        Fcr  fcr;
        Test test;
        Mov  mov;
        Lahf lahf;
        Sahf sahf;
        Jz   jz;

        test        (fcr[31], 0x00800000                   );
        lahf        (                                      );
        mov         (dslot[delayslot++], ah                );

        // recompile next instruction

        mov         (ah,                 dslot[--delayslot]);
        sahf        (                                      );
        jz          (                                      ); // TODO
    }

    __forceinline bool doBC1T(s32 simm16)
    {
        R32  eax(EAX);
        R8   ah(AH);
        M8   dslot(delayslot_stack);
        Fcr  fcr;
        Test test;
        Mov  mov;
        Lahf lahf;
        Sahf sahf;
        Jnz  jnz;

        test        (fcr[31], 0x00800000                   );
        lahf        (                                      );
        mov         (dslot[delayslot++], ah                );

        // recompile next instruction

        mov         (ah,                 dslot[--delayslot]);
        sahf        (                                      );
        jnz         (                                      ); // TODO
    }

    __forceinline bool doBC1FL(s32 simm16)
    {
        R32   eax(EAX);
        R8    ah(AH);
        M8    dslot(delayslot_stack);
        Fcr   fcr;
        Test  test;
        Mov   mov;
        Lahf  lahf;
        Sahf  sahf;
        Jz    jz;
        Jnz   jnz;
        Label skip;

        test        (fcr[31], 0x00800000                   );
        jnz.s       (skip                                  ); // TODO
        lahf        (                                      );
        mov         (dslot[delayslot++], ah                );

        // recompile next instruction

        mov         (ah,                 dslot[--delayslot]);
        sahf        (                                      );
        jz          (                                      ); // TODO

        skip.Bind();
    }

    __forceinline bool doBC1TL(s32 UNUSED(simm16), bool &t)
    {
        R32   eax(EAX);
        R8    ah(AH);
        M8    dslot(delayslot_stack);
        Fcr   fcr;
        Test  test;
        Mov   mov;
        Lahf  lahf;
        Sahf  sahf;
        Jnz   jnz;
        Jz    jz;
        Label skip;

        test        (fcr[31], 0x00800000   );
        jz.s        (skip                  ); // TODO
        lahf        (                      );
        mov         (dslot[delayslot++], ah);

        // recompile next instruction

        mov         (ah, dslot[--delayslot]);
        sahf        (                      );
        jnz         (                      ); // TODO

        skip.Bind();
    }

};

static u8 code[4096];

static al_Recompiler rec;

static AlContext ctx;

u32 AlContext::execute()
{
    return pc + 4;
}

void recompiler_test()
{
    rec.pointer = code;
#if 0
    rec.doADDU(1, 2, 3);
    rec.doSUBU(1, 2, 3);
    rec.doOR(1, 2, 3);
    rec.doAND(1, 2, 3);
    rec.doXOR(1, 2, 3);
    rec.doNOR(1, 2, 3);
    rec.doSLT(1, 2, 3);
    rec.doSLTU(1, 2, 3);
    rec.doADDIU(1, 2, 32);
    rec.doSLTI(1, 2, 32);
    rec.doSLTIU(1, 2, 32);
    rec.doANDI(1, 2, 32);
    rec.doORI(1, 2, 32);
    rec.doXORI(1, 2, 32);
    rec.doLUI(1, 32);
    rec.doROTR(1, 2, 8);
    rec.doROTRV(1, 2, 3);
    rec.doMOVZ(1, 2, 3);
    rec.doMOVN(1, 2, 3);
    rec.doCLO(1, 2);
    rec.doCLZ(1, 2);
    rec.doMIN(1, 2, 3);
    rec.doMAX(1, 2, 3);
    rec.doEXT(1, 2, 1, 30);
    rec.doINS(1, 2, 1, 30);
    rec.doWSBH(1, 2);
    rec.doWSBW(1, 2);
    rec.doSEB(1, 2);
    rec.doBITREV(1, 2);
    rec.doSEH(1, 2);
    rec.doMFHI(1);
    rec.doMTHI(1);
    rec.doMFLO(1);
    rec.doMTLO(1);
    rec.doMULT(1, 2);
    rec.doMULTU(1, 2);
    rec.doDIV(1, 2);
    rec.doDIVU(1, 2);
    rec.doMADD(1, 2);
    rec.doMADDU(1, 2);
    rec.doMSUB(1, 2);
    rec.doMSUBU(1, 2);

    rec.doCVT_S_W(1, 2);
    rec.doADD_S(1, 2, 3);
    rec.doSUB_S(1, 2, 3);
    rec.doMUL_S(1, 2, 3);
    rec.doDIV_S(1, 2, 3);
    rec.doSQRT_S(1, 2);
    rec.doCVT_W_S(1, 2);
    rec.doABS_S(1, 2);
    rec.doMOV_S(1, 2);
    rec.doNEG_S(1, 2);
    rec.doROUND_W_S(1, 2);
    rec.doTRUNC_W_S(1, 2);
    rec.doCEIL_W_S(1, 2);
    rec.doFLOOR_W_S(1, 2);
#endif
}
#else
void recompiler_test()
{

}
#endif