#include <iostream>

using namespace std;

int main(){
	
	int velocidad;

	const int INTERVALO1_VEL_MIN = 120, INTERVALO2_VEL_MIN = 150,
		INTERVALO3_VEL_MIN = 170, INTERVALO4_VEL_MIN = 180, 
		INTERVALO5_VEL_MIN = 190;

	const int PUNTOS_INTERVALO1 = 0, PUNTOS_INTERVALO2 = 2, 
		PUNTOS_INTERVALO3 = 4, PUNTOS_INTERVALO4 = 6, PUNTOS_INTERVALO5 = 6;

	const int MULTA_INTERVALO1 = 100, MULTA_INTERVALO2 = 300, 
		MULTA_INTERVALO3 = 400, MULTA_INTERVALO4 = 500, MULTA_INTERVALO5 = 600;

	// ENTRADAS

	cout << "Introduzca la velocidad: ";
	cin >> velocidad;

	// Comprobamos que se ha introducido una velocidad verídica.
	bool velocidad_positiva = velocidad >= 0;

	if(!velocidad_positiva){
		cout << endl;
		cout << "Error: la velocidad debe ser positiva." << endl;
		cout << endl;
	}

	// CÁLCULOS

	int puntos = 0, multa = 0;

	if(velocidad_positiva){
	
		if(velocidad > INTERVALO5_VEL_MIN){
	
			multa = MULTA_INTERVALO5;
			puntos = PUNTOS_INTERVALO5;

		}else{
			
			if(velocidad > INTERVALO4_VEL_MIN){
	
				multa = MULTA_INTERVALO4;
				puntos = PUNTOS_INTERVALO4;

			}else{

				if(velocidad > INTERVALO3_VEL_MIN){
	
					multa = MULTA_INTERVALO3;
					puntos = PUNTOS_INTERVALO3;

				}else{
	
					if(velocidad > INTERVALO2_VEL_MIN){
	
						multa = MULTA_INTERVALO2;
						puntos = PUNTOS_INTERVALO2;

					}else{
		
						if(velocidad > INTERVALO1_VEL_MIN){
	
							multa = MULTA_INTERVALO1;
							puntos = PUNTOS_INTERVALO1;

						}
					}	
				}
			}
		}
	}

	// SALIDAS

	// Si algún parámetro de la multa es 0, no se muestra.
	// Si ambos son 0, se muestra que no se aplica ninguna sanción.

	if(velocidad_positiva){
		
		cout << endl;

		if(multa == 0 && puntos == 0)
			cout << "A usted no se le aplica ninguna sancion." << endl;

		else{
			
			cout << "Se le aplica la siguiente sancion:" << endl;

			// Esta opción no se contempla, pero si se altera el valor de las
			// constantes podria contemplarse.
			if(multa != 0)
				cout << "\tUna multa de " << multa << " euros." << endl;

			if(puntos != 0)
				cout << "\tUna perdida de " << puntos << " puntos del carnet." 
				 << endl;

		}

		cout << endl;

	}

	return 0;
}
