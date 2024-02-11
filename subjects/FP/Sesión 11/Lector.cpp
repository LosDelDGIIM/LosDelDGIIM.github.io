#include <iostream>
#include <iomanip>

using namespace std;

class Lector{

	// Campos de clase

	private:
	string mensaje;

	// Métodos

	public:

	/**************************************************************/
	// Métodos constructores

    Lector(){}

	Lector(string msg) : mensaje(msg) {}

	/**************************************************************/	
	// Cambia el mensaje

	void SetTitulo(string msg){
		mensaje = msg;
	}

	/**************************************************************/
	// Métodos de enteros
	/**************************************************************/
	// Imprime el mensaje y se repite mientras que no sea un número entero

	int LeeEntero(){
		string numero;
	
		do{
	
			cout << mensaje;
			cin >> numero;
	
		}while(!EsEntero(numero));
	
		return stoi(numero);
	}

	/**************************************************************/
	// Devuelve un entero mayor o igual que referencia, repitiendo 
	// la entrada al usuario si esto no se da

	int LeeEnteroMayorOIgual(int referencia){
		int numero;

		do{
			numero = LeeEntero();
		}while(numero < referencia);

		return numero;
	}

	/**************************************************************/
	// Devuelve un entero entre min y max, repitiendo la entrada al 
	// usuario si esto no se da

	int LeeEnteroEnRango(int min, int max){
		int numero;

		do{
			numero = LeeEntero();
		}while(numero < min || numero > max);

		return numero;
	}

	/**************************************************************/
	// Métodos de reales
	/**************************************************************/
	// Imprime el mensaje y lee un número real del usuario

	double LeeReal(){
		string numero;

		do{
	
			cout << mensaje;
			cin >> numero;

		}while(!EsReal(numero));
	
		return stod(numero);
	}

	/**************************************************************/
	// Devuelve un número mayor o igual que referencia, repitiendo 
	// la entrada si esto no se da

	double LeeRealMayorOIgual(double referencia){
		double numero;
	
		do{
			numero = LeeReal();
		}while(numero < referencia);
	
		return numero;
	}

	/**************************************************************/
	// Devuelve un número real entre min y max, repitiendo la entrada 
	// si esto no se da

	double LeeRealEnRango(double min, double max){
		double numero;

		do{
			numero = LeeReal();
		}while(numero < min || numero > max);

		return numero;
	}

	/**************************************************************/
	// Métodos que determinan si un número es real o entero
	/**************************************************************/

	private:

	// Determina si un número es entero o si no

	bool EsEntero(string cadena){

		// Incluir en SIGNOS todos los signos válidos
	
		const string SIGNOS = "+-";
	
		bool es_entero;
	
		// Si la cadena está vacía no es un entero
		if(cadena.length() == 0)
			es_entero = false;
	
		else{
	
			// Si el primer caracter es un signo y hay más caracteres se borra
	
			if(SIGNOS.find(cadena.at(0)) != string::npos && cadena.length() > 1)
				cadena.erase(0, 1);
	
			// Comprobamos que todos los caracteres sean dígitos
	
			int i = 0;
	
			es_entero = true;
	
			while(i < cadena.length() && es_entero){
	
				if(!isdigit(cadena.at(i)))
					es_entero = false;
	
				else
					i++;
	
			}
		}
	
		return es_entero;
	}

	/**************************************************************/

	// Determina si un número es real o si no

	bool EsReal(string cadena){
	
		const string SIGNOS = "+-";
	
		const char PUNTO_DECIMAL = '.';
	
		bool es_real;
	
		// Si cadena está vacía no es un número real
		if(cadena.length() == 0)
			es_real = false;
	
		else{
		
			// Si el primer caracter es un signo y hay más caracteres se borra
	
			if(SIGNOS.find(cadena.at(0)) != string::npos && cadena.length() > 1)
				cadena.erase(0, 1);
	
			int i = 0;
	
			es_real = true;
	
			bool hay_punto = false;
	
			// Comprobamos todos los caracteres
	
			while(es_real && i < cadena.length()){
	
				// Si no es un dígito
	
				if(!isdigit(cadena.at(i))){
		
					// Se comprueba que sea un punto y que haya más caracteres
	
					if(cadena.at(i) == PUNTO_DECIMAL && cadena.length() > 1){
		
						// Si ya había un punto, hay 2 puntos => no es un real
	
						if(hay_punto) 
							es_real = false;
	
						// Si no había ninguno, lo tenemos en cuenta ahora
	
						else{
							hay_punto = true;
							i++;
						}
	
					}else	// No es un real
						es_real = false;
		
				}else	// Es un dígito
					i++;
	
			}
	
		}
	
		return es_real;

	}	// EsReal(string cadena)

};	// Clase Lector

/****************************************************************************/

int main(){
	
	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);

	// Ejecuta el código especificado en el enunciado:

	// Lectura de un entero arbitrario

	Lector lector_temp("Temperatura (sin decimales): "); 
	
	int temp = lector_temp.LeeEntero();
	
	cout << endl;
	cout << "Temperatura leida = " << temp << endl;
	cout << endl;


	// Lectura de enteros acotados superior e inferiormente 
	
	int hora, minuto, segundo;
	
	Lector lector_hora; 
	
	lector_hora.SetTitulo ("Introduzca hora: "); 	
	hora = lector_hora.LeeEnteroEnRango (0, 23);
	
	lector_hora.SetTitulo ("Introduzca minuto: "); 		
	minuto = lector_hora.LeeEnteroEnRango (0, 59);
	
	lector_hora.SetTitulo ("Introduzca segundo: "); 		
	segundo = lector_hora.LeeEnteroEnRango (0, 59);

	cout << endl;
	cout << "Hora: " << hora << ":" << minuto << ":" << segundo << endl;
	cout << endl << endl;
		
		
	// Lectura de un entero acotado inferiormente 
	
	int ingreso;
	
	Lector lector_ingreso("Cantidad a ingresar: "); 

	ingreso = lector_ingreso.LeeEnteroMayorOIgual (0);
	
	cout << endl;
	cout << "Valor del ingreso = " << ingreso << endl;
	cout << endl << endl;
	
	
	// Lectura de un valor real arbitrario 
	
	double temperatura;
	
	Lector lector_temperatura("Temperatura (con decimales): "); 

	temperatura = lector_temperatura.LeeReal ();
	
	cout << endl;
	cout << "Valor de la temperatura = " 
	     << setw(6) << setprecision(2) << temperatura << endl;
	cout << endl << endl;
	
	
	// Lectura de un real acotado superior e inferiormente 
	
	Lector lector_iva ("Introduzca IVA -entre 4.0 y 21.0-: "); 	 
	
	double iva = lector_iva.LeeRealEnRango (4.0, 21.0);
	
	cout << endl;
	cout << "Valor del IVA = " << setw(5) << setprecision(2) << iva << endl;
	cout << endl << endl;
	
	
	// Lectura de un real acotado superior e inferiormente 
	
	lector_iva.SetTitulo("Introduzca IVA (>=4.0): "); 	 

	iva = lector_iva.LeeRealMayorOIgual (4.0);
	
	cout << endl;
	cout << "Valor del IVA = " << setw(5) << setprecision(2) << iva << endl;
	cout << endl << endl;

	return 0;
}
