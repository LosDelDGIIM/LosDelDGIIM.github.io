class Examen
  @atributo1 = 1
  @atributo2 = 2
  @atributo3 = 3
  @MAX_SUMA_ATRIB = 10

  def initialize(param1, param2)
    @atributo1 = param1
    @atributo2 = param2

    while(!(cumple_restricciones(param1) && cumple_restricciones(param2)))
      # Código que modifica los atributos
    end
  end

  private

  def cumple_restricciones(a)
    result = true
    # Código que modifica el valor de result
    result
  end



  # Ejericio 2
  def metodoExamen(e)
    e.cumple_restricciones(7)
    e2= Examen.new(1,2)
    e2.cumple_restricciones(7)
  end


  # Ejercicio 4
  def self.newCons
    param1 = rand(@MAX_SUMA_ATRIB)
    param2 = rand(@MAX_SUMA_ATRIB)
    new(param1, param2)
  end


end


# Para probar el código
e = Examen.new(1,2)

# e.metodoExamen(e)     # Ejercicio 2

e2= Examen.newCons    # Ejercicio 4


# Ejercicio 6
class ExamenDerivada < Examen

end
ed = ExamenDerivada.new(1,2)
