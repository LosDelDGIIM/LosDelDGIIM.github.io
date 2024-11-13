<br>
# Fundamentos de Bases de Datos. Tipo Test Parcial I

**Autor:** Arturo Olivares Martos
***

- **Asignatura:** Fundamentos de Bases de Datos
<!--- **Curso Académico:** Actualizado al curso 2024-25-->
<!--- **Grado:** Preguntas comunes para el Grado en Ingeniería Informática y los Dobles Grados-->
<!--- **Grupo:** A.-->
<!--- **Profesor:** Ignacio Rojas Ruiz.-->
<!--- **Fecha:** 19-10-2023.-->
- **Descripción:** Recopilación de preguntas Tipo Test del Parcial I (Temas 1-3 y Seminarios 1-2).<br>
Si encuentran algún error o pregunta repetida, rogamos nos lo comuniquen.
______

1. Un modelo de datos es ...
    - ( ) Un mecanismo formal para consultar información de manera general y sistemática.
    - ( ) Las otras respuestas mencionadas son correctas.
    - (x) Un mecanismo formal para representar y manipular información de manera general y sistemática.
    - ( ) Un mecanismo formal para programar datos en programas de aplicación.

2. El lenguaje anfitrión o de aplicación ...
    - (x) Complementa al DSL para hacer procesamiento avanzado de datos o facilitar el desarrollo de la interfaz de usuario.
    - ( ) Complementa al DSL con nuevos tipos de datos.
    - ( ) Evita tener que aprender un nuevo lenguaje para acceder a una base de datos.
    - ( ) Al tratarse de un lenguaje de más bajo nivel que el DSL, acelera el acceso a los datos.

3. El nivel interno ...
    - ( ) Supone una abstracción del nivel conceptual.
    - ( ) Es otra forma de llamar al Sistema Operativo.
    - ( ) Supone una abstracción del nivel lógico.
    - (x) Es la representación más cercana a la estructura de almacenamiento físico.

4. Al actualizar una clave externa ...
    - ( ) El sistema lo impide para mantener la consistencia.
    - ( ) Se debe aceptar siempre el cambio si el valor nuevo es nulo.
    - ( ) Se debe aceptar el cambio si el valor nuevo no pertenece al dominio activo de la clave referenciada.
    - (x) Se debe aceptar el cambio si el valor nuevo pertenece al dominio activo de la clave referenciada.

5. En relación con la redundancia y la inconsistencia:
    - ( ) La ausencia de la segunda indica la ausencia de la primera.
    - ( ) Son dos formas de referirse a lo mismo.
    - ( ) Redundancia e inconsistencia no guardan relación.
    - (x) La primera facilita que aparezca la segunda.

6. El conjunto de atributos de una relación junto con sus dominios se llama ...
    - ( ) Tupla.
    - ( ) Instancia.
    - (x) Esquema.
    - ( ) Grado.

7. Los datos operativos son:
    - ( ) Cualquier información que guarde la empresa.
    - ( ) Sólo datos relativos a ítems básicos de nuestro problema.
    - (x) Piezas de información que necesita una organización para su funcionamiento.
    - ( ) Sólo datos relativos a ítems básicos de nuestro problema y sus atributos.

8. Una abstracción global de la BD desde el punto de vista lógico se encuentra ...
    - ( ) En el nivel interno.
    - ( ) En el nivel externo.
    - (x) En el nivel conceptual.
    - ( ) En todos los niveles en su conjunto.

9. PL/SQL es un ejemplo de ...
    - ( ) Acoplamiento débil.
    - (x) Acoplamiento fuerte.
    - ( ) Lenguaje anfitrión.
    - ( ) DCL.

10. Una vista de usuario ...
    - ( ) Puede definirse sobre otras vistas de usuario.
    - (x) Todas las respuestas mencionadas son correctas.
    - ( ) Forma parte de un esquema externo.
    - ( ) Puede contener atributos que no aparezcan en el nivel conceptual.

11. Gracias a la independencia lógica:
    - ( ) Se puede modificar un esquema externo sin que afecte al nivel conceptual.
    - (x) Se puede modificar el esquema conceptual sin que afecte al nivel externo.
    - ( ) Se puede modificar el esquema interno sin que afecte al nivel conceptual.
    - ( ) Se puede modificar el esquema conceptual de la BD sin que afecte al nivel interno.

