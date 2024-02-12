#include <iostream>
#include <cmath>

using namespace std;

/****************************************************************************
	Eleva al cuadrado un número

  Parámetro: numero
  Devuelve: numero^2

****************************************************************************/

double Cuadrado(double numero){
	return numero * numero;
}

/****************************************************************************/

class Punto2D{

	// Campos de clase

	private:
	
	double abscisa;
	double ordenada;

	// Métodos

	public:

	/****************************************************************/
	// Métodos constructores

	Punto2D() :Punto2D(0, 0) {}

	Punto2D(double x, double y) :abscisa(x), ordenada(y) {}

	/****************************************************************/
	// SETTERS

	void SetAbscisa(double x){
		abscisa = x;
	}

	void SetOrdenada(double y){
		ordenada = y;
	}

	void SetCoordenadas(double x, double y){
		abscisa = x;
		ordenada = y;
	}

	/****************************************************************/
	// GETTERS

	double GetAbscisa(){
		return abscisa;
	}

	double GetOrdenada(){
		return ordenada;
	}

	/****************************************************************/
	// Devuelve la información del punto en el formato:
	// (abscisa, ordenada)

	string ToString(){

		return "(" + to_string(abscisa) + ", " + to_string(ordenada) + ")";

	}

};

/****************************************************************************/

class LectorPunto2D{

	// Campos de clase

	private:
	
	string mensaje;

	// Métodos

	public:
	
	/****************************************************************/
	// Método constructor

	LectorPunto2D() :mensaje("") {}

	LectorPunto2D(string msg) :mensaje(msg) {}

	/****************************************************************/
	// Cambia el mensaje

	void SetMensaje(string msg){
		mensaje = msg;
	}

	/****************************************************************/
	// Imprime el mensaje en consola

	void ImprimeMensaje(){
		cout << mensaje << endl;
	}

	/****************************************************************/
	// Solicita por consola un punto al usuario y lo devuelve

	Punto2D Lee(){

		double abscisa, ordenada;

		abscisa = LeeReal("\tAbscisa: ");
		ordenada = LeeReal("\tOrdenada: ");

		return Punto2D(abscisa, ordenada);
	}

	// Métodos privados

	private:

	/**************************************************************/
	// Imprime el mensaje y lee un número real del usuario

	double LeeReal(string msg){
		string numero;

		do{
	
			cout << msg;
			cin >> numero;

		}while(!EsReal(numero));
	
		return stod(numero);
	}

	/****************************************************************/
	// Determina si un número es real o si no

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

	}	// EsReal(string cadena)

};	// Clase LectoPunto2D

/****************************************************************************/

class Circunferencia{
	
	// Campos de clase

	private:
	
	static const double PI;

	Punto2D centro;
	double radio;		// PRE: radio >= 0

	// Métodoss

	public:
	
	/****************************************************************/
	// Métodos constructores

	Circunferencia() :radio(0) {}

	// PRE: r >= 0
	Circunferencia(Punto2D punto, double r) :centro(punto), radio(r) {}

	/****************************************************************/
	// GETTERS

	Punto2D ObtenerCentro(){
		return centro;
	}

	double ObtenerRadio(){
		return radio;
	}

	double ObtenerDiametro(){
		return 2 * radio;
	}

	/****************************************************************/
	// Devuelve el área de la circunferencia

	double ObtenerArea(){
		return PI * radio * radio;
	}

	/****************************************************************/
	// Devuelve la longitud de la circunferencia

	double ObtenerLongitud(){
		return 2 * PI * radio;
	}

	/****************************************************************/
	// Aumenta el radio de la circunferencia

	void AumentarRadio(double aumento){
		radio += aumento;
	}

	/****************************************************************/
	// Devuelve true si punto está contenido en esta circunferencia, false si 
	// no, usando la fórmula:
	// (x0 - x)^2 + (y0 - y)^2 <= r^2

	bool Contiene(Punto2D punto){

		return Cuadrado(centro.GetAbscisa() - punto.GetAbscisa()) + 
			   Cuadrado(centro.GetOrdenada() - punto.GetOrdenada()) 
												<= Cuadrado(radio);

	}

	/****************************************************************/
	// Devuelve los datos de la circunferencia en el formato:
	// {(abscisa, ordenada), radio}

	string ToString(){
		return "{" + centro.ToString() + ", " + to_string(radio) + "}";
	}
};

const double Circunferencia::PI = 6 * asin(0.5);

/****************************************************************************/

class Rectangulo{

	// Campos de clase	

	private:
	
	Punto2D vert_s_i;	// Vértice superior izquierdo
	double base;		// PRE: 0 < base
	double altura;		// PRE: 0 < altura

	// Métodos

	public:
	
	/****************************************************************/
	// Métodos constructores

	Rectangulo() :base(0), altura(0) {}

	// PRE: 0 < long_base
	//		0 < long_altura

	Rectangulo(Punto2D punto1, double long_base, double long_altura)
			:vert_s_i(punto1), base(long_base), altura(long_altura) {}

	Rectangulo(Punto2D punto1, Punto2D punto2) :vert_s_i(punto1) {
	
		// Calcula las longitudes de una base y de una altura

		base = abs(punto1.GetAbscisa() - punto2.GetAbscisa());
		altura = abs(punto1.GetOrdenada() - punto2.GetOrdenada());
	}

	/****************************************************************/
	// GETTERS

	Punto2D ObtenerVerticeSuperiorIzquierdo(){
		return vert_s_i;
	}

	Punto2D ObtenerVerticeSuperiorDerecho(){
		return Punto2D(vert_s_i.GetAbscisa() + base, vert_s_i.GetOrdenada());
	}

	Punto2D ObtenerVerticeInferiorIzquierdo(){
		return Punto2D(vert_s_i.GetAbscisa(), vert_s_i.GetOrdenada() - altura);
	}

