# Inteligencia Artificial

**Autor:** Arturo Olivares Martos
**Descripción:** Recopilación de preguntas Tipo Test de la asignatura de Inteligencia Artificial.

Se han obtenido de fuentes diversas, por lo que si faltasen, sobrasen o estuviesen mal formuladas, por favor, se ruega nos lo hagan saber para corregirlo.

---

1. ¿Cuál de los siguientes métodos de búsqueda es un caso particular de búsqueda primero el mejor?:
    - (x) Algoritmo A*.
    - ( ) Búsqueda en profundidad.
    - ( ) Algortimo genético.

2. ¿Cuál o cuáles de los siguientes algoritmos tienen una componente aleatoria?:
    - (x) Genéticos.
    - ( ) A*.
    - ( ) Escalada máxima pendiente.
    - ( ) Escalada simple.

3. ¿El uso de una función heurística garantiza que un método de búsqueda consiga la solución óptima?:
    - ( ) Siempre.
    - ( ) Nunca.
    - (x) Depende del algoritmo y de la heurística.

4. En el algoritmo A* ABIERTOS representa:
    - ( ) El conjunto de nodos generados y explorados.
    - (x) El conjunto de nodos generados y no explorados.
    - ( ) El conjunto de nodos no generados y explorados.
    - ( ) El conjunto de nodos no generados y no explorados.

5. En el algoritmo A* Cerrados representa:
    - ( ) el conjunto de nodos no generados y no explorados.
    - (x) el conjunto de nodos generados y explorados.
    - ( ) el conjunto de nodos generados y no explorados.
    - ( )  el conjunto de nodos no generados y explorados.

6. En el algoritmo A* cuando un sucesor corresponde con un nodo que ya estaba en CERRADOS:
    - ( ) el nodo se revisa para determinar cuál es su mejor sucesor, y en el caso de que haya cambio se propaga al padre del nodo..
    - ( ) el nodo se revisa para determinar cuál es su mejor padre. (correcta, pero está incompleta).
    - ( ) el nodo de elimina..
    - (x) el nodo se revisa para determinar cuál es su mejor padre, y en el caso de que haya cambio se propaga dicho cambio a los sucesores..

7. En el algoritmo A* el enlace al mejor padre determina una estructura de:
    - (x) árbol representando los mejores caminos desde cualquier nodo a la raíz..
    - ( ) árbol representando los mejores descendientes de cada nodo.
    - ( ) grafo con todos los descendientes desde cualquier nodo al objetivo.

8. En el algoritmo A*, ¿qué es la función g? Selecciona la respuesta correcta:
    - ( ) Es una estimación del coste necesario para alcanzar un estado objetivo por el camino que se el nodo actual.
    - ( ) Es una estimación del coste adicional necesario para alcanzar un nodo objetivo a partir del no.
    - (x) Es una medida del coste para ir desde el estado inicial hasta el nodo actual.

9. En el algoritmo A*, \\(g(n)\\) indica el coste del mejor camino hasta el momento desde el nodo inicial a unexpresa el coste estimado desde el nodo inicial hasta el nodo objetivo:
    - ( ) Verdadero.
    - (x) Falso.

10. Las heurísticas son:
    - ( ) funciones usadas en algunos problemas.
    - (x) criterios, métodos o principios para decidir cuál de entre varias acciones promete ser la mejor para alcanzar una meta.
    - ( ) criterios, métodos o principios para obtener el óptimo.

11. Los métodos heurísticos en general no garantizan la solución óptima, pero producen resultados satisresolución de problemas:
    - (x) Verdadero.
    - ( ) Falso.

12. Un juego es determinístico porque:
    - ( ) Siempre se puede determinar una solución.
    - (x) Siempre se pueden determinar los resultados de los movimientos de los jugadores.
    - ( ) Un jugador puede determinar siempre una estrategia ganadora.

13. Hay una diferencia destacable entre un estado de un juego y un estado de un problema de búsqueda heurística y es que::
    - ( ) En un estado de un juego no se representa la situación del mundo..
    - ( ) En un estado de un juego no se representa una valoración numérica sobre el estado..
    - (x) En un estado de un juego hay que representar el jugador que le toca mover.

14. Un juego puede considerarse como un caso de sistema multiagente _______.:
    - (x) Competitivo.
    - ( ) Cooperativo.

15. En un juego inicialmente hay 3 palillos sobre la mesa, y dos jugadores Max y Min. Max comienza el jupalillos. Le sigue Min, que también podrá quitar 1, 2 ó 3 palillos. Estas acciones se repiten hasta que último palillo, en cuyo caso pierde el juego. ¿La figura muestra el árbol de este juego?.:
    - ( ) Sí, porque todos los nodos min están bien valorados.
    - ( ) Sí, porque los nodos min son terminales.
    - (x) No, porque no todos los nodos terminales están etiquetados.
    - ( ) No, porque faltan operadores por aplicar al nodo max..

16. Las técnicas de juegos se llaman de búsqueda con adversario porque::
    - (x) Los agentes usan valoraciones de los estados terminales opuestas..
    - ( ) Los agentes usan repertorios de acciones opuestos..
    - ( ) Los agentes usan estados iniciales opuestos..

17. Un estado terminal en un juego bipersonal es un estado en el que::
    - ( ) hay empate entre los jugadores.
    - ( ) los dos jugadores ganan.
    - ( ) los dos jugadores pierden.
    - (x) no hay más movimientos aplicables y el juego finaliza.

18. Un juego bipersonal con información perfecta se considera un laboratorio de interés para la IA porque::
    - (x) Tiene un repertorio de acciones pequeño y aun así son duros de resolver..
    - ( ) Siempre se puede encontrar una solución óptima con una buena heurística..
    - ( ) Es más difícil de representar que juegos físicos, como el “RoboSoccer” o Fútbol Robótico..

19. Al inicio de la exploración de un árbol de juego:
    - ( ) Todos los nodos valen inicialmente 0.
    - ( ) . Todos los nodos valen inicialmente 0 menos los terminales.
    - (x) Todos los nodos tienen un valor desconocido menos los terminales.

20. El tamaño aproximado del espacio de nodos a explorar en el ajedrez, que tiene un factor de ramificacprofundidad media de 50 movimientos por cada jugador es de::
    - (x) \\(O(35^{100})\\).
    - ( ) \\(O(100^{35})\\).
    - ( ) \\(O(35*{100})\\).
    - ( ) \\(O(e^{-\frac{35}{100}})\\).

21. En un juego una estrategia contingente::
    - ( ) Es un camino lineal entre el estado inicial y un estado terminal que incluye nodos max y nodo.
    - (x) Es un grafo Y/O que representa movimientos de max y todos los posibles movimientos de op.

22. La solución de un juego permite indicar a cada jugador::
    - (x) Qué resultado puede esperar y cómo alcanzarlo.
    - ( ) Un camino lineal para encontrar un estado ganador.

23. Las valoraciones de los nodos terminales de un juego se realizan considerando el punto de vista de _:
    - (x) max.
    - ( ) min.

