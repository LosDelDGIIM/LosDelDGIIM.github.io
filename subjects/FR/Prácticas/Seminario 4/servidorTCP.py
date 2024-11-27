import socket
# Un socket es como un PIPE entre dos máquinas que se comunican por red

s_server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

s_server.bind(('', 12345))

# Se almacenan colas de conexiones entrantes, con un buffer de tamaño 1
s_server.listen(1)

# Se acepta la conexión entrante
# sc: socket cliente, addr: dirección del cliente
sc, addr = s_server.accept()

while True:
    recibido = sc.recv(1024)
    if recibido.decode() == 'close':
        break
    print('Recibido:', recibido.decode(), 'de', addr[0], ':', addr[1])
    #sc.send(recibido)  No es necesario enviar el mensaje de vuelta

print('Cerrando conexión')
sc.close()
s_server.close()