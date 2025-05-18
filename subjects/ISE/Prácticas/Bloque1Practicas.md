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
    Este comando nos pedirá la contraseña de dicho usuario. Por último, hemos de darle permisos de superusuario. Todo esto se regyla en archivo `/etc/sudoers`, que define qué usuarios tienen permisos de superusuario. De hecho, vemos que:
    ```shell
    $ sudo cat /etc/sudoers
    ## Sudoers allows particular users to run various commands as the root user, without needing the root password.
    ##
    ## ...
    ## 
    ## This file must be edited with the 'visudo' command.
    ```

    El mismo documento indica que, para editarlo, hemos de usar el comando `visudo`. Si abrimos dicho archivo con `nano` (previamente el lector deberá instalarlo con `dnf`), veremos que hay una alerta en rojo que nos indica que no se debe editar con un editor de texto normal. Esto se debe a que `visudo` comprueba la sintaxis del archivo antes de guardarlo, evitando así errores que podrían dejar al sistema sin acceso a superusuario. Por tanto, si necestásemos editarlo (no lo necesitaremos ahora), lo haremos con el siguiente comando:
    ```shell
    $ visudo
    ```

    En el archivo, tenemos las siguientes líneas:
    ```shell
    ## Allows people in group wheel to run all commands
    %wheel	ALL=(ALL)	ALL

    ## Same thing without a password
    # %wheel	ALL=(ALL)	NOPASSWD: ALL
    ```

    La primera línea indica que el grupo `wheel` (sabemos que es un grupo puesto que va precedido de `%`) tiene permisos de superusuario para ejecutar todos los comandos, pero ha de introducir la contraseña. La segunda línea (que está comentada para dehabilitar esa opción por seguridad) indica cómo se ha de configurar para que no se le pida la contraseña al grupo `wheel`. En el caso de que quisiésemos que no fuese a un grupo sino a un usuario, tendríamos que añadir:
    ```shell
    <nombre_usuario> ALL=(ALL) ALL  NOPASSWD: ALL
    ```

    Por tanto, y en lo que en este ejemplo nos atañe, para darle permisos de superusuario al usuario recién creado, lo añadimos al grupo `wheel` (que hemos visto que tiene permisos de superusuario) con el siguiente comando:
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

    Como ejemplo de prompt interesante, podemos usar el siguiente valor:
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

    - En el dispositivo "desperdiciado", se almacenan los *códigos de redundancia cíclica* (RCR, *Rebuild Check Rate*). Si uno de los $N$ primeros dispositivos falla, en vez de fallar el sistema entero como ocurría con RAID 0, se emplea una función que, en base al código de redundancia y a la información presente en el resto de los discos, reconstruye el disco que ha fallado. 

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


## Acceso Seguro al Servidor

### Cortafuegos

El cortafuegos es una herramienta de seguridad que controla el tráfico de red entrante y saliente en un sistema. El lector debe estar familiarizado con este concetp, puesto que se estudió en la asignatura de Fundamentos de Redes. Aquí, tan solo veremos cómo administrarlo en un sistema Linux.

Hay que diferenciar tres niveles de abstracción:
- **`iptables`**: Herramienta de bajo nivel Linux para gestionar el cortafuegos a nivel de kernel. Permite definir de forma directa las reglas del firewall, pero su uso es complejo. No se verá en la asignatura.
- **`firewalld`**: Servicio/demonio de medio/alto nivel, más sencillo de usar que `iptables`, que por debajo controla `iptables`. Permite gestionar el firewall de forma más sencilla y flexible. 
- **`firewall-cmd`**: Comando de alto nivel para interactuar con `firewalld`. Permite gestionar el firewall de forma sencilla y rápida desde la terminal. Es una especie de interfaz de usuario para `firewalld`.

Para ver si el firewall está activo, podemos ejecutar los siguientes comandos:
```shell
$ firewall-cmd --state
$ systemctl status firewalld
```

Como cualquier servicio, podemos activarlo/desactivarlo haciendo uso de `systemctl`:
```shell
$ systemctl start firewalld   # Activa el servicio
$ systemctl stop firewalld    # Desactiva el servicio
```

