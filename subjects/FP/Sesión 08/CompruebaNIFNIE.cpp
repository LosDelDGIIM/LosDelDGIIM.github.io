#include <iostream>

using namespace std;

/***********************************************************/
//	Constantes que definen la longitud de un DNI, de un NIE y las letras
//  iniciales que puede contener el NIE

const int LONGITUD_DNI = 9, LONGITUD_NIE = 9;

const int DIGITOS_DNI = 8, DIGITOS_NIE = 7;

const int LETRA_NIE_1 = 'X', LETRA_NIE_2 = 'Y', LETRA_NIE_3 = 'Z';

/***********************************************************/

/****************************************************************************
	Función que comprueba si un caracter es un dígito.

  Parámetros: caracter
  Devuelve: true si caracter es un dígito, false si no

****************************************************************************/

bool EsDigito(char caracter){
	const int ASCII_0 = '0', ASCII_9 = '9';

	// Devuelve si el código ascii de caracter se encuentra entre los códigos
	// ascii del 0 y del 9 (en resumen, si caracter es un dígito)

	return caracter >= ASCII_0 && caracter <= ASCII_9;
}

/****************************************************************************
	Función que comprueba si un caracter es un caracter alfabético.

  Parámetros: carracter
  Devuelve: true si caracter es un caracter alfabético, false si no

	*Nota: En este caso, no consideramos a la ñ como un dato alfabético

****************************************************************************/

bool EsAlfabetico(char caracter){
	const int ASCII_A = 'A', ASCII_Z = 'Z';

	// Pasamos caracter a mayuscula para facilitar la comprobación

	caracter = toupper(caracter);

	// Devuelve si el código ascii de caracter en mayúscula se encuentra entre 
	// los códigos ascii de A y de Z (es decir, si era un caracter alfabético)

	return caracter >= ASCII_A && caracter <= ASCII_Z;
}

/****************************************************************************
	Función que determina si la cadena indicada tenía numero número de
	dígitos a partir de la posición inicio.

  Parámetros: cadena, inicio, numero
  Devuele: true si cadena contiene numero dígitos desde la posición inicio
  PRE: 0 <= inicio < cadena.length()
	   numero es un dato natural

****************************************************************************/

bool ContarDigitos(string cadena, int inicio, int numero){
	// Supone que los dígitos son correctos
	bool digitos_correctos = true;

	// Recorre la cadena desde inicio, hasta procesar numero caracteres
	// si alguno no era un número, digitos_correctos pasa a valer false
	// y se detiene la ejecución del bucle

	int i = inicio;

	while(digitos_correctos && i < numero){
		if(!EsDigito(cadena.at(i)))
			digitos_correctos = false;

		i++;
	}	

	return digitos_correctos;
}

/****************************************************************************
	Función que determina si el formato de un DNI es correcto o no
  
	Comprueba que el DNI sea del formato:
		NNNNNNNNC

	Donde N representa a cualquier dígito y C a cualquier caracter alfabético

  Parámetros: dni
  Devuelve: true si el DNI tenía formato correcto, false si no

	*Nota: Necesita valor de constantes globales LONGITUD_DNI y DIGITOS_DNI

****************************************************************************/

bool DNIFormatoCorrecto(string dni){

	bool digitos_correctos;
	bool letra_final;
	bool formato_correcto;

	// Si la longitud del DNI es la adecuada, comprueba que tenga un 
	// formato correcto

	if(dni.length() == LONGITUD_DNI){

		// Comprueba si el último caracter es alfabético

		letra_final = EsAlfabetico(dni.at(LONGITUD_DNI - 1));

		// Comprueba que todos los CANTIDAD_NUMEROS primeros caracteres
		// sean dígitos 

		digitos_correctos = ContarDigitos(dni, 0, DIGITOS_DNI);

		// Si se verifican las dos condiciones, es un formato de DNI válido

		formato_correcto = letra_final && digitos_correctos;

	}else		// Si no, directamente no es un formato de DNI
		formato_correcto = false;

	return formato_correcto;
}

/****************************************************************************
	Función que determina si el formato de un NIE es válido o no
  
	Comprueba que el NIE sea del formato:
		CNNNNNNNC

	Donde N representa a cualquier dígito y C a cualqueir caracter alfabético

  Parámetros: nie
  Devuelve: true si el NIE tenía formato correcto, false si no

	*Nota: necesita valor de constantes globales LONGITUD_NIE y DIGITOS_NIE

****************************************************************************/

