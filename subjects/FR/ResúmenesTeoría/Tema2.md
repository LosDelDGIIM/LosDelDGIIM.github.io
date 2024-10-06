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

Veremos la diferencia entre IP públicas y privadas.

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
Por tanto, la dirección de red es 192.168.1.0

Tanto la dirección de red (xxx.xxx.xxx.0) como la última de equipo (xxx.xxx.xxx.255) están reservadas.

192.168.1.255 es la dirección de difusión o broadcast para la red 192.168.1.0.

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

### Saber identificar redes

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

### Desperdicio de direcciones IP

Conforme avanzamos en jerarquías de IP, desperdiciamos más direcciones IPs.
Por ejemplo, si necesitamos 1000 equipos, necesitamos una red de clase B, con la que desperdiciamos más de 60000 direcciones.

Para ello, existe el direccionamiento sin clase: las máscaras no tienen por qué ser 8, 16 o 24.

**Subred**: Una red de 256 equipos podemos dividirla en dos redes más chicas:
- xxx.xxx.xxx.1x ... x/25
- xxx.xxx.xxx.0x ... x/25
Cada una con capacidad para 128 equipos.

Podemos juntar redes de 256 equipos (superredes), para tener una red de 500 equipos.
