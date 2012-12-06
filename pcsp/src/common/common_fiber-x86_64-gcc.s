.text
.globl _SwitchStackInternal

_SwitchStackInternal:
    // save callee-saved registers
    push		%rbp
    movq		%rsp, %rbp
    push		%rbx
    push		%r12
    push		%r13
    push		%r14
    push		%r15

    // store SIMD floating point control word
    sub			$4, %rsp
    stmxcsr		(%rsp)

    // store floating point control bytes
    sub			$4, %rsp
    fstcw		(%rsp)

    // save the old stack pointer (second arg in rsi)
    movq		%rsp, (%rsi)
    // set the new stack pointer (first arg in rdi)
    movq		%rdi, %rsp

    // restore floating point control bytes
    fnclex
    fldcw		(%rsp)
    add			$4, %rsp

    // restore SIMD floating point control word
    ldmxcsr		(%rsp)
    add			$4, %rsp

    // pop callee-saved registers
    pop			%r15
    pop			%r14
    pop			%r13
    pop			%r12
    pop			%rbx
    pop			%rbp

    retq
