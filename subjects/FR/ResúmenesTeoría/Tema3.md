# Tema 3. Capa de transporte.

# Introducción
El nivel de enlace se encarga de ir punto a punto
El nivel de red se encarga de encaminar punto a punto
El nivel de transporte sólo se encarga de la transferencia entre los extremos.

Por tanto, sólo hablaremos de los extremos
Siempre dentro de un paquete de transporte va un paquete de aplicación.

Cualquier nivel de transporte sea el que sea tendrá multiplexación y demultiplexación.
Esto significa que multiplexamos (juntar informacion de muchos procesos en la misma tarjeta) mucha información en un mismo cable y los demultiplexamos en el final (los sacamos de la tarjeta de red y lo distribuimos entre los procesos que necesitan la infomación).


Únicamente los equipos extremos cuentan con la capacidad de tener procesamiento a nivel de transporte.

## Resumen
Veremos principalmente UDP y TCP, los más usados.

UDP: User Datagram Protocol.
    - El hecho de que indique que es de datagrama significa que no tiene ninguna fiabilidad.
    - UDP no hace nada más porque su intención no es ser fiable, sino ir rápido (ejemplo, iperf -u, que se encarga de medir la velocidad)
    - Una de sus cuestiones es que no sabemos ni siquiera si el receptor está encendido.
TCP: Transfer Control Protocol.
    - Sí se asegura de que el otro esté encendido y listo para recibir datos.
    - También hace control de errores. Siempre supondrá que son debidos por congestión.
        TCP nunca considera en cableadas la posibilidad de que un bit cambia. En inalámbricas sí (10% de errores).
    - Control de flujo: el receptor es lento procesando los datos, se llenan los buffers y le dice al emisor que vaya más lento.
        Hace que TCP adopte su velocidad.

- Velocidad de transmisión de una aplicación en UDP: 7Mbps. Va sobre una media. La velocidad depende de la aplicación.
- En TCP: empieza con una velocidad baja, sube exponencialmente y a partir de un cierto punto estará la capacidad del canal. 
    Cuando se produzca un fallo, vuelve a la velocidad baja y etc.

Veremos que TCP tiene varias extensiones, una relacionada con el control de flujo (ventana de control de flujo, que puede limitar la velocidad a la que se transmite).

Recordamos que los paqeutes en :
- la capa de enlace son trazas o frames.
- En red, datagramas.
- En UDP, son datagramas y en TCP segmentos
- En aplicaciones, mensajes.

SCTP trata de ser una mezcla de UDP y TCP (no entra en la asignatura).

# UDP (Protocolo de Datagrama de Usuario, User Datagram Protocol)
Es best-effort (intenta hacerlo bien pero si no funciona mala suerte).
No es orientado a conexión (es decir, no establece conexión).
Cada paquete es totalmente independiente (también dentro de un Socket).
Cada PDU es independiente.

TPDU: Transport Packet Data Unit.

Servicio no fiable, puede haber pérdidas que no se transmitan. Esto significa que el nivel de transporte no arregla errores.
Puede haber aplicaciones fiables sobre UDP, que se encarguen de arreglar los errores que UDP no hace.

Los datos pueden llegar desordenados (hemos visto que rutas pueden cambiar a lo largo del camino, también hay routers con distintas colas de prioridad, aunque no se verá en la asignatura). UDP no hace nada para arreglarlo.

Lo único que hace UDP es multiplexar y demultiplexar (mucha info --> cable --> muchos procesos).

## Cabecera UDP:
8 bytes:
- Puerto origen, 16 bits (hasta 65535).
- Puerto destino, 16 bits.
- Longitud UDP (datos + cabecera).
- Comprobación, checksum.

El checksum no comprueba los datos (no es un protocolo fiable).
El checksum no solo comprueba la cabecera, sino la pseudo cabecera de UDP.

La pseudo cabecera de UDP es una parte de la cabecera IP que son importantes:
- IP Origen.
- IP Destino.
- Protocolo (número que indica protocolo).
- Longitud UDP.

## Puertos
Número que le dice al SO "cuando llegue un paquete por este puerto, está asociado a este proceso".

