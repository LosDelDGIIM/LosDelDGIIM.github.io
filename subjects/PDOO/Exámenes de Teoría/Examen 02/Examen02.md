# Programación y Diseño Orientado a Objetos. Examen II de Teoría

**Autor:** Arturo Olivares Martos
***

- **Asignatura:** Programacición y Diseño Orientado a Objetos.
- **Curso Académico:** 2023-24.
- **Grado:** Doble Grado en Ingeniería Informática y Matemáticas.
- **Grupo:** Único.
- **Profesor:** Miguel Lastra Leidinger.
- **Descripción:** Parcial I de Teoría, Temas 1-8.
- **Fecha:** 19 de abril de 2024.
- **Duración:** 45 minutos.

Notemos que del siguiente examen hubo diversos modelos, todos ellos con 4 ejercicios. Debido al mero fin didáctico de este documento, se incluirán todos los efecicios, aunque un examen no los incluyese todos.

- El Modelo A constaba de los ejercicios [2](#ejercicio-2-ruby), [4](#ejercicio-4-ruby), [5](#ejercicio-5-java) y [8](#ejercicio-8-java).
- El Modelo B constaba de los ejercicios [1](#ejercicio-1-java), [3](#ejercicio-3-java), [6](#ejercicio-6-ruby) y [7](#ejercicio-7-ruby).


Como última consideración, hemos de destacar que se permitió al alumnado llevar una hoja con información escrita (o impresa) por una cara.

****
El examen completo se basó en la clase `Examen`, implementada en Java en el archivo [`Examen.java`](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/PDOO/Exámenes%20de%20Teor%C3%ADa/Examen%2002/Examen.java) y en Ruby en el archivo [`Examen.rb`](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/PDOO/Exámenes%20de%20Teor%C3%ADa/Examen%2002/Examen.rb). A continuación se muestra el contenido de dichos archivos:
- Archivo [`Examen.java`](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/PDOO/Exámenes%20de%20Teor%C3%ADa/Examen%2002/Examen.java):
    ```java
    import java.util.Random;

    public class Examen{
        private float atributo1;
        private float atributo2;
        private static final int MAX_SUMA_ATRIB=10;

        public Examen(float param1, float param2){
            atributo1=param1;
            atributo2=param2;
            
            while(!(cumpleRestricciones(param1) && cumpleRestricciones(param2))){
                // Código que modifica los atributos
            }
        }

        private boolean cumpleRestricciones(float a){
            boolean result=false;
            // Código que modifica el valor de result
            return result;
        }
    }
    ```
- Archivo [`Examen.rb`](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/PDOO/Exámenes%20de%20Teor%C3%ADa/Examen%2002/Examen.rb):
    ```ruby
    class Examen
    @atributo1 = 1
    @atributo2 = 2
    @atributo3 = 3
    @MAX_SUMA_ATRIB = 10

    def initialize(param1, param2)
        @atributo1 = param1
        @atributo2 = param2

        while(!(cumpleRestricciones(param1) && cumpleRestricciones(param2)))
        # Código que modifica los atributos
        end
    end

    private

    def cumple_restricciones(a)
        result = false
        # Código que modifica el valor de result
        result
    end
    end
    ```



## Ejercicio 1 (Java)

**Suponga que se incluye el siguiente método en la clase `Examen` del fichero [`Examen.java`](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/PDOO/Exámenes%20de%20Teor%C3%ADa/Examen%2002/Examen.java):**
```java
void metodoExamen(Examen e){
    e.cumpleRestricciones(e.atributo1);
    Examen e2= new Examen(1,2);
    e2.cumpleRestricciones(e2.atributo1);
}
```
**Rellenar la siguiente tabla con todos los errores de compilación que se producirían al intentar compilar la clase `Examen` con el método `metodoExamen` incluido.**

*Nota: En el caso de que no haya errores, dejar la tabla vacía y explicar por qué.*

| Línea | Breve Descripción del Error |
|-------|------------------------------|
|-|-|
<!--No hay errores de compilación.-->


## Ejercicio 2 (Ruby)

**Suponga que se incluye el siguiente método en la clase `Examen` del fichero [`Examen.rb`](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/PDOO/Exámenes%20de%20Teor%C3%ADa/Examen%2002/Examen.rb):**
```ruby
def metodoExamen(e)
    e.cumple_restricciones(7)
    e2= Examen.new(1,2)
    e2.cumple_restricciones(7)
end
```


**Rellenar la siguiente tabla con todos los errores que produciría el intérprete en tiempo de ejecución al llamar al método `metodoExamen` de la clase `Examen`.**

*Nota: En el caso de que no haya errores, dejar la tabla vacía y explicar por qué.*

| Línea | Breve Descripción del Error |
|-------|------------------------------|
|-|-|

<!--Primera línea. Da error. No puedo llamar a un método privado desde otra instancia. Sí es verdad que puede ser que e no fuese un error, por lo que... En la tercera línea da el mismo error.-->


## Ejercicio 3 (Java)
**Implementar un constructor sin parámetros en la clase `Examen` del fichero [`Examen.java`](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/PDOO/Exámenes%20de%20Teor%C3%ADa/Examen%2002/Examen.java). Este debe realizar la misma función que el constructor actual, aunque los dos parámetros han de ser números aleatorios entre $0$ y la variable de clase `MAX_SUMA_ATRIB` declarada en la línea 6 del fichero [`Examen.java`](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/PDOO/Exámenes%20de%20Teor%C3%ADa/Examen%2002/Examen.java).**

**De esta forma, el siguiente código sería válido:**
```java
Examen e = new Examen(3, 4);    // Constructor actual
Examen e2= new Examen();        // Constructor sin parámetros
```

*Nota: Para generar un número aleatorio entre $0$ y $n$, suponer definida la instrucción `rand(n)`, que devolverá el número buscado.*

En este ejercicio, se busca que el alumno tenga claro que, para no repetir código, se puede llamar a un constructor desde otro constructor mediante la pseudovariable `this`. Además, en un constructor esta llamada debe ser la primera instrucción. Por tanto, la solución sería la siguiente:

```java
Examen(){
    this(rand(MAX_SUMA_ATRIB), rand(MAX_SUMA_ATRIB));
}
```

## Ejercicio 4 (Ruby)
**Implementar un constructor sin parámetros en la clase `Examen` del fichero [`Examen.rb`](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/PDOO/Exámenes%20de%20Teor%C3%ADa/Examen%2002/Examen.rb). Este debe realizar la misma función que el constructor actual, aunque los dos parámetros han de ser números aleatorios entre $0$ y la variable declarada en la línea 5 del fichero [`Examen.rb`](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/PDOO/Exámenes%20de%20Teor%C3%ADa/Examen%2002/Examen.rb).**

**De esta forma, el siguiente código sería válido:**
```ruby
e = Examen.new(3, 4)    # Constructor actual
e2= Examen.newCons      # Constructor sin parámetros
```

*Nota: Para generar un número aleatorio entre $0$ y $n$, suponer definida la instrucción `random(n)`, que devolverá el número buscado.*

En este caso, la solución sería la siguiente:
```ruby
def self.newCons
    param1 = random(@MAX_SUMA_ATRIB)
    param2 = random(@MAX_SUMA_ATRIB)
    new(param1, param2)
end
```
En este caso, se buscaba en primer lugar que el estudiante fuese consciente de que no se pueden sobrecargar los métodos, tampoco el constructor. De igual forma, se buscaba que el alumno no duplicase código, sino que hiciese una llamada al constructor ya implementado. Además, se buscaba que el alumno fuese consciente de que, en Ruby, los métodos de clase se definen con `self`, y que el constructor es un ejemplo de esto. Por último, implementar un consultor para la variable de instancia de la clase `@MAX_SUMA_ATRIB` no era necesario, ya que al encontrarnos en ámbito de clase no hay problema, por lo que su implementación se habría penalizado al exponer el estado de la clase.


## Ejercicio 5 (Java)
**Suponga que se incluye el siguiente código al archivo [`Examen.java`](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/PDOO/Exámenes%20de%20Teor%C3%ADa/Examen%2002/Examen.java):**
```java
class ExamenDerivada extends Examen{
    
}
```
**Indicar si el código anterior produciría errores de compilación y por qué sí o por qué no.**



## Ejercicio 6 (Ruby)
**Suponga que se incluye el siguiente código al archivo [`Examen.rb`](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/PDOO/Exámenes%20de%20Teor%C3%ADa/Examen%2002/Examen.rb):**
```ruby
class ExamenDerivada < Examen
    
end
```
**Indicar si intérprete produciría en tiempo de ejecución y por qué sí o por qué no a la hora de crear una instancia de la clase `ExamenDerivada`.**



## Ejercicio 7 (Ruby)
**Indicar la cantidad de atributos de instancia de cada instancia de la clase `Examen` del fichero [`Examen.rb`](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/PDOO/Exámenes%20de%20Teor%C3%ADa/Examen%2002/Examen.rb).**

En este caso, se buscaba ver si el alumno tenía claro la diferencia entre los atributos de instancia de clase y los atributos de clase. Aunque ambos se noten con tan solo una `@`, los atributos de instancia son los que se declaran en ámbito de instancia, dentro del `initialize` (aunque también se podrían declaran en otros métodos, esto no es una buena práctica, por lo que no se incluye).

Por tanto, en este caso, *la respuesta correcta sería 2*, ya que en el `intialize` tan solo se declaran dos atributos de instancia, `@atributo1` y `@atributo2`.




## Ejercicio 8 (Java)
Suponga que se incluye el siguiente código al archivo [`Examen.java`](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/PDOO/Exámenes%20de%20Teor%C3%ADa/Examen%2002/Examen.java):
```java
class ExamenDerivada extends Examen{
    @Override
    public boolean cumpleRestricciones(float a){
        boolean resultado=false;
        // Cuerpo del método
        return resultado;
    }
}
```
**Rellenar la siguiente tabla con todos los errores de compilación que se producirían al intentar compilar el archivo [`Examen.java`](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/PDOO/Exámenes%20de%20Teor%C3%ADa/Examen%2002/Examen.java) con la clase `ExamenDerivada` incluida.**

*Nota: En el caso de que no haya errores, dejar la tabla vacía y explicar por qué.*

| Línea | Breve Descripción del Error |
|-------|------------------------------|
|-|-|

<!--Sí da error, en el Override. Si no pusiesemos en el override no daría error, pq estaría definiendo un nuevo método.-->