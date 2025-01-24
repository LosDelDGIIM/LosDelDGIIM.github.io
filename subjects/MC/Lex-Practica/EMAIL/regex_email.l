/**
 * @file regex_email.l
 * @brief Programa que analiza una serie de cadenas de texto, indicando cuales de ellas
 *        son correos electrónicos válidos, basandonos en las siguientes reglas y viendo la 
 *        la expresión regular definida más abajo.
 *
 * @param fichero Archivo de texto que contiene las cadenas a analizar.
 * 
 * Reglas para los correos electrónicos:
 *  - Deben contener un conjunto de caracteres alfanuméricos seguido de un @.
 *  - Solo se permiten caracteres alfanuméricos del alfabeto inglés: de la 'a' a la 'z'.
 *  - Después del @, debe haber un conjunto de caracteres alfanuméricos seguido de un punto,
 *    seguido del dominio del correo electrónico (com, es, org).
 *  - No se permiten puntos ni guiones al inicio y final del correo (final del nombre y del dominio),
 *    y siempre irán seguidos de un conjunto de caracteres alfanuméricos.
 *  - No se permiten dos puntos o guiones seguidos.
 *  - Detrás de @ habrá caracteres alfanuméricos, pero no podrá haber solo números.
 * 
 *
 * @note
 *      Compilación:
 *          1. flex++ -o regex_email.cpp regex_email.l
 *          2. g++ -Wall -o regex_email regex_email.cpp
 *      Ejecución:
 *          1. ./regex_email_exe <fichero>
 *
 *  Notar que esta compilación y ejecución se hace mediante make email , pues
 *  al usar el menu se hará otro tipo de compilación y ejecución, la cual está definida
 *  en menu.l y makefile, pero es dependiente únicamente del menu.
 *
 * @details
 *
 * @author Arturo Olivares Martos
 * @author Joaquín Avilés de la Fuente
 * @date 18 de diciembre de 2024
 */


    /*---------------DECLARACIONES---------------*/
%{

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

ifstream fichero;

// Conjunto en el que almacenaremos los DNI's y los NIE's
vector<string> emails;

%}

%option noyywrap

EMAIL   [a-zA-Z0-9]+((\.|-)?[a-zA-Z0-9]+)*@[0-9]*[a-zA-Z]+[a-zA-Z0-9]*\.(com|es|org)

%%
    /* ---------------REGLAS--------------- */

{EMAIL}             {emails.push_back(yytext);}
\n                  {   ; }
[^ \n]+             {   cout << "\t- " << yytext << endl; }

%%
    /*---------------PROCEDIMIENTOS---------------*/

int main (int argc, char *argv[]){

    cout << endl;

    // Comprobamos que se haya introducido un argumento
    if (argc == 2){
        fichero.open (argv[1]);
        if (!fichero){
            cerr << "Error de lecura del archivo de datos." << endl;
            exit (1);
        }
    }
    // En caso contrario mandamos error y no ejecutamos nada
    else{
        cerr << "Error en la introducción de argumentos." << endl;
        exit (1);
    }

    // Leemos el .txt y mostramos las cadenas que no son emails
    cout << "Cadenas leídas que no pueden ser emails:" << endl;
    yyFlexLexer flujo (&fichero,0);
    flujo.yylex();
    cout << endl;

    // Mostramos los emails válidos
    cout << "Emails válidos:" << endl;

    for (auto it=emails.begin(); it!=emails.end(); it++){
        cout << "\t- " << *it << endl;
    }
    
    return 0;
}
