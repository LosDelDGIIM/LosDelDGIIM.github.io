from scipy.optimize import bisect

# Este script genera las coordenadas de los puntos de la telaraña del Modelo de la Oferta y la Demanda en LaTeX.
# La función de la oferta es O(x) y la función de la demanda es D(x). El punto inicial es p_0.

# Definir la función de la oferta O(x)
def O(x):
    return 1+ x**2

# Definir la función de la demanda D(x)
def D(x):
    return 3-2*x

# Valor inicial para p_0
p_0 = 1

# Lista para almacenar los puntos
solucion = []
solucion.append((p_0, 0))

# Número de iteraciones
N = 4

for _ in range(N):
    p_n = solucion[-1][0]
    
    o = O(p_n)
    d = bisect(lambda x: D(x) - o, -5, 5) # Resuelve D(x)=o

    solucion.append((p_n, o))
    solucion.append((d, o))

for i in range(len(solucion) - 1):
    comando = "\draw[dashed, -stealth] "
    salida = comando
    salida += "(" + format(solucion[i][0], " 2.5f") + "," + format(solucion[i][1], " 2.5f") + ")"
    salida += " -- "
    salida += "(" + format(solucion[i+1][0], " 2.5f") + "," + format(solucion[i+1][1], " 2.5f") + ")"
    salida += ";"

    print (salida)

