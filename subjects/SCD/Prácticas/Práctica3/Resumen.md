# Sistemas Concurrentes y Distribuidos. Sesión 3 de Prácticas.

**Autor:** José Juan Urrutia Milán
***

- **Asignatura:** Sistemas Concurrentes y Distribuidos.  
- **Curso Académico:** 2024-25.
- **Grado:** Doble Grado en Ingeniería Informática y Matemáticas.
- **Profesor:** José Miguel Mantas Ruíz.
- **Descripción:** Resumen de la práctica 3.

Veremos varias soluciones al problema de los productores/consumidores y el problema de los filósofos.
  
# Productor/Consumidor
En el caso distribuido, necesitaremos tener tres roles de procesos:
- **Productor**: Que produce una secuencia de datos y los envía al proceso **buffer**.
- **Consumidor**: Que realiza peticiones al proceso **buffer** y como respuesta recibe y consume los enteros.
- **Buffer:** Recibe (de forma alterna) enteros del proceso productor y peticiones del consumidor. Responde al consumidor enviándole los enteros recibidos.  
  
