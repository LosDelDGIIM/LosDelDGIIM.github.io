# Tema 5. Capa de aplicación.

# Introducción.
Veremos:
- Sockets.
- DNS.
- Navegación web (HTTP, HTTPS).
- Correo electrónico.
- Aplicaciones multimedia.

Lo normal en capa de aplicación es que tengamos capa de transporte (como se espera).
Al revés también: si tenemos capa de transporte (UDP o TCP), lo normal es que encima haya una capa de aplicación.

# 1. Introducción a aplicaciones de red
Hay alternativas similares: 
- como p2p (*peer-to-peer*, Skype).
- publisher/subscriber: publicadores que publican en temas. Usado en IOT.

## Cliente/Servidor
Un proceso en un equipo habla con un proceso en otro equipo, de forma que el primero hace peticiones y el segundo responde.
Servidor:
- Siempre encendido.
- IP pública y fija.

Clientes:
- Se encienden cuando quieran.
- IPs dinámicas y privadas (comúnmente).
- No hablan entre sí en general (es lo normal y si hablan entre sí hablamos de otro tipo de arquitecturas).

"Agrupados en granjas" (no entra):
En empresas solemos tener una red troncal de las que salen redes de distribución.
A la red troncal podemos agrupar todos los servidores en una misma red que distribuirlos en cada red.
En resumen, separar equipos terminales de servidores dentro de una empresa.


- Entre los procesos (de cliente y/o servidor) y la capa de transporte (gestionada por SO), tendremos una API o socket, para añadir abstracción.

## Socket
Socket: tenemos dos procesos que quieren comunicarse entre sí.
La habitual de C es BSD (Berkeley Socket Distribution), que es la que vamos a ver.

Va a intentar que sea muy parecido a la escritura y lectura de ficheros. Tendremos:
- Descriptor de fichero (un número entero que apunta a una tabla donde tenemos las estructuras de datos de los sockets).
- open, read, write, close.
Extiende la I/O para conexiones en red.

Podemos tener 3 tipos de sockets, cada uno relacionado con un tipo de conexión:
- TCP: Conexión TCP perfectamente identificada: IPsrc, IPdst, sport (source port), dport.
- UDP: (no existen conexiones) sirve para enviar y recibir lo que sea de cualquier puerto y a cualquier IP. Cada datagrama es totalmente independiente.
Ambas devuelven un paquete de aplicación (la parte de datos del nivel de transporte), no vemos ninguna cabecera.
- raw (o de bajo nivel): Un socket que permite ver cabeceras de paquetes (por ejemplo, si implementamos Source-Nat).
Si un programa no va sobre capa de transporte, usaremos un socket raw; aunque los sockets son orientados para crear cosas a nivel de aplicación.

Tenemos una tabla de sockets en el sistema operativo y cada uno apunta a una estructura que contiene:
- Familia (existen muchos tipos de sockets para otros tipos de comunicaciones, PF_UNIX para comunicar procesos dentro de la misma máquina).
- Servicio: 3 tipos: TCP (orientado a flujo, SOCK_STREAM), UDP (orientado a datagrama, SOCK_DGRAM), raw (SOCK_RAW).
- IP local.
- IP remota.
- Puerto local.
- Puerto remoto.

### Funciones
Ver transparencias.

Para decir IP dest y dport: struct sockaddr

Suponiendo un cliente y TCP:

-- Cliente -- :
s = socket();
connect(s, toaddr), Si estamos en TCP enviamos SYN, SYN + ACK, ACK. Si estamos en UDP no se hace nada (no hace falta ponerlo).

send(s, buffer)
recv(s, buffer)

close(s)

-- Servidor --:
sc (socket de control) = socket();
bind(..., puerto, ..., sc, ...), le decimos al SO que nos asigne un puerto y que esté pendiente del socket sc. Si el puerto no está libre, devuelve -1 (fallo).
listen(sc), le dice al SO que vamos a usar un socket.

while(true){
    sd = accept(sc, &fromaddr), es bloqueante, bloquea hasta que se conecte alguien (sincroniza con connect del cliente). 
        Devuelve un socket (al que llamamos de datos). El de control solo sirve para esperar conexiones. El sd es el que usamos para mandar y recibir datos a un cliente concreto.

    recv(sd, buffer)
    send(sd, buffer)

    close(sd)
}

