.section .data
lista: 	.int 	0x10000000,0x10000000,0x10000000,0x10000000
		.int 	0x10000000,0x10000000,0x10000000,0x10000000
		.int 	0x10000000,0x10000000,0x10000000,0x10000000
		.int 	0x10000000,0x10000000,0x10000000,0x10000000

/*
	Número de elementos de la lista.
	"." es la dirección actual en memoria, y se resta la posición de lista.
	Esto es el número total de posiciones de memoria ocupadas.
	Se divide entre 4 por ser este el tamaño de un int.
*/
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
	mov	 $lista, %rbx
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
	add  (%rbx,%rdx,4), %eax 	# resultado += lista[rdx]
	jc   acarreo		 		# Comprobar acarreo
fin_acarreo:
	inc   %rdx		 			# i++
	cmp   %rdx,%rcx		 		# i<longlista
	jne   bucle

	ret

acarreo:
	inc   %esi
	jmp   fin_acarreo

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
