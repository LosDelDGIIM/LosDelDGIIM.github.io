#!/bin/bash

# Tests para cada uno de los niveles. El nivel se pedirá como argumento al script.
# Si no se pasa ningún argumento, se probarán todos los niveles.
# Los posibles niveles son: 0, 1, 2, 3, 4

# Configuraciones a probar
tests_0=(
    "./practica2SG ./mapas/mapa30.map 0 0 8 4 2 14 17 0"
    "./practica2SG ./mapas/mapa30.map 0 0 17 5 0 17 17 0"
    "./practica2SG ./mapas/mapa30.map 0 0 24 7 2 17 17 0"
    "./practica2SG ./mapas/mapa30.map 0 0 24 10 2 17 17 0"
    "./practica2SG ./mapas/mapa30.map 0 0 16 9 2 16 14 6"
    "./practica2SG ./mapas/mapa75.map 0 0 63 29 6 59 68 1"
    "./practica2SG ./mapas/pruebaCiclo.map 0 0 13 3 6 5 12 6"               # Evitar Ciclos
    "./practica2SG ./mapas/pruebaDosUnicos_Zapas.map 0 0 24 10 2 17 17 0"   # Permitir ciclos si ha conseguido zapatillas
    "./practica2SG ./mapas/pruebaDosUnicos_Choque.map 0 0 16 9 2 16 14 6"   # Permitir ciclos si ha habido un choque
)
tests_1=(
    "./practica2SG ./mapas/mapa30.map 0 1 6 3 0 21 15 2"
)
# A test_1, añado todos los tests_0 pero cambiando el nivel de 0 a 1
for test in "${tests_0[@]}"; do
    test_1=$(echo "$test" | awk '{ $4=1; print }')
    tests_1+=("$test_1")
done

tests_2=(
    "./practica2SG mapas/mapa30.map 1 2 8 13 0 11 18 0 18 12 0"
)
tests_3=(
    "./practica2SG mapas/mapa30.map 1 3 8 13 0 11 18 0 18 12 0"
)
tests_4=(
    "./practica2SG mapas/mapa30.map 1 4 8 13 0 11 18 0 18 12 1"
)




# Se comprueba que se ha pasado un argumento
if [ $# -eq 0 ]; then
    echo "No se ha pasado ningún argumento. Se probarán todos los niveles."
    levels=(0 1 2 3 4)
else
    levels=("$@")
fi

# Se comprueba que los argumentos son válidos
for level in "${levels[@]}"; do
    if ! [[ "$level" =~ ^[0-4]$ ]]; then
        echo "El argumento $level no es válido. Debe ser un número entre 0 y 4."
        exit 1
    fi
done

# Ejecuta los tests para cada nivel
for level in "${levels[@]}"; do
    for test in $(eval echo "\${!tests_${level}[@]}"); do
        echo "Ejecutando test: $(eval echo "\${tests_${level}[$test]}")"
        # Ejecuta el test
        eval $(eval echo "\${tests_${level}[$test]}")
        echo "-----------------------------------------------------"
    done
done
echo "Todos los tests han finalizado."
