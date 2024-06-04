	.file	"daxpy.c"
	.text
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC0:
	.string	"Faltan argumentos de entrada (n. componentes, alpha)"
	.align 8
.LC2:
	.string	"/ alpha*x[%d]+y[%d]=z[%d](%8.6f*%8.6f+%8.6f=%8.6f) /\n"
	.align 8
.LC3:
	.string	"Tiempo:%11.9f\t / Tama\303\261o Vectores:%d\t/ alpha*x[0]+y[0]=z[0](%8.6f*%8.6f+%8.6f=%8.6f) / / alpha*x[%d]+y[%d]=z[%d](%8.6f*%8.6f+%8.6f=%8.6f) /\n"
	.align 8
.LC4:
	.string	"Tiempo:%11.9f\t / Tama\303\261o Vectores:%d\n"
	.section	.text.startup,"ax",@progbits
	.p2align 4
	.globl	main
	.type	main, @function
main:
.LFB39:
	.cfi_startproc
	endbr64
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	subq	$72, %rsp
	.cfi_def_cfa_offset 128
	movq	%fs:40, %rax
	movq	%rax, 56(%rsp)
	xorl	%eax, %eax
	cmpl	$2, %edi
	jle	.L25
	movq	8(%rsi), %rdi
	movq	%rsi, %rbp
	movl	$10, %edx
	xorl	%esi, %esi
	call	strtol@PLT
	movq	16(%rbp), %rdi
	xorl	%esi, %esi
	movq	%rax, %rbx
	movl	%eax, %r12d
	call	strtod@PLT
	movsd	%xmm0, 8(%rsp)
	cmpl	$33554432, %ebx
	jg	.L15
	cmpl	$8, %ebx
	jg	.L3
	testl	%ebx, %ebx
	jle	.L4
	pxor	%xmm1, %xmm1
	xorl	%eax, %eax
	movsd	.LC1(%rip), %xmm3
	leaq	x(%rip), %rbp
	cvtsi2sdl	%ebx, %xmm1
	leaq	y(%rip), %r13
	mulsd	%xmm3, %xmm1
	.p2align 4,,10
	.p2align 3
.L5:
	pxor	%xmm0, %xmm0
	movapd	%xmm1, %xmm2
	cvtsi2sdl	%eax, %xmm0
	mulsd	%xmm3, %xmm0
	addsd	%xmm0, %xmm2
	movsd	%xmm2, 0(%rbp,%rax,8)
	movapd	%xmm1, %xmm2
	subsd	%xmm0, %xmm2
	movsd	%xmm2, 0(%r13,%rax,8)
	addq	$1, %rax
	cmpl	%eax, %r12d
	jg	.L5
.L6:
	leaq	16(%rsp), %rsi
	xorl	%edi, %edi
	leaq	z(%rip), %r15
	call	clock_gettime@PLT
	xorl	%eax, %eax
	.p2align 4,,10
	.p2align 3
.L8:
	movsd	8(%rsp), %xmm0
	mulsd	0(%rbp,%rax,8), %xmm0
	addsd	0(%r13,%rax,8), %xmm0
	movsd	%xmm0, (%r15,%rax,8)
	addq	$1, %rax
	cmpl	%eax, %r12d
	jg	.L8
	leaq	32(%rsp), %rsi
	xorl	%edi, %edi
	call	clock_gettime@PLT
	movq	40(%rsp), %rax
	pxor	%xmm0, %xmm0
	subq	24(%rsp), %rax
	cvtsi2sdq	%rax, %xmm0
	pxor	%xmm1, %xmm1
	movq	32(%rsp), %rax
	subq	16(%rsp), %rax
	cvtsi2sdq	%rax, %xmm1
	divsd	.LC5(%rip), %xmm0
	addsd	%xmm1, %xmm0
	cmpl	$10, %r12d
	jg	.L26
	movl	%r12d, %edx
	movl	$1, %edi
	movl	$1, %eax
	xorl	%ebx, %ebx
	leaq	.LC4(%rip), %rsi
	leaq	.LC2(%rip), %r14
	call	__printf_chk@PLT
	.p2align 4,,10
	.p2align 3
.L10:
	movsd	(%r15,%rbx,8), %xmm3
	movsd	0(%rbp,%rbx,8), %xmm1
	movl	%ebx, %edx
	movl	%ebx, %ecx
	movl	%ebx, %r8d
	movq	%r14, %rsi
	movl	$1, %edi
	movl	$4, %eax
	movsd	0(%r13,%rbx,8), %xmm2
	movsd	8(%rsp), %xmm0
	addq	$1, %rbx
	call	__printf_chk@PLT
	cmpl	%ebx, %r12d
	jg	.L10
.L11:
	movq	56(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L27
	addq	$72, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	xorl	%eax, %eax
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	ret
.L15:
	.cfi_restore_state
	movl	$33554432, %r12d
.L3:
	leaq	x(%rip), %rbp
	leaq	y(%rip), %r13
	leal	-1(%r12), %eax
	leaq	8(%rbp), %rdx
	movq	%rbp, %rbx
	movq	%r13, %r15
	leaq	(%rdx,%rax,8), %r14
	.p2align 4,,10
	.p2align 3
.L7:
	call	drand48@PLT
	addq	$8, %rbx
	addq	$8, %r15
	movsd	%xmm0, -8(%rbx)
	call	drand48@PLT
	movsd	%xmm0, -8(%r15)
	cmpq	%rbx, %r14
	jne	.L7
	jmp	.L6
.L26:
	leal	-1(%r12), %ecx
	pushq	%rdx
	.cfi_def_cfa_offset 136
	movsd	0(%r13), %xmm3
	movl	%r12d, %edx
	movslq	%ecx, %rax
	movl	%ecx, %r9d
	movl	%ecx, %r8d
	movl	$1, %edi
	pushq	(%r15,%rax,8)
	.cfi_def_cfa_offset 144
	movsd	24(%rsp), %xmm5
	leaq	.LC3(%rip), %rsi
	movsd	0(%r13,%rax,8), %xmm7
	movsd	0(%rbp,%rax,8), %xmm6
	movsd	(%r15), %xmm4
	movapd	%xmm5, %xmm1
	movl	$8, %eax
	movsd	0(%rbp), %xmm2
	call	__printf_chk@PLT
	popq	%rcx
	.cfi_def_cfa_offset 136
	popq	%rsi
	.cfi_def_cfa_offset 128
	jmp	.L11
.L4:
	leaq	16(%rsp), %rsi
	xorl	%edi, %edi
	call	clock_gettime@PLT
	leaq	32(%rsp), %rsi
	xorl	%edi, %edi
	call	clock_gettime@PLT
	movq	40(%rsp), %rax
	pxor	%xmm0, %xmm0
	movl	%ebx, %edx
	subq	24(%rsp), %rax
	pxor	%xmm1, %xmm1
	movl	$1, %edi
	cvtsi2sdq	%rax, %xmm0
	movq	32(%rsp), %rax
	subq	16(%rsp), %rax
	divsd	.LC5(%rip), %xmm0
	cvtsi2sdq	%rax, %xmm1
	leaq	.LC4(%rip), %rsi
	movl	$1, %eax
	addsd	%xmm1, %xmm0
	call	__printf_chk@PLT
	jmp	.L11
.L25:
	movl	$1, %edi
	leaq	.LC0(%rip), %rsi
	call	__printf_chk@PLT
	orl	$-1, %edi
	call	exit@PLT
.L27:
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE39:
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
.LC5:
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
