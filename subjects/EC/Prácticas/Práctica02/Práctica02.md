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
```



2. Sumar $N$ enteros sin signo de 32 bits sobre dos registros de 32 bits mediante extensión con ceros ($N\approx 16$).

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

Para esta versión, bastaría con ejecutar `./test.sh 1 9 2`, ya que hay 9 test y es la versión 2.



## 3. Sumar $N$ enteros con signo de 32 bits sobre dos registros de 32 bits (mediante extensión de signo, naturalmente) ($N\approx 16$)