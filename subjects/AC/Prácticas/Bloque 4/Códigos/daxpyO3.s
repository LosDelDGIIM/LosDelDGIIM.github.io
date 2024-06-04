	.file	"daxpy.c"
	.text
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC1:
	.string	"Faltan argumentos de entrada (n. componentes, alpha)"
	.align 8
.LC5:
	.string	"/ alpha*x[%d]+y[%d]=z[%d](%8.6f*%8.6f+%8.6f=%8.6f) /\n"
	.align 8
.LC6:
	.string	"Tiempo:%11.9f\t / Tama\303\261o Vectores:%d\t/ alpha*x[0]+y[0]=z[0](%8.6f*%8.6f+%8.6f=%8.6f) / / alpha*x[%d]+y[%d]=z[%d](%8.6f*%8.6f+%8.6f=%8.6f) /\n"
	.align 8
.LC7:
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
	jle	.L34
	movq	8(%rsi), %rdi
	movq	%rsi, %rbp
	movl	$10, %edx
	xorl	%esi, %esi
	call	strtol@PLT
	movq	16(%rbp), %rdi
	xorl	%esi, %esi
	movq	%rax, %rbx
	movl	%eax, %r13d
	call	strtod@PLT
	movsd	%xmm0, 8(%rsp)
	cmpl	$33554432, %ebx
	jg	.L21
	cmpl	$8, %ebx
	jg	.L3
	testl	%ebx, %ebx
	jle	.L4
	pxor	%xmm1, %xmm1
	movsd	.LC2(%rip), %xmm6
	leal	-1(%rbx), %eax
	cvtsi2sdl	%ebx, %xmm1
	mulsd	%xmm6, %xmm1
	cmpl	$2, %eax
	jbe	.L22
	movl	%ebx, %esi
	movapd	%xmm1, %xmm3
	leaq	x(%rip), %rbp
	xorl	%ecx, %ecx
	leaq	y(%rip), %r12
	shrl	$2, %esi
	unpcklpd	%xmm3, %xmm3
	movdqa	.LC0(%rip), %xmm4
	movdqa	.LC3(%rip), %xmm8
	movapd	.LC4(%rip), %xmm5
	movq	%rbp, %rdx
	movq	%r12, %rax
.L6:
	movdqa	%xmm4, %xmm0
	addl	$1, %ecx
	paddd	%xmm8, %xmm4
	addq	$32, %rdx
	cvtdq2pd	%xmm0, %xmm2
	mulpd	%xmm5, %xmm2
	pshufd	$238, %xmm0, %xmm0
	addq	$32, %rax
	cvtdq2pd	%xmm0, %xmm0
	mulpd	%xmm5, %xmm0
	movapd	%xmm2, %xmm7
	addpd	%xmm3, %xmm7
	movaps	%xmm7, -32(%rdx)
	movapd	%xmm0, %xmm7
	addpd	%xmm3, %xmm7
	movaps	%xmm7, -16(%rdx)
	movapd	%xmm3, %xmm7
	subpd	%xmm2, %xmm7
	movapd	%xmm3, %xmm2
	subpd	%xmm0, %xmm2
	movaps	%xmm7, -32(%rax)
	movaps	%xmm2, -16(%rax)
	cmpl	%ecx, %esi
	jne	.L6
	movl	%ebx, %eax
	andl	$-4, %eax
	testb	$3, %bl
	je	.L7
.L5:
	pxor	%xmm0, %xmm0
	movapd	%xmm1, %xmm2
	movslq	%eax, %rdx
	cvtsi2sdl	%eax, %xmm0
	mulsd	%xmm6, %xmm0
	addsd	%xmm0, %xmm2
	movsd	%xmm2, 0(%rbp,%rdx,8)
	movapd	%xmm1, %xmm2
	subsd	%xmm0, %xmm2
	movsd	%xmm2, (%r12,%rdx,8)
	leal	1(%rax), %edx
	cmpl	%ebx, %edx
	jge	.L7
	pxor	%xmm0, %xmm0
	movapd	%xmm1, %xmm2
	addl	$2, %eax
	cvtsi2sdl	%edx, %xmm0
	movslq	%edx, %rdx
	mulsd	%xmm6, %xmm0
	addsd	%xmm0, %xmm2
	movsd	%xmm2, 0(%rbp,%rdx,8)
	movapd	%xmm1, %xmm2
	subsd	%xmm0, %xmm2
	movsd	%xmm2, (%r12,%rdx,8)
	cmpl	%ebx, %eax
	jge	.L8
	pxor	%xmm0, %xmm0
	movapd	%xmm1, %xmm2
	cvtsi2sdl	%eax, %xmm0
	cltq
	mulsd	%xmm6, %xmm0
	addsd	%xmm0, %xmm2
	subsd	%xmm0, %xmm1
	movsd	%xmm2, 0(%rbp,%rax,8)
	movsd	%xmm1, (%r12,%rax,8)
.L8:
	xorl	%edi, %edi
	leaq	16(%rsp), %rsi
	call	clock_gettime@PLT
	testl	%ebx, %ebx
	movl	$1, %ecx
	cmovg	%ebx, %ecx
	jmp	.L19
.L21:
	movl	$33554432, %r13d
