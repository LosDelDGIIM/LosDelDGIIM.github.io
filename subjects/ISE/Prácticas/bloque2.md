# 1. Introducción. Contenedores
Usaremos docker para gestión de contenedores, por ser el más extendido.
Tenemos que instalar el engine de docker en el equipo anfitrión (ref [8], buscar por centOS). 
    **Hay un último paso opcional que es para dar permisos de correr contenedores sin ser root (añadir el usuario dentro del grupo de docker), hacerlo**.
    Podemos instalar Docker Desktop para herramientas gráficas.
Ver [7] (interesante).
Las practicas no van a ser de contenedores.

## VM vs Containers
Ver la diferencia de capas de abstracción.
Solo hay soporte para contenedores de forma nativa en linux y windows. La tecnologia es nativa a linux. 
    Mac crea una maquina virtual linux para correr docker. La distribucion docker de mac viene una vm: hyperkit (hipervisor para mac). Antiguamente era un virtualbox.
    Windows hacía esto antes.

Encima del SO tenemos el engine (en nuestro caso Docker) y encima tenemos la app.

Caracteristicas. (en resumen, no virtualizan)
- Los contenedores no virtualizan: sobre un SO linux solo podemos correr aplicaciones linux. Por esto no podemos usar windows, vamos a correr contenedores linux.
- No virtualiza a nivel de SO ni a nivel de infraestructura: todos los cores / discos duros están disponibles para la aplicacion.

### Ventajas de los contenedores
- Namespace de linux: tecnologia muy antigua (anterior a contenedores). Permite que si estamos en una shell y ejecutamos `namespaces` en `/home/carlos/dev/trabajos`, inmediatamente crea un sistema de ficheros virtual y lo coloca en la raíz. Al hacer `ls` estamos en ese directorio pero da la sensacion de que estamos en la raiz (no podemos hacer cd ..).
    A partir del momento, cualquier programa que ejecutemos aqui solo tiene información desde este punto hacia debajo, no puede tocar nada fuera de este entorno.
    Primer concepto: crear un entorno de ejecucion (llamado sandbox) de donde no se puede salir, introducimos un nivel de seguridad, a efectos de que el codigo toque cosas que no se debe.
- Además, crea un espacio de procesos independientes. Si ejecutamos ps -ax, solo se ven los procesos de la aplicacion, no se puede hacer comunicacion entre procesos.
Las primeras implementaciones de contenedores utilizaron estos namespaces.


Además, a esto le añaden el concepto de "red virtual": comunicar entre sí distintas aplicaciones mediante una red que no es real. El modelo por defecto es bridge.
Esto es una extension propia de los contenedores (no de los benchmarks).


No hay diferencia en cuanto a performance por el uso de los contenedores.
    El único en el que hay pérdidas es en la red, porque esto sí que es algo virtual. Hay una pequeña degradación.
En las aplicaciones de contenedores lo normal es que haya varios contenedores que se comuniquen entre ellos. Si un contenedor hace uso de una interfaz para acceder afuera es una tarjeta real, por lo que no hay pérdida de prestaciones, solo la hay entre contenedores.


Ventajas:
1. Concepto de seguridad
2. La que vamos a ver ahora (sobre la distribucion de soluciones)

Cuando distribuimos un contenedor por rpm o un instalador de windows, los instaladores instalan algunas cosas en el sistema de ficheros, por lo que al desinstalar la aplicacion a veces se desinstala todo o se quedan algunos archivos.
Tambien puede pasar que las aplicaciones dependan de dependencias externas y en cuyo caso intente instalarlas o sea necesario que el usuario lo haga.
La gestión de software con instaladores tiene su problematiac.

Si lo hacemos con contenedores, distribuimos un filesystem que distribuye todas las dependencias necesarias en el entorno del contenedor.
Cuando estamos en un entorno de desarrollo, estamos corriendo sobre docker. Al pasar a un entorno de produccion, como se llevan todas las dependencias en el contenedor, va a funcionar exactamente igual que en la etapa de desarrollo, lo que garantiza que a efectos de distribución la solución distribuida está autocontenida, es independiente.


La mayor parte de aplicaciones de contenedores son bastante complejas, aunque hay otras soluciones muy basicas.
Cuando se distribuye una imagen de contenedor, no se distribuyen todas las dependencias, sino un archivo Dockerfile que contiene todas las dependencias a descargar.
Hay versiones de linux hechas para ser base de contenedores.

