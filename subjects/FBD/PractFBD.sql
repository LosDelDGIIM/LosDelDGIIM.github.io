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
-- Inserción de equipos
INSERT INTO equipos VALUES ('E01', 'Dragones', 'Madrid', 'Juan Perez', TO_DATE('01/01/2010','DD/MM/YYYY'));
INSERT INTO equipos VALUES ('E02', 'Fénix', 'Barcelona', 'Laura López', TO_DATE('15/02/2012','DD/MM/YYYY'));
INSERT INTO equipos VALUES ('E03', 'Tiburones', 'Valencia', 'Carlos Ruiz', TO_DATE('10/06/2015','DD/MM/YYYY'));
INSERT INTO equipos VALUES ('E04', 'Cóndores', 'Sevilla', 'Ana Martínez', TO_DATE('20/09/2018','DD/MM/YYYY'));

-- Inserción de jugadores
-- Dragones
INSERT INTO jugadores VALUES ('J01', 'E01', 'Pedro García');
INSERT INTO jugadores VALUES ('J02', 'E01', 'Luis Fernández');
INSERT INTO jugadores VALUES ('J03', 'E01', 'Sergio Sánchez');
INSERT INTO jugadores VALUES ('J04', 'E01', 'Diego Torres');
INSERT INTO jugadores VALUES ('J05', 'E01', 'Pablo Gómez');

-- Fénix
INSERT INTO jugadores VALUES ('J06', 'E02', 'Andrés López');
INSERT INTO jugadores VALUES ('J07', 'E02', 'Ricardo Díaz');
INSERT INTO jugadores VALUES ('J08', 'E02', 'Miguel Álvarez');
INSERT INTO jugadores VALUES ('J09', 'E02', 'Jorge Ramírez');
INSERT INTO jugadores VALUES ('J10', 'E02', 'David Vega');

-- Tiburones
INSERT INTO jugadores VALUES ('J11', 'E03', 'José Moreno');
INSERT INTO jugadores VALUES ('J12', 'E03', 'Hugo Prieto');
INSERT INTO jugadores VALUES ('J13', 'E03', 'Alberto Márquez');
INSERT INTO jugadores VALUES ('J14', 'E03', 'Carlos Romero');
INSERT INTO jugadores VALUES ('J15', 'E03', 'Gabriel Ortiz');

-- Cóndores
INSERT INTO jugadores VALUES ('J16', 'E04', 'Antonio Flores');
INSERT INTO jugadores VALUES ('J17', 'E04', 'Mario Castro');
INSERT INTO jugadores VALUES ('J18', 'E04', 'Iván Gómez');
INSERT INTO jugadores VALUES ('J19', 'E04', 'Felipe Herrera');
INSERT INTO jugadores VALUES ('J20', 'E04', 'Julio Jiménez');

-- Inserción de encuentros
INSERT INTO encuentros VALUES ('E01', 'E02', TO_DATE('01/01/2023','DD/MM/YYYY'), 80, 65);
INSERT INTO encuentros VALUES ('E01', 'E03', TO_DATE('08/01/2023','DD/MM/YYYY'), 75, 70);
INSERT INTO encuentros VALUES ('E01', 'E04', TO_DATE('15/01/2023','DD/MM/YYYY'), 85, 60);
INSERT INTO encuentros VALUES ('E02', 'E03', TO_DATE('22/01/2023','DD/MM/YYYY'), 60, 78);
INSERT INTO encuentros VALUES ('E02', 'E04', TO_DATE('29/01/2023','DD/MM/YYYY'), 70, 80);
INSERT INTO encuentros VALUES ('E03', 'E04', TO_DATE('05/02/2023','DD/MM/YYYY'), 88, 90);
INSERT INTO encuentros VALUES ('E02', 'E01', TO_DATE('12/02/2023','DD/MM/YYYY'), 62, 70);
INSERT INTO encuentros VALUES ('E03', 'E01', TO_DATE('19/02/2023','DD/MM/YYYY'), 68, 75);
INSERT INTO encuentros VALUES ('E04', 'E01', TO_DATE('26/02/2023','DD/MM/YYYY'), 55, 65);
INSERT INTO encuentros VALUES ('E04', 'E02', TO_DATE('05/03/2023','DD/MM/YYYY'), 82, 78);

-- Inserción de faltas (al menos una por encuentro)
INSERT INTO faltas VALUES ('J01', 'E01', 'E02', 3);
INSERT INTO faltas VALUES ('J06', 'E01', 'E02', 2);
INSERT INTO faltas VALUES ('J02', 'E01', 'E03', 1);
INSERT INTO faltas VALUES ('J11', 'E01', 'E03', 4);
INSERT INTO faltas VALUES ('J03', 'E01', 'E04', 2);
INSERT INTO faltas VALUES ('J16', 'E01', 'E04', 3);
INSERT INTO faltas VALUES ('J07', 'E02', 'E03', 5);
INSERT INTO faltas VALUES ('J13', 'E02', 'E03', 4);
INSERT INTO faltas VALUES ('J09', 'E02', 'E04', 2);
INSERT INTO faltas VALUES ('J19', 'E02', 'E04', 3);
INSERT INTO faltas VALUES ('J14', 'E03', 'E04', 2);
INSERT INTO faltas VALUES ('J18', 'E03', 'E04', 1);
INSERT INTO faltas VALUES ('J08', 'E02', 'E01', 3);
INSERT INTO faltas VALUES ('J05', 'E02', 'E01', 2);
INSERT INTO faltas VALUES ('J12', 'E03', 'E01', 4);
INSERT INTO faltas VALUES ('J04', 'E03', 'E01', 1);
INSERT INTO faltas VALUES ('J15', 'E04', 'E01', 3);
INSERT INTO faltas VALUES ('J10', 'E04', 'E01', 2);
INSERT INTO faltas VALUES ('J20', 'E04', 'E02', 1);
INSERT INTO faltas VALUES ('J17', 'E04', 'E02', 2);
--


