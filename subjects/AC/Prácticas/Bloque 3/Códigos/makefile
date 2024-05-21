# Makefile

# Definición del compilador y las opciones de compilación
CXX := g++
CXXFLAGS := -fopenmp -O2	# -D DEBUG

# Objetivo predeterminado (compilar el archivo proporcionado)
.DEFAULT_GOAL := compile

# Regla para compilar el archivo CPP especificado
compile: $(FILE)
	$(CXX) $(CXXFLAGS) -o $(basename $(FILE)) $(FILE)

# Limpieza de archivos generados.
# Se eliminan todos los archivos ejecutables que no sean scripts de bash o archivos de código fuente.
clean:
	find . -type f -executable ! -name "*.cpp" ! -name "*.sh" -exec rm {} \;