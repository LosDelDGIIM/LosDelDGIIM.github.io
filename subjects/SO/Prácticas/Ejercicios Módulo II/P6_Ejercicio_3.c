#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    
    int fd = open("lockfile", O_RDWR | O_CREAT, 0666);
    struct flock lock;

    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0; // Bloquear todo el archivo

    if (fork() == 0) {
        // Primer proceso hijo
        if (fcntl(fd, F_SETLK, &lock) == -1) {
            perror("fcntl");
            exit(EXIT_FAILURE);
        }
        printf("Primer proceso hijo ha bloqueado el archivo\n");
        sleep(10); // Mantener el archivo bloqueado
        exit(EXIT_SUCCESS);
    }

    sleep(1); // Dar tiempo al primer proceso hijo para bloquear el archivo

    if (fork() == 0) {
        // Segundo proceso hijo
        if (fcntl(fd, F_SETLK, &lock) == -1) {
            printf("Segundo proceso hijo no puede bloquear el archivo, el kernel ha prevenido el interbloqueo\n");
            return EXIT_FAILURE;
        }
        printf("Segundo proceso hijo ha bloqueado el archivo\n");
        exit(EXIT_SUCCESS);
    }

    // Esperar a que los procesos hijos terminen
    wait(NULL);
    wait(NULL);

    return EXIT_SUCCESS;
}