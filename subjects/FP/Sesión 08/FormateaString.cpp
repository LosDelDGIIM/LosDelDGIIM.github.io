#include <iostream>

using namespace std;

// Los tipos de ajustes contemplados

enum class TipoAjuste {izquierda, centro, derecha};

/****************************************************************************
	Función que genera una cadena en la que hay veces veces el caracter
	caracter.

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
	Función que centra la cadena cadena mediante caracteres relleno:

	Los caracteres relleno se añadirán según el tipo de ajuste seleccionado:
		Si se selecciona izquierda, los caracteres relleno se colocan a la 
			derecha para dejar cad alineado a la izquierda.
		Si se selecciona derecha, los caracteres relleno se colocan a la 
			izquierda para dejar cad alineado a la derecha.
		Si se selecciona centro, los caracteres relleno se dividen entre la
			izquierda y la derecha de cad, alineándolo al centro.

  Parámetros: cadena, numero_caracteres, ajuste, relleno
  Devuele: Una nueva cadena que contiene la cadena anterior centrada en el
	sitio indicado, con la ayuda de tantos caracteres como se especificaron
	del tipo especificado
  PRE: numero_caracteres >= 0

****************************************************************************/

string Centrar(string cadena, int numero_caracteres, TipoAjuste ajuste
												   , char relleno){

	string cadena_centrada;

	// Realiza un ajuste u otro dependiendo del tipo de ajuste

	switch(ajuste){
		case TipoAjuste::izquierda:
			
			// Añade los caracteres relleno a la derecha

			cadena_centrada = cadena 
							+ GenerarCaracteres(numero_caracteres, relleno);
			
			break;

		case TipoAjuste::derecha:
			
			// Añade los carcteres relleno a la izquierda

			cadena_centrada = GenerarCaracteres(numero_caracteres, relleno) 
							+ cadena;

			break;

		case TipoAjuste::centro:
	
			// Reparte el número de caracteres entre delante y detrás

			int caracteres_delante = numero_caracteres / 2;

			int caracteres_detras = numero_caracteres - caracteres_delante;

			// Añade los caracteres relleno correspondientes a ambos lados

			cadena_centrada = GenerarCaracteres(caracteres_delante, relleno) 
					+ cadena + GenerarCaracteres(caracteres_detras, relleno);

			break;
	}

	return cadena_centrada;
}

/****************************************************************************
	Función que transforma el contenido de cad a un nuevo string según el
	formato indicado en los parámetros:

	La nueva cadena tendrá una longitud mínima de num_casillas casillas:
		Si cad tenía ya ese número de casillas, no se modifica.
		Si la longitud de cad era menor a ese númemro, se añaden caracteres
			relleno hasta llegar a la longitud deseada.

	Se centrará según el criterio especificado en la función
	Centrar(cadena, numero_caracteres, ajuste, relleno)

  Parámetros: cad, num_casillas, ajuste, relleno
  Devuelve: La cadena formateada según los parámetros.
  PRE: num_casillas >= 0

****************************************************************************/

string FormateaString (string cad, int num_casillas, TipoAjuste ajuste, 
													char relleno = ' '){

	string devuelta;

	// Si cad ya tenía la longitud mínima, no se modifica
	if(num_casillas <= cad.length())
		devuelta = cad;

	else{		// Si no, se modifica: 
	
		// Se calcula el número de caracteres de relleno que son necesarios
		// incluir para llegar a la longitud deseada

		int caracteres_necesarios = num_casillas - cad.length();

		// Se centra la cadena

		devuelta = Centrar(cad, caracteres_necesarios, ajuste, relleno);

	}

	return devuelta;
}

/****************************************************************************/

int main(){
	
	string cadena;
	int casillas;
	TipoAjuste ajuste;
	char relleno;

	// ENTRADAS

	// Cadena

	cout << "Cadena a formatear: ";
	getline(cin, cadena);

	// Número mínimo de casillas

	bool casillas_validas;

	do{

		cout << "Numero minimo de casillas: ";
		cin >> casillas;

		casillas_validas = casillas >= 0;

	}while(!casillas_validas);

	// Ajuste

	bool entrada_valida;

	char caracter;

	do{
	
		cout << "Tipo de ajuste (i -> izquierda, c -> centro, d -> derecha): ";
		cin >> caracter;

		entrada_valida = caracter == 'i' || caracter == 'c' || caracter == 'd';

	}while(!entrada_valida);

	// Se asigna el tipo enumerado en función del caracter introducido

	switch(caracter){
		case 'i':
			ajuste = TipoAjuste::izquierda;
			break;

		case 'c':
			ajuste = TipoAjuste::centro;
			break;

		case 'd':
			ajuste = TipoAjuste::derecha;
			break;
	}

	// Caracter relleno

	cout << "Caracter para rellenar: ";
	cin >> relleno;

	// SALIDAS

	cout << endl;

	cout << FormateaString(cadena, casillas, ajuste, relleno);

	cout << endl;

	return 0;
}
