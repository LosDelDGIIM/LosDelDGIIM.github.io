# suma.s:
# Sumar los elementos de una lista llamando a función, pasando argumentos mediante registros
# Comprobar con "./suma; echo $?" o con depurador gdb/ddd
# SECCIÓN DE DATOS (.data, variables globales inicializadas)
.section .data
lista: .int 0x40000000,0x40000000,0x40000000,0x40000000,0x40000000,0x40000000,0x40000000,0x40000000,0x40000000  # ejs. binario 0b / hex 0x
longlista: .int (.-lista)/4             # . = contador posiciones. Aritm.etiq.
resultado: .int 0

formato: .asciz "suma = %u = 0x%x hex\n" # fmt para printf() libC
# el string "formato" sirve como argumento a la llamada printf opcional
# opción: 1) no usar printf, 2)3) usar printf/fmt/exit, 4) usar tb main
# 1) as suma.s -o suma.o
#    ld suma.o -o suma                                                      1232 B
# 2) as suma.s -o suma.o                                                    6520 B
#    ld suma.o -o suma -lc -dynamic-linker /lib64/ld-linux-x86-64.so.2
# 3) gcc suma.s -o suma –no-pie –nostartfiles                               6544 B
# 4) gcc suma.s -o suma –no-pie                                             8664 B

# SECCIÓN DE CÓDIGO (.text, instrucciones máquina)
.section .text              # PROGRAMA PRINCIPAL
# _start: .global _start      # se puede abreviar de esta forma
main: .global main        # Programa principal si se usa C runtime

    call trabajar           # subrutina de usuario
    call imprimir_C         # printf() de libC 
#   call acabar_L           # exit() del kernel Linux
    call acabar_C           # exit() de libC
    ret

trabajar:
    mov $lista, %rbx        # dirección del array lista
    mov longlista, %ecx     # número de elementos a sumar
    call suma               # llamar suma(&lista, longlista);
    mov %eax, resultado     # salvar resultado
    ret



# SUBRUTINA: int suma(int* lista, int longlista);
# entrada:  1) %rbx = dirección inicio array
#           2) %ecx = número de elementos a sumar
# salida:   %eax = resultado de la suma

suma:
    push %rdx               # preservar %rdx (se usa como índice)
    mov $0, %eax            # poner a 0 acumulador
    mov $0, %rdx            # poner a 0 índice
    
bucle:
    add (%rbx,%rdx,4), %eax # acumular i-ésimo elemento
    inc %rdx                # incrementar índice
    cmp %rdx, %rcx          # comparar con longitud
    jne bucle               # si no iguales, seguir acumulando

    pop %rdx                # recuperar %rdx antiguo
    ret

imprimir_C:
    #   si se usa esta subrutina, usar también la línea que define formato
    #   se puede linkar con ld –lc –dyn ó gcc –nostartfiles, o usar main
   mov $formato , %rdi     # traduce resultado a decimal/hexadecimal
   mov resultado, %esi     # versión libC de syscall __NR_write
   mov resultado, %edx     # ventaja: printf() con fmt "%u" / "%x"
   mov $0, %eax            # varargin sin xmm
   call printf             # == printf(formato,resultado,resultado)
   ret

acabar_L:                   # void _exit(int status);
    mov $60, %rax           # exit: servicio 60 kernel Linux
    mov resultado, %edi     # status: código a retornar (la suma)
    syscall                 # == _exit(resultado);
    ret

acabar_C:                  # void exit(int status);
   mov resultado, %edi     # status: código a retornar (la suma)
   call exit               # == exit(resultado);
   ret
