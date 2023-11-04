#!/bin/bash

# Verifica que se proporcionen tres argumentos
if [ $# -ne 2 ]; then
  echo "Uso: $0 test_init test_fin"
  exit 1
fi

test_init="$1"
test_fin="$2"

# Bucle para ejecutar el código desde test_init hasta test_fin
for i in $(seq $test_init $test_fin); do
    gcc -D TEST=$i -no-pie -g popcount.c -o popcount
    printf "__TEST%02d__%70s\n" $i "" | tr " " "-"
    ./popcount
    rm ./popcount
done
