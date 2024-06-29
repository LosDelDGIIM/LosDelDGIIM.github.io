# Algorítmica. Examen IV

**Autor:** Arturo Olivares Martos
***

- **Asignatura:**  Algorítmica.
- **Curso Académico:** 2018-19.
- **Grado:** Doble Grado en Ingeniería Informática y Matemáticas.
- **Grupo:** Único.
- **Profesor:** Juan Francisco Huete Guadix (aunque el examen lo pone el departamento).
- **Descripción:** Convocatoria Ordinaria.
- **Fecha:** 6 de junio de 2019.
- **Duración:** 2 horas y 30 minutos.
- **Observaciones:** En todos los problemas se debe emplear alguna de las técnicas de diseño o análisis de algoritmos estudiadas en esta asignatura.

## Ejercicio 1
Resolver la ecuación en recurrencias $T(n)=3T\left(n/2\right) + n\log_2(n)$, indicando el orden resultante asumiendo que la ecuación se obtuvo para el caso peor de un algoritmo.

## Ejercicio 2
Una estación de ITV consta de $m$ líneas de inspección de vehículos iguales. Hay un total de $n$ vehículos que necesitan inspección. En función de sus características, cada vehículo tardará en ser inspeccionado un tiempo $t_i$, $i = 1, \ldots, n$. Se desea encontrar la manera de atender a los $n$ vehículos y acabar en el menor tiempo posible. 

Diseñad un algoritmo de exploración de grafos que determine cómo asignar los vehículos a las líneas. Especificad claramente, además del algoritmo, la representación del problema, la representación de la solución, las restricciones explícitas e implícitas, así como las posibles cotas a utilizar.

## Ejercicio 3
La empresa $X$ ha decidido instalar una red de fibra óptica para interconectar sus seis centros de trabajo. El coste (positivo) del tendido de cable entre ellos aparece en la figura siguiente. (En el examen se aportaba un grafo, pero por simplicidad aquí aportaremos la matriz de adyacencia)

```cpp
M =  {
          {0, 3, X, 7, X, 3},
          {3, 0, 4, 8, X, 6},
          {X, 4, 0, 9, X, 5},
          {7, 8, 9, 0, 8, X},
          {X, X, X, 8, 0, 6},
          {3, 6, 5, X, 6, 0}
     };
```

Especificad un algoritmo que sea capaz de encontrar la forma de interconectar todos los centros con un coste mı́nimo, y aplicadlo para resolver el problema de la figura, describiendo el proceso paso a paso.

## Ejercicio 4
Tenemos que pagar la cuenta en un restaurante por valor de $M$ euros, y disponemos de una cantidad ilimitada de monedas de $n$ tipos diferentes, siendo $c[i]$ el valor de cada moneda de tipo $i$, $i = 1, \ldots, n$. Tenemos prisa y no queremos esperar que, en su caso, nos den la vuelta, pero como no hemos quedado muy satisfechos queremos pagar o la cantidad exacta $M$ o la mı́nima cantidad posible mayor que $M$ (o sea dejar ninguna propina o la mı́nima propina posible de acuerdo a las monedas que tenemos). 

Diseñar un algoritmo eficiente que determine la cantidad mı́nima que tenemos que pagar y cómo hacerlo. 

Aplicadlo para resolver el siguiente caso: hay $n = 3$ tipos de monedas de valores $5$, $7$ y $13$, y queremos pagar una cantidad de $M = 11$ unidades.

## Ejercicio 5
 Un aficionado al póker juega una partida cada dı́a, y anota los euros que gana o pierde. Por ejemplo, la siguiente tabla muestra los resultados del último mes.

| L   | M   | X   | J   | V   | S   | D   |
|-----|-----|-----|-----|-----|-----|-----|
|     |     |     |     |     | 29  | -7  |
| 14  | 21  | 30  | -47 | 1   | 7   | -39 |
| 23  | -20 | -36 | -41 | 27  | -34 | 7   |
| 48  | 35  | -46 | -16 | 32  | 18  | 5   |
| -33 | 27  | 28  | -22 | 1   | -20 | -42 |

Podemos ver que empezó el mes con una ganancia de $29$ euros, y terminó con una pérdida de $42$. El beneficio total obtenido en el mes (la suma de todas las ganancias y pérdidas) es $−50$ euros. Analizando la información, el jugador se podrı́a dar cuenta de que si hubiera empezado a jugar el dı́a $16$ y terminado el dı́a $26$, habrı́a maximizado sus ganancias, obteniendo $105$ euros.

En general, dado un vector de ganancias/pérdidas de longitud $n$, se desea encontrar el subvector sobre el cual se consigue el beneficio total máximo. Diseñad un algoritmo que realice esta tarea de forma lo más eficiente posible.