.L3:
	leaq	x(%rip), %rbp
	leaq	y(%rip), %r12
	leal	-1(%r13), %eax
	leaq	8(%rbp), %rdx
	movq	%rbp, %rbx
	movq	%r12, %r15
	leaq	(%rdx,%rax,8), %r14
	.p2align 4,,10
	.p2align 3
.L9:
	call	drand48@PLT
	addq	$8, %rbx
	addq	$8, %r15
	movsd	%xmm0, -8(%rbx)
	call	drand48@PLT
	movsd	%xmm0, -8(%r15)
	cmpq	%r14, %rbx
	jne	.L9
	xorl	%edi, %edi
	leaq	16(%rsp), %rsi
	call	clock_gettime@PLT
	testl	%r13d, %r13d
	movl	$1, %ecx
	cmovg	%r13d, %ecx
.L19:
	movsd	8(%rsp), %xmm1
	movl	%ecx, %edx
	xorl	%eax, %eax
	shrl	%edx
	leaq	z(%rip), %r15
	unpcklpd	%xmm1, %xmm1
	salq	$4, %rdx
	.p2align 4,,10
	.p2align 3
.L12:
	movapd	0(%rbp,%rax), %xmm0
	mulpd	%xmm1, %xmm0
	addpd	(%r12,%rax), %xmm0
	movaps	%xmm0, (%r15,%rax)
	addq	$16, %rax
	cmpq	%rax, %rdx
	jne	.L12
	movl	%ecx, %eax
	andl	$-2, %eax
	andl	$1, %ecx
	je	.L11
.L18:
	cltq
	movsd	8(%rsp), %xmm0
	mulsd	0(%rbp,%rax,8), %xmm0
	addsd	(%r12,%rax,8), %xmm0
	movsd	%xmm0, (%r15,%rax,8)
.L11:
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
	divsd	.LC8(%rip), %xmm0
	addsd	%xmm1, %xmm0
	cmpl	$10, %r13d
	jg	.L35
	movl	%r13d, %edx
	movl	$1, %edi
	movl	$1, %eax
	xorl	%ebx, %ebx
	leaq	.LC7(%rip), %rsi
	leaq	.LC5(%rip), %r14
	call	__printf_chk@PLT
	.p2align 4,,10
	.p2align 3
.L14:
	movsd	(%r15,%rbx,8), %xmm3
	movsd	(%r12,%rbx,8), %xmm2
	movl	%ebx, %edx
	movl	%ebx, %ecx
	movl	%ebx, %r8d
	movq	%r14, %rsi
	movl	$1, %edi
	movl	$4, %eax
	movsd	0(%rbp,%rbx,8), %xmm1
	movsd	8(%rsp), %xmm0
	addq	$1, %rbx
	call	__printf_chk@PLT
	cmpl	%ebx, %r13d
	jg	.L14
.L15:
	movq	56(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L36
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
.L35:
	.cfi_restore_state
	leal	-1(%r13), %ecx
	pushq	%rdx
	.cfi_def_cfa_offset 136
	movsd	z(%rip), %xmm4
	leaq	.LC6(%rip), %rsi
	movslq	%ecx, %rax
	movl	%ecx, %r9d
	movl	%ecx, %r8d
	movl	%r13d, %edx
	pushq	(%r15,%rax,8)
	.cfi_def_cfa_offset 144
	movsd	24(%rsp), %xmm5
	movl	$1, %edi
	movsd	(%r12,%rax,8), %xmm7
	movsd	0(%rbp,%rax,8), %xmm6
	movsd	y(%rip), %xmm3
	movapd	%xmm5, %xmm1
	movl	$8, %eax
	movsd	x(%rip), %xmm2
	call	__printf_chk@PLT
	popq	%rcx
	.cfi_def_cfa_offset 136
	popq	%rsi
	.cfi_def_cfa_offset 128
	jmp	.L15
.L7:
	xorl	%edi, %edi
	leaq	16(%rsp), %rsi
	leaq	z(%rip), %r15
	call	clock_gettime@PLT
	testl	%ebx, %ebx
	movl	$1, %ecx
	cmovg	%ebx, %ecx
	xorl	%eax, %eax
	subl	$1, %ebx
	je	.L18
	jmp	.L19
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
	divsd	.LC8(%rip), %xmm0
	cvtsi2sdq	%rax, %xmm1
	leaq	.LC7(%rip), %rsi
	movl	$1, %eax
	addsd	%xmm1, %xmm0
	call	__printf_chk@PLT
	jmp	.L15
.L22:
	xorl	%eax, %eax
	leaq	x(%rip), %rbp
	leaq	y(%rip), %r12
	jmp	.L5
.L36:
	call	__stack_chk_fail@PLT
.L34:
	movl	$1, %edi
	leaq	.LC1(%rip), %rsi
	call	__printf_chk@PLT
	orl	$-1, %edi
	call	exit@PLT
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
	.section	.rodata.cst16,"aM",@progbits,16
	.align 16
.LC0:
	.long	0
	.long	1
	.long	2
	.long	3
	.set	.LC2,.LC4
	.align 16
.LC3:
	.long	4
	.long	4
	.long	4
	.long	4
	.align 16
.LC4:
	.long	-1717986918
	.long	1069128089
	.long	-1717986918
	.long	1069128089
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LC8:
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
