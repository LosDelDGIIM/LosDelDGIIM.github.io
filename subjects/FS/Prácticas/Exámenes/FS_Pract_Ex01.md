# Fundamentos del Software. Examen I de Prácticas.

- **Asignatura:** Fundamentos del Sofware.
- **Curso Académico:** 2022-23.
- **Grado:** Doble Grado en Ingeniería Informática y Matemáticas.
- **Grupo:** A.
- **Profesor:** David Griol Barres.
- **Descripción:** Examen de Prácticas del Módulo I (Prácticas 1-4).
- **Fecha:** 18 de abril de 2023.
<!-- - **Duración:** -->




## Ejercicio 1.<small style="font-size: 0.9rem; margin-left: 1rem;">[15 puntos]</small>

A partir del directorio personal y utilizando una única orden, crea un directorio llamado `Asignaturas`, dentro de él otros dos directorios llamados `IA` y `TOC`, y dentro de `TOC` otros dos diremtorios llamados `Teoria` y `Practicas`.

Desde el directorio `TOC`, con una única orden, crea cuatro archivos en el directorio `Practicas` llamados `practicas.jpg`, `soluciones.txt`, `practica1.gif` y `practica2.pdf`.

Desde el directorio `Practicas`, copia al directorio `Teoria` utilizando una única orden los archivos que cumplan estos dos requisitos:
1. Su nombre contenga una "p"
2. Su extensión contenga una "g".

**Nota** *Se debe adjuntar una captura de pantalla en la que aparezca el comando(s) requeridos para la resolución del ejercicio, el resultado de su ejecución, así como el nombre de usuario. Esta captura es <u>obligatoria</u> para que se evalúe el ejercicio. La no aportación de la captura implicará una calificación de 0 puntos en el ejercicio.*



```console
$ cd ~
$ mkdir -p ./Asignaturas ./Asignaturas/{IA,TOC} ./Asignaturas/TOC/{Teoria,Practicas} 

$ cd ./Asignaturas/TOC
$ touch ./Practicas/{practicas.jpg,soluciones.txt,practica1.gif,practica2.pdf}

$ cd ./Practicas
$ cp ./*p*.*g* ../Teoria/
```



## Ejercicio 2.<small style="font-size: 0.9rem; margin-left: 1rem;">[40 puntos]</small>

En la carpeta personal, construye un guion llamado `examen2223.fs` que admita tres argumentos:
1. El primero será el nombre de una variable
2. El segundo una ruta de un directorio
3. El tercero un comando:

```bash
examen2223.fs <nombre variable> <directorio> <comando>
```
El guion debe:
- Comprobar que se le están pasando tres argumentos; y si no fuera así, indicar cómo se debe ejecutar el programa para que funcione correctamente mostrando una pequeña ayuda y terminando la ejecución.
- Comprobar que el primer argurnento es un nombre válido para una variable (es decir, una combinación de letras y/o dígitos siempre que comience por una letra). En caso de que no sea así, mostrar una pequeña ayuda y terminar la ejecución.
- Comprobar que el segundo parámetro es la ruta completa de un directorio existente. En dicho caso, buscar si existe un fichero en dicho directorio cuyo nombre coincida con el primer parámetro recibido. En caso contrario, generar dicho directorio y fichero.
- Si el comando pasado como tercer argumento es `ls`, mostrar en pantalla los primeros 5 elementos que contenga el directorio recibido como segundo parámetro. Si el tercer argumento no es `ls`, ejecutar dictar argumento y en caso de que suceda cualquier tipo de error, hacer que en pantalla se muestre **únicamente** el aviso "La ejecución del comando pasado como tercer argumento no ha funcionado bien".

**Nota 1.** *Se debe adjuntar una captura de pantalla en la que aparezca el código del guion, el resultado de su ejecución, asi como el nombre de usuario. Esta captura es <u>obligatoria</u> para que se evalúe el ejercicio. La no aportación de la captura implicará una calificación de O puntos en el ejercicio. En la captura deberá aparecer, por un lado, el editor de texto abierto con el guión, y por otro, la ejecución del mismo.*

**Nota 2.** *Adjuntar también el fichero con el código del guión.*