12. Un valor nulo es ...
    - ( ) Un valor cero.
    - ( ) No se admite ese valor en una BD.
    - (x) Un valor desconocido o no aplicable.
    - ( ) Un valor desconocido.

13. De la definición de clave candidata se deduce que sus atributos:
    - ( ) No pueden tomar el valor nulo.
    - ( ) Todas las respuestas mencionadas son correctas.
    - ( ) Podrían tomar el valor nulo parcialmente.
    - (x) No pueden duplicar su valor en la misma tabla.

14. El modelo de datos jerárquico ...
    - ( ) Implementa todas las cardinalidades de forma similar.
    - ( ) Tiene problemas con las relaciones uno a uno.
    - (x) Tiene problemas con las relaciones muchos a muchos.
    - ( ) Tiene problemas con las relaciones muchos a uno.

15. El expediente académico de un alumno que se obtiene de la aplicación de la Secretaría de un Centro forma parte de:
    - ( ) Una correspondencia externa-conceptual.
    - (x) Un esquema externo.
    - ( ) Un esquema conceptual.
    - ( ) Una correspondencia externa-externa.

16. Respecto a la fusión de tablas:
    - ( ) Si dos tablas comparten clave primaria y candidata no deben fusionarse.
    - ( ) Es muy conveniente fusionar una entidad débil con la fuerte de la que depende.
    - (x) Ninguna de las otras respuestas mencionadas es correcta.
    - ( ) Siempre que dos tablas compartan las claves primarias deben fusionarse.

17. La regla de integridad de entidad ...
    - ( ) Siempre permite nulos en la clave primaria.
    - ( ) A veces permite nulos en la clave primaria, en función de la semántica del problema.
    - (x) Nunca permite valores nulos en la clave primaria.
    - ( ) No permite valores duplicados en las claves candidatas.

18. Sean `R` y `S` dos tablas tales que `S` tiene definida una clave externa sobre `R`. Si se quiere eliminar una fila de `R`, el sistema...
    - ( ) Prohíbe el borrado.
    - ( ) Lo acepta pero también borra las filas de la tabla `S` donde se haga referencia al valor de la clave primaria que se va a eliminar.
    - ( ) Lo acepta pero pone valores nulos en las filas de la tabla `S` donde se haga referencia al valor de la clave primaria que se va a eliminar.
    - (x) Permite al diseñador elegir entre las tres opciones anteriores.

19. SQL es ...
    - (x) Un DSL.
    - ( ) Un DDL.
    - ( ) Un lenguaje de consulta.
    - ( ) Un DML.

20. El rango de valores que puede tomar un atributo se denomina ...
    - ( ) Integridad referencial.
    - ( ) Tipo de dato.
    - (x) Dominio.
    - ( ) Dominio activo.

21. El concepto de seguridad se refiere a la realización de copias periódicas de los datos.
    - ( ) Verdadero.
    - (x) Falso.

22. Como solo acceden a través de las aplicaciones, los usuarios finales no pueden actualizar una base de datos.
    - ( ) Verdadero.
    - (x) Falso.

23. El nivel interno debe ser diseñado por el administrador.
    - (x) Verdadero.
    - ( ) Falso.

24. El SGBD debe gestionar los accesos concurrentes de manera que la BD esté siempre libre de errores.
    - (x) Verdadero.
    - ( ) Falso.

25. Puesto que una BD ofrece los datos centralizados, la arquitectura centralizada es siempre la más conveniente.
    - ( ) Verdadero.
    - (x) Falso.

26. El catálogo de una BD ofrece almacenar los metadatos de la misma y debe ser accesible a los usuarios.
    - (x) Verdadero.
    - ( ) Falso.

27. La introducción de nuevas aplicaciones implica la modificación de todos los niveles de la BD.
    - ( ) Verdadero.
    - (x) Falso.

28. Las aplicaciones deben actualizarse cuando el administrador indexa una tabla por algún atributo.
    - ( ) Verdadero.
    - (x) Falso.

29. `UPDATE...` un comando:
    - ( ) DDL.
    - (x) DML.
    - ( ) DCL.
    - ( ) DSL.

