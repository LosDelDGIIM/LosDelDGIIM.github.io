#!/bin/bash

# Script para compilar archivos LaTeX en un proyecto grande
# Maneja glosarios, errores y limpieza de archivos auxiliares
# Uso: ./script_todos.sh errores_compilacion.log [lista_archivos.txt]
# Si no se proporciona lista_archivos.txt, compila todos los .tex con \begin{document}
# Requiere: latexmk, makeglossaries

# Funciones (idénticas a la versión anterior)
compilar_latex_silencioso() {
    local file="$1"
    local dir base
    dir="$(dirname "$file")"
    base="$(basename "$file")"

    (
        cd "$dir" || exit 1
        latexmk -synctex=1 -interaction=nonstopmode -file-line-error -pdf -outdir="." -shell-escape "$base" > /dev/null 2>&1
    )
}

compilar_latex() {
    local file="$1"
    local error_log="$2"
    local dir base exit_code
    dir="$(dirname "$file")"
    base="$(basename "$file")"

    (
        cd "$dir" || exit 1
        latexmk -synctex=1 -interaction=nonstopmode -file-line-error -pdf -outdir="." -shell-escape "$base" > /dev/null
    )
    
    # Capturar el código de salida del subshell
    exit_code=$?
    
    if [ $exit_code -ne 0 ]; then
        [ -n "$error_log" ] && echo "$file" >> "$error_log"
        return 1
    fi
    
    return 0
}

make_glossaries() {
    local file="$1"
    local dir base file_sin_ext
    dir="$(dirname "$file")"
    base="$(basename "$file")"
    file_sin_ext="${base%.tex}"

    (
        cd "$dir" || exit 1
        makeglossaries "$file_sin_ext" > /dev/null
    )
}

clean_minted() {
    local file="$1"
    local dir base file_sin_ext
    dir="$(dirname "$file")"
    base="$(basename "$file")"
    file_sin_ext="${base%.tex}"

    (
        cd "$dir" || exit 1
        [ -d "_minted-$file_sin_ext" ] && rm -rf "_minted-$file_sin_ext"
    )
}

limpiar_aux() {
    local file="$1"
    local dir base file_sin_ext
    dir="$(dirname "$file")"
    base="$(basename "$file")"
    file_sin_ext="${base%.tex}"

    (
        cd "$dir" || exit 1
        rm -f "$file_sin_ext".{aux,bbl,blg,idx,ind,lof,lot,out,toc,acn,acr,alg,glg,glo,gls,fls,log,fdb_latexmk,snm,synctex.gz,vrb,ist} *.aux *.cpt
    )
}

# Parámetros
ERROR_LOG="$1"
LISTA_ARCHIVOS="$2"

if [ -z "$ERROR_LOG" ]; then
    echo "Uso: $0 <archivo_errores.log> [archivo_lista.txt]"
    echo "Ejemplo: $0 errores_compilacion.log"
    echo "         $0 errores_compilacion.log lista_archivos.txt"
    exit 1
fi

> "$ERROR_LOG"
echo "Registrando errores en: $ERROR_LOG"

# Determinar archivos a compilar
if [ -n "$LISTA_ARCHIVOS" ]; then
    if [ ! -f "$LISTA_ARCHIVOS" ]; then
        echo "Archivo de lista '$LISTA_ARCHIVOS' no encontrado."
        exit 1
    fi
    ARCHIVOS=$(grep -E '\.tex$' "$LISTA_ARCHIVOS" | sort)
else
    # Buscar todos los .tex con \begin{document}
    ARCHIVOS=$(find ../ -name '*.tex' -exec grep -l '\\begin{document}' {} + | sort)
fi

# Compilación
echo "$ARCHIVOS" | while read -r file; do
    [ -z "$file" ] && continue

    if grep -q '\\printglossary' "$file"; then
        echo "Compilando con glosarios $file..."
        compilar_latex_silencioso "$file"
        compilar_latex "$file" "$ERROR_LOG"
        make_glossaries "$file"
        compilar_latex "$file" "$ERROR_LOG"
    else
        echo "Compilando $file..."
        compilar_latex_silencioso "$file"
        compilar_latex "$file" "$ERROR_LOG"
    fi

    clean_minted "$file"
    limpiar_aux "$file"
done

# Resumen final
if [ -s "$ERROR_LOG" ]; then
    echo -e "\n=== ARCHIVOS CON ERRORES ==="
    cat "$ERROR_LOG"
    echo "Total de archivos con errores: $(wc -l < "$ERROR_LOG")"
else
    echo -e "\n✓ Todos los archivos se compilaron correctamente"
fi
