# Sistemas Operativos. Examen I de Prácticas.

**Autor:** Jose Juan Urrutia Milán 'JJ'.<br>
**Autor:** Arturo Olivares Martos.
***

- **Asignatura:** Sistemas Operativos.
- **Curso Académico:** 2023-24.
- **Grado:** Doble Grado en Ingeniería Informática y Matemáticas.
- **Grupo:** A.
- **Profesor:** Alejandro José León  Salas.
- **Descripción:** Examen de Prácticas del Módulo I (Prácticas 1-4).
- **Fecha:** 23 de octubre de 2023.
- **Duración:** 105 minutos.
- **Observaciones:** Los enunciados no son literalmente los descritos en el examen, ya que son los que se han recordado tras la finalización del examen.



## Ejercicio 1.<small style="font-size: 0.9rem; margin-left: 1rem;">[2.5 puntos]</small>

1. Cree un usuario con el comando `adduser` con `username=user1` y directorio `home=home_user1`. ¿Se le añade una contraseña por defecto? Menciona el archivo de configuración del sistema en el que puedas consultar esta información, especificando la línea del archivo que usas para responder a esta pregunta.

    ```console
    # adduser --home /home_user1 user1
    ```

    Veamos ahora si se le añade una contraseña por defecto:
    ```console
    # cat /etc/passwd | grep user1
    user1:x:500:500::/home_user1:/bin/bash
    ```
    Vemos que en el campo de la contraseña contiene `x`, por lo que la contraseña está encriptada. Veamos el archivo correspondiente a las contraseñas encriptadas:
    ```console
    # cat /etc/shadow | grep user1
    user1:!!:19653:0:99999:7:::
    ```
    En el manual de este archivo (`man 5 shadow`), podemos leer:
    > A password field which starts with an exclamation mark means that the password is locked. The remaining characters on the line represent the password field before the password was locked.

    > If the password field contains some string that is not a valid result of `crypt(3)`, for instance ! or *, the user will not be able to use a unix password to log in (but the user may log in the system by other means).

    Por tanto, como podemos leer, la contraseña de `user1` está bloqueada, y antes de bloquearla leyendo el archivo podríamos pensar que era `!`. No obstante, tenemos que esta no es una salida válida para la orden de encriptamiento, por lo que tenemos que no se le asigna ninguna contraseña por defecto

    Además, `user1` no podrá iniciar sesión hasta que no contenga una contraseña válida.
   

2. Especifica el archivo de configuración que contiene en formato `clave=valor` la variable por defecto que especifica el número máximo de días que el usuario `user1` puede usar su contraseña. Especifique explícitamente el nombre de la clave y su valor dentro de este archivo. A continuación, especifica el archivo de configuración en el que se guardan las especificaciones reales de envejecimiento de contraseña del usuario `user1`, especificando el nombre de cada campo.

    Para ver los valores por defecto de los parámetros de envejecimiento de contraseñas y usuarios, acudimos al archivo `/etc/login.defs`. En él, podemos encontrar:
    ```bash
    # Password aging controls:
    #
    #	PASS_MAX_DAYS	Maximum number of days a password may be used.
    #	PASS_MIN_DAYS	Minimum number of days allowed between password changes.
    #	PASS_MIN_LEN	Minimum acceptable password length.
    #	PASS_WARN_AGE	Number of days warning given before a password expires.
    #
    PASS_MAX_DAYS	99999
    PASS_MIN_DAYS	0
    PASS_MIN_LEN	5
    PASS_WARN_AGE	7
    ```

    Por tanto, tenemos que la clave descrita en el enunciado es `PASS_MAX_DAYS`, que tiene un valor por defecto de 99999 días.


    Respecto a los valores actuales, estos se encuentran en `/etc/shadow`. Sus campos, separados por `:` son:
    * Login Name.
    * Contraseña encriptada.
    * Fecha de último cambio de la contraseña.
    * Edad mínima de la contraseña para poder cambiarla, en días.
    * Edad máxima de la contraseña sin cambiarla, en días.
    * Periodo de aviso de contraseña: Número de días antes de la edad máxima de la contraseña, en los que se avisa al usuario.
    * Periodo de inactividad de la contraseña: Número de días tras la edad máxima de la contraseña en la que se permite iniciar sesión, obligando a cambiarla inmediatamente.
    * Fecha de expiración de la cuenta: Fecha en la que la cuenta deja de ser accesible.

    En el archivo `/etc/shadow` (salida mostrada arriba), vemos que `user1` tiene el valor de `PASS_MAX_DAYS` por defecto, 99999.

   