Es un tipo de servidor iterativo (solo puede estar pendiente de un cliente a la vez).

#### UDP:
-- Cliente --:
s = socket();
sendto(s, buffer, destaddr)
recvfrom(s, buffer, sourceaddr)
close(s);

-- Servidor --:
sc = socket();
bind(..., puerto, ..., sc, ...)
listen(sc)

while(true){
    recvfrom(sd, buffer, sourceaddr)
    sendto(sd, buffer, destaddr)
}
close(sd)

#### Más funciones
write(), read(), por similitud a ficheros.

gethostbyname() Traduce nombre de dominio a IP.

Un equipo tiene un resolutor local de direcciones en /etc/hosts.
Si no aparece ahí el nombre de dominio, consulta un resolutor DNS: /etc/resolv.conf

getservbyname() Qué puerto se utiliza para cierto servicio (HTTP el 80).
getprotobyname() Cada protocolo tiene un número asociado.

Los sport y dport de las cabeceras dependen de si la máquina usa little-endian o big-endian. 
Funciones que permiten cambiar del codificado de la máquina al de la red:
hton() (h = host byte order) 
ntoh() (n = network byte order)
(s = sort)
Para cualquier campo de 2 o 4 bytes hay que hacerlo.

### Tipos de servidores
- Orientado a flujo?: TCP o UDP.
- Concurrencia?: Iterativos o concurrentes.

- El dibujo: Socket <--> Servidor significa que es UDP e iterativo:
1. Solo tenemos una flecha y un proceso, tiene que ser iterativo.
2. No tenemos socket para aceptar peticiones (no hay uno unidireccional).

- El dibujo: Socket ---> Servidor
             Socket <--> Servidor significa que es TCP e iterativo:
1. Solo tenemos una flecha para hablar con el proceso.
2. Tenemos una flecha unidireccional para aceptar conexión, hacen falta dos socket.

#### Servidores concurrentes
- Estructura maestro-esclavo para el servidor.
    Pros: podemos tener un esclavo para cada tipo de cliente.
    Contras: crea procesos extra.
- Uso de espera selectiva en el servidor.
    Contras: un mismo código para todos los clientes.
    Pros: no crea procesos extra.

***
Más tipos de servidores:
- Multiprotocolo: Servidor que gestiona un puerto UDP Y uno TCP:
    Sockets <---> Servidor
    Sockets <---> Servidor
    Sockets ----> Servidor

- Multiservicio: Servidor que está pendiente de varios puertos.

- Superservidor: (el habitual de linux es xinetd, para optimizar el pc en el uso de los puertos), (para ver los puertos de escucha: sudo netstat -tulpn ; tulipan)
    está pendiente de varios puertos y cuando llega una petición se abre un esclavo que llama a un programa y es quien atiende a dicho cliente.
    el superservidor no implementa los protocolos, está pendiente de los puertos y permite poner condiciones: permito estos puertos, estos no, ...
    una vez se acepta una petición se habre el programa que ejecuta eso.
    
    Pendiente de muchas cosas y abre el servidor correspondiente cuando haga falta.
    Está bien para cosas no muy costosas y que no estén siempre en uso.
    Apache2 puede tener esta opción (si no está standalone).

## Teoría de colas:
M/M/1:
Llegan peticiones en fraccion \lm y un servidor tarda \mu_s en procesar un elemento.

## Tipos de servicio
Para definir una aplicación, una vez definidos: (ver), entendemos bien la aplicación.
- Mensajes: Peticiones, Métodos.
- Sintaxis (tengo que enviar estos mensajes, con estos campos), semática (qué significan los mensajes y los campos)

### Tipos:
- Hay protocolos de dominio público (especificados en un RFC) y protocolos propietarios (Youtubte, Skype, ...).

- Protocolos en banda: Usa el mismo socket (puerto) para mandar información de control y los datos. Por ejemplo, HTTP: 80.
           fuera de banda: Usa control y datos por separado. Por ejemplo, FTP.
           
- Stateles: EL protocolo responde sin tener en cuenta lo que ha sucedido antes. Por ejemplo: HTTP sin cookies: Las cookies introducen un estado (recordar cosas)
- Statefull: Guarda información en estado, como el correo electrónico.

