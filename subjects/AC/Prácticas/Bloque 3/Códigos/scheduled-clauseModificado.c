#include <stdio.h>
#include <stdlib.h>

#ifdef _OPENMP
    #include <omp.h>
#else
    #define omp_get_thread_num() 0
    #define omp_get_max_threads() 1
    #define omp_get_thread_limit() 1
    #define omp_get_dynamic() 0
    #define omp_get_schedule(kind, chunk) 0
#endif

void print_var_control(){
    printf("- Ajuste dinámico de nº de hilos (0=false, 1=true): %d\n", omp_get_dynamic());
    printf("- Nº de threads: %d\n", omp_get_max_threads());
    printf("- Limite de threads: %d\n", omp_get_thread_limit());

    #ifdef _OPENMP
        omp_sched_t kind;
        int chunk;
    #else
        int kind=-1, chunk=-1;
    #endif
    
    omp_get_schedule(&kind, &chunk);
    printf("- Kind para la planificacion con runtime: %x\n", kind);
    printf("- Chunk para la planificacion con runtime: %d\n", chunk);
}


int main(int argc, char **argv)
{
    int i, n=200, chunk, a[n], suma=0;
    
    if(argc < 3)
    {
        fprintf(stderr,"\nFalta iteraciones o chunk\n");
        exit(-1);
    }

    n = atoi(argv[1]);
    if (n>200)
        n=200;

    chunk = atoi(argv[2]); 

    for (i=0; i<n; i++)
        a[i] = i; 
    
    printf("Fuera de la region paralela:\n");
    print_var_control();
    printf("\n\n");

    #pragma omp parallel
    {
        #pragma omp master
        {
            printf("Dentro de la region paralela:\n");
            print_var_control();
            printf("\n\n"); 
        }

        #pragma omp barrier

        #pragma omp for reduction(+:suma) schedule(static,chunk)
        for (i=0; i<n; i++)
        {
            suma = suma + a[i];
            printf(" thread %d suma a[%d]=%d suma=%d \n",
                omp_get_thread_num(),i,a[i],suma);
        }
    }
    

    printf("Fuera de 'parallel for' suma=%d\n",suma); 
}

