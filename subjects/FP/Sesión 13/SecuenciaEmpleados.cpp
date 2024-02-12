#include <iostream>

using namespace std;

/****************************************************************************
	Extrae una subcadena de otra, desde la posición indicada hasta encontrar 
	el caracter especificado

  Parámetros: cadena, posicion, caracter
  Devuelve: la subcadena especificada de cadena
  PRE: 0 <= posicion

****************************************************************************/

string ExtraeCadena(string cadena, int posicion, char caracter){

	string cad;

	bool seguir_leyendo = true;

	char car_actual = cadena.at(posicion);

	// Mientras que se pueda seguir leyendo

	while(seguir_leyendo && posicion < cadena.length()){
	
		cad += car_actual;

		posicion++;

		car_actual = cadena.at(posicion);

		// Lee hasta que no se encuentre caracter

		seguir_leyendo = car_actual != caracter;
	}

	return cad;
}

/****************************************************************************
	Pasa a mayúsculas un string

  Parámetro: cad
  Devuelve: cad en mayúsculas

****************************************************************************/

string Mayusculas(string cadena){
	string cad;

	for(int i = 0; i < cad.length(); i++){
		cad += toupper(cadena.at(i));
	}

	return cad;
}

/****************************************************************************
	Genera una cadena en la que hay veces veces el caracter caracter.

  Parámetros: veces (el número que se repite el caracter)
			  caracter (el caracter a repetir)
  Devuelve: una cadena que contiene caracter veces veces
  PRE: veces >= 0

****************************************************************************/

string GenerarCaracteres (int veces, char caracter){
	string devuelta;	

	// Concatena caracter a devuelta veces número de veces
	for(int i = 0; i < veces; i++)
		devuelta += caracter;

	return devuelta;
}

/****************************************************************************
	Formatea el string indicado de forma que contenga al menos el número de
	caracteres especificado, rellenando con caracteres relleno

  Parámetros: cad, caracteres, relleno
  Devuelve: una cadena con cad alineado a la izquierda de al menos caracteres
	caracteres

****************************************************************************/

string Formatea(string cad, int caracteres, char relleno){

	string cadena;

	if(cad.length() < caracteres){

		int num_relleno = caracteres - cad.length();

		cadena = cad + GenerarCaracteres(num_relleno, relleno);

	}else
		cadena = cad;

	return cadena;
}

/****************************************************************************
	Devuelve en una cadena la representación de un dato double con dos valores 
	decimales

  Parámetro: numero
  Devuelve: numero expresado como string, mostrando 2 decimales

****************************************************************************/

string FormateaNumero(double numero){
	
	string cadena = to_string(numero);

	string cad = cadena.substr(0, cadena.length() - 4);

	return cad;
}

/****************************************************************************/

class Fecha{

	// Campos de clase

	private:
		
	int dia;		// PRE: 0 < dia <= 31
	int mes;		// PRE: 0 < mes <= 12
	int anio;		// PRE: 1990 <= anio <= 2022

	// Métodos

	public:
	
	/*****************************************************************/
	// Métodos constructores

	Fecha() :dia(1), mes(1), anio(2000) {}

	// PRE: 0 < dia <= 31
	//		0 < mes <= 12
	//		1990 <= anio <= 2022

	Fecha(int d, int m, int a) :dia(d), mes(m), anio(a) {}

	// linea define una fecha con el siguiente formato:
	// dd/mm/aaaa

	Fecha(string linea){
		SetFecha(linea);
	}

	/*****************************************************************/
	// GETTERS y SETTERS

	int GetDia(){
		return dia;
	}

	int GetMes(){
		return mes;
	}

	int GetAnio(){
		return anio;
	}

	// PRE: 0 < d <= 31

	void SetDia(int d){
		dia = d;	
	}

	// PRE: 0 < m <= 12

	void SetMes(int m){
		mes = m;
	}

	// PRE: 1990 <= a <= 2022

	void SetAnio(int a){
		anio = a;
	}

	// PRE: 0 < dia <= 31
	//		0 < mes <= 12
	//		1990 <= anio <= 2022	

	void SetFecha(int d, int m, int a){
		dia = d;
		mes = m;
		anio = a;
	}

	// linea define una fecha con el siguiente formato:
	// dd/mm/aaaa

	void SetFecha(string linea){

		// Obtiene el día, el mes y el año

		string el_dia = linea.substr(0, 2);

		string el_mes = linea.substr(3, 2);

		string el_anio = linea.substr(6, 4);

		// Almacena cada uno en su campo correspondiente

		SetFecha(stoi(el_dia), stoi(el_mes), stoi(el_anio));
	}

	/*****************************************************************/
	// Obtiene las tres primeras letras del mes indicado

