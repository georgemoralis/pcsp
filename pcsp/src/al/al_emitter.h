#include "common_types.h"

#if defined(__i386__) /* gcc */ || defined(_M_IX86) /* msvc */ || defined(_X86_) || defined(__386__) || defined(i386)
struct al_Emitter
{
    al_Emitter() {}

    static AlContext *context;
    static u8        *pointer;

    static u8         delayslot_stack[4];
    static u32        delayslot;

    static void Write1(u8  data) { (*(u8  *)pointer) = data; pointer += 1; }
    static void Write2(u16 data) { (*(u16 *)pointer) = data; pointer += 2; }
    static void Write4(u32 data) { (*(u32 *)pointer) = data; pointer += 4; }
    static void Write8(u64 data) { (*(u64 *)pointer) = data; pointer += 8; }

    enum R32Enum { EAX, ECX, EDX, EBX, ESP, EBP, ESI, EDI };
    enum R16Enum {  AX,  CX,  DX,  BX,  SP,  BP,  SI,  DI };
    enum R8Enum  {  AL,  CL,  DL,  BL,  AH,  CH,  DH,  BH };

    struct R32;
    struct R16;
    struct R8;
    struct V128;

    struct R32_ModRM_SIB_Disp
    {
        int const base;
        int const index;
        int const scale;
        int const offset;

        explicit R32_ModRM_SIB_Disp(int const base, int const index, int const scale, int const offset) : base(base), index(index), scale(scale), offset(offset) {}
    };

    struct R32_ModRM_SIB
    {
        int const base;
        int const index;
        int const scale;

        explicit R32_ModRM_SIB(int const base, int const index, int const scale) : base(base), index(index), scale(scale) {}

        // reg32 + reg32 * scale + offset
        __forceinline R32_ModRM_SIB_Disp operator +(int offset) const
        {
            return R32_ModRM_SIB_Disp(base, index, scale, offset);
        }
    };

    struct R32_ModRM_Disp
    {
        int const base;
        int const offset;

        explicit R32_ModRM_Disp(int const base, int const offset) : base(base), offset(offset) {}
    };

    struct R32_SIB_Disp
    {
        int const index;
        int const scale;
        int const offset;

        explicit R32_SIB_Disp(int const index, int const scale, int const offset) : index(index), scale(scale), offset(offset) {}
    };

    struct R32_SIB
    {
        int const index;
        int scale;

        explicit R32_SIB(int const index, int scale) : index(index), scale(scale) {}

        __forceinline R32_SIB_Disp operator +(int const offset) const
        {
            return R32_SIB_Disp(index, scale, offset);
        }
    };

    template< typename Rxx >
    struct RegisterAccessor
    {
        int const reg;

        explicit RegisterAccessor(int const reg) : reg(reg) {}
    };

    struct R8 : public RegisterAccessor< R8 >
    {
        explicit R8(int const reg) : RegisterAccessor< R8 >(reg) {}
    };

    struct R16 : public RegisterAccessor< R16 >
    {
        explicit R16(int const reg) : RegisterAccessor< R16 >(reg) {}

        operator R8 () const { return R8 (reg); }
    };

    struct R32 : public RegisterAccessor< R32 >
    {
        explicit R32(int const reg) : RegisterAccessor< R32 >(reg) {}

        operator R8 () const { return R8 (reg); }
        operator R16() const { return R16(reg); }

        // reg * scale
        __forceinline R32_SIB operator *(int const scale) const
        {
            switch (scale)
            {
            case 1:
                return R32_SIB(reg, 0);
            case 2:
                return R32_SIB(reg, 1);
            case 4:
                return R32_SIB(reg, 2);
            case 8:
                return R32_SIB(reg, 3);
            }
            return R32_SIB(reg, 0);
        }

        // reg << scale
        __forceinline R32_SIB operator <<(int const scale) const
        {
            return R32_SIB(reg, scale & 3);
        }

        // reg + offset
        __forceinline R32_ModRM_Disp operator +(int const offset) const
        {
            return R32_ModRM_Disp(reg, offset);
        }

        // reg + reg << scale
        __forceinline R32_ModRM_SIB operator +(R32_SIB const &ri) const
        {
            return R32_ModRM_SIB(reg, ri.index, ri.scale);
        }
    };

    struct V128 : public RegisterAccessor< V128 >
    {
        explicit V128(int const reg) : RegisterAccessor< V128 >(reg) {}
    };

    struct Xmm
    {
        __forceinline V128 operator ()(int const reg) { return V128(reg); }
    };

    template< typename Mxx >
    struct EA
    {
        int const base;
        int const index;
        int const scale;
        int const offset;

        EA(                                                                  ) : base(           -1           ), index(           -1          ), scale(  0  ), offset(  0   ) {}
        EA(int const base, int const index, int const scale, int const offset) : base(          base          ), index(         index         ), scale(scale), offset(offset) {}
        EA(R32 const &r                                                      ) : base(r.reg == 5 ? -1 : r.reg ), index(r.reg == 5 ? r.reg : -1), scale(  0  ), offset(  0   ) {}

        __forceinline Mxx operator [](int const ea) const                  { return Mxx(base, index, scale, offset+ea); }

        __forceinline Mxx operator [](R32 const &ea) const                 { return ea.reg == 5 ? Mxx(base, 5, scale, offset) : Mxx(ea.reg, index, scale, offset); } // EBP cannot be a base but can be an index without base

        __forceinline Mxx operator [](R32_ModRM_Disp const &ea) const      { return ea.base == 5 ? Mxx(base, 5, scale, offset+ea.offset) : Mxx(ea.base, index, scale, offset+ea.offset); } // EBP cannot be a base but can be an index without base

        __forceinline Mxx operator [](R32_SIB const &ea) const             { return Mxx(base, ea.index, ea.scale, offset); } // /!\ ESP cannot be an index /!\ 

        __forceinline Mxx operator [](R32_SIB_Disp const &ea) const        { return Mxx(base, ea.index, ea.scale, offset+ea.offset); } // /!\ ESP cannot be an index /!\ 

        __forceinline Mxx operator [](R32_ModRM_SIB const &ea) const       { return Mxx(ea.base, ea.index, ea.scale, offset); } // /!\ ESP cannot be an index or EBP cannot be a base /!\ 

        __forceinline Mxx operator [](R32_ModRM_SIB_Disp const &ea) const  { return Mxx(ea.base, ea.index, ea.scale, offset+ea.offset); } // /!\ ESP cannot be an index or EBP cannot be a base /!\ 
    };

    struct M8 : public EA< M8 >
    {
        M8(                                                                  ) : EA< M8 >( -1 ,  -1  ,   0  ,   0    ) {}
        M8(int const base, int const index, int const scale, int const offset) : EA< M8 >(base, index, scale, offset ) {}
        M8(R32 const &r                                                      ) : EA< M8 >(            r              ) {}
        M8(int const offset                                                  ) : EA< M8 >( -1 ,  -1  ,   0  , offset ) {}
        M8(u8 const *ea                                                      ) : EA< M8 >( -1 ,  -1  ,   0  , (int)ea) {}
        M8(s8 const *ea                                                      ) : EA< M8 >( -1 ,  -1  ,   0  , (int)ea) {}
    };

    struct M16 : public EA< M16 >
    {
        M16(                                                                  ) : EA< M16 >( -1 ,  -1  ,   0  ,   0    ) {}
        M16(int const base, int const index, int const scale, int const offset) : EA< M16 >(base, index, scale, offset ) {}
        M16(R32 const &r                                                      ) : EA< M16 >(            r              ) {}
        M16(int const offset                                                  ) : EA< M16 >( -1 ,  -1  ,   0  , offset ) {}
        M16(u16 const *ea                                                     ) : EA< M16 >( -1 ,  -1  ,   0  , (int)ea) {}
        M16(s16 const *ea                                                     ) : EA< M16 >( -1 ,  -1  ,   0  , (int)ea) {}

        __forceinline operator M8 () const { return M8 (base, index, scale, offset); }
    };

    struct M32 : public EA< M32 >
    {
        M32(                                                                  ) : EA< M32 >( -1 ,  -1  ,   0  ,   0    ) {}
        M32(int const base, int const index, int const scale, int const offset) : EA< M32 >(base, index, scale, offset ) {}
        M32(R32 const &r                                                      ) : EA< M32 >(            r              ) {}
        M32(int const offset                                                  ) : EA< M32 >( -1 ,  -1  ,   0  , offset ) {}
        M32(u32 const *ea                                                     ) : EA< M32 >( -1 ,  -1  ,   0  , (int)ea) {}
        M32(s32 const *ea                                                     ) : EA< M32 >( -1 ,  -1  ,   0  , (int)ea) {}

        __forceinline operator M8 () const { return M8 (base, index, scale, offset); }
        __forceinline operator M16() const { return M16(base, index, scale, offset); }
    };

