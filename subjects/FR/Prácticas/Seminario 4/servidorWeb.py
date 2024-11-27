# Ejercicio 3: Servidor web   
# Seminario 4: Seminario aplicación cliente - servidor conexión TCP
# Fundamentos de Redes (FR)
# Autor: Juan José Ramos Muñoz - jjramos@ugr.es 
# Curso 2023 - 2024


import socket

INTERFACES=""   # estas son las interfaces en las que se escuchará. Podría indicarse solo la IP de una tarjeta.
PUERTO = 8080   # Puerto donde escuchará
TAMANIO_BUFFER=1024  # Se leen grupos de bytes.

# creamos un socket TCP (desde la aplicación se ve como un stream de bytes)
print("Creando socket TCP... ", end="")
######################################################################
## ... socket_escucha ..... (Completar)
s_server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
######################################################################
print("Ok.")

# indicamos en qué puerto debe escuchar. En los clientes no hace falta, los proporciona el sistema operativo.
print("Escuchando en interfaz"+str(INTERFACES)+" y puerto "+str(PUERTO)+ "... ", end="")
######################################################################
## ... socket_escucha ..... (Completar)
s_server.bind((INTERFACES, PUERTO))
######################################################################
print("Ok.")

# Le indicamos que espere una conexión entrante
print("Pasando a modo escucha... ", end="")
######################################################################
## ..... socket_escucha ..... (Completar)
s_server.listen(5)
######################################################################
print("Ok.")

# suponemos que este servidor no termina nunca...
while True:

    # Aceptamos una conexión, y copiamos los datos de la misma:
    print("Esperando nueva conexión... ", end="")
    ######################################################################
    ## ... socket_datos ... direccion_remota .... (Completar)
    sc, direccion_remota = s_server.accept()
    ######################################################################
    print("Conectado a "+str(direccion_remota)+".")

    # Leemos todos los bytes que nos lleguen hasta que haya dos saltos de línea seguidos:
    mensaje=""
    bytes_leidos=TAMANIO_BUFFER
    while bytes_leidos==TAMANIO_BUFFER:
        print("Esperando mensajes... ", end="")
        # Leemos los mensajes
        ######################################################################
        ## bytes = ...socket_datos.... TAMANIO_BUFFER ...(Completar)
        bytes = sc.recv(TAMANIO_BUFFER)
        ######################################################################
        print("Recibidos " + str(len(bytes))+" bytes.")

        # Actualizamos el número de bytes leidos.
        if not bytes:
            bytes_leidos=0
        else:
            bytes_leidos= len(bytes)
            mensaje=mensaje+bytes.decode("utf-8")
    # se muestra el mensaje
    print(mensaje)


    buffer_envio="HTTP/1.1 200 Ok\n\nHola caracola.".encode("utf-8")
    # enviamos el mensaje que se desea mostrar
    ######################################################################
    ## .... socket_datos ..... buffer_envio .... (Completar)
    sc.send(buffer_envio)
    ######################################################################
    # cerramos la conexion
    ######################################################################
    ## .... socket_datos ..... (Completar)
    sc.close()
    ######################################################################
s_server.close()
