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
    ansible.builtin.shell:
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

