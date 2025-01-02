# Fundamentos de Bases de Datos. Tipo Test Parcial II

**Autor**: Elías Monge Sánchez
***

- **Asignatura:** Fundamentos de Bases de Datos
<!--- Curso Académico: Actualizado al curso 2024-25-->
<!--- Grado: Preguntas comunes para el Grado en Ingeniería Informática y los Dobles Grados-->
<!--- Grupo: A.-->
<!--- Profesor: Ignacio Rojas Ruiz.-->
<!--- Fecha: 19-10-2023.-->
- **Descripción**: Recopilación de preguntas Tipo Test del Parcial II (Tema 4 y Seminarios 3-4).<br>
Si encuentran algún error o pregunta repetida, rogamos nos lo comuniquen.
______

1. Al aplicar `DROP TABLE` sobre una tabla `T`:
    - ( ) Se borrarán las tuplas de la tabla, aunque se mantenga la tabla en nuestro esquema.
    - (x) Es posible que se produzca un error, aunque la tabla `T` exista en nuestro esquema.
    - ( ) Ninguna de las otras opciones es cierta.

2. Considere la tabla `PIEZA (codpie, nompie, color)`, cuya clave primaria es `codpie`; considere la consulta: *encontrar los colores que cumplen que el número de piezas de la tabla que tienen ese color es exactamente 2*:
    - (x) La consulta se puede resolver tanto con SQL como con Álgebra Relacional.
    - ( ) La consulta no se puede resolver con SQL.
    - ( ) La consulta se puede resolver con SQL, pero no se puede resolver con Álgebra Relacional.

3. Considere una tabla \\(T(A,B)\\). En relación con los operadores del Álgebra Relacional:
    - ( ) La consulta \\(\pi_A(T) \cup \pi_B(T)\\) equivale a \\(\pi_{A,B}(T)\\)
    - (x) La consulta \\( \sigma_{A=a_1}(T) \cap \sigma_{B=b_1}(T)\\) se puede plantear con una sola selección sobre la tabla \\(T\\).
    - ( ) Ninguna de las otras opciones es cierta.

4. Cuando operamos con dos tablas que están conectadas por una clave externa formada por dos atributos:
    - ( ) Es posible que su producto cartesiano devuelva menos tuplas que su reunión.
    - ( ) Es imposible que su producto cartesiano devuelva más tuplas que su reunión.
    - (x) Ninguna de las otras es cierta.

5. Considere la siguiente consulta en SQL: `SELECT codpro FROM ventas`.
    - ( ) El resultado de dicha consulta coincidirá, en cualquier caso, con la proyección por el campo `codpro` de la tabla `ventas`.
    - ( ) El resultado de dicha consulta coincidirá, en cualquier caso, con el de la siguiente consulta:<br><code>SELECT codpro FROM ventas WHERE cantidad >= 1000<br>UNION<br>SELECT codpro FROM ventas WHERE cantidad < 1000;</code>
    - (x) Ninguna de las otras opciones es cierta.

6. Considere dos tablas \\(T_1\\) y \\(T_2\\) con esquemas equivalentes. Considere la siguiente expresión en Álgebra Relacional: \\((T_1 - T_2) \cup T_2\\). El resultado de aplicar dicha operación sobre dos instancias \\(t_1\\) y \\(t_2\\) de las tablas:
    - ( ) Producirá siempre como resultado una instancia \\(t\\) contenida en o igual a \\(t_2\\).
    - ( ) Producirá siempre como resultado la instancia \\(t_1\\).
    - (x) Ninguna de las otras opciones es cierta.

7. En relación con la capacidad de consulta:
    - (x) Todas las consultas que se pueden resolver con Álgebra Relacional, se pueden resolver con SQL.
    - ( ) Todas las consultas que se pueden resolver con SQL, se pueden resolver con Álgebra Relacional.
    - ( ) No sabe o no contesta.

