# Programación y Diseño Orientado a Objetos. Examen I de Teoría

**Autor:** Arturo Olivares Martos
***

- **Asignatura:** Programacición y Diseño Orientado a Objetos.
- **Curso Académico:** 2019-20.
- **Grado:** Doble Grado en Ingeniería Informática y Matemáticas.
- **Grupo:** Único.
- **Profesor:** Miguel Lastra Leidinger
- **Descripción:** Parcial I de Teoría, Temas 1-8.
<!--- **Fecha:** 18 de abril de 2023. -->
<!-- - **Duración:** -->



## Ejercicio 1

**Este ejercicio se encuentra disponible en el archivo Ejercicio1.rb y descrito a continuación.**

Se proporciona el siguiente código:
```ruby
class Examen1
    def initialize (a=44, b=33)
        if ((a!=44) && (b!=33))
            @a = ajuste_del_atributo_a(a)
            factor = calculo_del_factor(a)
            if (factor < 1)
                factor=ajuste_factor(factor)
            end
            @b=ajuste_del_atributo_b(a, b, factor)
        else
            @a=a+1
            @b=b+1
        end
    end

    def salida
        return 2*(@a+@b)
    end
end
```

Los métodos privados `ajuste_del_atributo_a`, `calculo_del_factor`, `ajuste_factor` y `ajuste_del_atributo_b` ya se encuentran implementados en la clase `Examen1`y este ejercicio no requiere conocer su implementación.

- Crear otro constructor para la clase `Examen1` que tenga 3 parámetros (`a`,`b`,`filtro`) que se deben proporcionar siempre obligatoriamente. Los dos primeros son los mismos que los del constructor existente y el otro es un valor utilizado para una operación de filtrado del parámetro `a`. Así, este constructor funcionará igual que el proporcionado, pero como primer paso, se llama a un método llamado `filtro_a(a,filtro)` que utiliza el primer y tercer parámetro del nuevo constructor y que devuelve el valor de a filtrado. Ese valor filtrado es el que se usa como valor de `a` para el resto de operaciones requeridas en la construcción del objeto.

- Se debe además escribir la cabecera completa del método `filtro_a(a,filtro)`. El cuerpo se dejará vacío.
     
La solución aportada no puede depender de cambios en el código existente.
_______
- Para el primer apartado, el segundo constructor quedaría:
    ```ruby
    def self.newEj1(a,b,filtro)
        a = filtro_a(a,filtro)
        new(a,b)
    end
    ```

    La prueba de ambos constructores quedan:
    ```ruby
    puts Examen1.new(4,5).inspect
    puts Examen1.newEj1(4,5,1).inspect
    ```

- La cabecera de dicho método queda:
    ```ruby
    private
    def self.filtro_a(a,filtro)
        # Para pruebas
        return a
    end
    ```


## Ejercicio 2

**Este ejercicio se encuentra disponible en el archivo Ejercicio2.java y descrito a continuación.**

Se proporciona el siguiente código:
```java
class Examen2{
    private float a;
    private float b;

    public Examen2(float a, float b){
        this.a=ajusteAtributoA(a);
        float factor=calculoFactor(a);
        if (factor < 1.0f){
            factor=ajusteFactor(factor);
        }
        this.b=ajusteAtributoB(a,b,factor);
    }
    
    public float salida(){return 2*(a+b);}

    private static float filtrarA(float a, float filtro){...}
    private static float ajusteAtributoA(float a){...}
    private static float calculoFactor(float a){...}
    private static float ajusteFactor(float factor){...}
    private static float ajusteAtributoB(float a, float b, float factor){...}

    
}
```

Los métodos privados de los que no se visualiza el cuerpo se considerarán implementados y este ejercicio no requiere conocer dicha implementación.

También se proporciona:
```java
class Examen2Hija extends Examen2{
    private float c;
}
```

- Indicar razonadamente si el código asociado a la segunda clase produciría errores de compilación. En caso de errores de este tipo, indicar los cambios que serían necesarios (en la segunda clase) y escribir el código correspondiente a los mismos.