- Protocolos no persistentes: Si me descargo varias usa distintas conexiones TCP: HTTP/1.0 Se descarga el texto, analiza el texto y hace conexión TCP por cada objeto.
- Protocolos persistentes: Todos los objetos van por la misma conexión TCP: HTTP/1.1 en adelante.
***

### Tipos de campos:
- Tamaño fijo y presentes siempre (si el protocolo está sencillo).
- Campos que a veces están presentes y a veces no (definir parámetros TLV (Type-Length-Variable), de tamaño variable). El nombre de red de WIFI es variable.
***

### Requisitos de aplicaciones:
Aplicaciones inalásticas: Datos que se mandan de forma muy estable.
- Tolerancia a errores: No queremos errores.
- Exigencia de requisitos temporales (sensibles a retardo): 
    En los conversacionales son requisitos estrictos, no más de 200ms; Streaming o video online: tiempo real pero si hay retardo inicial no hay problema.
    Sistemas de tiempo real (conducir coches o cosas serias): orden de 1ms 

Aplicaciones elásticas: Las velocidades van cambiando, son las de TCP, requisitos menos estrictos.
- Interactivo (una página web); o de background.
- Demanda de ancho de banda: Hay aplicaciones que piden mucho (como las de vídeo).
- Nivel de seguridad: Depende del tipo de aplicación.

Streaming: UDP o TCP.
- UDP: es lo óptimo, para usar menos ancho de banda.
- TCP: como todo va sobre HTTP, se usa. Tenemos más ancho de banda de la cuenta.

# DNS (Domain Name Server, Servicio de Nombres de Dominio)
Similar al árbol de ficheros de un SO pero al revés:
- Existe un dominio raíz que siempre está presente (como / en linux, se llama .). Se suele omitir. 
- Después tenemos un dominio (como un directorio), (es, com, ...), se le llama TLD: Top Level Domain 
- Después un subdominio, como por ejemplo, ugr.
- Después, un recurso: ejemplo, main. Esto es una máquina.
mail.ugr.es.  : mail     ugr        es   .
                Máquina  subdominio TLD  Dominio raíz
                
Dependen del ICANN, Ministerio de Defensa de EEUU.
Ver diapositiva para ver los distintos TLD.

## Cómo resuelve
Un DNS tendrá una función similar al gethostbyname(), de forma que dentro tenemos un resolutor local en cada equipo (/etc/hosts).
Si la solución no aparece ahí, nos vamos al resolver, quien realiza la petición DNS query, que llega al servidor correspondiente.
Servidores DNS típicos: 8.8.8.8, 8.8.4.4 (Google), 150.214.204.10 (UGR)


Al definir una BD en un DNS, metemos un par (IP, nombre).
Se suelen meter los Name Servers (NS) donde decimos a qué dominios se van a delegar.
El delegado no sabe quién le ha dado esa autoridad: Si preguntamos al DNS de la ugr y no ha dado la respuesta, al único que conoce es el ., quien sabe de quién ha delegado, por lo que la respuesta baja hacia debajo para luego volver a ..   VER DIAPOSITIVA 22.

Hay dos tipos de resuluciones: recursiva e iterativa.

### Resolución iterativa
Preguntamos a DNS --> Raíz --> DNS --> otro DNS --> DNS --> ... Nuestro DNS es quien realiza todas las preguntas.

Se suele usar por dar menos coste a los raíces.

### Resolución recursiva
Preguntamos a DNS --> Raíz --> ... Va volviendo a través de los mismos.

Más rápida.

## Zonas
Dominios consecutivos que los asignamos a un DNS.

Existen distintas categorías de DNS: Autoridado o no Autoridado (SOA, Start Of Authority). Cada zona necesita un SOA.
    Primario: Tengo los datos en mi BS o Secundario: Es autoridad pero consigue los datos por transferencia (pide copia cuando arranca).
    Los DNS tienen cachés.
    
Hay 13 servidores raíz en todo el mundo y suelen ser granjas de servidores

### Tipos de respuestas
Me responden: 
- autoridad (en mi BD):
- Sin autoridad.
- No conocen eso.

