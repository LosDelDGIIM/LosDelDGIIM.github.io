# Introducción a los fundamentos de redes
## Historia
Un servicio de banda ancha es un servicio de velocidad grande, que se inició en España a partir del 2000. Comenzaron por 2Mbps.
El ADSL en España comenzó transmitiendo 256kbps (el máximo teórico del ADSL son 20Mbps (al lado de la estación), aunque lo normal son 10 o 12).
Las redes de cable eran HFC (redes de cable y fibras híbridas), pero ahora tenemos FTTH (Fiber to the home), fibra directa a casa. La fibra es el mejor material para transmitir información del mundo, además de que no cuenta con interferencias, consiguiendo varios Gbps.

El principal uso de dicha red era para:
- Televisiones (contaban con una resolución de $640x240$, necesitando un servicio de 2Mbps sin comprimir).

Cerca del 70% del tráfico de internet es debido al multimedia, a través de las CDNs (Content Delivery Network), redes de transmisión de contenidos.
Por ejemplo, un vídeo de Youtube cuenta con varias copias del mismo alrededor del mundo.

## Sistemas de comunicación y redes
El sistema de comunicación típico es:

En un sistema de comunicaciones contamos con una fuente y con un transmisor (ambos en el mismo equipo), de forma que la fuente genera datos.
Después del transmisor, contamos con un canal de comunicación, el cual provoca errores:
- Ruidos.
- Interferencias.
- Diafonías: sucede mucho en ADSL, al tener muchos cables en paralelo juntos puede suceder que la información de un cable se meta en otro.

En el final del destino, contamos con un equipo que cuenta con un receptor y con el destino (que espera los datos a recibir).


Cuando hablamos de redes, tenemos que tener varios equipos interconectados, que funcionen de forma autónoma (sin interferencia de nadie) y que se realice de forma eficaz.

## Primera red de comunicaciones

La primera red de comunicaciones era la red de telefonía móvil.

Contábamos con nuestra línea de teléfono, que conectaba con una central de conmutación local, luego regional y luego nacional, la cual debía conectar con la central local a la que queríamos llamar.
Se usaba la conmutación de circuitos: 
- Inicialmente se creaba un camino físico juntando cables. A dicho camino se le llamaba circuito. 
- Era ineficiente porque dicho cable cuenta con una eficiencia del 50\%, debido a que aproximadamente se habla la mitad del tiempo de la llamada.
- Era un problema de seguridad el mal funcionamiento de una central, ya que dejaba sin servicio a miles de teléfonos.

Si ahora cambiamos los teléfonos por ordenadores y las centrales de conmutación por routerse, contamos con muchísimos caminos para conectar dos ordenadores, haciendo mucho más segura la red (a expensas de la seguridad en la red).

Ahora ya no tenemos un circuito físico, sino que son los routers quienes deciden a dónde enviar los paquetes y en qué momento hacerlo. Con el inconveniente de generar retardo pero con la ventaja de usar mejor el canal (si hay silencios, puede usarlo otro).

El departamento de defensa americana y posteriormente la NSF crearon las primeras redes asemejables a internet.

De una red esperamos:
- Autonomía.
- Interconexión.
- Eficiencia.

Una red clásica va a tener equipos terminales (hosts) y equipos de interconexión, que permiten conectar toda la red.

## Líneas de transmisión
Podemos contar con enlaces inalámbricos y cableados (Ver diapositivas).

Comenzó con los enlaces cableados con cables de pares (pensado para transmitir 4kHz, la media en la voz humana), luego con cables coaxiales y fibra óptica.
Este último es el mejor medio guiado existente.

---------------------------------------- Apuntes de 26-09

## Topologías

Una cosa es topología física y otra lógica.

#### Ethernet
Para compartir un medio común como un bus utiliza `CSMA/CD`: Acceso múltiple sintiendo la portadora (Carrier sense).
CD detecta colisiones: si lo que hay en el cable no es lo que he puesto (si hay más ruido), hay error.

Cuando no estoy en un medio compartido no utilizo CSMA/CD, para mayor velocidad.

