.text
.globl _SwitchStackInternal

_SwitchStackInternal:
    // save callee-saved registers
    push		%ebp
    movl		%esp, %ebp
    push		%ebx
    push		%esi
    push		%edi

    // store SIMD floating point control word
    sub			$4, %esp
    stmxcsr		(%esp)

    // store floating point control bytes
    sub			$4, %esp
    fstcw		(%esp)

    // save the old stack pointer
    movl		0x20(%esp), %edx // 8+4*6 = 32
    movl		%esp, (%edx)
    
    // set the new stack pointer
    movl		0x1C(%esp), %esp // 4+4*6 = 28

    // restore floating point control bytes
    fnclex
    fldcw		(%esp)
    add			$4, %esp

    // restore SIMD floating point control word
    ldmxcsr		(%esp)
    add			$4, %esp

    // pop callee-saved registers
    pop			%edi
    pop			%esi
    pop			%ebx
    pop			%ebp

    ret
