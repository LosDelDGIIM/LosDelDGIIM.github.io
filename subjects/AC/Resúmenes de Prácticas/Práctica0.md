# Arquitectura de Computadores. Sesión 0 de Prácticas.

**Autor:** José Juan Urrutia Milán
***

- **Asignatura:** Arquitectura de Computadores.  
- **Curso Académico:** 2023-24.
- **Grado:** Doble Grado en Ingeniería Informática y Matemáticas.
- **Profesor:** Mancia Anguita López.
- **Descripción:** Resúmen de la Sesión 0 de Prácticas.

## Introducción
Para conectarse a atcgrid usando `ssh`, usaremos:
```bash
ssh [username]@atcgrid.ugr.es
```
Donde en *username* debemos proporcionar nuestro usuario (ac*xxx*). A continuación, se nos solicitará la contraseña.  
Si no estamos conectados a `eduroam`, podemos usar la VPN de la universidad que debe tener instalada. Una vez instalada (consultar en Google cómo instalarla si no), ejecutaremos el script `/opt/cisco/anyconnect/bin/vpnui`. Este nos preguntará a qué queremos conectarnos (incluir `vpn.ugr.es`), nuestro usuario (correo `@correo.ugr.es`) y dos contraseñas, la primera es asociada al correo y la segunda es el doble factor de autentificación que deberíamos haber fijado al instalar la VPN.  
  
### Sistema
Una vez conectado a `atcgrid`, nos encontramos en la máquina host, que es la encargada de soportar todo el sistema de peticiones. Esta cuenta con un gestor de colas de trabajo llamado `srun`.  
Contamos con dos colas de trabajo:
- `ac`
- `ac4`
  
La primera que cuenta con los nodos `atcgrid1`, `atcgrid2` y `atcgrid3`, todos ellos iguales. La segunda cuenta con el nodo `atcgrid4`, más potente y con procesador gráfico dedicado. Para mandar trabajo a `atcgrid4`, debemos usar `ac4` y en caso contrario, `ac`.  
  
Disponemos de distintas órdenes para trabajar con dichas colas:
- `srun`
- `sbatch`
  
La única diferencia entre ambos es que `srun` se ejecuta en primer plano en terminal, bloqueándola hasta que se termina la ejecución de lo deseado, mientras que `sbatch` manda el trabajo a ejecutar en segundo plano, con posibilidad de seguir usando la terminal. Por tanto, recomendamos el uso de `srun` para comandos sencillos y de `sbatch` para scripts. Estos scripts, en caso de necesitar una línea que ejecute una orden, escribimos delante de la orden `srun`. Estos `srun` heredan las opciones fijadas en el `sbatch` que se usa para enviar el script a la cola.  
*Nota:* El tiempo máximo de ejecución en cada nodo está fijado en un minuto.  

### Hardware
El nodo host o frontend, es un computador modelo `Asus RS300-E9-PS4`.  
Los nodos `atcgrid1`, `atcgrid2` y `atcgrid3` son servidores rack `SuperMicro SuperServer 6016T-T`.  
Y el `atcgrid4` es un servidor rack `SuperMicro SYS-6019U-TR4 1U`  
  
No vamos a entrar mucho en detalle sobre el hardware de cada uno (ya que no nos concierne), pero vamos a mencionar al menos el número de cores de cada nodo:

##### atcgrid1-3
En el caso de estos nodos, contamos con una CPU por nodo de 12 cores físicos y 2 cores lógicos por físico; un total de 24 cores lógicos. 

##### atcgrid4
En este nodo, contamos con dos CPUs, cada una con 16 cores físicos y 2 cores lógicos po físico, luego contamos con $2 \cdot 16 \cdot 2 = 64$ cores lógicos.
  
## Parámetros 
A continuación, revelamos una serie de opciones que podemos especificar a la hora de mandar trabajos a ejecución con `srun` o `sbatch` (todos los ejemplos serán de `srun`).

##### Elegir cola de trabajo
Para elegir la cola (`ac` o `ac4`) a la que queremos enviar el trabajo, usamos el parámetro `-p [cola]`:
```bash
srun -p [cola] [comando]
```
Por ejemplo:
```bash
srun -p ac lscpu
srun -p ac4 lscpu
```
*Nota:* el espacio puede omitirse: `srun -pac [comando]`, `srun -pac4 [comando]`.  
A las colas también se les llama *particiones*.

##### Elegir nodo particular
Para elegir un nodo particular en la cola de trabajo, usamos `-w`:
```bash
srun -p [cola] -w [nombreNodo] [comando]
```
Por ejemplo:
```bash
srun -p ac -w atcgrid2 lscpu
```