    struct M128 : public EA< M128 >
    {
        M128(                                                                  ) : EA< M128 >( -1 ,  -1  ,   0  ,   0    ) {}
        M128(int const base, int const index, int const scale, int const offset) : EA< M128 >(base, index, scale, offset ) {}
        M128(R32 const &r                                                      ) : EA< M128 >(               r           ) {}
        M128(int const offset                                                  ) : EA< M128 >( -1 ,  -1  ,   0  , offset ) {}
        M128(u32 const *ea                                                     ) : EA< M128 >( -1 ,  -1  ,   0  , (int)ea) {}
        M128(s32 const *ea                                                     ) : EA< M128 >( -1 ,  -1  ,   0  , (int)ea) {}

        __forceinline M32 operator [](int const i) const { return M32(base, index, scale, offset+4*i); }
    };

    static __forceinline void WriteModRegRM(int const mod, int const reg, int const rm)  { Write1(u8(mod << 6) | u8(reg << 3) | u8(rm));                          }
    static __forceinline void WriteSIB(int const scale, int const index, int const base) { Write1(u8(scale << 6) | u8(index << 3) | u8(base));                    }
    static __forceinline void WriteDisp8(int const offset)                               { Write1(u8(offset));                                                    }
    static __forceinline void WriteDisp32(int const offset)                              { Write4(offset);                                                        }
    static __forceinline void WriteDisp(int const mod, int const offset)                 { if (mod == 1) Write1(offset & 255); else if (mod == 2) Write4(offset); }

    static __forceinline void WriteM32(int const reg, M32 const &m)
    {
        if (m.base < 0)
        {
            if (m.index < 0)
            {
                WriteModRegRM(0, reg, 5);
            }
            else
            {
                WriteModRegRM(0, reg, 4);
                WriteSIB(m.scale, (m.index < 0 ? 4 : m.index), 5);
            }
            WriteDisp32(m.offset);
        }
        else
        {
            int mod = (!m.offset && m.base != 5) ? 0 : ((1 + u32(m.offset >> 7)) < 2) ? 1 : 2;
            WriteModRegRM(mod, reg, m.base);
            if (m.index >= 0 || m.base == 4)
            {
                WriteSIB(m.scale, (m.index < 0 ? 4 : m.index), m.base);
            }
            WriteDisp(mod, m.offset);
        }
    }

    static __forceinline void WriteM16(int const reg, M16 const &m)
    {
        WriteM32(reg, M32(m.base, m.index, m.scale, m.offset)); 
    }

    static __forceinline void WriteM8(int const reg, M8 const &m)
    {
        WriteM32(reg, M32(m.base, m.index, m.scale, m.offset)); 
    }

    static __forceinline void WriteM128(int const reg, M128 const &m)
    {
        WriteM32(reg, M32(m.base, m.index, m.scale, m.offset)); 
    }


    //////////////////////////////////////////////////////////////////////////

    enum AluEnum { ADD, OR, ADC, SBB, AND, SUB, XOR, CMP };

    struct Alu
    {
        int const op1;

        Alu(int const op1) : op1(op1)
        {}

        //01 /r 	ADD r32, r32 	    Add r32 to r32
        __forceinline void operator()(R32 const &d, R32 const &s)
        {
            Write1((op1<<3)+0x01);
            WriteModRegRM(3, s.reg, d.reg);
        }

        //01 /r 	ADD m32, r32 	    Add r32 to m32
        __forceinline void operator()(M32 const &m, R32 const &r)
        {
            Write1((op1<<3)+0x01);
            WriteM32(r.reg, m);
        }

        //03 /r 	ADD r32, m32 	    Add m32 to r32
        __forceinline void operator()(R32 const &r, M32 const &m)
        {
            Write1((op1<<3)+0x03);
            WriteM32(r.reg, m);
        }

        //05 id 	ADD EAX, imm32 	    Add imm32 to EAX
        //81 /0 id 	ADD r32, imm32 	    Add imm32 to r32
        //83 /0 ib 	ADD r32, imm8 	    Add sign-extended imm8 to r32
        __forceinline void operator()(R32 const &r, int immediate)
        {
            if ((u32(immediate>>7)+1)<2)
            {
                Write1(0x83);
                WriteModRegRM(3, op1, r.reg);
                Write1(immediate);
            }
            else
            {
                Write1(r.reg ? 0x81 : (op1<<3)+0x05);
                if (r.reg)
                {
                    WriteModRegRM(3, op1, r.reg);
                }
                Write4(immediate);
            }
        }

        //81 /0 id 	ADD m32, imm32 	    Add imm32 to m32
        //83 /0 ib 	ADD m32, imm8 	    Add sign-extended imm8 to m32
        __forceinline void operator()(M32 const &m, int immediate)
        {
            if ((u32(immediate>>7)+1)<2)
            {
                Write1(0x83);
                WriteM32(op1, m);
                Write1(immediate);
            }
            else
            {
                Write1(0x81);
                WriteM32(op1, m);
                Write4(immediate);
            }
        }
    };

    struct Add : public Alu { Add() : Alu(ADD) {} };
    struct Or  : public Alu { Or () : Alu(OR ) {} };
    struct Adc : public Alu { Adc() : Alu(ADC) {} };
    struct Sbb : public Alu { Sbb() : Alu(SBB) {} };
    struct And : public Alu { And() : Alu(AND) {} };
    struct Sub : public Alu { Sub() : Alu(SUB) {} };
    struct Xor : public Alu { Xor() : Alu(XOR) {} };
    struct Cmp : public Alu { Cmp() : Alu(CMP) {} };

    enum RsuEnum { ROL, ROR, RCL, RCR, SHL, SHR, SAL, SAR };

    struct Rsu
    {
        int const op1;

        Rsu(int const op1) : op1(op1)
        {}

        //D3 /0     ROL r32, CL 	    Rotate 32 bits r32 left CL times. 	
        __forceinline void operator()(R32 const &r)
        {
            Write1(0xD3);
            WriteModRegRM(3, op1, r.reg);
        }

        //D3 /0     ROL r32, CL 	    Rotate 32 bits m32 left CL times. 	
        __forceinline void operator()(M32 const &m)
        {
            Write1(0xD3);
            WriteM32(op1, m);
        }

        //C1 /0 ib  ROL r32, imm8 	    Rotate 32 bits r32 left imm8 times. 	
        //D1 /0     ROL r32, 1 	        Rotate 32 bits r32 left once. 	
        __forceinline void operator()(R32 const &r, int immediate)
        {
            Write1(immediate == 1 ? 0xD1 : 0xC1);
            WriteModRegRM(3, op1, r.reg);
            if (immediate != 1)
            {
                Write1(immediate);
            }
        }

        //C1 /0 ib  ROL m32, imm8 	    Rotate 32 bits m32 left imm8 times. 	
        //D1 /0     ROL m32, 1 	        Rotate 32 bits m32 left once. 	
        __forceinline void operator()(M32 const &m, int immediate)
        {
            Write1(immediate == 1 ? 0xD1 : 0xC1);
            WriteM32(op1, m);
            if (immediate != 1)
            {
                Write1(immediate);
            }
        }
    };

    struct Rol : public Rsu { Rol() : Rsu(ROL) {} };
    struct Ror : public Rsu { Ror() : Rsu(ROR) {} };
    struct Rcl : public Rsu { Rcl() : Rsu(RCL) {} };
    struct Rcr : public Rsu { Rcr() : Rsu(RCR) {} };
    struct Shl : public Rsu { Shl() : Rsu(SHL) {} };
    struct Shr : public Rsu { Shr() : Rsu(SHR) {} };
    struct Sal : public Rsu { Sal() : Rsu(SAL) {} };
    struct Sar : public Rsu { Sar() : Rsu(SAR) {} };

    struct Test
    {
        Test()
        {}

        //85 /r 	TEST r32,r32 	    AND r32 with r/m32; set SF, ZF, PF according to result.
        __forceinline void operator()(R32 const &d, R32 const &s)
        {
            Write1(0x85);
            WriteModRegRM(3, s.reg, d.reg);
        }

        //A9 id 	TEST EAX,imm32 	    AND imm32 with EAX; set SF, ZF, PF according to result.
        //F7 /0 id 	TEST r32,imm32 	    AND imm32 with r32; set SF, ZF, PF according to result.
        __forceinline void operator()(R32 const &r, int const immediate)
        {
            if (r.reg)
            {
                Write1(0xF7);
                WriteModRegRM(3, 0, r.reg);
            }
            else
            {
                Write1(0xA9);
            }
            Write4(immediate);
        }

        //85 /r 	TEST m32,r32 	    AND r32 with m32; set SF, ZF, PF according to result.
        __forceinline void operator()(M32 const &m, R32 const &r)
        {
            Write1(0x85);
            WriteM32(r.reg, m);
        }

        //F7 /0 id 	TEST m32,imm32 	    AND imm32 with m32; set SF, ZF, PF according to result.
        __forceinline void operator()(M32 const &m, int const immediate)
        {
            Write1(0xF7);
            WriteM32(0, m);
            Write4(immediate);
        }
    };

    struct NXX
    {
        int const op;

