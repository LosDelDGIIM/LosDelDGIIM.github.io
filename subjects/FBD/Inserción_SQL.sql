-- Inserción de equipos
DELETE FROM faltas;
DELETE FROM encuentros;
DELETE FROM jugadores;
DELETE FROM equipos;
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
--------------------------------------------------

-- Coches --
DELETE FROM repara;
DELETE FROM vehiculo;
DELETE FROM modelo;
DELETE FROM mecanico;
-- Insertar datos en la tabla modelo
INSERT INTO modelo (id_modelo, marca, descripcion) VALUES ('M01', 'Toyota', 'Corolla');
INSERT INTO modelo (id_modelo, marca, descripcion) VALUES ('M02', 'Honda', 'Civic');
INSERT INTO modelo (id_modelo, marca, descripcion) VALUES ('M03', 'Ford', 'Focus');
INSERT INTO modelo (id_modelo, marca, descripcion) VALUES ('M04', 'Chevrolet', 'Cruze');
INSERT INTO modelo (id_modelo, marca, descripcion) VALUES ('M05', 'BMW', 'Series 3');

-- Insertar datos en la tabla mecanico
INSERT INTO mecanico (id_mecanico, nombre_mecanico, cargo, salario, fecha_nacimiento) VALUES ('ME1', 'Juan', 'Senior', 3000, TO_DATE('1990-01-01', 'YYYY-MM-DD'));
INSERT INTO mecanico (id_mecanico, nombre_mecanico, cargo, salario, fecha_nacimiento) VALUES ('ME2', 'Ana', 'Junior', 2000, TO_DATE('1995-02-15', 'YYYY-MM-DD'));
INSERT INTO mecanico (id_mecanico, nombre_mecanico, cargo, salario, fecha_nacimiento) VALUES ('ME3', 'Carlos', 'Senior', 3200, TO_DATE('1985-06-10', 'YYYY-MM-DD'));
INSERT INTO mecanico (id_mecanico, nombre_mecanico, cargo, salario, fecha_nacimiento) VALUES ('ME4', 'Maria', 'Junior', 2100, TO_DATE('1992-09-20', 'YYYY-MM-DD'));
INSERT INTO mecanico (id_mecanico, nombre_mecanico, cargo, salario, fecha_nacimiento) VALUES ('ME5', 'Luis', 'Mid', 2800, TO_DATE('1980-12-25', 'YYYY-MM-DD'));
INSERT INTO mecanico (id_mecanico, nombre_mecanico, cargo, salario, fecha_nacimiento) VALUES ('ME6', 'Sofia', 'Mid', 2700, TO_DATE('1988-08-15', 'YYYY-MM-DD'));