#### Wifi
Cuenta on CSMA/CA:
Wifi no puede escuchar el medio.
Primero escucha que no haya nadie, envía el mensaje y recibe confirmación. Si no recibe confirmación, hay colisión.

### Bus.
Ventaja: es la más sencilla.
Desventaja: Que varios intenten usar la red a vez (colisiones). El bus es común para todos.

Se implementa mediante:
HUB: bocas ethernet que internamente funcionan como bus

### Anillo.
Un círculo en el que tenemos los distintos computadores. Se parece al bus ya que el medio es compartido.

Una versión habitual es `token rings`: testigo de anillo.
Como el medio es común, se va pasando el testigo entre los computadores para evitar que haya colisiones.

### Estrella.
Todos están conectados a un centro principal, típicamente un switch.
Es típica.

Su diferencia con el bus es que cada cable que sale del bus es independiente del resto.
Si un pc pone algo en una toma el resto de pcs no la escuchan.
Cada una de las líneas tienen colas para guardar a dónde enviar los paquetes.
TEnemos un procesador que coge los paquetes de las colas y los envían a las salidas.

Para ir de un equipo a otro, envía el paquete, lo recibe y lo envía. El resto de usuarios no ven el paquete.

No compartimos el medio y hay más seguridad porque el resto no ve lo que se envía.

### Árbol
Típica para redes empresariales en tres niveles:

Primer nivel: red troncal.
Segundo nivel: red de división.
Tercer nivel: red de acceso.

Los equipos de primer y segundo nivel suelen ser switches. Pueden aparecer ciclos en el árbol.
Ethernet y otros mecanismos no tienen ningún mecanismo para evitar que un paquete circule en círculo. Esto echa la red abajo en 2 segudos.

Existe el protocolo STP que hace que cualquier topología quite los enlaces que formen bucle.

En el nivel de red (IP) hay ya un protocolo que evita que se formen bucles.

### Mallada
Todos los nodos están conectados entre sí por medios independientes.

Ventaja: Es muy fiable, si se cae un enlace hay enlaces que usar.
Problema: Falta de escabilidad, al meter un nuevo nodo hay que meter $n-1$ enlaces al meter el nodo $n$-ésimo, inmanejable para redes grandes.

Dentro de una empresa la red troncal puede seguir dicha topología para evitar caídas importantes.

### Híbrida
Se usa una mezcla de todas. Es la más típica.

## Clasificación de redes
Pueden clasificarse según:

### Según tamaño o área de extensión
Redes de área personal: PAN, todos los dispositivos de un escritorio (reloj, portátil, cascos, ...).
Redes locales: LAN (Local Area Network), decenas de metros.
Redes de áreas metropolitanas: MAN (como un campus o ciudad).
Red de área extensa: WAN (redes disponibles en todo el país), como redes telefónicas.

### Según difusión o punto a punto
Difusión: lo que pone alguien llega a todos.
punto a punto: Sólo estoy unido a un nodo.

Un switch es una conexión punto a punto.
Un HUB es una conexión de difusión.

### Según tipo de transferencias de datos

full-duplex: transmite y recibe simultáneamente.
half-duplex: transmite en un sentido y recibe en el otro simultáneamente.
simple: sólo recibe en un sentido (no transmite), o viceversa. Los TDT son simples.

Wifi o transmite o recibe, pero lo hace muy rápido.

## Iconos
Consultar diapositiva de iconos.

Los importantes son los de la columna izquierda.
- HUB: Caja con flechas.
- Switch: Caja con 4 flechas.
- Router: Caja redonda con 4 flechas o una cruz.
- Cortafuegos: Un muro.
- NAT: 
 

Los switches funcionan a nivel de enlace y los routers a nivel de red (a nivel 3).
Cómo diferenciar switches y routers:
Los switches tienen muchas bocas para conectar muchos equipos.
Los routers tienen pocas bocas, porque conectan 2, 3, 4 redes.

### Switch multicapa
No entra pero nos comenta idea:

Cuando tenemos un switch con 48 bocas (es algo normal), todas esas bocas son de la misma red de área local.
Hay veces que no nos interesan que estén en la misma red (LAN). Hay un concepto para decir que ciertas bocas pertenecen a cierta red.
Este concepto es VLAN (redes virtuales). Sirve para dividir el switch en varios switches, haciendo que sean redes distintas.

