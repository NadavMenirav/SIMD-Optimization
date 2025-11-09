.section .data


.section .text
.globl strlen_sse42
.type strlen_sse42, @function

strlen_sse42:
    pushq %rcx #administrations
    xorl %ecx, %ecx

    pxor xmm0, xmm0 # The null terminator string
    movdqu (%rdi), xmm1 # the first 16 bytes of our string

    xorl %eax, %eax # zero the eax register

    xorl %esi %esi #counter

loop: # while we did not reach the end of the string
    pcmpistri xmm0, xmm1, 0x08 # first index that they are equal
    add %ecx, %esi # add the number of matches to our counter
    cmpl 16, %ecx #if we did not reach the null terminator on our string
    je loop
    jump outside

outside:
    movl %esi, %eax # our return value, number of chars in the string

