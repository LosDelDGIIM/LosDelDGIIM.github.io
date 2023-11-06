#!/bin/bash

# Verifica que se proporcionen 0 argumentos
if [ $# -ne 0 ]; then
  echo "Uso: $0"
  exit 1
fi

# Bucle para ejecutar todos los test en todos los niveles de optimización
for i in 0 g 1 2 3; do
  printf "__OPTIM%1c__%70s\n" $i "" | tr " " "="

  gcc -D TEST=0 -no-pie -g -O$i popcount.c -o popcount
  
  for j in $(seq 0 10); do
    echo "Ej $j;" ; ./popcount
  done | pr -11 -l 22 -w 80

  rm ./popcount
done
