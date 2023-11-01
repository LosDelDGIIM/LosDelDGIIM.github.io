# Sistemas Operativos.  Módulo I. Práctica 04.

**Autor:** Arturo Olivares Martos
***

- **Asignatura:** Sistemas Operativos.
- **Curso Académico:** 2023-24.
- **Grado:** Doble Grado en Ingeniería Informática y Matemáticas.
- **Grupo:** Único.
- **Profesor:** Alejandro José León Salas
- **Descripción:** Sesión 4 del Módulo I de las prácticas de SO.
<!--- **Fecha:** 17 de abril de 2023. -->
<!-- - **Duración:** -->


## Actividad 4.1. Consulta de información sobre procesos demonio
A partir de la información proporcionada por la orden `ps` encuentre los datos asociados a los demonios `atd` y `crond`, en concreto: quién es su padre, qué terminal tienen asociado y cuál es su usuario.

Para facilitar la búsqueda, empleo la orden `grep`:
```console
# ps -ef | grep crond
root      1176     1  0 10:55 ?        00:00:00 crond
root      1703  1189  0 19:57 tty0     00:00:00 grep --color=auto crond

# ps -ef | grep atd  
root      1692     1  0 19:56 ?        00:00:00 /usr/sbin/atd
root      1705  1189  0 19:57 tty0     00:00:00 grep --color=auto atd
```

Obviando la segunda línea de cada salida, que es el proceso grep en sí, tenemos que el proceso padre de ambos procesos es el `init (PID=1)`.

Además, no tienen terminal asociada `(tty=?)`, de forma que se puedan ejecutar sin terminal asociada.

Por último, el usuario asociado es `root`.



## Actividad 4.2. Ejecución postergada de órdenes con `at` (I)
Crea un archivo `genera-apunte` que escriba la lista de hijos del directorio home en un archivo de nombre **listahome-\`date +%Y-%j-%T-$$\`**, es decir, la yuxtaposición del literal “listahome” y el año, día dentro del año, la hora actual y `PID` (consulte la ayuda de `date`). Lanza la ejecución del archivo `genera-apunte` un minuto más tarde de la hora actual.

¿En qué directorio se crea el archivo de salida?


El fichero `genera-apunte` es el siguiente:
```bash
#!/bin/bash

nomArchivo=listahome-`date +%Y-%j-%T-$$`

ls /root > $nomArchivo
```

La orden `at` para lanzar ese guión un minuto más tarde de la hora actual, usamos:
```console
[DIR]# at -f genera-apunte now+1 minute
job 3 at 2023-10-12 20:27
```

Un minuto más tarde, ya se ha ejecutado ese guión y podemos ver el contenido del fichero:
```console
[DIR]# cat ./listahome-2023-285-20\:27\:00-1784 
DIR
archivo_SA20
archivo_SA30
prueba_procesos
```

Este archivo se encuentra en `DIR`, la carpeta desde donde he ejecutado la orden `at`.



## Actividad 4.3. Ejecución postergada de órdenes con `at` (II)
Lanza varias órdenes `at` utilizando distintas formas de especificar el tiempo como las siguientes (será de utilidad la opción `-v` y las órdenes `atq` y `atrm`):
1. a medianoche de hoy
    ```console
    # at -f genera-apunte midnight
    job 4 at 2023-10-14 00:00
    ```

2. un minuto después de la medianoche de hoy
    ```console
    # at -f genera-apunte midnight +1 minute
    job 5 at 2023-10-14 00:01
    ```
   

3. a las 17 horas y 30 minutos de mañana
    ```console
    # at -f genera-apunte 17:30 tomorrow      
    job 6 at 2023-10-14 17:30
    ```
   

4. a la misma hora en que estemos ahora pero del día 25 de diciembre del presente año
    ```console
    # at -f genera-apunte 25 Dec        
    job 7 at 2023-12-25 05:08
    ```
   

5. a las 00:00 del 1 de enero del presente año.
    ```console
    # at -f genera-apunte midnight 1 Jan         
    job 8 at 2024-01-01 00:00
    ```

Veamos que efectivamente se han creado los trabajos a las horas especificadas:
```console
# atq
8	2024-01-01 00:00 a root
7	2023-12-25 05:08 a root
5	2023-10-14 00:01 a root
6	2023-10-14 17:30 a root
4	2023-10-14 00:00 a root
```

Eliminamos ahora dichos trabajos:
```console
# atrm 8
# atrm 7
# atrm 6  
# atrm 5 
# atrm 4
# atq
#
```

## Actividad 4.4. Cuestiones sobre `at`
El proceso nuevo que se lanza al cumplirse el tiempo que se especificó en la orden at....
1. ¿qué directorio de trabajo tiene inicialmente? ¿hereda el que tenía el proceso que invocó a at o bien es el home, directorio inicial por omisión?
2. ¿qué máscara de creación de archivos umask tiene? ¿es la heredada del padre o la que se usa por omisión?
3. ¿hereda las variables locales del proceso padre?

Experimenta con la orden at lanzando las órdenes adecuadas para encontrar las respuestas. 
(Puede encontrar información en la ayuda de at)

La información del `man` nos informa de que:
```
The working directory, the environment (except for the variables BASH_VERSINFO, DISPLAY, EUID, GROUPS, SHELLOPTS, TERM, UID, and _) and  the  umask  are  retained from the time of invocation.

