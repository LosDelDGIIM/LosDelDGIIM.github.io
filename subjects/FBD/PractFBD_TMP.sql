/*
Asignatura: Fundamentos de Bases de Datos
Autor: Arturo Olivares Martos
Profesor: Nicolás Marín Ruiz
Descripción: Prácticas de FBD, ejercicios obtenidos del Cuaderno dado por el profesorado.
*/


/*--------------------------------------------------------------
    Capítulo 1: Definición del esquema de una base de datos
*/--------------------------------------------------------------
--DROP TABLE prueba1;
CREATE TABLE prueba1 (
    cad char(3),
    n int,
    x float
);

-- Ejercicio 1.1. Ver la descripción de la tabla prueba1.
DESCRIBE prueba1;
--

-- Ejemplo 1
--DROP TABLE serjefe;
--DROP TABLE plantilla;
CREATE TABLE plantilla(
    dni varchar2(9),
    nombre varchar2(15),
    estadocivil varchar2(10)
        CHECK (estadocivil IN ('soltero', 'casado', 'divorciado', 'viudo')),
    fechaalta date,
    PRIMARY KEY (dni)
);
CREATE TABLE serjefe(
    dnijefe REFERENCES plantilla(dni),
    dnitrabajador REFERENCES plantilla(dni) PRIMARY KEY
);
--

-- Ejercicio 1.2
-- Data types in Oracle Database:
-- https://docs.oracle.com/en/database/oracle/oracle-database/19/sqlrf/Data-Types.html
--

-- Ejercicio 1.3
-- Dibujo de un diagrama E/R
--

-- Ejercicio 1.4
--DROP TABLE prueba1;
--

-- Ejercicio 1.5
ALTER TABLE plantilla ADD (fechabaja date);
--

-- Seccion 1.6.1
DROP TABLE ventas;
DROP TABLE proveedor;
CREATE TABLE proveedor(
    codpro VARCHAR2(3) CONSTRAINT codpro_clave_primaria PRIMARY KEY,
    nompro VARCHAR2(30) CONSTRAINT nompro_no_nulo NOT NULL,
    status NUMBER CONSTRAINT status_entre_1_y_10
        CHECK (status>=1 and status <=10),
    ciudad VARCHAR2(15)
);
DESCRIBE proveedor;
--

-- Seccion 1.6.2
DROP TABLE pieza;
CREATE TABLE pieza(
    codpie VARCHAR2(3) CONSTRAINT codpie_clave_primaria PRIMARY KEY,
    nompie VARCHAR2(10) CONSTRAINT nompie_no_nulo NOT NULL,
    color VARCHAR2(10),
    peso NUMBER(5,2)
        CONSTRAINT peso_entre_0_y_100 CHECK (peso>0 and peso <=100),
    ciudad VARCHAR2(15)    
);
DESCRIBE pieza;
--

-- Seccion 1.6.3
DROP TABLE proyecto;
CREATE TABLE proyecto(
    codpj VARCHAR2(3) CONSTRAINT codpj_clave_primaria PRIMARY KEY,
    nompj VARCHAR2(20) CONSTRAINT nompj_no_nulo NOT NULL,
    ciudad VARCHAR2(15)
);
DESCRIBE proyecto;
--

-- Seccion 1.6.4
CREATE TABLE ventas(
    codpro CONSTRAINT codpro_clave_externa_proveedor
        REFERENCES proveedor(codpro),
    codpie CONSTRAINT codpie_clave_externa_pieza
        REFERENCES pieza(codpie),
    codpj CONSTRAINT codpj_clave_externa_proyecto
        REFERENCES proyecto(codpj),
    cantidad NUMBER(4),
    CONSTRAINT clave_primaria_ventas PRIMARY KEY (codpro, codpie, codpj)
);
DESCRIBE ventas;
--

-- Ejericio 1.6
ALTER TABLE ventas ADD (fecha DATE);
DESCRIBE ventas;
--