        NXX(int const op) : op(op)
        {}

        //F7 /2 	NOT r32 	        Reverse each bit of r32.
        //F7 /3 	NEG r32 	        Two's complement negate r32.
        __forceinline void operator()(R32 const &r)
        {
            Write1(0xF7);
            WriteModRegRM(3, op+2, r.reg);
        }

#if 0
        //F6 /2 	NOT m8 	            Reverse each bit of m32.
        //F6 /3 	NEG m8 	            Two's complement negate m32.
        __forceinline void operator()(M8 const &d)
        {
            Write1(0xF6);
            WriteM8(op+2, d);
        }
#endif
        //F7 /2 	NOT m32 	        Reverse each bit of m32.
        //F7 /3 	NEG m32 	        Two's complement negate m32.
        __forceinline void operator()(M16 const &m)
        {
            Write1(0xF7);
            WriteM16(op+2, m);
        }
    };

    struct Not : public NXX { Not() : NXX(0) {} };
    struct Neg : public NXX { Neg() : NXX(1) {} };

    struct ShXd
    {
        int const dir;

        ShXd(int const dir) : dir(dir)
        {}

        //0F A4 	SHLD r/m32, r32, imm8 	Shift r/m32 to left imm8 places while shifting bits from r32 in from the right.
        //0F A5 	SHLD r/m32, r32, CL 	Shift r/m32 to left CL places while shifting bits from r32 in from the right.

        //0F A5 	SHLD r32, r32, CL 	Shift r32 to left CL places while shifting bits from r32 in from the right.
        __forceinline void operator()(R32 const &d, R32 const &s)
        {
            Write2(dir ? 0xAD0F : 0xA50F);
            WriteModRegRM(3, s.reg, d.reg);
        }

        //0F A5 	SHLD m32, r32, CL 	Shift m32 to left CL places while shifting bits from r32 in from the right.
        __forceinline void operator()(M32 const &m, R32 const &s)
        {
            Write2(dir ? 0xAD0F : 0xA50F);
            WriteM32(s.reg, m);
        }

        //0F A4 	SHLD r32, r32, imm8 Shift r32 to left imm8 places while shifting bits from r32 in from the right.
        __forceinline void operator()(R32 const &d, R32 const &s, int immediate)
        {
            Write2(dir ? 0xAC0F : 0xA40F);
            WriteModRegRM(3, s.reg, d.reg);
            Write1(immediate);
        }

        //0F A4 	SHLD m32, r32, imm8 Shift m32 to left imm8 places while shifting bits from r32 in from the right.
        __forceinline void operator()(M32 const &m, R32 const &r, int immediate)
        {
            Write2(dir ? 0xAC0F : 0xA40F);
            WriteM32(r.reg, m);
            Write1(immediate);
        }
    };

    struct Shld : public ShXd { Shld() : ShXd(0) {} };
    struct Shrd : public ShXd { Shrd() : ShXd(1) {} };

    struct Mov
    {
        //89 /r 	MOV r32,r32 	    Move r32 to r32.
        __forceinline void operator()(R32 const &d, R32 const &s)
        {
            Write1(0x89);
            WriteModRegRM(3, s.reg, d.reg);
        }

        //8B /r 	MOV r32,m32 	    Move m32 to r32.
        //A1 	    MOV EAX,moffs32	    Move 32-bit value at (ds:offset) to EAX.
        __forceinline void operator()(R32 const &r, M32 const &m)
        {
            if (!r.reg && m.base == -1 && m.index == -1)
            {
                Write1(0xA1);
                Write4(m.offset);
            }
            else
            {
                Write1(0x8B);
                WriteM32(r.reg, m);
            }
        }

        //8B /r 	MOV r16,m16 	    Move m16 to r16.
        //A1 	    MOV AX,moffs16	    Move 16-bit value at (ds:offset) to AX.
        __forceinline void operator()(R16 const &r, M16 const &m)
        {
            Write1(0x66);
            if (!r.reg && m.base == -1 && m.index == -1)
            {
                Write1(0xA1);
                Write4(m.offset);
            }
            else
            {
                Write1(0x8B);
                WriteM16(r.reg, m);
            }
        }

        //8A /r 	MOV r8,m8 	        Move m8 to r8.
        //A0 	    MOV AL,moffs8	    Move 8-bit value at (ds:offset) to AL.
        __forceinline void operator()(R8 const &r, M8 const &m)
        {
            if (!r.reg && m.base == -1 && m.index == -1)
            {
                Write1(0xA0);
                Write4(m.offset);
            }
            else
            {
                Write1(0x8A);
                WriteM8(r.reg, m);
            }
        }

        //89 /r 	MOV m32,r32 	    Move r32 to m32.
        //A3 	    MOV moffs32,EAX	    Move EAX to (ds:offset).
        __forceinline void operator()(M32 const &m, R32 const &r)
        {
            if (!r.reg && m.base == -1 && m.index == -1)
            {
                Write1(0xA3);
                Write4(m.offset);
            }
            else
            {
                Write1(0x89);
                WriteM32(r.reg, m);
            }
        }

        //89 /r 	MOV m16,r16 	    Move r16 to m16.
        //A3 	    MOV moffs16,AX	    Move AX to (ds:offset).
        __forceinline void operator()(M16 const &m, R16 const &r)
        {
            Write1(0x66);
            if (!r.reg && m.base == -1 && m.index == -1)
            {
                Write1(0xA3);
                Write4(m.offset);
            }
            else
            {
                Write1(0x89);
                WriteM16(r.reg, m);
            }
        }

        //88 /r 	MOV m8,r8 	        Move r8 to m8.
        //A2 	    MOV moffs8,AL	    Move AL to (ds:offset).
        __forceinline void operator()(M8 const &m, R8 const &r)
        {
            if (!r.reg && m.base == -1 && m.index == -1)
            {
                Write1(0xA2);
                Write4(m.offset);
            }
            else
            {
                Write1(0x88);
                WriteM8(r.reg, m);
            }
        }

        //B8+ rd 	MOV r32,imm32 	    Move imm32 to r32.
        __forceinline void operator()(R32 const &r, int const immediate)
        {
            Write1(0xB8|r.reg);
            Write4(immediate);
        }

        //C7 /0 	MOV m32,imm32	    Move imm32 to m32.
        __forceinline void operator()(M32 const &m, int const immediate)
        {
            Write1(0xC7);
            WriteM32(0, m);
            Write4(immediate);
        }

        //C7 /0 	MOV m16,imm32	    Move imm32 to r/m32.
        __forceinline void operator()(M16 const &m, int const immediate)
        {
            Write1(0xC7);
            WriteM16(0, m);
            Write2(immediate);
        }

        //C6 /0 	MOV m8,imm8	        Move imm8 to r/m8.
        __forceinline void operator()(M8 const &m, int const immediate)
        {
            Write1(0xC6);
            WriteM8(0, m);
            Write1(immediate);
        }
    };

    struct Lea
    {
        //8D /r 	LEA r32,m32 	    Store effective address for m32 in register r32.
        __forceinline void operator()(R32 const &r, M32 const &m)
        {
            Write1(0x8D);
            WriteM32(r.reg, m);
        }
    };

    struct MovXx
    {
        int const ext;

        MovXx(int const ext) : ext(ext)
        {}

        //0F B6 /r 	MOVZX r32,r8 	    Move byte to doubleword with zero-extension.
        //0F BE /r 	MOVSX r32,r8 	    Move byte to doubleword with sign-extension.
        __forceinline void operator()(R32 const &d, R8 const &s)
        {
            Write2(ext ? 0xBE0F : 0xB60F);
            WriteModRegRM(3, s.reg, d.reg);
        }

        //0F B7 /r 	MOVZX r32,r16 	    Move word to doubleword with zero-extension.
        //0F BF /r 	MOVSX r32,r16 	    Move word to doubleword with sign-extension.
        __forceinline void operator()(R32 const &d, R16 const &s)
        {
            Write2(ext ? 0xBF0F : 0xB70F);
            WriteModRegRM(3, s.reg, d.reg);
        }

        //0F B6 /r 	MOVZX r32,m8 	    Move byte to doubleword with zero-extension.
        //0F BE /r 	MOVSX r32,m8 	    Move byte to doubleword with sign-extension.
        __forceinline void operator()(R32 const &r, M8 const &m)
        {
            Write2(ext ? 0xBE0F : 0xB60F);
            WriteM8(r.reg, m);
        }

        //0F B7 /r 	MOVZX r32,m16 	    Move word to doubleword with zero-extension.
        //0F BF /r 	MOVSX r32,m16 	    Move word to doubleword with sign-extension.
        __forceinline void operator()(R32 const &r, M16 const &m)
        {
            Write2(ext ? 0xBF0F : 0xB70F);
            WriteM16(r.reg, m);
        }
    };

    struct Movzx : public MovXx { Movzx() : MovXx(0) {} };
    struct Movsx : public MovXx { Movsx() : MovXx(1) {} };

    struct Push
    {
        Push()
        {}

