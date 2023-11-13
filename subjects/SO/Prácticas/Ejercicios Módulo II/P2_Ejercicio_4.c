/*
P2_Ejercicio_4.c
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

#define __USE_XOPEN_EXTENDED
#include<ftw.h>		// Needed por managing directories


// Los permisos buscados son los de ejecución para el grupo y others.
const mode_t PERM = S_IXGRP | S_IXOTH;

long tot_size = 0;	// Bytes totales que cumplen los permisos especificados
long count_files = 0;	// Contador de los archivos que cumplen esos datos


/**
 * @brief  Busca en el directorio especificado los archivos que cumplen los permisos especificados como variable global.
 * 
 * @param path  Directorio en el que se busca.
 * @param atributos  Stat de la entrada actual.
 * @param typeflag  Tipo de archivo de la entrada actual.
 * @param ftwbuf  Estructura con información del archivo.
 * @return 0, ya que nunca genera error.
 */
int check_file(const char *path, const struct stat *atributos, int typeflag, struct FTW *ftwbuf){

	// Si no es un directorio y tiene los permisos buscados, se imprime y se contabiliza
	if ( (typeflag != FTW_D) && ((atributos->st_mode & PERM) == PERM) ){
		
		printf("\t%-20s:\t %9lu\n", path, atributos->st_ino);
		count_files ++;
		tot_size += atributos->st_size;
	}

	return 0;
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

	printf("Los i-nodos son:\n");
	// Llamamos con FTW_PHYS para que no siga los enlaces simbólicos.
	// Es decir, para que use lstat en vez de stat, como se hace en el ejercicio 3.
	if (nftw(path_ini, check_file, 10, FTW_PHYS)!= 0){
		perror("Error en nftw");
		exit(EXIT_FAILURE);
	}

	printf("\nExisten %ld archivos regulares con permiso x para grupo y otros.\n", count_files);
	printf("El tamaño total ocupado por dichos archivos es %ld bytes.\n", tot_size);

	return EXIT_SUCCESS;
}