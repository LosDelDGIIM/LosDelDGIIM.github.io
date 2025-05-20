# Introducción
En este documento abordamos herramientas y técnicas para la monitorización de sistemas y la simulación de carga de trabajo en servidores. Utilizaremos tecnologías modernas como contenedores Docker, herramientas de benchmark, generadores de carga como JMeter, y soluciones de monitorización como Grafana y Prometheus. Esta infraestructura permite evaluar el rendimiento de los sistemas y asegurar su correcto funcionamiento bajo diferentes condiciones de uso.

# Contenedores Docker
Los contenedores proporcionan una capa de abstracción sobre el sistema operativo, similar a una máquina virtual pero más ligera y eficiente. A diferencia de los hipervisores, Docker permite ejecutar múltiples aplicaciones encapsuladas, compartiendo el kernel del host.
Los contenedores han facilitado la adopción de arquitecturas de microservicios, donde cada servicio corre de forma independiente y se comunica con otros mediante APIs o colas de mensajes.
Cabe mencionar alternativas a Docker como Podman, que destaca por tener una sintaxis muy similar pero no requiere un daemon para su ejecución, lo que lo hace más seguro y ligero.

Otra herramienta que usaremos más adelante es Docker Compose, que sirve para definir y ejecutar aplicaciones multi-contenedor. Con un solo comando, podemos crear y ejecutar todos los contenedores necesarios para una aplicación, facilitando la gestión de entornos complejos.

## Instalación de Docker
Para instalar docker, podemos optar por la instalación en la MV o en el host. Para instalarlo en el Host, podemos seguir la guia de instalación oficial de Docker. Sin embargo, se muestran algunos comandos para distribuciones comunes.
### Debian 
```bash
sudo apt-get update
sudo apt-get install ca-certificates curl
sudo install -m 0755 -d /etc/apt/keyrings
sudo curl -fsSL https://download.docker.com/linux/debian/gpg -o /etc/apt/keyrings/docker.asc
sudo chmod a+r /etc/apt/keyrings/docker.asc
```

```bash
echo \
  "deb [arch=$(dpkg --print-architecture) signed-by=/etc/apt/keyrings/docker.asc] https://download.docker.com/linux/debian \
  $(. /etc/os-release && echo "$VERSION_CODENAME") stable" | \
  sudo tee /etc/apt/sources.list.d/docker.list > /dev/null
sudo apt-get update
```

Y ahora ya podemos instalar docker junto con algunos plugins adicionales que usaremos:
```bash
sudo apt-get install docker-ce docker-ce-cli containerd.io docker-buildx-plugin docker-compose-plugin
wget https://desktop.docker.com/linux/main/amd64/docker-desktop-amd64.deb?utm_source=docker&utm_medium=webreferral&utm_campaign=docs-driven-download-linux-amd64
sudo apt-get update
sudo apt-get install ./docker-desktop-amd64.deb

```

### Arch (By The Way)
```bash
sudo pacman -S docker docker-compose
```

## Comandos esenciales de Docker
```bash
# Imágenes
docker pull <imagen>        # Descargar una imagen desde Docker Hub
docker image ls             # Listar imágenes descargadas
docker image rm <imagen>    # Eliminar una imagen del sistema

# Contenedores
docker run <imagen>         # Crear y ejecutar un nuevo contenedor
docker run -it <img> sh     # Ejecutar un contenedor con terminal interactivo
docker container ls         # Ver contenedores en ejecución
```

## Ejercicio Evaluable (Hello World)
Para este ejercicio, bastará con descargar la imagen de hello-world y ejecutarla. Si los pasos anteriores están bien realizados, bastará con ejecutar los siguientes comandos:
```bash
sudo systemctl start docker
sudo usermod -aG docker $USER
sudo reboot
```
Ahora una vez aplicados los cambios:
```bash
docker pull hello-world
docker run hello-world
```

# Benchmarking
El benchmarking es una técnica fundamental para evaluar el rendimiento de sistemas y servicios. Permite comparar distintas configuraciones, detectar cuellos de botella y validar mejoras de rendimiento. En este bloque se explorarán tanto herramientas de propósito general como específicas para servidores web.

## OpenBenchmark
Es un repositorio de benchmarks de codigo abierto, *Phoronix* es la plataforma de OpenBench que permite ejecutar benchmarks en una amplia variedad de sistemas y configuraciones. Permite realizar pruebas de rendimiento en CPU, GPU, memoria, almacenamiento y más.

