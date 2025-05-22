# Bloque 2: Simulación de Carga de Trabajo y Monitorización

- **Autor**: Arturo Olivares Martos
- **Autor**: Miguel Ángel de la Vera


## Introducción
En este documento abordamos herramientas y técnicas para la monitorización de sistemas y la simulación de carga de trabajo en servidores. Utilizaremos tecnologías modernas como contenedores Docker, herramientas de benchmark, generadores de carga como JMeter, y soluciones de monitorización como Grafana y Prometheus. Esta infraestructura permite evaluar el rendimiento de los sistemas y asegurar su correcto funcionamiento bajo diferentes condiciones de uso.

## Contenedores
Los contenedores proporcionan una capa de abstracción sobre el sistema operativo, similar a una máquina virtual pero más ligera y eficiente. A diferencia de los hipervisores, esta tecnología permite ejecutar múltiples aplicaciones encapsuladas, compartiendo el kernel del host.
Los contenedores han facilitado la adopción de arquitecturas de microservicios, donde cada servicio corre de forma independiente y se comunica con otros mediante APIs o colas de mensajes.

Sus principales ventajas son:
- **Prestaciones**: Puesto que no hay virtualización, no hay pérdida ninguna de rendimiento.
- **Portabilidad**: Debido al encapsulamiento de la aplicación y sus dependencias, los contenedores pueden ejecutarse en cualquier entorno compatible. Facilita por tanto la migración entre entornos de desarrollo, pruebas y producción. Es, sobretodo, una tecnología de distribución del software.
- **Seguridad**: Se crea un filesystem aislado para cada contenedor, lo que mejora la seguridad al evitar que una aplicación afecte a otras. De hecho, es un `sandbox` que permite ejecutar aplicaciones de forma aislada, evitando conflictos entre ellas.
- **Espacio de Procesos Propio**: Cada contenedor tiene su propio espacio de procesos, lo que evita conflictos entre aplicaciones. De hecho, si desde un mismo contenedor ejecutamos `ps -ax`, veremos que solo aparecen los procesos de ese contenedor, no los del host.


Como contrapartida, hemos de mencionar que se crea una "red virtual" entre las distintas aplicaciones de un contenedor para poder comunicarse entre ellas, por lo que en este aspecto sí hay una ligera pérdida de rendimiento. Por otro lado, las dependencias de cada contenedor son independientes, lo que puede llevar a un aumento del uso de espacio en disco si no se gestionan adecuadamente, puesto que pueden existir dependencias duplicadas en diferentes contenedores.

Hay varias tecnologías de contenedores, pero la más popular es **Docker**, y es la que estudiaremos en este bloque. No obstante, cabe mencionar alternativas a Docker como *Podman*, que destaca por tener una sintaxis muy similar pero no requiere un *daemon* para su ejecución, lo que lo hace más seguro y ligero.

Otra herramienta que usaremos más adelante es *Docker Compose*, que sirve para definir y ejecutar aplicaciones multi-contenedor. Con un solo comando, podemos crear y ejecutar todos los contenedores necesarios para una aplicación, facilitando la gestión de entornos complejos.

