# Sistemas Operativos. Examen III de Prácticas.

**Autor:** Arturo Olivares Martos.
***

- **Asignatura:** Sistemas Operativos.
- **Curso Académico:** 2021-22.
- **Grado:** Doble Grado en Ingeniería Informática y Matemáticas.
<!-- **Grupo:** A.
- **Profesor:** José Luis Garrido Bullejos.-->
- **Descripción:** Examen de Prácticas del Módulo II (Prácticas 1-7).
<!-- **Fecha:** 18 de diciembre de 2023.
- **Duración:** 2h.
- **Material:** Bolígrafo, manual de prácticas y dos folios únicamente.-->
- **Observaciones:** Los enunciados no son literalmente los descritos en el examen, ya que son los que se han recordado tras la finalización del examen.



## Ejercicio 1.

Crear un programa que reciba 4 argumentos:
1. Directorio fuente
2. Número de bloques
3. Profundidar a ahondar en el directorio fuente
4. Directorio destino

El programa deberá copiar en el directorio destino los archivos que se encuentren en el directorio fuente y en los subdirectorios de este (hasta la profundidad indicada) que tengan un tamaño mayor o igual al número de bloques indicado. El programa deberá mostrar por pantalla el número total de archivos copiados.

## Ejercicio 2.

Crear un programa que reciba por entrada estándar números enteros hasta que reciba "fin".

Dicho programa debe crear dos hijos.
- El primer hijo, por cada número dado, comprueba si es primo:
  - Si es primo, informa por pantalla.
  - Si no lo es, informa por pantalla y busca el siguiente número primo mayor o igual.

- El segundo hijo escribe los números que se han recibido en un archivo llamado `resultado.txt`. Cuando termine, cambia los permisos del archivo a `0642`.