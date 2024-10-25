# Tema 2. Capa de red.

# Introducción

Recordamos el modelo que seguiremos:

|------------
|  App
|------------
|  TCP/UDP
|------------
|  IP
|------------
|  LINK
|------------
|  PHY
|------------

Cada una de las capas suele tener un nombre para los paquetes

En este tema, veremos la capa de red, IP a fondo.

Veremos:

- Dos funcionalidades de IP: Identificación de equipos y encaminamiento (llegar salto a salto entre los extremos), a parte de la fragmentación:
    Las tarjetas tienen un concepto llamado MTU (unidad de transferencia máxima). Tamaño máximo = si queremos paquete IP más grande, hay que cortarlo en trozos.
    Juntarlo en el destino se llama ensamblar.
- Si queremos enviar un paquete a una dirección IP, necesitamos la dirección de enlace del equipo, porque tenemos que enviar a nivel de enlace. En el caso de ethernet y wifi, se le llama dirección MAC.
    Hace falta algo que diga: para esta IP, cuál es su dirección MAC? Esto lo hace el protocolo ARP.
- Protocolo ICMP. Es un protocolo de mejor esfuerzo: intenta que los datos lleguen bien pero si no se hace bien, no hace nada para evitarlo. Si un paquete no llega lo ha intentado pero no puede hacer nada. Lo único que se puede hacer es enviar un mensaje de error. Sin embargo, las capas superiores tratarán de resolver este problema (el de que los paquetes no llegan y no se ha hecho nada).
- Porotocolo DHCP (protocolo de configuración de host dinámica): Para configurar todo lo que hace falta de forma automática: que las direcciones IP y el DNS se configuren automáticamente.

# Objetivos (ver de diapositivas)

- Conmutación de circuitos, datagramas y paquetes.
- Direccionamiento.
- Encaminamiento salto a salto. Se basará en tablas. 
    Estático: se rellenan las tablas de forma manual. 
    Dinámica: los routers usan protocolos para rellenar las tablas.
- Protocolo ARP para asociar capas de red y enlace.
- Errores con ICMP.

Ver bibliografía, cualquier libro de TCP/IP.

# Funcionalidades
TCP simplifica el modelo OSI.

Tiene como funcionalidades:
- Encaminamiento
- Conmutación
- Interconexión de redes
- En OSI: control de gestión

Protocolos de red que veremos:
- IP
Existen más como ATM, x25, ... (antes de que IP fuera la elegida).

# Conmutación

La conmutación es la acción de establecer o determinar caminos que permitan transmitir información de extremo a extremo.

Como dos grandes esquemas de comnutación, encontramos los **circuitos** y los **paquetes**.

## Conmutación de circuitos
Antiguamente, existía una conmutación física de circuitos, para conectar de forma física los equipos emisor y receptor. Era muy usado en telefonía.
De esta forma, tenemos muchos cables entre los usuarios y las centrales, y menos cables entre cada par de centrales, ya que no todos los usuarios hablan al mismo tiempo.

En las centrales iniciales, eran simplemente rotarius (piezas físicas que rotaban para conectar los cables adecuados).
Si hacemos esto en todas las centrales de comunicación, tenemos un circuito (camino) físico que conecta ambos equipos.

Los módem antiguos utilizaban conmutación de circuitos de forma analógica.

Beneficios:
- Recursos dedicados (tenemos un sólo cable para nosotros), lo que facilita las comunicaciones a tiempo real y sin retardos.
- El recurso se mantiene dedicado toda la sesión.
- No hay contención (competición por conseguir el medio).
Problemas: 
- Cuando un usuario no usa su cable hasta la central, no lo usa nadie más. Uso ineficiente de recursos.
- Hay establecimiento de llamada (para que todos los cables se toquen).
- Es poco tolerable a fallos (si algo no funciona, deja todo de funcionar).

(Ver diapositivas sobre ventajas e inconvenientes)

## Conmutación de paquetes
Ahora no enviamos una señal analógica, sino datos en binario en bloques, a los que llamamos paquetes.
En los elementos de interconexión tenemos que poner ahora colas, porque tenemos que ver por dónde sale.

|------------
|  App
|------------
|  TCP/UDP
|------------
|  IP
|------------
|  LINK
|------------
|  PHY
|------------

Cada una de las capas suele tener un nombre para los paquetes

- Link:     tramas.
- IP:       datagramas
- TCP:      segmento.
- UDP (User datagram protocol): datagrama.
- Aplicación: mensaje.

Si queremos en binario, necesitamos conmutación de paquetes. Dos grandes tipos:

### Conmutación de datagrama
Una carta que le damos al cartero y el cartero intentará que llegue al destino. 
Si no llega, se ha perdido.
El mejor esfuerzo.

Así funcionan muchas conmutaciones de paquetes.
Debe haber una capa superior que se encargue de resolver esta situación.
IP hace envío de datagramas.

Características:
- No hay estableceimiento de conexión: enviamos un paquete y no sabemos si el otro extremo está encendido.
- Cada paquete enviado es totalmente independiente (se olvida del resto de paquetes):
    - El encaminamiento se realiza paquete a paquete: un paquete puede ir por una ruta y otro podría ir por una ruta distinta (si por ejemplo cambia la tabla de encaminamiento del router). Puede suceder que un paquete adelante a otro, no tienen por qué llegar en orden. Otra capa ha de encargarse para solucionar esto.
    - Si troceamos los paquetes, fragmentamos donde nos haga falta, pero las fragmentaciones sólo se ensamblan en el destino.
- En cada salto hay almacenamiento en las colas de cada nodo (equipos intermedios o routers) y reenvío de los paquetes.
- Como queremos hacer el encaminamiento salto a salto, todos los paquetes han de tener dirección de origen (para las respuestas o encaminamientos específicos) y de destino; aunque en la asignatura se considera que el encaminamiento sólo dependerá del destino. A veces puede intersar tener varias direcciones de destino (para hacer difusiones de datos).