-- Ejercicio 1.7
--DROP TABLE faltas;
--DROP TABLE encuentros;
--DROP TABLE jugadores;
--DROP TABLE equipos;
CREATE TABLE equipos(
    codE VARCHAR2(3) CONSTRAINT codE_clave_primaria PRIMARY KEY,
    nombreE VARCHAR2(20) CONSTRAINT nombreE_no_nulo NOT NULL CONSTRAINT nombreE_unico UNIQUE,
    localidad VARCHAR2(20) CONSTRAINT localidad_no_nulo NOT NULL,
    entrenador VARCHAR2(20) CONSTRAINT entrenador_no_nulo NOT NULL,
    fecha_crea DATE CONSTRAINT fecha_crea_no_nulo NOT NULL
);

CREATE TABLE jugadores(
    codJ VARCHAR2(3) CONSTRAINT codJ_clave_primaria PRIMARY KEY,
    codE  CONSTRAINT codE_no_nulo NOT NULL CONSTRAINT codE_clave_externa_equipos
        REFERENCES equipos(codE),
    nombreJ VARCHAR2(20) CONSTRAINT nombreJ_no_nulo NOT NULL
);

CREATE TABLE encuentros(
    ELocal CONSTRAINT ELocal_clave_externa_equipos
        REFERENCES equipos(codE),
    EVisitante CONSTRAINT EVisitante_clave_externa_equipos
        REFERENCES equipos(codE),
    fecha DATE,
    PLocal NUMBER(3) DEFAULT 0 CONSTRAINT PLocal_no_negativo
        CHECK (PLocal >= 0),
    PVisitante NUMBER(3) DEFAULT 0 CONSTRAINT PVisitante_no_negativo
        CHECK (PVisitante >= 0),
    CONSTRAINT clave_primaria_encuentros PRIMARY KEY (ELocal, EVisitante)
);

CREATE TABLE faltas(
    codJ CONSTRAINT codJ_clave_externa_jugadores
        REFERENCES jugadores(codJ),
    ELocal,
    EVisitante,
    num NUMBER(1) DEFAULT 0 CONSTRAINT num_entre_0_y_5
        CHECK (num >= 0 and num <= 5),
    CONSTRAINT clave_primaria_faltas PRIMARY KEY (codJ, ELocal, EVisitante),
    CONSTRAINT clave_externa_encuentro FOREIGN KEY (ELocal, EVisitante)
        REFERENCES encuentros(ELocal, EVisitante)
);
--

COMMIT;

/*--------------------------------------------------------------
    Capítulo 2: Mantenimiento de una base de datos
*/--------------------------------------------------------------
-- Ejemplo 2.1
INSERT INTO prueba1 VALUES ('aa', 1, 1.1);
INSERT INTO prueba1 VALUES ('Aa', 2, 2.1);
INSERT INTO prueba1 VALUES ('aa', 1, 1.1);
SELECT * FROM prueba1;
--

-- Ejemplo 2.2
DESCRIBE plantilla;
DESCRIBE serjefe;
INSERT INTO plantilla (dni,nombre,estadocivil,fechaalta)
    VALUES ('12345678','Pepe','soltero', SYSDATE);
INSERT INTO plantilla (dni,nombre,estadocivil,fechaalta)
    VALUES ('87654321','Juan', 'casado', SYSDATE);
INSERT INTO serjefe
    VALUES ('87654321','12345678');
INSERT INTO plantilla (dni, estadocivil)
    VALUES ('11223344','soltero');
--

-- Ejercicio 2.1
SELECT * FROM prueba1;
SELECT * FROM plantilla;
--

-- Ejemplo 2.3
UPDATE plantilla
    SET estadocivil = 'divorciado'
    WHERE nombre='Juan';
--

-- Ejercicio 2.2
UPDATE plantilla
    SET nombre = 'Luis'
    WHERE dni='12345678';
--

-- Ejemplo 2.4
DELETE FROM prueba1;
--

-- Ejercicio 2.3
--DELETE FROM plantilla;  -- No se puede borrar porque serjefe tiene una referencia a plantilla
DELETE FROM serjefe;
DELETE FROM plantilla;
--

-- Ejemplo 2.5
SELECT * FROM plantilla;
UPDATE plantilla
    SET fechaalta = fechaalta+1
    WHERE nombre='Juan';
