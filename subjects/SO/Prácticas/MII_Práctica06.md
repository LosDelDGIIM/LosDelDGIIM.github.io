# Sistemas Operativos.  Módulo II. Práctica 06.

**Autor:** Arturo Olivares Martos
***

- **Asignatura:** Sistemas Operativos.
- **Curso Académico:** 2023-24.
- **Grado:** Doble Grado en Ingeniería Informática y Matemáticas.
- **Grupo:** Único.
- **Profesor:** Alejandro José León Salas
- **Descripción:** Sesión 6 del Módulo II de las prácticas de SO.
<!--- **Fecha:** 17 de abril de 2023. -->
<!-- - **Duración:** -->


## Ejercicio 1.
Implementa un programa que admita tres argumentos. El primer argumento será una orden de Linux; el segundo, uno de los siguientes caracteres "<" o ">", y el tercero el nombre de un archivo (que puede existir o no).

El programa ejecutará la orden que se especifica como argumento primero e implementará la redirección especificada por el segundo argumento hacia el archivo indicado en el tercer argumento. Por ejemplo, si deseamos redireccionar la entrada estándar de `sort` desde un archivo temporal, ejecutaríamos:
```console
$> ./mi_programa sort "<" temporal
```

Tenemos que el programa es:
```c
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>

int main (int argc, char *argv[]){

    if (argc != 4) {
        printf("Usage: %s <orden> \"<\"/\">\" <archivo>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (strcmp(argv[2], "<") != 0 && strcmp(argv[2], ">") != 0) {
        printf("Usage: %s <orden> \"<\"/\">\" <archivo>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int redirige_entrada = strcmp(argv[2], "<") == 0;

    // Si redirige la entrada, se abre para lectura.
    // Si redirige la salida, se abre para escritura y se permite crear y truncar.
    int flags = redirige_entrada ? O_RDONLY : O_WRONLY | O_CREAT | O_TRUNC;

    // Si redirige la salida y tiene que crearse, se crea con permisos 744.
    mode_t mode = redirige_entrada ? 0 : S_IRWXU | S_IRGRP | S_IROTH;

    int fd;
    if ((fd = open(argv[3], flags, mode)) == -1) {
        perror("Error al abrir el archivo");
        exit(EXIT_FAILURE);
    }

    // Si redirige la entrada, se redirige la entrada estándar al archivo.
    // Si redirige la salida, se redirige la salida estándar al archivo.
    int fd_dup = redirige_entrada ? STDIN_FILENO : STDOUT_FILENO;

    /*
    // Opción con DUP2
    if (dup2(fd, fd_dup) == -1) {
        perror("Error al redirigir la entrada/salida estándar");
        exit(EXIT_FAILURE);
    }
    */

    
    // Opción con fnctl
    if (close(fd_dup) == -1) {
        perror("Error al cerrar la entrada/salida estándar");
        exit(EXIT_FAILURE);
    }
    if (fcntl(fd, F_DUPFD, fd_dup) == -1) {
        perror("Error al redirigir la entrada/salida estándar");
        exit(EXIT_FAILURE);
    }
    
    
    // Se ejecuta el comando.
    if (execlp(argv[1], argv[1], NULL) == -1) {
        perror("Error al ejecutar el comando");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}
```

En primer lugar, vemos que valida los argumentos. Posteriormente, abre el archivo correspondiente en función de si se va a redirigir la entrada o la salida.

A continuación, redirige la entrada o la salida estándar al archivo, que se puede hacer tanto con `dup2` como con `fcntl`. Finalmente, ejecuta el comando, el cual tomará la entrada/salida del archivo indicado.

Notemos que se usa `execlp` para poder buscar también según la variable `PATH`.

## Ejercicio 2.

Reescribir el programa que implemente un encauzamiento de dos órdenes pero utilizando `fcntl`. Este programa admitirá tres argumentos. El primer argumento y el tercero serán dos órdenes de Linux. El segundo argumento será el carácter "|". El programa deberá ahora hacer la redirección de la salida de la orden indicada por el primer argumento hacia el cauce, y redireccionar la entrada estándar de la segunda orden desde el cauce.

Por ejemplo, para simular el encauzamiento ls|sort, ejecutaríamos nuestro programa como:
```console
$> ./mi_programa2 ls "|" sort
```
Tenemos que el programa es:
```c
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
```

