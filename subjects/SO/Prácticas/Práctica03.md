# Sistemas Operativos. Práctica 03.

**Autor:** Arturo Olivares Martos
***

- **Asignatura:** Sistemas Operativos.
- **Curso Académico:** 2023-24.
- **Grado:** Doble Grado en Ingeniería Informática y Matemáticas.
- **Grupo:** Único.
- **Profesor:** Alejandro José León Salas
- **Descripción:** Sesión 3 del Módulo I de las prácticas de SO.
<!--- **Fecha:** 17 de abril de 2023. -->
<!-- - **Duración:** -->


## Actividad 3.1. Consulta de estadísticas del sistema

Responde a las siguientes cuestiones y especifica, para cada una, la opción que has utilizado (para ello utiliza `man` y consulta las opciones de las órdenes anteriormente vistas)

```console
# uptime   
19:21:53 up  6:32,  1 user,  load average: 0.00, 0.01, 0.01
```

1. ¿Cuánto tiempo lleva en marcha el sistema?
   
   6 horas, 32 minutos.

2. ¿Cuántos usuarios hay trabajando?
   
    Un usuario. 

3.  ¿Cuál es la carga media del sistema en los últimos 15 minutos?
   
    0.01, por ser este el tercer valor. Se muestran los de los últimos 1, 5 y 15 minutos, respectivamente.


## Actividad 3.2. Prioridad de los procesos
1.  Crea un script o guión shell que realice un ciclo de un número variable de iteraciones en el que se hagan dos cosas: una operación aritmética y el incremento de una variable. Cuando terminen las iteraciones escribirá en pantalla un mensaje indicando el valor actual de la variable. Este guión debe tener un argumento que es el número de iteraciones que va a realizar.

    ```bash
    #!/bin/bash

    if [[ $# -ne 1 ]]; then
        echo "Número incorrecto de parámetros"
        exit 1
    fi

    x=0

    for ((i=0; i<$1; i++)); do
        x=$(( x + 1 ))
    done

    printf "El valor de la variable es %d.\n\n" $x

    printf "Mi PID es $$.\n\n"
    ps -ef | grep $$
    ```
    donde el comando `ps` se ha añadido para resolver el tercer apartado. 

    La ejecución es:
    ```console
    $ ./prueba_procesos 1000  
    El valor de la variable es 1000.

    Mi PID es 1321.

    root      1321  1210  0 05:51 tty0     00:00:00 /bin/bash ./prueba_procesos 1000
    root      1322  1321  0 05:51 tty0     00:00:00 ps -ef
    root      1323  1321  0 05:51 tty0     00:00:00 grep 1321
    ```

2. Ejecuta el guión anterior varias veces en background (segundo plano) y comprueba su prioridad inicial. Cambia la prioridad de dos de ellos, a uno se la aumentas y a otro se la disminuyes, ¿cómo se comporta el sistema para estos procesos?

    En primer lugar lo lanzamos en segundo plano varias veces:
   ```console
    # ./prueba_procesos 1000000 &
    [1] 1305
    [root@localhost ~]# ./prueba_procesos 1000000 &
    [2] 1306
    [root@localhost ~]# ./prueba_procesos 1000000 &
    [3] 1307
    ```
    
    Consolutamos ahora su prioridad inicial:
    ```console
    # top 
    ...
    PID USER      PR  NI  VIRT  RES  SHR S %CPU %MEM    TIME+  COMMAND                       
    1305 root      20   0  3120 1088  964 R 34.4  0.1   0:15.93 prueba_procesos               
    1306 root      20   0  3120 1096  964 R 33.4  0.1   0:16.76 prueba_procesos               
    1307 root      20   0  3120 1092  964 R 32.1  0.1   0:15.59 prueba_procesos  
    ...
    ```
    
    Como podemos ver, su prioridad inicial es 20, y no se ha modificado ya que `NI=0`. Modificamos ahora las prioridades:
    ```console
    # renice 10 1306
    1306: old priority 0, new priority 10
    # renice -10 1307
    1307: old priority 0, new priority -10
    ```
    
    Vemos ahora la consecuencia que tiene:
    ```console
    # top 
    ...
    PID USER      PR  NI  VIRT  RES  SHR S %CPU %MEM    TIME+  COMMAND                       
    1307 root      10 -10  3120 1096  964 R 89.7  0.1   0:56.56 prueba_procesos               
    1305 root      20   0  3120 1088  964 R  8.9  0.1   0:29.01 prueba_procesos               
    1306 root      30  10  3120 1088  964 R  1.6  0.1   0:18.24 prueba_procesos
    ...
    ```
    Como podemos ver, se modifica la prioridad. Los que tienen prioridad más baja vemos que usan más procentaje de la CPU y más tiempo de computación también.

