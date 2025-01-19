# Fundamentos de Redes. Seminario 1 de Prácticas.

**Autor:** José Juan Urrutia Milán
***

- **Asignatura:** Fundamentos de Redes.  
- **Curso Académico:** 2024-25.
- **Grado:** Doble Grado en Ingeniería Informática y Matemáticas.
- **Profesor:** Jorge Navarro Ortiz.
- **Descripción:** Resúmen del Seminario 1 de Prácticas.

Este seminario trata de la creación y configuración de 3 máquinas virtuales, 2 que simularán ser computadores y una tercera que simulará ser un router. Configuraremos las máquinas virtuales, las lanzaremos y cambiaremos en cada una su IP, para comprobar que están bien conectadas.

## Pasos previos

Debe tener instalado en su PC (es indiferente el sistema operativo que tenga):
- VirtualBox: [https://www.virtualbox.org/wiki/Downloads](https://www.virtualbox.org/wiki/Downloads)
  
Además, deberá tener descargado:
- La imagen del computador: [https://drive.google.com/file/d/1SWcH0rciqHgrqJOeU8WG0h4NJPSgEf_d/view?usp=drive_link](https://drive.google.com/file/d/1SWcH0rciqHgrqJOeU8WG0h4NJPSgEf_d/view?usp=drive_link)
- La imagen del router marca MicroTik: [https://drive.google.com/file/d/17K5IBVBJFrHfkXpvbA6UNQgIDgnMruYq/view?usp=drive_link](https://drive.google.com/file/d/17K5IBVBJFrHfkXpvbA6UNQgIDgnMruYq/view?usp=drive_link)
  
Abra VirtualBox e importe las dos imágenes como máquinas virtuales.

## Lo que haremos

El seminario consiste en crear dos máquinas virtuales que simulen dos computadores (`PC1` y `PC2`) y una que simule ser un router que conecta ambas (`R1`).  
  
Para ello, deberemos configurar previamente las máquinas virtuales antes de su lanzamiento mediante la interfaz que nos proporciona VirtualBox.  
Posteriormente, cambiaremos las IPs de cada máquina virtual, con el fin de obtener:
```
R1:  33.1.1.1/24
PC1: 33.1.1.2/24
PC2: 33.1.1.3/24
```
Donde `33.1.1.x` es la IP que asociamos a cada dispositivo, mientras que el número que hay detrás de `/` es la máscara de red de dicha IP (se verá en teoría).  
  
Cada máquina cuenta con una interfaz de red:
- En el caso de los computadores, esta se llama `enp0s3`.
- Mientras que en el router: `ether1`.  
  
Finalmente, comprobaremos la interconexión de los ordenadores y el router con ayuda de la aplicación `ping`.  
  
Tras esto, veremos dos aplicaciones sencillas muy útiles, como lo son `telnet` (aunque se recomienda usar `ssh`) y `winbox`.

## Clonación de máquinas virtuales

Hay dos formas de clonar máquinas virtuales:
- Clonación completa: Es una copia exactamente igual a partir de una máquina virtual ya existente, por lo que ocupará la misma memoria que la copia original.
- Clonación enlazada: Es una copia que se basa en la original, con la distinción de que sólo se almacena en disco las diferencias que esta presenta respecto a la original. Ocupa menos espacio, ya que sólo es necesario guardar las diferencias; aunque si la máquina original se destruye, deja todas las copias enlazadas inservibles.  
  
Por tanto, cuando queramos clonar muchas máquinas virtuales, usaremos la segunda opción. En este caso, usaremos la primera, ya que son máquinas virtuales muy livianas.  
  
### Práctica

Una vez importados los dos modelos de máquinas virtuales: `Modelo_PC_FR` y `MikroTik_RouterOS_CHR`, procederemos a realizar dos clones de `Modelo_PC_FR`, que llamaremos `PC1` y `PC2`; y a realizar un clon de `MikroTik_RouterOS_CHR`, al que llamaremos `R1`.

## Configuración de las redes de las VM

Una vez clonadas las máquinas virutales, accederemos a la configuración que nos ofrece VirtualBox, primero de los computadores y después del router.  
Nos dirijimos al apartado de `Red` y, en el `Adaptador 1`, cambiaremos el valor de los campos de `Conectado a:` y `Nombre:` por `Red interna` y `datos`, respectivamente.  
  
Una vez hecho este cambio en las tres máquinas, ya habremos conseguido simular una red local interna, y habremos conseguido interconectar las máquinas virtuales entre sí. Esto es como si lus hubiésemos conectado en la realidad mediante un cable de red.

## Configuración de IP en los computadores

Primero, accederemos a `PC1` y trataremos de cambiar asignarle una dirección IP en dicha red (terminado `PC1`, realizaremos el procedimiento análogo en `PC2`).  
  
- Para ello, en primer lugar hemos de iniciar sesión en los computadores. El usuario y contraseña de los computadores son `administrador` y `finisterre`.
- En una terminal, y puesto que vamos a ejecutar bastantes comandos que requieren permiso de administrador, ejecutaremos `sudo su`, seguido de la contraseña anterior, para poder ejecutar comandos en modo administrador sin necesidad de escribir `sudo` cada vez.  
- Ejecutaremos `hostname PC1` para cambiar el nombre del computador a `PC1`, y seguidamente `bash` para actualizar el prompt. Este nombre se mostrará en la terminal, y nos ayudará a identificar en qué máquina estamos trabajando. 
  
A continuación, pasaremos a consultar y cambiar la dirección IP de la máquina virtual:
- Ejecutaremos `ifconfig` y consultaremos la información relacionada con la interfaz de red `enp0s3`, donde podremos ver la IP del equipo (que probablemente no coincida con la deseada), etiquetada como `inet`.
- Para cambiar la IP desde consola y asignarle `33.1.1.2/24`, podemos usar el comando
    ```
    ifconfig enp0s3 33.1.1.2 netmask 255.255.255.0
    ```
    No obstante, este cambio solo tendrá efecto temportl mientras esté la consola en funcionamiento.
- Para cambiar la IP de forma definitiva, tendremos que modificar el siguiente archivo:
    ```
    nano /etc/netplan/01-network-manager-all.yaml
    ```
    De esta forma, tras cambiar la dirección IP en dicho fichero, ejecutaremos `netplan apply` para aplicar los cambios (estos además se mantendrán tras reiniciar la máquina).

A continuación, ejecutaremos `ifconfig` para consultar que efectivamente hemos cambiado la IP. Una vez conseguido esto, le completaremos la tabla de enrutamiento (se verá en teoría).
- La tabla de enrutamiento se podrá consultar con el comando `route -n`.
- Para completarla y añadirle la pasarela por defecto (que será la IP del router), ejecutaremos:
    ```
    route add default gw 33.1.1.1
    ```
  
Una vez hayamos repetido este procedimiento con `PC2` y, por tanto, le hayamos asignado a ambas computadores direcciones IP, podemos comprobar la conexión haciendo un `ping` de una a la otra, con el comando:
```
ping [IP]
```
En el caso de hacerlo desde `PC1` a `PC2` (se podrá hacer en ambos sentidos), ejecutaremos:
```
ping 33.1.1.3
```

Notemos que este ping podemos solo hacerlo entre las dos máquinas, ya que no hemos configurado aún el router.


## Configuración de IP en el router

De forma similar, ahora debemos asignarle una dirección IP al router.
- Para ello, en primer lugar, iniciaremos sesión en el router. El usuario es `admin`, y no tiene contraseña.
- Seguidamente, renombraremos el router a `R1`, con el comando:
    ```
    system identity set name=R1
    ```
- A continuación, estableceremos la IP correpondiente al router en la interfaz `ether1`, con el comando:
    ```
    ip address add address=33.1.1.1/24 interface=ether1
    ```
    **Nota:** En la máquina virtual del router el carácter `=` se escribe pulsando `¡` en el teclado (no es una `i`, sino una exclamación), y el carácter `/` con el `-`.  
  
    Podemos comprobar si ha surgido efecto con el comando:
    ```
    ip address print
    ```
    Podremos comprobar si todo está correcto realizando ping desde un computador al router, ejecutando `ping 33.1.1.1` desde `PC1` (por ejemplo).

- En el caso de que nos hayamos equivocado, para poder borrar la IP antes hemos de saber su identificador (`#`), que podremos consultar con el comando `ip address print`. Una vez lo tengamos, ejecutaremos:
    ```
    ip address remove numbers=#
    ```

## Telnet

Una vez ya tenemos configuradas las máquinas virtuales, podemos hacer uso de distintas aplicaciones. El primer ejemplo es `telnet`, que nos permite conectarnos a un computador remoto de forma remota (notemos que, como no pasaremos por el router, se podría haber hecho antes de configurar este). Para, desde `PC1`, conectarnos a `PC2`, ejecutaremos:
```
telnet [IP_de_PC2]
```

El servicio `Telnet` envía la información por la red en texto plano, por lo que si un tercero se encuentra escuchando la red, podría captar todos los datos enviados, incluida la contraseña para iniciar sesión en el computador remoto.  

Como opción más segura que `telnet` tenemos `ssh`, que manda la información de forma cifrada.



## Winbox

Una vez tengamos configuradas tanto las máquinas virtuales como el router, contamos con la aplicación de `winbox` para acceder a la configuración del router desde un computador mediante una interfaz gráfica. 
  
Para abrir esta, nos dirigiremos a la carpeta `/Desktop/Software` y ejecutaremos:
```
wine winbox
```
donde hemos de emplear `wine`, puesto que `winbox` es una aplicación de Windows y estamos trabajando en Linux.

Este programa nos permite acceder de forma remota al router y configurarlo de forma sencilla. Desde él, podemos consultar:
- La dirección IP del router: `IP/Adresses`.
- La tabla de enrutamiento: `IP/Routes`.
- Las interfaces de red: `Interfaces`.
- Herramientas como `Ping`: `Tools/Ping`.

## Wireshark

Por último, podemos hacer uso de `Wireshark`, un programa que nos permite capturar el tráfico de cierta interfaz de red. Para ello, ejecutamos en la carpeta `/Desktop/Software`
```
sudo wireshark
```
Tras elegir la interfaz correspondiente, podemos escuchar todos los paquetes, viendo toda la información que va por ellos.



## Cerrar máquinas virtuales

Finalmente, para cerrar las máquinas virtuales, los computadores los apagaremos como ordenadores con sistema operativo Linux:
```
poweroff
```
Respecto al router, el comando a emplear es:
```
system shutdown
```
