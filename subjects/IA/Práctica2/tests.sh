#!/bin/bash

# Valores predeterminados
ejecutable="./practica2" # Por defecto
level=""

# Procesa los argumentos
while [[ $# -gt 0 ]]; do
    case "$1" in
        -SG)
            ejecutable="./practica2SG"
            shift
            ;;
        -n)
            if [[ -n "$2" && "$2" =~ ^[0-4]$ ]]; then
                level="$2"
                shift 2
            else
                echo "Error: Debes especificar un nivel válido (0, 1, 2, 3 o 4) después de -n."
                exit 1
            fi
            ;;
        *)
            echo "Uso: $0 [-SG] -n nivel"
            echo "  -SG: (opcional) Usar ./practica2SG en lugar de ./practica2"
            echo "  -n nivel: Nivel a ejecutar (0, 1, 2, 3 o 4)"
            exit 1
            ;;
    esac
done

# Comprueba que se haya especificado un nivel
if [[ -z "$level" ]]; then
    echo "Error: Debes especificar un nivel con -n."
    exit 1
fi

# Configuraciones a probar
tests_0=(
    "$ejecutable ./mapas/mapa30.map 0 0 8 4 2 14 17 0"
    "$ejecutable ./mapas/mapa30.map 0 0 17 5 0 17 17 0"
    "$ejecutable ./mapas/mapa30.map 0 0 24 7 2 17 17 0"
    "$ejecutable ./mapas/mapa30.map 0 0 24 10 2 17 17 0"
    "$ejecutable ./mapas/mapa30.map 0 0 16 9 2 16 14 6"
    "$ejecutable ./mapas/mapa75.map 0 0 63 29 6 59 68 1"
    "$ejecutable ./mapas/pruebaCiclo.map 0 0 13 3 6 5 12 6"               # Evitar Ciclos
    "$ejecutable ./mapas/pruebaDosUnicos_Zapas.map 0 0 24 10 2 17 17 0"   # Permitir ciclos si ha conseguido zapatillas
    "$ejecutable ./mapas/pruebaDosUnicos_Choque.map 0 0 16 9 2 16 14 6"   # Permitir ciclos si ha habido un choque
    "$ejecutable ./mapas/pruebaDosUnicos_Choque.map 0 0 15 18 2 17 17 0"
    "$ejecutable ./mapas/mapa75.map 0 0 8 5 2 17 17 0 3 3 0"
    "$ejecutable ./mapas/mapa100.map 0 0 70 38 6 79 91 1 0 3 3 0"
)
tests_1=(
    "$ejecutable ./mapas/mapa30.map 0 1 6 3 0 21 15 2"
)
for test in "${tests_0[@]}"; do
    test_1=$(echo "$test" | awk '{ $4=1; print }')
    tests_1+=("$test_1")
done

tests_2=(
    "$ejecutable mapas/mapa30.map 1 2 8 13 0 11 18 0 18 12 0"
)
tests_3=(
    "$ejecutable mapas/mapa30.map 1 3 8 13 0 11 18 0 18 12 0"
)
tests_4=(
    "$ejecutable mapas/mapa30.map 1 4 8 13 0 11 18 0 18 12 1"
)

# Ejecuta los tests para el nivel especificado
for test in $(eval echo "\${!tests_${level}[@]}"); do
    echo "Ejecutando test: $(eval echo "\${tests_${level}[$test]}")"
    # Ejecuta el test
    eval $(eval echo "\${tests_${level}[$test]}")
    echo "-----------------------------------------------------"
done

echo "Todos los tests han finalizado."