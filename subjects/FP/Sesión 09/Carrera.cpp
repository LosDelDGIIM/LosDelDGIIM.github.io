#include <iostream>
#include <iomanip>

using namespace std;

/****************************************************************************/
// Constantes

// Límites de valores que consideramos válidos

const int MAX_HORA = 24, MIN_HORA = 0;
const int MAX_MINS = 60, MIN_MINS = 0;
const int MAX_SEG = 60, MIN_SEG = 0;

// Conversión entre unidades

const int DIAS_A_HORAS = 24, HORAS_A_MINS = 60, MINS_A_SEGS = 60;

/****************************************************************************/
// Definiciones de structs

// Hora del día en un instante

struct Instante{
	int hora;
	int minuto;
	int segundo;
};

// Tiempo que transcurre entre dos instantes	

struct Tiempo{
	int horas;
	int minutos;
	int segundos;
};

/****************************************************************************
	Pasa la hora en un instante a los segundos que han pasado desde el
	instante inicial del día (00:00:00)

  Parámetros: instante
  Devuelve: El tiempo en segundos que transcurre desde 00:00:00 hasta el 
	instante

	*Nota: Necesita las ctes globales HORAS_MINS y MINS_SEGS

****************************************************************************/

int InstanteASegundos(Instante instante){
	return instante.hora * HORAS_A_MINS * MINS_A_SEGS 
		+ instante.minuto * MINS_A_SEGS + instante.segundo;
}

/****************************************************************************
	Calcula el tiempo que transcurre entre dos instantes

  Parámetros: inst1 (el primer instante), inst2
  Devuelve: El tiempo que transcurre entre instante1 e instante2

****************************************************************************/

Tiempo TiempoEntre(Instante inst1, Instante inst2){
	int segundos1 = InstanteASegundos(inst1);
	int segundos2 = InstanteASegundos(inst2);

	Tiempo tiempo_transcurrido;

	int segundos_transcurridos;

	// Si el primer instante sucede después o al mismo tiempo que el segundo
	// instante, consideramos que ha pasado un día

	if(segundos1 >= segundos2)

		// A los segundos de un día le restamos los segundos que transcurren
		// entre inst1 e inst2

		segundos_transcurridos = MINS_A_SEGS * HORAS_A_MINS * DIAS_A_HORAS 
								- (segundos1 - segundos2);

	else
		segundos_transcurridos = segundos2 - segundos1;

	// Calculamos los minutos y las horas exactas a las que equivalen
	// esos segundos

	int minutos_transcurridos = segundos_transcurridos / MINS_A_SEGS;

	int horas_transcurridas = minutos_transcurridos / HORAS_A_MINS;

	// Los almacenamos de forma correspondiente en tiempo_transcurrido

	tiempo_transcurrido.segundos = segundos_transcurridos % MINS_A_SEGS;

	tiempo_transcurrido.minutos = minutos_transcurridos % HORAS_A_MINS;

	tiempo_transcurrido.horas = horas_transcurridas;

	return tiempo_transcurrido;
}

/****************************************************************************
	Calcula la velocidad media de un corredor en km / h.

  Parámetros: km (distancia en km de la distancia),
			  tiempo (tiempo que tardó en completarlos)
  Devuelve: la velocidad media del corredor en km / h
  PRE: tiempo != 0 (que haya al menos un campo suyo distinto de 0)

****************************************************************************/

double Velocidad_km_h(double km, Tiempo tiempo){

	// Calcula las horas que hay en tiempo

	double horas = tiempo.horas + ((double)tiempo.minutos) / HORAS_A_MINS 
					+ ((double) tiempo.segundos) / (HORAS_A_MINS * MINS_A_SEGS);

	return km / horas;
}

/****************************************************************************
	Calcula el ritmo medio de un corredor en min/km

  Parámetros: km (distancia en km de la distancia),
			  tiempo (tiempo que tardó en completarlos)
  Devuelve: El ritmo medio del corredor en min / km
  PRE: km != 0

****************************************************************************/

double Ritmo_min_km(double km, Tiempo tiempo){
	
	// Calcula los minutos que hay en tiempo

	double minutos = tiempo.horas * HORAS_A_MINS + tiempo.minutos 
					+ ((double) tiempo.segundos) / MINS_A_SEGS;

	return minutos / km;
}

