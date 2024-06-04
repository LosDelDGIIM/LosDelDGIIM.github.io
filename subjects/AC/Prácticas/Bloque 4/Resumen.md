# Arquitectura de Computadores. Sesión IV de Prácticas.

**Autor:** José Juan Urrutia Milán
***

- **Asignatura:** Arquitectura de Computadores.  
- **Curso Académico:** 2023-24.
- **Grado:** Doble Grado en Ingeniería Informática y Matemáticas.
- **Profesor:** Mancia Anguita López.
- **Descripción:** Resúmen de la Sesión IV de Prácticas.

# Introducción
En esta sesión aprenderemos a optimizar los códigos de nuestro programas, aprovechando las arquitecturas de los computadores en los que ejecutaremos los códigos. Como normas generales:
- Se recomienda no optimizar los códigos al final, lo que dificulta esta labor, sino ir optimizando conforme se programa.
- Es un error no programar sin tener en cuenta la arquitectura, ya que genera códigos muy ineficientes cuyos tiempos pueden reducirse fácilmente pensando un poco en la arquitectura.
- No se debe reducir el tiempo de ejecución eliminando funcionalidades del programa.
- A la hora de optimizar, debemos fijarnos en la parte del código que más tiempo suponga en la ejecución del programa, eliminando cuellos de botella.
- No es necesario bajar a código ensamblador para optimizar, aunque a veces es la única opción.
  
Hay optimizaciones con las que veremos mejoras en todos los núcleos de procesamiento actuales, por tener características comunes a tener en cuenta (por ejemplo, todas las CPUs actuales tienen varias ALUs).  
Además, hay características propias de implementaciones concretas que si se tienen en cuenta podemos reducir tiempos de ejecución.  
  
### Conocer gcc
Los compiladores introducen además varias opciones de compilación con optimización, que realizan las optimizaciones de forma automática, teniendo en cuenta partes del hardware que suelen ser comunes a todos los procesadores actuales.  
Por ejemplo, `gcc` cuenta con las opciones de optimización `-O0` (no optimiza nada), `-O1`, `-O2` y `-O3` para tiempo (se encuentran en orden creciente de número de actualizaciones), además de `-Os` para espacio, para que el programa a ejecutar ocupe el menor espacio posible.  
  
La opción de compilación con optimización que recomendamos usar es `-O2`, que suele dar los mejores tiempos de ejecución.  
`-O3` cuenta con varias funcionalidades que todavía no están bien depuradas (las cuales pueden provocar errores a la hora de compilar los programas). Cuando una funcionalidad de optimización está depurada y lleva tiempo en uso, suele pasarse a `-O2`.  
Puede suceder que el tiempo con `-O3` aumente en relación a `-O2`, ya que aunque suele intentar realizar mejores optimizaciones, como ya se ha dicho no está del todo depurado.  
  
Además, la opción `-O3` genera instrucciones vectoriales (las reconoceremos por acabar con el sufijo `p`, o `pd` en el caso de instrucciones vectoriales para `double`). Las instrucciones con el sufijo `sd` son instrucciones escalares.  
Con la opción `-O0` se optimiza poco, por lo que obtendremos códigos largos con grandes tiempos de ejecución.  
  
***
A continuación, enumeramos una serie de estrategias a realizar con la finalidad de generar códigos con menores tiempos de ejecución, aprovechando las características de las arquitecturas actuales. Posiblemente se conozcan ya otras estrategias que también consigan este propósito, aquí simplemente describimos los conocimientos que nos aporta esta práctica. Las clasificamos en tres categorías:

# Optimización de la ejecución
## Reducción de fuerza
Muchas veces usamos operaciones sobre nuestros datos de forma natural pero que podrían realizarse de formas más rápidas (empleando menos ciclos) con otro tipo de operaciones que nos proporcionan el mismo resultado.  
  
Vemos algunos ejemplos en los que se aplica esta técnica:

### Sustituir divisiones por multiplicaciones
Si por ejemplo en un bucle tenemos el siguiente código:
```c
for(int i = 0; i < n; i++){
    a[i] = i / n;
}
```
En vez de realizar `n` veces una división (tarda entre 10 y 40 ciclos, dependiendo de la arquitectura), podemos realizar primero la división y luego hacer `n` multiplicaciones (tarda entre 1 y 4 ciclos), con lo que obtendremos unos mejores tiempos con el siguiente código:
```c
int b = 1 / n;
for(int i = 0; i < n; i++){
    a[i] = i * b;
}
```

### Sustituir multiplicaciones por shifts
Si queremos realizar multiplicaciones, siempre será más eficiente realizar operaciones de shift, que ocupan menos ciclos (entre 1 y 2). Por ejemplo, en vez de ejecutar:
```c
a = b * 10;
```
Podemos aplicar que `b * 10 = b * (2 + 8) = b * 2 + b * 8` y aprovechar las multiplicaciones por potencias de 2 para realizar shifts en vez de multiplicaciones.

