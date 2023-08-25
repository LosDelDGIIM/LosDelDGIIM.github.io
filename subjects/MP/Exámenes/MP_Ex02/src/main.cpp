#include <iostream>
#include <fstream>
using namespace std;

int nalumnos = 51;
const string _nombres[] = {"JOSE ALGAR FERNANDEZ", "JOAQUIN ARCILA PEREZ", "GERARDO ARENAS NASRAWIN", "CARMEN AZORIN MARTI", "RUBEN BALLESTEROS RIVERO", "MARTA BENITEZ HERNANDEZ", "MANUEL VICENTE BOLAÑOS QUESADA", "CLARA BOLIVAR PELAEZ", "LORENA CACERES ARIAS", "PEDRO HAIMAR CASTILLO GARCIA", "LUCIA CEPEDA GONZALEZ", "MARIA CRIBILLES PEREZ", "MANUEL DIAZ-MECO TERRES", "PABLO GALVEZ ORTIGOSA", "JESUS SAMUEL GARCIA CARBALLO", "CARLOS GARCIA JIMENEZ", "BORA GOKER SOLA", "JAVIER GOMEZ LOPEZ", "ANA GRACIANI DONAIRE", "JOSE ALBERTO HOCES CASTRO", "SHAO JIE HU CHEN", "ADRIAN JAEN FUENTES", "AARON JERONIMO FERNANDEZ", "NOURA LACHHAB BOUHMADI", "LAURA LAZARO SORALUCE", "RAMON LIRIA SANCHEZ", "ENRIQUE LOPEZ GARCIA", "CARLOTA LOPEZ QUESADA", "PAULA MANGANO GONZALEZ", "JOSE MARIA MARTIN MARTIN", "JAIME MARTINEZ BRAVO", "FRANCISCO NICOLAS MEDINA ROSAS", "MARIO MEGIAS MATEO", "JOSE LUIS MERA CARDOSO", "CRISTOBAL MERINO SAEZ", "QUINTIN MESA ROMERO", "ALVARO MOLINA ALVAREZ", "JUAN MOLINA MOLINA", "EDUARDO MOLINA VELAZQUEZ", "CLARA ORTEGA SEVILLA", "CARLOS MANUEL PERALES GOMEZ", "PEDRO PLAZAS MUNUERA", "CARLOS QUESADA PEREZ", "EDUARDO RODRIGUEZ CAO", "TOMAS RODRIGUEZ HERNAEZ", "ELSA RODRIGUEZ MACMICHAEL", "MARIO RUBIO VENZAL", "MANUEL RUIZ AGUILAR", "SOLEDAD RUIZ GOMEZ", "DAVID TORONJO MENDOZA", "ELENA TORRES FERNANDEZ"};

void Introduccion(const string &nombre) {
    int _i, _tipo;
    string aux;
    cout << "Buscando (" << nombre << ")" << endl;
    for (_i = 1; _i <= nalumnos && _nombres[_i - 1] != nombre; _i++);
    if (_i <= nalumnos) {
        cerr << "Alumno: " << nombre << endl;
        cerr << "Fichero: " << "1." + to_string(_i) + ".xhtml" << endl;
        cerr << "Variante: ";
        _tipo = nombre[0] % 4;
        switch (nombre[0] % 4) {
            case 0: cerr << "<class=" << endl;
                break;
            case 1: cerr << "<href=" << endl;
                break;
            case 2: cerr << "<sup>" << endl;
                break;
            case 3: cerr << "<h3>" << endl;
                break;
        }
        cerr << endl << endl << endl;
        //        cout << nombre << " " << _i << " " << _tipo << endl;
    } else {
        cout << "Por favor introduce tu nombre tal y como aparece en el array nombres[] " << endl;
        exit(1);
    }
}

/**
 * @brief Función que añadie la string @p a_aniadir al vector dinámico @p vector.
 * @param vector
 * @param util número de elementos de @p vector
 * @param a_aniadir
 */
void aniade(string* &vector, int &util, const string a_aniadir){
    string *aux = new string[util+1];
    
    // Copia en la nueva posición de memoria
    for(int i=0; i<util; i++)
        aux[i] = vector[i];
    
    delete[] vector;
    vector = aux;
    
    // Se añade
    vector[util] = a_aniadir;
    util ++;
}

/**
 * @brief Implementa la función del enunciado 
 * @param v1 Primer vector
 * @param nv1 Número de elementos de @a v1
 * @param v3 Vector resultado. Debe reservarse memoria dentro de la función
 * @param nv3 Número de elementos de @a v3
 */
