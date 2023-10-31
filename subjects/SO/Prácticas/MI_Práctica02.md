# Sistemas Operativos.  Módulo I. Práctica 02.

**Autor:** Arturo Olivares Martos
***

- **Asignatura:** Sistemas Operativos.
- **Curso Académico:** 2023-24.
- **Grado:** Doble Grado en Ingeniería Informática y Matemáticas.
- **Grupo:** Único.
- **Profesor:** Alejandro José León Salas
- **Descripción:** Sesión 2 del Módulo I de las prácticas de SO.
<!--- **Fecha:** 17 de abril de 2023. -->
<!-- - **Duración:** -->


## Actividad 2.1. Partición de un dispositivo: *“USB pen drive”* o *“memory stick”*
En esta práctica, vamos a particionar un dispositivo simulado mediante un archivo `/dev/loop?`. Estos archivos permiten crear un dispositivo de almacenamiento virtual cuyo espacio de almacenamiento viene soportado por un archivo asociado. También nos referiremos a cómo particionar un USB, pero las pruebas por norma general las haremos con los archvos `/dev/loop?`, ya que el *usermode linux* no reconoce los USB, y siempre preferimos trabajar en él que en nuestro SO personal.

Como las particiones que vamos a hacer no van a ser excesivamente grandes vamos a utilizar la
herramienta `fdisk`. En el caso de que fuesen de mayor tamaño, se podría emplear la herramienta `parted`.
______
______

1. **Preparación previa a la partición de un dispositivo simulado mediante un archivo especial de dispositivo `/dev/loop?`.**

    En primer lugar, tenemos que comprobar qué dispositivos se encuentran ya en uso, para no sobreescribirlos.
    ```console
    # ls -l /dev/loop*
    ls: cannot access /dev/loop*: No such file or directory
    ```
    Esto nos informa de que no hay dispositivos ya en uso, por lo que podemos usar `/dev/loop0` y `/dev/loop1`.

    Una vez hemos comprobado que los tenemos disponibles, los creamos con la orden `mknod`, ya que son archivos especiales de dispositivos. Como son dispositivos de bloques, incluimos la opción `b`. A continuación, vienen el *Major Number* y el *Minor Number*. El *Major Number* lo encontramos en el siguiente documento:
    ```console
    # cat /proc/devices
    Character devices:
      ...

    Block devices:
      ...
      7 loop
      ...
    ```
    Donde los ... implican que hay gran cantidad de tipos disponibles. Por tanto, tenemos que el *Major Number* es 7. El *Minor Number* identifica a cada dispositivo, por lo que la instrucción para crear ambos dispositivos queda:
    ```console
    # mknod /dev/loop0 b 7 0
    # mknod /dev/loop1 b 7 1
    ```

    Ahora, es necesario crear los archivos que vamos a asociar a los dispositivos `loop`. Los crearemos con la orden `dd`, que es una orden de copiado de bajo nivel. Como *input file* tomaremos `if=/dev/zero`, que es un archivo fuente de 0s. Usaremos la opción `bs=2k`, que indica que el tamaño de bloque (*block size*) es de 2k bytes; y la opción `count=10000`, que indica que se copiarán ese número de bloques. Por tanto, para crear un archivo de 20 y 30MB, usamos:
    ```console
    # dd if=/dev/zero of=/root/archivo_SA20 bs=2k count=10000
    10000+0 records in
    10000+0 records out
    20480000 bytes (20 MB) copied, 0.276427 s, 74.1 MB/s

    # dd if=/dev/zero of=/root/archivo_SA30 bs=3k count=10000
    10000+0 records in
    10000+0 records out
    30720000 bytes (31 MB) copied, 0.377243 s, 81.4 MB/s
    ```

    Una vez creados dichos archivos, es necesario asociarlos a los dipositivos `loop` mediante la siguiente instrucción:
    ```console
    # losetup /dev/loop0 /root/archivo_SA20
    # losetup /dev/loop1 /root/archivo_SA30
    ```


    Para comprobar que está todo listo para crear la tabla de particiones en los dispositivos simulados, usamos el siguiente comando:
    ```console
    # fdisk -l /dev/loop0 /dev/loop1
    ```
    ____________



    En el caso de trabajar con un USB, necesitamos saber qué archivo especial de dispositivo tiene asignado. Para ello usamos la instrucción `mount` o, equivalentemente:
    ```console
    # sudo cat /proc/mounts
    ....
    /dev/sdc1 /media/arturo/USB exfat rw,nosuid,nodev,relatime,uid=1000,gid=1000,fmask=0022,dmask=0022,iocharset=utf8,errors=remount-ro 0 0
    ```
    Notemos que la máscara `022` quita por defecto los permisos de escritura para el grupo y para el resto de usuarios.


    Podemos ver que el USB tiene asignado el archivo `/dev/sdc1`. Para trabajar con él, en primer lugar hemos de desmontarlo haciendo uso de:
    ```console
    # umount /dev/sdc1
    ```