        //50+rd 	PUSH r32 	        Push r32.
        __forceinline void operator()(R32 const &r)
        {
            Write1(0x50+r.reg);
        }

        //FF /6 	PUSH m32 	        Push m32.
        __forceinline void operator()(M32 const &m)
        {
            Write1(0xFF);
            WriteM32(6, m);
        }

        //68 	    PUSH imm32 	        Push imm32.
        __forceinline void operator()(int const immediate)
        {
            Write1(0x68);
            Write4(immediate);
        }
    };

    struct Pop
    {
        Pop()
        {}

        //58+rd 	POP r32             Pop top of stack into r32; increment stack pointer.
        __forceinline void operator()(R32 const &r)
        {
            Write1(0x58+r.reg);
        }

        //8F /0 	POP m32 	        Pop top of stack into m32; increment stack pointer.
        __forceinline void operator()(M32 const &m)
        {
            Write1(0x8F);
            WriteM32(0, m);
        }
    };

    struct Pushad
    {
        Pushad()
        {}

        //60 	    PUSHAD 	            Push EAX, ECX, EDX, EBX, original ESP, EBP, ESI, and EDI.
        __forceinline void operator()()
        {
            Write1(0x60);
        }
    };

    struct Popad
    {
        Popad()
        {}

        //61        POPAD 	            Pop EDI, ESI, EBP, EBX, EDX, ECX, and EAX.
        __forceinline void operator()()
        {
            Write1(0x61);
        }
    };

    struct Pushf
    {
        Pushf()
        {}

        //9C 	    PUSHFD 	            Push EFLAGS.
        __forceinline void operator()() { Write2(0x9C66); }
    };

    struct Popf
    {
        Popf()
        {}

        //9D        POPFD 	            Pop top of stack into EFLAGS.
        __forceinline void operator()() { Write2(0x9D66); }
    };

    struct Lahf
    {
        Lahf() {}

        //9F 	    LAHF 	            Load: AH = EFLAGS(SF:ZF:0:AF:0:PF:1:CF).
        __forceinline void operator()() { Write1(0x9F); }
    };

    struct Sahf
    {
        Sahf() {}

        //9E 	    SAHF 	            Load SF, ZF, AF, PF, and CF from AH into EFLAGS register.
        __forceinline void operator()() { Write1(0x9E); }
    };

    enum CcEnum
    {
        O,
        NO,
        C, B = C, NAE = C,
        NC, NB = NC, AE = NC,
        Z, E = Z,
        NZ, NE = NZ,
        BE, NA = BE,
        A, NBE = A,
        S, NS,
        P, PE = P,
        NP, PO = NP,
        L, NGE = L,
        GE, NL = GE,
        LE, NG = LE,
        G, NLE = G
    };

    struct CmovXX
    {
        int const cc;

        CmovXX(int const cc) : cc(cc)
        {}

        //0F 40 	CMOVO r32, r32 	    Move if overflow (OF=1).
        //0F 41 	CMOVNO r32, r32 	Move if not overflow (OF=0).
        //0F 42 	CMOVB r32, r32 	    Move if below (CF=1).
        //0F 42 	CMOVC r32, r32 	    Move if carry (CF=1).
        //0F 42 	CMOVNAE r32, r32 	Move if not above or equal (CF=1).
        //0F 43 	CMOVNB r32, r32 	Move if not below (CF=0).
        //0F 43 	CMOVNC r32, r32 	Move if not carry (CF=0).
        //0F 43 	CMOVAE r32, r32 	Move if above or equal (CF=0).
        //0F 44 	CMOVE r32, r32 	    Move if equal (ZF=1).
        //0F 44 	CMOVZ r32, r32 	    Move if zero (ZF=1).
        //0F 45 	CMOVNZ r32, r32 	Move if not zero (ZF=0).
        //0F 45 	CMOVNE r32, r32 	Move if not equal (ZF=0).
        //0F 46 	CMOVBE r32, r32 	Move if below or equal (CF=1 or ZF=1).
        //0F 46 	CMOVNA r32, r32 	Move if not above (CF=1 or ZF=1).
        //0F 47 	CMOVNBE r32, r32 	Move if not below or equal (CF=0 and ZF=0).
        //0F 47 	CMOVA r32, r32 	    Move if above (CF=0 and ZF=0).
        //0F 48 	CMOVS r32, r32 	    Move if sign (SF=1).
        //0F 49 	CMOVNS r32, r32 	Move if not sign (SF=0).
        //0F 4A 	CMOVP r32, r32 	    Move if parity (PF=1).
        //0F 4A 	CMOVPE r32, r32 	Move if parity even (PF=1).
        //0F 4B 	CMOVPO r32, r32 	Move if parity odd (PF=0).
        //0F 4B 	CMOVNP r32, r32 	Move if not parity (PF=0).
        //0F 4C 	CMOVL r32, r32 	    Move if less (SF<>OF).
        //0F 4C 	CMOVNGE r32, r32 	Move if not greater or equal (SF<>OF).
        //0F 4D 	CMOVGE r32, r32 	Move if greater or equal (SF=OF).
        //0F 4D 	CMOVNL r32, r32 	Move if not less (SF=OF).
        //0F 4E 	CMOVLE r32, r32 	Move if less or equal (ZF=1 or SF<>OF).
        //0F 4E 	CMOVNG r32, r32 	Move if not greater (ZF=1 or SF<>OF).
        //0F 4F 	CMOVG r32, r32 	    Move if greater (ZF=0 and SF=OF).
        //0F 4F 	CMOVNLE r32, r32 	Move if not less or equal (ZF=0 and SF=OF).
        __forceinline void operator()(R32 const &d, R32 const &s)
        {
            Write2(0x400F+(cc<<8));
            WriteModRegRM(3, s.reg, d.reg);
        }

        //0F 40 	CMOVO r32, m32 	    Move if overflow (OF=1).
        //0F 41 	CMOVNO r32, m32 	Move if not overflow (OF=0).
        //0F 42 	CMOVB r32, m32 	    Move if below (CF=1).
        //0F 42 	CMOVC r32, m32 	    Move if carry (CF=1).
        //0F 42 	CMOVNAE r32, m32 	Move if not above or equal (CF=1).
        //0F 43 	CMOVNB r32, m32 	Move if not below (CF=0).
        //0F 43 	CMOVNC r32, m32 	Move if not carry (CF=0).
        //0F 43 	CMOVAE r32, m32 	Move if above or equal (CF=0).
        //0F 44 	CMOVE r32, m32 	    Move if equal (ZF=1).
        //0F 44 	CMOVZ r32, m32 	    Move if zero (ZF=1).
        //0F 45 	CMOVNZ r32, m32 	Move if not zero (ZF=0).
        //0F 45 	CMOVNE r32, m32 	Move if not equal (ZF=0).
        //0F 46 	CMOVBE r32, m32 	Move if below or equal (CF=1 or ZF=1).
        //0F 46 	CMOVNA r32, m32 	Move if not above (CF=1 or ZF=1).
        //0F 47 	CMOVNBE r32, m32 	Move if not below or equal (CF=0 and ZF=0).
        //0F 47 	CMOVA r32, m32 	    Move if above (CF=0 and ZF=0).
        //0F 48 	CMOVS r32, m32 	    Move if sign (SF=1).
        //0F 49 	CMOVNS r32, m32 	Move if not sign (SF=0).
        //0F 4A 	CMOVP r32, m32 	    Move if parity (PF=1).
        //0F 4A 	CMOVPE r32, m32 	Move if parity even (PF=1).
        //0F 4B 	CMOVPO r32, m32 	Move if parity odd (PF=0).
        //0F 4B 	CMOVNP r32, m32 	Move if not parity (PF=0).
        //0F 4C 	CMOVL r32, m32 	    Move if less (SF<>OF).
        //0F 4C 	CMOVNGE r32, m32 	Move if not greater or equal (SF<>OF).
        //0F 4D 	CMOVGE r32, m32 	Move if greater or equal (SF=OF).
        //0F 4D 	CMOVNL r32, m32 	Move if not less (SF=OF).
        //0F 4E 	CMOVLE r32, m32 	Move if less or equal (ZF=1 or SF<>OF).
        //0F 4E 	CMOVNG r32, m32 	Move if not greater (ZF=1 or SF<>OF).
        //0F 4F 	CMOVG r32, m32 	    Move if greater (ZF=0 and SF=OF).
        //0F 4F 	CMOVNLE r32, m32 	Move if not less or equal (ZF=0 and SF=OF).
        __forceinline void operator()(R32 const &r, M32 const &m)
        {
            Write2(0x400F+(cc<<8));
            WriteM16(r.reg, m);
        }
    };

