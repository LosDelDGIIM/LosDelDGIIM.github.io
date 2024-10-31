# Fundamentos de Redes. Sesión 2 de Prácticas.

**Autor:** José Juan Urrutia Milán
***

- **Asignatura:** Fundamentos de Redes.  
- **Curso Académico:** 2024-25.
- **Grado:** Doble Grado en Ingeniería Informática y Matemáticas.
- **Profesor:** Jorge Navarro Ortiz.
- **Descripción:** Resúmen de la Práctica 2.

# Primera parte
Esta primera parte de la práctica trata sobre la configuración de routers como servidores DHCP, usando para ello el laboratorio 3.7.  
Es reconmendable mirar primero en la teoría el funcionamiento de DHCP.

## Ejercicio 1
Este primer ejercicio trata sobre la previa configuración en el PC del uso de DHCP (quitarle a la tarjeta de datos su IP e indicarle que use DHCP). Estaremos usando clientes ubuntu, luego será necesario trabajar con `netplan`.  
Posteriormente, nos conecaremos al servidor para configurarlo como un servidor DHCP, donde tendremos que especificiarle algunas opciones, entre ellas el interfaz por el que es servidor de DHCP y un pool de direcciones a asignar (qué rangos de direcciones puede asignar).  
Cuando esto esté listo, usaremos *wireshark* para ver si hemos configurado correctamente DHCP.  
  
### Realización
Suponiendo que nos encontramos en el `PCX_1` de la isla `X` y que queremos usar como servidor DHCP el router `RX_1` de IP `33.X.1.1`:  
1. En primer lugar, nos dirigimos al archivo `/etc/netplan/01-network-manager-all.yaml`. Dentro de la parte para la interfaz `datos`, comentaremos el campo `addresses` y la IP indicada (usando para ello `#`). Además, cambiaremos la opción `dhcp4: no` por `dhcp4: yes`.
2. Posteriormente y para aplicar los cambios, ejecutaremos `netplan apply` en la terminal (puede tardar un poco).  
  
Ahora, nos conectaremos al router `RX_1` para configurarlo como servidor DHCP. Para ello, usaremos la red de gestión, ya que en este momento `PCX_1` no dispone de IP, por lo que no puede conectarse a la red de datos:
1. Dentro del router, lo primero que haremos será crear un pool de direcciones para asignar a la red. Para ello, nos dirigimos a `IP --> Pool` y creamos un nuevo pool, al que le especificamos un nombre (por ejemplo, `pool1`) y un rango de direcciones a usar. Le especificaremos el rango `33.X.1.200`, `33.X.1.210`.
2. Una vez creado el pool, nos dirigimos a crear el servidor DHCP. Para ello, nos dirigimos a `IP --> DHCP Server --> DHCP`. Creremos una nueva entrada en la tabla, llamada `server1`. Le asignaremos la interfaz `ether1` (que es la que conecta al router con la red de encima), le especificaremos un *lease time* de 10 minutos y el pool de direcciones anteriormente creado, `pool1`.
3. Finalmente, nos dirigimos a `IP --> DHCP Server --> Networks` y creamos una, añadiendo en *address* la red en la que nos encontramos con la máscara, en *gateway* el gateway a asignar, que en este caso es la IP de `RX_1`, `33.X.1.1`; y el servidor DNS a usar. Para ello, le especificaremos por ejemplo este router también, `33.X.1.1`.  
  
Alternativamente, podríamos también haber configurado el router en `IP --> DHCP Server --> DHCP Setup`, donde pulsaremos *next* hasta llegar a *Addresses to Give Out*, donde le especificaremos el rango de direcciones a asignar.  
  
Una vez configurados tanto el cliente como el servidor DHCP, nos disponemos a probar si todo funciona correctamente. Para ello:
1. Primero, ejecutamos *wireshark*, con filtro `dhcp` para observar los paquetes DHCP que envíe y reciba nuestro cliente.
2. Posteriormente, ejecutaremos `dhcliente -v datos` para solicitar una IP al servidor DHCP.
3. Para ver que nos ha asignado una IP (un `lease`), podemos abrir el archivo `/var/lib/dhcp/dhclient.leases`, donde deben aparecer configuradas varias opciones que hemos configurado en el router.
4. Además, al hacer `ifconfig` podemos ver nuestra nueva IP, que ha de correponderse con una IP del pool del router. Además, podemos hacer `route -n` para ver si se nos ha asignado la pasarela por defecto correcta.

## Ejercicio 2
Ahora, haremos que `RX_1` no funcione como servidor de DHCP, sino como un DHCP Relay (un equipo intermedio entre el cliente y el servidor DHCP), lo que nos permite tener un servidor DHCP centralizado. Configuraremos ahora como servidor DHCP `RX_4`, que tendrá como relays a `RX_1` y `RX_2`.

### Realización
Suponiendo que tenemos las tablas de encaminamiento de `RX_1`, `RX_2` y `RX_4` bien configuradas, procedemos con el ejercicio.  
Tras haber hecho el ejercicio 1, en el cliente no habrá que cambiar nada (si no se ha hecho el ejercicio 1, repetir los pasos del cliente). Simplemente ejecutaremos `dhclient -r` para decirle al router que libere nuestra IP (DHCP Release).  
  
En primer lugar, configuraremos los routers `RX_1` y `RX_2` para que actúen como relays. Mostramos sólo la configuración para `RX_1` y en `RX_2` es análoga:
1. Accedemos a `IP --> DHCP Relay` y creamos una nueva entrada, donde especificamos el nombe, el interfaz y la IP del servidor DHCP. En este caso, la IP de `RX_4`, es decir, `172.16.X.4`.  

Una vez configurados los dos relays, procedemos a configurar `RX_4` de forma análoga a como lo hicimos en el ejercicio 1 para el servidor de DHCP (accediendo desde la IP de gestión):
1. El primer paso es crear los pools de direcciones: crearemos un pool para la red `33.X.1.0` y otro para la red `33.X.2.0`, en la pestaña `IP --> Pool` al igual que lo hicimos en el ejercicio 1.
2. Posteriormente, en `IP --> DHCP Server --> DHCP`, crearemos dos entradas, una por cada relay que tengamos. Especificaremos los pasos para `RX_1` y para `RX_2` es análogo:
    - Especificaremos el nombre de la entrada, `server1`.
    - Especificaremos el interfaz por el que sirve de DHCP server, `ether1`.
    - Especificaremos la IP del relay, en este caso, `33.X.1.1` (debemos especificar la IP del router que conecta con la red que contiene a los clientes, para que el servidor DHCP conozca desde qué red se manda DHCP).
    - Especificaremos un *lease time*, así como el pool de direcciones anteriormente creado para `33.X.1.0`.
3. Finalmente, en `IP --> DHCP Server --> Networks` crearemos una entrada por cada red, especificando en cada caso:
    - La red en cuestión.
    - La pasarela por defecto para dicha red.
    - El DNS asociado (por ejemplo, la IP del router).  
  
Una vez configurado todo, nos dirigiremos al cliente y ejecutaremos *wireshark*. Seguidamente, `dhclient -v datos` para solicitar una IP a DHCP. Podemos comprobar que todo ha ufuncionado correctamente con los mismos pasos que hicimos en el ejercicio1.  
  
Además, desde winbox en los routers podemos consultar el número de peticiones DHCP completadas.