Usaremos en la asignatura principalmente conmutación de datagramas.


En resumen, necesitamos colas y el medio no es exclusivo: un cable ethernet puede ser usado por muchos, luego hace falta algo que determine quién usa el cable cada vez.

### Conmutación con circuitos virtuales
Siguen siendo paquetes pero cuando enviamos datos se reservan recursos.
Hay paquetes que reservan ciertas colas en los routeres para los siguientes paquetes.

Se usaba en ATM (Asyncronous Transfer Mode), el inicio de la telefonía digital.

La idea es que si tenemos diferentes caminos posibles por los que ir, que todos los paquetes sigan el mismo camino, estableciéndose el camino al inicio. Este camino se denominaba circuito, siguiendo la idea de los circuitos .
Este camino lo decide cada router.
A pesar de no ser un circuito como tal, ya que estaba disponible para más paquetes.

- Hay que establecer la conexión para averiguar la ruta a seguir.
- Los recursos no son dedicados, pero temporalmente sí.
- Si un router se cae, se cambia de camino. En la mayoría de las veces sigue el mismo camino, pero no es obligatorio.


Simplemente para ver que existen más tipos de conmutación a parte del datagrama.

**NO FIARSE DE CHATGPT EN LOS EJERCICIOS DE LA RELACIÓN**.

# Protocolo IP

Dos grandes versiones: IPv4 (la que vamos a ver y la que se utiliza) y IPv6 (se empieza a utilizar, se ven algunas diferencias en las diapositivas).
IPv4 especificadao en el RFC 791.

Permite conectar redes y superredes.

- Direccionamiento: cada equipo (tarjeta de red en realidad) tiene que tener una dirección IP.
- Encaminamiento salto a salto entre equipos y routers.
- No tiene establecimiento de transmisión ni handshake, porque no es fiable, es un protocolo de máximo esfuerzo.
    - *protocol*: Cómo dos elementos de la misma capa hablan entre sí.
    - *handshake*: Intercambio concreto de mensajes.
- Al envío de datos (PDU, datos que venían de capa de encima y cabecera) se les llama datagramas. A los fragmentos IP se les llama paquetes.
    Como la mayoría de las veces no hay fragmentación, datagrama = paquete, generalmente.
- Gestiona la fragmentación.

## Funcionalidad 1. Direccionamiento
**Dentro de una misma red, no pueden repetirse direcciones IP**.
Las direcciones IP tienen 32 bits (son 4 bytes). La nomenclatura usada es: A.B.C.D, cada una en decimal. La máxima es 255.255.255.255.

Los nombres de dominio (www.google.com) se usan en la capa de aplicación. En la capa de red se usan las direcciones IP. El DNS traduce los nombres de dominio a direcciones IP (Tema 5).

Veremos la diferencia entre IP públicas y privadas (si se sabe la diferencia, pensamos ahora que estamos trabajando con públicas).

### Direccionamiento jerárquico

Internet usa direccionamiento jerárquico. Las direcciones IP se organizan en clases:

(Cuando se inicia internet, se dividen los 32 bits en dos trozos: | red | equipo |)

**NECESARIO APRENDERSE LOS RANGOS**.
- Clase A: Todas las que empiezan por: 0xx ... x/8 ==>  0.0.0.0 -- 127.255.255.255
    Los bits que definen la red son los 8 primeros, luego tenemos 128 redes de 2^24 ~ 16.000.000 equipos
- Clase B: Todas las que empiezan por: 10x ... x/16 =>  128.0.0.0 -- 191.255.255.255
    Tendremos $2^14 = 16384$ redes de 2^16 = 65536 equipos
- Clase C: Todas las que empiezan por: 110x ... x/24 => 192.0.0.0 -- 223.255.255.255
    Tendremos $2^(24-3) = 2^21 = 2.000.000$ redes de 2^8 = 256 equipos
- Clase D: Todas las que empiezan por: 1110x ... x => 224.0.0.0 -- 239.255.255.255
- Clase E: Todas las que empiezan por: 1111x ... x => 240.0.0.0 -- 255.255.255.255

Para crear redes y asignárselas a equipos, tenemos tres clases: A, B y C.

Las clases D y E no se usan para identificar ni redes ni equipos:
- E de *experimental*, se deja un rango para hacer pruebas.
- D se usa para multidifusión. Cada dirección identifica un grupo de equipos. Para ello, hay un protocolo IGMP para suscribirse a grupos.

Ej: IPTV es ver la TV a través de internet mediante una red gestionada mediante un decodificador. La información de un canal de TV se envía a miles de usuarios a la vez. Manda un paquete a la dirección de multidifusión del canal de televisión.
También hay protocolos de multidifusión que utilizan direcciones de dicho rango que usan los routers al hablar entre sí.

En IP:
- Difusión (broadcast), enviar algo a todos los equipos de la red.
- Multidifusión (multicast)
***

### Máscaras de red
Nomenclatura de máscaras: Como las ips: A.B.C.D
Es obligatorio que todos los bits a 1 estén consecutivos y a la izquierda.
- 8 bits a 1 es: 255.0.0.0
- /x, tal que x es el número de bits a 1.

Las máscaras de red sirven para identificar qué parte de la dirección IP es la red asociada a una IP.

Ejemplo: dada la IP 192.168.1.5/24 (máscara 24, luego los primeros 24 bits son la red):
```
  11000000.10101000.00000001.00000101
& 11111111.11111111.11111111.00000000
--------------------------------------
  11000000.10101000.00000001.00000000   =   192.168.1.0
```