______
______

2. **Creación de una partición**

    Una vez que ya tenemos los dispositivos disponibles, hemos de emplear la orden `fdisk` con cada uno de los disposigtivos para crear las particiones.
    ```console
    # fdisk /dev/loop1
    ```

    Esta instrucción muestra un menú interactivo que nos permite trabajar con el dispositivo. Contiene distintas opciones, como `n` para nuevas particiones, `p` para imprimir la tabla de particiones o `w` para guardarla y salir, entre otras muchas opciones.

    En el caso del USB, tan solo es necesario saber cuáles el dispositivo asociado, ya que aunque el archivo sea `/dev/sdc1` el archivo es `/dev/sdc`. Esto se puede emplear fácilmente usando el comando `fdisk -l`. Además, antes de crear una nueva partición, se recomienda usar la opción `o` de `fdisk` para crear una nueva tabla de particiones, eliminando así la anterior.



## Actividad 2.2. Creación de sistemas de archivos

Una vez tenemos creadas las particiones, es necesario asignarles un SA, formateándolo. Para ello, se emplea la instrucción `mke2fs`. La opción `-t` permite indicar el tipo de SA, normalmente `ext2, ext3, ext4`, etc. Para el caso de `/dev/loop0`, quedaría:
```console
# mke2fs -t ext3 -L LABEL_ext3 /dev/loop0  
mke2fs 1.41.12 (17-May-2010)
Filesystem label=LABEL_ext3
OS type: Linux
Block size=1024 (log=0)
Fragment size=1024 (log=0)
Stride=0 blocks, Stripe width=0 blocks
5016 inodes, 20000 blocks
1000 blocks (5.00%) reserved for the super user
First data block=1
Maximum filesystem blocks=20709376
3 block groups
8192 blocks per group, 8192 fragments per group
1672 inodes per group
Superblock backups stored on blocks: 
	8193

Writing inode tables: done                            
Creating journal (1024 blocks): done
Writing superblocks and filesystem accounting information: done

This filesystem will be automatically checked every 28 mounts or
180 days, whichever comes first.  Use tune2fs -c or -i to override.
```

El caso de `/dev/loop1` es análogo. Vemos que en la salida se mencionan los `inodos`. Un *inodo* es una estructura de datos que almacena información sobre cada "archivo". Puede haber más de un archivo que se refiera  a un único inodo, ya que puede ser que estos se traten de *links*, no teniendo por tanto inodos propios.



## Actividad 2.3. Personalización de los metadatos del SA

Consultando el manual en línea para la orden `tune2fs` responde a las siguientes preguntas:
1.  ¿Cómo podrías conseguir que en el siguiente arranque del sistema se ejecutara
automáticamente `e2fsck` sin que se haya alcanzado el máximo número de montajes?

    La instrucción `e2fsck` comprueba un SA de Linux, y para que se ejecute en el siguiente arranque del sistema hay dos opciones:
    * Ejecutar `tune2fs -c 0` o `tune2fs -c -1`, ya que esa instrucción sirve para especificar el número máximo de montajes que se pueden realizar antes de ejecutar dicha orden.
    * Ejecutar `tune2fs -C [num]`, con [num] un valor mayor que el establecido con la opción `-c`, ya que esta establece el número de veces que ha sido montado a [num]. Como podemos ver, es preferible usar la otra opción.  


2.  ¿Cómo podrías conseguir reservar para uso exclusivo de un usuario username un número de
bloques del sistema de archivos?

    La opción `-r [reserved-blocks-count]` reserva una cantidad determinada de bloques, y la opción `-u [user]` establece qué usuario puede usar los bloques reservados.

    Por tanto, quedaría:
    ```console
    # tune2fs /dev/loop0 -r [reserved-blocks-count] -u [user]
    ```



## Actividad 2.4. Montaje de sistemas de archivos

Utiliza el manual en línea para descubrir la forma de montar nuestros SAs de manera que cumplas los siguientes requisitos:
1. El SA etiquetado como `LABEL_ext3` debe estar montado en el directorio `/mnt/SA_ext3` y en modo de solo lectura.

    La operación para montar SAs es `mount`. La instrucción `-o` permite poner opciones, y `ro` indica que es de solo lectura (*read only*).
    ```console
    # mkdir /mnt/SA_ext3
    # mount -L LABEL_ext3 /mnt/SA_ext3 -o ro
    [20002.980000] EXT3-fs: barriers not enabled
    [20002.980000] kjournald starting.  Commit interval 5 seconds
    [20002.980000] EXT3-fs (loop0): mounted filesystem with writeback data mode
    ```


