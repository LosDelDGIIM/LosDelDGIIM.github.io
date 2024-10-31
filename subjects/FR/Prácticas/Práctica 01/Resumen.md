# Fundamentos de Redes. Sesión 1 de Prácticas.

**Autor:** José Juan Urrutia Milán
***

- **Asignatura:** Fundamentos de Redes.  
- **Curso Académico:** 2024-25.
- **Grado:** Doble Grado en Ingeniería Informática y Matemáticas.
- **Profesor:** Jorge Navarro Ortiz.
- **Descripción:** Resúmen de la Práctica 1.

# Primera parte
Esta primera parte de la práctica trata de la configuración estática (manual) y automática de las tablas de encaminamiento de varios routers, usando para ello el laboratorio 3.7.  
  
## Introducción
Una vez leídos los manuales de la práctica y comprendido la topología de red del laboratorio 3.7 en islas, procederemos a realizar la configuración estática y automática de las tablas de encaminamiento tanto de los routers como de los PCs.

## Encaminamiento estático
Conformando equipo los que se encuentren en una misma isla, esta primera parte trata sobre la configuración manual de las tablas de encaminamiento de todos los PCs y de las tablas de encaminamiento para los routers 1, 2 y 3 de dicha isla.  
  
Suponiendo que nos encontramos en la isla `x`, encontramos 3 redes en nuestro entorno:
- `33.x.1.0/24`
- `33.x.2.0/24`
- `33.x.3.0/24`
- `172.16.x.0/24`

Utilizando `ifconfig`, resulta que la IP de nuestro PC es la `33.x.1.2`, por lo que nos encontramos en el `PCx_1`. Teniendo esto en cuenta, nos dispondremos a configurar la tabla de encaminamiento de nuestro PC y la tabla de encaminamiento de nuestro router (`Rx_1`, poniéndonos de acuerdo con nuestro compañero de `PCx_2` para no hacerlo dos veces). Esto es fácil extrapolarlo al resto de ordenadores.

### Configuración de tabla de PC
Para mostrar la tabla de encaminamiento de nuestro PC, podemos usar `route -n`.  
Tenemos que añadir simplemente dos entradas a dicha tabla:
- La entrada para el acceso a cualquier equipo de nuestra misma red (viene ya configurada en el equipo, ya que se condigura al asignar la IP del dispositivo a una interfaz de red), mediante:
    - Red destino: `33.x.1.0/24`.
    - Siguiente salto: `*` (al estar en la misma red, nos comunicamos directamente con él).
- La entrada para el acceso a cualqueir otra red:
    - Red destino: `0.0.0.0` (cualquiera).
    - Siguiente salto: `33.x.1.1` (nuestro router).
    - Para ello, usaremos: `route add default gw 33.x.1.1`.
  
Si quisiésemos que para acceder a la red `A.B.C.D` con máscara `M.N.O.P` se encamine a través de la IP `W.X.Y.Z`, usaríamos:
```
route add -net A.B.C.D netmask M.N.O.P gw W.X.Y.Z
```

### Configuración de tabla de router
Para configurar manualmente la tabla de encaminamiento de nuestro router (en este caso, `Rx_1`), nos conectaremos a él usando la herramienta `winbox_ubuntu1204.exe` (ha de ejecutarse con `wine`). Respecto a la IP, como está en la misma red que nosotros (tenemos conexión directa por cable), podemos usar la IP de la red de datos de nuestro router (`33.x.1.1`). Evidentemente, también podríamos usar su IP de la red de gestión.
Dentro de este, deberemos configurar el acceso a las redes `33.x.2.0/24` y `33.x.3.0/24`. Para ello:  
- Accedemos a la interfaz de `IP > Routes`.
- Pulsamos en Añadir, y añadimos esas dos redes:
    - Para la primera red, ponemos como dirección de destino `33.x.2.0/24` y como gateway el router `Rx_2`: `172.16.x.2`.
    - Para la segunda red, ponemos como dirección de destino `33.x.3.0/24` y como gateway el router `Rx_3`: `172.16.x.3`.  
  
Y ya tendremos terminada esta primera parte de encaminamiento estático.  
Esperaremos a que el resto de nuestra isla termine de cofigurar sus routers. Cuando esto suceda, podremos comprobar el buen funcionamiento de la red intentando hacer ping a un equipo de la red `33.x.2.0/24` y a otro equipo de la red `33.x.3.0/24`:
```
ping 33.x.2.2
ping 33.x.3.2
```
Si todo funciona, acabamos de demostrar que hemos hecho bien el encaminamiento estático.

