#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include <stdlib.h>

#define FIRST_SIGNAL 1 //Señales iniciales y finales. Visible en man 7 signal
#define LAST_SIGNAL 31 
#define NUM_SIGNALS (LAST_SIGNAL - FIRST_SIGNAL) //Número de señales
int contadores[NUM_SIGNALS]; //Array de contadores de señales

void handler(int sig){

    // Incrementamos el contador de la señal recibida
    contadores[sig - FIRST_SIGNAL]++;

    // Imprimimos el número de señal recibida y el número de veces que se ha recibido
    printf("Señal %d recibida %d veces\n", sig, contadores[sig - FIRST_SIGNAL]);
}

int main(int argc, char *argv[]){

    if(argc != 1){
        printf("Error en el número de argumentos\n");
        printf("Uso: ./P5_Ejercicio_2\n");
        exit(EXIT_FAILURE);
    }

    // Iniciamos contadores a 0, ya que incialmente no se ha llamado a ninguna señal
    for(int i = FIRST_SIGNAL; i <= LAST_SIGNAL; i++)
        contadores[i] = 0;

    // Definimos la estructura sigaction
    struct sigaction sa;
    sa.sa_handler = handler;
    sa.sa_flags = 0; //Reinicio de llamadas interrumpidas por señales
    sigemptyset(&sa.sa_mask); //Inicializamos la máscara de señales a vacío


    // Recorremos todas las señales
    for(int i = FIRST_SIGNAL; i <= LAST_SIGNAL; i++){

        // Ignoramos la señal SIGKILL y SIGSTOP, ya que estas no se pueden capturar
        if(i == SIGKILL)
            printf("No se puede manejar la señal SIGKILL (%i)\n", i);
        else if(i == SIGSTOP)
            printf("No se puede manejar la señal SIGSTOP (%i)\n", i);

        // Para el resto de señales, llamamos a sigaction, cambiando su handler
        else if (sigaction(i, &sa, NULL) < 0) {
            perror("Error en sigaction");
            exit(EXIT_FAILURE);
        }
    }

    printf("Esperando el envio de señales...\n");

    while(1); //Bucle infinito a la espera de señales
}