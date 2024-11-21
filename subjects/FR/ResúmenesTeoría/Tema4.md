# Tema 4. Seguridad en Redes.

Se verán algunos mecanismos básicos, como un certificado digital.

##### Aspectos de seguridad
Los aspectos de seguridad que vamos a ver son: 
- Confidencialidad: Transmitimos algo a un receptor y solo queremos que dicho receptor sea capaz de ver el mensaje.
    Se consigue con el cifrado.
- Autentificación: Queremos estar seguros de saber quién es exactamente el emisor.
    - Reto-Respuesta.
    - Cifrar con K_privA() o doble cifrado.
- Integridad de los datos: Estar seguro de que algunos datos no han sido manipulados.
    Se consigue con funciones hash o compendios (resúmenes del mensaje).
- No repudio: No nos podemos echar atrás de haber participado en una transacción. Prueba legal.
    Se consigue con la firma digital o con doble cifrado con certificado
- Disponibilidad (no se verá, requiere de cosas que no se ven. Requiere de líneas de respaldo, servidores duplicados, ...): 
    Tenemos un banco con todo pero puede ser suceptible de ser atacado y a lo mejor la mitad del día está y la otra mitad no.
    Analogía con WhatsApp.

Importante distinguir entre:
- Firma digital: Algo para conseguir algo.
- Certificado: Una herramienta. Puede conseguir confidencialidad, autentificación, no repudio, ... si lo usamos bien. Por sí solo no consigue nada.

Ejercicio típico: tenemos estos protocolos, ..., ¿qué aspectos de seguridad se cumplen?

Veremos:
- Algoritmos de clave secreta y clave pública.
- Algoritmos de intercambio de claves.
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

# Cifrado (para conseguir confidencialidad)
Suponiendo que los cifrados funcionan (parte matemática), buscamos que el protocolo no tenga debilidades.

Tendremos un texto plano a transmitir (P) y lo cifraremos con una función E_k encoder, que dará lugar a un texto cifrado (C), el cual se mandará a través de un canal de comunicaciones.
Llegará al otro extremo y será descifrado para poder ver los datos, con una función D_k de desencriptado y con una clave.

Veremos dos tipos de algoritmos de cifrado:
- Misma clave pero funciones E y D son distintas.
- Claves distintas pero las funciones E y D son iguales.

Y 3 algoritmos de cifrado.

Tipos de algoritmos de cifrado:
- Cifrado simétrico (clave secreta).
- Cifrado asimétrico (clave pública).

## Cifrado simétrico (de clave secreta)
Se llama simétrico porque usa la misma clave para cifrar así como para descifrar. Usan la misma clave, hay simetría. 
Esto significa que es de clave secreta (que la comparten los dos).

### DES, Data Encryption Standard
Texto plano de 64 bits (una palabra de 64 bits) y sale una palabra de 64 bits.
Puede ejecutarse en tiempo real.
Usa **claves de 56 bits** (son pocos, 2^56 pruebas se puede resolver por fuerza bruta rápido) y lo que hacemos es:
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

#### Evitar que DES sea de sustitución
Que las E_k realimenten la entrada de la sigiente.

### IDEA, International Data Encryption Algorithm
Pasa palabras de 64 en palabras de 64 con claves de 128 bits.
Puede ejecutarse en tiempo real.

## Cifrado asimétrico, (de clave pública)
Tenemos una clave pública del usuario A (la conoce todo el mundo). Asociado a cada clave pública hay una única clave privada (solo la conoce A).
**Si ciframos con la clave pública, solo podemos descifrar con la clave privada y viceversa.**

Hace falta algún requisito, pero si hay algo hecho con una clave privada, solo lo hemos podido haber hecho nosotros. De cara a la autentificación.

### RSA (APRENDERSE LAS FORMULAS Y ALGORITMO)
Coge p y q primos (grandes, > 10^{100} para que sea distinto de romper)
n = p * q
z = (p-1)(q-1)
Elegimos d primo relativo con z
Tenemos que buscar e tal que: e * d mod z = 1

Usaremos como claves:
- Pública: (e,n)
- Privada: (d,n)