bool NIEFormatoCorrecto(string nie){

	bool digitos_correctos;
	bool letra_inicial;
	bool letra_final;
	bool formato_correcto;

	// Comprueba que la longitud del NIE sea válida

	if(nie.length() == LONGITUD_NIE){

		// Comprueba que tenga CANTIDAD_NUMEROS número de dígitos a partir
		// de la posición 1

		digitos_correctos = ContarDigitos(nie, 1, DIGITOS_NIE);

		// Comprueba que el primer caracter del NIE sea alfabético

		letra_inicial = EsAlfabetico(nie.at(0));

		// Comprueba que el últio caracter del NIE sea alfabético

		letra_final = EsAlfabetico(nie.at(LONGITUD_NIE - 1));

		// Si se dan las tres, el formato es válido

		formato_correcto = digitos_correctos && letra_inicial && letra_final;

	}else	// Si no, tenía un formato equivocado
		formato_correcto = false;

	return formato_correcto;
}

/****************************************************************************
	Función que devuelve la letra correspondiente a un DNI

	Para ello, se calcula el módulo del número del DNI entre DIVISOR y 
	dependiendo del valor se asigna una letra u otra.

  Parámetros: dni (número del DNI)
  Devuelve: El caracter que le corresonde al DNI

****************************************************************************/

char ObtenerLetraDNI(long dni){

	const int DIVISOR = 23;

	// Contiene todas las letras que se pueden asignar a un DNI, ordenadas
	// según los posibles valores de resto (del 0 al 22)

	const string LETRAS = "TRWAGMYFPDXBNJZSQVHLCKE";

	// Se calcula el resto y se devuelve el caracter correspondiente

	int resto = dni % DIVISOR;

	return LETRAS.at(resto);
}

/****************************************************************************
	Función que determina si la letra de un DNI es correcta o no
  
	Para ello, se extrae el número del DNI y se comprueba que la letra
	especificada coincida con la letra que debe tener el número del DNI

  Parámetros: dni
  Devuelve: true si la letra del DNI era válida, false si no
  PRE: dni debe tener un formato válido, debe filtrarse por la función
	DNIFormatoCorrecto(dni)

	*Nota: Necesita valor de constante global DIGITOS_DNI

****************************************************************************/

bool DNILetraCorrecta(string dni){

	// Nos quedamos con el número del DNI y con la letra

	long numero_DNI = stol(dni.substr(0, DIGITOS_DNI));

	char letra = toupper(dni.at(dni.length() - 1));

	// Devolvemos el resultado de comparar la letra del DNI que introdujo
	// el usuario y la letra que debería tener ese número de DNI

	return letra == ObtenerLetraDNI(numero_DNI);
}

/****************************************************************************
	Función que determina si la primera letra de un NIE es correcta o no.
	Para ser correcta, debe ser igual a X, Y o Z.

  Parámetros: nie
  Devuelve: true si la primera letra es correcta, false si no
  PRE: nie no puede estar vacío

	*Nota: necesita los valores de las constantes globales LETRA_NIE_1,
	LETRA_NIE_2 y LETRA_NIE_3

****************************************************************************/

bool PrimeraLetraCorrectaNIE(string nie){
	char primera_letra = toupper(nie.at(0));

	return primera_letra == LETRA_NIE_1 || primera_letra == LETRA_NIE_2 
							|| primera_letra == LETRA_NIE_3;
}

/****************************************************************************
	Función que determina si las letras de un NIE son correctas o no
  
	Para ello, el primer caracter debe ser X, Y o Z

	Posteniormente se calcula la letra final, que se obtiene de la misma
	forma que la del DNI. La letra inicial se sustituye por un número
	para obtener un número similar al DNI:
		X --> 0
		Y --> 1
		Z --> 2

  Parámetros: nie
  Devuelve: true si el NIE era válido, false si no
  PRE: nie debe tener un formato correcto, debe filtrarse mediante la función
	NIEFormatoCorrecto(nie)

	*Nota: Necesita los valores de las constantes globales DIGITOS_NIE 
		   y LETRA_NIE_1

****************************************************************************/

