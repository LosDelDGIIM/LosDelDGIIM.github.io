# FR

Jorge Navarro Ortiz
jorgenavarro@ugr.es
Despacho 2.19, Tutorías M,X 9:30-12:30

----------------------------------------

Prácticas:
1. Encaminamiento y cortafuegos
2. Servicios básicos de red (ssh)
3. Servicios avanzados de red (apache)

Seminarios:
1. Creación de máquinas virtuales e interconectarlas
2. Diagnóstico y resolución de fallos en red
3. Problemas (3, 5, 6)
4. Creación de aplicaciones cliente/servidor

----------------------------------------

Calificaciones:
60 teoría:      final; extra por ejercicios
25 prácticas:   entrevistas y examen de prácticas
15 seminarios:  examenes

----------------------------------------
----------------------------------------
----------------------------------------
----------------------------------------

## Teoría de la presentación

---------------------------------------- Arquitectura de internet por capas ----------------------------------------

La arquitectura lógica de internet cuenta con varias capas:

Modelo TCP/IP (también está el modelo OSI)

|-------------------------
| Aplicación que hace uso de la red
|-------------------------
| Transporte (TCP / UDP)
|-------------------------
| Red (IP)
|-------------------------
| Enlace
|-------------------------
| Física
|-------------------------

(Las dos últimas implementadas en Hardware y las tres primeras en software, también llamado NOS (Network Operator System)).
Las tarjetas de red tratan de ser compatibles con el NOS (independientemente de qué tipo de tarjeta tenga, que son diferentes en los últimos dos niveles).
La asignatura trata sobre las capas altas.

En la parte de transporte podemos tener un protocolo que haga todo (como TCP) o que no haga nada (como UDP).

Definiciones:
- Un **protocolo** es el conjunto de mensajes que tenemos que enviar entre dos entes para que se entiendan.
- Un **paquete** es un conjunto de bits que cuentan con cabeceras (donde indican origen y destino, entre otros), además de la información útil.

- TCP garantiza la funcionalidad de la red, mientras que UDP no garantiza nada (intenta que lleguen los paquetes pero no intenta nada para recuperar el error).
- UDP es un clásico de protocolo útil en conversaciones de voz, ya que es esencial que los datos lleguen sí o sí aunque sean afectados por interferencias o se pierdan paquetes.

Podemos pensar que la seguridad se encuentra entre las capas de transporte y de aplicación.

---------------------------------------- Red y Transporte ----------------------------------------

El Router con el NAT (Network Address Translator) consigue que un servidor responda a una IP privada.

Un puerto identifica qué aplicación o proceso está escuchando a qué paquete.


------------------- Transporte ---------------------

Pregunta importante (SUELE CAER EN EXÁMENES):
¿Qué entendemos por congestión en la red?
Los routers que hay en el camino tienen unas colas donde van almacenando los paquetes.
Si se meten más paquetes de los que se sacan de las colas, llegamos a llenar las colas. Cuando esto sucede, los equipos intermedios descartan los paquetes nuevos.
TCP cuenta con un mecanismo para evitar esto.

En streaming, necesitamos una velocidad cte. similar a la cantidad de imagenes a transmitir por segundo.
En descargas, se intenta conseguir la velocidad máxima cada vez. El protocolo TCP cuando hay errores baja la velocidad de la descarga (control de conjestión).

Control de flujo hace que el receptor negocie con el emisor la velocidad de transmisión, para que no pierda paquetes.

---------------------------------------- Relativo al tema de seguridad ----------------------------------------

Veremos 5 aspectos de seguridad:
- Confidencialidad, cifrado.
- Autentificación, tipos de autentificación.
- Integridad (los datos no han sido modificados).
- No repudio (no podemos echarnos atrás en una transacción).
- Disponibilidad (que el servicio se encuentre disponible, no se verá).

Además de:
- Es importante el aspecto legal, cómo demostrar que una clave es de alguien, de cara a problemas legales.
- Cómo funciona el certificado digital.
- Protocolos seguros.

---------------------------------------- Aplicaciones ----------------------------------------

Paradigmas cliente/servidor, p2p.
DNS.
Servicios de correo electrónico y de páginas web.

----------------------------------------

Bibliografía: cualquiera de redes con la arquitectura TCP/IP sirve
El primero de las 5 capas por profesores, en español
El último libro de complementario es de programación, sockets y etc

Los temas son las capas
