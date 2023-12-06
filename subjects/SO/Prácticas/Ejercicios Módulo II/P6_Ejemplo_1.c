#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main (int argc, char * argv[]) {

	struct flock cerrojo;
	int fd;

	// Iteramos sobre cada uno de los archivos pasados como argumento
	while (--argc > 0 ) {
		
		// Abrimos el archivo con permisos de lectura y escritura
		if ((fd=open(*++argv, O_RDWR)) == -1 ){
			perror("open fallo");
			continue;
		}
		
		cerrojo.l_type=F_WRLCK; /* cerrojo de escritura */
		cerrojo.l_whence=SEEK_SET;
		cerrojo.l_start=0;
		cerrojo.l_len=0;
		/* intentamos un bloqueo de escritura del archivo completo */

		// Este bucle itera hasta que se libere el cerrojo y, por tanto, se pueda bloquear el archivo
		while (fcntl (fd, F_SETLK, &cerrojo) == -1) {

			/* si el cerrojo falla, vemos quien lo bloquea */
			while (fcntl (fd, F_SETLK, &cerrojo) == -1 && cerrojo.l_type != F_UNLCK) {
				printf ("%s bloqueado por %d desde %lld hasta %lld para %c", *argv, cerrojo.l_pid, cerrojo.l_start, cerrojo.l_len, cerrojo.l_type==F_WRLCK ? 'w':'r');
				
				if (!cerrojo.l_len) break; // El cerrojo está bloqueando todo el archivo, por lo que no hay que iterar más

				cerrojo.l_start += cerrojo.l_len;
				cerrojo.l_len = 0;
			} /*mientras existan cerrojos de otros procesos */
			
		} /*mientras el bloqueo no tenga exito */

		/* ahora el bloqueo tiene exito y podemos procesar el archivo*/
		printf ("procesando el archivo\n");
		sleep (10); /* simulamos un trabajo de 10 segundos */
		printf ("fin del procesamiento\n");

		/* una vez finalizado el trabajo, desbloqueamos el archivo entero*/
		cerrojo.l_type=F_UNLCK;
		cerrojo.l_whence=SEEK_SET;
		cerrojo.l_start=0;
		cerrojo.l_len=0;
		if (fcntl (fd, F_SETLKW, &cerrojo) == -1){
			perror ("fcntl fallo");
			exit (EXIT_FAILURE);
		}
	}
	return EXIT_SUCCESS;
}