### Organizamiento de la BD
Se le llama BIND y el principal servidor de DNS de linux tmb es BIND (Berkley Internet Name Domain).
Tiene un conjunto de registros, cada uno con tupla de 5 valores:
- Nombre de registro (nombre de dominio).
- Tiempo de vida (TTL): cuánto tiempo va a ser válido el registro.
- Clase: IN (de Internet).
- Tipo de registro.
- Valor de dicho registro.

#### Tipos de registro
- SOA: Tal equipo es la autoridad de esta zona.
- NS: Name Server.
- A (Address): Tal nombre tiene esta IP.
- MX (Mail Exchange): El servidor de correo electrónico se configura en el cliente, pero tenemos que saber cuál es el servidor de gmail.
      Se pregunta a un DNS por un registro del tipo MX: gmail.com, con lo que nuestro DNS enviará un mensaje al servidor de gmail.
- CNAME: Nombres canónicos (alias).
- HINFO (Host Info): Preguntar por información como SO o cosas de la máquina.
- TXT: Preguntar por información del dominio.

### Formato de mensajes
- Identificar transaccion.
- Prametro para tipo de mensaje.
- nº solicitudes / respuestas.

DNS sobre UDP en 53, aunque también sobre TCP (MUY POCO).

##### Ejemplo
ARP Req
ARP Rep
DNS Req
DNS Rep
-------- TCP
SYN X
SYN Y, ACK X + 1
ACK X + 1
-------- TCP
GET Página
200 OK Página
FIN -->
FIN <--

##### Comandos linux interesantes
cdn = Content Delivery Network
Red hecha por un proveedor muy grande con servidores muy cercanos a los usuarios.
La más conocida es AKAMAI

Pregunta DNS por cdn-dynmedia-1.microsoft.com:
nslookup cdn-dynmedia-1.microsoft.com
con el formato de la BD:
dig cdn-dynmedia-1.microsoft.com

WIFI Windows lo emula como Ethernet.

# 3. Navegación Web (HTTP)
Sobre TCP, sigue modelo cliente/servidor. 
URL: Universal Resource Locator
HTTP: puerto 80, HTTPS: 443.
Esquema: VER DIAPOSITIVA, normalmente HTTP o HTTPS, aunque pueden ser otros protocolos.
Normalmente empezaremos por dominio pero podemos decir usuario@correo (user at correo).

\# segmento: inicio de la pagina, final, ..., tiene que estar definido en el paquete HTML, para ir a trozos de la misma página.

## Páginas web estáticas / dinámicas
Si empieza por www, son estáticas: HTML y ya.
Si es otro, como wpd, son dinámicas: 
    Permiten BD, MYSQL, ... 
    Scripts: Se ejecutan en cliente: JavaScript.
             Se ejecutan en servidor: PHP.
             
## Características HTTP
Orientado a conexión, fiable, puerto 80 (configurable). 

Ejemplo clásico de aplicación sin estado (las primeras versiones): Pedimos una url, se devuelve dicha url y ya.
Se vió que hay situaciones donde queremos que cambie. Usamos cookies.

Puede ser persistente o no persistente:
- No persistente (HTTP/1.0): Utiliza distintas conexiones TCP para cada objeto (lo que añade un syn, (+2), ..., fin (+2) para cada objeto).
- Persistente (>= HTTP/1.1): Utiliza la misma conexión TCP para cada objeto.

### Peticiones / Métodos (Peticiones si hablamos de aplicaciones)
1. GET recurso version_http servidor
   user-agent: navegador que usamos
   Accept-language: lenguaje preferido

Muchas aplicaciones suelen tener un codigo XYZ mas un mensaje explicativo.

2. Respuesta típica:
   version_http XYZ mensaje_explicativo
   Server: Servidor que me lo devuelve
   Last-Modified: Últ. vez que se modificó la página

Protocolo en banda.

#### Métodos
- GET: Pide página y se devuelve.
- HEAD: Igual que GET pero solo devuelve cabecera (equipo muy sencillo y si interesa descargar).
- POST: Mandar formularios.
- PUT: Sobreescribir página en el servidor.
- DELETE: Borrarla.

