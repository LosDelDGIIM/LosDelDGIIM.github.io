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

    /*
    * Los métodos privados de los que no se visualiza el cuerpo se considerarán implementados y este ejercicio no requiere conocer dicha implementación.
    * 
    * 1-   Proporciona una implementación para el método salida de la segunda clase sabiendo que el resultado debe ser menor en una unidad que el resultado
    *      del método del mismo nombre de la primera clase.
    * 
    * 2-   Indicar si en la segunda clase se podría crear adicionalmente otro método llamado salida que aceptase dos parámetros. En caso negativo, indicar si
    *      podría hacerse en la primera clase. Justificar la respuesta.
    * 
    * 
    * La solución aportada no puede depender de cambios en el código existente.
    * 
    */

    // Este constructor no se daba, pero como se ha visto en el ejercicio 2 es necesario para que la clase compile y poder así probar.
    public Examen2Hija(float a, float b, float c){
        super(a,b);
        this.c = c;
    }


    // 1-
    static final float DIFF_SALIDA = 1.0f;

    @Override
    public float salida(){
        return super.salida() - DIFF_SALIDA;
    }

    // 2-
    // Notemos que en este caso no se produce redefinición, ya que el método salida de la clase Examen2 no acepta parámetros.
    public float salida(float p1, float p2){
        return this.c*(p1 + p2);   // Implementación de prueba
    }

}