Los puertos que están por debajo de 1024, el SO los ofrece para usuarios root.
Los que están por encima de 1024 se dan normalmente a los clientes, con lo que permisos de root no son necesarios. A disposición del desarrollador.

Cuando se manda un paquete desde un origen hasta un destino, el puerto origen es el puerto donde está escuchando el origen, mientras que el puerto de destino es el puerto por el que el destinatario escucha el paquete.

Ver puertos más usados. `cat /etc/services` para ver los puertos activos.

53: domain es para el DNS (DNS va normalmente sobre UDP, aunque permite TCP).
69: tftp (trivial file transport protocol).

Los puertos de udp y tcp son independientes, podemos tener 80 tcp y 80 udp.

# TCP
- Tiene sabores o versiones de TPC: había una versión que hacía que el control de congestión funcionaba de una forma y ahora se puede hacer de otra forma.
- Es punto a punto (UDP no), ya que va desde un origen concreto hasta un destino concreto, al establecer conexión.
- Cuando se manda un paquete en multicast necesariamente tiene que ser en UDP, ya que TCP es punto a punto (no puedo hablar con muchos).
- Es orientado a conexión, utiliza un protocolo (hand-shacking, se traduce como protocolo pero se refiere a un intercambio muy específico de mensajes).
- Los datos tienen que entregarse ordenados (UDP no tenía nada relativo a esto).
- Es transmisión full-duplex (podemos transmitir y recibir a la vez).
- Tiene mecanismo de corrección de errores, retransmitiendo automáticamente, ARQ. Lo consigue usando confirmaciones, que son positivas (dice solo las cosas que han llegado bien) y acumulativas (si decimos que este paquete ha llegado bien hasta este byte, entonces todo lo anterior ha llegado bien).
- Es un servicio fiable: control de flujo, congestión.
- Usa piggybacking: Si manda un paquete en un sentido y se manda una confirmación (ACK), puede aprovechar y mandar más cosas.

## Cabecera TCP:
20 bytes + opciones (normalmente no).

5 filas + opciones (cabecera) + datos.
- Puerto origen.
- Puerto destino.
- Número de secuencia: 32 bits para indicar la posición del primer byte del paquete (debería empezar en 0, aunque en verdad lo hace aleatorio) (x).
- Número de acuse de recibo: (nº de bytes que esperamos recibir). Recibimos un paquete, enviamos ACK diciendo que hemos recibido bien hasta este byte (es decir, le decimos que el siguiente a recibir es este).
- Hlen: Longitud de la cabecera. Como máximo 5 => 20 bytes.
- Reservado: Por si dentro de varios años hacen falta más bits.
- UAPRSF: Flags. 
- Ventana del receptor: Un campo para el control de flujo (xx). 16 bits => la ventana más grande es de 65535 bytes. 
- Comprobación: checksum. Como TCP es fiable, no es sólo de la cabecera sino de la parte de datos y pseudocabecera IP.
- Puntero de datos urgentes: Puede haber datos normales y datos urgentes. Indica a partir de qué byte los datos son urgentes.
- Opciones.

(x) Si tenemos un buffer en el receptor y llegan datos que vamos colocando, el nº de secuencia indica el 1er byte del paquete que acabamos de recibir.
(xx) El receptor del dice al emisor cuántos datos tiene libres en su buffer. Avisamos al emisor de que vaya más lento.

#### Flags:
- U: Urgente. El buffer es circular, ventana deslizante, cuando llegan algunos se van pasando a la aplicación. Si U está activo, hay un paquete que se salta ese orden, dato urgente.
- A: ACK, si está activo, es una confirmación, que el campo de acuse tiene sentido.
- P: Push, En TCP el paquete no se manda hasta llegar a un determinado tamaño (En Ethernet, 1480). Si queremos que esto no pase (WhatsApp), Push a 1.
- R: Reset, Estamos estableciendo conexion o ya la tenemos establecida. Si está a 1, obliga a hacer un reset.
- S: Sincronismo, relacionado con el establecimiento de conexión. Se envían mensajes que permiten sincronizar el número de mensajes entre emisor y receptor. Si está puesto a 1, estableceimiento de conexión.
- F: Fin, cierre de conexión.

