<br>

# Fundamentos de Redes. Práctica I (Sesiones 1 y 2)

**Autor:** Arturo Olivares Martos
***

- **Asignatura:** Fundamentos de Redes
- **Curso Académico:** Actualizado al curso 2024-25
- **Grado:** Preguntas comunes para el Grado en Ingeniería Informática y los Dobles Grados
<!--- **Grupo:** A.-->
<!--- **Profesor:** Ignacio Rojas Ruiz.-->
<!--- **Fecha:** 19-10-2023.-->
- **Descripción:** Examen de la Práctica 1 (sesiones 1 y 2).

El examen de la Práctica 1 (sesiones 1 y 2) consiste en un cuestionario de 10 preguntas tipo test, donde cada error resta 1/3 puntos.
La preguntas se sacaron de un banco de preguntas y salían aleatorias, por lo que los exámenes no coincidieron. En este documento hemos buscado juntar todos los exámenes en un mismo fichero.
______


1. Considerando la topología de la red de datos del laboratorio, si configuramos la acción `DROP` para la cadena `FORWARD` en `RX_1` de la isla `X`:
    - ( ) Se podrá seguir haciendo `ping` desde el router `RX_1` a cualquiera de las interfaces de la red.
    - ( ) El router `RX_1` podrá seguir siendo configurado desde cualquiera de sus interfaces.
    - ( ) Excluyendo la red de gestión, la red `33.X.1.0/24` dejará de ser alcanzable desde cualquier interfaz externa a dicha red.
    - (x) Todas las respuestas son correctas.

2. ¿Cuál de estas afirmaciones es cierta?.
    - ( ) La acción `Accept`, permitirá pasar a todos los paquetes, independientemente de si cumplen el criterio de selección o no.
    - (x) El orden en el que se definen las reglas del firewall en un router es importante.
    - ( ) La acción `Drop` es conveniente definirla al principio de una lista de reglas.
    - ( ) Las acciones `Drop` y `Reject` hacen lo mismo.

3. ¿A qué se refiere la cadena `INPUT` a la hora de definir una regla para un firewall en el router?.
    - (x) Se refiere al tráfico (paquetes) que tienen como destino una de las IPs del router.
    - ( ) No se refiere a ningún tráfico que pase por el router.
    - ( ) Se refiere al tráfico (paquetes) que atraviesa el router y entra por uno de sus interfaces.
    - ( ) Se refiere al tráfico que tiene como destino una de las salidas del router.

4. Considerando la topología de la red de datos del laboratorio, ¿cuál de las siguientes configuraciones para la tabla de enrutamiento sería válida para que `RX_2` supiera alcanzar cualquier interfaz dentro de su isla `X`?
    - ( ) <table border="1"><thead><tr><th>Red de Destino</th><th>Pasarela (gw)</th></tr></thead><tbody><tr><td>`33.X.2.0/24`</td><td>`ether1`</td></tr><tr><td>`172.16.X.0/24`</td><td>`ether2`</td></tr><tr><td>`33.X.1.0/24`</td><td>`172.16.X.1`</td></tr><tr><td>`33.X.3.0/24`</td><td>`172.16.X.3`</td></tr><tr><td>`172.17.X.0/24`</td><td>`172.16.X.5`</td></tr><tr><td>`220.10.10.X/24`</td><td>`172.16.X.5`</td></tr></tbody></table>
    - ( ) <table border="1"><thead><tr><th>Red de Destino</th><th>Pasarela (gw)</th></tr></thead><tbody><tr><td>`33.X.2.0/24`</td><td>`ether1`</td></tr><tr><td>`172.16.X.0/24`</td><td>`ether2`</td></tr><tr><td>`33.X.1.0/24`</td><td>`172.16.X.1`</td></tr><tr><td>`33.X.3.0/24`</td><td>`172.16.X.3`</td></tr><tr><td>`172.17.X.0/24`</td><td>`172.16.X.4`</td></tr><tr><td>`220.10.10.X/24`</td><td>`172.16.X.5`</td></tr></tbody></table>
    - ( ) <table border="1"><thead><tr><th>Red de Destino</th><th>Pasarela (gw)</th></tr></thead><tbody><tr><td>`33.X.2.0/24`</td><td>`ether1`</td></tr><tr><td>`172.16.X.0/24`</td><td>`ether2`</td></tr><tr><td>`33.X.1.0/24`</td><td>`172.16.X.1`</td></tr><tr><td>`33.X.3.0/24`</td><td>`172.16.X.3`</td></tr><tr><td>`172.17.X.0/24`</td><td>`172.16.X.5`</td></tr><tr><td>`220.10.10.X/24`</td><td>`172.16.X.4`</td></tr></tbody></table>
    - (x) Todas las respuestas son válidas.

