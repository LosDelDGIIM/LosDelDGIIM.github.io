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





////////////////////////////////////////////////////////////////

class Enero2022{
    public static void main(String[] args){
        ((ProfesorUniversidad) new ProfesorUniversidadDoctor("Manolo")).investigar();
        Profesor prof1 = new ProfesorUniversidad("Pepe");
        //prof1.investigar();
        //Investigador inv1 = prof1;
        //ProfesorSecundaria sec1 = (ProfesorSecundaria)(Profesor) new ProfesorUniversidad("Juan");
    }
}