3. Escriba exactamente qué significan las opciones `atime` y `noexec` que aparecen en el archivo de configuración `/etc/fstab` usando la orden `man`.

    En el manual de dicho archivo, tenemos lo siguiente:
    > **The fourth field (fs_mntops)**.
    >
    > This field describes the mount options associated with the filesystem.
    > 
    > It is formatted as a comma-separated list of options. It contains at least the type of mount (**ro** or **rw**), plus any additional options appropriate to the filesystem type (including performance-tuning options). For details, see **mount**(8) or **swapon**(8).


    Por tanto, consultamos el manual de `mount` para ver la información sobre las opciones. En él, encontramos:
    > **atime**
    >
    > Do not use the noatime feature, so the inode access time is controlled by kernel defaults. See also the descriptions of the relatime and strictatime mount options.

    > **noatime**
    >
    > Do not update inode access times on this filesystem (e.g. for faster access on the news spool to speed up news servers). This works for all inode types (directories too), so it implies nodiratime.

    Por tanto, vemos que `atime` sirve para que la hora a la que se ha accedido a cada inodo sea controlada por el kernel. Con la orden `noatime`, esta hora no se actualiza. Veamos ahora la opción `noexec`:
    > **noexec**
    > 
    > Do not permit direct execution of any binaries on the mounted filesystem.

    Por tanto, tenemos que sirve para que en el dispositivo que se monte no se puedan ejecutar archivos binarios.




## Ejercicio 2.<small style="font-size: 0.9rem; margin-left: 1rem;">[3 puntos]</small>
1. Cree un archivo de dispositivo `/dev/loop0` y asígnele un tamaño de `40MB`. Cree una partición y especifique el número de cabezas, sectores por pista y cilindros de la partición.

    En primer lugar, creamos el archivo `/dev/loop0`:
    ```console
    # mknod /dev/loop0 b 7 0
    ```

    Ahora, creamos el archivo de 40MB que va a sostener nuestra partición, ya que no se trata de un dispositivo físico sino simulado. Esto se hace con la siguiente orden:
    ```console
    # dd if=/dev/zero of=/root/DIR/archivo_SA40 bs=4KB count=10000
    10000+0 records in
    10000+0 records out
    40000000 bytes (40 MB) copied, 0.283562 s, 141 MB/s
    ```

    Asignamos ahora al dispositivo el archivo de los 40MB:
    ```console
    # losetup /dev/loop0 /root/DIR/archivo_SA40
    ```

    Por tanto, ya tenemos nuestro dispositivo simulado. Creamos ahora la partición. Para ello, usamos la orden `fdisk /dev/loop0`, que muestra un menú interactivo para hacer la partición. Una vez creada, la información pedida se obtiene con la opción `-l` como sigue:
    ```console
    # fdisk -l /dev/loop0 

    Disk /dev/loop0: 40 MB, 40000000 bytes
    221 heads, 5 sectors/track, 70 cylinders, total 78125 sectors
    Units = sectors of 1 * 512 = 512 bytes
    Sector size (logical/physical): 512 bytes / 512 bytes
    I/O size (minimum/optimal): 512 bytes / 512 bytes
    Disk identifier: 0x2bc90105

        Device Boot      Start         End      Blocks   Id  System
    /dev/loop0p1            2048       78124       38038+  83  Linux
    ```

    Por tanto, vemos que tiene 221 cabezas, 5 sectores por pista y 70 cilindros.