## Funcionalidades
### Multiplexación y demultiplexación con puertos
Lo de los puertos van igual que para UDP.
Ver puertos para TCP.

21: FTP para mandar comandos.
20: FTP para mandar datos.
22: ssh. Como telnet pero permite usar claves y certificados.
23: telnet. Todo va en texto plano.
25: SMTP, correo electrónico.
110: POP3, descargas de correo.
80: HTTP. No seguro, en texto plano
443: HTTPS: HTTP cifrado.

Ahora el correo va sobre SSL.

Al igual que antes, para solicitar un puerto menor o igual a 1024, root.

### Control de conexión
Relativamente sencillo.
Tenemos un número de secuencia, un número de acuse y un flag de sincronismo.

1. TCP A manda para activar conexión, activamos el flag de sincronismo y en el campo de secuencia se pone un byte aleatorio X.
2. Cuando la entidad B lo recibe, activa el flag de ACK (para confirmar el sincronismo), poniendo el campo de acuse a X+1.
    Como hacemos piggybacking, enviamos un sincronismo en sentido contrario, por lo que activamos sincronismo con numero de secuencia Y (aleatorio).
3. Cuando lo recibe A, confirma el mensaje de sincronismo (flag ACK a 1) e incrementa el numero de acuse a Y+1.

Hemos sincronizado los núemros de secuencia: A conoce los numeros de B y B los de A.
Esto se suele simplificar y representar con:
1. Syn X
2. ACK X+1, Syn Y       (Por ser piggybacking)
3. ACK Y+1

La conexión es iniciada siempre por el cliente.
A esto se le llama apertura activa.
El servidor hace todo esto, mediante apertura pasiva (abre conexion en consecuencia de que tiene un cliente).

Pregunta: Es posible garantizar un establecimiento de conexión fiable sabiendo que los mensajes van sobre IP?
No: IP no es fiable, con lo que no vamos a asegurar de que esto va a ocurrir bien. Tendremos relojes que hacen que si tarda mucho, algo ha pasado mal.

#### Número de secuencia
Campo importante para indicar el orden.
Si alguien quiere secuestrar una conexión TCP (meter paquetes en medio), es necesario conocer el número de secuencia.
Para evitarlo, se utiliza un nº de secuencia ISN (Initial Sequence Number). Cada 4 microsegundos, el SO incrementa el ISN. Un ISN tarda en repetirse ~ 5h.

Es muy fácil averiguar el nº de secuencia para un atacante.
Para ello:
SYN X
ACK X+1, SYN Y.
Como cada 4 microsegundos se actualiza, al ver una conexion de verdad se puede estimar mas o menos el nº de secuencia.

TCP incrementa el nº de secuencia según el tamaño del paquete.
Similar al offset.

Sencillo de calcular salvo cuando tenemos flags de sincronismo o ACK (se incrementan en 1). Estos mensajes no tienen datos, sólo cabecera.

##### Ejemplos
Ver diapositivas.

Hay una serie de estados del cliente y del servidor:
Cliente Closed => Syn-sent => Established
Servidor Listen => Syn-received => Established

- Conexión normal.
- Caso de conexión simultánea (ambos de cliente y servidor).
- SYN retrasados y duplicados:
    A manda mensaje que se retrasa 90.
    Como después de cierto tiempo (timeout) no recibe ACK, lo reintenta con otro sincronismo que se retrasa.
    El mensaje inicial ahora llega y contesta, ack 91.
    El cliente diche que no, reset 91 (descarta conexión).
    Llega el sincronismo de 100, que se resuelve normalmente.

### Cierre de conexión
1. Se envía un FIN (flag de fin a 1) y se envía el último número de secuencia X'.
2. Responde con ACK con X'+1, envía un FIN de Y'.
3. Responde con ACK con Y'.

Igual que la conexión.
Depende del protocolo de aplicación, cerrará uno o el otro. No sabemos quién es el cliente y el servidor.

Igualmente, el que arranca hace un cierre activo y el otro un cierre pasivo.
La conexión se cierra pero hasta dentro de 2 min no se cierra totalmente (por si ha quedado algun dato sin llegar).

