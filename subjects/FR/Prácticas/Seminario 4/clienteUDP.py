import socket
# Un socket es como un PIPE entre dos máquinas que se comunican por red

s_client = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
# En localhost habría que poner la IP de la máquina servidor
# 12345 es el puerto por el que se comunica el cliente con el servidor
s_client.sendto(b'Hola Clase', ('localhost', 12345))    # b convierte el string en bytes

#s_client.bind(('', 12345))

data, servereaddr = s_client.recvfrom(4096) # 4096 es el tamaño del buffer

print('Recibido:', data.decode(), 'de', servereaddr[0], ':', servereaddr[1])

s_client.close()