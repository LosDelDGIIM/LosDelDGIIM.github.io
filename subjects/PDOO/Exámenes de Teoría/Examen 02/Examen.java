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