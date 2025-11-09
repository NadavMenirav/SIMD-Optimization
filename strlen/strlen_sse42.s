.section .data


.section .text
.globl strlen_sse42
.type strlen_sse42, @function

strlen_sse42:
    pushq %rcx #administrations
    xorl %ecx, %ecx

    pxor %xmm0, %xmm0 # The null terminator string

    xorl %eax, %eax # zero the eax register

    xorl %esi, %esi #counter

loop: # while we did not reach the end of the string
    movdqu (%rdi), %xmm1 # the first 16 bytes of our string
    pcmpistri  $0x08, %xmm0, %xmm1 # first index that they are equal

    addl %ecx, %esi # add the number of matches to our counter
    cmpl $16, %ecx #if we did not reach the null terminator on our string
    je add # we need to move te string 16 bytes ahead

    jmp outside #else

add:
    addq $16, %rdi
    jmp loop

outside:
    movl %esi, %eax # our return value, number of chars in the string
    ret