Vemos que el programa es análogo al ya hecho en la sesión 4, pero en vez de usar `dup2` se usa `fcntl`.


## Ejercicio 3.
Construir un programa que verifique que, efectivamente, el kernel comprueba que puede darse una situación de interbloqueo en el bloqueo de archivos.

Tenemos que el programa es:
```c
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    
    int fd = open("lockfile", O_RDWR | O_CREAT, 0666);
    struct flock lock;

    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0; // Bloquear todo el archivo

    if (fork() == 0) {
        // Primer proceso hijo
        if (fcntl(fd, F_SETLK, &lock) == -1) {
            perror("fcntl");
            exit(EXIT_FAILURE);
        }
        printf("Primer proceso hijo ha bloqueado el archivo\n");
        sleep(10); // Mantener el archivo bloqueado
        exit(EXIT_SUCCESS);
    }

    sleep(1); // Dar tiempo al primer proceso hijo para bloquear el archivo

    if (fork() == 0) {
        // Segundo proceso hijo
        if (fcntl(fd, F_SETLK, &lock) == -1) {
            printf("Segundo proceso hijo no puede bloquear el archivo, el kernel ha prevenido el interbloqueo\n");
            return EXIT_FAILURE;
        }
        printf("Segundo proceso hijo ha bloqueado el archivo\n");
        exit(EXIT_SUCCESS);
    }

    // Esperar a que los procesos hijos terminen
    wait(NULL);
    wait(NULL);

    return EXIT_SUCCESS;
}
```


Vemos que se crea un primer proceso hijo que bloquea el archivo entero. Posteriormente, se crea un segundo proceso hijo que intenta bloquear el archivo entero. Como el kernel previene el interbloqueo, el segundo proceso hijo no podrá bloquear el archivo y muestra dicho mensaje por pantalla.
```console
$ ./P6_Ej3
Primer proceso hijo ha bloqueado el archivo
Segundo proceso hijo no puede bloquear el archivo, el kernel ha prevenido el interbloqueo
```

## Ejercicio 4.

Construir un programa que se asegure que solo hay una instancia de él en ejecución en un momento dado. El programa, una vez que ha establecido el mecanismo para asegurar que solo una instancia se ejecuta, entrará en un bucle infinito que nos permitirá comprobar que no podemos lanzar más ejecuciones del mismo. En la construcción del mismo, deberemos asegurarnos de que el archivo a bloquear no contiene inicialmente nada escrito en una ejecución anterior que pudo quedar por una caída del sistema.

Tenemos que el programa es:
```c
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>

// Este archivo para comprobar la unicidad tendría que ser una ruta absoluta,
//          para que no se pueda ejecutar desde distintas carpetas.
// No obstante, para comodidad del usuario, y como es una simple prueba, se mantiene en esta carpeta dicho archivo
#define arch_unicidad "./P6_Ej4_Unicidad.pid"

int main() {

    struct flock cerrojo;
    cerrojo.l_type = F_WRLCK;
    cerrojo.l_whence = SEEK_SET;
    cerrojo.l_start = 0;
    cerrojo.l_len = 0;
    // Vamos a intentar un cerrojo de escritura para todo el archivo

    int fd; // Abrimos el archivo
    if ((fd = open(arch_unicidad, O_WRONLY | O_CREAT, S_IRGRP|S_IROTH|S_IRWXU)) < 0){
        perror("Error en open");
        exit(EXIT_FAILURE);
    }

    // Intentamos el cerrojo. Esta es la comprobación de que solo hay un programa ejecutándolo a la vez
    if (fcntl(fd, F_SETLK, &cerrojo) == -1) {
        perror("Error en fcntl");
        exit(EXIT_FAILURE);
    }

    // Si llegamos aquí, es que el cerrojo se ha establecido correctamente
    // Ahora vamos a escribir el PID del proceso en el archivo
    pid_t pid = getpid();
    char pid_str[10];
    sprintf(pid_str, "%d", pid);
    if (write(fd, &pid_str, strlen(pid_str)*sizeof(char)) < 0) {
        perror("Error en write");
        exit(EXIT_FAILURE);
    }

    sleep(15); // Esperamos 30 segundos para que el usuario pueda comprobar que no se puede ejecutar el programa dos veces

    // Ahora vamos a liberar el cerrojo
    cerrojo.l_type = F_UNLCK;
    if (fcntl(fd, F_SETLK, &cerrojo) < 0) {
        perror("Error en fcntl");
        exit(EXIT_FAILURE);
    }

    close(fd); // Cerramos el archivo

    return EXIT_SUCCESS;
}
```