**Resumen**:
- No virtualiza
- Performance igual que en nativo: no hay pérdida de prestaciones (salvo el caso de red entre contenedores).
- Se utiliza para distribucion de aplicaciones por tener soluciones autocontenidas.

## Hola mundo
EL hola mundo es un contenedor trivial (dockerhub es un repositorio de contenedores para docker). Se usa solo para probar que la instalación de docker ha sido correcta.
El engine se instala con un servicio el engine: tenerlo siempre levantado.
Las imagenes de docker están versionadas (en las etiquetas).



docker pull hello-world
docker run hello-world
Saca un mensaje que dice que todo parece que funciona correctamente.

Que una imagen esté basada en ubuntu siginifica que contiene el filesystem normal de ubuntu.


docker images (ver los contenedores disponibles)

## Benchmarks
El proyecto mas significativo de benchmark open-source es OpenBenchmarking, un repositorio específico con código para benchmark.
Tiene una herramienta phoronix que permite bajar los benchmarks y ejecutarlos de forma sencilla. Están discontinuando su mantenimiento, en la parte de downloads no hay opcion de bajar los instaladores, solo se puede bajar a traves de github. Aquí podemos bajarnos los rpm, aunque lo mejor es bajar un zip y compilar en local.

Vamos a ejecutar la herramienta mediante un contenedor de docker. **Basta con saber los 3 puntos del ejercicio opcional**.


docker pull phoronix/pts
docker run -it phoronix/pts

it: para que se quede el contenedor en primer plano y dar terminal interactiva (los contenedores no están orientados a esto).

system-info: información del hardware
system-sensors: informacion sobre sensores
Tiene acceso a todos los cores. Tiene sentido correr benchmarks sobre contenedores (ya que no degrada prestaciones).

La aplicacion tiene acceso a toda la estructura subyacente, pero es usual que los engines de los contenedores limiten esta capacidad.
Esto hace que las aplicaciones que corren sobre contenedores pueden ser que las tengamos que adaptar.
Las aplicaciones sobre contenedores sí se enteran de que están sobre contenedores. De hecho, tienen que saberlo.
    La VM java intenta acaparar una cantidad de memoria y usar todos los cores. Al correr una app java sobre un contenedor y limitamos los cores, el engine de contenedores limita a la aplicacion matandola. Hay que adaptarlo para contenedores.
    Si se accede a bajo nivel, hay que saber cual es el limite para que el engine no mate nuestra aplicacion. Hay que averiguar los cores que están disponibles. Codigo distinto para contenedores: adaptar la aplicación. Es algo comun.
    

openbenchmarking: tests son agrupaciones de benchmarks que alguien considera que es bueno para unas ciertas aplicaciones.


list-available-suites: tarda mucho, para ver todas las suites

list-available-tests: list todos los tests
Tipo:
    System: todo el sistema
    memoria, procesador, red, ....
    

### gzip
Es dificil encontrar un benchmark que no tenga dependencias. Recomienda no instarlar las dependencias.
- gzip (un benchmark sin dependencias) 

info <test>: nos da informacion sobre el benchmark. Nos dice las dependendicas, entre otras. Para gzip nos dice que no necesita.

install pts/compress-gzip y luego becnhmark
o luego: benchmark pts/compress-gzip (si no esta instalado, lo instala y lo ejecuta)

Cuando finaliza nos pide resultados y nombre para guardar información.



Para recuperar resultados: list-saved-results
Tenemos otros comandos para ver detalles de resultados.

show-result <id>: recuperamos resultados.


Por defecto los contenedores de docker usan un espacio de almacenamiento interno. Para exportarlo, montar volumenes.

### Apache benchmark
Para hacer benchmark de servidores http (da igual si es apache, nginx, ...), lo que importa es que esté el protocolo http.
opciones:
- n: nº peticiones
- c: concurrencia

(20 peticiones con 4 hebras)
ab -n 20 -c 4 http://www.ugr.es/

Document length: es muy pequeño, hay no hay una pagina web. Problema: https



**curl hay que manejarlo** Es para realizar peticiones http
curl -v http://www.ugr.es

Nos muestra la conexion, cabeceras y cabeceras de respuesta. Vemos codigo 301: movido permanentemente y nos dice a donde se ha movido: https.



ab -n 20 -c 4 https://www.ugr.es/
Ahora el tamaño si que tiene sentido

La tabla de métricas es interesante.
- connect time: lo que tarda en abrir la conexión. Valor minimo de las 20 peticiones.
- processing: tiempo del server en procesamiento. Valor minimo de las 20 peticiones.
- Total: no tiene por uqe coincir con connect + processing.
- waiting: tiempo transcurrido desde GET / hasta recibido el primer byte.

