#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char **argv)
{
    int i, n=20, tid, n_threads = 1;
    int a[n], suma=0, sumalocal;
    
    if (argc < 3)
    {
        fprintf(stderr,"[ERROR] uso: <programa> <n_iteraciones> <n_threads>\n");
        exit(-1);
    }

    // Limitación del número de iteraciones
    n = atoi(argv[1]);
    if (n>20)
        n=20;

   for (i=0; i<n; i++)
      a[i]=i;

    // Limitación del número de hilos
    n_threads = atoi(argv[2]);
    if (n_threads>4)
        n_threads=4; 
 
    #pragma omp parallel if(n>4) default(none) \
                private(sumalocal,tid) shared(a,suma,n) \
                num_threads(n_threads)
    {
        sumalocal=0;
        tid=omp_get_thread_num();

        #pragma omp for private(i) schedule(static) nowait
        for (i=0; i<n; i++)
        {
            sumalocal += a[i];
            printf(" thread %d suma de a[%d]=%d sumalocal=%d \n",
                   tid, i, a[i], sumalocal);
        } 

        #pragma omp atomic 
        suma += sumalocal;

        #pragma omp barrier

        #pragma omp master
        printf("thread master=%d imprime suma=%d\n", tid, suma);
    }  
}

