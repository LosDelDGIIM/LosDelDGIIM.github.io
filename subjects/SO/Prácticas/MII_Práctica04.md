# Sistemas Operativos.  Módulo II. Práctica 04.

**Autor:** Arturo Olivares Martos
***

- **Asignatura:** Sistemas Operativos.
- **Curso Académico:** 2023-24.
- **Grado:** Doble Grado en Ingeniería Informática y Matemáticas.
- **Grupo:** Único.
- **Profesor:** Alejandro José León Salas
- **Descripción:** Sesión 4 del Módulo II de las prácticas de SO.
<!--- **Fecha:** 17 de abril de 2023. -->
<!-- - **Duración:** -->


## Ejercicio 1.

Consulte en el manual las llamadas al sistema para la creación de archivos especiales en general (`mknod`) y la específica para archivos FIFO (`mkfifo`). Pruebe a ejecutar el siguiente código correspondiente a dos programas que modelan el problema del productor/consumidor, los cuales utilizan como mecanismo de comunicación un cauce FIFO. Determine en qué orden y manera se han de ejecutar los dos programas para su correcto funcionamiento y cómo queda reflejado en el sistema que estamos utilizando un cauce FIFO. Justifique la respuesta.


Este es el código del consumidor:

```c
//consumidorFIFO.c
//Consumidor que usa mecanismo de comunicacion FIFO.

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#define _XOPEN_SOURCE 500


#define ARCHIVO_FIFO "ComunicacionFIFO"

int main(void){
    int fd;
    char buffer[80];// Almacenamiento del mensaje del cliente.

    //Crear el cauce con nombre (FIFO) si no existe
    umask(0);
    mknod(ARCHIVO_FIFO,S_IFIFO|0666,0);
    //también vale: mkfifo(ARCHIVO_FIFO,0666);

    //Abrir el cauce para lectura-escritura
    if ( (fd=open(ARCHIVO_FIFO,O_RDWR)) <0) {
        perror("Error en open");
        exit(EXIT_FAILURE);
    }

    //Aceptar datos a consumir hasta que se envíe la cadena fin
    while(1) {
        read(fd,buffer,80);
        if(strcmp(buffer,"fin")==0) {
            close(fd);
            return EXIT_SUCCESS;
        }
        printf("\nMensaje recibido: %s\n", buffer);
    }

    return EXIT_SUCCESS;
}
```


Este es el código del productor:
```c
//productorFIFO.c
//Productor que usa mecanismo de comunicacion FIFO

#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#define _XOPEN_SOURCE 500

#define ARCHIVO_FIFO "ComunicacionFIFO"

int main(int argc, char *argv[])
{
    int fd;

    //Comprobar el uso correcto del programa
    if(argc != 2) {
        printf("\nproductorFIFO: faltan argumentos (mensaje)");
        printf("\nPruebe: productorFIFO <mensaje>, donde <mensaje> es una cadena de caracteres.\n");
        exit(EXIT_FAILURE);
    }

    //Intentar abrir para escritura el cauce FIFO
    if( (fd=open(ARCHIVO_FIFO,O_WRONLY)) <0) {
        perror("\nError en open");
        exit(EXIT_FAILURE);
    }

    //Escribir en el cauce FIFO el mensaje introducido como argumento
    if( (write(fd,argv[1],strlen(argv[1])+1)) != strlen(argv[1])+1) {
        perror("\nError al escribir en el FIFO");
        exit(EXIT_FAILURE);
    }

    close(fd);
    return EXIT_SUCCESS;
}
```

En primer lugar, lo lógico sería pensar que es necesario ejecutar el consumidor antes que el productor, ya que si se ejecutase en primer lugar el productor, no habría nadie que consumiese los datos que este produce. Sin embargo, esto no es así, ya que la orden `open` del productor se queda bloqueada hasta que el cauce tenga un consumidor para no perder los datos. Por tanto, el orden de ejecución no importa.
Tan solo es necesario que, la primera vez, se ejecute primero el consumidor; ya que el cauce ha de estar creado para que el productor no de error.

