#include <iostream>

using namespace std;

int main()
{
	string input;	// Cadena original del usuario

	// ENTRADA

	cout << "Introduzca la cadena a formatear (53 caracteres): " << endl;
	getline(cin, input);

	// MANIPULACIÓN DE LA CADENA
	// Divide la cadena en cada componente usando el método substr()

	int seccion = stoi(input.substr(0, 3));

	int subseccion = stoi(input.substr(3, 3));

	int subsubseccion = stoi(input.substr(6, 3));

	string titulo = input.substr(9, 40);

	int pagina = stoi(input.substr(48, 4));

	// SALIDAS

	cout << endl;
	cout << endl;

	cout << "Componentes: " << endl;
	cout << "\tSeccion: 	" << seccion << endl;
	cout << "\tSubseccion: 	" << subseccion << endl;
	cout << "\tSubsubseccion: 	" << subsubseccion << endl;
	cout << "\tPagina:  	" << pagina << endl;
	cout << "\tTitulo: " << titulo << endl;

	cout << endl;

	cout << "Linea procesada: " << endl;
	cout << seccion << "." << subseccion << "." << subsubseccion << ". " 
		 << titulo << " " << pagina << endl;

	cout << endl;

	return 0;
}
