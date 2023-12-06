#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include <stdlib.h>

#define SENAL_ESPERADA SIGUSR1 // El proceso se bloque hasta que reciba dicha señal

int main(int argc, char *argv[]){

    if(argc != 1){
        printf("Error en el número de argumentos\n");
        printf("Uso: ./P5_Ejercicio_3\n");
        exit(EXIT_FAILURE);
    }


    sigset_t new_mask;

    sigfillset(&new_mask); // Inicializamos la máscara de señales lleno
    sigdelset(&new_mask, SENAL_ESPERADA); // Eliminamos la señal a la máscara
    
    sigsuspend(&new_mask); // El proceso se bloquea hasta que reciba la señal

    printf("Señal recibida\n");
    
    exit(EXIT_SUCCESS);
}