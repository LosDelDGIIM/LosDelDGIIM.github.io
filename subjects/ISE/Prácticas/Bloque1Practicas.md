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


