# Sistemas Operativos.  Módulo II. Práctica 02.

**Autor:** Arturo Olivares Martos
***

- **Asignatura:** Sistemas Operativos.
- **Curso Académico:** 2023-24.
- **Grado:** Doble Grado en Ingeniería Informática y Matemáticas.
- **Grupo:** Único.
- **Profesor:** Alejandro José León Salas
- **Descripción:** Sesión 2 del Módulo II de las prácticas de SO.
<!--- **Fecha:** 17 de abril de 2023. -->
<!-- - **Duración:** -->


## Ejercicio 1.
¿Qué hace el siguiente programa?
```c
/*
P2_Ejercicio_1.c
Trabajo con llamadas al sistema del Sistema de Archivos ''POSIX 2.10 compliant''
Este programa fuente está pensado para que se cree primero un programa con la parte
 de CREACION DE ARCHIVOS y se haga un ls -l para fijarnos en los permisos y entender
 la llamada umask.
En segundo lugar (una vez creados los archivos) hay que crear un segundo programa
 con la parte de CAMBIO DE PERMISOS para comprender el cambio de permisos relativo
 a los permisos que actualmente tiene un archivo frente a un establecimiento de permisos
 absoluto.
*/

#include<sys/types.h>	//Primitive system data types for abstraction of implementation-dependent data types.
						//POSIX Standard: 2.6 Primitive System Data Types <sys/types.h>
#include<unistd.h>		//POSIX Standard: 2.10 Symbolic Constants         <unistd.h>
#include<sys/stat.h>
#include<fcntl.h>		//Needed for open
#include<stdio.h>
#include<errno.h>
#include<stdlib.h>

int main(int argc, char *argv[]){
	int fd1,fd2;
	struct stat atributos;

	//CREACION DE ARCHIVOS
	if( (fd1=open("archivo1",O_CREAT|O_TRUNC|O_WRONLY,S_IRGRP|S_IWGRP|S_IXGRP))<0) {
		printf("\nError %d en open(archivo1,...)",errno);
		perror("\nError en open");
		exit(EXIT_FAILURE);
	}

	umask(0);
	if( (fd2=open("archivo2",O_CREAT|O_TRUNC|O_WRONLY,S_IRGRP|S_IWGRP|S_IXGRP))<0) {
		printf("\nError %d en open(archivo2,...)",errno);
		perror("\nError en open");
		exit(EXIT_FAILURE);
	}

	//CAMBIO DE PERMISOS
	if(lstat("archivo1",&atributos) < 0) {
		printf("\nError al intentar acceder a los atributos de archivo1");
		perror("\nError en lstat");
		exit(EXIT_FAILURE);
	}
	if(chmod("archivo1", (atributos.st_mode & ~S_IXGRP) | S_ISGID) < 0) {
		perror("\nError en chmod para archivo1");
		exit(EXIT_FAILURE);
	}

	if(chmod("archivo2",S_IRWXU | S_IRGRP | S_IWGRP | S_IROTH) < 0) {
		perror("\nError en chmod para archivo2");
		exit(EXIT_FAILURE);
	}

	return EXIT_SUCCESS;
}
```

Para entender el programa, le hemos añadido unas pequeñas variaciones.
En primer lugar, cuando se cambia la máscara, imrpimimos también la antigua, para que se puedan entender los permisos de `archivo1`.




