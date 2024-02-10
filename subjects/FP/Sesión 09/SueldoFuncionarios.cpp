#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

/****************************************************************************/
// Constantes

// Registros de subida del sueldo de los funcionarios y del IPC de España
// entre ANIO_INICIAL y ANIO_FINAL

const int ANIO_INICIAL = 2010, ANIO_FINAL = 2021;
const int NUM_ANIOS = ANIO_FINAL - ANIO_INICIAL + 1;

const double PORC_SUBIDA[NUM_ANIOS] = {-5, 0, 0, 0, 0, 0, 1, 1, 1.75, 2.5, 2,
																		 0.9};
const double IPC [NUM_ANIOS] = {3, 2.4, 2.9, 0.3, -1, 0, 1.6, 1.1, 1.2, 0.8, 
																-0.5, 6.5};

/****************************************************************************
	Calcula el precio introducido en el año final teniendo en cuenta el
	valor del IPC en España

  Parámetros: precio, anio_inicial, anio_final
  Devuelve: El valor de precio en el anio_final según las variaciones del IPC
  PRE: ANIO_INICIAL <= anio_inicial, anio_final <= ANIO_FINAL

	*Nota: necesita el valor de las ctes ANIO_INICIAL, ANIO_FINAL, IPC

****************************************************************************/

double CalculaPrecio_IPC(double precio, int anio_inicial, int anio_final){
	double precio_final = precio;	
	
	// Aumenta el precio según el IPC

	for(int i = anio_inicial + 1; i <= anio_final; i++){
				
		precio_final += precio_final * IPC[i - ANIO_INICIAL] / 100;

	}

	return precio_final;
}

/****************************************************************************
	Calcula el salario introducido de un funcionario en el año final
	teniendo en cuenta las variaciones de los sueldos de los funcionarios
	en España

  Parámetros: salario, anio_inicial, anio_final
  Devuelve: El valor del salario en el anio_final según las variaciones de los
	sueldos de los funcionarios
  PRE: ANIO_INICIAL <= anio_inicial, anio_final <= ANIO_FINAL

	*Nota: Necesita el valor de las ctes ANIO_INICIAL, ANIO_FINAL, PORC_SUBIDA

****************************************************************************/

double CalculaSalario_Funcionario(double salario, int anio_inicial, 
															int anio_final){
	double salario_final = salario;	
	
	// Aumenta el salario según el porcentaje de subida

	for(int i = anio_inicial + 1; i <= anio_final; i++){
				
		salario_final += salario_final * PORC_SUBIDA[i - ANIO_INICIAL] / 100;

	}

	return salario_final;
}

/****************************************************************************/

int main(){

	const int MIN_SALARIO = 0;

	double sueldo;
	int anio;
	int anio_posterior;

	// Se solicita el primer sueldo

	cout << "Para terminar, introduzca un sueldo menor o igual que " << MIN_SALARIO 
		 << endl << endl;

	cout << "Sueldo: ";
	cin >> sueldo;

	// Se formatea la consola

	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);

	while(sueldo > MIN_SALARIO){

		// ENTRADAS

		do{
		
			cout << "Anio (entre " << ANIO_INICIAL << " y " << ANIO_FINAL 
				 << "): ";
			cin >> anio;
		
		}while(anio < ANIO_INICIAL || anio > ANIO_FINAL);
		
		do{
		
			cout << "Anio a consultar (entre " << anio << " y " 
				 << ANIO_FINAL << "): ";
			cin >> anio_posterior;
		
		}while(anio_posterior < anio || anio_posterior > ANIO_FINAL);
		
		// CÁLCULOS
		
		double salario_ipc = CalculaPrecio_IPC(sueldo, anio, anio_posterior);
		
		double salario_real = 
					CalculaSalario_Funcionario(sueldo, anio, anio_posterior);
		
		double diferencia = abs(salario_ipc - salario_real);

		double porc_ganancia_perdida = salario_real * 100 / salario_ipc;
		
		// SALIDAS
		
		cout << endl;

		cout << setw(7) << setprecision(2);
		
		cout << "Salario teorico (segun IPC): " << salario_ipc << "e" 
			 << endl;

		cout << "Salario real: " 
			 << salario_real << "e" << endl;

		cout << "Diferencia: " << diferencia << "e" 
			 << endl;
		
		cout << setw(9) << setprecision(5) <<  porc_ganancia_perdida 
			 << " % del salario teorico." << endl;

		cout << endl;

		// Se solicita el siguiente sueldo

		cout << "Sueldo: ";
		cin >> sueldo;

	}

	return 0;
}
