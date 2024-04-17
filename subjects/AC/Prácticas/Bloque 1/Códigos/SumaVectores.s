	.file	"SumaVectores.c"
	.text
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC0:
	.string	"Faltan n\302\272 componentes del vector"
	.align 8
.LC2:
	.string	"/ V1[%d]+V2[%d]=V3[%d](%8.6f+%8.6f=%8.6f) /\n"
	.align 8
.LC3:
	.string	"Tiempo:%11.9f\t / Tama\303\261o Vectores:%u\t/ V1[0]+V2[0]=V3[0](%8.6f+%8.6f=%8.6f) / / V1[%d]+V2[%d]=V3[%d](%8.6f+%8.6f=%8.6f) /\n"
	.align 8
.LC4:
	.string	"Tiempo:%11.9f\t / Tama\303\261o Vectores:%u\n"
	.section	.text.startup,"ax",@progbits
	.p2align 4
	.globl	main
	.type	main, @function
main:
.LFB20:
	.cfi_startproc
	pushq	%r13
	.cfi_def_cfa_offset 16
	.cfi_offset 13, -16
	pushq	%r12
	.cfi_def_cfa_offset 24
	.cfi_offset 12, -24
	pushq	%rbp
	.cfi_def_cfa_offset 32
	.cfi_offset 6, -32
	pushq	%rbx
	.cfi_def_cfa_offset 40
	.cfi_offset 3, -40
	subq	$40, %rsp
	.cfi_def_cfa_offset 80
	cmpl	$1, %edi
	jle	.L24
	movq	8(%rsi), %rdi
	movl	$10, %edx
	xorl	%esi, %esi
	call	strtol
	movl	%eax, %ebp
	cmpl	$33554432, %eax
	ja	.L14
	cmpl	$8, %eax
	ja	.L3
	testl	%eax, %eax
	je	.L4
	pxor	%xmm1, %xmm1
	movsd	.LC1(%rip), %xmm3
	cvtsi2sdl	%eax, %xmm1
	xorl	%eax, %eax
	mulsd	%xmm3, %xmm1
	.p2align 4,,10
	.p2align 3
.L5:
	pxor	%xmm0, %xmm0
	movapd	%xmm1, %xmm2
	cvtsi2sdl	%eax, %xmm0
	mulsd	%xmm3, %xmm0
	addsd	%xmm0, %xmm2
	movsd	%xmm2, v1(,%rax,8)
	movapd	%xmm1, %xmm2
	subsd	%xmm0, %xmm2
	movsd	%xmm2, v2(,%rax,8)
	addq	$1, %rax
	cmpl	%eax, %ebp
	ja	.L5
.L6:
	movq	%rsp, %rsi
	xorl	%edi, %edi
	call	clock_gettime
	xorl	%eax, %eax
	.p2align 4,,10
	.p2align 3
.L8:
	movsd	v1(,%rax,8), %xmm0
	addsd	v2(,%rax,8), %xmm0
	movsd	%xmm0, v3(,%rax,8)
	addq	$1, %rax
	cmpl	%eax, %ebp
	ja	.L8
	leaq	16(%rsp), %rsi
	xorl	%edi, %edi
	call	clock_gettime
	movq	24(%rsp), %rax
	pxor	%xmm0, %xmm0
	subq	8(%rsp), %rax
	cvtsi2sdq	%rax, %xmm0
	pxor	%xmm1, %xmm1
	movq	16(%rsp), %rax
	subq	(%rsp), %rax
	cvtsi2sdq	%rax, %xmm1
	divsd	.LC5(%rip), %xmm0
	addsd	%xmm1, %xmm0
	cmpl	$9, %ebp
	jbe	.L25
	leal	-1(%rbp), %eax
	movl	%ebp, %esi
	movl	$.LC3, %edi
	movsd	v3(%rip), %xmm3
	movsd	v2(%rip), %xmm2
	movq	%rax, %rdx
	movl	%eax, %r8d
	movl	%eax, %ecx
	movsd	v3(,%rax,8), %xmm6
	movsd	v1(%rip), %xmm1
	movsd	v2(,%rax,8), %xmm5
	movsd	v1(,%rax,8), %xmm4
	movl	$7, %eax
	call	printf
