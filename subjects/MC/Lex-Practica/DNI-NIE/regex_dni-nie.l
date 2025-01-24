/**
 * @file regex_dni-nie.l
 * @brief Programa que analiza una serie de cadenas de texto, indicando cuales de ellas
 *        son DNI's y NIE's válidos.
 * 
 * @note
 *      Compilación:
 *          1. flex++ -o regex_dni-nie.cpp regex_dni-nie.l
 *          2. g++ -Wall -o regex_dni-nie regex_dni-nie.cpp -lfl
 *      Ejecución:
 *          1. ./regex_dni-nie_exe
 * 
 * @author Arturo Olivares Martos
 * @author Joaquín Avilés de la Fuente
 * @date 18 de diciembre de 2024
 */

    /*---------------DECLARACIONES---------------*/
%{

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

ifstream fichero;

// Conjunto en el que almacenaremos los DNI's y los NIE's
vector<string> dnis, nies;

vector<string> dnis_validos, nies_validos;

%}

%option noyywrap

DNI  [0-9]{8}(" "|"-")?[A-Z]
NIE  [XYZ](" "|"-")?[0-9]{7}(" "|"-")?[A-Z]

%%
    /* ---------------REGLAS--------------- */

{DNI}       {dnis.push_back(yytext);}
{NIE}       {nies.push_back(yytext);}
\n                  {   ; }
[^ \n]+             {   cout << "\t- " << yytext << endl; }

%%
    /*---------------PROCEDIMIENTOS---------------*/

/**
 * @brief Función que comprueba si un DNI es válido.
 * 
 * @param dni DNI a comprobar
 * @param CADENA Cadena de caracteres que se utilizará para calcular la letra del DNI
 * @return true Si el DNI es válido
 * @return false Si el DNI no es válido
 */
bool dni_valido(const string& dni, const string &CADENA, const int divisor){
    int num=stoi(dni.substr(0,8));
    int resto=num%divisor;
    char letra;
    if(dni[8] == ' ' || dni[8] == '-'){
        letra=dni[9];
    }
    else
        letra=dni[8];

    return letra==CADENA[resto];
}

int main (int argc, char *argv[]){

    // Variables necesarias para el cálculo de la letra del DNI
    // Consultar https://www.interior.gob.es/opencms/es/servicios-al-ciudadano/tramites-y-gestiones/dni/calculo-del-digito-de-control-del-nif-nie/
    const string CADENA="TRWAGMYFPDXBNJZSQVHLCKE";
    const int DIVISOR=23;

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


    cout << "Cadenas leidas que no pueden ser DNI's ni NIE's: " << endl;
    yyFlexLexer flujo (&fichero,0);
    flujo.yylex();
    cout << endl;

    string dni;
    
    // Mostramos los DNI's leidos y añadimos los que sean realmente
    // DNI's al vector nies_validos
    auto it=dnis.begin();
    while(it!=dnis.end()){
        string dni=*it;
        if(dni_valido(dni, CADENA, DIVISOR)){
            dnis_validos.push_back(dni);
            dnis.erase(it);
        }
        else
            it++;
    }

    // Estudiamos cada NIE leido y añadimos los que sean realmente
    // NIE's al vector nies_validos
    it=nies.begin();
    string nie, nie_aux;
    while(it!=nies.end()){
        nie=*it;

        // Hacemos una copia del NIE para poder modificarlo
        nie_aux = nie;

        // En función de la primera letra pondremos un número inicial
        // u otro y haremos la comprobación de si es un NIE válido
        // igual que si fuera un DNI cambiando dicha letra por el número
        // Se sustituyen las letras X, Y y Z por 0, 1 y 2 respectivamente
       nie_aux[0]= '0' + (nie_aux[0] - 'X');

        // Si el NIE tiene un espacio o un guión después de la letra, lo eliminamos
        if(nie_aux[1]== ' ' || nie_aux[1] == '-'){
            nie_aux.erase(nie_aux.begin()+1);
        }


        if(dni_valido(nie_aux, CADENA, DIVISOR)){
            nies_validos.push_back(nie);
            nies.erase(it);
        }
        else
            it++;
    }

    cout << "DNI's no válidos: " << endl;
    // mostramos los dnis restantes en dnis
    for(auto it=dnis.begin(); it<dnis.end(); it++){
        cout << "\t- " << *it << endl;
    }
    cout << endl;

    cout << "NIE's no válidos: " << endl;
    // mostramos los nies restantes en nies
    for(auto it=nies.begin(); it<nies.end(); it++){
        cout << "\t- " << *it << endl;
    }
    cout << endl;

    cout << "DNI's validos: " << endl;
    for(auto it=dnis_validos.begin(); it<dnis_validos.end(); it++){
        cout << "\t- " << *it << endl;
    }
    cout << endl;

    cout << "NIE's validos: " << endl;
    for(auto it=nies_validos.begin(); it<nies_validos.end(); it++){
        cout << "\t- " << *it << endl;
    }

    return 0;
}