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
        printf("Usage: %s <orden> \"|\" <orden>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (strcmp(argv[2], "|") != 0) {
        printf("Usage: %s <orden> \"|\" <orden>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int fd[2];
	pid_t PID;

	pipe(fd); // Llamada al sistema para crear un pipe

	if ( (PID= fork())<0) {
		perror("\nError en fork");
		exit(EXIT_FAILURE);
	}
	if (PID == 0) { // argv[1]. Proceso hijo porque PID == 0.
		//Cerrar el descriptor de lectura de cauce en el proceso hijo
		close(fd[0]);

		// dup2(fd[1],STDOUT_FILENO);
        if (close(STDOUT_FILENO) == -1) {
            perror("Error en close");
            exit(EXIT_FAILURE);
        }
        if (fcntl(fd[1], F_DUPFD, STDOUT_FILENO) == -1) {
            perror("Error en fcntl");
            exit(EXIT_FAILURE);
        }
        

        // Una vez regirigida, ya podemos ejecutar el comando
        if (execlp(argv[1],argv[1],NULL) < 0) {
            perror("Error en execlp");
            exit(EXIT_FAILURE);
        }
	}
	else { // argv[3]. Proceso padre porque PID != 0.

		//Cerrar el descriptor de escritura en cauce situado en el proceso padre
		close(fd[1]);

		//dup2(fd[0],STDIN_FILENO);

        if (close(STDIN_FILENO) == -1) {
            perror("Error en close");
            exit(EXIT_FAILURE);
        }
        if (fcntl(fd[0], F_DUPFD, STDIN_FILENO) == -1) {
            perror("Error en fcntl");
            exit(EXIT_FAILURE);
        }

        // Una vez regirigida, ya podemos ejecutar el comando
        if (execlp(argv[3],argv[3],NULL) < 0) {
            perror("Error en execlp");
            exit(EXIT_FAILURE);
        }
	}

	return EXIT_SUCCESS;
}