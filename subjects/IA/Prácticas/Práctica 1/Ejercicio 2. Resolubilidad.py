import sys

# Configuración objetivo
GOAL_STATE = "123456780"

# Función para contar el número de inversiones en una secuencia
def count_inversions(state):
    inversions = 0
    for i in range(len(state)):
        if state[i] == '0':
            continue  # Ignorar el espacio vacío
        for j in range(i + 1, len(state)):
            if state[j] == '0':
                continue  # Ignorar el espacio vacío
            if int(state[i]) > int(state[j]):
                inversions += 1
    return inversions

# Función para verificar si un estado es resoluble
def is_solvable(state):
    # Contar el número de inversiones
    inversions = count_inversions(state)
    # Si el número de inversiones es par, el estado es resoluble
    return inversions % 2 == 0

# Función principal
def main():
    if len(sys.argv) != 2:
        print("Uso: python script.py <configuración_inicial>")
        return

    initial_state = sys.argv[1]
    if len(initial_state) != 9 or not initial_state.isdigit() or '0' not in initial_state:
        print("La configuración inicial debe ser una cadena de 9 dígitos que incluya el 0.")
        return

    print(f"Configuración inicial: {initial_state}")
    if is_solvable(initial_state):
        print("El estado inicial es resoluble.")
    else:
        print("El estado inicial no es resoluble.")

if __name__ == "__main__":
    main()