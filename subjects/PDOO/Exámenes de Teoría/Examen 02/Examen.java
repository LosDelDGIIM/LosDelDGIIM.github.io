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
        boolean result=true;
        // Código que modifica el valor de result
        return result;
    }


    // Método rand mencionado. No se aportaba en el examen porque no era necesario.
    private static float rand(int max){
        Random r= new Random();
        return r.nextFloat()*max;
    }


    // Ejercicio 1
    /*
    void metodoExamen(Examen e){
        e.cumpleRestricciones(e.atributo1);
        Examen e2= new Examen(1,2);
        e2.cumpleRestricciones(e2.atributo1);
    }
     */



    // Ejercicio 3
    /*
    Examen(){
        this(rand(MAX_SUMA_ATRIB), rand(MAX_SUMA_ATRIB));
    }

    // Método main
    public static void main(String[] args){
        Examen e = new Examen(3, 4);    // Constructor actual
        Examen e2= new Examen();        // Constructor sin parámetros
    }
     */
    
}


// Ejercicio 5
// Para comprobar que da error, se ha de comentar el constructor sin parámetros del Ejercicio 3
// El ejercicio 8 no pertenece a este ejercicio, por lo que ha de comentarse.
/*
class ExamenDerivada extends Examen{

    // Ejercicio 8
    @Override
    public boolean cumpleRestricciones(float a){
        boolean resultado=false;
        // Cuerpo del método
        return resultado;
    }
    
}
 */