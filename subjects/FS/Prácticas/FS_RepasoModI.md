# Fundamentos del Software. Repaso Módulo I de Prácticas

- **Asignatura:** Fundamentos del Sofware.
- **Curso Académico:** 2022-23.
- **Grado:** Doble Grado en Ingeniería Informática y Matemáticas.
- **Grupo:** B.
- **Profesor:** David Griol Barres.
- **Descripción:** Repaso del Módulo I (Prácticas 1-4).
<!--- **Fecha:** 17 de abril de 2023. -->
<!-- - **Duración:** -->


## Ejercicio 1.

A partir del directorio personal y utilizando una única orden, cree un directorio llamado `repaso`, dentro de él otros dos directorios llamados `prueba1` y `prueba2` , y dentro de prueba1 otro directorio llamado `ejercicio1`.

```console
$ mkdir -p ./repaso ./repaso/prueba{1,2} ./repaso/prueba1/ejercicio1
```

## Ejercicio 2.
Situados en el directorio `ejercicio1`, con una única orden, cree cinco archivos llamados `arch1.txt`, `arch2.txt`, `arch3.txt`, `arch4.pdf` y `arch5.pdf`.

```console
$ touch arch{1,2,3}.txt arch{4,5}.pdf
```


## Ejercicio 3.
Desde el directorio `ejercicio1`, redireccione al archivo `arch1.txt` el resultado de buscar la palabra “expresiones” en la ayuda (help) de la orden `let`.

```console
$ help let | grep "expresiones" > arch1.txt
```


## Ejercicio 4.
Desde el **directorio personal**, copie los ficheros de ejercicio1 cuya extensión tenga una x al directorio `prueba2`.

```console
$ cp ./repaso/prueba1/ejercicio1/*.*x* ./repaso/prueba2
```


## Ejercicio 5.
Nuevamente desde el directorio personal, obtenga las 15 primeras líneas del manual de la orden find y añádalo al final del archivo `arch1.txt` del directorio `prueba2`.

```console
$ man find | head -n 15 >> ./repaso/prueba2/arch1.txt
```


## Ejercicio 6.
Exprese la siguiente operación aritmética e indique su resultado:
$$2+3+4+5/2$$
1. Sin decimales:
    ```console
    $ echo $((2+3+4+5/2))
    ```

2. Con decimales:
    ```console
    $ echo 2+3+4+5/2 | bc -l
    ```


## Ejercicio 7.
En la carpeta personal, construya un guión llamado `repaso` que admita dos argumentos, el primero será un directorio y el segundo será un archivo:
```console
$ repaso <nombre_directorio> <nombre_archivo>
```

El guión deberá hacer lo siguiente:
1. Comprobar que el número de argumentos es correcto, y si no fuera así, indicar cómo se debe ejecutar para que funcione correctamente. Esto es, una pequeña ayuda y terminar.

2. Si el **segundo** argumento es un archivo, escribir las tres primeras líneas en otro archivo llamado `salida` y mostrar un mensaje informando de dicha acción. En caso contrario informar del error y salir.

3. Si el **primer** argumento es un directorio, mostrar un mensaje con el número de archivos que contiene. En caso contrario crear un directorio con el nombre del primer argumento.

4. Buscar en el directorio pasado como **primer** argumento los archivos que tienen permiso de lectura y añadir el resultado de la búsqueda al final del archivo `salida`. Además, mostrar por pantalla el siguiente mensaje: "De un total de $N$ archivos, hay $X$ archivos con permiso de lectura" (siendo $N$ el número total de archivos del directorio y $X$ los que tienen permiso de lectura).

```bash
#!/bin/bash
# Titulo repaso.fs
# Uso ./repaso.fs <nombre_directorio> <nombre_archivo>


# Se comprueba que el número de argumentos es correcto
if (($# != 2)); then
    echo "Error. Se deben introducir dos parámetros."
    exit 1
fi

num_lineas=3
arch_salida=./salida

# Si es un archivo, se imprimen las $num_lineas primeras líneas 
# al archivo $arch_salida.
if [ -f $2 ]; then
    head -n $num_lineas $2 > $arch_salida
    echo "Las $num_lineas primeras líneas de $2 se guardan en $arch_salida"
else
    echo "Error. El segundo parámetro debe ser un archivo."
    exit 1
fi

# Si es un directorio, se muestran cuántos archivos tiene
num_archivos=0
if [ -d $1 ]; then
    num_archivos=$(find $1 -type f | wc -l)
    printf "El directorio %s contiene %d archivos.\n" $1 $num_archivos
else
    mkdir ./$1
fi


# En el archivo de salida se guardan los que tienen permiso de lectura
find $1 -type f -perm -444 >> $arch_salida

# En esta variable se guardan cuántos tienen permiso de lectura
archivos_lectura=$(find $1 -type f -perm -444 | wc -l)

printf "De un total de %d archivos, hay %d" $num_archivos $archivos_lectura
printf " archivos con permiso de lectura.\n" 
```