24. En los juegos bipersonales con información perfecta::
    - (x) Los jugadores actúan cada uno racionalmente, es decir, cada uno trata de obtener el máximo beneficio.
    - ( ) Los jugadores actúan cada uno racionalmente, es decir, cada uno trata de maximizar su pérdia.

25. Un juego de suma nula::
    - ( ) Hay reparto de beneficio entre los jugadores y la suma de beneficios es 0.
    - ( ) El resultado final del juego es 0.
    - (x) Cada situación final el beneficio de un jugador es total y la pérdida del oponente es total.

26. Un juego puede considerarse como un caso de sistema multiagente cooperativo.:
    - ( ) Verdadero.
    - (x) Falso.

27. Es necesario valorar  situaciones o asociar una utilidad a situaciones distintas a las terminales  para poder resolver un juego:
    - (x) Verdadero.
    - ( ) Falso.

28. Un juego con información perfecta es un caso de sistema multiagente con dos jugadores en el toda la información del tablero está disponible para cada jugador.:
    - (x) Verdadero.
    - ( ) Falso.

29. El caso promedio la poda alfa beta permite profundizar:
    - ( ) el triple que un procedimiento minimax con el mismo esfuerzo.
    - (x) un 33% más que un procedimiento minimax con el mismo esfuerzo.
    - ( ) el doble que un procedimiento minimax con el mismo esfuerzo.

30. En el algoritmo minimax podemos cambiar el jugador MAX por el jugador MIN sin más que::
    - ( ) Cambiar el orden de la exploración sin alterar ningún otro elemento.
    - ( ) Modificar la función heurística sumando -1 a todos sus valores.
    - (x) Cambiar el orden de la exploración y el signo de la función heurística.

31. En teoría de juegos, minimax es:
    - ( ) un método para encontrar la salida a un laberinto.
    - ( ) un algoritmo para resolver una partida de ajedrez.
    - (x) un método de decisión para minimizar la pérdida máxima esperada en juegos con adversario, perfecta y suma nula.
    - ( ) un tipo de agente deliberativo.
    - ( ) e. un método de decisión para maximizar la pérdida mínima esperada en juegos con adversario, perfecta y suma nula.

32. En un juego con componente aleatoria, si realizamos un cambio de escala en los valores ¿la variantetipo de juegos elegirá la misma jugada?:
    - ( ) Si, no depende de los cambios de escala siempre que se conserve el orden de los valores.
    - (x) No siempre, pues puede cambiar el orden de la esperanza matemática de las opciones de unaconserve el orden de los valores.

33. La cota alfa se calcula como el:
    - (x) el valor máximo de los nodos MAX en el camino del nodo a la raíz.
    - ( ) el valor máximo de los nodos MIN en el camino del nodo a la raíz.
    - ( ) el valor mínimo de los nodos MIN en el camino del nodo a la raíz.
    - ( ) el valor máximo de los nodos MAX del árbol del juego.

La efectividad de la poda alfa-beta del algoritmo minimax depende del orden en que se exploren las jugadas:
    - (x) cierto.
    - ( ) falso.
    - ( ) depende de la función de evaluación estática usada.

35. En el contexto de búsqueda en juegos con una profundidad de corte o limitada, una posición estable:
    - ( ) a. Una posición del juego en la que la valoración de sus sucesores no cambia respecto a la posicion actual.
    - (x) Una posición del juego desde la no se producen variaciones drásticas de la valoración de sus posición actual..
    - ( ) Una posición a la que se puede volver para iniciar una nueva estrategia contingente..

36. Una función de valoración de nodos intermedios de un juego::
    - ( ) No tiene que contemplar situaciones terminales del juego..
    - (x) Tiene que contemplar situaciones terminales del juego, valorándolas con -inf si gana MIN y +inf si pierde MIN..
    - ( ) Tiene que contemplar situaciones terminales del juego, valorándolas con -inf si pierde MIN y +inf si gana MIN..

37. Una regla general como “Todas las casillas azules de un mapa pueden transitarse si el agente tiene bikini:
    - ( ) se puede representar más adecuadamente con un modelo icónico que con un modelo descriptrivo.
    - (x) se puede representar más adecuadamente con un modelo descriptivo que con un modelo icónico.
    - ( ) no puede representarse ni con un modelo descriptivo ni con un modelo icónico..

38. La información que se almacena en un nodo de un espacio de estados es un ejemplo de:
    - ( ) un modelo de representación icónico.
    - (x) un modelo de representación descriptivo.
    - ( ) un modelo de presentación ad-hoc..

39. El cálculo proposicional es decidible, lo cual significa que::
    - ( ) . Se puede usar para tomar decisiones a partir de un conjunto de fórmulas..
    - (x) Se puede determinar en tiempo finito si una proposición es deducible de un conjunto de fórmulas.
    - ( ) Se puede garantizar que si una fórmula es cierta entonces se puede decidir su certeza..

40. La relación “X es el padre de Y”:
    - ( ) se puede representar más adecuadamente con proposiciones que con predicados.
    - (x) se puede representar más adecuadamente con predicados que con proposiciones..
    - ( ) solo puede representarse con predicados.

41. Un árbol de demostración::
    - (x) es una representación del proceso de demostración de una fórmula bien formada.
    - ( ) es una representación del espacio de estados en la búsqueda de una fórmula bien formada.
    - ( ) es una representación del espacio de fórmulas donde se debe encontrar una demostración.

42. El modus ponens::
    - ( ) es una regla de inferencia para modelos icónicos.
    - (x) es una regla de inferencia en lógica en lógica proposicional y de predicados.
    - ( ) es una regla de inferencia solo aplicable en lógica proposicional..

43. Si partimos de dos cláusulas, una en la que se afirma que “no llueve o hace frío” y otra que en la que hace frío”, la regla de resolución aplicada a ambas establece que::
    - (x) hace frío.
    - ( ) no llueve.
    - ( ) no se pueden resolver, son cláusulas inconsistentes.

44. La instanciación universal nos permite deducir::
    - ( ) reglas generales a partir de casos particulares.
    - (x) casos particulares a partir de reglas generales.
    - ( ) la instanciación no nos permite deducir, nos permite inferir..

45. Para representar con predicados la información sobre una Asignatura, el Curso en que se imparte y el cuatrimestre:
    - ( ) se puede usar un único predicado asignatura(A,C,Cu) donde A es una variable que representa y Cu el cuatrimestre.
    - ( ) se pueden usar dos predicados, asignatura-curso(A,C) y asignatura-cuatrimestre(A,Cu) donde representa la asignatura, C el curso y Cu el cuatrimestre.
    - ( ) ninguna de las otras respuestas es cierta porque no se pueden usar predicados para represenen una base de datos.
    - (x) a y b son ciertas.

46. ¿Es eficiente la resolución en lógica de predicados?:
    - ( ) No, solo sirve como concepto teórico,.
    - (x) Si, siempre que nos limitemos a utilizar cláusulas de Horn.
    - ( ) Si, siempre encuentra en tiempo eficiente las demostraciones.

47. ¿Cuál de los siguientes es un tipo de aprendizaje?:
    - ( ) Aprendizaje normal.
    - ( ) no sabe no contesta.
    - ( ) Aprendizae por eliminación.
    - (x) Aprendizaje supervisado.

