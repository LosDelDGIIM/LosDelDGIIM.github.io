# Sistemas Operativos.  Módulo II. Práctica 05.

**Autor:** Arturo Olivares Martos
***

- **Asignatura:** Sistemas Operativos.
- **Curso Académico:** 2023-24.
- **Grado:** Doble Grado en Ingeniería Informática y Matemáticas.
- **Grupo:** Único.
- **Profesor:** Alejandro José León Salas
- **Descripción:** Sesión 5 del Módulo II de las prácticas de SO.
<!--- **Fecha:** 17 de abril de 2023. -->
<!-- - **Duración:** -->


## Ejercicio 1. Compila y ejecuta los siguientes programas y trata de entender su funcionamiento.

```c
/*
 envioSignal.c
 Trabajo con llamadas al sistema del Subsistema de Procesos conforme a POSIX 2.10
 Utilización de la llamada kill para enviar una señal:
 0: SIGTERM
 1: SIGUSR1
 2: SIGUSR2
  a un proceso cuyo identificador de proceso es PID.
 SINTAXIS: envioSignal [012] <PID> 
*/


#include <sys/types.h> //POSIX Standard: 2.6 Primitive System Data Types 
#include<limits.h> //Incluye <bits/posix1_lim.h> POSIX Standard: 2.9.2 //Minimum    //Values Added to <limits.h> y <bits/posix2_lim.h>
#include <unistd.h> //POSIX Standard: 2.10 Symbolic Constants         <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>
int main(int argc, char *argv[]){
	long int pid;
	int signal;

	if(argc<3) {
		printf("\nSintaxis de ejecucion: envioSignal [012] <PID>\n\n");
        exit(EXIT_FAILURE);
    }

	pid=strtol(argv[2],NULL,10);
	// Comprobación avanzada de errores en el strol
	if(pid == LONG_MIN || pid == LONG_MAX){
        if(pid == LONG_MIN)
         	printf("\nError por desbordamiento inferior LONG_MIN %ld",pid);
		else
            printf("\nError por desbordamiento superior LONG_MAX %ld",pid);

		perror("\nError en strtol");
		exit(EXIT_FAILURE);
    }
    
	signal=atoi(argv[1]);
    
	switch(signal) {
        case 0: //SIGTERM
            kill(pid,SIGTERM); break;
		case 1: //SIGUSR1
            kill(pid,SIGUSR1); break;
		case 2: //SIGUSR2
            kill(pid,SIGUSR2); break;
		default : // not in [012]
            printf("\n No puedo enviar ese tipo de senal"); 
	}
}
```


```c
/*
 reciboSignal.c
 Trabajo con llamadas al sistema del Subsistema de Procesos conforme a POSIX 2.10
 Utilización de la llamada sigaction para cambiar el comportamiento del proceso       
 frente a la recepción de una señal.
*/

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include <stdlib.h>

static void sig_USR_hdlr(int sigNum){

    if(sigNum == SIGUSR1)
        printf("\nRecibida la senal SIGUSR1\n\n");
    else if(sigNum == SIGUSR2)
        printf("\nRecibida la senal SIGUSR2\n\n"); 
}



int main(int argc, char *argv[]){

    struct sigaction sig_USR_nact;

    if(setvbuf(stdout,NULL,_IONBF,0))   // Para que no haya buffering
        perror("\nError en setvbuf");

    //Inicializar la estructura sig_USR_na para especificar la nueva acción para la señal.
    sig_USR_nact.sa_handler= sig_USR_hdlr;


    //'sigemptyset' inicia el conjunto de señales dado al conjunto vacio.
    sigemptyset (&sig_USR_nact.sa_mask);
    sig_USR_nact.sa_flags = 0;

    //Establecer mi manejador particular de señal para SIGUSR1
    if( sigaction(SIGUSR1,&sig_USR_nact,NULL) <0){
        perror("\nError al intentar establecer el manejador de senal para SIGUSR1");
        exit(EXIT_FAILURE);
    }

    //Establecer mi manejador particular de señal para SIGUSR2
    if( sigaction(SIGUSR2,&sig_USR_nact,NULL) <0){
        perror("\nError al intentar establecer el manejador de senal para SIGUSR2");
        exit(EXIT_FAILURE);
    
    }


    while(1); //Bucle infinito a la espera de señales
}
```

Veamos en primer lugar qué hace el programa que envía señales. Tras comprobar la validez de los parámetros, le envía al proceso con PID igual al segundo parámetro la señal que se le pasa como primer parámetro. Para ello, utiliza la función `kill()`, que recibe como primer parámetro el PID del proceso al que se le quiere enviar la señal y como segundo parámetro el tipo de señal que se le quiere enviar. Notemos que la distinción entre qué señal enviar se hace mediante un `switch` que recibe como parámetro el primer parámetro del programa.

