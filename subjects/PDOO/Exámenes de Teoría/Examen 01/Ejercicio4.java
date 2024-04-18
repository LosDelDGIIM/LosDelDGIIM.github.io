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

        System.out.println(Arrays.toString(ex4.getContenedor().toArray()));   // Para probarlo
        ex4.getContenedor().add(44);
        System.out.println(Arrays.toString(ex4.getContenedor().toArray()));   // Para probarlo
    }
}


/*
 * Dado el anterior código:
 * 1- Indicar razonadamente si la línea 28 produce un error de compilación.
 * 
 * 2- Indicar la respuesta a la pregunta anterior si se elimina el comentario de la línea 6.
 * 
 * 
 * 
 * 
 * 
 * En ambos casos, tenemos que no se produce error de compilación, independientemente de la visibilidad del ArrayList contenedor.
 * Esto se debe a que el consultor getContenedor() devuelve una referencia al ArrayList contenedor, y ya no se controla qué se hace con ella.
 * 
 * Para evitar esto, habría que devolver una copia del ArrayList contenedor, en lugar de una referencia a él.
 */