48. En un sistema basado en el conocimiento, el motor de inferencia:
    - ( ) contiene los hechos inferidos y las reglas para inferir.
    - (x) permite razonar sobre el conocimiento de la base de conocimiento y los datos proporcionados por un usuario.
    - ( ) es independiente del modelo de representación.

49. ¿Cuál o cuáles son los componentes esenciales que necesita un Sistema Basado en el Conocimiento:
    - ( ) se puede usar un único predicado asignatura(A,C,Cu) donde A es una variable que representa y Cu el cuatrimestre.
    - ( ) se pueden usar dos predicados, asignatura-curso(A,C) y asignatura-cuatrimestre(A,Cu) donde representa la asignatura, C el curso y Cu el cuatrimestre.
    - ( ) Interfaz de usuario.
    - ( ) ninguna de las otras respuestas es cierta porque no se pueden usar predicados para represenen una base de datos.
    - (x) e. a, b y c son ciertas.

50. ¿Cuáles son los dos métodos de aprendizaje supervisado?:
    - ( ) Métodos basados en instancias.
    - ( ) Métodos basado en grafos.
    - ( ) Métodos basados en modelos.
    - ( ) Métodos basados en funciones.
    - (x) e. a y c son ciertas.
    - ( ) f. b y c son ciertas.

51. ¿Con qué método o métodos de búsqueda se obtiene siempre la solución con un número menor de iteracciones?:
    - ( ) Descenso iterativo.
    - ( ) Búsqueda en profundidad.
    - ( ) Búsqueda en anchura.
    - (x) a y c son correctas.

52. ¿Cuál de entre los siguientes algoritmos de escalada reduce la posibilidad de caer en óptimos locales?:
    - ( ) escalada simple.
    - (x) ninguno de ellos.
    - ( ) escalada por máxima pendiente.

53. ¿Cuál o cuáles de las siguientes afirmaciones acerca de los algoritmos de búsqueda no informada son ciertas?:
    - (x) La búsqueda en anchura garantiza obtener la solución óptima siempre y cuando el coste sea unitario.
    - ( ) Los algoritmos de búsqueda no informada requieren de información heurística para que funcionen.
    - ( ) La búsqueda en profundidad garantiza obtener la solución óptima siempre que el coste sea unitario.

54. ¿Cuáles de las siguientes opciones son correctas:
    - ( ) El agente deliberativo dispone de un modelo de los efectos de sus acciones sobre el mundo.
    - ( ) El agente deliberativo dispone de un modelo en el mundo que habita.
    - ( ) El agente deliberativo reacciona a los cambios que percibe, aunque no estén en modelo.
    - (x) a y b son correctas.

55. ¿Cuáles  de los siguientes métodos son búsqueda sin información?:
    - ( ) búsqueda en profundidad pero no búsqueda en anchura.
    - ( ) búsqueda en anchura, pero no búsqueda en profundidad.
    - (x) búsqueda en anchura, búsqueda en profundidad.

56. ¿Cuántos caminos se mantendrán en memoria en la búsqueda en profundidad retroactiva?:
    - ( ) 2.
    - (x) 1.
    - ( ) todos.
    - ( ) 3.

57. ¿El uso de una función heurística garantiza que un método de búsqueda consiga la solución óptima?:
    - ( ) Nunca.
    - ( ) Siempre.
    - (x) Depende del algoritmo y de la heurística.

58. ¿El uso de una función heurística garantiza que un método de búsqueda consiga la solución óptima?:
    - ( ) Siempre.
    - ( ) Nunca.
    - (x) Depende del algoritmo y de la heurística.

59. ¿Qué estrategia de control utiliza un método de escalada?:
    - ( ) Exploración de grafos.
    - (x) Irrevocable.
    - ( ) Retroactiva.

60. ¿Qué representan los nodos cuando se usa la estructura de grafo dirigido para representar un Artificial? ¿Y los arcos?:
    - ( ) Nodos: un objeto; Arcos: un camino.
    - (x) Nodos: un estado del sistema; Arcos: una posible acción.
    - ( ) Nodos: una posible acción; Arcos: un estado del sistema.
    - ( ) Ninguna de las respuestas anteriores es cierta.

61. ¿Sería viable generar el grafo completo para representar el espacio de estados del ajedrez?:
    - ( ) Si, pero es más eficiente trabajar con el grafo implícito.
    - (x) No, tendría demasiados nodos.

62. ¿De entre la búsqueda en anchura y en profundidad retroactiva, ¿cuál de los dos usa menos memoria?:
    - ( ) La búsqueda en anchura.
    - (x) La búsqueda en profundidad retroactiva.
    - ( ) Los dos usan la misma cantidad de memoria.
    - ( ) No usan memoria.

63. ¿En el problema del mono y los plátanos, ¿qué tipo de agente sería más eficaz?:
    - ( ) Social.
    - ( ) Reactivo.
    - (x) Deliberativo.

64. ¿En la búsqueda en anchura es necesario ir analizando desde el estado inicial todos los sucesos para pasar al nivel siguiente en el árbol de búsqueda?:
    - ( ) solo en los primeros pasos.
    - ( ) no.
    - (x) si.

65. ¿En la búsqueda en profundidad retroactiva, el contenido de la memoria almacenada es?:
    - (x) el camino que se está explorando.
    - ( ) el nodo actual.
    - ( ) todos los caminos que se han explorado.

66. ¿La búsqueda en anchura permite obtener la solución con menor número de acciones?:
    - ( ) no.
    - (x) si.
    - ( ) depende del problema.

67. ¿La búsqueda en profundidad retroactiva es una estrategia de búsqueda:
    - ( ) especulativa.
    - (x) tentativa.
    - ( ) explicativa.

68. La principal diferencia entre el algoritmo de escalada simple y el algoritmo de escalada por la máxima pendiente es:
    - ( ) el uso de la heurística sobre los nodos sucesores y el criterio de parada.
    - (x) los estados que se tienen en cuenta para la generación del siguiente estado.
    - ( ) la posibilidad de vuelta atrás y el criterio de parada.

69. ¿Las heurísticas son?:
    - ( ) criterios, métodos o principios para obtener el óptimo.
    - (x) criterios, métodos o principios para decidir cuál de entre varias acciones promete ser la mejor para alcanzar una meta.
    - ( ) funciones usadas en algunos problemas.

70. ¿Los métodos heurísticos en general no garantizan la solución óptima, pero producen resultados que satisfacen la resolución del problema?:
    - ( ) Falso.
    - (x) Verdadero.

71. ¿Los problemas fundamentales de un método de escalada son?:
    - ( ) Cálculo de la heurística.
    - ( ) Mesetas.
    - ( ) Máximos locales.
    - (x) b y c.

72. Qué tipo de aprendizaje aprende una función a partir de ejemplos de sus entradas y salidas?:
    - ( ) Aprendizaje por refuerzo.
    - ( ) aprendizaje no supervisado.
    - (x) aprendizaje supervisado.
    - ( ) no sabe no contesta.

