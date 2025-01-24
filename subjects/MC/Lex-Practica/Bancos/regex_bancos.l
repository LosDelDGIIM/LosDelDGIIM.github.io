/**
 * @file regex.l
 * @brief Programa que analiza una serie de cadenas de texto, indicando cuales de ellas son
 *        cuentas bancarias, y si lo son, indica además a que banco pertenecen, banco que debe 
 *        ser recogido en un archio extensión .csv pasado por el usuario (en nuestro caso
 *        usaremos el archivo Cods_Bancos.csv).
 * 
 * @note
 *      Compilación:
 *          1. flex++ -o regex_bancos.cpp regex_bancos.l
 *          2. g++ -Wall -o regex_bancos regex_bancos.cpp -lfl
 *      Ejecución:
 *          1. ./regex_bancos
 * 
 * @author Arturo Olivares Martos
 * @author Joaquín Avilés de la Fuente
 * @date 18 de diciembre de 2024
 */
%option noyywrap

    /*---------------DECLARACIONES---------------*/
%{
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <set>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

ifstream fichero;   // Fichero a analizar

// Conjunto en el que almacenaremos las cuentas bancarias
set<string> cuentas_espanolas;
map<string, set<string>> cuentas_banco;

// Relacion: Código -> Nombre Banco
map<string, string> codigos_bancos;


%}
cuentaEspanola  ES[0-9]{2}(" "[0-9]{4}){5}

%%
    /* ---------------REGLAS--------------- */

{cuentaEspanola}    {   cuentas_espanolas.insert(yytext);}
\n                  {   ; }
[^ \n]+             {   cout << "\t- " << yytext << endl; }

%%
    /*---------------PROCEDIMIENTOS---------------*/

/**
 * @brief Función que divide una cadena en función de un delimitador.
 * 
 * Si el delimitador se encuentra entre comillas, se considera que el campo está entre comillas (no se divide).
 * 
 * @param str Cadena a dividir
 * @param delimiter Delimitador
 * 
 * @return vector<string> Vector con las cadenas resultantes
 */
vector<string> split(const string& str, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(str);
    bool entre_comillas = false;
    string campo;
    while (getline(tokenStream, token, delimiter)){
        if (token[0] == '"' && token[token.size()-1] != '"'){   // Inicio de campo entre comillas, pero no fin
            campo = token;
            entre_comillas = true;
        }
        else if (token[token.size()-1] == '"' && entre_comillas){   // Fin de campo entre comillas, pero no inicio
            campo += delimiter + token;
            entre_comillas = false;
            campo = campo.substr(1, campo.size()-2);
            tokens.push_back(campo);
        }
        else if (entre_comillas)    // Campo entre comillas, pero no inicio ni fin
            campo += delimiter + token;
        else{   // Campo normal
            if (token[0] == '"')    // Campo entero entre comillas
                token = token.substr(1, token.size()-2);
            
            tokens.push_back(token);
        }
    }
    return tokens;
}

/**
 * @brief Función que calcula el resto de un número al dividirlo por 97.
 * 
 * @param numero Número a dividir
 * 
 * @return int Resto de la división
 */
int calcularRestoPor97(const string& numero) {
    int resto = 0;

    // Necesario, puesto que el número puede ser muy grande y no ser representado por un int
    
    // Iteramos sobre cada carácter de la cadena
    for (size_t i = 0; i < numero.size(); i++) {

        // Obtenemos el carácter actual
        char digito_c = numero[i];
        
        // Convertimos el carácter a su valor numérico
        int digito = digito_c - '0';
        
        // Actualizamos el resto utilizando la aritmética modular
        resto = (resto * 10 + digito) % 97;
    }
    
    return resto;
}

/**
 * @brief Función que comprueba si una cuenta bancaria española es válida.
 * 
 * @param cuenta Cuenta bancaria española
 * 
 * @return true Si la cuenta es válida
 * @return false Si la cuenta no es válida
 * 
 * @pre La cuenta debe ser con un formato español correcto
 */
