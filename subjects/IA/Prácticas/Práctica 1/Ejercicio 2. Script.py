from collections import deque
import sys

# Configuración objetivo
GOAL_STATE = "123456780"

# Movimientos posibles (arriba, abajo, izquierda, derecha)
MOVES = {
    'up': -3,
    'down': 3,
    'left': -1,
    'right': 1
}

# Función para imprimir el estado en forma de cuadrícula 3x3
def print_state(state):
    for i in range(0, 9, 3):
        print(state[i:i+3])
    print()

# Función para encontrar la posición del espacio vacío (0)
def find_empty(state):
    return state.index('0')

# Función para generar los estados vecinos
def get_neighbors(state):
    neighbors = []
    empty_index = find_empty(state)
    for move, delta in MOVES.items():
        new_index = empty_index + delta
        if 0 <= new_index < 9:
            # Verificar que el movimiento no cruce los bordes de la cuadrícula
            if (move == 'left' and empty_index % 3 == 0) or \
               (move == 'right' and empty_index % 3 == 2):
                continue
            # Intercambiar el espacio vacío con el número adyacente
            new_state = list(state)
            new_state[empty_index], new_state[new_index] = new_state[new_index], new_state[empty_index]
            neighbors.append((''.join(new_state), move))
    return neighbors

# Función para resolver el 8-Puzzle utilizando BFS
def solve_puzzle(initial_state):
    visited = set()
    queue = deque()
    queue.append((initial_state, []))

    while queue:
        current_state, path = queue.popleft()
        if current_state == GOAL_STATE:
            return path
        if current_state not in visited:
            visited.add(current_state)
            for neighbor, move in get_neighbors(current_state):
                if neighbor not in visited:
                    queue.append((neighbor, path + [(neighbor, move)]))

    return None

# Función principal
def main():
    if len(sys.argv) != 2:
        print("Uso: python script.py <configuración_inicial>")
        return

    initial_state = sys.argv[1]
    if len(initial_state) != 9 or not initial_state.isdigit() or '0' not in initial_state:
        print("La configuración inicial debe ser una cadena de 9 dígitos que incluya el 0.")
        return

    print("Configuración inicial:")
    print_state(initial_state)

    path = solve_puzzle(initial_state)
    if path:
        print("Solución encontrada:")
        for step, (state, move) in enumerate(path):
            print(f"Paso {step + 1}: Mover {move}")
            print_state(state)
    else:
        print("No se encontró solución.")

if __name__ == "__main__":
    main()