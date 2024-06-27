# Algorítmica. Examen II

**Autor:** Arturo Olivares Martos
***

- **Asignatura:**  Algorítmica.
- **Curso Académico:** 2020-21.
- **Grado:** Doble Grado en Ingeniería Informática y Matemáticas.
- **Grupo:** Único.
- **Profesor:** Juan Francisco Huete Guadix (aunque el examen lo pone el departamento).
- **Descripción:** Convocatoria Ordinaria.
- **Fecha:** 15 de junio de 2021.
- **Duración:** 2 horas y 30 minutos.
- **Observaciones:** En todos los problemas se debe emplear alguna de las técnicas de diseño o análisis de algoritmos estudiadas en esta asignatura.

## Ejercicio 1
Resolver la ecuación en recurrencias $T(n)=3T\left(n/2\right) + 4T\left(n/4\right)+n^2$, indicando el orden resultante asumiendo que la ecuación se obtuvo para el caso peor de un algoritmo.

## Ejercicio 2
Dado un conjunto de $n$ números enteros positivos $C = \{c_1, c_2, \ldots, c_n\}$ y dado un entero positivo $N$, se quiere encontrar un subconjunto de $C = \{y_1, \ldots, y_m\}$ que maximice $\prod_{i=1}^{m} y_i$ (se maximice el producto de los números del subconjunto), sujeto a la restricción $\prod_{i=1}^{m} y_i \leq N$. 

Nota: $m$ NO es un parámetro de entrada. 

Diseñad un algoritmo de vuelta atrás (backtraking) para resolver este problema. 

Por ejemplo, para $n = 4$, $N = 37$ y $C = \{4, 4, 12, 3\}$, la solución es emplear el subconjunto $\{12, 3\}$ con un valor de producto igual a $36$.

## Ejercicio 3
Estamos en una posición $(x, y)$ de un laberinto bidimensional representado por una matriz $M$ de $f$ filas y $c$ columnas. De cada casilla se puede viajar a cualquiera de las colindantes con la casilla actual, en la misma fila o la misma columna, siempre que la casilla destino sea transitable. Los posibles valores de las casillas son $M(i, j) = t$ (transitable), $M(i, j) = n$ (no transitable) y $M(i, j) = s$ (salida). 

Sabiendo que disponemos del mapa del laberinto a priori, y que pueden existir varias salidas del mismo, plantee un algoritmo eficiente que devuelva el camino a la salida más próxima a la casilla inicial $(x, y)$. 

NOTA: El coste de viajar de una casilla a otra es siempre 1.

## Ejercicio 4
Disponemos de $n$ tipos de monedas, las monedas de tipo $i$ tienen un valor de $v[i]$. La cantidad de monedas disponibles de tipo $i$ es igual a $c[i]$. Se quiere devolver una cantidad exacta $M$ utilizando el menor número posible de monedas. 

Diseñad un algoritmo de programación dinámica que determine el número óptimo de monedas a usar. 

Aplicadlo para resolver el siguiente caso del problema, con $n = 3$, construyendo la tabla correspondiente:
$v = [2, 4, 6], c = [3,1,2], M = 8$

## Ejercicio 5
Diseñad un algoritmo que determine si un cierto número natural $N$ puede expresarse o no como producto de tres números naturales consecutivos, $N = Y \cdot (Y + 1) \cdot (Y + 2)$, con un orden de eficiencia lo mejor posible.