-- Finalización Capítulo 2
DROP TABLE prueba1;
DROP TABLE serjefe;
DROP TABLE plantilla;
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
SELECT DISTINCT ciudad, codpie
    FROM (ventas NATURAL JOIN proyecto) NATURAL JOIN proveedor;
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
SELECT codpj FROM proyecto
    WHERE ciudad IN (SELECT ciudad FROM pieza);
--

-- Ejercicio 3.21
-- Encuentra los códigos de aquellos proyectos que no utilizan ninguna pieza roja que esté suministrada por un proveedor de Londres. 
SELECT codpj FROM proyecto
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
    -- Más corto
SELECT DISTINCT codpj FROM ventas
        WHERE       codpie NOT IN (SELECT codpie FROM pieza WHERE color='Rojo')
                AND codpro NOT IN (SELECT codpro FROM proveedor WHERE ciudad='Londres');
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
    WHERE peso >= ALL (SELECT peso FROM pieza WHERE nompie='tornillo');
--

-- Ejercicio 3.23
-- Encuentra las piezas con peso máximo. Compara esta solución con la obtenida en el ejercicio 3.14.
SELECT codpie FROM pieza
    WHERE peso >= ALL (SELECT peso FROM pieza);
--  Importante el = en el >=, porque si no, no se incluiría la pieza con el peso máximo.

-- Ejemplo 3.18
-- Mostrar el código de los proveedores que suministran todas las piezas. en AR
-- \pi_{codpro, codpie}(ventas) : \pi_{codpie}(pieza)

-- Ejercicio 3.24
-- Encontrar los códigos de las piezas suministradas a todos los proyectos localizados en Londres.
-- En AR: \pi_{codpie, codpj}(ventas) : \pi_{codpj}(\sigma_{ciudad='Londres'}(proyecto))
-- Enfoque Mixto: Not Exists y Resta
    -- Obtener los códigos de las piezas para los que no existe un proyecto de Londres que no las use.
    SELECT codpie FROM pieza
        WHERE NOT EXISTS (  SELECT codpj FROM proyecto WHERE ciudad='Londres'
                                MINUS
                            SELECT codpj FROM ventas WHERE ventas.codpie=pieza.codpie
        );
-- Enfoque Cálculo Relacional: Dos Not Exists
    -- Obetener los códigos de las piezas para los que no existe un proyecto de Londres para el que no existe una venta de esa pieza.
    SELECT codpie FROM pieza
        WHERE NOT EXISTS ( 
            SELECT codpj FROM proyecto WHERE ciudad='Londres'
                AND NOT EXISTS (
                    SELECT codpj FROM ventas
                        WHERE   ventas.codpie=pieza.codpie
                            AND ventas.codpj=proyecto.codpj
                )
        );
-- Enfoque Álgebra Relacional
    SELECT codpie FROM pieza
        MINUS
    SELECT codpie FROM (SELECT codpie, codpj
                        FROM pieza,
                             (SELECT codpj FROM proyecto WHERE ciudad='Londres')
                                MINUS
                        SELECT codpie, codpj FROM ventas);
--

-- Ejercicio 3.25 Encontrar aquellos proveedores que envían piezas procedentes de todas las ciudades donde hay un proyecto.
-- En AR:   \pi_{codpro, ciudad}(ventas \bowtie pieza) : \pi_{ciudad}(proyecto) 
-- Enfoque Mixto: Not Exists y Resta
    -- Obtener los códigos de los proveedores para los que no existe una ciudad de proyecto a la que no envíen piezas.
    SELECT DISTINCT codpro FROM ventas v1
        WHERE NOT EXISTS (  SELECT ciudad FROM proyecto
                                MINUS
                            SELECT ciudad FROM ventas v2 NATURAL JOIN pieza
                                WHERE v1.codpro=v2.codpro
        );
-- Enfoque Cálculo Relacional: Dos Not Exists
    -- Obtener los códigos de los proveedores para los que no existe una ciudad de proyecto para la cual no exista una venta de pieza.
    SELECT DISTINCT codpro FROM ventas v1
        WHERE NOT EXISTS (
            SELECT ciudad FROM proyecto
                WHERE NOT EXISTS (
                    SELECT * FROM ventas v2 NATURAL JOIN pieza
                        WHERE   v1.codpro=v2.codpro
                            AND proyecto.ciudad=pieza.ciudad
                )
        );
-- Enfoque Álgebra Relacional
    SELECT codpro FROM ventas
        MINUS
    SELECT codpro FROM (SELECT codpro, proyecto.ciudad
                        FROM proveedor, proyecto
                            MINUS
                        SELECT codpro, ciudad
                        FROM ventas NATURAL JOIN pieza
    );
--
-- // TODO: REVISAR División


-- Ejemplo 3.19 Mostrar el máximo, el mínimo y el total de unidades vendidas.
SELECT MAX(cantidad), MIN(cantidad), SUM(cantidad)
    FROM ventas;
SELECT MAX(DISTINCT cantidad), MIN(DISTINCT cantidad), SUM(DISTINCT cantidad)
    FROM ventas;
    -- En el segundo caso, MAX y MIN son iguales, pero SUM es menor puesto que no se suman los valores repetidos.
--

-- Ejercicio 3.26 Encontrar el número de envíos con más de 1000 unidades.
SELECT COUNT(*)
    FROM ventas
    WHERE cantidad>1000;
--

-- Ejercicio 3.27 Mostrar el máximo peso.
SELECT MAX(peso)
    FROM pieza;
--

-- Ejercicio 3.28 Mostrar el código de la pieza de máximo peso. Compara esta solución con las correspondientes de los ejercicios 3.14 y 3.23.
SELECT codpie FROM pieza
    WHERE peso = (SELECT MAX(peso) FROM pieza);
--

-- Ejercicio 3.29 Comprueba si la siguiente sentencia resuelve el ejercicio anterior.
SELECT codpie, MAX(peso)
    FROM pieza;
    -- No funciona, puesto que las funciones de agregacion no se pueden mezclar con columnas no agregadas.
--

-- Ejercicio 3.30 Muestra los códigos de proveedores que han hecho más de 3 envíos diferentes.
SELECT codpro
    FROM proveedor
    WHERE (SELECT COUNT(*) FROM ventas WHERE ventas.codpro=proveedor.codpro) > 3;