SELECT * FROM plantilla;
--

INSERT INTO plantilla
    VALUES ('11223355','Miguel','casado',
                TO_DATE('22/10/2005','dd/mm/yyyy'),
            null);  -- Como no hemos especificado el nombre de las columnas, debemos insertar TODOS los valores, no puedo quitar el null
SELECT * FROM plantilla;
DELETE FROM plantilla WHERE nombre='Miguel';

-- Ejemplo 2.6
SELECT TO_CHAR(fechaalta, 'dd-mon-yyyy') FROM plantilla;
--

-- Ejemplo 2.7
SELECT * FROM plantilla;
--

-- Seccion 2.2
DESCRIBE proveedor;
INSERT INTO proveedor (codpro, nompro, status, ciudad)
    VALUES ('S1', 'Jose Fernandez', 2, 'Madrid');
INSERT INTO proveedor (codpro, nompro, status, ciudad)
    VALUES ('S2', 'Manuel Vidal', 1, 'Londres');
INSERT INTO proveedor (codpro, nompro, status, ciudad)
    VALUES ('S3', 'Luisa Gomez', 3, 'Lisboa');
INSERT INTO proveedor (codpro, nompro, status, ciudad)
    VALUES ('S4', 'Pedro Sanchez', 4, 'Paris');
INSERT INTO proveedor (codpro, nompro, status, ciudad)
    VALUES ('S5', 'Maria Reyes', 5, 'Roma');
INSERT INTO proveedor (codpro, nompro, status, ciudad)
    VALUES ('S6', 'Jose Perez', 6, 'Bruselas');
INSERT INTO proveedor (codpro, nompro, status, ciudad)
    VALUES ('S7', 'Luisa Martin', 7, 'Atenas');


DESCRIBE pieza;
INSERT INTO pieza (codpie, nompie, color, peso, ciudad)
    VALUES ('P1', 'Tuerca', 'Gris', 2.5, 'Madrid');
INSERT INTO pieza (codpie, nompie, color, peso, ciudad)
    VALUES ('P2', 'Tornillo', 'Rojo', 1.25, 'Paris');
INSERT INTO pieza (codpie, nompie, color, peso, ciudad)
    VALUES ('P3', 'Arandela', 'Blanco', 3, 'Londres');
INSERT INTO pieza (codpie, nompie, color, peso, ciudad)
    VALUES ('P4', 'Clavo', 'Gris', 5.5, 'Lisboa');
INSERT INTO pieza (codpie, nompie, color, peso, ciudad)
    VALUES ('P5', 'Alcayata', 'Blanco', 10, 'Roma');

DESCRIBE proyecto;
INSERT INTO proyecto (codpj, nompj, ciudad)
    VALUES ('J1', 'Proyecto 1', 'Londres');
INSERT INTO proyecto (codpj, nompj, ciudad)
    VALUES ('J2', 'Proyecto 2', 'Londres');
INSERT INTO proyecto (codpj, nompj, ciudad)
    VALUES ('J3', 'Proyecto 3', 'Paris');
INSERT INTO proyecto (codpj, nompj, ciudad)
    VALUES ('J4', 'Proyecto 4', 'Roma');

DESCRIBE ventas;
DESCRIBE medina.ventas;
INSERT INTO ventas (codpro, codpie, codpj, cantidad, fecha)
    SELECT codpro, rtrim(codpie), rtrim(codpj), cantidad, fecha  FROM medina.ventas;
/*
    Notemos que, si vemos el esquema de medina.ventas, este usa tipos de datos distintos (char(3)).
    Estos tipos de datos completan con espacios, por lo que no nos deja incluirlos (pruébese).
    Para evitar este problema, usamos la función rtrim, que recorta por la derecha.
*/
--


-- Ejercicio 2.4
INSERT INTO ventas VALUES ('S3', 'P1', 'J1', 150, '24/12/05');
        DELETE FROM ventas WHERE (codpro='S3' and codpj='J1' and codpie='P1');  -- Para que no tenga efectos.
