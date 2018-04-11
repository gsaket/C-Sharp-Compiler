.section .data
D.1737:
.int 0
D.1738:
.int 0
D.1739:
.int 0
D.1740:
.int 0
D.1741:
.int 0
D.1742:
.int 0
D.1745:
.int 0
D.1746:
.int 0
D.1747:
.int 0
D.1748:
.int 0
D.1749:
.int 0
D.1750:
.int 0
D.1752:
.int 0
a0:
.int 0
a1:
.int 0
a2:
.int 0
a3:
.int 0
a4:
.int 0
a5:
.int 0
a6:
.int 0
a7:
.int 0
b:
.int 0
b.0:
.int 0
b.1:
.int 0
c:
.int 0
fmt_str:
.ascii "%d\n\0"
fmt_str_:
.ascii "%d"
.section .bss
.section .text
.globl main
main:
Node0:
movl $10, %eax
movl $1, %ebx
movl $1, %ecx
movl $1, %edx
movl %edx, a2
movl $2, %edx
movl %edx, a3
movl $0, %edx
movl %edx, a4
movl $1, %edx
movl %edx, a5
movl $0, %edx
movl %edx, a6
movl $1, %edx
cmpl $0, %eax
movl %eax, c
movl %ebx, a0
movl %ecx, a1
movl %edx, a7
jg Node11
Node10:
jmp Node20
Node11:
movl a0, %eax
addl a1, %eax
movl %eax, %ebx
addl a2, %ebx
movl %ebx, %ecx
addl a3, %ecx
movl %ecx, %edx
addl a4, %edx
movl %edx, D.1740
movl D.1740, %edx
addl a5, %edx
movl %edx, D.1741
movl D.1741, %edx
addl a6, %edx
movl %edx, D.1742
movl D.1742, %edx
addl a7, %edx
movl %edx, b.0
movl b.0, %edx
movl %eax, D.1737
movl %ebx, D.1738
movl %ecx, D.1739
movl %edx, b
jmp Node28
Node20:
movl a0, %eax
subl a1, %eax
movl %eax, %ebx
addl a2, %ebx
movl %ebx, %ecx
addl a3, %ecx
movl %ecx, %edx
addl a4, %edx
movl %edx, D.1748
movl D.1748, %edx
addl a5, %edx
movl %edx, D.1749
movl D.1749, %edx
addl a6, %edx
movl %edx, D.1750
movl D.1750, %edx
addl a7, %edx
movl %edx, b.1
movl b.1, %edx
movl %eax, D.1745
movl %ebx, D.1746
movl %ecx, D.1747
movl %edx, b
Node28:
pushl b
pushl $fmt_str
call printf
movl $0, %eax
call exit
movl %eax, D.1752

