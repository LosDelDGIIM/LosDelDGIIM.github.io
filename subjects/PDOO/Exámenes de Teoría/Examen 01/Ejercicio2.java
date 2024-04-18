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


    // Se declaran para pruebas
    private static float filtrarA(float a, float filtro){
        // Pruebas
        return a;
    }

    private static float ajusteAtributoA(float a){
        // Pruebas
        return a;
    }

    private static float calculoFactor(float a){
        // Pruebas
        return a;
    }

    private static float ajusteFactor(float factor){
        // Pruebas
        return factor;
    }

    private static float ajusteAtributoB(float a, float b, float factor){
        // Pruebas
        return b;
    }

    
}



class Examen2Hija extends Examen2{
    private float c;

}





/*
 * Los métodos privados de los que no se visualiza el cuerpo se considerarán implementados y este ejercicio no requiere conocer dicha implementación.
 * 
 * 1-   Indicar razonadamente si el código asociado a la segunda clase produciría errores de compilación. En caso de errores de este tipo,
 *      indicar los cambios que serían necesarios (en la segunda clase) y escribir el código correspondiente a los mismos.
 * 
 * 
 * La solución aportada no puede depender de cambios en el código existente.
 * 
 */


// --------------------------------------------------------------------------------------------
// 1- Respuesta:
/*
 * 
 * La clase Examen2Hija no compilaría. La clase Examen2Hija no tiene constructor explícito, por lo que usa el constructor por defecto (sin parámetros).
 * Este llama al constructor sin parámetros de la clase padre (Examen2), pero esta no lo tiene (ya que al definir un constructor explícito ya no se cuenta
 * con el constructor por defecto), por lo que da un error de compilación.
 * 
 * Como solución, se podría definir un constructor sin parámetros en la clase padre Examen2, aunque posiblemente no terminaría de tener mucho sentido
 * pues habría que asignarle valores a los atributos a y b, que podrían ser valores por defecto o valores aleatorios. No obstante, la implementación
 * que seguramente se busca es que, simplemente, la clase Examen2 tenga un constructor con tres parámetros, y que la clase Examen2Hija llame a dicho
 * constructor usando el super. Además, es necesario que la clase Examen2Hija tenga un constructor, ya que es necesario inicializar el atributo c.
 * La implementación sería la siguiente:
 * 

public Examen2Hija(float a, float b, float c){
    super(a,b);
    this.c = c;
}


 * De hecho, el error que da es:

Implicit super constructor Examen2() is undefined for default constructor. Must define an explicit constructorJava(134217868)

 * Como podemos ver, informa que Examen2() no tiene constructor sin parámetros, por lo que no puede llamarlo.
 * 
 */