2. Formatee lógicamente el archivo creado y asígnele un sistema de archivos `ext2`. Especifique:
- El número de grupos de cilindros.
- El número de inodos totales. El número de inodos por grupo. El tamaño de un inodo.
- El número de bloques por grupo. El número total de bloques libres. El tamaño de un bloque.

    Tenemos que la asignación del SA de hace de la siguiente forma:
    ```console
    # mke2fs -t ext2 /dev/loop0 
    mke2fs 1.41.12 (17-May-2010)
    Filesystem label=
    OS type: Linux
    Block size=1024 (log=0)
    Fragment size=1024 (log=0)
    Stride=0 blocks, Stripe width=0 blocks
    9800 inodes, 39060 blocks
    1953 blocks (5.00%) reserved for the super user
    First data block=1
    Maximum filesystem blocks=40108032
    5 block groups
    8192 blocks per group, 8192 fragments per group
    1960 inodes per group
    Superblock backups stored on blocks: 
        8193, 24577

    Writing inode tables: done                            
    Writing superblocks and filesystem accounting information: done

    This filesystem will be automatically checked every 31 mounts or
    180 days, whichever comes first.  Use tune2fs -c or -i to override.
    ```

    Para ver la información pedida, usamos la siguiente orden:
    ```console
    # tune2fs -l /dev/loop0 
    tune2fs 1.41.12 (17-May-2010)
    Filesystem volume name:   <none>
    Last mounted on:          <not available>
    Filesystem UUID:          ca8ec685-bbcd-47c5-bbdc-a0ed0f6d66ce
    Filesystem magic number:  0xEF53
    Filesystem revision #:    1 (dynamic)
    Filesystem features:      ext_attr resize_inode dir_index filetype sparse_super
    Filesystem flags:         signed_directory_hash 
    Default mount options:    (none)
    Filesystem state:         clean
    Errors behavior:          Continue
    Filesystem OS type:       Linux
    Inode count:              9800
    Block count:              39060
    Reserved block count:     1953
    Free blocks:              37348
    Free inodes:              9789
    First block:              1
    Block size:               1024
    Fragment size:            1024
    Reserved GDT blocks:      152
    Blocks per group:         8192
    Fragments per group:      8192
    Inodes per group:         1960
    Inode blocks per group:   245
    Filesystem created:       Mon Oct 23 16:45:54 2023
    Last mount time:          n/a
    Last write time:          Mon Oct 23 16:45:54 2023
    Mount count:              0
    Maximum mount count:      31
    Last checked:             Mon Oct 23 16:45:54 2023
    Check interval:           15552000 (6 months)
    Next check after:         Sat Apr 20 16:45:54 2024
    Reserved blocks uid:      0 (user root)
    Reserved blocks gid:      0 (group root)
    First inode:              11
    Inode size:	          128
    Default directory hash:   half_md4
    Directory Hash Seed:      de8bb155-5f40-4d29-b6af-6d31d4a78ee4
    ```

    Vemos que tiene:
    - El número de grupos de cilindros.
    
    - El número de inodos totales: 9800.
    
        El número de inodos por grupo: 1960.
    
        El tamaño de un inodo: 128 bytes.

    - El número de bloques por grupo: 8192
    
        El número total de bloques libres: 37348
    
        El tamaño de un bloque: 1024 bytes.


3.  Monte el sistema de archivos creado en `/mnt/tmp` con opciones de lectura y escritura y que no permita la ejecución de binarios dentro del sistema de archivos.

    Tenemos que se hace con la siguiente instrucción:
    ```console
    # mount /dev/loop0 /mnt/tmp -o rw,noexec
    ```

## Ejercicio 4.<small style="font-size: 0.9rem; margin-left: 1rem;">[4.5 puntos]</small>
1. Usando la orden `top`, especifique qué campos registran el uso de CPU respecto a:
   - Procesos que se ejecutan con un nice modificado.
   - Rutinas de Servicio de Interrupciones.
  
    Con un proceso de ejemplo, especifique sus valores de `%MEM` y `SHR`, indicando qué significan estos campos.

    Para ver lo primero, ejecutamos la orden `top` y consultamos su manual:
    ```console
    top - 17:47:14 up 9 min,  1 user,  load average: 0.00, 0.04, 0.05
    Tasks:  38 total,   1 running,  37 sleeping,   0 stopped,   0 zombie
    Cpu(s):  0.0%us,  0.0%sy,  0.0%ni,100.0%id,  0.0%wa,  0.0%hi,  0.0%si,  0.0%st
    Mem:   1019384k total,    57156k used,   962228k free,    20088k buffers
    Swap:        0k total,        0k used,        0k free,    18488k cached

      PID USER      PR  NI  VIRT  RES  SHR S %CPU %MEM    TIME+  COMMAND                                                                                  
        1 root      20   0  2884 1320 1152 S  0.0  0.1   0:00.27 init
      ...
     1184 root      20   0  3792 1184  636 S  0.0  0.1   0:00.00 crond 

      ...
    ```

    Por tanto, tenemos que los campos del uso CPU están especificados en la tercera línea. En el manual de `top`, encontramos:
    > **ni, nice**    : time running niced user processes
    >
    > **si** : time spent servicing software interrupts

    Por tanto, tenemos que el porcentaje de la CPU ejecutando procesos con un nice modificado es, en este caso, 0%. Asimismo, el tiempo ejecutando RSI es también un 0%.

    Para el programa de ejemplo, `crond` tenemos que `%MEM=0.01` y `SHR=636`. El manual informa de lo que significa cada valor:
    > **%MEM**  --  Memory Usage (RES)
    >
    > A task's currently resident share of available physical memory.

    > **SHR**  --  Shared Memory Size (KiB)
    >
    > A subset of resident memory (RES) that may be used by other processes.  It will include shared anonymous pages and  shared  file-backed pages.  It also includes private pages mapped to files representing program images and shared libraries.

    Tenemos que `%MEM` indica el porcentaje de la memoria física ocupado por ese proceso, y `SHR` es la cantidad de memoria compartida que puede usar por otros procesos. Se expresa en `KiB`.


