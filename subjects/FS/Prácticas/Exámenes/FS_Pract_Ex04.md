# Fundamentos del Software. Examen IV de Prácticas.

- **Asignatura:** Fundamentos del Sofware.
- **Curso Académico:** 2022-23.
- **Grado:** Doble Grado en Ingeniería Informática y Matemáticas.
- **Grupo:** B.
- **Profesor:** David Griol Barres.
- **Descripción:** Examen de Prácticas. Módulo II. Prácticas 1-8.
<!--- **Fecha:** 17 de abril de 2023. -->
<!-- - **Duración:** -->




## Ejercicio 1.
A partir de los archivos `funciones.h`, `factorial.cpp`, `resta.cpp` y `main.cpp`, generar un guión makefile según lo especificado que genere un ejecutable `serie`:

1. Crear un guión makefile que realice el compilado y enlazado de los archivos
anteriores de forma correcta manteniendo las dependencias entre archivos y de la
forma más breve y compacta posible usando variables.

2. Reescribir el guión anterior usando las variables ($@, $?, $<, $^).

3. Ahora el archivo funciones.h se encuentra en una carpeta cabeceras. Ajustar el guion
creado para que se compile de forma correcta y lo más eficiente posible.

4. Añadir una orden `clean` que elimine los ficheros objeto.

```make
# Titulo Parcial_22-23_GrupoB_Ej1_Make
# Uso make -f Parcial_22-23_GrupoB_Ej1_Make


CC=g++

EJECUTABLE=serie
LIBS_DIR=./CABECERAS
SOURCE_FILES=factorial.cpp resta.cpp main.cpp

$(EJECUTABLE): factorial.o resta.o main.o
    $(CC) -go $@ $^

factorial.o: factorial.cpp
    $(CC) -c -L$(LIBS_DIR) $^

resta.o: resta.cpp
    $(CC) -c -L$(LIBS_DIR) $^

main.o: main.cpp
    $(CC) -c -L$(LIBS_DIR) $^

clean:
    rm ./*.o
```


## Ejercicio 2.
A partir del fichero `calcular.cpp`:
1. Compilarlo de forma que pueda ser ejecutado con gdb y ejecutarlo.
2. Listar el código
3. Poner puntos de ruptura en las líneas 17 y 20.
4. Mostrar el valor de todas las variables locales.
5. Mostrar todos los puntos de ruptura.
6. Mostrar el código en ensamblador.
7. Eliminar todos los puntos de ruptura.
8. Ejecutar el programa.
9. Crear un guión que contenga todos los pasos anteriores y que se ejecute sin errores.

```gdb
# Titulo Parcial_22-23_GrupoB_Ej2.gdb
# Uso gdb -x Parcial_22-23_GrupoB_Ej2.gdb <programa>

list 1,100
break 17
break 20

info locals
info breakpoints

disassemble

delete breakpoints
run
```


## Ejercicio 3.
Crear un guión en bash que cumpla lo siguiente:

Tendrá que recibir entre 2 y 4 parámetros, en caso de no hacerlo, el programa deberá finalizar e informar al usuario.

Posteriormente, el programa mostrará un menú con las siguientes opciones:

1. El programa deberá mostrar de menor a mayor los parámetros proporcionados al programa que sean números (podrá recibir enteros y decimales positivos y negativos) válidos.  
Además, deberá incluir en un fichero resultado.txt el número de números válidos.

2. El programa solicita una letra al usuario. El guión deberá comprobar que esta sea una única letra en minúscula o mayúscula, en caso de no informar al usuario.  
A continuación, se imprimirán todos los procesos que se estén ejecutando y comiencen por la letra especificada.

3. El programa solicita dos directorios al usuario. El guión deberá comprobar que ambos son directorios correctos (en caso de no, informar).  
A continuación, copiará en el segundo directorio los 5 primeros ficheros del primer directorio que tengan permiso de lectura.

4. El guión finalizará y el usuario volverá a la shell de linux.

```bash
#!/bin/bash
# Titulo Parcial_22-23_GrupoB_Ej3.fs
# Fecha 30 05 2023
# Uso ./Parcial_22-23_GrupoB_Ej3.fs


_menu(){
    printf "\n\n----------------------------------------------------------------------------------------\n"
    printf "Elija una de las siguientes opciones:\n"
    printf "\t1) Ordenar los parámetros del programa de menor a mayor.\n"
    printf "\t2) Imprimir los procesos que se estén ejecutando y comiencen por determinada letra.\n"
    printf "\t3) Copiar los 5 primeros archivos de un directorio en otro directorio.\n"
    printf "\t4) Salir\n"
}


# Comprobación del número de parámetros
if [[ $# -lt 2 || $# -gt 4 ]]; then
    echo "Se deben introducir entre 2 y 4 parámetros."
    exit 1
fi

_menu
read -p "Opción elegida: " OPCION
printf "\n\n"

while [[ $OPCION != 4 ]];
do
    case $OPCION in
        1)
            
            TMP=$(mktemp)
            OUTPUT=./resultado.txt;

            num_validos=0

            for param in "$@";
            do
                if [[ $param =~ ^[\+-]?[0-9]+(\[,][0-9]+)?$ ]]; then

                    num_validos=$(($num_validos + 1))
                    echo $param >> $TMP
                fi
            done

            num_sorted=$(sort -n $TMP)

            printf "Total de números válidos: %d\n" "$num_validos" >> $OUTPUT
            printf "Números válidos ordenados de menor a mayor:\n"
            echo $num_sorted

            rm $TMP
            ;;
            
        2)
            read -p "Introducir una letra: " LETRA

            if [[ ! $LETRA =~ ^[a-zA-Z]$ ]]; then
                printf "Error. %s no es una letra válida.\n" "$LETRA"
            else
                printf "Los procesos que empiezan con la letra %s son:\n" "$LETRA"
                ps -e | egrep --color "[0-9]{2}\s$LETRA"
            fi
            ;;
        3)  
            read -p "Introducir un directorio: " DIR_1
            read -p "Introducir un segundo directorio: " DIR_2

            eval DIR_1="$DIR_1"
            eval DIR_2="$DIR_2"

            if [[ -dr "$DIR_1" && -dw "$DIR_2" ]]; then
                num_legibles=0
                for archivo in $DIR_1/*;
                do
                    if [[ -fr $archivo ]]; then

                        cp "$archivo" "$DIR_2"/
                        num_legibles=$(($num_legibles + 1))

                        if [[ $num_legibles -eq 5 ]]; then
                            # Numero máximo de archivos legibles copiados
                            break
                        fi
                    fi
                done

            else
                printf "Error. Los directorios no son correctos\n"
            fi
            ;;
        *)
            printf "Opción %s no válida.\n" "$OPCION"
            ;;
    esac


    _menu
    read -p "Opción elegida: " OPCION
    printf "\n\n"
    
done

exit 0
```