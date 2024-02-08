#include <iostream>
#include <iomanip>

using namespace std;

int main(){
	
	double valor;
	string unidades_valor, unidades_transformar;
	char a;		// Donde almacenamos la preposición 'a'.

	const double MM_A_M = 0.001, CM_A_M = 0.01, KM_A_M = 1000;
	const double M_A_MM = 1000, M_A_CM = 100, M_A_KM = 0.001;

	// ENTRADAS  *********************************************************

	cout << "> ";
	cin >> valor;
	cin >> unidades_valor;

	// ALmacenamos 'a' para liberar el buffer y acceder a unidades_transformar
	cin >> a;	
	cin >> unidades_transformar;

	// Comprobamos que tanto el valor, las unidades del valor, las unidades a 
	// transformar y el formto son correctos:

	bool valor_correcto = valor >= 0;

	bool preposicion_correcta = a == 'a';

	bool unidades_valor_correctas = 
		unidades_valor == "mm" || unidades_valor == "cm" 
		|| unidades_valor == "m" || unidades_valor == "km";

	bool unidades_transformar_correctas =
		unidades_transformar == "mm" || unidades_transformar == "cm" 
		|| unidades_transformar == "m" || unidades_transformar == "km";

	bool datos_correctos = valor_correcto && preposicion_correcta 
		&& unidades_valor_correctas && unidades_transformar_correctas;

	// Se imprime error en caso de haberlo, especificando el error concreto

	if(!datos_correctos){
		cout << endl;
		cout << "Error:" << endl;

		if(!preposicion_correcta)
			cout << "Especifique un formato [valor] [unidades] a [unidades]" 
				 << endl;

		else{

			if(!valor_correcto)
				cout << "El valor debe ser positivo." << endl;
	
			if(!unidades_valor_correctas && !unidades_transformar_correctas)
				cout << "Las unidades \"" << unidades_valor << "\" y \"" 
					 << unidades_transformar << "\" no estan contempladas." 
					 << endl;
	
			else{
	
				if(!unidades_valor_correctas)
					cout << "Las unidades \"" << unidades_valor 
						 << "\" no estan contempladas." << endl;
		
				if(!unidades_transformar_correctas)
					cout << "Las unidades \"" << unidades_transformar 
						 << "\" no estan contempladas." << endl;
	
			}
		}

		cout << endl;
	}

	// CÁLCULOS  *********************************************************

	double valor_final = 0, valor_en_m = 0;

	// Realiza los cálculos si los datos son correctos

	if(datos_correctos){
		if(unidades_valor == unidades_transformar){
		
			// Si se quiere pasar a las mismas unidades, el valor es igual.
			valor_final = valor;
	
		}else{
	
			// En caso de no ser iguales, pasamos el valor a metros:
			if(unidades_valor == "mm"){
				valor_en_m = valor * MM_A_M;
			}
	
			if(unidades_valor == "cm"){
				valor_en_m = valor * CM_A_M;
			}
	
			if(unidades_valor == "m"){
				valor_en_m = valor;
			}
	
			if(unidades_valor == "km"){
				valor_en_m = valor * KM_A_M;
			}

			// Una vez que tenemos el valor en metros, lo pasamos a las 
			// unidades correctas:
			if(unidades_transformar == "mm"){
				valor_final = valor_en_m * M_A_MM;
			}

			if(unidades_transformar == "cm"){
				valor_final = valor_en_m * M_A_CM;
			}

			if(unidades_transformar == "m"){
				valor_final = valor_en_m;
			}

			if(unidades_transformar == "km"){
				valor_final = valor_en_m * M_A_KM;
			}
	
		}
	}

	// SALIDAS  *********************************************************

	if(datos_correctos){

		// Formateamos la consola
		cout.setf(ios::fixed);

		cout << setw(5) << setprecision(3);

		// Imprimimos el resultado
		cout << valor << (" " + unidades_valor + " = ") << valor_final 
			 << (" " + unidades_transformar);

		cout << endl;

	}
	
	return 0;
}
