// Problema de los lectores-escritores 

#include <iostream>
#include <iomanip>
#include <cassert>
#include <random>
#include <thread>
#include <chrono>
#include "scd.h"

using namespace std ;
using namespace scd ;

// Monitor a usar

class MonLecEsc : public HoareMonitor{
  private:
    int lec_dentro;
    bool esc_dentro;
    CondVar cola_lec, cola_esc;

  public:
    MonLecEsc();
    void inicia_lectura();
    void termina_lectura();
    void inicia_escritura();
    void termina_escritura();
};

MonLecEsc::MonLecEsc(){
    lec_dentro = 0;
    esc_dentro = false;
    cola_lec = newCondVar();
    cola_esc = newCondVar();
}

void MonLecEsc::inicia_lectura(){
    if(esc_dentro){
        cola_lec.wait();
    }

    lec_dentro++;
    cola_lec.signal();
}

void MonLecEsc::termina_lectura(){
    lec_dentro--;

    if(lec_dentro == 0){
        cola_esc.signal();
    }
}

void MonLecEsc::inicia_escritura(){
    if(esc_dentro || lec_dentro > 0){
        cola_esc.wait();
    }

    esc_dentro = true;
}

void MonLecEsc::termina_escritura(){
    esc_dentro = false;

    if(!cola_lec.empty()){
        cola_lec.signal();
    }else{
        cola_esc.signal();
    }
}

// --------------------------------------------------

void duerme(bool escritor){
    if(escritor){
       this_thread::sleep_for(chrono::milliseconds(aleatorio<2000,2000>()));
    }else{
       this_thread::sleep_for(chrono::milliseconds(aleatorio<100,1000>()));
    }
}

mutex m_cout;
void imprime(const string& s){
    m_cout.lock();
    cout << s << endl;
    m_cout.unlock();
}

void lector(MRef<MonLecEsc> monitor, int id){
    while(true){
        monitor->inicia_lectura();
        imprime("Lector nº " + to_string(id) + " entra a leer");
        duerme(false);
        imprime("Lector nº " + to_string(id) + " sale de leer");
        monitor->termina_lectura();
        duerme(false);
    }
}

void escritor(MRef<MonLecEsc> monitor, int id){
    while(true){
        monitor->inicia_escritura();
        imprime("Escritor nº" + to_string(id) + " entra a escribir");
        duerme(true);
        imprime("Escritor nº" + to_string(id) + " sale de escribir");
        monitor->termina_escritura();
    }
}

// --------------------------------------------------

int main(int argc, char** argv){
    int num = 3;

    thread lectores[num], escritores[num];
    MRef<MonLecEsc> monitor = Create<MonLecEsc>();

    for(int i = 0; i < num; i++){
        lectores[i] = thread(lector, monitor, i);
        escritores[i] = thread(escritor, monitor, i);
    }

    for(int i = 0; i < num; i++){
        lectores[i].join();
        escritores[i].join();
    }

    return 0;
}
