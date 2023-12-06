#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>

// Este archivo para comprobar la unicidad tendría que ser una ruta absoluta,
//          para que no se pueda ejecutar desde distintas carpetas.
// No obstante, para comodidad del usuario, y como es una simple prueba, se mantiene en esta carpeta dicho archivo
#define arch_unicidad "./P6_Ej4_Unicidad.pid"

int main() {

    struct flock cerrojo;
    cerrojo.l_type = F_WRLCK;
    cerrojo.l_whence = SEEK_SET;
    cerrojo.l_start = 0;
    cerrojo.l_len = 0;
    // Vamos a intentar un cerrojo de escritura para todo el archivo

    int fd; // Abrimos el archivo
    if ((fd = open(arch_unicidad, O_WRONLY | O_CREAT, S_IRGRP|S_IROTH|S_IRWXU)) < 0){
        perror("Error en open");
        exit(EXIT_FAILURE);
    }

    // Intentamos el cerrojo
    if (fcntl(fd, F_SETLK, &cerrojo) == -1) {
        perror("Error en fcntl");
        exit(EXIT_FAILURE);
    }

    // Si llegamos aquí, es que el cerrojo se ha establecido correctamente
    // Ahora vamos a escribir el PID del proceso en el archivo
    pid_t pid = getpid();
    char pid_str[10];
    sprintf(pid_str, "%d", pid);
    if (write(fd, &pid_str, strlen(pid_str)*sizeof(char)) < 0) {
        perror("Error en write");
        exit(EXIT_FAILURE);
    }

    sleep(15); // Esperamos 30 segundos para que el usuario pueda comprobar que no se puede ejecutar el programa dos veces

    // Ahora vamos a liberar el cerrojo
    cerrojo.l_type = F_UNLCK;
    if (fcntl(fd, F_SETLK, &cerrojo) < 0) {
        perror("Error en fcntl");
        exit(EXIT_FAILURE);
    }

    close(fd); // Cerramos el archivo

    return EXIT_SUCCESS;
}