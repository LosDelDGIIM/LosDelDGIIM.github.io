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

    private
    def ajuste_del_atributo_a(a)
        # Para pruebas
        return a
    end

    def calculo_del_factor(a)
        # Para pruebas
        return a
    end

    def ajuste_factor(factor)
        # Para pruebas
        return factor
    end

    def ajuste_del_atributo_b(a, b, factor)
        # Para pruebas
        return b
    end


    # Los métodos privados ajuste_del_atributo_a, calculo_del_factor, ajuste_factor y ajuste_del_atributo_b ya se encuentran implementados en la clase Examen1
    # y este ejercicio no requiere conocer su implementación.
    #
    # 1- Crear otro constructor para la clase Examen1 que tenga 3 parámetros (a,b,filtro) que se deben proporcionar siempre obligatoriamente.
    #    Los dos primeros son los mismos que los del constructor existente y el otro es un valor utilizado para una operación de filtrado del parámetro a.
    #    Así, este constructor funcionará igual que el proporcionado, pero como primer paso, se llama a un método llamado filtro_a(a,filtro) que
    #    utiliza el primer y tercer parámetro del nuevo constructor y que devuelve el valor de a filtrado. Ese valor filtrado es el que se usa como valor de a
    #    para el resto de operaciones requeridas en la construcción del objeto.
    #
    # 2- Se debe además escribir la cabecera completa del método filtro_a(a,filtro). El cuerpo se dejará vacío.
    # 
    # La solución aportada no puede depender de cambios en el código existente.
    
    private
    def self.filtro_a(a,filtro)
        # Para pruebas
        return a
    end

    def self.newEj1(a,b,filtro)
        a = filtro_a(a,filtro)
        new(a,b)
    end
end

# Pruebas
puts Examen1.new(4,5).inspect
puts Examen1.newEj1(4,5,1).inspect