### MSS (Maximum Segment Size)
El MTU era un concepto de nivel de enlace (concepto de capa 2), donde se especificaba la longitud máxima de la longitud de datos de un paquete de enlace. Dependía de la tarjeta.
Lo que metemos en los datos de ethernet es un paquete IP: cabecera + datos IP.

MSS es un concepto de capa 4 (transporte). Indica lo que puede oucpar la parte de datos de TCP.

Ethernet: MTU 1500 Bytes (cabecera IP de 20 + datos IP => 1480 max).
            Lo datos IP si enviamos un paquete TCP es la cabecera TCP (20 bytes) + parte de datos de TPC (MSS). Por tanto, el MSS será 1460 Bytes.
            
            
##### Problema dificil de encontrar que no cae en la asignatura
Si tenemos una VPN, tenemos:
Cabecera IP | Cabecera VPN | Paquete TCP (Cabecera TCP + Datos) |

Al SO le hemos dicho que MSS (datos TCP) son 1460, que las cabeceras IP y TCP son 40, el total es > 1500.
Si usamos una VPN manteniendo el MSS, metemos una cabecera nueva de VPN, que puede dar lugar a errores.

Dependiendo de la VPN, estará implementada en un nivel u otro, pero la cabecera la tendríamos igualmente.

### Diagrama de estados de conexiones TCP
(VER EN LA SIGUIENTE CLASE, esto es una breve idea poco desarrollada)

Un estado significa que se pueden hacer una serie de acciones.
La nomenclatura usada es: recibo algo / transmito algo.

### Control de errores y de flujo
Tenemos la ventana deslizante (el buffer anteriormente comentado) de forma que la aplicación coge datos de la izquierda y se introducen por la derecha en prioridad FIFO.
Para el control de errores, usamos retransmisión.

Campos involucrados:
- Nº de secuencia.
- Campo de acuse (qué byte espero recibir).
- Bit de ACK.
- Campo de checksum (por si hubiera un problema y hay un dato mal. Pilla cabecera + datos TCP y pseudocabecera IP).


##### Ejemplo diapositiva 25 (de concepto, pero no se generan así los ACKs).
En la izqda: perdemos un ACK y tenemos que reenviar. Da igual que se pierda el dato o el ACK, tienen el mismo efecto.

Si el timeout es muy chico, puede ocurrir que el ACK llegue bien pero muy pronto.
timeout muy grande: tardamos mucho en reaccionar que hemos perdido el dato (en caso de haberlo hecho).

En la dhca: El temporizador es muy chico. se trata de ACK acumulativo.


Si mandamos un dato y mandamos un ACK, el tiempo entre envío y recibo es RTT (Tiempo de ida y vuelta, Round Trip Time).
Es un valor dinámico que depende de la carga de red (si un router está muy solicita, incrementa)
Habrá que buscar un temporizador (timeout) que se adapte al RTT.


OTRA CLASE (séase, los títulos empienzan nuevamente, que alguien le de estructura a esto x dios)


### Control de errores
Relacionado con el control de flujo y de congestión.

Tendremos dos partes importantes:
- Generación de ACKs, que van a ser acumulativos y positivos (se verá).
- Timeouts, que van a ser adaptables.

Socket TCP (como idea, se verá en T5): Objeto obtenido a partir del SO que nos permite usar a alto nivel los paquetes de una conexión TCP.

En el receptor va a tener un buffer a nivel TCP (que se implementa en la pila TCP/IP del SO), con lo que se implementa en el SO.
El buffer del receptor (que está en el kernel del SO), se irá rellenando con los datos que irán llegando y podemos colocar dónde va el paquete gracias a su número de secuencia.
Hay un buffer por cada conexión TCP (primero hay que establecerla, ..., como ya se mencionó).

Es el SO quien gestiona el buffer.
Cuando la aplicación pide un dato a un socket, el SO saca de dicho buffer un paquete y se lo pasa a la aplicación.
Por tanto, la aplicación va consumiendo los paquetes más a la izquierda del buffer, con lo que los paquetes se van deslizando en el buffer (se dice que es ventana deslizante), de forma que se trata de una cola FIFO circular.

