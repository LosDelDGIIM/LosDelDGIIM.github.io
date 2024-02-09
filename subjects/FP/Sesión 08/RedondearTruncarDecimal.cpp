#include <iostream>
#include <iomanip>

using namespace std;

/***********************************************************************
	Función que calcula 10 elevado a exponente

  Parámetros: exponente
  Devuelve: 10 elevado a exponente
  PRE: exponente >= 0

***********************************************************************/

double Potencia_10(int exponente){
	double resultado = 1;	

	// Se calcula 10 * 10 * ... * 10 repitiendo 10 exponente veces

	for(int i = 0; i < exponente; i++)
		resultado *= 10;

	return resultado;
}

/***********************************************************************
	Función que devuelve num truncado a cifras cifras decimales

  Parámetros: num, cifras
  Devuelve: num truncado a cifras cifras decimales
  PRE: cifras >= 0

***********************************************************************/

double Trunca(double num, int cifras){
	double potencia_10 = Potencia_10(cifras);	 // 10 ^ cifras

	// Almacena las cifras del número truncado
	int auxiliar = num * potencia_10;

	// Desplazamos el punto decimal
	return auxiliar / potencia_10;
}

/***********************************************************************
	Función que devuelve num redondeado a cifras cifras decimales

  Parámetros: num, cifras
  Devuelve: num redondeado a cifras cifras decimales
  PRE: cifras >= 0

***********************************************************************/

double Redondear(double num, int cifras){
	
	// Trabajamos sobre el valor absoluto del número
	bool negativo = num < 0;

	if(negativo)
		num = -num;

	// Almacena las cifras del número truncado a cifras + 1
	int auxiliar = num * Potencia_10(cifras + 1);

	// ALmacena las cifras del número truncado a cifras
	int cifras_truncado = auxiliar / 10;	// = num * Potencia_10(cifras)

	// Obtiene la cifra posterior a la cifra decimal a redondear

	int cifra_redondear = auxiliar - 10 * cifras_truncado;

	// Almacena las cifras del número redondeado 

	int cifras_redondeado = (cifra_redondear < 5)? 
							cifras_truncado : cifras_truncado + 1;

	// Desplazamos el punto decimal
	double redondeado = cifras_redondeado / Potencia_10(cifras);

	// Si num era negativo, pasamos el resultado para que sea negativo
	if(negativo)
		redondeado = -redondeado;

	return redondeado;
}

/***********************************************************************/

int main(){

	// El algoritmo está limitado: no puede redondear ni truncar números a 
	// más de 7 cifras decimales por las limitaciones de las variables
	const int MAXIMO_SOPORTADO = 7;

	double numero;
	int cifras;

	// ENTRADAS

	cout << "Introduzca un numero: ";
	cin >> numero;

	bool cifras_invalidas = false;

	do{
		// Imprime por qué la última entrada no fue válida
		if(cifras_invalidas)
			cout << endl << "Las cifras deben estar entre 0 y " 
				 << MAXIMO_SOPORTADO << endl;

		cout << "Numero de cifras decimales: ";
		cin >> cifras;

		cifras_invalidas = cifras < 0 || cifras > MAXIMO_SOPORTADO;

	}while(cifras_invalidas);

	// SALIDAS

	// Formateamos la consola, para que se puedan visualizar bien
	// los digitos decimales deseados

	cout.setf(ios::fixed);

	cout << setw(cifras+3) << setprecision(cifras);

	cout << endl;

	cout << "Numero truncado: " << Trunca(numero, cifras) << endl;
	cout << "Numero redondeado: " << Redondear(numero, cifras) << endl;

	cout << endl;

	return 0;
}
