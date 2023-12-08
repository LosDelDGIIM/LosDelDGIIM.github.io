# Sistemas Operativos.  Módulo II. Práctica 03.

**Autor:** Arturo Olivares Martos
***

- **Asignatura:** Sistemas Operativos.
- **Curso Académico:** 2023-24.
- **Grado:** Doble Grado en Ingeniería Informática y Matemáticas.
- **Grupo:** Único.
- **Profesor:** Alejandro José León Salas
- **Descripción:** Sesión 3 del Módulo II de las prácticas de SO.
<!--- **Fecha:** 17 de abril de 2023. -->
<!-- - **Duración:** -->


## Ejercicio 1.
Implementa un programa en C que tenga como argumento un número entero. Este programa debe crear un proceso hijo que se encargará de comprobar si dicho número es un número par o impar e informará al usuario con un mensaje que se enviará por la salida estándar. A su vez, el proceso padre comprobará si dicho número es divisible por 4, e informará si lo es o no usando igualmente la salida estándar.


Tenemos que el programa es:
```c
/*
P3_Ejercicio_1.c
*/

#include<sys/types.h>	//Primitive system data types for abstraction of implementation-dependent data types.
						//POSIX Standard: 2.6 Primitive System Data Types <sys/types.h>
#include<unistd.h>		//POSIX Standard: 2.10 Symbolic Constants         <unistd.h>
#include<stdio.h>
#include<errno.h>
#include<stdlib.h>

#include<string.h>


int main(int argc, char *argv[]){

	// Comprobación del número de parámetros
	if (argc != 2){
		printf("Uso: P3_Ejercicio_1 <entero>\n");
		exit(EXIT_FAILURE);
	}

	int n = atoi(argv[1]);

	pid_t retval;
	if ((retval = fork()) < 0){
		perror("Error en el fork");
		exit(EXIT_FAILURE);
	}
	
	if (retval == 0){	// Hijo. Se comprueba si el número es par o impar.

		char tipo_num[10];

		// Comprobación del tipo de número
		if (n%2 == 0)
			strcpy(tipo_num, "par");
		else
			strcpy(tipo_num, "impar");
		
		// Imprime si el número es par o impar
		printf("El número %d es %s.\n", n, tipo_num);

		return EXIT_SUCCESS; // Necesario para que el hijo no ejecute el código del padre
	}


	char tipo_num[10];

	// Comprobación de la divisibilidad entre 4
	if (n%4 != 0)
		strcpy(tipo_num, " no");
	
	// Imprime si el número es par o impar
	printf("El número %d%s es divisible entre 4.\n", n, tipo_num);

	return EXIT_SUCCESS;
}
```

El resultado de la ejecución del programa es:
```console
$ ./P3_Ejercicio_1 4
El número 4 es divisible entre 4.
El número 4 es par.
```

## Ejercicio 2.
¿Qué hace el siguiente programa? Intenta entender lo que ocurre con las variables y sobre todo con los mensajes por pantalla cuando el núcleo tiene activado/desactivado el mecanismo de buffering.

El programa es:
```c
//P3_Ejercicio_2.c
//Trabajo con llamadas al sistema del Subsistema de Procesos "POSIX 2.10 compliant"
//Prueba el programa tal y como está. Después, elimina los comentarios (1) y pruebalo de nuevo.

#include<sys/types.h>	//Primitive system data types for abstraction of implementation-dependent data types.
						//POSIX Standard: 2.6 Primitive System Data Types <sys/types.h>
#include<unistd.h>		//POSIX Standard: 2.10 Symbolic Constants         <unistd.h>
#include<stdio.h>
#include<errno.h>
#include <stdlib.h>

#include <string.h>

int global=6;
char buf[]="cualquier mensaje de salida\n";

int main(int argc, char *argv[]){
	int var;
	pid_t pid;

	var=88;
	// Se ha cambiado sizeof(buf)+1 por strlen(buf), ya que esta función permite que no dependa de la plataforma.
	if(write(STDOUT_FILENO,buf,strlen(buf)) != strlen(buf)) {
		perror("\nError en write");
		exit(EXIT_FAILURE);
	}

	//(1)if(setvbuf(stdout,NULL,_IONBF,0)) {
	//	perror("\nError en setvbuf");
	//  exit(EXIT_FAILURE);
	//}


	printf("\nMensaje previo a la ejecución de fork");

	if( (pid=fork())<0) {
		perror("\nError en el fork");
		exit(EXIT_FAILURE);
	}

	else if(pid==0) {  
		//proceso hijo ejecutando el programa
		global++;
		var++;
	} else  //proceso padre ejecutando el programa
		sleep(1);
		
				
	printf("\npid= %d, global= %d, var= %d\n", getpid(),global,var);
	exit(EXIT_SUCCESS);
}
```