Campos involucrados:
- Nº de secuencia. Normalmente, nº acuse del ACK anterior (si no, un nº aleatorio).
- Campo de acuse (qué byte espero recibir). Normalmente, nº secuencia + datos del ultimo paquete.
- Bit de ACK.
- Campo de checksum (por si hubiera un problema y hay un dato mal. Pilla cabecera + datos TCP y pseudocabecera IP).

#### Generación de ACKs
Antes de verlos, damos una idea en la diapositiva 25 (que no es lo que pasa en la realidad, NO ES LO QUE HACE TCP: NO envia paquete y contesta con ACK cada vez).
Importante diapositiva 26. Pasamos a explicarl las 4 lineas:

Positivas: Decimos lo que ha llegado bien.
Acumulativo: Cuando digamos que ha llegado bien hasta algo, todo lo anterior ha llegado bien (ordenado).


2 casos en los que va bien:
1. Suponemos que tenemos el buffer del receptor bien (tenemos todos los paquetes ordenados y confirmados) hasta un cierto punto.
Llega ahora un paquete que sabemos que es el siguiente (por el nº de secuencia).
- Cuando llega, llega un segmento de forma ordenada y sin discontinuidad de forma que lo anterior ya está confirmado.
- *Acción:* Retrasamos el ACK, esperando un segundo paquete en 500mseg (según el flavor TCP Tahoe). Si tras 500mseg no viene ninguno, entonces enviamos el ACK.

2. Si tenemos todo en orden y el último paquete no confirmado (el resto sí):
- Si ahora llega un segundo paquete sin problemas (es el siguiente sin discontinuidad pero hay un ACK retrasado). 
- *Acción:* Manda inmediatamente un ACK acumulativo, con el nº de acuse el siguiente bit al último.
De esta forma, **mandamos un ACK cada 2 paquetes**. Si se queda uno suelto, esperar los 500 mseg.

2 casos en los que hay algo mal:
3. Llegada desordenada de segmento con nº de secuencia mayor al bytes esperado $n$.
Resulta que llega un paqeute con un nº de secuencia mayor al esperado $n$ (falta un cacho).
*Acción:* Mandamos inmediatamente un ACK con nº de secuencia del siguiente byte esperado, $n$.

4. Llegada de un segmento que completa una discontinuidad entera (paquete que completa el hueco) o parcialmente (paquete que reduce un poco el hueco):
*Acción:* Se manda ACK inmediatamente hasta todo lo k estaba bien.


En resumen: si todo va bien, se envía un ACK cada dos paquetes.
Si llegan paquetes desordenados, se mandan ACKs inmediatamente.
Se retransmite en el emisor por timeouts. Si no se ha recibido un ACK, se reenvía.

Otro caso de envío de ACKs:
(Ver tras control de flujo)
Si la ventana pasa de llena (Win = 0) a tener algo de espacio libre, se envía un ACK indicando el espacio libre. Notemos que este ACK es importante (si se pierde, el emisor se queda bloqueado). Ver en control de flujo

#### Estimación de timeouts
Motivamos un poco el uso de la estimación.
Anteriormente dijimos que el tiempo de timeout debe adaptarse al RTT (Round Trip Time).

El RTT no es un valor fijo:
- Tiempo de transmisión: tiempo que tarda en enviarse un paquete, 1/velocidad de transmisión. Depende de la tarjeta.
- Tiempo de propagación: tiempo desde que se comienza a enviar un paquete hasta que se empieza a recibir. Depende de la distancia y las condiciones de la red.
- Tiempo de procesado (en un router): variable, depende de la carga de la red (los paquetes que haya), la longitud de la tabla de encaminamiento, ... . No es fijo.
- Tiempo de transmisión (del router).
- Tiempo de propagación, ...
- Todo esto es tiempo de ida.
- El tiempo de vuelta es similar.

RTT = tiempo de ida + tiempo de vuelta.
Como tenemos uno (o varios) tiempos de procesado en el RTT, tenemos un RTT variable.

Como enviamos un paquete y recibimos un ACK, el emisor puede medir el RTT.