As  at  is  currently  implemented  as a setuid program, other environment variables (e.g., LD_LIBRARY_PATH or LD_PRELOAD) are also not exported.  This may change in the future.  As a workaround, set these variables explicitly in your job.
```


Por tanto, vemos que tanto el directorio de trabajo como la máscara se heredan del proceso padre. Además, la mayoría de las variables de entorno se mantienen, pero no hace referencia a las variables locales.

Veámoslo con un ejemplo concreto:
``` console
DIR]# umask = 0777
DIR]# hola=7

DIR]# at now + 1 minute                         
at> pwd >> /root/DIR/resultado_at
at> umask >> /root/DIR/resultado_at
at> set | grep hola >> /root/DIR/resultado_at
at> <EOT>
job 13 at 2023-10-13 06:02
```

Como podemos ver, primero hemos cambiado la máscara por defecto, y hemos añadido una variable local. Entonces, cuando se lanze el proceso podremos comprobar el directorio de trabajo con `pwd`, la máscara con `umask` y si se mantiene la variable local `hola`.

La salida de cada orden la hemos redirigido a `/root/DIR/resultado_at`, ya que la orden `at` no tiene terminal asociada. Veamos el contenido de ese fichero:
```console
DIR]# cat resultado_at 
/root/DIR
0777
DIR]#
```

Como podemos ver, el directorio y la máscara se heredan, pero las variables locales.



## Actividad 4.5. Relación padre-hijo con órdenes ejecutadas mediante `at`
El proceso nuevo que se lanza al cumplirse el tiempo que se especificó en la orden `at`.... ¿de quién es hijo? Investiga lanzando la ejecución retardada de un script que muestre la información completa sobre los procesos existentes y el pid del proceso actual.

Hemos empleado el siguiente script:
```bash
#!/bin/bash

nombrearchivo=`date +%Y-%j-%T`