8. Considere dos tablas \\(T_1\\) y \\(T_2\\) tales que el esquema de \\(T_2\\) está contenido en el de \\(T1\\). Considere la siguiente expresión en Álgebra Relacional: \\((T_1/T_2) \times T_2\\). El resultado de aplicar dicha operación sobre dos instancias \\(t_1\\) y \\(t_2\\) de las tablas:
    - (x) Producirá como resultado una instancia \\(t\\) contenida en o igual a \\(t_1\\).
    - ( ) Producirá siempre como resultado la instancia \\(t_1\\).
    - ( ) Ninguna de las otras opciones es cierta.

9. Cuando operamos con dos tablas que están conectadas por una clave externa:
    - ( ) Su producto cartesiano siempre devuelve la misma cantidad de tuplas que su reunión.
    - (x) Su producto cartesiano puede devolver más tuplas que la reunión, aunque no siempre.
    - ( ) Su producto cartesiano puede devolver menos tuplas que su reunión, aunque no siempre.

10. En relación con los operadores fundamentales y no fundamentales del Álgebra Relacional:
    - ( ) Solo una parte de los operadores no fundamentales pueden reproducirse utilizando operadores fundamentales.
    - (x) Todos los operadores no fundamentales pueden reproducirse utilizando operadores fundamentales.
    - ( ) Todos los operadores fundamentales pueden reproducirse utilizando operadores no fundamentales.

11. En general, en Oracle si añadimos un índice a una tabla:
    - ( ) Habrá que reescribir todas las sentencias de consulta que hayamos planteado previamente sobre dicha tabla, puesto que pueden dar errores sintácticos.
    - ( ) Habrá que reescribir solo las sentencias de consulta en las que aparezca la tabla más de una vez, puesto que darán errores sintácticos.
    - (x) Ninguna de las otras opciones es cierta.

12. En relación con el comando `DESCRIBE`:
    - ( ) Se trata de un comando fundamental, puesto que la información que proporciona sobre dichas tablas es imposible de obtener de otra manera.
    - (x) La información que proporciona el comando `DESCRIBE` sobre dichas tablas está almacenada en el catálogo de la base de datos.
    - ( ) Ninguna de las otras opciones es cierta.

13. Un índice primario:
    - ( ) Nunca puede ser denso.
    - ( ) Nunca puede ser no denso.
    - (x) Ninguna de las otras es cierta.

14. En general para acceder a los datos:
    - (x) Ni índices ni acceso directo son mejores en términos absolutos frente al otro.
    - ( ) El acceso directo es siempre la mejor alternativa si está disponible en el SGBD.
    - ( ) Los índices son siempre la mejor alternativa si está disponible en el SGBD.

15. En un índice de mapa de bits:
    - ( ) El número de entradas es el doble del número de valores que tiene la clave por la que se quiere indexar el fichero.
    - ( ) El número de entradas coincide con el número de registros que hay en el fichero que se quiere indexar.
    - (x) El número de entradas coincide con el número de valores que tiene la clave por la que se quiere indexar el fichero.

16. En la aproximación del método de acceso a la base de datos vista en clase:
    - ( ) El gestor de archivos y el gestor de disco son dos elementos del S.O. que permiten la transformación entre páginas almacenadas y sectores de disco.
    - ( ) El gestor de archivos y el gestor de disco son dos formas de decir lo mismo.
    - (x) Ninguna de las otras es cierta.

17. Cuando se utilizan técnicas de hashing básico:
    - ( ) Deja de ser necesario usar estrategias para solventar colisiones, puesto que estas no pueden presentarse.
    - ( ) En general, no ayuda a conocer zonas del dominio del campo clave donde pueden presentarse más valores.
    - (x) Es posible que se produzcan huecos.

18. En relación con los índices:
    - ( ) No se pueden utilizar si el fichero de datos no está ordenador por la clave del índice.
    - ( ) Cuantos más campos añadamos a la clave de búsqueda, más rápido será el proceso de búsqueda en el índice por uno de esos campos.
    - (x) Ninguna de las otras es cierta

19. En general, cuanto mayor es el número de colisiones que produce una función hash
    - (x) Las búsquedas tenderán a ser más lentas
    - ( ) Menos huecos se producirán
    - ( ) Ninguna de las otras es cierta

20. Un objetivo primordial en relación con el método de acceso es:
    - ( ) Evitar la aparición de valores nulos
    - ( ) Ocultar al usuario el verdadero valor de la clave física
    - (x) Ninguna de las otras es cierta