	Punto2D ObtenerVerticeInferiorDerecho(){
		return Punto2D(vert_s_i.GetAbscisa() + base, 
											vert_s_i.GetOrdenada() - altura);
	}

	double ObtenerBase(){
		return base;
	}

	double ObtenerAltura(){
		return altura;
	}

	/****************************************************************/
	// Devuelve el perímetro del rectángulo

	double ObtenerPerimetro(){
		return 2 * (base + altura);
	}

	/****************************************************************/
	// Devuelve el centro del rectángulo

	Punto2D ObtenerCentro(){
	
		// Calculamos las longitudes de las mediatrices

		Punto2D centro;

		double mediatriz_base = base / 2;
		double mediatriz_altura = altura / 2;

		// Desplazamos el vértice superior izquierdo para obtener el centro

		centro.SetAbscisa(vert_s_i.GetAbscisa() + mediatriz_base);
		centro.SetOrdenada(vert_s_i.GetOrdenada() - mediatriz_altura);

		return centro;
	}

	/****************************************************************/
	// Devuelve el área del rectángulo

	double ObtenerArea(){
		return base * altura;
	}

	/****************************************************************/
	// Devuelve true si punto está contiendo en el rectángulo, false si no

	bool Contiene(Punto2D punto){

		bool abscisa_valida = vert_s_i.GetAbscisa() <= punto.GetAbscisa() 
						&& punto.GetAbscisa() <= vert_s_i.GetAbscisa() + base;

		bool ordenada_valida = vert_s_i.GetOrdenada() >= punto.GetOrdenada() 
					&& punto.GetOrdenada() >= vert_s_i.GetOrdenada() - altura;

		return abscisa_valida && ordenada_valida;

	}

	/****************************************************************/
	// Devuelve true si circf está contenida en el rectángulo, false si no

	bool Contiene(Circunferencia circf){

		// Obtiene los datos de circf

		Punto2D centro = circf.ObtenerCentro();

		double abscisa_centro = centro.GetAbscisa();
		double ordenada_centro = centro.GetOrdenada();

		double radio = circf.ObtenerRadio();

		// Comprueba que el punto más arriba esté contenido

		centro.SetOrdenada(ordenada_centro + radio);

		bool punto_sup = Contiene(centro);

		// Comprueba que el punto más abajo esté contenido

		centro.SetOrdenada(ordenada_centro - radio);
		
		bool punto_inf = Contiene(centro);

		centro.SetOrdenada(ordenada_centro);

		// Comprueba que el punto más a la izqda esté contenido

		centro.SetAbscisa(abscisa_centro - radio);

		bool punto_izqda = Contiene(centro);

		// Comprueba si el punto más a la dcha está contenido

		centro.SetAbscisa(abscisa_centro + radio);

		bool punto_dcha = Contiene(centro);

		return punto_sup && punto_inf && punto_izqda && punto_dcha;

	}

	/****************************************************************/
	// Devuelve true si una circunferencia centrada en el rectángulo está 
	// inscrita en este o si no
	// PRE: circf.ObtenerCentro() = ObtenerCentro()

	bool ContieneCentrada(Circunferencia circf){

		double radio = circf.ObtenerRadio();

		// Determina si las coordenadas horizontales de la circunferencia
		// están dentro de las horizontales del rectángulo

		bool horizontal_ok = radio <= base / 2;

		// Repite el proceso con coordenadas verticales

		bool vertical_ok = radio <= altura / 2;

		return horizontal_ok && vertical_ok;
	}

	/****************************************************************/
	// Devuelve la información del rectángulo en formato:
	// {(abscisa, ordenada), base, altura}

	string ToString(){

		const string SEPARADOR = ", ";

		return "{" + vert_s_i.ToString() + SEPARADOR + to_string(base) 
								+ SEPARADOR + to_string(altura) + "}";

	}

};

/****************************************************************************/

int main(){
	
	const double RADIO_INIC = 0.5, INCREMENTO = 0.25;

	const int TAMANIO_MAX = 100;

	Circunferencia circfs[TAMANIO_MAX];

	int pos_validas = 0;

	LectorPunto2D lector;

	// ENTRADAS --------------------------------------------------------------

	// Vertice superior izqdo

	cout << "Datos de su rectangulo: " << endl << endl;

	lector.SetMensaje("Vertice superior izquierdo de su rectangulo: ");

	lector.ImprimeMensaje();
	Punto2D vert_s_i = lector.Lee();

	cout << endl;

	// vertice inferior derecho

	lector.SetMensaje("Vertice superior derecho de su rectangulo: ");

	lector.ImprimeMensaje();
	Punto2D vert_i_d = lector.Lee();

	// CÁLCULOS -------------------------------------------------------------

	Rectangulo rect(vert_s_i, vert_i_d);

	Circunferencia auxiliar(rect.ObtenerCentro(), RADIO_INIC);

	// Mientras que sea una circunferencia válida

	while(rect.ContieneCentrada(auxiliar)){

		circfs[pos_validas] = auxiliar;
	
		pos_validas++;

		// Considera la siguiente circunferencia

		auxiliar.AumentarRadio(INCREMENTO);

	}

	// SALIDAS -------------------------------------------------------------

	cout << endl;

	// Si hay alguna circunferencia que se pueda inscribir

	if(pos_validas != 0){
		
		cout << "Hay " << pos_validas << " circunferencias inscritas: ";

		cout << endl << endl;

		// Las imprime todas

		for(int i = 0; i < pos_validas; i++){

			cout << circfs[i].ToString() << endl;

		}

	}else
		
		cout << "No se pudo inscribir ninguna circunferencia." << endl;

	cout << endl;

	return 0;
}