da tmb percentiles.

Comando muy sencillo que hace que no sea bueno para realizar prueba de carga compleja.
Para hacer prueba rapida de un endpoint que queremos ver que está funcionando más o menos bien. smoketest (si sale humo, funciona).
Para tests en profundidad, jmeter.

# JMeter
Aplicación java de apache muy antigua y muy utilizada por la industria. Lleva tanto tiempo que forma parte del catalogo de las soluciones.
Recomienda cambiar JMeter al ingles, ya que los campos no estan bien traducidos.
Al configurar un test, dar documentacion del mismo.
JMeter cuenta con muchos plugins de empresas (como de cisco)

Añadir > threads (usares) > thread group
Simula un grupo de usuarios que acceden a la vez con un perfil de trabajo concreto. Vamos a crear un thread group para acceder a unas direcciones concretas para simular a un grupo de usuarios distintos.
Cada grupo de thread modela los habitos de los usuarios.

name: estudiantes.

Tres parametros fundamentales:
- Número de threads (users): va a lanzar ese numero de hebras (usuarios). Al empezar a trabajar dejarlo en 1.
- Ramp-up period (seconds): en los tests de carga: . Es el periodo en el que vamos a incrementar la carga de trabajo. 10 users y 10 seconds: levanta una hebra cada segundo. Jmeter lo hace de forma lineal.
    warmup: es irreal arrancar un servidor y que de repente le lleguen 100000 de accesos. La arquitectura solicita recursos de forma progresiva.
    cooldown: lo mismo pero al reves.
- Loop count: cuantas iteraciones vamos a hacer.

Sobre este:
Add > Sampler > http request
- Server name: www.ugr.es
- HTTP Request:
    - GET
    - path: /

Hacen falta Listeners para ver los resultados.
Add > Listener > View Results Tree      (se usa para depurar, en produccion no se usa). para deshabilitarlo: click derecho y deshabilitar.
Add > Listener > Aggregate/Summary Report 


Guardamos y ejecutamos.
View results: verde = bien.

Borrar resultados: click dcho > clear


Advanced: Para simular una crga mas realista, le podemos dar a "retrieve embebed", para que se baje todo lo ue se bajaría un browser.

##### Mas
Los estudiantes suelen entrar a un sitio:
    Añadimos otro http request para simular que los estudiantes se meten.
    
Add > Timer, para añadir delays entre "clicks". Este tiempo no se tienen en cuenta en las estadisticas.

Add > config element > valores por defecto
    Para no repetir parametros en distintas cosas, metemos uno de estos y se añade en todos.
    
##### Variables
Podemos definir variables en "user defined variables".
HOST: IP

Para usarlas: ${HOST}.

Si queremos usar varios thread grups, mover los listeners al nodo principal.



Cuando pasamos a produccion y queremos ejecutarlo contra los equipos, de verdad, cambiar parametros.
NUNCA LANZAR A PRODUCCION EN ENTORNO GRÁFICO: CERRAR Y:
    jmeter -n -t./asdfa.jmx -l results.jtl
        -n: no abre modo gráfico
        -t: el archivo
        -l: donde guarda los resultados (archivo csv para excel).
        
Si abrimos el archivo de resultados con jmeter, y abrimos un sumary, pinta los resultados.

### Ejercicio
##### Preparar el entorno para el ejercicio
Meterse al repositorio para el ejercicio. Leer README.

docker compose up
-d: quedarse atras como demonio (no usarla).

API RES: resource estate transfer: una práctica que utiliza los verbos de http para hacer operaciones de tipo CRUD sobre entidades remotas (crear alumno, borrar, ...).
    Es comun que RES utilice JSON para serializar parametros.
    
Una interfaz RES tiene 2 endpoint (es una api privada):
- Un endpoint para loggearnos. En uno introducimos nuestro nombre y contraseña para obtener acceso, un token jwt (javascript web token).
- Otro es la consulta de un expediente academico, pasando la llave anterior.

Hay dos perfiles: alumnos, estudiantes y administradores.
Los estudiantes solo pueden ver su expediente. Loa administradores pueden ver cualquier expediente.

El fichero pruebaEntorno.sh tiene dos llamadas a curl, haciendo un post 
En jMeter > alumnos.csv tenemos login - passwd validos para alumnos y administradores.

./pruebaEntorno
Si todo va bien, nos da un resultado. Usar JSONPretty.
En cuyo caso, esta el entorno listo

