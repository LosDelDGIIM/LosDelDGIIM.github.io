# Fundamentos de Redes. Seminario 2 de Prácticas.

**Autor:** José Juan Urrutia Milán
***

- **Asignatura:** Fundamentos de Redes.  
- **Curso Académico:** 2024-25.
- **Grado:** Doble Grado en Ingeniería Informática y Matemáticas.
- **Profesor:** Jorge Navarro Ortiz.
- **Descripción:** Resúmen del Seminario 2 de Prácticas.

Este seminario trata de la detección y solución de errores de red típicos en empresas.

## Herramientas de diagnóstico de fallos
Para comenzar el seminario, haremos primero un resumen de las herramientas de las que disponemos como administrador de redes para identificar y resolver proeblemas.

#### ping
- Es la herramienta más conocida.
- Usa dos paquetes de tipo ICMP, uno de tipo 8 (*Echo Request*) y otro de tipo 0 (*Echo Reply*).

El equipo origen envía un mensaje *Echo Request* al equipo destino. Si este está disponible, le resonde con un mensaje *Echo Reply*. Una vez que vuelva el mensaje al origen, se muestra por pantalla el número de secuencia, el campo TTL (*Time To Live*) y el cálculo RTT (el tiempo que el paquete tarda en salir del emisor, llegar al destino y volver).  
Al finalizar el ping, este muestra una estadística de los paquetes transmitidos, los paquetes recibidos correctamente, el porcentaje de paquetes que se ha perdido y el RTT.

- `ping -R`: Muestra la ruta de ida (del *Echo Request*) y la ruta de vuelta (del *Echo Reply*). El RTT que muestra es el total de idea y vuelta.
- `ping -n`: Muestra las direcciones IP en lugar de los nombres de dominio.
  
En ocasiones podemos pensar que en nuestro hogar el router no funciona, ya que no tenemos acceso a internet. Sin embargo, podemos ejecutar `ping 8.8.8.8` (se trata de un DNS de Google), para comprobar que efectivamente no tenemos internet (en caso de que dicho `ping` no se realice bien) o si lo que pasa es que nuestro servidor DNS (se verá en teoría) se ha caído y no nos puede traducir urls a direcciones IP.  
  
#### nslookup
Nos permite obtener la IP asociada a una url haciendo un acceso a nuestro servidor DNS: `nslookup url`.

#### traceroute
O `tracert` en Windows, muestra salto a salto el flujo de tráfico que hace un paquete UDP (el que usa `traceroute`) desde un emisor a un receptor, trazando la ruta hasta llegar al destino. Así, se puede conocer qué punto de la red está fallando.  
Se obtienen estadísticas de RTT o de latencia de red. También indica cada uno de los nodos por los que pasa el paquete hasta llegar a su destino.  
  
Se envía un paquete al destino con `TTL=1` (determina cuántos saltos puede realizar el paquete antes de devolver al emisor un paquete ICMP de tiempo excedido) y los siguientes paquetes a enviar incrementan el TTL en 1 tras recibir el mensaje ICMP de tiempo excedido anterior.
- `traceroute -I`: Usa ICMP para las pruebas (como ping).
- `traceroute -T`: Usa TCP SYN para las pruebas.

#### netsat
Muestra todos los puertos y conexiones abiertas en una máquina.  
Si la dirección de origen en un puerto de escucha es 0.0.0.0, está escuchando en todas las interfaces disponibles.  
Sin embargo, si hay una IP, entonces el puerto está abierto sólo en una interfaz específica.  
  
Al ejecutarla en terminal, se muestran direcciones IP de origen y destino, así como puertos de origen y destino.  
Los campos Recv-Q y Send-Q muestran el número de bytes pendientes de reconocimiento.  
El campo PID/Nombre del programa muestra el PID del proceso y el nombre del proceso responsable del puerto o conexión de escucha.  
  
- `netstat -tln`: Muestra los puertos que usan TCP en modo escucha con el puerto en formato número. La opción `u` (en lugar de `t`) lista los puertos que usan el protocolo UDP.
- `netstat -tn`: Muestra los puertos que usan TCP con conexiones establecidas con el puerto en formato número.  
  
Para mostrar la utilidad de `netstat`, podemos hacer uso de `netcat` o `nc`, que permite abrir puertos TCP/UDP en un host y realizar el trastreo del tráfico en esos puertos: 
```
nc -l 12345
netstat -tln
# En otra terminal:
nc localhost 12345
netstat -tn
```