21. Considere las tablas organizadas por índice (IOT):
    - ( ) Son la forma de implementar los arboles B+ en bases de datos
    - ( ) La clave de búsqueda del índice no tiene nada que ver con la clave física
    - (x) Ninguna de las otras es cierta

22. En el nivel interno
    - ( ) El almacenamiento persistente de los datos se hace con dispositivos de memoria de las primeras posiciones de la jerarquía de memoria para que las operaciones sean más rápidas.
    - ( ) El almacenamiento persistente de los datos se hace con dispositivos de memoria de las primeras posiciones de la jerarquía de memoria para que sea más barata la implantación del sistema.
    - (x) Ninguna de las otras es cierta

23. Considere que se está usando Hashing dinámico. En un momento dado, al insertar un nuevo registro en un cubo con profundidad local igual a la profundidad global:
    - (x) En ningún caso habrá que desdoblar la tabla índice.
    - ( ) Es posible que no haya que desdoblar la tabla índice
    - ( ) Necesariamente habrá que desdoblar la tabla índice.

24. Considere un fichero secuencial indexado:
    - ( ) Cuanto mas grandes sean los registros del fichero índice, más se ayudará a acelerar el proceso de búsqueda.
    - (x) Cuando más pequeños sean los registros del fichero índice, más se ayudará a acelerar el proceso de búsqueda.
    - ( ) Ninguna de las otras es cierta

25. El Hashing dinámico:
    - (x) Va asignando más espacio en disco a zonas del dominio de la clave donde se van presentando más valores en la instancia de la base de datos.
    - ( ) Asigna mas espacio en disco a aquellas zonas del dominio de la clave que teóricamente van a presentar más valores en la instancia de la base de datos.
    - ( ) No utiliza ninguna estructura auxiliar, aparte del propio fichero que almacena los registros.

26. En un árbol B+:
    - (x) Cuanto menor es \\(M\\), mayor tiende a ser el número de niveles.
    - ( ) Cuanto mayor es \\(M\\), mayor tiende a ser el número de niveles
    - ( ) Ninguna de las otras es cierta.

27. La BD en el nivel interno se puede representar de distintas formas, pero:
    - ( ) Nunca deben ubicarse juntos registros de distinto tipo para facilitar operaciones.
    - ( ) Cuando se ponen juntos los registros del mismo tipo, se optimizan operaciones como las de reunión de tablas.
    - (x) Ninguna de las otras es cierta.

28. Cuando se utiliza Hashing dinámico:
    - ( ) No se puede utilizar una función de direccionamiento.
    - ( ) Es imposible que se produzcan colisiones.
    - (x) Ninguna de las otras es cierta.

29. En relación con el método de acceso a la BD, las páginas o bloques de la BD deben tener un tamaño múltiplo de las páginas o bloques del sistema operativo...
    - ( ) Para garantizar que la memoria y el disco duro sean compatibles.
    - (x) Para aprovechar bien cada operación de E/S en disco.
    - ( ) Para que sea fácil hacer cuentas a la hora de organizar los datos.

30. Cuando se organiza el acceso a los datos de un fichero mediante el uso de índices:
    - ( ) En general, lo mejor es usar tantos índices como configuraciones de consulta pueden plantearse.
    - ( ) Si el espacio de disco no es un problema, lo mejor es usar tantos índices como configuraciones de consulta puedan plantearse.
    - (x) Ninguna de las otras es cierta.

31. Al respecto de los índices jerárquicos:
    - (x) El número de niveles depende, entre otras cosas, del número de registros del fichero de datos.
    - ( ) Los arboles B+ no son un ejemplo de índice jerárquico.
    - ( ) Los arboles B no son un ejemplo de índice jerárquico.

32. En general, cuando se utiliza un índice denso:
    - ( ) Al realizar una operación de borrado de un registro en el fichero nunca hay que actualizar el índice.
    - ( ) Al realizar una operación de inserción de un nuevo registro en el fichero nunca hay que actualizar el índice.
    - (x) Ninguna de las otras es cierta.