5. Obtén los tiempos de finalización de cada uno de los guiones del apartado anterior.

        Una vez terminen, se imprime el tiempo de finalización de cada uno en la columna `TIME` de `ps`. No obstante, esto no funciona en el *UML*.


## Actividad 3.3. Jerarquía e información de procesos
1. La orden pstree muestra el árbol de procesos que hay en ejecución. Comprueba que la
jerarquía mostrada es correcta haciendo uso de la orden ps y de los valores “PID" y “PPID" de
cada proceso.

    Veamos la salida de `pstree -p`, donde añado la opción `-p` para que se vea el `PID`:
    ```console
    # pstree -p
    init(1)-+-auditd(1095)---{auditd}(1096)
            |-crond(1176)
            |-login(1188)---bash(1189)---pstree(1322)
            |-rsyslogd(1113)-+-{rsyslogd}(1116)
            |                |-{rsyslogd}(1117)
            |                `-{rsyslogd}(1310)
            |-sendmail(1164)
            `-sshd(1138)
    ```

    Veamos ahora la salida de `ps -eo comm,pid,ppid`, donde la `-e` indica que se seleccionan todos los procesos, y `-o` indica que se usan las opciones indicadas, que este caso son `comm` (nombre del comando), `PID` y `PPID`.
    ```console
    # ps -eo comm,pid,ppid
    COMMAND           PID  PPID
    init                1     0
    kthreadd            2     0
    ksoftirqd/0         3     2
    kworker/0:0         4     2
    kworker/u:0         5     2
    rcu_kthread         6     2
    watchdog/0          7     2
    cpuset              8     2
    khelper             9     2
    kworker/u:1        10     2
    sync_supers       115     2
    bdi-default       117     2
    kblockd           118     2
    rpciod            134     2
    kworker/0:1       135     2
    khungtaskd        143     2
    kswapd0           144     2
    fsnotify_mark     192     2
    ecryptfs-kthrea   216     2
    nfsiod            218     2
    glock_workqueue   240     2
    delete_workqueu   241     2
    gfs_recovery      246     2
    crypto            248     2
    kthrotld          263     2
    jbd2/ubda-8       961     2
    ext4-dio-unwrit   962     2
    kauditd          1057     2
    auditd           1095     1
    rsyslogd         1113     1
    sshd             1138     1
    sendmail         1164     1
    crond            1176     1
    login            1188     1
    bash             1189  1188
    flush-98:0       1320     2
    ps               1323  1189
    ```

    Es fácil ver que el `PPID` de cada proceso coincide con el que se puede ver en el árbol de procesos de `pstree`. Por ejemplo, es fácil ver la relación `init(1) -- login(1188) -- bash(1189) -- ps(1323)`.


