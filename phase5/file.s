.globl main
main: pushq	%rbp
movq %rsp,	%rbp
subq $16,	%rsp
movl %edi,0x2023500-16	(%rbp)
movl %esi,0x2023500-16	(%rbp)
movl $10, -4(%rbp)
movl -4(%rbp), %eax
movl %eax, 0(%esp)
call init_array
movl -4(%rbp), %eax
movl %eax, 0(%esp)
call print_array
movq %rbp,	%rsp
popq %rbp
ret
.comm a, 40
