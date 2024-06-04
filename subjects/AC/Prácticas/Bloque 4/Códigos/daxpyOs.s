	.file	"daxpy.c"
	.text
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"Faltan argumentos de entrada (n. componentes, alpha)"
.LC3:
	.string	"Tiempo:%11.9f\t / Tama\303\261o Vectores:%d\n"
.LC4:
	.string	"/ alpha*x[%d]+y[%d]=z[%d](%8.6f*%8.6f+%8.6f=%8.6f) /\n"
.LC5:
	.string	"Tiempo:%11.9f\t / Tama\303\261o Vectores:%d\t/ alpha*x[0]+y[0]=z[0](%8.6f*%8.6f+%8.6f=%8.6f) / / alpha*x[%d]+y[%d]=z[%d](%8.6f*%8.6f+%8.6f=%8.6f) /\n"
	.section	.text.startup,"ax",@progbits
	.globl	main
	.type	main, @function
main:
.LFB24:
	.cfi_startproc
	endbr64
	pushq	%r14
	.cfi_def_cfa_offset 16
	.cfi_offset 14, -16
	pushq	%r12
	.cfi_def_cfa_offset 24
	.cfi_offset 12, -24
	pushq	%rbp
	.cfi_def_cfa_offset 32
	.cfi_offset 6, -32
	pushq	%rbx
	.cfi_def_cfa_offset 40
	.cfi_offset 3, -40
	subq	$56, %rsp
	.cfi_def_cfa_offset 96
	movq	%fs:40, %rax
	movq	%rax, 40(%rsp)
	xorl	%eax, %eax
	cmpl	$2, %edi
	jg	.L2
	movl	$1, %edi
	leaq	.LC0(%rip), %rsi
	call	__printf_chk@PLT
	orl	$-1, %edi
	call	exit@PLT
.L2:
	movq	8(%rsi), %rdi
	movq	%rsi, %rbx
	call	atoi@PLT
	movq	16(%rbx), %rdi
	movl	%eax, %r12d
	call	atof@PLT
	movq	%xmm0, %r14
	cmpl	$33554432, %r12d
	jg	.L15
	cmpl	$8, %r12d
	jg	.L3
	xorl	%eax, %eax
	movsd	.LC1(%rip), %xmm2
	leaq	x(%rip), %rdx
	leaq	y(%rip), %rcx
.L4:
	cmpl	%eax, %r12d
	jle	.L6
	cvtsi2sdl	%r12d, %xmm0
	cvtsi2sdl	%eax, %xmm1
	mulsd	%xmm2, %xmm0
	mulsd	%xmm2, %xmm1
	movaps	%xmm0, %xmm3
	addsd	%xmm1, %xmm3
	subsd	%xmm1, %xmm0
	movsd	%xmm3, (%rdx,%rax,8)
	movsd	%xmm0, (%rcx,%rax,8)
	incq	%rax
	jmp	.L4
.L15:
	movl	$33554432, %r12d
.L3:
	xorl	%ebx, %ebx
	leaq	x(%rip), %rbp
.L7:
	call	drand48@PLT
	movsd	%xmm0, 0(%rbp,%rbx,8)
	call	drand48@PLT
	leaq	y(%rip), %rax
	movsd	%xmm0, (%rax,%rbx,8)
	incq	%rbx
	cmpl	%ebx, %r12d
	jg	.L7
.L6:
	leaq	8(%rsp), %rsi
	xorl	%edi, %edi
	call	clock_gettime@PLT
	xorl	%eax, %eax
	leaq	z(%rip), %rdx
	leaq	x(%rip), %rcx
	leaq	y(%rip), %rsi
.L8:
	cmpl	%eax, %r12d
	jle	.L20
	movq	%r14, %xmm0
	mulsd	(%rcx,%rax,8), %xmm0
	addsd	(%rsi,%rax,8), %xmm0
	movsd	%xmm0, (%rdx,%rax,8)
	incq	%rax
	jmp	.L8
.L20:
	leaq	24(%rsp), %rsi
	xorl	%edi, %edi
	call	clock_gettime@PLT
	movq	32(%rsp), %rax
	subq	16(%rsp), %rax
	cvtsi2sdq	%rax, %xmm0
	movq	24(%rsp), %rax
	subq	8(%rsp), %rax
	divsd	.LC2(%rip), %xmm0
	cvtsi2sdq	%rax, %xmm1
	addsd	%xmm1, %xmm0
	cmpl	$10, %r12d
	jg	.L10
	movl	%r12d, %edx
	leaq	.LC3(%rip), %rsi
	movb	$1, %al
	xorl	%ebx, %ebx
	movl	$1, %edi
	leaq	z(%rip), %rbp
	call	__printf_chk@PLT
.L11:
	movl	%ebx, %edx
	cmpl	%ebx, %r12d
	jle	.L13
	movsd	0(%rbp,%rbx,8), %xmm3
	movl	%ebx, %r8d
	movq	%r14, %xmm0
	movl	%edx, %ecx
	leaq	y(%rip), %rax
	leaq	.LC4(%rip), %rsi
	movl	$1, %edi
	movsd	(%rax,%rbx,8), %xmm2
	leaq	x(%rip), %rax
	movsd	(%rax,%rbx,8), %xmm1
	movb	$4, %al
	incq	%rbx
	call	__printf_chk@PLT
	jmp	.L11
.L10:
	leal	-1(%r12), %ecx
	pushq	%rdx
	.cfi_def_cfa_offset 104
	leaq	z(%rip), %rdx
	movsd	z(%rip), %xmm4
	movslq	%ecx, %rax
	movl	%ecx, %r9d
	movl	%ecx, %r8d
	movl	$1, %edi
	pushq	(%rdx,%rax,8)
	.cfi_def_cfa_offset 112
	leaq	y(%rip), %rdx
	movsd	y(%rip), %xmm3
	leaq	.LC5(%rip), %rsi
	movsd	(%rdx,%rax,8), %xmm7
	movq	%r14, %xmm5
	movq	%r14, %xmm1
	leaq	x(%rip), %rdx
	movsd	(%rdx,%rax,8), %xmm6
	movsd	x(%rip), %xmm2
	movl	%r12d, %edx
	movb	$8, %al
	call	__printf_chk@PLT
	popq	%rcx
	.cfi_def_cfa_offset 104
	popq	%rsi
	.cfi_def_cfa_offset 96
.L13:
	movq	40(%rsp), %rax
	subq	%fs:40, %rax
	je	.L14
	call	__stack_chk_fail@PLT
.L14:
	addq	$56, %rsp
	.cfi_def_cfa_offset 40
	xorl	%eax, %eax
	popq	%rbx
	.cfi_def_cfa_offset 32
	popq	%rbp
	.cfi_def_cfa_offset 24
	popq	%r12
	.cfi_def_cfa_offset 16
	popq	%r14
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE24:
	.size	main, .-main
	.globl	z
	.bss
	.align 32
	.type	z, @object
	.size	z, 268435456
z:
	.zero	268435456
	.globl	y
	.align 32
	.type	y, @object
	.size	y, 268435456
y:
	.zero	268435456
	.globl	x
	.align 32
	.type	x, @object
	.size	x, 268435456
x:
	.zero	268435456
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LC1:
	.long	-1717986918
	.long	1069128089
	.align 8
.LC2:
	.long	0
	.long	1104006501
	.ident	"GCC: (Ubuntu 11.4.0-1ubuntu1~22.04) 11.4.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