Si tenemos otro switches, podemos asociarle las mismas redes virtuales que las del otro y conectarlos por cable, de forma que los computadores que envían información a un switch, este puede enviarla a otro switch para que lo envíe al computador correspondiente.
Permite extender zonas de redes locales a zonas más extensas.


No se pueden conectar dos VLAN distintas entre sí: hace falta pasar por un router.
Por norma general, para conectar dos redes hay que trabajar a nivel de red.
Si un switch permite conmutación entre LANs, se supone que tiene alguna funcionalidad a nivel de red.

Por tanto, un switch normal funciona a nivel de capa mientras que un switch multicapa funciona a nivel de red.

La red de la UGR tiene en primer lugar switches para conectarnos hacia ellos. Por encima, switches multicapa y más arriba routers.

### Bridge
Un bridge es lo mismo que un switch, funciona a nivel 2 pero actúa como puente entre dos tecnologías distintas (como Ethernet y ATM).
En muchos protocolos se verán bridges, aunque en realidad se estará hablando de switches.

# Diseño y estandarización de redes
Estandarización = modelo de capas. 

Si lo recordamos, modelos OSI y TCP/IP.

   |-------------------------
L5 | Aplicación que hace uso de la red
   |-------------------------
L4 | Transporte (TCP / UDP)
   |-------------------------
L3 | Red (IP)
   |-------------------------
L2 | Enlace
   |-------------------------
L1 | Física
   |-------------------------
   
Problemas a resolver dada una red: muchos

Por capas:
- A nivel físico: ver cómo transmitir los datos. Hay varios tipos de codificaciones para enviar bits.
    Codificación de canal: añadir redundancia a los datos. De ello se encarga la capa física.
- Capa de enlace: Se encarga principalmente de los mecanismos de acceso al medio. SI hay un medio común: detectar si hay gente transmitiendo, si no transmito.
    Protocolo MAC: de control de acceso al medio. LLC: Control de acceso lógico para primeras retransmisiones. Si paquete llega mal, retransmite unas cuantas veces.
- Capa de red: (Se supone que no haya colisiones) Lo importante es llegar al otro extremo salto a salto: Direccionamiento (dar una dirección y ser alguien en la red) y encaminamiento (saber cómo llegar al destino).
- Transporte: Encargado de ver qué pasa con los paquetes (el enlace intenta recuperar paquetes pero no lo consigue). 
    Se encarga de fiabilidad (corregir errores, congestion de red, extremo lento que recibe datos y regula velocidad (control de flujo)) y de multiplexación de datos (por la tarjeta de red tenemos información que llega a varias aplicaciones que usamos. Para que el SO sepa qué datos corresponden a qué aplicaciones, contamos con los puertos, que nos definen a qué aplicaciones corresponden los datos ).
- Aplicación: Lo que queremos hacer pero los clientes y servidores tienen que buscar mecanismos para hacerlo.

Modelo de referencia: Algo abstracto que nos gustaría tener (no es una implementación).
Llegó ISO y puso un modelo, que dividía los problemas de cierta forma.
Modelo TCP/IP fue el que hizo internet.

Una cosa es una implementación y otra una abstracción.

OSI: 7 niveles, TCP/IP: 4
Copiar diapositiva 9.

RFC: Estándar que permite saber cómo funciona TCP/IP.

Lo importante entre el modelo de capas es que el enlace entre una y otra sea el mismo.

## Capas de nivel físico y de enlace

Dibujamos dos clientes que quieren conectarse mediante sistemas intermedios.
Dichas capas sólo se tienen en cuenta en la primera conexión (por ejemplo, de un pc a un router). Dichas capas escapan a la comprensión del envío de datos de un computador a otro.

## Capa de red
En nuestro caso, será IP

Salto a salto, la información llega de un extremo a otro. Va salto a salto pero consigue llegar al extremo, usando routeres y sus tablas de encaminamiento.
Una vez hecho el encaminamiento, las capas superiores son sólo de los extremos (ya no hablan los equipos intermedios, sino sólo los computadores de los extremos).

