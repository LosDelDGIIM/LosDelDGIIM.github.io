import socket
# Un socket es como un PIPE entre dos máquinas que se comunican por red

s_client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

s_client.connect(('localhost', 12345))
while True:
    mensaje = input('Introduce un mensaje: ')
    s_client.send(mensaje.encode())
    if mensaje == 'close':
        break
print('Cerrando conexión')
s_client.close()