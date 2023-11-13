# Sistemas Operativos.  Módulo II. Práctica 01.

**Autor:** Arturo Olivares Martos
***

- **Asignatura:** Sistemas Operativos.
- **Curso Académico:** 2023-24.
- **Grado:** Doble Grado en Ingeniería Informática y Matemáticas.
- **Grupo:** Único.
- **Profesor:** Alejandro José León Salas
- **Descripción:** Sesión 1 del Módulo II de las prácticas de SO.
<!--- **Fecha:** 17 de abril de 2023. -->
<!-- - **Duración:** -->


## Ejercicio 1.
¿Qué hace el siguiente programa?
```c
/*
P1_Ejercicio_1.c
Trabajo con llamadas al sistema del Sistema de Archivos ''POSIX 2.10 compliant''
Probar tras la ejecución del programa: $>cat archivo y $> od -c archivo
*/
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>  	/* Primitive system data types for abstraction\
			                of implementation-dependent data types.
			                POSIX Standard: 2.6 Primitive System Data Types
                            <sys/types.h>
                        */
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>

char buf1[]="abcdefghij";
char buf2[]="ABCDEFGHIJ";

int main(int argc, char *argv[]){
	int fd;

	if( (fd=open("archivo",O_CREAT|O_TRUNC|O_WRONLY,S_IRUSR|S_IWUSR))<0) {
		printf("\nError %d en open",errno);
		perror("\nError en open");
		exit(EXIT_FAILURE);
	}
	if(write(fd,buf1,10) != 10) {
		perror("\nError en primer write");
		exit(EXIT_FAILURE);
	}

	if(lseek(fd,40,SEEK_SET) < 0) {
		perror("\nError en lseek");
		exit(EXIT_FAILURE);
	}

	if(write(fd,buf2,10) != 10) {
		perror("\nError en segundo write");
		exit(EXIT_FAILURE);
	}

	close(fd);
	return EXIT_SUCCESS;
}
```
Probad tras la ejecución del programa las siguientes órdnes del shell: `$> cat archivo` y `$> od -c archivo`.


Este programa abre un archivo con permisos de escritura llamado `archivo`. Si existe, lo sobreescribe, y si no existe, lo crea. El modo con el que se crea el archivo en tal caso es `600`, aunque posteriormente se le aplicará la máscara.

Posteriormente, escribe en el archivo 10 bytes procedentes del buffer `buf1`. Como este es un array de `char`, y cada char ocupa 1 byte, tenemos que escriben 10 carácteres; es decir, el array entero.

Posteriormente, se va al byte 40 del fichero `archivo`, ya que se cuenta desde el inicio por tener como parámetro `SEEK_SET`. Como aún no se ha escrito, el tamaño del archivo no aumenta.

En este punto, se escribe el segundo buffer `buf2`. Como no se ha escrito desde el byte con offset 10 hasta el que tiene offset 40, al leer esos bytes, se leerán `\0`. 

Por último, cierra el file descriptor.

Veamos lo que ocurre al ejecutar las instrucciones pedidas:
```console
$ gcc tarea1.c -o tarea1
$ ./tarea1 
$ cat archivo 
abcdefghijABCDEFGHIJ$ od -c archivo 
0000000   a   b   c   d   e   f   g   h   i   j  \0  \0  \0  \0  \0  \0
0000020  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0
0000040  \0  \0  \0  \0  \0  \0  \0  \0   A   B   C   D   E   F   G   H
0000060   I   J
0000062
$
```

Notemos que, al ejecutar `cat`, imprime solo los bytes con información. Además, es importante notar que no incluye un salto de línea.

Al ejecutar `od -c`, mientra el archivo byte a byte, y gracias a la opción `-c`, no solo selecciona los caracteres, sino también el valor `\0`.




## Ejercicio 2.

Implementa un programa que realice la siguiente funcionalidad. El programa acepta como argumento el nombre de un archivo (_pathname_), lo abre y lo lee en bloques de tamaño 80 Bytes, y crea un nuevo archivo de salida, `salida.txt`, en el que debe aparecer la siguiente información:
```txt
Bloque 1
// Aquí van los primeros 80 Bytes del archivo pasado como argumento.
Bloque 2
// Aquí van los siguientes 80 Bytes del archivo pasado como argumento.
...
Bloque n
// Aquí van los siguientes 80 Bytes del archivo pasado como argumento.
```