Para probar el funcionamiento, se han de ejecutar ambos programas un dos terminales distintas. Se verá que el consumidor no termina hasta que el productor envíe el mensaje `fin`; y hasta entonces cada vez que recibe un mensaje lo imprime. Esto es así porque el consumidor se queda bloqueado en la orden `read` hasta que el productor envíe algo. El productor, no obstante, terminará su ejecución cada vez que haya enviado el mensaje.


## Ejercicio 2.

Consulte en el manual en línea la llamada al sistema `pipe` para la creación de cauces sin nombre. Pruebe a ejecutar el siguiente programa que utiliza un cauce sin nombre y describa la función que realiza. Justifique la respuesta.
```c
/*
Trabajo con llamadas al sistema del Subsistema de Procesos y Cauces conforme a POSIX 2.10
*/

#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>

int main(int argc, char *argv[]){
	int fd[2], numBytes;
	pid_t PID;
	char mensaje[]= "\nEl primer mensaje transmitido por un cauce!!\n";
	char buffer[80];

	pipe(fd); // Llamada al sistema para crear un cauce sin nombre

	if ( (PID= fork())<0) {
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (PID == 0) {
		//Cierre del descriptor de lectura en el proceso hijo
		close(fd[0]);
		// Enviar el mensaje a traves del cauce usando el descriptor de escritura
		write(fd[1],mensaje,strlen(mensaje)+1);
		exit(EXIT_SUCCESS);
	}
	else { // Estoy en el proceso padre porque PID != 0
		//Cerrar el descriptor de escritura en el proceso padre
		close(fd[1]);
		//Leer datos desde el cauce.
		numBytes= read(fd[0],buffer,sizeof(buffer));
		printf("\nEl numero de bytes recibidos es: %d",numBytes);
		printf("\nLa cadena enviada a traves del cauce es: %s", buffer);
	}

	return EXIT_SUCCESS;
}
```

Este programa crea un cauce sin nombre y crea un proceso hijo. El proceso padre cierra el descriptor de escritura y el hijo el de lectura, por lo que es el hijo el que va a transmitirle información al padre.

El hijo escribe en el cauce el mensaje guardado en la variable `mensaje`, y el padre lo lee y lo imprime por pantalla.


## Ejercicio 3.

Redirigiendo las entradas y salidas estándares de los procesos a los cauces podemos escribir un programa en lenguaje C que permita comunicar órdenes existentes sin necesidad de reprogramarlas, tal como hace el shell (por ejemplo `ls | sort`). En particular, ejecute el siguiente programa que ilustra la comunicación entre proceso padre e hijo a través de un cauce sin nombre redirigiendo la entrada estándar y la salida estándar del padre y el hijo respectivamente.
```c
/*
Programa ilustrativo del uso de pipes y la redirección de entrada y
salida estándar: "ls | sort"
*/

#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>

int main(int argc, char *argv[]) {
	int fd[2];
	pid_t PID;

	pipe(fd); // Llamada al sistema para crear un pipe

	if ( (PID= fork())<0) {
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if(PID == 0) { // ls
		//Establecer la direccion del flujo de datos en el cauce cerrando
		// el descriptor de lectura de cauce en el proceso hijo
		close(fd[0]);

		//Redirigir la salida estandar para enviar datos al cauce
		//--------------------------------------------------------
		//Cerrar la salida estandar del proceso hijo
		close(STDOUT_FILENO);

		//Duplicar el descriptor de escritura en cauce en el descriptor
		//correspondiente a la salida estandar (stdout)
		dup(fd[1]);
		execlp("ls","ls",NULL);
	}
	else { // sort. Estoy en el proceso padre porque PID != 0

		//Establecer la dirección del flujo de datos en el cauce cerrando
		// el descriptor de escritura en el cauce del proceso padre.
		close(fd[1]);

		//Redirigir la entrada estándar para tomar los datos del cauce.
		//Cerrar la entrada estándar del proceso padre
		close	(STDIN_FILENO);

		//Duplicar el descriptor de lectura de cauce en el descriptor
		//correspondiente a la entrada estándar (stdin)
		dup(fd[0]);
		execlp("sort","sort",NULL);
	}

	return EXIT_SUCCESS;
}
```

