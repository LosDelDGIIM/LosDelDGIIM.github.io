class Examen
  @atributo1 = 1
  @atributo2 = 2
  @atributo3 = 3
  @MAX_SUMA_ATRIB = 10

  def initialize(param1, param2)
    @atributo1 = param1
    @atributo2 = param2

    while(!(cumpleRestricciones(param1) && cumpleRestricciones(param2)))
      # Código que modifica los atributos
    end
  end

  private

  def cumple_restricciones(a)
    result = false
    # Código que modifica el valor de result
    result
  end
end
