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
sdb: disco sata b (el segundo)
....

sdxi: i partición del x-éximo (en letras) disco

sr0: CDROM

## Particionado
Motivo: Proteger un área concreta del disco

Si decidimos poner / (raíz) en todo el disco sin particionar, puede haber un usuario k ocupe el 100% del disco, lo que pueda llegar a impedir el arranque del sistema. Para ello, reservamos una partición para el boot.
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
Volúmenes lógicos, para evitar problemas con particionados estáticos (una vez hecha una partición, no se puede expandir).

- Physical Volume: Donde meter datos, particiones o discos
- Volume Group: Cajón desastre
- Logical Volume: 

Cuando creamos un volumen lógico, no sabemos en qué dispositivo físico va a acabar.
En cualquier momento se puede añadir un nuevo physical volume con el que hacer crecer los volúmenes lógicos.

Da una gran versatilidad. Todas las versiones de linux incorporan LVM.


sda2
    rl-root         : particion logica root sobre el volume group rl.
    rl-swap         : particion logica swap sobre el volume group rl.
    
Physical volume: pv (+ tab para ver comandos), lv, vg

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
    firewall-cmd --permanent --add-service https
Y luego cargarlo:
    firewall-cmd --reload
    
Para borrar: (o --remove-service https)
    firewall-cmd --remove-port 443/tcp
Tampoco es permanente, nada es permanente.    

## Repaso más en profundidad de firewall
Lo que hacen los firewalls es filtrar paquetes TCP.
Al levantar un firewall, lo normal es que todo se filtre.

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
Lo mejor es tener llaves entre pares (en vez de una única llave), pero escala muy mal.

Se inventaron por esto los de llave asimétrica.

##### Llave asimétrica (clave pública - privada).
Toda persona tiene dos llaves: una privada y otra pública.
La pública se da a todo el mundo y la privada te la guardas.

Problema: hace falta tener las publicas de la gente con la que quieras hablar.
Sin embargo, al ser públicas, se pueden recuperar cuando sea necesario.

El algoritmo es RSA.
Son algoritmos muy costosos computacionalmente.

##### Hash
Un algoritmo: Hash SHAn (n tiene que ver con la clave).

Un algoritmo de hash es bueno si:
- Un cambio muy pequeño genera un hash totalmente distinto.
- No se puede recuperar la información original a partir del hash

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
En el candado, dar a mas informacion
Buscar quien ha generado el certificado. Ver quien ha generado el certificado, ...
Se detiene en la raiz: los que en la configuracion están configurados como raices: configuracion > certificados ...

### Cómo funciona SSH: como usa llave publica / llave privada
#### 1. Garantizar la confidencialidad de la comunicacion
usuario -- servidor con ssh
--> ssh login
<-- el servidor envia llave publica
--> Enviamos nuestra contraseña cifrada con su llave publica
<-- Comprueba la passwd en la bbdd y devuelve si sí o no

si nos intentamos concetar por ssh a la maquina, nos devuelve:
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
    ~/.shh/ssh-keygen
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

# Sesión 4: Ansible
En ansible tenemos un nodo de control (un equipo) donde tenemos instalado ansible (solo ahí). Para la práctica podemos usar el equipo anfitrión como nodo de control.
Desde este nodo también necesitamos un cliente de ssh.

Desde él, lanzamos comandos a los servidores, llamados nodos manejados (en la práctica, las VMs), que no tienen ansible.
En estos nodos necesitamos sshd y python, muy comunes en las instalaciones de linux.

## Archivos de configuración
Paquete ansible-core, que instala software de ansible, jnto con un directorio de configuración en /etc/ansible, donde hay dos archivos:
- ansible.cfg: de configuración, que probablemente no toquemos.
- roles: nombre que da ansible a funciones reutilizables (componentes/scripts/pluggins).
- hosts: 

ansible.cfg: está vacío, pero podemos descomentar líneas para hacer cambios.
Una línea importante es `;home=~/.ansible`, que es donde se encuentran los archivos de configuración de ansible para los usuarios (para no modificar archivos de /etc sin ser root).
- `;inventory`: localización del inventario por defecto.
- Número máximo de hebras que lanza: `;forks=5`
    Ansible manda varios comandos en varias hebras en paralelo. 