2.  Ejecuta la orden ps con la opción -A, ¿qué significa que un proceso tenga un carácter “?” en
la columna etiquetada como TTY?

    La opción `-A` es equivalente a `-e`. Tenemos que:
    ```console
    # ps -A
    PID TTY          TIME CMD
        1 ?        00:00:00 init
        2 ?        00:00:00 kthreadd
        3 ?        00:00:01 ksoftirqd/0
        4 ?        00:00:00 kworker/0:0
        5 ?        00:00:00 kworker/u:0
        6 ?        00:00:00 rcu_kthread
        7 ?        00:00:00 watchdog/0
        8 ?        00:00:00 cpuset
        9 ?        00:00:00 khelper
    10 ?        00:00:00 kworker/u:1
    115 ?        00:00:00 sync_supers
    117 ?        00:00:00 bdi-default
    118 ?        00:00:00 kblockd
    134 ?        00:00:00 rpciod
    135 ?        00:00:00 kworker/0:1
    143 ?        00:00:00 khungtaskd
    144 ?        00:00:00 kswapd0
    192 ?        00:00:00 fsnotify_mark
    216 ?        00:00:00 ecryptfs-kthrea
    218 ?        00:00:00 nfsiod
    240 ?        00:00:00 glock_workqueue
    241 ?        00:00:00 delete_workqueu
    246 ?        00:00:00 gfs_recovery
    248 ?        00:00:00 crypto
    263 ?        00:00:00 kthrotld
    961 ?        00:00:00 jbd2/ubda-8
    962 ?        00:00:00 ext4-dio-unwrit
    1057 ?        00:00:00 kauditd
    1095 ?        00:00:00 auditd
    1113 ?        00:00:00 rsyslogd
    1138 ?        00:00:00 sshd
    1164 ?        00:00:00 sendmail
    1176 ?        00:00:00 crond
    1188 ?        00:00:00 login
    1189 tty0     00:00:00 bash
    1324 tty0     00:00:00 ps
    ```

    Las siglas `tty` significan *Teletypewriters*, y se refieren a las terminales abiertas. Los procesos con `tty ?` no tienen terminal asociada, por lo que se ejecutan aunque se cierre la terminal.



## Actividad 3.4. Estadísticas de recursos del sistema
Responde a las siguientes cuestiones y especifica, para cada una, la orden que has utilizado:
1.  ¿Qué porcentaje de tiempo de CPU se ha usado para atender interrupciones hardware?

    Suponiendo que se refiere desde que se inició el sistema, se puede obtener con la orden `mpstat` sin parámetros, con la información que proporciona `%irq`.
    ```console
    # mpstat
    Linux 3.0.4 (localhost) 	10/12/23 	_i686_	(1 CPU)

    16:20:39     CPU    %usr   %nice    %sys %iowait    %irq   %soft  %steal  %guest   %idle
    16:20:39     all    1.33    0.19    0.16    0.02    0.00    0.00    0.00    0.00   98.30
    ```

    En este caso, tenemos que es del 0%. 

2.  ¿Y qué porcentaje en tratar interrupciones software?

    De igual forma, suponiendo que se refiere desde que se inició el sistema, se puede obtener con la orden `mpstat` sin parámetros, con la información que proporciona `%sirq`.

    En este caso, tenemos que es del 0% también.

3. ¿Cuánto espacio de swap está libre y cuánto ocupado?

    Esto se obtiene con las primeras líneas de la instrucción `top`:
    ```console
    # top

    top - 22:24:34 up  5:31,  1 user,  load average: 0,63, 0,42, 0,33
    Tasks: 269 total,   1 running, 260 sleeping,   8 stopped,   0 zombie
    %Cpu(s):  2,7 us,  1,6 sy,  0,0 ni, 95,6 id,  0,0 wa,  0,0 hi,  0,1 si,  0,0 st
    MiB Mem :   7836,0 total,   1390,9 free,   2690,4 used,   3754,8 buff/cache
    MiB Swap:   2048,0 total,   2048,0 free,      0,0 used.   4099,3 avail Mem 

        PID USER      PR  NI    VIRT    RES    SHR S  %CPU  %MEM     TIME+ COMMAND                                                                        
    1542 arturoo+  20   0 5055232 298856 133136 S   6,0   3,7   3:36.48 gnome-shell                                                                    
    2681 arturoo+  20   0  835328  61132  45144 S   2,7   0,8   1:08.66 gnome-terminal-                                                                
    4331 arturoo+  20   0 1052508  88216  87700 S   1,0   1,1   9:28.91 kernel32-3.0.4                                                                 
        1 root      20   0  168256  13336   8240 S   0,3   0,2   0:04.64 systemd                                                                        
        92 root       0 -20       0      0      0 I   0,3   0,0   0:05.36 kworker/u9:0-i915_flip  
        ...
        ...
        ...
    ```

    Podemos ver que en total hay 2048 MiB de swap, y toda está libre.

## Actividad 3.5. Utilización de las órdenes `free` y `watch`
Explora las opciones de las que consta la orden `free` prestando especial atención a las diferentes unidades de medida según las que puede informar acerca de memoria. Además, compare los resultados con los obtenidos usando la orden `watch`.

