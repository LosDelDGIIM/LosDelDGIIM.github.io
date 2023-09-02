# Fundamentos del Software. Examen II de Prácticas.

**Autor:** Arturo Olivares Martos
***

- **Asignatura:** Fundamentos del Sofware.
- **Curso Académico:** 2022-23.
- **Grado:** Doble Grado en Ingeniería Informática y Matemáticas.
- **Grupo:** B.
- **Profesor:** David Griol Barres.
- **Descripción:** Examen de Prácticas del Módulo I (Prácticas 1-4).
- **Fecha:** 17 de abril de 2023.
<!-- - **Duración:** -->




## Ejercicio 1.<small style="font-size: 0.9rem; margin-left: 1rem;">[15 puntos]</small>

Asigna a una variable `variable2023` el resultado de comprobar si un archivo `archivo2023` tiene permiso de lectura o ejecución e imprime el resultado.

**Nota** *Se debe adjuntar una captura de pantalla en la que aparezca el comando(s) requeridos para la resolución del ejercicio, el resultado de su ejecución, así como el nombre de usuario. Esta captura es <u>obligatoria</u> para que se evalúe el ejercicio. La no aportación de la captura implicará una calificación de 0 puntos en el ejercicio.*

```console
$ nom_archivo="archivo2023"

$ variable2023=$( [[ -r ./$nom_archivo || -x ./$nom_archivo ]]
                    && echo "true" || echo "false" )

$ printf "La variable variable2023 vale: %s.\n" $variable2023
```



## Ejercicio 2.<small style="font-size: 0.9rem; margin-left: 1rem;">[40 puntos]</small>

Crear un guión llamado `examen170423.fs` con la siguiente sintaxis:
```console
$ examen170423.fs <ruta_directorio> <numero_entero> <comando_Linux>
```

Este deberá:
- Comprobar que se le están pasando tres argumentos, y si no fuera así, indicar cómo debe ejecutarse correctamente mostrando una pequeña ayuda en pantalla y terminando la ejecución.

- Comprobar si el primer parámetro es tu directorio home. En caso de no coincidir, avisar al usuario de la no coincidencia e indicar si el parámetro proporcionado es un directorio existente o no, terminando a continuación la ejecución.

- Comprobar que el segundo parámetro sea un número entero positivo. Si no fuera así,  mostrar en pantalla un mensaje de error y terminar la ejecución. Si se trata de un número entero:

    - Comprobar si existe el fichero AyudaComandos.txt en el directorio pasado como primer parámetro. Generar ese fichero en caso de que no exista.

    - Comprobar si la palabra proporcionada como tercer parámetro coincide con los comandos `chmod`, `ls` o `mv`. En dicho caso, copiar al final del fichero `AyudaComandos.txt` el resultado de `<numero_entero>` últimas líneas de la ayuda del comando proporcionado como tercer parámetro. En caso contrario, añadir al fichero `AyudaComandos.txt` la frase "Comando proporcionado no válido".

    - Mostrar por pantalla el contenido del fichero `AyudaComandos.txt`

**Nota 1.** *Se debe adjuntar una captura de pantalla en la que aparezca el código del guion, el resultado de su ejecución, asi como el nombre de usuario. Esta captura es <u>obligatoria</u> para que se evalúe el ejercicio. La no aportación de la captura implicará una calificación de O puntos en el ejercicio. En la captura deberá aparecer, por un lado, el editor de texto abierto con el guión, y por otro, la ejecución del mismo.*

**Nota 2.** *Adjuntar también el fichero con el código del guión.*


```bash
#!/bin/bash
# Nombre examen170423.fs
# Autor Arturo Olivares Martos
# Fecha 17 04 23
# Grupo A1
# Uso: examen170423.fs <ruta_directorio> <numero_entero> <comando_Linux>

# Comprobación del número de argumentos
if [[ $# -ne 3 ]]; then
    printf "Error. Numero de parámetros incorrecto.\n"
    exit 1
fi

# Comprobación de que sea el directorio HOME
if [[ $1 != $HOME ]]; then
    if [[ -d $1 ]]; then
        printf "El directorio %s no es el directorio Home(~) pero existe.\n" $1
    else
        printf "El directorio %s no es el directorio Home(~) ni existe.\n" $1
    fi

    exit 1
fi

# Comprobación en el caso de que no sea un entero positivo.
if ! [[ ( $2 =~ ^\+?[0-9]+$ ) ]]; then
    printf "El segundo parámetro no es un entero positivo.\n"
    exit 1
fi

# Ya se dan todas las condiciones necesarias
salida="AyudaComandos.txt"

# Si el archivo no existe, se crea
if [[ ! -f $1/$salida ]]; then
    touch $1/$salida
fi

# Se comprueba si son los comandos correctos
if [[ $3 == "chmod" || $3 == "ls" || $3 == "mv" ]]; then
    man $3 | tail -n $2 >> $1/$salida
else
    echo "Comando proporcionado no válido" >> $1/$salida

fi

cat $1/$salida
```