##### El ejercicio en sí

# Sesión 2 de Bloque 2
##### El ejercicio en sí
Seguimos con el ejercicio: damos uusario + passwd y obtenemos JWT Tocken.
Pasamos el Token en una cabecera.

Mecanismos de autenticación en la API:
1. El token. Vamos a ver cómo funciona
2. BasicAuth

## JWT Token
Es una cadena codificada (no cifrada) en base 64 con 3 partes separadas por . : cabecera.payload/contenido.firma
JWT Debugger (página web): Podemos ver cuándo fue emitido, cuándo expira
No se pueden meter información confidencial en un token JWT, como un correo.
Lo que sí, los tokens están firmados, lo que nos garantiza quién creó el token.

## BasicAuth
Protocolo de identificación más simple. Obsoleto.
Es para paliar el problema del ruido de canal:
    siempre que exponemos un servicio a internet, está siendo continuamente atacado.
    Un mecanismo sencillo es filtrar las llamadas con el BasicAuth.
    No lo usaremos para autenticarnos pero es un filtro para acceder a la API: evitando ese ruido.
    
Se encuentra con la opción -u en el script con curl.

##### Requerimientos del ejercicio (CÓMO SE HACE)
LOOP COUNT > 1

Vamos a usar un log como fuente de acciones a realizar.
Parametrizar el endpoint (el servidor).
Para definir variables: Sobre el proyecto, añadir.
Add > config element > http request defaults
Add > config element > http authorization manager (basic auth)

Alumnos > add > http request:
    name: login
    post
    En el cuerpo añadimos los parámetros (tienen que cambiar para cada alumno, en el valor hay que poner una variable):
        login       correo@ugr.es
        password    asdfasdfasf
        
    Para las variables: add > config elemnt > csv data set config: lee archivo csv y lo mete en variables.
    
Alumnos > add > http request:
    name: consultar expediente
    get
    path: /api/v1/alumnos/alumno/${EMAIL}   Hay que ponerlo en funcion deu na variable
    
    Pasar el token: 
    Add > config element > http header manager:
        authorization: Bearear ${TOKEN}
    
    De dónde sale el token? La peticion de login la devuelve, hay que extraerlo:
    Add > post processors > regular expression extractor
        Configurar para que meta el token en una variable
        


Para los administradores se hace igual con los datos de los administradores pero:
En lugar de hacer una llamada clásica, vamos a usar el contenido del archivo apialumnoslogs (el archivo de log de antes):
    Add > sampler > access log sampler
        log file: 
        
    Los samplers que leen de archivos es **OBLIGATORIO** que los paths sean relativos.
        **HAY QUE TENER CUIDADO PORQUE EL BROWSE PONE LA RUTA ABSOLUTA, cambiar por ./asdfasdf/asdf...**
    Para ello, hay que lanzar JMETER en el mismo sitio donde guardamos el archivo.
    
Los ficheros de datos los tiene, hay que subir el fichero que nos genera el jmeter y poco más:
    jmeter -n -t Ejercicio.jmx 
    
## (3.2),  dockerfile y docker-compose
## Docker-compose
Cuando lanzamos: `docke compose up`, funciona porque hay un fichero de `docker-compose.yaml`.
Es una herramienta de orquestación de contendores. La herramienta más importante es cubernetes, pero docker-compose es un cubernetes sencillo.

En un entorno de ejecución de docker-compose lanza los distintos contenedores y monta una red interna que permite que se comuniquen entre sí. Lanza los contenedores y asegura que tengan comunicación entre sí.
services: cada una de las entradas es cada uno de los servicios que vamos a lanzar. Por ejemplo:
- mongodb
    - image: mongo:6        Se baja automáticamente la imagen especificada de dockerhub: docker pull mongo:6;docker run mongo:6
    - ports:
        - "27017:27017"     Publica el puerto: anfitrión:contenedor.
- mongodbinit
    - build: ./mongodb
    - links: mongodb
- nodejs
Equivalente a lanzar 3 máquinas virtuales (en el contexto de VM).


mongodb Expone el puerto para que te conectes con él. Tanto mongodbinit como el otro van a poder comunicarse con este puerto, pero no desde fuera.
Si queremos conectar desde fuera al 27017, tenemos que publicar el puerto (por defecto están protegidos). Lo que hacemos con la fila esa es publicar el 27017 en el 27017.