30. La independencia física es posible gracias a la correspondencia externa-conceptual.
    - ( ) Verdadero.
    - (x) Falso.

31. La elaboración del esquema conceptual es tarea del programador de aplicaciones.
    - ( ) Verdadero.
    - (x) Falso.

32. Las reglas de integridad de una BD deben formar parte del esquema de la misma y almacenarse dentro del catálogo de la BD.
    - (x) Verdadero.
    - ( ) Falso.

33. Si una relación es obligatoria para una entidad, no se puede insertar un elemento de dicha entidad sin establecer la relación.
    - (x) Verdadero.
    - ( ) Falso.

34. Las filas de una relación están ordenadas por su orden de llegada.
    - ( ) Verdadero.
    - (x) Falso.

35. La forma de determinar la cardinalidad de una relación en un diagrama E/R es mediante el análisis semántico de la conexión entre entidades.
    - (x) Verdadero.
    - ( ) Falso.

36. Siempre que dos tablas compartan las claves primarias o candidatas deben fusionarse.
    - ( ) Verdadero.
    - (x) Falso.

37. Una entidad débil no tiene claves candidatas.
    - (x) Verdadero.
    - ( ) Falso.

38. La diferencia entre una clave candidata y una primaria es que la candidata puede tomar valores nulos.
    - ( ) Verdadero.
    - (x) Falso.

39. La diferencia entre una clave candidata y una clave primaria es que la candidata no tiene por qué ser minimal.
    - ( ) Verdadero.
    - (x) Falso.

40. La actualización de un valor de una llave primaria, que es referenciada por una clave externa CE implica que los valores de las llaves externas también deben cambiarse.
    - (x) Verdadero.
    - ( ) Falso.

41. La regla de integridad de entidad exige que no existan tuplas duplicadas en la relación.
    - ( ) Verdadero.
    - (x) Falso.

42. Una clave externa y la primaria a la que está asociada pueden tener diferentes nombres.
    - (x) Verdadero.
    - ( ) Falso.

43. En el modelo relacional, el acceso a los datos de una tupla se hace por valor.
    - (x) Verdadero.
    - ( ) Falso.

44. La cardinalidad de una relación no puede cambiar durante la vida de la BD.
    - ( ) Verdadero.
    - (x) Falso.

45. En los modelos de datos basados en grafos se identifica cada registro por su dirección.
    - (x) Verdadero.
    - ( ) Falso.

46. Una tabla puede tener varias claves candidatas y con distinto número de atributos.
    - (x) Verdadero.
    - ( ) Falso.

47. No se puede actualizar un valor de una clave primaria que es referenciada por llaves externas.
    - ( ) Verdadero.
    - (x) Falso.

48. El modelo de datos jerárquico permite modelar bien las relaciones muchos a muchos.
    - ( ) Verdadero.
    - (x) Falso.

49. El SGBD debe permitir incluir reglas de integridad en la definición de la BD y preservar el cumplimiento de las mismas.
    - (x) Verdadero.
    - ( ) Falso.

50. La condición de normalización permite que los valores de un atributo sean registros.
    - ( ) Verdadero.
    - (x) Falso.

51. La introducción de nuevas aplicaciones implica la modificación del nivel externo de la BD.
    - ( ) Verdadero.
    - (x) Falso.

52. Las reglas de integridad debe mantenerlas el administrador de la BD (DBA).
    - ( ) Verdadero.
    - (x) Falso.

53. El nivel interno de una BD no puede cambiarse una vez implantada la base de datos.
    - ( ) Verdadero.
    - (x) Falso.

54. En el nivel externo se plasma la perspectiva que tiene cada usuario de la BD.
    - (x) Verdadero.
    - ( ) Falso.

55. En una relación ni las tuplas ni los atributos están ordenados.
    - (x) Verdadero.
    - ( ) Falso.

56. La independencia física permite reorganizar las estructuras del nivel interno sin que se vean afectados los programas de aplicaciones.
    - (x) Verdadero.
    - ( ) Falso.

57. No se puede eliminar una tupla cuyo valor para la clave externa coincida con el valor de la clave primaria de una tupla de la relación a la que hace referencia.
    - ( ) Verdadero.
    - (x) Falso.