## Ejercicio 3.<small style="font-size: 0.9rem; margin-left: 1rem;">[15 puntos]</small>

Buscar la palabra `tests` en el manual del comando `find` y redirigir el resultado a un archivo llamado `Palabras.txt`. Redirigir la salida de errores a otro archivo llamado `MisErrores.txt`.

**Nota** *Se debe adjuntar una captura de pantalla en la que aparezca el comando(s) requeridos para la resolución del ejercicio, el resultado de su ejecución, así como el nombre de usuario. Esta captura es <u>obligatoria</u> para que se evalúe el ejercicio. La no aportación de la captura implicará una calificación de 0 puntos en el ejercicio.*


```console
$ cad_buscada="tests"
$ salida="Palabras.txt"
$ errores="MisErrores.txt"

$ man find | grep $cad_buscada > $salida 2> $errores
```


## Ejercicio 4.<small style="font-size: 0.9rem; margin-left: 1rem;">[10 puntos]</small>

Hacer con una única orden el cálculo $19/3$ con decimales y redirigir el resultado a un archivo llamado `operacion.txt`.   
Mostrar el comando para añadir al propietario el permiso de ejecución y eliminar a todos los usuarios el permiso de escritura en un único comando.

**Nota** *Se debe adjuntar una captura de pantalla en la que aparezca el comando(s) requeridos para la resolución del ejercicio, el resultado de su ejecución, así como el nombre de usuario. Esta captura es <u>obligatoria</u> para que se evalúe el ejercicio. La no aportación de la captura implicará una calificación de 0 puntos en el ejercicio.*


```console
$ nom_salida="operacion.txt"

$ echo 19/3|bc -l > $nom_salida

$ chmod u+x,a-w $nom_salida
```




## Ejercicio 5.<small style="font-size: 0.9rem; margin-left: 1rem;">[10 puntos]</small>

Muestra el comando adecuado de Linux para buscar los archivos en tu directorio personal que pertenezcan a tu usuario y que su tamaño sea mayor de 2000k.

**Nota** *Se debe adjuntar una captura de pantalla en la que aparezca el comando(s) requeridos para la resolución del ejercicio, el resultado de su ejecución, así como el nombre de usuario. Esta captura es <u>obligatoria</u> para que se evalúe el ejercicio. La no aportación de la captura implicará una calificación de 0 puntos en el ejercicio.*


```console
$ find ~ -maxdepth 1 -type f -user $USER -size +2000k
```


## Ejercicio 6.<small style="font-size: 0.9rem; margin-left: 1rem;">[10 puntos]</small>

Crea con una única orden el directorio `FS` y dentro de éste los directorios `Prácticas` y `Teoría`. Situado en el directorio `FS` y con una única orden, crea tres archivos llamados `enunciados.gif`, `unidad1.txt` y `resultados2.jpg` dentro del directorio `Prácticas`.

Situado dentro del directorio `Prácticas`, copie con una única orden los archivos cuyo nombre contenga una "s" y extensión tenga una "g" al directorio `Teoría`.

**Nota** *Se debe adjuntar una captura de pantalla en la que aparezca el comando(s) requeridos para la resolución del ejercicio, el resultado de su ejecución, así como el nombre de usuario. Esta captura es <u>obligatoria</u> para que se evalúe el ejercicio. La no aportación de la captura implicará una calificación de 0 puntos en el ejercicio.*


```console
$ mkdir -p ./FS ./FS/{Prácticas,Teoría}

$ cd FS
$ touch ./Prácticas/{enunciados.gif,unidad1.txt,resultados2.jpg}

$ cd Prácticas
$ cp ./*s*.*g* ../Teoría/
```