Con `firewall-cmd`, podemos trabajar de forma directa con puertos (bajo nivel), o con servicios. Los servicios son alias a puertos, y permiten gestionar el firewall de forma más sencilla. Los servicios disponibles se pueden obtener como sigue:
```shell
$ firewall-cmd --get-services
```

Para ver la información relativa a un servicio, como qué puerto y de qué protocolo usa, podemos ejecutar el siguiente comando:
```shell
$ firewall-cmd --info-service=<nombre_servicio>
```

De hecho, cada servicio tiene su archivo correspondiente, que almacena dicha información, en la carpeta siguiente:
```shell
$ ls -la /usr/lib/firewalld/services/
$ cat /usr/lib/firewalld/services/<nombre_servicio>.xml
```

De hecho, para crear un servicio nuevo, tan solo deberemos crear un archivo XML en la carpeta `/usr/lib/firewalld/services/` con el nombre del servicio, y con el contenido que queramos, y posteriormente recargar el servicio `firewalld` para que lo reconozca (esto se verá más adelante).


Para listar el estado actual del firewall, donde podemos ver los servicios y puertos abiertos (refiriéndose siempre a conexiones entrantes), podemos ejecutar el siguiente comando:
```shell
$ firewall-cmd --list-all
$ firewall-cmd --list-ports       # Solo puertos
$ firewall-cmd --list-services    # Solo servicios
```

Para modificar el firewall, es importante que no es posible realizar una modificación de forma instantánea y, además, almacenarlo en memoria para que se mantenga tras un reinicio. Hay por ello dos formas de trabajar:
1. **Modificaciones temporales**: Se aplican de forma inmediata, pero no se guardan tras un reinicio. Tienen nombres ilustrativos, y se recomienda al lector probarlas:
    ```shell
    $ firewall-cmd --add-service=http
    $ firewall-cmd --add-port=80/tcp    # Al habilitar un puerto siempre hemos de especificar el protocolo
    $ firewall-cmd --remove-service=http
    $ firewall-cmd --remove-port=80/tcp
    ```

    Una vez realizados todos estos cambios temporales, para guardarlos de forma permanente, hemos de ejecutar el siguiente comando:
    ```shell
    $ firewall-cmd --runtime-to-permanent
    ```

2. **Modificaciones permanentes**: Se guardan de forma inmediata, pero no se aplican hasta el reinicio. Para realizarlas, ha de añadirse la opción `--permanent` al comando. Por ejemplo:
    ```shell
    $ firewall-cmd --permanent --add-service=http
    $ firewall-cmd --permanent --add-port=80/tcp
    $ firewall-cmd --permanent --remove-service=http
    $ firewall-cmd --permanent --remove-port=80/tcp

    $ firewall-cmd --list-all   # Comprobamos que efectivamente no se activan de forma instantánea
    ```

    Una vez realizados todos estos cambios permanentes, si deseamos que se apliquen de forma instanea basta con:
    ```shell
    $ firewall-cmd --reload
    $ systemctl reload firewalld    # Alternativa
    ```

<!--
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
-->

### Nmap

**Nmap** (*Network Mapper*) es una herramienta de código abierto para la exploración de redes. Permite explorar redes, detectar hosts y puertos abiertos, etc. Se recomienda ejecutarlo con privilegios de administrador para obtener resultados más precisos.

Se pueden analizar tanto redes, como hosts individuales, como nombres de dominio. Por defecto realiza un escaneo de los puertos más comunes, pero se pueden especificar alternativas:
```shell
$ sudo nmap 192.168.56.0/24    # Escaneo de puertos (por defecto) en una red
$ sudo nmap 192.168.56.1    # Escaneo de un puertos en un host
$ sudo nmap -sn 192.168.56.0/24   # Escaneo de hosts en una red, haciendo tan solo PING
```

Normalmente, `nmap` escanea los 1000 puetos más comunes. Se puede especificar `-p-` para escanear todos los puertos (del 0 al 65535), o `-p <puerto>` para escanear un puerto específico. Hay otras opciones como:
- `-F` : Escaneo rápido (menos puertos). Tan solo escanea los 100 puertos más comunes.
- `--top-ports <n>`: Escaneo de los n puertos más comunes.


### Servidores Web