58. Gracias a la transformación conceptual/interna se puede mantener la independencia física.
    - (x) Verdadero.
    - ( ) Falso.

59. En el modelo relacional todas las tablas tienen clave primaria necesariamente.
    - (x) Verdadero.
    - ( ) Falso.

Explicacion:<!-- 60 repetida 60. El SGBD debe gestionar los accesos concurrentes de manera que la base de datos esté siempre libre de errores. - (x) Verdadero. - ( ) Falso.-->

61. En una jerarquía todas las entidades de un conjunto específico deben estar en el conjunto de entidades genéricas.
    - (x) Verdadero.
    - ( ) Falso.

62. En los modelos de BD basados en grafos se consulta mediante lenguajes declarativos.
    - ( ) Verdadero.
    - (x) Falso.

63. Las herramientas de administración permiten evaluar el uso de la base de datos y, si fuera necesario, afinar el nivel interno.
    - (x) Verdadero.
    - ( ) Falso.

64. El acceso a través de C++ se hace mediante acoplamiento débil.
    - (x) Verdadero.
    - ( ) Falso.

65. En una jerarquía los conjuntos de entidades específicas no se pueden solapar.
    - ( ) Verdadero.
    - (x) Falso.

66. Cuando se pasa un diagrama E/R a tablas, las claves candidatas deben seguir manteniendo sus restricciones.
    - (x) Verdadero.
    - ( ) Falso.

67. La independencia lógica no se puede conseguir al 100%.
    - (x) Verdadero.
    - ( ) Falso.

68. En el modelo relacional cada atributo debe tener definido un dominio.
    - (x) Verdadero.
    - ( ) Falso.

69. Cuando hay claves externas asociadas a una primaria, el borrado de ésta última siempre obliga a borrar todas las filas donde aparezca su valor en la tabla que referencia.
    - ( ) Verdadero.
    - (x) Falso.

70. Una relación de cardinalidad muchos-muchos siempre genera una tabla con clave primaria.
    - (x) Verdadero.
    - ( ) Falso.

Explicacion:<!-- 71 repetida 71. El catálogo de una base de datos almacena los metadatos de la misma y debe ser accesible a los usuarios.   - (x) Verdadero. - ( ) Falso.-->

72. Un SGBD Relacional siempre debe rechazar la introducción de valor nulo en los atributos de clave externa.
    - ( ) Verdadero.
    - (x) Falso.

73. La actualización de una tupla donde hay definida una clave externa nunca puede vulnerar la integridad referencial.
    - (x) Verdadero.
    - ( ) Falso.

74. Un atributo puede ser clave externa a la clave primaria de su misma tabla.
    - (x) Verdadero.
    - ( ) Falso.

75. La dependencia existencial solo se da entre entidades débiles y fuertes.
    - (x) Verdadero.
    - ( ) Falso.

Explicacion:<!--76 repetida 76. La estructura de almacenamiento del nivel interno debe ser diseñada por el administrador. - (x) Verdadero. - ( ) Falso.-->

77. La definición de clave candidata exige que ésta cumpla unicidad y que ningún subconjunto suyo lo haga.
    - (x) Verdadero.
    - ( ) Falso.

78. El grado de una relación forma parte del esquema de base de datos y es invariable frente a las actualizaciones de los datos.
    - (x) Verdadero.
    - ( ) Falso.

79. En el modelo jerárquico se identifica cada registro por el valor de alguno de sus campos.
    - ( ) Verdadero.
    - (x) Falso.

80. En el modelo relacional el acceso a los datos de una tupla se hace por valor.
    - (x) Verdadero.
    - ( ) Falso.

81. Los SGBD deben proporcionar herramientas específicas de administración.
    - (x) Verdadero.
    - ( ) Falso.

82. El principal problema que produce la información redundante es el consumo desmesurado de espacio en disco.
    - ( ) Verdadero.
    - (x) Falso.

83. La integridad de entidad se mantiene por parte del SGBD y la referencial debe hacerse por programa.
    - ( ) Verdadero.
    - (x) Falso.

84. Las tuplas de una relación deben estar ordenadas antes de almacenar en fichero y este orden debe mantenerse durante toda la vida de la base de datos.
    - ( ) Verdadero.
    - (x) Falso.