## Encaminamiento dinámico
Suponiendo que seguimos en el mismo equipo: `33.x.1.2`, trataremos ahora de hacer este segundo ejercicio.  
Ahora, borraremos las tablas de encaminamiento que rellenamos en el ejercicio anterior, usando la interfaz que nos proporciona `winbox`.  
El ejercicio consiste en configurar todos los routers (1, 2, 3, 4, 5 y 6) de nuestra red, mediante el protocolo RIP, enfocado en rellenar tablas de encaminamiento mediante el menor número de saltos.  
  
De esta forma, nos pondremos de acuerdo con nuestra isla en qué PC se encarga de configurar cada router (hay 6 PCs y 6 routers, luego cada PC puede configurar un router).  
Supongamos que somos los encargados de configurar el router `Rx_6`:  
  
Para ello, nos conectaremos a él usando la herramienta que usamos en el ejercicio anterior (`winbox_ubuntu1204.exe`). En este caso, como no estamos en la misma red, estamos obligados a usar la IP de la red de gestión de nuestro router.
Una vez dentro del router, abriremos la pestaña `Routing > RIP`.  
Dentro de la pestaña de `Interfaces`, añadiremos dos interfaces para el router (por ejemplo, `ether1` y `ether4`).  
Posteriormente, nos dirigiremos a la pestaña `Network` e introduciremos las IPs de nuestro router (es decir, cada una de las IPs que tiene nuestro router, en cada red):
- Primero, especificaremos la IP `172.17.x.6`.
- Posteriormente, indicamos la IP `220.10.10.x`.  
  
Una vez hecho esto, hemos finalizado de configurar nuestro router.  
Ahora, sólo falta esperar a que el resto de nuestro equipo termine de configurar cada uno su router.  
Una vez conigurados todos, podremos observar en la pestaña de `IP` que, efectivamente, el router tiene acceso al resto de IPs de los routers.  
  
Finalmente, para probar que todo funciona, podemos usar el comando `ping -R [IP]`, para realizar ping desde nuestro equipo a cualquier otro o a un router, obteniendo la lista de nodos intermedios por los que pasó el paquete.  
Un buen ejemplo de funcionamiento es realizar un ping al router `Rx_6`, ya que `ping -R 172.17.x.6` debería mostrarnos que el paquete ICMP pasó por los routers: 1, 4 (o 5) y 6.

# Segunda parte
Esta segunda parte de la práctica trata sobre los firewall de red que tenemos en los routers MicroTick. Usaremos para ello el laboratorio 3.7.  
Existen dos tipos principales de cortafuetos, de filtrado o de aplicación (proxys). En esta práctica, usaremos los primeros.  
  
## Reglas
Para definir reglas en un firewall, debemos especificar dos opcciones:
- El **criterio de selección**: cómo identificar ciertos paquetes. Por ejemplo, cualquier paquete que entre al puerto `x`, cualqueir paquete que llegue de esta IP, ...
- La **acción** a realizar sobre dicho paquete.
  
Encontramos distintos tipos de acciones a realizar:
- **accept:** Acepta los paquete que cumplen el criterio de selección.
- **drop:** Descarta los paquetes que cumplan el criterio de selección.
- **reject:** Además de descartar el paquete seleccionado, el router envía un mensaje ICMP del tipo que se especifique.
  
Las reglas se ejecutan en orden, de forma que llega un paquete, se consulta en la tabla del firewall y la primera regla que tenga un criterio de selección compatible con el paquete será la que se aplique.  
Normalmente, los firewalls se configuran de forma que se acepten una serie de paquetes y que se descarten todos los que no coincidan con esos (para ello, añadir una regla drop que descarte cualquier paquete al final de la tabla).

#### Cadenas
Las reglas se asocian con un criterio de selección previo dependiendo del tipo de paquetes a las que se aplican. Estos criterios de selección previo reciben el nombre de **cadenas**. Podemos encontrar las cadenas:
- **INPUT**: Reglas que se aplican a paquetes que tienen como dirección destino alguna IP del router. Paquetes que van dirigidos al propio router.
- **OUTPUT:** Reglas que se aplican a paquetes que tienen como dirección de origen alguna IP del router. Paquetes que son generados por el propio router.
- **FORWARD:** Reglas que se aplican a paqeutes que reenvía el router. Es decir, paquetes que ni se han generado ni van al propio dispositivo, sino tráfico que lo atraviesa.  
  