mongodbinit es un contenedor efímero: se lanza, ejecuta un comando sobre mongodb y listo.
link: por una parte, indicamos que un contenedor depende de este y que mongo le de init y resuelva por mongodb la resolución del servidor.
    Cada vez que docker-compose inicia la estructura, asigna una direccion distinta a cada uno de los servidores.
    Para que desde un servidor consigas abrir una conexión de shell hacia otro, se hace con esto, con mongodb.
    Lo que hará docker-compose será abrir una entrada en /etc/hosts con este nombre hacia la IP indicada en link. Permite trabajar con nombres simbólicos sin tener un DNS.

##### Diferencia entre imagen y build
Tenemos un archivo docker-file, con primera línea:
FROM mongo:6
Los docker-file son como los makefile y se usan para construir contenedores, a partir de un contenedor base (el que indica FROM).
Como queríamos tener las herramientas de mongo, la forma más útil es basarse en la misma distribución de mongo y posteriormente ejecutar la tarea.

# Monitorización
## top
La versión `htop` es más bonita.
Da información de variables de uso de cómputo del SO.
Expone variables importantes en muchos otros entornos.

La primera línea es el uptime. Puede obtenerse con uptime tmb. La diferencia entre top y por uptime es que uno es foreground y otro es el output.

top lo que hace es consultar la información que se encuentra en el sistema de ficheros /proc.

##### watch -n seg comando
Es para mostrar cada seg segundos un comando.

### /proc 
No es un directorio persistente, sino que se monta en memoria. Información volátil y completamente actualizada. Propósitos:
1. Monitorear el sistema.
2. Tunear el comportamiento del kernel de linux.

Tenemos carpetas con el PID de cada proceso. Si nos metemos en una carpeta, tenemos varios ficheros con información sobre los mismos.

- loadavg: de donde uptime y top extraen la información. 1/116: De 116 en ejecución, 1 está running.
- meminfo: información de memoria.

Ventajas de directorios y ficheros.
1. Jerárquica.
2. fread y fwrite disponible en todos los lenguajes, no hace falta crear APIs. Los software de 3os son más fáciles de crear.


##### Tunear el kernel
Para tunear el kernel: /proc/sys. Tenemos parámetros de configuración del kernel. 

Si queremos que nuestro pc actúe de rutering, hay que activar el parámetro:
net/ipv4/ip_forward.
echo 1 > ip_forward

Podemos cambiar el tamaño de la ventana TCP.
Podemos cambiar el tamaño de paquetes TCP, time2live, ...

Los parámetros al reiniciar el pc se pierden (estamos en /proc). Dos opciones:
1. Recompilar el kernel de linux.
2. Ir a /etc y cambiar un fichero (no lo sabe)

#### free
da información sobre el uso de memoria.
vmstat tmb hace algo parecido.

### load average de top
Se usa mucho en el mundo UNIX/Linux. Los tres valores son: uso de CPU en los últimos: minuto, 5 min, 15 min.

Si tenemos 1 core y un 1.0: CPU usada al 100%
Si tenemos 1 core y un 2.0: CPU en sobreuso del 200%: no ha podido atenderlo todo.
Si tenemos 4 core y un 2.0: CPU usada al 50%

Hay que tener en cuenta el nº de cores del sistema al consultar la cantidad.

### 2a linea
Sobre información de los procesos:
total, corriendo, durmiendo, esperando salidas, zombies.

Zombie: proceso que muere pero que no ha liberado los recursos liberados.
Si vemos cosas en zombie, un proceso tiene alguna fuga de recursos: ha hecho un malloc y no ha hecho un free. 

### 3a linea
% de uso de CPU: load average pero lo divide en uso de CPU en espacio de usuario (us), espacio del sisetma, instrucciones privilegiadas e instrucciones nice.
idle: cuenta del tiempo parado, waiting: op de entrada/salida, hardware int, software int, stolen: SO que soportan virtualizacion, los ciclos de virtualización robados los muestra.

### 4a linea
Estadística de memoria: memoria principal: total, libre, usada, destinada a buff/caches (espacio del SO para operaciones de E/S).
La memoria de buff/cache en un momento dado la puede liberar. La memoria "avail Mem" no coincide con libre, es una estimacion de la memoria principal que puede demandar a un proceso en un momento dado. 
Este dato debería ir en la fila de arriba, pero por organización va en la fila de swap.

### 5a linea
Estadística de memoria: memoria swap.
0% usada es ideal.

## stress-ng
Programa para estresar equipos Linux.
Muy útil, mucha documentación, puede generar zombies, waitings, ...

Vamos al final de man y copiamos el 2o ejemplo.