##### Un proceso por trabajo
Para asegurarnos de que `slurm` sólo crea un proceso por nuestro trabajo, usamos la opción `--ntasks=`, abreviada con `-n`:
```bash
srun -n [número] [comando]
```
Por ejemplo:
```bash
srun -pac -n1 lscpu
```

##### Nombre de trabajo
Para especificar un nombre al trabajo, podemos usar `--job-name=`:
```bash
srun --job-name=[nombre] [comando]
```

##### Indicar el número de núcleos
Para elegir el número de núcleos con el que queremos que el sistema operativo ejecute nuestro trabajo, usamos la opción `--cpus-per-task=`, abreviada como `-c` (por defecto, `slurm` asigna un core a un proceso): 
```bash
srun -c [número] [comando]
```
Por ejemplo:
```bash
srun -pac -c1 lscpu
```
*Nota:* Por defecto, el sistema operativo considera como núcleos los núcleos lógicos.  
Obviamente, no podemos pedir más núcleos que los disponibles por la máquina. Por tanto, en un supuesto computador de una CPU con 6 cores (físicos) y dos `threads` (cores lógicos) por core, el número máximo que podrá acompañar a `-c` será 12.

##### Indicar el tipo de cores
Por defecto, la opción anterior (`-c`) selecciona el número de cores *lógicos* en los que nuestro trabajo se ejecutará. Si por contra, queremos usar sólo cores físicos y no lógicos, especificaremos la opción `--hint=nomultithread`. Por ejemplo:
```bash
srun -pac -c4 --hint=nomultithread [comando]
```
*Nota:* Volvemos a tener ahora la misma restricción. En el suspuesto computador enunciado anteriormente, el mayor número que podrá acompañar a la opción `-c` será 6.  
Para que con `sbatch` se tenga en cuenta, se debe usar `srun` dentro del script delante del ejecutable a ejecutar.

##### Uso de nodo de forma exclusiva
Recordamos que el sistema es usado por varios usuarios al mismo tiempo y `slurm` es el encargado de asignar a cada usuario ciertos núcleos de cada nodo cuando el usuario realiza la petición de un trabajo. Si por ejemplo, queremos ejecutar un programa que mida el rendiminto del nodo, no queremos que otros usuarios lo usen al mismo tiempo que nosotros. Por tanto, podemos ejecutar la opción `--exclusive`. Por ejemplo:
```bash
srun -pac --exclusive [comando]
```
Nadie más podrá usar el nodo hasta que el trabajo se termine de realizar.  
*Nota:* recordamos que cada nodo tiene un tiempo de duracion máximo de 1 minuto por trabajo.  
Se recomienda no utilizarlo en los `srun` dentro de un script.

##### Selección de cuenta
Si disponemos de varias cuentas en `slurm`, a la hora de mandar un trabajo podemos especificar desde qué cuenta queremos enviarlo con la opción `--account=` o de forma abreviada, `-A` :
```bash
srun -A [cuenta] [comando]
```
Por ejemplo:
```bash
srun -pac -Aac [comando]
```
*Nota:* esto no será necesario para el alumnado que desarrolla la asignatura, ya que cada alumno sólo cuenta con una cuenta dentro de atcgrid.

