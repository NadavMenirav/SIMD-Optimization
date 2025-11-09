.section .text
.globl strlen_sse42

strlen_sse42:
    pushq %rcx #administrations
    xorl %ecx, %ecx

    pxor xmm0, xmm0 # The null terminator string
    movdqu (%rdi), xmm1 # the first 16 bytes of our string

    xorl %eax, %eax # zero the eax register

loop: # while we did not reach the end of the string
    pcmpistri xmm0, xmm1, 0x08 # first index that they are equal
    cmpl 16, %ecx
    je loop
    jump outside

