#include <iostream>
#include <cmath>

using namespace std;

/****************************************************************************/

class Bin{

	// Campos de clase

	private:
	
	unsigned int valor_bin;		// PRE: 0 <= valor_bin < 2^(32) - 1

	// Métodos públicos

	public:
	
	/***********************************************************/
	// Métodos constructores

	Bin() :valor_bin(0) {}

	// PRE: 0 <= valor < 2^(32) - 1

	Bin(unsigned int valor) :valor_bin(valor) {}

	// PRE: valor es una cadena no vacía de sólo 1s y 0s
	// 		y valor.length() <= 32

	Bin(string valor) :valor_bin(BinToDec(valor)) {}

	/***********************************************************/
	// SETTERS
	
	// PRE: 0 <= valor < 2^(32) - 1

	void SetValor(unsigned int valor){
		valor_bin = valor;
	}

	// PRE: valor es una cadena no vacía de sólo 1s y 0s
	// 		y valor.length() <= 32

	void SetValor(string valor){
		valor_bin = BinToDec(valor);
	}

	/***********************************************************/
	// GETTERS

	// Devuelve los bits necesarios para representar valor_bin en binario

	int MinNumBits(){
		return log2(valor_bin) + 1;
	}

	// Devuelve valor_bin

	unsigned int GetValorDecimal(){
		return valor_bin;
	}

	// Devuelve valor_bin en binario usando el mínimo número de bits necesarios

	string GetValorBinario(){
		return DecToBin(valor_bin, 1);
	}

	// Devuelve valor_bin en binario con un número de bits (caracteres)
	// mayor o igual que num_casillas con el formato: [n_binario]
	// PRE: num_casillas > 0

	string ToString(int num_casillas){
		return "[" + DecToBin(valor_bin, num_casillas) + "]";
	}

	/***********************************************************/
	// Suma dos números binarios

	Bin Suma(Bin otro){

		const int BITS_OVERFLOW = 33;

		unsigned int suma;

		// Si no se produce overflow

		if(log2(valor_bin + otro.GetValorDecimal()) + 1 < BITS_OVERFLOW)
			suma = valor_bin + otro.GetValorDecimal();
		
		// Si se produce overflow

		else
			suma = 0;

		return Bin(suma);
	}

	/***********************************************************/
	// Devuelve el valor absoluto de la diferencia de dos números binarios

	Bin Resta(Bin otro){

		unsigned int resta = valor_bin - otro.GetValorDecimal();

		return Bin(resta);
	}

	/***********************************************************/
	// Devuelve el número que obtenemos al aplicarle una AND a todos
	// los bits de este objeto y del indicado dos a dos

	Bin AND(Bin otro){

		unsigned int y = valor_bin & otro.GetValorDecimal();

		return Bin(y);
	}

	/***********************************************************/
	// Devuelve el número que obtenemos al aplicarle una OR a todos
	// los bits de este objeto y del indicado dos a dos

	Bin OR(Bin otro){

		unsigned int o = valor_bin | otro.GetValorDecimal();

		return Bin(o);
	}

	/***********************************************************/	
	// Desplaza los bits del número hacia la derecha veces veces
	// PRE: 0 <= veces

	Bin DespDcha(int veces){

		int num = valor_bin;

		num >>= veces;

		return Bin(num);
	}

	/***********************************************************/
	// Desplaza los bits del número hacia la izquierda veces veces
	// PRE: 0 <= veces

	Bin DespIzda(int veces){

		int num = valor_bin;

		num <<= veces;

		return Bin(num);
	}

	// Métodos privados

	private:

	/***********************************************************/
	// Conversores de decimal a binario y viceversa

	// Devuelve la representacion en binario de num_decimal con al menos 
	// num_casillas caracteres de longitud
	// PRE: 0 <= num_decimal < 2^(32) - 1
	//		0 < num_casillas <= 32

	string DecToBin(unsigned int num_decimal, int num_casillas){

		const char CERO = '0', UNO = '1';

		string n_binario;

		while(num_decimal > 0){
	
			// Vamos dividiendo entre dos y procesando resultados

			if(num_decimal % 2 == 0)
				n_binario = CERO + n_binario;
	
			else
				n_binario = UNO + n_binario;
	
			num_decimal /= 2;
	
		}
		
		// Ajusta los bits para representar num_casillas bits
	
		if(n_binario.length() != num_casillas){
	
			// Se calcula cuantos ceros le faltan al número binario delante
			
			int diferencia = num_casillas - n_binario.length();
	
			// Obtenemos esos ceros y concatenamos
	
			string str_ceros = Generar(diferencia, CERO);
	
			n_binario = str_ceros + n_binario;
		}

		return n_binario;
	}

	// PRE: cad es una cadena no vacía de sólo 1s y 0s
	// 		y cad.length() <= 32

	unsigned int BinToDec(string cad){

		unsigned int decimal;
		int potencia = 1;
	
		// Recorre el número binario, comenzando por su bit menos significativo

		for(int i = cad.length()-1; i>= 0; i--){
	
			// En caso de haber un 1, se le suma al número decimal la potencia 
			// correspondiente
	
			if(cad.at(i) == '1')
				decimal += potencia;

			// Se aumenta la potencia

			potencia *= 2;
		}

		return decimal;
	}

	/***********************************************************/
	// Genera una cadena de caracteres del tipo indicado que se repite el 
	// número de veces indicado
	// PRE: cantidad >= 0

	string Generar(int cantidad, char caracter){

		string cad;
	
		// Concatena caracter cantidad veces
	
		for(int i = 0; i < cantidad; i++){
	
			cad += caracter;	
	
		}

		return cad;
	}

};		// Clase Bin

/****************************************************************************/

int main(){
	
	// BATERÍA DE PRUEBAS

	// Números

	Bin n1("1110");

	Bin n2;
	n2.SetValor(10);

	const int BITS = 8;

	// Operaciones

	// Suma

	cout << n1.ToString(BITS) << " + " << n2.ToString(BITS) << " = " 
		 << n1.Suma(n2).ToString(BITS) << endl;

	cout << endl;

	// Resta

	cout << n1.ToString(BITS) << " - " << n2.ToString(BITS) << " = " 
		 << n1.Resta(n2).ToString(BITS) << endl;

	cout << endl;

	// AND

	cout << n1.ToString(BITS) << " AND " << n2.ToString(BITS) << " = " 
		 << n1.AND(n2).ToString(BITS) << endl;

	cout << endl;

	// OR

	cout << n1.ToString(BITS) << " OR " << n2.ToString(BITS) << " = " 
		 << n1.OR(n2).ToString(BITS) << endl;

	cout << endl;

	// Desplazar dcha

	int dcha = 2;

	cout << n1.ToString(BITS) << " " << dcha << " a la dcha: " 
		 << n1.DespDcha(dcha).ToString(BITS) << endl;

	cout << endl;

	// Desplazar izqda

	int izqda = 2;

	cout << n2.ToString(BITS) << " " << izqda << " a la izqda: " 
		 << n2.DespIzda(izqda).ToString(BITS) << endl;

	cout << endl;

	return 0;
}