Por tanto, los computadores tienen las 5 capas mientras que los routers sólo las 3 más bajas.

Garantizar que la información llega de forma fiable se hace en los extremos.

# Terminología, conceptos y servicios

- Entidad de nivel n:   Entidad que ejecuta la capa n-ésima.
- Entidades pares:      Entidades iguales, son de la misma capa, en distintos equipos y hablan entre sí.
- Protocolo:            Cómo hablan entidades pares.
- Interfaz:             Cómo interactúan los protocolos de la misma entidad.
- Servicio:             Lo que proporciona una capa a otra.

- Las capas proveedoras son usuarias de las capas inferiores que les sirven de servicio. Las capas superiores son productoras.
- Pila de protocolos: Todos los protocolos juntos en una misma máquina.
- Arquitectura de red: Qué entidades hay en la red. OSI: Capas, TCP/IP: Capas.
- SAP: Dónde me dan servicio las distintas capas (cómo se comunican).

## Proceso de encapsulamiento y transmisión de datos
Ver diapositiva 12.
Los datos del nivel anterior se encapsulan en los datos del siguiente (debajo) nivel:

- Datos del nivel de aplicación: datos + cabecera.
- La aplicación le pasa la información al nivel de transporte, que mete eso en los datos y añade su cabecera del nivel de transporte.
- Todo se envía al nivel de red como sus datos. El nivel de red añade su cabecera (equipo origen, equipo destino, ...).
- Igual al nivel de enlace.
- Igual al nivel físico: Señales eléctricas para determinar dónde empieza el mensaje y al final para terminarlo.
Los datos que se pasan de una capa a otra se llaman SDU. Al añadir las cabeceras, se convierte en la unidad de datos de paquete (PDU).
La PDU de una capa es la SDU de la capa de abajo.

Al transmitir los datos:
Cuando se va a transmitir algo, lo genera la aplicación --> SO --> Pila TCP/IP --> Transporte --> Red --> Enlace y lo manda a nivel físico.
Una vez recibido, pasa los datos a nivel de enlace, coge cabecera para ver si tiene que hacer algo, quita cabecera y pasa a nivel de red.
Se realiza otra vez el encapsulamiento y sucede el mismo proceso, hasta llegar al otro computador.

Hay dos tipos de comunicaciones:
- Verticales (o comunicaciones reales): En el mismo dispositivo.
- Comunicaciones virtuales: el nivel de red del computador habla con el nivel de red del router (de forma abstracta).

Las capas de transporte y aplicaciones sólo hablan entre los extremos.

## Retardos en comunicación
Tenemos una entidad que va a hablar con otra a través de otra (por ejemplo, dos computadores y un router en medio). Queremos transmitir un paquete.

En Ethernet un paquete típico son 1500 Bytes x 8 bits = 12000 bits. El tiempo que se tarda en transmitir sale como resultado de dividirlo entre los x bps.

- Desde que se pone el 1er bit hasta que se pone el último hay un **tiempo de transmisión** que depende exclusivamente de la tarjeta gráfica: bits / velocidad de transmisión.
- Una vez transmitido, hay un retardo. El **tiempo de propagación** (distancia / velocidad de transmisión) es el tiempo que sucede entre que se escribe el primer bit y llega el primer bit. 
   La velocidad de transmisión inalámbrica es a la velocidad de la luz. La velocidad de un cable (depende del cable) es a 2/3 de la velocidad de la luz. En los cables se pierde un bit por cada millón de bits. La pérdida de bits es usualmente por colas llenas.
- El paquete llega al intermediario, que ha de decidir qué hace con dicho paquete (si fuera un router, mirar tablas de encaminamiento). 
  El equipo intermedio tiene unas colas donde va metiendo los paquetes que recibe, que irá procesando. El tiempo que nuestro paquete está en la cola depende de la situación del equipo intermedio. Hay un **tiempo de procesamiento** más un **tiempo en cola** que el paquete permanece en el equipo intermedio.