33. En la indexación con árboles B:
    - (x) El orden de un árbol influye directamente en el número de niveles.
    - ( ) El orden de un árbol se determina por el tamaño de página/bloque que se asigna a los nodos.
    - ( ) Se puede montar un árbol B sobre cualquier campo.
    - ( ) Las otras respuestas indicadas son ciertas.

34. La técnica de acceso directo:
    - ( ) No utiliza área de desbordamiento.
    - ( ) Garantiza siempre que encuentro una fila con una sola lectura de bloque.
    - (x) No permite realizar la lectura secuencial de datos en un rango.
    - ( ) No necesita una estimación previa del número de registros.

35. El objetivo principal de los mecanismo de indexación y métodos de acceso es:
    - (x) Localizar datos requeridos con el número mínimo de operaciones de lectura en disco.
    - ( ) Garantizar que no se duplique la clave primaria
    - ( ) Acceder a los datos de una tabla de forma ordenada.

36. El clúster:
    - ( ) Perjudica la lectura individual de las tablas que contiene
    - ( ) Acelera las consultas que involucran la reunion natural de las tablas que contiene.
    - ( ) Es una estructura inter-archivo.
    - (x) Todo lo anterior es cierto.

37. En un índice denso:
    - ( ) El índice ocupa lo mismo que la tabla indexada.
    - ( ) El número de registros del índice es menor que el número de registros de la tabla indexada.
    - (x) El número de registros del índice es igual al número de registros de la tabla indexada.
    - ( ) Ninguna de las otras respuestas propuestas es cierta.

38. En el Hashing extendido:
    - (x) Lo mejor es que la pseudollave se ajuste al tamaño del índice que se guarda en memoria.
    - ( ) Lo mejor es que la pseudollave tenga muchos dígitos.
    - ( ) Hay que reservar de antemano un número fijo de bloques.
    - ( ) No hay que tener una estimación del número de registros a almacenar.

39. Las páginas que componen un archivo almacenado:
    - ( ) Contienen siempre registros de una misma tabla.
    - ( ) Pueden ser de distinto tamaño dependiendo del tamaño de los registros que se almacenen en ellas.
    - ( ) Tienen que estar consecutivas en disco.
    - (x) Todo lo anterior es falso.

40. Sean \\(F\\) y \\(D\\) las tablas procedentes de una entidad fuerte y una débil, respectivamente. Las filas de \\(D\\) se recuperan con las de \\(F\\), y rara vez, por separado. La mejor opción sería:
    - ( ) Indexar \\(D\\) por el atributo que tiene en común con \\(F\\).
    - ( ) Crear una vista en la que aparezcan los datos de ambas tablas en el formato adecuado.
    - (x) Almacenarlas conjuntamente en un clúster.
    - ( ) Poner en \\(D\\) como clave externa el atributo que tiene en común con \\(F\\).

41. Indica la afirmación verdadera:
    - (x) Se pueden montar tantos índices densos como se necesiten.
    - ( ) En ficheros no ordenados físicamente se pueden montar índices no densos
    - ( ) El índice no denso es el único mecanismo de indexación posible cuando los datos están ordenados físicamente.
    - ( ) Un árbol B solo se puede montar sobre la clave física de un archivo.

42. La sentencia `CREATE TABLE` provoca:
    - (x) La creación de un nuevo archivo almacenado.
    - ( ) La creación de un nuevo fichero en disco.

43. Un índice no denso:
    - ( ) Permite realizar preguntas de tipo existencial sin acceder al fichero de datos.
    - (x) Exige que los registros esten ordenados físicamente.
    - ( ) El rendimiento desciende considerablemente cuando se realizan muchas inserciones o borrados en la tabla.
    - ( ) Es adecuado para consultas por rangos de valores del campo clave.

44. El *record identifier* (RID):
    - ( ) Es un campo de un índice denso.
    - ( ) Es un campo de un indice no denso.
    - ( ) Puede servir para identificar varios registros.
    - (x) Se calculan mediante un algoritmo de direccionamiento.

45. El índice por clave invertida:
    - ( ) Se puede montar sobre cualquier campo de la tabla.
    - (x) Ayuda a distribuir mejor los datos en el espacio de almacenamiento.
    - ( ) Es útil para recorrer una tabla por el campo clave en orden inverso al establecido.
    - ( ) Todo lo anterior es cierto.