ps -ef > $nombrearchivo
echo Mi PID = $$ >> $nombrearchivo
```

Tras lanzarlo con `at` con la orden `at -f at_padre-hijo now +1 minute`, vemos que:
```console
# cat 2023-286-06\:14\:00 
UID        PID  PPID  C STIME TTY          TIME CMD
root         1     0  0 Oct12 ?        00:00:00 /sbin/init
root         2     0  0 Oct12 ?        00:00:00 [kthreadd]
root         3     2  0 Oct12 ?        00:00:10 [ksoftirqd/0]
root         4     2  0 Oct12 ?        00:00:00 [kworker/0:0]
root         5     2  0 Oct12 ?        00:00:00 [kworker/u:0]
root         6     2  0 Oct12 ?        00:00:00 [rcu_kthread]
root         7     2  0 Oct12 ?        00:00:00 [watchdog/0]
root         8     2  0 Oct12 ?        00:00:00 [cpuset]
root         9     2  0 Oct12 ?        00:00:00 [khelper]
root        10     2  0 Oct12 ?        00:00:00 [kworker/u:1]
root       115     2  0 Oct12 ?        00:00:00 [sync_supers]
root       117     2  0 Oct12 ?        00:00:00 [bdi-default]
root       118     2  0 Oct12 ?        00:00:00 [kblockd]
root       134     2  0 Oct12 ?        00:00:00 [rpciod]
root       135     2  0 Oct12 ?        00:00:00 [kworker/0:1]
root       143     2  0 Oct12 ?        00:00:00 [khungtaskd]
root       144     2  0 Oct12 ?        00:00:00 [kswapd0]
root       192     2  0 Oct12 ?        00:00:00 [fsnotify_mark]
root       216     2  0 Oct12 ?        00:00:00 [ecryptfs-kthrea]
root       218     2  0 Oct12 ?        00:00:00 [nfsiod]
root       240     2  0 Oct12 ?        00:00:00 [glock_workqueue]
root       241     2  0 Oct12 ?        00:00:00 [delete_workqueu]
root       246     2  0 Oct12 ?        00:00:00 [gfs_recovery]
root       248     2  0 Oct12 ?        00:00:00 [crypto]
root       263     2  0 Oct12 ?        00:00:00 [kthrotld]
root       961     2  0 Oct12 ?        00:00:00 [jbd2/ubda-8]
root       962     2  0 Oct12 ?        00:00:00 [ext4-dio-unwrit]
root      1057     2  0 Oct12 ?        00:00:00 [kauditd]
root      1095     1  0 Oct12 ?        00:00:00 auditd
root      1113     1  0 Oct12 ?        00:00:00 /sbin/rsyslogd -c 4
root      1138     1  0 Oct12 ?        00:00:00 /usr/sbin/sshd
smmsp     1164     1  0 Oct12 ?        00:00:00 sendmail: Queue runner@01:00:00 for /var/spool/clientmqueue
root      1176     1  0 Oct12 ?        00:00:00 crond
root      1188     1  0 Oct12 ?        00:00:00 login -- root     
root      1189  1188  0 Oct12 tty0     00:00:00 -bash
root      1373  1189  0 Oct12 tty0     00:00:00 watch free
root      1692     1  0 Oct12 ?        00:00:00 /usr/sbin/atd
root      1813     2  0 05:20 ?        00:00:00 [flush-98:0]
root      1885     1  0 06:01 ?        00:00:00 /usr/sbin/anacron -s
root      1909  1692  0 06:13 ?        00:00:00 /usr/sbin/atd
root      1910  1909  0 06:13 ?        00:00:00 sh
root      1912  1910  0 06:13 ?        00:00:00 /bin/bash
root      1914  1912  0 06:13 ?        00:00:00 ps -ef
Mi PID = 1912
```

Vemos que el PID del proceso lanzado es `1912`. Estableciendo la jerarquía padre-hijo, vemos que es:

```
bash(1912) -- sh(1910) -- atd(1909) -- atd (1692) -- init(1)
```

Como podemos ver, el script de linux (`bash`) lo ha lanzado un shell `sh` que ha sido lanzado por el demonio `atd`, que tiene como padre `init`.



## Actividad 4.6. Script para orden at
Construye un script que utilice la orden `find` para generar en la salida estándar los archivos modificados en las últimas 24 horas (partiendo del directorio `home` y recorriéndolo en
profundidad). La salida deberá escribirse el archivo de nombre `modificados_<año><día><hora>` (dentro del directorio home). Con la orden `at` provoque que se ejecute dentro de un día a partir de este momento.


El script es el siguiente:
```bash
#!/bin/bash

nombrearchivo=/root/modificados_`date +%Y-%j-%T`

find /root -mtime -1 > $nombrearchivo
```

Para que se ejecute dentro de un día, empleamos la siguiente orden:
```console
# at -f /root/DIR/at_salidas now + 1 day
job 15 at 2023-10-14 06:57
```


## Actividad 4.7. Trabajo con la orden batch
Lanza los procesos que sean necesarios para conseguir que exista una gran carga de trabajo para el sistema de modo que los trabajos lanzados con la orden batch no se estén ejecutando (puede simplemente construir un script que esté en un ciclo infinito y lanzarla varias veces en segundo plano). Utiliza las órdenes oportunas para manejar este conjunto de procesos (la orden `jobs` para ver los trabajos lanzados, `kill` para finalizar un trabajo, y tal vez también las órdenes `fg`, `bg` para pasar de segundo a primer plano y viceversa, `<Ctrl-Z>` para suspender el proceso en primer plano actual, etc). Experimenta para comprobar cómo al ir disminuyendo la carga de trabajos habrá un momento en que se ejecuten los trabajos lanzados a la cola batch.



El script empleado ha sido el siguiente bucle infinito:
```bash
#!/bin/bash