void funcion(string const *v1, int nv1, string * &v3, int &nv3) {
    
    const string BUSCADO_INIT = "<p class=\"";
    const string BUSCADO_FIN = "\"";
    
    // Itero sobre cada linea
    for (int i=0; i<nv1; i++){
        string linea = v1[i];
        
        int pos_init = linea.find(BUSCADO_INIT);

            
        if(pos_init != string::npos){ // Hay una coincidencia
                
            pos_init += BUSCADO_INIT.length();
            
            //Elimino la parte anterior a la coincidencia, para buscar desde entonces
            linea = linea.substr(pos_init, linea.length()-pos_init);
                
            int pos_fin = linea.find(BUSCADO_FIN);
            
            string a_aniadir = linea.substr(0, pos_fin);
            aniade(v3, nv3, a_aniadir);
                
        } // if(pos_init != string::npos)
         
    }// for linea
}


// Error. En esta versión busca TODAS las coincidencias, no solo la primera de cada linea
/*
 * void funcion(string const *v1, int nv1, string * &v3, int &nv3) {
    
    const string BUSCADO_INIT = "<sup>";
    const string BUSCADO_FIN = "</sup>";
    
    // Itero sobre cada linea
    for (int i=0; i<nv1; i++){
        string linea_restante = v1[i];
        
        bool seguir = true;
        while (seguir){
            int pos_init = linea_restante.find(BUSCADO_INIT);

            
            if(pos_init != string::npos){ // Hay una coincidencia
                
                pos_init += BUSCADO_INIT.length();
                
                int pos_fin = linea_restante.find(BUSCADO_FIN);
                string a_aniadir = linea_restante.substr(pos_init, pos_fin - pos_init);
                aniade(v3, nv3, a_aniadir);
                
                // Elimino la parte que ya no necesito
                pos_fin += BUSCADO_FIN.length();
                linea_restante = linea_restante.substr(pos_fin, linea_restante.length()-pos_fin);
                
            } // if(pos_init != string::npos)
            
            else{ // Ya no quedan coincidencias
                seguir = false;
            }
        } // while seguir
    }// for linea
}
 * */

int main() {
    ifstream findice, ficapitulo;
    ofstream fosalida;
    string nameindice = "./data/index.dat",
            namesalida = "./data/salida.dat",
            namecapitulo = "1.25.xhtml"; // Copia aquí el nombre de tu fichero de trabajo
    string *capitulo = nullptr, *seleccion = nullptr;
    int ncapitulo, nseleccion=0;

    string linea, cadena;
    bool salir;

    // Consulta tu nombre, fichero de trabajo y variante
    Introduccion("LAURA LAZARO SORALUCE"); // Copia aquí tu nombre
    
    // Abrir fichero de indice. Comprobar sólo error de apertura
    findice.open(nameindice);
    
    if (!findice){
        
        string err;
        err += "The file " + nameindice + " could not be opened";
        
        throw ios_base::failure(err);
    }

    // Buscar namecapitulo en el fichero de índice y leer el número de líneas
    salir = false;
    
    while (getline(findice, linea) && !salir){
        
        if (linea.find(namecapitulo) != string::npos){
            salir = true;
            
            // Las líneas tienen el formato "37 nombre"
            // Busco hasta llegar al espacio
            string tmp;
            for(int i=0; i<linea.length() && linea.at(i)!= ' '; i++)
                tmp += linea.at(i);
            
            ncapitulo = stoi(tmp);
        }
    }
    
    findice.close();
    
    // Reservar memoria para *capitulo
    capitulo = new string[ncapitulo];
    
    // Abrir fichero namecapitulo dentro de "./data/"
    ficapitulo.open("./data/"+namecapitulo);
    if (!ficapitulo){
        
        string err;
        err += "The file " + namecapitulo + " could not be opened";
        
        throw ios_base::failure(err);
    }

    // Leer las líneas en memoria dinámica
    for (int i=0; i<ncapitulo; i++)
        getline(ficapitulo,capitulo[i]);
    
    // Calcular la lista de cadenas de la variante
    funcion(capitulo, ncapitulo, seleccion, nseleccion);
    
    // Guardar el resultado en "./data/salida.dat"
    fosalida.open(namesalida);
    
    if (!fosalida){
        
        string err;
        err += "The file " + namesalida + " could not be opened";
        
        throw ios_base::failure(err);
    }
    
    for (int i=0; i<nseleccion; i++)
        fosalida << seleccion[i] << endl;

    // Liberar la memoria
    delete [] capitulo;
    capitulo = nullptr;
    
    delete [] seleccion;
    seleccion = nullptr;
    
    return 0;
}

