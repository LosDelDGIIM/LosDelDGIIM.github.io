# Estructura de Computadores. Práctica 02.

**Autor:** Arturo Olivares Martos
***

- **Asignatura:** Estructura de Computadores.
- **Curso Académico:** 2023-24.
- **Grado:** Doble Grado en Ingeniería Informática y Matemáticas.
- **Grupo:** Único.
- **Profesor:** Ignacio Rojas Ruiz.
- **Descripción:** Práctica 2 de ED.
<!--- **Fecha:** 17 de abril de 2023. -->
<!-- - **Duración:** -->


Esta práctica consiste en calcular la media de una lista de $N$ enteros realizando los cálculos sobre registros enteros. Para ello,se hacen distintas versiones del programa `media.s`, desarrollando cada una en un apartado.

## 1. Sumar $N$ enteros sin signo de 32 bits sobre dos registros de 32 bits usando uno de ellos como acumulador de acarreos ($N \approx 16$)

Este apartado suma 16 números, con control del acarreo para que no se produzca *overflow*.

```asm
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
	cmp  %rcx,%rsi		 		# i!=longlista
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
```



## 2. Sumar $N$ enteros sin signo de 32 bits sobre dos registros de 32 bits mediante extensión con ceros ($N\approx 16$).

En este caso, para controlar el acarreo, se usa la instrucción ya implementada `ADC`.

Además, por comodidad a la hora de hacer pruebas, se usan las directivas de `C` para poder ejecutar gran cantidad de test. También se ha añadido la funcionalidad de que no se copien los 16 números iguales, sino que esto se realice mediante la instrucción `irpc`.

El código de esta versión quedaría:
```asm
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
	add  (%rdi,%rcx,4), %eax 	# resultado += lista[rcx]. Suma LSB
	adc   $0, %edx				# Suma MSB. Supongo lista[rcx] positivo, por lo que extiendo con 0s.
								# adc también suma CF, contabilizando acarreo.

	inc   %rcx		 			# i++
	cmp  %rcx,%rsi		 		# i<longlista
	jne   bucle

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
```


Para ejecutar los test, bastaría con el siguiente script:
```bash
#!/bin/bash

# Verifica que se proporcionen tres argumentos
if [ $# -ne 3 ]; then
  echo "Uso: $0 test_init test_fin version"
  exit 1
fi

test_init="$1"
test_fin="$2"
version="$3"        # Versión del ejercicio

# Bucle para ejecutar el código desde test_init hasta test_fin
for i in $(seq $test_init $test_fin); do
    gcc -x assembler-with-cpp -D TEST=$i -no-pie -g media$version.s -o media$version
    printf "__TEST%02d__%35s\n" $i "" | tr " " "-"
    ./media$version
    rm ./media$version
done
```

Para esta versión, bastaría con ejecutar `./test.sh 1 8 2`, ya que hay 8 test y es la versión 2.



## 3. Sumar $N$ enteros con signo de 32 bits sobre dos registros de 32 bits (mediante extensión de signo, naturalmente) ($N\approx 16$)

En este caso, no podemos simplemente extender con 0, como hicimos en el apartado anterior, ya que estaríamos convirtiendo números negativos en positivos. Por ello, extendemos con signo con la orden `cltd`, que extiende `%EAX` a `%EDX:%EAX`. Una vez extendidos, ya podemos sumar.

```asm
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
```


## 4. Media y resto de N enteros con signo de 32 bits calculada usando registros de 32 bits ($N\approx 16$)

En este caso, la principal diferencia es que se calcula la media. Para ello, es necesario dividir usando la orden `idiv`. El acarreo se sigue gestionando con otro registro de 32 bits.

```asm
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
media: 	.int 0
resto: 	.int 0


formato:.ascii	"media\t= %11d \t resto\t= %11d\n"
		.ascii	"\t= 0x %08x \t\t= 0x %08x\n"


.section .text
main: .global  main

	call trabajar	# subrutina de usuario
	call imprim_C	# printf()  de libC
	call acabar_C	# exit()    de libC
	ret

trabajar:
	movq	 $lista, %rdi
	movl  longlista, %esi
	push %rsi		# Guardamos el valor de %rsi (salva invocante)
	call suma		# == suma(&lista, longlista);
	pop %rsi		# Obtenemos el valor de %rsi
	idiv %esi
	mov	 %eax, media
	mov  %edx, resto
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

	mov   media,%ecx		# 4º. Media hex
	mov   resto,%r8d		# 5º. Resto hex
	mov   $formato, %rdi	# 1er
	mov   media,%esi		# 2º Media decimal
	mov   resto,%edx		# 3º Resto decimal
	
	call  printf
	ret

acabar_C:
	mov  media, %rdi			# requiere libC
	call exit		# ==  exit(resultado)
	ret
```





## 5. Media y resto de N enteros calculada en 32 y en 64 bits ($N\approx 16$)

En este caso, la principal diferencia es la extensión de signos no se hace usando dos registros, sino solo uno, usando por tanto la orden `cltq`. Por ello, ya no es necesario controlar el acarreo, ya que los números son de 32 bits pero están en registros de 64.

No obstante, a la hora de realizar la división, como reduce el número de bits tenemos que extender el signo a 128 bits, usando `cqto`.

```asm
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
	cmp   %rcx,%rsi		 # i<longlista
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
```