x=0

while [[ 1 -ne 0 ]]; do
        x=$(( x + 1  ))
done
```

Tras lanzar varias veces dicho bucle infinito en segundo plano, lancé la orden batch.

```console
# ./inf.sh &
[2] 2104
# ./inf.sh &
[3] 2105
# ./inf.sh &
[4] 2106
# ./inf.sh &
[5] 2107

DIR]# batch               
at> ls > /root/DIR/res_batch
at> <EOT>
```

El fihcero `res_batch` no se me generó, debido a que con la orden `top` comprobaba que los bucles infinitos suponían una gran carga de trabajo. No fue hasta que los eliminé usando la opción `kill`, que entonces se me generó dicho fichero al bajar la carga de trabajo.

```console
# ls /root/DIR
at_padre-hijo  at_salidas  inf.sh

# kill 2104
# kill 2105
# kill 2106
# kill 2107

# ls /root/DIR
at_padre-hijo  at_salidas  inf.sh  res_batch
```


## Actividad 4.8. Utilización de las colas de trabajos de `at`
Construye tres script que deberás lanzar a las colas *c*, *d* y *e* especificando una hora concreta que esté unos pocos minutos más adelante (no muchos para ser operativos). Idea qué actuación deben tener dichos script de forma que se ponga de manifiesto que de esas colas la más prioritaria es la *c* y la menos es la *e*. Visualiza en algún momento los trabajos asignados a las
distintas colas.


En primer lugar, usando el script del bucle infinito de la actividad anterior, lo he lanzaado con `at` en tres colas distintas en tres momentos distintos. En primer lugar, lo he lanzado con la co,a *e*, luego la *d* y luego *c*.
```console
# at now + 1 minute -q e -f inf.sh 
job 44 at 2023-10-13 08:05
# at now + 2 minute -q d -f inf.sh 
job 45 at 2023-10-13 08:06
# at now + 3 minute -q c -f inf.sh 
job 46 at 2023-10-13 08:07
```

Una vez se estaban ejecutando, con la orden `top`, he visualizado los procesos. Debido a que los PID se crean en orden ascendente, podemos ver que el correspondiente a la cola *q* tiene `PID=1338` y tiene un valor de la opción `nice` mayor, por lo que es menos prioritario.

De forma análoga, vemos que el menor valor de `nice`, 6, corresponde al proceso de la cola *c*, que ha sido el que se ha añadido más tarde.
```console
# top
...
 PID USER      PR  NI  VIRT  RES  SHR S %CPU %MEM    TIME+  COMMAND                                                                                  
 1346 root      26   6  3120 1084  956 R 34.3  0.1   0:05.83 bash                                                                                     
 1341 root      28   8  3120 1080  956 R 33.4  0.1   0:35.80 bash                                                                                     
 1338 root      30  10  3120 1084  956 R 32.4  0.1   1:35.79 bash