/****************************************************************************
	Devuelve en un texto la información de un dato de tipo Tiempo

  Parámetros: tiempo
  Devuelve: la información de los campos de tiempo en forma textual

****************************************************************************/

string TiempoToString(Tiempo tiempo){
	return to_string(tiempo.horas) + " horas, " + to_string(tiempo.minutos) 
			+ " minutos y " + to_string(tiempo.segundos) + " segundos";
}

/****************************************************************************
	Solicita al usuario la hora del día en un instante, devolviendo lo
	introducido por el usuario en un tipo de dato Instante.
	Antes de solicitar la hora, imprime el mensaje correspondiente

  Parámetros: mensaje (mensaje que imprime antes de solicitar datos)
  Devuelve: La hroa del día en el instante especificado por el usuario

	*Nota: necesita las ctes globales MAX_HORA, MIN_HORA, MAX_MIN, MIN_MIN,
		MAX_SEG, MIN_SEG.

****************************************************************************/

Instante LeerHora(string mensaje){
	
	// Imprime el mensaje

	cout << mensaje << endl;	

	int hora, minuto, segundo;

	// Lee las hora, el minuto y el segundo, obligando a que esté entre
	// el rengo de valores válidos

	do{

		cout << "\tHora: ";
		cin >> hora;

	}while(hora < MIN_HORA || hora > MAX_HORA);

	do{

		cout << "\tMinuto: ";
		cin >> minuto;

	}while(minuto < MIN_MINS || minuto > MAX_MINS);

	do{

		cout << "\tSegundo: ";
		cin >> segundo;

	}while(segundo < MIN_SEG || segundo > MAX_SEG);

	// Crea un objeto de tipo Instante y lo devuelve

	Instante inst;

	if(hora == MIN_HORA && minuto == MIN_MINS && segundo == MIN_SEG)
		inst = {24, 0, 0};

	else
		inst = {hora, minuto, segundo};

	return inst;
}

/****************************************************************************/

int main(){
	
	// La distancia mínima de la carrera es de 100m
	const double DISTANCIA_MIN = 0.1;	//(km)
	const int DORSAL_MIN = 0;

	double distancia_carrera;
	Instante comienzo_carrera;

	// ENTRADAS

	// Datos de la carrera
	
	do{

		cout << "Distancia (mayor o igual que " << DISTANCIA_MIN << " km) : ";
		cin >> distancia_carrera;

	}while(distancia_carrera < DISTANCIA_MIN);

	comienzo_carrera = LeerHora("Hora de inicio de la carrera: ");

	// Se comienzan a solicitar corredores

	cout << endl;
	cout << "(Para terminar, introduzca el dorsal " << DORSAL_MIN << ")" << endl;
	cout << endl;

	int dorsal;

	// Se solicita el dorsal del primer corredor

	do{
	
		cout << "Dorsal (mayor o igual que " << DORSAL_MIN << "): ";
		cin >> dorsal;

	}while(dorsal < DORSAL_MIN);

	Instante tiempo_corredor;

	// Se formatea la consola

	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);

	while(dorsal != DORSAL_MIN){

		// Se solicita el tiempo del corredor

		tiempo_corredor = LeerHora("Completa la carrera en: ");

		// Se calcula el tiempo que ha tardado, su velocidad y su ritmo

		Tiempo tiempo = TiempoEntre(comienzo_carrera, tiempo_corredor);

		double velocidad = Velocidad_km_h(distancia_carrera, tiempo);

		double ritmo = Ritmo_min_km(distancia_carrera, tiempo);

		// Se imprime en consola la información de los resultados del corredor

		cout << endl;

		cout << "El corredor " << dorsal << " ha tardado " 
			 << TiempoToString(tiempo) << " en completar la carrera." << endl;
		cout << "Ha llevado una velocidad media de " << setw(6) 
			 << setprecision(3) << velocidad << " km/h." << endl;
		cout << "Y un ritmo medio de " << setw(6) << setprecision(3) << ritmo 
			 << " min/km." << endl;

		cout << endl;

		// Se solicita el dorsal del siguiente corredor
	
		do{
		
			cout << "Dorsal (mayor o igual que " << DORSAL_MIN << "): ";
			cin >> dorsal;
	
		}while(dorsal < DORSAL_MIN);
	}

	return 0;
}
