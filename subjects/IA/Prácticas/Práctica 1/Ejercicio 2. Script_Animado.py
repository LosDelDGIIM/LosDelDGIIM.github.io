import sys
from collections import deque
import pygame
import time

# Configuración objetivo
GOAL_STATE = "123456780"

# Movimientos posibles (arriba, abajo, izquierda, derecha)
MOVES = {
    'up': -3,
    'down': 3,
    'left': -1,
    'right': 1
}

# Dimensiones de la ventana y el tablero
WINDOW_SIZE = 300
TILE_SIZE = WINDOW_SIZE // 3

# Colores
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
GRAY = (200, 200, 200)

# Inicializar pygame
pygame.init()
screen = pygame.display.set_mode((WINDOW_SIZE, WINDOW_SIZE))
pygame.display.set_caption("8-Puzzle Solver")
font = pygame.font.Font(None, 36)

# Función para dibujar el tablero
def draw_board(state):
    screen.fill(WHITE)
    for i in range(9):
        row = i // 3
        col = i % 3
        if state[i] != '0':
            pygame.draw.rect(screen, GRAY, (col * TILE_SIZE, row * TILE_SIZE, TILE_SIZE, TILE_SIZE))
            text = font.render(state[i], True, BLACK)
            text_rect = text.get_rect(center=(col * TILE_SIZE + TILE_SIZE // 2, row * TILE_SIZE + TILE_SIZE // 2))
            screen.blit(text, text_rect)
    pygame.display.flip()

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
    if len(sys.argv) != 3:
        print("Uso: python script.py <configuración_inicial> <velocidad>")
        print("Ejemplo: python script.py 130425786 1.0")
        return

    initial_state = sys.argv[1]
    speed = float(sys.argv[2])  # Velocidad en segundos (pausa entre movimientos)

    if len(initial_state) != 9 or not initial_state.isdigit() or '0' not in initial_state:
        print("La configuración inicial debe ser una cadena de 9 dígitos que incluya el 0.")
        return

    if speed <= 0:
        print("La velocidad debe ser un número positivo.")
        return

    # Resolver el puzzle
    path = solve_puzzle(initial_state)
    if not path:
        print("No se encontró solución.")
        return

    # Mostrar la animación gráfica
    # Introduce al inicio de path el estado inicial, y movimiento 'start'
    path.insert(0, (initial_state, 'start'))

    for state, move in path:
        draw_board(state)
        time.sleep(speed)  # Pausa ajustable para visualizar el movimiento
        pygame.display.set_caption(f"8-Puzzle Solver - Movimiento: {move}")
        pygame.event.pump()  # Actualizar la ventana

    # Mantener la ventana abierta hasta que el usuario la cierre
    running = True
    while running:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False

    pygame.quit()

if __name__ == "__main__":
    main()