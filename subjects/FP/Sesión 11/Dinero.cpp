#include <iostream>

using namespace std;

class Dinero{

	/*****************************************************************/
	// Campos de clase	

	private:
	
	int euros;		// PRE: euros >= 0
	int centimos;	// PRE: centimos >= 0

	public:
	
	/*****************************************************************/
	// Métodos constructores

	Dinero() :euros(0), centimos(0) {}

	// PRE: e >= 0, c >= 0
	Dinero(int e, int c){
		Asignar(e, c);
	}

	/*****************************************************************/
	// Devuelve la información de los campos en un texto

	string ToString(){
		return to_string(euros) + " euros y " + to_string(centimos) 
				+ " centimos ";
	}

	/*****************************************************************/
	// Incrementa el saldo según porc

	// PRE: porc >= 0

	void Incrementar(double porc){
	
		// Pasa el saldo a céntimos

		double dinero = euros * 100 + centimos;

		// Aplica el porcentaje redondeando los céntimos

		int dinero_final = (dinero + dinero * porc / 100) + 0.5;

		// Vuelve a ajustar el saldo en los campos de clase

		Asignar(0, dinero_final);

	}

	/*****************************************************************/

	private: 

	/*****************************************************************/
	// Asigna los euros y los céntimos especificados a los campos de clase
	// con un formato válido (100 cents = 1 e)

	// PRE: e >= 0, c >= 0

	void Asignar(int e, int c){
	
		// Calcula los euros que hay en los centimos
		int euros_en_c = c / 100;

		// Estos centimos ya no cuenta como céntimos
		c -= euros_en_c * 100;

		// Se asignan los euros y los céntimos

		euros = e + euros_en_c;

		centimos = c;
	}

};

/****************************************************************************
	Determina si una cadena es un número entero o si no.

  Parámetros: cadena
  Devuelve: true si cadena es un número entero, false si no

****************************************************************************/

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

/****************************************************************************
	Imprime un mensaje en consola y lee el número entero que introduce el 
	usuario. Repite la entrada mientras que el valor introducido no sea
	un número entero.

  Parámetros: titulo, el mensaje que se muestra al usuario
  Devuelve: el número entero que introduce el usuario

****************************************************************************/

int LeerEntero(string mensaje){
	string numero;

	do{

		cout << mensaje;
		cin >> numero;

	}while(!EsEntero(numero));

	return stoi(numero);
}

/****************************************************************************
	Imprime un mensaje en consola y lee el número entero que introduce el 
	usuario. Repite la entrada mientras que el valor introducido no sea
	un número entero o mientras que este no sea mayor o igual que la referencia

  Parámetros: titulo, el mensaje que se muestra al usuario
			  referencia, valor mínimo que acepta la función
  Devuelve: el número entero que introduce el usuario

****************************************************************************/

int LeerEnteroMayorOIgual(string mensaje, int referencia){

	int numero;

	do{

		numero = LeerEntero(mensaje);

	}while(numero < referencia);

	return numero;
}

/****************************************************************************
	Determina si cadena es un número real o si no.

  Parámetros: cadena
  Devuelve: true si cadena es un número real, false si no

****************************************************************************/

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
}

/****************************************************************************
	Imprime un mensaje en consola y lee un número real. Mientras que el número 
	introducido por el usuario no sea real, repite la lectura.

  Prámetros: mensaje
  Devuelve: Un número double introducido por el usuario

****************************************************************************/

double LeerReal(string mensaje){
	string numero;

	do{
		cout << mensaje;
		cin >> numero;
	}while(!EsReal(numero));

	return stod(numero);
}

/****************************************************************************
	Imprime un mensaje en consola y lee un número real. Mientras que el número 
	introducido por el usuario no sea real o mientras que el real no sea mayor 
	o igual que la refenrencia, repite la lectura.

  Prámetros: mensaje, referencia
  Devuelve: Un número double introducido por el usuario

****************************************************************************/

double LeerRealMayorOIgual(string mensaje, double referencia){
	double numero;

	do{
	
		numero = LeerReal(mensaje);

	}while(numero < referencia);

	return numero;
}

/****************************************************************************/

int main(){
	
	const int MIN_VALOR_DINERO = 0, MIN_VALOR_PORC = 0, MIN_VALOR_MES = 0;
	int euros, centimos;

	double incremento;

	int meses;

	// ENTRADAS

	// Solicita el saldo de la cuenta

	cout << "Saldo: " << endl;

	euros = LeerEnteroMayorOIgual("\tEuros: ", MIN_VALOR_DINERO);
	centimos = LeerEnteroMayorOIgual("\tCentimos: ", MIN_VALOR_DINERO);

	Dinero monedero(euros, centimos);

	cout << endl;

	// Solicita el porcentaje del incremento y el número de meses

	incremento = LeerRealMayorOIgual("Incremento mensual: ", MIN_VALOR_PORC);

	meses = LeerEnteroMayorOIgual("Numero de meses: ", MIN_VALOR_MES);

	// CÁLCULOS Y SALIDAS

	cout << endl;

	// Por cada mes incrementa el salario y lo imprime en consola

	for(int i = 1; i <= meses; i++){

		monedero.Incrementar(incremento);

		cout << "Mes " << i << ": " << monedero.ToString() << endl;

	}
	
	return 0;
}
