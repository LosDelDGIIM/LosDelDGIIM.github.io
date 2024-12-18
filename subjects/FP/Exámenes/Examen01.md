# Fundamentos de Programación. Examen I de Prácticas

***

- **Asignatura:** Fundamentos de Programación.
- **Curso Académico:** 2024-25.
- **Grado:** Doble Grado en Ingeniería Informática y Matemáticas.
- **Profesor:** Francisco José Cortijo Bon.
- **Descripción:** Parcial I de Prácticas.
- **Fecha:** 27 de Noviembre de 2024.
- **Duración:** 75 minutos.

## Ejercicio 1. Números desgarrables.
### Definición
Un número entero $n$ se dice que es **desgarrable** si al dividirlo en dos partes $n_{izda}$ y $n_{dcha}$, el cuadrado de la suma de ambas partes es igual a $n$.  
Por ejemplo, el número 81 es desgarrable ya que $(8+1)^2 = 9^2 = 81$. El número $88209$ también es desgarrable ya que $(88+209)^2=297^2 = 88209$. Sin embargo, $12345$ no es desgarrable ya que $(12 + 345)^2 = 357^2 = 127449$.  
  
**Nota:** Observe la manera en la que se *desgarra* un número cuando se tiene un número impar de cifras: la parte de la izquierda tiene una cifra menos que la de la derecha.

### Tareas a implementar
El programa leerá dos valores enteros positivos que determinan el intervalo cerrado (los dos extremos incluidos) de trabajo. A continuación realizará, por orden, las siguientes tareas:
1. Indicar **cuántos** números desgarrables hay entre ellos.
2. **Mostrar** detalladamente los números desgarrables encontrados entre ellos (sus **valores**) y su **descomposición**. Ejemplos de descomposición:
```
    1 --> (  0 +   1 )^2 = (   1 )^2 =     1
   81 --> (  8 +   1 )^2 = (   9 )^2 =    81
 2025 --> ( 20 +  25 )^2 = (  45 )^2 =  2025
 3025 --> ( 30 +  25 )^2 = (  55 )^2 =  3025
 9801 --> ( 98 +   1 )^2 = (  99 )^2 =  9801
88209 --> ( 88 + 209 )^2 = ( 297 )^2 = 88209
```

### Indicaciones y restricciones
1. Modularice el código utilizando **funciones**. Se valorará especialmente la calidad de la **modularización**.
2. Suponemos que el usuario es honesto e introduce valores numéricos enteros. Implemente los **filtros** que sean necesarios.
3. No puede usarse la clase `string`.
4. Para *desgarrar* un número en sus dos mitades le aconsejamos usar las operaciones de *división entera* y *módulo*. Cualquier otra solución puede ocuparle mucho más tiempo codificando.

### Ejemplos
```
Introduzca un numero positivo:   100000
Introduzca otro numero positivo: 1

Calculando numeros desgarrables entre 1 y 100000
..................................................
1. Total de numeros desgarrables.
    Se han encontrado   6 numeros desgarrables.
2. Los numeros desgarrables y su descomposicion.
        1 --> (  0 +   1 )^2 = (   1 )^2 =     1
       81 --> (  8 +   1 )^2 = (   9 )^2 =    81
     2025 --> ( 20 +  25 )^2 = (  45 )^2 =  2025
     3025 --> ( 30 +  25 )^2 = (  55 )^2 =  3025
     9801 --> ( 98 +   1 )^2 = (  99 )^2 =  9801
    88209 --> ( 88 + 209 )^2 = ( 297 )^2 = 88209
```
***
```
Introduzca un numero positivo:   100000
Introduzca otro numero positivo: 1000000

Calculando numeros desgarrables entre 100000 y 1000000
..................................................
1. Total de numeros desgarrables.
    Se han encontrado   2 numeros desgarrables.
2. Los numeros desgarrables y su descomposicion.
    494209 --> ( 494 + 209 )^2 = ( 703 )^2 = 494209
    998001 --> ( 998 +   1 )^2 = ( 999 )^2 = 998001
```
