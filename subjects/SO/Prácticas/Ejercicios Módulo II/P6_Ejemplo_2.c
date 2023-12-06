#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include<errno.h>

const int MMAPSIZE=1024;
#define archivo "tmp"

int main(){

	int fd, num, i;
	char ch='\0';
	char *memoria;

	// Abre el archivo
	if ((fd = open(archivo, O_RDWR|O_CREAT|O_EXCL, S_IRWXU))<0){
		perror("Error al abrir el archivo");
		exit(EXIT_FAILURE);
	}

	
	// Escribe en el archivo los caracteres nulos
	for (i=0; i < MMAPSIZE; i++)
		if ((num=write(fd, &ch, sizeof(char))) != sizeof(char)){
			perror("Error al escribir en el archivo");
			exit(EXIT_FAILURE);
		}
	
	/* Opción 2. Equivalente a la anterior.
	// Como el offset está más hallá del final del archivo, se añaden caracteres nulos hasta el offset, por lo que es quivalente

	lseek(fd, MMAPSIZE, SEEK_SET);
	if ((num=write(fd, &ch, sizeof(char))) != sizeof(char)){
		perror("Error al escribir en el archivo");
		exit(EXIT_FAILURE);
	}
	*/
	

	// Proyecta el archivo en memoria
	if ((memoria = (char *)mmap(0, MMAPSIZE, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0)) == MAP_FAILED){
		perror("Fallo la proyeccion");
		exit(EXIT_FAILURE);
	}

	close(fd);  /* ya no es necesario el descriptor*/


	strcpy(memoria, "hola mundo\n");  /* copia la cadena en la proyeccion */
	exit(EXIT_SUCCESS);
}
