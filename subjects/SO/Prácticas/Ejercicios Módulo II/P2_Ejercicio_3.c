/*
P2_Ejercicio_3.c
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



/**
 * @brief Busca en el directorio especificado los archivos que cumplen los permisos especificados.
 * 
 * @param path_dir  Directorio en el que se busca.
 * @param count_files  Contador de archivos que cumplen los permisos.
 * @param tot_size  Tamaño total acumulados de los archivos que cumplen los permisos.
 * @param PERM  Permisos que se buscan.
 */
void busqueda_directorio(const char *path_dir, long* count_files, long* tot_size, const mode_t PERM){

	// Abrimos el directorio
	DIR* directorio;
	if ((directorio=opendir(path_dir)) == NULL){
		printf("Error %d en opendir(%s)\n", errno, path_dir);
		perror("\nError en opendir.");
		exit(EXIT_FAILURE);
	}

	errno = 0; // Para detectar si ha habido error en readdir
	struct dirent *entrada;	// Cada entrada del directorio
	struct stat atributos;	// La stat de cada entrada
	while ((entrada=readdir(directorio))!= NULL){

		// Se saltan los directorios que mantienen la jerarquía
		if ((strcmp(entrada->d_name, "." )==0) || (strcmp(entrada->d_name, "..")==0))
			continue;

		char path_entrada[500];	// Compongo para que las rutas sean absolutas, ya que si no, no funciona
		sprintf(path_entrada, "%s/%s", path_dir, entrada->d_name);
		
		// Para obtener el número de inodo y el tipo de archivo.
		if (lstat(path_entrada, &atributos) < 0){
			printf("\nError %d al intentar acceder a los atributos de %s.\n",errno, path_entrada);
			perror("\nError en lstat");
			exit(EXIT_FAILURE);
		}

		// Si es un directorio, se busca ahora dentro de él
		if (S_ISDIR(atributos.st_mode))
			busqueda_directorio(path_entrada, count_files, tot_size, PERM);

		// Si no es un directorio y tiene los permisos buscados, se imprime y se contabiliza
		else if ((atributos.st_mode & PERM) == PERM){
			printf("\t%-20s:\t %9lu\n", path_entrada, entrada->d_ino);
			(*count_files) ++;
			(*tot_size) += atributos.st_size;
		}

		errno = 0;	// Para detectar si ha habido error en readdir
	}

	if (errno != 0){ // Ha habido error en readdir
		printf("Error %d en readdir(%s)\n", errno, path_dir);
		perror("\nError en readdir.");
		exit(EXIT_FAILURE);
	}

	if (closedir(directorio) < 0){ // Ha habido error en closedir
		printf("Error %d en closedir(%s)\n", errno, path_dir);
		perror("\nError en readdir.");
		exit(EXIT_FAILURE);
	}
}

int main(int argc, char *argv[]){

	// Comprobación del número de parámetros
	if (argc > 2){
		printf("Uso: P2_Ejercicio_3 [<pathname>]\n");
		exit(EXIT_FAILURE);
	}

	// Obtención del directorio inicial de búsqueda
	char path_ini[100] = ".";	// Default

	if (argc == 2)	// Si se le da un directorio, se actualiza.
		strcpy(path_ini, argv[1]);

	// Los permisos buscados son los de ejecución para el grupo y others.
	const mode_t PERM = S_IXGRP | S_IXOTH;

	long tot_size = 0;	// Bytes totales que cumplen los permisos especificados
	long count_files = 0;	// Contador de los archivos que cumplen esos datos

	printf("Los i-nodos son:\n");
	busqueda_directorio(path_ini, &count_files, &tot_size, PERM);	// Búsqueda

	printf("\nExisten %ld archivos regulares con permiso x para grupo y otros.\n", count_files);
	printf("El tamaño total ocupado por dichos archivos es %ld bytes.\n", tot_size);

	return EXIT_SUCCESS;
}