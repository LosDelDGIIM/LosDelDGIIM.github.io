# Tema 4. Seguridad en Redes.

Se verán algunos mecanismos básicos, como un certificado digital.

Los aspectos de seguridad que vamos a ver son: 
- Confidencialidad: Transmitimos algo a un receptor y solo queremos que dicho receptor sea capaz de ver el mensaje.
    Se consigue con el cifrado.
- Autentificación: Queremos estar seguros de saber quién es exactamente el emisor.
- Integridad de los datos: Estar seguro de que algunos datos no han sido manipulados.
    Se consigue con funciones hash o compendios (resúmenes del mensaje).
- No repudio: No nos podemos echar atrás de haber participado en una transacción. Prueba legal.
    Se consigue con la firma digital.
- Disponibilidad (no se verá, requiere de cosas que no se ven. Requiere de líneas de respaldo, servidores duplicados, ...): 
    Tenemos un banco con todo pero puede ser suceptible de ser atacado y a lo mejor la mitad del día está y la otra mitad no.
    Analogía con WhatsApp.

Importante distinguir entre:
- Firma digital: Algo para conseguir algo.
- Certificado: Una herramienta. Puede conseguir confidencialidad, autentificación, no repudio, ... si lo usamos bien. Por sí solo no consigue nada.

Ejercicio típico: tenemos estos protocolos, ..., ¿qué aspectos de seguridad se cumplen?

Veremos:
- Algoritmos de clave secreta y clave pública.
- Protocolos seguros que lo usan: IPSec, TLS, PGP.

# Introducción
Necesitamos seguridad en todos los aspectos en todas las redes.
Cuando tenemos algo de seguridad, el punto débil dice qué tan seguro es todo.

Ataques básicos:
- Sniffing: Escuchar comunicaciones, Wireshark es un sniffer.
- Spoofing (o phising): Suplantar a alguien.
- Man_in_the_middle: Se pone a alguien en medio entre dos equipos que se conectan por un enlace seguro.
    HTTPS utiliza SSL para transmitir los datos. SSL soporta muchas familia de cifrados, unas más seguras que otras.
    Podeíamos poner un server en medio con el que se habría un certificado y funcionaba de intermediario.
- Denial_of_service: Todo va bien pero te mando tantos paquetes que deja de funcionar. Distributed si los ataques vienen de muchos sitios.
- Malware: Software malicioso.
    Ransomware: Se encriptan todos o parte de los datos y se requiere un rescate de los datos.

Intercambio de Diffie-Hellman: Intercambio de claves.
Para claves serias no podemos realizarlo por una red (como el certificado digital):

# Cifrado
Suponiendo que los cifrados funcionan (parte matemática), el protocolo no tiene debilidades.

Tendremos un texto plano a transmitir (P) y lo cifraremos con una función E_k encoder, que dará lugar a un texto cifrado (C), el cual se mandará a través de un canal de comunicaciones.
Llegará al otro extremo y será descifrado para poder ver los datos, con una función D_k de desencriptado y con una clave.

Veremos dos tipos de algoritmos de cifrado:
- Misma clave pero funciones E y D son distintas.
- Claves distintas pero las funciones E y D son iguales.

Y 3 algoritmos de cifrado:

## Cifrado simétrico (DES, Data Encryption Standard)
Se llama simétrico porque usa la misma clave para cifrar así como para descifrar. Usan la misma clave, hay simetría. 
Esto significa que es de clave secreta (que la comparten los dos).

Texto plano de 64 bits (una palabra de 64 bits) y sale una palabra de 64 bits.
Clave de 56 bits (son pocos, 2^56 pruebas se puede hacer rápido) y lo que hacemos es:
- Transposición (desordenarlos) inicial.
- En medio, 16 iteraciones.
- Transposición inversa a la inicial.

Cada iteración:
tenemos 32 bits de la izquierda y hacemos XOR con algo que es función de los bits de la derecha.
Los bits de la izquierda los pasamos a la derecha y los de la derecha a la izquierda.

En resumen, desordenar bits y hacer XOR. 
Idea: si podemos implementarlo en hardware, podemos hacerlo en tiempo real.
De esta forma, si queremos codificar voz lo podemos hacer de esta forma.


##### Pregunta 1:
En general, existen dos tipos de cifrado: 
- De sustitución:   Coger letra A y cambiarla por K, B --> Z, ...
- De transposición: Cambiar el orden, desordenarlo.

El más seguro es transposición:
A sustitución podemos hacerle un ataque estadístico:
- SI vemos que una letra aparece un % de veces, podemos coger el % del español y sacar cierta información para romperlo.


##### Pregunta 2:
DES es sustitución, ya  que si metemos una palabra x de 64 bits, siempre sale lo mismo.
Veremos cómo evitar que sea de sustitución (ataques estadísticos), así como una clave más grande.