--

-- Ejemplo 3.20 Para cada proveedor, mostrar la cantidad de ventas realizadas y el máximo de unidades suministrado en una venta.
SELECT codpro, COUNT(*), MAX(cantidad)
    FROM ventas
    GROUP BY codpro;
--

-- Ejercicio 3.31 Mostrar la media de las cantidades vendidas por cada código de pieza junto con su nombre.
SELECT codpie, nompie, AVG(cantidad)
    FROM ventas NATURAL JOIN pieza
    GROUP BY codpie, nompie;
--

-- Ejercicio 3.32 Encontrar la cantidad media de ventas de la pieza 'P1' realizadas por cada proveedor.
SELECT codpro, AVG(cantidad)
    FROM ventas
    WHERE codpie='P1'
    GROUP BY codpro;
--

-- Ejercicio 3.33 Encontrar la cantidad total de cada pieza enviada a cada proyecto.
SELECT codpj, codpie, SUM(cantidad)
    FROM ventas
    GROUP BY codpj, codpie;
--

-- Ejemplo 3.21 Hallar la cantidad media de ventas realizadas por cada proveedor, indicando solamente los códigos de proveedores que han hecho más de 3 ventas.
SELECT codpro, AVG(cantidad)
    FROM ventas
    GROUP BY codpro
    HAVING COUNT(*) > 3;
--

-- Ejemplo 3.22 Mostrar la media de unidades vendidas de la pieza 'P1' realizadas por cada proveedor, indicando solamente la información de aquellos proveedores que han hecho entre 2 y 10 ventas.
SELECT codpro, AVG(cantidad)
    FROM ventas
    WHERE codpie='P1'
    GROUP BY codpro
    HAVING COUNT(*) BETWEEN 2 AND 10;
--

-- Ejemplo 3.23 y Ejercicio 3.34 Encuentra los nombres de proyectos y cantidad media de piezas que recibe por proveedor.
SELECT codpro, codpj, nompj, AVG(cantidad)
    FROM ventas NATURAL JOIN proyecto
    GROUP BY codpro, codpj, nompj
    ORDER BY nompj, codpro;
--

-- Ejercicio 3.35. Mostrar los nombres de proveedores tales que el total de sus ventas superen la cantidad de 1000 unidades.
SELECT codpro, nompro
    FROM proveedor
    WHERE (SELECT SUM(cantidad) FROM ventas WHERE codpro=ventas.codpro)>1000;
SELECT codpro, nompro
    FROM proveedor NATURAL JOIN ventas
    GROUP BY codpro, nompro
    HAVING SUM(cantidad) > 1000;
--

-- Ejemplo 3.24 Mostrar el proveedor que más ha vendido en total.
SELECT codpro, SUM(cantidad)
    FROM ventas
    GROUP BY codpro
    HAVING SUM(cantidad) = (SELECT MAX(SUM(cantidad))
                                FROM ventas v2
                                GROUP BY v2.codpro);
--

-- Ejercicio 3.36. Mostrar la pieza que más se ha vendido en total.
SELECT codpie, SUM(cantidad)
    FROM ventas
    GROUP BY codpie
    HAVING SUM(cantidad) = (SELECT MAX(SUM(cantidad))
                                FROM ventas v2
                                GROUP BY v2.codpie);
--

-- Ejemplo 3.25 Lista las fechas de las ventas en un formato día, mes y año con 4 dígitos.
SELECT TO_CHAR(fecha, 'dd-mm-yyyy')
    FROM ventas;
--

-- Ejemplo 3.26 Encontrar las ventas realizadas entre el 1 de enero de 2002 y el 31 de diciembre de 2004.
SELECT * FROM ventas
    WHERE fecha BETWEEN TO_DATE('01-01-2002', 'dd-mm-yyyy') AND TO_DATE('31-12-2004', 'dd-mm-yyyy');
--

-- Ejercicio 3.37 Comprueba que no funciona correctamente si las comparaciones de fechas se hacen con cadenas.
SELECT * FROM ventas
    WHERE fecha BETWEEN '01/01/2002' AND '31/12/2004';
--

-- Ejemplo 3.27 Mostrar las piezas que no han sido suministradas después del año 2001.
SELECT codpie
    FROM pieza
MINUS
SELECT codpie
    FROM ventas
    WHERE TO_NUMBER(TO_CHAR(fecha, 'yyyy')) > 2001;
    --WHERE fecha > TO_DATE('31-12-2001', 'dd-mm-yyyy');
    --
SELECT codpie
    FROM pieza
    WHERE NOT EXISTS (SELECT * FROM ventas
                            WHERE ventas.codpie=pieza.codpie
                            AND TO_NUMBER(TO_CHAR(fecha, 'yyyy')) > 2001);
--

-- Ejemplo 3.28 Agrupar los suministros de la tabla de ventas por años y sumar las cantidades totales anuales.
SELECT TO_NUMBER(TO_CHAR(fecha, 'yyyy')), SUM(cantidad)
    FROM ventas
    GROUP BY TO_NUMBER(TO_CHAR(fecha, 'yyyy'))
    ORDER BY TO_NUMBER(TO_CHAR(fecha, 'yyyy'));
--

-- Ejercicio 3.38 Encontrar la cantidad media de piezas suministradas cada mes.
SELECT TO_NUMBER(TO_CHAR(fecha, 'mm')), AVG(cantidad)
    FROM ventas
    GROUP BY TO_NUMBER(TO_CHAR(fecha, 'mm'))
    ORDER BY TO_NUMBER(TO_CHAR(fecha, 'mm'));

-- Ejemplo 3.29 Mostrar la información de todos los usuarios del sistema; la vista que nos interesa es ALL_USERS.
SELECT * FROM ALL_USERS
ORDER BY username;
--

-- Ejemplo 3.30 Queremos saber qué índices tenemos definidos sobre nuestras tablas, pero en esta ocasión vamos a consultar al propio catálogo para que nos muestre algunas de las vistas que contiene.
DESCRIBE DICTIONARY

SELECT * FROM DICTIONARY
    WHERE table_name
    LIKE '%INDEX%';
--