73. Según su funcionamietno, ¿qué estructura de datos sería más apropiada para implementar la búsqueda en profundidad?:
    - ( ) Una cola con prioridad.
    - ( ) Una lista.
    - (x) Una pila.
    - ( ) Una cola.

74. Selecciona la definición que mejor se ajusta al concepto de espacio de estados::
    - (x) Grafo cuyos nodos representan las configuraciones alcanzables (los estados válidos) y explicitan las acciones posibles.
    - ( ) Es la representación de conocimientos del problema, ya generada al inicio del problema en la ejecución del agente.
    - ( ) Grafo cuyos nodos representan acciones, algunas imposibles y otras posibles; el agente elige la que mejora le satisfaga.

75. Una ventaja de los métodos de escalada es que son siempre fáciles de implementar:
    - (x) tan solo los métodos de escalada simples.
    - ( ) tan solo cuando no se incluyen probabilidades.
    - ( ) siempre.

76. ¿Cuál de entre los siguientes algoritmos de escalada tiene más probabilidad de caer en óptimo?:
    - ( ) escalada por máxima pendiente.
    - ( ) enfriamiento simulado.
    - (x) escalada simple.

77. ¿Cuál de entre los siguientes algoritmos de escalada reduce la posibilidad de caer en óptimos locales?:
    - ( ) escalada simple.
    - ( ) escalada por máxima pendiente.
    - (x) enfriamiento simulado.

78. ¿Cuál o cuáles de los siguientes algoritmos tienen una componente aleatoria?:
    - (x) Géneticos.
    - ( ) A*.
    - ( ) Escalada simple.
    - ( ) Escalada máxima pendiente.

79. Cuando la salida de un árbol de decisión es una variable continua, el proble se denomina::
    - ( ) Completo.
    - ( ) continuo.
    - (x) regresión.
    - ( ) no sabe no contesta.

80. ¿El uso de una función heurística garantiza que un método de búsqueda consiga la solución óptima?:
    - ( ) Nunca.
    - ( ) Siempre.
    - (x) Depende del algoritmo y de la heurística.

81. ¿Qué estrategia de control utiliza un método de escalada?:
    - (x) Irrevocable.
    - ( ) Retroactiva.
    - ( ) Exploración en grafos.

82. ¿Qué hace diferente a los algoritmos genéticos de los otros métodos de escalada?:
    - (x) el uso de conjuntos de estados y operaciones sobre conjuntos de estados.
    - ( ) el uso de decisiones probabilísticas.
    - ( ) el uso de estrategias irrevocables.

83. ¿Qué representa en el problema la adecuación con el entorno en un algoritmo genético?:
    - (x) el valor de la función heurística.
    - ( ) la población.
    - ( ) el operador de selección.

84. Cuando se resuelve un problema con un algoritmo genético tanto la condificación del problema:
    - ( ) es conveniente que se adapten al modelo definido por el algoritmo genético.
    - ( ) no es necesario que se adapten al modelo definido por el algoritmo genético.
    - (x) es necesario que se adapten al modelo definido por el algoritmo genético.

85. ¿De los siguientes algoritmos ¿cuál tiene más posibilidades de caer en un máximo o mínimo local?:
    - (x) Escalada máxima pendiente.
    - ( ) Profundizaje iterativo.
    - ( ) Algoritmos genéticos.

86. ¿El algoritmo de enfriamiento simulado es una variante de los métodos de escalada que se cambia en algunos casos?:
    - ( ) estados diferentes al actual.
    - ( ) estados mejores que el actual.
    - (x) estados peores que el actual.

87. ¿El algoritmo de escalada estocástico selecciona el siguiente estado?:
    - ( ) Aleatoriamente entre todos los descendientes.
    - ( ) Aleatoriamente entre todos los descendientes que mejoran al actual y con una probabilidad constante.
    - (x) Aleatoriamente entre todos los descendientes que mejoran al actual y con una probabilidad descendiente proporcional al valor de la heurística del mismo.
    - ( ) Aleatoriamente entre todos los descendientes que mejoran al actual.

88. ¿En el algoritmo de enfriamiento simulado la energía representa?:
    - ( ) un valor global del sistema.
    - ( ) la cercanía al óptimo.
    - (x) la función heurística.

89. En el algoritmo simulado la temperatura representa:
    - ( ) la cercanía al óptimo.
    - (x) un parámetro artificial que permite controlar la conducta del algoritmo a lo largo del tiempo.
    - ( ) el incremento de la función heurística.
    - ( ) un parámetro artificial que permite controlar la definición de la función heurística a lo.

90. La principal diferencia entre el algoritmo de escalada simple y el algoritmo de escalada por la máxima pendiente:
    - ( ) el uso de la heurística sobre los nodos sucesores y el criterio de parada.
    - (x) los estados que se tienen en cuenta para la generación del siguiente estado.
    - ( ) la posibilidad de vuelta atrás y el criterio de parada.

91. Los métodos de escalada tienen como objetivo pasar irrevocablemente desde un nodo al nodo siguiente:
    - ( ) a todos los nodos sucesores.
    - (x) que mejore al nodo actual.
    - ( ) ninguna de las anteriores.

92. Los métodos heurísticos en general no garantizan la solución óptima, pero producen resultados para la resolución deñ problema:
    - (x) Verdadero.
    - ( ) Falso.

93. Los problemas fundamentales de un método de escalada son:
    - ( ) Cálculo de la heurística.
    - ( ) Máximos locales.
    - ( ) Mesetas.
    - (x) d, b y c.

94. Una ventaja de los métodos de escalada es que son siempre fáciles de implementar:
    - ( ) siempre.
    - (x) tan solo los métodos de escalada simples.
    - ( ) tan solo cuando no incluyen probabilidades.

95. Una ventaja de los métodos de escalada es que son siempre fáciles de implementar:
    - ( ) siempre.
    - (x) tan solo los métodos de escalada simples.
    - ( ) tan solo cuando no incluyen probabilidades.

96. En el algoritmo de búsqueda A*, g(n) expresa el coste estimado desde el nodo n hasta el nodo del mejor camino hasta el momento desde el nodo inicial al n:
    - ( ) Verdadero.
    - (x) Falso.

97. Para un nodo, en el algoritmo A* la función g es un valor que no cambia a lo largo del algoritmo:
    - ( ) Verdadero.
    - (x) Falso.

98. Para un nodo, el algoritmo A* la función h es un valor que no cambia a lo largo del algoritmo:
    - (x) Verdadero.
    - ( ) Falso.

99. ¿Cuál de entre los siguientes algoritmos de escalada reduce la posibilidad de caer en óptimos locales?:
    - ( ) escalada simple.
    - ( ) escalada por máxima pendiente.
    - (x) enfriamiento simulado.

100. Según su funcionamiento, ¿qué estructura de datos sería más apropiada para implementar la búsqueda en profundidad sobre grafos?:
    - ( ) Una cola con prioridad.
    - (x) Una pila.
    - ( ) Una cola.

101. Si realizamos un cambio de escala en los valores de la función de evaluación estática, por ejemplo, multiplicar el valor por 10, ¿el algoritmo minimax elige la misma jugada?:
    - ( ) Solo si el cambio de escala aumenta el valor actual.
    - ( ) Solo si el cambio de escala disminuye el valor actual.
    - (x) Sí, no depende de los cambios de escala.

