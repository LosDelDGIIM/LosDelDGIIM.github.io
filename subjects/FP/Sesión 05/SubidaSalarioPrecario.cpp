#include <iostream>

using namespace std;

int main(){
	
	int edad;
	double salario;

	const int EDAD_MAYOR = 65, EDAD_MENOR = 35;
	const double PORC_EDAD = 4;		// 4%

	const int SALARIO_BAJO = 300;
	const double PORC_SALARIO = 3; 	// 3%

	const int SALARIO_REDUCIDO = 900;
	const double PORC_SALARIO2 = 1.5;	// 1.5%

	// Constantes para verificar la entrada de datos adecuados:
	const int EDAD_MIN_ADECUADA = 16, EDAD_MAX_ADECUADA = 80;
	const int SALARIO_MIN_ADECUADO = 0;

	// Creamos un tipo enumerado con todas las razones por las que podemos
	// subirle el salario al empleado.
	enum class Razones 
		{ninguna, edad, edad_salario_bajo, edad_salario_reducido};

	// ENTRADAS  *********************************************************

	cout << "Su edad: ";
	cin >> edad;

	// Consideramos que la edad es correcta si está en [16, 80], ya que se
	// trata de la edad de un trabajador.
	bool edad_correcta = edad >= EDAD_MIN_ADECUADA && edad <= EDAD_MAX_ADECUADA;

	if(!edad_correcta){
		cout << endl;
		cout << "Error: edad inadecuada." << endl;
		cout << endl;
	}else{
		cout << "Su salario: ";
		cin >> salario;
	}
	
	// Los salarios negativos se contemplan como error.
	bool salario_correcto = salario >= SALARIO_MIN_ADECUADO;

	// Se imprime el error sólo si la edad era correcta, ya que si era 
	// incorrecta el programa ya finaliza.
	if(!salario_correcto && edad_correcta){
		cout << endl;
		cout << "Error: salario inadecuado." << endl;
		cout << endl;
	}

	bool datos_correctos = edad_correcta && salario_correcto;

	// CÁLCULOS  **********************************************************

	Razones situacion;
	double salario_final;

	// Realiza los cálculos sólo si los datos son correctos
	if(datos_correctos){

		// Asigna a situacion el tipo enum correspondiente a la situación
		if(edad > EDAD_MAYOR || edad < EDAD_MENOR){
			
			if(salario < SALARIO_REDUCIDO){
				
				if(salario < SALARIO_BAJO)
					situacion = Razones::edad_salario_bajo;

				else
					situacion = Razones::edad_salario_reducido;

			}else
				situacion = Razones::edad;

		}else
			situacion = Razones::ninguna;

		// Determina el procentaje de subida

		double porc_subida;

		switch(situacion){
			case Razones::ninguna:
				porc_subida = 0;
				break;
			
			case Razones::edad:
				porc_subida = PORC_EDAD;
				break;

			case Razones::edad_salario_bajo:
				porc_subida = PORC_EDAD + PORC_SALARIO;
				break;

			case Razones::edad_salario_reducido:
				porc_subida = PORC_EDAD + PORC_SALARIO2;
				break;
		}

		// Calcula el salario final
		salario_final = salario + salario * (porc_subida / 100);

	}

	// SALIDAS  *********************************************************

	if(datos_correctos){
		cout << endl;
		cout << endl;

		cout << "Su salario final es de " << salario_final << " euros." 
			 << endl;
		
		cout << endl;

		// Imprime si se le ha subido el salario o si no

		switch(situacion){
			case Razones::ninguna:
				cout << "No se ha aplicado ninguna subida" << endl;
				break;
			
			case Razones::edad:
				cout << "Se ha aplicado una subida del " << PORC_EDAD 
					 << "% por la edad." << endl;
				break;

			case Razones::edad_salario_bajo:
				cout << "Se ha aplicado una subida del " << PORC_EDAD 
					 << "% por la edad." << endl;
				cout << "Ademas de otra del " << PORC_SALARIO 
					 << "% por el salario bajo." << endl;
				break;

			case Razones::edad_salario_reducido:
				cout << "Se ha aplicado una subida del " << PORC_EDAD 
					 << "% por la edad." << endl;
				cout << "Ademas de otra del " << PORC_SALARIO2 
					 << "% por el salario reducido." << endl;
				break;
		}

		cout << endl;
	}

	return 0;
}