bool cuenta_espanola_valida(const string &cuenta){
    // Eliminamos los espacios
    string cuenta_sin_espacios = cuenta;
    cuenta_sin_espacios.erase(remove(cuenta_sin_espacios.begin(), cuenta_sin_espacios.end(), ' '), cuenta_sin_espacios.end());
    cuenta_sin_espacios.erase(remove(cuenta_sin_espacios.begin(), cuenta_sin_espacios.end(), '\n'), cuenta_sin_espacios.end());
    cuenta_sin_espacios.erase(remove(cuenta_sin_espacios.begin(), cuenta_sin_espacios.end(), '\t'), cuenta_sin_espacios.end());

    // Obtenemos el código de seguridad, los dígitos 2 y 3 (empezando desde 0)
    int codigo_seguridad = stoi(cuenta_sin_espacios.substr(2, 2));

    string CCC_str = cuenta_sin_espacios.substr(4);
    string aux = CCC_str + to_string('E' - 'A' + 10) + to_string('S' - 'A' + 10) + "00";
    
    int resto=calcularRestoPor97(aux);
    int codigo_calculado = 98 - resto;

    return codigo_seguridad == codigo_calculado;
}


/**
 * @brief Función que obtiene los códigos de los bancos a partir de un archivo.
 * 
 * @param archivo Archivo con los códigos de los bancos
 * 
 * @return map<string, string> Mapa con los códigos de los bancos
 */
map<string, string> obtener_codigos_bancos(const string &archivo){
    ifstream f_bancos;
    f_bancos.open(archivo);
    if (!f_bancos){
        cerr << "Error de lectura del archivo de códigos de bancos (" << archivo << ")." << endl;
        exit(1);
    }

    map<string, string> codigos_bancos;
    string linea;

    // Obtenemos en qué posición se encuentran los campos "CÓDIGO EUROPEO" y "NOMBRE"
    int pos_codigo=0, pos_nombre=0;
    getline(f_bancos, linea);
    vector<string> campos= split(linea, ',');
    for (size_t i = 0; i < campos.size(); i++){
        if (campos[i] == "CÓDIGO EUROPEO")
            pos_codigo = i;
        else if (campos[i] == "NOMBRE")
            pos_nombre = i;
    }

    // Guardamos los códigos y nombres de los bancos
    while (getline(f_bancos, linea)){
        campos = split(linea, ',');
        codigos_bancos[campos[pos_codigo]] = campos[pos_nombre];
    }

    f_bancos.close();
    return codigos_bancos;
}


int main (int argc, char *argv[]){
    // Comprobamos que se ha introducido un archivo
    if (argc == 3){
        fichero.open (argv[2]);
        if (!fichero){
            cerr << "Error de lecura del archivo de datos." << endl;
            exit (1);
        }
    }
    else{
        cerr << "Error en la introducción de argumentos." << endl;
        exit (1);
    }

    // Obtenemos los códigos de los bancos
    codigos_bancos = obtener_codigos_bancos(argv[1]);


    cout << endl << endl << "Cadenas leidas que no pueden ser cuentas españolas: " << endl;
    yyFlexLexer flujo (&fichero,0);
    flujo.yylex();

    set<string> cuentas_espanolas_no_validas;

    // Cada cuenta española, vemos si es válida
    // Lo haremos con un bucle while hasta llegar al final
    // Debemos tener en cuenta que al eliminar un elemento a función .erase(iterator)
    // devuelve el iterador apuntando al siguiente elemento, por lo que
    // no debemos sumar nada a it. Solo se suma si no se elimina elemento.
    auto it = cuentas_espanolas.begin();
    while (it != cuentas_espanolas.end()){

        if (!cuenta_espanola_valida(*it)){
            // No es válida. La eliminamos de cuentas españolas, y la añadimos al conjunto de cuentas no válidas
            cuentas_espanolas_no_validas.insert(*it); 
            it=cuentas_espanolas.erase(it);
        }
        else    // Es válida, pasamos a la siguiente
            it++;
    }

    // Cada cuenta española, la asignamos a un banco
    for (auto it = cuentas_espanolas.begin(); it != cuentas_espanolas.end(); it++){

        string nombre_banco = "Banco Desconocido";
        string codigo_banco = "ES"+it->substr(5, 4);

        if (codigos_bancos.find(codigo_banco) != codigos_bancos.end())
            nombre_banco = codigos_bancos[codigo_banco];
       
        cuentas_banco[nombre_banco].insert(*it);
    }

    // Mostramos los resultados
    cout << endl;
    cout << "Cuentas españolas no válidas: " << endl;
    for (auto it = cuentas_espanolas_no_validas.begin(); it != cuentas_espanolas_no_validas.end(); it++)
        cout << "\t-" << *it << endl;
    cout << endl;
    cout << "Cuentas por banco: " << endl;
    for (auto it = cuentas_banco.begin(); it != cuentas_banco.end(); it++){
        cout << "- " << it->first << ": " << endl;
        for (auto it2 = it->second.begin(); it2 != it->second.end(); it2++)
            cout << "\t- " << *it2 << endl;
        cout << endl;
    }
    return 0;
}