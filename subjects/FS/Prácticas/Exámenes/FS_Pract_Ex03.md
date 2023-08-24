# Fundamentos del Software. Examen III de Prácticas.

- **Asignatura:** Fundamentos del Sofware.
- **Curso Académico:** 2018-19.
- **Grado:** Doble Grado en Ingeniería Informática y Matemáticas.
- **Grupo:** A.
<!--- **Profesor:** David Griol Barres. -->
- **Descripción:** Examen de Prácticas del Módulo I (Prácticas 1-4).
<!--- **Fecha:** 17 de abril de 2023. -->
<!-- - **Duración:** -->




## Ejercicio 1.<small style="font-size: 0.9rem; margin-left: 1rem;">[8 puntos]</small>

Construya un script `examen1.sh` que cumpla lo siguiente:
1. <u>`./examen1.sh cadenaCaracteres`:</u> Saca todos los archivos del directorio de trabajo que contenga en su nombre la `cadenaCaracteres`.
        

2. <u>`./examen1.sh nombreArchivo1 nombreArchivo2`:</u> Si no existe el archivo `nombreArchivo2`, copia el archivo `nombreArchivo1` en el archivo `nombreArchivo2`. Si ya existe el archivo `nombreArchivo2`, entonces se le añade al final del archivo `nombreArchivo2` el contenido del archivo `nombreArchivo1`.

3. <u>`./examen1.sh nombreArchivo1 nombreDirectorio `:</u> Copia el archivo `nombreArchivo1` en el directorio `nombreDirectorio`.

4. En cualquier otro caso que sea ejecutado el guión `./examen1.sh`, deberá imprimir sobre el terminal el texto que contiene los apartados 1.) hasta el 4.), que servirá de ayuda.


```bash
#!/bin/bash    
    
if [[ $# -eq 1 ]]; then
    printf "Opción 1. Sacando todos los archivos del directorio de trabajo"
    printf " que contienen en su nombre la cadena %s.\n\n" $1

    find . -type f -name "*$1*.*"

elif [[ $# == 2 ]]; then

    if [ ! -f $1 ]; then
        printf "Error. El archivo %s no existe.\n" $1;

    else # $1 existe

        if [ -d  $2 ]; then
            printf "Opción 3. Copiando el archivo %s en el directorio %s.\n\n" $1 $2

            cp $1 $2
        
        else #Opcion 2. $2 es un archivo

            if [ -f $2 ]; then
                printf "Opción 2. Se añade al final del archivo %s " $2
                printf "el contenido del archivo %s. \n\n" $1

                cat $1 >> $2
            
            else
                printf "Opción 2. Se copia en el archivo %s " $2
                printf "el archivo %s. \n\n" $1

                cp $1 $2
            
            fi #if [ -f $2 ]; then
        
        fi #if [ -d  $2]; then
    
    fi #if [ ! -f $1 ]; then

else #Num incorrecto de parámetros
    printf "Error. Número incorrecto de parámetros.";

fi
```



## Ejercicio 2.<small style="font-size: 0.9rem; margin-left: 1rem;">[2 puntos]</small>

Cree un script `examen2.sh` para que saque por pantalla solamente aquellos ficheros en `/etc` que cumplan todas las condiciones:

1. El propietario es el usuario `root`.
2. No fue modificado en las últimas 2 semanas.
3. El fichero no contiene la letra r, a y p.
4. El fichero tiene permisos de lectura para otros.

```bash
#!/bin/bash

if [[ $# -ne 0 ]]; then
    printf "Error. Número incorrecto de parámetros.\n\n"

else
    find /etc/ -type f -user root -ctime +2w -perm -004 -exec grep -L [rap] {} \;

fi
```