#### Direcciones reservadas
- Por tanto, la dirección de red es 192.168.1.0
- Tanto la dirección de red (xxx.xxx.xxx.0) como la última de equipo (xxx.xxx.xxx.255) están reservadas.
- 192.168.1.255 es la dirección de difusión o broadcast para la red 192.168.1.0.
- 127.0.0.1: local loop o localhost, para conectarse a un servidor en nuestra propia máquina.

En la actualidad, cualquiera que empiece por 127 es para eso.
Para la 127.0.0.1 no hace falta tener una tarjeta de red (como para el resto de IPs).

### Desperdicio de direcciones IP

Conforme avanzamos en jerarquías de IP, desperdiciamos más direcciones IPs.
Por ejemplo, si necesitamos 1000 equipos, necesitamos una red de clase B, con la que desperdiciamos más de 60000 direcciones.

#### Subredes
Si queremos una red de menos de 256 equipos, podemos añadir bits a la máscara para conseguir más huecos para red y menos para equipos.
De esta forma, la primera dirección IP será la dirección de red y la última la de difusión de dicha red.
Cada vez que añadimos un bit a la máscara, estamos dividiendo una red en dos mitades.
Si comenzamos con una red de clase C y la dividimos en 2:
- xxx.xxx.xxx.1x ... x/25
- xxx.xxx.xxx.0x ... x/25
Cada una con capacidad para 128 equipos.
Si hacemos esto, decimos que tenemos dos **subredes**. 
De esta forma, una subred es cualquier red con máscara mayor a una red de un tipo ya conocido.

#### Superredes
Si hacemos el procedimiento inverso, quitarle un bit a la máscara, duplicamos la capacidad de equipos.
En este caso, decimos que tenemos **superredes**, aunque siempre lo llamaremos red.
Quitarle un bit a la máscara de red es como juntar dos redes con un tamaño de máscara de red una unidad menor.

Si tenemos 500 equipos a direccionar, es mejor usar una superred como resultado de juntar dos de tipo C a usar una de tipo B, ya que desperdiciaríamos más.

##### Ejemplo
Queremos direccionar 700 equipos.
Para ello, necesitamos 702 direcciones (más la de red y de difusión). Tenemos que buscar un n tal que 702<=2^n. En este caso, n = 10.
En este caso, para la parte de equipo usaremos 10 bits, y para la parte de red 32-10 = 22, máscara /22:

La parte de la IP de la red sería la:
11111111.11111111.11111100.00000000
La dirección de red sería la primera, la        192.168.0.0/22
La dirección de difusión sería la última, la    192.168.3.255



Sin embargo, lo de subred y superred son nomenclaturas. Nos referiremos normalmente como redes.

### Saber identificar redes en los diagramas

Las direcciones IPs son de cada tarjeta.

Las redes del nivel de red tienen un identificador, pero tenemos que identificar a las redes.
Un router es como un pc pero con varias tarjetas de red, para conectarse con varias redes.
    Como curiosidad, `sysctl -a`, podemos buscar `net.ipv4.ip_forward` y si tenemos la variable a 0, nuestro equipo no es un router, si es un 1 sí.
    Varios routers son realmente ordenadores linux con varias tarjetas de red.
Definición: funciona a nivel de red y encamina paquetes.

Podemos tener por ejemplo tres redes, todas ellas conectadas a un mismo router: 192.168.0.0/24, 192.168.1.0/24, 192.168.2.0/24
Un router sirve para separar redes.

Sin embargo, hemos hecho una simplificación:
Tenemos realmente un switch que tiene muchas bocas a las que conectar los equipos, teniendo una boca con la que conectarse al router mediante RJ45.
Todo eso (varios equipos conectados a un switch y a un router), es una red doméstica o LAN.
Si conectamos cosas con switches, seguimos a nivel 2, luego no separan redes IPs, seguimos en la misma red IP (es necesario un router para separar redes).

Al ver un dibujo en el que conectamos directamente equipos con un router, se trata de una simplificación en la que hemos eliminado el switch como intermediario (siempre estará este).


Un router doméstico tiene en su interior: 
- Un router que conecta la red doméstica con la red exterior (ADSL, o fibra óptica),
- Un switch de usualmente 4 bocas ethernet de forma que cada boca está conectado a un punto de acceso inalámbrcio.
- Un punto de acceso inalámbrico es similar a un switch pero de forma inalámbrica. En esta asignatura, la conexión por cable o inalámbrica son indiferentes.

### Direccionamiento privado
Hay un problema, que es la escasez de direcciones.

Soluciones:
- Una de las soluciones es el direccionamiento sin clase (CIDR, creo): Las máscaras no tienen por qué ser 8, 16 o 24. Desperdiciamos menos direcciones.
- Direcciones privadas.
- (se verá luego) Aumentar el número de bits, de 32 a 128: IPv6 (mete más cosas).
    En hexadecimal separando con dos puntos: FFFF:FFFF:FFFF:FFFF:FFFF:FFFF:FFFF:FFFF

Las direcciones IPs son únicas en todo el mundo. 
Sin embargo, nos imaginamos que estamos en una isla totalmente aislada del exterior. En este caso, podemos poner las direcciones que queramos, ya que como no se comunica con el exterior, pues no habrá interferencias. 
De esta forma, en cada isla podemos repetir direcciones y no tendremos problema en comunicarnos dentro de la isla (aunque en otra haya un equipo con la misma dirección, ya que no podremos comunicarnos con el mismo).

Dentro de cada clase se definen algunos rangos de direcciones a usar como direcciones IP privadas.
Clase A:   0...127.x.y.z/8 -->  10.x      .y.z
Clase B: 128...191.x.y.z/8 --> 172.16...31.y.z
Clase C: 192...223.x.y.z/8 --> 192.168    .y.z
**Hay que saber dichos rangos para saber identificar redes privadas y públicas**