##### Ejercicio opcional
Ejercicio de estrés con top.

## Sistema de logs
Todos los linux usan el servicio systemd, el responsable de loggear: recibir logs del kernel y distintos servicios en funcionamiento y enviarlos a localizaciones preestablecidas, en /var/log.
Hay una serie de archivos del SO, la mayoría en modo texto.

El más importamente es el messages, mucha información sobre lo que ocurre en cada momento en el sistema.
Tenemos también los comandos who y last (usan archivos binarios de aquí): quien esta loggeado ahora, ...

### logger
Permite mandar mensajes al sistema de logs.
Podemos tener una tarea programada que mande una informació periódicamente al archivo messages:
    logger -t ise "hola"
    
## cron
Hay dos soluciones para tareas periódicas: cron y systemd timers (mucho más potentes y complicados de programar).
Cron es muy sencillo de programar y es un standar de facto muy usado. Existen muchas páginas web (como cron guru, cron expression tool), que permiten conversión cron-calendario-cron.

El programa que ejecuta las tareas es crond, que continuamente lee el archivo de configuración y actualizando memoria sobre la acutalización de las tareas.
El fichero es /etc/crontab. No escribiremos directamente ahi.

Lo normal es no ser root del sistema. Para programar tareas, usamos `crontab -e`, que crea un crontab específico para un usuario no privilegiado.
cron no tiene consola, no podemos hacer echo. Sin embargo, podemos pasar cosas al logger: logger -t tag
crontab lo comunica directamente a cron.

##### Ejercicio
Programar tarea con cron y logger en el que se mande lo indicado.

#### date
Admite formados, ver el man.

## Seguimos con los logs
En /var/logs:
La forma buena de ver los logs es utilizando el comando `journalctl`. Permite filtrar bien lo que estamos buscando.

Mostrar los mensajes creados por un usuario y que lo mande por un orden de prioridad (de este para arriba).
`journalctl -f --facility=user -p warning `

Para verlo:
`logger -p user.warning -t ISE "mensaje`

Consultar los logs de arranque del kernel de linux (a veces salen logs rojos que se pierden muy rápido) (b de boot):
`journalctl -b`
`journalctl -b -p warning`

systemd solo guarda los logs desde el ultimo boot. Para guardar mas, hay que activarlo explicitamente:
/etc/systemd/journal.conf
Cambiar la opción Storage por 'yes' para que almacene siempre.

`journalctl --list-boots`
Para listar los boots que tenemos guardados.
`journalctl -b -2` para ver 2 boots anteriores.

### Rotación de logs - logrotate (no hace falta ver cómo se configura)
En /var/logs hay archivos que tienen una fecha.
Cuando se cumple uno de los dos criterios se crea una copia.

Llenar logs puede bloquear el sistema.
Si se hacen muy grandes, no hay herramientas de edición que puedan abrirse. Existen varias soluciones para rotación de log. La más estándar es logrotate.
Un programa que hay que ejecutar explicitamente (no es un servicio).
Lo normal es que esté programado en cron o systemd timers.

La configuración está en /etc/logrotate
Especifica lo que hará con los ficheros de archivos. Lo normal es rotar y comprimir.

La configuración real está en /etc/logrotate.d, donde hay varias configuraciones para los distintos archivos. Veamos el de apache (httpd):



Lo importante es ver cómo se realiza la rotación: hay que matar al proceso que escribe. Este es un problema de logrotate.
sshd, apache, ... son capaces de ejecutar reload, para permitir la rotación de logs.
Si no tenemos programas con reload, lo mata y lo abre. Hay una alternativa (no cae), rotatelogs.
    Se prefiere que los logs no se manden a archivos, sino a stdout. logrotate se conecta con un pipe, recibe logs y rota archivos él solo.
    Es el programa externo quien se encarga de manejar los logs.
    
# Sesión 3 de Bloque 3. Grafana + Prometheus
Productos distintos que combinan muy bien.

## Prometheus
Accede a las máquinas a monitorear en una operación llamada 'scrapping' para obtener sus métricas (por HTTP), que almacena en una BD.
Para ello, cada nodo implementa un 'exporter'.
Hay una configuración estándar, las metricas se recuperan siempre de `/metrics`.

Lo que se almacena en la BD son series temporales: tiempo + datos recopilados. La BD permite obtener informaicón en base a tiempo de forma cómoda.

Prometheus ofrece una GUI a través de una página web muy pobre. Las alertas también son pobres. Por ello, usaremos Grafana.

