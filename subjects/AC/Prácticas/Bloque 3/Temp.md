### run-sched-var
Cuyo ámbito es el entorno de datos.  
Controla la planificación de bucles para `runtime`. Adopta valores `(kind[, chunk])` (depende de la implementación).

### def-sched-var
Planificación de bucles por defecto de `gcc`, asignación estática de forma que interacciones consecutivas se asignan a un mismo hilo.  
Podemos cambiar dicha asignación mediante una cláusula de asignación, cambiando la asignación a la que haya en `run-sched-var`.  
Cuyo ámbito es el dispositivo.  
Controla la planificación de los bucles por defecto con ámbito de programa. Adopta valores `(kind[, chunk])` (depende de la implementación).  
No puede modificarse ni consultarse.

```c
omp_set_schedule(omp_ched_t kind, int chunk_size);
omp_get_schedule(&kind, &chunk_size);
```

monotonic con chunk de 1: Si asignamos la iteracion `i` a un hilo, la siguiente a asignar es la `i+1`. Se asignan de forma creaciente.
`nomonotonic`: Se asignan en cualquier orden.

Podemos combinar omp_monotonic con el resto.
En dígito hexadecimal menos significativo se pone el tipo y en el bit de signo si es monotonic o no.

## schedule 
Cláusula de planificación, cambiar el valor por defecto de asignación que usa `gcc`.
- static. Por defecto, monotonic.
- dynamic
- guided
- auto
- runtime

chunk: tamaño de unidades de trabajo que se asignan a los hilos. El tamaño es el número de iteraciones del bucle que tienen las unidades. Cuando asignamos un chunk a todos los hilos, sigue de forma rotatoria.

static con chunk de 1: se asigna de forma rotatoria.

En la estática la sobrecarga se reduce bastante. Siempre que podamos utilizar una asignación estática lo haremos.  
La asignación de forma dinámica nos permite realizar repartos más equitativos, útil en repartos complejos.

Con chunks más grandes tenemos un menor overhead (sobrecarga). Podemos comenzar añadiendo unidades de trabajo grandes y disminuir su tamaño progresivamente de forma que el tamaño más pequeño va a ser el especificado (guided).

#### runtime
La planificación que nosotros pongamos en la variable de control `run-sched-var`, que podemos cambiar su valor mediante ve o función.  
Copiar diagrama de flujo.

# Funciones 
Para sincronización con cerrojos o para obtener tiempos de ejecución.

## Cerrojos
Con ellas podemos implementar un `atomic`. Podemos sustituir estas funciones por código, necesariamente en ASM.

MPI usa procesos en lugar de hebras: sobrecarga enorme. En resumen, evitar usar procesos.
