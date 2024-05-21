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
    #define omp_set_dynamic(val_dynamic) 0
    #define omp_set_num_threads(val_max_threads) 0
    #define omp_set_schedule(val_schedule_kind, val_schedule_chunk) 0
#endif

void print_var_control(){
    printf("- Ajuste dinámico de nº de hilos (0=false, 1=true): %d\n", omp_get_dynamic());
    printf("- Nº de threads: %d\n", omp_get_max_threads());

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
    
    printf("Antes de la 1ª modificación fuera del parallel:\n");
    print_var_control();
    printf("\n\n");
    omp_set_dynamic(1);
    omp_set_num_threads(4);
    omp_set_schedule((omp_sched_t)(omp_sched_guided | omp_sched_monotonic), 7);
    printf("Después de la 1ª modificación fuera del parallel:\n");
    print_var_control();
    printf("------------------------------------\n\n");
    printf("\n\n");


    #pragma omp parallel
    {
        #pragma omp master
        {
            printf("Antes de la modificación dentro del parallel:\n");
            print_var_control();
            printf("\n\n");
            omp_set_dynamic(0);
            omp_set_num_threads(5);
            omp_set_schedule(omp_sched_dynamic, 4);
            printf("Después de la modificación dentro del parallel:\n");
            print_var_control();
            printf("------------------------------------\n\n");
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

    printf("Antes de la 2ª modificación fuera del parallel:\n");
    print_var_control();
    printf("\n\n");
    omp_set_dynamic(0);
    omp_set_num_threads(5);
    omp_set_schedule(omp_sched_dynamic, 4);
    printf("Después de la 2ª modificación fuera del parallel:\n");
    print_var_control();
    printf("------------------------------------\n\n");
    printf("\n\n"); 
    

    printf("Fuera de 'parallel for' suma=%d\n",suma); 
}