En este apartado, y para trabajar con el firewall, veremos cómo instalar y configurar un servidor web. Para ello, usaremos dos de los servidores más comunes: Nginx y Apache. Ambos son servidores web de código abierto, pero tienen algunas diferencias. Muy a gran escala, Apache es más sencillo, antiguo y flexible, mientras que Nginx es más moderno, ligero, rápido, y eficiente. Veremos por tanto cómo instalar un servidor web de ambas formas.

En primer lugar, y puesto que las conexiones las realizaremos desde el host, es necesario que el firewall tenga abierto el puerto para el servicio `http`. Para ello, ejecutaremos el siguiente comando:
```shell
$ firewall-cmd --permanent --add-service=http
$ firewall-cmd --reload
```

Procedemos ahora a trabajar con cada uno de los servidores web. Notemos que, puesto que no disponemos de certificado para autenticarnos, no podremos usar el protocolo `https`, y por tanto nuestro navegador nos informará de que no es seguro acceder a dichas páginas web.


#### Nginx

En primer lugar, hemos de instalarnos el servicio de `Nginx`, y activarlo. Lo configuraremos además para que se inicie automáticamente al arrancar el sistema. Para ello, ejecutamos los siguientes comandos:
```shell
$ dnf install nginx
$ systemctl enable nginx    # Activa el servicio al arrancar el sistema
$ systemctl start nginx     # Iniciarlo sin necesidad de reiniciar
```

Una vez realizado esto, podemos comprobar que efectivamente todo va correctamente accediendo a la dirección IP del servidor. Para ello, desde el anfitrión, accedemos en un navegador a la dirección IP del servidor. Si todo ha ido bien, deberíamos ver una página de bienvenida de Nginx.

A continuación, buscamos cambiar la página de bienvenida por una página web personalizada. Para ello hemos de saber que la web que se muestra está ubicada en `/usr/share/nginx/html/index.html`. Para modificarla, sustituimos el contenido de dicho `index.html` por:
```html
<!DOCTYPE html>
<html>
    <body>
        <h1>Bienvenidos a la Web de [Tu Nombre y Apellido] en Prácticas ISE</h1>
    </body>
</html>
```

La configuración de Nginx, como era de esperar, se encuentra en `/etc/nginx/nginx.conf`. En este archivo se pueden modificar varias configuraciones, como el puerto en el que se escucha o la ubicación de la web. Se recomienda al lector que le eche un vistazo a este archivo, donde podrá ver:
```shell
server {
    listen       80;          # Puerto en el que escucha
    listen       [::]:80;
    server_name  _;
    root         /usr/share/nginx/html;   # Ubicación de la web

    # Load configuration files for the default server block.
    include /etc/nginx/default.d/*.conf;

    error_page 404 /404.html;
    location = /404.html {
    }

    error_page 500 502 503 504 /50x.html;
    location = /50x.html {
    }
}
```

#### Apache

Veamos ahora la configuración equivalente para un servidor en apache:
```shell
$ dnf install httpd
$ systemctl enable httpd
$ systemctl start httpd
```

Si el lector ha intentado ejecutar directamente esos tres comandos, verá que no ha funcionado. Esto se debe a que no se puede tener el servicio `httpd` y `nginx` al mismo tiempo escuchando en el mismo puerto. Por tanto, si se ha instalado `nginx`, hemos de pararlo o cambiarlo de puerto. En este caso lo pararemos por simplicidad:
```shell
$ systemctl stop nginx
$ systemctl disable nginx
```

Una vez realizado esto e iniciado el servicio `httpd`, podemos comprobar que efectivamente todo va correctamente accediendo a la dirección IP del servidor. Para ello, desde el anfitrión, accedemos en un navegador a la dirección IP del servidor. Si todo ha ido bien, deberíamos ver una página de bienvenida de Apache.


En este caso, la página web se encuentra en `/var/www/html/index.html`. Podemos modificarla como hicimos en el caso de Nginx.

La configuración de Apache se encuentra en `/etc/httpd/conf/httpd.conf`. En este archivo se pueden modificar varias configuraciones, como el puerto en el que se escucha o la ubicación de la web. Se recomienda al lector que le eche un vistazo a este archivo. Algunas de las líneas que podrá ver y modificar son:
```shell
...
Listen 80
...
DocumentRoot "/var/www/html"
...
```


### SSH

