# SCD. Examen de las Prácticas I y II.

***

- **Asignatura:** Sistemas Concurrentes y Distribuidos.
- **Curso Académico:** 2023-24.
- **Grado:** Doble Grado en Ingeniería Informática y Matemáticas + ADE.
- **Descripción:** Examen de las prácticas 1 y 2 de SCD.

***

# Ejercicio 1.
Modifique su solución del problema de los fumadores realizada mediante **semáforos** con las siguientes modalidades:
1. El mostrador tiene capacidad para dos ingredientes diferentes en vez de solo uno.
2. El estanquero debe realizar sus iteraciones de dos en dos. Es decir:
    - Producir dos ingredientes en cada iteración. Además, estos dos deben ser diferentes. Se produce el primero de ellos de forma aleatoria y después se puede entrar en un bucle donde se genere el otro hasta que sea distinto del primero. Tras producir ambos ingredientes, se imprimirá un mensaje por pantalla indicando los ingredientes generados.
    - Depositar ambos en el mostrador, avisando a los fumadores que necesitan esos ingredientes.
    - Cuando el estanquero ha avisado a los fumadores, espera la confirmación de ambos para volver a poner otros ingredientes distintos. Por lo tanto, el estanquero debe asegurares que cada uno de los fumadores ha cogido su ingrediente, haciendo una espera, si fuera necesario, para cada fumador.
3. El comportamiento de los fumadores no cambia con respecto a la versión original, ya que cada fumador espera que le indiquen si su ingrediente está en el mostrador, y avisa al estanquero de ello, antes de fumar. Se debe usar un array de hebras para definir las hebras fumadoras y esas hebras fumadoras se deben generar a partir de una misma función.

***

Puede encontrar la solución al problema en el siguiente [enlace](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/SCD/Prácticas/Práctica2/Exámenes/Examen2Ej1.cpp).

# Ejercicio 2.
Modifque la solución del problema de los fumadores realizada con **monitores** teniendo en cuenta que:
  
Tenemos un mostrador que tiene capacidad para dos ingredientes y el estanquero pone dos ingredientes diferentes cada vez, permitiendo que dos fumadores distintos tengan sus ingredientes para fumar. Se realizarán unos cambios:
1. El estado del mostrador se representa con un array de celdas, cada celda almacenará un valor que indicará el ingrediente correspondiente que hay en esa zona del mostrador, o ausencia dl ingrediente en esa zona.
2. Operaciones del monitor Estanco modificadas:
    - *Poner ingrediente*: Como estanquero produce dos ingredientes diferentes en el mostrador, la interfaz de operación y su implementación se tienen que modificar para parmitir que se pongan dos ingredientes en el mostrador e indicar que se permite continuar a dos fumadores.
    - *Obtener ingrediente*: La operación se tiene que modificar ya que el fumador debe asegurarse de que su ingrediente está en alguna de las zonas del mostrador, dejar vacía esa zona y, si la otra zona también estaba vacía, indicar al estanquero que el mostrador ha quedado totalmente vacío (por si estuviera esperando).
    - *Esperar recogida ingrediente*: La condición lógica que describe el mostrador *no está vacío* debe cambiarse al ser más compleja esta nueva situacion.

***

Puede encontrar la solución al problema en el siguiente [enlace](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/SCD/Prácticas/Práctica2/Exámenes/Examen2Ej2.cpp).