--INSERT INTO ventas (codpro, codpj) VALUES ('S4', 'J2');             -- No se puede porque codpie no puede ser NULL (es parte de la CP)
--INSERT INTO ventas VALUES('S5','P3','J6',400,TO_DATE('25/12/00'));  -- No se puede porque J6 no existe en proyecto
--

-- Ejercicio 2.5. Comento para que no haga efectos
--UPDATE ventas
--    SET fecha = TO_DATE(2005,'YYYY')
--    WHERE codpro='S5';
--

-- Ejercicio 2.6
SELECT codpro,codpie, TO_CHAR(fecha,'"Dia" day,dd/mm/yy')
    FROM ventas;
--


-- Ejercicio 2.7
-- Rellenar Tablas Baloncesto.
--


-- Finalización Capítulo 2
DROP TABLE prueba1;
DROP TABLE serjefe;
DROP TABLE plantilla;

DROP TABLE faltas;
DROP TABLE encuentros;
DROP TABLE jugadores;
DROP TABLE equipos;
COMMIT;


/*--------------------------------------------------------------
    Capítulo 3: Realización de consultas a una base de datos
*/--------------------------------------------------------------

-- Ejemplo 3.1
-- AR: \pi_{ciudad}(proyecto)
--

-- Ejercicio 3.1
SELECT DISTINCT ciudad FROM proyecto;
--

-- Ejemplo 3.2
SELECT * FROM proveedor;
--

-- Ejercicio 3.2
SELECT codpro, codpj, codpie FROM ventas;
-- No es necesario el DISTINCT porque la clave primaria de ventas es (codpro, codpj, codpie)
--

-- Ejemplo 3.3
SELECT codpro FROM ventas WHERE codpj='J1';
--

-- Ejercicio 3.3
-- Muestra las piezas de Madrid que son grises o rojas.
SELECT * FROM pieza WHERE (ciudad='Madrid' and (color='Rojo' or color='Gris'));
--

-- Ejercicio 3.4
-- Encontrar todos los suministros cuya cantidad está entre 200 y 300, ambos inclusive.
SELECT * FROM ventas WHERE (200<=cantidad AND cantidad<=300);
SELECT * FROM ventas WHERE cantidad BETWEEN 200 AND 300;    -- Incluye los extremos
--

-- Ejemplo 3.4
-- Mostrar los nombres y ciudades de los proveedores cuyo nombre de ciudad empieza por 'L'. 
SELECT nompro, ciudad FROM proveedor WHERE ciudad LIKE 'L%';
--

-- Ejercicio 3.5
-- Mostrar las piezas que empiezan por un carácter seguido de ornillo.
SELECT * FROM pieza WHERE nompie LIKE '_ornillo';
--

-- Ejemplo 3.5
SELECT cantidad/12, round(cantidad/12,3), trunc(cantidad/12, 3), floor(cantidad/12), ceil(cantidad/12)
    FROM ventas WHERE (cantidad/12)>10;     -- Si además quiero todos, pongo *.ventas
--

-- Ejemplo 3.6
-- Encontrar los proveedores que tienen su status registrado en la base de datos.
SELECT * FROM proveedor WHERE status IS NOT NULL;
--

-- Ejemplo 3.7 || Ejercicio 3.6
-- Mostrar la información de todas las tablas denominadas ventas a las que tienes acceso.
SELECT * FROM ALL_TABLES WHERE table_name LIKE upper('%ventas%');
--

-- Ejemplo 3.8
-- Ciudades donde viven proveedores con status mayor de 2 en las que no se fabrica la pieza 'P1'. 
SELECT ciudad FROM proveedor WHERE status>2
    MINUS
SELECT ciudad FROM pieza WHERE codpie='P1';
--

-- Ejercicio 3.7
-- Resolver la consulta del ejemplo 3.8 utilizando el operador ∩ (Interseccion).
SELECT ciudad FROM proveedor WHERE status>2 -- Seleccionamos ciudades con proveedores con status mayor de 2
    INTERSECT
SELECT proveedor.ciudad FROM proveedor, pieza
    WHERE pieza.codpie='P1' AND proveedor.ciudad != pieza.ciudad;
--