    struct Cmovo   : public CmovXX { Cmovo  () : CmovXX(O  ) {} };
    struct Cmovno  : public CmovXX { Cmovno () : CmovXX(NO ) {} };
    struct Cmovb   : public CmovXX { Cmovb  () : CmovXX(B  ) {} };
    struct Cmovc   : public CmovXX { Cmovc  () : CmovXX(C  ) {} };
    struct Cmovnae : public CmovXX { Cmovnae() : CmovXX(NAE) {} };
    struct Cmovnb  : public CmovXX { Cmovnb () : CmovXX(NB ) {} };
    struct Cmovnc  : public CmovXX { Cmovnc () : CmovXX(NC ) {} };
    struct Cmovae  : public CmovXX { Cmovae () : CmovXX(AE ) {} };
    struct Cmove   : public CmovXX { Cmove  () : CmovXX(E  ) {} };
    struct Cmovz   : public CmovXX { Cmovz  () : CmovXX(Z  ) {} };
    struct Cmovnz  : public CmovXX { Cmovnz () : CmovXX(NZ ) {} };
    struct Cmovne  : public CmovXX { Cmovne () : CmovXX(NE ) {} };
    struct Cmovbe  : public CmovXX { Cmovbe () : CmovXX(C  ) {} };
    struct Cmovna  : public CmovXX { Cmovna () : CmovXX(NA ) {} };
    struct Cmovnbe : public CmovXX { Cmovnbe() : CmovXX(NBE) {} };
    struct Cmova   : public CmovXX { Cmova  () : CmovXX(A  ) {} };
    struct Cmovs   : public CmovXX { Cmovs  () : CmovXX(S  ) {} };
    struct Cmovns  : public CmovXX { Cmovns () : CmovXX(NS ) {} };
    struct Cmovp   : public CmovXX { Cmovp  () : CmovXX(P  ) {} };
    struct Cmovpe  : public CmovXX { Cmovpe () : CmovXX(PE ) {} };
    struct Cmovpo  : public CmovXX { Cmovpo () : CmovXX(PO ) {} };
    struct Cmovnp  : public CmovXX { Cmovnp () : CmovXX(NP ) {} };
    struct Cmovl   : public CmovXX { Cmovl  () : CmovXX(L  ) {} };
    struct Cmovnge : public CmovXX { Cmovnge() : CmovXX(NGE) {} };
    struct Cmovge  : public CmovXX { Cmovge () : CmovXX(GE ) {} };
    struct Cmovnl  : public CmovXX { Cmovnl () : CmovXX(NL ) {} };
    struct Cmovle  : public CmovXX { Cmovle () : CmovXX(LE ) {} };
    struct Cmovng  : public CmovXX { Cmovng () : CmovXX(NG ) {} };
    struct Cmovg   : public CmovXX { Cmovg  () : CmovXX(G  ) {} };
    struct Cmovnle : public CmovXX { Cmovnle() : CmovXX(NLE) {} };

    struct SetXX
    {
        int const cc;

        SetXX(int const cc) : cc(cc)
        {}

        //0F 40 	SetO r8, r8 	    Set byte if overflow (OF=1).
        //0F 41 	SetNO r8, r8 	    Set byte if not overflow (OF=0).
        //0F 42 	SetB r8, r8 	    Set byte if below (CF=1).
        //0F 42 	SetC r8, r8 	    Set byte if carry (CF=1).
        //0F 42 	SetNAE r8, r8 	    Set byte if not above or equal (CF=1).
        //0F 43 	SetNB r8, r8 	    Set byte if not below (CF=0).
        //0F 43 	SetNC r8, r8 	    Set byte if not carry (CF=0).
        //0F 43 	SetAE r8, r8 	    Set byte if above or equal (CF=0).
        //0F 44 	SetE r8, r8 	    Set byte if equal (ZF=1).
        //0F 44 	SetZ r8, r8 	    Set byte if zero (ZF=1).
        //0F 45 	SetNZ r8, r8 	    Set byte if not zero (ZF=0).
        //0F 45 	SetNE r8, r8 	    Set byte if not equal (ZF=0).
        //0F 46 	SetBE r8, r8 	    Set byte if below or equal (CF=1 or ZF=1).
        //0F 46 	SetNA r8, r8 	    Set byte if not above (CF=1 or ZF=1).
        //0F 47 	SetNBE r8, r8 	    Set byte if not below or equal (CF=0 and ZF=0).
        //0F 47 	SetA r8, r8 	    Set byte if above (CF=0 and ZF=0).
        //0F 48 	SetS r8, r8 	    Set byte if sign (SF=1).
        //0F 49 	SetNS r8, r8 	    Set byte if not sign (SF=0).
        //0F 4A 	SetP r8, r8 	    Set byte if parity (PF=1).
        //0F 4A 	SetPE r8, r8 	    Set byte if parity even (PF=1).
        //0F 4B 	SetPO r8, r8 	    Set byte if parity odd (PF=0).
        //0F 4B 	SetNP r8, r8 	    Set byte if not parity (PF=0).
        //0F 4C 	SetL r8, r8 	    Set byte if less (SF<>OF).
        //0F 4C 	SetNGE r8, r8 	    Set byte if not greater or equal (SF<>OF).
        //0F 4D 	SetGE r8, r8 	    Set byte if greater or equal (SF=OF).
        //0F 4D 	SetNL r8, r8  	    Set byte if not less (SF=OF).
        //0F 4E 	SetLE r8, r8 	    Set byte if less or equal (ZF=1 or SF<>OF).
        //0F 4E 	SetNG r8, r8 	    Set byte if not greater (ZF=1 or SF<>OF).
        //0F 4F 	SetG r8, r8 	    Set byte if greater (ZF=0 and SF=OF).
        //0F 4F 	SetNLE r8, r8 	    Set byte if not less or equal (ZF=0 and SF=OF).
        __forceinline void operator()(R8 const &r)
        {
            Write2(0x900F+(cc<<8));
            WriteModRegRM(3, 0, r.reg);
        }

        //0F 40 	SetO r8, m8 	    Set byte if overflow (OF=1).
        //0F 41 	SetNO r8, m8 	    Set byte if not overflow (OF=0).
        //0F 42 	SetB r8, m8 	    Set byte if below (CF=1).
        //0F 42 	SetC r8, m8 	    Set byte if carry (CF=1).
        //0F 42 	SetNAE r8, m8 	    Set byte if not above or equal (CF=1).
        //0F 43 	SetNB r8, m8 	    Set byte if not below (CF=0).
        //0F 43 	SetNC r8, m8 	    Set byte if not carry (CF=0).
        //0F 43 	SetAE r8, m8 	    Set byte if above or equal (CF=0).
        //0F 44 	SetE r8, m8 	    Set byte if equal (ZF=1).
        //0F 44 	SetZ r8, m8 	    Set byte if zero (ZF=1).
        //0F 45 	SetNZ r8, m8 	    Set byte if not zero (ZF=0).
        //0F 45 	SetNE r8, m8 	    Set byte if not equal (ZF=0).
        //0F 46 	SetBE r8, m8 	    Set byte if below or equal (CF=1 or ZF=1).
        //0F 46 	SetNA r8, m8 	    Set byte if not above (CF=1 or ZF=1).
        //0F 47 	SetNBE r8, m8 	    Set byte if not below or equal (CF=0 and ZF=0).
        //0F 47 	SetA r8, m8 	    Set byte if above (CF=0 and ZF=0).
        //0F 48 	SetS r8, m8 	    Set byte if sign (SF=1).
        //0F 49 	SetNS r8, m8 	    Set byte if not sign (SF=0).
        //0F 4A 	SetP r8, m8 	    Set byte if parity (PF=1).
        //0F 4A 	SetPE r8, m8 	    Set byte if parity even (PF=1).
        //0F 4B 	SetPO r8, m8 	    Set byte if parity odd (PF=0).
        //0F 4B 	SetNP r8, m8 	    Set byte if not parity (PF=0).
        //0F 4C 	SetL r8, m8 	    Set byte if less (SF<>OF).
        //0F 4C 	SetNGE r8, m8 	    Set byte if not greater or equal (SF<>OF).
        //0F 4D 	SetGE r8, m8 	    Set byte if greater or equal (SF=OF).
        //0F 4D 	SetNL r8, m8 	    Set byte if not less (SF=OF).
        //0F 4E 	SetLE r8, m8 	    Set byte if less or equal (ZF=1 or SF<>OF).
        //0F 4E 	SetNG r8, m8 	    Set byte if not greater (ZF=1 or SF<>OF).
        //0F 4F 	SetG r8, m8 	    Set byte if greater (ZF=0 and SF=OF).
        //0F 4F 	SetNLE r8, m8 	    Set byte if not less or equal (ZF=0 and SF=OF).
        __forceinline void operator()(M8 const &m)
        {
            Write2(0x900F+(cc<<8));
            WriteM8(0, m);
        }
    };