102. Un problema para el que existe una resolución algorítmica ¿podría ser un problema de Inteligencia Artificial?:
    - ( ) Si, esos problemas se incluyen siempre en Inteligencia Artificial.
    - (x) Podría ser, dependiendo del tipo de solución que tenga el problema.
    - ( ) No, ya existe un algoritmo que lo resuelve.

103. ¿En qué consiste actuar racionalmente?:
    - ( ) en percibir y actuar.
    - ( ) en dar una solución aunque no sea la mejor.
    - ( ) en resolver el problema de forma óptima.
    - (x) en actuar de la forma correcta según la información que se posee.

104. En su definición más estricta, una arquitectura reactiva es aquella que:
    - ( ) no incluye ninguna clase de modelo centralizado de representación simbólica del mundo, y hace uso de razonamiento complejo.
    - (x) no incluye ninguna clase de modelo centralizado de representación simbólica del mundo, y/o no hace uso de razonamiento complejo sobre dicha representación.
    - ( ) incluye una clase de modelo centralizado de representación simbólica del mundo, y hace uso de razonamiento complejo.
    - ( ) incluye una clase de modelo centralizado de representación simbólica del mundo, y no hace uso de razonamiento complejo.

105. El aprendizaje basado en instancias:
    - ( ) representa el conocimiento mediante reglas.
    - (x) representa el conocimiento mediante los mismos ejemplos.
    - ( ) representa el conocimiento mediante árboles de decisión.

106. La búsqueda primero el mejor o por el mejor nodo hace uso de una estrategia de control:
    - (x) de exploración en grafos.
    - ( ) irrevocable.
    - ( ) retroactiva.

107. ¿Cuál de los siguientes algoritmos tienen una componente aleatoria?:
    - ( ) Algoritmo A*.
    - (x) Algoritmos genéticos.
    - ( ) Algoritmo de escalada por la máxima pendiente.
    - ( ) Algoritmo de escalada simple.

108. ¿Es esencial el uso de memoria en un agente reactivo?:
    - ( ) no, porque seguiría siendo inteligente, aunque no tuviera memoria.
    - (x) no, pero incluirla provocaría una mejora de la eficiencia y el comportamiento del agente.
    - ( ) no, porque si se incluye dicha memoria pasa a ser un agente deliberativo.
    - ( ) si, porque es imposible que un agente funcione sin memoria.

109. Todo juego bipersonal con información perfecta y suma nula tiene solución.:
    - (x) La afirmación es cierta pero no podemos conseguir resolver de forma práctica juegos complejos.
    - ( ) La afirmación es falsa, el ajedrez es un ejemplo de juego que no se puede resolver.
    - ( ) La verdad de la afirmación depende de la complejidad del juego y de la implementación del algoritmo.

110. En el contexto del aprendizaje automático, ¿Qué es una instancia?:
    - (x) Una observación de una situación conocida en un problema.
    - ( ) Un recurso del sistema.
    - ( ) Un algoritmo de búsqueda.

111. Con qué método de búsqueda se obtienen siempre la solución con un número menor de pasos?:
    - ( ) Descenso iterativo.
    - ( ) Búsqueda en profundidad.
    - ( ) Búsqueda en anchura.
    - (x) a y c son correctas.

112. Cuál de entre los siguientes algoritmos de escalada reduce la posibilidad de caer en óptimos locales?:
    - ( ) escalada por máxima pendiente.
    - ( ) escalada simple.
    - (x) ninguno de ellos.

113. El test de Turing tiene que ver con:
    - ( ) sistemas que piensan como humanos.
    - ( ) sistemas que actúan racionalmente.
    - (x) sistemas que actúan como humanos.
    - ( ) sistemas que piensan racionalmente.

114. Cuando se dice que un agente es capaz de razonar sobre un modelo del mundo para decidir qué hacer para lograr un objetivo, estamos hablando de un agente:
    - ( ) reactivo.
    - ( ) social.
    - (x) deliberativo.

115. El subsistema de explicación de un sistema experto basado en reglas tiene como misión:
    - ( ) deducir los hechos más importantes que se han utilizado en el proceso.
    - (x) justificar como se ha llegado a la decisión propuesta por el sistema.
    - ( ) obtener una retroalimentación de la decisión tomada.

116. ¿Cuál de las siguientes opciones es incorrecta?:
    - (x) El agente deliberativo reacciona a los cambios que percibe, aunque no estén en su modelo del mundo.
    - ( ) El agente deliberativo dispone de un modelo de los efectos de sus acciones sobre el mundo.
    - ( ) El agente deliberativo dispone de un modelo del mundo en el que habita.

117. En el algoritmo A* usando \\(f = g+h\\), la función g es un valor asociado a cada estado que no cambia a lo largo del tiempo:
    - ( ) Es falso, el valor cambia en función de la heurística empleada..
    - (x) Es falso, el valor puede cambiar.
    - ( ) Es cierto, ese valor nunca cambia.

118. En el algoritmo de poda alfa-beta, un nodo min se puede podar cuando:
    - ( ) su valor actual es menor o igual que la cota beta.
    - ( ) su valor actual es mayor que la cota alfa.
    - (x) su valor actual es menor o igual que la cota alfa.
    - ( ) su valor actual es mayor que la cota beta.

119. Cuando tengamos más de una hipótesis que satisfaga todos los ejemplos debemos elegir:
    - (x) la más simple.
    - ( ) la más difícil.
    - ( ) la primera que se haya obtenido.
    - ( ) no saber no contestar.
    - ( ) la que más nos guste.

120. Cuando tengamos más de una hipótesis que satisfaga todos los ejemplos debemos elegir:
    - (x) la más simple.
    - ( ) la más difícil.
    - ( ) la primera que se haya obtenido.
    - ( ) podemos elegir cualquiera.

121. ¿Con qué método de búsqueda, entre los siguientes, se obtiene siempre la solución con un número menor de operadores/acciones?:
    - ( ) Algoritmo genético.
    - ( ) Búsqueda en profundidad.
    - ( ) Enfriamiento simulado.
    - (x) Descenso iterativo.

122. Señalar de entre los siguientes cuál es un modelo de representación del conocimiento:
    - ( ) el campo de potencial.
    - (x) la lógica de predicados.
    - ( ) los algoritmos genéticos.

123. En un grafo Y/O si tenemos un nodo O, debemos:
    - ( ) resolver el subproblema asociado y devolverlo.
    - ( ) resolver todos sus hijos por separado, si todos están resueltos el nodo padre está resuelto, en otro caso el nodo padre no se puede resolver.
    - (x) resolver un nodo hijo para ver si está resuelto, si es así, el padre está resuelto, en caso contrario comprobar con otro hijo, si ninguno de los nodos hijos se puede resolver, el nodo padre tampoco.

124. El enfriamiento simulado consiste en:
    - ( ) definir los valores de las probabilidades del modelo.
    - ( ) definir el número de iteraciones y el valor de la constante K.
    - (x) definir la temperatura de inicio y el cambio de temperatura en las diferentes iteraciones.

