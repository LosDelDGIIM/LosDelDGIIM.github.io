.section .data

#ifndef TEST	// Test por defecto
#define TEST 20
#endif

	.macro 	linea
	
#if TEST==1
		.int -1,-1,-1,-1
#elif TEST==2
		.int 0x04000000, 0x04000000, 0x04000000, 0x04000000
#elif TEST==3
		.int 0x08000000, 0x08000000, 0x08000000, 0x08000000
#elif TEST==4
		.int 0x10000000, 0x10000000, 0x10000000, 0x10000000
#elif TEST==5
		.int 0x7FFFFFFF, 0x7FFFFFFF, 0x7FFFFFFF, 0x7FFFFFFF
#elif TEST==6
		.int 0x80000000, 0x80000000, 0x80000000, 0x80000000
#elif TEST==7
		.int 0xF0000000, 0xF0000000, 0xF0000000, 0xF0000000
#elif TEST==8
		.int 0xF8000000, 0xF8000000, 0xF8000000, 0xF8000000
#elif TEST==9
		.int 0xF7FFFFFF, 0xF7FFFFFF, 0xF7FFFFFF, 0xF7FFFFFF
#elif TEST==10
		.int 100000000, 100000000, 100000000, 100000000
#elif TEST==11
		.int 200000000, 200000000, 200000000, 200000000
#elif TEST==12
		.int 300000000, 300000000, 300000000, 300000000
#elif TEST==13
		.int 2000000000, 2000000000, 2000000000, 2000000000
#elif TEST==14
		.int 3000000000, 3000000000, 3000000000, 3000000000
#elif TEST==15
		.int -100000000, -100000000, -100000000, -100000000
#elif TEST==16
		.int -200000000, -200000000, -200000000, -200000000
#elif TEST==17
		.int -300000000, -300000000, -300000000, -300000000
#elif TEST==18
		.int -2000000000, -2000000000, -2000000000, -2000000000
#elif TEST==19

		.int -3000000000, -3000000000, -3000000000, -3000000000
#else
	.error 	"Definir TEST entre 1..19"
#endif
	
	.endm

lista: 	.irpc i,1234	# Repite la correspondiente linea 4 veces
			linea
		.endr


longlista: 	.int (.-lista)/4
resultado: 	.quad 0


formato:.ascii	"resultado \t =   %18ld (sgn)\n" # Ocupa mínimo 18 espacios. Long Unsigned
		.ascii	"	\t = 0x%18lx (hex)\n"		 # Long Hexadecimal
		.asciz	"	\t = 0x %08x %08x \n"		 # 08x. 8 en hex, con 0 a la izquierda si es necesario.


.section .text
main: .global  main

	call trabajar	# subrutina de usuario
	call imprim_C	# printf()  de libC
	call acabar_C	# exit()    de libC
	ret

trabajar:
	movq	 $lista, %rdi
	movl  longlista, %esi
	call suma		# == suma(&lista, longlista);
	movl  %eax, resultado
	movl  %edx, (resultado+4)
	ret

suma:
	xor  %r8, %r8 # acarreo
	xor  %r9, %r9 # resultado
	xor  %r10, %r10 # i=0
bucle:

	movl  (%rdi,%r10,4), %eax
	cltd 	# Extiende el signo a %edx:%eax
	addl   %eax, %r9d # resultado += lista[rdx]
	adcl   %edx, %r8d
	inc    %r10		 # i++
	cmp   %r10,%rsi		 # i<longlista
	jne   bucle

	movl %r9d, %eax
	movl %r8d, %edx

	ret

imprim_C:			# requiere libC

	mov   %rdx,%rcx			# 4º. Acarreo
	mov   %r9d,%r8d			# 5º. Bits - sig de suma
	mov   $formato, %rdi	# 1er
	mov   resultado,%rsi	# 2º
	mov   resultado,%rdx	# 3º
	
	call  printf
	ret

acabar_C:
	mov resultado, %rdi			# requiere libC
	call exit		# ==  exit(resultado)
	ret