46. En Hashing dinámico si el número de registros por bloque es 4 y tengo alrededor de 1000 registros, el número de bits necesario para la tabla hash es:
    - (x) 8
    - ( ) 4
    - ( ) 16
    - ( ) 5

47. Cuando se necesita acceder a la tabla `alumnos` por rangos de notas el mejor mecanismo es:
    - ( ) Un índice no denso.
    - (x) Un índice denso
    - ( ) Un índice de mapa de bits
    - ( ) Hashing básico.

48. Cuando la cardinalidad del campo por el que se indexa una tabla es muy baja, el mejor mecanismo de indexación es:
    - ( ) Un árbol B donde el conjunto secuencia sea denso.
    - ( ) Un árbol B donde el conjunto secuencia sea no denso.
    - ( ) Algún mecanismo de acceso directo.
    - (x) Un índice de mapa de bits.

49. Indica cual de estas afirmaciones es verdadera:
    - ( ) El tamaño de los bloques físicos y de las páginas deben ser independientes.
    - ( ) El nivel interno de una base de datos está enteramente gestionado por el SO del ordenador.
    - (x) Las páginas que componen un archivo almacenado no tienen porque estar consecutivas en disco.

50. Con la consulta `SELECT codpro, sum(cantidad) FROM ventas GROUP BY codpro`:
    - (x) Se puede crear una vista, pero no será actualizable.
    - ( ) No se puede crear una vista por estar agrupada.
    - ( ) Se puede crear una vista y será actualizable porque solo usa una tabla.
    - ( ) Ninguna de las anteriores es cierta.

51. Las tablas organizadas por índice (IOT):
    - ( ) No admiten ningún tipo de índice
    - ( ) No tienen llave primaria
    - ( ) No pueden recuperarse de forma ordenada.
    - (x) Se organizan como un árbol B cuyas hojas contienen las tuplas.

52. Indica cual de estas afirmaciones es **FALSA**:
    - ( ) En el Hashing extendido una mala elección en el tamaño de las páginas puede obligar a reorganizar completamente la estructura.
    - ( ) El Hashing extendido es muy eficaz porque la tabla hash va en memoria principal
    - (x) El índice no denso es el único mecanismo de indexación posible cuando los datos están ordenados físicamente.
    - ( ) La actualización de los archivos puede no influir en la actualización de los índices no densos.

53. En general, un algoritmo de direccionamiento:
    - ( ) Interesa que produzca pocos huecos, aunque da igual el número de colisiones que genere.
    - ( ) Interesa que produzca pocas colisiones, aunque da igual el número de huecos que genere.
    - (x) Interesa que produzca pocas colisiones y pocos huecos.

54. La técnica de hashing que va asignando más cubos a zonas del dominio de la clave donde se van presentando más valores en la instancia de la base de datos:
    - ( ) Es el hashing básico.
    - (x) Es el hashing dinámico
    - ( ) Ninguna de las otras es cierta.

55. Considere que se está usando hashing dinámico. En ese caso:
    - (x) Es posible que se produzcan colisiones.
    - ( ) Da igual la función hash que se utilice.
    - ( ) Ninguna de las otras es cierta.

56. Considere las tablas organizadas por índice:
    - ( ) Solo las operaciones de borrado implican operar sobre el índice asociado.
    - ( ) Sólo las operaciones de actualización implican operar sobre el índice asociado.
    - (x) El índice asociado sirve para acelerar algunas consultas.

57. En los índices multinivel:
    - (x) El número de accesos a disco está relacionado con el número de niveles del índice.
    - ( ) Siempre permiten localizar el registro con un único acceso a disco.
    - ( ) Sólo se pueden construir sobre la clave física.

58. Un factor de bloqueo alto:
    - ( ) Aumenta la aparición de valores nulos en el campo de la clave física.
    - (x) Disminuye la aparición de valores nulos en el campo de la clave física.
    - ( ) Ninguna de las otras es cierta.

59. Considere un índice montado sobre los siguientes campos de un registro (en el orden que se muestran): `nombre, ciudad, color`:
    - (x) El índice es útil para consultas que tratan de localizar los registros correspondientes a un determinado nombre.
    - ( ) El índice es útil para consultas que tratan de localizar los registros correspondientes a una determinada ciudad.
    - ( ) Ninguna de las otras es cierta.

