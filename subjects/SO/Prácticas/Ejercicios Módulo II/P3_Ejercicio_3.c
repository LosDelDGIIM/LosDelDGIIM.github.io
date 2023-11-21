//P3_Ejercicio_3.c

#include<sys/types.h>	//Primitive system data types for abstraction of implementation-dependent data types.
						//POSIX Standard: 2.6 Primitive System Data Types <sys/types.h>
#include<unistd.h>		//POSIX Standard: 2.10 Symbolic Constants         <unistd.h>
#include<stdio.h>
#include<errno.h>
#include <stdlib.h>

#include <string.h>

// #define TIPO_1 1	// Definir para jerarquía de procesos 1
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

		if (childpid == 0){
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

		if (childpid != 0){
			break;
		}
	}
	#endif

	
	printf("Padre: %d\t\tHijo: %d\n", getppid(), getpid());

	exit(EXIT_SUCCESS);
}
