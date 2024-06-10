# Programación y Diseño Orientado a Objetos. Examen III de Teoría

**Autor:** Arturo Olivares Martos
***

- **Asignatura:** Programacición y Diseño Orientado a Objetos.
- **Curso Académico:** 2021-22.
- **Grado:** Grado en Ingeniería Informática.
<!--- **Grupo:** Único.-->
- **Profesor:** Miguel Lastra Leidinger.
- **Descripción:** Convocatoria Ordinaria.
- **Fecha:** 17 de enero de 2022.
- **Duración:** 45 minutos.


## Ejercicio 1 (Java) [2 puntos]

Dado el siguiente código, disponible en el archivo [`Profesores.java`](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/PDOO/Exámenes%20de%20Teor%C3%ADa/Examen%2003/Profesores.java):
```java
abstract class Profesor{

    private String nombre;

    public Profesor(String nombre){
        this.nombre = nombre;
    }
    abstract void impartirDocencia();
}


interface Investigador{
    public void investigar();
}


class ProfesorSecundaria extends Profesor{
    ProfesorSecundaria(String nombre){
        super(nombre);
    }

    @Override
    void impartirDocencia(){
        System.out.println("Dando clase en un instituto");
    }

    void vigilarRecreo(){
        System.out.println("Vigilando el recreo en un instituto");
    }
}


class ProfesorUniversidad extends Profesor implements Investigador{
    ProfesorUniversidad(String nombre){
        super(nombre);
    }

    @Override
    void impartirDocencia(){
        System.out.println("Dando clase en una facultad");
    }

    @Override
    public void investigar(){
        System.out.println("Investigando en una facultad");
    }
}


class ProfesorUniversidadDoctor extends ProfesorUniversidad{
    ProfesorUniversidadDoctor(String nombre){
        super(nombre);
    }

    @Override
    public void investigar(){
        super.investigar();
        System.out.println("Como doctor");
    }
}
```


Indicar los errores relacionados con compatibilidad de tipos presentes en el siguiente programa principal. Se tendrá que indicar el error, la línea en la que se produce, y si se produce en tiempo de ejecución o de compilación.
```java
1. class Enero2022{
2.     public static void main(String[] args){
3.         ((ProfesorUniversidad) new ProfesorUniversidadDoctor("Manolo")).investigar();
4.         Profesor prof1 = new ProfesorUniversidad("Pepe");
5.         prof1.investigar();
6.         Investigador inv1 = prof1;
7.         ProfesorSecundaria sec1 = (ProfesorSecundaria)(Profesor) new ProfesorUniversidad("Juan");
8.     }
9. }
```

| Línea | Compilación/Ejercución | Breve Descripción del Error |
|-------|------------------------|-----------------------------|
|5|Compilación|El método `investigar` no está definido en la clase `Profesor`, que es el tipo estático de la variable `prof1`.|
|6|Compilación|No se puede asignar un objeto de tipo estático `Profesor` a una variable de tipo `Investigador`, ya que `Profesor` no implementa la interfaz `Investigador`.|
|7|Ejecución|Se produce una excepción de tipo `ClassCastException` al intentar hacer un *casting* de un objeto de tipo `ProfesorUniversidad` a un objeto de tipo `ProfesorSecundaria`|



## Ejercicio 2 (Ruby) [2 puntos]

Dado el siguiente código, disponible en el archivo [`PadreHija.rb`](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/PDOO/Exámenes%20de%20Teor%C3%ADa/Examen%2003/PadreHija.rb):    
```ruby
module Primero
	class Padre

		def metodoPublico(p)
			metodoPrivado
			p.metodoPrivado
			metodoProtegido
			p.metodoProtegido
		end

		private
		def metodoPrivado
		end

		protected
		def metodoProtegido
		end
	end

end

module Segundo
	class Hija < Primero::Padre

		def metodoPublico(p)
			metodoPrivado
			p.metodoPrivado
			metodoProtegido
			p.metodoProtegido
		end

	end
end

Primero::Padre.new.metodoPublico(Segundo::Hija.new)
Segundo::Hija.new.metodoPublico(Primero::Padre.new)
```

Usaremos la notación de las líneas disponibles en el archivo `PadreHija.rb` para referirnos a ellas. Empezando desde las líneas 35 y 36 (las dos últimas), indicar las líneas en las que se produce algún error relacionado con la accesibilidad (visibilidad) de los métodos, asumiendo que cada error es ignorado y que la ejecución puede continuar.

- Tras la ejecución de la línea 35, se produce un error en la línea 6, ya que el método `metodoPrivado` es privado, por lo que no se puede ejecutar en otra instancia, por lo que `p.metodoPrivado` no se puede ejecutar.

- Tras la ejecución de la línea 36, se produce un error en la línea 27 por el mismo motivo.

Evidentemente, en ambos casos acceder a los métodos de la misma instancia no provoca problemas. Además, en ambos casos se puede acceder a los métodos protegidos (en el primer caso debido a que en `Hija` no se ha redefinido, por lo que se hereda; y en el segundo caso porque el método al que se intenta acceder se ha heredado).



## Ejercicio 3 (Java) [2 puntos]

Dado el siguiente código, disponible en el archivo [`Doblable.java`](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/PDOO/Exámenes%20de%20Teor%C3%ADa/Examen%2003/Doblable.java):
```java
interface Doblable{
    public void doblar();
}

class Mapa implements Doblable{
    @Override
    public void doblar(){
        // ...
    }
}

class Kebab implements Doblable{
    @Override
    public void doblar(){
        // ...
    }
}

class Alfombra implements Doblable{
    @Override
    public void doblar(){
        // ...
    }
}
```

Este ejercicio se centra en la operación de enrollar mapas, alfombras y kebabs. Sobre esta operación, se proporciona la siguiente información:
- La operación de enrollado, cuyo código no se proporciona, se debe asumir que tiene una cierta complejidad (unas 100 líneas de código) y que se basa siempre en el uso progresivo e iterativo del método `doblar` del elemento que se desea enrollar.
- El enrollado de un mapa, de un kebab y de una alfombra se realiza de exactamente la misma forma (usando, como se ha dicho, el método `doblar` de cada uno de ellos).
- Se desea crear las clases `EnrolladorDeMapas`, `EnrolladorDeKebabs` y `EnrolladorDeAlfombras` de forma que dispongan todas de un método de instancia llamado `enrollar` que se aplique a un parámetro del tipo adecuado en cada caso (mapa, kebab o alfombra, respectivamente).
- Es importante que un enrollador no pueda enrollar elementos de otro tipo (por ejemplo, un `EnrolladorDeMapas` no puede enrollar un kebab). De esta comprobación se debe encargar el compilador.
- Es probable que en el futuo aparezcan más elementos doblables y que también se tengan que crear clases que permitan enrollarlos.

Proporcionar una implementación, utilizando el lenguaje de programación *Java* para las tres clases indicadas. Del método `enrollar`, solo se debe proporcionar la cabecera completa (incluyendo el parámetro).

La solución, disponible también en el archivo [`Doblable.java`](https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/PDOO/Exámenes%20de%20Teor%C3%ADa/Examen%2003/Doblable.java), es la siguiente:
```java
class Enrollador <T extends Doblable>{
    
    public void enrollar(T objeto){
        ///...
        objeto.doblar();
        ///...
    }
}

class EnrolladorDeAlfombras extends Enrollador<Alfombra> {}

class EnrolladorDeKebabs extends Enrollador<Kebab> {}

class EnrolladorDeMapas extends Enrollador<Mapa> {}
```

Como podemos ver, todo se basa en la clase parametrizable `Enrollador`.