5. A la hora de establecer una entrada en una tabla de encaminamiento de un router Mikrotik, ¿qué campos principales añadiría?
    - ( ) La dirección del próximo salto
    - ( ) La dirección de red origen y la pasarela por defecto
    - ( ) La dirección de red destino y la dirección del salto origen
    - (x) La dirección de red destino y la dirección del próximo salto

6. Las acciones básicas que se pueden utilizar en el firewall de un router Mikrotik son:
    - (x) `reject`, `drop`, `accept`
    - ( ) `reject`, `drop`, `input`
    - ( ) `reject`, `forward`, `accept`
    - ( ) `react`, `drop`, `accept`

7. Cuando un paquete IP llega a un router, ¿cómo sabe este hacia dónde reenviarlo?
    - ( ) Mediante la comparación de la dirección IP de origen con las entradas en la tabla de encaminamiento
    - ( ) Mediante la comparación de la dirección MAC de origen con la entradas en la tabla encaminamiento
    - (x) Mediante la comparación de la dirección IP de destino con las entradas en la tabla de encaminamiento
    - ( ) Mediante la comparación de la dirección MAC de destino con las entradas en la tabla encaminamiento

8. Considerando la topología de las redes del laboratorio y asumiendo que `RX_4` solo conoce las redes que tiene directamente conectadas, ¿cómo se conectaría a dicho router desde `PCX_1` para administrarlo?
    - ( ) A través de cualquiera de sus interfaces.
    - (x) A través de la red de gestión.
    - ( ) No habría posibilidad de administrarlo.
    - ( ) A través de la red gestión o la interfaz perteneciente a la red `172.16.X.0/24`

9. Asumiendo que el protocolo RIP está correctamente configurado en la red de datos de la isla `X`, ¿qué pasaría si se cae la interfaz `eth1` con IP `33.X.2.1` de `RX_2`?
    - (x) La red `33.X.2.0/24` dejaría de ser alcanzable desde cualquier interfaz externa a dicha red.
    - ( ) La red `33.X.2.0/24` seguiría siendo alcanzable a través de la red de gestión.
    - ( ) La red `33.X.2.0/24` seguiría siendo alcanzable porque RIP es un protocolo dinámico capaz de encontrar rutas alternativas de forma autónoma.
    - ( ) `PCX_3` y `PCX_4` podrían alcanzar el resto de las interfaces de la red de datos, pero ellos dejarían de ser alcanzables.

10. Considerando la topología de la red de datos del laboratorio, ¿qué lista de redes elegiría para configurar el protocolo RIP en `RX_6` de la isla `X`?
    - ( ) `172.16.X.0/24` y `172.17.X.0/24`
    - ( ) `33.X.1.0/24`, `33.X.2.0/24`, `33.X.3.0/24` y `172.16.X.0/24`
    - ( ) `33.X.1.0/24`, `33.X.2.0/24`, `33.X.3.0/24`, `172.16.X.0/24`, `172.17.X.0/24` y `220.10.10.0/24`
    - (x) `172.17.X.0/24` y `220.10.10.0/24`