Tenemos que las opciones de `free` son:
```console
usage: free [-b|-k|-m|-g] [-l] [-o] [-t] [-s delay] [-c count] [-V]
  -b,-k,-m,-g show output in bytes, KB, MB, or GB
  -l show detailed low and high memory statistics
  -o use old format (no -/+buffers/cache line)
  -t display total for RAM + swap
  -s update every [delay] seconds
  -c update [count] times
  -V display version information and exit
```

Por tanto, vemos que para expresar la salida en distintas unidades, se usan las opciones `[-b|-k|-m|-g]`.

Además, si queremos actualizar la salida cada $n$ segundos, tenemos que son equivalentes:
```console
# free -s n
# watch -n 2 free
```
Esto se debe a que `watch` ejecuta el comando que se le pasa como opción de forma repetida.



## Actividad 3.6. Utilización de `vmstat`
Intente reproducir el escenario justo descrito anteriormente supervisando la actividad del sistema mediante la ejecución periódica de `vmstat` tal cual se ha descrito, y proporcione como muestra la salida almacenada en un archivo de texto.


## Actividad 3.7. Consulta de metadatos de archivo

1. Anota al menos dos nombres de archivo de dispositivo de bloques y dos nombres de dispositivo de caracteres de tu sistema UML.
   
   ```console
   # ls /dev -l 
    total 12
    crw------- 1 root root 5, 1 Oct 12 10:55 console
    crw-rw-rw- 1 root root 1, 7 Nov  3  2010 full
    -rw-r--r-- 1 root root   54 Sep 13  \t 2011 kmsg
    srw-rw-rw- 1 root root    0 Oct 12 10:55 log
    brw-r--r-- 1 root root 7, 0 Oct  9 17:38 loop0
    brw-r--r-- 1 root root 7, 1 Oct  9 17:43 loop1
    drwxr-xr-x 2 root root 4096 Nov  3  2010 mapper
    crw-rw-rw- 1 root root 1, 3 Nov  3  2010 null
    crw-rw-rw- 1 root root 5, 2 Nov  3  2010 ptmx
    drwxr-xr-x 2 root root    0 Oct 12 10:55 pts
    crw-rw-rw- 1 root root 1, 8 Nov  3  2010 random
    drwxr-xr-x 2 root root 4096 Nov  3  2010 shm
    lrwxrwxrwx 1 root root   15 Nov  3  2010 stderr -> /proc/self/fd/2
    lrwxrwxrwx 1 root root   15 Nov  3  2010 stdin -> /proc/self/fd/0
    lrwxrwxrwx 1 root root   15 Nov  3  2010 stdout -> /proc/self/fd/1
    crw-rw-rw- 1 root root 5, 0 Nov  3  2010 tty
    crw--w---- 1 root tty  4, 0 Oct 12 17:02 tty0
    cr--r--r-- 1 root root 1, 9 Nov  3  2010 urandom
    crw-rw-rw- 1 root root 1, 5 Nov  3  2010 zero
   ```

   Tenemos que dos ejemplos de archivos de dispositivos de bloques son `/dev/loop0` y `/dev/loop1`. Dos ejemplos de dispoitivos de caracteres son `/dev/null` o `/dev/zero.`

   
