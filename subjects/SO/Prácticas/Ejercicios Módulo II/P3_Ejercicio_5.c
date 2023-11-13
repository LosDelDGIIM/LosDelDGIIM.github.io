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
