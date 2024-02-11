#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

/****************************************************************************
	Eleva un número al cuadrado

  Parámetro: x
  Devuelve: x^2

****************************************************************************/

double Cuadrado(double x){
	return x * x;
}

/****************************************************************************
	Determina si cadena es un número real o si no.

  Parámetros: cadena
  Devuelve: true si cadena es un número real, false si no

****************************************************************************/

bool EsReal(string cadena){
	
	const string SIGNOS = "+-";

	const char PUNTO_DECIMAL = '.';

	bool es_real;

	// Si cadena está vacía no es un número real
	if(cadena.length() == 0)
		es_real = false;

	else{
	
		// Si el primer caracter es un signo y hay más caracteres se borra

		if(SIGNOS.find(cadena.at(0)) != string::npos && cadena.length() > 1)
			cadena.erase(0, 1);

		int i = 0;

		es_real = true;

		bool hay_punto = false;

		// Comprobamos todos los caracteres

		while(es_real && i < cadena.length()){

			// Si no es un dígito

			if(!isdigit(cadena.at(i))){
	
				// Se comprueba que sea un punto y que haya más caracteres

				if(cadena.at(i) == PUNTO_DECIMAL && cadena.length() > 1){
	
					// Si ya había un punto, hay 2 puntos => no es un real

					if(hay_punto) 
						es_real = false;

					// Si no había ninguno, lo tenemos en cuenta ahora

					else{
						hay_punto = true;
						i++;
					}

				}else	// No es un real
					es_real = false;
	
			}else	// Es un dígito
				i++;

		}

	}

	return es_real;
}

/****************************************************************************
	Imprime el mensaje y lee un número real por consola. Si el número
	introducio no era un número real, vuelve a repetir la entrada hasta que 
	el usuario inroduzca uno

  Parámetros: mensaje
  Devuelve: Un número real introducido por el usuario

****************************************************************************/

double LeeReal(string mensaje){
	string numero;

	// Repita la entrada mientas numero no sea un número real

	do{

		cout << mensaje;
		cin >> numero;

	}while(!EsReal(numero));

	return stod(numero);
}

/****************************************************************************
	Imprime el mensaje y lee un número real por consola. Si el número 
	introducido no era un real o era menor o igual que la referencia repite 
	la entrada hasta que el usuario introduzca un real mayro que la referencia

  Parámetro: mensaje, referencia
  Devuelve: Un número real introducido por el usuario mayor que referencia

****************************************************************************/

double LeeRealMayorQue(string mensaje, double referencia){

	double numero;

	// Repite la entrada mientras que numero <= referencia

	do{
		numero = LeeReal(mensaje);
	}while(numero <= referencia);

	return numero;
}

/****************************************************************************/

class Gaussiana{

	private:

	// Constante estática

	static const double PI;		

	// Campos de clase

	double media;
	double desviacion;	// PRE: desviacion > 0

	public:

	/***********************************************************/
	// Métodos constructores

	// Lo inicializa en la gaussiana normalizada
	Gaussiana() :media(0), desviacion(1) {}

	// PRE: sigma > 0
	Gaussiana(double mu, double sigma) :media(mu), desviacion(sigma) {}

	/***********************************************************/
	// Devuelve el valor de la gaussiana en la abscisa x con la media y 
	// la desviación típica indicadas
		
	double Evaluar(double x){

		double parte1 = 1 / (desviacion * sqrt(2 * PI));

 		double exponente = -0.5 * Cuadrado((x - media) / desviacion);

		return parte1 * exp(exponente);

	}

	/***********************************************************/
	// Devuelve el valor de CDF(x) realizando una aproximación 
	// de la integral

	double CDF_1(double x){

		const double SALTO = 0.001;

		// Abscisa en la que comienza a realizar la sumatoria de área de 
		// rectángulos

		double abscisa_inicial = media - 3 * desviacion;

		// Realiza la sumatoria del área de varios rectángulos, aproximando 
		// el valor de la integral

		double sumatoria = 0;

		for(double xi = abscisa_inicial; xi <= x; xi += SALTO){

			sumatoria += Evaluar(xi);

		}

		// Devuelve el área de los rectángulos 
		// (sumatoria de las alturas por la base)

		return sumatoria * SALTO;

	}

	/***********************************************************/
	// Devuelve el valor de CDF(x) realizando una aproximación numérica 

	double CDF_2(double x){

		const double B0 =  0.231641900;
		const double B1 =  0.319381530;
		const double B2 = -0.356563782;
		const double B3 =  1.781477937;
		const double B4 = -1.821255978;
		const double B5 =  1.330274429;

		double z = (x - media) / desviacion;

		double t = 1.0 / (1 + B0*fabs(z));
		double t2 = t*t;
		double t3 = t2*t;
		double t4 = t3*t;
		double t5 = t4*t;

		// Calcula el valor absoluto de la gaussiana normalizada en x

		Gaussiana g_normalizada;

		double gaussiana = g_normalizada.Evaluar(fabs(x));

		double w = 1 - gaussiana * (B1*t + B2*t2 + B3*t3 + B4*t4 + B5*t5);

		// Si la abscisa era positiva devuelve w y si no, 1 - w 

		return (x >= 0)? w : 1 - w;
	}

	/***********************************************************/
	// Devuelve en formato string los datos de la clase

	string ToString(){
		return "(" + to_string(media) + ", " + to_string(desviacion);
	}

};

const double Gaussiana::PI = 6 * asin(0.5);

/****************************************************************************/

int main(){
	
	const double SALTO_ABSCISA = 0.25;

	const int RANGO_DATOS = 3;

	double media, desviacion;

	// ENTRADAS

	media = LeeReal("Media: ");

	desviacion = LeeRealMayorQue("Desviacion tipica: ", 0);

	// CÁLCULOS Y SALIDAS
	
	double min_abscisa = media - RANGO_DATOS * desviacion;
	double max_abscisa = media + RANGO_DATOS * desviacion;	

	Gaussiana g(media, desviacion);

	// Formatea la consola

	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);

	cout << endl;

	for(double x = min_abscisa; x <= max_abscisa; x += SALTO_ABSCISA){

		double gaussiana = g.Evaluar(x);
		double cdf_1 = g.CDF_1(x);
		double cdf_2 = g.CDF_2(x);

		// SALIDAS

		cout << "G(" << setw(6) << setprecision(3) << x << ") = " 
			 << setw(5) << setprecision(3) << gaussiana << " ----- ";
		cout << "CDF_1 (" << setw(6) << setprecision(3) << x << ") = " 
			 << setw(5) << setprecision(3) << cdf_1 << " ----- ";
		cout << "CDF_2 (" << setw(6) << setprecision(3) << x << ") = " 
			 << setw(5) << setprecision(3) << cdf_2;			
		cout << endl;

	}

	return 0;
}
