# Sistemas Operativos. Examen II de Prácticas.

**Autor:** Jose Juan Urrutia Milán 'JJ'.<br>
**Autor:** Arturo Olivares Martos.
***

- **Asignatura:** Sistemas Operativos.
- **Curso Académico:** 2023-24.
- **Grado:** Doble Grado en Ingeniería Informática y Matemáticas.
- **Grupo:** A.
- **Profesor:** José Luis Garrido Bullejos.
- **Descripción:** Examen de Prácticas del Módulo II (Prácticas 1-7).
- **Fecha:** 18 de diciembre de 2023.
- **Duración:** 2h.
- **Material:** Bolígrafo, manual de prácticas y dos folios únicamente.
- **Observaciones:** Los enunciados no son literalmente los descritos en el examen, ya que son los que se han recordado tras la finalización del examen.



## Ejercicio 1.<small style="font-size: 0.9rem; margin-left: 1rem;">[4 puntos]</small>

Crea un programa llamado `duplicar` que se ejecute con los siguientes parámetros:
```console
duplicar <directorio-fuente> <directorio-destino>
```
El programa copiará únicamente los subdirectorios (no los archivos) a partir de `directorio-fuente` en el directorio indicado por `directorio-destino`, de forma que se realice una copia **exacta** de la estructura original. No deben seguirse enlaces simbólicos. En el caso de que la carpeta `directorio-destino` no exista, el programa deberá crearla. Los subdirectorios copiados deberán tener exactamente el mismo nombre y los mismos permisos que los directorios originales. Finalmente, se escribirá por salida estándar el número total de subdirectorios copiados. 


## Ejercicio 2.<small style="font-size: 0.9rem; margin-left: 1rem;">[3 puntos]</small>

Crea un programa llamado `duplicar2` que se ejecute con los siguientes parámetros:
```console
duplicar2 <directorio-fuente1> … <directorio-fuenteN> <directorio-destino>
```
El programa deberá crear por cada una de las $N-1$ primeras parejas de fuente-destino un hijo que ejecute el programa `duplicar`. El mismo programa deberá ejecutar el último par fuenteN-destino. El programa deberá esperar a que todos sus hijos finalicen antes de terminar (controlando que no queden en estado zombie). Cada vez que un hijo termine, se debe imprimir en pantalla (en el padre), el nombre del directorio copiado.


## Ejercicio 3.<small style="font-size: 0.9rem; margin-left: 1rem;">[3 puntos]</small>
Modificar el programa `duplicar2` para que cuando finalice muestre en pantalla el número total de subdirectorios copiados por los hijos.