##### Referencias
Además de todos estos comandos, disponemos de muchos más. Podemos encontrar en los siguientes enlaces una tabla resumen, además de la documentación oficial de `slurm`:  
[https://slurm.schedmd.com/pdfs/summary.pdf](https://slurm.schedmd.com/pdfs/summary.pdf)  
[https://slurm.schedmd.com/man_index.html](https://slurm.schedmd.com/man_index.html)

### Opciones en sbatch
Además de especificar las opciones junto con la orden `sbatch`, podemos especificarlas dentro del script usando `#SBATCH`.  

##### sbatch sin script
Podemos a su vez usar `sbatch` para mandar a ejecución un trabajo sin necesidad de crear un archivo que contenga el script a ejecutar. Para ello, usamos la opción `--wrap`:
```bach
sbatch --wrap [comando]
```
Por ejemplo:
```bash
sbatch -pac --wrap "echo 'Hola mundo'"
```

#### Variables especiales
Dentro de nuestro script (en `bash`) que mandaremos a un trabajo con `sbatch`, disponemos de varias constantes especiales que nos proporciona `slurm` y que podemos usar en nuestros scripts:

##### Identificador del usuario del trabajo
Para obtener el identificador del usuario del trabajo, disponemos de `$SLURM_JOB_USER`.

##### Identificador del trabajo
Para obtener el identificador del trabajo, disponemos de `$SLURM_JOBID`.

##### Nombre del trabajo
Para obtener el nombre del trabajo especificado por el usuario: `$SLURM_JOB_NAME`.

##### Directorio de trabajo
Para obtener el directorio de trabajo del script (directorio en el cual este se ejecuta): `$SLURM_SUBMIT_DIR`.

##### Cola asignada
Para obtener la cola a la que se mandó el script cuando se creó un trabajo con él: `$SLURM_JOB_PARTITION`.

##### Nodo
Para imprimir el nodo atcgrid en el que se ha ejecutado el trabajo: `$SLURM_SUBMIT_HOST`.

##### Número de nodos
Para imprimir el número de nodos en el que se ha ejecutado el trabajo: `$SLURM_JOB_NUM_NODES`.

##### CPUs por nodo
Para imprimir el número de CPUs por nodo: `$SLURM_JOB_CPUS_PER_NODE`.

### Uso recomendado con sbatch
A la hora de ejecutar un trabajo con `sbatch`, se recomienda usar las opciones:
```bash
sbatch -n1 -c [cores] --exclusive --hint=nomultithread [comando]
```
Para asegurarnos de que se crea un sólo proceso, indicar el número de cores que queremos usar, no compartir recursos y usar cores físicos.

### Uso recomendado con srun
A la hora de usar `srun` fuera de un script, se recomienda usar:
```bash
srun -n1 -c [cores] --hint=nomultithread [comando]
```
Para asegurarnos de que se crea un sólo proceso, indicar el número de cores que queremos usar y usar cores físicos.  
  
Tanto con `srun` como con `sbatch`, se recomienda escribir las órdenes directamente en el shell en vez de copiar y pegar.  
  
*Nota:* a la hora de compiar arhivos en `c` (o en cualquier otro lenguaje), se recomienda usar `srun` para realizar este trabajo en un nodo y no en la máquina host, ya que puede laggearse fácilmente, al tener que adminisitrar muchos usuarios al mismo tiempo.

## Comandos 
#### Obtener información sobre colas
Para obtener información sobre las colas de trabajo que nos proporciona `slurm` en el sistema, podemos usar `sinfo`:
```bash
sinfo
```
Para obtener más detalle sobre cada cola:
```bash
sinfo -p [cola] -o"%10D %10G %20b %f"
```
Por ejemplo:
```bash
sinfo -pac -o"%10D %10G %20b %f"
```

#### Obtener informacion sobre trabajos
Para obtener información sobre los trabajos realizados y por realizar, así como sus identificadores de trabajos:
```bash
qstat
```

#### Matar trabajos
Para matar un trabajo, conocido su identificador de trabavo (con `qstat`):
```bash
scancel [identificador]
```

#### Importar archivos
Para importar archivos a atcgrid desde cualquier máquina, podemos usar el comando `scp` desde la terminal de la máquina que proporcional el archivo:
```bash
scp [ruta_archivo] [username]@atcgrid.ugr.es:[ruta]
```
Por ejemplo:
```bash
scp archivo.cpp ac111@atcgrid.ugr.es:~/ejercicios/
```
A continuación, se solicitará la contraseña del *username* correspondiente.

#### Exportar gráficos 
Para que aplicaciones gráficas que se ejecutan en remoto (dentro de atcgrid) muestren sus interfaces en la máquina desde la que nos conectamos a atcgrid, debemos especificar a la hora de conectarnos mediante `ssh`:
```bash
ssh -X [username]@atcgrid.ugr.es
```

## Introducción a OpenMP
Podemos ver en la práctica un primer ejemplo del uso de OpenMP, en el archivo `HelloOMP.c`:
```c
#include <stdio.h>
#include <omp.h>

int main(){
    #pragma omp parallel
    printf("(%d:!!!Hello world!!!)", omp_get_thread_num());
    
    return 0;
}
```
En este ejemplo, que se debe compilar con:
```bash
gcc -O2 -fopenmp -o HelloOMP HelloOMP.c
```
Podemos ver que en cada hilo que le aportemos en su ejecución (se recomienda que se use el parámetro `-c` a la hora de ejecutar con `srun` o `sbatch`), imprime el identificardor de cada hilo (que se obtiene con la función `omp_get_thread_num()`), un número de entre 0 y `n-1` siendo `n` el número de hilos del computador; además de un `!!!Hello world!!!` en cada hilo.  
  
La función de que la rutina `printf()` se ejecute en todos los hilos proporcionados al proceso la hemos obtenido mediante la directiva `pagma omp parallel`. A lo largo de la asignatura, se desarrollarán más directivas y funcionalidades de OpenMP.

