/**
 * 
 Código para multimplicación secuencial matriz cuadrada por vector: v2 = m * v1 pmv-secuencial.c
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
#endif

/**
 * @file  pmv-secuencial.c  
 * @brief multimplicación secuencial matriz cuadrada por vector: v2 = m * v1
 * 
 * @param int n=atoi(argv[1])  número de componentes de los vectores y número de filas y columnas de la matriz
 * @return 0 upon exit success (print tiempo de cálculo de la multiplicación, longitud vectores y resultados (primer y último componente del resultado para longitudes mayores que 9))
 *  
 * **Compilación**
 * @code
	gcc  -O2  pmv-secuencial.c -o pmv-secuencial -lrt
    (-lrt: real time library, es posible que no sea necesario usar -lrt)
 * @endcode
* **Generar ensamblador**
 * @code
 * gcc  -O2 -S pmv-secuencial.c -lrt
 * @endcode
 *  **Ejecución**
 * ~~~~~~~~~~~~~~~~~~~~~{.c}
 * pmv-secuencial 8    (para 8 componentes en los vectores)
 * ~~~~~~~~~~~~~~~~~~~~~
 * 
**/
int main(int argc, char** argv){
    unsigned int N;
    
    // La orden del tiempo de OMP devuelve double,
    // pero la función clock_gettime() devuelve una estructura struct timespec.
    double ncgt; //para tiempo de ejecución
    #ifdef _OPENMP
        double cgt1,cgt2;
    #else
        struct timespec cgt1,cgt2;
    #endif

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

    // Inicializar vectores
    #pragma omp parallel for
    for (int i = 0; i < N; i++){
        v1[i] = 0.1*i;
        v2[i] = 0;
    }
    
    // Inicializar matriz    
    #pragma omp parallel // Para que solo cree y destruya los hilos una vez
    for (int i = 0; i < N; i++){
        
        #pragma omp for    // Paraleliza recorrido por columnas
        for (int j = 0; j < N; j++)
            m[i][j] = i*N+j;
    }


    // Calcular v2 = m * v1
    // Medida de tiempo inicial
    #ifdef _OPENMP
        cgt1 = omp_get_wtime();
    #else
        clock_gettime(CLOCK_REALTIME,&cgt1);
    #endif


    
    #pragma omp parallel // Para que solo crea y destruya los hilos una vez
    for(int i = 0; i < N; i++){
        double suma_local = 0;

        #pragma omp for    // Paraleliza recorrido por columnas
        for (int j = 0; j < N; j++)
            suma_local += m[i][j] * v1[j];
        
        #pragma omp atomic
        v2[i] += suma_local;
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
    if (N < 10){
        printf("Tiempo: %11.9f\t Tamaño: %u\n", ncgt, N);
        printf("Matriz:\n\t");
        for (int i = 0; i < N; i++){
            for (int j = 0; j < N; j++)
                printf("%8.6f\t ", m[i][j]);
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