125. En el algoritmo A* usando la fórmula f = g+h en cada nodo, ¿qué es la función g?:
    - ( ) Es una estimación del mejor coste para ir desde el nodo actual al nodo objetivo.
    - ( ) Es una estimación del mejor coste para ir desde el estado inicial al estado objetivo pasando por el nodo actual.
    - (x) Es una estimación del mejor coste para ir desde el estado inicial hasta el nodo actual.

126. En un juego la incertidumbre producida por la tirada de un dado se mide:
    - (x) con el caso promedio.
    - ( ) con el caso más desfavorable.
    - ( ) con el caso más favorable.

127. ¿Cuál de las siguientes herramientas no debería emplearse para construir un agente reactivo?:
    - ( ) Un sistema basado en reglas de producción.
    - ( ) Variables de estado.
    - ( ) Una tabla entrada-salida.
    - (x) Un sistema de búsqueda.

128. En el algoritmo de poda alfa-beta, beta es:
    - ( ) el mayor valor actual de entre los nodos MAX en el camino que hay desde el nodo actual al nodo solución.
    - (x) el menor valor actual de entre los nodos MIN en el camino que hay desde el nodo actual al nodo de inicio.
    - ( ) el menor valor actual de entre los nodos MIN en el camino que hay desde el nodo actual al nodo solución.
    - ( ) el mayor valor actual de entre los nodos MAX en el camino que hay desde el nodo actual al nodo de inicio.

129. La búsqueda en anchura permite obtener la solución con menor número de acciones:
    - (x) Sí.
    - ( ) depende del problema.
    - ( ) no.

130. En el problema del mono y los plátanos, donde el mono tiene que determinar una serie de acciones para coger un plátano colgado del techo conociendo los objetos presentes en la habitación, ¿qué tipo de agente sería más apropiado?:
    - ( ) Un agente social.
    - (x) Un agente deliberativo.
    - ( ) Un agente reactivo.

131. Un problema de aprendizaje es realizable:
    - ( ) si el espacio de hipótesis se representa mediante un modelo.
    - ( ) si el espacio de hipótesis es finito.
    - (x) si el espacio de hipótesis contiene a la función verdadera.

132. La arquitectura de subsunción:
    - ( ) consiste en usar ejemplos para aprender el comportamiento del agente y usar ese comportamiento para determinar la acción más apropiada.
    - ( ) consiste en seleccionar reglas usando una determinada ordenación y comprobar si se cumple una condición para asociarle la acción correspondiente.
    - (x) consiste en usar módulos de comportamiento que se activan y que con una determinada prioridad devuelven una acción a aplicar.

133. El algoritmo de escalada estocástico selecciona el siguiente estado:
    - (x) aleatoriamente entre todos los descendientes que mejoran al actual y con una cierta probabilidad para cada descendiente proporcional al valor de la heurística en el mismo.
    - ( ) aleatoriamente entre todos los descendientes que mejoran al actual y con una cierta probabilidad con valor constante para cada descendiente.
    - ( ) aleatoriamente entre todos los descendientes.
    - ( ) aleatoriamente entre todos los descendientes que mejoran al actual.

1Un algoritmo de aprendizaje es bueno si:
    - ( ) produce hipótesis que hacen un buen trabajo al evaluar clasifacaciones de ejemplos observados previamente.
    - (x) produce hipótesis que hacen un buen trabajo al evaluar clasificaciones de ejemplos no han sido observados.
    - ( ) no sabe no contesta.
    - ( ) hace un buen trabajo produciendo clasificaciones de las diferentes hipótesis observadas.

135. Se dice que un problema de aprendizaje es realizable si el espacio de hipotesis:
    - (x) contiene a la función verdadera.
    - ( ) no sabe no contesta.
    - ( ) es lo suficientemente grande.
    - ( ) es continuo.

136. En aprendizaje una hipótesis estará bien generalizada si::
    - (x) puede predecir ejemplos que no se conocen.
    - ( ) es simple.
    - ( ) no sabe no contesta.
    - ( ) es consistente con los datos del conjunto de entrenamiento.

137. Una hipótesis es consistente si:
    - ( ) es completa.
    - (x) satisface a los datos.
    - ( ) no sabe no contesta.
    - ( ) generaliza el conocimiento.

138. En el algoritmo A* CERRADOS representa:
    - ( ) el conjunto de nodos no generados y explorados.
    - ( ) el conjunto de nodos no generados y no explorados.
    - ( ) el conjunto de nodos generados y no explorados.
    - (x) el conjunto de nodos generados y explorados.

139. En el algoritmo de poda alfa-beta, la cota alfa se calcula como el:
    - ( ) el valor mínimo de los nodos MIN en el árbol del juego.
    - ( ) el valor mínimo de los nodos MIN en el camino del nodo a la raíz.
    - (x) el valor máximo de los nodos MAX en el camino del nodo a la raíz.
    - ( ) el valor máximo de los nodos MAX del árbol del juego.

140. 35. En el algoritmo minimax el valor minimax V(J) de un nodo J de la frontera de búsqueda es ___ al de su función de evaluación estática.:
    - ( ) menor.
    - ( ) diferente.
    - ( ) mayor.
    - (x) igual.

141. La complejidad de un juego se mide:
    - ( ) con el resultado de multiplicar la profundidad por la anchura del árbol del juego.
    - ( ) con la profundidad del árbol del juego.
    - ( ) con la anchura del árbol del juego.
    - ( ) con el número de nodos que se procesan.
    - (x) con \\(B^p\\) donde \\(B\\) es el factor de ramificación y P la profundidad.

142. ¿Qué estrategia de control utiliza un método de escalada?:
    - ( ) Exploración en grafos.
    - (x) Irrevocable.
    - ( ) Retroactiva.

143. Las bases de conocimiento:
    - ( ) son dinámicas, pueden incorporar siempre nuevos datos a lo largo del tiempo.
    - ( ) son estáticas, no varían a lo largo del tiempo dado que pueden deducir nuevo conocimiento en cualquier momento.
    - (x) pueden ser estáticas o dinámicas dependiendo del campo que trate y las necesidades que se tengan que cubrir.

144. En el contexto de los problemas de búsqueda ¿qué es el factor de ramificación?:
    - (x) El número promedio de descendientes por nodo.
    - ( ) Un parámetro que determina la probabilidad de mutación en un algoritmo genético.
    - ( ) Una constante asociada al algoritmo de enfriamiento simulado.

145. ¿El uso de una función heurística garantiza que un método de búsqueda consiga la solución óptima?:
    - ( ) Siempre.
    - (x) Depende del algoritmo y de la heurística.
    - ( ) Nunca.

146. ¿Cuál de estos problemas no es de interés para la inteligencia artificial?:
    - (x) Apagar automáticamente un calefactor cuando haya más de 30ºC.
    - ( ) Jugar al ajedrez.
    - ( ) Apagar automáticamente un calefactor cuando se perciba sensación de calor.
    - ( ) Invertir en bolsa.