El programa, tal y como está sin descomentar (1), imprime en lugar por salida estándar el mensaje de salida. Posteriormenete, se ejecuta el `fork()`.

El proceso hijo incrementa en 1 la variable global y la variable local, por lo que al imrpimirlas se ve que han aumentado.

El proceso padre, tras esperar 1 segundo, imprime el valor de las variables global y local, que no se han modificado. Esto se debe a que el padre y el hijo tienen espacios de direcciones distintas, que se copial al realizar el `fork()`. Por tanto, cuando se aumentan en el hijo no se aumentan en el padre.

Notemos que para que el padre espere al hijo, se ha usado la función `sleep()`, que hace que el proceso se suspenda durante un tiempo determinado. En este caso, se suspende durante 1 segundo. Esto en realidad no es la mejor opción ya que se debería usar la orden `wait()`, que veremos más adelante.

La salida del programa es:
```console
$ ./P3_Ejercicio_2
cualquier mensaje de salida

Mensaje previo a la ejecución de fork
pid= 6706, global= 7, var= 89
Mensaje previo a la ejecución de fork
pid= 6705, global= 6, var= 88
```

Si descomentamos (1), esta es la salida del programa:
```console
$ ./P3_Ejercicio_2
cualquier mensaje de salida

Mensaje previo a la ejecución de fork
pid= 7099, global= 7, var= 89

pid= 7098, global= 6, var= 88
```
Notemos que ahora el mensaje previo solo se imprime una vez, mientras que antes se imprimía 2 veces. Esto se debe a la gestión del buffer del flujo de la salida estándar, `stdout`.

La función `write()` no lleva buffering, por lo que nada más ejecutarse se imprime en el archivo con el `fd` asociado, en este caso `stdout`. No obstante, las funciones de C de `stdio.h` sí realizan por defecto buffering de salida, y `printf()` es una de ellas. Por norma general, suele ser buffering por bloque, pero cuando el flujo de salida asociado es una terminal (como el caso de `stdou` que es el asociado a `printf`) el buffering es por línea. Esto implica que todo se guarda en un buffer hasta que recibe un salto de línea, y entonces se imprime en el flujo asociado.

Como por defecto el buffer es por línea, antes de descomentar (1) el mensaje previo se guardó en el buffer asociado a `stdout`, pero no se imprimió ya que no termina en un `\n`. Al ejecutar el `fork()`, como se realiza una copia de memoria también se copió el buffer, y por tanto tanto el hijo como el padre imprimieron el mensaje previo cuando llegaron al `\n` del último `printf()` del programa.

La orden `int setvbuf(FILE *stream, char *buf, int mode, size_t size)` cambia el buffering del flujo dado mediante `stream` al modo especificado en `mode`. En nuestro caso, se cambia el buffering de la salida estadar a `_IONBF` _(input-output no buffering)_. Por tanto, nada más ejecutarse el `printf()` del mensaje previo se imprime el mensaje, por lo que tanto en el caso del padre como en el del hijo ya no se imprime. Es decir, se imprime solo una vez.



## Ejercicio 3.
Indica qué tipo de jerarquías de procesos se generan mediante la ejecución de cada una de las dos jerarquías de procesos descritas a continuación. Comprueba tu solución implementando un código para generar 20 procesos en cada caso, en donde cada proceso imprima su PID y el del padre, PPID.

La jerarquía de procesos tipo 1 es:
```c
for (int i=0; i<NPROCS; i++){
	if ((childpid = fork()) == -1){
		fprintf(stderr, "Could not create child %d: %s\n", i, strerror(errno));
		exit(EXIT_FAILURE);
	}

	if (childpid != 0){ //(childpid)
		break;
	}
}
```

En este caso, vemos que el proceso padre crea un hijo y termina su ejecución, ya que se encuentra el `break` y sale del bucle. A su vez, ese hijo crea un solo nieto y termina también su ejecución; y así sucesivamente. Por tanto, en cada generación solo se crea un proceso, pero se aumenta en una generación.