-- Ejercicio 3.39 ¿ Cuál es el nombre de la vista que tienes que consultar y qué campos te pueden interesar?
-- // TODO: Ej 39

-- Ejercicio 3.40 Muestra las tablas ventas a las que tienes acceso de consulta junto con el nombre del propietario y su número de identificación en el sistema.
SELECT table_name, owner, user_id
    FROM ALL_TABLES JOIN ALL_USERS ON owner=username
    WHERE lower(table_name) LIKE '%ventas%';
--

-- Ejercicio 3.41 Muestra todos tus objetos creados en el sistema. ¿Hay algo más que tablas?
-- // TODO: Ej 41

-- Ejercicio 3.42 Mostrar los códigos de aquellos proveedores que hayan superado las ventas totales realizadas por el proveedor 'S1'.
SELECT codpro
    FROM ventas
    GROUP BY codpro
    HAVING SUM(cantidad) > (SELECT SUM(cantidad) FROM ventas WHERE codpro='S1');
--

-- Ejercicio 3.43 Mostrar los mejores proveedores, entendiéndose como los que tienen mayores cantidades totales.
SELECT codpro, SUM(cantidad)
    FROM ventas
    GROUP BY codpro
    HAVING SUM(cantidad) = (SELECT MAX(SUM(cantidad)) FROM ventas GROUP BY codpro);
--

-- Ejercicio 3.44 Mostrar los proveedores que venden piezas a todas las ciudades de los proyectos a los que suministra 'S3', sin incluirlo.
-- AR: Ciudades de los proyectos a los que suministra 'S3':
        -- \pi_{ciudad}(\sigma_{codpro=S3}(ventas) \bowtie proyecto)
-- AR: Parejas de proveedores y ciudades a las que suministran:
        -- \pi_{codpro, ciudad}(\sigma_{codpro!=S3}(ventas) \bowtie proyecto)
-- AR: Proveedores que venden a todas las ciudades de los proyectos a los que suministra 'S3', sin incluirlo:
        -- \pi_{codpro, ciudad}(\sigma_{codpro!=S3}(ventas) \bowtie proyecto) : \pi_{ciudad}(\sigma_{codpro=S3}(ventas) \bowtie proyecto)
-- Enfoque Mixto: Not Exists y Resta
    -- Obtener los códigos de los proveedores para los que no existe una ciudad de proyecto al que suministra 'S3' a la cual no envíen piezas a ningún proyecto de esa ciudad.
    SELECT DISTINCT codpro
        FROM ventas v1
        WHERE v1.codpro != 'S3'
            AND NOT EXISTS (    SELECT ciudad
                                    FROM (ventas NATURAL JOIN proyecto)
                                    WHERE codpro='S3'
                                MINUS
                                SELECT ciudad
                                    FROM ventas v2 NATURAL JOIN proyecto
                                    WHERE v1.codpro=v2.codpro
                            );
-- Enfoque Cálculo Relacional: Dos Not Exists
    -- Obtener los códigos de los proveedores para los que no existe una ciudad de proyecto al que suministra 'S3' para la cual no exista una venta de ese proveedor a un proyecto de esa ciudad.
    SELECT DISTINCT codpro
        FROM ventas v1
        WHERE v1.codpro != 'S3'
            AND NOT EXISTS (
                SELECT ciudad
                    FROM (ventas NATURAL JOIN proyecto p1)
                    WHERE codpro='S3'
                        AND NOT EXISTS (
                            SELECT * FROM ventas v2 NATURAL JOIN proyecto p2
                                WHERE   v1.codpro=v2.codpro
                                    AND p1.ciudad=p2.ciudad
                        )
            );
-- Enfoque Álgebra Relacional
    SELECT codpro
        FROM ventas
        WHERE codpro != 'S3'
    MINUS
    SELECT codpro
        FROM (  SELECT codpro, ciudad
                    FROM (SELECT codpro FROM ventas WHERE codpro!='S3'),
                        (SELECT ciudad FROM proyecto NATURAL JOIN ventas WHERE codpro='S3')
                MINUS
                SELECT codpro, ciudad
                    FROM ventas NATURAL JOIN proyecto
                    WHERE codpro!='S3'
                    AND ciudad IN (SELECT ciudad FROM ventas NATURAL JOIN proyecto WHERE codpro='S3')
        );
--


-- Ejercicio 3.45 Encontrar aquellos proveedores que hayan hecho al menos diez pedidos.
SELECT codpro
    FROM ventas
    GROUP BY codpro
    HAVING COUNT(*) >= 10;
--

-- Ejercicio 3.46 Encontrar aquellos proveedores que venden todas las piezas suministradas por S1.
-- En AR: \pi_{codpro, codpie}(ventas) : \pi_{codpie}(\sigma_{codpro=S1}(ventas))
-- Enfoque Mixto: Not Exists y Resta
    -- Obtener los códigos de los proveedores para los que no existe una pieza suministrada por 'S1' a la que no envíen piezas.
    SELECT DISTINCT codpro
        FROM proveedor v1
        WHERE   codpro != 'S1'
                AND NOT EXISTS (  SELECT codpie
                                    FROM ventas
                                    WHERE codpro='S1'
                                MINUS
                                SELECT codpie
                                    FROM ventas v2
                                    WHERE v1.codpro=v2.codpro
                                );
-- Enfoque Cálculo Relacional: Dos Not Exists
    -- Obtener los códigos de los proveedores para los que no existe una pieza suministrada por 'S1' para la cual no exista una venta de ese proveedor.
    SELECT DISTINCT codpro
        FROM proveedor v1
        WHERE   codpro != 'S1'
                AND NOT EXISTS (
                    SELECT codpie
                        FROM ventas v3
                        WHERE codpro='S1'
                            AND NOT EXISTS (
                                SELECT * FROM ventas v2
                                    WHERE   v1.codpro=v2.codpro
                                        AND v3.codpie=v2.codpie
                            )
                );
-- Enfoque Álgebra Relacional
    SELECT codpro
        FROM proveedor
        WHERE codpro != 'S1'
    MINUS
    SELECT codpro
        FROM (  SELECT codpro, codpie
                    FROM proveedor,
                        (SELECT codpie FROM ventas WHERE codpro='S1')
                MINUS
                SELECT codpro, codpie
                    FROM ventas
        );

