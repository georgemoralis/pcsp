/*
 *  01/06/2022 - synced with jpcsp 31/05/2022 - 9084111 - Complete!
 */
#pragma once

namespace Allegrex {
    namespace Opcodes {

    // CPU: encoded by opcode field.
    //
    //     31---------26---------------------------------------------------0
    //     |  opcode   |                                                   |
    //     ------6----------------------------------------------------------
    //     |--000--|--001--|--010--|--011--|--100--|--101--|--110--|--111--| lo
    // 000 | *1    | *2    | J     | JAL   | BEQ   | BNE   | BLEZ  | BGTZ  |
    // 001 | ADDI  | ADDIU | SLTI  | SLTIU | ANDI  | ORI   | XORI  | LUI   |
    // 010 | *3    | *4    | VFPU2 | ---   | BEQL  | BNEL  | BLEZL | BGTZL |
    // 011 | VFPU0 | VFPU1 |  ---  | VFPU3 | * 5   | ---   | ---   | *6    |
    // 100 | LB    | LH    | LWL   | LW    | LBU   | LHU   | LWR   | ---   |
    // 101 | SB    | SH    | SWL   | SW    | ---   | ---   | SWR   | CACHE |
    // 110 | LL    | LWC1  | LVS   | ---   | VFPU4 | ULVQ  | LVQ   | VFPU5 |
    // 111 | SC    | SWC1  | SVS   | ---   | VFPU6 | USVQ  | SVQ   | VFPU7 |
    //  hi |-------|-------|-------|-------|-------|-------|-------|-------|
    //
    //      *1 = SPECIAL, see SPECIAL list    *2 = REGIMM, see REGIMM list
    //      *3 = COP0                         *4 = COP1
    //      *5 = SPECIAL2 , see SPECIAL2      *6 = SPECIAL3 , see SPECIAL 3
    //      *ULVQ is buggy on PSP1000 PSP
    //      *VFPU0 check VFPU0 table
    //      *VFPU1 check VFPU1 table
    //      *VFPU2 check VFPU2 table
    //      *VFPU3 check VFPU3 table
    //      *VFPU4 check VFPU4 table
    //      *VFPU5 check VFPU5 table
    //      *VFPU6 check VFPU6 table
    //      *VFPU7 check VFPU7 table

