# Sistemas Operativos. Módulo I. Práctica 01.

**Autor:** Arturo Olivares Martos
***

- **Asignatura:** Sistemas Operativos.
- **Curso Académico:** 2023-24.
- **Grado:** Doble Grado en Ingeniería Informática y Matemáticas.
- **Grupo:** Único.
- **Profesor:** Alejandro José León Salas
- **Descripción:** Sesión 1 del Módulo I de las prácticas de SO.
<!--- **Fecha:** 17 de abril de 2023. -->
<!-- - **Duración:** -->


## Actividad 1.1. Repaso de *scripts* de bash
Crea un script de bash que automatice todos los pasos necesarios para abrir el *user-mode Linux*. Al entrar de nuevo en el sistema sólo tendrás que ejecutar el script para empezar a trabajar en modo root.
```bash
#!/bin/bash

./kernel32-3.0.4 ubda=./Fedora14-x86-root_fs mem=1024m
```



## Actividad 1.2. Valores por omisión para nuevas cuentas.
Visualiza el contenido de los dos archivos anteriores y comprueba cuáles son las opciones por defecto que tendría un usuario que se creara en nuestro sistema. A continuación, crea una cuenta de usuario y visualiza el contenido de los archivos `/etc/passwd` y `/etc/group`, y el directorio `/home` para comprobar que los nuevos datos se han rellenado conforme a la especificación tomada de `/etc/default/useradd` y `/etc/login.defs`.
```console
# useradd user1
```

En `/etc/default/useradd` hay mucha información relevante sobre los datos por defecto.
- HOME_DIR = BASE_DIR/LOGIN_NAME. Por ejemplo, `~=/home/arturo`.


## Actividad 1.3. Creación de usuarios

1. Utiliza el manual en línea para leer la sintaxis completa de la utilidad para creación de cuentas y crea dos o tres usuarios en tu sistema cambiando alguno de los valores por defecto.

    ```console
    # useradd user1

    # mkdir /home/aqui
    # useradd -b /home/aqui user2
    ```

    Es importante notar que el directorio `~` del `user2` va a ser `/home/aqui/user2`, habieno nosotros cambiado los valores por defecto. Hemos tenido que crear previamente la carpeta, ya que en caso contrario no hubiese generado el directorio.

2. Elimina alguno de ellos y comprueba que "rastro" ha dejado la cuenta recién eliminada en el sistema.
    ```console
    # userdel user1
    ```
    Con ese código se elimina ese usuario, quitándolo también del archivo `/etc/passwd` y `/etc/shadow`, pero su directorio `HOME` no se elimina. Para ello, es necesario usar la opción `-r`.

3. Entra (orden `su`) en el sistema como uno de estos usuarios que has creado y mira qué archivos tiene en su directorio home.

    Tienen los archivos que se encuentran en `/etc/skel`, que son los archivos que se copian por defecto al crear un usuario.

## Actividad 1.4. Archivo `/etc/passwd`
Visualiza el archivo `/etc/passwd` e indica cual es el formato de cada línea de dicho archivo. Para ello también puedes consultar el `man` o `info` de Linux. ¿Quién es el propietario de este archivo y cuáles son sus permisos?

Para ver el formato de cada línea, consultamos el manual.
``` console
$ man 5 passwd
```

El manual nos informa de lo siguiente:

`/etc/passwd` contains one line for each user account, with seven fields delimited by colons (“:”). These fields are:
- login name
- optional encrypted password
- numerical user ID
- numerical group ID
- user name or comment field
- user home directory
- optional user command interpreter

Por ejemplo, para el `user1`, su línea correspondiente es:
```console
user1:x:500:500::/home/user1:/bin/bash
```

Para ver sus privilegios, ejecutamos lo siguiente:
``` console
# ls -l /etc/passwd
-rw-r--r-- 1 root 881 Oct 8 06:46 /etc/passwd
```
Por tanto, vemos que el propietario es `root` y que sus permisos para son de lectura para todos, y de escritura también para `root`.

