#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>
#include<string.h>

int main (int argc, char *argv[]){

    if (argc != 4) {
        printf("Usage: %s <orden> \"<\"/\">\" <archivo>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (strcmp(argv[2], "<") != 0 && strcmp(argv[2], ">") != 0) {
        printf("Usage: %s <orden> \"<\"/\">\" <archivo>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int redirige_entrada = strcmp(argv[2], "<") == 0;

    // Si redirige la entrada, se abre para lectura.
    // Si redirige la salida, se abre para escritura y se permite crear y truncar.
    int flags = redirige_entrada ? O_RDONLY : O_WRONLY | O_CREAT | O_TRUNC;

    // Si redirige la salida y tiene que crearse, se crea con permisos 744.
    mode_t mode = redirige_entrada ? 0 : S_IRWXU | S_IRGRP | S_IROTH;

    int fd;
    if ((fd = open(argv[3], flags, mode)) == -1) {
        perror("Error al abrir el archivo");
        exit(EXIT_FAILURE);
    }

    // Si redirige la entrada, se redirige la entrada estándar al archivo.
    // Si redirige la salida, se redirige la salida estándar al archivo.
    int fd_dup = redirige_entrada ? STDIN_FILENO : STDOUT_FILENO;

    /*
    // Opción con DUP2
    if (dup2(fd, fd_dup) == -1) {
        perror("Error al redirigir la entrada/salida estándar");
        exit(EXIT_FAILURE);
    }
    */

    
    // Opción con fnctl
    if (close(fd_dup) == -1) {
        perror("Error al cerrar la entrada/salida estándar");
        exit(EXIT_FAILURE);
    }
    if (fcntl(fd, F_DUPFD, fd_dup) == -1) {
        perror("Error al redirigir la entrada/salida estándar");
        exit(EXIT_FAILURE);
    }
    
    
    // Se ejecuta el comando.
    if (execlp(argv[1], argv[1], NULL) == -1) {
        perror("Error al ejecutar el comando");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}