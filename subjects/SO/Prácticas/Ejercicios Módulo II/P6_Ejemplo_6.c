#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdlib.h>

int main (int argc, char *argv[])
{
        
	int fd;
	char *p;
		
	fd = open("/dev/zero", O_RDONLY);

	if ((p = (char *) mmap (0, sizeof(int), PROT_READ , MAP_SHARED, fd, 0))== MAP_FAILED) {
		printf("Fallo el mapeo\n");
		return EXIT_FAILURE;
	}
	
	close(fd);
	return EXIT_SUCCESS;
}
					  