INSERT INTO vehiculo (matricula, id_modelo, fecha_matriculacion) VALUES ('123ABC', 'M01', TO_DATE('2022-03-01', 'YYYY-MM-DD'));
INSERT INTO vehiculo (matricula, id_modelo, fecha_matriculacion) VALUES ('234DEF', 'M02', TO_DATE('2021-06-15', 'YYYY-MM-DD'));
INSERT INTO vehiculo (matricula, id_modelo, fecha_matriculacion) VALUES ('345GHI', 'M03', TO_DATE('2020-11-23', 'YYYY-MM-DD'));
INSERT INTO vehiculo (matricula, id_modelo, fecha_matriculacion) VALUES ('456JKL', 'M04', TO_DATE('2019-07-12', 'YYYY-MM-DD'));
INSERT INTO vehiculo (matricula, id_modelo, fecha_matriculacion) VALUES ('567MNO', 'M05', TO_DATE('2018-09-30', 'YYYY-MM-DD'));
INSERT INTO vehiculo (matricula, id_modelo, fecha_matriculacion) VALUES ('678PQR', 'M01', TO_DATE('2020-04-22', 'YYYY-MM-DD'));
INSERT INTO vehiculo (matricula, id_modelo, fecha_matriculacion) VALUES ('789STU', 'M02', TO_DATE('2021-12-10', 'YYYY-MM-DD'));
INSERT INTO vehiculo (matricula, id_modelo, fecha_matriculacion) VALUES ('890VWX', 'M03', TO_DATE('2023-08-05', 'YYYY-MM-DD'));
INSERT INTO vehiculo (matricula, id_modelo, fecha_matriculacion) VALUES ('901YZA', 'M04', TO_DATE('2019-05-15', 'YYYY-MM-DD'));
INSERT INTO vehiculo (matricula, id_modelo, fecha_matriculacion) VALUES ('012BCD', 'M05', TO_DATE('2017-07-20', 'YYYY-MM-DD'));
INSERT INTO vehiculo (matricula, id_modelo, fecha_matriculacion) VALUES ('345EFG', 'M01', TO_DATE('2020-01-25', 'YYYY-MM-DD'));
INSERT INTO vehiculo (matricula, id_modelo, fecha_matriculacion) VALUES ('456HIJ', 'M02', TO_DATE('2022-10-30', 'YYYY-MM-DD'));
INSERT INTO vehiculo (matricula, id_modelo, fecha_matriculacion) VALUES ('567KLM', 'M03', TO_DATE('2021-02-18', 'YYYY-MM-DD'));
INSERT INTO vehiculo (matricula, id_modelo, fecha_matriculacion) VALUES ('678NOP', 'M04', TO_DATE('2018-06-11', 'YYYY-MM-DD'));
INSERT INTO vehiculo (matricula, id_modelo, fecha_matriculacion) VALUES ('789QRS', 'M05', TO_DATE('2020-03-05', 'YYYY-MM-DD'));
INSERT INTO vehiculo (matricula, id_modelo, fecha_matriculacion) VALUES ('890TUV', 'M01', TO_DATE('2019-09-23', 'YYYY-MM-DD'));
INSERT INTO vehiculo (matricula, id_modelo, fecha_matriculacion) VALUES ('901WXY', 'M02', TO_DATE('2022-05-16', 'YYYY-MM-DD'));
INSERT INTO vehiculo (matricula, id_modelo, fecha_matriculacion) VALUES ('012ZAB', 'M03', TO_DATE('2021-07-19', 'YYYY-MM-DD'));
INSERT INTO vehiculo (matricula, id_modelo, fecha_matriculacion) VALUES ('123CDE', 'M04', TO_DATE('2023-01-01', 'YYYY-MM-DD'));
INSERT INTO vehiculo (matricula, id_modelo, fecha_matriculacion) VALUES ('234FGH', 'M05', TO_DATE('2020-06-25', 'YYYY-MM-DD'));
INSERT INTO vehiculo (matricula, id_modelo, fecha_matriculacion) VALUES ('345IJK', 'M01', TO_DATE('2021-11-13', 'YYYY-MM-DD'));
INSERT INTO vehiculo (matricula, id_modelo, fecha_matriculacion) VALUES ('456LMN', 'M02', TO_DATE('2022-03-14', 'YYYY-MM-DD'));
INSERT INTO vehiculo (matricula, id_modelo, fecha_matriculacion) VALUES ('567OPQ', 'M03', TO_DATE('2019-10-18', 'YYYY-MM-DD'));
INSERT INTO vehiculo (matricula, id_modelo, fecha_matriculacion) VALUES ('678RST', 'M04', TO_DATE('2020-12-07', 'YYYY-MM-DD'));
INSERT INTO vehiculo (matricula, id_modelo, fecha_matriculacion) VALUES ('789UVW', 'M05', TO_DATE('2021-09-02', 'YYYY-MM-DD'));
INSERT INTO vehiculo (matricula, id_modelo, fecha_matriculacion) VALUES ('890XYZ', 'M01', TO_DATE('2018-08-15', 'YYYY-MM-DD'));
INSERT INTO vehiculo (matricula, id_modelo, fecha_matriculacion) VALUES ('901ABC', 'M02', TO_DATE('2023-06-09', 'YYYY-MM-DD'));
INSERT INTO vehiculo (matricula, id_modelo, fecha_matriculacion) VALUES ('012DEF', 'M03', TO_DATE('2020-02-04', 'YYYY-MM-DD'));