## Actividad 1.5. Archivo `/etc/shadow`

Visualiza el archivo `/etc/shadow` desde un usuario distinto al `root` ¿Te da algún problema? ¿Sabes por qué? Intenta averiguarlo.

```console
$ cat /etc/shadow
cat: /etc/shadow: Permission denied
```

Esto se debe a que el archivo en cuestión contiene los datos sobre las contraseñas de los usuarios, por lo que tiene protección para que no cualquiera pueda leerlo. Veamos sus permisos:

```console
$ ls -l /etc/shadow
-rw-r----- 1 root shadow 1435 abr 18 02:41 /etc/shadow
```
Como podemos ver, el propietario es `root`, con permisos de lectura y escritura, y los usuarios en su grupo también tienen permiso de lectura.

## Actividad 1.6. Creación de grupos
1. Crea un par de grupos y asignáselos a algunos de los usuarios de tu sistema.
```console
# groupadd grCreado
#
# gpasswd -a user2 grCreado
Adding user user2 to group grCreado
#
# gpasswd -a user2 grCreado
Adding user user2 to group grCreado
```

2. ¿Qué información devuelve la orden id si estás conectado como root?
```console
# id
uid=0(root) gid=0(root) groups=0(root),1(bin),2(daemon),3(sys),4(adm),6(disk),10(wheel)
```


## Actividad 1.7. Archivo del *kernel* de Linux
Utilizando la orden (`find`) que ya conoces para la búsqueda de archivos en el sistema de
archivos, anota el nombre absoluto del archivo del kernel de Linux que se ha cargado en
el sistema operativo que estás usando en el laboratorio de prácticas para acceso modo
`root`.

El archivo que buscamos es `vmlinuz`, que contiene el kernel comprimido. Este archiv se carga de forma general en el inicio de sistema, pero en el UML que empleamos en el laboratio no se encuentra, ya que este solo contiene lo esencial. En un sistema UNIX, tenemos lo siguiente:
```console
$ cd /
$ sudo find -name vmlinuz*
./boot/vmlinuz.old
./boot/vmlinuz-5.15.0-43-generic
./boot/vmlinuz
./boot/vmlinuz-6.2.0-32-generic
find: ‘./run/user/1000/doc’: Permission denied
find: ‘./run/user/1000/gvfs’: Permission denied

$ ls -l /boot/vmlinuz*
lrwxrwxrwx 1 root root       24 sep 19 09:24 /boot/vmlinuz -> vmlinuz-6.2.0-32-generic
-rw-r--r-- 1 root root 11090688 feb 23  2023 /boot/vmlinuz-5.15.0-43-generic
-rw------- 1 root root 13791304 ago 18 11:40 /boot/vmlinuz-6.2.0-32-generic
lrwxrwxrwx 1 root root       25 sep 19 09:24 /boot/vmlinuz.old -> vmlinuz-5.15.0-43-generic
```

Como podemos ver, el archivo `vmlinuz` se encuentra en la carpeta de arranque `/boot`, y es un enlace a la versión correspondiente, en este caso `vmlinuz-6.2.0-32-generic`.


## Actividad 1.8. Organización del SA
Un programa que se ejecuta en modo `root`, ¿dónde podría guardar la información temporal de
forma que ésta se mantuviese entre arranques del sistema?

Si se guardase en `/tmp`, esa información se perdería a apagar el sistema. Por tanto, en esta carpeta no se puede guardar. Una posible opción sería el directorio de inicio de `root` (`/root`).

## Actividad 1.9. Información de los SAs
Los archivos `/etc/fstab` y `/etc/mtab` muestran información sobre los sistemas de archivos que se encuentran montados en el sistema. ¿Cuál es la diferencia entre la información que muestra cada uno de ellos?