EN primer lugar, se abre el archivo a bloquear. Posteriormente, se intenta el cerrojo. Si se consigue, significa que este programa no se está ejecutando, por lo que se escribe el PID del proceso en el archivo y empieza la ejecucicón del programa (en nuestro caso `sleep`).

Una vez pasado ese tiempo, se libera el cerrojo y se cierra el archivo, pudiénsose ejecutar de nuevo el programa. Veamos un ejemplo de ejecución:
```console
$ ./P6_Ej4 &
[1] 7912

$ cat P6_Ej4_Unicidad.pid
7912

$ ./P6_Ej4
Error en fcntl: Resource temporarily unavailable
```

Vemos que se ejecuta el programa en segundo plano, y se escribe el PID en el archivo. Posteriormente, se intenta ejecutar el programa de nuevo, pero no se puede porque el cerrojo está puesto. Habrá que esperar a que termine la ejecución del programa en segundo plano para poder ejecutarlo de nuevo.


## Ejercicio 5.

Escribir un programa, similar a la orden `cp`, que utilice para su implementación la llamada al sistema `mmap()` y una función de C que nos permite copiar memoria, como por ejemplo `memcpy()`. Para conocer el tamaño del archivo origen podemos utilizar `stat()` y para establecer el tamaño del archivo destino se puede usar `ftruncate()`.

Tenemos que el programa es:
```c
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/mman.h>

int main(int argc, char **argv) {

    if (argc != 3) {
        printf("Usage: %s <arch_orig> <arch_dest>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Abrimos el archivo de origen
    int fd_origen;
    if ((fd_origen=open(argv[1], O_RDONLY)) == -1) {
        perror("Error al abrir el archivo de origen");
        return EXIT_FAILURE;
    }
    // Obtenemos su tamaño y sus permisos
    struct stat st;
    if (fstat(fd_origen, &st) == -1) {
        perror("Error al obtener los atributos del archivo de origen");
        return EXIT_FAILURE;
    }
    size_t tam_orig= st.st_size;
    mode_t permisos_orig= st.st_mode & 0777;


    // Creamos el archivo de destino
    int fd_destino;
    if ((fd_destino=open(argv[2], O_RDWR | O_CREAT | O_TRUNC, permisos_orig)) == -1) {
        perror("Error al crear el archivo de destino");
        return EXIT_FAILURE;
    }
    // Redimensionamos el archivo de destino
    if (ftruncate(fd_destino, tam_orig) == -1) {
        perror("Error al redimensionar el archivo de destino");
        return EXIT_FAILURE;
    }


    // Mapeamos el archivo de origen
    char *map_origen;
    if ((map_origen=mmap(NULL, tam_orig, PROT_READ, MAP_SHARED, fd_origen, 0)) == MAP_FAILED) {
        perror("Error al mapear el archivo de origen");
        return EXIT_FAILURE;
    }

    // Mapeamos el archivo de destino
    char *map_destino;
    if ((map_destino=mmap(NULL, tam_orig, PROT_WRITE, MAP_SHARED, fd_destino, 0)) == MAP_FAILED) {
        perror("Error al mapear el archivo de destino");
        return EXIT_FAILURE;
    }

    // Copiamos el contenido del archivo de origen al de destino
    memcpy(map_destino, map_origen, tam_orig);

    // Liberamos los mapeos
    if (munmap(map_origen, tam_orig) == -1) {
        perror("Error al liberar el mapeo del archivo de origen");
        return EXIT_FAILURE;
    }
    if (munmap(map_destino, tam_orig) == -1) {
        perror("Error al liberar el mapeo del archivo de destino");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
```

Vemos que se abre el archivo de origen y se obtienen sus atributos. Posteriormente, se crea el archivo de destino con los mismos permisos que el de origen y se redimensiona al mismo tamaño. A continuación, se mapean ambos archivos y se copia el contenido del archivo de origen al de destino. Finalmente, se liberan los mapeos.