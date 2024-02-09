#include <iostream>
#include <cmath>

using namespace std;

double const PI = 6 * asin(0.5);

/****************************************************************************
	Función que calcula g(x) (la función gaussiana evaludada en x)

  Parámetros: x, sigma, mu (la abscisa y los parámetros de la gaussiana)
  Devuelve g(x) (el valor de la gaussiana de desviación típica y media
	especificadas evaluada en la abscisa x)
  PRE: sigma > 0

****************************************************************************/

double Gaussiana(double x, double sigma, double mu){
	double parte1_gaussiana = 1 / (sigma * sqrt(2 * PI));
	double parte2_gaussiana = exp(-0.5 * pow((x - mu) / sigma, 2));

	return parte1_gaussiana * parte2_gaussiana;
}

/****************************************************************************
	Función que calcula CDF(x) realizando una aproximación del área bajo
	la curva entre las abscisas [mu-3sigma, x]

  Parámetros: x, sigma, mu (la abscisa y los parámetros de la gaussiana)
  Devuelve: CDF(x)
  PRE: sigma > 0

****************************************************************************/

double CDF_Aproximacion1(double x, double sigma, double mu){
	const double SALTO = 0.25;	

	// Calculamos la parte de la gaussiana que se mantiene constante

	double parte1_gaussiana = 1 / (sigma * sqrt(2 * PI));

	double sumatoria_alturas = 0;

	// Recorremos las abscisas desde mu - 3sigma hasta la abscisa indicada,
	// dando saltos de SALTO entre cada abscisa 

	for(double xi = mu - 3 * sigma; xi <= x; xi += SALTO){

		// Segunda parte de la gaussiana, depende de xi:

		double parte2_gaussiana = exp(-0.5 * pow((xi - mu) / sigma, 2));

		// Obtenemos el valor de la gaussiana en xi

		double gaussiana = parte1_gaussiana * parte2_gaussiana;

		// Vamos realizando la sumatoria de las alturas

		sumatoria_alturas += gaussiana;

	}

	// Para obtener CDF(x) (el área bajo la curva), multiplicamos la 
	// sumatoria de las alturas por la base de los rectángulos que hemos 
	// considerado (base = SALTO) para obtener la sumatoria de las áreas de 
	// los rectángulos

	return sumatoria_alturas * SALTO;
}

/****************************************************************************
	Función que calcula CDF(x) realizando una aproximación por la fórmula:

		w = 1 - g(|x|) * (b1 * t + b2 * t^2 + ... + b5 * t^5)
	
							1
		con:	t = ---------------	
					  1 + b0 * |x|
	
				b0 = 0.2316419			b1 = 0.319381530
				b2 = -0.356563782		b3 = 1.781477937
				b4 = -1.821255978		b5 = 1.330274429
		
		Si x >= 0:
			CDF(x) = w
		Si no:
			CDF(x) = 1 - w

  Parámetros: x, sigma, mu (la abscisa y los parámetros de la gaussiana)
  Devuelve: CDF(x)
  PRE: sigma > 0

****************************************************************************/

double CDF_Aproximacion2(double x, double sigma, double mu){
	const double B0 = 0.2316419, B1 = 0.319381530, B2 = -0.35653782,
				 B3 = 1.781477937, B4 = -1.821255978, B5 = 1.330274429;

	// Calcula t
	double t = 1 / (1 + B0 * abs(x));

	// Calcula w
	double w = 1 - Gaussiana(abs(x), sigma, mu) * (B1 * t + B2 * pow(t, 2) 
				+ B3 * pow(t, 3) + B4 * pow(t, 4) + B5 * pow(t, 5));

	// Si x>=0 --> CDF(x) = w ; Si no --> CDF(x) = 1 - w
	double cdf = (x >= 0)? w : 1 - w;

	return cdf;
}

/****************************************************************************/

int main(){
	double x, sigma, mu;

	// ENTRADAS

	do{

		cout << "Desviacion tipica (mayor que 0): ";
		cin >> sigma;

	}while(sigma <= 0);

	cout << "Media: "; 
	cin >> mu;

	cout << "Abscisa: "; 
	cin >> x;

	// SALIDAS

	cout << endl;

	cout << "g(" << x << ") = " << Gaussiana(x, sigma, mu) 
	 	 << " (funcion gaussiana)" << endl;
	cout << "CDF(" << x << ") = " << CDF_Aproximacion1(x, sigma, mu) 
		 << " (aproximacion de la sumatoria del area de rectangulos)" << endl;
	cout << "CDF(" << x << ") = " << CDF_Aproximacion2(x, sigma, mu) 
		 << " (aproximacion de Abramowitz y Stegun)" << endl;

	cout << endl;

	return 0;
}