La solución aportada no puede depender de cambios en el código existente.
____
- La clase `Examen2Hija` no compilaría. La clase `Examen2Hija` no tiene constructor explícito, por lo que usa el constructor por defecto (sin parámetros). Este llama al constructor sin parámetros de la clase padre (`Examen2`), pero esta no lo tiene (ya que al definir un constructor explícito ya no se cuentacon el constructor por defecto), por lo que da un error de compilación.

    Como solución, se podría definir un constructor sin parámetros en la clase padre `Examen2`, aunque posiblemente no terminaría de tener mucho sentido, pues habría que asignarle valores a los atributos `a` y `b`, que podrían ser valores por defecto o valores aleatorios. No obstante, la implementaciónque seguramente se busca es que, simplemente, la clase `Examen2` tenga un constructor con tres parámetros, y que la clase `Examen2Hija` llame a dicho constructor usando el `super`. Además, es necesario que la clase `Examen2Hija` tenga un constructor, ya que es necesario inicializar el atributo `c`.La implementación sería la siguiente:
    ```java
    public Examen2Hija(float a, float b, float c){
        super(a,b);
        this.c = c;
    }
    ```

    De hecho, el error que da es:
    ```java
    Implicit super constructor Examen2() is undefined for default constructor. Must define an explicit constructorJava(134217868)
    ```

    Como podemos ver, informa que Examen2() no tiene constructor sin parámetros, por lo que no puede llamarlo.


## Ejercicio 3

**Este ejercicio se encuentra disponible en el archivo Ejercicio3.java y descrito a continuación.**

Se proporciona el siguiente código:
```java
class Examen2{
    private float a;
    private float b;

    public Examen2(float a, float b){
        this.a=ajusteAtributoA(a);
        float factor=calculoFactor(a);
        if (factor < 1.0f){
            factor=ajusteFactor(factor);
        }
        this.b=ajusteAtributoB(a,b,factor);
    }
    
    public float salida(){return 2*(a+b);}

    private static float filtrarA(float a, float filtro){...}
    private static float ajusteAtributoA(float a){...}
    private static float calculoFactor(float a){...}
    private static float ajusteFactor(float factor){...}
    private static float ajusteAtributoB(float a, float b, float factor){...}

    
}
```

Los métodos privados de los que no se visualiza el cuerpo se considerarán implementados y este ejercicio no requiere conocer dicha implementación.

También se proporciona:
```java
class Examen2Hija extends Examen2{
    private float c;
}
```

- Proporciona una implementación para el método `salida` de la segunda clase sabiendo que el resultado debe ser menor en una unidad que el resultado del método del mismo nombre de la primera clase.

- Indicar si en la segunda clase se podría crear adicionalmente otro método llamado `salida` que aceptase dos parámetros. En caso negativo, indicar si podría hacerse en la primera clase. Justificar la respuesta.

La solución aportada no puede depender de cambios en el código existente.
____
- La implementación sería:
    ```java
    static final float DIFF_SALIDA = 1.0f;

    @Override
    public float salida(){
        return super.salida() - DIFF_SALIDA;
    }
    ```

- Sí, no habría problema. Además, notemos que en este caso no se produce redefinición, ya que el método `salida` de la clase `Examen2` no acepta parámetros.
    ```java
    public float salida(float p1, float p2){...}
    ```


## Ejercicio 4
**Este ejercicio se encuentra disponible en el archivo Ejercicio4.java y descrito a continuación.**

Dado el siguiente código:
```java
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Random;

class Examen4{
    /*private*/ ArrayList<Integer> contenedor = new ArrayList<>();
    private Random generador=new Random();

    public void rellena(){
        for (int i=0;i<10;i++){
            contenedor.add(generador.nextInt(100));
        }
    }

    public ArrayList<Integer> getContenedor(){
        return contenedor;
    }
}


public class Ejercicio4{

    public static void main(String[] args) {
        Examen4 ex4 = new Examen4();
        ex4.rellena();
        ex4.getContenedor().add(44);
    }
}
```
- Indicar razonadamente si la última linea (el método `.add(44)`) produce un error de compilación.
- Indicar la respuesta a la pregunta anterior si se elimina el comentario de la palabra reservada `private` del atributo `contenedor`.
____
En ambos casos, tenemos que no se produce error de compilación, independientemente de la visibilidad del `ArrayList contenedor`. Esto se debe a que el consultor `getContenedor()` devuelve una referencia al `ArrayList contenedor`, y ya no se controla qué se hace con ella.

Para evitar esto, habría que devolver una copia del `ArrayList contenedor`, en lugar de una referencia a él.