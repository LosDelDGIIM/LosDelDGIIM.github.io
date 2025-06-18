# Programación y Diseño Orientado a Objetos. Examen I de Prácticas

**Autor:** Arturo Olivares Martos
***

- **Asignatura:** Programación y Diseño Orientado a Objetos.
- **Curso Académico:** 2023-24.
- **Grado:** Doble Grado en Ingeniería Informática y Matemáticas.
- **Grupo:** A.
- **Profesor:** Miguel Lastra Leidinger.
- **Descripción:** Parcial I de Prácticas del Grupo A, Prácticas 1-3 de Irrgarten.
- **Fecha:** 24 de abril de 2024.
- **Duración:** 45 minutos.

Para el presente examen, era necesario que el alumno llevase implementadas ya las prácticas 1 a 3 del proyecto Irrgarten tanto en Java como en Ruby. Se pidió modificar determinados métodos ya implementados tan solo para comprobar de una manera más fácil que la práctica funcionaba.
***

Respecto a tu proyecto de **RUBY**, realize los siguientes cambios:
- Haz que el fichero que contenga el programa principal que permita jugar esté en un fichero denominado `play.rb`.
- Configura tu juego para que sólo existan 2 jugadores.
- Modifica el método que genera el laberinto para que produzca uno exactamente como el siguiente:

    ```txt
    E - M -
    - - - 0
    - X X X
    - M - -
    - - - 1
    ```

    Los números de la tabla anterior indican la posición al inicio de la partida de ambos jugadores. Modifica el código que posiciona los jugadores en el laberinto para asegurar que ambos aparecen en el lugar indicado. El código para este punto no tiene que ser general y puede ser específicamente particularizado al hecho de que sólo hay 2 jugadores en exactamente esas posiciones.


- En el método `next_move` de la clase que hace el papel de interfaz de texto, , en vez de solicitar cada vez al usuario la dirección en que debe moverse el jugador del juego con el turno, genera siempre una dirección de una secuencia fija de direciones. Esa secuencia será tal que las dos primeras indiquen movimiento hacia *arriba* y después se encadenarán una secuencia de 20 movimientos a la *izquierda*. Esto quiere decir que al llamar al método `next_move` 22 veces, devolverá el valor que indica hacia arriba 2 veces y después 20 veces el valor que representa un desplazamiento a la izquierda.

    Almacena la secuencia completo de direcciones preestablecidas en un contenedor en ámbito de clase. *Esta cuestión es importante que la hagas exactamente como se indica.* En ámbito de instancia se irá guardando un índice para saber cual es la siguiente dirección que debe ser devuelta cuando se llame al método `next_move`.

    *Nota: No tienes que temer quedarte sin direcciones que devolver ya que el juego acabará antes.*

- El monstruo que está más cerca de la salida debe tener unas características que hagan que siempre pierda los combates con los jugadores y el otro que los gane siempre.
    
    *Nota: Durante el examen, el profesor especificó que debido a la aleatoriedad del juego no se pedía estrictamente que **siempre** ganase, sino que en la gran, gran mayoría de los casos ganase. Esto daba a entender que simplemente pedía que se fijase el valor de `strength` e `intelligence` del monstruo a un valor muy alto.*

- Recuerda usar los métodos de los que dispone el laberinto para situar jugadores, obstáculos, y monstruos.


Es importante notar que, debido a que está programando para unos valores muy concretos y no se está generalizando, no se peneralizará el uso de números mágicos en las modificaciones que se han pedido.