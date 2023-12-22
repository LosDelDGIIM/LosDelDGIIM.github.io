# Sistemas Operativos. Examen IIII de Prácticas.

**Autor:** Arturo Olivares Martos.
***

- **Asignatura:** Sistemas Operativos.
- **Curso Académico:** 2023-24.
- **Grado:** Doble Grado en Ingeniería Informática y Matemáticas.
- **Grupo:** B.
- **Profesor:** Germán Arroyo Moreno.
- **Descripción:** Examen de Prácticas del Módulo II (Prácticas 1-7).
- **Fecha:** 19 de diciembre de 2023.
- **Duración:** 2h.
- **Material:** Bolígrafo, manual de prácticas.



## Ejercicio 1. [5 puntos]

Crea el programa (`ej1`) que tome el nombre de un directorio, en caso de error se saldrá del programa. Desués, el programa creará u cauce con nombre en `/tmp/cauce.pipe` y leerá entonces los subdirectorios que existan en el directorio dado, y creará un proceso hijo para cada uno de ellos. Cada proceso hijo enviará por el cauce con nombre el nombre del subdirectorio que le tocó y el número de archivos regulares que hay en el subdirectorio. Debe controlarse que no queden procesos _zombie_. Recuerda eliminar el dichero del cauce al salir del programa.


## Ejercicio 2. [5 puntos]

Crea el programa (`ej2`) que tome el nombre de un cauce como argumento. El programa leerá del cauce los datos dados por el programa `ej1`. Por cada entrada que lea (fichero + número de archivos), crear un fichero nuevo con un identificador único (por ejemplo, `/tmp/fichero1.txt`, `/tmp/fichero2.txt`, etc.) y por cada fichero creará un proceso compartiendo su descriptor de fichero con él. El proceso hijo rellenará el fichero con la información recibida del cauce con nombre y, cuando muera, el padre cerrará el descriptor de fichero correspondiente.