SSH *(Secure Shell)* es un protocolo de red que permite la comunicación segura entre dos dispositivos mediante una terminal remota segura. Antes existían otros protocolos como `telnet`, pero este enviaba toda la información en texto plano (incluida la información del login), por lo que no es una opción segura. SSH en cambio cifra toda la información, tanto el proceso de login como el de dsesón, luego es seguro. De hecho, en lo que llevamos de práctica hemos estado accediendo a la VM a través de SSH.

#### Resumen Criptografía
Veamos ahora un pequeño repaso de cifrado y seguridad, aunque recomendamos al lector leer el Temario de Fundamentos de Redes si no está familiarizado con estos conceptos. Hay dos algoritmos de cifrado:
- **Cifrado Simétrico**: Entre cada par de entidades se comparte una clave secreta. Al cifrar con cierta clave, solo el receptor que tenga la misma clave podrá descifrarlo. El algoritmo más empleado se denomina `DES`.
    - Este tipo de cifrado es muy eficiente, pero tiene el problema de la escalabilidad, ya que cada par de entidades ha de compartir una clave secreta. Por ello, se desarrolló el cifrado asimétrico.
- **Cifrado Asimétrico**: Cada entidad tiene dos claves, una pública y otra privada. La clave pública se comparte con todos, mientras que la privada es secreta. Cuando se cifra con la clave pública, solo el receptor que tenga la clave privada podrá descifrarlo. El algoritmo más empleado se denomina `RSA`.
    - Este tipo de cifrado es muy seguro, pero tiene el problema de la eficiencia, ya que es mucho más costoso computacionalmente.

Además, se emplean los resúmenes llamados `hash`, que son funciones unidireccionales que generan un valor único a partir de unos datos. Estos permiten comprobar la integridad de los datos, ya que un pequeño cambio en los datos genera un hash completamente diferente. Los algoritmos se denominan `SHA-n` (*Secure Hash Algorithm*), donde `n` es el número de bits del hash. Por ejemplo, `SHA-256` genera un hash de 256 bits.

Por tanto, para garantizar la integridad de los documentos se emplea la firma dital. Esta consiste en, a partir de una información, calcular su hash y cifrar todo con la llave privada. Cuando el receptor recibe el mensaje, descifra el hash con la llave pública del emisor y compara el hash recibido con el calculado. Si son iguales, se garantiza la integridad del mensaje y que ha sido enviado por el emisor.

Todo esto tiene un último problema: nada nos garantiza que las claves públicas y privadas efectivamente sean de quien dicen ser. Para ello, se emplean las Autoridades de Certificación (AC). Estas son entidades de confianza que validan la correspondencia entre claves y personas/entidades. Por ejemplo, en España la FNMT (Fábrica Nacional de Moneda y Timbre) es la AC oficial. Estas emiten un certificado que contiene la clave pública y los datos del propietario, firmado con la clave privada de la AC para garantizar que ese certificado es válido. Cuando un usuario recibe un certificado, hay dos opciones.
- Si confía en la AC, puede confiar en el certificado.
- Si no conoce la AC, comprueba quién ha certificado a dicha AC (ya que estas se autorizan entre sí). Se repite por tanto el proceso hasta llegar a una AC raíz, que es de confianza (caso anterior).