    struct Seto   : public SetXX { Seto  () : SetXX(O  ) {} };
    struct Setno  : public SetXX { Setno () : SetXX(NO ) {} };
    struct Setb   : public SetXX { Setb  () : SetXX(B  ) {} };
    struct Setc   : public SetXX { Setc  () : SetXX(C  ) {} };
    struct Setnae : public SetXX { Setnae() : SetXX(NAE) {} };
    struct Setnb  : public SetXX { Setnb () : SetXX(NB ) {} };
    struct Setnc  : public SetXX { Setnc () : SetXX(NC ) {} };
    struct Setae  : public SetXX { Setae () : SetXX(AE ) {} };
    struct Sete   : public SetXX { Sete  () : SetXX(E  ) {} };
    struct Setz   : public SetXX { Setz  () : SetXX(Z  ) {} };
    struct Setnz  : public SetXX { Setnz () : SetXX(NZ ) {} };
    struct Setne  : public SetXX { Setne () : SetXX(NE ) {} };
    struct Setbe  : public SetXX { Setbe () : SetXX(C  ) {} };
    struct Setna  : public SetXX { Setna () : SetXX(NA ) {} };
    struct Setnbe : public SetXX { Setnbe() : SetXX(NBE) {} };
    struct Seta   : public SetXX { Seta  () : SetXX(A  ) {} };
    struct Sets   : public SetXX { Sets  () : SetXX(S  ) {} };
    struct Setns  : public SetXX { Setns () : SetXX(NS ) {} };
    struct Setp   : public SetXX { Setp  () : SetXX(P  ) {} };
    struct Setpe  : public SetXX { Setpe () : SetXX(PE ) {} };
    struct Setpo  : public SetXX { Setpo () : SetXX(PO ) {} };
    struct Setnp  : public SetXX { Setnp () : SetXX(NP ) {} };
    struct Setl   : public SetXX { Setl  () : SetXX(L  ) {} };
    struct Setnge : public SetXX { Setnge() : SetXX(NGE) {} };
    struct Setge  : public SetXX { Setge () : SetXX(GE ) {} };
    struct Setnl  : public SetXX { Setnl () : SetXX(NL ) {} };
    struct Setle  : public SetXX { Setle () : SetXX(LE ) {} };
    struct Setng  : public SetXX { Setng () : SetXX(NG ) {} };
    struct Setg   : public SetXX { Setg  () : SetXX(G  ) {} };
    struct Setnle : public SetXX { Setnle() : SetXX(NLE) {} };

    struct Label : std::vector< u32 >
    {
        u8 *pointer;

        Label() : pointer(0) {}

        ~Label()
        {
            if (pointer && size())
            {
                Bind();
            }
        }

        void AddJump()
        {
            push_back(u32(al_Emitter::pointer));
        }

        void Bind()
        {
            if (!pointer)
            {
                pointer = al_Emitter::pointer;
            }

            for (std::vector< u32 >::iterator i = begin(); i != end(); ++i)
            {
                s32 delta = s32(pointer - *i);  
                if (((*((u8 *)(*i - 1)) & 0x70) == 0x70) || (*((u8 *)(*i - 1)) == 0xEB)) // Jcc/JUMP SHORT
                {
                    delta -= 1;
                    if (u32((delta >> 7) + 1) < 2)
                    {
                        *((u8 *)(*i)) = u8(delta);    
                    }
                }
                else if (((*((u16 *)(*i - 2)) & 0x800F) == 0x800F) || ((*((u8 *)(*i - 2)) == 0xE9))) // Jcc/JUMP NEAR
                {
                    *((u32 *)(*i)) = u32(delta - 4);    
                }                 
            }

            clear();
        }
    };

    struct Jump
    {
        Jump() {}

        //EB cb 	JMP rel8 	    Jump short, relative, displacement relative to next instruction.
        __forceinline void s(Label &label)
        {
            Write1(0xEB);
            label.AddJump();
            Write1(0);
        }

        //E9 cd 	JMP rel32 	    Jump near, relative, displacement relative to next instruction.
        __forceinline void n(Label &label)
        {
            Write1(0xE9);
            label.AddJump();
            Write4(0);
        }

        __forceinline void operator ()()
        {
            Write1(0xE9);
            Write4(0);
        }
    };

    struct Ret
    {
        Ret() {}

        //C3 	    RET 	        Near return to calling procedure.
        __forceinline void operator ()()
        {
            Write1(0xC3);
        }
    };

    struct JXX
    {
        int const cc;

        JXX(int const cc) : cc(cc)
        {}

        //70 cb 	JO rel8 	    Jump short if overflow (OF=1).
        //71 cb 	JNO rel8 	    Jump short if not overflow (OF=0).
        //72 cb 	JB rel8 	    Jump short if below (CF=1).
        //72 cb 	JC rel8 	    Jump short if carry (CF=1).
        //72 cb 	JNAE rel8 	    Jump short if not above or equal (CF=1).
        //73 cb 	JAE rel8 	    Jump short if above or equal (CF=0).
        //73 cb 	JNB rel8 	    Jump short if not below (CF=0).
        //73 cb 	JNC rel8 	    Jump short if not carry (CF=0).
        //74 cb 	JE rel8 	    Jump short if equal (ZF=1).
        //74 cb 	JZ rel8 	    Jump short if zero (ZF = 1).
        //75 cb 	JNE rel8 	    Jump short if not equal (ZF=0).
        //75 cb 	JNZ rel8 	    Jump short if not zero (ZF=0).
        //76 cb 	JBE rel8 	    Jump short if below or equal (CF=1 or ZF=1).
        //76 cb 	JNA rel8 	    Jump short if not above (CF=1 or ZF=1).
        //77 cb 	JA rel8 	    Jump short if above (CF=0 and ZF=0).
        //77 cb 	JNBE rel8 	    Jump short if not below or equal (CF=0 and ZF=0).
        //78 cb 	JS rel8 	    Jump short if sign (SF=1).
        //79 cb 	JNS rel8 	    Jump short if not sign (SF=0).
        //7A cb 	JP rel8 	    Jump short if parity (PF=1).
        //7A cb 	JPE rel8 	    Jump short if parity even (PF=1).
        //7B cb 	JNP rel8 	    Jump short if not parity (PF=0).
        //7B cb 	JPO rel8 	    Jump short if parity odd (PF=0).
        //7C cb 	JL rel8 	    Jump short if less (SF<>OF).
        //7C cb 	JNGE rel8 	    Jump short if not greater or equal (SF<>OF).
        //7D cb 	JGE rel8 	    Jump short if greater or equal (SF=OF).
        //7D cb 	JNL rel8 	    Jump short if not less (SF=OF).
        //7E cb 	JLE rel8 	    Jump short if less or equal (ZF=1 or SF<>OF).
        //7E cb 	JNG rel8 	    Jump short if not greater (ZF=1 or SF<>OF).
        //7F cb 	JG rel8 	    Jump short if greater (ZF=0 and SF=OF).
        //7F cb 	JNLE rel8 	    Jump short if not less or equal (ZF=0 and SF=OF).
        __forceinline void s(Label &label)
        {
            Write1(0x70+cc);
            label.AddJump();
            Write1(0);
        }

        //0F 80 cd 	JO rel32 	    Jump near if overflow (OF=1).
        //0F 81 cd 	JNO rel32 	    Jump near if not overflow (OF=0).
        //0F 82 cd 	JB rel32 	    Jump near if below (CF=1).
        //0F 82 cd 	JC rel32 	    Jump near if carry (CF=1).
        //0F 82 cd 	JNAE rel32 	    Jump near if not above or equal (CF=1).
        //0F 83 cd 	JAE rel32 	    Jump near if above or equal (CF=0).
        //0F 83 cd 	JNB rel32 	    Jump near if not below (CF=0).
        //0F 83 cd 	JNC rel32 	    Jump near if not carry (CF=0).
        //0F 84 cd 	JE rel32 	    Jump near if equal (ZF=1).
        //0F 84 cd 	JZ rel32 	    Jump near if 0 (ZF=1).
        //0F 85 cd 	JNE rel32 	    Jump near if not equal (ZF=0).
        //0F 85 cd 	JNZ rel32 	    Jump near if not zero (ZF=0).
        //0F 86 cd 	JBE rel32 	    Jump near if below or equal (CF=1 or ZF=1).
        //0F 86 cd 	JNA rel32 	    Jump near if not above (CF=1 or ZF=1).
        //0F 87 cd 	JA rel32 	    Jump near if above (CF=0 and ZF=0).
        //0F 87 cd 	JNBE rel32 	    Jump near if not below or equal (CF=0 and ZF=0).
        //0F 88 cd 	JS rel32 	    Jump near if sign (SF=1).
        //0F 89 cd 	JNS rel32 	    Jump near if not sign (SF=0).
        //0F 8A cd 	JP rel32 	    Jump near if parity (PF=1).
        //0F 8A cd 	JPE rel32 	    Jump near if parity even (PF=1).
        //0F 8B cd 	JNP rel32 	    Jump near if not parity (PF=0).
        //0F 8B cd 	JPO rel32 	    Jump near if parity odd (PF=0).
        //0F 8C cd 	JL rel32 	    Jump near if less (SF<>OF).
        //0F 8C cd 	JNGE rel32 	    Jump near if not greater or equal (SF<>OF).
        //0F 8D cd 	JNL rel32 	    Jump near if not less (SF=OF).
        //0F 8D cd 	JGE rel32 	    Jump near if greater or equal (SF=OF).
        //0F 8E cd 	JLE rel32 	    Jump near if less or equal (ZF=1 or SF<>OF).
        //0F 8E cd 	JNG rel32 	    Jump near if not greater (ZF=1 or SF<>OF).
        //0F 8F cd 	JG rel32 	    Jump near if greater (ZF=0 and SF=OF).
        //0F 8F cd 	JNLE rel32 	    Jump near if not less or equal (ZF=0 and SF=OF).
        __forceinline void n(Label &label)
        {
            Write2(0x800F+(cc<<8));
            label.AddJump();
            Write1(0);
        }
        __forceinline void operator ()()
        {
            Write2(0x800F+(cc<<8));
            Write4(0);
        }
    };

