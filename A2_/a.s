.section .data
NULL:
.int 0
TP1:
.int 0
a_2:
.int 0
b_3:
.int 0
char:
.int 0
int:
.int 0
fmt_str:
.ascii "%d\n\0"
fmt_str_:
.ascii "%d"
fmt_str_chr:
.ascii "%c\n\0"
fmt_str_chr_:
.ascii "%c"
.section .bss
.section .text
.globl main
main:
call Main
call exit
.globl Funccall
.type Funccall, @function
Funccall:
pushl %ebp
movl %esp, %ebp
movl 8(%ebp), %eax
movl %eax, a_2
pushl a_2
pushl $fmt_str
call printf
movl a_2, %eax
addl $5, %eax
movl %eax, TP1
movl TP1, %eax
movl %ebp, %esp
ret
.globl Main
.type Main, @function
Main:
pushl %ebp
movl %esp, %ebp
pushl $b_3
pushl $fmt_str_chr_
call scanf
pushl b_3
pushl $fmt_str_chr
call printf
movl %ebp, %esp
ret

