/**
 * @file menu.cpp
 * @brief Menu que permite al usuario elegir entre distintas opciones de expresiones regulares:
 *        1. Dado un teléfono, comprobar si es válido en España.
 *        2. Dado un correo electrónico, comprobar si es válido.
 *        3. Dado un DNI, comprobar si es válido.
 *        4. Dado un número de tarjeta de crédito, indicar de qué entidad bancaria es.
 *
 *  Se usa para ello los distintos programas creados en las carpetas, de forma que a estos les pasaremos
 *  un archivo .txt especial con la entrada introducida por el usuario y mostrándo por tanto en pantalla su salida usual
 *  en función del archivo dado.
 * 
 * @note
 *      Compilación:
 *          1. g++ -Wall -o menu_exe menu.cpp
 *      Ejecución:
 *          1. ./menu_exe
 * 
 * @author Arturo Olivares Martos
 * @author Joaquín Avilés de la Fuente
 * @date 18 de diciembre de 2024
 */

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>


using namespace std;
ofstream f_escritura;

void imprime_menu(){
    cout << "Menú:" << endl;
    cout << "\t1. Dado un teléfono, comprobar si es válido en España." << endl;
    cout << "\t2. Dado un correo electrónico, comprobar si es válido." << endl;
    cout << "\t3. Dado un DNI, comprobar si es válido." << endl;
    cout << "\t4. Dado un número de tarjeta de crédito, indicar de qué entidad bancaria es." << endl;
    cout << "Introduce el número de la opción elegida:" << endl;
}


int main (int argc, char *argv[]){
    const string INICIAL="0";

    string input;
    string line;
    stringstream ss;

    string opcion_elegida=INICIAL;
    string comando, archivo;


    cout << "En el siguiente programa, encontrarás un menú que te permitirá trabajar con distintas expresiones regulares." << endl;
    imprime_menu();

    while(opcion_elegida == INICIAL){
        getline(cin, opcion_elegida);
        try{
            stoi(opcion_elegida);
        }
        catch(...){
            // Si no se introduce un número, se establece en la opción inicial
            // para que se lance el mensaje de error
            opcion_elegida=INICIAL;
        }
        switch(stoi(opcion_elegida)){
            case 1:
                cout << "Has elegido la opción 1 (Teléfonos)" << endl;
                comando="make telefonos-menu";
                archivo="Telefonos/telefonos-menu.txt";
                break;
            case 2:
                cout << "Has elegido la opción 2 (EMAIL)" << endl;
                comando="make email-menu";
                archivo="EMAIL/email-menu.txt";
                break;
            case 3:
                cout << "Has elegido la opción 3 (DNI-NIE)" << endl;
                comando="make dni-nie-menu";
                archivo="DNI-NIE/dni-nie-menu.txt";
                break;
            case 4:
                cout << "Has elegido la opción 4 (Cuentas Bancarias)" << endl;
                comando="make bancos-menu";
                archivo="Bancos/cuentas-menu.txt";
                break;
            default:
                cout << "Opción no válida. Intente de nuevo." << endl;
                opcion_elegida=INICIAL;
                break;
        }
    }

    cout << "Introduce texto (termina con -1 en una línea nueva):" << endl;

    // Leer entrada hasta que se introduzca -1
    while (getline(cin, line)) {
        if (line == "-1") {
            break;
        }
        ss << line << '\n';
    }

    // Pasar el contenido del stringstream al analizador léxico
    string input_data = ss.str();

    // Se abre el archivo definido (se crea si no existe) y con la funcion
    // ios::trunc se se sobreescribe si ya existía
    f_escritura.open(archivo, ios::trunc);
    if (!f_escritura){
        cerr << "Error de escritura del archivo (" << archivo << ")." << endl;
        exit(1);
    }

    // Se escribe el contenido del stringstream en el archivo
    f_escritura << input_data << endl;

    // Se cierre el archivo
    f_escritura.close();

    // Se ejecuta el comando definido
    system(comando.c_str());

    return 0;
}