#### Códigos de respuesta
XYZ:
1YZ, 2YZ: éxito
4YZ, 5YZ: errores
3YZ: incompleto: se ha iniciado una transacción que está en curso.

#### Cabeceras típicas
- Content-Type: MIME (Multipurouse Internet Mail Extensions), indica tipo de contenido.
- Content-Length: Longitud.
- Content-Encoding: Codificación.
- Date: Fecha de la operación.

Para peticiones:
- Accept: Para indicar lo que aceptamos (HTML, video, ...).
- Authorization.
- From.
- If-Modified-Since: Descargar página solo si ha sido modificada desde una fecha.
- Referer: Qué página es la que me ha referenciado a través de un hipervínculo.
- User-agent: Tipo y versión de navegador.

Para respuestas:
- Allow: Para decir qué permito (por ejemplo, put y delete no).
- Expires: en cache
- Last-modified.

### Cachés
Referido a servidores caché, servidores que se ponen en medio, con objetivo de reducir retardo. Son típicos de los ISP (Internet Service Provider).
Pedimos cosas al caché, si tiene la página la devuelve y si no la pide al servidor y se la guarda.
Aumenta bastante el rendimiento de HTTP.

- Cache-control.
- Expires.
- Last-modified.

Sirven para contenido estático.
Aunque tengamos páginas dinámicas, la gran parte del contenido es estático.

### Cookies
Ficheros concretos en un directorio del equipo.
No se debe permitir que las páginas web accedan a los archivos de una máquina.
Permitimos que ciertos ficheros sí sean modificables en un directorio específico, ficheros del estilo: variable-valor.

Surgió inicialmente para las compras electrónicas, para dar estados a un protocolo sin estados.

### Acceso restringido
Pedimos página web y devuelve 401: no autorizado.
En la siguiente enviamos los datos para la autorización.

# 4. Correo Electrónico
MUA (Mail User Agent), aplicación de mail/correo de usuario. Somos fulanito@ugr.es
    Se puede elegir TLS, SSl (si ninguno, texto plano); correo de entrada y correo de salida.
    
Mi cliente solo habla con su servidor (ugr.es), MTA (Mail Transfer Agent).

Desde el MUA al MTA usamos SMTP (Simple Mail Transfer Protocol), siempre el mismo.
Para descargar correos del MTA usamos POP (Post Office Protocol) o IMAP (Internet Mail Application Protocol). Aunque puedan hacer cosas muy parecidas, la filosofia es distinta:
- POP: borra correos del servidor y los descarga.
- IMPA: trabaja con los correos en el servidor. Nos permite conectarnos desde distintos dispositivos.
    Los servidores te dan una cuota (una cantidad máxima de correos).


Ventajas de servidores de correo: cliente no encendido siempre, sino servidor.

## Funcionamiento básico
Si enviamos un correo a otro usuario, este tendrá un MUA: menganito@gmail.com, que tendrá su MTA gmail.com
Cuando mandamos un correo por SMTP, el servidor ve que es menganito@gmail.com y hace peticion MX preguntando por servidor de gmail.com, devolviendo cuál es.
Se conecta a dicho equipo, gmail.com. Entre servidores SIEMPRE se usa SMTP, porque se mandan correos y no descargan correos.


Son protocolos en modo texto: la información que mandan es textual.
Se puede cambiar el emisor, aunque algunas aplicaciones permiten ver el paquete original, con el emisor real.

## SMTP (Simple Mail Transfer Protocol)
Sobre TCP.
Parecido a HTTP, manda códigos de error, XYZ.
Es dentro de banda (mismo puerto para msgs de control y descargar correos).
Sí tiene estados.

- Primero un saludo.
- Transmitir mensajes.
- Cierra.

Van a ser de texto, aunque también se permite mandar imágenes, texto, otros correos, ... MIME.
VER DIAPOSITIVA para funcionamiento de envío de correo electrónico.

## POP, IMAP
Sobre TCP

### MIME (Multiporpuse Internet Mail Protocol Extensions)
Permite enviar cosas que no sean solo texto.
- MIME-Version.
- Content-Transfer-Encoding.
- Content-Type.

External-body: si se ejecuta puede contener virus, nos pregunta antes de descargar (mandar información al servidor).
Multipart: Un mismo contenido trabajan juntos.