-- Ejercicio 3.47 Encontrar la cantidad total de piezas que ha vendido cada proveedor que cumple la condición de vender todas las piezas suministradas por S1.
-- La división está en el ejercicio anterior.
SELECT DISTINCT codpro, SUM(cantidad)
    FROM ventas v1
    WHERE   codpro != 'S1'
            AND NOT EXISTS (
                SELECT codpie
                    FROM ventas v3
                    WHERE codpro='S1'
                        AND NOT EXISTS (
                            SELECT * FROM ventas v2
                                WHERE   v1.codpro=v2.codpro
                                    AND v3.codpie=v2.codpie
                        )
            )
    GROUP BY codpro;

-- Ejercicio 3.48 Encontrar qué proyectos están suministrados por todos lo proveedores que suministran la pieza P3.
-- En AR: \pi_{codpj, codpro}(ventas) : \pi_{codpro}(\sigma_{codpie=P3}(ventas))
-- Enfoque Cálculo Relacional: Dos Not Exists
    -- Obtener los códigos de los proyectos para los que no existe un proveedor que suministre la pieza 'P3' para el cual no exista una venta entre ese proveedor y el proyecto.
    SELECT DISTINCT codpj
        FROM proyecto p1
        WHERE NOT EXISTS (
            SELECT codpro
                FROM ventas v1
                WHERE codpie='P3'
                    AND NOT EXISTS (
                        SELECT * FROM ventas v2
                            WHERE   v1.codpro=v2.codpro
                                AND p1.codpj=v2.codpj
                    )
        );
--

-- Ejercicio 3.49 Encontrar la cantidad media de piezas suministrada a aquellos proveedores que venden la pieza P3.
SELECT codpro, AVG(cantidad)
    FROM ventas
    WHERE codpie='P3'
    GROUP BY codpro;
--

-- Ejercicio 3.50 Queremos saber los nombres de tus índices y sobre qué tablas están montados. Indica además su propietario.
-- // TODO: Ejercicio 3.50

-- Ejercicio 3.51 Implementar el comando DESCRIBE para tu tabla ventas a través de una consulta a las vistas del catálogo.
-- // TODO: Ejercicio 3.51

-- Ejercicio 3.52 Mostrar para cada proveedor la media de productos suministrados cada año.
SELECT codpro, TO_NUMBER(TO_CHAR(fecha, 'yyyy')), AVG(cantidad)
    FROM ventas
    GROUP BY codpro, TO_NUMBER(TO_CHAR(fecha, 'yyyy'))
    ORDER BY codpro, TO_NUMBER(TO_CHAR(fecha, 'yyyy'));
--

-- Ejercicio 3.53 Encontrar todos los proveedores que venden una pieza roja.
SELECT DISTINCT codpro FROM ventas
    WHERE codpie IN (SELECT codpie FROM pieza WHERE color='Rojo');
SELECT DISTINCT codpro
    FROM ventas NATURAL JOIN pieza
    WHERE color='Rojo';
--

-- Ejercicio 3.54 Encontrar todos los proveedores que venden todas las piezas rojas.
-- AR: \pi_{codpro, codpie}(ventas) : \pi_{codpie}(\sigma_{color='Rojo'}(pieza))
-- Enfoque Cálculo Relacional: Dos Not Exists
    -- Obtener los códigos de los proveedores para los que no existe una pieza roja para la cual no exista una venta de ese proveedor.
    SELECT DISTINCT codpro
        FROM proveedor v1
        WHERE NOT EXISTS (
            SELECT codpie
                FROM pieza
                WHERE color='Rojo'
                    AND NOT EXISTS (
                        SELECT * FROM ventas v2
                            WHERE   v1.codpro=v2.codpro
                                AND pieza.codpie=v2.codpie
                    )
        );
--

-- Ejercicio 3.55 Encontrar todos los proveedores tales que todas las piezas que venden son rojas. 
-- De todos los proveedores, no nos sirven los que venden alguna pieza que no sea roja.
SELECT codpro
    FROM proveedor
MINUS
SELECT codpro
    FROM ventas NATURAL JOIN pieza
    WHERE color != 'Rojo';
--

-- Ejercicio 3.56 Encontrar el nombre de aquellos proveedores que venden más de una pieza roja.
SELECT codpro, nompro, COUNT(*)
    FROM ((proveedor NATURAL JOIN ventas) JOIN pieza ON ventas.codpie=pieza.codpie)
    WHERE color='Rojo'
    GROUP BY codpro, nompro
    HAVING COUNT(*) > 1;
SELECT codpro, nompro, COUNT(*)
    FROM ventas NATURAL JOIN proveedor
    WHERE codpie IN (SELECT codpie FROM pieza WHERE color='Rojo')
    GROUP BY codpro, nompro
    HAVING COUNT(*) > 1;
--

-- Ejercicio 3.57 Encontrar todos los proveedores que vendiendo todas las piezas rojas cumplen la condición de que todas sus ventas son de más de 10 unidades.
    -- Usamos el Ejercicio 3.54
SELECT codpro
    FROM proveedor v1 
    WHERE NOT EXISTS (
            SELECT codpie
                FROM pieza
                WHERE color='Rojo'
                    AND NOT EXISTS (
                        SELECT * FROM ventas v2
                            WHERE   v1.codpro=v2.codpro
                                AND pieza.codpie=v2.codpie
                    )
        )
MINUS   -- Importante. No nos quedamos con los que tengan UNA venta de más de 10 unidades, sino con los que tengan TODAS las ventas de más de 10 unidades.
SELECT codpro
    FROM ventas
    WHERE cantidad <= 10;

-- Otra opción. La restricción es sobre los candidatos.
SELECT codpro
    FROM (
        SELECT codpro FROM proveedor
        MINUS
        SELECT codpro FROM ventas WHERE cantidad <= 10
    ) v1
    WHERE NOT EXISTS (
            SELECT codpie
                FROM pieza
                WHERE color='Rojo'
                    AND NOT EXISTS (
                        SELECT * FROM ventas v2
                            WHERE   v1.codpro=v2.codpro
                                AND pieza.codpie=v2.codpie
                    )
        );