Por otro lado, el programa que recibe señales, tras establecer que no haya buffering para que las señales se muestren nada más se recibidas, inicializa la estructura `sigaction` para especificar la nueva acción para la señal. En este caso, la nueva acción es la función `sig_USR_hdlr`, que se encarga de imprimir por pantalla el mensaje correspondiente a la señal recibida. Tras eliminar la máscara y las banderas, se establece el manejador de señal para `SIGUSR1` y `SIGUSR2` mediante la función `sigaction`. Finalmente, el programa entra en un bucle infinito a la espera de señales.

Para probar este programa, ejecutamos en segundo plano el programa que recibe señales, y se nos informará de su `PID`. Posteriormente, ejecutamos el programa que envía señales con el 0, 1 o 2 (dependiendo de la señal que queramos enviar) junto con el `PID` del proceso que está en segundo plano. Este es un ejemplo:
```console
$ ./P5_Ej_1_Rec &
[1] 25655
$ ./P5_Ej_1_Env 1 25655
 
Recibida la senal SIGUSR1

$ ./P5_Ej_1_Env 2 25655
 
Recibida la senal SIGUSR2

$ ./P5_Ej_1_Env 0 25655
[1]+  Terminated              ./P5_Ej_1_Rec
```

Como podemos ver, al enviar la señal `SIGUSR1` o `SIGUSR2`, el programa que recibe señales imprime por pantalla el mensaje correspondiente. Sin embargo, al enviar la señal `SIGTERM`, el programa que recibe señales termina su ejecución.


## Ejercicio 2.

Escribe un programa en C llamado contador, tal que cada vez que reciba una señal que se pueda manejar, muestre por pantalla la señal y el número de veces que se ha recibido ese tipo de señal, y un mensaje inicial indicando las señales que no puede manejar. En el cuadro siguiente se muestra un ejemplo de ejecución del programa.

```console
$ ./P5_Ej_2 &
[1] 28751
No se puede manejar la señal SIGKILL (9)
No se puede manejar la señal SIGSTOP (19)
Esperando el envio de señales...
$ kill -SIGINT 28751
Señal 2 recibida 1 veces
$ kill -SIGINT 28751
Señal 2 recibida 2 veces
$ kill -SIGTERM 28751
Señal 15 recibida 1 veces
$ kill -111 28751
bash: kill: 111: invalid signal specification
$ kill -SIGSTOP 28751

[1]+  Stopped                 ./P5_Ej_2

$ kill -SIGTERM 28751
$ kill -SIGTERM 28751
$ kill -SIGTERM 28751
$ kill -SIGTERM 28751
$ kill -SIGCONT 28751
Señal 18 recibida 1 veces
Señal 15 recibida 2 veces
$ kill -SIGKILL 28751
[1]+  Killed                  ./P5_Ej_2
```

Notemos que, antes de que se bloquease el proceso, la señal `SIGTERM (15)` se había recibido 1 vez. Tras llamarla 4 veces mientras estaba bloqueado, tan solo ha aumentado en una unidad el contador. Esto se debe a que, mientras que el proceso o la señal están bloqueados, si se llaman más de una vez se contabilizan como solo una.

El programa que he realizado es el siguiente:

```c
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include <stdlib.h>

#define FIRST_SIGNAL 1 //Señales iniciales y finales. Visible en man 7 signal
#define LAST_SIGNAL 31 
#define NUM_SIGNALS (LAST_SIGNAL - FIRST_SIGNAL) //Número de señales
int contadores[NUM_SIGNALS]; //Array de contadores de señales

void handler(int sig){

    // Incrementamos el contador de la señal recibida
    contadores[sig - FIRST_SIGNAL]++;

    // Imprimimos el número de señal recibida y el número de veces que se ha recibido
    printf("Señal %d recibida %d veces\n", sig, contadores[sig - FIRST_SIGNAL]);
}

int main(int argc, char *argv[]){

    if(argc != 1){
        printf("Error en el número de argumentos\n");
        printf("Uso: ./P5_Ejercicio_2\n");
        exit(EXIT_FAILURE);
    }

    // Iniciamos contadores a 0, ya que incialmente no se ha llamado a ninguna señal
    for(int i = FIRST_SIGNAL; i <= LAST_SIGNAL; i++)
        contadores[i] = 0;

    // Definimos la estructura sigaction
    struct sigaction sa;
    sa.sa_handler = handler;
    sa.sa_flags = 0; //Reinicio de llamadas interrumpidas por señales
    sigemptyset(&sa.sa_mask); //Inicializamos la máscara de señales a vacío


    // Recorremos todas las señales
    for(int i = FIRST_SIGNAL; i <= LAST_SIGNAL; i++){

        // Ignoramos la señal SIGKILL y SIGSTOP, ya que estas no se pueden capturar
        if(i == SIGKILL)
            printf("No se puede manejar la señal SIGKILL (%i)\n", i);
        else if(i == SIGSTOP)
            printf("No se puede manejar la señal SIGSTOP (%i)\n", i);

        // Para el resto de señales, llamamos a sigaction, cambiando su handler
        else if (sigaction(i, &sa, NULL) < 0) {
            perror("Error en sigaction");
            exit(EXIT_FAILURE);
        }
    }

    printf("Esperando el envio de señales...\n");

    while(1); //Bucle infinito a la espera de señales
}
```