```bash
#!/bin/bash
#Autor Arturo Olivares
#Fecha 18 04 2023
#Grupo A1
#Uso  ./examen2122-guion.fs <nombre_variable> <directorio> <comando>


# Comprobación del número de parámetros
if [[ $# -ne 3 ]]; then
    printf "Error. Sintaxis incorrecta. Su uso es el siguiente:\n"
    printf "\t./examen2122-guion.fs <nombre_variable> <directorio> <comando>\n"
    
    exit 1
fi

# Comprobación de que $1 es una variable
# (combinación de letras y/o dígitos siempre que comience por una letra)
if [[ ! $1 =~ ^([a-zA-Z])([a-zA-Z0-9])*$ ]]; then
    printf "El primer argumento debe ser una variable. Es decir, "
    printf "una combinación de letras y/o dígitos siempre que comience "
    printf "por una letra.\n"
    exit 1
fi

# Comprobación de $2
if [[ -d $2 ]]; then
    # El directorio existe
    find $2 -maxdepth 1 -type f -name $1

else
    # El directorio no existe
    mkdir $2
    touch $2/$1
fi

if [[ $3 == "ls" ]]; then
    ls -1 $2 | head -n 5
else
    error="La ejecución del comando pasado como
                tercer argumento no ha funcionado bien"
    $3 &> /dev/null || echo $error
fi

```




## Ejercicio 3.<small style="font-size: 0.9rem; margin-left: 1rem;">[15 puntos]</small>

Crea en una única línea el comando necesario para marcar en el manual de la orden `chmod` el resueltado de buscar las palabras que comiencen por la inicial de tu nombre o de tu primer apellido y terminen con la letra final de tu nombre o de tu primer apellido.

*Ejemplo: David Griol*  
*Las palabras deben empezar por "d" o "g" y terminar por "d" o "l".*

**Nota** *Se debe adjuntar una captura de pantalla en la que aparezca el comando(s) requeridos para la resolución del ejercicio, el resultado de su ejecución, así como el nombre de usuario. Esta captura es <u>obligatoria</u> para que se evalúe el ejercicio. La no aportación de la captura implicará una calificación de 0 puntos en el ejercicio.*


```console
$ man chmod | egrep --color "\<(a|o)[a-zA-Z]*(o|s)\b"
```


## Ejercicio 4.<small style="font-size: 0.9rem; margin-left: 1rem;">[10 puntos]</small>

Si tengo el archivo `mifichero` con los siguientes permisos:
```console
$ -rw-r--r--    1 david  staff   884 04 abr 10:53 mifichero
```

¿Qué orden ejecutarías para cambiar los permisos del fichero y obtener lo siguiente? Indica además cómo harías para que en caso de error al ejecutar el comando, el mensaje de error se redireccionase al fichero `errores.txt`
```console
$ -r-xr-xr-x    1 david  staff   884 04 abr 10:53 mifichero
```

**Nota** *Se debe adjuntar una captura de pantalla en la que aparezca el comando(s) requeridos para la resolución del ejercicio, el resultado de su ejecución, así como el nombre de usuario. Esta captura es <u>obligatoria</u> para que se evalúe el ejercicio. La no aportación de la captura implicará una calificación de 0 puntos en el ejercicio.*


```console
$ chmod 555 mifichero 2> errores.txt
```




## Ejercicio 5.<small style="font-size: 0.9rem; margin-left: 1rem;">[10 puntos]</small>

En una única línea, sin utilizar ";", haz que se muestre el contenido de un archivo en tu directorio `home` cuyo nombre coincida con tu nombre propio y apellido (por ejempo, *davidgriol*). En caso de que falle esa orden (no existe o cualquier otra razón), se debe crear dicho fichero e informar en pantalla al usuario sobre su creación.

**Nota** *Se debe adjuntar una captura de pantalla en la que aparezca el comando(s) requeridos para la resolución del ejercicio, el resultado de su ejecución, así como el nombre de usuario. Esta captura es <u>obligatoria</u> para que se evalúe el ejercicio. La no aportación de la captura implicará una calificación de 0 puntos en el ejercicio.*


```console
$ cat ~/arturoolivares || (touch ~arturoolivares; echo "Error. El archivo no existía. Se ha creado")
```


## Ejercicio 6.<small style="font-size: 0.9rem; margin-left: 1rem;">[10 puntos]</small>

Utilizando el carácter especial con el que podemos acceder directamente a nuestro directorio `home`, lista los últimos 3 archivos de dicho directorio cuyo tamaño sea mayor a 2000K.

**Nota** *Se debe adjuntar una captura de pantalla en la que aparezca el comando(s) requeridos para la resolución del ejercicio, el resultado de su ejecución, así como el nombre de usuario. Esta captura es <u>obligatoria</u> para que se evalúe el ejercicio. La no aportación de la captura implicará una calificación de 0 puntos en el ejercicio.*


```console
$ find ~ -type f -size +200k | tail -n 3
```