--


-- Ejercicio 3.58 Coloca el status igual a 1 a aquellos proveedores que solo suministran la pieza P1.
-- Los proveedores elegidos son S6 y S7
SELECT codpro FROM ventas
MINUS
SELECT codpro FROM ventas
    WHERE codpie != 'P1';

-- Sus status son: S6 -> 6 y S7 -> 7 (necesario para deshacer la consulta)
SELECT codpro, status FROM proveedor
    WHERE codpro IN (
        SELECT codpro FROM ventas
        MINUS
        SELECT codpro FROM ventas
            WHERE codpie != 'P1'
    );

-- Consulta pedida:
UPDATE proveedor
    SET status = 1
    WHERE codpro IN (
        SELECT codpro FROM ventas
        MINUS
        SELECT codpro FROM ventas
            WHERE codpie != 'P1'
    );

-- Deshacer la consulta:
UPDATE proveedor
    SET status = 6
    WHERE codpro = 'S6';
UPDATE proveedor
    SET status = 7
    WHERE codpro = 'S7';
--

-- Ejercicio 3.59 Encuentra, de entre las piezas que no se han vendido en septiembre de 2009, las ciudades de aquellas que se han vendido en mayor cantidad durante Agosto de ese mismo año.
-- Piezas, junto a la cantidad que se han vendido en Agosto de 2009:
SELECT codpie, SUM(cantidad)
    FROM ventas
    WHERE TO_CHAR(fecha, 'MM/YYYY') = '08/2009'
    GROUP BY codpie;
-- Piezas que no se han vendido en septiembre de 2009:
SELECT codpie FROM pieza
MINUS 
SELECT codpie FROM ventas
    WHERE TO_CHAR(fecha, 'MM/YYYY') = '09/2009';
-- Piezas que no se han vendido en septiembre de 2009, junto a la cantidad que se han vendido en Agosto de 2009:
SELECT codpie, SUM(cantidad)
    FROM (
        SELECT codpie FROM pieza
        MINUS 
        SELECT codpie FROM ventas
            WHERE TO_CHAR(fecha, 'MM/YYYY') = '09/2009'
    )  
    NATURAL JOIN ventas
    WHERE TO_CHAR(fecha, 'MM/YYYY') = '08/2009'
    GROUP BY codpie;
-- CONSULTA. Ciudades de aquellas piezas que no se han vendido en septiembre de 2009 que se han vendido en mayor cantidad durante Agosto de 2009:
SELECT DISTINCT codpie, ciudad
    FROM (
        SELECT codpie FROM pieza
        MINUS 
        SELECT codpie FROM ventas
            WHERE TO_CHAR(fecha, 'MM/YYYY') = '09/2009'
    )  
    NATURAL JOIN pieza NATURAL JOIN ventas
    WHERE cantidad >= ALL (
        SELECT SUM(cantidad)
            FROM (
                SELECT codpie FROM pieza
                MINUS 
                SELECT codpie FROM ventas
                    WHERE TO_CHAR(fecha, 'MM/YYYY') = '09/2009'
            )  
            NATURAL JOIN ventas
            WHERE TO_CHAR(fecha, 'MM/YYYY') = '08/2009'
            GROUP BY codpie
    );
-- 2ª Opción. Obliga a que se hayan vendido en Agosto 2009
SELECT DISTINCT codpie, ciudad, SUM(cantidad) AS TotalAgosto
    FROM (
        SELECT codpie FROM pieza
        MINUS 
        SELECT codpie FROM ventas
            WHERE TO_CHAR(fecha, 'MM/YYYY') = '09/2009'
    )  
    NATURAL JOIN pieza NATURAL JOIN ventas
    WHERE TO_CHAR(fecha, 'MM/YYYY') = '08/2009'
    GROUP BY codpie, ciudad
    HAVING SUM(cantidad) >= ALL (
        SELECT SUM(cantidad)
            FROM (
                SELECT codpie FROM pieza
                MINUS 
                SELECT codpie FROM ventas
                    WHERE TO_CHAR(fecha, 'MM/YYYY') = '09/2009'
            )  
            NATURAL JOIN ventas
            WHERE TO_CHAR(fecha, 'MM/YYYY') = '08/2009'
            GROUP BY codpie
    );


-- Base de Datos del Baloncesto
-- Ejercicio 3.60 Muestra la información disponible acerca de los encuentros de liga.
SELECT * FROM encuentros;
--

-- Ejercicio 3.61 Muestra los nombres de los equipos y de los jugadores jugadores ordenados alfabéticamente.
SELECT nombreJ FROM jugadores
    ORDER BY nombreJ;
SELECT nombreE FROM equipos
    ORDER BY nombreE;
-- Otra opción, todo junto:
    SELECT nombreJ AS nombre FROM jugadores
UNION
    SELECT nombreE AS nombre FROM equipos
ORDER BY nombre;

-- Ejercicio 3.62 Muestra los jugadores que no tienen ninguna falta.
SELECT codJ FROM jugadores
MINUS
SELECT codJ FROM faltas
    WHERE num > 0;
--

-- Ejercicio 3.63 Muestra los compañeros de equipo del jugador que tiene por código x (codJ='x') y donde x es uno elegido por ti.
SELECT codJ, nombreJ
    FROM jugadores
    WHERE   codE = (SELECT codE FROM jugadores WHERE codJ='J01')
        AND codJ != 'J01';
--

-- Ejercicio 3.64 Muestra los jugadores y la localidad donde juegan (la de sus equipos).
SELECT codJ, nombreJ, localidad
    FROM jugadores NATURAL JOIN equipos;
--

-- Ejercicio 3.65 Muestra todos los encuentros posibles de la liga.
SELECT e1.codE AS local, e2.codE AS visitante
    FROM equipos e1, equipos e2
    WHERE e1.codE != e2.codE;
--

-- Ejercicio 3.66 Muestra los equipos que han ganado algún encuentro jugando como local.
SELECT DISTINCT ELocal
    FROM encuentros
    WHERE PLocal > PVisitante;