    struct Jo   : public JXX { Jo  () : JXX(O  ) {} };
    struct Jno  : public JXX { Jno () : JXX(NO ) {} };
    struct Jb   : public JXX { Jb  () : JXX(B  ) {} };
    struct Jc   : public JXX { Jc  () : JXX(C  ) {} };
    struct Jnae : public JXX { Jnae() : JXX(NAE) {} };
    struct Jnb  : public JXX { Jnb () : JXX(NB ) {} };
    struct Jnc  : public JXX { Jnc () : JXX(NC ) {} };
    struct Jae  : public JXX { Jae () : JXX(AE ) {} };
    struct Je   : public JXX { Je  () : JXX(E  ) {} };
    struct Jz   : public JXX { Jz  () : JXX(Z  ) {} };
    struct Jnz  : public JXX { Jnz () : JXX(NZ ) {} };
    struct Jne  : public JXX { Jne () : JXX(NE ) {} };
    struct Jbe  : public JXX { Jbe () : JXX(C  ) {} };
    struct Jna  : public JXX { Jna () : JXX(NA ) {} };
    struct Jnbe : public JXX { Jnbe() : JXX(NBE) {} };
    struct Ja   : public JXX { Ja  () : JXX(A  ) {} };
    struct Js   : public JXX { Js  () : JXX(S  ) {} };
    struct Jns  : public JXX { Jns () : JXX(NS ) {} };
    struct Jp   : public JXX { Jp  () : JXX(P  ) {} };
    struct Jpe  : public JXX { Jpe () : JXX(PE ) {} };
    struct Jpo  : public JXX { Jpo () : JXX(PO ) {} };
    struct Jnp  : public JXX { Jnp () : JXX(NP ) {} };
    struct Jl   : public JXX { Jl  () : JXX(L  ) {} };
    struct Jnge : public JXX { Jnge() : JXX(NGE) {} };
    struct Jge  : public JXX { Jge () : JXX(GE ) {} };
    struct Jnl  : public JXX { Jnl () : JXX(NL ) {} };
    struct Jle  : public JXX { Jle () : JXX(LE ) {} };
    struct Jng  : public JXX { Jng () : JXX(NG ) {} };
    struct Jg   : public JXX { Jg  () : JXX(G  ) {} };
    struct Jnle : public JXX { Jnle() : JXX(NLE) {} };

    struct BsX
    {
        int const dir;

        BsX(int const dir) : dir(dir)
        {}

        //0F BC 	BSF r32, r32 	    Bit scan forward on r32
        //0F BD 	BSR r32, r32 	    Bit scan reverse on r32
        __forceinline void operator()(R32 const &d, R32 const &s)
        {
            Write2(dir ? 0xBD0F : 0xBC0F);
            WriteModRegRM(3, s.reg, d.reg);
        }

        //0F BC 	BSF r32, m32 	    Bit scan forward on m32
        //0F BD 	BSR r32, m32 	    Bit scan reverse on m32
        __forceinline void operator()(R32 const &r, M32 const &m)
        {
            Write2(dir ? 0xBD0F : 0xBC0F);
            WriteM32(r.reg, m);
        }
    };

    struct Bsf : public BsX { Bsf() : BsX(0) {} };
    struct Bsr : public BsX { Bsr() : BsX(1) {} };


    //0F C8+rd 	BSWAP r32 	Reverses the byte order of a 32-bit register.

    struct Bswap
    {
        Bswap()
        {}

        //0F C8+rd 	BSWAP r32 	        Reverses the byte order of a 32-bit register.
        __forceinline void operator()(R32 const &d)
        {
            Write2(0xC80F+(d.reg<<8));
        }
    };

    enum MduEnum { IMUL, MUL, IDIV, DIV };

    struct Mdu
    {
        int const op1;

        Mdu(int const op1) : op1(op1)
        {}

        //F7 \4 	MUL r32 	        Unsigned multiply (EDX:EAX = EAX * r32)
        //F7 \5 	IMUL r32 	        Signed multiply (EDX:EAX = EAX * r32)
        //F7 \6 	DIV r32 	        Unsigned divide (EAX = EDX:EAX / r32, EDX = EDX:EAX % r32)
        //F7 \7 	IDIV r32 	        Signed divide (EAX = EDX:EAX / r32, EDX = EDX:EAX % r32)
        __forceinline void operator()(R32 const &r)
        {
            Write1(0xF7);
            WriteModRegRM(3, 4+op1, r.reg);
        }

        //F7 \4 	MUL m32 	        Unsigned multiply (EDX:EAX = EAX * m32)
        //F7 \5 	IMUL m32 	        Signed multiply (EDX:EAX = EAX * m32)
        //F7 \6 	DIV m32 	        Unsigned divide (EAX = EDX:EAX / m32, EDX = EDX:EAX % m32)
        //F7 \7 	IDIV m32 	        Signed divide (EAX = EDX:EAX / m32, EDX = EDX:EAX % m32)
        __forceinline void operator()(M32 const &m)
        {
            Write1(0xF7);
            WriteM32(4+op1, m);
        }

    };

    struct Mul  : public Mdu { Mul()  : Mdu(MUL ) {} };
    struct Imul : public Mdu { Imul() : Mdu(IMUL) {} };
    struct Div  : public Mdu { Div()  : Mdu(DIV ) {} };
    struct Idiv : public Mdu { Idiv() : Mdu(IDIV) {} };


    struct Movss
    {
        Movss() {}

        //F3 0F 10 /r 	MOVSS xmm1, xmm2 	Move scalar single-precision floating-point value from xmm2 to xmm1 register.
        __forceinline void operator()(V128 const &d, V128 const &s) { Write2(0x0FF3); Write1(0x10); WriteModRegRM(3, d.reg, s.reg); }

        //F3 0F 10 /r 	MOVSS xmm1, m32 	Move scalar single-precision floating-point value from m32 to xmm1 register.
        __forceinline void operator()(V128 const &r, M32 const &m) { Write2(0x0FF3); Write1(0x10); WriteM32(r.reg, m); }

        //F3 0F 11 /r 	MOVSS m32, xmm1 	Move scalar single-precision floating-point value from xmm1 register to m32.
        __forceinline void operator()(M32 const &m, V128 const &r) { Write2(0x0FF3); Write1(0x11); WriteM32(r.reg, m); }
    };

    struct MovXps
    {
        int const aligned;

        MovXps(int const aligned) : aligned(aligned)
        {}

        //0F 10 /r 	MOVUPS xmm1, xmm2 	Move packed single-precision floating-point values from xmm2 to xmm1.
        //0F 28 /r 	MOVAPS xmm1, xmm2 	Move packed single-precision floating-point values from xmm2 to xmm1.
        __forceinline void operator()(V128 const &d, V128 const &s)
        {
            Write2(aligned ? 0x280F : 0x100F);
            WriteModRegRM(3, d.reg, s.reg);
        }

        //0F 10 /r 	MOVUPS xmm1, m128 	Move packed single-precision floating-point values from m128 to xmm1.
        //0F 28 /r 	MOVAPS xmm1, m128 	Move packed single-precision floating-point values from m128 to xmm1.
        __forceinline void operator()(V128 const &r, M128 const &m)
        {
            Write2(aligned ? 0x280F : 0x100F);
            WriteM128(r.reg, m);
        }

        //0F 11 /r 	MOVUPS m128, xmm1 	Move packed single-precision floating-point values from xmm1 to m128.
        //0F 29 /r 	MOVAPS m128, xmm1 	Move packed single-precision floating-point values from xmm1 to m128.
        __forceinline void operator()(M128 const &m, V128 const &r)
        {
            Write2(aligned ? 0x290F : 0x110F);
            WriteM128(r.reg, m);
        }
    };

    struct Movups : public MovXps { Movups() : MovXps(0) {} };
    struct Movaps : public MovXps { Movaps() : MovXps(1) {} };

    struct Cvtsi2ss
    {
        Cvtsi2ss() {}

        //F3 0F 2A /r 	CVTSI2SS xmm, r32 	Convert one signed doubleword integer from r32 to one single-precision floating-point value in xmm.
        __forceinline void operator()(V128 const &d, R32 const &s) { Write2(0x0FF3); Write1(0x2A); WriteModRegRM(3, d.reg, s.reg); }