Este programa crea un cauce sin nombre y crea un proceso hijo. El proceso padre cierra el descriptor de escritura y el hijo el de lectura, por lo que es el hijo el que va a transmitirle información al padre.

El hijo vemos que cierra el _file descriptor_ de escritura de la salida estándar, y luego copia el _file descriptor_ de escritura del cauce en el primer _file descriptor_ que haya libre en la tabla de descriptores de archivo.

Esto de forma efectiva hace que la salida estándar del hijo sea el cauce; ya que la salida estándar es el _file descriptor_ 1, por lo que como se ha cerrado justo antes y es un entero muy bajo, es ahí donde se va a asignar `fd[1]`. No obstante, esto no se asegura plenamente, ya que se podría dar que el _file descriptor_ 1 no contuviese la salida estándar o que el _file descriptor_ 0 estuviese libre y se copiase entonces ahí. Estos problemas se solucionarán con la orden `dup2`, como veremos en la siguiente actividad.

Por tanto, tenemos que el hijo ejecuta el comando `ls` y envía su salida el cauce. El padre hace lo análogo con la entrada estándar, por lo que recibe la salida del comando `ls` y la envía al comando `sort`, obteniendo entonces el resultado de `ls | sort`.


## Ejercicio 4.
Compare el siguiente programa con el anterior y ejecútelo. Describa la principal diferencia, si existe, tanto en su código como en el resultado de la ejecución.
```c
/*
tarea8.c
Programa ilustrativo del uso de pipes y la redirección de entrada y
salida estándar: "ls | sort", utilizando la llamada dup2.
*/

#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>

int main(int argc, char *argv[]){
	int fd[2];
	pid_t PID;

	pipe(fd); // Llamada al sistema para crear un pipe

	if ( (PID= fork())<0) {
		perror("\nError en fork");
		exit(EXIT_FAILURE);
	}
	if (PID == 0) { // ls
		//Cerrar el descriptor de lectura de cauce en el proceso hijo
		close(fd[0]);

		//Duplicar el descriptor de escritura en cauce en el descriptor
		//correspondiente a la salida estandr (stdout), cerrado previamente en
		//la misma operacion
		dup2(fd[1],STDOUT_FILENO);
		execlp("ls","ls",NULL);
	}
	else { // sort. Proceso padre porque PID != 0.
		//Cerrar el descriptor de escritura en cauce situado en el proceso padre
		close(fd[1]);

		//Duplicar el descriptor de lectura de cauce en el descriptor
		//correspondiente a la entrada estándar (stdin), cerrado previamente en
		//la misma operación
		dup2(fd[0],STDIN_FILENO);
		execlp("sort","sort",NULL);
	}

	return EXIT_SUCCESS;
}
```

La principal diferencia es que en este caso se utiliza la orden `dup2` para asegurar que el _file descriptor_ 1 es el de la salida estándar y el _file descriptor_ 0 el de la entrada estándar.

Esto se debe a que, cuando llamamos a `dup2(fd[1],STDOUT_FILENO);`, lo que estamos haciendo es copiar el _file descriptor_ `fd[1]` en el _file descriptor_ `STDOUT_FILENO`, que es el de la salida estándar. Además, en el caso de que  `STDOUT_FILENO` estuvise ocupado (que normalmente lo estará con `stdin`), lo cierra antes de copiarlo. Por tanto, así nos aseguramos que no se va a copiar en el primer _file descriptor_ disponible, sino en el de la salida estándar.