Tenemos que, en primer lugar se crean dos archivos con la llamada al sistema `open`. Ambas reciben el mismo modo como parámetros, pero a la hora de crear `archivo1`. Además, tanto tras crear los archivos como tras cambiar sus permisos, se ejecuta `ls -l` con la llamada al sistema `system` (se verá más adelante). Por tanto, el programa queda así:
```c
/*
P2_Ejercicio_1.c
Trabajo con llamadas al sistema del Sistema de Archivos ''POSIX 2.10 compliant''
Este programa fuente está pensado para que se cree primero un programa con la parte
 de CREACION DE ARCHIVOS y se haga un ls -l para fijarnos en los permisos y entender
 la llamada umask.
En segundo lugar (una vez creados los archivos) hay que crear un segundo programa
 con la parte de CAMBIO DE PERMISOS para comprender el cambio de permisos relativo
 a los permisos que actualmente tiene un archivo frente a un establecimiento de permisos
 absoluto.
*/

#include<sys/types.h>	//Primitive system data types for abstraction of implementation-dependent data types.
						//POSIX Standard: 2.6 Primitive System Data Types <sys/types.h>
#include<unistd.h>		//POSIX Standard: 2.10 Symbolic Constants         <unistd.h>
#include<sys/stat.h>
#include<fcntl.h>		//Needed for open
#include<stdio.h>
#include<errno.h>
#include<stdlib.h>

int main(int argc, char *argv[]){
	int fd1,fd2;
	struct stat atributos;

	//CREACION DE ARCHIVOS
	if( (fd1=open("archivo1",O_CREAT|O_TRUNC|O_WRONLY,S_IRGRP|S_IWGRP|S_IXGRP))<0) {
		printf("\nError %d en open(archivo1,...)",errno);
		perror("\nError en open");
		exit(EXIT_FAILURE);
	}

	// Variación ----------------------------------
	mode_t ant_mask = umask(0);
	printf("Máscara original: %04o\n\n", ant_mask);
	// --------------------------------------------


	if( (fd2=open("archivo2",O_CREAT|O_TRUNC|O_WRONLY,S_IRGRP|S_IWGRP|S_IXGRP))<0) {
		printf("\nError %d en open(archivo2,...)",errno);
		perror("\nError en open");
		exit(EXIT_FAILURE);
	}

	// Variación ----------------------------------------
	printf("Imprimiendo ficheros creados...\n");
	if (system("ls -l") < 0) {
		perror("\nError al ejecutar ls -l");
		exit(EXIT_FAILURE);
	}
	// --------------------------------------------------

	//CAMBIO DE PERMISOS
	if(lstat("archivo1",&atributos) < 0) {
		printf("\nError al intentar acceder a los atributos de archivo1");
		perror("\nError en lstat");
		exit(EXIT_FAILURE);
	}
	if(chmod("archivo1", (atributos.st_mode & ~S_IXGRP) | S_ISGID) < 0) {
		perror("\nError en chmod para archivo1");
		exit(EXIT_FAILURE);
	}

	if(chmod("archivo2",S_IRWXU | S_IRGRP | S_IWGRP | S_IROTH) < 0) {
		perror("\nError en chmod para archivo2");
		exit(EXIT_FAILURE);
	}

	// Variación --------------------------------------------------------
	printf("\n\nImprimiendo ficheros con permisos modificados...\n");
	if (system("ls -l") < 0) {
		perror("\nError al ejecutar ls -l");
		exit(EXIT_FAILURE);
	}
	// -------------------------------------------------------------------

	return EXIT_SUCCESS;
}
```

La salida de este programa es:
```console
$ ./P2_Ej1 
Máscara original: 0022

Imprimiendo ficheros creados...
total 40
----r-x--- 1 arturo arturo     0 nov  7 17:55 archivo1
----rwx--- 1 arturo arturo     0 nov  7 17:55 archivo2
-rwxr-xr-x 1 arturo arturo 16408 nov  7 17:55 P2_Ej1
-rw-rw-r-- 1 arturo arturo  2275 nov  7 17:55 P2_Ejercicio_1.c


Imprimiendo ficheros con permisos modificados...
total 40
----r-S--- 1 arturo arturo     0 nov  7 17:55 archivo1
-rwxrw-r-- 1 arturo arturo     0 nov  7 17:55 archivo2
-rwxr-xr-x 1 arturo arturo 16408 nov  7 17:55 P2_Ej1
-rw-rw-r-- 1 arturo arturo  2275 nov  7 17:55 P2_Ejercicio_1.c
```

Veamos ahora qué hace el programa. En primer lugar, crea el `archivo1` en el que tan solo le da permisos de lectura, escritura y ejecución al grupo, pero ni al propietario ni a others les da permisos. No obstante, en la salida vemos que la máscara original es `0022`, por lo que se le quitan los permisos de escritura al grupo. Vemos que esto es cierto en la primera salida de `ls`. Respecto al `archivo2`, como la máscara se pone a `0`, tenemos que los permisos son los especificados en `mode`, es decir, lectura, escritura y ejecución para el grupo.

En la segunda parte, se modifican los permisos. En el caso de `archivo1`, se le quita el permiso de ejecución al grupo, y se le añade el bit `SGID`. Esto se puede ver en la segunda salida de`ls` donde además el `SGID` está marcado con la `S`. Respecto a los permisos de `archivo2`, vemos que se establecen unos nuevos, como se ve reflejado en la salida de `ls -l`.