Para el desarrollo de la práctica, usaremos sólo la cadena **forward**, ya que un mal uso de **input** o **output** (como acciones *drop* con tablas de firewall no bien configuradas) puede dejar un router innaccesible.

## Ejercicio 1
Como primer ejercicio, nos situaremos en `PCX_1` y queremos conectarnos a través de `RX_1` a `PCX_3` con *ssh*. Configuraremos el firewall en `RX_1` de forma que sólo dejemos pasar el tráfico ssh en cualquier sentido (que `PCX_1` se conecte a `PCX_3` y viceversa) y que no deje pasar cualquier otro tráfico (de forma que no deje pasar *ping*, por ejemplo).

### Realización
Suponiendo que tenemos bien configuradas las tablas de encaminamiento de los PCs y de los routers `RX_1` y `RX_2`, configuraremos el firewall solo de `RX_1`, dejando `RX_2` tal y como nos lo hemos encontrado.  
  
Para configurar el firewall en `RX_1`, accederemos al menú `IP --> Firewall --> Filter Rules` y añadiremos varias nuevas reglas, indicando (en orden):  
1. En *General*, indicaremos:
    - Chain: *forward*.
    - Source: La IP de `PCX_3` o si queremos, la red de `PCX_3` para que cualquier equipo pueda hacerlo.
    - Procolo: *6 (tcp)*.
    - Source port: *22* (el de ssh).
    - En la pestaña *Action*, indicaremos *accept*.  
2. En *General*, indicaremos:
    - Chain: *forward*.
    - Source: La IP de `PCX_1` o si queremos, la red de `PCX_1` para que cualquier equipo pueda hacerlo.
    - Procolo: *6 (tcp)*.
    - Destination port: *22* (el de ssh).
    - En la pestaña *Action*, indicaremos *accept*.  
3. En *General*, indicaremos:
    - Chain: *forward* y nada más para que coja cualquier paquete que atraviese el router.
    - En la pestaña *Action*, indicaremos *drop*.  
  
Si ahora probamos con las configuraciones realizadas, sólo nos debería dejar conectarnos con `ssh` desde un equipo a otro. Para ello:
- En el equipo que actúe como servidor, ejecutar:
```bash
sudo systemctl start ssh.service
```
- En el equipo que se conecta al servidor:
```bash
ssh usuario_PC_remoto@IP
```
Donde `usuario_PC_remoto` seguramente sea `administrador`.  
  
Si ahora probamos a usar otro protocolo como por ejemplo ICMP mediante un ping de `PCX_1` a `PCX_3`, no debería funcionar, ya que la última entrada de la tabla debería descartar dichos paquetes.

## Ejercicio 2
Ahora, queremos permitir que `PCX_3` pueda realizar *ping* a `PCX_1` pero que `PCX_1` no peudda realizar *ping* a `PCX_3`. Queremos que cualquier otro paquete se descarte.

### Realización
para ello, en `RX_1` nos dirigiremos al menú `IP --> Firewall --> Filter Rules` y añadiremos varias nuevas reglas, indicando (en orden):
1. En *General*, indicaremos:
    - Chain: *forward*.
    - Source: La IP de `PCX_3` o la de su red.
    - Protocolo: *1 (icmp)*.
    - En la pestaña *Advanced*:
    - ICMP Options --> ICMP Type: *8 (Echo Request)*.
    - En la pestaña *Action*, *accept*.
2. En *General*, indicaremos:
    - Chain: *forward*.
    - Destination: La IP de `PCX_3` o la de su red.
    - Protocolo: *1 (icmp)*.
    - En la pestaña *Advanced*:
    - ICMP Options --> ICMP Type: *0 (Echo Repply)*.
    - En la pestaña *Action*, *accept*.
3. En *General*, indicaremos:
    - Chain: *forward* y nada más para que coja cualquier paquete que atraviese el router.
    - En la pestaña *Action*, indicaremos *drop*.  
  
Ahora, si intentamos hacer *ping* desde `PCX_1` a `PCX_3` no funcionará, pero si lo hacemos desde `PCX_3` a `PCX_1` sí debe funcionar.
