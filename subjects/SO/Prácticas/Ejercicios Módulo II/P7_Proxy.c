#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>



// Estos archivo tendría que ser una ruta absoluta
// No obstante, para comodidad del usuario, y como es una simple prueba, se mantiene en esta carpeta dicho archivo
#define FIFO_PROXY_BASE "./fifo_proxy"
#define ARCHIVO_BLOQUEO "./bloqueo"

#define BUFF_SIZE 1024


int main() {

    char fifo_proxy[50];
    sprintf(fifo_proxy, "%s.%d", FIFO_PROXY_BASE, getpid());

    // Creación del FIFO
    if (mkfifo(fifo_proxy, S_IRWXU) < 0) {
        perror("Error en mkfifo de proxy");
        exit(EXIT_FAILURE);
    }

    // Abrimos el FIFO en modo lectura
    int fd_fifo_proxy;
    if ((fd_fifo_proxy = open(fifo_proxy, O_RDONLY)) < 0) {
        perror("Error en open de proxy");
        exit(EXIT_FAILURE);
    }

    // El proxy leerá del FIFO correspondiente; por lo que redirigimos la entrada estándar
    //      a dicho FIFO
    if (dup2(fd_fifo_proxy, STDIN_FILENO) < 0) {
        perror("Error en dup2 de entrada");
        exit(EXIT_FAILURE);
    }

    // Creación del archivo temporal
    FILE *f_temp;
    if ((f_temp = tmpfile()) == NULL) {
        perror("Error en tmpfile");
        exit(EXIT_FAILURE);
    }

    // Leemos del FIFO y escribimos en el archivo temporal
    char buff[BUFF_SIZE];
    int bytes_leidos;
    while ((bytes_leidos = read(STDIN_FILENO, buff, BUFF_SIZE)) > 0) {
        if (fwrite(buff, sizeof(char), bytes_leidos, f_temp) < 0) {
            perror("Error en fwrite");
            exit(EXIT_FAILURE);
        }
    }

    // Bloqueamos el archivo de bloqueo; y luego leemos del temporal y escribimos en Pantalla
    int fd_bloqueo;
    if ((fd_bloqueo = open(ARCHIVO_BLOQUEO, O_WRONLY)) < 0) {
        perror("Error en open de bloqueo");
        exit(EXIT_FAILURE);
    }

    // Bloqueamos el archivo de bloqueo hasta que se quede libre
    struct flock lock;
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0; // Bloquear desde el principio
    lock.l_len = 0; // Bloquear todo el archivo

    if (fcntl(fd_bloqueo, F_SETLKW, &lock) < 0) {
        perror("Error en fcntl de bloqueo al bloquear");
        exit(EXIT_FAILURE);
    }

    // Leemos del archivo temporal y escribimos en pantalla
    fseek(f_temp, 0, SEEK_SET);
    while ((bytes_leidos = fread(buff, sizeof(char), BUFF_SIZE, f_temp)) > 0) {
        if (write(STDOUT_FILENO, buff, bytes_leidos) < 0) {
            perror("Error en write");
            exit(EXIT_FAILURE);
        }
    }

    // Desbloqueamos el archivo de bloqueo
    lock.l_type = F_UNLCK;
    if (fcntl(fd_bloqueo, F_SETLK, &lock) < 0) {
        perror("Error en fcntl de bloqueo al desbloquear");
        exit(EXIT_FAILURE);
    }

    // Cerramos el archivo temporal
    if (fclose(f_temp) < 0) {
        perror("Error en fclose");
        exit(EXIT_FAILURE);
    }

    // Cerramos el FIFO
    if (close(fd_fifo_proxy) < 0) {
        perror("Error en close de proxy");
        exit(EXIT_FAILURE);
    }

    // Eliminamos el FIFO
    if (unlink(fifo_proxy) < 0) {
        perror("Error en unlink de proxy");
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}