Notemos además que, como tras ejectar el programa el usuario no tiene permisos de escritura en `archivo1`, si se vuelve a ejecutar dará error al intentar abrir el archivo, por lo que es necesario borrar el archivo antes de volver a ejecutar el programa.

## Ejercicio 2.

Realiza un programa en C utilizando las llamadas al sistema necesarias que acepte
como entrada:
- Un argumento que representa el `pathname` de un directorio.
- Otro argumento que es un número octal de 4 dígitos (similar al que se puede utilizar para cambiar los permisos en la llamada al sistema `chmod`). Para convertir este argumento tipo cadena a un tipo numérico puedes utilizar la función `strtol`. Consulta el manual en línea para conocer sus argumentos.

El programa tiene que usar el número octal indicado en el segundo argumento para cambiar los permisos de todos los archivos que se encuentren en el directorio indicado en el primer argumento. El programa debe proporcionar en la salida estándar una línea para cada archivo del directorio
que esté formada por:
> <nombre_de_archivo> : <permisos_antiguos> <permisos_nuevos>

Si no se pueden cambiar los permisos de un determinado archivo se debe especificar la siguiente información en la línea de salida:
> <nombre_de_archivo> : <errno> <permisos_antiguos>


El programa implementado es el siguiente:
```c
/*
P2_Ejercicio_2.c
*/

#include<sys/types.h>	//Primitive system data types for abstraction of implementation-dependent data types.
						//POSIX Standard: 2.6 Primitive System Data Types <sys/types.h>
#include<unistd.h>		//POSIX Standard: 2.10 Symbolic Constants         <unistd.h>
#include<sys/stat.h>
#include<fcntl.h>		//Needed for open
#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include<string.h>
#include<dirent.h>		// Needed por managing directories

int main(int argc, char *argv[]){

	// Comprobación de los parámetros
	if (argc != 3){
		printf("Uso: P2_Ejercicio_2 <pathname> <permisos_nuevos>\n");
		exit(EXIT_FAILURE);
	}

	if (strlen(argv[2])!= 4){
		printf("El número que representa los permisos nuevos ha de tener 4 dígitos.\n");
		exit(EXIT_FAILURE);
	}

	char *invalid;	// Conversión del octal
	mode_t new_perm = strtol(argv[2], &invalid, 8);
	if (*invalid != '\0'){ // Ha habido un error al convertir a octal
		printf("El número que representa los permisos ha de ser un octal.\n");
		exit(EXIT_FAILURE);
	}


	DIR *directorio;
	if ((directorio=opendir(argv[1])) == NULL){
		printf("Error %d en opendir(%s)\n", errno, argv[1]);
		perror("\nError en opendir.");
		exit(EXIT_FAILURE);
	}


	errno = 0; // Para detectar si ha habido error en readdir
	const mode_t MASK_PERM = S_IRWXU | S_IRWXG | S_IRWXO | S_ISGID | S_ISUID | S_ISVTX; // Máscara para obtener solo los permisos
	struct dirent *entrada;
	struct stat atributos;
	while ((entrada=readdir(directorio))!= NULL){
		
		// Para obtener los permisos antiguos llamamos a lstat.
		if (lstat(entrada->d_name, &atributos) < 0){
			printf("\nError %d al intentar acceder a los atributos de %s.\n",errno, entrada->d_name);
			perror("\nError en lstat");
			exit(EXIT_FAILURE);
		}

		// A los directorios no se le cambian los permisos, solo a los archivos
		if (! S_ISDIR(atributos.st_mode)){
			mode_t old_perm = atributos.st_mode & MASK_PERM;

			if (chmod(entrada->d_name, new_perm) < 0){ // Ha habido error
				printf("%-20s: \t%4d\t %04o\n", entrada->d_name, errno, old_perm);
			}else{	// No ha habido error
				printf("%-20s: \t%04o\t %04o\n", entrada->d_name, old_perm, new_perm);	
			}
		}

		errno = 0;	// Para detectar si ha habido error en readdir
	}

	if (errno != 0){ // Ha habido error en opendir
		printf("Error %d en readdir(%s)\n", errno, argv[1]);
		perror("\nError en readdir.");
		exit(EXIT_FAILURE);
	}


	closedir(directorio);


	return EXIT_SUCCESS;
}
```