Lo que se hace es buscar un RTT filtrado (en promedio), no el RTT como tal.
Lo que se hace es:
RTT_nuevo = alpha * RTT_viejo + (1-alpha) * RTT_medio, con alpha en [0,1]
Ver diap. 28.
Tambien vamos calculando la desviacion:
Desviacion_nueva = (1-x) * Desvicion_vieja + x * |RTT_medio - RTT_nuevo|

Finalmente, el Timeout = RTT_nuevo + 4 * Desviacion_nueva


Tenemos un problema con los ACKs repetidos, pero para eso está el algoritmo de Karn, que sólo cambia el timeout en los no ambiguos.
SI hay alguna expiración del timeout: timeout = 2 * timeout.

### Control de flujo
Es un mecanismo de atrás hacia adelante: el receptor le dice al emisor que envíe más o menos datos.
Antes hemos visto que el receptor tiene un buffer (que será pequeño en dispositivos livianos).
Los paquetes que lleguen cuando el buffer esté lleno se descartan (flujo inútil).
Es un sistema crediticio: se envía crédito de lo que se puede o no mandar.

Esto se controla con el campo de ventana en la cabecera TCP (AWND, Advertised Window ..., de 16 bits). Se indican los bytes libres.

Cuando la ventana esté llena (recibe un ACK con Win = 0), el emisor se bloquea hasta recibir un nuevo ACK que confirme que se acaba de sacar una paquete de la ventana.
Este ACK es importante. Para ello, se usa un Timer de persistencia (determina el tiempo máximo a bloquear un emisor). Entonces, se envía 1 byte al receptor para que se fuerce el posible reenvío de confirmación del ACK.


Por otra parte,
En control de congestión tenemos una ventana que no envía a ningún sitio.
El emisor se dice a sí mismo de enviar más o menos datos (lo decide el emisor).
Como no se manda nunca, no hay un campo en la cabecera TCP, con lo que puede tener el tamaño deseado.



Ventana útil:
Es la ventana ofertada - bytes en tránsito.
(Ya que la información de la ventana ofertada la obtenemos mucho más tarde de los datos que enviamos)

Ventana optimista:
No cogemos la ventana útil ni la ofertada, sino una cosa intermedia.


Hay dos flags que nos permiten saltarnos el orden:
- Datos urgentes con puntero de urgentes.
- Solicitar entregas inmediataas.

Síndrome de la ventana tonta:
Situación liosa en la que la aplicación lee cada vez menos datos.

### Control de congestión
De las partes más importantes de TCP (junto con ACK + timeouts).
La velocidad de TCP depende de esto.

En Tahoe se manifiesta por las pérdidas de ACKs.
Intenta reducir la velocidad de emisión ante congestiones e incrementarla si todo va bien.

##### Explicado a la vez que se hace un prblema
En general, RTT = 2 Tiempo de propagacion + 2 Tiempo de transmisión
El establecimiento de la conexión TCP tarda 1.5 RTT o 3 Tiempos de propagación
Tiempo de programación = T_p, Tiempo de transmisión = T_t

En realidad el ACK final de establecimiento puede ser útil para enviar los primeros datos.


Tenemos en el emisor una ventana de congestión (CW) con un valor inicial de paquetes a enviar, parámetro dependiente del SO.
Esta controla el total de paquetes a enviar de una vez.

Si el valor inicial de la CW es 1, habrá que esperar en el receptor los 500mseg.
Si es 2, se recibe el ACK al llegar el 2º.

Estamos al inicio en una fase llamada **inicio lento**.
En esta fase, se mandan los paquetes permitidos por la ventana
Si estamos en inicio lento el tamaño de la ventana de congestión (CW) se incrementa tras un ACK:
CW = CW + nº de datos confirmados en el ACK.
La velocidad es CW/RTT
La velocidad incrementa exponencialmente.

Los paquetes a enviar permancen en la ventana hasta ser confirmados.


Notemos que cada RTT duplicamos el valor de CW en inicio lento.
Cuando llegamos a un umbral de CW, llegamos a una fase llamada **prevención de congestión**.
Por cada confirmación: CW = CW + 1/CW
Cuando confirmamos todos los paquetes de un RTT, aumentamos en 1 el CW.
La velocidad incrementa linealmente.

