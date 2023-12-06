// P4_Ejercicio_5_Maestro.c

#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<sys/wait.h>

#define NUM_PROC 2
#define BUF_SIZE 100

int main(int argc, char *argv[]){


	if (argc != 3) {
		printf("Usage: %s <extremo_inf> <extremo_sup> \n", argv[0]);
		exit(EXIT_FAILURE);
	}

	// Comprobación del intervalo
	int inf = atoi(argv[1]);
	int sup = atoi(argv[2]);
	if (inf > sup) {
		printf("Usage: %s <extremo_inf> <extremo_sup> \n", argv[0]);
		exit(EXIT_FAILURE);
	}



	// Conversión de los enteros a cadenas de caracteres
	char intervalos[NUM_PROC*2][10]; // Un intervalo por cada proceso

    sprintf(intervalos[0], "%d", inf);
	sprintf(intervalos[NUM_PROC*2-1], "%d", sup);

	// Calculo de los intervalos. Obtenemos los puntos medios
	for (int i=1; i<NUM_PROC; i++){
		int medio_i = inf + (sup-inf)/NUM_PROC*i;
		sprintf(intervalos[2*i-1], 	"%d", medio_i);
		sprintf(intervalos[2*i], 	"%d", medio_i+1);
	}



	// Creación de los cauces para los procesos hijos
	int fd[NUM_PROC][2];	 // Cada proceso tiene un cauce, y cada cauce son 2 file descriptors.

	// Creación de los procesos hijos
	for (int i=0; i<NUM_PROC; i++){

		pid_t retval;
		
		if ( pipe(fd[i]) < 0 ) { // Llamada al sistema para crear un pipe
			perror("\nError en pipe");
			exit(EXIT_FAILURE);
		}

		if ( (retval=fork()) <0) {
			perror("\nError en fork");
			exit(EXIT_FAILURE);
		}

		if (retval == 0) { // Estamos en el hijo

			//Cerrar el descriptor de lectura de cauce en el proceso hijo
			close(fd[i][0]);

			// El proceso hijo escribe en el cauce el resultado de la ejecución del programa esclavo
			// Como el proceso hijo escribe con printf, asociamos la salida estándar al cauce
			dup2(fd[i][1],STDOUT_FILENO);

			// Llamada al programa esclavo con el intervalo correspondiente
			if (execl("./P4_Ej5_E","./P4_Ej5_E",intervalos[2*i],intervalos[2*i+1],NULL) < 0){
				perror("\nError en execl");
				exit(EXIT_FAILURE);
			}
		}

		else { // Proceso padre porque PID != 0.
			
			//Cerrar el descriptor de escritura en cauce situado en el proceso padre
			close(fd[i][1]);
		}

	} // for (int i=0; i<NUM_PROC; i++)
	

	// Código del proceso padre
	int n_leidos;
	char buffer[BUF_SIZE];

	// El proceso padre lee de los cauces y escribe en pantalla
	for (int i=0; i<NUM_PROC; i++)
		while ( (n_leidos = read(fd[i][0], &buffer, sizeof(buffer))) > 0 )
			write(STDOUT_FILENO, &buffer, n_leidos);
	

	// Espera del padre a los hijos
	for (int i=0; i<NUM_PROC; i++)
		wait(NULL);

	return EXIT_SUCCESS;
}