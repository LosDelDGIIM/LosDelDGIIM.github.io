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