hosts: aunque recuerde al de /etc/hosts, el nombre oficial en la documentación es 'inventario', y contiene la lista de hosts con los que vamos a trabajar.
Por defecto pone ejemplos.
El formato en texto plano es IML en terminología de ansible, más antiguo y por retrocompatibilidad, se recomienda YAML.
    [algo] es una etiqueta y todo lo que hay por debajo está agrupado bajo ella.
    Cuando lanzamos un comando, podemos lanzarlo sobre una etiqueta, con lo que el comando se ejecutaría en todos los equipos.
    Un mismo equipo puede estar en varias etiquetas. Aquí reside la potencia de ansible.
    
ansible.cfg (EN EL HOME) permite definir variables en el archivo ansible.cfg, para mayor personalizacion. Si no somos superuser y no podemos tocar ficheros en /etc, podemos tunear la configuración del entorno para nosotros (no para el resto de usuarios).

hosts (EN EL HOME):
Ha añadido 3 servidores, que corresponden con 3 VM.
- Nombre simbólico
- ansible_host: ip a la que corresponde un equipo.
- ansible_user: usuario del equipo al que me conecto por ssh
- ansible_port: puerto específico de la maquina para ssh

Checkear el inventario para ver si tiene errores de sintaxis:
`ansible-inventory --graph`
- Si no pasamos, busca: home/.ansible/hosts; y si no --> /etc/ansible/hosts

## Ejecutar comandos
Lo primero que hay que hacer en las VM es configurar un ssh por llave publica.

Para ejecutarlos por linea de comandos:

`ansible <equipo> -m <comando>`
`ansible ansi_control -m ping`

- equipo ha de estar en el inventario
- La liea de ordenes de ansible está en [43] > Modulos > .
    ansible.builtin: comandos que ansible distribuye en version oficial

- ping lo que hace es verifica que una maquina puede ser manejada por ansible. 
    Si responde en verde es que está bien.


Parámetros que podemos pasar (a de argumento):
(Para evitar que la shell expanda, (* o $) comillas simples)
`ansible <equipo> -m <comando> -a '<parametro>' `
`ansible ansi_control -m ping -a 'data="hola mundo"'`

- `all`: etiqueta especial para todas las máquinas que detecta en el inventario.

## Ejecutar comandos privilegiados sobre máguinas
Para ejecutar comandos de shell:
ansible equipo -m shell -a "find ."

El móduo shell es el por defecto.

El siguiente comando requiere permisos de admin:
ansible euipo -a "firewall-cmd --list-all" 
Al ejecutarlo dará error.

La forma de hacer `sudo` (no se puede porque se pedira una contraseña), es usando --become:
ansible euipo -a "firewall-cmd --list-all" --become
Necesitamos algo más, ya que ciertos usuarios necesitan contraseña para pasar a root.

Para ejecutar comandos privilegiados sin contraseña:
Ir al archivo: /etc/sudoers, que contiene quién puede ejecutar comandos privilegiados.
Para editarlo, hay que usar el comando visudo (para decir al kernel que los cambios han sido realizados)
SI en visudo empieza por %, significa un grupo:
%wheel  ALL=(ALL)   ALL
Lo siguiente permite sin passwd:
%wheel  ALL=(ALL)   NOPASSWD: ALL
Sin embargo, como es muy general, solo daremos esto a un usuario en concreto: admin

Una vez hecho, se puede usar --become.


**Siempre que podamos, tener que buscar módulos de ansible que ejecuten comandos de shell y no comandos de shell directos, ya que permiten mayor flexibilidad.**
Los comandos de shell son más frágiles al nivel de configuracion del sistema operativo.

## Playbooks (~ scripts de lotes)
En lugar de ejecutar un comando, damos una serie de comandos que queremos que ejecute.

