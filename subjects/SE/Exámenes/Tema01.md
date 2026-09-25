# Sistemas Empotrados - Test Tema 1: Introducción a los Sistemas Empotrados

- **Descripción:** Preguntas Tipo Test correspondientes al Tema 1: Introducción a los Sistemas Empotrados (Metodologías de diseño, partición HW/SW, SoC, BSP y procesadores).

---

1. Para mejorar las prestaciones del sistema, se pueden usar circuitos específicos (co-procesadores o aceleradores) que implementen ciertas funciones clave
    - (x) Los co-procesadores se gestionan mediante instrucciones específicas de la CPU y los aceleradores mediante instrucciones load/store
    - ( ) No hay diferencia. Ambos se gestionan mediante instrucciones load/store
    - ( ) Los aceleradores se gestionan mediante instrucciones específicas de la CPU y los co-procesadores mediante instrucciones load/store
    - ( ) No hay diferencia. Ambos se gestionan mediante instrucciones específicas

2. Una tableta...
    - ( ) Es un sistema empotrado porque está basada en un SoC
    - ( ) Es un sistema empotrado porque su diseño minimiza su consumo energético
    - (x) No es un sistema empotrado porque se le pueden instalar aplicaciones para múltiples fines
    - ( ) No es un sistema empotrado porque usa un SO de propósito general

3. La partición HW/SW...
    - (x) Se lleva a cabo en cualquier metodología de diseño
    - ( ) No forma parte del proceso de co-diseño de un sistema empotrado
    - ( ) No forma parte del proceso de diseño basado en plataformas
    - ( ) Sólo se lleva a cabo en la metodología clásica de diseño de sistemas empotrados

4. Un entorno inteligente es...
    - (x) Un entorno físico dotado de sensores y actuadores conectados a un servidor que los gestiona de forma inteligente
    - ( ) Un entorno en el que se ha desplegado una red de sensores
    - ( ) Un entorno en el que hay desplegados dispositivos inteligentes
    - ( ) Ninguna de las otras respuestas es correcta

5. Se desea implementar un robot aspirador con posibilidad de configuración mediante una interfaz Web. ¿Cuál de las siguientes opciones sería las más adecuada para el software de sistema?
    - (x) Portar un GPOS para nuestra plataforma que haga uso de nuestro BSP, y diseñar la aplicación de forma que haga uso de los servicios del GPOS
    - ( ) Desarrollar la aplicación haciendo uso directamente de los servicios proporcionados por nuestro BSP
    - ( ) Usar un middleware de comunicaciones que implemente un servidor Web
    - ( ) Portar un RTOS para nuestra plataforma que haga uso de nuestro BSP, y diseñar la aplicación de forma que haga uso de los servicios del RTOS

6. Un smart device es...
    - ( ) Un dispositivo móvil con GPS y pantalla
    - ( ) Un dispositivo que ejecuta algoritmos de inteligencia artificial
    - ( ) Un dispositivo con multitud de sensores
    - (x) Un dispositivo que transmite información contextual del usuario a la nube

7. Con un editor de textos...
    - ( ) No se podría desarrollar la parte HW de un sistema empotrado
    - ( ) Sólo se podría desarrollar la parte SW de un sistema empotrado
    - ( ) Sólo se podría desarrollar la parte HW de un sistema empotrado
    - (x) Se podría desarrollar un sistema empotrado completo

8. Dentro de los componentes HW de un sistema, los controladores de sistema..
    - (x) Coordinan los componentes importantes del sistema
    - ( ) Ejecutan funciones complejas mediante hardware específico
    - ( ) Proporcionan las capacidades de E/S del sistema
    - ( ) Ejecutan el software de la aplicación

9. Un core IP soft..
    - ( ) Un core IP no puede ser soft, ya que describe un diseño HW
    - ( ) Contiene el diseño de una función software que nos viene bien para nuestro sistema
    - ( ) Contiene el diseño de una parte HW de nuestro sistema, por lo que no podemos modificarla
    - (x) Contiene el diseño de una parte HW que puede modificarse y adaptarse a nuestro diseño y a nuestra tecnología de implementación

10. A la hora de implementar un SoC..
    - ( ) Es mejor fabricarlo mediante una FPGA
    - ( ) Es necesario mandarlo a una fundición para que fabrique el chip
    - ( ) Es mejor fabricarlo mediante un ASIC
    - (x) Ninguna de las otras respuestas es correcta

11. Al tener parte de las funciones implementadas en software, los sistemas empotrados permiten
    - (x) Implementar sistemas actualizables
    - ( ) Implementación del software y hardware
    - ( ) mejorar al hardware
    - ( ) mejorar el software

12. El middleware.....
    - (x) Proporciona interoperabilidad en los sistemas empotrados distribuidos.
    - ( ) mejora el hardware
    - ( ) mejora el software
    - ( ) todas son falsas

13. A la hora de seleccionar el procesador más adecuado para un sistema empotrado.
    - ( ) Selecionar siempre aquel que obtenga mejores prestaciones para la aplicacion.
    - ( ) Se debe escoger siempre el que menos energia consuma.
    - ( ) Se debe escoger el mas barato para no penalizar el coste total.
    - (x) Ninguna de las anteriores es correcta.

14. ¿Que es Dhrystone?
    - (x) Es un programa escrito en c con instruciones generadas de forma arbitraria.
    - ( ) está escrito en c++
    - ( ) son todas falsas
    - ( ) Es un programa escrito en emsamblador

15. Dentro de los componentes de HW de un sistema,los controladores e sistema..
    - ( ) mejora la cpu
    - ( ) se encarga de la cpu
    - (x) Coordinan los componentes importantes del sistema.
    - ( ) Todas son falsas

16. Para mejorar las prestaciones del sistema,se pueden usar circuitos específicos (Co-procesadores o aceleradores) que implemente ciertas funciones clave
    - ( ) Hacen uso de un acelerador
    - ( ) Hacen uso de procesador para llevar a cabo la mejora de las prestaciones
    - (x) Los co-procesadores se gestionan mediante instrucciones específicas de la cpu y los aceleradores mediente instrucciones load/store.
    - ( ) Todas son falsas