2. Anota los nombres de los archivos ocultos de tu directorio de inicio como usuario root que tienen relación con el intérprete de órdenes que tienes asignado por defecto. Ahora efectúa la misma tarea pero en una consola de terminal del sistema Ubuntu que arrancas inicialmente en el laboratorio de prácticas. ¿Qué diferencias encuentras entre los nombres de los archivos?


    En el UML, tengo que los archivos son:
    ```console
    # ls -la       
    total 50036
    dr-xr-x---  2 root root     4096 Oct 12 17:09 .
    dr-xr-xr-x 22 root root     4096 Oct 12 10:55 ..
    -rw-------  1 root root       53 Sep 13  \t 2011 .bash_history
    -rw-r--r--  1 root root       18 Mar 30  2009 .bash_logout
    -rw-r--r--  1 root root      176 Mar 30  2009 .bash_profile
    -rw-r--r--  1 root root      176 Sep 22  2004 .bashrc
    -rw-r--r--  1 root root      100 Sep 22  2004 .cshrc
    -rw-r--r--  1 root root      129 Dec  3  2004 .tcshrc
    -rw-r--r--  1 root root 20480000 Oct  9 17:38 archivo_SA20
    -rw-r--r--  1 root root 30720000 Oct 10 03:09 archivo_SA30
    -rwxr-xr-x  1 root root      190 Oct 12 10:57 prueba_procesos
    ```


    En mi SO local, tengo que son:
    ```console
    $ ls -la
    total 140
    drwxr-x--- 22 arturo arturo  4096 oct 12 23:14 .
    drwxr-xr-x  3 root        root         4096 abr 18 02:41 ..
    -rw-------  1 arturo arturo 26977 oct 12 16:50 .bash_history
    -rw-r--r--  1 arturo arturo   220 abr 18 02:41 .bash_logout
    -rw-r--r--  1 arturo arturo  3771 abr 18 02:41 .bashrc
    drwx------ 18 arturo arturo  4096 oct  9 13:41 .cache
    drwx------ 20 arturo arturo  4096 oct 10 15:56 .config
    drwxr-xr-x  6 arturo arturo  4096 oct  9 14:05 Desktop
    drwxr-xr-x  2 arturo arturo  4096 abr 18 02:47 Documents
    drwxrwxr-x  3 arturo arturo  4096 oct  9 14:13 .dotnet
    drwxr-xr-x  4 arturo arturo  4096 oct 12 21:58 Downloads
    -rw-rw-r--  1 arturo arturo   115 oct 10 15:25 .gitconfig
    drwx------  2 arturo arturo  4096 oct 11 15:31 .gnupg
    drwxrwxr-x  2 arturo arturo  4096 abr 18 02:48 .gphoto
    drwxrwxr-x  4 arturo arturo  4096 sep 26 10:57 .java
    -rw-------  1 arturo arturo   282 oct 12 23:14 .lesshst
    drwx------  3 arturo arturo  4096 abr 18 02:47 .local
    drwxr-xr-x  2 arturo arturo  4096 abr 18 02:47 Music
    drwxr-xr-x  3 arturo arturo  4096 oct 11 15:33 Pictures
    drwx------  3 arturo arturo  4096 oct  9 13:59 .pki
    -rw-r--r--  1 arturo arturo   807 abr 18 02:41 .profile
    drwxr-xr-x  2 arturo arturo  4096 abr 18 02:47 Public
    drwx------  7 arturo arturo  4096 sep 26 10:57 snap
    drwx------  2 arturo arturo  4096 abr 18 03:28 .ssh
    -rw-r--r--  1 arturo arturo     0 abr 18 02:50 .sudo_as_admin_successful
    drwxr-xr-x  2 arturo arturo  4096 abr 18 02:47 Templates
    drwxrwxr-x 32 arturo arturo  4096 oct 12 16:55 .uml
    drwxr-xr-x  2 arturo arturo  4096 abr 18 02:47 Videos
    drwxrwxr-x  4 arturo arturo  4096 oct  9 13:59 .vscode
    ```

    Podemos ver que, debido a ser mi SO local más completo, contiene más archivos ocultos. No obstante, los relativos a `bash` son muy similares. Ambos SO tienen `.bash_logout`, `.bash_history` y `.bashrc`. El UML además tiene `.bash_profile`, pero el equivalente en mi SO local es `.profile`.

##  Actividad 3.8. Listados de metadatos de archivos: `ls`
Conocemos la sintaxis de la orden para obtener un listado en formato largo (*“long listing format”*). Manteniendo la opción de listado largo añade las opciones que sean necesarias para
obtener un listado largo con las siguientes especificaciones:
1. Que contenga el campo `access time` de los archivos del directorio especificado y que esté ordenado por dicho campo.
   ```console
   # ls -ltuh
    total 49M
    -rwxr-xr-x 1 root root 190 Oct 12 10:57 prueba_procesos
    -rw-r--r-- 1 root root 30M Oct  9 13:01 archivo_SA30
    -rw-r--r-- 1 root root 20M Oct  9 13:01 archivo_SA20
   ```

   La opción `-u` muestra el `access time`, y la opción `-t` ordena por ese campo.
2. Que contenga el campo `ctime` de los archivos del directorio especificado y que esté ordenado por dicho campo.
   ```console
   # ls -ltch
    total 49M
    -rwxr-xr-x 1 root root 190 Oct 12 10:57 prueba_procesos
    -rw-r--r-- 1 root root 30M Oct 10 03:09 archivo_SA30
    -rw-r--r-- 1 root root 20M Oct  9 17:38 archivo_SA20
   ```

   La opción `-c` muestra el `ctime`, y la opción `-t` ordena por ese campo.



