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