La velocidad es CW/RTT
El throughput (rendimiento) = CWND / RTT


(Ver diapositiva 36)
Si perdemos un ACK (se sucede un timeout):
1. Volvemos al valor inicial de CW
2. El umbral ahora vale la mitad del CW cuando sucedió dicho error.


Cada vez que empezamos en inicio lento hay una posible velocidad que no conseguimos.
Por esto surgen los distintos flavours.

**Nota:** Estamos suponiendo que todos los errores son por congestión.

### Tipos de flavours de TCP
#### TCP Tahoe
El básico, el que hemos visto.

#### TCP Reno
Siguiente versión a TCP Tahoe.

Distingue ACKs duplicados y timeout:
- Timeout (no ha llegado nada): Igual que Tahoe.
- ACKs duplicados (sin timeout, siguen llegando): paso a la mitad de CW y sigo en prevención de congestión.

##### TCP NewReno
Distingue otras situaciones.

##### TCP Vegas
Si el RTT aumenta, disminuye la ventana.
Si el RTT disminuye, aumenta la ventana.

##### TCP Cubic
Se usaba en todos los equipos con Windows y Linux hasta hace poco
Tiene dos ventanas de congestión:
- CW --> Depende de ACKs.
- CW --> Depende de RTT.
Hace una mezcla de esas dos.

##### Redes inalámbricas
No podemos suponer que los errores son debidos a congestión, ya que se pierden muchos paquetes.
Surgen versiones especiales para tener en cuenta a la redes inalámbricas.
TCP Westwood es especial para esto.

### Parte opcional de cabecera TCP
- Sello de tiempo: Añadir la IP de los routers por los que ha ido pasando.
- Estimación del RTT.

- Ventana escalada:
El control de congestión no manda la ventana nunca (ya que es lo que tiene el emisor para sí mismo, con lo que no se manda en el paquete).
Sin embargo, hay un campo para la ventana de control de flujo: AWDD (o Win), campo de 16 bits que indica el nº de bytes de dicha ventana (16 bits --> máximo 65535 bytes).

throughput = 65535 bytes x 8 bits_por_byte / RTT (suponemos RTT = 10ms = 0.01 s) = 52 Mbps
Con lo que como tenemos control de flujo (campo limitado a 16 bits), no podemos transmitir con TCP a más de 52 Mbps si tenemos dicho RTT (y la cosa empeora subiendo el RTT).

Para solucionar esto, podemos escalar la ventana: podemos escalar el 2^16 = 65535 bytes por un nº. Este va hasta 14 y multiplica hasta por 2^14.
De esta forma, de 2^16 pasamos a 2^30. Tenemos 16000 veces dicha velocidad.

# Ejercicios
## Pregunta 3. (1.5 puntos sobre 10)
Explique qué condición se debe cumplir entre el tiempo de transmisión, el tiempo de propagación y el tamaño de la ventana de congestión en un emisor TCP para que no haya interrupcción (paradas) en la transmisión.

Nota: Los tiempos de transmisión de los ACKs los despreciamos, así como los tiempos de procesamiento.

En la emisión de dos paquetes:
Teenemos 2 T_t (tiempo de transmisión), un T_p (tiempo de propagación) y otro T_p de vuelta al emisor, con lo que:
RTT = 2T_p + 2T_t

Si vamos a transmitir CW paquetes, tardamos en emitiros CW x T_t, con lo que queremos que CW x T_t >= RTT, para no tener interrupcciones.
Con lo que: CW x T_t >= RTT = 2T_t + 2T_p => CW >= 2 + 2 T_p / T_t


Por tanto, obtenemos transmisión continua cuando suceda qu:
CW >= 2 + 2 T_p / T_t

Si tuviesemos 95% de eficiencia, entonces:
CW x T_t = 0.95 RTT