En caso de darnos una dirección IP, si está dentro de los rangos de la derecha, son direcciones privadas.

Las direcciones privadas son similares al número de piso dentro de un bloque de pisos.
Si estamos dentro del bloque, sabemos exactamente al lugar que nos referimos.
Si estamos en otro bloque, no sabremos llegar al mismo. Hace falta una traducción de red (NAT).

##### Ejemplo útil
Tenemos un router conectado a una red pública con dirección del router 33.33.33.33
El router presenta otro extremo a una red privada, con la dirección 192.168.1.1
La red pública se encuentra conectada a internet.
En otra red conectada a internet, tenemos un servidor http escuchando con el puerto (TCP) 80.

Tenemos a un equipo en la red privada con IP 192.168.1.2 que es un cliente http.
Si el equipo envía una petición al servidor, la petición llegará al servidor, ya que era una IP pública. La petición llega.
Sin embargo, para que el servidor nos responda, necesitamos más información.

##### Nomenclatura en empresas
Si tenemos un router que conecta una empresa a internet, podemos tener que este esté conectado a una red con servidores con direccions públicas.
Y a su vez una red con equipos de los empleados, los cuales tienen direcciones privadas.

Cuando hablamos de empresas:
A la red de los empleados con direcciones privadas se le llama **intranet**.
A la red que contiene los servidores o equipos accesibles desde fuera, se les llama **extranet**.

## Traducción de direcciones de red (NAT, Network Address Translation)
Estamos en nuestra casa, en el equipo 192.168.1.2, conectados al router 192.168.1.1 que conecta con una red pública 33.33.33.33
La red pública se conecta a internet, que llega a un equipo 66.66.66.66

El equipo envía una petición (1), que pasa al router (2) y este lo envía al internet con el fin de que llegue al equipo 66.66.66.66
El equipo responde al router (3) y el router al equipo (4).

(1)
Una petición http está formada por una cabecera http y por datos. La cabecera contiene:
Header IP
- Dirección IP de origen (source) + puerto (sport):          192.168.1.2 + 1075
- Dirección IP de destino (destination) + puerto (dport):    66.66.66.66 + 80

Normalmente hay muchos procesos usando servicios de navegador en un equipo.
Lo que sucede es que el SO asigna un número de puerto superior a 1024 para cualquier nuevo proceso que use http.

En el paso (2), el router modifica la cabecera del paquete http:
- Dirección IP de origen (source) + puerto:          33.33.33.33
- Dirección IP de destino (destination) + puerto:    66.66.66.66 + 80
Para que el router pueda recibir la petición del servidor, debe cambiar la IP de origen por la suya (por la pública).
Además, el router debe contar con la información necesaria para enviársela a dicho PC.
El puerto origen del router no puede ser el mismo en todos, ya que puede haber varios equipos pidiendo lo mismo (usando http, por ejemplo).
De esta forma, ponemos un puerto que el router no haya usado todavía. Por ejemplo, el 12345.

El paquete llega correctamente al servidor y este responde con su paquete de respuesta (3):
- Dirección IP de origen (source) + puerto:          66.66.66.66 + 80
- Dirección IP de destino (destination) + puerto:    33.33.33.33 + 12345

El paquete llega sin problema al router, ya que este tenía una IP pública. El router debe enviarlo al equipo (4):
- Dirección IP de origen (source) + puerto:          66.66.66.66 + 80
- Dirección IP de destino (destination) + puerto:    192.168.1.2 + 1075
El router recibe el paquete por el puerto 12345, asociado a la petición anterior, que sabía que provenía del equipo 192.168.1.2 que enviaba por el puerto 1075.
***

En el caso de que tenemos un cliente en la parte privada, tenemos SNAT (Source Network Address Translation) o SNAPT (la P de Port, porque también cambiamos el puerto).
Luego veremos DNAT (Destination Network Address Translation)

### Tabla de traducción del router
Para hacer esto, el router tiene que tener una tabla:

IP source + sport | IP' source + sport'
 192.168.1.2:1075 |  33.33.33.33:12345

En el caso de Linux, tenemos las `iptables`, tenemos distintas tablas, cada una que se encarga de una cosa distinta.

Se llama enmascaramiento porque el que está fuera no es capaz de ver la red de dentro, no es capaz de acceder dentro.

Tenemos un problema de seguridad:
Por cada PC de dentro con una salida hacia afuera, tiene una entrada en la tabla.

Si un atacante envía paquetes al router con fuerza bruta a todos los puertos, es capaz de conseguir que entre un paquete hacia dentro, con lo que es un primer paso en un ataque, ya que es posible identificar a algún equipo de dentro de la red.
Otra forma es añadir en la tabla la IP de destino (66.66.66.66) con su dport, para que el router no busque puertos sin comprobar que la dirección que envía el paquete no sea esa.
Nos aseguramos de que alguien que simplemente escanea puertos sea incapaz de enviar un paquete a un equipo de la red.

Uno se llama NAT estricto y otro no comprueba qué IPs le hablan a través de la red pública.

## DNAT (Destination NAT)
Tenemos dentro de una red privada un equipo que funciona como servidor.
Mediante un router, la red privada se conecta a internet.
En algún lugar de internet, hay un cliente que se conecta a nuestro router (1), que este envía la información al servidor (2). El servidor responde al router (3), y este al cliente (4).

Suponiendo que el cliente es 66.66.66.66, que la pública del router es 33.33.33.33 y que la privada del servidor es 192.168.1.2

(1)
Header IP:
- IP source: 66.66.66.66:1050
- IP destin: 33.33.33.33:23456

Suponiendo que nuestro servidor funciona a través del puerto 80:
(2)
- IP source: 66.66.66.66:1050
- IP destin: 192.168.1.2:80