El programa sería el siguiente:
```c
/*
P1_Ejercicio_2.c
*/
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>  	/* Primitive system data types for abstraction\
			                of implementation-dependent data types.
			                POSIX Standard: 2.6 Primitive System Data Types
                            <sys/types.h>
                        */
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>
#include<string.h>

int main(int argc, char *argv[]){

	int fd_in, fd_out;	

	if (argc != 2 && argc != 1){
		printf("Uso: <P1_Ejercicio_2> <pathname>\n");
		exit(EXIT_FAILURE);
	}	

	// Fichero de entrada. Solo leer
	if (argc == 2){ // Se ha proporcionado un archivo
		const char* path_in = argv[1];
		if( (fd_in=open(path_in,O_RDONLY))<0) {
			printf("\nError %d en open (In)",errno);
			perror("\nError en open");
			exit(EXIT_FAILURE);
		}
	}else{ // No se ha proporcionado archivo. Se lee de la entrada estándar
		fd_in = STDIN_FILENO;
	}

	// Fichero de salida. Si existe lo sobreescribe, y si no existe lo crea.
	const char* path_out = "./salida.txt";
	if( (fd_out=open(path_out,O_CREAT|O_TRUNC|O_WRONLY, S_IRUSR|S_IWUSR))<0) {
		printf("\nError %d en open (Out)",errno);
		perror("\nError en open");
		exit(EXIT_FAILURE);
	}

	int n_bloque = 0;
	const int TAM_BLOQUE = 80;
	char buff[TAM_BLOQUE];	// Buffer en el que se almacena lo leído

	// Lee paquetes de 80B y los escribe por bloques.
	int n_leidos;
	while (n_leidos = read(fd_in, buff, TAM_BLOQUE)){

		char cabecera[50];
		sprintf(cabecera, "\nBloque %d\n", ++n_bloque);

		// Se escribe en primer lugar el número del bloque
		write(fd_out, cabecera, strlen(cabecera));

		// Se escriben los bits leídos. Es importante notar que no se escriben 80, sino solo los que se ha leído.
		write(fd_out, buff, n_leidos*sizeof(char));
	}
	

	// Se cierran ambos archivos
	close(fd_in);
	close(fd_out);

	return EXIT_SUCCESS;
}
```
Vemos que, tras comprobar la validez de los argumentos y abrir los correspondientes archivos, se escribe. Cabe destacar la función `sprintf`, que funciona como `printf` solo que no imprime en la salida estándar, sino que el resultado se guarda en la cadena pasada como primer parámetro.

**Modificación adicional:** ¿Cómo tendrías que modificar el programa para que pudiésemos indicar en su primera línea el número de etiquetas `Bloque i` escritas de forma que tuviese la siguiente apariencia?:
```txt
El número de bloques es <nº_bloques>
Bloque 1
// Aquí van los primeros 80 Bytes del archivo pasado como argumento.
Bloque 2
// Aquí van los siguientes 80 Bytes del archivo pasado como argumento.
...
```

Es necesario obtener el número bytes antes de leer, ya que sería muy costoso leer solo para obtener los bytes, y luego leer para escribir los bloques. Además, tampoco podemos escribir primero los bloques y luego la cadena inicial, ya que se sobreescribiría el primer bloque. Por tanto, tenemos que, justo antes del bucle `while` que lee, hemos de incluir el siguiente código:
```c
	// -----------------------------------------------------------------------------
	// Modificación adicional. Antes de leer, debo escribir el número de bloques.

	int n_bytes = lseek(fd_in, 0, SEEK_END);	// Obtengo el número de bytes totales
	lseek(fd_in, 0, SEEK_SET);	// Para a empezar a leer y escribir desde el principio del fichero

	int bloques_totales; // Función ceil aplicada, ya que el último bloque puede no estar completo.
	if ((n_bytes % TAM_BLOQUE) == 0)
		bloques_totales = n_bytes/TAM_BLOQUE;
	else
		bloques_totales = (n_bytes/TAM_BLOQUE) + 1;	
	
	char cadena[100];	// Cadena de inicio
	sprintf(cadena, "El número de bloques es %d\n", bloques_totales);
	write(fd_out, cadena, strlen(cadena));
	// ----------------------------------------------------------------------------
```