Notemos que, tras comprobar la validez de los argumentos, se abre el directorio. Para cada uno de los archivos del directorio (notemos que se omiten los directorios) se intentan cambiar los archivos.





## Ejercicio 3.
Programa una nueva orden que recorra la jerarquía de subdirectorios existentes a partir de uno dado como argumento y devuelva la cuenta de todos aquellos archivos regulares que tengan permiso de ejecución para el _grupo_ y para _otros_. Además del nombre de los archivos encontrados, deberá devolver sus números de inodo y la suma total de espacio ocupado por dichos archivos. El formato de la nueva orden será:
```console
$> ./buscar <pathname>
```
donde `<pathname>` especifica la ruta del directorio a partir del cual queremos que empiece a analizar la estructura del árbol de subdirectorios. En caso de que no se le dé argumento, tomará como punto de partida el directorio actual.

Ejemplo de la salida después de ejecutar el programa:
```console
./buscar
Los i-nodos son:
./a.out 55
./bin/ej 123
./bin/ej2 87
...

Existen 24 archivos regulares con permiso x para grupo y otros
El tamaño total ocupado por dichos archivos es 2345674 bytes.
```


Tenemos que el programa es:
```c
/*
P2_Ejercicio_3.c
*/

#include<sys/types.h>	//Primitive system data types for abstraction of implementation-dependent data types.
						//POSIX Standard: 2.6 Primitive System Data Types <sys/types.h>
#include<unistd.h>		//POSIX Standard: 2.10 Symbolic Constants         <unistd.h>
#include<sys/stat.h>
#include<fcntl.h>		//Needed for open
#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include<string.h>
#include<dirent.h>		// Needed por managing directories



/**
 * @brief Busca recursivamente en el directorio especificado los archivos que cumplen los permisos especificados.
 * 
 * @param path_dir  Directorio en el que se busca.
 * @param count_files  Contador de archivos que cumplen los permisos.
 * @param tot_size  Tamaño total acumulados de los archivos que cumplen los permisos.
 * @param PERM  Permisos que se buscan.
 */
void busqueda_directorio(const char *path_dir, long* count_files, long* tot_size, const mode_t PERM){

	// Abrimos el directorio
	DIR* directorio;
	if ((directorio=opendir(path_dir)) == NULL){
		printf("Error %d en opendir(%s)\n", errno, path_dir);
		perror("\nError en opendir.");
		exit(EXIT_FAILURE);
	}

	errno = 0; // Para detectar si ha habido error en readdir
	struct dirent *entrada;	// Cada entrada del directorio
	struct stat atributos;	// La stat de cada entrada
	while ((entrada=readdir(directorio))!= NULL){

		// Se saltan los directorios que mantienen la jerarquía
		if ((strcmp(entrada->d_name, "." )==0) || (strcmp(entrada->d_name, "..")==0))
			continue;

		char path_entrada[500];	// Compongo para que las rutas sean absolutas, ya que si no, no funciona
		sprintf(path_entrada, "%s/%s", path_dir, entrada->d_name);
		
		// Para obtener el número de inodo y el tipo de archivo.
		if (lstat(path_entrada, &atributos) < 0){
			printf("\nError %d al intentar acceder a los atributos de %s.\n",errno, path_entrada);
			perror("\nError en lstat");
			exit(EXIT_FAILURE);
		}

		// Si es un directorio, se busca ahora dentro de él
		if (S_ISDIR(atributos.st_mode))
			busqueda_directorio(path_entrada, count_files, tot_size, PERM);

		// Si no es un directorio y tiene los permisos buscados, se imprime y se contabiliza
		else if ((atributos.st_mode & PERM) == PERM){
			printf("\t%-20s:\t %9lu\n", path_entrada, entrada->d_ino);
			(*count_files) ++;
			(*tot_size) += atributos.st_size;
		}

		errno = 0;	// Para detectar si ha habido error en readdir
	}

	if (errno != 0){ // Ha habido error en readdir
		printf("Error %d en readdir(%s)\n", errno, path_dir);
		perror("\nError en readdir.");
		exit(EXIT_FAILURE);
	}

	if (closedir(directorio) < 0){ // Ha habido error en closedir
		printf("Error %d en closedir(%s)\n", errno, path_dir);
		perror("\nError en readdir.");
		exit(EXIT_FAILURE);
	}
}

int main(int argc, char *argv[]){

	// Comprobación del número de parámetros
	if (argc > 2){
		printf("Uso: P2_Ejercicio_3 [<pathname>]\n");
		exit(EXIT_FAILURE);
	}

	// Obtención del directorio inicial de búsqueda
	char path_ini[100] = ".";	// Default

	if (argc == 2)	// Si se le da un directorio, se actualiza.
		strcpy(path_ini, argv[1]);

	// Los permisos buscados son los de ejecución para el grupo y others.
	const mode_t PERM = S_IXGRP | S_IXOTH;

	long tot_size = 0;	// Bytes totales que cumplen los permisos especificados
	long count_files = 0;	// Contador de los archivos que cumplen esos datos

	printf("Los i-nodos son:\n");
	busqueda_directorio(path_ini, &count_files, &tot_size, PERM);	// Búsqueda

	printf("\nExisten %ld archivos regulares con permiso x para grupo y otros.\n", count_files);
	printf("El tamaño total ocupado por dichos archivos es %ld bytes.\n", tot_size);

	return EXIT_SUCCESS;
}
```

