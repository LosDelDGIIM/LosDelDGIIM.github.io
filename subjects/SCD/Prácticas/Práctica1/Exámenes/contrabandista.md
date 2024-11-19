# SCD. Simulacro I de la Práctica I

**Autor:** Arturo Olivares Martos.<br>
**Autor:** José Juan Urrutia Milán.
***

- **Asignatura:** Sistemas Concurrentes y Distribuidos.
- **Curso Académico:** 2024-25.
- **Grado:** Doble Grado en Ingeniería Informática y Matemáticas + ADE.
- **Grupo:** 2.
- **Profesor:** José Miguel Mantas Ruiz.
- **Descripción:** Simulacro I de la práctica 1 de SCD.
- **Fecha:** 23 de octubre de 2024.
- **Duración:** 50 minutos.

***
Para ver la plantilla o la solución, dirígase al final del documento.

***
Se proporciona un archivo denominado `contrabandista_plantilla.cpp` que incluye una implementación del problema de los fumadores de la práctica 1, pero con solo dos fumadores y dos ingredientes diferentes (en lugar de tres fumadores y tres ingredientes). Modifique dicho código tal y como se muestra a continuación, guardando el resultado en un archivo `contrabandista.cpp`.
- La **relación entre el estanquero y los 2 fumadores es idéntica** al problema original.
- Los fumadores, tras liar el cigarro, en lugar de fumar, dedican ese tiempo a enviar el cigarro liado a un **contrabandista** que se implementará como una **nueva hebra** del sistema concurrente.
- El contrabandista obtiene cigarros de España (gracias a los 2 supuestos fumadores) para venderlos en un país donde el tabaco está prohibido. La comunicación entre los dos fumadores y el contrabandista se realiza mediante un **buzón de correos secreto** con capacidad para un máximo de 3 cigarros donde los dos fumadores pueden meter el cigarro, ya liado, dentro de un sobre que indica su número de fumador. De este buzón, el contrabandista **puede coger solo un sobre cada vez** que viene a España. El contrabandista coge **siempre el sobre que lleva más timpo depositado en el buzón.**
- El **contrabandista realiza iterativamente** la siguiente actividad en un bucle infinito:  
    1. Duerme durante un tiempo aleatorio entre 20 y 150 milisegundos.  
    2. Después intenta sacar un cigarro del buzón. Si el **buzón está vacío** deberá esperar a que haya algún nuevo cigarro en el buzón.  

    Tras realizar **4 nuevas itaraciones** de esta actividad (dormir y extraer sobre del buzón), el contrabandista **imprime por pantalla un mensaje indicando el número de cigarros que apoarta cada fumador**.
- Cuando un fumador intenta insertar en el **buzón** y éste está **lleno** (tiene ya 3 cigarros) debe esperar a que haya menos de 3 cigarros en el buzón.
- El **buzón secreto** se puede implementar como un **array de 3 celdas** de tipo entero, donde se guardan los números del fumador que ha proporcionado cada cigarro.
- Se debe garantizar el **acceso correcto al buzón** por parte de los fumadores, evitando que se pierdan sobre o que se recoja varias veces el mismo sobre.
  
***

La plantilla se encuentra en el siguiente [enlace](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/SCD/Prácticas/Práctica1/Exámenes/contrabandista_plantilla.cpp).
  
Puede encontrar la solución al problema en el siguiente [enlace](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/SCD/Prácticas/Práctica1/Exámenes/contrabandista.cpp).


Respecto a la solución mediante monitores (que se verán en la práctica siguiente), puede encontrar la solución en el siguiente [enlace](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/SCD/Prácticas/Práctica1/Exámenes/contrabandistaMonitores.cpp).