## Ejercicio 5.
Este ejercicio se basa en la idea de utilizar varios procesos para realizar partes de una computación en paralelo. Para ello, deberá construir un programa que siga el esquema de computación maestro-esclavo, en el cual existen varios procesos trabajadores (esclavos) idénticos y un único proceso que reparte trabajo y reúne resultados (maestro). Cada esclavo es capaz de realizar una computación que le asigne el maestro y enviar a este último los resultados para que sean mostrados en pantalla por el maestro.

El ejercicio concreto a programar consistirá en el cálculo de los números primos que hay en un intervalo. Será necesario construir dos programas, **maestro** y **esclavo**. Ten en cuenta la siguiente especificación:

1. El intervalo de números naturales donde calcular los número primos se pasará como argumento al programa **maestro**. El maestro creará dos procesos esclavos y dividirá el intervalo en dos subintervalos de igual tamaño pasando cada subintervalo como argumento a cada programa **esclavo**.
 
    Por ejemplo, si al maestro le proporcionamos el intervalo entre 1000 y 2000, entonces un esclavo debe calcular y devolver los números primos comprendidos en el subintervalo entre 1000 y 1500, y el otro esclavo entre 1501 y 2000. El maestro creará dos cauces sin nombre y se encargará de su redirección para comunicarse con los procesos esclavos. El maestro irá recibiendo y mostrando en pantalla (también uno a uno) los números primos calculados por los esclavos en orden creciente.

2. El programa **esclavo** tiene como argumentos el extremo inferior y superior del intervalo sobre el que buscará números primos. Para identificar un número primo utiliza el siguiente método concreto: un número `n` es primo si no es divisible por ningún `k` tal que `2 < k <= sqrt(n)`, donde sqrt corresponde a la función de cálculo de la raíz cuadrada (consulte dicha función en el manual). El esclavo envía al maestro cada primo encontrado como un dato entero (4 bytes) que escribe en la salida estándar, la cuál se tiene que encontrar redireccionada a un cauce sin nombre. Los dos cauces sin nombre necesarios, cada uno para comunicar cada esclavo con el maestro, los creará el maestro inicialmente. Una vez que un esclavo haya calculado y enviado (uno a uno) al maestro todos los primos en su correspondiente intervalo terminará.

Veamos en primer lugar el código del esclavo, que es de menor complejidad. Importante destacar que el esclavo no tiene que crear ningún cauce, ya que estos ya han sido creados por el maestro. El esclavo imprime por la salida estándar, y ya se encarga el maestro de redirigirlo al cauce.

Destaquemos también que es necesario compilar con `-lm` para que el compilador incluya la librería matemática.
```c
// P4_Ejercicio_5_Esclavo.c

#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<math.h>

int esPrimo(int n){

	if (n <= 1) return 0;
	if (n == 2) return 1;

	// Casos base que aumentan en gran medida la eficiencia del algoritmo
	if (n % 2 == 0) return 0;

	// Para el resto, aplico dicha fórmula. Me salto los pares, porque ya he visto que no es par
	for (int i=3; i<=sqrt(n); i+=2)
		if (n % i == 0) return  0;
	
	return 1;

}

int main(int argc, char *argv[]){
	
	if (argc != 3) {
		printf("Usage: %s <extremo_inf> <extremo_sup> \n", argv[0]);
		exit(EXIT_FAILURE);
	}

	int inf = atoi(argv[1]);
	int sup = atoi(argv[2]);

	for (int i=inf; i<=sup; i++)
		if (esPrimo(i)) printf("%d\n", i);


	return EXIT_SUCCESS;
}
```


