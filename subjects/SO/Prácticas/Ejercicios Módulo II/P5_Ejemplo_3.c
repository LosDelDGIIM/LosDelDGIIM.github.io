#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include <stdlib.h>

int main(){
    sigset_t new_mask;

    /* inicializar la nueva mascara de se�ales */
    sigemptyset(&new_mask);

    sigaddset(&new_mask, SIGUSR1);

    /*esperar a cualquier señal excepto SIGUSR1 */
    sigsuspend(&new_mask);

    printf("Señal recibida\n");
    exit(EXIT_SUCCESS);
}