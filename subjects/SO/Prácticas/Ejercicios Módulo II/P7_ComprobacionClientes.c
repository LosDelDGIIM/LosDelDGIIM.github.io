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