## Ejercicio 8.
Cree tres directorios con una única orden: `curso_1920` y dentro de éste, `cuatrimestre_1` y `cuatrimestre_2`.

```console
$ mkdir -p ./curso_1920/cuatrimestre_{1,2}
```


## Ejercicio 9.
Cree un archivo cuyo nombre sea `repasoMod1` en el directorio `curso_1920`. A continuación, edítelo y escriba lo siguiente:
> **DNI:** *número del DNI*  
> **Nombre y apellidos:** *nombre y apellidos*  
> **Fecha:** *fecha actual (dd/mm/aaaa)*

```console
$ touch ./curso_1920/repasoMod1

$ echo "DNI: número del DNI" >> ./curso_1920/repasoMod1
$ echo "Nombre y apellidos: Nombre y apellidos" >> ./curso_1920/repasoMod1
$ echo "Fecha: fecha" >> ./curso_1920/repasoMod1 
```


## Ejercicio 10.
Copie el archivo `repasoMod1` del directorio `curso_1920` en el directorio `cuatrimestre_1`.

```console
$ cp ./curso_1920/repasoMod1 ./curso_1920/cuatrimestre_1
```


## Ejercicio 11.
Redireccione el resultado de ejecutar la orden que obtiene la fecha actual al fichero que ha creado en el 9 (en el directorio `curso_1920`) sin destruir su contenido.

```console
$ date >> ./curso_1920/repasoMod1
```


## Ejercicio 12.
Indique qué es necesario hacer para crear una variable `RUTA` que contenga la ruta absoluta del directorio en el que nos encontramos. Compruebe con el comando correspondiente las variables locales de su sistema.

```console
$ RUTA=$(pwd)
$ set
```


## Ejercicio 13.
Obtenga las 20 últimas líneas del manual de la orden find y guárdelas en un fichero llamado `ayudafind`, dentro del directorio `cuatrimestre_2`

```console
$ man find | tail -n 20 > ./curso_1920/cuatrimestre_2/ayudafind
```


## Ejercicio 14.
En la carpeta personal, construya un guión llamado `repaso-guion` que admita tres argumentos, el primero será un directorio, el segundo una letra, y el tercero una palabra:
```console
$ repaso-guion <nombre_directorio> <letra> <palabra>
```

El guión debe:
1. Comprobar que se le están pasando tres argumentos, y si no fuera así, indicar cómo se debe ejecutar para que funcione correctamente. Esto es, dar una pequeña ayuda y terminar.

2. Crear, en caso de no existir, el directorio dado como primer argumento.

3. Comprobar que el segundo argumento sea una "f" o una "d". Si no fuera así, indicarlo con un mensaje de error y salir.

4. Encontrar la palabra dada en el **tercer** argumento de forma recursiva en los archivos existentes a partir del directorio indicado por el usuario (**primer** argumento), incluyendo el número de línea en donde se localiza el término. Almacenar el resultado de la consulta en un fichero llamado `resultado` dentro del directorio desde el que se ejecute el guión.

5. Buscar en el directorio indicado por el usuario (**primer** argumento) todos los ficheros o directorios según la letra pasada como **segundo** argumento `(f=fichero, d=directorio)`. Almacenar el resultado de la consulta al final del fichero `resultado` del apartado anterior.

```bash
#!/bin/bash
# Titulo repaso-guion.fs
# Descripción Ejercicio de repaso de las sesiones 1-4. Ejercicio 14
# Uso ./repaso-guion.fs <nombre_directorio> <letra> <palabra>


# Se comprueba que el número de argumentos es correcto
if (($# != 3)); then
    echo "Error. Se deben introducir tres parámetros."
    exit 1
fi

# Si no existe el directorio, se crea
if [ ! -d $1 ]; then
    mkdir $1
fi

#El segundo argumento debe ser una f o una d
if [[ "$2" != "d" && "$2" != "f" ]]; then
    echo "Error. El segundo parámetro debe ser una letra 'd' o 'f'."
    exit 1
fi


arch_salida=./resultado

# Busco la palabra $3 en el directorio $1 recursivamente.
# Añado el número de línea
grep -rn "$3" "$1" > $arch_salida


# Añado todos los archivos de tipo $2 al final del archivo de salida
find $1 -type $2 >> $arch_salida
```

