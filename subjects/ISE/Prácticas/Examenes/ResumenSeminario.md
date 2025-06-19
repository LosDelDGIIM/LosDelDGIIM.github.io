# Seminario
## DevOps
No es normativa: no hay una autoridad que defina lo que es. Hay muchos autores de opinión que recomienda unas prácticas u otras.
Se basa en métricas cuantitativas: aplican cambios y cuentan el nº de errores o tiempos de producción para garantizar software de mayor calidad y en menor tiempo.
Soluiona el SDLT (tiempo desde que se concibe idea hasta llevarla a producción, año 2008).

SDP: **Service Delivery Pipeline** (liberación de servicios): Encargados de negocio diseñan un cambio a llevar a producción y se pasa a responsables de ejecutar decisiones.
Negocio => Product Owner / Manager => Analista
Operaciones: mantenimiento


En el proceso hay una parte que es desde que se implementa un cambio hasta que llega a desplegarse. Es una parte de ingeniería, el **Deployment (despliegue) Lead Time (tiempo, lo que tardamos)**. Cuánto tiempo tardamos en hacer despliegues. Viene a medir lo que transcurre desde que un cambio está listo por el equipo de desarrollo (implementado y probado) hasta que llega a que se pueda utilizar por los usuarios finales.

Más del 50% tardan una cantidad de tiempo aparentemente que no es normal. Es el principal problema en el que se centra DevOps: Por qué tardamos tanto si ya está hecho? Causas:
1. **Transferencia de responsabilidad**. existen equipos compartimentados con responsabilidades claras: traspaso de responsabilidad (over the wall) y se desentendían
    - Tanto el equipo de desarrollo como el de operaciones tienen equipos distintos: el primero (de desarrollo) recibe recursos porque hace cambios rápido y pronto, y el segundo (el de operaciones) cobra porque los sistemas de producción no se caigan (y los cambios conducen a ello).
    - De esta forma, se produce un equipo ping pong: Los equipos de desarrollo se dan mucha prisa por desarrollar y los de operaciones no quieren meter cambios, porque cualqueir fallo puede romper todo el sistema.

Cómo solucionarlo: Equipos multidisciplinares: que no sean de desarrollo ni de operaciones, sino equipos DevOps (Development & Operations).
SDLM (Software Developmen Life Menagment): Modelo de trabajo donde se desarrolla y se opera: tú lo desarrollas, tú lo mantienes.
    No se producen transferencias de responsabilidad.
    Aumenta la visibilidad: el de operaciones recomienda a los de desarrollo.
    
La metodología ágil se basa en el modelo hacia la izqda: cuanto antes se adelante el modelo de calidad, más barato es.
Problemas durante la fase de desarrollo más barato durante test, más barato que durante producción.

2. **Falta de automatización**: muchas tareas que se hacían de forma manual: integrar componentes con librerías y etc, documentación, hacer tests, ...
Pasos manuales muy farragosos que requieren manuales grandes de cientos de páginas y listas de check lists. Mucho tiempo.
Una de las principales habilidades a los desarrolladores de sistemas es programar.

- Lleva a la reducción de tiempos (no es el principal factor para reducirlo).
- Asegurar la calidad: reduce los errores, las tareas automáticas siempre se reproducen de la misma forma.
La automatización reduce el nº de cambios por esto, por reducir los errores.

3. A esto se junta que sobre el 2008 se hace desarrollo continuo y métodos ágiles, similar a lo que promulgaba el DevOps.

### Funciona?
- La competitividad está guiada por el tiempo que se tarda en llevar los cambios a producción. DevOps fomenta la competitividad de las compañías.
- Volatilidad del talento: Es difícil contratar gente con talento y más aún mantenerla en el equipo.
    Burn out: estar quemado.
    eNPS (Name Promotion Scont): recomendarías a un amigo que viera a trabajar a esta empresa? Hacer encuestas entre el personal.
        El indicador está muy relacionado con la sensación de pertenencia a una empresa. Traductor muy fiable del bienestar.

    Uno de los motivos más frecuentes es que no se siente identificado por lo que está haciendo o desarrollando.
    Estar en un equipo multidisciplinar y trabajar desde que se concive la idea hasta llevarla a producción es más motivador. 


Las empresas que implementan DevOps en el equipo IT tienen +50% de alcanzar sus objetivos, según un estudio.

### Las 4 métricas
Muy sencillas y **muy fáciles de medir**, muy buenos.
    Dentro de una empresa los cambios están identificados con un nº: muy fácil saber cuando un commit está listo hasta que llega a producción.
    
