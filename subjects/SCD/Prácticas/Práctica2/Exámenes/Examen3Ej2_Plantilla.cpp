#include <iostream>
#include <cassert>
#include <thread>
#include <mutex>
#include <random> 
#include <chrono> 
#include "scd.h"

using namespace std ;
using namespace scd ;

constexpr int 
	escritores = 2,
	lectores = 4,
	min_ms = 500,
	max_ms = 2000;

mutex mtx;

//**********************************************************************
class Lectores_Escritores : public HoareMonitor{
	private:
	    bool escribiendo;
	    int nlectores;
	    CondVar lectura, escritura;
        
    
	public:
	    Lectores_Escritores();
	    void lectura_ini();
	    void lectura_fin();
	    void escritura_ini();
	    void escritura_fin();
};


//**********************************************************************
Lectores_Escritores::Lectores_Escritores(){
	escribiendo = false;
	nlectores = 0;
	
	lectura = newCondVar();
	escritura = newCondVar();
}
//**********************************************************************
void Lectores_Escritores::lectura_ini(){
	
	if (escribiendo) lectura.wait();
	
	nlectores++;

	lectura.signal();
}
//**********************************************************************
void Lectores_Escritores::lectura_fin(){
	nlectores--;
	
	if (nlectores == 0)	escritura.signal();	
}
//**********************************************************************
void Lectores_Escritores::escritura_ini(){
	if (escribiendo || nlectores > 0){
		escritura.wait();
	}
	
	escribiendo = true;
}
//**********************************************************************
void Lectores_Escritores::escritura_fin(){
	escribiendo = false;
	
	if (!lectura.empty()) 
	    lectura.signal();
	else 
	    escritura.signal();
}


//**********************************************************************
void funcion_hebra_escritora(MRef<Lectores_Escritores> monitor, int i){
	while (true){
		monitor->escritura_ini();
		    mtx.lock();
		        cout << "..........................................Escritor: " << i << " ESCRIBIENDO" << endl;
			mtx.unlock();
		    chrono::milliseconds duracion(aleatorio < min_ms, max_ms > ());
		    this_thread::sleep_for(duracion);
		monitor->escritura_fin();
	}		
}

//**********************************************************************
void funcion_hebra_lectora(MRef<Lectores_Escritores> monitor, unsigned i){
	while (true){
		monitor->lectura_ini();
		    mtx.lock();
		        cout << "LECTOR: " << i << " leyendo" << endl;
			mtx.unlock();
		monitor->lectura_fin();

		chrono::milliseconds duracion(aleatorio < max_ms, max_ms > ());
	    this_thread::sleep_for(duracion);
	}	
}


//**********************************************************************
int main()
{
	MRef<Lectores_Escritores> monitor = Create<Lectores_Escritores>();
	
	thread hebras_escritoras[escritores], hebras_lectoras[lectores];
	
	for (int i = 0; i < escritores; i++)
		hebras_escritoras[i] = thread(funcion_hebra_escritora,monitor,i);
	for (int i = 0; i < lectores; i++) 
	    hebras_lectoras[i] = thread(funcion_hebra_lectora,monitor,i);
	

	for (int i = 0; i < escritores; i++) hebras_escritoras[i].join();
	for (int i = 0; i < lectores; i++) 	hebras_lectoras[i].join();
	
}