Los exporters de Prometheus exportan en HTTP en texto plano, por lo que es fácil crear nuestros propios exporters, para medir parámetros que nos interesan.
Solamente trabaja con pull: sacar información de los nodos. Otros programas usan push (son los equipos quien envían la información).

## Grafana
Se puede combinar con otros orígenes de información.
Realiza consoultas sobre prometheus. Prometheus tiene `PromQL` como lenguaje de consultas.
Grafana nos permite muchas alternativas para consultar los datos, así como para dar alertas. 
Las alertas que proporciona son muy variadas, pudiendo organizarse por niveles.

### PromQL
Debemos tratar de trabajar de forma basica con promQL. (en la doc: Prometheus server > Querys)

## Comenzando la práctica
En el guión hay un docker-compose y un prometheus.yml, con el protocolo de scrapping de Prometheus.

docker-compose:
volumes:
    Mandamos un directorio local `prometheus_data` contra uno interno: `prometheus`, como un mount para montar un directorio del host dentro del contenedor.
Cambiamos el puerto de grafana del 3000 al 4000 (la API de la escuela usa el 3000), aunque entre ellos seguirán comunicándose por el 3000.

En prometheus_data tendremos almacenada la BD y en grafana_data los distintos contenedores para mostrar información.


En localhost:9090 tenemos la interfaz gráfica de prometheus.

Para recargar el fichero de scrapper tenemos que recargar prometheus (matarlo y encenderlo). 
Además, en la pagina web: Status > Targets y tendremos que ver UP, lo que indica que prometheus está funcionando bine, lo que indica que prometheus está funcionando bien.

### Diferencias entre tipos de metricas de prometheus
Hay 4 tipos de métricas:
- Contadores (counter): valores acumulativos que siempre son crecientes.
- Gauge (aguja de sensor): puede crecer o decrecer.
- Histograma (para simplificar la representación de valores continuos): Los datos los calcula prometheus automáticamente. Hay buckets definidos por defecto.
    Típicas sobre el tiempo que tarda en responder un servidor HTTP.
    La forma que tienen los buckets es: (le/l/u/equal), es decir, para "le=0.1", es el nº de peticiones que han tardado menos o igual que 0.1 segundos.
    Puede haber buckets que incluyan a otros.
- Summary (no cae): Como un histograma pero los buckets son por percentiles. Son muy usados para ver latencias.

### Hacer gráfica
Graph
Buscar: cpu, sale: process_cpu_seconds_total > Ejecutar, nos da un valor instantáneo (en este caso, siempre incrementa por ser counter).
Nos interesa en este caso la pendiente de la gráfica, que nos da el uso/seg.

La función `rate` (ver doc) nos da esto:
Table > rate(proces_cpu_seconds_total{instance="prometheus:9090", job="prometheus_server"}[5m])      // cada 5min
Ahora la gráfica muestra el uso de cpu en cada segundo. Al multiplicar por 100 tenemos tanto por ciento.

### Llevarnos el gráfico a grafana
Recordamos que grafana está en el 4000: localhost:4000. Muestra la pagina de bienvenida por primera vez. Credenciales: admin, admin (luego meter passwd).

Lo primero: configurar prometheus como fuente de datos: Configuracion > Data sources > Add data source > Prometheus.
    Name: Prometheus
    url: url donde está prometheus (no es localhost, es desde dentro de compose), está en prometheus:9090. Compose resuelve el nombre de forma interna (por IP).
    Save&Test
    
Crear un dashboard: Dashboard > New 
Podemos meter paneles, filas, traer paneles de componentes (hay repositorios por ahí).

##### Para hacer uno desde 0 (lo normal es usar de otra gente):
Creamos un panel nuevo, salvamos dándole un nombre. Podemos meternos de nuevo para editar, hay muchas opciones.
Query:
- Data source: prometheus.
- Componer la query: podemos pegar la query que obtuvimos con prometheus en Code.
                     también podemos crearla desde 0 en Builder:
    - Métrica: process_cpu_seconds_total
    - Labels (se da cuenta de ciertas cosas y te dice k es intersante meter un rate).
    Debajo se va metiendo la consulta.

    $_\_rate_interval es una optimización pura de grafana, que permite variar el rate para la granularidad, aunque no siempre es bueno.
    Al cambiar rangos de visualización cambia la variable.

    - labels: instance, prometheus:9090
              job, prometheus_server

    Rate: operation > binaria > multiplicar por 100 (para ver el %)
              
Podemos dar a Run para ver cómo va quedando.


