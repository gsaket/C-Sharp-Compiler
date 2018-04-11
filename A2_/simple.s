.section .data
a:
.int 0
b:
.int 0
i:
.int 0
j:
.int 0
sum:
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
jmp Node1

.type fun, @function
fun:
pushl %ebp
mov %esp, %ebp

pushl $10
pushl $fmt_str
call printf

movl %ebp, %esp
popl %ebp
ret

Node1:
call fun

pushl $20
pushl $fmt_str
call printf


call exit

