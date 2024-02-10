#include <iostream>
#include <iomanip>

using namespace std;

int main(){

	const int PRECIO_MINIMO = 0;

	const int ANIO_INICIAL = 1990;
	const int ANIO_FINAL = 2021;
	const int NUM_ANIOS = ANIO_FINAL - ANIO_INICIAL + 1;

	// IPC de España entre ANIO_INICIAL y ANIO_FINAL

	const double IPC [NUM_ANIOS] = {6.5, 5.5, 5.3, 4.9, 4.3, 4.3, 3.2, 2, 1.4, 
						2.9, 4, 2.7, 4, 2.6, 3.2, 3.7, 2.7, 4.2, 1.4, 0.8, 3, 
						2.4, 2.9, 0.3, -1, 0, 1.6, 1.1, 1.2, 0.8, -0.5, 6.5};

	double precio;
	int anio_precio, anio_final;

	// Formateo de consola

	cout.setf(ios::fixed);

	cout << "Introduzca un precio menor o igual que " << PRECIO_MINIMO 
		 << " para terminar." << endl << endl;

	// Solicita el primer precio

	cout << "Precio: ";
	cin >> precio;

	while(precio > PRECIO_MINIMO){

		// Solicita los años de compra y de consulta

		// Consideramos ANIO_INICIAL - 1 un año válido porque conocemos
		// el IPC de ANIO_INICIAL

		do{
	
			cout << "Anio de compra del producto [" << ANIO_INICIAL - 1 
				 << ", " << ANIO_FINAL << "]: ";
			cin >> anio_precio;

		}while(anio_precio < ANIO_INICIAL - 1 || anio_precio > ANIO_FINAL);
	
		do{
	
			cout << "Anio de consulta [" << ANIO_INICIAL - 1 
				 << ", " << ANIO_FINAL << "]: ";
			cin >> anio_final;
	
		}while(anio_final < ANIO_INICIAL - 1 || anio_final > ANIO_FINAL);
	
		// CÁLCULOS
	
		// Se inicializa el precio final en precio inicial
		double precio_final = precio;	
	
		if(anio_precio <= anio_final){
	
			// Si el anño final es mayor avanzamos años

			for(int i = anio_precio + 1; i <= anio_final; i++){
					
				precio_final += precio_final * IPC[i - ANIO_INICIAL] / 100;
	
			}

		}else{

			// Si no, retrocedemos años

			for(int i = anio_precio - 1; i >= anio_final; i--){
	
				precio_final -= precio_final * IPC[i - ANIO_INICIAL] / 100;
	
			}

		}
	
		// SALIDAS

		cout << endl;

		cout << "Precio en " << anio_final << " : " << setw(9) 
			 << setprecision(6) << precio_final << endl;
	
		cout << endl;

		// Solicitamos el siguiente precio

		cout << "Precio: ";
		cin >> precio;
	}

	cout << endl;

	return 0;
}
