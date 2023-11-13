/*
P1_Ejercicio_2.c
*/
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>  	/* Primitive system data types for abstraction\
			                of implementation-dependent data types.
			                POSIX Standard: 2.6 Primitive System Data Types
                            <sys/types.h>
                        */
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>
#include<string.h>

int main(int argc, char *argv[]){

	int fd_in, fd_out;	

	if (argc != 2 && argc != 1){
		printf("Uso: <P1_Ejercicio_2> <pathname>\n");
		exit(EXIT_FAILURE);
	}	

	// Fichero de entrada. Solo leer
	if (argc == 2){ // Se ha proporcionado un archivo
		const char* path_in = argv[1];
		if( (fd_in=open(path_in,O_RDONLY))<0) {
			printf("\nError %d en open (In)",errno);
			perror("\nError en open");
			exit(EXIT_FAILURE);
		}
	}else{ // No se ha proporcionado archivo. Se lee de la entrada estándar
		fd_in = STDIN_FILENO;
	}

	// Fichero de salida. Si existe lo sobreescribe, y si no existe lo crea.
	const char* path_out = "./salida.txt";
	if( (fd_out=open(path_out,O_CREAT|O_TRUNC|O_WRONLY, S_IRUSR|S_IWUSR))<0) {
		printf("\nError %d en open (Out)",errno);
		perror("\nError en open");
		exit(EXIT_FAILURE);
	}

	int n_bloque = 0;
	const int TAM_BLOQUE = 80;
	char buff[TAM_BLOQUE];	// Buffer en el que se almacena lo leído

	// -----------------------------------------------------------------------------
	// Modificación adicional. Antes de leer, debo escribir el número de bloques.

	int n_bytes = lseek(fd_in, 0, SEEK_END);	// Obtengo el número de bytes totales
	lseek(fd_in, 0, SEEK_SET);	// Para a empezar a leer y escribir desde el principio

	int bloques_totales; // Función ceil aplicada, ya que el último bloque puede no estar completo.
	if ((n_bytes % TAM_BLOQUE) == 0)
		bloques_totales = n_bytes/TAM_BLOQUE;
	else
		bloques_totales = (n_bytes/TAM_BLOQUE) + 1;	
	
	char cadena[100];	// Cadena de inicio
	sprintf(cadena, "El número de bloques es %d\n", bloques_totales);
	write(fd_out, cadena, strlen(cadena));
	// ----------------------------------------------------------------------------


	// Lee paquetes de 80B y los escribe por bloques.
	int n_leidos;
	while (n_leidos = read(fd_in, buff, TAM_BLOQUE)){

		char cabecera[50];
		sprintf(cabecera, "\nBloque %d\n", ++n_bloque);

		// Se escribe en primer lugar el número del bloque
		write(fd_out, cabecera, strlen(cabecera));

		// Se escriben los bits leídos. Es importante notar que no se escriben 80, sino solo los que se ha leído.
		write(fd_out, buff, n_leidos*sizeof(char));
	}
	

	// Se cierran ambos archivos
	close(fd_in);
	close(fd_out);

	return EXIT_SUCCESS;
}