147. Los sistemas expertos son un ejemplo de:
    - ( ) Sistemas que actúan racionalmente.
    - ( ) Sistemas que piensan como humanos.
    - (x) Sistemas que actúan como humanos.
    - ( ) Ninguna de las otras respuestas.

148. La denominada edad oscura de la I.A., fue debida a que::
    - (x) Se necesitaba un gran conocimiento para resolver problemas específicos y se descubrió la complejidad de algunos problemas.
    - ( ) El trabajo de investigación sobre la IA se desarrollaba en sótanos oscuros..
    - ( ) Se perdió totalmente el interés por la IA, debido a su dificultad..

149. Un problema para el que hay una resolución algorítmica nunca puede ser un problema de I.A.:
    - ( ) False.
    - (x) Depende.
    - ( ) Verdadero.

150. La Inteligencia Artificial surge a partir (seleccionar solo una opción):
    - ( ) La informática y la electrónica.
    - ( ) Filosofía, psicología y neurociencia.
    - (x) Todas las mencionadas y algunas más.

151. ¿Cuál de las siguientes respuestas representa mejor los pasos que lleva a cabo un agente reactivo?:
    - ( ) percibir y buscar la mejor alternativa..
    - (x) b percibir, procesar la información percibida, seleccionar la acción usando esa información y realizar la acción..
    - ( ) percibir y actuar.

152. ¿ Cuál de las siguientes no es una característica propia de los agentes?:
    - ( ) Proactividad.
    - (x) Capacidad individualista.
    - ( ) Autonomía.
    - ( ) Capacidad estímulo-respuesta..

153. ¿Cómo podría beneficiar el uso de una arquitectura de subsunción en un robot aspirador?:
    - ( ) El comportamiento sería emergente y permitiría entender fácilmente el comportamiento global esperado..
    - ( ) Las decisiones se basan en información local..
    - (x) Los estímulos del exterior se procesan por capas especializadas de modo que se siguen unas prioridades a la hora de actuar..

154. ¿Qué es un agente inteligente?:
    - ( ) es el estudio de cómo hacer que los ordenadores hagan cosas que por el momento son realizadas mejor por los seres humanos..
    - (x) es un sistema de ordenador, situado en algún entorno, que es capaz de realizar acciones de forma autónoma y que es flexible para lograr los objetivos planteados..
    - ( ) es el sentido en que se puede tomar una sentencia, un dicho o una expresión..
    - ( ) es un sistema robótico que se desplaza de forma segura por un entorno de habitaciones realizando diversas tareas..

155. ¿Cuál de los siguientes problemas no debería modelizarse como un agente reactivo?:
    - ( ) un robot aspirador.
    - ( ) una casa domotizada.
    - ( ) un robot que recorre el centro de un pasillo.
    - (x) un navegador GPS que recomienda rutas.

156. Las heurísticas son:
    - (x) criterios, métodos o principios para decidir cuál de entre varias acciones promete ser la mejor para alcanzar una meta.
    - ( ) criterios, métodos o principios para obtener el óptimo.
    - ( ) funciones usadas en algunos problemas.

157. ¿Cuál o cuáles de los siguientes juegos son bipersonales con información perfecta? (marcar todos los que sean): Seleccione una o más de una::
    - ( ) Backgammon.
    - ( ) Damas.
    - ( ) Poker.
    - ( ) Ajedrez.
    - (x) e. b y d.

158. En el algoritmo minimax se parte de la hipótesis de que los dos jugadores juegan de manera perfecta. ¿Qué ocurre si uno de ellos falla y no actúa según lo previsto? Seleccione una::
    - ( ) Ese fallo no afecta al contrincante.
    - ( ) El contrincante se perjudica.
    - (x) El contricante se beneficia.

159. La cota beta es::
    - ( ) una cota inferior.
    - (x) una cota superior.

160. En un juego con componente aleatoria los valores de los estados se propagan hacia arriba en las capas aleatorias usando:
    - ( ) una variación de la función heurística.
    - (x) la esperanza matemática.
    - ( ) las cotas alfa o beta según corresponda.

161. En el algoritmo minimax el valor V(J) de un nodo J de la frontera de búsqueda es _____ al de su función de evaluación estática. Seleccione una::
    - ( ) menor.
    - ( ) diferente.
    - ( ) mayor.
    - (x) igual.

162. Entre las múltiples formas de inferir un árbol de decisión la más usada y eficaz consiste en::
    - (x) seleccionar el atributo en cada nivel del árbol en función de la calidad de la división que produce.
    - ( ) crear una ruta del árbol para cada instancia de entrenamiento.
    - ( ) inferir el árbol más pequeño posible que sea compatible con todas las instancias..

163. En aprendizaje una hipótesis estará bien generalizada si::
    - ( ) es consistente con los datos del conjunto de entrenamiento.
    - ( ) es la más simple.
    - (x) puede predecir ejemplos que no se conocen.

164. ¿Qué dice el principio conocido como Navaja de Ockham (cuando dos teorías explican los hechos observados)?:
    - (x) Que la teoría más simple tiene más probabilidades de ser correcta que la compleja.
    - ( ) Que la teoría más simple siempre y en todos los casos es la mejor.
    - ( ) Que la teoría más simple tiene más probabilidades de ser incorrecta que la compleja.
    - ( ) Que la teoría más compleja tiene más probabilidades de ser correcta que la simple.

165. El aprendizaje inductivo se basa en:
    - ( ) aprender en base a prueba y error.
    - ( ) resolver problemas exactamente iguales a los resueltos anteriormente.
    - (x) aprender a partir de ejemplos.

166. Un aprendizaje que se basa en aprender a partir de patrones de entradas sin especificar sus salidas es un aprendizaje::
    - ( ) Por refuerzo.
    - ( ) Supervisado.
    - (x) No supervisado.

167. Según su funcionamiento, ¿qué estructura de datos sería más apropiada para implementar la búsqueda en profundidad sobre grafos?:
    - ( ) Una cola con prioridad.
    - (x) Una pila.
    - ( ) Una cola.
    - ( )  Una lista.

168. Cuando se dice que un agente es capaz de razonar sobre un modelo del mundo para decidir qué hacer para lograr un objetivo, estamos hablando de un agente:
    - ( ) reactivo.
    - ( ) social.
    - (x) deliberativo.

169. El subsistema de explicación de un sistema experto basado en reglas tiene como misión:
    - ( ) deducir los hechos más importantes que se han utilizado en el proceso.
    - (x) justificar como se ha llegado a la decisión propuesta por el sistema.
    - ( ) obtener una retroalimentación de la decisión tomada.

170. ¿Cuál de las siguientes opciones es incorrecta?:
    - (x) El agente deliberativo reacciona a los cambios que percibe, aunque no estén en su modelo del mundo.
    - ( ) El agente deliberativo dispone de un modelo de los efectos de sus acciones sobre el mundo.
    - ( ) El agente deliberativo dispone de un modelo del mundo en el que habita.

171. En el algoritmo A* usando f = g+h, la función g es un valor asociado a cada estado que no cambia a lo largo del tiempo:
    - ( ) Es falso, el valor cambia en función de la heurística empleada..
    - (x) Es falso, el valor puede cambiar.
    - ( ) Es cierto, ese valor nunca cambia.

