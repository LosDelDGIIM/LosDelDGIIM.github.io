# Relación Tema 1.

## Ejercicio 1.1
En el código de prueba (benchmark) que ejecuta un procesador no segmentado que funciona a
300 MHz, hay un 20% de instrucciones LOAD que necesitan 4 ciclos, un 10% de instrucciones STORE que
necesitan 3 ciclos, un 25% de instrucciones con operaciones de enteros que necesitan 6 ciclos, un 15% de
instrucciones con operandos en coma flotante que necesitan 8 ciclos por instrucción, y un 30% de
instrucciones de salto que necesitan 3 ciclos. (a) ¿Cuál es la ganancia que se puede obtener por reducción a
3 ciclos de las instrucciones con enteros? y (b) ¿cuál es la ganancia que se puede obtener por reducción a 3
ciclos de las instrucciones en coma flotante?

## Ejercicio 1.2
Un circuito que implementaba una operación en un tiempo de Top=450 ns se ha segmentado
mediante un cauce lineal con cuatro etapas de duración T1=100 ns, T2=125 ns, T3=125 ns y T4=100 ns
respectivamente, separadas por un registro de acoplo que introduce un retardo de 25 ns.
- ¿Cuál es la máxima ganancia de velocidad posible? ¿Cuál es la productividad máxima del cauce?

Tenemos que el ciclo de reloj es de $T_c = 125ns + 25ns = 150ns$. La ganancia de velocidad es:
$$
S(N) = \frac{T^b(N)}{T^s(N)} = \frac{N\cdot T_R}{TLI + (N-1)T_c}
= \frac{N\cdot T_R}{4\cdot T_c + (N-1)T_c}
$$
donde el 4 se debe a que es el número de etapas del cauce.

La ganancia máxima es:
$$
S(N\ggg) = \lim_{N\to\infty} S(N) = \lim_{N\to\infty} \frac{N\cdot T_R}{4\cdot T_c + (N-1)T_c} = \frac{T_R}{T_c}
$$

- ¿A partir de qué
número de operaciones ejecutadas se consigue una productividad igual al 90% de la productividad máxima?

## Ejercicio 1.3
En un procesador sin segmentación de cauce, determine cuál de estas dos alternativas para
realizar un salto condicional es mejor:
- ALT1: Una instrucción COMPARE actualiza un código de condición y es seguida por una instrucción BRANCH
que comprueba esa condición. Se usan dos intrucciones.
- ALT2: Una sola instrucción incluye la funcionalidad de las instrucciones COMPARE y BRANCH. Se usa una
única instrucción.
Hay que tener en cuenta que hay un 20% de instrucciones BRANCH para ALT1 en el conjunto de programas
de prueba; que las instrucciones BRANCH en ALT1 y COMPARE+BRANCH en ALT2 necesitan 4 ciclos mientras
que todas las demás necesitan sólo 3; y que el ciclo de reloj de la ALT1 es un 25% menor que el de la ALT2,
dado que en éste caso la mayor funcionalidad de la instrucción COMPARE+BRANCH ocasiona una mayor
complejidad en el procesador


## Ejercicio 1.4
¿Qué ocurriría en el problema anterior si el ciclo de reloj fuese únicamente un 10% mayor para
la ALT2?

## Ejercicio 1.5
Considere un procesador no segmentado con una arquitectura de tipo LOAD/STORE en la que las
operaciones sólo utilizan como operandos registros de la CPU. Para un conjunto de programas
representativos de su actividad se tiene que el 43% de las instrucciones son operaciones con la ALU (3 CPI),
el 21% LOADs (4 CPI), el 12% STOREs (4 CPI) y el 24% BRANCHs (4 CPI).
Se ha podido comprobar que un 25% de las operaciones con la ALU utilizan operandos en registros que no se
vuelven a utilizar. Compruebe si mejorarían las prestaciones si, para sustituir ese 25% de operaciones, se
añaden instrucciones con un dato en un registro y otro en memoria. Tengan en cuenta en la comprobación que para estas nuevas instrucciones el valor de CPI es 4 y que añadirlas ocasiona un incremento de un ciclo
en el CPI de los BRANCHs, pero no afectan al ciclo de reloj.

## Ejercicio 1.6
Se ha diseñado un compilador para la máquina LOAD/STORE del problema anterior. Ese
compilador puede reducir en un 50% el número de operaciones con la ALU, pero no reduce el número de
LOADs, STOREs, y BRANCHs. Suponiendo que la frecuencia de reloj es de 50 Mhz. ¿Cuál es el número de
MIPS y el tiempo de ejecución que se consigue con el código optimizado? Compárelos con los
correspondientes del código no optimizado.

## Ejercicio 1.7
. En un programa que se ejecutan en un procesador no segmentado que funciona a 100 MHz, hay
un 20% de instrucciones LOAD que necesitan 4 ciclos, un 15% de instrucciones STORE que necesitan 3 ciclos,
un 40% de instrucciones con operaciones en la ALU que necesitan 6 ciclos, y un 25% de instrucciones de
salto que necesitan 3 ciclos. (a) Si en las instrucciones que usan la ALU el tiempo en la ALU supone 4 ciclos,
determine cuál es la máxima ganancia que se puede obtener si se mejora el diseño de la ALU de forma que
se reduce su tiempo de ejecución a la mitad de ciclos. (b) Con qué porcentaje de instrucciones con
operaciones en la ALU se podría haber obtenido en los cálculos del apartado (a) una ganancia mayor que 2?
Razone su respuesta.

## Ejercicio 1.8
Suponga que en los programas que constituyen la carga de trabajo habitual de un procesador las
instrucciones de coma flotante consumen un promedio del 13% del tiempo del procesador.
(a) Ha aparecido en el mercado una nueva versión del procesador en la que la única mejora con respecto a la
versión anterior es una nueva unidad de coma flotante que permite reducir el tiempo de las instrucciones de
coma flotante a tres cuartas partes del tiempo que consumían antes. ¿Cuál es la máxima ganancia de
velocidad que puede esperarse en los programas que constituyen la carga de trabajo si se utiliza la nueva
versión del procesador?
(b) ¿Cuál es la máxima ganancia de velocidad con respecto a la versión inicial del procesador que, en
promedio, puede esperarse en los programas debido a mejoras en la velocidad de las operaciones en coma
flotante?
(c) ¿Cuál debería ser el porcentaje de tiempo de cálculo con datos en coma flotante en los programas para
esperar una ganancia máxima de 4 en lugar de la obtenida en el apartado (b)?
(d) ¿Cuánto debería reducirse el tiempo de las operaciones en coma flotante con respecto a la situación
inicial para que la ganancia máxima sea 2 suponiendo que en la versión inicial el porcetaje de tiempo de
cálculo con como flotante es el obtenido en (c)?