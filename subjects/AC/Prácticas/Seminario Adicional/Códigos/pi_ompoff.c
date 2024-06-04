/**
 * 
PI paralelo con integración numérica empleando coprocesadores.
 * 
 */
#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <math.h>
/**
 * @file  pi_ompoff.c 
 * @brief PI paralelo con integración numérica, área de rectángulos
 * @author Arturo Olivares Martos
 *  
 * **Compilación atcgrid4 para GPU**
 * @code
 *  srun -pac4 -Aac nvc -O2 -openmp -mp=gpu pi_ompoff.c -o pi_ompoff_GPU
 * @endcode
 * 
 *  **Ejecución en atcgrid4**
 * ~~~~~~~~~~~~~~~~~~~~~
 * srun -pac4 -Aac pi_ompoff_GPU  10000000    (10000000 intervalos de integración)
 * ~~~~~~~~~~~~~~~~~~~~~
 * 
*/
int main(int argc, char **argv)
{
  register double width;
  double sum;
  register int intervals; 
    
  //Los procesos calculan PI en paralelo
  if (argc<2) {printf("Falta número de intevalos");exit(-1);}
  intervals=atoi(argv[1]);  
  if (intervals<1) {intervals=1E6; printf("Intervalos=%d",intervals);}
  width = 1.0 / intervals;
  sum = 0;


  double t0 = omp_get_wtime();

  // Entrada de datos al coprocesador
  #pragma omp target enter data map(to: intervals, width, sum)

  double t1 = omp_get_wtime();


  // Cálculo de PI en el coprocesador
  #pragma omp target
  {
      #pragma omp teams distribute parallel for reduction(+:sum)
      for (int i = 0; i < intervals; i++) {
          register double x = (i + 0.5) * width;
          sum += 4.0 / (1.0 + x * x);
      }
      
      sum *= width;
  }

  double t2 = omp_get_wtime();

  // Salida de datos del coprocesador
  #pragma omp target exit data map(delete: intervals, width) map(from: sum)

  double t3 = omp_get_wtime();

  double diferencia = fabs(sum - M_PI);
  double tiempo_calculo = t2 - t1;
  double tiempo_transferencias = t3 - t2 + t1 - t0;

  printf("Iteraciones:\t%d\t. PI Calculado:\t%26.24f\t. Tiempo:\t%8.6f\n", intervals,sum,t3-t0);
  printf("Diferencia con PI:\t%26.24f\n", diferencia);
  printf("Tiempo de cálculo:\t%8.6f. Tiempo de transferencias:\t%8.6f\n", tiempo_calculo, tiempo_transferencias);

  // Cada uno de los tiempos, especificando cada directiva
  printf("- Target enter data:\t%8.6f\n", t1 - t0);
  printf("- Target teams distribute parallel for:\t%8.6f\n", t2 - t1);
  printf("- Target exit data:\t%8.6f\n", t3 - t2);

  return(0);
}