A la derecha:
- Podemos cambiar la forma de visualizar (otro tipo de gráfico). Hace sugerencias.
- Es interesante aclarar que el eje de ordenadas es un porcentaje (Unit).
- Podemos indicar valores mínimos y máximos. Si dejamos libre el max, hace zoom en el eje, a veces es mejor no fijar max y min.
- Thresholds: a partir de un valor, cambia de color.

### Alertas en grafana
Podemos crear alertas desde el panel, pero para series temporales (histogramas, para gauge no se puede).
Antes de nada, salvar el panel.
Alert > Crear alerta, y nos lleva al apartado: Alerting > Create rules.

Al ir desde el diálogo, nos ajusta algunas cosas. Por ejemplo, marca en el eje de abscisas los momentos importantes.
Como es una copia, si cambiamos el panel no se cambia la alerta, hay que cambiarla.

- Condiciones: cuando la ultima A esté por encima del 80.
- Se evaluará cada x min y se enviará a los x minutos (es capaz de detectar cuando se acerca a la alerta y después de x tiempo mantenido la lanza).
- A quién enviar la alerta con qué nombre.
- Folder: estructura donde Grafana estructura los contenidos. Grupo: grupo de usuarios con derecho a verlo.


La forma más interesante de ver las alertas es en el panel y ver el corazón.

## Ejercicio obligatorio
#### Monitorizar rocky linux
Monitorizar equipo linux (rocky). Para ello, hay que instalar el exporter de linux, que exporta para prometheus.
En las referencias [56] [57] encontramos cómo hacerlo. 
El exporter es un ejecutable. Al lanzarlo nos da las variables. 

Es necesario hacerlo un servicio (configurado como un servicio), [51], configurar exporter como servicio.
**La guía no tiene en cuenta**:
- El firewall: Hay que abrir el firewall para el 9100.
- La security extensión de linux (una opcion es deshabilitar, pero no le gusta): que permiten lanzar un proceso como servicio, para ello: 
                `restorecon -v /usr/local/bin/node_exporter`
    Y ya nos deja arrancarlo como un servicio.

Una vez hecho eso: ir al navegador en el host y hacer ip:9100/metrics, donde obtenemos las métricas del exporter.
La métrica de cpu node_cpu_seconds_total está dividida según las métricas de top, por lo que tenemos que juntarlas para sacar porcentaje.
Nos recomienda buscar métricas de grafana e inspirarnos.

Lo que tenemos que hacer es instalar en grafana un Dashboard predefinido (en [52] y [53], Grafana Labs), donde podemos buscar un dashboard
Para ello: copiamos la id, vamos a Grafana y: Dashboard > Import > pegamos IP y seguimos adelante. ELegir prometheus como datasource.
Podemos meternos en cosas, echar vistazos, eliminar cosas, ...

Leer las notas del dashboard, ya que en uno pide que el job del scrapper de prometheus (sobre docker) se llame node, por ejemplo. (recordad que si cambiamos fichero de conf hay que volver a arrancar prometheus).
Es importante que el node exporter se lance con unas opciones de configuración del dashboard:
    `collector.systemd` o `collector.processes` no está bien escrito y es necesario (necesitamos acceso a /proc)
    
    
Hay que hacer:
- Panel personalizado con uso de CPU en %. Configurarle una alarma que se dispare al 75% y siga por 5 min.
    Podemos usar `stress` para probarlo.

#### Monitorizar API Web
Para jugar con histogramas, hacerlo usando también jmeter.
API: localhost:3000
Los exporters de la API están en localhost:3000/metrics

Codigo 304: cuando un cliente pide el mismo contenido todo el rato (devuelve 304 en vez de devolver el contenido). 
No hacen falta referencias [54] y [55].

- Lanzar la API
- Crear dashboard
- Usar jmeter


**Peculiaridad**
Prometheus puede acceder al puerto ofertado en la VM por el bridge que se ofrece entre el compose y el host.
Sin embargo, prometheus no puede acceder al puerto del node.js del compose quen o es del compose del otro prometheus.

- Una forma **cutre** es acceder a través de la IP de la red a la que estamos conectados. NO.
- También podemos coger los contenedores node.js y mongodb dentro de los contenedores del otro compose, lanzando en un compose 5 contenedores, pero no.
- **La buena**: Utilizar una alias que da docker: host.docker.internal siempre es la tarjeta de red de mi pc.
    Esta variable se instala con docker-desktop.
    Sin embargo, si no lo tenemos, hay que lanzar docker con: 
    extra_hosts:
    - "host.docker.internal:host-gateway"