--

-- Ejercicio 3.67 Muestra los equipos que han ganado algún encuentro.
SELECT ELocal AS equipo FROM encuentros
    WHERE PLocal > PVisitante
UNION
SELECT EVisitante AS equipo FROM encuentros
    WHERE PVisitante > PLocal;
-- Otra opción, más larga:
SELECT CodE FROM equipos
    WHERE CodE IN (
        SELECT ELocal FROM encuentros
            WHERE PLocal > PVisitante
    )
    OR CodE IN (
        SELECT EVisitante FROM encuentros
            WHERE PVisitante > PLocal
    );
--

-- Ejercicio 3.68 Muestra los equipos que cumplen que todos los encuentros que han ganado lo han hecho como equipo local.
-- Todos los equipos, menos los que han ganado como visitante
SELECT CodE FROM equipos
    MINUS
SELECT EVisitante FROM encuentros
    WHERE PLocal < PVisitante;

-- Ejercicio 3.69 Muestra los equipos que han ganado todos los encuentros jugando como equipo local.
-- Todos los equipos, menos los que han perdido o empatado como local
SELECT CodE FROM equipos
    MINUS
SELECT ELocal FROM encuentros
    WHERE PLocal <= PVisitante;
--

-- Ejercicio 3.70 Muestra los encuentros que faltan para terminar la liga suponiendo que en la tabla Encuentros solo se almacenan los encuentros celebrados hasta la fecha
-- A todos los encuentros posibles, le quito los que ya se han jugado
SELECT e1.codE AS local, e2.codE AS visitante
    FROM equipos e1, equipos e2
    WHERE e1.codE != e2.codE
MINUS
SELECT ELocal AS local, EVisitante AS visitante
    FROM encuentros;
--

-- Ejercicio 3.71 Muestra los encuentros que tienen lugar en la misma localidad.
-- (Entendemos que se refiere a encuentros de equipos de la misma localidad)
SELECT ELocal, EVisitante, l.localidad
    FROM encuentros JOIN equipos l ON ELocal=l.codE
                    JOIN equipos v ON EVisitante=v.codE
    WHERE l.localidad = v.localidad;
--

-- Ejercicio 3.72 Para cada equipo muestra cantidad de encuentros que ha disputado como local.
SELECT ELocal, COUNT(*)
    FROM encuentros
    GROUP BY ELocal;
--

-- Ejercicio 3.73 Muestra los encuentros en los que se alcanzó mayor diferencia.
SELECT * FROM encuentros
    WHERE abs(PLocal - PVisitante)=(SELECT MAX(abs(PLocal - PVisitante)) FROM encuentros);
--

-- Ejercicio 3.74 Muestra los jugadores que no han superado 3 faltas acumuladas.
SELECT CodJ FROM jugadores
MINUS
SELECT CodJ FROM faltas
    GROUP BY CodJ
    HAVING (SUM(num)>3);
-- Si queremos mostrar las faltas que tienen (no saldrán los que tienen 0 faltas)
SELECT CodJ, SUM(num)
    FROM faltas
    GROUP BY CodJ
    HAVING (SUM(num)<=3);
--

-- Ejercicio 3.75 Muestra los equipos con mayores puntuaciones en los partidos jugados fuera de casa.
SELECT EVisitante, PVisitante FROM encuentros
    WHERE PVisitante=(SELECT MAX(PVisitante) FROM encuentros);
--

-- Ejercicio 3.76 Muestra la cantidad de victorias de cada equipo, jugando como local o como visitante.
SELECT equipo, COUNT(*)
    FROM
        (SELECT ELocal AS equipo
            FROM encuentros
            WHERE PLocal > PVisitante
        UNION ALL
        SELECT EVisitante AS equipo
            FROM encuentros
            WHERE PLocal < PVisitante)
    GROUP BY equipo;
--

-- Ejercicio 3.77 Muestra el equipo con mayor número de victorias.
SELECT equipo, COUNT(*)
    FROM
        (SELECT ELocal AS equipo
            FROM encuentros
            WHERE PLocal > PVisitante
        UNION ALL
        SELECT EVisitante AS equipo
            FROM encuentros
            WHERE PLocal < PVisitante)
    GROUP BY equipo
    HAVING COUNT(*)=(SELECT MAX(COUNT(*)) FROM
            (SELECT ELocal AS equipo
                FROM encuentros
                WHERE PLocal > PVisitante
            UNION ALL
            SELECT EVisitante AS equipo
                FROM encuentros
                WHERE PLocal < PVisitante)
        GROUP BY equipo
    );
--

-- Ejercicio 3.78 Muestra el promedio de puntos por equipo en los encuentros de ida.
SELECT EVisitante, AVG(PVisitante)
    FROM encuentros
    GROUP BY EVisitante;
--

-- Ejercicio 3.79 Muestra el equipo con mayor número de puntos en total de los encuentros jugados.
SELECT equipo, SUM(puntos)
    FROM
        (SELECT ELocal AS equipo, PLocal AS puntos
            FROM encuentros
        UNION ALL
        SELECT EVisitante AS equipo, PVisitante AS puntos
            FROM encuentros
        )
    GROUP BY equipo
    HAVING SUM(puntos)=(SELECT MAX(SUM(puntos)) FROM
            (SELECT ELocal AS equipo, PLocal AS puntos
                FROM encuentros
            UNION ALL
            SELECT EVisitante AS equipo, PVisitante AS puntos
                FROM encuentros)
        GROUP BY equipo
    );
--


/*--------------------------------------------------------------
    Capítulo 4: Definición del nivel externo de un DBMS
*/--------------------------------------------------------------

-- Ejemplo 4.1 Elaborar una vista con el conjunto de suministros realizados solo con integrantes procedentes de Paris.
CREATE VIEW VentasParis (codpro,codpie,codpj,cantidad,fecha) AS
    SELECT codpro,codpie,codpj,cantidad,fecha
        FROM ventas
        WHERE (codpro,codpie,codpj) IN
            (
                SELECT codpro,codpie,codpj
                    FROM proveedor,pieza,proyecto
                    WHERE proveedor.ciudad='Paris'
                        AND pieza.ciudad='Paris'
                        AND proyecto.ciudad='Paris'
            );
