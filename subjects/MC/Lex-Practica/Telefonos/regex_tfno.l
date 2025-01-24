/**
 * @file regex_tfno.l
 * @brief Programa que analiza una serie de cadenas de texto, indicando cuales de ellas son
 *        números de teléfono válidos en España.
 *
 * @param fichero Archivo de texto que contiene las cadenas a analizar.
 * @note
 *      Compilación:
 *          1. flex++ -o regex_tfno.cpp regex_tfno.l
 *          2. g++ -Wall -o regex_tfno regex_tfno.cpp -lfl
 *      Ejecución:
 *          1. ./regex_tfno_exe <fichero>
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
map<string, set<string>> tfno_pais;


%}
tfno_espanol_grupos3  ((00|"+")34(" ")?)?([0-9]{3}(" ")?){3}
tfno_espanol_grupos2  ((00|"+")34(" ")?)?([0-9]{3}(" ")?){1}([0-9]{2}(" ")?){3}

%%
    /* ---------------REGLAS--------------- */

^{tfno_espanol_grupos3}|{tfno_espanol_grupos2}$   {   tfno_pais["España"].insert(yytext);}
\n                  {   ; }
[^ \n]+             {   cout << "\t- " << yytext << endl; }

%%
    /*---------------PROCEDIMIENTOS---------------*/



int main (int argc, char *argv[]){
    // Comprobamos que se ha introducido un archivo
    if (argc == 2){
        fichero.open (argv[1]);
        if (!fichero){
            cerr << "Error de lecura del archivo de datos." << endl;
            exit (1);
        }
    }
    else{
        cerr << "Error en la introducción de argumentos." << endl;
        exit (1);
    }


    cout << endl << endl << "Cadenas leidas no identificadas: " << endl;
    yyFlexLexer flujo (&fichero,0);
    flujo.yylex();
    cout << endl;

    // Mostramos los resultados
    cout << "Números por Pais: " << endl;
    for (auto it = tfno_pais.begin(); it != tfno_pais.end(); it++){
        cout << "- " << it->first << ": " << endl;
        for (auto it2 = it->second.begin(); it2 != it->second.end(); it2++)
            cout << "\t- " << *it2 << endl;
        cout << endl;
    }
    return 0;
}