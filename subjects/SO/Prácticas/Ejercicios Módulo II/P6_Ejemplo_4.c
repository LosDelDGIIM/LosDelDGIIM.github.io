#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <wait.h>

#define MMAPSIZE 1

int main (int argc, char *argv[]){
    off_t len;
    char bufer='a';
    char *cnt;
    int fd, num;

	umask(0);
    if ((fd = open("Archivo", O_RDWR|O_CREAT|O_TRUNC, S_IRWXU)) < 0) {
		perror("Error al abrir el archivo");
		exit(EXIT_FAILURE);
	}
    if ((num=write(fd, &bufer, sizeof(char)))!= sizeof(char)){
		perror("Error al escribir en el archivo");
		exit(EXIT_FAILURE);
	}
	

	// Proyecta el archivo en memoria
    if ((cnt = (char *) mmap (0, MMAPSIZE, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0)) == MAP_FAILED) {
		printf("Fallo el mapeo\n");
		return EXIT_FAILURE;
	}
    if (close (fd) == -1) {
		printf("Error al cerrar el archivo\n");
		return EXIT_FAILURE;
	}

	if (fork() == 0) { /* hijo */
		sleep(2);	// Esperamos 2 segundos para que el padre escriba en el archivo
		printf("El valor de cnt es: %s\n", cnt);
		exit(EXIT_SUCCESS);
	}

	/* padre */
	strcpy(cnt, "b");
	
	wait(NULL);
	exit(EXIT_SUCCESS);
}
					  
