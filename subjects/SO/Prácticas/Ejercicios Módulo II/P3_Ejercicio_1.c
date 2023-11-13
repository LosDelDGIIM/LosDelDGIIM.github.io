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