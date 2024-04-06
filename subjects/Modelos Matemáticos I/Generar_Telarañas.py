# Este script genera las coordenadas de los puntos de la telaraña de una función iterada en LaTeX.
# La función iterada es f(x) y punto inicial es x_0. El número de iteraciones es N.



# Definir la función f(x)
def f(x):
    return -x**3 + 3*x**2 -2*x + 1

# Valor inicial para x_0
x_0 = 0.5

# Lista para almacenar los puntos
solucion = []
solucion.append(x_0)

# Número de iteraciones
N = 4

for _ in range(N):
    x_n = solucion[-1]
    solucion.append(f(x_n))

for i in range(len(solucion) - 1):
    comando = "\draw[dashed, -stealth] "
    salida_1 = comando
    salida_1 += "(" + format(solucion[i], " 2.5f") + "," + format(solucion[i], " 2.5f") + ")" # Punto inicial en y=x
    salida_1 += " -- "
    salida_1 += "(" + format(solucion[i], " 2.5f") + "," + format(solucion[i+1], " 2.5f") + ")" # Punto imagen
    salida_1 += ";"

    salida_2 = comando
    salida_2 += "(" + format(solucion[i], " 2.5f") + "," + format(solucion[i+1], " 2.5f") + ")" # Punto imagen
    salida_2 += " -- "
    salida_2 += "(" + format(solucion[i+1], " 2.5f") + "," + format(solucion[i+1], " 2.5f") + ")" # Punto final en y=x
    salida_2 += ";"
    print (salida_1 + "\n" +  salida_2)

