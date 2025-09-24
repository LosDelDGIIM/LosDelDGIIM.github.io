#!/bin/bash

# Función para compilar un archivo con latexmk (silenciosa)
compilar_latex_silencioso() {
    local file="$1"
    local dir base
    dir="$(dirname "$file")"
    base="$(basename "$file")"

    (
        cd "$dir" || exit 1
        # stdout y stderr a /dev/null para evitar mensajes de archivos faltantes
        latexmk \
            -synctex=1 \
            -interaction=nonstopmode \
            -file-line-error \
            -pdf \
            -outdir="." \
            -shell-escape \
            "$base" \
            > /dev/null 2>&1
    )
}

# Función para compilar un archivo con latexmk
compilar_latex() {
    local file="$1"
    local error_log="$2"
    local dir base
    dir="$(dirname "$file")"
    base="$(basename "$file")"

    (
        cd "$dir" || exit 1
        # stdout a /dev/null, stderr queda en pantalla
        if ! latexmk \
            -synctex=1 \
            -interaction=nonstopmode \
            -file-line-error \
            -pdf \
            -outdir="." \
            -shell-escape \
            "$base" \
            > /dev/null; then
            # Si hay error y se proporcionó un archivo de log, añadir el archivo
            if [ -n "$error_log" ]; then
                echo "$file" >> "$error_log"
            fi
            return 1
        fi
    )
}

# Función para generar glosarios
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

# Función para limpiar carpetas _minted
clean_minted() {
    local file="$1"
    local dir base file_sin_ext
    dir="$(dirname "$file")"
    base="$(basename "$file")"
    file_sin_ext="${base%.tex}"

    (
        cd "$dir" || exit 1
        [ -d "_minted-$file_sin_ext" ] && rm -r "_minted-$file_sin_ext"
    )
}

# Función para eliminar archivos auxiliares generados por latexmk
limpiar_aux() {
    local file="$1"
    local dir base file_sin_ext
    dir="$(dirname "$file")"
    base="$(basename "$file")"
    file_sin_ext="${base%.tex}"

    (
        cd "$dir" || exit 1
        rm -f \
            "$file_sin_ext".aux \
            "$file_sin_ext".bbl \
            "$file_sin_ext".blg \
            "$file_sin_ext".idx \
            "$file_sin_ext".ind \
            "$file_sin_ext".lof \
            "$file_sin_ext".lot \
            "$file_sin_ext".out \
            "$file_sin_ext".toc \
            "$file_sin_ext".acn \
            "$file_sin_ext".acr \
            "$file_sin_ext".alg \
            "$file_sin_ext".glg \
            "$file_sin_ext".glo \
            "$file_sin_ext".gls \
            "$file_sin_ext".fls \
            "$file_sin_ext".log \
            "$file_sin_ext".fdb_latexmk \
            "$file_sin_ext".snm \
            "$file_sin_ext".synctex.gz \
            "$file_sin_ext".synctex.gz\(busy\) \
            "$file_sin_ext".vrb \
            "$file_sin_ext".ist \
            *.aux \
            *.cpt
    )
}

# Verificar si se proporcionó el archivo de errores como parámetro
ERROR_LOG="$1"

if [ -z "$ERROR_LOG" ]; then
    echo "Uso: $0 <archivo_errores.log>"
    echo "Ejemplo: $0 errores_compilacion.log"
    exit 1
fi

# Crear o limpiar el archivo de errores
> "$ERROR_LOG"

echo "Registrando errores en: $ERROR_LOG"

# Recorre todos los .tex con \begin{document}
find ../ -name '*.tex' -exec grep -l '\\begin{document}' {} + | sort | while read -r file; do
    if grep -q '\\printglossary' "$file"; then
        # Caso 1: contiene \begin{document} y \printglossary
        echo "Compilando con glosarios $file..."
        compilar_latex_silencioso "$file"  # Primera compilación silenciosa
        compilar_latex "$file" "$ERROR_LOG"
        make_glossaries "$file"
        compilar_latex "$file" "$ERROR_LOG"
    else
        # Caso 2: contiene \begin{document} pero NO \printglossary
        echo "Compilando $file..."
        compilar_latex_silencioso "$file"  # Primera compilación silenciosa
        compilar_latex "$file" "$ERROR_LOG"
    fi

    clean_minted "$file"
    limpiar_aux "$file"
done

# Mostrar resumen al final
if [ -s "$ERROR_LOG" ]; then
    echo ""
    echo "=== ARCHIVOS CON ERRORES ==="
    cat "$ERROR_LOG"
    echo ""
    echo "Total de archivos con errores: $(wc -l < "$ERROR_LOG")"
else
    echo ""
    echo "✓ Todos los archivos se compilaron correctamente"
fi