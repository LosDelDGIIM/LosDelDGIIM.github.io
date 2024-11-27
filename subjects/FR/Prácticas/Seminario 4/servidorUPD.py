import socket
s_server = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

# El primer parámetro de bind es el nombre de las interfaces que aceptamos. En blanco aceptamos todas
s_server.bind(('', 12345))

data, clienteaddr = s_server.recvfrom(4096) # 4096 es el tamaño del buffer

print('Recibido:', data.decode(), 'de', clienteaddr[0], ':', clienteaddr[1])
s_server.sendto(b'Bienvenido a clase', (clienteaddr[0], clienteaddr[1]))    # b convierte el string en bytes
s_server.close()