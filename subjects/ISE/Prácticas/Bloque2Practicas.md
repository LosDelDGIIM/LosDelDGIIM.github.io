**Autora:** Laura Mandow Fuentes

## Docker

Para permitir que un usuario no privilegiado use docker:
```
groupadd docker # en caso de que no esté creado ya
sudo usermod -aG docker $(whoami)
```
Para ver los contanier ejecutándose: `docker ps`
Para hacer que un container ya lanzado ejecute un comando:
```
docker contanier exec <container id> <command>
```

# Bechmarks

### Phoronix Test Suite
Hay varias formas de instalar esta aplicación. Nosotros usaremos el contenedor asociado que tiene con Docker.
Para instalarlo:
```
docker pull phoronix/pts
```

Para ejecutarlo de forma que la shell te permita ejecutar comandos -it (interativo). 
```
docker run -it phoronix/pts
```
Tras esto se nos abrirá una shell interactiva en la que podremos ejecutar comandos de Phoronix Test Suite.
Consultemos los tests disponibles:
```
list-available-tests
```
Escogemos uno, por ejemplo:
```
install pts/git
```
Una vez instalado, lo ejecutamos:
```
run pts/git
```
Nos preguntará si queremos guardar los resultados de este test, y el fichero en el que queremos hacerlo.


### Apache Benchmark

En primer lugar, se realizan los pasos vistos en el bloque 1 para montar un servidor web http en una MV. Se aconseja montar un servidor de Apache en una y otro de Nginx en otra para poder comparar ambas.

Instalamos la herramienta `ab`, en Ubuntu:
```
sudo apt install apache2-utils
```

Este comando tiene muchas opciones interesantes, pero solo nos interesan dos:
- `-n`: especifica el número peticiones a realizar.
- `-c`: número de peticiones que se envían simultáneamente de cada vez (concurrencia). 

Finalmente probamos el benchmark:
```
ab -n 1000 -c 100 192.168.56.69/index.html
```
**Nota:** es necesariop especificar la ruta del fichero que quiero obtener del servidor.

## JMeter
**MUY** recomendable Listener > View Results Tree

### HTTP REQUEST DEFAULTS
Para poner campos comunes a las http request como la ip del servidor y el puesto

### HTTP AUTHENTICATION MANAGER
Lo usamos para el BasicAuth
user:password

### THREAD GROUP
Tenemos 2:
- Alumnos
- Administradores

### Alumnos
Son un Thread Group.
Primero debemos hacer login
- Http Request:
    - path: /api/v1/auth/login
    - Tipo: POST
    - Parametros (name): login y password.
- CSV Data Set Config: para obtener los user and passwd de todos los alumnos. El nombre de las variables ya viene especificado en el fichero. **OJO:** el path del fichero debe ser relativo (estamos en el dir del repo, ./jMeter/alumnos.csv sería el path correcto). 

Una vez hecho el login, queremos obtener el expediente del alumno. 
Para ello hacemos otro Http Request:
- Tipo: GET
- path: /api/v1/alumnos/alumno/${login}
Este a su vez tiene un hijo que será un Http Header Manager. Debemos pasarle "Bearer ${token}" a un campo "Authentication" de la cabecera. 
Para ello necesitamos el token que es valor de retorno de el Http Request anterior.
Para logralo le añadimos un Regular Extractor (Post-Processor). 
- name: token
- regular expresion: .* (pq queremos todo lo q devuelve)
- group: $0$ (por poner uno, da igual pero si no lo poner no funciona)
El token lo devuelve en el Body.

### Administradores
Se hace igual pero en vez de un segundo Http Request para el contenido, usamos un Access Log Server para leer del fichero. Hace falta especificar ip y puerto pq no viene en el fichero dado y no lo toma por defecto.

## Monitorizacion
### TOP
mirar jj

### Stress
Utilidad para meterle workload al sistema. 
`--timeout 10s`: importante si no quieres que se te quede infinitamente
`--cpu 20`: para workload de cpu (sqrt()). Número de procesos creados.

## Cron
Usaremos `cron` y `logger`.
### Logger
Escribe en el archivo `/var/log/syslog`.
`-t`: la tag del msg a loguear
```
logger -t ise "hola"
```
### Cron
Para ejecutarlo: `crontab -e`
Cada usuario tiene su `crontab` asociado distinto.
Para ejecutar algo cada 5 minutos: `/5 * * * *`
```
* * * * * logger -t ISE "LMF:`date` - `cat /proc/loadavg`"
```

## Grafana + Prometheus

Copiamos el los ficheros del guión y hacemos `docker compose up -d`.
Tenemos que darle permiso de escritura al grupo para la carpeta `grafana_data` y `prometheus_data` para que se nos lancen los cubernetes.

### Node exporter Linux
Hay que instalarlo en la **MV**. 
curl -LO con O de Oso
hay que hacer lo que dice jj y el guion
ponerlo como servicio firewall etc
incluyendo recovecon skljfls

En el host runeamos el grafana y prometheus con docker
para hacer los dashboard que nos piden
Status sshd y Apache httpd: necesitamos instalar en la MV systemd_explorer
Hay que modificar el promtheus.yml para incluir este job, el puerto 9558.
Hay que meterlo como servicio tb.
Lo movemos el ejecutable a /usr/local/bin


Otra opcion es sin instalar esto con node_explorer usando un collector (crear script, updatearlo con cron etc).


Bueno hemos hecho la query del porcentaje de cpu:
- node_cpu_seconds_total{mode="idle"}: tiempo de la cpu en segundos que pasa en estado "idle" (sin usarse)
- [5m]: durante 5 minutso
- rate: nos da la media por segundo (de los 5 min el procentaje) 
- avg by (instace): nos da la media 


## lo de la API
para poder conectar los distintos contenedores con distintos compose he creado un red interna con:
```
docker network create <red>
```
y en los dockerfiles la he añadido
```yml
networks:
    default:
        external: true
        name: <red>
```