	string LetrasMes(int el_mes){
	
		const string MESES[] = {"Ene", "Feb", "Mar", "Abr", "May", 
							"Jun", "Jul", "Ago", "Sep", "Oct", "Nov", "Dic"};	

		return MESES[el_mes - 1];
	}

	/*****************************************************************/
	// Devuelve en un string la información de la clase, en formato:
	//		dd MES aaaa

	string ToString(){
		
		const string CERO = to_string(0);
		const string SEPARADOR = " ";

		string cad;

		// Se añaden los días

		if(dia < 10)
			cad += CERO;

		cad += to_string(dia) + SEPARADOR;

		// Se añaden los meses

		cad += LetrasMes(mes) + SEPARADOR;

		// Se añaden los años

		cad += to_string(anio);

		return cad;
	}	

	/*****************************************************************/
	// Devuelve en un string la información de la clase en el formato:
	// aaaammdd

	string ToString2(){

		const char CERO = '0';

		string meses, dias;

		// Se adaptan los meses para ocupar dos cifras

		if(mes < 10)
			meses += CERO;

		meses += to_string(mes);

		// Se adaptan los días para ocupar dos cifras

		if(dia < 10)
			dias += CERO;

		dias += to_string(dia);

		// Se construye la cadena

		string cad = to_string(anio) + meses + dias;

		return cad;
	}

	/*****************************************************************/
	// Devuelve true si la fecha indicada sucede después que esta fecha

	bool SucedeDespues(Fecha fecha){
		return stoi(ToString2()) < stoi(fecha.ToString2());
	}

};

/****************************************************************************/

class Empleado{

	// Campos de clase

	private:

	string nombre;
	string apellidos;
	double salario;		// PRE: salario > 0
	Fecha fecha_nac;

	// Métodos

	public:

	/*****************************************************************/
	// Métodos constructores

	Empleado() :salario(0) {}

	// PRE: sueldo > 0

	Empleado(string nom, string ape, double sueldo, Fecha nacimiento)
		:nombre(nom), apellidos(ape), salario(sueldo), fecha_nac(nacimiento) {}

	// linea define un empleado con el siguiente formato:
	// Apellidos*Nombre*dd/mm/aaaa*salario*

	Empleado(string linea){
		SetDatos(linea);
	}

	/*****************************************************************/
	// GETTERS

	string GetNombre(){
		return nombre;
	}

	string GetApellidos(){
		return apellidos;
	}

	double GetSalario(){
		return salario;
	}

	Fecha GetFecha(){
		return fecha_nac;
	}

	/*****************************************************************/
	// SETTERS

	void SetNombre(string nom){
		nombre = nom;
	}

	void SetApellidos(string ape){
		apellidos = ape;
	}

	// PRE: sueldo > 0

	void SetSalario(double sueldo){
		salario = sueldo;
	}

	void SetFecha(Fecha nacimiento){
		fecha_nac = nacimiento;
	}

	// PRE: sueldo > 0

	void SetDatos(string nom, string ape, double sueldo, Fecha nacimiento){
		nombre = nom;
		apellidos = ape;
		salario = sueldo;
		fecha_nac = nacimiento;
	}

	void SetDatos(string linea){
	
		const char SEPARADOR = '|';

		int pos = 0;

		// Extrae los apellidos, el nombre, el salario y la fecha

		apellidos = ExtraeCadena(linea, pos, SEPARADOR);
		pos += apellidos.length() + 1;

		nombre = ExtraeCadena(linea, pos, SEPARADOR);
		pos += nombre.length() + 1;

		string fecha = ExtraeCadena(linea, pos, SEPARADOR);
		fecha_nac.SetFecha(fecha);
		pos += fecha.length() + 1;

		string sueldo = ExtraeCadena(linea, pos, SEPARADOR);
		salario = stod(sueldo);
	}

	/*****************************************************************/
	// Devuelve los datos del objeto con el siguiente formato:
	// Apellidos    Nombre    DD Mes AAAA   Salario

	string ToString(){

		// Longitudes mínimas de cada sección

		const int LONG_APELLIDOS = 24;
		const int LONG_NOMBRE = 24;
		const int LONG_FECHA = 11;
		const int LONG_SALARIO = 7;

		const string SEPARADOR = "     ";
		const char ESPACIADO = ' ';

		return Formatea(apellidos, LONG_APELLIDOS, ESPACIADO) + SEPARADOR
			+ Formatea(nombre, LONG_NOMBRE, ESPACIADO) + SEPARADOR
			+ Formatea(fecha_nac.ToString(), LONG_FECHA, ESPACIADO) + SEPARADOR
			+ Formatea(FormateaNumero(salario), LONG_SALARIO, ESPACIADO);
	}

};