    static constexpr int SPECIAL = 0x0;
    static constexpr int REGIMM = 0x1;
    static constexpr int J = 0x2;  // Jump
    static constexpr int JAL = 0x3;  // Jump And Link
    static constexpr int BEQ = 0x4;  // Branch on Equal
    static constexpr int BNE = 0x5;  // Branch on Not Equal
    static constexpr int BLEZ = 0x6;  // Branch on Less Than or Equal to Zero
    static constexpr int BGTZ = 0x7;  // Branch on Greater Than Zero
    static constexpr int ADDI = 0x8;  // Add Immediate
    static constexpr int ADDIU = 0x9;  // Add Immediate Unsigned
    static constexpr int SLTI = 0xa;  // Set on Less Than Immediate
    static constexpr int SLTIU = 0xb;  // Set on Less Than Immediate Unsigned
    static constexpr int ANDI = 0xc;  // AND Immediate
    static constexpr int ORI = 0xd;  // OR Immediate
    static constexpr int XORI = 0xe;  // Exclusive OR Immediate
    static constexpr int LUI = 0xf;  // Load Upper Immediate
    static constexpr int COP0 = 0x10;  // Coprocessor Operation
    static constexpr int COP1 = 0x11;  // Coprocessor Operation
    static constexpr int VFPU2 = 0x12;
    /*  0x13 reserved or unsupported */
    static constexpr int BEQL = 0x14;  // Branch on Equal Likely
    static constexpr int BNEL = 0x15;  // Branch on Not Equal Likely
    static constexpr int BLEZL = 0x16;  // Branch on Less Than or Equal to Zero Likely
    static constexpr int BGTZL = 0x17;  // Branch on Greater Than Zero Likely
    static constexpr int VFPU0 = 0x18;
    static constexpr int VFPU1 = 0x19;
    static constexpr int ME1 = 0x1A;  // Only for the ME
    static constexpr int VFPU3 = 0x1b;
    static constexpr int SPECIAL2 = 0x1c;  // Allegrex table
    /*  0x1d reserved or unsupported */
    /*  0x1e reserved or unsupported */
    static constexpr int SPECIAL3 = 0x1f;  // special3 table
    static constexpr int LB = 0x20;  // Load Byte
    static constexpr int LH = 0x21;  // Load Halfword
    static constexpr int LWL = 0x22;  // Load Word Left
    static constexpr int LW = 0x23;  // Load Word
    static constexpr int LBU = 0x24;  // Load Byte Unsigned
    static constexpr int LHU = 0x25;  // Load Halfword Unsigned
    static constexpr int LWR = 0x26;  // Load Word Right
    /*  0x27 reserved or unsupported */
    static constexpr int SB = 0x28;  // Store Byte
    static constexpr int SH = 0x29;  // Store Halfword
    static constexpr int SWL = 0x2A;  // Store Word Left
    static constexpr int SW = 0x2B;  // Store Word
    static constexpr int ME2 = 0x2C;  // Only for the ME
    /*  0x2d reserved or unsupported */
    static constexpr int SWR = 0x2E;  // Store Word Right
    static constexpr int CACHE = 0x2f;  // Allegrex Cache Operation
    static constexpr int LL = 0x30;  // Load Linked
    static constexpr int LWC1 = 0x31;  // Load FPU Register
    static constexpr int LVS = 0x32;  // Load Scalar VFPU Register
    /*  0x32 reserved or unsupported */
    /*  0x33 reserved or unsupported */
    static constexpr int VFPU4 = 0x34;
    static constexpr int ULVQ = 0x35;  // Load Quad VFPU Register (Unaligned)
    static constexpr int LVQ = 0x36;  // Load Quad VFPU Register
    static constexpr int VFPU5 = 0x37;
    static constexpr int SC = 0x38;  // Store Conditionaly
    static constexpr int SWC1 = 0x39;  // Store FPU Register
    static constexpr int SVS = 0x3a;  // Store Scalar VFPU Register
    /*  0x3b reserved or unsupported */
    static constexpr int VFPU6 = 0x3c;
    static constexpr int USVQ = 0x3d;  // Store Quad VFPU Register (Unaligned)
    static constexpr int SVQ = 0x3e;  // Store Quad VFPU Register
    static constexpr int VFPU7 = 0x3f;  // SPECIAL: encoded by function field when opcode field = SPECIAL
    //
    //     31---------26------------------------------------------5--------0
    //     |=   SPECIAL|                                         | function|
    //     ------6----------------------------------------------------6-----
    //     |--000--|--001--|--010--|--011--|--100--|--101--|--110--|--111--| lo
    // 000 | SLL   | ---   |SRLROR | SRA   | SLLV  |  ---  |SRLRORV| SRAV  |
    // 001 | JR    | JALR  | MOVZ  | MOVN  |SYSCALL| BREAK |  ---  | SYNC  |
    // 010 | MFHI  | MTHI  | MFLO  | MTLO  | ---   |  ---  |  CLZ  | CLO   |
    // 011 | MULT  | MULTU | DIV   | DIVU  | MADD  | MADDU | ----  | ----- |
    // 100 | ADD   | ADDU  | SUB   | SUBU  | AND   | OR    | XOR   | NOR   |
    // 101 | ---   |  ---  | SLT   | SLTU  | MAX   | MIN   | MSUB  | MSUBU |
    // 110 | ---   |  ---  | ---   | ---   | ---   |  ---  | ---   | ---   |
    // 111 | ---   |  ---  | ---   | ---   | ---   |  ---  | ---   | ---   |
    //  hi |-------|-------|-------|-------|-------|-------|-------|-------|
    static constexpr int SLL = 0x0;  // Shift Left Logical
    /*  0x1 reserved or unsupported */
    static constexpr int SRLROR = 0x2;  // Shift/Rotate Right Logical
    static constexpr int SRA = 0x3;  // Shift Right Arithmetic
    static constexpr int SLLV = 0x4;  // Shift Left Logical Variable
    /*  0x5 reserved or unsupported */
    static constexpr int SRLRORV = 0x6;  // Shift/Rotate Right Logical Variable
    static constexpr int SRAV = 0x7;  // Shift Right Arithmetic Variable
    static constexpr int JR = 0x8;  // Jump Register
    static constexpr int JALR = 0x9;  // Jump And Link Register
    static constexpr int MOVZ = 0xa;  // Move If Zero
    static constexpr int MOVN = 0xb;  // Move If Non-zero
    static constexpr int SYSCALL = 0xc;  // System Call
    static constexpr int BREAK = 0xd;  // Break
    /*  0xe reserved or unsupported */
    static constexpr int SYNC = 0xf;  // Sync
    static constexpr int MFHI = 0x10;  // Move From HI
    static constexpr int MTHI = 0x11;  // Move To HI
    static constexpr int MFLO = 0x12;  // Move From LO
    static constexpr int MTLO = 0x13;  // Move To LO
    /*  0x14 reserved or unsupported */
    /*  0x15 reserved or unsupported */
    static constexpr int CLZ = 0x16;  // Count Leading Zero
    static constexpr int CLO = 0x17;  // Count Leading One
    static constexpr int MULT = 0x18;  // Multiply
    static constexpr int MULTU = 0x19;  // Multiply Unsigned
    static constexpr int DIV = 0x1a;  // Divide
    static constexpr int DIVU = 0x1b;  // Divide Unsigned
    static constexpr int MADD = 0x1c;  // Multiply And Add
    static constexpr int MADDU = 0x1d;  // Multiply And Add Unsigned
    /*  0x1e reserved or unsupported */
    /*  0x1f reserved or unsupported */
    static constexpr int ADD = 0x20;  // Add
    static constexpr int ADDU = 0x21;  // Add Unsigned
    static constexpr int SUB = 0x22;  // Subtract
    static constexpr int SUBU = 0x23;  // Subtract Unsigned
    static constexpr int AND = 0x24;  // AND
    static constexpr int OR = 0x25;  // OR
    static constexpr int XOR = 0x26;  // Exclusive OR
    static constexpr int NOR = 0x27;  // NOR
    /*  0x28 reserved or unsupported */
    /*  0x29 reserved or unsupported */
    static constexpr int SLT = 0x2a;  // Set on Less Than
    static constexpr int SLTU = 0x2b;  // Set on Less Than Unsigned
    static constexpr int MAX = 0x2c;  // Move Max
    static constexpr int MIN = 0x2d;  // Move Min
    static constexpr int MSUB = 0x2e;  // Multiply And Substract
    static constexpr int MSUBU = 0x2f;  // Multiply And Substract
    // SPECIAL rs : encoded by rs field when opcode/func field = SPECIAL/SRLROR
    //
    //     31---------26-----21-----------------------------------5--------0
    //     |=   SPECIAL| rs  |                                    |= SRLROR|
    //     ------6--------5-------------------------------------------6-----
    //     |--000--|--001--|--010--|--011--|--100--|--101--|--110--|--111--| lo
    // 000 | SRL   | ROTR  |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |
    // 001 |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |
    // 010 |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |
    // 011 |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |
    //  hi |-------|-------|-------|-------|-------|-------|-------|-------|
    static constexpr int SRL = 0x0;
    static constexpr int ROTR = 0x1;  
    // SPECIAL sa : encoded by sa field when opcode/func field = SPECIAL/SRLRORV
    //
    //     31---------26------------------------------------10----5--------0
    //     |=   SPECIAL|                                    | sa  |=SRLRORV|
    //     ------6---------------------------------------------5------6-----
    //     |--000--|--001--|--010--|--011--|--100--|--101--|--110--|--111--| lo
    // 000 | SRLV  | ROTRV |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |
    // 001 |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |
    // 010 |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |
    // 011 |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |
    //  hi |-------|-------|-------|-------|-------|-------|-------|-------|
    static constexpr int SRLV = 0x0;
    static constexpr int ROTRV = 0x1;  
    //
    //     REGIMM: encoded by the rt field when opcode field = REGIMM.
    //     31---------26----------20-------16------------------------------0
    //     |=    REGIMM|          |   rt    |                              |
    //     ------6---------------------5------------------------------------
    //     |--000--|--001--|--010--|--011--|--100--|--101--|--110--|--111--| lo
    //  00 | BLTZ  | BGEZ  | BLTZL | BGEZL |  ---  |  ---  |  ---  |  ---  |
    //  01 |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |
    //  10 | BLTZAL| BGEZAL|BLTZALL|BGEZALL|  ---  |  ---  |  ---  |  ---  |
    //  11 |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |
    //  hi |-------|-------|-------|-------|-------|-------|-------|-------|

