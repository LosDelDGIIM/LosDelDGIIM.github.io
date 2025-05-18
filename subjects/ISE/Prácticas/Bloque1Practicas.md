# Introducción

En este documento, exploraremos la instalación de un software de máquinas virtuales (denominado aquí como **VMSW**), que crea una capa de abstracción sobre el hardware, permitiendo ejecutar varias máquinas virtuales simultáneamente en un mismo servidor. Este enfoque, conocido como **virtualización completa**, implica que el sistema operativo invitado no requiere modificaciones para operar sobre el hardware virtualizado, a diferencia de la virtualización parcial. Una alternativa moderna a esta tecnología es el uso de **contenedores** (como Docker), que comparten recursos del kernel del anfitrión con los contenedores, optimizando el uso de recursos pero sacrificando aislamiento completo.

Nos centraremos en la instalación de **VirtualBox** como ejemplo de VMSW, un hipervisor de tipo 2 gratuito y de código abierto, aunque también mencionaremos alternativas como **VMware** y compararemos con hipervisores de tipo 1 como **Hyper-V**.

### Diferencia entre Hyper-V y VirtualBox

- **Hyper-V**: Hipervisor de tipo 1 desarrollado por Microsoft, integrado en Windows Professional y superiores. Opera directamente sobre el hardware sin depender de un sistema operativo anfitrión, lo que mejora el rendimiento, especialmente en entornos Windows. Es ideal para servidores y sistemas Microsoft, pero su compatibilidad está limitada a hardware soportado por Windows y no es tan flexible en entornos Linux o macOS.
- **VirtualBox**: Hipervisor de tipo 2 de Oracle, ejecutado como una aplicación sobre un sistema operativo anfitrión (Windows, Linux, macOS). Su diseño lo hace más versátil y compatible con una amplia gama de sistemas invitados, incluyendo distribuciones Linux poco comunes. Sin embargo, al depender del anfitrión, puede tener un rendimiento inferior en escenarios de alta carga.

**Ventajas de la virtualización** (aplicables a ambos):
- Ejecución de plataformas distintas a la del anfitrión.
- Mayor seguridad mediante aislamiento.
- Uniformización de entornos para desarrollo o pruebas.
- Amortización de recursos físicos al consolidar servidores.
- Aprovisionamiento a demanda, base del **cloud computing**, donde los recursos pasan de ser activos fijos a servicios bajo demanda.

**Desventajas**: En el modelo de servicio (cloud), si un proyecto falla, los costos no se amortizan como con activos físicos, y un servicio prolongado puede superar el costo de adquirir hardware.

---

## Realización