Los playbooks son archivos de formado YAML con nombre. Obligatorios:
- name: (nombre del playbook)
- hosts: (a los que vamos a atacar)
- remote_user: (equivalente al ansible_user). Mejor definirlas en el inventario.

Rocky no permite el acceso remoto por ssh

Tenemos por ahí una descripción del formato YAML ([45] > YAML Syntax).
El payo recomienda un playbook por un archivo.
Special variables: variables que proporciona en ejecución de cualquier playbook.


Utilizar un inventario personalizado:
ansible-inventory -i archivo --list
ansible-inventory -i archivo --graph


Ejecutar playbook:
Si no pasamos inventario, se usa el por defecto. Para estas prácticas, pasar siempre inventario personalizado.
ansible-playbook -i <inventario> <playbook>

Ir poco a poco y probando cuando usemos ansible

```
name: nombre
    hosts:
        - ansi00
    vars_files:
        - "archivo"
    tasks:
        - ansible.builtin.ango
            parametro
```

La notación de `{{  }}` es una variable: reemplazar su valor.
Para pasar variables por comand lines, tenemos que pasar el parámetro -e: 
    -e "mivar='ISE ansible'".
    

ansible_facts: datos del equipo al que atacamos.
item: nombre estándar que le da ansible a una variable asociada a un bucle: como la i del for.

Procesar resultados:

- name: está el usuario
    ansible.builtin.command:
        cmd: who
    register: who_results

- name: print 
    ansible.builtin.debug:
        msg: "Connectd: {\{ who_results.stdout }}"

## Ejercicio a realizar
Partir de servidores configurados al apartado 2: acceso ssh con llave publica.
Antes de empezar a hacer el ejercicio (no forma parte), modificarlos para que root pueda acceder con contraseña: por defecto, ssh no deja acceder con contraseña a root@maquina

Para esto, hay que modificar la configuracion de sshd:
`PermitRootLogin yes`
`systemctl restart sshd`

Cómo dar la contraseña a ansible para un usuario (buscar):
- ansible_user: usuario
- ansible_algo (buscar)



### 
Una vez tenemos 2+ máquinas virtuales que tienen acceso por root y contraseña:

Primer ejercicio:
Creamos un playbook que haga: 1 - 5
1. Hacer los cambios y Para que coja los cambios: o visudo o hacer los cambios y llamar a visudo (con parametro especial) para que este lo comunique al SO.
2. Copiar una llave publica valida de nuestro nodo configuracion, ... 
3. Crear grupo wheel (aunque ya este configurado por defecto). Para eso, modulo de ansible que se llama groups.
    Hay una peculiaridad: la idempotencia de ansible. Si llamamos a un modulo con los mismos parametros varias veces repetidas, el resultado es el mismo.
    Si creamos un grupo y ya está creado, no hace nada. Sin embargo, tenemos que hacerlo.
    Tenemos que hacer que nuestros scripts funcionen igual: no duplicar el usuario.
    Añadir wheel a sudoers
4. Añadir lista de usuarios variable: para el login no daremos contraseña, sino una llave publica.
    Cada usuario tendria k tener una distinta, pero damos la misma a todos:
    usuarios:
        antonio: asdfñkasjdfñkajsdf
        maria: asdfñkasjdfñkajsdf
5. Prohibir el acceso con root por contraseña (devolver el equipo al modo por defecto, quitar la linea descomentada).

Segundo ejercicio:
Dos máquinas donde hemos ejecutado el playbook:
En una maquina instalamos apache httpd y en la otra nginx (alternativa a apache).
En la practica 2 que hicimos manual ahora por playbook.
    
## Cómo quiere el tio que le entreguemos los ejercicios:
- Fichero de script para ejecutar playbook
- Playbook
- inventario.yaml
- variables.yaml

Podemos usar dos inventarios.
Probablemente tengamos además:
- Fichero html
- fichero con public key (o si no dentro de variable)

Lo de:
    usuarios:
        antonio: asdfñkasjdfñkajsdf
        maria: asdfñkasjdfñkajsdf
También podemos hacerlo con una carpeta `keys` que tenga en distintos archivos las llaves publicas.