La jerarquía de procesos tipo 2 es:
```c
for (int i=0; i<NPROCS; i++){
	if ((childpid = fork()) == -1){
		fprintf(stderr, "Could not create child %d: %s\n", i, strerror(errno));
		exit(EXIT_FAILURE);
	}

	if (childpid == 0){ //(!childpid)
		break;
	}
}
```

En este caso, vemos que el proceso padre crea `NPROCS` hijos, pero cada uno no genera ningún nieto ya que el `break` hace que se salga del bucle. Por tanto, se crea un árbol con el padre como raíz y `NPROCS` hijos.


El programa para probar su ejecución es:
```c
//P3_Ejercicio_3.c

#include<sys/types.h>	//Primitive system data types for abstraction of implementation-dependent data types.
						//POSIX Standard: 2.6 Primitive System Data Types <sys/types.h>
#include<unistd.h>		//POSIX Standard: 2.10 Symbolic Constants         <unistd.h>
#include<stdio.h>
#include<errno.h>
#include <stdlib.h>

#include <string.h>

#define TIPO_1 1	// Definir para jerarquía de procesos 1
					// No definir para jerarquía de procesos 2

int main(int argc, char *argv[]){
	
	const int NPROCS = 20;
	pid_t childpid;


	#ifdef TIPO_1
	// Jerarquía de procesos 1
	for (int i=0; i<NPROCS; i++){
		if ((childpid = fork()) == -1){
			fprintf(stderr, "Could not create child %d: %s\n", i, strerror(errno));
			exit(EXIT_FAILURE);
		}

		if (childpid != 0){ // (childpid)
			break;
		}
	}
	#endif

	#ifndef TIPO_1
	// Jerarquía de procesos 2
	for (int i=0; i<NPROCS; i++){
		if ((childpid = fork()) == -1){
			fprintf(stderr, "Could not create child %d: %s\n", i, strerror(errno));
			exit(EXIT_FAILURE);
		}

		if (childpid == 0){ // (!childpid)
			break;
		}
	}
	#endif

	
	printf("Proceso: %d\t\tPadre: %d\n", getpid(), getppid());

	exit(EXIT_SUCCESS);
}
```

No obstante, la salida no está definida ya que el proceso padre termina antes que sus descendientes lo hagan, por lo que quedan _zombies_ (procesos sin padre asociado). Para resolver esto, tendría que usarse la orden `wait()`, que se verá más adelante.


## Ejericio 4
Implementa un programa que lance cinco procesos hijo. Cada uno de ellos se identificará en la salida estándar, mostrando un mensaje del tipo `Soy el hijo PID`. El proceso padre simplemente tendrá que esperar la finalización de todos sus hijos y cada vez que detecte la finalización de uno de sus hijos escribirá en la salida estándar un mensaje del tipo:
> Acaba de finalizar mi hijo con <PID>
> 
> Sólo me quedan <NUM_HIJOS> hijos vivos

El programa es:
```c
//P3_Ejercicio_4.c

#include<sys/types.h>	//Primitive system data types for abstraction of implementation-dependent data types.
						//POSIX Standard: 2.6 Primitive System Data Types <sys/types.h>
#include<unistd.h>		//POSIX Standard: 2.10 Symbolic Constants         <unistd.h>
#include<stdio.h>
#include<errno.h>
#include <stdlib.h>

#include <sys/wait.h>

int main(int argc, char *argv[]){
	
	const int N_PROCS = 5;	// Número de hijos a lanzar
	int procs_vivos = N_PROCS;	// Número de hijos vivos

	pid_t retval;
	for (int i=0; i<N_PROCS; i++){		// Creación de los procesos hijos
		if ((retval = fork()) < 0){
			printf("Error al crear el proceso hijo\n");
			perror("fork");
			exit(EXIT_FAILURE);
		}
		
		if (retval == 0){	// Código del hijo
			printf("Soy el hijo %d, mi padre es %d\n", getpid(), getppid());
			exit(EXIT_SUCCESS);
		}
	}


	while (procs_vivos > 0){ // Espera a que todos los hijos finalicen. El orden de finalización no importa.

		if ((retval = wait(NULL)) <= 0){
			printf("Error en la invocacion de wait o la llamada ha sido interrumpida por una señal.\n");
			perror("waitpid");
			exit(EXIT_FAILURE);
		}

		printf("Acaba de finilizar mi hijo con PID %d\n", retval);
		printf("Solo me quedan %d hijos vivos\n", --procs_vivos);
	}


	exit(EXIT_SUCCESS);
}
```