    static constexpr int BLTZ = 0x0;  // Branch on Less Than Zero
    static constexpr int BGEZ = 0x1;  // Branch on Greater Than or Equal to Zero
    static constexpr int BLTZL = 0x2;  // Branch on Less Than Zero Likely
    static constexpr int BGEZL = 0x3;  // Branch on Greater Than or Equal to Zero Likely
    /*  0x4 reserved or unsupported */
    /*  0x5 reserved or unsupported */
    /*  0x6 reserved or unsupported */
    /*  0x7 reserved or unsupported */
    /*  0x8 reserved or unsupported */
    /*  0x9 reserved or unsupported */
    /*  0xa reserved or unsupported */
    /*  0xb reserved or unsupported */
    /*  0xc reserved or unsupported */
    /*  0xd reserved or unsupported */
    /*  0xe reserved or unsupported */
    /*  0xf reserved or unsupported */
    static constexpr int BLTZAL = 0x10;  // Branch on Less Than Zero And Link
    static constexpr int BGEZAL = 0x11;  // Branch on Greater Than or Equal to Zero And Link
    static constexpr int BLTZALL = 0x12;  // Branch on Less Than Zero And Link Likely
    static constexpr int BGEZALL = 0x13;  // Branch on Greater Than or Equal to Zero And Link Likely
    //     COP0: encoded by the rs field when opcode field = COP0.
    //     31---------26----------23-------31------------------------------0
    //     |=      COP0|          |   rs    |                              |
    //     ------6---------------------5------------------------------------
    //     |--000--|--001--|--010--|--011--|--100--|--101--|--110--|--111--| lo
    //  00 |  MFC0 |  ---  |  CFC0 |  ---  |  MTC0 |  ---  |  CTC0 |  ---  |
    //  01 |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |
    //  10 |  *1   |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |
    //  11 |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |
    //  hi |-------|-------|-------|-------|-------|-------|-------|-------|
    //
    //     *1 COP0 func
    static constexpr int MFC0 = 0x0;  // Move from Coprocessor 0
    static constexpr int CFC0 = 0x2;  // Move from Coprocessor 0
    static constexpr int MTC0 = 0x4;  // Move to Coprocessor 0
    static constexpr int CTC0 = 0x6;  // Move to Coprocessor 0
    static constexpr int COP0ERET = 0x10;  
    //     COP0: encoded by the func field when opcode/rs field = COP0/10000.
    //     31---------26------------------------------------------5--------0
    //     |=      COP0|                                         | function|
    //     ------6----------------------------------------------------6-----
    //     |--000--|--001--|--010--|--011--|--100--|--101--|--110--|--111--| lo
    //  00 |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |
    //  01 |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |
    //  10 |  ERET |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |
    //  11 |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |
    //  hi |-------|-------|-------|-------|-------|-------|-------|-------|
    static constexpr int ERET = 0x10;  // Exception Return            */
    //     SPECIAL2 : encoded by function field when opcode field = SPECIAL2
    //     31---------26------------------------------------------5--------0
    //     |=  SPECIAL2|                                         | function|
    //     ------6----------------------------------------------------6-----
    //     |--000--|--001--|--010--|--011--|--100--|--101--|--110--|--111--| lo
    // 000 | HALT  |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |
    // 001 |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |
    // 010 |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |
    // 011 |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |
    // 100 |  ---  |  ---  |  ---  |  ---  | MFIC  |  ---  | MTIC  |  ---  |
    // 101 |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |
    // 110 |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |
    // 111 |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |
    //  hi |-------|-------|-------|-------|-------|-------|-------|-------|
    static constexpr int HALT = 0x0;  // halt execution until next interrupt
    static constexpr int MFIC = 0x24;  // move from IC (Interrupt) register
    static constexpr int MTIC = 0x26;  // move to IC (Interrupt) register
    static constexpr int DBREAK = 0x3F;  // Debugging break, only for the ME
    //     SPECIAL3: encoded by function field when opcode field = SPECIAL3
    //     31---------26------------------------------------------5--------0
    //     |=  SPECIAL3|                                         | function|
    //     ------6----------------------------------------------------6-----
    //     |--000--|--001--|--010--|--011--|--100--|--101--|--110--|--111--| lo
    // 000 |  EXT  |  ---  |  ---  |  ---  |  INS  |  ---  |  ---  |  ---  |
    // 001 |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |
    // 010 |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |
    // 011 |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |
    // 100 |  *1   |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |
    // 101 |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |
    // 110 |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |
    // 111 |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |
    //  hi |-------|-------|-------|-------|-------|-------|-------|-------|
    //       * 1 BSHFL encoding based on sa field
    static constexpr int EXT = 0x0;  // extract bit field
    static constexpr int INS = 0x4;  // insert bit field
    static constexpr int BSHFL = 0x20;  // BSHFL table
    //     BSHFL: encoded by the sa field.
    //     31---------26----------20-------16--------------8---6-----------0
    //     |          |          |         |               | sa|           |
    //     ------6---------------------5------------------------------------
    //     |--000--|--001--|--010--|--011--|--100--|--101--|--110--|--111--| lo
    //  00 |  ---  |  ---  | WSBH  | WSBW  |  ---  |  ---  |  ---  |  ---  |
    //  01 |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |
    //  10 |  SEB  |  ---  |  ---  |  ---  |BITREV |  ---  |  ---  |  ---  |
    //  11 |  SEH  |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |
    //  hi |-------|-------|-------|-------|-------|-------|-------|-------|
    static constexpr int WSBH = 0x02;  // Swap Bytes In Each Half Word
    static constexpr int WSBW = 0x03;  // Swap Bytes In Word
    static constexpr int SEB = 0x10;  // Sign-Extend Byte
    static constexpr int BITREV = 0x14;  // Revert Bits In Word
    static constexpr int SEH = 0x18;  // Sign-Extend HalfWord
    //     COP1: encoded by the rs field when opcode field = COP1.
    //     31-------26------21---------------------------------------------0
    //     |=    COP1|  rs  |                                              |
    //     -----6-------5---------------------------------------------------
    //     |--000--|--001--|--010--|--011--|--100--|--101--|--110--|--111--| lo
    //  00 |  MFC1 |  ---  |  CFC1 |  ---  |  MTC1 |  ---  |  CTC1 |  ---  |
    //  01 |  *1   |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |
    //  10 |  *2   |  ---  |  ---  |  ---  |  *3   |  ---  |  ---  |  ---  |
    //  11 |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |
    //  hi |-------|-------|-------|-------|-------|-------|-------|-------|
    //    *1 check COP1BC table
    //    *2 check COP1S table;
    //    *2 check COP1W table;
    static constexpr int MFC1 = 0x00;
    static constexpr int CFC1 = 0x02;
    static constexpr int MTC1 = 0x04;
    static constexpr int CTC1 = 0x06;
    static constexpr int COP1BC = 0x08;
    static constexpr int COP1S = 0x10;
    static constexpr int COP1W = 0x14;  
    //
    //     COP1BC: encoded by the rt field
    //     31---------21-------16------------------------------------------0
    //     |=    COP1BC|  rt   |                                           |
    //     ------11---------5-----------------------------------------------
    //     |--000--|--001--|--010--|--011--|--100--|--101--|--110--|--111--| lo
    //  00 |  BC1F | BC1T  | BC1FL | BC1TL |  ---  |  ---  |  ---  |  ---  |
    //  01 |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |
    //  10 |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |
    //  11 |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |
    //  hi |-------|-------|-------|-------|-------|-------|-------|-------|
    static constexpr int BC1F = 0x00;
    static constexpr int BC1T = 0x01;
    static constexpr int BC1FL = 0x02;
    static constexpr int BC1TL = 0x03;  
    //
    //     COP1S: encoded by function field
    //     31---------21------------------------------------------5--------0
    //     |=  COP1S  |                                          | function|
    //     -----11----------------------------------------------------6-----
    //     |--000--|--001--|--010--|--011--|--100--|--101--|--110--|--111--| lo
    // 000 | add.s | sub.s | mul.s | div.s |sqrt.s | abs.s | mov.s | neg.s |
    // 001 |  ---  |  ---  |  ---  |  ---  |            <*1>.w.s           |
    // 010 |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |
    // 011 |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |
    // 100 |  ---  |  ---  |  ---  |  ---  |cvt.w.s|  ---  |  ---  |  ---  |
    // 101 |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |
    // 110 |                            c.<*2>.s                           |
    // 110 |                            c.<*3>.s                           |
    //  hi |-------|-------|-------|-------|-------|-------|-------|-------|
    //
    // *1 : round.w.s | trunc.w.s | ceil.w.s | floor.w.s
    // *2 : c.f.s | c.un.s | c.eq.s | c.ueq.s | c.olt.s | c.ult.s | c.ole.s | c.ule.s
    // *3 : c.sf.s | c.ngle.s | c.seq.s | c.ngl.s | c.lt.s | c.nge.s | c.le.s  | c.ngt.s
    //
    static constexpr int ADDS = 0x00;
    static constexpr int SUBS = 0x01;
    static constexpr int MULS = 0x02;
    static constexpr int DIVS = 0x03;
    static constexpr int SQRTS = 0x04;
    static constexpr int ABSS = 0x05;
    static constexpr int MOVS = 0x06;
    static constexpr int NEGS = 0x07;
    static constexpr int ROUNDWS = 0xc;
    static constexpr int TRUNCWS = 0xd;
    static constexpr int CEILWS = 0xe;
    static constexpr int FLOORWS = 0xf;
    static constexpr int CVTWS = 0x24;
    static constexpr int CCONDS = 0x30;
    static constexpr int CF = 0x0;
    static constexpr int CUN = 0x1;
    static constexpr int CEQ = 0x2;
    static constexpr int CUEQ = 0x3;
    static constexpr int COLT = 0x4;
    static constexpr int CULT = 0x5;
    static constexpr int COLE = 0x6;
    static constexpr int CULE = 0x7;
    static constexpr int CSF = 0x8;
    static constexpr int CNGLE = 0x9;
    static constexpr int CSEQ = 0xa;
    static constexpr int CNGL = 0xb;
    static constexpr int CLT = 0xc;
    static constexpr int CNGE = 0xd;
    static constexpr int CLE = 0xe;
    static constexpr int CNGT = 0xf;  
    //
    //     COP1W: encoded by function field
    //     31---------21------------------------------------------5--------0
    //     |=  COP1W  |                                          | function|
    //     -----11----------------------------------------------------6-----
    //     |--000--|--001--|--010--|--011--|--100--|--101--|--110--|--111--| lo
    // 000 |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |
    // 001 |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |
    // 010 |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |
    // 011 |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |
    // 100 |cvt.s.w|  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |
    // 101 |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |
    // 110 |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |
    // 110 |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |
    //  hi |-------|-------|-------|-------|-------|-------|-------|-------|
    static constexpr int CVTSW = 0x20;  //
    // VFPU2: /* known as COP2 */
    static constexpr int MFVMFVC = 0x00;
    static constexpr int MTVMTVC = 0x04;
    static constexpr int VFPU2BC = 0x08;  //
    static constexpr int MFV = 0x0;
    static constexpr int MFVC = 0x1;
    static constexpr int MTV = 0x0;
    static constexpr int MTVC = 0x1;
    // VFPU0:
    //
    //     31---------26-----23--------------------------------------------0
    //     |=     VFPU0| VOP |                                             |
    //     ------6--------3-------------------------------------------------
    //     |--000--|--001--|--010--|--011--|--100--|--101--|--110--|--111--|
    //     | VADD  | VSUB  | VSBN  |  ---  |  ---  |  ---  |  ---  | VDIV  |
    //     |-------|-------|-------|-------|-------|-------|-------|-------|
    static constexpr int VADD = 0x00;  //
    static constexpr int VSUB = 0x01;  //
    static constexpr int VSBN = 0x02;  //
    static constexpr int VDIV = 0x07;  //
    // VFPU1:
    //
    //     31---------26-----23--------------------------------------------0
    //     |=     VFPU1| VOP |                                             |
    //     ------6--------3-------------------------------------------------
    //     |--000--|--001--|--010--|--011--|--100--|--101--|--110--|--111--|
    //     | VMUL  | VDOT  | VSCL  |  ---  | VHDP  | VCRS  | VDET  |  ---  |
    //     |-------|-------|-------|-------|-------|-------|-------|-------|
    static constexpr int VMUL = 0x00;  //
    static constexpr int VDOT = 0x01;  //
    static constexpr int VSCL = 0x02;  //
    static constexpr int VHDP = 0x04;  //
    static constexpr int VCRS = 0x05;  //
    static constexpr int VDET = 0x06;  //
    // VFPU3:
    //
    //     31---------26-----23--------------------------------------------0
    //     |=     VFPU3| VOP |                                             |
    //     ------6--------3-------------------------------------------------
    //     |--000--|--001--|--010--|--011--|--100--|--101--|--110--|--111--|
    //     | VCMP  |  ---  | VMIN  | VMAX  |  ---  | VSCMP | VSGE  | VSLT  |
    //     |-------|-------|-------|-------|-------|-------|-------|-------|
    static constexpr int VCMP = 0x00;  //
    static constexpr int VMIN = 0x02;  //
    static constexpr int VMAX = 0x03;  //
    static constexpr int VSCMP = 0x05;  //
    static constexpr int VSGE = 0x06;  //
    static constexpr int VSLT = 0x07;  //
    // VFPU4:
    //     31---------26-----24--------------------------------------------0
    //     |=     VFPU4| VOP |                                             |
    //     ------6--------2-------------------------------------------------
    //     |-------00-------|-------01-------|------10------|------11------|
    //     |    VFPU4_0     |      ---       |    VFPU4_2   |     VWBN     |
    //     |----------------|----------------|--------------|--------------|
    static constexpr int VFPU4_0 = 0x0;  //
    static constexpr int VFPU4_1 = 0x1;  //
    static constexpr int VFPU4_2 = 0x2;  //
    static constexpr int VWBN = 0x3;  //
    // VFPU4_0:
    //     31---------26-----24--------------------------------------------0
    //     |=     VFPU4| 00  |                                             |
    //     ------6--------2-------------------------------------------------
    //     |--000--|--001--|--010--|--011--|--100--|--101--|--110--|--111--|
    //     |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |
    //     |-------|-------|-------|-------|-------|-------|-------|-------|
    //
    // VFPU4_2:
    //     31---------26-----24--------------------------------------------0
    //     |=     VFPU4| 10  |                                             |
    //     ------6--------2-------------------------------------------------
    //     |--000--|--001--|--010--|--011--|--100--|--101--|--110--|--111--|
    //     | VF2IN | VF2IZ | VF2IU | VF2ID | VI2F  |   1*  |  ---  |  ---  |
    //     |-------|-------|-------|-------|-------|-------|-------|-------|
    //     *1 : VCMOVF/VCMOVT
    static constexpr int VF2IN = 0x0;  //
    static constexpr int VF2IZ = 0x1;  //
    static constexpr int VF2IU = 0x2;  //
    static constexpr int VF2ID = 0x3;  //
    static constexpr int VI2F = 0x4;  //
    static constexpr int VFPU4_2_2 = 0x5;  //
    // VFPU4_2_2:
    //     31---------26----24----19---------------------------------------0
    //     |=     VFPU4| 10 | 101 |                                        |
    //     ------6--------2----3--------------------------------------------
    //     |-------00-------|-------01-------|------10------|------11------|
    //     |     VCMOVF     |     VCMOVT     |     ----     |     ----     |
    //     |----------------|----------------|--------------|--------------|
    static constexpr int VCMOVF = 0x0;  //
    static constexpr int VCMOVT = 0x1;  //
    // VFPU5:
    //
    //     31---------26----24---------------------------------------------0
    //     |=     VFPU5| VOP |                                             |
    //     ------6--------2-------------------------------------------------
    //     |-------00-------|-------01-------|-------10-----|------11------|
    //     |     VPFXS      |     VPFXT      |     VPFXD    |  VIIM/VFIM   |
    //     |----------------|----------------|--------------|--------------|
    static constexpr int VPFXS = 0x00;
    static constexpr int VPFXT = 0x01;
    static constexpr int VPFXD = 0x02;
    static constexpr int VFPU5_3 = 0x03;  
    //
    //     31---------------23---------------------------------------------0
    //     |=   VFPU5/VIFM  |                                              |
    //     ---------8-------------------------------------------------------
    //     |----------------0----------------|--------------1--------------|
    //     |              VIIM               |            VFIM             |
    //     |---------------------------------|-----------------------------|
    static constexpr int VIIM = 0x0;
    static constexpr int VFIM = 0x1;  
    // VFPU6:
    //
    //     31---------26-----23--------------------------------------------0
    //     |=     VFPU6| VOP |                                             |
    //     ------6--------3-------------------------------------------------
    //     |--000--|--001--|--010--|--011--|--100--|--101--|--110--|--111--|
    //     |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |
    //     |-------|-------|-------|-------|-------|-------|-------|-------|
    //
    // VFPU7:
    //
    //     31---------26-----23--------------------------------------------0
    //     |=     VFPU6| VOP |                                             |
    //     ------6--------3-------------------------------------------------
    //     |--000--|--001--|--010--|--011--|--100--|--101--|--110--|--111--|
    //     |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |
    //     |-------|-------|-------|-------|-------|-------|-------|-------|
    //
    }
}
