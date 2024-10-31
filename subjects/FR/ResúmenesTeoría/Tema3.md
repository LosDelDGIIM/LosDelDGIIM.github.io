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
2. ACK X+1, Syn Y
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