```



## Actividad 4.9. Relación padre-hijo con órdenes ejecutadas mediante `crontab`
Al igual que se investigó en la [Actividad 4.5](Práctica04.md#actividad-45-relación-padre-hijo-con-órdenes-ejecutadas-mediante-at) sobre quién es el proceso padre del nuestro, lanza el script construido en dicha actividad con una periodicidad de un minuto y analiza los resultados.


En primer lugar, como no hay un fichero `crontab` definido, hemos de crear uno. Para ello, usamos la orden `crontab -e`, para editar el `crontab` correspondiente. Una vez se abre el editor, ponemos `* * * * * /root/DIR/at_padre-hijo` para que ejecute cada minuto. De tal forma, el `crontab` queda:
```consol
# crontab -l
* * * * * /root/DIR/at_padre-hijo
```

Veamos ahora la jerarquía correspondiente a uno de los archivos cualesquiera:
```console
# cat 2023-286-09\:24\:01 
UID        PID  PPID  C STIME TTY          TIME CMD
root         1     0  0 07:50 ?        00:00:00 /sbin/init
root         2     0  0 07:50 ?        00:00:00 [kthreadd]
root         3     2  0 07:50 ?        00:00:01 [ksoftirqd/0]
root         4     2  0 07:50 ?        00:00:00 [kworker/0:0]
root         5     2  0 07:50 ?        00:00:00 [kworker/u:0]
root         6     2  0 07:50 ?        00:00:00 [rcu_kthread]
root         7     2  0 07:50 ?        00:00:00 [watchdog/0]
root         8     2  0 07:50 ?        00:00:00 [cpuset]
root         9     2  0 07:50 ?        00:00:00 [khelper]
root        10     2  0 07:50 ?        00:00:00 [kworker/u:1]
root       115     2  0 07:50 ?        00:00:00 [sync_supers]
root       117     2  0 07:50 ?        00:00:00 [bdi-default]
root       118     2  0 07:50 ?        00:00:00 [kblockd]
root       134     2  0 07:50 ?        00:00:00 [rpciod]
root       135     2  0 07:50 ?        00:00:00 [kworker/0:1]
root       143     2  0 07:50 ?        00:00:00 [khungtaskd]
root       144     2  0 07:50 ?        00:00:00 [kswapd0]
root       192     2  0 07:50 ?        00:00:00 [fsnotify_mark]
root       216     2  0 07:50 ?        00:00:00 [ecryptfs-kthrea]
root       218     2  0 07:50 ?        00:00:00 [nfsiod]
root       240     2  0 07:50 ?        00:00:00 [glock_workqueue]
root       241     2  0 07:50 ?        00:00:00 [delete_workqueu]
root       246     2  0 07:50 ?        00:00:00 [gfs_recovery]
root       248     2  0 07:50 ?        00:00:00 [crypto]
root       263     2  0 07:50 ?        00:00:00 [kthrotld]
root       961     2  0 07:50 ?        00:00:00 [jbd2/ubda-8]
root       962     2  0 07:50 ?        00:00:00 [ext4-dio-unwrit]
root      1059     2  0 07:50 ?        00:00:00 [kauditd]
root      1103     1  0 07:50 ?        00:00:00 auditd
root      1121     1  0 07:50 ?        00:00:00 /sbin/rsyslogd -c 4
root      1129     2  0 07:50 ?        00:00:00 [flush-98:0]
root      1147     1  0 07:50 ?        00:00:00 /usr/sbin/sshd
smmsp     1173     1  0 07:50 ?        00:00:00 sendmail: Queue runner@01:00:00 for /var/spool/clientmqueue
root      1184     1  0 07:50 ?        00:00:00 crond
root      1197     1  0 07:50 ?        00:00:00 /usr/sbin/atd
root      1209     1  0 07:50 ?        00:00:00 login -- root     
root      1210  1209  0 07:50 tty0     00:00:00 -bash
root      1615  1184  0 09:24 ?        00:00:00 CROND
root      1616  1615  4 09:24 ?        00:00:00 /bin/bash /root/DIR/at_padre-hijo
root      1618  1616  0 09:24 ?        00:00:00 ps -ef
Mi PID = 1616
```


Vemos que el proceso lanzado tiene `PID=1616`. Entonces, la jerarquía es:
```
at_padre-hijo(1616) -- CROND (1615) -- crond (1184) -- init(1)
```


## Actividad 4.10. Ejecución de scripts con `crontab` (I)
Construye un script que sea lanzado con una periodicidad de un minuto y que borre los nombres de los archivos que cuelguen del directorio `/tmp/varios` y que comiencen por *core* (cree ese directorio y algunos archivos para poder realizar esta actividad). Utiliza la opción `-v` de la orden `rm` para generar como salida una frase de confirmación de los archivos borrados; queremos que el conjunto de estas salidas se añadan al archivo `/tmp/listacores`.

Prueba la orden `crontab -l` para ver la lista actual de trabajos (consulte la ayuda para ver las restantes posibilidades de esta orden para gestionar la lista actual de trabajos).


En primer lugar, creamos el directorio y los archivos necesarios:
```console
# mkdir /tmp/varios
# touch /tmp/varios/core{1,2,56,78}
# ls -l /tmp/varios
total 0
-rw-r--r-- 1 root root 0 Oct 13 09:38 core1
-rw-r--r-- 1 root root 0 Oct 13 09:38 core2
-rw-r--r-- 1 root root 0 Oct 13 09:38 core56
-rw-r--r-- 1 root root 0 Oct 13 09:38 core78
```

Posteriormente, creamos el script:
```bash
#!/bin/bash

