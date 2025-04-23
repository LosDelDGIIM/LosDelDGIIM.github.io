"""
Ejemplo de modulo python. Contiene una variable llamada mi_variable,
una funcion llamada mi_funcion, y una clase llamada MiClase.
"""

mi_variable = 0

def mi_funcion():
    """
    Ejemplo de funcion
    """
    return mi_variable

class MiClase:
    """
    Ejemplo de clase.
    """

    def __init__(self):
        self.variable = mi_variable

    def set_variable(self, nuevo_valor):
        u"""
        Le da a  self.variable un nuevo valor
        """
        self.variable = nuevo_valor

    def get_variable(self):
        return self.variable
