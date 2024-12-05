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
- Existe un dominio raíz que siempre está presente (se llama .) se suele omitir.
- Después tenemos un dominio (como un directorio), (es, com, ...), se le llama TLD: Top Level Domain 
- Después un subdominio, como por ejemplo, ugr.
- Después, un recurso: ejemplo, main. Esto es una máquina.
mail.ugr.es.