El servidor reenvía al router:
(3)
- IP source: 192.168.1.2:80
- IP destin: 66.66.66.66:1050

El router reenvía al cliente:
(4)
- IP source: 33.33.33.33:23456
- IP destin: 66.66.66.66:1050

### Tabla necesaria
 IP dest + dport  | IP' dest + sport'
33.33.33.33:23456 | 192.168.1.2:80

El cliente le envía un paquete a un router a través de un puerto.
Sin embargo, el router no tiene ni idea de a qué servidor va el paquete. Para ello, debemos fijar la tabla a mano en el router.
Este proceso se llama *port forwarding* (NO LLAMAR ABRIR UN PUERTO).

Como hay que configurar la tabla a mano, SNAT viene por defecto y DNAT no, hay que configurarlo en el router.
***

## Ejercicios más o menos fáciles
1. Diapositiva 30: Tenemos 30 dispositivos y direcciones privadas 192.168.0.0

Solución fácil: direcciones de clase C y suponiendo que son privadas
Red A: 192.168.0.0/24, al router la .1 y a los pcs a partir de .2
Red B: 192.168.1.0/24, los routers la .1 y .2 y a los pcs a partir de .3
Red C: 192.168.2.0/24, al router la .1 y a los pcs a partir de .2

Solución difícil: 
Hay 30 equipos (incluyen a =los routers o no?) supongamos que sí. Los rangos disponibles son: 
- Red A: 30 + 1 de red + 1 de difusión = 32. Usamos 5 bits para equipo y 27 para red.
    La dirección de red será:                       192.168.0.0/27
    La dirección de difusión (últimos 5 bits):      192.168.0.31
- Red B: 30 + 1 de red + 1 de difusión = 32. Usamos 5 bits para equipo y 27 para red. Lo haremos a continuación de la red A.
    La dirección de red será:                       192.168.0.32/27
    La dirección de difusión (últimos 5 bits):      192.168.0.63
- Red C: 30 + 1 de red + 1 de difusión = 32. Usamos 5 bits para equipo y 27 para red. Lo haremos a continuación de la red B.
    La dirección de red será:                       192.168.0.64/27
    La dirección de difusión (últimos 5 bits):      192.168.0.95

2. Tenemos un router conectado a varias redes. Usar direcciones 192.168.x.y
- Red A con 25 equipos.
- Red B con 50 equipos.
- Red C con 100 equipos.
- Red D con 200 equipos.
Ajustar máscaras de red al número de equipos.

Hay un problema que puede surgir si vamos de las chicas a las grandes. Si vamos al revés, no.

***
# Encaminamiento
Los procesos que se hacen antes de encaminar (*routing*) reciben el nombre de *prerouting* y los de después *postrouting*.
DNAT es un proceso de *prerouting*.

- Normalmente, los routers domésticos están conectados a un router llamado "pasarela del operador" por donde pasan los paquetes al exterior, para conectarnos a internet.

## Tablas de encaminamiento
Son necesarios para realizar el encaminamiento de los paquetes. 
Las tienen todos los equipos con capacidad para conectarse (PCs y routers).

Campos importantes (los no importantes entre paréntesis):
- Red destino.
- Máscara.
- Siguiente salto.
*En exámenes, indicar entre paréntesis a qué equipo nos referimos cuando ponemos las IPs*.

Puede tener campos adicionales, como:
- Interfaz de salida del equipo, puede ser redundante.
- Protocolo.
- Flags.
- Coste, coste esperado para llegar a dicho equipo, como número de saltos.

Una vez que se le asigna una IP a la tarjeta de red, se le configura automáticamente la red de destino de su red, con un salto directo.

- Rutas directas (marcadas con `*` en siguiente salto): Para llegar a redes a las que estamos directamente conectados. No es necesario realizar ningún salto, lo ponemos en la red y será recibido.
- Rutas indirectas: Para llegar a redes a las que no estamos directamente conectados. Es necesario pasar por mínimo un salto para llegar a él.
- Entrada por defecto (*default*): La red de destino es la *default* , o `0.0.0.0`. Hace referencia a cualquier red que no haya sido accesible. Al equipo en el que hacemos el siguiente salto (el que nos conecta con el exterior) le llamamos *pasarela*. No siempre hace falta.

Dada una dirección IP, para buscar su entrada en la tabla de encaminamiento, se hace la AND con la máscara de red de cada entrada de la tabla. Si el resultado coincide con la red de destino, es una entrada válida para dicha IP.
Si no hay ninguna entrada válida, se envía hacia detrás un mensaje ICMP.

- Si hay varias entradas válidas para un salto, se escoge el salto más restrictivo (ya que es probable que sea el que menos saltos tiene), aquel cuya máscara tenga más unos.
- Poner como máscara de red 0 es equivalente a una entrada por defecto.
- *localhost* tiene que estar en la tabla de encaminamiento. Su interfaz es *lo*.

Ejemplo:
          Red destino | Máscara | Sig. salto
  directa 192.168.1.0 |  /27    | \*
indirecta 192.168.1.0 |  /27    | 192.168.2.1 (Router)
 defecto    default   |  /0     | 129.168.3.1 (Router para exterior)
 
Ejemplo 2:
192.
... (del estilo 192.x...)
default 150.100.0.222

No sabemos llegar a 150.100.0.222.

##### Ejercicio de minimizar tablas de encaminamiento (saber agrupar redes)
Queremos minimizar el tamaño de las tablas de encaminamiento
Si tenemos n interfaces, como mínimo tenemos que incluir n entradas en la tabla. Este será el número a conseguir.
Tenemos:

                              /---- Red A  192.168.0.0/24
                              |
