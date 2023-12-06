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