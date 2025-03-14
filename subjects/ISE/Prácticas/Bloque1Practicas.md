# Sesión 1
Hipervisor ~ Software de virtualización
Virtualbox realiza una virtualización de hardware completa: el SO que instala sobre el HW virtual no necesita adaptarse, como en la virtualización parcial.

Ventajas:
- Plataformas distintas de la real.
- Seguridad.
- Uniformización.
- Amortización de los activos de cómputo.
- Aprovisionamiento a demanda: origen del cloud computing (posibilidad de solicitar capacidad de cómputo cuando se necesita y dejar de pagarla cuando no).
    Los recursos de cómputo pasan de ser un activo (como en virtualización) a ser un servicio.
    Contra: si el proyecto no va bien o no llega a ser exitoso, los activos se pierden. Los activos necesitan ser amortizados, los servicios no.
    Hay que tener en cuenta que un servicio prolongado puede ser peor que el activo, porque es más caro contratar el servicio que comprar los activos necesarios.

Servicios de infraestructura (redes, cómputo y sistema operativo), Infraestructure as a Service:
- Servicios de networking.
- Servicios de almacenamiento.
- Servicios de servidores (creación de máquinas virtuales).

Platform as a Service:
- Ellos te proporcionan BBDD, su gestión, las licencias, ...

Software as a Service:
- Office 360

Function as a Service:
- De APIs.
- Lambda computing.
Proporcionan APIs que facilitan la gestión.
Inconveniente: Una vez desarrollada la solución usando una API de un proveedor, estás ligado a dicho proveedor.


Tipos de cloud computing:
- Privada: Alojadas en nuestras instructuras.
- Públicas: Todo el mundo puede acceder.
- Híbridas.


## Tipos de networking
Tipos de networking entra en examen: NAT, Host-only y bridge (ver documentación de virtualbox).

Por qué usar dos tarjetas de red:

- Con la tarjeta de red NAT: virtualbox emula el router ISP encargado de realizar NAT.
Virtualbox hace esto porque por defecto no quiere dar acceso a IP públicas.
Sin embargo, como resultado ni el host ni otras máquinas virtuales tienen acceso a esta máquina virtual.

- Host-only: Permite comunicación host-vm y vm-vm.
Se crean dos tarjetas virtuales: una para el anfitrión y otra para el host (192.168.56.1).

- Bridged: hackea la tarjeta real del host a nivel de sistema operativo y se conecta con ella como si fuera la misma tarjeta.
Todos los recursos de la tarjeta real están disponibles para la tarjeta virtual.
Por motivos de seguridad, en la UGR no funciona porque ve dos IPs distintas con la misma MAC.
Tiene implicaciones de seguridad: cualquier acceso de la VM lo ve el host y viceversa (imaginar en Amazon o etc).
Útil para hacer pruebas en casa de conexión a máquina virtual de compañero.



Instalar: vim, ifconfig, ...
Ver posibilidad de crear snapshots

# Sesión 2: Discos
Comandos:
- lsblk (list blocks) : representación gráfica de estructura de volúmenes


Todos los dispositivos están en /dev:
sda: disco sata a (el primero)
    sda1: 1a partición
sdb: disco sata a (el primero)
....

sdxi: i partición del x-éximo (en letras) disco

sr0: CDROM

## Particionado
Motivo: Proteger un área concreta del disco

Si decidimos poner / (root) en todo el disco sin particionar, puede haber un usuario k ocupe el 100% del disco, lo que pueda llegar a impedir el arranque del sistema. Para ello, reservamos una partición para el boot.
    Si el resto del disco se llena, ese espacio estaría protegido. El arranque de linux se encuentra en /boot.
    
(Cultura) El primer sector de sda se llama MBR

/dev  : dispositivos
/boot : sistemas de arranque
/etc  : configuración de SO y servicios (puntos de montaje, sudoers, config IP, apache)
/home : directorios de usuarios
/root : home de root
/mnt  : punto de montaje por defecto (manual)
/media: donde monta el demonio de gestor de medios de linux. Se recomienda no usar.
/var  : (variable), se almacena información que puede cambiar de tamaño como consecuencia de uso. Variables del SO o de servicios.

/var y /home crecen con el tiempo => hay que controlarlos.

Una práctica común es llevar /var a una partición distinta.




- diskfree -h : Información del espacio que queda en los volúmenes.
tmpfs: sistemas de ficheros que linux monta en memoria, bufferes de acceso.

## RAID (Redundant Array of Independent/Inexpensive (ahorrar costes, juntar discos) Disks)
### RAID 0 (Striping)
Striping) - Si tenemos varios discos, crea disco virtual con la suma de los tamaños
striping: sectores contiguos se intentan colocar en distintos discos, para un acceso paralelo a discos en sectores contiguos. Se usaba antes para aumentar velocidad.
- Problema: Si cae un disco cae todo el sistema. Muy sensible a errores físicos. Usado poco o nada.