-- Ejercicio 3.8
-- Encontrar los códigos de aquellos proyectos a los que solo abastece 'S1'.
SELECT codpj FROM ventas    -- Seleccionamos de ventas, porque S1 ha de abastecerle
    MINUS
SELECT codpj FROM ventas WHERE codpro != 'S1';
--

-- Ejercicio 3.9
-- Mostrar todas las ciudades de la base de datos. Utilizar UNION.
SELECT ciudad FROM proveedor
    UNION
SELECT ciudad FROM proyecto
    UNION
SELECT ciudad FROM pieza;
--

-- Ejercicio 3.10
-- Mostrar todas las ciudades de la base de datos. Utilizar UNION ALL. 
SELECT ciudad FROM proveedor
    UNION ALL
SELECT ciudad FROM proyecto
    UNION ALL
SELECT ciudad FROM pieza;
--

-- Ejercicio 3.11
-- Comprueba cuántas tuplas resultan del producto cartesiano aplicado a ventas y proveedor. 
SELECT * FROM proveedor;
SELECT * FROM ventas;
SELECT * FROM proveedor, ventas;
--

-- Ejemplo 3.9
-- Muestra las posibles ternas (codpro,codpie,codpj) tales que todos los implicados sean de la misma ciudad.
SELECT codpro, codpie, codpj FROM proveedor, pieza, proyecto
    WHERE   proveedor.ciudad = pieza.ciudad
        AND proveedor.ciudad = proyecto.ciudad;
--

-- Ejemplo 3.10
-- Mostrar las ternas (codpro,codpie,codpj) tales que todos los implicados son de Londres.
SELECT codpro, codpie, codpj FROM proveedor, pieza, proyecto
    WHERE   proveedor.ciudad = 'Londres'
        AND proveedor.ciudad = pieza.ciudad
        AND proveedor.ciudad = proyecto.ciudad;
    -- Esta es poco eficiente. Mejor hacer el filtrado ANTES de hacer el producto cartesiano.
SELECT codpro, codpie, codpj
    FROM (SELECT * FROM proveedor WHERE ciudad='Londres'),
         (SELECT * FROM pieza WHERE ciudad='Londres'),
         (SELECT * FROM proyecto WHERE ciudad='Londres');
--

-- Ejericio 3.12
-- Mostrar las ternas que son de la misma ciudad pero que hayan realizado alguna venta.
SELECT codpro, codpie, codpj FROM ventas
    INTERSECT
SELECT codpro, codpie, codpj FROM proveedor, pieza, proyecto
    WHERE   proveedor.ciudad = pieza.ciudad
        AND proveedor.ciudad = proyecto.ciudad;
--

-- Ejercicio 3.13
-- Encontrar parejas de proveedores que no viven en la misma ciudad.
SELECT p1.codpro, p2.codpro FROM proveedor p1, proveedor p2
    WHERE p1.ciudad > p2.ciudad;    -- No usar != porque produce duplicados (A,B) y (B,A)
--

-- Ejercicio 3.14
-- Encuentra las piezas con máximo peso.
SELECT codpie FROM pieza
    MINUS
SELECT A.codpie FROM pieza A, pieza B
    WHERE A.peso < B.peso;
--

-- Ejemplo 3.12
-- Mostrar los nombres de proveedores y la cantidad de aquellas ventas de cantidad superior a 800 unidades.
SELECT nompro, cantidad
    FROM proveedor NATURAL JOIN (SELECT * FROM ventas WHERE cantidad>800);
--

-- Ejercicio 3.15
-- Mostrar las piezas vendidas por los proveedores de Madrid.
SELECT DISTINCT codpie
    FROM ventas NATURAL JOIN (SELECT * FROM proveedor WHERE ciudad='Madrid');
--

-- Ejercicio 3.16
-- Encuentra la ciudad y los códigos de las piezas suministradas a cualquier proyecto por un proveedor que está en la misma ciudad donde está el proyecto.
SELECT DISTINCT proveedor.ciudad, ventas.codpie FROM ventas
    JOIN proveedor ON ventas.codpro = proveedor.codpro
    JOIN proyecto ON ventas.codpj = proyecto.codpj
    WHERE proveedor.ciudad = proyecto.ciudad;