Cifrar: C = P^e mod n
Descrifrar: P = C^d mod n

*Ver ejemplo*

# Autenticación
## Lo más sencillo
Si somos un equipo A y queremos autenticarnos a un servidor B, lo más sencillo es:
Que B almacene en BBDD el par (Usuario, clave).
Que A envíe a B su usuario (A) y su clave (K_A), que el servidor confirme si son correctas y que devuelva un mensaje de aceptación o rechazo.
- Usado por PAP (Password Autentication Protocol)

## Reto-Respuesta
Tenemos un usuario A, y un usuario B.
B tiene una BBDD con la clave que comparten A y B para A (para cada usuario).

Lo primero que tenemos que enviar es la identidad (A), que no es un dato sensible.
Lo que va a mandar B es un reto: un número aleatorio.
A calcula X, un cifrado con la clave compartida entre A y B del reto.
B calcula X': descifra con la clave compartida X, y compara si X' es igual al reto.

Falta ahora autenticar B:
B manda a A su identidad (B).
A manda un reto a B.
B manda Y, ...
A calcula Y' y comprueba si era igual al reto.

En este momento, A está seguro de que está hablando con B y que B está hablando con A.

### Problemas:
- Ataque por reflexión: 
    - A manda identidad a B.
    - B responde con reto.
    - A manda a B autentificación con el mismo reto para que el propio B responda a su reto.
    - Cuando B responda, sabremos la respuesta a dar al reto dado por B, con lo que respondemos con la propia respuesta de B.
- Solución: Dominios de retos distintos.

- Ataque por repetición: Si hubiera un espía, no sabe cual es la clave, pero para cada reto puede averiguar cual es su respuesta correcta.
- Solución: Hacer que los retos sean irrepetibles (nonce). Por ejemplo: Reto = fecha + hora + nº aleatorio.

# Distribución de claves (no está relacionado con nada, es una herramienta)
## Intercambio de Diffie-Hellman
Dos usuarios, A y B que quieren tener una misma clave secreta compartida.
- A se inventan números n, g y x.
- A envía a B: n, g y (g^x mod n).
- B se inventa un número y.
- B envía a A: g^y mod n.
- A hace: (g^y mod n)^x = g^{xy} mod n.
- B hace: (g^x mod n)^x = g^{xy} mod n.
La clave compartida será: g^xy mod n

### Problema
Suceptible de ataque man-in-the-middle:
- Tenemos A, que manda n, g g^x mod n a un atacante.
- El atacante genera z y calcula g^xz mod n.
- El atacante devuelve g^z mod n a A.
- Atacante envia a B n, g, g^z mod n.
- B devuelve g^y mod n.

El atacante tiene una clave secreta compartida con A y con B, de forma que para que A hable con B hace de intermediario.

# Funciones hash (para conseguir integridad)
Tenemos una función de forma que dada una palabra P, nos da una palabra a modo de resumen o compendio de los datos, R.
La palabra a introducir es de cualquier longitud, el resumen suele ser de longitud fija y es imposible obtener P a partir de R.

Dado un mensaje P, se envia P junto con su hash.
Para que no se pueda modificar el mensaje a P' e incluir el hash de P':
Enviamos P junto con el hash(P + K_{AB}), es decir, el hash de P concatenada con la clave compartida de A y de B.

Este hash(P + K_{AB}) se le suele llamar MAC (Message Autentification Code), o HMAC (Hash ...).

Algoritmos:
## MD5 (Message Digest)
Dado un mensaje P de K dígitos, necesitamos que sea múltiplo de 512 bits, con lo que mete un relleno: 1000...0
Parte el mensaje en trozos de longitud 512, mete el trozo en una caja MD5 y saca una de longitud 128.
Cada salida anterior sirve como entrada para la siguiente caja MD5.

## SHA (Secure Hash Algorithm)
Dado un mensaje P de K dígitos, necesitamos que sea múltiplo de 512 bits, con lo que mete un relleno: 1000...0
Parte el mensaje en trozos de longitud 512, mete el trozo en una caja SHA y saca una de longitud 160.
Cada salida anterior sirve como entrada para la siguiente caja SHA.