#### tcpdump
Herramiento de captura de paquetes que se utiliza para solucionar problemas de conectividad de red (parecido a `wiresharck`), solo que más liviano y se ejecuta en la línea de comandos.
- `tcpdump -D`: Muestra todas las interfaces disponibles.
- `tcpdump -n -i [nombre-interfaz]`: Captura paquetes IP en dicha interfaz y muestra la información (direccion IP, puertos) en formato numérico.

#### wireshark
Software open-source de monitorización y análisis de tráfico de red, que suele usarse como analizador de protocolos. Sirve como una herramienta didáctica para el estudio de las comunicaciones y para la resolución de problemas de red.  
Se pueden visualizar los campos de cada una de ls cabeceras y capas que componen los paquetes monitorizados, proporcionando un gran abanico de posibilidades al administrador de redes a la hora de abordar ciertas tareas de análisis de tráfico.

## Descripción de laboratorio virtual
En esta ocasión, dispondremos de un laboratorio virtual que el estudiante habrá podido desgargar en el siguiente [enlace](https://drive.google.com/file/d/1kVpxTiKHUy3HXYeGowSMZNL16-e8HdBo/view?usp=drive_link).  
  
Este se compone de 3 equipos y 2 routers, que forman 3 redes de la siguiente forma:
- Una primera red (Red A), `33.1.1.0/24`, que está conformada por los equipos:
    - El router `R1`, con IP `33.1.1.1`, que se conecta mediante su interfaz `ether1`.
    - `PC1`, con IP `33.1.1.2`, que se conecta mediante su interfaz `enp0s3`.
    - `PC2`, con IP `33.1.1.3`, que se conecta mediante su interfaz `enp0s3`.
- Una segunda red (Red B), `33.1.2.0/24`, que está conformada por los equipos:
    - El router `R2`, con IP `33.1.2.1`, que se conecta mediante su interfaz `ether1`.
    - `PC3`, con IP `33.1.2.2`, que se conecta mediante su interfaz `enp0s3`.
- Una tercera red (Red C), `172.16.1.0/24`, que está conformada por los equipos:
    - El router `R1`, con IP `172.16.1.1`, que se conecta mediante su interfaz `ether4`.
    - El router `R2`, con IP `172.16.1.2`, que se conecta mediante su interfaz `ether4`.
  
Los usuarios de los PCs son `administrador` de contraseña `finisterre` y en los routers, `admin` sin contraseña (dejar el campo vacío).  
  
Una vez descrita y entendida la topología de nuestra red, procedemos a comprobar su buen funcionamiento y, en caso de no funcionar correctamente, tratar de localizar y solventar los problemas que esta pueda tener.

## Experienza del seminario
A continuación, describimos la experiencia que tuvo el grupo A2 en este seminario, tratando de identificar y solventar los errores que presentaba la red:  
  
### Identificación y resolución de error 1
Desde `PC1` (`33.1.1.2`):
- Probamos ping a `PC2` con `ping 33.1.1.3`,  para ver si funciona. Sí.
- Probamos ping a `R1` con `ping 33.1.1.1`,  para ver si funciona. Sí.
- Probamos ping a `PC3` con `ping 33.1.2.2`,  para ver si funciona. No.
- Probamos `traceroute 33.1.2.2`, no funciona.
  
Lanzamos `winbox.exe` desde `PC1`, para conectarnos a `R1` (`33.1.1.1`):
- Desde `Tools > Ping` tratamos de hacer ping a `R2` (`172.16.1.2`), funciona.  
Hemos comprobado ya que los paquetes desde `PC1` a `R1` llegan bien y que desde `R1` a `R2` llegan bien.  
  
Desde `PC3` (`33.1.2.2`):
- Probamos ping a `R2` con `ping 33.1.2.1`, para ver si funciona. Sí.  
Todas las conexiones parecen funcionar, comprobamos ahora las distintas tablas de encaminamiento.  
  
Desde `PC1` (`33.1.1.2`):
- Ejecutamos `route -n` para consultar su tabla de rutas:  
    - La primera línea dice que para acceder a cualquier IP (`0.0.0.0`), accedamos al router (`33.1.1.1`).
    - La segunda línea dice que para acceder a una IP de nuestra red (`33.1.1.0/24`), que accedamos directamente (`0.0.0.0`).  
  
Accedemos a `R1` (`33.1.1.1`) desde `PC1` (`33.1.1.2`) con `winebox`:
- Accedemos a `IP > Route`, donde vemos su tabla de encaminamiento. Nos dice que para acceder a la Red C (`33.1.2.0/24`), acceda a `R2` (`172.16.1.2`).  
  
Desde `PC3`, ejecutamos `winbox.exe` para conectarnos a `R2` (`33.1.2.1`):
- Consultamos `IP > Route` para consultar la tabla de encaminamiento. No aparece la Red A (`33.1.1.0/24`). Lo que sucedía es que el *Echo Request* llegaba correctamente a `PC3`, este devolvía la *Echo Reply* a `R2` y este no sabía a dónde enviarlo. Con `traceroute` sucedía algo similar. Añadiremos la entrada de la Red A en el router:
    - Pulsamos en `+`.
    - Añadimos como red de destino la Red A: `33.1.1.0/24`.
    - Ponemos como gateway (pasarela), el router `R1`: `172.16.1.1`.
    - *Apply* y ya debería poder funcionar todo.
  
Hacemos `ping 33.1.2.2` desde `PC1` y funciona.  
Nos hemos asegurado ya de que toda la red está funcionando.  

### Identificación y resolución de error 2
Como empleados de un empresa, queremos comprobar ahora que la aplicación que usa la red funciona correctamente. Como simulación, usaremos `telnet` como aplicación que queremos que funcione en la red.  
  
Desde `PC1` (`33.1.1.2`):
- Hacemos telnet a `PC3`: `telnet 33.1.2.2`. No funciona.
Lo que sucede es que los routers que estamos usando además de routers funcionan como firewalls, deciden qué paquetes dejan pasar a través de ellos.  
Cada router cuenta con una lista ordenada que contiene qué hacer cuando recibe un paquete de un tipo por cada interfaz. Cuando recibe un paquete, busca por orden en la tabla qué hacer con dicho paquete (en función de su tipo). Cuando encuentra la primera entrada para un paquete de dicho tipo, hace lo que diga esta primera entrada (por tanto, esta será la de mayor jerarquía).  
  
Desde `PC3`, consultamos `R2` con `winebox`:
- Consultamos su firewall, accediendo a `IP > Firewall`:
    - Las dos primeras reglas permiten el paso de paquetes ICMP (como ping).
    - La 3ª dice que cualquier paquete se desecha.
    - Las reglas 4ª y 5ª permiten usar telnet (puerto 23).
- Para solucionar el problema, arrastramos la 3ª regla hacia debajo, para que el firewall permita pasar sólo paquetes ICMP y los que usa telnet a través del puerto 23.  

### Identificación y resolución de error 3
Desde `PC1` (`33.1.1.2`):
- Volvemos a intentar hacer `telnet 33.1.2.2`. No funciona.
Resulta que además de existir firewalls en routers, existen firewalls de hosts.  
- Comprobamos firewall de `PC3` con `ufw status` (*uncomplicated firewall*).
- Vemos que sale `DENY` para el puerto 23 (el de telnet).
- Ejecutamos `ufw allow 23` para permitir el paso a telnet.  
  
Desde `PC1` (`33.1.1.2`):
- Hacemos `telnet 33.1.2.2` al `PC3`. Funciona.  
  
Desde `PC2` (`33.1.1.3`):
- Hacemos `telnet 33.1.2.2` al `PC3`. Se conecta pero pasa algo raro.

### Identificación y resolución de error 4
Lo que sucede es que son servidores que utilizan posibilidades de seguridad adicionales:  
Los tcp-wrappers son técnicas que facilitan incorporar medidas de seguridad a los servicios de red de un host.  
  
Podemos mostrar los archivos de configuración con (dentro de `PC3`):
```
ls -l /etc/hosts.*
```
Donde tenemos `hosts.allow` y `hosts.deny`.  
  
Si editamos el archivo `hosts.deny` (hacerlo con `sudo`), vemos que deniega `telnet`. Eliminamos dicha condición.  
***
  
Como resumen:
1. Había una tabla de encaminamiento mal configurada en `R2`.
2. El firewall de `R2` no nos permitía usar telnet.
3. El firewall de host de `PC3` no nos permitía conectarnos con telnet.
4. Teníamos otra restricción de seguridad sobre `PC3` para conectarnos con telnet.
