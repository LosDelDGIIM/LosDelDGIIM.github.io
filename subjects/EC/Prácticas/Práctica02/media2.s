.section .data

#ifndef TEST	// Test por defecto
#define TEST 9
#endif

	.macro 	linea
						# Resultado - Comentario
#if TEST==1				// 16 - Ejemplo sencillo
		.int 1,1,1,1
#elif TEST==2			// 0x0 ffff fff0 	- Máximo para que no se produzca acarreo
		.int 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF
#elif TEST==3			// 0x1 0000 0000	- Mínimo para que se produzca acarreo
		.int 0x10000000, 0x10000000, 0x10000000, 0x10000000
#elif TEST==4
		.int 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF
#elif TEST==5
		.int -1,-1,-1,-1
#elif TEST==6
		.int 200000000, 200000000, 200000000, 200000000
#elif TEST==7
		.int 300000000, 300000000, 300000000, 300000000
#elif TEST==8
		.int 5000000000, 5000000000, 5000000000, 5000000000
#else
	.error 	"Definir TEST entre 1..8"
#endif
	
	.endm

lista: 	.irpc i,1234	# Repite la correspondiente linea 4 veces
			linea
		.endr


longlista: 	.int (.-lista)/4
resultado: 	.quad 0


formato:.ascii	"resultado \t =   %18lu (uns)\n" # Ocupa mínimo 18 espacios. Unsigned
		.ascii	"	\t = 0x%18lx (hex)\n"
		.asciz	"	\t = 0x %08x %08x \n"


.section .text
main: .global  main

	call trabajar	# subrutina de usuario
	call imprim_C	# printf()  de libC
#	call acabar_L	# exit()   del kernel Linux
	call acabar_C	# exit()    de libC
	ret

trabajar:
	mov     $lista, %rbx
	mov  longlista, %ecx
	call suma		# == suma(&lista, longlista);
	mov  %eax, resultado
	mov  %esi, (resultado+4)
	ret

suma:
	mov  $0, %esi # acarreo
	mov  $0, %eax # resultado
	mov  $0, %rdx # i=0
bucle:
	add  (%rbx,%rdx,4), %eax # resultado += lista[rdx]
	adc   $0, %esi
	inc   %rdx		 # i++
	cmp   %rdx,%rcx		 # i<longlista
	jne   bucle

	ret

imprim_C:			# requiere libC

	mov   %rsi,%rcx			# 4º. Acarreo
	mov   %rax,%r8			# 5º. Bits - sig de suma
	mov   $formato, %rdi	# 1er
	mov   resultado,%rsi	# 2º
	mov   resultado,%rdx	# 3º
	
	call  printf
	ret

acabar_L:
	mov        $60, %rax
	mov  resultado, %rdi
	syscall			# == _exit(resultado)
	ret

acabar_C:
	mov resultado, %rdi			# requiere libC
	call exit		# ==  exit(resultado)
	ret