rm -v /tmp/varios/core* >> /tmp/listacores
```

Ahora, modficamos la `crontab`. Para ello, ejecutamos `crontab -e` para editar, y al final añadimos la línea correspondiente a la ejecución de este archivo. El archivo crontab queda:
```console
# crontab -l
* * * * * /root/DIR/at_padre-hijo
* * * * * /root/DIR/borrar_core.sh
```

Comprobamos ahora que el script ha tenido el resultado deseado:
```console
# ls /tmp/varios
# cat /tmp/listacores 
removed `/tmp/varios/core1'
removed `/tmp/varios/core2'
removed `/tmp/varios/core56'
removed `/tmp/varios/core78'
```

## Actividad 4.11. Ejecución de scripts con `crontab` (II)
Para asegurar que el contenido del archivo `/tmp/listacores` no crezca demasiado, queremos que periódicamente se deje dicho archivo solo con sus 10 primeras líneas (puede ser de utilidad la orden `head`). Construye un script llamado `reducelista` (dentro del directoio `~/SO`) que realice la función anterior y lance su ejecución con periodicidad de un minuto.

Creamos en primer lugar el script:
```bash
#!/bin/bash

archivo=/tmp/listacores

head -n 10 $archivo > temp_file
cp temp_file $archivo
rm temp_file
```
donde he hecho uso del `temp_file`, ya que al usar redirección de salida, el archivo se vaciaba antes de considerar las 10 líneas, por lo que se perdía información.

Ahora, modficamos la `crontab`. Para ello, ejecutamos `crontab -e` para editar, y al final añadimos la línea correspondiente a la ejecución de este archivo. El archivo crontab queda:
```console
# crontab -l
* * * * * /root/DIR/at_padre-hijo
* * * * * /root/DIR/borrar_core.sh
* * * * * /root/SO/reducelista
```



## Actividad 4.12. Ejecución de scripts con `crontab` (III)
Construye un sencillo script que escriba en el archivo `~/SO/listabusqueda` una nueva línea con la fecha y hora actual y después el valor de la lista de búsqueda, por ejemplo:
```
...
2011-297-12:39:10 - /usr/local/bin:/usr/local/bin:/usr/bin...
...
```
Ejecuta este script desde el lenguaje de órdenes y también lánzalo como trabajo `crontab` y compara los resultados, ¿se tiene en ambos casos la misma lista de búsqueda?

En primer lugar, creo el script:
```bash
#!/bin/bash

archivo=/root/SO/listabusqueda

echo `date +%Y-%d-%T` " - " $PATH >> $archivo
```

Ahora, lo lanzo desde el lenguaje de órdenes, y tenemos el resultado esperado:
```console
# cat /root/SO/listabusqueda 
2023-13-10:13:02  -  /usr/local/sbin:/usr/local/bin:/sbin:/bin:/usr/sbin:/usr/bin:/root/bin
```

Lo añadimos ahora a `crontab` usando la opción `-e`:
```console
# crontab -l
* * * * * /root/DIR/at_padre-hijo
* * * * * /root/DIR/borrar_core.sh
* * * * * /root/SO/reducelista
* * * * * /root/DIR/path.sh
```

Vemos el valor del archivo, y comparamos los resultados. A prori, deberían salir resultados similares.
```console
# cat /root/SO/listabusqueda 
2023-13-10:13:02  -  /usr/local/sbin:/usr/local/bin:/sbin:/bin:/usr/sbin:/usr/bin:/root/bin
2023-13-10:16:01  -  /usr/bin:/bin
```

El problema de la diferencia se debe a que nos encontramos en un ámbito (*environment*) distinto.


## Actividad 4.13. Variables de entorno en archivos `crontab`
Practicamos ahora lo que acabamos de explicar situándonos en lo que hemos realizado en la
[Actividad 4.11](#actividad-411-ejecución-de-scripts-con-crontab-ii). Construye un script que generará un archivo `crontab` llamado `crontab-reducelista` que deberá contener:
1. Como primera linea la asignación a la variable `PATH` de la lista de búsqueda
actual y además el directorio `$HOME/SO`.

2. Después, la indicación a `cron` de la ejecución con periodicidad de 1 minuto del script `reducelista`.


Una vez construido `crontab-reducelista` lánzalo con la orden `crontab`. Comprueba que con esta nueva lista de búsqueda podremos hacer alusión a reducelista especificando únicamente su nombre independientemente del directorio de trabajo en que nos situemos (no como ocurría en la [Actividad 4.11](#actividad-411-ejecución-de-scripts-con-crontab-ii) en que el directorio `$HOME/SO` no estaba en la lista de búsqueda).



El script encargado de generar `crontab-reducelista` es:
```bash
#!/bin/bash