Notemos que es una función recursiva, ya que se busca en todos los directorios. Para cada archivo que cumple los permisos, se imprime su nombre, su número de inodo y se contabiliza el tamaño.


## Ejercicio 4.

Implementa de nuevo el programa `buscar` del [ejercicio 3](#ejercicio-3) utilizando la llamada al sistema `nftw`.

Tenemos que el programa es:
```c
/*
P2_Ejercicio_4.c
*/

#include<sys/types.h>	//Primitive system data types for abstraction of implementation-dependent data types.
						//POSIX Standard: 2.6 Primitive System Data Types <sys/types.h>
#include<unistd.h>		//POSIX Standard: 2.10 Symbolic Constants         <unistd.h>
#include<sys/stat.h>
#include<fcntl.h>		//Needed for open
#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include<string.h>

#define __USE_XOPEN_EXTENDED
#include<ftw.h>		// Needed por managing directories


// Los permisos buscados son los de ejecución para el grupo y others.
const mode_t PERM = S_IXGRP | S_IXOTH;

long tot_size = 0;	// Bytes totales que cumplen los permisos especificados
long count_files = 0;	// Contador de los archivos que cumplen esos datos


/**
 * @brief  Busca en el directorio especificado los archivos que cumplen los permisos especificados como variable global.
 * 
 * @param path  Directorio en el que se busca.
 * @param atributos  Stat de la entrada actual.
 * @param typeflag  Tipo de archivo de la entrada actual.
 * @param ftwbuf  Estructura con información del archivo.
 * @return 0, ya que nunca genera error.
 */
int check_file(const char *path, const struct stat *atributos, int typeflag, struct FTW *ftwbuf){

	// Si no es un directorio y tiene los permisos buscados, se imprime y se contabiliza
	if ( (typeflag != FTW_D) && ((atributos->st_mode & PERM) == PERM) ){
		
		printf("\t%-20s:\t %9lu\n", path, atributos->st_ino);
		count_files ++;
		tot_size += atributos->st_size;
	}

	return 0;
}

int main(int argc, char *argv[]){

	// Comprobación del número de parámetros
	if (argc > 2){
		printf("Uso: P2_Ejercicio_3 [<pathname>]\n");
		exit(EXIT_FAILURE);
	}

	// Obtención del directorio inicial de búsqueda
	char path_ini[100] = ".";	// Default

	if (argc == 2)	// Si se le da un directorio, se actualiza.
		strcpy(path_ini, argv[1]);

	printf("Los i-nodos son:\n");
	// Llamamos con FTW_PHYS para que no siga los enlaces simbólicos.
	// Es decir, para que use lstat en vez de stat, como se hace en el ejercicio 3.
	if (nftw(path_ini, check_file, 10, FTW_PHYS)!= 0){
		perror("Error en nftw");
		exit(EXIT_FAILURE);
	}

	printf("\nExisten %ld archivos regulares con permiso x para grupo y otros.\n", count_files);
	printf("El tamaño total ocupado por dichos archivos es %ld bytes.\n", tot_size);

	return EXIT_SUCCESS;
}
```