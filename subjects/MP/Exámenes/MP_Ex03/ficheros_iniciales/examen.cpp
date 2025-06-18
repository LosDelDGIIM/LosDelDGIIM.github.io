/*
NOMBRE Y APELLIDOS:
DNI:
GRUPO DE PRACTICAS: Jueves
*/

#include <iostream>
#include <cmath>

using namespace std;

struct Pos{
	int x,y;
};

string toString(const Pos & p){
	string s = "(" + to_string(p.x) + "," + to_string(p.y) + ")";

	return s;
}


void imprimirArray(const Pos v[], int n)  {
	for (int i=0; i<n-1; i++)
		cout << toString(v[i]) << ", ";

		cout << toString(v[n-1]) << endl;
}

float distancia(const Pos & p, const Pos & k){
	float tmp = (p.x - k.x) * (p.x - k.x) + (p.y - k.y) * (p.y - k.y);
	return sqrt(tmp);
}
bool cubierto(const Pos & p, const Pos & k, int R){
	return (distancia(p,k) < R);
}



int main()  {
	// declare los arrays Ant (para las antenas), Cli (para los clientes), Aux (para resultados)
	// tamaños nCli, nAnt, nAux, respectivamente;
	
	// implemente la lectura de datos

	
	
	// mostrar por pantalla los puntos leidos
	cout << "Conjunto de clientes: " << endl;
	imprimirArray(Cli,nCli);
	
	cout << "\n\nConjunto de antenas: " << endl;
	imprimirArray(Ant,nAnt);
	
	
	// para cada antena, muestre la distancia promedio a los clientes cubiertos
	for(int i = 0; i < nAnt; i++){
		// LLAMAR FUNCION distanciaPromedio(.... Ant[i] .....);
		//cout << "Antena " << toString(Ant[i]) << ", Nro Clientes: " << .... << " Dist.Prom: " << .... << endl;
	}


	// funcion servidosPorAntena con la antena Ant[0]
	// Los resultados se guardan en el array Aux con tamaño nAux

	// servidosPorAntena(...Ant[0]...)
	cout << "\nClientes de antena: " << toString(Ant[0]) << endl;
	imprimirArray(Aux, nAux);
	
	// funcion servidosPorAntena con la antena Ant[1]
	// Los resultados se guardan en el array Aux con tamaño nAux

	// servidosPorAntena(...Ant[1]...)
	cout << "\nClientes de antena: " << toString(Ant[1]) << endl;
	imprimirArray(Aux, nAux);

	//llamada a la funcion datosCliente utilizando el cliente Cli[0]

	// datosCliente(...Cli[0]...)
	//cout << "Cliente: " << toString(Aux[0]) << " Dist: " << ..... << " Antena: " << toString(....) << endl;

	return 0;
}
