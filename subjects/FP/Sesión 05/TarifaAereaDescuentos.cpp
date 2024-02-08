#include <iostream>
#include <iomanip>

using namespace std;

int main(){

	// DECLARACIONES	

	int kilometros;
	double puntos;		// quizás los puntos puedan contener decimales.

	const double PRECIO_BASE = 150.0;	// en euros
	const double PRECIO_POR_KM = 0.1;	// 10 cents

	// kilometros cuyo precio va incluido en el base:
	const int KILOMETROS_LIMITE = 300;

	const int KILOMETROS_DESCUENTO = 700;
	const double DESCUENTO_POR_KILOMETROS = 2;	// 2%

	const int PUNTOS_DESCUENTO1 = 100, PUNTOS_DESCUENTO2 = 200;
	const double DESCUENTO1_POR_PUNTOS = 3;	// 3%
	const double DESCUENTO2_POR_PUNTOS = 4;	// 4%

	// Al tratarse de una aerolínea, consideramos que unos kilómetros son
	// correctos si al menos son superiores a 10km.
	const int KILOMETROS_MIN_ADECUADOS = 10;

	// ENTRADA	

	cout << "Kilometros al destino: ";
	cin >> kilometros;

	// Comprobaciones de que los kilómetros son correctos
	bool kilometros_adecuados = kilometros > KILOMETROS_MIN_ADECUADOS;

	if(kilometros_adecuados){
	
		cout << "Puntos de su tarjeta: ";
		cin >> puntos;

	}else{
		
		cout << endl;
		cout << "Error: Los kilometros deben ser mayores que " 
			 << KILOMETROS_MIN_ADECUADOS << " km." << endl;
		cout << endl;

	}

	// Nota: no consideramos los puntos negativos como erróneos ya que la 
	// empresa puede contemplarlos como una penalización.

	// CÁLCULOS  *************************************************************

	// Si los kilómetros son los adecuados, realizamos los cálculos.

	double precio_final, precio_sin_descuento;

	if(kilometros_adecuados){
	
		if(kilometros <= KILOMETROS_LIMITE)
			precio_sin_descuento = PRECIO_BASE;
	
		else{
			// Calcula el precio, sabiendo que hasta 300 km el precio es de 
			// 150€ y que a partir de estos cada kilómetros son 10 céntimos.
	
			// Kilómetros cuyo precio no va incluido en el precio base.
			int kilometros_extra = kilometros - KILOMETROS_LIMITE;
	
			precio_sin_descuento = PRECIO_BASE + kilometros_extra * PRECIO_POR_KM;
		
		}
	
		// Descuentos a aplicar:
	
		double descuento_kilometros = 0, descuento_puntos = 0;
	
		// Si los kilómetros son mayores a unos, se aplica un descuento.
		if(kilometros > KILOMETROS_DESCUENTO){
			descuento_kilometros = DESCUENTO_POR_KILOMETROS;
		}
	
		// Si los puntos del cliente son mayores a PUNTOS_DESCUENTO1 se aplica
		// un descuento y si son mayores a PUNTOS_DESCUENTO2 se aplica un 
		// descuento mayor
	
		if(puntos > PUNTOS_DESCUENTO2)
			descuento_puntos = DESCUENTO2_POR_PUNTOS;
	
		else{
			
			if(puntos > PUNTOS_DESCUENTO1)
				descuento_puntos = DESCUENTO1_POR_PUNTOS;
	
		}
	
		double descuento = descuento_kilometros + descuento_puntos;
	
		// Aplicamos el descuento
	
		precio_final = 
			precio_sin_descuento - precio_sin_descuento * (descuento / 100);

	}

	// SALIDA  **************************************************************

	if(kilometros_adecuados){
	
		// Formateamos la consola para que se muestren los céntimos de forma
		// correcta.
		cout.setf(ios::fixed);
	
		cout << endl;

		cout << "El precio del billete es de " << setw(6) << setprecision(2) 
				 << precio_final << " euros." << endl;

		cout << endl;
	}

	return 0;
}