172. En el algoritmo de poda alfa-beta, un nodo min se puede podar cuando:
    - ( ) su valor actual es menor o igual que la cota beta.
    - ( ) su valor actual es mayor que la cota alfa.
    - (x) su valor actual es menor o igual que la cota alfa.
    - ( ) su valor actual es mayor que la cota beta.

173. Cuando tengamos más de una hipótesis que satisfaga todos los ejemplos debemos elegir:
    - (x) la más simple.
    - ( ) la más difícil.
    - ( ) la primera que se haya obtenido.
    - ( ) podemos elegir cualquiera.

174. ¿Con qué método de búsqueda, entre los siguientes, se obtiene siempre la solución con un número menor de operadores/acciones?:
    - ( ) Algoritmo genético.
    - ( ) Búsqueda en profundidad.
    - ( ) Enfriamiento simulado.
    - (x) Descenso iterativo.

175. Señalar de entre los siguientes cuál es un modelo de representación del conocimiento:
    - ( ) El campo potencial.
    - (x) La lógica de predicados.
    - ( ) Los algoritmos genéticos.

176. En un grafo Y/O si tenemos un nodo O, debemos:
    - ( ) resolver el subproblema asociado y devolverlo.
    - ( ) resolver todos sus hijos por separado, si todos están resueltos el nodo padre está resuelto, en otro caso el nodo padre no se puede resolver.
    - (x) resolver un nodo hijo para ver si está resuelto, si es así, el padre está resuelto, en caso contrario comprobar con otro hijo, si ninguno de los nodos hijos se puede resolver, el nodo padre tampoco.

177. El enfriamiento simulado consiste en:
    - ( ) definir los valores de las probabilidades del modelo.
    - ( ) definir el número de iteraciones y el valor de la constante K.
    - (x) definir la temperatura de inicio y el cambio de temperatura en las diferentes iteraciones.

178. En el algoritmo A* usando la fórmula f = g+h en cada nodo, ¿qué es la función g?:
    - ( ) Es una estimación del mejor coste para ir desde el nodo actual al nodo objetivo.
    - ( ) Es una estimación del mejor coste para ir desde el estado inicial al estado objetivo pasando por el nodo actual.
    - (x) Es una estimación del mejor coste para ir desde el estado inicial hasta el nodo actual.

179. En un juego la incertidumbre producida por la tirada de un dado se mide:
    - (x) con el caso promedio.
    - ( ) con el caso más desfavorable.
    - ( ) con el caso más favorable.

180. ¿Cuál de las siguientes herramientas no debería emplearse para construir un agente reactivo?:
    - ( ) Un sistema basado en reglas de producción.
    - ( ) Variables de estado.
    - ( ) Una tabla entrada-salida.
    - (x) Un sistema de búsqueda.

181. En el algoritmo de poda alfa-beta, beta es:
    - ( ) el mayor valor actual de entre los nodos MAX en el camino que hay desde el nodo actual al nodo solución.
    - (x) el menor valor actual de entre los nodos MIN en el camino que hay desde el nodo actual al nodo de inicio.
    - ( ) el menor valor actual de entre los nodos MIN en el camino que hay desde el nodo actual al nodo solución.
    - ( ) el mayor valor actual de entre los nodos MAX en el camino que hay desde el nodo actual al nodo de inicio.

182. Un problema para el que existe una resolución algorítmica ¿podría ser un problema de Inteligencia Artificial?:
    - ( ) Si, esos problemas se incluyen siempre en Inteligencia Artificial.
    - (x) Podría ser, dependiendo del tipo de solución que tenga el problema.
    - ( ) No, ya existe un algoritmo que lo resuelve.

183. La búsqueda en anchura permite obtener la solución con menor número de acciones:
    - (x) Si.
    - ( ) Depende del problema.
    - ( ) No.

184. En el problema del mono y los plátanos, donde el mono tiene que determinar una serie de acciones para coger un plátano colgado del techo conociendo los objetos presentes en la habitación, ¿qué tipo de agente sería más apropiado?:
    - ( ) Un agente social.
    - (x) Un agente deliberativo.
    - ( ) Un agente reactivo.

185. Un problema de aprendizaje es realizable:
    - ( ) si el espacio de hipótesis se representa mediante un modelo.
    - ( ) si el espacio de hipótesis es finito.
    - (x) si el espacio de hipótesis contiene a la función verdadera.

186. La arquitectura de subsunción:
    - ( ) consiste en usar ejemplos para aprender el comportamiento del agente y usar ese comportamiento para determinar la acción más apropiada.
    - ( ) consiste en seleccionar reglas usando una determinada ordenación y comprobar si se cumple una condición para asociarle la acción correspondiente.
    - (x) consiste en usar módulos de comportamiento que se activan y que con una determinada prioridad devuelven una acción a aplicar.

187. El algoritmo de escalada estocástico selecciona el siguiente estado:
    - (x) aleatoriamente entre todos los descendientes que mejoran al actual y con una cierta probabilidad para cada descendiente proporcional al valor de la heurística en el mismo.
    - ( ) aleatoriamente entre todos los descendientes que mejoran al actual y con una cierta probabilidad con valor constante para cada descendiente.
    - ( ) aleatoriamente entre todos los descendientes.
    - ( ) aleatoriamente entre todos los descendientes que mejoran al actual.

188. En el algoritmo A* CERRADOS representa:
    - ( ) el conjunto de nodos no generados y explorados.
    - ( ) el conjunto de nodos no generados y no explorados.
    - ( ) el conjunto de nodos generados y no explorados.
    - (x) el conjunto de nodos generados y explorados.

189. En el algoritmo de poda alfa-beta, la cota alfa se calcula como el:
    - ( ) el valor mínimo de los nodos MIN en el árbol del juego.
    - ( ) el valor mínimo de los nodos MIN en el camino del nodo a la raíz.
    - (x) el valor máximo de los nodos MAX en el camino del nodo a la raíz.
    - ( ) el valor máximo de los nodos MAX del árbol del juego.

190. n el algoritmo minimax el valor minimax V(J) de un nodo J de la frontera de búsqueda es _____ al de su función de evaluación estática:
    - ( ) menor.
    - ( ) diferente.
    - ( ) mayor.
    - (x) igual.

193. Las bases de conocimiento:
    - ( ) son dinámicas, pueden incorporar siempre nuevos datos a lo largo del tiempo.
    - ( ) son estáticas, no varían a lo largo del tiempo dado que pueden deducir nuevo conocimiento en cualquier momento.
    - (x) pueden ser estáticas o dinámicas dependiendo del campo que trate y las necesidades que se tengan que cubrir.

194. En el contexto de los problemas de búsqueda ¿qué es el factor de ramificación?:
    - (x) El número promedio de descendientes por nodo.
    - ( ) Un parámetro que determina la probabilidad de mutación en un algoritmo genético.
    - ( ) Una constante asociada al algoritmo de enfriamiento simulado.

195. ¿El uso de una función heurística garantiza que un método de búsqueda consiga la solución óptima?:
    - ( ) Siempre.
    - (x) Depende del algoritmo y de la heurística.
    - ( ) Nunca.
