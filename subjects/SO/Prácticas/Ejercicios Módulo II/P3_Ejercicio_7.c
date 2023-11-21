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