Podemos instalar Phoronix en el equipo anfitrion, en la MV, o en Docker, se ha recomendado aprender a usarlo en Docker sin embargo vamos a tener menos problemas de dependencias si lo instalamos directamente.

Una vez instalado, deberemos configurarlo, descargar los tests y ejecutarlos:
```bash
phoronix-test-suite batch-setup
phoronix-test-suite install compress-7zip
phoronix-test-suite install stress-ng
phoronix-test-suite batch-run compress-7zip stress-ng
```
De otra forma, podríamos haber usado la versión de Docker y haber instalado tests sin dependencias, por ejemplo compress-gzip.

## Apache Benchmark
Dentro de los benchmarks para servidores web hay varias herramientas, una de ellas bastante popular es Apache Benchmark (Mediante el comando *ab*). Particularmente, nos dice cuantas peticiones por segundo es capaz de soportar nuestro servidor.

Para ejecutar ApacheBench, tenemos la sintaxis:
```bash
ab <OPTIONS> <WEB_SERVER_ADDRESS>/<PATH>
```
Las opciones mas comunes que usaremos son:
- *-n*: El número de peticiones a enviar
- *-t*: La duración (en segundos) del benchmark
- *-c*: El número de peticiones concurrentes a realizar. 
Si usamos -t y -n, deberemos poner primero -t ya que de lo contrario, ApacheBench lo va a ignorar, dejando por defecto 50000.
El comando *ab* se ejecuta en un solo hilo, el flag -c indica cuantos fd se van a reservar para la ejecución, no cuantas peticiones HTTP se van a mandar simultáneamente.

### Ejercicio 2.2.1 

Para la resolución de este ejercicio usaremos la maquina o maquinas virtuales en las que hayamos desplegado un servidor web ya sea con Apache o con Nginx como se explica en el bloque 1. A continuación ejecutaremos el benchmark, por ejemplo:
```bash
ab -n 5000 -c 10 http://192.168.69.69/
```
Lo que nos devolverá una salida con varios campos, destacamos los siguientes:
- Time per request: Apache proporciona dos variantes de esta métrica, ambas dependen del tiempo tomado para los tests (Time taken for tests) y del número de respuestas que se han procesado. Ambas multiplican por 1000 para obtener el resultado en ms.
La diferencia es que la primera que aparece no toma la concurrencia en cuenta.

- Request per second: El número de peticiones que nuestro servidor es capaz de procesar por cada segundo.

- Transfer Rate: Es otra métrica importante ya que nos dice la cantidad de datos que es capaz de transferir la pagina por segundo, este dato esta relacionado con los anteriores sin embargo, existen ciertas técnicas que pudieran mantener el rendimiento ante una página más pesada.

# Simulación Carga Jmeter
Aunque Apache Benchmark tiene muchas posibilidades y es una herramienta poderosa y correcta, existen otras herramientas que permiten hacer tests más complejos, nosotros veremos concretamente Jmeter. Este software está diseñado para cargar funcionalidades de benchmark y medir rendimiento, es decir, puede medir y generar carga de forma genérica para varios elementos, si que es cierto, que en un principio estaba reservada a medir servidores web.

Una de las características interesantes de Jmeter es que se puede crear concurrencia real gracias a la posibilidad de crear varias hebras dentro de las mismas CPU así como de distribuir el esfuerzo de carga entre varios equipos en red local.

La ejecución es mediante linea de comandos, lo que aligera la carga de la maquina que genera las peticiones al servidor, además facilita la automatización de ciertos tests.

Para la realización del siguiente ejercicio, deberemos clonarnos el siguiente repositorio:
```bash
git clone https://github.com/davidPalomar-ugr/iseP4JMeter
```
Una vez clonado, podemos acceder a el, veremos que nos encontramos con un docker-compose.yaml, haciendo simplemente: 
```bash
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
    - Template: `$0$`. $i$ significa que coja la i-ésima ocurrencia. Con 0 coge todas.

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
    - Parser: `shared`

Ahora añadimos a ETSII Alumnos API los siguientes Listener
Add > Listener > Summary Report
Add > Listener > View Results in Table
Add > Listener > Aggregate Report
**Nota:** Se aconseja además: Add > Listener > View Results Tree

Ahora podemos ejecutar con el run de la interfaz gráfica, sin embargo, para aplicaciones que vayamos a lanzar a producción, y, para la resolución de este ejercicio, ejecutamos sin modo gráfico:
```bash
jmeter -n -t ./archivo.jmx -l results.jtl
```

Donde -n significa que no se abre el modo gráfico, -t es el archivo a ejecutar con la configuración y -l se utiliza para saber en que fichero guardar los resultados.
