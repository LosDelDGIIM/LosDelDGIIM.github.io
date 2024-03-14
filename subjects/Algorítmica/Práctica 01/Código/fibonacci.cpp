/**
   @file Cálculo de la sucesión de Fibonacci
*/

   
#include <iostream>
using namespace std;
#include <ctime>
#include <chrono>
using namespace std::chrono;


/**
   @brief Calcula el término n-ésimo de la sucesión de Fibonacci.

   @param n: número de orden del término buscado. n >= 1.

   @return: término n-ésimo de la sucesión de Fibonacci.
*/
int fibo(int n)
{
  if (n < 2)
    return 1;
  else
    return fibo(n-1) + fibo(n-2);
}


int main(int argc, char** argv)
{
    int n = strtol(argv[1], NULL, 10);
    int f;

  high_resolution_clock::time_point tantes, tdespues;
  duration<double> transcurrido;

  tantes = high_resolution_clock::now();
  f = fibo(n);
  tdespues = high_resolution_clock::now();
  transcurrido = duration_cast<duration<double>>(tdespues - tantes);
  cout << n << " " << transcurrido.count() << endl;


  return 0;
}