### Instalación de VirtualBox
- **Enlace de descarga**: [VirtualBox Downloads](https://www.virtualbox.org/wiki/Downloads).
- **Para Arch Linux**:
 ```
sudo pacman -S virtualbox
```

### Alternativa: VMware
- **Enlace**: [VMware Workstation y Fusion](https://www.vmware.com/products/desktop-hypervisor/workstation-and-fusion)

---

# Instalación de Rocky Linux

Utilizaremos el **VMSW** (por ejemplo, VirtualBox) para instalar **Rocky Linux** en modo mínimo, sin entorno gráfico, incluyendo el demonio **sshd**. La instalación será por defecto, pero crearemos una cuenta no root con privilegios administrativos. La máquina tendrá **dos tarjetas de red**, configuradas teniendo en cuenta:

### Modos de red en VirtualBox
- **Not Attached**: Simula una tarjeta sin conexión, como si no hubiera cable.
- **NAT**: Ideal para navegación y descargas básicas; traduce direcciones de red del invitado al anfitrión.
- **NAT Network**: Permite conexiones salientes en una red interna.
- **Bridged Networking**: Conecta la VM directamente a la red física del anfitrión, útil para servidores o simulaciones.
- **Internal Networking**: Crea una red aislada visible solo para las VMs seleccionadas.
- **Host-Only Networking**: Conecta el anfitrión y las VMs sin acceso externo, usando una interfaz virtual.
- **Cloud Networking**: Conecta la VM a una subred en un servicio en la nube.
- **Generic Networking**: Modos avanzados con control de drivers específicos.

Configuraremos una tarjeta en **NAT** (para acceso a internet) y otra en **Host-Only** con una **IP estática** (para comunicación entre el anfitrión y el invitado). También estableceremos un **hostname** (nombre legible para identificar la máquina).

### Snapshot
Tras la configuración, crearemos un **snapshot** de la VM, que guarda su estado actual (configuración, archivos y memoria si está en ejecución). Esto permite volver al estado inicial en cualquier momento. A diferencia de un **clon** (otra máquina independiente), el snapshot depende de la VM original.

### sshd
El demonio **sshd** gestiona conexiones SSH, proporcionando comunicación segura entre hosts. Se activa al inicio desde `/etc/rc`.

## Realización

1. Descarga Rocky Linux desde su [página oficial](https://rockylinux.org/) o este [enlace directo](http://atcproyectos.ugr.es/esriie/Rocky-9.0-20220805.0-x86_64-minimal.iso). Guarda la ISO en un directorio estable.
2. Arrastra la ISO a VirtualBox para abrir el menú de importación:
 - Deja las opciones por defecto, ajustando nombre y recursos (CPU, RAM) si deseas más rendimiento.
 - Activa **Enable EFI** para evitar errores.
3. Inicia la VM y en el menú de instalación:
 - (1) Crea un usuario no root con contraseña y permisos administrativos.
 - (2) Configura el **hostname** (ejemplo: `dekMV01` para Donald Ervin Knuth).
4. Tras instalar, verifica en la terminal:
 - `systemctl status sshd` (comprueba que sshd esté activo).
 - Confirma que el usuario tiene privilegios de superusuario.
 - En caso de no haberlo hecho en el paso previo, se puede configurar el **hostname** desde la terminal con `hostname xxxMV01`. Para hacer este cambio permanente ejecute el comando `hostnamectl set-hostname xxxMV01`.
5. Configurar el prompt:
 - (1) Edita el fichero .bashrc
 - (2) Añade una linea para modificar el prompt (por ejemplo): PS1='\[\u@\h \W\] \[\e[0;32m\]\t \W>\[\e[1;37m\]'. O uno más básico: PS1='\[\u@\h-\t \W\]$'
 - (3) Aplica los cambios a la sesión actual con source .bashrc
6. Configura las redes en VirtualBox:
 - Adaptador 1: **NAT**.
 - Adaptador 2: **Host-Only Adapter**, con "Cable Connected" activado. Es posible que VirtualBox no tenga una red de este tipo creada por defecto, en cuyo caso puede crearla en `Tools > Network Manager > Host-only Networks > Create`.
7. Para la ip estática, usaremos la herramienta nmcli(network manager command line), en nuestro caso particular ejecutaremos:
 ```
sudo nmcli connection modify "Wired connection 1" ipv4.addresses 192.168.56.69/24 # Para asignar la ip deseada
sudo nmcli connection modify "Wired connection 1" ipv4.gateway 192.168.56.1 # Configuración del gateway
sudo nmcli connection modify "Wired connection 1" ipv4.dns "8.8.8.8,8.8.4.4" # DNS 
sudo nmcli connection modify "Wired connection 1" ipv4.method manual # Para indicar que use IP estática
sudo nmcli connection up "Wired connection 1" # Para activar la nueva configuración de la conexión
 ```
Otra opción más cómoda es usar `nmtui` (network manager text user interface).
8. Verifica el funcionamiento:
 - Ping desde el anfitrión a la VM y viceversa. Para saber la ip de tu máquina puedes usar el comando `ifconfig`.
 - Conéctate por SSH desde el anfitrión. `ssh user@ip`
 - Haz ping a internet desde la VM (ejemplo: `ping 1.1.1.1`).
9. Guarda y crea un **snapshot** desde el menú de snapshots como estado de referencia. (`Tools > Snapshots`)

---

# Configuración de LVM

El **Logical Volume Manager (LVM)** abstrae el almacenamiento físico, permitiendo crear volúmenes lógicos flexibles. Esto elimina restricciones de tamaño físico y separa la configuración hardware del software, facilitando ajustes sin desmontar el sistema de archivos.

### Componentes de LVM
- **Physical Volumes (PV)**: Discos o particiones físicas inicializadas para LVM.
- **Volume Groups (VG)**: Grupos que combinan PVs para formar un pool de almacenamiento.
- **Logical Volumes (LV)**: Volúmenes lógicos creados desde el VG, usados como particiones flexibles.

En este apartado modificaremos la configuración por defecto de Rocky Linux para usar LVM.

### Comandos útiles
- `pvdisplay`, `vgdisplay`, `lvdisplay`: Muestran detalles de PVs, VGs y LVs.
- `vgextend`: Añade un nuevo PV a un VG existente.
- `lvextend`/`lvreduce`: Aumenta o reduce el tamaño de un LV.
- `resize2fs`: Ajusta el sistema de archivos tras redimensionar un LV (para `ext4`).

Sin LVM, si `/` (root) ocupa todo el disco y un usuario llena el espacio (ej. en `/var` o `/home`), el sistema puede fallar, incluso impidiendo el arranque. Por ello, es común separar directorios críticos como `/boot` (con los archivos de arranque) o `/var` (con datos variables como logs) en particiones o volúmenes distintos.

## RAID

**RAID** (Redundant Array of Independent/Inexpensive Disks) es una tecnología que agrupa dispositivos de almacenamiento en un disco virtual con características específicas, como redundancia o mayor rendimiento, a un costo potencialmente menor al combinar discos económicos. Nos centraremos en tres niveles principales: RAID 0, RAID 1 y RAID 5, además de diferenciar entre implementaciones hardware y software.

- **RAID 0** (Striping)
    - Combina varios discos en un único volumen virtual cuya capacidad es la suma de los discos individuales. Utiliza striping (segmentación), distribuyendo sectores contiguos entre discos distintos para permitir acceso paralelo y aumentar la velocidad de lectura/escritura.
    - Antes era común en sistemas donde la velocidad era crítica (ej. HDD en servidores antiguos).
    - No ofrece redundancia. Si un disco falla, se pierde toda la información del arreglo, lo que lo hace muy sensible a errores físicos. Por esta razón, hoy se usa poco o nada en entornos críticos.

- **RAID 1** (Mirroring)

    - Copia idénticamente toda la información en todos los discos que forman el "espejo", proporcionando redundancia total. La capacidad útil se reduce a la del disco más pequeño en el arreglo.
    - Alta tolerancia a fallos; si un disco muere, los datos persisten en los demás. Al leer un bloque, puede comparar datos entre discos para detectar errores, y algunas implementaciones permiten lectura en paralelo para mejorar el rendimiento.
    - Para evitar retrasos en escritura, los discos suelen conectarse a buses distintos (ej. canales SATA separados).
    -  Ideal para datos críticos donde la integridad es prioritaria sobre la capacidad (ej. sistemas operativos, configuraciones clave).

- **RAID 5**

    - Mejora de RAID 1 en términos de costo y eficiencia. Requiere al menos tres discos: usa striping como RAID 0 para los datos y reserva un disco virtual equivalente para almacenar información de paridad (recuperación). Si un disco falla, los datos se reconstruyen usando la paridad y los bloques restantes.
    - Ofrece robustez a un costo razonable (solo se "pierde" la capacidad de un disco para paridad). Soporta la caída de un disco sin pérdida de datos.
    - Las operaciones de escritura son más lentas debido al cálculo de paridad, y la reconstrucción tras un fallo reduce aún más las prestaciones. En centros de datos grandes, donde la caída de discos es común, esto puede ser un cuello de botella.
    - Adecuado para logs del sistema, bases de datos no críticas o entornos donde el balance entre costo y redundancia es clave.

Diferenciamos además entre RAID Hardware y Software. En el hardware, hay un controlador físico que gestiona el RAID, es más rápido gracias a la controladora independiente y transparente al SO, que ve un único disco conjunto (ej. con 4 discos en RAID 5, el SO detecta uno solo). En cuanto al software, la gestión la realiza el sistema operativo o un programa, sin hardware dedicado. Depende de la CPU, lo que puede reducir rendimiento, pero es más económico y flexible.

## Configuración de RAID en VirtualBox

 - En VirtualBox, ve a Configuración > Almacenamiento > Controladora SATA.
        Crea y añade discos virtuales nuevos (ej. dos discos de 10 GB cada uno: /dev/sdb y /dev/sdc). 
        Recuerda que se necesitan al menos 3 discos para RAID 5.
 - Crear un RAID con `mdadm`:
        Crea un RAID 1:
```
sudo mdadm --create /dev/md0 --level=1 --raid-devices=2 /dev/sdb /dev/sdc
```
Los arreglos RAID se nombran como /dev/mdX (multidisk). Por ello, si escribimos ($ echo 1 > /dev/md0) se escribira en ambos discos mientras que si lo hacemos sobre /dev/sdb romperemos la integridad.
## Integración de LVM con RAID

LVM y RAID pueden combinarse para obtener redundancia (RAID) y flexibilidad (LVM). Por ejemplo, un RAID 1 puede usarse como base para un PV, asegurando que los datos estén duplicados antes de gestionarlos con LVM. Sin embargo, hay que tener cuidado al integrar RAIDs en Volume Groups con discos sin RAID, ya que no se garantiza que los datos aprovechen la redundancia del RAID si el VG mezcla discos con capacidades o configuraciones distintas. Por ello, una práctica recomendada es separar los discos en VGs según su tipo: SSD, HDD o RAIDs (y dentro de RAIDs, usar el mismo nivel, como RAID 1).

### Configuración práctica: Mover /var a un volumen lógico sobre RAID 1
A continuación, detallamos cómo mover el directorio `/var` (que crece con el tiempo por logs y datos variables) a un volumen lógico basado en un RAID 1 creado con `mdadm`. Este proceso asegura redundancia y flexibilidad para el almacenamiento.

#### 1. Crear el RAID 1
- Añade dos discos virtuales en VirtualBox (ej. `/dev/sdb` y `/dev/sdc`, 10 GB cada uno).
- Crea el arreglo RAID:
```
sudo mdadm --create /dev/md0 --level=1 --raid-devices=2 /dev/sdb /dev/sdc
```

#### 2. Inicializar LVM sobre RAID

- Crea un Physical Volume (PV) en el RAID:
```
sudo pvcreate /dev/md0
```
Esto añade metadatos de LVM al inicio del dispositivo RAID.
- Crea un Volume Group (VG) llamado `raid1`:
```
sudo vgcreate raid1 /dev/md0
sudo vgdisplay raid1
```
- Crea un Logical Volume (LV) llamado `rvar` de 10 GB:
```
sudo lvcreate -L 10G -n rvar raid1
```
- Verifica el LV:

```
sudo lvdisplay /dev/raid1/rvar
```
Nota: Los LVs tienen dos nombres equivalentes:
- `/dev/raid1/rvar`
- `/dev/mapper/raid1-rvar`

#### 3. Formatear y montar temporalmente
- Formatea el LV con el sistema de archivos `ext4`:
```
sudo mkfs -t ext4 /dev/raid1/rvar # mkfs.ext4 /dev/raid1/rvar
```
- Monta el LV en `/mnt` para pruebas:
```
sudo mount /dev/mapper/raid1-rvar /mnt
```

#### 4. Copiar /var en modo mantenimiento
Dado que `/var` está en uso constante por el sistema (logs, servicios activos), una copia directa como `cp -a /var/* /mnt` podría perder datos escritos durante el proceso. Para evitarlo, cambiamos al modo mantenimiento (single-user), que expulsa a todos los usuarios y detiene procesos no esenciales:
- Cambia al modo single-user (debes ser **root** para ello):
```
sudo systemctl isolate runlevel1.target
```
Podemos comprobarlo con `systemctl status` y nos debería salir `State: maintenance`, una vez comprobado y con todo correcto:
```
cp -a /var/* /mnt/
ls /mnt
```

#### 5. Reubicar /var
- Desmonta el volumen lógico de `/mnt`:
```
sudo umount /mnt
```
- Renombra el `/var` original como respaldo (por seguridad):
```
mv /var /oldvar
```
- Crea un nuevo directorio `/var`:
```
sudo mkdir /var
sudo mount /dev/raid1/rvar /var
```
- Verifica el espacio y montaje:
```
df -h
```
#### 6. Hacer el montaje permanente
Los montajes con mount son temporales y se pierden al reiniciar, para hacerlo permanente, podemos editar /etc/fstab y añadir la linea:
```
/dev/raid1/rvar  /var  ext4  defaults  0  0
```

Para probarlo todo:
```
sudo systemctl daemon-reload # Recargar el demonio
sudo mount -a # Monta todo lo definido en /etc/fstab
df -h
```
Ahora tras reiniciar todo (desmontar /var antes) debería mantenerse como lo hemos definido. Lo podremos comprobar con df y con lsblk
Estos últimos pasos vienen explicados con más detenimiento a continuación.

## Administración del Sistema de Archivos

### systemd
**systemd** es el sistema de inicio predominante en Linux, reemplazando a SysVinit. SysVinit usaba niveles de ejecución (runlevels) con capacidades específicas, mientras que systemd ofrece un enfoque más modular.

### Jerarquía del sistema de archivos
- `/bin`: Binarios de comandos esenciales.
- `/boot`: Archivos estáticos del cargador de arranque.
- `/dev`: Archivos de dispositivos.
- `/etc`: Configuración específica del sistema.
- `/lib`: Bibliotecas compartidas esenciales y módulos del kernel.
- `/media`: Punto de montaje para medios extraíbles.
- `/mnt`: Punto de montaje temporal para sistemas de archivos.
- `/opt`: Paquetes de software adicionales.
- `/sbin`: Binarios esenciales del sistema.
- `/srv`: Datos de servicios del sistema.
- `/tmp`: Archivos temporales.
- `/usr`: Jerarquía secundaria (binarios, bibliotecas, etc.).
- `/var`: Datos variables (logs, bases de datos, etc.).

### Sistemas de archivos
- **ext4**: El más usado, rápido y robusto, con soporte para volúmenes y archivos grandes.
- **btrfs**: Basado en árboles B, usa *copy-on-write* para mayor integridad, pero es más lento.

Para manejar y consultar cómodamente los montajes y discos conectados podemos usar las siguientes herramientas:
- lsblk: Para ver las distintas particiones y discos conectados
- df -h: Disk free, nos da el espacio disponible en disco, -h se usa para el formato humano

### /etc/fstab
Archivo que facilita montar/desmontar sistemas de archivos, su estructura se compone de varias columnas para cada sistema, con las siguientes correspondencias y orden:

- **Device**: Nombre o UUID del dispositivo (ej. `/dev/sda1`).
- **Mount Point**: Directorio donde se monta (ej. `/mnt`).
- **File System Type**: Tipo de sistema (ej. `ext4`).
- **Options**: Opciones de montaje (ej. `defaults`).
- **Backup Operation**: 1 para respaldo (obsoleto), 0 para ninguno.
- **FS Check Order**: 0 (sin chequeo), 1 (raíz), 2 (otros).

## Ejercicio Opcional: Servicio de Gestión Documental

Partiendo de un servidor básico configurado según el apartado 2 (Rocky Linux en VirtualBox con LVM, dos tarjetas de red y sshd), se plantea la instalación de un **servicio de gestión documental**. Este servicio requiere:
- **Espacio de almacenamiento creciente**: Posiblemente considerable con el tiempo.
- **Contenido crítico**: Necesita un mecanismo de respaldo ante fallos de hardware.
- **Máxima disponibilidad**: Garantizando la conservación de datos y continuidad del servicio.


## Diseño del Sistema de Almacenamiento

### Requisitos y Solución Propuesta
1. **Crecimiento del almacenamiento**: Usaremos **LVM** (Logical Volume Manager) para permitir la expansión dinámica del espacio, añadiendo discos según sea necesario sin interrumpir el servicio, (por ejemplo podríamos llevarnos el directorio /var a otro volumen lógico) (No se puede alojar a un volume group ya que al poder estar formado de varios discos, puede ser que perdamos garantías de RAID o tengamos un comportamiento no deseado)
2. **Redundancia ante fallos**: Implementaremos **RAID 1** (mirroring) para duplicar los datos entre dos discos, asegurando que un fallo en uno no comprometa la información. (RAID 5 también sería válido)
3. **Sistema de archivos**: Optaremos por **ext4** por su rendimiento, estabilidad y soporte amplio en Linux, aunque se considerará **btrfs** como alternativa por su capacidad de snapshots y mayor integridad de datos.
4. **Disponibilidad**: La combinación de LVM y RAID 1, junto con copias de seguridad regulares, maximizará el tiempo de actividad y la recuperación ante desastres.

# Acceso Seguro al Servidor

**iptables** es una utilidad de Linux para configurar el firewall a nivel de kernel. En Rocky Linux, usamos **firewalld**, un frontend más sencillo, gestionado mediante el comando `firewall-cmd`. Este se ejecuta como un servicio y podemos activarlo o verificarlo así:
```
sudo systemctl enable --now firewalld
sudo systemctl status firewalld
```

### Comandos básicos de `firewall-cmd`
- `firewall-cmd --state`: Muestra el estado del firewall.
- `firewall-cmd --reload`: Recarga la configuración (necesario tras cambios permanentes).
- `firewall-cmd --list-all`: Lista la configuración actual.
- `firewall-cmd --runtime-to-permanent`: Guarda los cambios temporales como permanentes.

## Zonas

Las **zonas** son conjuntos de reglas que se aplican según el nivel de confianza de la red. Ejemplo: conexiones Ethernet más confiables que Wi-Fi. Resumen de las principales zonas:

- **drop**: Bloquea todo el tráfico entrante sin respuesta; solo permite saliente.
- **block**: Similar a drop, pero rechaza con mensaje ICMP.
- **public**: Para redes públicas no confiables; permite conexiones selectivas.
- **external**: Para redes externas con NAT; oculta la red interna.
- **internal**: Para redes internas de confianza moderada.
- **dmz**: Para equipos aislados en una DMZ.
- **work**: Para redes de trabajo; confianza media.
- **home**: Para entornos domésticos; confianza alta.
- **trusted**: Máxima confianza; todo permitido (usar con precaución).

Normalmente usaremos **trusted**, **home** o **public**. Para ver la zona por defecto:
```
firewall-cmd --get-default-zone
```

### Gestión de zonas
- Cambiar zona por defecto: `firewall-cmd --set-default-zone=[zona]`
- Añadir interfaz a zona: `firewall-cmd --zone=[zona] --add-interface=[dispositivo]`
- Cambiar zona de interfaz: `firewall-cmd --zone=[zona] --change-interface=[dispositivo]`
- Eliminar interfaz de zona: `firewall-cmd --zone=[zona] --remove-interface=[dispositivo]`

## Puertos

Para servicios comunes como **SSH**, **FTP** o **HTTPS**, es mejor gestionarlos como servicios, no como puertos. Comandos útiles:

- `firewall-cmd --list-ports`: Lista puertos abiertos (alternativa: `nmap`).
- `firewall-cmd --zone=public --add-port=[numero]/[tcp/udp]`: Abre un puerto.
- `firewall-cmd --zone=public --remove-port=[numero]/[tcp/udp]`: Cierra un puerto.

### Gestión de servicios
- Lista de servicios disponibles: `firewall-cmd --get-services`
- Servicios activos: `firewall-cmd --list-services`
- Añadir servicio: `firewall-cmd --zone=public --add-service=[servicio]`
- Eliminar servicio: `firewall-cmd --zone=public --remove-service=[servicio]`

## Restricción de Acceso

Para un servidor no público (ej. acceso SSH restringido), hay dos enfoques:

### 1. Zona restrictiva con IP específica
1. Usa una zona como **trusted** y asigna tu interfaz.
2. Añade el servicio SSH: `firewall-cmd --zone=trusted --add-service=ssh`.
3. Restringe acceso a una IP o rango:
```
firewall-cmd --permanent --zone=trusted --add-source=192.168.1.0/24
```
(Cambia `--add-source` por `--remove-source` para revertir).

### 2. Combinación de zonas (público + privado)
Para un servidor con servicios públicos (ej. web) pero SSH restringido:

- **Zona public**: Interfaz asignada, con servicios como HTTP/HTTPS:
```
firewall-cmd --zone=public --add-service=http
firewall-cmd --zone=public --add-service=https
```
- **Zona trusted**: Solo para SSH desde un rango IP:
```
firewall-cmd --zone=trusted --add-source=192.168.1.0/24
firewall-cmd --zone=trusted --add-service=ssh
```
- Elimina SSH de la zona pública:
```
firewall-cmd --zone=public --remove-service=ssh
```

### Nota
Si pierdes acceso, reinicia el servidor desde el panel de control del VPS y ajusta la configuración. Guarda cambios con `--runtime-to-permanent` solo tras probar.

### Nmap
Nmap es una herramienta que permite explorar redes y hacer auditorías de seguridad. Está diseñado para escanear rápidamente redes grandes, tiene muchas posibilidades y configuraciones así que vamos a dar algunos comandos que pueden resultar útiles en nuestro caso de uso:

```
sudo nmap -v direccion.es
nmap -sS xxx.xxx.xxx.xxx/24
```
La primera activa el modo verbose para escanear puertos reservados (TCP) en la máquina dada y el segundo lanza un escaneo SYN hacia las 256 IPs de la red dada
En caso de no tener esta herramienta instalada en su MV Rocky Linux, puede instalarla con `sudo dnf install nmap`

## Ejercicio Opcional

### Nginx 
Nginx es un servidor que podemos usar para montar un servidor web o un reverse proxy.

Para instalar Nginx en Rocky Linux, ejecutaremos el siguiente comando que usa el gestor de paquetes dnf (recomendable hacer update antes)
```
sudo dnf install nginx
```

Una vez instalado, ejecutaremos el siguiente comando para empezar el servidor web:

```
sudo systemctl enable nginx
sudo systemctl start nginx
```
Con esta configuración ya se iniciará nginx cada vez que reiniciemos la máquina virtual, deberemos tener en cuenta en el firewall este servicio:

```
sudo firewall-cmd --permanent --add-service=http 
sudo firewall-cmd --permanent --list-all
```
De otra forma podemos hacer que la configuración actual sea permanente mediante:
```
sudo firewall-cmd --runtime-to-permanent
```
Que deberá incluir en la linea services: http. Además deberemos recargar la configuración para hacer el servidor accesible a visitantes externos
```
sudo firewall-cmd --reload
```
Además se sugiere el siguiente comando para saber nuestra ip publica y accediendo al servidor:
```
curl -4 icanhazip.com
```
### Apache

**Nota:** Si has realizado la configuración para el servidor de Nginx, asegurate de pararlo primero con `sudo service nginx stop` para que libere el puerto 80 y así lo pueda usar tu servidor de Apache.

Veamos ahora la configuración equivalente para un servidor en apache:
```
sudo dnf -y install httpd
mv /etc/httpd/conf.d/welcome.conf /etc/httpd/conf.d/welcome.conf.org
vi /etc/httpd/conf/httpd.conf
```
Ahora cambiaremos las siguientes líneas:

- ServerAdmin (Pondremos el correo del administrador)
- ServerName (Pondremos el nombre o dirección del servidor)
- Options (Quitaremos los índices)
- AllowOverride (All)
- DirectoryIndex (index.html index.php index.cgi (Según lo queramos configurar nosotros))

```
systemctl enable --now httpd
```
Ahora el firewall igual que antes:
```
sudo firewall-cmd --permanent --add-service=http 
sudo firewall-cmd --reload
sudo firewall-cmd --permanent --list-all
```

Podemos probarlo ahora creando una página web en /var/www/html/index.html 
```
<!DOCTYPE html>
<html>
    <body>
        <h1>Bienvenidos a la Web de [Tu Nombre y Apellido] en Prácticas ISE</h1>
    </body>
</html>
```

## Ejercicio opcional
Eligiremos uno de anteriores programas, ejecutaremos el procedimiento dado para iniciar el servidor y editaremos el archivo index.html para que muestre:

Bienvenidos a la Web de <Nombre y Apellido> en Prácticas ISE

Para comprobar que está bien realizado, podemos tanto entrar a la página web como escanear los puertos sobre el servidor y comprobar que muestra ssh y el de http

# SSH y Criptografía

## SSH

SSH (Secure Shell) es una aplicación de terminal remoto segura que reemplaza soluciones antiguas como Telnet, donde tanto el inicio de sesión como la sesión se transmitían en texto plano, sin cifrado. En SSH, tanto el proceso de autenticación como la sesión están protegidos mediante cifrado.

- **Uso básico**: `ssh usuario@ip/nombreDominio`.
- **Ventaja**: Utiliza varias técnicas criptográficas para garantizar seguridad.
- **Nota**: El término SSH puede referirse tanto al cliente como al servicio. Para el servicio, a menudo se usa `sshd` (demonio de SSH). OpenSSH es la implementación más común y segura.

### Servicios incluidos en OpenSSH
- **Operaciones remotas**: `ssh` (conexión), `scp` (copia segura), `sftp` (transferencia de archivos segura).
- **Gestión de claves**: `ssh-add`, `ssh-keysign`, `ssh-keyscan`, `ssh-keygen`.
- **Lado del servidor**: `sshd`, `sftp-server`, `ssh-agent`.

### Configuración recomendada
- Limitar el acceso por contraseña al usuario `root`.
- Cambiar el puerto por defecto (por ejemplo, de 22 a otro mayor a 1024).
- Actualizar la configuración del firewall (`firewalld`) tras cambiar el puerto.
- Automatizar comandos remotos usando claves simétricas y asimétricas.

---

## Repaso rápido de criptografía y seguridad

### Algoritmos más comunes

#### Llave simétrica
- **Definición**: Usa un secreto compartido entre las partes.
- **Características**:
  - Muy eficiente computacionalmente.
  - Ideal para ciertas circunstancias.
- **Algoritmo más usado**: DES (Data Encryption Standard), aunque hoy se considera obsoleto; AES (Advanced Encryption Standard) lo ha reemplazado ampliamente.
- **Problema**: 
  - Escalabilidad limitada.
  - Solución parcial: Llaves por pares, pero sigue siendo ineficiente a gran escala.
- **Solución**: Esto motivó el desarrollo de algoritmos de llave asimétrica.

#### Llave asimétrica (clave pública - privada)
- **Definición**: Cada entidad tiene dos claves:
  - **Pública**: Compartida con todos.
  - **Privada**: Secreta y personal.
- **Problema**: Requiere obtener las claves públicas de los interlocutores, pero al ser públicas, esto es manejable.
- **Algoritmo principal**: RSA.
- **Desventaja**: Alto costo computacional.

#### Hash
- **Definición**: Genera un valor único (hash) a partir de datos.
- **Ejemplo**: Familia SHA (Secure Hash Algorithm), como SHA-256.
- **Características de un buen hash**:
  - Un pequeño cambio en los datos produce un hash completamente diferente.
  - No es reversible (unidireccional).

### Identidad y firma digital
- **Garantía**: Mediante firma digital.
- **Proceso**:
  1. Calcular el hash de la información.
  2. Cifrar el hash con la clave privada del emisor.
- **Verificación**:
  1. El receptor descifra la firma con la clave pública del emisor.
  2. Compara el hash recibido con el calculado.
  - **Resultado**: Confirma integridad y autenticidad.

### Autoridades de certificación
- **Función**: Validan la correspondencia entre claves y personas/entidades.
- **Ejemplo (España)**:
  1. Generación de claves pública y privada.
  2. Envío de la clave pública a la FNMT.
  3. Validación presencial ante un funcionario.
  4. Emisión de un certificado por la FNMT.
- **Contenido del certificado**:
  - Datos personales.
  - Información adicional.
  - Firmado con hash y clave privada de la FNMT.
- **Formato común**: X.509.

### Cadena de certificación
- **Funcionamiento**: Certificados firmados recursivamente hasta un certificado raíz.
- **Confianza**: Basada en claves públicas preinstaladas en el software.
- **Visualización**:
  1. Clic en el candado del navegador.
  2. "Más información" > Ver certificado.
  3. Seguir la cadena hasta el raíz (Configuración > Certificados).

---

## Cómo funciona SSH

SSH combina criptografía simétrica y asimétrica para garantizar confidencialidad y autenticación.

### 1. Confidencialidad de la comunicación
- **Proceso**:
  1. El cliente inicia `ssh usuario@ip`.
  2. El servidor envía su clave pública.
  3. El cliente cifra la contraseña con esa clave pública y la envía.
  4. El servidor verifica la contraseña en su base de datos y responde.
- Al aceptar, la clave se guarda en `~/.ssh/known_hosts` para futuras conexiones.

- **Cifrado de la sesión**:
1. El servidor envía su clave pública.
2. El cliente genera una clave de sesión (secreto simétrico), la cifra con la clave pública del servidor y la envía.
3. Ambos usan esta clave simétrica para el resto de la comunicación, reduciendo el costo computacional.

- **Nota**: La criptografía asimétrica se usa solo para autenticación e intercambio inicial; luego se pasa a simétrica por eficiencia.

### 2. Acceso sin contraseña (autenticación por claves)
- **Proceso**:
1. El servidor tiene una base de datos de claves públicas en `~/.ssh/authorized_keys`.
2. Al conectar, el servidor envía un "challenge" (mensaje aleatorio).
3. El cliente firma el challenge con su clave privada y lo devuelve.
4. El servidor verifica la firma con la clave pública del usuario y, si es correcta, permite el acceso.

- **Generación de claves**:
```
ssh-keygen -t rsa -b 4096
```
- Genera `id_rsa` (privada) y `id_rsa.pub` (pública) en `~/.ssh/`.
- Se recomienda proteger la clave privada con contraseña.

- **Envío de clave pública al servidor**:
```
ssh-copy-id usuario@ip
```
- Añade la clave pública a `~/.ssh/authorized_keys` en el servidor tras ingresar la contraseña por última vez.

- **Uso**: Ahora se puede conectar sin contraseña:
En el siguiente ejercicio aplicaremos estos conceptos.

## Ejercicio opcional
**Nota:** Se aconseja crear un clon de la MV. De está forma una actuará como servidor y otra como cliente. Recordad cambiar el hostname y la dirección ip en el clone. 
Otra opción es usar una MV como servidor y el anfitrión como cliente.

### Cambiar el puerto de SSH
Editamos el archivo de configuración de `sshd`:
```
sudo vi /etc/ssh/sshd_config
```
- Buscamos la línea `Port 22` y la sustituimos por un puerto mayor a 1024, por ejemplo, `2025`:
- Verificamos en `/etc/services` que el puerto no esté en uso por otra aplicación.

Actualizamos el firewall:
```
sudo firewall-cmd --permanent --remove-service=ssh
sudo firewall-cmd --permanent --add-port=2025/tcp
sudo firewall-cmd --reload
```

Reiniciamos SSH: 
```
sudo systemctl restart sshd
```
En caso de error en el archivo de configuración o de que no tiene permiso para utilizar ese puerto a pesar de ser un puerto > 1024 y estar libre, puede ser que lo esté bloqueando SELinux. Para solucionarlo:
```
sudo dnf install policycoreutils-python-utils
sudo semanage port -a -t ssh_port_t -p tcp 2025
```
Se puede comprobar que se ha añadido correctamente con:
```
sudo semanage port -l | grep ssh
```

## Configurar acceso por clave pública
Generamos un par de claves en el cliente usando RSA (Podríamos haber usado cualquier otro método, por ejemplo para GitHub se suele usar ed25519)
```
ssh-keygen -t rsa -b 4096
ssh-copy-id -p 2025 usuario@<IP-del-servidor>
```
- Sustituye `usuario` por el nombre del usuario remoto y `<IP-del-servidor>` por la dirección IP real.

### Validación
Comprobamos la configuración ejecutando un comando remoto:
```
ssh -p 2025 usuario@<IP-del-servidor> "ls -la /"
```
- Esto debería mostrar el contenido completo del directorio raíz (`/`) sin pedir contraseña.

### Seguridad adicional (opcional)
Para limitar el acceso por contraseña y al usuario `root`, editamos `/etc/ssh/sshd_config`:
```
PermitRootLogin no
PasswordAuthentication no
```
Reiniciando el servicio podremos comprobar que ya se puede acceder sin contraseña.

## Ansible
Ansible es una herramienta que automatiza la gestión remota de sistemas y controla su estado deseado.
