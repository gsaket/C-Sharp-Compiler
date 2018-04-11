.section .data
NULL:
.int 0
a:
.int 0
m:
.int 0
p:
.int 0
t:
.int 0
temp:
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
movl $2, %eax
movl $10, %ebx
movl $1, %ecx
movl $1, %edx
movl %edx, p
movl $0, %edx
movl %eax, m
movl %ebx, a
movl %ecx, t
movl %edx, temp
movl $100, t


pushl t
call fact
addl $4, %esp


Node6:
pushl t
pushl $fmt_str
call printf

call exit



Node8:
.globl fact
.type fact, @function
fact:
pushl %ebp
movl %esp, %ebp
movl 8(%ebp), %eax
movl %eax, a

pushl a
pushl $fmt_str
call printf

movl %ebp, %esp
popl %ebp
ret

Node15:

