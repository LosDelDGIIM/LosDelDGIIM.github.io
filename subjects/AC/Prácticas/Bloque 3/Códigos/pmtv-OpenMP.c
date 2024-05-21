/**
 * 
 Código para multimplicación secuencial matriz cuadrada triangular superior por vector: v2 = m * v1 pmtv-secuencial.c
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//#define VECTOR_GLOBAL
#define VECTOR_DYNAMIC

#ifdef VECTOR_GLOBAL
#define MAX 16375	
double v1[MAX], v2[MAX], m[MAX][MAX]; 
#endif

#ifdef _OPENMP
  #include <omp.h>
#else
   #define omp_get_thread_num() 0
   #define omp_get_num_threads() 1
#endif

/**
 * @file  pmv-secuencial.c  
 * @brief multimplicación secuencial matriz cuadrada triangular superior por vector: v2 = m * v1
 * 
 * @param int n=atoi(argv[1])  número de componentes de los vectores y número de filas y columnas de la matriz
 * @return 0 upon exit success (print tiempo de cálculo de la multiplicación, longitud vectores y resultados (primer y último componente del resultado para longitudes mayores que 9))
 *  
 * **Compilación**
 * @code
	gcc  -O2  pmtv-secuencial.c -o pmtv-secuencial -lrt
    (-lrt: real time library, es posible que no sea necesario usar -lrt)
 * @endcode
* **Generar ensamblador**
 * @code
 * gcc  -O2 -S pmv-secuencial.c -lrt
 * @endcode
 *  **Ejecución**
 * ~~~~~~~~~~~~~~~~~~~~~{.c}
 * pmtv-secuencial 8    (para 8 componentes en los vectores)
 * ~~~~~~~~~~~~~~~~~~~~~
 * 
**/
int main(int argc, char** argv){
    unsigned int N;

    #ifdef _OPENMP
        double cgt1,cgt2;
    #else
        struct timespec cgt1,cgt2;
    #endif
    double ncgt;

    if (argc < 2){
        printf("Uso: %s tamaño\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    N = atoi(argv[1]);

    #ifdef VECTOR_GLOBAL
    if (N > MAX)  N = MAX;
    #endif
    
    #ifdef VECTOR_DYNAMIC
    double *v1, *v2, **m;
    v1 = (double*)malloc(N*sizeof(double));
    v2 = (double*)malloc(N*sizeof(double));
    m = (double**)malloc(N*sizeof(double*));
    if ((v1 == NULL) || (v2 == NULL) || (m == NULL)) {
        printf("No hay suficiente espacio para v1, v2 y m \n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < N; i++) {
        m[i] = (double*)malloc(N*sizeof(double));
        if (m[i] == NULL) {
            printf("No hay suficiente espacio para m \n");
            exit(EXIT_FAILURE);
        }
    }
    #endif

    // Semilla de los números aleatorios
    srand48(time(NULL));

    // Inicializar vector y matriz
    for (int i = 0; i < N; i++){
        v1[i] = drand48();
        v2[i] = 0;
        for (int j = 0; j < i; j++)
            m[i][j] = 0;
        for (int j = i; j < N; j++)
            m[i][j] = drand48();
    }

    // Imprime el contenido de la variable de control run-sched-var
    printf("Antes de la modificación:\n");
    #ifdef _OPENMP
        omp_sched_t kind;
        int chunk;
    #else
        int kind=-1, chunk=-1;
    #endif
    omp_get_schedule(&kind, &chunk);
    printf("- Kind para la planificacion con runtime: %x\n", kind);
    printf("- Chunk para la planificacion con runtime: %d\n", chunk);

    // Medida de tiempo inicial
    #ifdef _OPENMP
        cgt1 = omp_get_wtime();
    #else
        clock_gettime(CLOCK_REALTIME,&cgt1);
    #endif

    // Calcular v2 = m * v1
    #pragma omp parallel for schedule(runtime)
    for(int i = 0; i < N; i++){
        for (int j = i; j < N; j++)
            v2[i] += m[i][j] * v1[j];
        
        // Imprime qué hilo ha realizado cada fila
        // Eliminar si N es muy grande
        printf("Fila: %d\t Hilo: %d\n", i, omp_get_thread_num());
    }
    // Medida de tiempo final y cálculo del tiempo de ejecución
    #ifdef _OPENMP
        cgt2 = omp_get_wtime();
        ncgt = (cgt2-cgt1);
    #else
        clock_gettime(CLOCK_REALTIME,&cgt2);
        ncgt = (double) (cgt2.tv_sec-cgt1.tv_sec)+
            (double) ((cgt2.tv_nsec-cgt1.tv_nsec)/(1.e+9));
    #endif

    // Imprimir resultados
    printf("------------------------------------\n\n");
    if (N < 10){
        printf("Tiempo: %11.9f\t Tamaño: %u\n", ncgt, N);
        printf("Matriz:\n\t");
        for (int i = 0; i < N; i++){
            for (int j = 0; j < N; j++)
                printf("%8.6f \t ", m[i][j]);
            printf("\n\t");
        }
        printf("\nVector:\n\t");
        for (int i = 0; i < N; i++)
            printf("%8.6f ", v1[i]);
        printf("\n\nVector resultado:\n\t");
        for (int i = 0; i < N; i++)
            printf("%8.6f ", v2[i]);
        printf("\n");
    } else {
        printf("Tiempo: %11.9f \t Tamaño: %u \t v2[0]: %8.6f \t v2[N-1]: %8.6f \n",ncgt, N, v2[0], v2[N-1]);
    }
    return(0);
}