11. Considerando la topología de la red de datos del laboratorio, ¿cuál de las siguientes configuraciones para la tabla de enrutamiento sería válida para que `RX_4` supiera alcanzar cualquier interfaz dentro de su isla `X`?
    - ( ) Ninguna respuesta es correcta
    - ( ) <table border="1"><thead><tr><th>Red de Destino</th><th>Pasarela (gw)</th></tr></thead><tbody><tr><td>`172.16.X.0/24`</td><td>`ether1`</td></tr><tr><td>`172.17.X.0/24`</td><td>`ether2`</td></tr><tr><td>`33.X.2.0/24`</td><td>`172.16.X.2`</td></tr><tr><td>`33.X.3.0/24`</td><td>`172.16.X.3`</td></tr><tr><td>`0.0.0.0`</td><td>`172.17.X.4`</td></tr></tbody></table>
    - ( ) <table border="1"><thead><tr><th>Red de Destino</th><th>Pasarela (gw)</th></tr></thead><tbody><tr><td>`172.16.X.0/24`</td><td>`ether1`</td></tr><tr><td>`172.17.X.0/24`</td><td>`ether2`</td></tr><tr><td>`33.X.1.0/24`</td><td>`172.16.X.1`</td></tr><tr><td>`33.X.2.0/24`</td><td>`172.16.X.2`</td></tr><tr><td>`33.X.3.0/24`</td><td>`172.16.X.3`</td></tr><tr><td>`220.10.10.X/24`</td><td>`172.17.X.4`</td></tr></tbody></table>
    - (x) <table border="1"><thead><tr><th>Red de Destino</th><th>Pasarela (gw)</th></tr></thead><tbody><tr><td>`172.16.X.0/24`</td><td>`ether1`</td></tr><tr><td>`172.17.X.0/24`</td><td>`ether2`</td></tr><tr><td>`33.X.1.0/24`</td><td>`172.16.X.1`</td></tr><tr><td>`33.X.2.0/24`</td><td>`172.16.X.2`</td></tr><tr><td>`33.X.3.0/24`</td><td>`172.16.X.3`</td></tr><tr><td>`220.10.10.X/24`</td><td>`172.17.X.6`</td></tr></tbody></table>

12. ¿Cuál de los siguientes comandos usaría para configurar la ruta por defecto (`default gateway`) de `PCX_1` a través de la red de datos?
    - (x) `route add default gw 33.X.1.1`
    - ( ) `route add default gw 33.X.1.0/24`
    - ( ) `route add -net 0.0.0.0 netmask 0.0.0.0 gw ether1`
    - ( ) `route add -net 33.X.1.0 netmask 255.255.255.0 gw 33.X.1.1`

13. Las cadenas básicas en las que se agrupan las reglas de filtrado de paquetes en un router Mikrotik son:
    - ( ) `INPUT`, `OUTPUT`, `THROUGH`
    - (x) `INPUT`, `OUTPUT`, `FORWARD`
    - ( ) `INSIDE`, `OUTSIDE`, `FORWARD`
    - ( ) `LEFT`, `RIGHT`, `UP`, `DOWN`

14. Asumiendo que la red de datos del laboratorio está correctamente configurada para que haya alcanzabilidad total en la red, si configuramos la acción `DROP` para la cadena `INPUT` en cualquiera de los routers del laboratorio:
    - ( ) El router donde aplicamos la regla sigue siendo administrable puesto que puede seguir recibiendo mensajes.
    - ( ) El router donde apliquemos la regla podrá recibir mensajes, pero no podrá contestarlos.
    - ( ) Todas las respuestas son correctas.
    - (x) Todas las interfaces seguirán siendo alcanzables.

15. Si toda aquella información que no vaya a la subred a la que pertenece cierto dispositivo se reenvía hacia un punto de salida dentro de dicha subred, ¿de qué se está hablando?
    - ( ) Máscara de subred
    - ( ) Dirección de broadcast
    - ( ) Próximo salto
    - (x) Pasarela por defecto

16. En el laboratorio existen dos redes principales. Suponga que se ubica en un PC de la isla 1 y desea ver las entradas en las tablas de encaminamiento del `R4_1` ¿es posible?.
    - ( ) Ninguna de las anteriores afi rmaciones es correcta.
    - ( ) Sí. Aunque ese router no pertenece a la isla 1, sería alcanzable por la red de datos y por lo tanto se podría.
    - (x) Sí, utilizando winbox a través de la IP `192.168.4.11`
    - ( ) Sí, si la interfaz de la red interna está habilitada.
    
17. ¿Cuál es el menú que debemos elegir en un router Mikrotik usando Winbox para utilizar el encaminamiento dinámico con RIP?
    - ( ) IP->RIP.
    - ( ) Routing->Dynamic Protocols->RIP.
    - (x) Routing->RIP->Networks.
    - ( ) IP->Routing Information Protocol.