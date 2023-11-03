.section .data

#ifndef TEST	// Test por defecto
#define TEST 20
#endif

	.macro 	linea
#if TEST==1
		.int 1,2,1,2
#elif TEST==2
		.int -1,-2,-1,-2
#elif TEST==3
		.int 0x7FFFFFFF, 0x7FFFFFFF, 0x7FFFFFFF, 0x7FFFFFFF
#elif TEST==4
		.int 0x80000000, 0x80000000, 0x80000000, 0x80000000
#elif TEST==5
		.int 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF
#elif TEST==6
		.int 2000000000, 2000000000, 2000000000, 2000000000
#elif TEST==7
		.int 3000000000, 3000000000, 3000000000, 3000000000
#elif TEST==8
		.int -2000000000, -2000000000, -2000000000, -2000000000
#elif TEST==9
		.int -3000000000, -3000000000, -3000000000, -3000000000
#elif TEST>=10 && TEST<=14
		.int 1,1,1,1
#elif TEST>=15 && TEST<=19
		.int -1,-1,-1,-1
#else
	.error 	"Definir TEST entre 1..19"
#endif
	.endm



	.macro 	linea0
#if TEST>=1 && TEST<=9
		linea
#elif TEST==10
		.int 0,2,1,1
#elif TEST==11
		.int 1,2,1,1
#elif TEST==12
		.int 8,2,1,1
#elif TEST==13
		.int 15,2,1,1
#elif TEST==14
		.int 16,2,1,1
#elif TEST==15
		.int 0,-2,-1,-1
#elif TEST==16
		.int -1,-2,-1,-1
#elif TEST==17
		.int -8,-2,-1,-1
#elif TEST==18
		.int -15,-2,-1,-1
#elif TEST==19
		.int -16,-2,-1,-1
		
#else
	.error 	"Definir TEST entre 1..19"
#endif
	.endm




lista: 	linea0
		.irpc i,123	# Repite la correspondiente linea 3 veces
			linea
		.endr


longlista: 	.int (.-lista)/4
media: 	.quad 0
resto: 	.quad 0


// Añado las l en el formato para que me permita imprimir 64 bits.
formato:.ascii	"media\t= %19ld \t resto\t= %19ld\n"
		.asciz	"\t= 0x %016lx \t\t= 0x %016lx\n"


.section .text
main: .global  main

	call trabajar	# subrutina de usuario
	call imprim_C	# printf()  de libC
	call acabar_C	# exit()    de libC
	ret

trabajar:
	movq     $lista, %rdi
	movl  longlista, %esi
	push %rsi		# Guardamos el valor de %rsi (salva invocante)
	call suma		# == suma(&lista, longlista);
	pop %rsi		# Obtenemos el valor de %rsi
	
	cqto # Extensión de signo a RDX:RAX
	idivq %rsi
	movq  %rax, media
	movq  %rdx, resto
	ret

suma:
	xor  %r8, %r8 # resultado
	xor  %rcx, %rcx # i=0
bucle:

	movl  (%rdi,%rcx,4), %eax
	cltq 	# Extiende el signo a %RAX
	addq   %rax, %r8 # resultado += lista[rcx]
	inc   %rcx		 # i++
	xor   %rcx,%rsi		 # i<longlista
	jne   bucle

	movq %r8, %rax
	ret

imprim_C:			# requiere libC

	movq   media,%rcx			# 4º. Media hex
	movq   resto,%r8				# 5º. Resto hex
	movq   $formato, %rdi		# 1er
	movq   media,%rsi		# 2º Media decimal
	movq   resto,%rdx		# 3º Resto decimal
	
	call  printf
	ret

acabar_C:
	mov  media, %rdi			# requiere libC
	call exit		# ==  exit(resultado)
	ret
