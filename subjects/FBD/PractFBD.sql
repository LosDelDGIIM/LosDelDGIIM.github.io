---------------------------- 21 / 11 / 2024 ---------------------------
SELECT table_name FROM user_tables;

DROP TABLE prueba1;
CREATE TABLE prueba1 (
    cad char(3),
    n int,
    x float
);

-- Ejercicio 1.1
DESCRIBE prueba1;
--

-- Ejemplo 1
DROP TABLE plantilla;
CREATE TABLE plantilla(
    dni varchar2(9),
    nombre varchar2(15),
    estadocivil varchar2(10)
        CHECK (estadocivil IN ('soltero', 'casado', 'divorciado', 'viudo')),
    fechaalta date,
    PRIMARY KEY (dni)
);
--

-- Ejercicio 1.2
-- Busqueda en Internet
--

DROP TABLE serjefe;
CREATE TABLE serjefe(
    dnijefe REFERENCES plantilla(dni),
    dnitrabajador REFERENCES plantilla(dni) PRIMARY KEY
);

-- Ejercicio 1.3
-- Dibujo de un diagrama E/R
--

-- Ejercicio 1.4
DROP TABLE prueba1;
--

-- Ejercicio 1.5
ALTER TABLE plantilla ADD (fechabaja date);
--

-- Seccion 1.6.1
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
DROP TABLE ventas;
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
DROP TABLE equipos;
CREATE TABLE equipos(
    codE VARCHAR2(3) CONSTRAINT codE_clave_primaria PRIMARY KEY,
    nombreE VARCHAR2(20) CONSTRAINT nombreE_no_nulo NOT NULL CONSTRAINT nombreE_unico UNIQUE,
    localidad VARCHAR2(20) CONSTRAINT localidad_no_nulo NOT NULL,
    entrenador VARCHAR2(20) CONSTRAINT entrenador_no_nulo NOT NULL,
    fecha_crea DATE CONSTRAINT fecha_crea_no_nulo NOT NULL
);

DROP TABLE jugadores;
CREATE TABLE jugadores(
    codJ VARCHAR2(3) CONSTRAINT codJ_clave_primaria PRIMARY KEY,
    codE  CONSTRAINT codE_no_nulo NOT NULL CONSTRAINT codE_clave_externa_equipos
        REFERENCES equipos(codE),
    nombreJ VARCHAR2(20) CONSTRAINT nombreJ_no_nulo NOT NULL
);

DROP TABLE encuentros;
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

DROP TABLE faltas;
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