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