DROP VIEW VentasParis;
-- Segunda Opción, haciendo uso del NATURAL JOIN uniendo también por la ciudad
CREATE VIEW VentasParis (codpro,codpie,codpj,cantidad,fecha) AS
    SELECT codpro,codpie,codpj,cantidad,fecha
        FROM ventas NATURAL JOIN proveedor NATURAL JOIN pieza NATURAL JOIN proyecto
        WHERE ciudad='Paris';

SELECT * FROM VentasParis;
DROP VIEW VentasParis;
--

-- Ejemplo 4.2 Elaborar una vista con el conjunto de piezas procedentes de Londres, prescindiendo del atributo ciudad de la tabla original. Después, intenta hacer una inserción en la vista.
CREATE VIEW PiezasLondres (codpie,nompie,color,peso) AS
    SELECT codpie,nompie,color,peso
        FROM pieza
        WHERE ciudad='Londres';
INSERT INTO PiezasLondres VALUES ('P9','Pieza 9','rojo',90);

SELECT * FROM PiezasLondres WHERE codpie='P9';
SELECT * FROM pieza WHERE codpie='P9';
-- Notemos que, efectivamente, se puede añadir. No obstante, como la vista no tiene el atributo ciudad, este se pone a Null, por lo que no pertenecerá a Londres, y por tanto tampoco a la vista PiezasLondres.
DELETE FROM PiezasLondres WHERE codpie='P9';
DROP VIEW PiezasLondres;

-- Ejercicio 4.1 Crear una vista con los proveedores de Londres. ¿Qué sucede si insertamos en dicha vista la tupla (’S7’,’Jose Suarez’,3,’Granada’)?. (Buscar en [3] la cláusula WITH CHECK OPTION ).
CREATE OR REPLACE VIEW ProveedoresLondres (codpro,nompro,status, ciudad) AS
    SELECT codpro,nompro,status,ciudad
        FROM proveedor
        WHERE ciudad='Londres';
-- INSERT INTO ProveedoresLondres VALUES ('S7','Jose Suarez',3,'Granada');
-- Nos da error, puesto que el proveedor S7 ya existe. Que sea de Granada no da problema, probemos con S8
INSERT INTO ProveedoresLondres VALUES ('S8','Jose Suarez',3,'Granada');
SELECT * FROM ProveedoresLondres WHERE codpro='S8';
SELECT * FROM proveedor WHERE codpro='S8';
DELETE FROM Proveedor WHERE codpro='S8';
-- Vemos que, efectivamente se añade, pero no se incluye a la vista, solo a la tabla. Para limitar esto, usamos WITH CHECK OPTION
CREATE OR REPLACE VIEW ProveedoresLondres (codpro,nompro,status,ciudad) AS
    SELECT codpro,nompro,status,ciudad
        FROM proveedor
        WHERE ciudad='Londres'
    WITH CHECK OPTION;
-- INSERT INTO ProveedoresLondres VALUES ('S8','Jose Suarez',3,'Granada');
-- Nos da error, puesto que no cumple la condición de la vista.
INSERT INTO ProveedoresLondres VALUES ('S8','Jose Suarez',3,'Londres');
DELETE FROM ProveedoresLondres WHERE codpro='S8';
DROP VIEW ProveedoresLondres;
--

-- Ejercicio 4.2 Crear una vista con los nombres de los proveedores y sus ciudades. Inserta sobre ella una tupla y explica cuál es el problema que se plantea. ¿Habría problemas de actualización?
CREATE OR REPLACE VIEW ProveedoresCiudades (nompro, ciudad) AS
    SELECT nompro, ciudad
        FROM proveedor;
-- INSERT INTO ProveedoresCiudades VALUES ('Jose Suarez','Granada');
-- ORA-01400: cannot insert NULL into ("X7446815"."PROVEEDOR"."CODPRO")
-- No nos deja, ya que no conoce qué valor poner en el campo codpro, que no está en la vista.
DROP VIEW ProveedoresCiudades;
--

-- Ejercicio 4.3 Crear una vista donde aparezcan el código de proveedor, el nombre de proveedor y el código del proyecto tales que la pieza sumistrada sea gris. Sobre esta vista realiza alguna consulta y enumera todos los motivos por los que sería imposible realizar una inserción
CREATE OR REPLACE VIEW ProveedoresProyectosGris (codpro, nompro, codpj) AS
    SELECT codpro, nompro, codpj
        FROM proveedor NATURAL JOIN ventas JOIN pieza ON ventas.codpie=pieza.codpie
        WHERE color='Gris';
SELECT * FROM ProveedoresProyectosGris;
DROP VIEW ProveedoresProyectosGris;
-- No puedo hacer insercióones, ya que no proviene de una única tabla.

COMMIT;


/*--------------------------------------------------------------------------------------
    Capítulo 5: Introducción a la administración: el catálogo y gestión de privilegios
*/--------------------------------------------------------------------------------------
-- Tabla 5.1
SELECT * FROM DICTIONARY;
SELECT * FROM USER_CATALOG;
SELECT * FROM USER_CONSTRAINTS;
SELECT * FROM USER_CONS_COLUMNS;
SELECT * FROM USER_ROLE_PRIVS;
SELECT * FROM USER_SYS_PRIVS;
SELECT * FROM USER_TAB_COLUMNS;
SELECT * FROM USER_TABLES;
SELECT * FROM USER_VIEWS;
SELECT * FROM USER_INDEXES;
SELECT * FROM USER_CLUSTERS;
SELECT * FROM USER_TABLESPACES;
SELECT * FROM USER_USERS;
SELECT * FROM ALL_USERS;
SELECT * FROM ALL_TABLES;
SELECT * FROM ALL_VIEWS;

-- Ejercicio 5.1 Ver la descripción de la vista del catálogo USER_TABLES.
SELECT * FROM ALL_VIEWS
    WHERE VIEW_NAME='USER_TABLES';
SELECT * FROM USER_TABLES;
--

-- Ejercicio 5.2
-- // TODO: Ejercicio 5.2
--