### Sustituir operaciones aritméticas por leaq
Hablamos ya de una optimización que sólo se puede realizar a nivel de ensamblador, y es que podemos aprovechar la unidad artimético-lógica de cálculo de direcciones de memoria para realizar cálculos, en lugar de una ALU del procesador, donde las instrucciones pueden tardar más.  
Además, de esta forma podemos llegar a emitir dos instrucciones de cálculo a la vez: una que se realizará en la ALU y otra en la unidad de cálculo de direcciones de memoria.  
  
En el ejemplo anterior:
```asm
lea ecx, [eax + eax]    ; ecx <-- 2eax
lea eax, [ecx + eax*8]  ; eax <-- 2eax + 8eax = 10eax
```

## Desenrollado de bucles
Permite aprovechar la productividad de las unidades reduciendo latencias producidas por dependencias RAW.
Por ejemplo, en el siguiente código:
```c
int i, float tmp = 0.0;
for(i = 0; i < ARR; i++){
    tmp += a[i] * b[i];
}
return tmp;
```
Tenemos una dependencia RAW en cada iteración (varias operaciones que escriben en `tmp`). Por lo que antes de escribir en `tmp` debemos esperar a que termine la multiplicación (puede llegar a tardar 4 ciclos) anterior, por lo que nuestro bucle está siendo afectado por la latencia de la multiplicación.  
Sin embargo, podemos reducir tiempos aprovechando la estructura segmentada del procesador, usando desenrollado de bucle: sustituir el bucle por otro en el que cada iteración son varias del original.  
  
Suponiendo que `ARR % 4 = 0` (si no, debemos añadir, tras dividir todas las veces posibles entre 4, tantas operaciones como el resto `ARR % 4`), realizamos un desenrollado de 4:
```c
int i, float tmp0 = 0.0, tmp1 = 0.0, tmp2 = 0.0, tmp3 = 0.0; 
for(i = 0; i < ARR; i+=4){
    tmp0 += a[i]*b[i];
    tmp1 += a[i+1]*b[i+1];
    tmp2 += a[i+2]*b[i+2];
    tmp3 += a[i+3]*b[i+3];
}
return tmp0 + tmp1 + tmp2 + tmp3;
```
De esta forma (suponiendo que la multiplicación tarda 4 ciclos), se realiza la multiplicación de `tmp0`, en el siguiente la de `tmp1`, ..., hasta volver a la siguiente iteración con la multiplicación sobre `tmp0`, que tiene una dependencia RAW con la iteración anterior. Sin embargo, como ya han pasado 4 ciclos desde la última operación sobre `tmp0`, la siguiente puede empezar instantáneamente, sin esperar a la anterior y eliminando las latencias provocadas por RAW.  
  
Ante una operación que provoca un RAW de `n` ciclos, un desenrollado de `n` puede ser buena idea, aunque con realizar un desenrollado de menor número ya eliminamos ciertas latencias.  
Por ejemplo, si en el ejemplo hubiésemos puesto sólo `tmp0` y `tmp1`, eliminamos la latencia de cada RAW en 1 ciclo frente al bucle original.  
Cabe destacar que no siempre un mayor desenrollado nos va a dar unos mejores tiempos, el número de registros de la arquitectura es principal limitante (cuando se gasten, las variables se almacenan en memoria, ralentizando el programa).  
  
A partir del desenrollado, el compilador generará el código según su optimización, añadiendo operaciones vectoriales o no. Los compiladores aplican desenrollado.

### Reducir latencias de saltos
Por ejemplo, ante el siguiente código:
```c
for(int i = 0; i < 100; i++){
    if(i % 2 == 0){
        a[i] = x;
    }else{
        a[i] = y;
    }
}
```
Encontramos un salto condicional en cada iteración, lo que puede ralentizar el programa si las predicciones fallan. Sin embargo, podemos plantear como solución el siguiente bucle, que no introduce saltos condicionales, por lo que elimina la latencia introducida por los saltos:
```c
for(int i = 0; i < 100; i+=2){
    a[i] = x;
    a[i+1] = y;
}
```

## Códigos difíciles para el compilador
Antes de generar el código ejecutable, el compilador optimiza el código existente, aunque puede tener problemas a la hora de optimizarlas.  
  
Por ejemplo, muchos sabemos que el uso de punteros en código puede ayudar mucho a la hora de obtener unos menores tiempos de ejecución. Sin embargo, a veces este uso es contraproducente.  
Ante el siguiente código:
```c
int j = 7;
int v = 15;
j /= 7;
```
El compilador puede cambiar las líneas 1 y 3 por simplemente `int j = 1;`, optimizando el código. Pero si en vez del anterior, tenemos que:
```c
int j = 7;
int* v = 15;
j /= 7;
```
La dirección de memoria a la que apunta `v` se sabe en tiempo de ejecución pero no en tiempo de compilación, luego el compilador no sabe si es que `v` apunto o no a `j`, por lo que no puede realizar la optimización anteriormente comentada.