.L20:
	addq	$40, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 40
	xorl	%eax, %eax
	popq	%rbx
	.cfi_def_cfa_offset 32
	popq	%rbp
	.cfi_def_cfa_offset 24
	popq	%r12
	.cfi_def_cfa_offset 16
	popq	%r13
	.cfi_def_cfa_offset 8
	ret
.L14:
	.cfi_restore_state
	movl	$33554432, %ebp
.L3:
	xorl	%edi, %edi
	movl	%ebp, %r13d
	xorl	%ebx, %ebx
	call	time
	movl	%eax, %edi
	call	srand
	.p2align 4,,10
	.p2align 3
.L7:
	call	rand
	movl	%eax, %r12d
	call	rand
	pxor	%xmm0, %xmm0
	pxor	%xmm1, %xmm1
	cvtsi2sdl	%eax, %xmm1
	cvtsi2sdl	%r12d, %xmm0
	divsd	%xmm1, %xmm0
	movsd	%xmm0, v1(,%rbx,8)
	call	rand
	movl	%eax, %r12d
	call	rand
	pxor	%xmm0, %xmm0
	pxor	%xmm1, %xmm1
	cvtsi2sdl	%r12d, %xmm0
	cvtsi2sdl	%eax, %xmm1
	divsd	%xmm1, %xmm0
	movsd	%xmm0, v2(,%rbx,8)
	addq	$1, %rbx
	cmpq	%rbx, %r13
	jne	.L7
	jmp	.L6
.L25:
	movl	%ebp, %esi
	movl	$.LC4, %edi
	movl	$1, %eax
	xorl	%ebx, %ebx
	call	printf
	.p2align 4,,10
	.p2align 3
.L10:
	movsd	v1(,%rbx,8), %xmm0
	movl	%ebx, %esi
	movl	%ebx, %ecx
	movl	%ebx, %edx
	movsd	v3(,%rbx,8), %xmm2
	movl	$.LC2, %edi
	movl	$3, %eax
	movsd	v2(,%rbx,8), %xmm1
	addq	$1, %rbx
	call	printf
	cmpl	%ebx, %ebp
	ja	.L10
	jmp	.L20
.L4:
	movq	%rsp, %rsi
	xorl	%edi, %edi
	call	clock_gettime
	leaq	16(%rsp), %rsi
	xorl	%edi, %edi
	call	clock_gettime
	movq	24(%rsp), %rax
	pxor	%xmm0, %xmm0
	xorl	%esi, %esi
	subq	8(%rsp), %rax
	pxor	%xmm1, %xmm1
	movl	$.LC4, %edi
	cvtsi2sdq	%rax, %xmm0
	movq	16(%rsp), %rax
	subq	(%rsp), %rax
	divsd	.LC5(%rip), %xmm0
	cvtsi2sdq	%rax, %xmm1
	movl	$1, %eax
	addsd	%xmm1, %xmm0
	call	printf
	jmp	.L20
.L24:
	movl	$.LC0, %edi
	call	puts
	orl	$-1, %edi
	call	exit
	.cfi_endproc
.LFE20:
	.size	main, .-main
	.globl	v3
	.bss
	.align 32
	.type	v3, @object
	.size	v3, 268435456
v3:
	.zero	268435456
	.globl	v2
	.align 32
	.type	v2, @object
	.size	v2, 268435456
v2:
	.zero	268435456
	.globl	v1
	.align 32
	.type	v1, @object
	.size	v1, 268435456
v1:
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
	.ident	"GCC: (GNU) 11.2.1 20220127 (Red Hat 11.2.1-9)"
	.section	.note.GNU-stack,"",@progbits