### Instalación de Docker
Para instalar **Docker**, podemos optar por la instalación en la MV o en el host, aunque la instalación en el host es suficiente para la práctica. Para instalarlo, podemos seguir [la guía oficial de Docker](https://docs.docker.com/engine/install/). Sin embargo, se muestran algunos comandos para distribuciones comunes.
#### Debian 
```shell
$ sudo apt-get update
$ sudo apt-get install ca-certificates curl
$ sudo install -m 0755 -d /etc/apt/keyrings
$ sudo curl -fsSL https://download.docker.com/linux/debian/gpg -o /etc/apt/keyrings/docker.asc
$ sudo chmod a+r /etc/apt/keyrings/docker.asc
```

```shell
$ echo \
  "deb [arch=$(dpkg --print-architecture) signed-by=/etc/apt/keyrings/docker.asc] https://download.docker.com/linux/debian \
  $(. /etc/os-release && echo "$VERSION_CODENAME") stable" | \
  sudo tee /etc/apt/sources.list.d/docker.list > /dev/null
sudo apt-get update
```

Y ahora ya podemos instalar docker junto con algunos plugins adicionales que usaremos:
```shell
$ sudo apt-get install docker-ce docker-ce-cli containerd.io docker-buildx-plugin docker-compose-plugin
$ wget https://desktop.docker.com/linux/main/amd64/docker-desktop-amd64.deb?utm_source=docker&utm_medium=webreferral&utm_campaign=docs-driven-download-linux-amd64
$ sudo apt-get update
$ sudo apt-get install ./docker-desktop-amd64.deb

```

#### Arch (By The Way)
```shell
$ sudo pacman -S docker docker-compose
```

### Trabajando con Docker

Comenzamos con algunos comandos básicos para trabajar con Docker. Cabe destacar que tan solo pueden ejecutar comandos de Docker los usuarios que pertenezcan al grupo `docker` o que tengan permisos de superusuario. Para añadir un usuario al grupo `docker`, podemos usar el siguiente comando:
```shell
$ sudo usermod -aG docker <usuario>
```
En caso contrario, deberemos usar `sudo` para ejecutar los comandos de Docker.


En primer lugar, hay que distinguir entre imágenes y contenedores.
- **Imágenes**: Son plantillas de solo lectura que contienen el código y las dependencias necesarias para ejecutar una aplicación. Se pueden considerar como un "snapshot" del sistema de archivos.
- **Contenedores**: Son instancias en ejecución de imágenes. Cada contenedor tiene su propio sistema de archivos, red y espacio de procesos, pero comparte el kernel del host.

Los comandos básicos para trabajar con las imágenes de Docker son:
```shell
$ docker pull <imagen>        # Descargar una imagen desde Docker Hub
$ docker image ls             # Listar imágenes descargadas
$ docker image rm <imagen>    # Eliminar una imagen del sistema
```

Para trabajar con contenedores, los comandos son:
```shell
$ docker container ls -la     # Listar todos los contenedores (en ejecución y detenidos)
$ docker run <imagen>         # Crear y ejecutar un nuevo contenedor
$ docker run -it <img> sh     # Ejecutar un contenedor con terminal interactivo
$ docker stop <nombre>        # Detener un contenedor en ejecución
$ docker container rm <nombre>  # Eliminar un contenedor detenido
```

Cabe destacar que el comando `docker run` crea y ejecuta un nuevo contenedor a partir de una imagen. Si la imagen no está disponible localmente, Docker la descargará automáticamente.

Notemos que, tras detener la ejecución de un contenedor, este sigue existiendo en el sistema, por lo que si queremos eliminarlo, deberemos usar el comando para eliminarlo visto. No obstante, si queremos eliminarlo al finalizar la ejecución, podemos usar el flag `--rm` al ejecutar el contenedor. Por ejemplo:
```shell
$ docker run --rm <imagen>      # Ejecutar y eliminar el contenedor al finalizar
```
Aun así, si queremos eliminar todos los contenedores detenidos, podemos usar el siguiente comando:
```shell
$ docker container prune
```

Para comprobar que Docker está instalado y funcionando correctamente, podemos comprar su estado como servicio:
```shell
$ systemctl status docker
```

Cuando hablamos de descargar imágenes, estas se descargan de [Docker Hub](https://hub.docker.com/), que es el repositorio oficial de imágenes de Docker. Muchas aplicaciones populares (como `ubuntu`, `nginx`, `mysql`) tienen imágenes oficiales mantenidas por Docker o sus creadores.

Para ilustrar su fácil uso, y especialmente comprobar que toda la instalación ha sido correcta, vamos a ejecutar el primer contener. Este será el contenedor [hello-world](https://hub.docker.com/_/hello-world), que es una imagen de prueba que simplemente imprime un mensaje en la consola. Para ello, ejecutamos el siguiente comando:
```shell
$ docker run hello-world
```
Como vemos, este se descarga automáticamente y se ejecuta, mostrando un mensaje de bienvenida.

Hacemos referencia ahora brevemente a distintos términos:
1. **Dockerfile**: Es un archivo de texto que contiene instrucciones para construir una imagen de Docker. Define cómo se debe configurar el contenedor, qué software instalar, etc. Se puede considerar como un script de construcción de la imagen. Aunque en la asignatura no se nos pide saber construirlos, veamos un ejemplo:
    ```
    FROM mongo:6
    COPY ./scripts/* /tmp/
    RUN chmod 755 /tmp/initializeMongoDB.sh
    WORKDIR /tmp
    CMD ./initializeMongoDB.sh
    ```
    - Se está especificando que se use la versión 6 de la imagen de `mongo`. Además, se ejecutan ciertos comandos para el correcto funcionamiento del contenedor. Se emplea además el sistema de archivos propio, como vemos en `/tmp/`.

    Otro ejemplo relevante es el siguiente:
    ```
    FROM node:16.13.0-stretch
    RUN mkdir -p /usr/src/app
    COPY . /usr/src/app
    EXPOSE 3000
    WORKDIR /usr/src/app
    RUN ["npm", "install"]
    ENV NODE_ENV=production
    CMD ["npm","start"]
    ```
    - Este ejemplo cabe destacarlo, puesto que se emplea la opción `EXPOSE`, que indica el puerto que se va a exponer al exterior. En este caso, el puerto 3000. Esto es importante, ya que si no se expone el puerto, no podremos acceder al contenedor desde el exterior de este.



<!-- TODO: Dockerfile 
https://chatgpt.com/share/682e5f7a-7b08-8010-a721-22aa50685d96
Lo de ADE
-->


## Benchmarking
El benchmarking es una técnica fundamental para evaluar el rendimiento de sistemas y servicios. Permite comparar distintas configuraciones, detectar cuellos de botella y validar mejoras de rendimiento. En este bloque se explorarán tanto herramientas de propósito general como específicas para servidores web.

### OpenBenchmarking
*OpenBenchmarking* es el proyecto más significativo en el ámbito de benchmarking de código abierto. Se trata de un repositorio en el que se pueden encontrar una amplia variedad de benchmarks para evaluar el rendimiento de sistemas y aplicaciones.

*Phoronix Test Suite* es la plataforma de *OpenBenchmarking* que permite ejecutar benchmarks en una amplia variedad de sistemas y configuraciones. Notemos no obstante que no está muy mantenida. Aunque se puede instalar tanto en el host como en una MV, recomendamos instalarlo mediante contenedores Docker empleando la [imagen oficial de Phoronix](https://hub.docker.com/r/phoronix/test-suite). Notemos además que buscamos una interfaz interactiva:
```shell
docker run -it phoronix/pts
```

Una vez ejecutándose el contenedor, podemos ejecutar los dos siguientes comandos:
- `system-info`: Muestra información detallada sobre el sistema, incluyendo CPU, memoria, disco y red. Notemos que, aun estando en un contenedor, como no hay virtualización, podemos ver la información del host.
- `system-sensors`: Muestra información sobre los sensores del sistema, como temperatura, voltaje y velocidad de los ventiladores. Esto es útil para monitorear el estado del hardware.


Phoronix distingue entre:
- **Tests**: Son los benchmarks individuales que se pueden ejecutar. Cada test tiene su propio conjunto de parámetros y configuraciones.
- **Suites**: Son colecciones de tests que se pueden ejecutar juntos. Permiten evaluar el rendimiento de un sistema en diferentes áreas (CPU, memoria, disco, etc.). Por ejemplo, puede haber una `suite` de ofimática que emplee test de acceso a disco, RAM, etc.

Para ver todos los tests o suites disponibles, podemos usar el siguiente comando:
```shell
$ phoronix-test-suite list-available-tests      # Listar todos los tests disponibles
$ phoronix-test-suite list-available-suites     # Listar todas las suites disponibles
```

Para ver información de un test o suite en concreto (como son sus dependencias), podemos usar el siguiente comando:
```shell
$ phoronix-test-suite info <test/suite>
```

Para ejecutar un test o suite, podemos usar el siguiente comando:
```shell
$ phoronix-test-suite install <test/suite>
$ phoronix-test-suite run <test/suite>
$ phoronix-test-suite benchmark <test/suite>  # Equivalente al anterior
```
Notemos que si se usa sin instalar, se descargará automáticamente. Para que los datos se guarden y se puedan comparar con otros resultados, hay dos opciones:
- `--save-results`: Esta opción añadida al parámetro `run` permite guardar los resultados de la prueba en un archivo específico.
- En la ejecución, se pedirá el nombre del fichero en el que se van a guardar los resultados.

Para ver los resultados guardados, podemos usar los siguientes comandos:
```shell
$ phoronix-test-suite list-saved-results  # Listar el nombre de todos los resultados guardados
$ phoronix-test-suite show-result <fichero_resultados>                      # Ver resultados de un test específico
```

Comprobémoslo con un ejemplo (aunque evidentemente tardará). Para evitar tener que instalarlos dependencias, emplearemos la imagen de Docker de [gZip](https://openbenchmarking.org/test/pts/compress-gzip) que contiene la herramienta de compresión `gzip`. Para ello, ejecutamos el siguiente comando:
```shell
$ phoronix-test-suite run compress-gzip
```

### Apache Benchmark
Dentro de los benchmarks para servidores web, hay varias harramientas que destacan. En este caso nos centraremos en *Apache Benchmark*, benchmark de la empresa Apache pero que está destinado a estudiar cualquier sevidor web (Apache, Nginx, etc.). Se emplea como sigue:
```shell
$ ab -n <num_requests> -c <num_concurrent_requests> <url>
```
Donde:
- `num_requests`: Número total de peticiones a enviar al servidor.
- `num_concurrent_requests`: Número de peticiones concurrentes a enviar al servidor.

Evidentemente, no tiene sentido aplicar el benchmark desde el mismo servidor, puesto que el resultado se va a ver afectado por la carga que el propio servidor genera. Por tanto, es recomendable usar una máquina diferente para realizar el benchmark.

<!--
Las opciones mas comunes que usaremos son:
- *-n*: El número de peticiones a enviar
- *-t*: La duración (en segundos) del benchmark
- *-c*: El número de peticiones concurrentes a realizar. 
Si usamos -t y -n, deberemos poner primero -t ya que de lo contrario, ApacheBench lo va a ignorar, dejando por defecto 50000.
El comando *ab* se ejecuta en un solo hilo, el flag -c indica cuantos fd se van a reservar para la ejecución, no cuantas peticiones HTTP se van a mandar simultáneamente.
-->

#### Ejemplo Práctico

Veamos ahora un ejemplo práctico de benchmarking con Apache Benchmark, junto con la herramienta `curl`, que nos permite realizar peticiones HTTP y ver la respuesta del servidor.
```shell
$ curl -v <url>   # -v: verbose, también las cabeceras
```

Buscamos aplicar el benchmarl en la web de la [Universidad de Granada](https://www.ugr.es/). Para ello, ejecutamos el siguiente comando:
```shell
$ ab -n 5000 -c 10 http://www.ugr.es/
```

Como podemos ver, el servidor está implementadocon `nginx`. No obstante, nos extraña que la longitud de la respuesta es de tan solo 162 bytes. Para comprobar qué ocurre, empleamos `curl` para ver la respuesta del servidor:
```shell
$ curl -v http://www.ugr.es/
* Host www.ugr.es:80 was resolved.
* IPv6: (none)
* IPv4: 150.214.27.71
*   Trying 150.214.27.71:80...
* Connected to www.ugr.es (150.214.27.71) port 80
> GET / HTTP/1.1
> Host: www.ugr.es
> User-Agent: curl/8.5.0
> Accept: */*
> 
< HTTP/1.1 301 Moved Permanently
< Server: nginx
< Date: Thu, 22 May 2025 00:43:17 GMT
< Content-Type: text/html
< Content-Length: 162
< Connection: keep-alive
< Location: https://www.ugr.es/
< 
# ....
```

Como vemos, el servidor responde con un `301 Moved Permanently`, lo que indica que la página ha sido movida permanentemente a otra URL. En este caso, la nueva URL es `https://www.ugr.es/`. Como vemos, esto es una *limitación* de Apache Benchmark, que no sigue redirecciones. Para comprobar que, efectivamente, la página ha sido movida, podemos usar `curl` con el flag `-L`, que sigue las redirecciones:
```shell
$ curl -vL http://www.ugr.es/
```

En este caso, la respuesta es mucho más larga, por lo que procedemos a aplicar el benchmark de nuevo:
```shell
$ ab -n 5000 -c 10 https://www.ugr.es/
# ...
Server Software:        nginx
Server Hostname:        www.ugr.es
Server Port:            443
SSL/TLS Protocol:       TLSv1.2,ECDHE-RSA-AES128-GCM-SHA256,2048,128
Server Temp Key:        ECDH P-384 384 bits
TLS Server Name:        www.ugr.es

Document Path:          /
Document Length:        111344 bytes

Concurrency Level:      10
Time taken for tests:   201.923 seconds
Complete requests:      5000
Failed requests:        0
Total transferred:      560673874 bytes
HTML transferred:       556720000 bytes
Requests per second:    24.76 [#/sec] (mean)
Time per request:       403.845 [ms] (mean)
Time per request:       40.385 [ms] (mean, across all concurrent requests)
Transfer rate:          2711.60 [Kbytes/sec] received

Connection Times (ms)
              min  mean[+/-sd] median   max
Connect:      102  138  37.4    132    1174
Processing:   126  265  67.9    275    1145
Waiting:       60   84  34.0     74     944
Total:        238  403  75.2    408    1495

Percentage of the requests served within a certain time (ms)
  50%    408
  66%    425
  75%    437
  80%    442
  90%    457
  95%    477
  98%    514
  99%    639
 100%   1495 (longest request)
```

Además de las métricas de fácil interpretación, hemos de resaltar los Tiempos de Conexión:
- **Connect**: Tiempo que tarda en establecer la conexión con el servidor.
- **Processing**: Tiempo que tarda el servidor en procesar la petición y enviar la respuesta completa.
- **Waiting**: Tiempo que transcurre desde que se envía la petición hasta que se recibe la primera respuesta del servidor. Este tiempo es importante porque puede indicar si el servidor está saturado o si hay problemas de red.

Es normal que la suma de los tiempos no sea igual al tiempo total, ya que se consideran los valores mínimos, máximos. En los valores medios no obstante sí se mantiene la relación.

También es de notar por qué hay dos tipos de *Time per request*:
- El menor especifica *across all concurrent requests*, es decir, el tiempo medio de cada petición teniendo en cuenta todas las peticiones concurrentes. Es menor porque hay peticiones ejecutándose al mismo tiempo.
- El mayor especifica *mean* a secas, es decir, el tiempo medio de cada petición sin tener en cuenta la concurrencia. Este tiempo es mayor porque no se están ejecutando varias peticiones al mismo tiempo, por lo que el tiempo es mayor que el real.


Como vemos, esta es una herramienta útil por su sencillez, pero nos impide hacer estudios más en profundidad. Se usa para lo que se conoce como *smoketest* (prueba de humo), que es una prueba rápida para comprobar que el sistema funciona correctamente. Sin embargo, no es suficiente para hacer un análisis exhaustivo del rendimiento de un sistema. Ahí es donde entran en juego otras herramientas más avanzadas como JMeter, que nos permiten hacer pruebas más complejas y detalladas.

## Simulación de Carga: Jmeter
Aunque Apache Benchmark tiene muchas posibilidades y es una herramienta poderosa y correcta, existen otras herramientas que permiten hacer tests más complejos. Nosotros estudiaremos JMeter, que es una de las más populares y completas. Aunque es ciertamente antigua, sigue siendo una de las más utilizadas en la industria. Está está diseñado para cargar funcionalidades de benchmark y medir rendimiento, especialmente en servidores web.

Una de las características interesantes de Jmeter es su manejo de la distribución de la carga:
- Puede crear concurrencia real gracias a la posibilidad de crear varias hebras dentro de la misma CPU.
- También puede distribuir el esfuerzo de carga entre varios equipos en red local.
- Existen otros proveedores de servicios de carga en la nube, como *Flood*, que permiten distribuir el esfuerzo de carga entre varios equipos en la nube, de forma global.

Como veremos, una de las principales ventajas de JMeter, que le distingue de Apache Benchark, es que se puede configurar como proxy de un servidor a JMeter, registrando la navegación de los usuarios. De esta forma, podremos replicar situaciones exactas de carga en el servidor, lo que es muy útil para hacer pruebas de rendimiento.
- Por ejemplo, si el servidor ha estado especialmente recargado en cierto momento y se ha caído, podemos realizar pequeños ajustes y comprobar si, con la misma carga, el servidor aguantará.

Los test en JMeter se diseñan y se configuran mediante la interfaz gráfica, y esto también nos permite ejecutarlos con fines de depuración; pero no es recomendable usar la interfaz gráfica para ejecutar los tests en producción, ya que esta consume muchos recursos y los resultados se verían alterados.

Para ejecutar los tests en producción mediante la línea de comandos, se emplea:
```shell
$ jmeter -n -t <jmx file>.jmx -l <results file> -e -o <Path to web report folder>
```
donde:
- `-n`: Indica que se va a ejecutar en modo no gráfico.
- `-t`: Indica el archivo de configuración del test. Este es el que habremos creado previamente con la interfaz gráfica. Tendrá extensión `.jmx`.
- `-l`: Indica el archivo donde se van a guardar los resultados del test. Este archivo tendrá extensión `.jtl`, aunque también puede ser `.csv` o `.xml`.
- `-e`: Indica que se va a generar un informe HTML al finalizar el test. Esto es opcional.
- `-o`: Indica la ruta donde se va a guardar el informe HTML. Este informe se generará al finalizar el test y contendrá información detallada sobre los resultados del test. Esta carpeta ha de estar vacía, o bien no existir, para que el comando no falle.

Una vez ejecutado, los resultados se pueden ver desde la interfaz gráfica de JMeter, o bien desde el informe HTML generado. Este informe contiene gráficos y tablas con información detallada sobre los resultados del test, lo que facilita la interpretación de los resultados.


### Ejemplo Práctico

JMeter tiene infinidad de opciones, y sería imposible explicarlas todas. Es por ello que veremos un ejemplo práctico, en el que explicaremos en detalle cada aspecto.

Para este ejemplo, emplearemos una web disponible gracias en el siguiente repositorio.
```shell
$ git clone https://github.com/davidPalomar-ugr/iseP4JMeter
```
Una vez clonado, podemos acceder a el, veremos que nos encontramos con un docker-compose.yaml, haciendo simplemente: 
```shell
docker compose up
```
Podremos ejecutarlo y lo detendremos mediante down. Para ver la API podemos conectarnos a localhost en el puerto 3000. En esta página encontraremos una descripción básica de la API, concretamente dos métodos que usaremos:

- /auth/login: Un método POST que nos permite autenticar un usuario, devolviendo un token de acceso JWT. La autenticación se realiza mediante un email y una contraseña.
El acceso a este servicio está protegido por HTTP Basic Auth, por lo que deberemos enviar las credenciales en la cabecera de la petición.

- /alumnos/alumno/\<email\>: Un método GET que nos permite obtener información sobre un alumno en particular. Este método requiere un token de acceso JWT que se obtiene al autenticar al usuario mediante el método anterior. El token portará la identidad y rol del usuario. El rol alumno solo puede solicitar sus datos mediante que un administrador puede solicitar los datos de cualquier alumno. Retorna un objeto JSON.

Una vez levantado el servidor, podemos comprobar que funciona ejecutando pruebaEntorno.sh, que nos debería devolver la información en formato JSON de un alumno junto con comentarios de relleno estilo Lorem. Para ejecutarlo deberemos tener instalado curl. Además es recomendable copiar la salida a algún interprete de JSON para ver la salida de forma más legible.

## Ejercicio
El subdirectorio del repositorio jMeter contiene los ficheros necesarios para la realización del ejercicio:

- alumnos.csv: Archivo con credenciales de alumnos
- administradores.csv: Archivo con credenciales de administradores
- apiAlumno.log: Log de accesso Http en formato apache.

Para la realización de la prueba, crearemos un fichero .jmx, lo más cómodo es crearlo desde la aplicación de jMeter, el contenido del test será el siguiente:

- **User Defined Variables** (Add > Config Element > User defined variables):
  - Name: IP, Value: localhost (o la IP del servidor)
  - Name: PUERTO, Value: 3000

- **Access to ETSII API** (Add > Config Element > HTTP Request Defaults) :
  - Server Name: `${IP}`
  - Port Number: `${PUERTO}`
  - Protocol: `http`
  - Path: *(vacío)*

- **Basic Auth API** (Add > Config Element > HTTP Authorization Manager):
  - Base URL: `http://${IP}:${PUERTO}/api/v1/auth/login`
  - Username: `etsiiApi`
  - Password: `laApiDeLaETSIIDaLache`
  - Mechanism: `BASIC`

Ahora crearemos el Thread Group. Para este ejercicio crearemos uno para los usuarios y otro para los administradores. En JMeter, un Thread Group simula múltiples usuarios que ejecutan acciones simultáneamente contra tu servidor o API. Dentro de un thread group encontramos las siguientes definiciones fundamentales.

- Number of threads (users):Número de usuarios virtuales (hilos) que simulan peticiones concurrentes.

- Ramp-up period (seconds): Tiempo total en segundos que JMeter tarda en lanzar todos los usuarios. Si tienes 50 hilos y pones 25, lanzará 2 usuarios cada segundo.

- Loop Count: Número de veces que cada hilo ejecutará el conjunto de acciones del test. Si pones 5, cada uno de los 50 usuarios hará 5 ciclos de prueba.

Warm-up: El ramp-up simula un arranque progresivo, evitando una avalancha de tráfico al servidor. Esto es realista y reduce errores como saturaciones iniciales.

Cooldown: Aunque JMeter no lo implementa directamente, puedes finalizar grupos de hilos progresivamente o añadir retardos entre grupos para simularlo.

Para crearlo vamos a Add > Threads (Users) > Thread Group, podemos ponerle nombre Alumnos, en cuanto a los campos, por ejemplo poner 50, 25 y 5. Estos son los explicados anteriormente.
Ahora dentro de Alumnos vamos a configurar todo lo siguiente:

- **Credenciales Alumnos** (Add > Config Element > CSV Dataset):
    - Filename: `./jMeter/alumnos.csv`
    - File encoding: `UTF-8`
    - Variable Names: `login,password`
    - Ignore first line: `True`
    - Delimiter: `,`
    - Allow quoted data?: `False`
    - Recycle on EOF: `True`
    - Stop Thread on EOF: `False`
    - Sharing Mode: `Current thread group`

- **Login Alumno** (Add > Sampler > HTTP Request)
    - Name: `Login Alumno`
    - Method: `POST`
    - Path: `/api/v1/auth/login`
    - Parámetros:
    - Name: `login`, Value: `${login}`
    - Name: `password`, Value: `${password}`

Ahora en Login alumno:
- **JWT Token** (Add > Post > Regular Expression Extractor)
    - Podemos llamar a la variable como queramos pero debemos recordar el nombre para usarlo a la hora de recuperar datos, de aqui en adelante nos referiremos a esta variable como   
    ${token}.
    - Regular Expression: `.+`
    - Template: `$0$`

Añadimos además un temporizador mediante Add > Timer > Gaussian Random Timer.

- **Recuperar Datos Alumno** (Add > Sampler > HTTP Request)
    - Method: `GET`
    - Path: `/api/v1/alumnos/alumno/${login}`
    Add > Config Element > HTTP Header Manager:
    - Name: `Authorization`, Value: `Bearer ${token}`

Para los administradores, copia el grupo anterior y modifica lo siguiente:

- CSV Dataset:
  - Filename: `./jMeter/administradores.csv`

- Recuperar datos:
  - Sustituye por Add > Sampler > **Access Log Sampler**
    - Name: `Accesos Administradores`
    - Protocol: `http`
    - Server: `${IP}`
    - Port: `${PUERTO}`
    - Log file location: `./jMeter/apiAlumno.log`

Ahora añadimos a ETSII Alumnos API los siguientes Listener
Add > Listener > Summary Report
Add > Listener > View Results in Table
Add > Listener > Aggregate Report

Ahora podemos ejecutar con el run de la interfaz gráfica, sin embargo, para aplicaciones que vayamos a lanzar a producción, y, para la resolución de este ejercicio, ejecutamos sin modo gráfico:
```shell
jmeter -n -t ./archivo.jmx -l results.jtl
```

Donde -n significa que no se abre el modo gráfico, -t es el archivo a ejecutar con la configuración y -l se utiliza para saber en que fichero guardar los resultados.

# Monitorización
La monitorización es una parte esencial en la administración de sistemas.

## Herramientas de monitorización

### `top`
- Herramienta clásica, disponible en casi todos los sistemas Linux.
- Muestra en tiempo real:
  - Carga del sistema (`load average`)
  - Uso de CPU y memoria
  - Procesos en ejecución
- Funciona en terminales sin entorno gráfico.
- Usa información del sistema de archivos `/proc`.

### `htop`
- Versión mejorada de `top`:
  - Interfaz interactiva y más visual.
  - Permite ordenar procesos con teclas, matar procesos fácilmente.
  - Muestra uso de CPU por core y RAM con barras gráficas.

### `btop`
- Evolución moderna con mejor UI:
  - Interfaz basada en ncurses (colores, gráficos animados).
  - Muestra carga, memoria, procesos, red y disco.
  - Uso muy intuitivo.
  - Ideal para visualización avanzada en terminales modernos.

## Fuente de datos: `/proc`
- `/proc/loadavg`: carga media del sistema.
- `/proc/meminfo`: uso de memoria.
- `/proc/uptime`: tiempo activo del sistema.
- `/proc/cpuinfo`: info del procesador.
- `/proc/[PID]/`: info específica de cada proceso.

Además de las herramientas ya mencionadas, tenemos comandos como `uptime`, `free` o `vmstat` que acceden a las mismas fuentes de información pero son más adecuados para extraer información específica o para scripts.

## Ejercicio Opcional

Stress es una herramienta de carga que permite estresar el sistema, generando carga en CPU, memoria, disco y red. Permite simular condiciones extremas para evaluar la estabilidad y rendimiento del sistema. Se recomienda la herramienta `stress-ng`, que es una versión mejorada de `stress` y ofrece más opciones y configuraciones.

Las opciones más comunes son:
- --cpu N: Estresa N núcleos de CPU.
- --all 0: Estreza todos los subsistemas (No recomendado probar)
- --cpu-load N: Estresa la CPU al N% de carga (Aproximadamente).
- --timeout Ns: Ejecuta el estrés durante N segundos.

Para resolver el ejercicio, bastará con ejecutar el comando con las flags que veamos oportunas mientras monitoreamos el sistema con las herramientas anteriormente descritas.

## Programacion tareas
En el ambito de la adminitración de servidores es muy común la ejecución de tareas periódicas de mantenimiento. Para automatizar este fin, existen varias herramientas muy útiles, nos centraremos en cron, que es la clásica y más extendida solución, sin embargo, se recomienda leer sobre systemd timers, que para sistemas basados en systemd proporcionan una manera más adecuada, sencilla y eficiente de ejecutar estas tareas.

## ¿Cómo funciona `cron`?

`cron` ejecuta tareas en segundo plano definidas por el usuario mediante un archivo especial llamado *crontab* (tabla de cron). Cada usuario puede tener su propia tabla de tareas.

Para editarla:

```shell
crontab -e
```

Este comando abre el archivo de configuración asociado al usuario actual. Las tareas se escriben en líneas con el siguiente formato:

* * * * * comando
│ │ │ │ │
│ │ │ │ └── Día de la semana (0-7) (domingo es 0 o 7)
│ │ │ └──── Mes (1-12)
│ │ └────── Día del mes (1-31)
│ └──────── Hora (0-23)
└────────── Minuto (0-59)

## Comandos útiles

- Ver tareas programadas: crontab -l
- Borrar tareas: crontab -r
- Editar tareas: crontab -e
- Ver logs del sistema: journalctl, dmesg, o /var/log/syslog (depende del sistema)

## Ejercicio opcional

Queremos que ejecute un comando para el log del sistema con las características dadas, para ello, podemos usar el siguiente comando, que deberemos insertar en el crontab con la frecuencia deseada:
```shell
echo "[INICIALES] $(date '+%d-%m-%Y %H:%M:%S') – CPU: $(top -bn1 | grep 'Cpu(s)' | awk '{print 100 - $8}')%" | logger -t ISE
```
En este caso se imprime el % de CPU en uso, podríamos haber definido cualquier otra forma para representar la carga y sería valido. Por ejemplo en top tambien hay un parámetro de carga media.
Para poner la frecuencia editamos con crontab -e y añadimos la linea anterior junto con la frecuencia deseada, por ejemplo:
```shell
0 4 8-14 * * echo "[INICIALES] $(date '+%d-%m-%Y %H:%M:%S') – CPU: $(top -bn1 | grep 'Cpu(s)' | awk '{print 100 - $8}')%" | logger -t ISE
```
Que ejecutaría a las 4:00 cada dia del mes comprendido entre 8 y 14. Para obtener los tiempos de forma más sencilla, se recomienda la pagina crontab.guru.

## Logs
Una forma sencilla de monitorización es ver los logs del sistema, se almacenan en /var/logs/ que contiene tanto logs del sistema linux como de servicios instalados. En ocasiones el formato es texto plano y podemos consultarlos con herramientas del estilo de `cat`. En otras ocasiones necesitaremos comandos específicos para consultarlos, por ejemplo `last` y `who` permiten consultar los accesos registrados en el archivo binario btmp,wtmp.

## Journalctl
En sistemas modernos basados en systemd, todos los eventos del sistema y de los servicios se registran en el journal. El servicio encargado de esta tarea es `systemd-journald`.

Por defecto, el journal es volátil, lo que significa que los logs se almacenan en memoria y se pierden tras un reinicio. Para habilitar persistencia:
```shell
sudo mkdir -p /var/log/journal
sudo systemctl restart systemd-journald
```
También puede ajustarse la opción `Storage=persistent` en el archivo de configuración /etc/systemd/journald.conf.
Para consultar los registros del sistema se utiliza:
```shell
journalctl
```
Opciones comunes:

- -b: muestra los logs desde el último arranque.
- -p: filtra por prioridad (emerg, alert, crit, err, warning, etc.).
- -u nombre_servicio: filtra por unidad de systemd.
## Ejercicio Opcional: Logs del arranque

Queremos ver los logs del último arranque con nivel de severidad warning o superior (advertencias, errores, fallos críticos).
```shell
journalctl -b -p warning
```
