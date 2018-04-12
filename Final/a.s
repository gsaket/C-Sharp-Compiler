.section .data
Program.d:
.int 0
Program.l:
.int 0
Program.m:
.int 0
Program.p:
.int 0
TP1:
.int 0
TP2:
.int 0
TP3:
.int 0
TP4:
.int 0
l:
.int 0
m:
.int 0
x_4:
.int 0
x_5:
.int 0
y_2:
.int 0
y_5:
.int 0
write_int:
.ascii "%d\n\0"
read_int:
.ascii "%d"
.section .bss
.section .text
.globl main
main:
call Main
call exit
movl $6, %eax
movl Program.d, %ebx
movl %eax, l
movl %ebx, m
.globl fact
.type fact, @function
fact:
pushl %ebp
movl %esp, %ebp
movl 8(%ebp), %eax
movl %eax, %ebx
cmpl $1, %ebx
je EQ10
movl $0, %ebx
jmp NEQ10
EQ10: 
movl $1, %ebx
NEQ10:
movl $1, %ecx
cmpl %ebx, %ecx
movl %eax, y_2
movl %ebx, TP1
je L1
jmp L2
L1: 
movl $1, %eax
movl %ebp, %esp
popl %ebp
ret
L2: 
movl y_2, %eax
subl $1, %eax
pushl y_2
pushl %eax
movl %eax, TP2
call fact
addl $4, %esp
pop y_2
movl %eax, TP3
movl y_2, %eax
imul TP3, %eax
movl %eax, TP4
movl TP4, %eax
movl %ebp, %esp
popl %ebp
ret
.globl doublefact
.type doublefact, @function
doublefact:
pushl %ebp
movl %esp, %ebp
movl 8(%ebp), %eax
pushl %eax
pushl %eax
movl %eax, x_4
call fact
addl $4, %esp
pop x_4
movl %eax, TP1
movl Program.d, %eax
imul TP1, %eax
movl %eax, TP2
movl TP2, %eax
movl %ebp, %esp
popl %ebp
ret
.globl Main
.type Main, @function
Main:
pushl %ebp
movl %esp, %ebp
movl $2, %eax
movl $5, %ebx
pushl %ebx
pushl x_5
pushl %ebx
movl %eax, Program.d
movl %ebx, y_5
call doublefact
addl $4, %esp
pop x_5
pop y_5
movl %eax, TP1
movl TP1, %eax
movl %eax, x_5
pushl x_5
pushl $write_int
call printf
movl %ebp, %esp
popl %ebp
ret