Por ejemplo, para ver todo esto, en cualquier navegador accedemos a una web mediante el protocolo `https`, por ejemplo `https://www.ugr.es`. Para acceder al certificado depende del navegador, pero siempre podremos ver los detalles de esto, la jerarquía de Autenticación, etc. En [este enlace](chrome://certificate-manager/crscerts) se pueden ver las AC raíz en las que confía el navegador de Google Chrome.


#### Conexión SSH mediante usuario y contraseña

Veamos ahora cómo funciona SSH en concreto. As importante destacar dos entidades:
- **Cliente**: Máquina que inicia la conexión SSH. En nuestro caso, es el ordenador anfitrión.
- **Servidor**: Máquina que recibe la conexión SSH. En nuestro caso, es la VM.

Evidentemente, es necesario que el servicio `sshd` esté ejecutándose en el servidor. Para conectarnos, ejecutamos el siguiente comando desde el cliente:
```shell
$ ssh <usuario>@<ip>
$ ssh -u <usuario> <ip>   # Alternativa, pero no es común
```

Por defecto, se conecta al puerto `22/tcp` (puerto por defecto de SSH). Si el servidor está escuchando en otro puerto, hemos de especificarlo con la opción `-p`:
```shell
$ ssh -p <puerto> <usuario>@<ip>
```

En ese momento, el servidor responde con su clave pública para autenticarse. Como no hay AC, el cliente contiene en el archivo `~/.ssh/known_hosts` las claves públicas de los servidores de confianza a los que se ha conectado, junto con su dirección IP. De esta forma:
- Cuando es la primera vez que se conecta, el cliente pregunta si confía en la clave pública del servidor. Si el usuario acepta, se añade al archivo `known_hosts`.
- Si se detecta que ya se ha conectado a esa dirección IP pero la clave pública no es la misma, se impide la conexión y se avisa de un posible ataque de *man-in-the-middle*. En este caso, será el usurio el que tendrá que modificar manualmente el archivo `known_hosts` para eliminar la clave pública del servidor.

Una vez recibida la clave pública del servidor, el cliente envía su contraseña para iniciar sesión cifrada con la clave pública del servidor. El servidor comprueba la contraseña y, si las credenciales son correctas, se ha establecido la coneión. Como el cifrado asimétrico es muy costoso computacionalmente, en ese momento se establece una clave simétrica de sesión compartida por ambos, y se utiliza para cifrar el resto de la sesión.


#### Conexión SSH mediante clave pública

Supongamos ahora que el usuario no quiere introducir la contraseña cada vez que se conecta. Para ello, es posible usar claves asimétricas para autenticarse frente al servidor. En primer lugar, hemos de crearlas con el comando `ssh-keygen` (en el caso de no tener). Es recomendable siempre ponerles una contraseña, pero para evitar tener que introducirla cada vez, podemos usar el comando `ssh-agent` para almacenar la clave privada en memoria, y este escribirá por nosotros la contraseña.

Una vez las tengamos generadas (este proceso es muy común y es posible que el lector ya las tuviese, puesto que se usan por ejemplo en `GitHub`), podemos conectarnos al servidor sin necesidad de introducir la contraseña. Para ello, el servidor dispone del archivo `~/.ssh/authorized_keys`, donde se almacenan las claves públicas de los clientes autorizados a conectarse sin conectarse. Para añadir la clave pública del cliente al servidor, hay dos opciones:
1. Copiar la clave pública manualmente al servidor, y añadirla al archivo `~/.ssh/authorized_keys` del usuario con el que queremos conectarnos. Esta opción está desactonsejada, puesto que está sujeta a errores humanos.
2. Usar el comando `ssh-copy-id`, que se encarga de copiar la clave pública al servidor y añadirla al archivo `~/.ssh/authorized_keys` del usuario con el que queremos conectarnos. Esta es la opción recomendada.  Desde el cliente:
    ```shell
    $ ssh-copy-id <usuario>@<ip>
    ```
    Tras introducir la contraseña, el cliente se conecta al servidor y añade la clave pública al archivo `~/.ssh/authorized_keys` del usuario con el que queremos conectarnos.

Una vez realizada esta operación, el cliente puede conectarse al servidor como hemos descrito antes sin necesidad de introducir la contraseña.


Por último, cabe destacar que, si al comando SSH se le añade final un comando como parámetro, este se ejecutará en el servidor sin necesidad de abrir una terminal remota. Por ejemplo:
```shell
$ ssh arturo@rockybase ls -la
total 24
drwx------. 3 arturo arturo  111 May 18 13:51 .
drwxr-xr-x. 3 root   root     20 May 17 19:43 ..
-rw-------. 1 arturo arturo 5003 May 18 13:50 .bash_history
-rw-r--r--. 1 arturo arturo   18 May 16  2022 .bash_logout
-rw-r--r--. 1 arturo arturo  141 May 16  2022 .bash_profile
-rw-r--r--. 1 arturo arturo  537 May 17 20:03 .bashrc
-rw-------. 1 arturo arturo   46 May 18 12:32 .lesshst
drwx------. 2 arturo arturo   29 May 18 13:51 .ssh
```

Este es el inicio de la automatización. Notemos que, si en un servidor ponemos un firewall muy restrictivo en el que tan solo permitamos acceso por SSH, podremos administrarlo sin problema como hemos visto, pero será muy seguro.


#### Estructura de archivos de SSH

El servicio SSH cuenta con dos carpetas importantes.
1. `~/.ssh/`: Carpeta del usuario que contiene las claves públicas y privadas del usuario. Además, contiene:
    - `authorized_keys`: En el servidor, contiene las claves públicas de los clientes autorizados a conectarse sin contraseña.
    - `known_hosts`: En el cliente, contiene las claves públicas de los servidores a los que se ha conectado.
2. `/etc/ssh/`: Carpeta del sistema que contiene la configuración del servicio SSH. Notemos que se puede configurar tanto el cliente como el servidor, y es importante tener en cuenta qué se está configurando.
   - `sshd_config`: Archivo de configuración del *servidor* SSH. Termina en `d` por referirse al demonio `sshd`. Algunos aspectos importantes de este son:
       - **`Port`**: Puerto en el que escucha el servidor SSH. Por defecto es el 22.
       - **`PermitRootLogin`**: Permite o no el acceso por SSH al usuario `root`. Además de las opciones de `yes` o `no`, destaca la opción `prohibit-password`, que permite el acceso por SSH al usuario `root`, pero no permite el acceso por contraseña. Solo permite el acceso por clave pública.
   - `ssh_config`: Archivo de configuración del *cliente* SSH.

#### Ejercicio Adicional

Supongamos ahora que queremos cambiel puerto en el que escucha el servicio SSH. Para ello, en primer lugar hemos de detectar un puerto que no esté en uso, para evitar colisiones. Para ello, el archivo `/etc/services` contiene una lista de los puertos y servicios que están en uso. Por comodidad, recomendamos filtrar con `grep` para buscar el puerto que queremos.
```shell
$ cat /etc/services | grep <puerto>
```

Una vez detectado un puerto libre, y antes de cambiar la configuración de SSH, hemos de modificar el firewall para que permita el acceso a ese puerto.
```
$ firewall-cmd --add-port=<puerto>/tcp
```

Una vez abierto dicho puerto, procedemos a cambiarlo. Si intentamos modificar el puerto en el archivo de configuración `/etc/ssh/sshd_config`, vemos:
```shell
# If you want to change the port on a SELinux system, you have to tell
# SELinux about this change.
# semanage port -a -t ssh_port_t -p tcp #PORTNUMBER
#
#Port 22
```
Por tanto, para cambiar el puerto, además de modificar el archivo de configuración, hemos de emplear el comando `semanage` como ahí especifica. Notemos que este comando tendremos que instalarlo, y para ello hemos de hacer uso de `dnf provides`.
```shell
$ dnf provides semanage
Rocky Linux 9 - BaseOS                                                                                  2.0 MB/s | 2.3 MB     00:01    
Rocky Linux 9 - AppStream                                                                               5.2 MB/s | 8.4 MB     00:01    
Rocky Linux 9 - Extras                                                                                   21 kB/s |  16 kB     00:00    
policycoreutils-python-utils-3.6-2.1.el9.noarch : SELinux policy core python utilities
Repo        : appstream
Matched from:
Filename    : /usr/sbin/semanage

$ dnf install policycoreutils-python-utils-3.6-2.1.el9.noarch
$ semanage port -a -t ssh_port_t -p tcp 22212
$ systemctl restart sshd
```

Retiramos que es necesario tanto modificar el archivo de configración de `sshd` como emplear el comando `semenage`, puesto que si no hacemos lo segundo el `restart` nos dará error. Una vez realizado esto, podremos acceder sin problema desde el cliente empleando el puerto especificado.


Como último aspecto a mencionar, hemos de destacar que, una vez establecida la conexión, no va a cerrar la sesión automáticamente. Aunque se cambie el puerto de `ssh`, aunque se cierre el puerto en el que estaba escuchando, etc. No obstante, si se cierra la sesión, no podremos volver a conectarnos hasta que se abra el puerto de nuevo. Por tanto, es recomendable hacer un `ssh -p <puerto> <usuario>@<ip>` en una terminal diferente antes de cerrar la sesión, para asegurarnos de que efectivamente funciona.

## Ansible
Ansible es una herramienta que automatiza la gestión remota de sistemas y controla su estado deseado.