60. A la hora de decidir si se crea un determinado índice en la BD:
    - ( ) Sólo hay que tener en cuenta si aumenta la eficiencia de alguna consulta.
    - (x) Debemos tener en cuenta que operaciones como las de inserción se pueden ver ralentizadas.
    - ( ) Ninguna de las otras es cierta.

61. Considere que tengo que ubicar registros de cuentas bancarias y registros con los movimientos de dichas cuentas bancarias:
    - ( ) En cualquier caso, es mejor no usar ningún tipo de agrupamiento.
    - ( ) En cualquier caso, utilizaré agrupamiento interarchivo.
    - (x) Ninguna de las otras es cierta.

62. Desde un punto de vista general, si una BD es lo suficientemente pequeña:
    - ( ) Nos bastará con tenerla en memoria caché, sin necesidad de respaldo de un dispositivo no volátil como el disco duro.
    - ( ) Nos bastará con tenerla en memoria principal, sin necesidad de respaldo de un dispositivo no volátil como el disco duro.
    - (x) Ninguna de las otras es cierta.

63. En general, si quiero optimizar consultas del tipo "dame los registros cuyo valor del campo `X`, está comprendido entre \\(x_1\\) y \\(x_2\\), con \\(x1<x2\\):
    - ( ) Debo optar por técnicas de hashing dinámico.
    - ( ) Debo optar por técnicas de hashing básico.
    - (x) Ninguna de las otras es cierta.
  
64. Considere los árboles B+ (Tree1 y Tree2) construidos sobre la misma clave y el mismo fichero, y que el valor de M en Tree1 es mayor que el valor de M en el Tree2:
    - ( ) Entonces el número de valores de la clave presentes en el nivel de las hojas de Tree1 será menor que el número de valores de la clave presentes en el nivel de las hojas de Tree2.
    - ( ) Entonces el número de valores de la clave presentes en el nivel de las hojas de Tree1 será mayor que el número de valores de la clave presentes en el nivel de las hojas de Tree2.
    - (x) Ninguna de las otras es cierta.

65. La gestión de archivos de S.O es llevada a cabo por:
    - ( ) El gestor de eventos.
    - (x) El gestor de disco.
    - ( ) El gestor de archivos.
    
66. Considere un índice de clave invertida sobre el código de empleado de una tabla de empleados:
    - ( ) En ese índice, los códigos 7698 y 8967 producen una colisión.
    - ( ) El índice no sirve para consultas del tipo: localizar el empleado cuyo código es 7698.
    - (x) Ninguna de las otras es cierta.

67. En relación a los índices de mapa de bits:
    - (x) En general, no es adecuado construirlos sobre la clave primaria.
    - ( ) Cuantas más tuplas tiene la tabla, más cortos son los mapas de bits asociados a un valor.
    - ( ) Ninguna de las otras es cierta.

68. En el hashing dinámico, en un momento dado:
    - ( ) Todos los cubos deben tener el mismo valor de profundidad local.
    - (x) La profundidad local puede variar de unos cubos a otros.
    - ( ) Todos los cubos que están llenos tienen que tener el mismo valor de profundidad local.
  
69. En relación con la forma de representar la BD en el nivel interno:
    - ( ) Debe estar orientada a maximizar la E/S a disco.
    - ( ) Es obligatorio que cada conjunto de registros del mismo tipo sea un fichero.
    - (x) Ninguna de las otras es cierta.

70. En relación con el uso de índices:
    - ( ) No suponen el consumo de espacio extra en disco porque sólo se almacenan en memoria principal
    - (x) Debemos analizar su conveniencia, porque puede acelerar unas operaciones, pero ralentizar otras.
    - ( ) Aunque ocupan espacio extra, todas las operaciones se ven mejoradas en eficiencia o se mantienen igual.
  
71. Considere un índice denso que no sea jerárquico:
    - ( ) Nunca puede ser un índice secundario.
    - ( ) Nunca puede ser un índice primario.
    - (x) Ninguna de las otras es cierta.