Notemos que, en primer lugar, se hace un array que es el contador para cada una de las señales (se ha visto cuántas hay en `man 7 signal`). El `handler` tan solo aumenta en una unidad el contador y muestra el valor por pantalla.

Respecto al bucle que modifica el handler para todas las señales, notemos que `SIGSTOP` y `SIGKILL` se saltan, pues no se pueden manejar.


## Ejercicio 3.

Escribe un programa que suspenda la ejecución del proceso actual hasta que se reciba la señal `SIGUSR1`. Consulta en el manual en línea `sigemptyset` para conocer las distintas operaciones que permiten configurar el conjunto de señales de un proceso.

```c
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include <stdlib.h>

#define SENAL_ESPERADA SIGUSR1 // El proceso se bloque hasta que reciba dicha señal

int main(int argc, char *argv[]){

    if(argc != 1){
        printf("Error en el número de argumentos\n");
        printf("Uso: ./P5_Ejercicio_3\n");
        exit(EXIT_FAILURE);
    }


    sigset_t new_mask;

    sigfillset(&new_mask); // Inicializamos la máscara de señales lleno
    sigdelset(&new_mask, SENAL_ESPERADA); // Eliminamos la señal a la máscara
    
    sigsuspend(&new_mask); // El proceso se bloquea hasta que reciba la señal

    printf("Señal recibida\n");
    
    exit(EXIT_SUCCESS);
}
```

En este caso, tan solo es destacable el algortimo usado. En primer lugar, se inicializa la máscara de señales a lleno con `sigfillset`. Posteriormente, se elimina la señal que se espera recibir de la máscara. Finalmente, se bloquea el proceso hasta que reciba la señal esperada. Cuando la recibe, se muestra por pantalla el mensaje correspondiente.


## Ejercicio 4.

Compila y ejecuta el siguiente programa y trata de entender su funcionamiento.

```c
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

static int signal_recibida = 0;

static void manejador (int sig){
    signal_recibida = 1;
}


int main (int argc, char *argv[])
{
    sigset_t conjunto_mascaras;
    sigset_t conj_mascaras_original;
    struct sigaction act;
    
    //Iniciamos a 0 todos los elementos de la estructura act 
    memset (&act, 0, sizeof(act));

    act.sa_handler = manejador;

    if (sigaction(SIGTERM, &act, 0)) {
        perror ("sigaction");
        exit(EXIT_FAILURE);
    }
    
    //Iniciamos un nuevo conjunto de mascaras
    sigemptyset (&conjunto_mascaras);
    //Añadimos SIGTERM al conjunto de mascaras
    sigaddset (&conjunto_mascaras, SIGTERM);
    
    //Bloqueamos SIGTERM
    if (sigprocmask(SIG_BLOCK, &conjunto_mascaras, &conj_mascaras_original) < 0) {
        perror ("primer sigprocmask");
        exit(EXIT_FAILURE);
    }

    sleep (10);

    //Restauramos la señal y desbloqueamos SIGTERM
    if (sigprocmask(SIG_SETMASK, &conj_mascaras_original, NULL) < 0) {
        perror ("segundo sigprocmask");
        exit(EXIT_FAILURE);
    }

    sleep (1);

    if (signal_recibida)
        printf ("\nSenal recibida\n");
    

   exit(EXIT_SUCCESS);
}
```

Notemos que en primer lugar se usa `memset`, función de gran ayuda que le permite inicializar todo el `sigaction` a 0. Posteriormente, se inicializa el manejador de señales para `SIGTERM` a la función que simplemente pone a `1` la variable signal recibida.

Tras ello, se inicializa un nuevo conjunto de máscaras y se añade `SIGTERM` a dicho conjunto. Posteriormente, se bloquea `SIGTERM` mediante `sigprocmask`. Tras dormir 10 segundos, se restaura la señal y se desbloquea `SIGTERM`. Finalmente, se duerme un segundo y se comprueba si se ha recibido la señal. En caso afirmativo, se muestra por pantalla el mensaje correspondiente.

Veamos qué ocurre si ejecutamos el programa:
```console
$ ./P5_Ej4 &
[1] 6590
$ kill -SIGTERM 6590
$ 
Senal recibida
[1]+  Done                    ./P5_Ej4
```

Notemos que tras enviar la señal `SIGTERM`, el programa no cambia ni da señales de cualquier problema. No obstante, cuando se desbloquea la señal, se recibe esta por estar pendiente y se desbloquea el programa, terminándose su ejecución.