### Recomendaciones
Como recomendaciones para evitar este tipo de situaciones, se recomienda:
- Usar variables locales en lugar de punteros siempre que sea posible.
- Utilizar variables globales si no se pueden usar locales.
- Poner instrucciones de almacenamiento después o bastante antes de las de carga de memoria.

***
# Optimización del acceso a memoria
Como principal optimización a tener en cuenta, **dentro de un bucle se debe acceder a posiciones contiguas de memoria en medida de lo posible**, con el fin de reducir los fallos de caché, que introducen latencias considerables.

## Alineamiento de datos
Si trabajamos con un vector de longitud menor a 2 bloques de caché, si no alineamos bien los datos puede que dicho vector ocupe 3 bloques de caché (comience en el final de uno, rellene otro y termine en el principio de otro).  
Por tanto, si nos preocupamos de que nuestro vector comience justo en un bloque (dirección múltiplo de 32 bytes, ya que un bloque suele tener dicho tamaño), podemos obtener un menor número de fallos de caché: si el vector anterior lo alineamos de forma que sólo ocupe 2 bloques, al recorrerlo entero sólo necesitamos 2 bloques de caché, en vez de 3.  
  
Todos los compiladores ofrecen directivas para alinear datos en memoria.  
El procesador suele alinear los datos según el tamaño de dato al que se va a asignar una dirección (por ejemplo, para un vector de coma flotante de simple precisión, se le suele asignar una dirección de inicio múltiplo de 4, al ocupar este tipo de dato 4 bytes).

## Colisiones en caché
Las cachés modernas tienen una organización asociativa por conjuntos, ya vista en la asignatura de EC.  
Si todos los bloques traídos de memoria principal van al mismo conjunto de caché (dejando otros vacíos), obtenemos peores tiempos de ejecución al tener que desalojar bloques de caché de forma continuada.  
Buscamos por tanto, repartir los bloques de memoria principal entre los conjuntos en medida de lo posible.

## Localidad de los accesos
Debemos declarar las variables y estructuras de datos teniendo en cuenta cómo vamos a acceder a ellas, o acceder a ellas teniendo en cuenta cómo las hemos declarado; con el fin de **acceder a posiciones consecutivas**, explotando los principios de localidad local y temporal.

### Ejemplo 1: Acceso a matrices
En C, sabemos que las matrices se almacenan por filas, luego tras la dirección de memoria que almacena la componente `(i, j)` de una matriz, la siguiente dirección de memoria almacenará la componente (suponiendo una matriz de tamaño `n x m`):
```
(i, j+1) si j < m-1
(i+1, 0) si j = m-1 && i < n-1
```
Por tanto, con el fin de explotar el principio de localidad espacial que aprovechan las cachés, el bucle que recorre la matriz de la forma:
```c
for(int i = 0; i < n; i++){
    for(int j = 0; j < m; j++){
        matriz[i][j] = 0;
    }
}
```
provocará menos fallos en caché que el bucle:
```c
for(int j = 0; j < m; j++){
    for(int i = 0; i < n; i++){
        matriz[i][j] = 0;
    }
}
```
  
Hay lenguajes como Fortran en los que las matrices se almacenan por columnas. En estos lenguajes, el segundo bucle provocará menos fallos de caché que el primero.  
Vemos cómo es importante saber cómo los lenguajes almacenan las estructuras de datos.

### Ejemplo 2: Acceso a vectores
Supongamos que tenemos un código que trabaja sobre dos vectores `a` y `b` de 500 componentes cada uno. Dependiendo de cómo queramos acceder a ellos, podemos declararlos de una forma u otra con el fin de reducir las colisiones en caché.  
Por ejemplo, ante la siguiente forma de recorrerlos:
```c
for(int i = 0; i < 500; i++){
    a[i] = 2*a[i];
}
// ...
for(int i = 0; i < 500; i++){
    b[i] = 3*b[i];
}
```
es preferible tener la siguiente declaración:
```c
struct {
    int a[500];
    int b[500];
} s;
```
  
Sin embargo, si vamos a acceder a los vectores de la forma:
```c
for(int i = 0; i < 500; i++){
    a[i] = 2*a[i];
    b[i] = 2*b[i];
}
```
es preferible tener la siguiente declaración:
```c
struct {
    int a;
    int b;
} s[500];
```
con el fin de acceder a posiciones contiguas de memoria.

