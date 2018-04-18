.section .data
TP1:
.int 0
a_2:
.int 0
args_2:
.int 0
b_2:
.int 0
x_2:
.int 0
z_2:
.int 0
z_3:
.int 0
z_4:
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
.globl Main
.type Main, @function
Main:
pushl %ebp
movl %esp, %ebp
movl 8(%ebp), %eax
movl $10, %ebx
movl $0, %ecx
movl $10, %edx
movl %edx, b_2
movl $15, %edx
movl %eax, args_2
movl %ebx, x_2
movl %ecx, a_2
movl %edx, z_2
pushl z_2
pushl $write_int
call printf
movl $10, %eax
movl %eax, z_3
pushl z_3
pushl $write_int
call printf
movl z_3, %eax
addl $1, %eax
movl %eax, %ebx
movl %eax, TP1
movl %ebx, z_3
pushl z_3
pushl $write_int
call printf
movl $12, %eax
movl %eax, z_4
pushl z_4
pushl $write_int
call printf
movl z_4, %eax
addl $2, %eax
movl %eax, %ebx
movl %eax, TP1
movl %ebx, z_4
pushl z_4
pushl $write_int
call printf
pushl z_3
pushl $write_int
call printf
movl %ebp, %esp
popl %ebp
ret