bool NIELetrasCorrectas(string nie){

	bool letras_correctas;

	// Nos quedamos con la última y la primera letra

	char letra_inicial = toupper(nie.at(0));

	char letra_final = toupper(nie.at(nie.length() - 1));

	// Comprobamos si la letra inicial era válida:

	bool letra_inicial_valida = PrimeraLetraCorrectaNIE(nie);

	// Si la primera letra no era válida, las letras no son correctas

	if (!letra_inicial_valida)
		letras_correctas = false;

	else{		// letra_inicial es la contemplada

		// Restamos el código ascii de letra_inicial menos el código ascii
		// de la primera letra válida del NIE, obteniendo el primer núemro
		// del NIE

		int primer_numero = letra_inicial - LETRA_NIE_1;

		// Se obtiene el número del NIE, una vez sustituida la letra inicial
		// por el dígito corresondiente
		
		long numero_nie = 
				stol(to_string(primer_numero) + nie.substr(1, DIGITOS_NIE));

		// Se comprueba si la letra final es la correcta

		letras_correctas = letra_final == ObtenerLetraDNI(numero_nie);

	}

	return letras_correctas;
}

/***************************************************************************
	Función que comprueba si un DNI es válido o no

  Parámetros: dni
  Devuelve: true si el DNI es válido (si tiene un formato adecuado y la letra 
	adecuada al número), false si no

****************************************************************************/

bool DNIValido(string dni){
	bool dni_valido;

	// Filtramos que el formato sea válido antes de comprobar la letra

	if(DNIFormatoCorrecto(dni)){
	
		if(DNILetraCorrecta(dni))
			dni_valido = true;

		else
			dni_valido = false;

	}else
		dni_valido = false;

	return dni_valido;
}

/****************************************************************************
	Función que comprueba si un NIE es válido o no

  Parámetros: nie
  Devuelve: true si el NIE es válido (si tiene un formato adecuado, si
	las letras iniciales son las contempladas y si la letra final se 
	corresponde con el número y la letra inicial), false si no

****************************************************************************/

bool NIEValido(string nie){
	bool nie_valido;

	// Filtramos que el formato sea válido antes de comprobar las letras

	if(NIEFormatoCorrecto(nie)){

		if(NIELetrasCorrectas(nie))
			nie_valido = true;

		else
			nie_valido = false;

	}else
		nie_valido = false;

	return nie_valido;
}

/****************************************************************************
	Función que pasa una cadena entera a mayúsculas

  Parámetros: cadena
  Devuele: la cadena en mayúsculas

****************************************************************************/

string CadenaAMayuscula(string cadena){
	string cadena_en_mayusculas;	

	// Recorre cadena en todos los caracteres, pasándolos a mayúscula
	// y concatenándolos en cadena_en_mayusculas

	for(int i = 0; i < cadena.length(); i++)
		cadena_en_mayusculas += toupper(cadena.at(i));

	return cadena_en_mayusculas;
}

/****************************************************************************
	Función que imprime mensaje en consola, lee una cadena de caracteres
	y la devuelve toda en mayúsculas

  Parámetros: mensaje
  Devuele: La lectura en mayúsculas

****************************************************************************/

string LeerEnMayuscula (string mensaje){
	string lectura;

	cout << mensaje;
	getline(cin, lectura);

	return CadenaAMayuscula(lectura);
}

/****************************************************************************/

int main(){
	
	const string TERMINADOR = "FIN";

	// Lectura y comprobación de DNIs

	string entrada_dni;

	cout << "Introduzca los DNIs a comprobar (FIN para terminar): " << endl;
	entrada_dni = LeerEnMayuscula("DNI: ");

	// Mientras que no se introduzca TERINADOR

	while(entrada_dni != TERMINADOR){
	
		// Comprueba si el DNI es válido

		if(DNIValido(entrada_dni))
			cout << "DNI valido." << endl;
	
		else
			cout << "DNI invalido." << endl;

		cout << endl;

		// Lee el siguiente DNI

		entrada_dni = LeerEnMayuscula("DNI: ");
	}
	
	cout << endl << endl;

	// Lectura y comprobación de NIEs

	string entrada_nie;

	cout << "----------------------------------------------------" << endl;
	cout << "Introduzca los NIEs a comprobar (FIN para terminar): " << endl;
	entrada_nie = LeerEnMayuscula("NIE: ");

	// Mientras que no se introuduzca TERMINADOR

	while(entrada_nie != TERMINADOR){

		// Comprueba que el NIE sea válido

		if(NIEValido(entrada_nie))
			cout << "NIE valido." << endl;
	
		else
			cout << "NIE invalido." << endl;

		cout << endl;

		// Lee el siguiente NIE

		entrada_nie = LeerEnMayuscula("NIE: ");
	}

	return 0;
}