archivo_gen=/root/DIR/crontab-reducelista

echo "PATH="$PATH":"$HOME"/SO" > $archivo_gen
echo "* * * * * reducelista" >> $archivo_gen
```

Lo lanzamos ahora con la orden `crontab`:
```console
# /root/DIR/gen_reducelista 
# crontab /root/DIR/crontab-reducelista 
# crontab -l
PATH=/usr/local/sbin:/usr/local/bin:/sbin:/bin:/usr/sbin:/usr/bin:/root/bin:/root/SO
* * * * * reducelista
```

El matiz final del enunciado se refiere a que no es necesario poner `./reducelista`, sino que basta con poner `reducelista`.


## Actividad 4.14. Archivos `crontab` de diferentes usuarios
Vamos a lanzar un archivo `crontab` cuyo propietario es otro usuario. Visualiza el contenido del archivo `/fenix/depar/lsi/so/ver-entorno` y `/fenix/depar/lsi/so/crontabver`. Comprueba con `ls -l` que el propietario es el usuario `lsi`. Sin copiarlos, úsalos para lanzar la ejecución cada minuto del script `/fenix/depar/lsi/so/ver-entorno`.

Analiza el archivo de salida: ¿de qué línea del archivo `/etc/passwd` se toman `LOGNAME` y `HOME`, de la línea del propietario del archivo `crontab` o de la línea del usuario que lanza el archivo `crontab`?


Este ejercicio no lo podemos realizar al no contar con dichos ficheros. No obstante, la orden `man 5 crontab` nos informa de lo siguiente:
```md
Several environment variables are set up automatically by the cron(8) daemon.  SHELL is set to /bin/sh, and **LOGNAME and HOME are  set  from the  /etc/passwd line of the crontab's owner**.  PATH is inherited from the environment.  HOME, SHELL, and PATH may be overridden by settings in the crontab; LOGNAME is the user that the job is running from, and may not be changed.
```
donde he resaltado que se nos informa que se obtienen de la linea del propietario del `crontab`.


## Actividad 4.15. Ejecución de scripts con `crontab` (IV)
El objetivo es ejecutar todos los días a las 0 horas 0 minutos una copia de los archivos que cuelguen de `$HOME` que se hayan modificado en las últimas 24 horas. Vamos a programar este salvado incremental utilizando la orden find que usábamos en la [Actividad 4.6](#actividad-46-script-para-orden-at); ahora queremos que se copien los archivos encontrados por `find` utilizando la orden `cpio`:
```console
<orden find de la Actividad 4.6> | cpio -pmduv /tmp/salvado$HOME
```

Explico en primer lugar la orden `cpio`. 
* La opción  `-p`, que no lo permite `cp`, es que los archivos a copiar se toman de la entrada estándar.
* La opción `-v` informa por la salida estándar de lo que ha hecho el comando.
* La opción `-m` mantiene las fechas de modificación de los archivos.
* La opción `-u` es para que se sobreescriban los archivos. Esto es necesario porque, cuando se haga la copia el segundo día, los archivos han de ser sobreeescritos.
* La opción `-d` sirve para crear directorios en el caso de que sea necesario.


Creo ahora el fichero `crontab`:
```console
# cat cron_salvado 
@daily find /root -mtime -1 | cpio -pmduv /tmp/salvado/root
```
donde he empleado la string special `@daily`, que significa *Run once a day, "`0 0 * * *`"*.

Por tanto, solo me falta lanzar dicho proceso con `crontab`:
```console
# crontab cron_salvado
# crontab -l
@daily find /root -mtime -1 | cpio -pmduv /tmp/salvado/root
```