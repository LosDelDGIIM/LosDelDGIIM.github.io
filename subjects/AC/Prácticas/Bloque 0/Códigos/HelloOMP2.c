/**
 * 
 Compilar con gcc –O2 –fopenmp HelloOMP.c –o HelloOMP
 * 
 */

#include <stdio.h>
#include <omp.h>

int main(void) {

  #pragma omp parallel
  { // Incluir estas llaves es necesario para que todo se ejecute en paralelo.
    printf("(%d:!!!Hello)", 
            omp_get_thread_num());

    printf("(%d:world!!!)", 
            omp_get_thread_num());
  }

  return(0);

}