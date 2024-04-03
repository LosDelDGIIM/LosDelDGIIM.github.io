/**
 * 
 Compilar con gcc –O2 –fopenmp HelloOMP.c –o HelloOMP
 * 
 */

#include <stdio.h>
#include <omp.h>

int main(void) {

#pragma omp parallel
  printf("(%d:!!!Hello world!!!)", 
           omp_get_thread_num());

return(0);

}