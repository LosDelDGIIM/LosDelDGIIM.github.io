# Simulacro de la Práctica 1

Lea atentamente las siguientes **NORMAS DEL CONTROL**:
- Si hay una copia entre trabajos entregados se anularán ambos trabajos implicados.
- Se subirá un solo arhivo como resultado del ejercicio y nunca un archivo comprimido.
- Dispone de 50 minutos para realizar el ejercicio.

1. Se proporciona un archivo denominado **fumadores2.cpp** que incluye una implementación del problema de los fumadores de la práctica 1, pero con solo dos fumadores y dos ingredientes diferentes (en lugar de tres fumadores y tres ingredientes). Modifique dicho código tal y como se muestra a continuación, guardando el resultado en un archivo **"estancos2.cpp"**:  
  
    **a)** La **relación entre el estanquero y los 2 fumadores es idéntica** al problema original.  
  
    **b)** Los fumadores, tras liar el cigarro, en lugar de fumar, dedican ese tiempo a enviar el cigarro liado a un **contrabandista** que se implementará como una **nueva hebra** del sistema concurrente.  
  
    **c)** El contrabandista obtiene cigarros de España (gracias a los 2 supuestos fumadores) para venderlos en un país donde el tabaco está prohibido. La comunicación entre los dos fumadores y el contrabandista se realiza mediante un **buzón de correos secreto** con capacidad para un máximo de 3 cigarros donde los dos fumadores pueden meter el cigarro, ya liado, dentro de un sobre que indica su número de fumador. De este buzón, el contrabandista **puede coger solo un sobre cada vez** que viene a España. El contrabandista coge **siempre el sobre que lleva más timpo depositado en el buzón.**  
  
    **d)** El **contrabandista realiza iterativamente** la siguiente actividad en un bucle infinito:  
        1. Duerme durante un tiempo aleatorio entre 20 y 150 milisegundos.  
        2. Después intenta sacar un cigarro del buzón. Si el **buzón está vacío** deberá esperar a que haya algún nuevo cigarro en el buzón.  
           Tras realizar **4 nuevas itaraciones** de esta actividad (extraer sobre del buzón), el contrabandista **imprime por pantalla un mensaje indicando el número de cigarros que apoarta cada fumador**.  
  
    **e)** Cuando un fumador intenta insertar en el **buzón** y éste está **lleno** (tiene ya 3 cigarros) debe esperar a que haya menos de 3 cigarros en el buzón.  
  
    **f)** El **buzón secreto** se puede implementar como un **array de 3 celdas** de tipo entero, donde se guardan los números del fumador que ha proporcionado cada cigarro.  
  
    **g)** Se debe garantizar el **acceso correcto al buzón** por parte de los fumadores, evitando que se pierdan sobre o que se recoja varias veces el mismo sobre.  
  
  
Entregue la solución en un fichero llamado **estanco2.cpp**.  
  
  
  
  
  
Puede encontrar la solución al problema en el siguiente [enlace](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/SCD/Exámenes/estancos2.cpp).