## Actividad 3.9. Metadatos del sistema de archivos: `df` y `du`
Resuelve las siguientes cuestiones relacionadas con la consulta de metadatos del sistema de archivos:

1. Comprueba cuántos bloques de datos está usando la partición raíz del sistema UML del laboratorio. Ahora obtén la misma información pero expresada en *human readable format*: Megabytes o Gigabytes. Para ello consulta en detalle el manual en línea.

    Veamos en primer lugar el número de bloques:
    ```console
    # df   
    Filesystem           1K-blocks      Used Available Use% Mounted on
    LABEL=ROOT             1032088    464436    515224  48% /
    tmpfs                  1032088    464436    515224  48% /dev/shm
    /tmp                    509696         0    509696   0% /tmp
    none                  48862364  21132832  25215052  46% /mnt/Paquetes
    ```

    Como podemos ver, la partición ROOT ocupa 1032088 bloques.

    Para verla en *human readable format*, le añadimos la opción `-h`:
    ```console
    # df -h
    Filesystem            Size  Used Avail Use% Mounted on
    LABEL=ROOT           1008M  454M  504M  48% /
    tmpfs                1008M  454M  504M  48% /dev/shm
    /tmp                  498M     0  498M   0% /tmp
    none                   47G   21G   25G  46% /mnt/Paquetes
    ```

    Como podemos ver, la partición ROOT ocupa 1008 MiB.
   
2. ¿Cuántos inodos se están usando en la partición raíz? ¿Cuántos nuevos archivos se podrían crear en esta partición?

    Para ver los inodos, añado la opción `-i`.
    ```console
    # df -i
    Filesystem            Inodes   IUsed   IFree IUse% Mounted on
    LABEL=ROOT             65536   14771   50765   23% /
    tmpfs                  65536   14771   50765   23% /dev/shm
    /tmp                  127424       2  127422    1% /tmp
    none                 3123232  232133 2891099    8% /mnt/Paquetes
    ```

    Como podemos ver, se están usando 14771 inodos en la partición raíz.
    
    Además, quedan 50765 inodos libres. Por tanto, se podrían crear 50765 archivos nuevos *con metadatos distintos*. Añado este último matiz ya cabe la posibilidad de que haya varias entradas de directorio que hagan referencia a los mismos metadatos y, por tanto, al mismo inodo. Estos son los enlaces duros.
   
3. ¿Cuál es el tamaño del directorio `/etc`? ¿Y el del directorio `/var`? Compara estos tamaños con los de los directorios `/bin`, `/usr` y `/lib`. Anota brevemente tus conclusiones.

    Estos resultados se obtienen con el comando `du -h <dir>`. Además, la salida la procedo con `tail -1` para quedarme con la última línea, despreciando así el tamaño de todos los ficheros del interior del directorio en cuestión. Veámoslo.

    ```console
    # du -h /etc | tail -1
    21M	/etc
    # du -h /var | tail -1 
    16M	/var
    # du -h /bin | tail -1
    5.3M	/bin
    # du -h /usr | tail -1
    297M	/usr
    # du -h /lib | tail -1
    24M	/lib
    ```
   
4. Obtén el número de bloques de tamaño `4 KB` que utiliza la rama de la estructura jerárquica de directorios que comienza en el directorio `/etc`. En otras palabras, los bloques de tamaño `4 KB` del subárbol cuya raíz es `/etc`. ¿Cuál es el tamaño de bloque, por omisión, utilizado en el SA?

    Para especificar el tamaño del bloque, usamos la opción `-B 4K`. Por tanto,
    ```console
    # du -h -B 4K /etc | tail -1
    5271	/etc
    ```
    Por tanto, tenemos que hay 5271 bloques de `4 KB` en el subárbol con raíz `/etc`. 

    Para ver el tamaño de bloque, por omisión, del SA, recurrimos a la instrucción `tune2fs -l`. Para ello, necesitamos saber nuestro dispositivo, pero en el *UML* no podemos, ya que al hacer `cat /etc/fstab` no nos dice el nombre del dispositivo que está montado en `/`. 


