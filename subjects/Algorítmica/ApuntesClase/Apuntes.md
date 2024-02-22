# Introducción.
## Problemas como motivación.
### Parque de Atracciones.
Disponemos de un conjunto de atracciones $A_1, \ldots, A_n$.  
Para cada atracción tenemos la hora de inicio y la hora de fin.

#### Problema 1.
Seleccionar el mayor número de atracciones que un individuo pueda visitar.

#### Problema 2.
Seleccionar las atraciones que permitan que un visitante esté ocioso el menor tiempo posible.

#### Problema 3.
Conocidas las valoraciones de los usuarios, $val(A_i)$, seleccionar aquellas que garanticen la máxima valoración conjunta en la estancia.

### Optimizar robot.
El robot debe soldar $n$ puntos en un plano. Buscamos el orden en el cual el robot debe soldar los puntos.  
Minimizar el tiempo en realizar la operación (depende de la distancia).

## Nociones de conceptos.
- ```Instancia```: Ejemplo particular de un problema.
- ```Caso```: Instancia de un problema con una dificultad idéntica o muy similar.  
  
Tendremos generalmente tres casos: el mejor caso (instancia con menor número de operaciones/comparaciones), el peor caso (instancia con mayor número de operaciones/comparaciones) y el caso promedio.  
Para notar la eficiencia del peor caso, usaremos $O(\cdot)$, mientras que para el mejor caso, $\Omega(\cdot)$.
Normalmente, el peor caso y el promedio se comportan de forma similar.  
  
- ```Algoritmo estable```: Dado un problema de ordenación, si el criterio de orden es igual en dos casos, el orden de estos vendrá dado por el primero que se introdujo en la entrada.  
Por ejemplo, un algoritmo estable de ordenación de enteros en el que los pares son menores que los impares con la instancia ```1, 2, 3, 4```, la salida será:  
```2, 4, 1, 3```  
  
## Algoritmos de ordenación.
Burbuja es el peor algoritmo de ordenación. 
Cuando se tienen pocos elementos, suele ser más rápido un algoritmo simple como selección o inserción.
Selección hace muchas comparaciones, pocos intercambios mientras que inserción hace menos comparaciones pero más intercambios.  
Por tanto, ante unos datos pesados con varios registros, selección será mejor que inserción.
  
Cuando se tienen muchos, datos, es mejor un algoritmo $n \log(n)$.  

# Tema 1. Eficiencia de Algoritmos.
La asignatura se centrará en eficiencia basada en el tiempo de ejecución (no en la eficiencia en cuanto espacio, memoria usada por el programa).  
  
Para calcular la eficiencia de un algoritmo, tenemos:
- Método empírico: Tiempo real.
- Método teórico: Tiempo esperado.
- Método híbrido: Tiempo teórico sin evitar constantes.
  
## Principio de Invarianza.
Dadas dos implementaciones de un algoritmo, el tiempo de ejecución para una misma instancia de tamaño $n$, $T_{I1}(n)$ y $T_{I2}(n)$, no diferirá en más de una constante multiplicativa. Es decir, $\exists K > 0$ que verifica: $$T_{I1}(n) \leq K \cdot T_{I2}(n)$$
Por lo que podemos despreciar las constantes.  
  
En un principio, se asumiriá que operaciones básicas como sumas, multiplicaciones, etc. será constante, salvo excepciones (por ejemplo, multiplicaciones de números de 100000 dígitos).  

## Notación asintótica
Se dice que un algoritmo $A$ es de orden $O(f(n))$, donde $f$ es una función $f:\mathbb{N}\rightarrow \mathbb{R}^{+}$, cuando existe una implementación del mismo tamaño cuyo tiempo de ejecución $T_A(n)$ es menor igual que $K \cdot f(n)$, donde $K$ es una constante real positiva a partir de un tamaño grande $n_0$. Formalmente:
$$A \mbox{ es } O(f(n)) \Leftrightarrow \exists K \in \mathbb{R}^{+} \mid \exists n_0 \in \mathbb{N} \mid T_A(n) \leq K \cdot f(n)~~\forall n \geq n_0$$

Ejemplos de órdenes de eficiencia son:
- Constante, $O(1)$.
- Logarítmico, $O(\log(n))$.
- Lineal, $O(n)$.
- Cuadrático, $O(n^2)$.
- Exponencial, $O(a^n)$.
- $\ldots$