Explicacion:<!-- 85 repetida 85. La elaboración del esquema conceptual es tarea del programador de aplicaciones. - ( ) Verdadero. - (x) Falso.-->

86. Una relación de cardinalidad muchos-muchos puede generar una llave primaria compuesta.
    - (x) Verdadero.
    - ( ) Falso.

87. La modificación del nivel interno no tiene que implicar la modificación de los otros niveles de la base de datos.
    - (x) Verdadero.
    - ( ) Falso.

88. Todas las tuplas procedentes de entidades débiles tienen claves externas.
    - (x) Verdadero.
    - ( ) Falso.

89. El lenguaje C es un lenguaje fuertemente acoplado.
    - ( ) Verdadero.
    - (x) Falso.

90. El acceso a las bases de datos solo se puede hacer a través de los lenguajes propios del SGBD.
    - ( ) Verdadero.
    - (x) Falso.

91. Una clave externa no puede ser nula.
    - ( ) Verdadero.
    - (x) Falso.

92. Los modelos basados en grafos utilizan registros y ficheros como parte del modelo de datos.
    - ( ) Verdadero.
    - (x) Falso.

93. Una relación uno a muchos es siempre obligatoria para entidades de muchos.
    - ( ) Verdadero.
    - (x) Falso.

94. La independencia física permite modificar el método de acceso a los datos sin que se vea afectado el nivel conceptual.
    - (x) Verdadero.
    - ( ) Falso.

95. Lo mejor para que las aplicaciones sean independientes es que cada una posea sus propios datos.
    - ( ) Verdadero.
    - (x) Falso.

96. El SGBD debe proporcionar herramientas de definición, consulta y actualización.
    - (x) Verdadero.
    - ( ) Falso.

97. El grado de una relación forma parte del esquema de la base de datos y es invariable frente a las actualizaciones de los datos.
    - (x) Verdadero.
    - ( ) Falso.

98. Cuando se diseña una BD es fundamental conocer las características técnicas del servidor sobre el que se va a implantar.
    - ( ) Verdadero.
    - (x) Falso.

99. El término integridad hace referencia a la veracidad de los datos que se almacenan, esto es, a su correspondencia con la realidad.
    - (x) Verdadero.
    - ( ) Falso.

100. Cuando se pasa un diagrama E/R a tablas, las claves candidatas no se tienen en cuenta.
    - ( ) Verdadero.
    - (x) Falso.

101. Una entidad que no tiene clave primaria es siempre una entidad débil.
    - ( ) Verdadero.
    - (x) Falso.

102. La forma de implantar la cardinalidad de una relación en un diagrama E/R en una tabla es mediante la correcta elección de las claves candidatas y primarias.
    - (x) Verdadero.
    - ( ) Falso.

103. Una relación de cardinalidad muchos-uno puede generar una tabla con clave primaria compuesta.
    - (x) Verdadero.
    - ( ) Falso.

104. `CREATE TABLE` es un comando DDL.
    - (x) Verdadero.
    - ( ) Falso.

Explicacion: <!-- Repetida en 88. 105. Todas las tablas procedentes de entidades débiles tienen claves externas.    - (x) Verdadero.    - ( ) Falso.-->

106. La clave primaria puede tomar el valor nulo parcialmente.
    - ( ) Verdadero.
    - (x) Falso.

Explicacion: <!--107 repetida 107. La dependencia existencial solo se da entre entidades débiles y fuertes. - (x) Verdadero. - ( ) Falso.-->

108. Todas las restricciones de integridad se pueden mantener eligiendo convenientemente claves candidatas, primarias y externas.
    - ( ) Verdadero.
    - (x) Falso.

109. El modelo jerárquico es más eficaz para plasmar las relaciones uno a muchos que el modelo relacional.
    - (x) Verdadero.
    - ( ) Falso.

110. Un atributo no puede ser clave primaria y externa a la vez.
    - ( ) Verdadero.
    - (x) Falso.

111. El SGBD debe permitir consultar directamente a las bases de datos. No es necesario que permita crearlas.
    - ( ) Verdadero.
    - (x) Falso.

112. Los modelos de datos implementables permiten codificar los esquemas conceptuales.
    - (x) Verdadero.
    - ( ) Falso.