/****************************************************************************/

class SecuenciaEmpleados{

	// Campos de clase

	private:
	
	static const int POS_MAXIMAS = 100;
	Empleado array[POS_MAXIMAS];
	int pos_validas;

	// Métodos

	public:

	/*****************************************************************/
	// Método constructor

	SecuenciaEmpleados() :pos_validas(0) {}

	/*****************************************************************/
	// GETTERS

	int GetTamanio(){
		return pos_validas;
	}

	int GetTamanioMaximo(){
		return POS_MAXIMAS;
	}

	/*****************************************************************/
	// Añade un nuevo empleado al array
	// PRE: pos_validas < POS_MAXIMAS - 1

	void Aniade(Empleado nuevo){
		if(pos_validas < POS_MAXIMAS - 1){

			array[pos_validas] = nuevo;
			pos_validas++;

		}
	}

	/*****************************************************************/
	// Intercambia las posiciones de dos empleados en el array
	// PRE: 0 <= pos1, pos2 < pos_validas

	void Intercambia(int pos1, int pos2){

		Empleado auxiliar = array[pos1];
		array[pos1] = array[pos2];
		array[pos2] = auxiliar;

	}

	/*****************************************************************/
	// Devuelve la posición del menor Empleado del array a partir de una 
	// cierta posición
	// PRE: 0 <= pos_inicial < pos_validas

	int GetMenor(int pos_inicial){

		Empleado minimo = array[pos_inicial];
		int pos_minimo = pos_inicial;

		// Recorre el array

		for(int i = pos_inicial + 1; i < pos_validas; i++){

			// Guarda el empleado actual como mínimo en case de ser menor que
			// el mínimo actual

			if(EsMenor(array[i], minimo)){

				minimo = array[i];
				pos_minimo = i;

			}

		}

		return pos_minimo;
	}

	/*****************************************************************/
	// Ordena la secuencia de empleados por selection sort

	void OrdenarSelectionSort(){

		int minimo;

		for(int izda = 0; izda < pos_validas - 1; izda++){

			// Obtiene el mínimo a partir de izda

			minimo = GetMenor(izda);

			// Lo interambia con la posición izda

			Intercambia(izda, minimo);

		}

	}

	/*****************************************************************/
	// Devuelve el contenido de la secuencia en formato string, mostrando
	// en cada línea un empleado

	string ToString(){

		string cad;

		for(int i = 0; i < pos_validas - 1; i++){

			cad += array[i].ToString() + "\n";

		}

		cad += array[pos_validas - 1].ToString();

		return cad;
	}

	// Métodos privados

	private:

	/*****************************************************************/
	// Determina si un empleado es menor que otro o si no

	bool EsMenor(Empleado emp1, Empleado emp2){

		// Los ordena por salario

		return emp1.GetSalario() < emp2.GetSalario();

		// Los ordena por fecha de nacimiento

		// return emp1.GetFecha().SucedeDespues(emp2.GetFecha());

		// Los ordena por apellidos y nombre

		/*
		string nombre1 = emp1.GetApellidos() + emp1.GetNombre();
		string nombre2 = emp2.GetApellidos() + emp2.GetNombre();

		return nombre1 < nombre2;
		*/
	}

};

/****************************************************************************/

int main(){
	
	SecuenciaEmpleados secuencia;

	// ENTRADAS

	cout << "Introduzca los empleados con el formato: " 
		 << "Apellidos|Nombre|dd/mm/aaaa|Salario|" << endl;

	cout << endl;

	string linea;

	getline(cin, linea);

	// Lee líneas hasta toparse con una vacía

	Empleado auxiliar;

	while(linea != ""){
		
		// Guarda el empleado

		auxiliar.SetDatos(linea);

		secuencia.Aniade(auxiliar);

		// Lee la siguiente linea

		getline(cin, linea);
	}

	// CÁLCULOS Y SALIDAS ***************************************************

	// Si no se introdujo ningun empleado

	if(secuencia.GetTamanio() == 0){

		cout << "No se introdujo ningun empleado" << endl << endl;

	}else{

		// Muestra el contenido de empleados[]
	
		cout << "------------------------------------------------" << endl;
		cout << "Empleados registrados sin ordenar: " << endl << endl;
	
		cout << secuencia.ToString() << endl;
	
		cout << endl;
	
		// Ordena a los empleados
	
		secuencia.OrdenarSelectionSort();
	
		// Muestra el contenido de empleados[]
	
		cout << "------------------------------------------------" << endl;
		cout << "Empleados registrados ordenados: " << endl << endl;
	
		cout << secuencia.ToString() << endl;

	}
	
	return 0;
}