        //F3 0F 2A /r 	CVTSI2SS xmm, m32 	Convert one signed doubleword integer from r/m32 to one single-precision floating-point value in xmm.
        __forceinline void operator()(V128 const &r, M32 const &m) { Write2(0x0FF3); Write1(0x2A); WriteM32(r.reg, m); }
    };

    struct Cvtss2si
    {
        Cvtss2si() {}

        //F3 0F 2D /r 	CVTSS2SI r32, xmm 	Convert one single-precision floating-point value from xmm to one signed doubleword integer in r32.
        __forceinline void operator()(R32 const &d, V128 const &s) { Write2(0x0FF3); Write1(0x2D); WriteModRegRM(3, s.reg, d.reg); }

        //F3 0F 2D /r 	CVTSS2SI m32, xmm 	Convert one single-precision floating-point value from m32 to one signed doubleword integer in r32.
        __forceinline void operator()(M32 const &m, V128 const &r) { Write2(0x0FF3); Write1(0x2D); WriteM32(r.reg, m); }
    };

    enum AlussOperation { SQRTSS = 1, RSQRTSS, RCPSS, ADDSS = 8, MULSS, CVTSS2SD, CVTTPS2DQ, SUBSS, MINSS, DIVSS, MAXSS };
    struct Aluss
    {
        const int op;

        Aluss(const int op) : op(op) {}

        //F3 0F 58 /r 	ADDSS xmm1, xmm2 	Add the low single-precision floating-point value from xmm2 to xmm1.
        //F3 0F 59 /r 	MULSS xmm1, xmm2 	Multiply the low single-precision floating-point value in xmm2 by the low single-precision floating-point value in xmm1.
        //F3 0F 5C /r 	SUBSS xmm1, xmm2 	Subtract the lower single-precision floating-point values in xmm2 from xmm1.
        //F3 0F 5D /r 	MINSS xmm1, xmm2    Return the minimum scalar single-precision floating-point value between xmm2 and xmm1. 	
        //F3 0F 5E /r 	DIVSS xmm1, xmm2 	Divide low single-precision floating-point value in xmm1 by low single-precision floating-point value in xmm2.
        //F3 0F 5F /r 	MAXSS xmm1, xmm2 	Return the maximum scalar single-precision floating-point value between xmm2 and xmm1.
        __forceinline void operator()(V128 const &d, V128 const &s) { Write2(0x0FF3); Write1(0x50+op); WriteModRegRM(3, d.reg, s.reg); }

        //F3 0F 58 /r 	ADDSS xmm1, m32 	Add the low single-precision floating-point value from m32 to xmm1.
        //F3 0F 59 /r 	MULSS xmm1, m32 	Multiply the low single-precision floating-point value in m32 by the low single-precision floating-point value in xmm1.
        //F3 0F 5C /r 	SUBSS xmm1, m32 	Subtract the lower single-precision floating-point values in m32 from xmm1.
        //F3 0F 5D /r 	MINSS xmm1, m32     Return the minimum scalar single-precision floating-point value between m32 and xmm1. 	
        //F3 0F 5E /r 	DIVSS xmm1, m32 	Divide low single-precision floating-point value in xmm1 by low single-precision floating-point value in m32.
        //F3 0F 5F /r 	MAXSS xmm1, m32 	Return the maximum scalar single-precision floating-point value between m32 and xmm1.
        __forceinline void operator()(V128 const &r, M32 const &m) { Write2(0x0FF3); Write1(0x50+op); WriteM32(r.reg, m); }
    };

    struct Sqrtss  : public Aluss { Sqrtss()  : Aluss(SQRTSS ) {} };
    struct Rsqrtss : public Aluss { Rsqrtss() : Aluss(RSQRTSS) {} };
    struct Rcpss   : public Aluss { Rcpss()   : Aluss(RCPSS  ) {} };
    struct Addss   : public Aluss { Addss()   : Aluss(ADDSS  ) {} };
    struct Mulss   : public Aluss { Mulss()   : Aluss(MULSS  ) {} };
    struct Subss   : public Aluss { Subss()   : Aluss(SUBSS  ) {} };
    struct Minss   : public Aluss { Minss()   : Aluss(MINSS  ) {} };
    struct Divss   : public Aluss { Divss()   : Aluss(DIVSS  ) {} };
    struct Maxss   : public Aluss { Maxss()   : Aluss(MAXSS  ) {} };

    enum AlupsOperation { MOVMSKPS, SQRTPS, RSQRTPS, RCPPS, ANDPS, ANDNPS, ORPS, XORPS, ADDPS, MULPS, CVTPS2PD, CVTTDQ2PS, SUBPS, MINPS, DIVPS, MAXPS };
    struct Alups
    {
        const int op;

        Alups(const int op) : op(op) {}

        //0F 54 /r 	ANDPS xmm1, xmm2    Bitwise logical AND of xmm2 and xmm1.
        //0F 55 /r 	ANDNPS xmm1, xmm2 	Bitwise logical AND NOT of xmm2 and xmm1.
        //0F 56 /r 	ORPS xmm1, xmm2 	Bitwise OR of xmm2/m128 and xmm1.
        //0F 57 /r 	XORPS xmm1, xmm2 	Bitwise exclusive-OR of xmm2 and xmm1.
        __forceinline void operator()(V128 const &d, V128 const &s) { Write1(0x0F); Write1(0x50+op); WriteModRegRM(3, d.reg, s.reg); }

        //0F 54 /r 	ANDPS xmm1, m128 	Bitwise logical AND of m128 and xmm1.
        //0F 55 /r 	ANDNPS xmm1, m128 	Bitwise logical AND NOT of m128 and xmm1.
        //0F 56 /r 	ORPS xmm1, m128 	Bitwise OR of m128 and xmm1.
        //0F 57 /r 	XORPS xmm1, m128 	Bitwise exclusive-OR of m128 and xmm1.
        __forceinline void operator()(V128 const &r, M128 const &m) { Write1(0x0F); Write1(0x50+op); WriteM128(r.reg, m); }
    };

    struct Sqrtps  : public Alups { Sqrtps()  : Alups(SQRTPS ) {} };
    struct Rsqrtps : public Alups { Rsqrtps() : Alups(RSQRTPS) {} };
    struct Rcpps   : public Alups { Rcpps()   : Alups(RCPPS  ) {} };
    struct Andps   : public Alups { Andps()   : Alups(ANDPS  ) {} };
    struct Andnps  : public Alups { Andnps()  : Alups(ANDNPS ) {} };
    struct Orps    : public Alups { Orps()    : Alups(ORPS   ) {} };
    struct Xorps   : public Alups { Xorps()   : Alups(XORPS  ) {} };
    struct Addps   : public Alups { Addps()   : Alups(ADDPS  ) {} };
    struct Mulps   : public Alups { Mulps()   : Alups(MULPS  ) {} };
    struct Subps   : public Alups { Subps()   : Alups(SUBPS  ) {} };
    struct Minps   : public Alups { Minps()   : Alups(MINPS  ) {} };
    struct Divps   : public Alups { Divps()   : Alups(DIVPS  ) {} };
    struct Maxps   : public Alups { Maxps()   : Alups(MAXPS  ) {} };

    struct Comiss
    {
        Comiss() {}

        //0F 2F /r 	COMISS xmm1, xmm2 	Compare low single-precision floating-point values in xmm1 and xmm2 and set the EFLAGS flags accordingly.
        __forceinline void operator()(V128 const &d, V128 const &s) { Write2(0x2F0F); WriteModRegRM(3, d.reg, s.reg); }
        
        //0F 2F /r 	COMISS xmm1, m32 	Compare low single-precision floating-point values in xmm1 and mem32 and set the EFLAGS flags accordingly.
        __forceinline void operator()(V128 const &r, M32 const &m) { Write2(0x2F0F); WriteM32(r.reg, m); }
    };

    enum MxcsrFlags
    {
        mxcsr_round_mask        = 0x6000,
        mxcsr_round_nearest     = 0x0000,
        mxcsr_round_down        = 0x2000,
        mxcsr_round_up          = 0x4000,
        mxcsr_round_toward_zero = 0x6000,

        mxcsr_flush_zero_mask   = 0x8000,
        mxcsr_flush_zero        = 0x8000,

        mxcsr_all_mask          = mxcsr_round_mask|mxcsr_flush_zero_mask,

    };

    struct Ldmxcsr
    {
        Ldmxcsr() {}

        //0F AE /2 	LDMXCSR m32 	    Load MXCSR register from m32.
        __forceinline void operator()(M32 const &m) { Write2(0xAE0F); WriteM32(2, m); }
    };

    struct Stmxcsr
    {
        Stmxcsr() {}

        //0F AE /3 	STMXCSR m32 	    Store contents of MXCSR register to m32.
        __forceinline void operator()(M32 const &m) { Write2(0xAE0F); WriteM32(3, m); }
    };

   

};


#endif