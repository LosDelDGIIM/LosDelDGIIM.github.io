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
DELETE FROM ventas;
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