## Accesos a memoria especulativos
Sabemos ya por lo visto en teoría que todos los procesadores relajan `W --> R`, así como las lecturas propias pueden acceder antes a memoria que lecturas de otros procesadores.  
Si nuestros programas realizan accesos a memoria solapados, no se puede usar ninguna de las dos optimizaciones.  
Es por ello por lo que además recomendamos poner las lecturas tan lejos como sea posibles de las escrituras a las mismas áreas de memoria.

## Precaptación
El procesador, mediante instrucciones de `prefetch`, puede cargar zonas de memoria en caché antes de que se soliciten (en caso de haber ancho de banda disponible).  
Un uso positivo de la precaptación es, en un bucle que recorre un vector entero, introducir en ciertas iteraciones del bucle instrucciones de precaptación de iteraciones futuras, con el fin de que ya estén cargadas en caché cuando se soliciten, reduciendo latencias introducidas por fallos de caché.  
  
Todos los procesadores implementan precaptaciones a caché. El precaptador automático, tras 2 o 3 fallos de caché es capaz de preveer los accesos a memoria y de realizar un buen trabajo.  
Si detecta que estamos accediendo a bloques consecutivos, se preocupará de traer a caché bloques consecutivos. Si detecta que accedemos a posiciones de memoria con saltos de `k` bytes, se preocupará de traer a memoria los bloques que coincidan con dichos saltos.  
  
Debemos por tanto intentar acceder a los datos en memoria con un patrón fácilmente reconocible. En caso contrario, podemos usar instrucciones de precaptación para ayudar la labor de predecir los siguientes bloques de memoria a usar.

***
# Optimización de saltos
A la hora de reducir latencias introducidas por los saltos, trataremos de hacer códigos en los que sea fácil predecir si un salto se realizará o no.

## Cambiar condición de salto
Cada una de las instrucciones seperadas por `&&` en un salto condicional se evalúan como instrucciones de salto distintas.  
Ante el ejemplo siguiente, si todas las variables tienen un 50% de probabilidad de ser 0, la posibilidad de predecir las instrucciones de salto no es muy elevada:
```c
if(t1 == 0 && t2 == 0 && t3 == 0)
```
Sin embargo, si se utiliza un único salto con las condiciones anteriores, la probabilidad de saltar es del 0.125%, por lo que si siempre predecimos no saltar, obtendremos varias predicciones acertadas. Podemos recrear esta funcionalidad con el siguiente código:
```c
if((t1 | t2 | t3) == 0)
```
donde ya sólo usamos un salto.

## Usar instrucciones condicionales
Podemos eliminar saltos sencillos usando instrucciones condicionales de `asm`. Por ejemplo, en vez de usar un `if` para asignar un valor a una variable y otro en caso contrario, podemos en su lugar evaluar la condición y usar la instrucción `cmove`, que realiza la asignación en relación al resultado obtenido tras la condición.  
Esta transformación la realiza el compilador a veces, pero siempre la realiza con el uso del operador `?`, luego recomendamos su uso.  
  
Por ejemplo, ante el código en C:
```c
ebx = (A < B) ? C1 : C2;
```
podemos traducirlo a ensamblador como:
```asm
        cmp A, B
        jge L30         ; Si A >= B, jump L30
        mov ebx, C1     ; ebx <-- C1
        jmp L31         ; jump L31
L30:    mov ebx, C2     ; ebx <-- C2
L31:
```
sin embargo, podemos también hacer el siguiente código, donde eliminamos los saltos y el posible retardo introducido por malas predicciones:
```asm
xor ebx, ebx    ; ebx <-- 0
cmp A, B
setge bl        ; Si A >= B, bl = 1

dec ebx             ; ebx--, si ebx = 0 => ebx = FFFFFFFFF; si ebx = 1 => ebx = 0
and ebx, (C1-C2)    ; ebx <-- ebx & C1-C2
add ebx, C2         ; ebx += C2
```
Con este código inteligente:
- Si `A<B`: `bl = 0`, luego `ebx = FFFFFFFF`, de donde `ebx <-- C1-C2` y finalizará con `ebx += C2`, luego `ebx = C1`.
- Si `A>=B`: `bl = 1`, luego `ebx = 0`, de donde el `and` será 0 y finalizará con `ebx = C2`.  
  
Los compiladores son capaces de generar este tipo de códigos.

## Switches
Se pueden reducir el número de saltos de un programa reorganizando las alternativas en las sentencias `switch`, en el caso de que alguna opción tenga una mayor probabilidad a ejecutarse respecto a otras.  
Por ejemplo:
```c
switch(i){
    case 16:
        //...
        break;
    case 22:
        //...
        break;
    case 33:
        //...
        break;
}
```
si la opción 33 tiene un 50% de probabilidad de ejecutarse, podemos sustituir el código por:
```c
if(i == 33){
    // ...
}else{
    switch(i){
        case 16:
            //...
            break;
        case 22:
            //...
            break;
    }
}
```
