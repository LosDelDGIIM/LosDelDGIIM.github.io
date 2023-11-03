.section .data
lista: 	.int 	0x10000000,0x10000000,0x10000000,0x10000000
		.int 	0x10000000,0x10000000,0x10000000,0x10000000
		.int 	0x10000000,0x10000000,0x10000000,0x10000000
		.int 	0x10000000,0x10000000,0x10000000,0x10000000
/*
	Número de elementos de la lista.
	"." es la dirección actual por la que se va ensamblando, y se resta la posición de lista.
	Esto es el número total de posiciones de memoria ocupadas.
	Se divide entre 4 por ser este el tamaño de un int.
*/
longlista: 	.int (.-lista)/4

resultado: 	.quad 0

formato:.ascii	"resultado \t =   %18lu (uns)\n" # Ocupa mínimo 18 espacios. Long Unsigned
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
	xor  %rdx, %rdx # acarreo
	xor  %rax, %rax # resultado
	xor  %rcx, %rcx # i=0

bucle:
	add  (%rdi,%rcx,4), %eax 	# resultado += lista[rcx]

	jnc   fin_acarreo		 		# Comprobar acarreo
	inc	  %edx

fin_acarreo:
	inc   %rcx		 			# i++
	xor  %rcx,%rsi		 		# i!=longlista
	jne   bucle

	/* En vez de establecer como condición de parada i<longlista,
	se pone i!=longlista debido a que es una orden mucho más rápida.
	No obstante, esto también sería válido.

	cmpq  %rcx,%rsi		 		# i<longlista
	jg   bucle
	 */
	

	ret

imprim_C:			# requiere libC

	mov   %rdx,%rcx			# 4º. Acarreo
	mov   %rax,%r8			# 5º. Bits - sig de suma
	mov   $formato, %rdi	# 1er
	mov   resultado,%rsi	# 2º
	mov   resultado,%rdx	# 3º
	
	call  printf
	ret

acabar_C:
	mov resultado, %rdi			# requiere libC
	call exit		# ==  exit(resultado)
	ret
