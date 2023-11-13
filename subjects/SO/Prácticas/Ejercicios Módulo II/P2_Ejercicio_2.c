/*
P2_Ejercicio_2.c
*/

#include<sys/types.h>	//Primitive system data types for abstraction of implementation-dependent data types.
						//POSIX Standard: 2.6 Primitive System Data Types <sys/types.h>
#include<unistd.h>		//POSIX Standard: 2.10 Symbolic Constants         <unistd.h>
#include<sys/stat.h>
#include<fcntl.h>		//Needed for open
#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include<string.h>
#include<dirent.h>		// Needed por managing directories

int main(int argc, char *argv[]){

	// Comprobación de los parámetros
	if (argc != 3){
		printf("Uso: P2_Ejercicio_2 <pathname> <permisos_nuevos>\n");
		exit(EXIT_FAILURE);
	}

	if (strlen(argv[2])!= 4){
		printf("El número que representa los permisos nuevos ha de tener 4 dígitos.\n");
		exit(EXIT_FAILURE);
	}

	char *invalid;	// Conversión del octal
	mode_t new_perm = strtol(argv[2], &invalid, 8);
	if (*invalid != '\0'){ // Ha habido un error al convertir a octal
		printf("El número que representa los permisos ha de ser un octal.\n");
		exit(EXIT_FAILURE);
	}


	DIR *directorio;
	if ((directorio=opendir(argv[1])) == NULL){
		printf("Error %d en opendir(%s)\n", errno, argv[1]);
		perror("\nError en opendir.");
		exit(EXIT_FAILURE);
	}


	errno = 0; // Para detectar si ha habido error en readdir
	const mode_t MASK_PERM = S_IRWXU | S_IRWXG | S_IRWXO | S_ISGID | S_ISUID | S_ISVTX; // Máscara para obtener solo los permisos
	struct dirent *entrada;
	struct stat atributos;
	while ((entrada=readdir(directorio))!= NULL){
		
		// Para obtener los permisos antiguos llamamos a lstat.
		if (lstat(entrada->d_name, &atributos) < 0){
			printf("\nError %d al intentar acceder a los atributos de %s.\n",errno, entrada->d_name);
			perror("\nError en lstat");
			exit(EXIT_FAILURE);
		}

		// A los directorios no se le cambian los permisos, solo a los archivos
		if (! S_ISDIR(atributos.st_mode)){
			mode_t old_perm = atributos.st_mode & MASK_PERM;

			if (chmod(entrada->d_name, new_perm) < 0){ // Ha habido error
				printf("%-20s: \t%4d\t %04o\n", entrada->d_name, errno, old_perm);
			}else{	// No ha habido error
				printf("%-20s: \t%04o\t %04o\n", entrada->d_name, old_perm, new_perm);	
			}
		}

		errno = 0;	// Para detectar si ha habido error en readdir
	}

	if (errno != 0){ // Ha habido error en readdir
		printf("Error %d en readdir(%s)\n", errno, argv[1]);
		perror("\nError en readdir.");
		exit(EXIT_FAILURE);
	}





	closedir(directorio);


	return EXIT_SUCCESS;
}