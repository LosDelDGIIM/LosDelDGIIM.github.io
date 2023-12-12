# Sistemas Operativos.  Módulo II. Práctica 07.

**Autor:** Arturo Olivares Martos
***

- **Asignatura:** Sistemas Operativos.
- **Curso Académico:** 2023-24.
- **Grado:** Doble Grado en Ingeniería Informática y Matemáticas.
- **Grupo:** Único.
- **Profesor:** Alejandro José León Salas
- **Descripción:** Sesión 7 del Módulo II de las prácticas de SO.
<!--- **Fecha:** 17 de abril de 2023. -->
<!-- - **Duración:** -->


Esta práctica consiste en hacer un único ejercicio, que consiste en construir un spool de impresión. El enunciado completo se encuentra en el guion de la práctica.

Tenemos que el código del servidor es el siguiente:
```c
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
```



El código del proxy es el siguiente:
```c
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
```

Por último, el código para comprobar el funcionamiento (creación de clientes) es el siguiente:
```c
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFF_SIZE 1024
#define longnombre 50

#define FIFO_PROXY_BASE "./fifo_proxy"

// Manejador de senal (SIGPIPE) para cuando se escribe en FIFO no abierto aun 
// para lectura, por defecto esta senal terminaria el proceso.
static void mimanejador(int senal){
	printf ("Cliente %d: escribo en el FIFO aun no abierto para lectura\n", getpid());
	exit (EXIT_FAILURE);
}


// Funcion que devuelve un descriptor al FIFO a utilizar para imprimir. 
int obtenerfifo (int fd_fifo_entrada, int fd_fifo_salida, pid_t mipid){

	int fd_fifo_proxy, resultado;
	pid_t pidproxy;
	char fifo_proxy[longnombre];

	// Escribe cualquier cosa en el FIFO conocido del servidor
	if ((resultado =write (fd_fifo_entrada,&mipid,sizeof(int)))==-1) {
		perror ("Cliente: error al escribir peticion en fifo conocido del servidor");
		exit(EXIT_FAILURE);
	}
	printf("\nCliente %d: escrito pid mio en fifo conocido del servidor.\n",mipid);

	// Obtiene el pid del proceso proxy con el que se va a comunicar
	if ((resultado = read (fd_fifo_salida,&pidproxy,sizeof(pid_t)))==-1) {
		perror ("Cliente: error al leer pid del proxy asignado por servidor");
		exit(EXIT_FAILURE);
	}
	printf("\nCliente %d: leido pid del proxy %d en fifo de servidor. \n",mipid,pidproxy);

	// Abre el FIFO a utilizar en la comunicacion
	sprintf(fifo_proxy,"%s.%d", FIFO_PROXY_BASE, pidproxy);
	sleep(1);
	if ((fd_fifo_proxy = open (fifo_proxy, O_WRONLY)) == -1) {
		perror ("Cliente: problema al abrir fifo proxy asignado");
		printf ("Cliente %d: nombre fifo proxy asignado es %s\n",mipid,fifo_proxy);
		exit(EXIT_FAILURE);
	}
	
	return (fd_fifo_proxy);
}


// Funcion que escribe en el FIFO a utilizar para imprimir.
void producir (char c, int fd_fifo_proxy, pid_t mipid) {

	char buffer[BUFF_SIZE];
	int contador=0, i=0, resultado;
	int numcar;

	// Genera un numero aleatorio entre 1 y 10000, va a ser el numero de caracteres a enviar.
	srand ((unsigned int) mipid);
	numcar = 1 + (int) (10000.0*rand()/(RAND_MAX+1.0));
	printf("\nCliente %d: Numero caracteres %c a generar es %d\n",mipid,c,numcar);

	// Pone el manejador para la senal SIGPIPE.
	if (signal(SIGPIPE, mimanejador)== SIG_ERR)
		perror ("Cliente: Error configurando senal");

	// Escritura de los datos.
	while (contador<numcar){	// Mientrs queden caracteres por escribir
		buffer[i] = c;			// Añádelo al buffer
		contador++;				// Incrementa el contador de caracteres
		i++;					// Incrementa el indice del buffer. Para que el buffer no se llene
		if ((i == BUFF_SIZE) || (contador == numcar)) {	// Si el buffer se ha llenado o no quedan caracteres por añadir, se escribe
			sleep((mipid+contador)%1);
			if ((resultado = write(fd_fifo_proxy, buffer, i)) == -1) {
				perror ("ERROR AL ESCRIBIR EN EL FIFO");
				exit(EXIT_FAILURE);
			}
			printf("\nCliente %d: He escrito en el fifo %d\n",mipid,resultado);
			i= 0;				// Se reinicia el indice del buffer
		}
	} // En el caso de que el queden caracteres, sigue iterando.

}

int main (int argc, char **argv) {  

	char c = 'a';
	int numcli, i, fd_fifo_entrada, fd_fifo_salida, fd_fifo_proxy;
	pid_t retval, mipid;
	char fifo_entrada[longnombre], fifo_salida[longnombre];

	setbuf(stdout, NULL);
	if (argc < 3) {
		printf ("Uso: clientes <nombre_fifo> <numero_clientes>\n");
		exit(EXIT_FAILURE);
	}else if ( ((numcli= atoi (argv[2])) > 10) || (numcli < 1) ){
		printf ("Clientes: <numero_clientes> comprendido entre 1 y 10\n");
		exit(EXIT_FAILURE);
	}

	// Compone los nombres de los FIFOs conocidos a partir del parametro,
	// uno de entrada y otro de salida (desde el punto de vista del servidor).
	sprintf(fifo_entrada,"%s_e",argv[1]);
	sprintf(fifo_salida,"%s_s",argv[1]);


	if ((fd_fifo_entrada = open (fifo_entrada, O_WRONLY)) == -1) {
		perror ("Clientes: Problema con el archivo fifo de entrada al servidor");
		exit(EXIT_FAILURE);
	}
	if ((fd_fifo_salida = open (fifo_salida, O_RDWR)) == -1) {
		perror ("Clientes: Problema con el archivo fifo de salida del servidor");
		exit(EXIT_FAILURE);
	}

	// Crea procesos clientes, con un caracter distinto a imprimir cada uno.
	for (i=1; i<numcli; i++) {
		if ((retval = fork()) == -1) {
			perror ("Clientes: Problema al crear proceso cliente");
			exit(EXIT_FAILURE);
		}
		if (retval == 0 ) {
			mipid = getpid();
			fd_fifo_proxy = obtenerfifo(fd_fifo_entrada, fd_fifo_salida, mipid);
			producir(c, fd_fifo_proxy, mipid);
			exit(EXIT_SUCCESS);
		}else
			c++;
	}

	// El propio programa se convierte en un cliente.
	mipid = getpid ();
	fd_fifo_proxy = obtenerfifo(fd_fifo_entrada, fd_fifo_salida, mipid);
	producir(c, fd_fifo_proxy, mipid);

	// El proceso original elimina zombies ya que es el padre.
	while (wait(NULL)!=-1);

	exit(EXIT_SUCCESS);
}
```