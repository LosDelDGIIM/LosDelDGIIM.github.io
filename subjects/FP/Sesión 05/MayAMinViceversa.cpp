#include <iostream>

using namespace std;

int main(){
	
	char letra_original;

	const int MIN_MINUSCULA = 'a', MAX_MINUSCULA = 'z';
	const int MIN_MAYUSCULA = 'A', MAX_MAYUSCULA = 'Z';

	enum class TiposCaracter {mayuscula, minuscula, digito, otro};

	// ENTRADA

	cout << "Introduzca un caracter: ";
	cin >> letra_original;

	// CÁLCULOS

	// Asignamos a la variable tipo el tipo enum correspondiente al caracter
		
	TiposCaracter tipo;
	char letra_convertida;

	if(letra_original >= MIN_MINUSCULA && letra_original <= MAX_MINUSCULA){
		tipo = TiposCaracter::minuscula;
		letra_convertida = toupper(letra_original);
	
	}else{

		if(letra_original >= MIN_MAYUSCULA && letra_original <= MAX_MAYUSCULA){
			tipo = TiposCaracter::mayuscula;
			letra_convertida = tolower(letra_original);
	
		}else{

			letra_convertida = letra_original;

			if(isdigit(letra_original))
				tipo = TiposCaracter::digito;	

			else
				tipo = TiposCaracter::otro;
		}
	}

	// SALIDAS

	cout << endl;

	switch(tipo){
		case TiposCaracter::minuscula:
			cout << "La letra era una minuscula." << endl;
			cout << "La letra convertida: " << letra_convertida;
			break;
	
		case TiposCaracter::mayuscula:
			cout << "La letra era una mayuscula." << endl;
			cout << "La letra convertida: " << letra_convertida;
			break;

		case TiposCaracter::digito:
			cout << "El caracter era un digito." << endl;
			break;

		case TiposCaracter::otro:
			cout << "El caracter no era ni una letra minuscula o mayuscula"
				 << " ni un digito." << endl;
			break;
	}

	cout << endl;

	return 0;
}
