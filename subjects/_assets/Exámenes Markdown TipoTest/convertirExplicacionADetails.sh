#!/bin/bash

# Verificar si se pasó el archivo como argumento
if [ -z "$1" ]; then
    echo "Uso: $0 <archivo_markdown>"
    exit 1
fi

archivo_entrada="$1"

# Verificar si el archivo realmente existe
if [ ! -f "$archivo_entrada" ]; then
    echo "Error: El archivo '$archivo_entrada' no existe."
    exit 1
fi

# Crear un archivo temporal seguro
archivo_temporal=$(mktemp)

# Leer el archivo línea por línea y escribir en el temporal
while IFS= read -r linea || [ -n "$linea" ]; do
    # Eliminar espacios en blanco al principio para la validación
    linea_limpia=$(echo "$linea" | xargs)

    # Comprobar si la línea empieza por Explicación
    if [[ "$linea_limpia" =~ ^[Ee]xplicaci[oó]n:[[:space:]]*(.*) ]]; then
        contenido_despues="${BASH_REMATCH[1]}"
        
        echo "<details>" >> "$archivo_temporal"
        echo "  <summary>Respuesta</summary>" >> "$archivo_temporal"
        echo "  <p>${contenido_despues}</p>" >> "$archivo_temporal"
        echo "</details>" >> "$archivo_temporal"
    else
        # Si no empieza por Explicación, guardamos la línea original intacta
        echo "$linea" >> "$archivo_temporal"
    fi
done < "$archivo_entrada"

# Sobrescribir el archivo original con el contenido modificado del temporal
mv "$archivo_temporal" "$archivo_entrada"

echo "¡Archivo '$archivo_entrada' modificado correctamente!"