### RAID 1 (Espejo)
Copiar toda la información en todos los discos que forman el espejo.
Ventaja en la redundancia, para no perder datos.

Cuando lee un bloque, lo lee en varios discos y los compara para encontrar errores.
Hay versiones de RAID que permiten lectura en paralelo.

Se suelen montar en buses distintos para evitar retrasos de escritura.

### RAID 5 
Mejora de RAID 1, que tiene mucho coste.

Si tenemos varios discos, se usan todos menos uno en RAID 0 y en el último disco guardamos información de recuperación.
Si uno de los discos muere, usando información de bloques de los otros discos y de la información de recuperación se puede calcular la información perdida.

Las prestaciones se reducen mucho al pasar por dicha función.
La caida de discos es muy común en centros grandes.

Proporciona cierta robustez a cambio de eventuales pérdidas de prestaciones.
Coste muy bueno (solo perdemos un disco).

Sirve para: Logs del sistema, BBDD no crítica.


- RAID Hardware: Hay una controladora de RAID: Un chip en la placa base.
    Buenas prestaciones.
    Transparente al SO: El SO ve un solo disco y no sabe que son varios en RAID.
- RAID Software: Hay un SO driver para acceder a los discos virtuales RAID.
    El driver se encarga de los cálculos necesarios para mantener los RAIDs.
    El código se ejecuta en la CPU principal, bajan las prestaciones.
    Visible a nivel del administrador (el administrador ve el RAID), puede romperlo de forma accidental.


Instalar discos: config -> almacenamiento -> crear discos nuevos
Crear un RAID:
- mdadm

(dnf provides [comando]: me dice qué paquete contiene el comando)
A los RAIDs se les llama mdi (multidisk)

mdadm --create /dev/md0 --level 1 --raid-devices=2 /dev/sdb /dev/sdc

Si escribimos en el raid: echo 1 > /dev/md0, escribimos en ambos discos
Si escribimos en sdb: echo 1 > /dev/sdb, rompemos el raid

## LVM (Logical Volume Manager)
Volúmenes lógicos, para evitar porblemas con particionados estáticos (una vez hecha una partición, no se puede expandir).

- Physical Volume: Donde meter datos, particiones o discos
- Volume Group: Cajón desastre
- Logical Volume: 

Cuando creamos un volumen lógico, no sabemos en qué dispositivo físico va a acabar.
En cualquier momento se puede añadir un nuevo physical volume con el que hacer crecer los volúmenes lógicos.

Da una gran versatilidad. Todas las versiones de linux incorporan LVM.


sda2
    rl-root         : particion logica root sobre el volume group rl.
    rl-swap         : particion logica swap sobre el volume group rl.
    
Physical volume: pv (+ tab para ver comandos), lv, pv

vgdisplay:
Free PE / Size: Todo el espacio disponible ya lo ha dado a logical volumes


Procesos en ejecución + del espacio en memoria principal: problema serio

## Llevar /var a LVM
Cuidado con añadir RAIDs a Volume Groups con discos sin RAID. No se asegura usar RAID.
Volume Groups se usan para separar discos con capacidades distintas:

Separar en Volume Groups: SSD, HDD, RAIDs (separar en mismo tipo de raid).

1. Crear volumen logico para /var
    pvcreate /dev/md0           (añadir info al comienzo del dispositivo)
    vgcreate raid1 /dev/md0     Crear Volume Group
    vgdisplay raid1             Ver Volume Group
    lvcreate -L 10G -n rvar raid1   Crear Volumen Lógico
    vgdisplay /dev/raid1/rvar

Los logical volumen tienen como nombre de dispositivo (sinónimos):
/dev/[nombre volume group]/[nombre dispositivo]
/dev/mapper/[volume group]-[nombre dispositivo]

2. Queremos coger de /root /var y meterlo ahí: formatear /dev/raid1/rvar y montarlo
 
- mkfs (make filesystem)
- mout

Para ello, hay que formatearlo: mkfs -t ext4 /dev/raid1/rvar 

Una vez formateado, se puede montar:
mount /dev/mapper/raid1-rvar /mnt

mount para ver los dispositivos montados.

