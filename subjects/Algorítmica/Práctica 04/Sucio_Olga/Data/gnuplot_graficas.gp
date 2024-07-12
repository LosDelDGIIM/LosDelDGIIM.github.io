#!/bin/gnuplot

# <numero de entradas> <datos1> <nombre_datos1> 

decision=ARG1   	# Si numero de entradas es == 1 entonces solo hace regresion, si es 2 hace la comparacion
datos1=ARG2
titulo1=ARG3

set xlabel 'Nº ciudades (n)'		# Titulo del eje x
set ylabel 'Nodos generados'

if (ARG1 == 1) {		# Si no comparar

	set terminal 'png'
	
    set output 'salidaSoloPuntos.png'
	plot datos1 title "TSP V2" with points
	set output 'salidaSoloLineas.png'
	plot datos1 title "TSP V2" with lines
    
} else {
    
    set terminal 'png'

    set output 'CurvaAjustadaFactorial.png'
    f(x) = a*gamma(b*(x+1))
	fit f(x) datos1 via a,b
	plot datos1 title "TSP V2", f(x) title 'Curva ajustada'

    set output 'CurvaAjustadaExponencial.png'
    f(x)=a*exp(b*x)
	fit f(x) datos1 via a,b
	plot datos1 title "TSP V2", f(x) title 'Curva ajustada'

    set output 'CurvaAjustadaCubica.png'
    f(x)=a*x*x*x
	fit f(x) datos1 via a
	plot datos1 title "TSP V2", f(x) title 'Curva ajustada'

    set output 'CurvaAjustadaCuadratica.png'
    f(x)=a*x*x
	fit f(x) datos1 via a
	plot datos1 title "TSP V2", f(x) title 'Curva ajustada'
}