## Actividad 3.10. Creación de enlaces con la orden `ln`
Construye los mismos enlaces, duros y simbólicos, que muestra la siguiente salida por pantalla:
```console
~/DIR$> ls -lai
total 28
6163598 drwxr-xr-x 3 user user 4096  2011-10-23 19:05 .
6293041 drwxr-xr-x 3 user user 4096  2011-10-23 13:20 ..
6162979 -rw-r--r-- 2 user user 52    2011-10-23 11:18 archivo.txt
6163010 brw-r--r-- 1 root root 7, 0  2011-10-23 11:27 blockDeviceSpecialFile
6163027 crw-r--r-- 1 root root 7, 0  2011-10-23 11:32 characterDeviceSpecialFile
6163009 drwxr-xr-x 2 user user 4096  2011-10-23 11:19 D1
6163029 prw-rw---- 1 root root 0     2011-10-23 11:35 FIFOfile
6162979 -rw-r--r-- 2 user user 52    2011-10-23 11:18 hardLink
6163034 -rw-r--r-- 2 user user 80    2011-10-23 19:04 hardLink2
6163022 brw-r--r-- 1 root root 7, 0  2011-10-23 11:30 loop0
6162996 lrwxrwxrwx 1 user user 11    2011-10-23 11:19 softLink -> archivo.txt
6163034 -rw-r--r-- 2 user user 80    2011-10-23 19:04 target_hardLink2.txt


~/DIR$> cd D1/
~/DIR/D1$> ls -lai
total 8
6163009 drwxr-xr-x 2 user user 4096  2011-10-23 11:19 .
6163598 drwxr-xr-x 3 user user 4096  2011-10-23 19:05 ..
```


Para ello crea los archivos `archivo.txt` y `target_hardLink2.txt` y, utilizando el manual en línea para `ln`, construye los enlaces `softLink`, `hardLink` y `hardLink2`. Anota las órdenes que has utilizado. ¿Por qué el contador de enlaces del archivo `archivo.txt` vale 2 si sobre el existen un enlace duro `hardLink` y un enlace simbólico `softLink`?


En primer lugar, creo los archivos:
```console
# touch archivo.txt target_hardLink2.txt
```

Ahora, creo los archivos con la orden `ln <target> <link_name>`. En el caso de que el enlace sea simbólico, añadimos `--symbolic`.
```console
# ln --symbolic archivo.txt softlink
# ln target_hardLink2.txt hardLink2
# ln archivo.txt hardLink
```

Veamos que tenemos el resultado deseado:
```console
# ls -lai
total 8
14117 drwxr-xr-x 2 root root 4096 Oct 12 18:55 .
  311 dr-xr-x--- 3 root root 4096 Oct 12 18:52 ..
14320 -rw-r--r-- 2 root root    0 Oct 12 18:53 archivo.txt
14320 -rw-r--r-- 2 root root    0 Oct 12 18:53 hardLink
14658 -rw-r--r-- 2 root root    0 Oct 12 18:53 hardLink2
14659 lrwxrwxrwx 1 root root   11 Oct 12 18:54 softlink -> archivo.txt
14658 -rw-r--r-- 2 root root    0 Oct 12 18:53 target_hardLink2.txt
```

El contador de enlaces del archivo `archivo.txt` vale 2 ya que a ese inodo solo referencian dos nombres de archivos, `archivo.txt` y `hardlink`. El enlace simbólico `softLink` tiene su propio inodo, por lo que no se contabiliza.

## Actividad 3.11. Trabajo con enlaces
Proporciona las opciones necesarias de la orden `ls` para obtener la información de metadatos de los archivos de un directorio concreto en los dos casos siguientes:

