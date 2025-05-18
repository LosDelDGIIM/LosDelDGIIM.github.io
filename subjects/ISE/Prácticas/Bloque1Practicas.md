# Bloque 1: Instalación y Configuración de Sistema Operativo y Servicios

- **Autor**: Arturo Olivares Martos
- **Autor**: Miguel Ángel de la Vera


## Introducción

La virtualización es una técnica que permite crear una capa de abstracción entre el hardware y el software, facilitando la ejecución de múltiples sistemas operativos en un solo servidor físico. Puesto que en la presente asignatura no contamos con servidores físicos, emplearemos esta técnica para simular un entorno de trabajo real.

La virtualización se basa en la creación de máquinas virtuales (VMs), que son instancias independientes de un sistema operativo que funcionan como si fueran servidores físicos. Cada VM tiene su propio sistema operativo, aplicaciones y recursos asignados, lo que permite ejecutar diferentes entornos en un solo servidor físico. En una máquina virtual, se distinguen:
- **Anfitrión/*Host***: El servidor físico que ejecuta el software de virtualización.
- **Invitado/*Guest*/Virtualizado**: La máquina virtual que se ejecuta sobre el anfitrión, con su propio sistema operativo y aplicaciones.

En este documento, exploraremos la instalación de un software de máquinas virtuales (denominado aquí como **VMSW**, *Virtual Machine Software*). Algunos de ellos son *Oracle VirtualBox*o  *VMware* , por ejemplo.

Hay dos tipos de virtualización:
- **Virtualización Completa**: El sistema operativo invitado no necesita modificaciones para funcionar sobre el hardware virtualizado. Esto permite ejecutar sistemas operativos distintos al del anfitrión sin necesidad de adaptaciones.
- **Virtualización Parcial**: El sistema operativo invitado debe ser modificado para funcionar sobre el hardware virtualizado. Este tipo de virtualización es menos común y se utiliza principalmente en entornos específicos.

