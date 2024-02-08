#include <iostream>

using namespace std;

int main()
{
	int clave;
	char caracter;

	// Constantes que nos ayudarán en los cálculos para que el caracter
	// codificado no se salga del intervalo [A, Z].
	const int MIN = 'A', MAX = 'Z';
	const int RANGO = MAX - MIN + 1; 	//Número de letras en [A, Z].

	// ENTRADAS  ******************************************************

	cout << "La clave: ";
	cin >> clave;

	// Comprueba que la clave esté entre [0, RANGO-1]
	bool clave_correcta = clave >= 0 && clave <= RANGO - 1;

	if(!clave_correcta){
		cout << endl;
		cout << "La clave es incorrecta, debe estar en el intervalo [0, 25]." 
			 << endl;
		cout << endl;
	}else{
		cout << "El caracter (mayuscula): ";
		cin >> caracter;
	}

	// Comprueba que el caracter introducido sea una letra mayúscula
	bool caracter_correcto = caracter >= MIN && caracter <= MAX;

	// Si la clave era incorrecta, consideramos que el programa finaliza
	// por tanto, no se muestra esta opción
	if(!caracter_correcto && clave_correcta){
		cout << endl;
		cout << "El caracter es incorrecto, debe ser una letra mayuscula." 
			 << endl;
		cout << endl;
	}

	bool datos_correctos = clave_correcta && caracter_correcto;

	// CÁLCULO  ******************************************************

	char caracter_final;

	if(datos_correctos){
	
		// Obtiene el caracter rotado
		char caracter_rotado = caracter + clave;
	
		// Si está fuera del intervalo, hace que esté dentro
		if(caracter_rotado > MAX)
			caracter_final = caracter_rotado - RANGO;

		else
			caracter_final = caracter_rotado;
	}

	// SALIDA  ******************************************************

	if(datos_correctos){
		cout << endl;
		cout << "El caracter codificado: " << caracter_final << endl;
		cout << endl;
	}

	return 0;
}