INTERNET -- R1 -- R2 -- R3 -- R4 -- Red B  192.168.1.0/24
                        |
                        \---- R5 -- Red C  192.168.2.0/24
                              |
                              \---- Red D  192.168.3.0/24
                        
Router 4: dos entradas, A, B y por defecto a R3
Router 5: dos entradas, C, D y por defecto a R3
Router 3: el mínimo son 3 entradas, la por defecto a R2 y:
    Juntar las redes A y B: 192.168.0.0/23 (hacer en binario) (Primera y última direcciones: 192.168.0.0 - 192.168.1.255)
    Juntar las redes C y D: 192.168.2.0/23 (hacer en binario) (Primera y última direcciones: 192.168.2.0 - 192.168.3.255)
    (Notemos que podemos hacerlo por cómo hemos puesto las direcciones IP. En un ejercicio, puede suceder que tengamos que primero añadir las IP y luego rellenar la tabla)
Router 2: el mínimo son 2 entras, la por defecto a R1 y:
    Juntar las superredes anteriores en una: 192.168.0.0/22 (hacer en binario) (Primera y última dirección: 192.168.0.0 - 192.168.3.255)
Router 1: la por defecto a un router de internet y la superred anterior.
 
## Encaminamiento en sí
- Las tablas se configuran a mano (encaminamiento estático) o mediante un protocolo automático (encaminamiento dinámico, ya que si un router se cae, la tabla de encaminamiento puede cambiar) (como RIP). 
- Se realiza paquete a paquete. Usando direccionamiento dinámico, puede pasar que cambie una dirección, luego que no todos los paquetes sigan la misma ruta.
- Basado en dirección de destino.

### Protocolos de intercambio de información de encaminamiento (protocolos de encaminamiento, pero teniendo en cuenta que estos no son los que encaminan) Routing Protocols
Internet se organiza en sistemas autónomos (AS, *Autonomous System*), redes muy grandes gestionadas por una misma entidad. Del orden de un país.
Cada AS se organiza de la forma que le convenga al operador. IGP (Interior gateway protocol)
Entre sistemas autónomos, se utilizan EGP (exterior gateway protocol). Sólo se utiliza un protocolo, ya que tiene que ser el mismo: BGP (Border Gateway Protocol). Permite mandar prioridades y tener en cuenta políticas. No se verá.

Dentro de un AS podemos tener distintos tipos de protocolos: RIP (Routing Information Protocol), OSPF (Open Source Path First).

#### RIP
Definida en RFC 1058, 2453, 4822.
Una cosa es la capa de la funcionalidad y otra la capa en la que se implmenta.

RIP funciona en capa de red pero se implementa en capa de aplicación (ya que usa UDP, para difusión, en puerto 520).

Cuando un router RIP se enciende y es configurado, manda un mensaje a sus vecinos cada 30 segundos, sobre la información con las rutas a las que este router sabe llegar:
- Se envía: Información de redes que conocemos, el coste y quién lo envía. RIP sólo funciona con el número de saltos, no con velocidades.
- Esta información se envía a los vecinos mediante IPs de difusión, 224.0.0.9, la escuchan todos los routers que soportan RIP (análogo con OSPF).

R1 --  R2 -- R3
|            I
|            I
R6 -- R5 -- R4

Empieza R1, diciendo que sabe llegar a su red con coste 0. De esta forma, R2 y 6 aprenden que saben llegar a la red A por coste 1.
R2 dice que sabe llegar a su red con coste 0 y a la red 1 con coste 1. R1 y R3 aprenden y ...
...
Hay que dar unas ciertas vueltas hasta que todos lo aprenden.

##### Split Horizon - Problema del infinito
Si tenemos:

PC -- R1 -- R2 -- R3 -- R4 -- R5 -- PC

En un momento dado, R2 aprende que para llegar a Red A (izquierda), es por R1 y por coste 1.
R3 aprende que para llegar a Red A voy por R2 por coste 2.

Si derepente R1 explota, R2 puede aprender de R3 que puede llegar a la Red A en 3 saltos.

A partir de 16 saltos se supone que no podemos llegar. Infinito = 16.

- Hold down: Retrasa los mensajes que nos llegan de una direccion que ya conocemos 180 segundos, esperando a que nos respondan los anteriores, si están vivos.
- Poison reverse: Si no sabemos llegar a algo, decimos que el coste es infinito.

#### OSPF
RFC 2328
Existen los mensajes:
- Hello: para hablar entre vecinos.
- Database description: Para mandar las BD que conocemos.
- Link satatus request/update/ack: Para consultar/enviar cambios.

No tiene en cuenta el número de saltos, sino que hace algo un poco más complejo. Permite definir el coste, luego lo podemos poner en base a lo que queramos. Ingeniería de tráficos.
Tiene un criterio por defecto, de forma que el coste de un enlace es el inverso del ancho de banda (de la velocidad) de dicho enlace.
Busca el camino global que minimiza la suma de todos los costes, usando Dijkstra.

Permite definir áreas, de forma que la difusión se envía en una áreas.
Permite que OSPF sea muy escalable, al contrario que RIP.

# Cabeceras
La cabecera IP tiene 20 Bytes (**IMPORTANTE**). 

TTL es tiempo de vida, time to life. Un campo de 8 bits de un número que se decrementa cada vez que pasa por un router.
Hay protocolos que se encapsulan en la parte de IP.
Si el *checksum* de un paquete indica que está mal, el dispositivo descarta el paquete.
Las cabeceras de un paquete de red son múltiplo de 32.
Con *wireshark* podemos ver paquetes por dentro.

Ver la cabecera de IP en las diapositivas.

Campos:
 Versión(V)