- Se envía desde el equipo intermedio hasta el equipo destino. El **tiempo de propagación** de ahora probablmente no coincidirá con el anterior.

Ver página 14.

Al hacer ping hay tiempos distintos debido al tiempo de procesamiento.

##### Cómo funciona ping (se verá)
Mediante el protocolo ICMP y paquetes `echo-req` y `echo-reply`

## Tipos de servicios
Relacionado con el nivel de transporte, hay dos clasificaciones importantes: orientadas a conexión y a fiabilidad.

### Orientadas a conexión
Antes de enviar datos nos aseguramos de que el otro dispositivo esté encendido.
- TCP es orientado a conexión.
- UDP no es orientado a conexión.

### Orientados a fiabilidad
fiabilidad = que funcione bien (todos los bits de un archivo estén bien). Si es fiable, la conexión terminará una vez no vaya bien.

Para tener un protocolo fiable, contamos con los mecanismos de:
- Control de conexión:    Me conecto y sé que el otro esté encendido. Ser fiable => ser orientado a conexión.
- Control de errores.
- Control de congestión:  Relativa a red.
- Control de flujo:       "Garantizar que hay suficientes sillas para cada persona".
                          Ocurre en los extremos, normalmente al nivel de aplicación, con dispositivos con poca memoria.
- Entrega ordenada:       Si se envían muchos paquetes, estos llegan en orden.

Una red congestionada significa que los routers tienen colas de forma que se meten muchos paquetes por un lado y salen pocos por el otro: las redes no son capaces de ir tan rápidos.
Hay mecanismos para arreglarlo, basado en que las fuentes envíen datos deforma más lenta.

- TCP es un servicio fiable.
- UDP no es un servicio fiable.

La misión de UDP es ser rápido.

# Internet (Historia y organizamiento)

Dos cosas importantes: cuáles son los protocolos y cómo se gestiona internet.
Las direcciones IP son únicas en todo el mundo, así como las direcciones de DNS.

Antes había un protocolo por el que se enviaba un:
Requests for comments (Se quedó y se llaman RFC).

## Organización topológica

Los operadores se establecen en 3 jerarquías, llamando a cada nivel tier.

- Tier 3: los más cercanos a los usuarios, ISPs (Internet Service Provider).
- Tier 2: hacen de distribución entre tier 1 y tier 3.
- Tier 1: los que componen la estructura troncal de Internet. Todos comunicados entre sí y como mínimo en dos continentes.

Dos tipos de relaciones:
- Tránsito: un tier 3 paga a tier superior por enviar datos.
- Peering: entre el mismo nivel.

Antigüamente, para que un ISP de un país hable con otro del mismo país había que ir a EEUU, por falta de recursos.
Se pusieron los NIC (Neutra Interchange ...) en los que se pueden enviar datos a operadores del mismo país.

## Red Iris

Red real española para investigación.
Todas las universidades públicas y centros de investigación conectados en ella.

Las redes se dividen según autonomías (RICA).
Tiene conexiones externas con la red científica europea.

## Cómo se realiza el direccionamiento en las capas
Tenemos direccionamiento en varios niveles:

- Enlace: depende de la tarjeta. Si pensamos en Ethernet:
    - Se divide en dos niveles (MAC y LLC). Las direcciones se llaman direcciones MAC: AA:BB:CC:DD:EE:FF.
    - Las direcciones MAC en teoría son únicas en todo el mundo (los 3 primeros bites identifican el fabricante). 
      Si sabemos la MAC de una tarjeta, podemos hacer seguimiento de paquetes.
      Podemos aleatoriezar las direcciones MAC en redes pequeñas para evitar seguimientos (se hace en Apple y luego en Android).
      Programa macchanger para cambiar la dirección MAC.
- Red: Direcciones IP: A.B.C.D. Las públicas son únicas en todo el mundo y las privadas no.
- Transporte: Direccionamiento a través de puertos. Los puertos identifican a qué proceso va un determinado paquete.
- Aplicación: Nombres de dominio mediante DNS.

Se transmite punto a punto. Necesitamos saber direcciones MAC de entes punto a punto.
El protocolo ARP nos permite preguntar por direcciones MAC.