2. El SA etiquetado como `LABEL_ext4` debe estar montado en el directorio `/mnt/LABEL_ext4` y debe tener sincronizadas sus operaciones de E/S de modificación de directorios.

    Para que se sincronicen las operaciones de modificación **de directorios**, se emplea la opción `dirsync`. Si fuese en general para todos los archivos, se emplearía `sync`. Para lo pedido, queda:
    ```console
    # mkdir /mnt/LABEL_ext4
    # mount -L LABEL_ext4 /mnt/LABEL_ext4 -o dirsync
    [20066.480000] EXT4-fs (loop1): mounted filesystem with ordered data mode. Opts: (null)
    ```

    La parte `Opts: (null)` no indica que haya habido error. Posiblemente, indica que no se han establecido las opciones por defecto.

    Una vez que se han montado los SA, cada archivo que ubiquemos en nuestro punto de montaje residirá en la ubicación de la que depende nuestra partición. En nuestro caso, todo lo que subamos a `/mnt/LABEL_ext4` se ubicará en el archivo de 30GiB `/root/archivo_SA30`.


## Actividad 2.5. Automontaje de Sistemas de Archivos
Escribe las dos líneas necesarias en el archivo `/etc/fstab` para que se monten automáticamente
nuestros dos SA en el arranque del sistema con los mismos requisitos que se han pedido en la
Actividad 2.4.

```console
LABEL=LABEL_ext3				/mnt/SA_ext3	ext3	auto,ro		0 0
LABEL=LABEL_ext4				/mnt/LABEL_ext4	ext4	auto,dirsync	0 0
```
donde la opción `auto` se ha empleado para que se monten de forma automática.


## Actividad 2.6. Repositorios de paquetes
Accede a los sitios web especializados que ofrecen software para sistemas operativos Linux y enumera las principales características de cada uno de ellos en base, por ejemplo, a si contiene software abierto y/o propietario, tipos de aplicaciones disponibles, tamaño del sitio en cuanto a la cantidad de software que mantiene, y otras características que considere interesantes.


## Actividad 2.8. Trabajo con el gestor de paquetes rpm

1. Muestra la información general (nombre, versión, arquitectura, grupo, descripción, etc.) y lista los archivos que contiene un paquete ya instalado haciendo uso de la orden `rpm` y un
único conjunto de opciones.

    En primer lugar, hemos de seleccionar un paquete sobre el cual trabajar. Para ello, usamos la opción `-qa` (*query all*), que nos informa de todos los paquetes que tenemos instalados.
    ```console
    # rpm -qa
    filesystem-2.4.35-1.fc14.i686
    ...
    ncurses-libs-5.7-9.20100703.fc14.i686
    libss-1.41.12-6.fc14.i686
    ...
    libselinux-utils-2.0.96-6.fc14.1.i686
    ```

    Una vez seleccionado el paquete, (en este tomamos `libselinux-utils-2.0.96-6.fc14.1.i686`), podemos trabajar con él. En este caso, se usa la opción `-qi` (*-query information*) para obtener la información, y la opción `-l` para obtener el listado de los archivos del paquete:
    ```console
    # rpm -qli libselinux-utils-2.0.96-6.fc14.1.i686
    Name        : libselinux-utils             Relocations: (not relocatable)
    Version     : 2.0.96                            Vendor: Fedora Project
    Release     : 6.fc14.1                      Build Date: Thu Sep 30 02:04:16 2010
    Install Date: Sat Dec  4 06:17:19 2010         Build Host: x86-07.phx2.fedoraproject.org
    Group       : Development/Libraries         Source RPM: libselinux-2.0.96-6.fc14.1.src.rpm
    Size        : 49733                            License: Public Domain
    Signature   : RSA/SHA256, Thu Sep 30 11:16:04 2010, Key ID 421caddb97a1071f
    Packager    : Fedora Project
    URL         : http://www.selinuxproject.org
    Summary     : SELinux libselinux utilies
    Description :
    The libselinux-utils package contains the utilities
    /usr/sbin/avcstat
    ...
    /usr/share/man/man8/togglesebool.8.gz
    ```
    donde `...` representa la lista completa de archivos.

2. Idem que el anterior pero mostrando únicamente los archivos de configuración que contiene el paquete.

    Para solo mostrar los archivos de configuración, usamos la opción `-qc` (*query configuration*). Sí es cierto que muchos paquetes no contienen archivos de información, pero otros sí.
    ```console
    # rpm -qc glibc-common-2.13-2.i686
    /etc/default/nss
    /usr/lib/locale/locale-archive
    ```

3. Escribe una orden que muestre los paquetes requeridos por un paquete determinado que se encuentre instalado en el sistema. Escriba la orden que devuelva el mismo resultado pero para un paquete no instalado en el sistema.

    En el caso de un paquete instalado, tenemos que se usa la opción (*query requirements*).
    ```console
    # rpm -qR libselinux-2.0.96-6.fc14.1.i686
    /bin/sh  
    /sbin/ldconfig  
    ld-linux.so.2 
    ...
    rpmlib(PayloadFilesHavePrefix) <= 4.0-1
    rtld(GNU_HASH)  
    rpmlib(PayloadIsXz) <= 5.2-1

    ```

    En el caso de un paquete que no esté instalado, basta con añadir la  opción `-p` antes del nombre o *url* del paquete a instalar.