- Tamaño de la cabecera(LC)
- TS: es el campo encargado de marcar los datagramas para que, una vez lleguen al destino se sepa que se debe hacer una operación con ellos; en caso de que no se haga nada el campo pasa a tomar un valor correcto de forma automática.
- Longitud total del datagrama
- Identificador para conocer, en caso de fragmentación, qué paquetes son de qué datagrama y poder recomponerlo.
- Desplazamiento(offset)
- TTL: es el número de saltos máximo que puede dar un paquete en la red para evitar paquetes navegando en la red de forma indefinida. En cada salto, este campo se reduce en una unidad, si llega a cero, el paquete se descarta.
- Protocolo: contiene un identificar de algún protocolo que se usa en ese datagrama; normalmente, estos protocolos están contenidos en el protocolo IP.
- COmprobación: es un campo donde aparece el complemento a 1 del datagrama de manera que al llegar al destino se realizará la suma, luego si el resultado es todo a 1 el paqeute será correcto; en otro caso, se descarta.(El protocolo IP lo descarta pero no produce ningún mensaje de aviso a nivel de red, esto lo suele hacer ICMP si está implementado).
- Dirección IP origen del datagrama, es decir, quién lo manda.
- Dirección IP destino del datagrama, es decir, a quién se manda.
- Opciones.
- Relleno; este campo esta compuesto de tantos ceros como sea necesario para que el paquete tenga un tamaño múltiplo de 32.

# Fragmentación
Las redes no permiten paquetes de cualquier tamaño. El tamaño máximo es 2^16 bytes, aunque ninguna red suele aceptar dicho tamaño.
Las redes cuentan con MTU (Unidad Máxima de Transferencia, Maximum Transfer Unit): que nos dice cuál es el tamaño máximo de lo que podemos meter en el campo de datos de un paquete a nivel de enlace. Lo normal a meter en dicho campo es un paquete IP con sus datos. Esto es, un paquete de red.
El MTU indica cual es el tamaño máximo del paquete IP **incluyendo su cabecera**

El MTU depende del estándar de una tarjeta.
- Ethernet: 1500
- Wifi: Permite más pero el punto de acceso normalmente lo restringe a 1500.

Campos de cabecera de fragmentación:
Campo de identificación: identifica al datagrama (no al paquete), por lo que si fragmentamos un datagrama en varios paquetes, todos estos tendrán el mismo identificador.
Campo de indicadores (como more fragments): Si hay más fragmentos a enviar, poner a 1. Si no hay más detrás de este, 0.
Campo de desplazamiento (offset): Sirve para ensamblar los paquetes en el destino. Nos dice dónde hay que colocar este paquete.

Si no llegan todos los paquetes de un datagrama, el equipo lo descarta todo y debe ser una capa superior la que se encargue de solucionar el problema.

Sólo fragmentamos cuando pasamos a un MTU menor y sólo se ensamblan en el destino.

## Ejemplo
- Datagrama IP es lo que me gustaría mandar.
- Paquete IP es lo que mando.

Dado un datagrama (cabecera IP + datos)
Si tenemos 4180 bytes de datos, tendremos un datagrama de tamaño 4200 bytes (sabemos que la cabecera es de 20 bytes).
Tenemos dos redes (A y B) conectadas por una red intermedia con MTU de 1500 Bytes.

Sólo fragmentamos cuando pasamos a un MTU menor y sólo se ensamblan en el destino.

De esta forma, montamos un paquete de 1500 bytes como mucho y tenemos que poner la misma cabecera de 20 bytes en todos los paquetes, luego los datos tendrán como máximo 1480 bytes.
Crearemos a partir del datagrama los siguientes paquetes (el identificador del datagrama no varía en estos):

En el primero: cabecera de 20 bytes + 1480 bytes de datos (todavía quedan 2700)
- Identificador del datagrama.
- More fragments: 1.
- Offset: 0

En el segundo: cabecera de 20 bytes + 1480 bytes de datos (todavía quedan 1220)
- Identificador del datagrama.
- More fragments: 1.
- Offset: 1480

En el tercero: cabecera de 20 bytes + 1220 de datos
- Identificador del datagrama.
- More fragments: 0.
- Offset: 2960

## Ejemplo nº2
Si ahora tenemos:

         MTU      MTU 
A -- R1 ----- R2 ----- R3 --- B
        1500B    1000B
       
Si ahora se envian los tres paquetes anteriores por esta red, cuando los paquetes lleguen a R2 tendremos que fragmentarlos, porque todos estos tenían un tamaño mayor a 1000 bytes:
1. El primero se dividirá en dos:
- Uno de cabecera 20 + 980 datos con:  Id del datagrama, MF = 1, offset = 0.
- Otro de cabecera 20 + 500 datos con: Id del datagrama, MF = 1, offset = 980.
2. El segundo se dividirá en dos:
- Uno de cabecera 20 + 980 datos con:  Id del datagrama, MF = 1, offset = 1480.
- Otro de cabecera 20 + 500 datos con: Id del datagrama, MF = 1, offset = 2460.
3. El tercero se dividirá en dos:
- Uno de cabecera 20 + 980 datos con:  Id del datagrama, MF = 1, offset = 2960.
- Otro de cabecera 20 + 240 datos con: Id del datagrama, MF = 0, offset = 3940.

Si ahora el equipo de la red B responde con un datagrama de tamaño 4200 (luego de datos tiene 4180), se fragmentaría en el router R3 y en R2 no se fragmentaría.

# Protocolos: ARP, ICMP, DHCP
Protocolos importantes

ICMP ayuda, ARP es necesario y DHCP en la práctica es necesario.

# ARP
PC A --> R1 --> R2 --> PC B

Si tenemos un dispositivo contactando con otro, este le enviará un paquete en el nivel de enlace.
Como es a nivel de enlace, sólo se encarga de encaminar punto a punto (la capa de enlace sólo se dedica a esto).
Dicho paquete, tendrá una dirección MAC de origen y de destino.
Dichas direcciones cambian en cada reenvío que haga un equipo: (A manda a R1) (R1 manda a R2) (R2 manda a B)