Los componentes principales de la virtualización se muestran en la siguiente tabla:
|Virtualización|
|------------------|
| Apliación |
| SO Invitado |
| HW Virtualizado |
| Hipervisor/*VMSW* |
| SO Anfitrión |
| Hardware Físico |


Entre las ventajas de la virtualización, encontramos:
- **Plataforma distinta a la real**: Permite ejecutar sistemas operativos diferentes al del anfitrión.
- **Seguridad**: Como todo el flujo de datos pasa por el hipervisor, se puede aplicar un control de acceso más estricto.
- **Uniformidad**: Facilita la creación de entornos homogéneos para desarrollo o pruebas.
- **Amortización de los Activos de Cómputo**.
- **Aprovisionamiento a demanda**: Permite la creación de máquinas virtuales bajo demanda, lo que es fundamental en el contexto del **cloud computing**. En vez de comprar un servidor físico y dejar de usarlo al tiempo, se paga mientras que se usa, y se puede escalar, reducir, o incluso eliminar el servicio según las necesidades del momento. Los tipos de servicios de cloud computing son:
    - Privado: está todo alojado en nuestras infraestructuras.
    - Público: está todo alojado en la nube de un proveedor público.
    - Híbrido: una combinación de ambos, donde parte de la infraestructura está en la nube pública y parte en la privada.

Entre las desventajas, podemos encontrar evidentemente que, si el proyecto tiene éxito, posiblemente los costes de un servicio de cloud computing superen los de un activo físico.


## Oracle VirtualBox

En las prácticas, emplearemos **Oracle VirtualBox**, un software de virtualización que nos permitirá crear y gestionar máquinas virtuales. Este emplea *virtualización completa*.


### Instalación de VirtualBox
- **Enlace de descarga**: [VirtualBox Downloads](https://www.virtualbox.org/wiki/Downloads).
- **Para Ubuntu**:
  ```
  sudo apt install virtualbox
  ```
- **Para Arch Linux**:
  ```
  sudo pacman -S virtualbox
  ```



A continuación, hemos de crear una máquina virtual, que simbolizará nuestro servidor. Para ello, como en cualquier ordenador, hemos de elegir el Sistema Operativo previamente. El que usaremos en las prácticas será una distribución minimal de **Rocky Linux**, una distribución de Linux basada en Red Hat Enterprise Linux (RHEL). Optamos por esta distribución por ser sencilla y por requerir pocos recursos. En el caso de necesitar documentación, se recomienda consultar la documentación de Rocky Linux, en su defecto la de CentOS o RHEL, y también podrá ser útil la documentación de Fedora.
- La ISO que se empleará, con el objetivo de emplear una versión estable y común (y poder así compartir dudas) es [esta](http://atcproyectos.ugr.es/esriie/Rocky-9.0-20220805.0-x86_64-minimal.iso), proporcionada por la UGR.
- En su defecto, se puede descargar la última versión estable de [Rocky Linux](https://rockylinux.org/download).

Creamos ahora VM. Debemos seguir la configuración por defecto, eligiendo la ISO que hemos descargado. Tras crearla, arrancamos la VM para configurarla inicialmente. En la configuración, hemos de asignar la contraseña del usuario `root`, encargado de administrar el sistema. Como consejo, y debido a que tan solo nosotros podremos tener acceso a esta VM, recomendamos emplear contraseñas sencillas como `root`, aunque esto evidentemente no es recomendable en un entorno de producción. Tras un tiempo de espera, nos pedirá que reiniciemos el sistema. Tras reiniciar e iniciar sesión con el usuario `root` para comprobar que todo ha funcionado correctamente, apagaremos la VM con el comando `poweroff`. Ya tenemos creado nuestro servidor virtualizado.


### Clonaciones y Snapshots

Antes de avanzar con la configuración del servidor, es necesario hablar de dos conceptos generales de virtualización: **clonaciones** y **snapshots**. Ambas son formas distintas de proteger la máquina virtual frente a cambios no deseados, y permiten volver a un estado anterior de la máquina. Sin embargo, tienen diferencias clave:
- **Clonaciones**: Como su propio nombre indica, crean una copia de la máquina virtual. Esta copia es independiente de la original y puede ser utilizada como una nueva máquina virtual. Las clonaciones son útiles para crear entornos de prueba o desarrollo a partir de una configuración existente.
  > En ciertos momentos de la práctica, especialmente con el RAID, esta forma de protección dará problemas. Se preferirá por tanto el uso de **snapshots**.
  - **Clonación completa**: Crea una copia exacta de la máquina virtual, incluyendo su disco duro virtual y su configuración. Esta clonación es independiente de la original y puede ser utilizada como una nueva máquina virtual.
  - **Clonación vinculada**: Crea una copia de la máquina virtual que comparte el disco duro virtual con la original. Esto significa que los cambios realizados en la clonación no afectan a la original, pero ambas máquinas comparten el mismo espacio en disco. Esta opción es útil para ahorrar espacio en disco, pero puede ser menos eficiente en términos de rendimiento.

- **Snapshots**: Guardan el estado actual de la máquina virtual, incluyendo su configuración. Esto permite volver a un estado anterior en cualquier momento.

Notemos que el uso de ambas herramientas ha de ser limitado, pues consumen una gran cantidad de recursos en memoria. Recomendamos aun así que el lector se familiarice con ambos, especialmente con los `snapshots`.


### Configuración de la red

En este apartado, vamos a simular la red en la que estarán intercomunicados el ordenador anfitrión y el servidor virtualizado. Para ello, en primer lugar hemos de crear la red. Desde el programa de VirtualBox, accedemos a los ajusted de red:
```
File -> Tools -> Network Manager
```

En esta pestaña, en el apartado de `Host-Only Networks` (más delante desarrollaremos por qué en este) configuramos la red. Tras crearla, nos fijamos en la dirección de la red asignada. En nuestro caso (y a ella haremos referencia), nuestra red es `192.168.56.0/24` y se llama `vboxnet0`. En las propiedades de la red, podemos configurar el adaptador y el Servidor DHCP.
- El adaptador debemos configurarlo manualmente, para evitar así cambios inesperados en la configuración de la red. Ahí vemos la dirección IP del *anfitrión* (en nuestro caso `192.168.56.1`). Cuando guardemos los cambios, podemos comprobar en nuestro anfitrión que está conectado a esta red nueva. Esto podremos verlo, en Ubuntu, como sigue:
  ```shell
  $ ifconfig
  ```
- El servidor DHCP debemos desactivarlo, puesto que deseamos trabajar con direcciones IP estáticas.

Llegados a este punto, tenemos configurada la red en la que está el anfitrión. Debemos ahora configurar la VM. Para ello, en las preferencias de esta, accedemos al apartado de `Network`. Como vemos, puede tener distintos tipos de adaptadores, explicados en detalle [aquí](https://www.virtualbox.org/manual/UserManual.html#networkingdetails) con una tabla muy ilustrativa. Los principales tipos de adaptadores, y los que son necesarios que sepamos, son:
- **Not Attached**: Simula una tarjeta sin conexión, como si no hubiera cable.
- **NAT**: VirtualBox emula un router que realiza NAT, luego la VM tiene acceso al Host y a Internet, pero no al revés. Ideal para navegación y descargas básicas.
- **Bridged**: Conecta la VM directamente a la red física del anfitrión, teniendo por tanto los mismos servicios que el anfitrión. Por motivos de seguridad, en la UGR no funciona puesto que hay dos direcciones IP distintas con la misma dirección MAC. Es una opción que da muchas opciones, pero es más arriesgada. En estas prácticas no la usaremos.
- **Host-Only**: Se crea una red virtual (similar a `loopback`) que conecta el anfitrión y las VMs, pero no permite acceso a Internet. Crea además una tarjeta virtual en el anfitrión y en cada VM.

Nuestra máquina por defecto tiene el adaptador NAT, por lo que tiene acceso a la red. Procedemos ahora a configurarle el adaptador `Host-Only` para que haya conexión entre el anfitrión y la VM. La red virtual la hemos creado anteriormente, y notemos que hemos configurado el adaptador del anfitrión. Ahora, en la VM, habilitamos un segundo adaptador en modo `Host-Only`, y lo conectamos a la red que hemos creado. Ya está por tanto conectado el adaptador de red. Es como si tuviésemos el anfitrión y la VM conectados a un mismo switch.

### Configuración de la VM

Arrancamos ahora la VM, e iniciamos sesión como `root` (que es el único usuario que tenemos). Aunque forme parte de la configuración por defecto, comprobamos que:
- No se ha instalado el modo gráfico. Esto se podrá comprobar puesto que no podremos hacer uso del ratón.
- Se ha instalado el servicio SSHD (con el que trabajaremos y explicaremos más adelante). Esto lo comprobamos con el comando:
  ```shell
  $ systemctl status sshd
  ```
  Hemos de ver que está activo y habilitado.


Realizamos los siguientes cambios:

1. Creamos un usuario distinto de `root` con permisos de superusuario. Para crearlo, ejecutamos el siguiente comando:
    ```shell
    $ useradd <nombre_usuario>
    ```
    Para asignarle una contraseña, ejecutamos:
    ```shell
    $ passwd <nombre_usuario>
    ```
    Este comando nos pedirá la contraseña de dicho usuario. Por último, para darle permisos de superusuario, lo añadimos al grupo `wheel` (que tiene permisos de superusuario) con el siguiente comando:
    ```shell
    $ usermod -aG wheel <nombre_usuario>
    ```
    - `a`: *Add* (añadir).
    - `G`: *Group* (grupo).

    Llegados a este punto, ya tenemos un usuario con permisos de superusuario. Por motivos de seguridad, cerramos sesión con `root` (comando `exit`) y accedemos con el nuevo usuario, que será con el que trabajaremos a partir de ahora.

    **Nota**: De aquí en adelante, no especificaremos cuándo hemos de emplear el comando `sudo` para tener permisos de superusuario. Se espera que el usuario comprenda que, si al ejecutar un comando el sistema informa de que no tiene permisos, debe anteponer `sudo` al comando.

2. Configuramos el **hostname** de la máquina virtual. Para ello, ejecutamos:
    ```shell
    $ hostnamectl set-hostname <nombre_maquina>
    ```
    Tras cerrar sesión y volver a entrar, podemos comprobar que el nombre ha cambiado.De hecho, este nombre también se encuentra en el fichero `/etc/hostname`.

3. Cambiamos ahora el prompt de la terminal. Esta se configura con el valor de la variable `PS1`. Para hacer pruebas, podemos ejecutar el siguiente comando:
    ```shell
    $ export PS1=<valor_deseado>
    ```
    No obstante, para que el cambio sea permanente, hemos de modificar el archivo `~/.bashrc` (el archivo de configuración de la terminal) añadiendo la siguiente línea al final del archivo, y ejecutar `source ~/.bashrc` para que se aplique el cambio:
    ```shell
    PS1=<valor_deseado>
    ```

    Para modificar el archivo, posiblemente el usuario desee instalar mediante `dnf` el editor de texto `nano`. Como ejemplo de prompt interesante, podemos usar el siguiente valor:
    ```shell
    PS1="[\e[1;32m\u@\H\e[1;37m-\t \w\e[0m]\$ "
    ```

    El lector podrá encontrar en internet gran cantidad de ejemplos de `PS1` para personalizar su terminal, junto con qué significa cada uno de los símbolos. Algunos a destacar, aunque animamos al lector a investigar en este aspecto, son:
    - `\u`: Nombre de usuario.
    - `\H`: Nombre de la máquina, modificado anteriormente con `hostnamectl`.
    - `\t`: Hora actual, en formato de 24 horas.
    - `\w`: Ruta completa del directorio de trabajo.
    - `\$`: Símbolo del prompt (por defecto `$` para usuarios normales y `#` para root).

4. Como cambio más importante, buscamos ahora asignarle una dirección IP estática a la máquina virtual, para poder así conectarnos a ella desde el anfitrión. Para conocer el estado actual de la máquina, podemos emplear:
    ```shell
    $ ip a        # Interfaces de red y las direcciones IP
    $ ip route    # Tabla de enrutamiento del sistema
    ```

    Para los usuarios acostumbrados a trabajar con Ubuntu, pueden ejecutar el paquete `net-tools`, y podrán usar los comandos como en dicho sistema operativo.
    ```shell
    $ dnf install net-tools
    $ ifconfig    # Interfaces de red y las direcciones IP
    $ route -n    # Tabla de enrutamiento del sistema
    ```

    Podemos además ejecutar el comando `nmcli` (*NetworkManager Command Line Interface*), y observamos que hay una interfaz (en nuestro caso `enp0s8`) a la que está conectada la máquina virtual, pero no obtiene la dirección IP. Esta es la interfaz que debemos configurar. Para ello, ejecutamos el siguiente comando:
    ```shell
    $ nmcli con add type ethernet con-name vboxnet0 ifname enp0s8 ip4 192.168.56.2/24
    $ nmcli con up vboxnet0
    ```
    Notemos que el nombre de la conexión (`vboxnet0`) y la interfaz (`enp0s8`) pueden cambiar. La dirección a asignar depende de la red y de las direcciones IP que ya estén asignadas. En nuestro caso, la dirección IP que le hemos asignado es la `192.168.56.2`. Podemos comprobar ahora, con los comandos anteriormente descritos, que ya tenemos una dirección IP asignada. Para comprobar que efectivamente no se emplea DHCP, podemos ejecutar el siguiente comando:
    ```shell
    $ nmcli -p con show vboxnet0 | grep ipv4.method
    ```
    Y si todo ha ido bien, el resultado debería ser `manual`, lo que indica que no se está usando DHCP.


Ya se ha configurado la red de la máquina virtual. Para comprobar que todo funciona correctamente, debemos ser capaces de:
1. Hacer `ping` desde el anfitrión a la máquina virtual, y vicersa.
2. Hacer `ping` desde la máquina virtual a una dirección IP pública (por ejemplo, `8.8.8.8`).
3. Conectarnos a la máquina virtual desde el anfitrión mediante SSH. Para ello, en el anfitrión, ejecutamos:
    ```shell
    $ ssh <nombre_usuario>@<ip_maquina_virtual>
    ```
    Posiblemente nos pida confirmar que somos nosotros (más adelante explicaremos en datelle el funcionamiento de SSH), pero tras introducir la contraseña debemos poder acceder sin problemas.


    Esto nos permitirá, de aquí en adelante, no trabajar con la VM en sí (ya que no es del todo cómodo), sino conectarnos a ella desde el anfitrión por SSH. De esta forma, podremos usar, por ejemplo, el portapapeles sin problema. Como consejo adicional, se recomienda al lector añadir al archivo `/etc/hosts` del anfitrión la dirección IP de la máquina virtual junto con un nombre característico (como `rockybase`). Esto le permitirá conectarse a la máquina virtual sin necesidad de recordar la dirección IP como sigue:
    ```shell
    $ ssh <nombre_usuario>@rockybase
    ```

Llegados a este punto, hemos terminado la configuración inicial necesaria para nuestro servidor. Recomendamos al lector hacer un **snapshot** de la máquina virtual, para poder volver a este estado en caso de que algo falle, o incluso clonar el estado inicial del servidor en el caso de que lo necesitemos.


## Gestión del Almacenamiento

Como administrador de sistemas, este aspecto es de vital importancia, puesto que es muy configurable y tiene muchas repercusiones. Antes de empezar a ver cómo configurarlo y a entender medidas, hemos de entender que la estructura estándar del *filesystem* de Linux es jerárquica, comportándose como un árbol que cuelga del nodo raíz `/`. Esta jerarquía se encuentra explicada [aquí](https://www.pathname.com/fhs/pub/fhs-2.3.html), pero las principales carpetas son:
- `/boot`: Archivos de arranque.
- `/root`: Directorio personal del usuario root.
- `/home`: Directorios personales de los usuarios. Dentro de este directorio, cada usuario tiene su propio subdirectorio.
- `/var`: Archivos variables, como logs o bases de datos. Suele crecer en tamaño y provocar problemas, por lo que trabajaremos en él más adelante.
- `/tmp`: Archivos temporales.
- `/etc`: Archivos de configuración del SO y de distintos servicios. Será una carpeta con la que trabajemos continuamente, y contiene información sobre los sudoers, configuración IP, puntos de montaje, etc.
- `/dev`: Archivos de dispositivos. Aquí se encuentran los dispositivos conectados al sistema, como discos duros.
- `/mnt`: Punto de montaje temporal para sistemas de archivos, de forma manual.
- `/media`: Punto de montaje temporal para sistemas de archivos, de forma automática. Es donde monta el demonio de gestor de medios de Linux, y para evitar colisiones, no se recomienda usarlo.
- `/proc`: Archivos de proceso. Aquí se encuentran los archivos que representan los procesos en ejecución en el sistema.

Una vez vista la jerarquía del filesystem, hemos de mencionar los **sistemas de ficheros** más comunes en Linux. Todos los sistemas de ficheros se encuentran en:
```shell
$ ls -la /lib/modules/<version_kernel>/kernel/fs/
```
Los más usados son `ext4` y `xfs`, ambos sistemas de ficheros transaccionales (*journalist*). Esto se refiere a que, cuando se realiza una modificación en un fichero, esta se marca como provisional y tan solo se realiza cuando se confirma que todo ha ido bien. Esto permite evitar la corrupción de datos en caso de un fallo del sistema, y es una característica muy importante a la hora de elegir un sistema de ficheros.


Por otro lado, es importante comprender la asociación entre los sistemas de ficheros y los dispositivos de almacenamiento. En Linux, cada dispositivo de almacenamiento se representa como un archivo especial en el directorio `/dev`. Cada disco duro sata se representa como `/dev/sdX`, donde `X` es una letra que identifica el disco (a, b, c, etc.). Las particiones de un disco se representan como `/dev/sdXN`, donde `N` es un número que identifica la partición (1, 2, 3, etc.). Por ejemplo, `/dev/sda1` representa la primera partición del primer disco duro. Además, para poder saber cómo arrancar, el primer sector del `sda` se denomina `MBR` (*Master Boot Record*), y contiene información sobre cómo se organizan las particiones en el disco, dónde se encuentra el gestor de arranque, etc.


Con estos conocimientos, ya podemos emplear dos comandos útiles, `lsblk` y `df`.
1. `lsblk` (*list block devices*): Muestra la jerarquía de dispositivos de bloque y sus particiones. Es útil para ver cómo están organizados los discos y las particiones en el sistema.
    ```shell
    $ lsblk
    NAME             MAJ:MIN RM  SIZE RO TYPE MOUNTPOINTS
    sda                8:0    0   20G  0 disk 
    ├─sda1             8:1    0    1G  0 part /boot
    └─sda2             8:2    0   19G  0 part 
      ├─rl_vbox-root 253:0    0   17G  0 lvm  /
      └─rl_vbox-swap 253:1    0    2G  0 lvm  [SWAP]
    sr0               11:0    1 1024M  0 rom
    ```

    Como vemos, esta máquina virtual tan solo tiene un disco duro (`sda`), que tiene dos particiones (`sda1` y `sda2`). La primera partición es está montada en `/boot`, y la segunda partición (ahora desarrollaremos lo de `lvm`) está montada en `/`. Separar `/boot` es una buena práctica, puesto que es la partición que contiene los archivos de arranque del sistema. Si algún usuario crease muchos archivos y llenase el disco, podría provocar que el sistema no arrancase. Sin embargo, al separar esta información en una partición distinta, el sistema siempre va a poder arrancar sin problema.

2. `df -h` (*disk free human-readable*): Muestra información sobre el uso del espacio en disco de los sistemas de archivos montados. La opción `-h` muestra la información en un formato legible para humanos (por ejemplo, en GB o MB).


### RAID

**RAID** *(Redundant Array of Independent/Inexpensive Disks)* es una tecnología que agrupa dispositivos de almacenamiento en un nuevo dispositivo virtual con características extendidas. Antes se denominaba `Inexpensive`, puesto que antes usar 3 discos de 1 GB era más barato que usar un disco de 3 GB. Sin embargo, hoy en día esto no ocurre y el término `Inexpensive` ha pasado a ser `Independent`, puesto que los discos son independientes entre sí. Hay distintos tipos de RAID, cada uno con sus ventajas y desventajas, aunque nosotros nos centraremos en los tipos 0, 1 y 5.

- **RAID 0** (*Striping*)
    - Combina varios dispositivos en un único dispositivo virtual cuya capacidad es la suma de los dispositivos individuales. Es decir, si hay $N$ discos de $t_i\ GB$ de almacenamiento, la capacidad total es:
    $$C = \sum_{i=1}^{N} t_i\ \ GB$$
  
    - Si hay un único error, falla el dispositivo virtual entero, por lo que hoy en día no se usa apenas.

    - El concepto de *striping* (segmentación), de debe a que se intentan colocar segmentos contiguos en dispositivos distintos, para acceder en paralelo a ellos. Esto antes se empleaba para lograr un aumento en la velocidad.

- **RAID 1** (*Mirroring*)

    - Copia idénticamente toda la información en todos los discos que forman el "espejo", proporcionando redundancia total. Si hay $N$ discos de $t_i\ GB$ de almacenamiento, la capacidad total es:
    $$C = \min \{t_1, t_2, \ldots, t_N\}\ GB$$
    - Cuando se lee un bloque, se compara el resultado entre varios discos para encontrar errores. Si un disco falla, el sistema sigue funcionando con los demás *sin pérdida de prestaciones*, por lo que es mucho más seguro frente a fallos.
    - Para evitar retrasos en la lectura/escritura, los discos suelen conectarse a buses distintos (ej. canales SATA separados).
    - Aunque es más seguro, tiene un coste elevado, puesto que se necesita un mayor número de dispositivos para almacenar la misma cantidad de datos.
    - Nomalmente se emplean $N=2$ discos de la misma capacidad.

- **RAID 5**

    - Suge como una mejora de RAID 1, combinándolo con RAID 0. Si se dispone de $N+1$ discos, cada uno de $t_i$ GB, se crea un dispositivo virtual cuya capacidad es la suma de los $N$ primeros, y el $N+1$ se reserva para proporcionar seguridad (ahora se explicará). Por tanto, la capacidad del dispositivo virtual es:
    $$C = \sum_{i=1}^{N} t_i\ GB$$

    - En el dispositivo "desperdiciado", se almacenan los *códigos de redundancia cíclica*. Si uno de los $N$ primeros dispositivos falla, en vez de fallar el sistema entero como ocurría con RAID 0, se emplea una función que, en base al código de redundancia y a la información presente en el resto de los discos, reconstruye el disco que ha fallado. 

    - En términos de costes es muy bueno, puesto que tan solo se pierde un dispositivo. No obstante, las prestaciones son peores al necesitar pasar por dicha función, puesto que en los centros grandes de servidores es muy común la caída de discos.

    - Adecuado para logs del sistema, bases de datos no críticas o entornos donde el balance entre costo y redundancia es clave.

Diferenciamos además entre RAID Hardware y Software:
- **Hardware**: Un controlador físico gestiona el RAID, lo que mejora la velocidad gracias a la controladora independiente y transparente al sistema operativo (SO). El SO ve un único disco, aunque por debajo haya varios discos en RAID.

- **Software**: Hay un driver del SO dedicado a mantener los RAIDs. El código de este se ejecuta en la CPU, por lo que bajan las rprestciones. Además, es visible al administrador del sistema, por lo que este podría comprromperlo de forma accidental.


#### Comandos para gestionar RAID

Procedemos a ver ahora cómo configurar RAID software en Linux. Para ello, en primer lugar hemos de disponer de más de un disco, por lo que hemos de virtualizarlo. Crearemos dos de ellos.

Con la VM apagada, desde los ajustes de almacenamiento, selecionamos `Add Attachment` y elegimos `Hard Disk`. En ese punto, hemos de crear en sí el disco duro y seleccionarlo. Una vez hayamos creado estos dos discos duros, tras arrancar de nuevo el distema y ejecutar `lsblk` se puede ver que hay dos discos duros más, `/dev/sdb` y `/dev/sdc`, ambos sin montar. Ya están ambos creados, pero hemos de crear el RAID.

Creamos el RAID con el siguiente comando:
```shell
$ dnf install mdadm     # Multiple Device Admin
$ mdadm --create /dev/md0 --level=1 --raid-devices=2 /dev/sdb /dev/sdc
```
- `mdadm`: Herramienta para gestionar RAID en Linux.
- `--create /dev/md0`: Crea un nuevo dispositivo RAID, llamado en este caso `/dev/md0`.
- `--level=1`: Especifica el nivel de RAID (en este caso, RAID 1). Estamos empleando ambos discos para crear un RAID 1.
- `--raid-devices=2`: Número de dispositivos en el RAID (en este caso, 2).
- `/dev/sdb /dev/sdc`: Dispositivos físicos que se usarán para crear el RAID.

Ya que podemos siempre restaurar sin problema gracias a los snapshots, podemos probar ahora a dañar el RAID y ver qué ocurre. Los comandos para ver el estado del RAID son:
```shell
$ cat /proc/mdstat
$ mdadm --detail /dev/md0
```

Procedemos entonces como sigue:
1. Hacemos una escritura correcta (directamente en el RAID), y vemos cómo no daña el dispositivo.
    ```shell
    $ echo "OK desde RAID" | sudo dd of=/dev/md0 bs=512 count=1
    $ mdadm --detail /dev/md0   # Todo OK
    ```
2. Hacemos una escritura incorrecta, escribiendo directamente en uno de los dispositivos que forman el RAID 1. Esto provoca que no se mantenga el RAID:
    ```shell
    $ echo "desincronizado" | sudo dd of=/dev/sdb bs=512 count=1 conv=notrunc
    $ dmesg | grep md0
    [    7.443760] md/raid1:md0: active with 1 out of 2 mirrors
    [    7.446534] md0: detected capacity change from 0 to 41908224
    [    7.456755] md: recovery of RAID array md0
    [   42.789320] md: md0: recovery done.
    [  124.261490] md: data-check of RAID array md0
    [  229.738934] md: md0: data-check done.
    $ mdadm --detail /dev/md0   # Todo OK
    ```
    Como podemos ver, cuando "rompemos el RAID", el sistema lo detecta de forma automática y lo resuelve, provocando que el usuario no percibe queha habido ningún problema.

3. En vez de simular que se rompe el RAID, en este caso simularemos que se cae directamente un disco duro.
    ```shell
    $ sudo mdadm /dev/md0 --fail /dev/sdb     # Simulamos que se cae el disco duro
    mdadm: set /dev/sdb faulty in /dev/md0
    $ cat /proc/mdstat
    Personalities : [raid1] 
    md0 : active raid1 sdb[2](F) sdc[1]
          20954112 blocks super 1.2 [2/1] [_U]    # [_U] indica que hay un disco caído
    ```

    Como se ha caído el disco, suponemos que hay que sustituirlo. Veamos qué ocurre:
    ```shell
    $ mdadm /dev/md0 --remove /dev/sdb
    mdadm: hot removed /dev/sdb from /dev/md0
    $ mdadm /dev/md0 --add /dev/sdb
    mdadm: added /dev/sdb
    ```

    Como vemos, simula que se ha realizado el cambio del disco duro sin apagar la máquina, por eso lo de `hot removed`. Esto es una de las ventajas de usar RAID, puesto que si un disco duro se cae, el sistema sigue funcionando sin problemas. Veamos cómo se recupera el RAID:
    ```shell
    $ cat /proc/mdstat
    Personalities : [raid1] 
    md0 : active raid1 sdb[2] sdc[1]
          20954112 blocks super 1.2 [2/1] [_U]
          [===>.................]  recovery = 18.1% (3801728/20954112) finish=1.4min speed=200090K/sec
    ```

    Si monitorizamos dicho archivo mediante el comando `watch`, podemos ver cómo se va recuperando el RAID, y cómo dicho porcentaje va subiendo, hasta que llega al 100% y se obtiene `[UU]` de vuelta.




### LVM

Un problema de las particiones tal y como las conocemos es que son particionamientos estáticos: no se pueden redimensionar sin perder datos, y si un disco se llena, no se puede ampliar sin formatear. Para evitar esto, se introdujo el concepto de **Logical Volume Manager (LVM)** (presente actualmente en todas las versiones de Linux), que introduce varias capas de abstracción. Estas son:
- **Physical Volumes (PV)**: Discos o particiones físicas, base en la que se almacenarán los datos.
- **Volume Groups (VG)**: Grupos que combinan PVs para formar un pool de almacenamiento. Se pueden entender como una especie de "cajón de sastre".
- **Logical Volumes (LV)**: Volúmenes lógicos creados desde el VG, usados como particiones flexibles. Se pueden entender como "particiones virtuales". De hecho, y debido a la abstracción, cuando se crea un LV no se sabe en qué PV terminará. Como ventaja, en cualquier momento se puede añadir un nuevo PV a cierto VG, de forma que el LV puede crecer sin problemas.

#### Comandos para gestionar LVM

Son muchos, y es por ello que es importante saber cómo acceder a ellos. Todos los comandos relacionados con PV empiezan por `pv`, los de VG por `vg` y los de LV por `lv`. Por tanto, para ver todos los comandos disponibles para cierto nivel de abstracción, podemos escribir en la terminal las siglas por las que empieza y emplear el autocompletado del tabulador.

Los comandos más importantes son los siguientes, aunque más adelante veremos paso a paso cómo se usan:
- `{pv, vg, lv}create`: Crea un PV, VG o LV.
- `{pv, vg, lv}display`: Muestra información sobre PVs, VGs o LVs.

Llegados a este punto, podemos entender la salida del comando `lsblk` que hemos visto anteriormente.
```shell
$ lsblk
NAME             MAJ:MIN RM  SIZE RO TYPE  MOUNTPOINTS
sda                8:0    0   20G  0 disk  
├─sda1             8:1    0    1G  0 part  /boot
└─sda2             8:2    0   19G  0 part  
  ├─rl_vbox-root 253:0    0   17G  0 lvm   /
  └─rl_vbox-swap 253:1    0    2G  0 lvm   [SWAP]
sr0               11:0    1 1024M  0 rom
```
Como vemos, la partición `sda2` es un PV, y dentro de este hay dos LVs (`rl_vbox-root` y `rl_vbox-swap`). Estos son dos LV que están dentro de un mismo VG (`rl_vbox`). Este VG tiene como PV la partición `sda2`, que es un disco duro físico. Todo esto se puede comprobar con los comandos `display` ya mencionados. Notemos que un mismo LV siempre va a poder referenciarse mediante dos *path* distintos, uno enlace simbólico del otro:
1. `/dev/<VG>/<LV>`.
2. `/dev/mapper/<VG>-<LV>`. Notemos que esta es la notación que ha empleado el comando `lsblk` para referirse a los LVs.


Por último, es importante destacar que se deben separar PVs de distintas características en VGs distintos.
- Por ejemplo, si introducimos en un mismo VG dispositivos que emplean RAID y dispositivos que no, entonces cuando se escriba en cierto LV, como no se sabe en qué PV está, no sabremos si se ha empleado el RAID o no.
- Si mezclamos discos SSD y HDD, el rendimiento de los SSD se verá afectado por la latencia de los HDD.

Por tanto, es recomendable crear VGs separados para cada tipo de dispositivo.

#### Integración de LVM con RAID

Como mencionamos anteriormente, es de vital importancia separar `/boot` de `/`, para evitar así que se llene el disco y no se pueda arrancar. Algunas de las carpetas de `/` que más pueden crecer en temaño, provando dicho riesgo, son `/var`o `/home`. El LVM será de gran utilidad en estos casos, puesto que permite redimensionar los volúmenes lógicos sin perder datos.


Supongamos ahora un caso práctico en el que en `/var` se almacena una base de datos que que crecerá con el tiempo y que es de vital importancia. Como es de vital importancia, querremos que esté respaldado por un RAID 1, mientras que como crecerá con el tiempo, querremos que esté gestionado por LVM. Por tanto, vamos a desarrollar cómo pasar `/var` a un RAID 1 gestionado por LVM.


1. En este caso ya tenemos creado el RAID 1, por lo que podemos proceder directamente a crear el PV.
    ```shell
    $ pvcreate /dev/md0     # Le da el mismo nombre, /dev/md0
    $ pvdisplay     # No tiene VG asociado, por lo que Allocatable=NO
    ```

2. Como el único VG que tenemos no está sobre RAID 1, hemos de separarlo en un VG distinto. Lo creamos:
    ```shell
    $ vgcreate raid1 /dev/md0
    $ vgdisplay raid1
    $ pvdisplay     # Ya tiene un VG asociado, Allocatable=YES
    ```
    Notemos que se ha creado un VG de nombre `raid1`. Tras el nombre se indica el nombre de todos los PV que lo integran, que en este caso es solo uno.

3. Ahora que tenemos el VG creado, podemos crear un LV dentro de este. En este caso, vamos a crear un LV para `/var`, que es lo que nos interesa.
    ```shell
    $ lvcreate -L 10G -n rvar raid1
    $ lvdisplay /dev/raid1/rvar
    ```
    donde:
    - `-L 10G`: Especifica el tamaño del LV (en este caso, 10 GB).
    - `-n rvar`: Especifica el nombre del LV (en este caso, `rvar`).

    Recordemos que los LVs tienen dos nombres equivalentes:
    - `/dev/raid1/rvar`
    - `/dev/mapper/raid1-rvar`

4. Llegados a este punto, ya tenemos el LV creado, es como si fuese un USB. No obstante, no está montado, no tiene sistema de archivos... En primer lugar, le damos sistema de archivos con el siguiente comando:
    ```shell
    $ mkfs.ext4 /dev/raid1/rvar
    # Otra opción.
    # $ mkfs -t ext4 /dev/mapper/raid1-rvar
    ```
    Notemos que el tipo de sistema de archivos es `ext4`, y se puede proporcionar tanto con el parametro `-t` como con el comando `mkfs.ext4`.

5. Ahora que tenemos el LV creado y formateado, podemos montarlo. Para ello, y usando el directorio `/mnt` como punto de montaje, ejecutamos:
    ```shell
    $ mount /dev/mapper/raid1-rvar /mnt
    ```

    Se puede emplear el comando `mount` para ver los dispositivos montados.

6. Ahora, tan solo faltaría copiar el contenido de `/var` en `/mnt`. No obstante, como `/var` es un directorio que está en uso constante por el sistema (logs, servicios activos), una copia directa como `cp -a /var/* /mnt` podría perder datos escritos durante el proceso. Para evitarlo, se introduce el concepto de los modos de funcionamiento del sistema Linux. Hay distintos modos:
   - Modo 0 (*Halt*): Apaga el sistema.
   - Modo 1 (*Single-user*): Modo de mantenimiento. Expulsa a todos los usuarios y detiene procesos no esenciales (incluido servicios de red). Es el modo que nos interesa para que no se esté escribiendo en `/var` mientras lo copiamos.
   - Modo 2 (*Multi-user*): Modo normal, multiusuario, pero sin acceso a la red.
   - Modo 3 (*Extended multi-user*): Modo normal, multiusuario, pero en este caso con acceso a la red. No tiene GUI, tan solo acceso por consola.
   - Modo 5 (*Graphical*): Igual que el modo 3, pero sí tiene GUI.
   - Modo 6 (*Reboot*): Reinicia el sistema.

    Para saber en qué modo estamos, podemos ejecutar el siguiente comando:
    ```shell
    $ systemctl status
    ```

    Para cambiar al modo de mantenimiento, ejecutamos:
    ```shell
    $ systemctl isolate runlevelN.target
    ```
    donde `N` es el número del modo al que queremos cambiar.
    
    Por último, para saber qué modo de funcionamiento tiene el sistema por defecto, podemos ejecutar el siguiente comando:
    ```shell
    $ systemctl get-default
    multi-user.target
    ```
    En este caso, el sistema arranca en modo multiusuario, que es el modo por defecto. Si quisiéramos cambiarlo, podríamos ejecutar el siguiente comando:
    ```shell
    $ systemctl set-default runlevelN.target
    ```
    donde `N` es el número del modo al que queremos cambiar. Esta información del modo por defecto se almacena en `/etc/systemd/system/default.target`, que es un enlace simbólico a la unidad de destino por defecto.
    
    
    En nuestro caso, cambiamos al modo de mantenimiento y, tras comprobarlo, copiamos el contenido de `/var` en `/mnt`:
    ```shell
    $ systemctl isolate runlevel1.target
    $ systemctl status
    $ df -h       # Comprobamos USED de /dev/mapper/raid1-rvar
    $ cp -a /var/* /mnt/
    $ df -h       # Comprobamos USED de /dev/mapper/raid1-rvar, y vemos que efectivamente se ha escrito.
    ```

7. Ahora que tenemos el contenido de `/var` en `/mnt`, borramos `/var` (por si acaso lo movemos a `/var_old`):
    ```shell
    $ mv /var /var_old
    $ ls -la /    # Comprobamos que efectivamente se ha borrado
    ```

8. Creamos ahora `/var`, y montaremos el LV en `/var`:
    ```shell
    $ mkdir /var
    $ umount /mnt/
    $ mount /dev/mapper/raid1-rvar /var
    $ lsblk
    $ df -h
    ```

    Efectivamente ya estaría montado `/var` en un LVM sobre RAID 1, que es lo buscado. No obstante, esto es un montaje temporal, y al reiniciar el sistema se perderá.
    
9. Para evitar que esto ocurra, hemos de añadir el montaje a `/etc/fstab`, que es el archivo que contiene la información sobre los sistemas de archivos montados. Para ello, editamos el archivo `/etc/fstab` y añadimos la siguiente línea:
    ```shell
    /dev/raid1/rvar  /var  ext4  defaults  0  0
    ```
    El contenido de cada campo se puede consultar fácilmente con `man fstab`. Estos son:
   - **Device**: Nombre o UUID del dispositivo (ej. `/dev/sda1`).
   - **Mount Point**: Directorio donde se monta (ej. `/mnt`).
   - **File System Type**: Tipo de sistema (ej. `ext4`).
   - **Options**: Opciones de montaje (ej. `defaults`).
   - **Backup Operation**: 1 para respaldo (obsoleto), 0 para ninguno.
   - **FS Check Order**: Prioridad de verificación al arrancar (0 para no verificar, 1 para el sistema raíz, 2 para otros sistemas). En el caso de que todos tengan la misma prioridad, se montan por orden de aparición en el archivo.
   
   Es especialmente relevante el último caso si todos tienen la misma prioridad. Es importante añadir la línea mencionada después del punto de montaje de `/rl_vbox-root`, que se monta en `/`, puesto que si no, no podremos montar en `/var` al no estar montado `/`.

    Probamos ahora a desmontar y montarlo de forma automática.
    ```shell
    $ umount /var
    $ systemctl daemon-reload
    $ mount -a
    $ df -h
    ```

    Si llegados a este punto vemos que efectivamente el LV está montado en `/var`, podemos garantizar que se montará de forma automática al reiniciar el sistema. Hemos pues logrado el objetivo buscado, que era montar `/var` en un RAID 1 gestionado por LVM.


<!-- //TODO: Por aquí. Revisar lo de ADE desde RAID -->

## Acceso Seguro al Servidor

**iptables** es una utilidad de Linux para configurar el firewall a nivel de kernel. En Rocky Linux, usamos **firewalld**, un frontend más sencillo, gestionado mediante el comando `firewall-cmd`. Este se ejecuta como un servicio y podemos activarlo o verificarlo así:
```
sudo systemctl enable --now firewalld
sudo systemctl status firewalld
```

### Comandos básicos de `firewall-cmd`
- `firewall-cmd --state`: Muestra el estado del firewall.
- `firewall-cmd --reload`: Recarga la configuración (necesario tras cambios permanentes).
- `firewall-cmd --list-all`: Lista la configuración actual.
- `firewall-cmd --runtime-to-permanent`: Guarda los cambios temporales como permanentes.

## Zonas

Las **zonas** son conjuntos de reglas que se aplican según el nivel de confianza de la red. Ejemplo: conexiones Ethernet más confiables que Wi-Fi. Resumen de las principales zonas:

- **drop**: Bloquea todo el tráfico entrante sin respuesta; solo permite saliente.
- **block**: Similar a drop, pero rechaza con mensaje ICMP.
- **public**: Para redes públicas no confiables; permite conexiones selectivas.
- **external**: Para redes externas con NAT; oculta la red interna.
- **internal**: Para redes internas de confianza moderada.
- **dmz**: Para equipos aislados en una DMZ.
- **work**: Para redes de trabajo; confianza media.
- **home**: Para entornos domésticos; confianza alta.
- **trusted**: Máxima confianza; todo permitido (usar con precaución).

Normalmente usaremos **trusted**, **home** o **public**. Para ver la zona por defecto:
```
firewall-cmd --get-default-zone
```

### Gestión de zonas
- Cambiar zona por defecto: `firewall-cmd --set-default-zone=[zona]`
- Añadir interfaz a zona: `firewall-cmd --zone=[zona] --add-interface=[dispositivo]`
- Cambiar zona de interfaz: `firewall-cmd --zone=[zona] --change-interface=[dispositivo]`
- Eliminar interfaz de zona: `firewall-cmd --zone=[zona] --remove-interface=[dispositivo]`

## Puertos

Para servicios comunes como **SSH**, **FTP** o **HTTPS**, es mejor gestionarlos como servicios, no como puertos. Comandos útiles:

- `firewall-cmd --list-ports`: Lista puertos abiertos (alternativa: `nmap`).
- `firewall-cmd --zone=public --add-port=[numero]/[tcp/udp]`: Abre un puerto.
- `firewall-cmd --zone=public --remove-port=[numero]/[tcp/udp]`: Cierra un puerto.

### Gestión de servicios
- Lista de servicios disponibles: `firewall-cmd --get-services`
- Servicios activos: `firewall-cmd --list-services`
- Añadir servicio: `firewall-cmd --zone=public --add-service=[servicio]`
- Eliminar servicio: `firewall-cmd --zone=public --remove-service=[servicio]`

## Restricción de Acceso

Para un servidor no público (ej. acceso SSH restringido), hay dos enfoques:

### 1. Zona restrictiva con IP específica
1. Usa una zona como **trusted** y asigna tu interfaz.
2. Añade el servicio SSH: `firewall-cmd --zone=trusted --add-service=ssh`.
3. Restringe acceso a una IP o rango:
```
firewall-cmd --permanent --zone=trusted --add-source=192.168.1.0/24
```
(Cambia `--add-source` por `--remove-source` para revertir).

### 2. Combinación de zonas (público + privado)
Para un servidor con servicios públicos (ej. web) pero SSH restringido:

- **Zona public**: Interfaz asignada, con servicios como HTTP/HTTPS:
```
firewall-cmd --zone=public --add-service=http
firewall-cmd --zone=public --add-service=https
```
- **Zona trusted**: Solo para SSH desde un rango IP:
```
firewall-cmd --zone=trusted --add-source=192.168.1.0/24
firewall-cmd --zone=trusted --add-service=ssh
```
- Elimina SSH de la zona pública:
```
firewall-cmd --zone=public --remove-service=ssh
```

### Nota
Si pierdes acceso, reinicia el servidor desde el panel de control del VPS y ajusta la configuración. Guarda cambios con `--runtime-to-permanent` solo tras probar.

### Nmap
Nmap es una herramienta que permite explorar redes y hacer auditorías de seguridad. Está diseñado para escanear rápidamente redes grandes, tiene muchas posibilidades y configuraciones así que vamos a dar algunos comandos que pueden resultar útiles en nuestro caso de uso:

```
sudo nmap -v direccion.es
nmap -sS xxx.xxx.xxx.xxx/24
```
La primera activa el modo verbose para escanear puertos reservados (TCP) en la máquina dada y el segundo lanza un escaneo SYN hacia las 256 IPs de la red dada

## Ejercicio Opcional

### Nginx 
Nginx es un servidor que podemos usar para montar un servidor web o un reverse proxy.

Para instalar Nginx en Rocky Linux, ejecutaremos el siguiente comando que usa el gestor de paquetes dnf (recomendable hacer update antes)
```
sudo dnf install nginx
```

Una vez instalado, ejecutaremos el siguiente comando para empezar el servidor web:

```
sudo systemctl enable nginx
sudo systemctl start nginx
```
Con esta configuración ya se iniciará nginx cada vez que reiniciemos la máquina virtual, deberemos tener en cuenta en el firewall este servicio:

```
sudo firewall-cmd --permanent --add-service=http 
sudo firewall-cmd --permanent --list-all
```
De otra forma podemos hacer que la configuración actual sea permanente mediante:
```
sudo firewall-cmd --runtime-to-permanent
```
Que deberá incluir en la linea services: http. Además deberemos recargar la configuración para hacer el servidor accesible a visitantes externos
```
sudo firewall-cmd --reload
```
Además se sugiere el siguiente comando para saber nuestra ip publica y accediendo al servidor:
```
curl -4 icanhazip.com
```
### Apache

Veamos ahora la configuración equivalente para un servidor en apache:
```
sudo dnf -y install httpd
mv /etc/httpd/conf.d/welcome.conf /etc/httpd/conf.d/welcome.conf.org
vi /etc/httpd/conf/httpd.conf
```
Ahora cambiaremos las siguientes líneas:

- ServerAdmin (Pondremos el correo del administrador)
- ServerName (Pondremos el nombew o dirección del servidor)
- Options (Quitaremos los índices)
- AllowOverride (All)
- DirectoryIndex (index.html index.php index.cgi (Según lo queramos configurar nosotros))

```
systemctl enable --now httpd
```
Ahora el firewall igual que antes:
```
sudo firewall-cmd --permanent --add-service=http 
sudo firewall-cmd --reload
sudo firewall-cmd --permanent --list-all
```

Podemos probarlo ahora creando una página web en /var/www/html/index.html 
```
<!DOCTYPE html>
<html>
    <body>
        <h1>Bienvenidos a la Web de [Tu Nombre y Apellido] en Prácticas ISE</h1>
    </body>
</html>
```

## Ejercicio opcional
Eligiremos uno de anteriores programas, ejecutaremos el procedimiento dado para iniciar el servidor y editaremos el archivo index.html para que muestre:

Bienvenidos a la Web de <Nombre y Apellido> en Prácticas ISE

Para comprobar que está bien realizado, podemos tanto entrar a la página web como escanear los puertos sobre el servidor y comprobar que muestra ssh y el de http

# SSH y Criptografía

## SSH

SSH (Secure Shell) es una aplicación de terminal remoto seguro que reemplaza soluciones antiguas como Telnet, donde tanto el inicio de sesión como la sesión se transmitían en texto plano, sin cifrado. En SSH, tanto el proceso de autenticación como la sesión están protegidos mediante cifrado.

- **Uso básico**: `ssh usuario@ip/nombreDominio`.
- **Ventaja**: Utiliza varias técnicas criptográficas para garantizar seguridad.
- **Nota**: El término SSH puede referirse tanto al cliente como al servicio. Para el servicio, a menudo se usa `sshd` (demonio de SSH). OpenSSH es la implementación más común y segura.

### Servicios incluidos en OpenSSH
- **Operaciones remotas**: `ssh` (conexión), `scp` (copia segura), `sftp` (transferencia de archivos segura).
- **Gestión de claves**: `ssh-add`, `ssh-keysign`, `ssh-keyscan`, `ssh-keygen`.
- **Lado del servidor**: `sshd`, `sftp-server`, `ssh-agent`.

### Configuración recomendada
- Limitar el acceso por contraseña al usuario `root`.
- Cambiar el puerto por defecto (por ejemplo, de 22 a otro mayor a 1024).
- Actualizar la configuración del firewall (`firewalld`) tras cambiar el puerto.
- Automatizar comandos remotos usando claves simétricas y asimétricas.

---

## Repaso rápido de criptografía y seguridad

### Algoritmos más comunes

#### Llave simétrica
- **Definición**: Usa un secreto compartido entre las partes.
- **Características**:
  - Muy eficiente computacionalmente.
  - Ideal para ciertas circunstancias.
- **Algoritmo más usado**: DES (Data Encryption Standard), aunque hoy se considera obsoleto; AES (Advanced Encryption Standard) lo ha reemplazado ampliamente.
- **Problema**: 
  - Escalabilidad limitada.
  - Solución parcial: Llaves por pares, pero sigue siendo ineficiente a gran escala.
- **Solución**: Esto motivó el desarrollo de algoritmos de llave asimétrica.

#### Llave asimétrica (clave pública - privada)
- **Definición**: Cada entidad tiene dos claves:
  - **Pública**: Compartida con todos.
  - **Privada**: Secreta y personal.
- **Problema**: Requiere obtener las claves públicas de los interlocutores, pero al ser públicas, esto es manejable.
- **Algoritmo principal**: RSA.
- **Desventaja**: Alto costo computacional.

#### Hash
- **Definición**: Genera un valor único (hash) a partir de datos.
- **Ejemplo**: Familia SHA (Secure Hash Algorithm), como SHA-256.
- **Características de un buen hash**:
  - Un pequeño cambio en los datos produce un hash completamente diferente.
  - No es reversible (unidireccional).

### Identidad y firma digital
- **Garantía**: Mediante firma digital.
- **Proceso**:
  1. Calcular el hash de la información.
  2. Cifrar el hash con la clave privada del emisor.
- **Verificación**:
  1. El receptor descifra la firma con la clave pública del emisor.
  2. Compara el hash recibido con el calculado.
  - **Resultado**: Confirma integridad y autenticidad.

### Autoridades de certificación
- **Función**: Validan la correspondencia entre claves y personas/entidades.
- **Ejemplo (España)**:
  1. Generación de claves pública y privada.
  2. Envío de la clave pública a la FNMT.
  3. Validación presencial ante un funcionario.
  4. Emisión de un certificado por la FNMT.
- **Contenido del certificado**:
  - Datos personales.
  - Información adicional.
  - Firmado con hash y clave privada de la FNMT.
- **Formato común**: X.509.

### Cadena de certificación
- **Funcionamiento**: Certificados firmados recursivamente hasta un certificado raíz.
- **Confianza**: Basada en claves públicas preinstaladas en el software.
- **Visualización**:
  1. Clic en el candado del navegador.
  2. "Más información" > Ver certificado.
  3. Seguir la cadena hasta el raíz (Configuración > Certificados).

---

## Cómo funciona SSH

SSH combina criptografía simétrica y asimétrica para garantizar confidencialidad y autenticación.

### 1. Confidencialidad de la comunicación
- **Proceso**:
  1. El cliente inicia `ssh usuario@ip`.
  2. El servidor envía su clave pública.
  3. El cliente cifra la contraseña con esa clave pública y la envía.
  4. El servidor verifica la contraseña en su base de datos y responde.
- Al aceptar, la clave se guarda en `~/.ssh/known_hosts` para futuras conexiones.

- **Cifrado de la sesión**:
1. El servidor envía su clave pública.
2. El cliente genera una clave de sesión (secreto simétrico), la cifra con la clave pública del servidor y la envía.
3. Ambos usan esta clave simétrica para el resto de la comunicación, reduciendo el costo computacional.

- **Nota**: La criptografía asimétrica se usa solo para autenticación e intercambio inicial; luego se pasa a simétrica por eficiencia.

### 2. Acceso sin contraseña (autenticación por claves)
- **Proceso**:
1. El servidor tiene una base de datos de claves públicas en `~/.ssh/authorized_keys`.
2. Al conectar, el servidor envía un "challenge" (mensaje aleatorio).
3. El cliente firma el challenge con su clave privada y lo devuelve.
4. El servidor verifica la firma con la clave pública del usuario y, si es correcta, permite el acceso.

- **Generación de claves**:
```
ssh-keygen -t rsa -b 4096
```
- Genera `id_rsa` (privada) y `id_rsa.pub` (pública) en `~/.ssh/`.
- Se recomienda proteger la clave privada con contraseña.

- **Envío de clave pública al servidor**:
```
ssh-copy-id usuario@ip
```
- Añade la clave pública a `~/.ssh/authorized_keys` en el servidor tras ingresar la contraseña por última vez.

- **Uso**: Ahora se puede conectar sin contraseña:
En el siguiente ejercicio aplicaremos estos conceptos.

## Ejercicio opcional

### Cambiar el puerto de SSH
Editamos el archivo de configuración de `sshd`:
```
sudo vi /etc/ssh/sshd_config
```
- Buscamos la línea `Port 22` y la sustituimos por un puerto mayor a 1024, por ejemplo, `2025`:
- Verificamos en `/etc/services` que el puerto no esté en uso por otra aplicación.

Actualizamos el firewall:
```
sudo firewall-cmd --permanent --remove-service=ssh
sudo firewall-cmd --permanent --add-port=2025/tcp
sudo firewall-cmd --reload
sudo systemctl restart sshd
```
## Configurar acceso por clave pública
Generamos un par de claves en el cliente usando RSA (Podríamos haber usado cualquier otro método, por ejemplo para GitHub se suele usar ed25519)
```
ssh-keygen -t rsa -b 4096
ssh-copy-id -p 2025 usuario@<IP-del-servidor>
```
- Sustituye `usuario` por el nombre del usuario remoto y `<IP-del-servidor>` por la dirección IP real.

### Validación
Comprobamos la configuración ejecutando un comando remoto:
```
ssh -p 2025 usuario@<IP-del-servidor> "ls -la /"
```
- Esto debería mostrar el contenido completo del directorio raíz (`/`) sin pedir contraseña.

### Seguridad adicional (opcional)
Para limitar el acceso por contraseña y al usuario `root`, editamos `/etc/ssh/sshd_config`:
```
PermitRootLogin no
PasswordAuthentication no
```
Reiniciando el servicio podremos comprobar que ya no se puede acceder mediante contraseña.

## Ansible
Ansible es una herramienta que automatiza la gestión remota de sistemas y controla su estado deseado.
