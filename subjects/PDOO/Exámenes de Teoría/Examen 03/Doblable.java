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




//////////////////////////////
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