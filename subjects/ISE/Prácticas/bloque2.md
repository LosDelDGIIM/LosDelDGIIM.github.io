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

## JWT Token
Es una cadena codificada en base 64 con 3 partes separadas por . : cabecera.payload/contenido.firma
JWT Debygger: Podemos ver cuándo fue emitido, cuándo expira
