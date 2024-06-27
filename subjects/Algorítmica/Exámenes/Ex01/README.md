# Algorítmica. Examen I

**Autor:** Arturo Olivares Martos
***

- **Asignatura:**  Algorítmica.
- **Curso Académico:** 2021-22.
- **Grado:** Doble Grado en Ingeniería Informática y Matemáticas.
- **Grupo:** Único.
- **Profesor:** Juan Francisco Huete Guadix (aunque el examen lo pone el departamento).
- **Descripción:** Convocatoria ordinaria.
- **Fecha:** 23 de junio de 2022.
- **Duración:** 2 horas y 30 minutos.
- **Observaciones:** En todos los problemas se debe emplear alguna de las técnicas de diseño o análisis de algoritmos estudiadas en esta asignatura.

## Ejercicio 1
Resolver la ecuación en recurrencias $T(n)=3T\left(n/3\right) + \log_3(n)$, indicando el orden resultante asumiendo que la ecuación se obtuvo para el caso peor de un algoritmo.

## Ejercicio 2
Una empresa de gestión de aguas ha encontrado un nuevo pozo capaz de abastecer a una serie de $N$ pueblos de una comarca. Para diseñar la estrategia de abastecimiento deciden calcular el coste de interconectar (mediante tuberías) cada par de pueblos $x$ e $y$ entre sí, $c(x, y)$, y cada pueblo directamente con el pozo $p$, $c(x, p)$. 

Diseñad un algoritmo para que dicha empresa pueda abastecer de agua a los $N$ pueblos usando ese pozo de manera que el coste de construir toda la infraestructura sea el mínimo. El algoritmo debe encontrar la solución óptima y además hacerlo de forma eficiente.

## Ejercicio 3
Sea $T$ un conjunto de $n$ programas, cada uno con un tamaño $t_1, t_2, \ldots, t_n$ (los números $t_i$ son enteros positivos), y disponemos de un dispositivo de almacenamiento de capacidad máxima $C$ (también un número entero positivo). Se pretende encontrar la manera de decidir qué programas (completos) almacenar en el dispositivo de manera que se maximice el espacio ocupado del dispositivo. 

Diseñad un algoritmo de programación dinámica para resolver este problema. Aplicadlo para el caso en que $n = 4$, el vector de tamaños es $t(1) = 3$, $t(2) = 7$, $t(3) = 11$ y $t(4) = 8$, con capacidad del dispositivo $C = 12$.

## Ejercicio 4
Se desea conocer si, dado un número natural $n$, éste es o no un número combinatorio del tipo $k$ sobre $2$, $\binom{k}{2}$, para algún número $k$ natural. Por ejemplo, $36 = \binom{9}{2}$, o $499500 = \binom{1000}{2}$. 

Especificad un algoritmo lo más eficiente posible para resolver este problema.

Nota: $\binom{k}{2} = k \cdot (k-1) / 2$.

## Ejercicio 5
Dados $n$ números positivos $w_i; 1 \leq i \leq n$, y un entero más $M$, se trata de encontrar todos los subconjuntos de números $w_i$ cuya suma valga exactamente $M$. 

Por ejemplo, si $n = 4$; $(w_1 = 11; w_2 = 13; w_3 = 24; w_4 = 7)$ y $M = 31$, entonces los subconjuntos buscados son $(11, 13, 7)$ y $(24, 7)$. Se pide realizar un algoritmo de exploración en grafos para solucionar el problema.