## Ejercicio 3.
¿Qué hace el siguiente programa?
```c
/*
P1_Ejercicio_3.c
Trabajo con llamadas al sistema del Sistema de Archivos ''POSIX 2.10 compliant''
*/

#include<unistd.h>  /* POSIX Standard: 2.10 Symbolic Constants <unistd.h>
		     		*/
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>  /* Primitive system data types for abstraction	\
							of implementation-dependent data types.
							POSIX Standard: 2.6 Primitive System Data Types
							<sys/types.h>
						*/
#include<sys/stat.h>
#include<stdio.h>
#include<errno.h>
#include<string.h>

int main(int argc, char *argv[]){

	struct stat atributos;
	char tipoArchivo[30];

	if(argc<2) {
		printf("\nSintaxis de ejecucion: tarea3 [<nombre_archivo>]+\n\n");
		exit(EXIT_FAILURE);
	}

	for(int i=1; i<argc; i++) {
		printf("%s: ", argv[i]);

		if(lstat(argv[i],&atributos) < 0) {
			printf("\nError al intentar acceder a los atributos de %s",argv[i]);
			perror("\nError en lstat");
			exit(EXIT_FAILURE);
		}

		else {
			if(S_ISREG(atributos.st_mode)) 			strcpy(tipoArchivo,"Regular");
			else if(S_ISDIR (atributos.st_mode)) 	strcpy(tipoArchivo,"Directorio");
			else if(S_ISCHR (atributos.st_mode)) 	strcpy(tipoArchivo,"Especial de caracteres");
			else if(S_ISBLK (atributos.st_mode)) 	strcpy(tipoArchivo,"Especial de bloques");
			else if(S_ISFIFO(atributos.st_mode))	strcpy(tipoArchivo,"Tuberia con nombre (FIFO)");
			else if(S_ISLNK (atributos.st_mode))	strcpy(tipoArchivo,"Enlace relativo (soft)");
			else if(S_ISSOCK(atributos.st_mode))	strcpy(tipoArchivo,"Socket");
			
			else strcpy(tipoArchivo,"Tipo de archivo desconocido");
			
			printf("%s\n",tipoArchivo);
		}
	}

	return EXIT_SUCCESS;
}
```

En primer lugar, se comprueba que se le ha pasado, al menos, un archivo. Posteriormente, para cada archivo se obtiene su estructira `stat`, que se guarda en `atributos`. Notemos que la orden que se usa es `lstat`, que únicamente se difiere de `stat` cuando el archivo es un `soft link`. En ese caso, la información que se obtiene no es la del archivo al que apunta, sino la del enlace en sí.

Por último, se informa del tipo de cada archivo, con las correspondientes `macros` definidas según _POSIX_.




## Ejercicio 4.

Define una macro en lenguaje C que tenga la misma funcionalidad que la macro `S_ISREG(mode)` usando para ello los flags definidos en `<sys/stat.h>` para el campo `st_mode` de la struct `stat`, y comprueba que funciona en un programa simple. Consulta en un libro de C o en internet cómo se especifica una macro con argumento en C.

Tenemos que la macro es:
```c
#define S_ISREG2(mode)  ((mode & S_IFMT) == S_IFREG)
```

Una macro en C es una directiva del precompilador. El hecho de ser con parámtetros hace que se pueda asemejar a una función, pero no lo es ya que se procesa antes del proceso de compilación.

Notemos que, en este caso, en primer lugar nos quedamos con los bits que codifican el tipo de archivo (`&`), y luego verificamos si es un fichero regular (`==`).

Un programa de ejemplo es el siguiente, prácticamente idéntico al del ejercicio anterior.
```c
/*
P1_Ejercicio_4.c
*/

#include<unistd.h>  /* POSIX Standard: 2.10 Symbolic Constants <unistd.h>
		     		*/
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>  /* Primitive system data types for abstraction	\
							of implementation-dependent data types.
							POSIX Standard: 2.6 Primitive System Data Types
							<sys/types.h>
						*/
#include<sys/stat.h>
#include<stdio.h>
#include<errno.h>
#include<string.h>


#define S_ISREG2(mode)  ((mode & S_IFMT) == S_IFREG)



int main(int argc, char *argv[]){

	struct stat atributos;
	char tipoArchivo[30];

	if(argc<2) {
		printf("\nSintaxis de ejecucion: tarea4 [<nombre_archivo>]+\n\n");
		exit(EXIT_FAILURE);
	}

	for(int i=1; i<argc; i++) {
		printf("%s: ", argv[i]);

		if(lstat(argv[i],&atributos) < 0) {
			printf("\nError al intentar acceder a los atributos de %s",argv[i]);
			perror("\nError en lstat");
			exit(EXIT_FAILURE);
		}

		else {
			if(S_ISREG2(atributos.st_mode)) strcpy(tipoArchivo,"Regular");
			else strcpy(tipoArchivo,"No es un archivo regular");
			
			printf("%s\n",tipoArchivo);
		}
	}

	return EXIT_SUCCESS;
}
```