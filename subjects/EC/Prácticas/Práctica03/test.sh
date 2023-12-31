#!/bin/bash

# Verifica que se proporcionen 0 argumentos
if [ $# -ne 0 ]; then
  echo "Uso: $0"
  exit 1
fi

# Bucle para ejecutar todos los test en todos los niveles de optimización
for i in 0 g 1 2 3; do
  printf "__OPTIM%1c__%70s\n" $i "" | tr " " "="
  for j in $(seq 1 4); do
    printf "__TEST%02d__%70s\n" $j "" | tr " " "-"

    gcc -D TEST=$j -no-pie -g -O$i popcount.c -o popcount
    ./popcount
    rm ./popcount
  done
done