2. Especifique con qué comando puede consultar los siguientes aspectos respecto a la memoria:

   - El uso de memoria del sistema.
  
        Para esto, tenemos varios comandos, como vemos a continuación:
        ```console
        # free
                    total       used       free     shared    buffers     cached
        Mem:       1019384      57412     961972          0      20160      18720
        -/+ buffers/cache:      18532    1000852
        Swap:            0          0          0

        # vmstat
        procs -----------memory---------- ---swap-- -----io---- --system-- -----cpu-----
        r  b   swpd   free   buff  cache   si   so    bi    bo   in   cs us sy id wa st
        0  0      0 961972  20160  18720    0    0    18     9  103    9  0  0 100  0  0
        ```

   - El uso de memoria de un proceso.

        Sabiendo el `PID`, tenemos que se puede consultar de la siguiente manera:
        ```console
        # ps -f --pid 1
        UID        PID  PPID  C STIME TTY          TIME CMD
        root         1     0  0 17:38 ?        00:00:00 /sbin/init
        ```

   - Ver por separado la memoria en caché y en buffers del sistema.

        Esto depende de la versión de las órdenes `free` y `vmstat`, ya que ambas pueden mostrarlo. Veámoslo:
        ```console
        # free
                    total       used       free     shared    buffers     cached
        Mem:       1019384      57412     961972          0      20160      18776
        -/+ buffers/cache:      18476    1000908
        Swap:            0          0          0
        # vmstat
        procs -----------memory---------- ---swap-- -----io---- --system-- -----cpu-----
        r  b   swpd   free   buff  cache   si   so    bi    bo   in   cs us sy id wa st
        0  0      0 961972  20160  18776    0    0    16     8  102    8  0  0 100  0  0
        ```
        Como podemos ver, ambos comandos muestran la información separada en buffers y caché. No obstante, en las versiones más modernas de `free` es necesario usar `-w`.


3. Cree un guión que imprima exclusivamente el tamaño de la RAM total y la libre por el sistema:

    Al consultar el manual de `free`, tenemos que este toma la información de `/proc/meminfo`. Además, vemos que lo pedido coincide con las dos primeras líneas de dicho archivo. Por tanto, el script queda:
    ```bash
    #!/bin/bash

    cat /proc/meminfo | head -2
    ```

    La salida es:
    ```console
    # /root/usg_RAM.sh 
    MemTotal:        1019384 kB
    MemFree:          961188 kB
    ```


4. Cree un archivo en el directorio `root` llamado `log`. Queremos ir añadiendo la salida del guión anterior en el archivo `log` creado todos los Lunes, Miércoles y Viernes de Marzo a las 3h y 55 minutos. Especifique qué sería necesario para crear esta funcionalidad. Para probar esta función, ejecútela a cada minuto de hoy.

    En primer lugar, creamos el archivo:
    ```console
    # touch /root/log
    ```

    Para crear esta funcionalidad, usamos el demonio `cron`. para ello, modificamos la `crontab` usando `crontab -e`. En ella, ponemos:
    ```
    55 3 * 3 1,3,5  /root/script>>/root/log
    ```

    Esto provocará que ese script se ejecute a las 3:55 de los lunes, miércoles y viernes de marzo, guardando la salida en `/root/log`. Para ejecutarlo cada minuto, volvemos a modificar la `crontab`, poniendo ahora:
    ```
    * * * * *  /root/script>>/root/log
    ```

    Vemos ahora que:
    ```console
    # cat /root/log
    MemTotal:        1019384 kB
    MemFree:          960512 kB
    MemTotal:        1019384 kB
    MemFree:          960512 kB
    ```
    Por tanto, podemos ver que se ha ejecutado dos veces distintas.