El fichero `fstab` *(filesystem table)* es un archivo que contiene los distintos tipos de filesystem que se montan en el arranque. Por otro lado, el fihcero `mtab` *(mounted filesystem table)* contiene la información de los filesystem que ya han sido montados en el ordenador.

La diferencia se desarrolla más en la última actividad de esta práctica.

## Actividad 1.10 Información de los SAs
Edita el archivo `/etc/fstab` del sistema de archivos que estás utilizando en modo `root` y anota y describe la información que tiene registrada. Si no conoces alguna opción puedes consultar el manual en línea: `man fstab`.

```console
# cat /etc/fstab
#
# /etc/fstab
# <file system>             <mount point>   <type>  <options>                                       <dump>  <pass>
#
LABEL=ROOT					/		                auto,noatime                                        1 1
tmpfs						/dev/shm	    tmpfs	defaults		                                    0 0
tmp						    /tmp		    tmpfs	rw,mode=1777,fscontext=system_u:object_r:tmp_t:s0	0 0
devpts						/dev/pts	    devpts	gid=5,mode=620			                            0 0
sysfs						/sys		    sysfs	defaults	                                        0 0
proc						/proc		    proc	defaults	                                        0 0
[root@localhost /]#
```

Vemos que tiene la opción `noatime`. Esta sirve para no modificar la fecha de acceso (*access time*) a cada archivo cada vez que se accede, ganando así en rendimiento.

El modo *620* es equivalente a `chmod * 620`. En el manual de `fstab`, podemos encontrar el siguiente mensaje:
> A value of mode=620 and gid=5 makes "mesg y" the default on newly created pseudo terminals.

En este caso, nos informa de que las pseudo terminales que se inicien en el filesystem *devpts* tienen por defecto el comando `mesg` al valor `y (yes)`.


## Actividad 1.11. Archivos de información para los SAs
Compara la información que contienen los cuatro archivos de texto que se han presentado en este apartado (`/etc/fstab`, `/etc/mtab`, `/proc/filesystems` y `/proc/mounts`). Describe en un párrafo para qué te sirve la información que registra cada archivo.
1. `/etc/fstab`
Este archivo contiene la información sobre los distintos tipos de filesystems que se han montado en el boot. Está descrito en la actividad anterior.

2.  `/etc/mtab`
Este archivo contiene la información sobre los filesystem que ya han sido montados en el ordenador. No obstante, en sistemas modernos contiene un enlace simbólico a `proc/mounts`, como podemos ver aquí:
    ```console
    # ls -l /etc/mtab
    lrwxrwxrwx 1 root root 19 abr 18 02:41 /etc/mtab -> ../proc/self/mounts
    ```

3. `/proc/filesystems`
Contiene los distintos tipos de filesystem disponibles. Se corresponden al campo `<type>` del fichero `/etc/fstab`. Veamos que los tipos de dicho archivo se encuentran en este:
    ```console
    # cat /proc/filesystems
    nodev	sysfs
    ...
    nodev	proc
    ...
    nodev	tmpfs
    ...
    nodev	devpts
    ...
    ```
    donde `...` representa que había una gran cantidad de tipos entre ambas líneas.

4. `/proc/mounts`

    Este archivo contiene los filesystem que actualmente hay montados en el ordenador. 
    ```console
    # cat /proc/mounts
    rootfs      /                           rootfs      rw                                                  0 0
    /dev/root   /                           ext4        rw,noatime,user_xattr,acl,barrier=1,data=ordered    0 0
    none        /proc                       proc        rw,nosuid,nodev,noexec,relatime                     0 0
    none        /sys                        sysfs       rw,nosuid,nodev,noexec,relatime                     0 0
    devpts      /dev/pts                    devpts      rw,relatime,gid=5,mode=620                          0 0
    /tmp        /tmp                        tmpfs       rw,relatime                                         0 0
    none        /proc/sys/fs/binfmt_misc    binfmt_misc rw,relatime                                         0 0
    ```