#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <signal.h>


// Estos archivo tendría que ser una ruta absoluta
// No obstante, para comodidad del usuario, y como es una simple prueba, se mantiene en esta carpeta dicho archivo
#define FIFO "./fifo_conocido"
#define ARCHIVO_BLOQUEO "./bloqueo"
#define PROG_PROXY "./P7_Proxy"


// Manejador de señal (SIGCHLD) para cuando un proxy termine
void handler_CHLD(int senal) {
    // Señal SIGCHLD recibida. Esperamos al hijo
    waitpid (-1, NULL, WNOHANG);
}


int main() {

    char fifo_entrada[50], fifo_salida[50];

    // Nombre de los FIFOs de entrada y salida
    sprintf(fifo_entrada, "%s_e", FIFO);
    sprintf(fifo_salida, "%s_s", FIFO);

    // Creación de los FIFO de entrada y de salida
    if (mkfifo(fifo_entrada, S_IRWXU) < 0) {
        perror("Error en mkfifo de entrada");
        exit(EXIT_FAILURE);
    }
    if (mkfifo(fifo_salida, S_IRWXU) < 0) {
        perror("Error en mkfifo de salida");
        exit(EXIT_FAILURE);
    }

    // Abrimos los FIFO de entrada y de salida
    int fd_fifo_entrada, fd_fifo_salida;

    // El FIFO de entrada se abre en modo lectura y escritura.
    // Podría pensarse en abrirse solo en modo lectura, pero cuando no haya ningñun ciente conectado,
    //      ese cauce no tendría ningún proceso conectado, por lo que se desbloquearía la lectura
    if ((fd_fifo_entrada = open(fifo_entrada, O_RDWR)) < 0) {
        perror("Error en open de entrada");
        exit(EXIT_FAILURE);
    }
    if ((fd_fifo_salida = open(fifo_salida, O_WRONLY)) < 0) {
        perror("Error en open de salida");
        exit(EXIT_FAILURE);
    }
    //printf("\nServidor: abiertos FIFOs de entrada y salida.\n");


    // Proceso servidor crea un archivo para bloquear (controlar que solo un proxy imprime a la vez)
    if (creat(ARCHIVO_BLOQUEO, S_IRWXU) < 0) {
        perror("Error en creat de archivo de bloqueo");
        exit(EXIT_FAILURE);
    }
    //printf("\nServidor: creado archivo de bloqueo.\n");

    // Señal SIGCHLD. Cuando un proxy termine, se recibirá esta señal, y queremos que se termine.
    if (signal(SIGCHLD, handler_CHLD) == SIG_ERR) {
        perror("Error en signal");
        exit(EXIT_FAILURE);
    }


    // Bucle infinito de lectura de pids de clientes
    pid_t pid_cliente;
    while (read(fd_fifo_entrada, &pid_cliente, sizeof(pid_t)) > 0) {
        printf("\nServidor: leido pid %d en fifo de entrada.\n", pid_cliente);

        // Creación de un proxy (proceso hijo) para atender al cliente
        pid_t retval;
        if ((retval = fork()) < 0) {
            perror("Error en fork");
            exit(EXIT_FAILURE);
        }

        // El proxy se encarga de atender al cliente
        if (retval == 0) {
            // El proxy se encarga de atender al cliente
            if ((execl(PROG_PROXY, PROG_PROXY, NULL))==-1){
                perror("Error en execl");
                exit(EXIT_FAILURE);
            }
        }

        // El servidor informa al cliente del pid del proxy que le atenderá
        if (write(fd_fifo_salida, &retval, sizeof(pid_t)) < 0) {
            perror("Error en write para informar del pid al proxy");
            exit(EXIT_FAILURE);
        }


    }   // Bucle infinito while que espera a que se conecten clientes


}