-- Insertar datos en la tabla repara
-- 50 Reparaciones distintas
INSERT INTO repara (id_mecanico, matricula, fecha, numero_horas) VALUES ('ME1', '123ABC', TO_DATE('2023-01-15', 'YYYY-MM-DD'), 5);
INSERT INTO repara (id_mecanico, matricula, fecha, numero_horas) VALUES ('ME2', '123ABC', TO_DATE('2023-06-15', 'YYYY-MM-DD'), 3);
INSERT INTO repara (id_mecanico, matricula, fecha, numero_horas) VALUES ('ME3', '123ABC', TO_DATE('2024-01-10', 'YYYY-MM-DD'), 4);
INSERT INTO repara (id_mecanico, matricula, fecha, numero_horas) VALUES ('ME4', '234DEF', TO_DATE('2023-03-20', 'YYYY-MM-DD'), 2);
INSERT INTO repara (id_mecanico, matricula, fecha, numero_horas) VALUES ('ME5', '234DEF', TO_DATE('2024-02-01', 'YYYY-MM-DD'), 3);
INSERT INTO repara (id_mecanico, matricula, fecha, numero_horas) VALUES ('ME6', '345GHI', TO_DATE('2022-12-05', 'YYYY-MM-DD'), 6);
INSERT INTO repara (id_mecanico, matricula, fecha, numero_horas) VALUES ('ME1', '456JKL', TO_DATE('2023-07-14', 'YYYY-MM-DD'), 4);
INSERT INTO repara (id_mecanico, matricula, fecha, numero_horas) VALUES ('ME2', '567MNO', TO_DATE('2024-01-18', 'YYYY-MM-DD'), 5);
INSERT INTO repara (id_mecanico, matricula, fecha, numero_horas) VALUES ('ME3', '678PQR', TO_DATE('2022-11-30', 'YYYY-MM-DD'), 2);
INSERT INTO repara (id_mecanico, matricula, fecha, numero_horas) VALUES ('ME4', '789STU', TO_DATE('2023-04-22', 'YYYY-MM-DD'), 3);
INSERT INTO repara (id_mecanico, matricula, fecha, numero_horas) VALUES ('ME5', '890VWX', TO_DATE('2022-08-10', 'YYYY-MM-DD'), 4);
INSERT INTO repara (id_mecanico, matricula, fecha, numero_horas) VALUES ('ME6', '901YZA', TO_DATE('2023-05-15', 'YYYY-MM-DD'), 6);
INSERT INTO repara (id_mecanico, matricula, fecha, numero_horas) VALUES ('ME1', '012BCD', TO_DATE('2024-02-12', 'YYYY-MM-DD'), 3);
INSERT INTO repara (id_mecanico, matricula, fecha, numero_horas) VALUES ('ME2', '345EFG', TO_DATE('2023-09-05', 'YYYY-MM-DD'), 5);
INSERT INTO repara (id_mecanico, matricula, fecha, numero_horas) VALUES ('ME3', '456HIJ', TO_DATE('2023-03-17', 'YYYY-MM-DD'), 4);
INSERT INTO repara (id_mecanico, matricula, fecha, numero_horas) VALUES ('ME4', '567KLM', TO_DATE('2024-01-08', 'YYYY-MM-DD'), 2);
INSERT INTO repara (id_mecanico, matricula, fecha, numero_horas) VALUES ('ME5', '678NOP', TO_DATE('2023-06-21', 'YYYY-MM-DD'), 7);
INSERT INTO repara (id_mecanico, matricula, fecha, numero_horas) VALUES ('ME6', '789QRS', TO_DATE('2022-10-14', 'YYYY-MM-DD'), 4);
INSERT INTO repara (id_mecanico, matricula, fecha, numero_horas) VALUES ('ME1', '890TUV', TO_DATE('2023-01-18', 'YYYY-MM-DD'), 3);
INSERT INTO repara (id_mecanico, matricula, fecha, numero_horas) VALUES ('ME2', '901WXY', TO_DATE('2022-09-07', 'YYYY-MM-DD'), 5);
INSERT INTO repara (id_mecanico, matricula, fecha, numero_horas) VALUES ('ME3', '012ZAB', TO_DATE('2023-11-12', 'YYYY-MM-DD'), 2);
INSERT INTO repara (id_mecanico, matricula, fecha, numero_horas) VALUES ('ME4', '123CDE', TO_DATE('2023-04-03', 'YYYY-MM-DD'), 6);
INSERT INTO repara (id_mecanico, matricula, fecha, numero_horas) VALUES ('ME5', '234FGH', TO_DATE('2022-12-25', 'YYYY-MM-DD'), 4);
INSERT INTO repara (id_mecanico, matricula, fecha, numero_horas) VALUES ('ME6', '345IJK', TO_DATE('2023-08-15', 'YYYY-MM-DD'), 5);
INSERT INTO repara (id_mecanico, matricula, fecha, numero_horas) VALUES ('ME1', '456LMN', TO_DATE('2023-06-18', 'YYYY-MM-DD'), 3);
INSERT INTO repara (id_mecanico, matricula, fecha, numero_horas) VALUES ('ME2', '567OPQ', TO_DATE('2022-07-24', 'YYYY-MM-DD'), 7);
INSERT INTO repara (id_mecanico, matricula, fecha, numero_horas) VALUES ('ME3', '678RST', TO_DATE('2023-12-10', 'YYYY-MM-DD'), 4);
INSERT INTO repara (id_mecanico, matricula, fecha, numero_horas) VALUES ('ME4', '789UVW', TO_DATE('2023-02-14', 'YYYY-MM-DD'), 6);
INSERT INTO repara (id_mecanico, matricula, fecha, numero_horas) VALUES ('ME5', '890XYZ', TO_DATE('2023-10-19', 'YYYY-MM-DD'), 5);
INSERT INTO repara (id_mecanico, matricula, fecha, numero_horas) VALUES ('ME6', '901ABC', TO_DATE('2024-01-22', 'YYYY-MM-DD'), 2);
INSERT INTO repara (id_mecanico, matricula, fecha, numero_horas) VALUES ('ME1', '012DEF', TO_DATE('2023-07-07', 'YYYY-MM-DD'), 3);
INSERT INTO repara (id_mecanico, matricula, fecha, numero_horas) VALUES ('ME2', '123ABC', TO_DATE('2022-04-15', 'YYYY-MM-DD'), 4);
INSERT INTO repara (id_mecanico, matricula, fecha, numero_horas) VALUES ('ME3', '234DEF', TO_DATE('2023-09-22', 'YYYY-MM-DD'), 6);
INSERT INTO repara (id_mecanico, matricula, fecha, numero_horas) VALUES ('ME4', '345GHI', TO_DATE('2024-02-05', 'YYYY-MM-DD'), 5);
INSERT INTO repara (id_mecanico, matricula, fecha, numero_horas) VALUES ('ME5', '456JKL', TO_DATE('2023-03-20', 'YYYY-MM-DD'), 7);
INSERT INTO repara (id_mecanico, matricula, fecha, numero_horas) VALUES ('ME6', '567MNO', TO_DATE('2022-08-30', 'YYYY-MM-DD'), 4);
INSERT INTO repara (id_mecanico, matricula, fecha, numero_horas) VALUES ('ME1', '678PQR', TO_DATE('2023-11-25', 'YYYY-MM-DD'), 3);
INSERT INTO repara (id_mecanico, matricula, fecha, numero_horas) VALUES ('ME2', '789STU', TO_DATE('2023-06-19', 'YYYY-MM-DD'), 2);
INSERT INTO repara (id_mecanico, matricula, fecha, numero_horas) VALUES ('ME3', '890VWX', TO_DATE('2022-05-28', 'YYYY-MM-DD'), 4);
INSERT INTO repara (id_mecanico, matricula, fecha, numero_horas) VALUES ('ME4', '901YZA', TO_DATE('2023-09-15', 'YYYY-MM-DD'), 5);
INSERT INTO repara (id_mecanico, matricula, fecha, numero_horas) VALUES ('ME5', '012BCD', TO_DATE('2023-02-09', 'YYYY-MM-DD'), 6);
INSERT INTO repara (id_mecanico, matricula, fecha, numero_horas) VALUES ('ME6', '345EFG', TO_DATE('2023-04-12', 'YYYY-MM-DD'), 3);

COMMIT;