3. Copiar /var en /mnt
No podemos hacer cp -a /var/* /mnt 
En /var SIEMPRE se están escribiendo cosas, luego al hacer la copia se perderán cosas

Hay varios modos de ejecución de los sistemas linux. Modos:
0: reset (reinicia el sistema).
1: single user o mantenimiento.
3: multi user + network.
5: 3 + GUI
+ niveles personalizables por distribuciones de linux


Para ello, hay que dejar el sistema en modo manteminiento: expulsa a todos los usuarios y a los procesos que no sean de root.
Para ello:

systemctl isolate runlevel1.target

Para comprobarlo:
systemctl status

Ahora sí:
cp -a /var/* /mnt/

Si ahora nos vamos a /mnt y hacemos ls, vemos que todo lo de /var está allí

4. Falta sacar /dev/raid1/rvar de /mnt y meterlo en /var

umount /mnt
mv /var /var_old        (Copia de seguridad por si acaso)
mkdir /var
mount /dev/raid1/rvar /var

df -h       (Se ve todo)

5. Hacer permanentes los montajes
Los montajes con mount no son permanentes. Para hacer permanente un montaje, en /etc/fstab:

dispositivo     punto de montaje    sistema de ficheros     propiedades del fs      prioridad de montaje (en qué orden se montan, si todos = => lineal)
Hay que situarlo debajo de rl-root.


Probamos a demontar: umount /var
Al reiniciar iría bien

Para probarlo antes: 
systemctl daemon-reload     (hay que recargar el demonio)
mount -a                    (Va al fichero /etc/fstab y monta todo)

# Sesión 3: Configuración de firewall + ssh
## Firewall
(cultura) en las iptables se implementa todo de gestión de paquetes de TCP/IP.
Como es muy complejo ese nivel, se usa un front-end. En Rocky, firewall-cmd

Para ver si está on o no:
    firewall-cmd --state
    systemctl status firewalld

Para apagarlo lo único es parar el deminio
    systemctl stop firewalld

Para listar:
    firewall-cmd --list-all

Si no tenemos servicio habilitado, se descarga.
Los servicios son alias a los puertos en los que se trabajan. Es lo mismo hablitar un puerto a un servicio.

Se pueden crear alias propios, ya que están en un fichero de configuración de firewalld
La lista de alias para los servicios:
    firewall-cmd --get-services
    
Para añadir un servicio:    
    firewall-cmd --add-service http
    firewall-cmd --list-all
    
Si reiniciamos la máquina lo perdemos. Si queremos sque sean permanentes, lo salvamos con:
    firewall-cmd --runtime-to-permanent
    
Otra forma es guardarlo en dico (443/tcp = https, puerto/protocolo = servicio, indicar siempre si es tcp o udp):
    firewall-cmd --permanent --add-port 443/tcp
Y luego cargarlo:
    firewall-cmd --reload
    
Para borrar: (o --remove-service https)
    firewall-cmd --remove-port 443/tcp
Tampoco es permanente, nada es permanente.    

## Repaso más en profundidad de firewall
Lo que hacen los firewalls es filtrar paquetes TCP.
Al levantar un fireall, lo normal es que todo se filtre.

public (active): zona de trabajo
Como la zona de windows de red (publica, privada, ...)
Distintas reglas en funcion del tipo de red.

Filtra siempre las conexiones entrantes, nunca las salientes.

### Ejercicio
Instalar Apache o Nginx
Crear una página con nombres y apellidos
Tiene que poder accederse desde el anfitrión


Hay que usar nmap (herramienta de escaneo de puertos), aprender a usarla.
Cada vez se ha hecho más compleja (ha ido evolucionando), si queremos que salga rápido, usar -top 100 (buscarla), que busca en los 100 puertos más habituales.
Si buscamos como acelerar el proceso de escaneo en Google, sale.
 
## SSH
Aplicación de **terminal remoto seguro**.
- Solución antigua telnet, todo en texto plano (login + sesión)

Lo normal es:
    ssh usuario@ip/nombreDominio
Tanto el proceso de login como de sesión es seguro (está cifrado).
ssh usa varias técnicas criptográficas.


### Repaso rápido de criptografía / seguridad
Algoritmos más comunes:

##### Llave simétrica: Hay un secreto compartido.
Computacionalmente es muy eficiente, los más usados en determinadas circunstancias.
El algoritmo más usado es DES.

Principal problema: el escalado.
Lo mejor es tener llaves entre padres (en vez de una única llave), pero escala muy mal.

Se inventaron por esto los de llave asimétrica.

##### Llave asimétrica (clave pública - privada).
Toda persona tiene dos llaves: una privada y otra pública.
La pública se da a todo el mundo y la privada te la guardas.

Probema: hace falta tener las publicas de la gente con la que quieras hablar.
Sin embargo, al ser públicas, se pueden recuperar cuando sea necesario.

El algoritmo es RSA.

Son algoritmos muy costosos computacionalmente.

##### Hash
Un algoritmo: Hash SHAn (n tiene que ver con la clave).

Un algoritmo de hash es bueno si:
- Un cambio muy pequeño genera un hash totalmente distinto.
- No es reversible.

#### Identidad
Se garantiza mediante la firma digital. Para ello hacen falta las funciones hash.
Firma digital: coger una informacion, calcular su hash y cifrar con llave privada.

Al enviársela a alguien:
- Abre con llave pública la firma.
- Compara los hash

El destinatario sabe que el contenido no ha sido alterado y que procede del origen.

##### Autoridades de certificación
Autoridades que se dedican a decir que una cierta llave publica/privada corresponde a cierta persona.

La web genera dos llaves: publica y privada
La publica se envia al FNMT
Se genera un papel con el que ir a un funcionario, que le dice al FNMT que todo esta bien y se recibe un certificado

Un certificado contiene:
- Datos personales
- Información
Está firmado con hash y llave privada del FNMT.

Formato más usado: X509.

Para saber que la firma es de la FNMT, hay una autoridad de certificacion que firma la llave publica de la FNMT. Así de forma recursiva hasta certificados raíces.
Si se llega a una no conocida, hay un error de certificación.

Hoy en día depende de la confianza. Dentro del software ya van ciertas llaves públicas en las que el fabricante confía.

La cadena de certificación puede verse en los navegadores con:
En el candado, ddar a mas informacion
Buscar quien ha generado el certificado. Ver quien ha generado el certificado, ...
Se detiene en la raiz: los que en la configuracion están configurados como raices: configuracion > certificados ...

### Cómo funciona SSH: como usa llave publica / llave privada
#### 1. Garantizar la confidencialidad de la comunicacion
usuario -- servidor con ssh
--> ssh login
<-- el servidor envia llave publica
--> Enviamos nuestra contraseña cifrada con su llave publica
<-- Comprueba la passwd en la bbdd y devuelve si sí o no

si nos intentamos concetar por ssh a la maquina, nos devuelve:si nos intentamos concetar por ssh a la maquina, nos devuelve:
authenticity can't be established: el servidor devuelve una llave de publica cuyo algoritmo es SHA256 pero que no tiene certificado.

Al usar siempre ssh client nos va a rear un subdirectorio oculto de nombre .ssh
Tendremos un archivo 'know_hosts'. Mete en este archivo las llaves publicas de los ultimos servidores. La próxima vez que accedamos no pregutna, porque ya hemos confiado en él.

#### Cifrados en comunicaciones
<-- servidor manda llave publica
--> genero un secreto (llave de sesion, solo para reducir coste computacion) y se lo mando con su llave publica
Ambos tenemos el secreto, llave de sesion

Llave asimetrica solo para identificacion e inicio de sesion. El resto se hace por secreto compartido, solo para reducir costes computacionales.

#### 2. Como utiliza ssh la llave publica privada para acceder sin contraseña
--> ssh login
<-- el servidor tiene una bbdd con llaves publicas y va a buscar la llave publica del usuario solicitado. Va a pedir al usuario que firme algo con una clave, un challenge.
--> Se lo devuelvo firmado con llave privada
<-- descifra con clave publica y ve que el mensaje es correcto, devuelve OK.

Vamos a ver donde almacena ssh las llaves publicas.
    ssh-keygen
la BBDD donde sshd almacena llaves es el directorio home de la cuenta a la que nos queremos conectar en .shh: /home/usuario/.shh/id_rsa
Genera llaves publica-privada. Pide constraseña para cifrar la llave. Dar siempre contraseña.

Para darle a un servidor nuestra llave publica y que no nos pida la contraseña:
    ssh-copy-id usuario@ip
Nos va a pedir la contraseña por ultima vez.
En /home/usuario/.ssh en la maquina servidor nos genera un fichero que se llama autorished_keys. Podemos tener las llaves que queramos aquí. Es común en cuentas de administrador.
Es equivalente a copiar y pegar en el fichero la llave publica.

Ahora podemos ejecutar un comando remoto:
ssh usuario@ip "comando"
Sin necesidad de contraseñas

Esto es la base de ansible (permite ejecutar scripts en remoto)
- El lenguaje de script de ansible es python
- Da utilidades sutiles que facilitan

### Ejercicio
Se recomienda clonar la base de forma completa.

Garantizar acceso con ssh mediante llave publica (sin contraseña)

Cambiar el puerto por defecto de ssh: se suele hacer por motivos de seguridad, es algo comun.
Para ello, tenemos que ir a la configuracion de ssh: /etc/ssh

Hay dos archivos de configuracion:
- ssh_config: si suele estar, se instala con el cliente.
- sshd_config: configuracion del demonio. Si no se instala el demonio no está.
Tienen propiedades diferentes.

En sshd:
Como rocky corre el security extension system, hay que informarle del cmbio de puerto, hay que ejecutar el comando encima de Port n
Además, tendremos que habilitar el firewall para permitir dicho puerto.
