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
- La imagen del router: [https://drive.google.com/file/d/17K5IBVBJFrHfkXpvbA6UNQgIDgnMruYq/view?usp=drive_link](https://drive.google.com/file/d/17K5IBVBJFrHfkXpvbA6UNQgIDgnMruYq/view?usp=drive_link)
  
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
  
Finalmente, comprobaremos que todo funciona con ayuda de la aplicación `ping`.  
  
Tras esto, veremos dos aplicciones sencillas muy útiles, como lo son `telnet` (aunque se recomienda usar `ssh`) y `winbox`.

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
  
Una vez hecho este cambio en las tres máquinas, lanzaremos las tres máquinas.

## Configuración de IP en los computadores

Primero, accederemos a `PC1` y trataremos de cambiar su IP (terminado `PC1`, realizaremos el mismo procedimiento en `PC2`).  
  
- El usuario y contraseña de los computadores son `administrador` y `finisterre`, iniciaremos sesión y abriremos una terminal. Puesto que vamos a ejecutar bastantes comandos que requieren permiso de administrador, ejecutaremos `sudo su`, seguido de la contraseña anterior, para poder ejecutar comandos en modo administrador sin necesidad de escribir `sudo` cada vez.  
- Ejecutaremos `hostname PC1` para dejar claro que estamos trabajando en `PC1` (en `PC2`, `hostname PC2`), y seguidamente `bash` para actualizar el prompt.  
  
A continuación, pasaremos a consultar y cambiar la dirección IP de la máquina virtual:
- Ejecutaremos `ifconfig` y consultaremos la información relacionada con la interfaz de red `enp0s3`, donde podremos ver la IP del equipo (que probablemente no coincida con la deseada), etiquetada como `inet`.
- Para cambiar la IP desde consola, podemos usar:
```
ifconfig enp0s3 33.1.1.2 netmask 255.255.255.0
```
Para establecer como IP la `33.1.1.2/24`, aunque esto se hará temporalmente mientras esté la consola en funcionamiento.
- Para cambiar la IP de forma definitiva, tendremos que modificar el siguiente archivo (lo haremos con `nano`):
```
nano /etc/netplan/01-network-manager-all.yaml
```
(Para salir de `nano`, pulsaremos `Cntrl-O` para guardar, `Enter` para confirmar el nombre de fichero y finalmente `Cntrl-X` para salir)  
Cambiaremos la IP y ejecutaremos `netplan apply`.
- A continuación, ejecutaremos `ifconfig` para consultar que efectivamente hemos cambiado la IP.
- Finalmente, estableceremos como *gateway* por defecto la interfaz del router, con:
```
route add default gw 33.1.1.1
```
Podemos mostrar la tabla de rutas con `route -n`.  
  
Una vez que tengamos las dos máquinas montadas, podemos realizar `ping` de una a la otra, con el comando:
```
ping [IP]
```
En el caso de hacerlo desde `PC1` a `PC2`:
```
ping 33.1.1.3
```

### telnet

Ya que tenemos conectividad entre las dos máquinas, podemos hacer uso del comando `telnet` para, estando en `PC1` (por ejemplo), iniciar sesión en `PC2` y poder conectarnos a él de forma remota.  
```
telnet [IP]
```
  
`telnet` envía la información por la red en texto plano, por lo que si un tercero se encuentra escuchando la red, podría captar todos los datos enviados, incluida la contraseña para iniciar sesión en el computador remoto.  
  
Como opción más segura que `telnet` tenemos `ssh`, que manda la información de forma cifrada.

## Configuración de IP en el router

Para iniciar sesión en el router, que tiene como sistema operativo RouterOS, usamos el usuario `admin` sin contraseña (pulsar enter).  
Seguidamente, renombraremos el router a `R1`, con el comando:
```
system identity set name=R1
```
A continuación, estableceremos la IP correpondiente al router, con el comando:
```
ip address add address=33.1.1.1/24 interface=ether1
```
**Nota:** En la máquina virtual del router el carácter `=` se escribe pulsando `¡` en el teclado (no es una `i`, sino una exclamación), y el carácter `/` con el `-`.  
  
Podemos comprobar si ha surgido efecto con el comando:
```
ip address print
```
Podremos comprobar si todo está correcto realizando ping desde un computador al router, ejecutando `ping 33.1.1.1` desde `PC1` (por ejemplo).

## winbox

Una vez tengamos configuradas tanto las máquinas virtuales como el router, contamos con la aplicación de `winbox` para acceder a la configuración del router desde un computador mediante una interfaz gráfica.  
  
Para ello, nos dirigiremos a la carpeta `/Desktop/Software` y ejecutaremos:
```
wine winbox
```
(`wine` es un programa que permite ejecutar software de Windows en Linux).

## Cerrar máquinas virtuales

Finalmente, para cerrar las máquinas virtuales, ejecutaremos en los computadores:
```
poweroff
```
Y en el router:
```
system shutdown
```
