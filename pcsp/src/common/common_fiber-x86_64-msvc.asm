.model flat, c
.code

_SwitchStackInternal PROC to:QWORD, from:QWORD
    ; save callee-saved registers
    PUSH			RBP
    MOV				RBP, RSP
    
    PUSH			RBX
    PUSH			RSI
    PUSH			RDI
    PUSH			R12
    PUSH			R13
    PUSH			R14
    PUSH			R15

    SUB				RSP, 16
    MOVAPD			[RSP], XMM6
    SUB				RSP, 16
    MOVAPD			[RSP], XMM7
    SUB				RSP, 16
    MOVAPD			[RSP], XMM8
    SUB				RSP, 16
    MOVAPD			[RSP], XMM9
    SUB				RSP, 16
    MOVAPD			[RSP], XMM10
    SUB				RSP, 16
    MOVAPD			[RSP], XMM11
    SUB				RSP, 16
    MOVAPD			[RSP], XMM12
    SUB				RSP, 16
    MOVAPD			[RSP], XMM13
    SUB				RSP, 16
    MOVAPD			[RSP], XMM14
    SUB				RSP, 16
    MOVAPD			[RSP], XMM15

    ; store SIMD floating point control word
    SUB				RSP, 4
    STMXCSR			[RSP]

    ; store floating point control bytes
    SUB				RSP, 4
    FSTCW			[RSP]

    ; force 16-byte alignment
    SUB				RSP, 4
    
    ; save the old stack pointer
    MOV				[from], RSP
    
    ; set the new stack pointer
    MOV				RSP, to

    ; force 16-byte alignment
    ADD				RSP, 4

    ; restore floating point control bytes
    FNCLEX
    FLDCW			[RSP]
    ADD				RSP, 4

    ; restore SIMD floating point control word
    LDMXCSR			[RSP]
    ADD				RSP, 4

    ; pop callee-saved registers
    MOVAPD			XMM15, [RSP]
    ADD				RSP, 16
    MOVAPD			XMM14, [RSP]
    ADD				RSP, 16
    MOVAPD			XMM13, [RSP]
    ADD				RSP, 16
    MOVAPD			XMM12, [RSP]
    ADD				RSP, 16
    MOVAPD			XMM11, [RSP]
    ADD				RSP, 16
    MOVAPD			XMM10, [RSP]
    ADD				RSP, 16
    MOVAPD			XMM9, [RSP]
    ADD				RSP, 16
    MOVAPD			XMM8, [RSP]
    ADD				RSP, 16
    MOVAPD			XMM7, [RSP]
    ADD				RSP, 16
    MOVAPD			XMM6, [RSP]
    ADD				RSP, 16

    POP				R15
    POP				R14
    POP				R13
    POP				R12
    POP				RDI
    POP				RSI
    POP				RBX
    POP				RBP

    RET
_SwitchStackInternal ENDP

end