--

-- Ejemplo 3.13
-- Encontrar los nombres de proveedores ordenados alfabéticamente.
SELECT nompro
    FROM proveedor
    ORDER BY nompro;
--

-- Ejercicio 3.17
-- Comprobar la salida de la consulta anterior sin la cláusula ORDER BY.
SELECT nompro
    FROM proveedor;
--

-- Ejercicio 3.18
-- Listar las ventas ordenadas por cantidad. Si algunas ventas coinciden en la cantidad se ordenan en función de la fecha de manera descendente.
SELECT * FROM ventas
    ORDER BY cantidad, fecha DESC;
--jajajja oleee

-- Ejemplo 3.14
-- Encontrar las piezas suministradas por proveedores de Londres (sin usar el operador de reunión).
SELECT codpie FROM ventas
    WHERE codpro IN (SELECT codpro FROM proveedor WHERE ciudad='Londres');
    -- // TODO: El IN solo lo hace una vez, o todas?
    --
SELECT codpie FROM ventas
    NATURAL JOIN (SELECT codpro FROM proveedor WHERE ciudad='Londres');
--

-- Ejericio 3.19
-- Mostrar las piezas vendidas por los proveedores de Madrid (fragmentando la consulta con ayuda del operador IN).
-- Compara la solución con la del ejercicio 3.15.
SELECT DISTINCT codpie FROM ventas
    WHERE codpro IN (SELECT codpro FROM proveedor WHERE ciudad='Madrid');
--

-- Ejercicio 3.20
-- Encuentra los proyectos que están en una ciudad donde se fabrica alguna pieza.
SELECT DISTINCT codpj FROM proyecto
    WHERE ciudad IN (SELECT ciudad FROM pieza);
--

-- Ejercicio 3.21
-- Encuentra los códigos de aquellos proyectos que no utilizan ninguna pieza roja que esté suministrada por un proveedor de Londres. 
SELECT DISTINCT codpj FROM proyecto
    WHERE codpj NOT IN 
        (SELECT codpj FROM ventas
            WHERE       codpie IN (SELECT codpie FROM pieza WHERE color='Rojo')
                    AND codpro IN (SELECT codpro FROM proveedor WHERE ciudad='Londres'));
    -- NOT IN Equivale a MINUS
SELECT codpj FROM proyecto
    MINUS
SELECT codpj FROM ventas
    WHERE       codpie IN (SELECT codpie FROM pieza WHERE color='Rojo')
            AND codpro IN (SELECT codpro FROM proveedor WHERE ciudad='Londres');
    -- // TODO: Cuál es más eficiente?
--

-- Ejemplo 3.15
-- Encontrar los proveedores (código y nombre) que suministran la pieza 'P1'.
SELECT codpro, nompro
    FROM proveedor
    WHERE codpro IN (SELECT codpro FROM ventas WHERE codpie='P1');
--

-- Ejemplo 3.16
-- Mostrar el código de los proveedores cuyo estatus sea igual al del proveedor 'S3'.
SELECT codpro
    FROM proveedor
    WHERE status = (SELECT status FROM proveedor WHERE codpro='S3'); -- Aquí puedo usar = porque sé que solo hay un resultado por ser codpro clave primaria.
--

-- Ejemplo 3.17
-- Muestra el código de las piezas cuyo peso es mayor que el peso de alguna pieza 'tornillo'.
SELECT codpie
    FROM pieza
    WHERE peso > ANY (SELECT peso FROM pieza WHERE nompie='tornillo');
--

-- Ejercicio 3.22
-- Muestra el código de las piezas cuyo peso es mayor que el peso de cualquier 'tornillo'.
SELECT codpie
    FROM pieza
    WHERE peso > ALL (SELECT peso FROM pieza WHERE nompie='tornillo');
--

-- Ejercicio 3.23
-- Encuentra las piezas con peso máximo. Compara esta solución con la obtenida en el ejercicio 3.14.
SELECT codpie FROM pieza
    WHERE peso > ALL (SELECT peso FROM pieza);
--