Igual pero con 160 (respecto a la vista del usuario).

# Firma digital (para conseguir no repudio)
Dos formas:
- Big brother.
- Doble cifrado (con certificados).

## Big brother (BB)
Usar una entidad fiable, un gran hermano en el que todo el mundo confía.

Tenemos una entidad A que quiere enviar a una entidad B y B quiere tener una prueba de que A le ha enviado eso.
BB es un servidor con una BD en la que dice que tal usuario A tiene una clave compartida con BB, K_A.

- A quiere enviar un mensaje a B, para lo cual se lo envía a BB: 
  (A, K_A(...))
    - Identificador (A).
    - Cifrar con clave K_A:
    - B, destinatario.
    - R_A, Resumen para dar integridad.
    - t, instante de tiempo.
    - P, texto plano.
- BB reenvía el mensaje a B, ahora cifrado con la clave K_B y añade algo más:
  K_B(A, R_A, t, P, K_BB(A, t, P))
    - Donde K_BB(A, t, P) es la firma digital, algo cifrado con la clave del BB (que solo la conoce él).

## Doble cifrado, Introducción
Si somos A, queremos mandar msg a B y:
- ciframos con K_privA(P), todo el mundo puede descifrarlo, pero solo lo ha podido cifrar A: conseguimos **Autentificación**.
- ciframos con K_pubB(P), solo B puede descifrarlo, conseguimos **Confidencialidad**.
- ciframos con K_pubA(P), no sirve para nada.

Lo juntamos (es conmutativo):
K_pubB(K_privA(P)): Conseguimos **confidencialidad y autentificación**.

Esto solo da no repudio si conseguimos demostrar que A es el dueño de K_pubA y que B es el dueño de K_pubB.
Necesitamos de alguien fiable que lo haga, o de un certificado digital.

# Autoridades de certificación
Alguien de quien todos nos fiamos.

# Certificado digital
No consigue ningún aspecto de seguridad por sí solo, sino que es una herramienta para conseguir cosas.
Contiene tres cosas (las dos primeras muy importantes):
- Una identidad: A.
- Clave pública: de A.
- Más información: como el periodo de validez.

Todo ello firmado (cifrado) por la clave privada de la Autoridad de Certificación, K_AC.
De esta forma, cualquiera puede ver que A tiene K_A, y sabremos que lo ha hecho AC.
Cuando actualizamos los programas que usan los certificados, actualizamos las claves públicas de las ACs.


Un particular puede generar una propia autoridad de autentificación, pero que no serán AC fiables.

# Protocolos seguros
## PGP (Pretty Good Privacy) (Hay que sabérselo)
Tenemos el texto plano P, del que generamos         R = MD5(P).
Tendremos una firma digital                         FD = K_privA(R).
Comprimimos (para enviar menos datos):              Z = ZIP(FD + P).
Ciframos:                                           C = IDEA_k(Z) + K_pubB(k)     Con k una clave privada específica para esta sesión (si alguien saca la clave, solo puede sacar 1 msg)
El mensaje enviado se codifica base 64:             M = B64(C)

(base 64: en vez de usar 8 bits, usa 6, ascii simplificado)
Esto se envía por un canal al receptor:

Descodifica:                                        C = B64^{-1}(M)
Descifra con la clave privada                       K = K_privB(K_pubB(K))
                                                    Z = IDEA_k^{-1}(IDEA_k(Z))    
                                                    FD + P = ZIP^{-1}(Z)
                                                    R = K_pubA(FD)
                                                    R' = MD5(P)
                                                    Comprobar si R' = R para integridad de los datos.
                                                    
- Confidencialidad: Sí, clave de sesión.
- Integridad:       Sí, un reto para ver si texto plano ha sido modificado.
- Autentificación:  Sí, he cifrado con clave privada.
- No repudio:       Se puede conseguir con un certificado digital para claves privadas y públicas. Si no, no.

## TSL (Transport Secure Layer), SSL
Hacen lo mismo.

## IPSec