113. En los modelos de datos basados en grafos la manipulación debe hacerse mediante lenguajes procedimentales.
    - (x) Verdadero.
    - ( ) Falso.

114. Las reglas de integridad de una base de datos deben siempre incluirse en los programas que manejan dicha clase.
    - ( ) Verdadero.
    - (x) Falso.

115. En el modelo relacional se identifica cada fila por el número que tiene.
    - ( ) Verdadero.
    - (x) Falso.

116. Los modelos de datos semánticos son más cercanos al diseñador.
    - (x) Verdadero.
    - ( ) Falso.

117. Los modelos de datos semánticos no tiene por qué incluir formalismos de manipulación.
    - (x) Verdadero.
    - ( ) Falso.

118. La información correspondiente a los esquemas y correspondencias se guarda fuera de la base de datos para no alterar dichos datos.
    - ( ) Verdadero.
    - (x) Falso.

119. Para trabajar con una base de datos nos basta con utilizar ficheros y registros.
    - ( ) Verdadero.
    - (x) Falso.

120. El administrador de la base de datos no puede acceder a los datos que introducen los usuarios.
    - ( ) Verdadero.
    - (x) Falso.

121. La arquitectura cliente servidor ejecuta los programas de aplicación de cada cliente.
    - (x) Verdadero.
    - ( ) Falso.

122. El concepto de seguridad se refiere a la protección de una base de datos contra fallos catastróficos.
    - ( ) Verdadero.
    - (x) Falso.

123. Los modelos de datos implementables están basados en el concepto de registro.
    - (x) Verdadero.
    - ( ) Falso.

124. Toda relación se corresponde con una única tabla.
    - (x) Verdadero.
    - ( ) Falso.

125. En el modelo relacional cada atributo tiene un dominio distinto.
    - ( ) Verdadero.
    - (x) Falso.

126. El conjunto de tuplas se llama:
    - (x) Instancia.
    - ( ) Relación.
    - ( ) Esquema.
    - ( ) Grado.

127. La clave primaria de una tabla de una entidad débil es la misma que la clave primaria del conjunto de entidades del que depende.
    - ( ) Verdadero.
    - (x) Falso.

128. Una ejemplo de clave externa son los atributos de una entidad débil que provienen de la entidad fuerte.
    - (x) Verdadero.
    - ( ) Falso.

129. Solo puede haber dos atributos llamados de la misma forma cuando provienen de una entidad que interviene varias veces en la tabla.
    - ( ) Verdadero.
    - (x) Falso.

130. Las claves candidatas solo aparecen en las relaciones uno a uno.
    - ( ) Verdadero.
    - (x) Falso.

131. El atributo discriminador solo se pone como clave primaria en las relaciones muchos a muchos.
    - ( ) Verdadero.
    - (x) Falso.

132. El paso a tablas es una representación que permite mantener todas las restricciones que los diagramas de ER, como disjunto, obligatoriedad, etc.
    - ( ) Verdadero.
    - (x) Falso.

133. Puede haber una clave externa que no sea clave primaria o candidata.
    - (x) Verdadero.
    - ( ) Falso.

134. En las tablas, las entidades que heredan de otra deben contener todos los atributos de la entidad de la que heredan.
    - ( ) Verdadero.
    - (x) Falso.

135. Una clave primaria puede ser clave externa en dos sitios a la vez.
    - (x) Verdadero.
    - ( ) Falso.

136. Las relaciones se dan entre solo dos atributos.
    - ( ) Verdadero.
    - (x) Falso.

137. Las fusiones son optativas y se usan para reducir el espacio de las tablas.
    - (x) Verdadero.
    - ( ) Falso.

138. No se puede hacer fusión de tablas de jerarquías o se desharían las jerarquías.
    - (x) Verdadero.
    - ( ) Falso.

139. Las tablas con relaciones muchos a muchos no se pueden fusionar porque no coinciden las claves primarias.
    - (x) Verdadero.
    - ( ) Falso.

140. En las relaciones con atributos discriminadores, se puede fusionar siempre que las cardinalidades sean muchos a muchos.
    - ( ) Verdadero.
    - (x) Falso.

141. En las relaciones con obligatoriedad, el fusionado es obligatorio.
    - ( ) Verdadero.
    - (x) Falso.