Vemos que, tras la creación de los procesos, el padre espera a que todos los hijos finalicen. Para esto, se usa la orden `wait()`, que espera a que finalice un proceso hijo. En este caso, se espera a que finalice cualquier hijo sin importar el orden.


## Ejercicio 5
Implementa una modificación sobre el anterior programa ([Ejercicio 4](#ejercicio-4)) en la que el proceso padre espera primero a los hijos creados en orden impar (1º,3º,5º) y después a los hijos pares (2º y 4º).

El programa es:
```c
//P3_Ejercicio_5.c

#include<sys/types.h>	//Primitive system data types for abstraction of implementation-dependent data types.
						//POSIX Standard: 2.6 Primitive System Data Types <sys/types.h>
#include<unistd.h>		//POSIX Standard: 2.10 Symbolic Constants         <unistd.h>
#include<stdio.h>
#include<errno.h>
#include <stdlib.h>

#include <sys/wait.h>

int main(int argc, char *argv[]){
	
	const int N_PROCS = 5;	// Número de hijos a lanzar
	int procs_vivos = N_PROCS;	// Número de hijos vivos

	pid_t child_procs[N_PROCS];	// Array de PIDs de los hijos

	pid_t retval;
	for (int i=0; i<N_PROCS; i++){		// Creación de los procesos hijos
		if ((retval = fork()) < 0){
			printf("Error al crear el proceso hijo\n");
			perror("fork");
			exit(EXIT_FAILURE);
		}
		
		if (retval == 0){	// Código del hijo
			printf("Soy el hijo %d, mi padre es %d\n", getpid(), getppid());
			exit(EXIT_SUCCESS);
		}

		child_procs[i] = retval;	// Guardamos el PID del hijo en el array
	}


	// Esperamos a los hijos impares (ínidices pares por empezar desde 0)
	for (int i=0; i<N_PROCS; i+=2){
		if ((retval = waitpid(child_procs[i], NULL, 0)) <= 0){
			printf("Error en la invocacion de wait o la llamada ha sido interrumpida por una señal.\n");
			perror("waitpid");
			exit(EXIT_FAILURE);
		}

		printf("Acaba de finilizar mi hijo con PID %d\n", retval);
		printf("Solo me quedan %d hijos vivos\n", --procs_vivos);
	}

	// Esperamos a los hijos pares (ínidices impares por empezar desde 0)
	for (int i=1; i<N_PROCS; i+=2){
		if ((retval = waitpid(child_procs[i], NULL, 0)) <= 0){
			printf("Error en la invocacion de wait o la llamada ha sido interrumpida por una señal.\n");
			perror("waitpid");
			exit(EXIT_FAILURE);
		}

		printf("Acaba de finilizar mi hijo con PID %d\n", retval);
		printf("Solo me quedan %d hijos vivos\n", --procs_vivos);
	}

	exit(EXIT_SUCCESS);
}
```

Vemos que, tras la creación de los procesos en la que se han almacenado los PID de los hijos, el padre espera a que todos los hijos finalicen. Para esto, se usa la orden `waitpid()`, que espera a que finalice un proceso hijo. En este caso, se espera a que finalice un hijo concreto, que se especifica mediante el PID del hijo. Además, se espera a que finalice en orden, ya que se espera a que finalice el hijo con índice par y luego el hijo con índice impar.

## Ejercicio 6

¿Qué hace el siguiente programa?
```c
//P3_Ejercicio_6.c

//Trabajo con llamadas al sistema del Subsistema de Procesos conforme a POSIX 2.10

#include<sys/types.h>	
#include<sys/wait.h>	
#include<unistd.h>
#include<stdio.h>
#include<errno.h>
#include <stdlib.h>


int main(int argc, char *argv[]){
	pid_t pid;
	int estado;

	if( (pid=fork())<0) {
		perror("\nError en el fork");
		exit(EXIT_FAILURE);
	}
	else if(pid==0) {  //proceso hijo ejecutando el programa
		if( (execl("/usr/bin/ldd","ldd","./tarea5", NULL)<0)) {
			perror("\nError en el execl");
			exit(EXIT_FAILURE);
		}
	}
	wait(&estado);
	/*
	<estado> mantiene información codificada a nivel de bit sobre el motivo de finalización del proceso hijo 
	que puede ser el número de señal o 0 si alcanzó su finalización normalmente.
	Mediante la variable estado de wait(), el proceso padre recupera el valor especificado por el proceso hijo
	como argumento de la llamada exit(), pero desplazado 1 byte porque el sistema incluye en el byte menos significativo 
	el código de la señal que puede estar asociada a la terminación del hijo.
	
	Por eso se utiliza estado>>8 de forma que obtenemos el valor del argumento del exit() del hijo.
	*/

	printf("\nMi hijo %d ha finalizado con el estado %d\n",pid,estado>>8);

	exit(EXIT_SUCCESS);

}
```

Vemos que en primer lugar se crea un hijo mediante `fork()`. No obstante, en vez de ejecutar un código disponible en este archivo `.c`, se ejecuta el programa `ldd`. Esto es equivalente a que si en la terminal pusiésemos:
```console
$ ldd ./tarea5
```

Una vez creado, el padre espera a que el hijo termine. Además, obtiene el estado del hijo mediante la variable `estado`. Para esto, en el manual en línea de `exec()`, donde `wstatus` representa `estado`, vemos lo siguiente:
```console
WIFEXITED(wstatus)
		returns true if the child terminated normally, that is, by calling exit(3) or _exit(2), or by returning from main().

WEXITSTATUS(wstatus)
		returns the exit status of the child.  This consists of the least significant 8 bits of the status argument that the child specified in  a call to exit(3) or _exit(2) or as the argument for a return statement in main().  This macro should be employed only if WIFEX‐
		ITED returned true.
```
Por tanto, vemos que para obtener el estado de finalización, podemos ejecutar `WEXITSTATUS(estado)`, que nos devuelve el estado del hijo.

El manual nos informa de que el estado del hijo se almacena en los 8 bits menos significativos, por lo que a priori se puede aplicar la máscara `0xFF` para obtener el estado del hijo. No obstante, en la práctica el manual está el equivocado, ya que el estado de salida se puede obtener con `estado>>8`. Esto se puede deber a diferencias entre _big-endian_ y _little-endian_. Para evitar problemas, se recomienda usar `WEXITSTATUS(estado)` para obtener el estado del hijo. 


## Ejercicio 7

Escribe un programa que acepte como argumentos el nombre de un programa, sus argumentos si los tiene, y opcionalmente la cadena `bg`. Nuesto programa deberá ejecutar el programa pasado como primer argumento en foreground si no se especifica la cadena `bg` y en background en caso contrario. Si el programa tiene argumentos hay que ejecutarlo con éstos.

El programa es:
```c
//P3_Ejercicio_7.c

#include<sys/types.h>	
#include<sys/wait.h>	
#include<unistd.h>
#include<stdio.h>
#include<errno.h>
#include <stdlib.h>

#include <string.h>


int main(int argc, char *argv[]){

	if (argc < 2){
		printf("Uso: %s <path> [argumentos] [bg]\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	
	// Obtención de los parámetros. El primero no se tiene en cuenta, ya que es este programa.
	// Se desplazan por tanto uno a la izquierda.
	char* params[argc-1]; // Array de parámetros a pasar al programa de execvp
	for (int i=0; i<argc-1; i++)
		params[i] = argv[i+1];


	// Comprobación de si es en bg o no
	int foreground = 1;		// Por defecto, se ejecuta en fg
	if ((argc > 2) && strcmp(argv[argc-1], "bg") == 0){
		foreground = 0;
		params[argc-2] = NULL;		// Borrado lógico del parámetro bg
	}
	else{
		params[argc-1] = NULL;
	}
	
	
	pid_t retval;
	if( (retval=fork())<0) {
		perror("\nError en el fork");
		exit(EXIT_FAILURE);
	}
	
	if(retval==0) {  //proceso hijo ejecutando el programa
		if( (execvp(params[0],params)<0)) {
			printf("Error al ejecutar execvp() con ruta (%s)\n", params[0]);
			perror("\nError en el execvp");
			exit(EXIT_FAILURE);
		}
	}

	if (foreground){
		wait(NULL);
		printf("El programa ha terminado de ejecutarse en primer plano.\n\n");
	}
	else{
		waitpid(-1, NULL, WNOHANG);
		printf("El programa se está ejecutando en segundo plano.\n\n");
	}

	exit(EXIT_SUCCESS);
}
```
Para ejecutar en segundo plano, se usa la opción `WNOHANG`. Esto, según el manual, hace:
> WNOHANG
> 		return immediately if no child has exited.

Es decir, el proceso padre no espera a que el hijo termine, sino que sigue su ejecución y, por tanto, finaliza antes que el hijo. Esto es lo que se quiere para que se ejecute en segundo plano. Informa al SO de que se encargue de liberar la memoria del hijo cuando este termine.