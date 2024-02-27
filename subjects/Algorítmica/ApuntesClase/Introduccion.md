**Autor:** José Juan Urrutia Milán

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
  
Tendremos generalmente tres casos:  
- El mejor caso: instancia con menor número de operaciones/comparaciones.
- El peor caso: instancia con mayor número de operaciones/comparaciones.
- Caso promedio.
Para notar la eficiencia del peor caso, usaremos $O(\cdot)$, mientras que para el mejor caso, $\Omega(\cdot)$.
Normalmente, el peor caso y el promedio se comportan de forma similar.  
  
- ```Algoritmo estable```: Dado un problema de ordenación, si el criterio de orden es igual en dos casos, el orden de estos vendrá dado por el primero que se introdujo en la entrada.  
Por ejemplo, un algoritmo estable de ordenación de enteros en el que los pares son menores que los impares con la instancia ```1, 2, 3, 4```, la salida será:  
```2, 4, 1, 3```  
  
## Algoritmos de ordenación.
Repaso de algoritmos de ordenación.  
Burbuja es el peor algoritmo de ordenación.  
Cuando se tienen pocos elementos, suele ser más rápido un algoritmo simple como selección o inserción.
Selección hace muchas comparaciones y pocos intercambios, mientras que inserción hace menos comparaciones pero más intercambios.  
Por tanto, ante unos datos pesados con varios registros, selección será mejor que inserción.
  
Cuando se tienen muchos datos, es mejor un algoritmo $n \log(n)$.  

[Volver al índice]()