Veamos ahora el código del maestro:
```c
// P4_Ejercicio_5_Maestro.c

#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<sys/wait.h>

#define NUM_PROC 2
#define BUF_SIZE 100

int main(int argc, char *argv[]){


	if (argc != 3) {
		printf("Usage: %s <extremo_inf> <extremo_sup> \n", argv[0]);
		exit(EXIT_FAILURE);
	}

	// Comprobación del intervalo
	int inf = atoi(argv[1]);
	int sup = atoi(argv[2]);
	if (inf > sup) {
		printf("Usage: %s <extremo_inf> <extremo_sup> \n", argv[0]);
		exit(EXIT_FAILURE);
	}



	// Conversión de los enteros a cadenas de caracteres
	char intervalos[NUM_PROC*2][10]; // Un intervalo por cada proceso

    sprintf(intervalos[0], "%d", inf);
	sprintf(intervalos[NUM_PROC*2-1], "%d", sup);

	// Calculo de los intervalos. Obtenemos los puntos medios
	for (int i=1; i<NUM_PROC; i++){
		int medio_i = inf + (sup-inf)/NUM_PROC*i;
		sprintf(intervalos[2*i-1], 	"%d", medio_i);
		sprintf(intervalos[2*i], 	"%d", medio_i+1);
	}



	// Creación de los cauces para los procesos hijos
	int fd[NUM_PROC][2];	 // Cada proceso tiene un cauce, y cada cauce son 2 file descriptors.

	// Creación de los procesos hijos
	for (int i=0; i<NUM_PROC; i++){

		pid_t retval;
		
		if ( pipe(fd[i]) < 0 ) { // Llamada al sistema para crear un pipe
			perror("\nError en pipe");
			exit(EXIT_FAILURE);
		}

		if ( (retval=fork()) <0) {
			perror("\nError en fork");
			exit(EXIT_FAILURE);
		}

		if (retval == 0) { // Estamos en el hijo

			//Cerrar el descriptor de lectura de cauce en el proceso hijo
			close(fd[i][0]);

			// El proceso hijo escribe en el cauce el resultado de la ejecución del programa esclavo
			// Como el proceso hijo escribe con printf, asociamos la salida estándar al cauce
			dup2(fd[i][1],STDOUT_FILENO);

			// Llamada al programa esclavo con el intervalo correspondiente
			if (execl("./P4_Ej5_E","./P4_Ej5_E",intervalos[2*i],intervalos[2*i+1],NULL) < 0){
				perror("\nError en execl");
				exit(EXIT_FAILURE);
			}
		}

		else { // Proceso padre porque PID != 0.
			
			//Cerrar el descriptor de escritura en cauce situado en el proceso padre
			close(fd[i][1]);
		}

	} // for (int i=0; i<NUM_PROC; i++)
	

	// Código del proceso padre
	int n_leidos;
	char buffer[BUF_SIZE];

	// El proceso padre lee de los cauces y escribe en pantalla
	for (int i=0; i<NUM_PROC; i++)
		while ( (n_leidos = read(fd[i][0], &buffer, sizeof(buffer))) > 0 )
			write(STDOUT_FILENO, &buffer, n_leidos);
	

	// Espera del padre a los hijos
	for (int i=0; i<NUM_PROC; i++)
		wait(NULL);

	return EXIT_SUCCESS;
}
```

Notemos que se usan dos constantes que procesará el preprocesador, `BUF_SIZE` y `NUM_PROC`. La primera es el tamaño del buffer que se usará para leer de los cauces, y la segunda es el número de procesos esclavos que se van a crear. Para nuestro caso, se crearán dos procesos esclavos, pero el programa está pensado para poder crear más.

En primer lugar, se comprueba que se han pasado los argumentos correctos. Posteriormente, se calculan los intervalos que se le van a pasar a cada proceso hijo, teniendo en cuenta que se han de guardar como cadenas de caracteres, ya que serán los parámetros de un programa.

Posteriormente, para cada proceso hijo se crea un cauce `fd[i]`. En cada hijo, se asocia el descriptor de escritura con la salida estándar, y se ejecuta el programa esclavo con los parámetros correspondientes. 

En el padre, tan solo cerramos el descriptor de escritura de cada cauce, y leemos de cada cauce y escribimos en la salida estándar. Esto se hace en un bucle `while` para asegurarnos de que se leen todos los datos que se han escrito en el cauce.

Por último, se espera a que terminen los procesos hijos.
