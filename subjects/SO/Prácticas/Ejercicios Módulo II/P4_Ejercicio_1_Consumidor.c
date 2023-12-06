//consumidorFIFO.c
//Consumidor que usa mecanismo de comunicacion FIFO.

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#define _XOPEN_SOURCE 500


#define ARCHIVO_FIFO "ComunicacionFIFO"

int main(void){
    int fd;
    char buffer[80];// Almacenamiento del mensaje del cliente.

    //Crear el cauce con nombre (FIFO) si no existe
    umask(0);
    mknod(ARCHIVO_FIFO,S_IFIFO|0666,0);
    //también vale: mkfifo(ARCHIVO_FIFO,0666);

    //Abrir el cauce para lectura-escritura
    if ( (fd=open(ARCHIVO_FIFO,O_RDWR)) <0) {
        perror("Error en open");
        exit(EXIT_FAILURE);
    }

    //Aceptar datos a consumir hasta que se envíe la cadena fin
    while(1) {
        read(fd,buffer,80);
        if(strcmp(buffer,"fin")==0) {
            close(fd);
            return EXIT_SUCCESS;
        }
        printf("\nMensaje recibido: %s\n", buffer);
    }

    return EXIT_SUCCESS;
}