142. Cuando las relaciones tienen atributos, no se puede hacer fusión.
    - ( ) Verdadero.
    - (x) Falso.

143. En relación con las restricciones de integridad...
    - ( ) Toda superclave es una clave.
    - ( ) Ninguna superclave es una clave.
    - (x) Toda clave es superclave.

Explicacion:<!-- 144 repetida 144. Al actualizar una clave externa:    - (x) Se debe aceptar el cambio si el valor nuevo pertenece al dominio activo de la clave referenciada    - ( ) Se debe aceptar el cambio si el valor nuevo no pertenece al dominio activo    - ( ) Se debe aceptar el cambio si el valor nuevo es nulo.-->

145. El SGBD...
    - ( ) Implementa todas las restricciones de integridad.
    - (x) Controla todas las restricciones de integridad definidas sobre la BD.
    - ( ) Controla parte de las restricciones de integridad definidas sobre la BD.

146. El esquema centralizado de SGBD:
    - ( ) La carga de gestión y procesamiento se comparte por igual entre el servidor y los terminales.
    - (x) Los terminales no tienen instalado el SGBD.
    - ( ) Toda carga de gestión y procesamiento recae sobre los terminales.

147. El conjunto de elementos software con capacidad para definir, mantener y utilizar una base de datos se conoce como...
    - (x) SGBD.
    - ( ) Base de datos.
    - ( ) Ninguna de las anteriores.

Explicacion:<!-- 148 repetida 148. El lenguaje anfitrión o de aplicación...    - ( ) Complementa al DSL solo para facilitar el desarrollo de la interfaz de usuario    - ( ) Complementa al DSL solo para el procesamiento avanzado de datos    - (x) Complementa al DSL para hacer procesamiento avanzado de datos o facilitar el desarrollo de la interfaz de usuario.-->

Explicacion:<!-- 149 repetida 149. El modelo de datos jerárquico tiene problemas con las…    - ( ) Relaciones uno a uno    - ( ) Relaciones muchos a uno    - (x) Relaciones muchos a muchos.-->

Explicacion:<!-- 150 repetida 150. El rango de valores que puede tomar un atributo se denomina:    - ( ) Dominio activo    - ( ) Tipo de dato    - (x) Dominio    - ( ) Integridad referencial.-->

151. En el modelo de datos relacional la identidad es...
    - (x) Por valor.
    - ( ) Por posición.
    - ( ) Por clave externa.

Explicacion:<!-- 152 repetida 152. La regla de integridad de entidad...    - ( ) Nunca permite nulos en la clave primaria.    - ( ) A veces permite nulos en la clave primaria, en función de la semántica del problema    - (x) Supone una abstracción del nivel lógico.-->

153. El administrador de la base de datos...
    - ( ) Es el que desarrolla los programas de aplicación.
    - ( ) Es el responsable de introducir los datos en el sistema.
    - (x) Es responsable de configurar el SGBD.

154. El modelo de datos en red es un modelo de datos basado en...
    - (x) Items.
    - ( ) Realizar consultas.
    - ( ) Insertar tuplas.

155. Cuando el acoplamiento es débil...
    - (x) El programador puede distinguir el DSL del lenguaje anfitrión.
    - ( ) No se puede utilizar una API de acceso a la BD.
    - ( ) El programador no distingue el DSL del lenguaje anfitrión.

156. El DSL está compuesto por...
    - ( ) DDL, DML, DHL.
    - ( ) DCL, DHL, DDL.
    - (x) DDL, DCL, DML.

157. El grado de una relación...
    - (x) No varía con las inserciones en la instancia.
    - ( ) Varía al hacer actualizaciones de la instancia.
    - ( ) Varía al hacer inserciones en la instancias.

158. El coste de mantenimiento de los PCs es un problema...
    - ( ) Del esquema centralizado de SBD.
    - ( ) Solo del esquema centralizado si está implementado de forma distribuida.
    - (x) De la aproximación cliente/servidor.

159. En una jerarquía todas las entidades del conjunto de entidades genérico deben estar en un conjunto de entidades específico.
    - ( ) Verdadero.
    - (x) Falso.

160. El principal objetivo de evitar la redundancia en una BD es ahorrar espacio en disco.
    - ( ) Verdadero.
    - (x) Falso.