- Rápido: Como equipo de desarrollo
- **Deployment Lead Time**: Tiempo desde que todo está listo hasta que llega a producción
- **Deployment Frequency**: Instalaciones en producción (?) / unidad de tiempo.

- Cómo de buenos somos
- **Mean Time to Restore**: Tiempo medio en arreglar un problema que se produce en producción.
- **Change Fail Ratio**: Cambios/errores. Los principales errores son los cambios pero hay que ver cuál es el radio entre cambios y errores.

Lo importante es que con el tiempo las métricas vayan mejorando.
Los libros dicen que en la gran mayoría de sitios que los aplican los tiempos bajan.

### Plataformas de monitorización

## Automatización
### Continuous Integration (Integración continua)
Trata de hacer que cada cambio que desarrollemos esté lo más rápidamente posible probado y disponible para el resto de la organización.

- **Tiempo de integración**: Anterior al DLT. Desde que un cambio está desarrollado pero no probado hasta que está probado (testado) y disponible, para otro compañero de trabajo (decimos que es **correcto**). Cuando el cambio llega al repo principal decimos que está **integrado**.

Idealmente, una integración al día (es muy difícil). 
    El coste en hacer un cambio crece de forma exponencial, es mejor integrar cada día a cada semana.
    El sistema crece en complejidad de forma lineal, pero cuando dos sistemas diverjen, los posibles errores que se producen crecen exponencialmente, ya que son todas las combinaciones.
    Pesadilla del merge: coste que supone mezclar código

Hay que tener ingeniros que sean muy buenos con la tecnología y mentalmente (hay que garantizar hecho y probado).

#### Herramientas para integración continua
- Control de versiones: es el core.
- Test automáticos.
    - Tests unitarios.
    - Tests a nivel de servicio: cuando se integran distintas funciones para ver cómo funcionan todas juntas.
    - Tests a nivel de UI: proporciona una herramienta donde el usuario puede ...

    Cuanto más arriba, los tests son más lentos y más caros: Tienen que haber muchos tests abajo y menos arriba.

### Beneficios del Testing
Proporciona confianza al desarrollador, acelera los cambios y da pie a la experimentación.
Reduce el coste y control de calidad.
Hace explicito el funcionamiento de los componentes.


Las prácticas de agile dicen que no se documente el código.
    La documentación puede dar pie a fallos: es difícil mantener la documentación actualizada.
Hay principios de clean code:
    - Funciones cortas: max 10 lineas
    - Nombres explicativos.
Los tests son la buena documentación


Los tests protegen frente a las modificaciones:
    Codigo muy antiguo de gente que ya no está
Los tests reflejan el conocimiento de cómo se usará el código.
    Principio de la valla: si hay un código, asume que el que lo hizo era inteligente.

##### Motores de IC (Integración continua)
Herramientas que ejecutan scripts pequeñitos y los encadenan para hacer cosas más complejas: Jenkins.
Monitoriza git y cuando detecta un cambio de merge en una rama: 
- Se descarga el código
- Compila
- Corre tests.
- Despliega entorno, corre más tests
- Lo publica en el repo de la compañía.



Motivos por los que un cambio correcto no debe llegar a producción:
- Que el jefe dice que falta funcionalidad, producirá una mala satisfacción.

## Site Reliability Engineer (Google)
Aterrizó DevOps con prácticas más normativas para uso interno y que salieron al resto.

Cuando contratan a administradores de sistemas la principal capacidad es la de desarrollo: automatización
Elimina Toils: Pasos manuales basura.

Los equipos de trabajo se reunen para decidir lo que van a hacer: planificación.
Los products owners están obligados a que los ingenieros dediquen ciertas horas a eliminar basura, automatizar.

Presupuesto de errores (Errors Budgets): cada equipo se le admite que los sistemas se caigan durante un periodo de tiempo y no hay problema.
Se tiran los sistemas y se prueba si son capaces de recuperarlo en un tiempo dado: como los bomberos.
    Hay tests de monos, monkey.
    Otros de mono loco: tiran abajo sistemas de producción.

## 4 métricas SRE (Site Reliability Engineers)
Si tienes que medir algo, mide esto:
- Latencia: Tiempo que tarda en ejecutarse algo.
- Tráfico: Nº de peticiones o accesos / seg.
- Errores: Errores / unidad de tiempo.
- Saturación (+ dificil de calcular): % de uso de un recurso respecto a su máximo (hay que saber decir si estamos al 50, 70, ...).