1. En el caso de que haya archivos de tipo enlace simbólico, la orden debe mostrar la información del archivo al que enlaza cada enlace simbólico y no la del propio archivo de tipo enlace simbólico.

    La opción que se ha de usar es `-L`. Esto lo podemos ver con el ejemplo del ejercicio anterior, ya que usando esta opción, el enlace simbólico se muestra como si fuese un enlace duro, mostrando el inodo del archivo al que apunta, etc.
    ```console
    # ls -Llai
    total 8
    14117 drwxr-xr-x 2 root root 4096 Oct 12 18:55 .
    311 dr-xr-x--- 3 root root 4096 Oct 12 18:52 ..
    14320 -rw-r--r-- 2 root root    0 Oct 12 18:53 archivo.txt
    14320 -rw-r--r-- 2 root root    0 Oct 12 18:53 hardLink
    14658 -rw-r--r-- 2 root root    0 Oct 12 18:53 hardLink2
    14320 -rw-r--r-- 2 root root    0 Oct 12 18:53 softlink
    14658 -rw-r--r-- 2 root root    0 Oct 12 18:53 target_hardLink2.txt
    ```

2. En el caso de enlaces simbólicos debe mostrar la información del enlace en sí, no del archivo al cual enlaza. En el caso de directorios no debe mostrar su contenido sino los metadatos del directorio.

    Lo respectivo a los enlaces simbólicos es la opción por defecto, por lo que no es necesario especificar ninguna opción.

    En el caso de directorios, sí es necesario especificarla, `-d`. Veámoslo:
    ```console
    # ls -laid /
    2 dr-xr-xr-x 22 root root 4096 Oct 12 10:55 /
    # ls -laid softlink 
    14659 lrwxrwxrwx 1 root root 11 Oct 12 18:54 softlink -> archivo.txt
    ```


## Actividad 3.12. Creación de archivos especiales
Consulta el manual en línea para la orden `mknod` y crea un dispositivo de bloques y otro de caracteres. Anota las órdenes que has utilizado y la salida que proporciona un `ls -li` de los dos archivos de dispositivo recién creados. Puedes utilizar las salidas por pantalla mostradas en esta sección del guión para ver el aspecto que debe presentar la información de un archivo de dispositivo.

Creamos en primer lugar los ficheros. Para ver qué posibles *Major Numbers* darle, consultamos en `/proc/devices`
```console
# cat /proc/devices
Character devices:
  ...
  5 /dev/tty
  ...

Block devices:
  ...
  7 loop
  ...
```

Para ver qué *Minor Numbers* está disponibles para no sobreescribir en la Tabla de Dispositivos, consultamos en `/dev`:
```console
# ls -l /dev
total 12
crw------- 1 root root 5, 1 Oct 12 10:55 console
crw-rw-rw- 1 root root 1, 7 Nov  3  2010 full
-rw-r--r-- 1 root root   54 Sep 13  2011 kmsg
srw-rw-rw- 1 root root    0 Oct 12 10:55 log
brw-r--r-- 1 root root 7, 0 Oct  9 17:38 loop0
brw-r--r-- 1 root root 7, 1 Oct  9 17:43 loop1
drwxr-xr-x 2 root root 4096 Nov  3  2010 mapper
crw-rw-rw- 1 root root 1, 3 Nov  3  2010 null
crw-rw-rw- 1 root root 5, 2 Nov  3  2010 ptmx
drwxr-xr-x 2 root root    0 Oct 12 10:55 pts
crw-rw-rw- 1 root root 1, 8 Nov  3  2010 random
drwxr-xr-x 2 root root 4096 Nov  3  2010 shm
lrwxrwxrwx 1 root root   15 Nov  3  2010 stderr -> /proc/self/fd/2
lrwxrwxrwx 1 root root   15 Nov  3  2010 stdin -> /proc/self/fd/0
lrwxrwxrwx 1 root root   15 Nov  3  2010 stdout -> /proc/self/fd/1
crw-rw-rw- 1 root root 5, 0 Nov  3  2010 tty
crw--w---- 1 root tty  4, 0 Oct 12 19:16 tty0
cr--r--r-- 1 root root 1, 9 Nov  3  2010 urandom
crw-rw-rw- 1 root root 1, 5 Nov  3  2010 zero
```

Podeos ver que el par `7 3` está disponible para el dispositivo de bloques, y el par `5 4` también está libre para el dispositivo de caracteres. Por tanto, los creo con el correspondiente comando: 

```console
# mknod disp_bloq b 7 3
# mknod disp_car c 5 4
```

Comprobemos que, efectivamente, se han creado:
```console
# ls -li disp_*   
14660 brw-r--r-- 1 root root 7, 3 Oct 12 19:20 disp_bloq
14661 crw-r--r-- 1 root root 5, 4 Oct 12 19:21 disp_car
```