En el nivel de Red, encaminamos punto a punto pero en el paquete a nivel de red tendremos:
IP origen del que envía e IP destino del destinatario. Estos parámetros no cambian en ningún salto (salvo uso de NAT).


Un equipo antes de enviar un paquete, consulta su tabla de encaminamiento y mira quién es el siguiente salto.
De esta forma, se puede conocer el siguiente salto de un equipo a otro.
Con el diagrama del tema de los datagramas (encapsulación), se entiende mejor.

Una vez el paquete llega de A, R1 sabe su dirección MAC y sabe la dirección IP de R2, pero no sabe la dirección MAC de R2.
No sabemos determinar la MAC de un equipo antes de realizar el siguiente salto.
Esto es lo que soluciona ARP (Address Resolution Protocol).
***


Yo sé que soy A y mando un mensaje ARP Request a nivel de enlace, que no sabemos a quién estamos mandando (destino FF:FF:...:FF, la direccion de difusión a nivel de enlace), preguntando con la IP que ya sabemos
 ARP es necesario El siguiente router contestará con un mensaje ARP Reply con su dirección MAC en unicast (respuesta única, no difusión), para así poder enviar el paquete a nivel de red.

Esto no se hace siempre (si no, metería mucho tráfico).
La dirección MAC que recibimos se guarda en una caché y si pasa mucho tiempo, la entrada expira (se reactiva con ARP).


ARP es a nivel de enlace.
Si los campos tienen H delante de su nombre, es relativo a hardware.
SI los campos tienen P, es relativo a Protocolo.
Operación: Request o Repply

ARP tiene un protocolo asociado, RARP (Protocolo de Resolución de Direcciones a la inversa).
ARP: Tengo esta IP y quiero saber la MAC.
RARP: Tengo esta MAC y quiero saber la IP. Es útil y precursor del protocolo BOUT, precursor de DHCP.

Cuando Internet empezó, había equipos sencilos. Solía haber un workstation (ordenador) y teníamos varios equipos con pocas características (por ejemplo, sin HDD).
Se conectaban los equipos al workstation para trabajar.
Como no tenían HDD, no podían guardar su IP. Sin embargo, disponían de tarjetas de red que guardaban la MAC.
Era necesario por tanto un protocolo que nos de una IP a partir de una MAC.

# ICMP (Internet Control Message Protocol)
Sirve en general para informar al origen de que ha habido un error.
IP no arregla cosas pero tiene este protocolo para informar y ya las capas superiores deciden si hacen algo o no.

Cuando hay una situación de error, el equipo le manda un paquete ICMP al origen con varios campos.
Es un nivel de red que se encapsula dentro de IP.

Cabecera de ICMP:
Tipo (tipo de error), código (código de error, para detallar) y campo de comprobación (que verifica si el paquete es correcto o si ha llegado mal).

Además, tenemos el caso particular de ping, que usa Echo Request y Echo Repply (8 y 0 respectivamente).
Hay varios errores típicos:
- Destino inalcanzable.
- Tiempo de vida excedido. Cuando el TTL pasa a 0.
- Sello de tiempo.

## Funcionamiento
A parte de los mensajes de ping:
- Un equipo envía Echo Request y el otro responde con Echo Repply.

ICMP informa de errores. 
Es un protocolo de red que se encapsula dentro de un protocolo de red.
Se encapsula dentro de un paquete IP y cuenta con los primeros 64 bytes del paquete que provocó el error (a tener en cuenta que dentro de esos 64, los 20 primeros son de la cabecera IP del paquete que provocó el error).
Por tanto, podemos ver la IP del equipo que detectó el error (gracias a la cabecera IP del paquete ICMP) y la IP del equipo a quien iba destinado (con la cabecera IP del paquete que generó el error, que se encuentra como dato dentro del paquete ICMP).

# DHCP (Dynamic Host Configuration Protocol)
Funciona a nivel de red pero se implementa en capa de aplicación (porque se encapsula en UDP).
Un protocolo automático para asignar direcciones IP, máscaras, pasarela por defecto e IP del servidor DNS.

Cuando llegamos a un red y no tenemos IP, la IP es 0.0.0.0.
En primer lugar, DHCP pregunta si hay un servidor de red con un mensaje *DHCP Discover*. 
- Lo primero que hace es preguntar si hay alguien. Dirección de origen: 0.0.0.0. Dirección de destino: difusión, 255.255.255.255.
- El servidor responderá con *DHCP Offer*, con el que responde que es un servidor y de paso le ofrece una dirección IP (es una oferta, no una imperativa).
- El cliente le responde con *DHCP Request*, con el que le solicita tener una determinada dirección IP (por ejemplo, si anteriormente el dispositivo se conectó a la red y guarda la IP que tubo en el pasado).
- El servidor responde con *DHCP ACK*, que es la última respuesta del servidor, con la IP definitiva.
Todos los mensajes se mandan en difusión (el servidor debe y el cliente podría hacerlo pero el estándar diche que se manda en difusión, aunque permite las dos cosas).

Además, los pares de peticiones y respuestas se etiquetan con un identificador de transacción, para que el cliente sepa que el mensaje va para él.



DHCP es un protocolo de leasing (alquiler), con lo que la IP se asigna (alquila) durante un tiempo.
- *DHCP Release* para liberar la direccion IP si el dispositivo abandona bien (no surge un error inesperado) la red.
Sin embargo, si dentro de un rato no ha habido noticias de dicho dispositivo (no ha querido renovarla), se libera.

Es posible configurar un servidor de red para que use algunas direcciones IP fijas (estáticas) para ciertos dispositivos.