## Problema 2. (3 puntos sobre 10) - (Enero 2024)
Suponga dos entidades TCP A y B con la siguiente configuración: MSS = 1.250 bytes; la ventana de congestión inicial es de 2.500 bytes; el umbral de congesteión está fijado inicialmente a 10.000 bytes. Ambas entidades utilizan TCP Tahoe.
a) Muestre el diagrama de intercambio de segmentos de TCP que se produciría para que A envíe un fichero de tamaño 60.000 bytes a B. Calcule el tiempo requerido total, considerando que el tiempo de propagación es de 5 ms y la velocidad de transmisión es de 10 Mbps. En el diagrama incluya en cada momento el valor de la ventana de congestión y en qué fase del control de congestión se cuentra el transmisor. SUponga que la ventana del control de flujo es arbitrariamente grande. Explique detalladamente su respuesta.
b) ¿Cuánto sería el tiempo requerido total si usara UDP? Explique detalladamente su respuesta.


El tiempo de establecimiento de llamada podemos suponerlo como 3T_p o 1.5RTT.

Para transmisión continua:
CW >= 2 + 2T_p/T_t = 12

Como CW = 2 MSS, la ventana la inicio envia 2 paquetes.

Dividimos ráfagas cuando recibe primer ACK.
Inicio lento:
- Mando 2 paquetes (lo que permite la ventana)
- Recibo ACK 1,2. (Ha pasado un RTT). CW = 2 + 2 = 4
- Mando 4 paquetes (o segmentos).
- Recibo ACK 3, 4. (Ha pasado un RTT). CW = 4 + 2 = 6      (podríamos mandar 4 = 6-2, pero inmediatamente llega el siguiente)
- Recibo ACK 5, 6. CW = 6 + 2 = 8. Hemos llegado al umbral, con lo que pasamos a PREVENCIÓN DE CONGESTIÓN.
- Mando 8 paquetes.
- Recibo ACK 7, 8.  CW = 8 + 1/8 = 8.  (Ha pasado un RTT)
- Recibo ACK 9, 10. CW = (8+1/8) + 1/8 = 8.
- Recibo ACK 11, 12. CW = ... = 8.
- Recibo ACK 13, 14. CW = ... = 9.
- Envio 9 paquetes.
- Recibo primeros 4 ACKs, pero el ACK del 9º espera por ser impar.
- Puedo transmitir solo 8 paquetes. Se transmiten.
- El primer paquete cuando llegue manda ACK inmediato (habia uno retrasado). En dicho momento: CW = 9 + 1 = 10. (Ha pasado T_5 = RTT).
- Recibo 3 más ACKs y se queda uno pendiente.
- Podemos transmitir (10-1) 9 paquetes, se había quedado uno pendiente.
- El primer paquete confirma el anterior, con lo que CW = 10 + 1 = 11.
- Se recibirán 4 ACKs más. En este punto, tenemos todo confirmado. (Ha pasado T_6 = RTT).
- Podemos transmitir 11, pero sólo faltan 8 para llegar a 48.
- Confirmamos los 8 con 4 ACKS. (Ha pasado T_7 = RTT + 3x2xT_t (3x2T_t es el tiempo en recibir los 3 ACKs. Un ACK tarda 2T_t en enviarse (por recibir 2 paquetes)))

Por tanto, el tiempo total es: ... = 113ms. 

UDP: 48 T_t + T_p = 53ms

## Ejercicio 2.  (2 puntos sobre 10) - (Enero 2022)
Suponga dos entidades TCP A y B con la siguiente configuración: MSS = 2KB; tamaño del buffer en recepción 10 KB; la aplicación receptora consume 4KB cada vez que acumula 6KB o más en el buffer; la ventana de congestión empiza siendo 1 MSS; el umbral de congestión está fijado inicialmente en 8 KB.
Muestre el diagrama de intercambio de segmentos TCP que se produciría para que A envíe un fichero de tamaño 24 KB a B. Calcule el tiempo requerido, considerando que el tiempode propagación es 20 ms. El tiempo de transmisión es despreciable.


Comprobación de transmisión continua (HACE FALTA COMPROBARLO SIEMPRE), esto es, que se comporta "similar" a UDP:
CW >= 2 + 2T_p/T_t. Como T_t = 0, entonces eso --> infinito. 
Por tanto, nunca vamos a tener transmisión continua.


