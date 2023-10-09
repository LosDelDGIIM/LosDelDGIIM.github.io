#!/bin/bash

# Verifica que se proporcionen tres argumentos
if [ $# -ne 3 ]; then
  echo "Uso: $0 test_init test_fin version"
  exit 1
fi

test_init="$1"
test_fin="$2"
version="$3"

# Bucle para ejecutar el código desde test_init hasta test_fin
for i in $(seq $test_init $test_fin); do
    gcc -x assembler-with-cpp -D TEST=$i -no-pie -g media$version.s -o media$version
    printf "__TEST%02d__%35s\n" $i "" | tr " " "-"
    ./media$version
    rm ./media$version
done
