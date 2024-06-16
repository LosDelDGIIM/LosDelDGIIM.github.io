/**
 * @file Ejercicio3.cpp
 * @author Arturo Olivares Martos
 * @brief Ejericio 3 del Examen 2 (disponible en https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/tree/main/subjects/Algorítmica/Exámenes/Ex02)
 * 
 * *Enunciado:*
 * Estamos en una posición $(x, y)$ de un laberinto bidimensional representado por una matriz $M$ de $f$ filas y $c$ columnas.
 * De cada casilla se puede viajar a cualquiera de las colindantes con la casilla actual, en la misma fila o la misma columna,
 *      siempre que la casilla destino sea transitable.
 * Los posibles valores de las casillas son $M(i, j) = t$ (transitable), $M(i, j) = n$ (no transitable) y $M(i, j) = s$ (salida).
 * 
 * Sabiendo que disponemos del mapa del laberinto a priori, y que pueden existir varias salidas del mismo,
 *      plantee un algoritmo eficiente que devuelva el camino a la salida más próxima a la casilla inicial $(x, y)$.
 * 
 * NOTA: El coste de viajar de una casilla a otra es siempre 1.
 * _______________________________________________________________________________________________________________________________________________________________
 * 
 * Resolveremos el problema mediante un algoritmo de vuelta atrás (backtracking) que recorrerá el laberinto en busca de la salida más cercana.
 *  
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;



typedef pair<int, int> Casilla;
typedef pair<int, int> Direccion;

/**
 * @brief Clase Laberinto. Representa un laberinto con muros y pasillos y una casilla de salida
 */
class Laberinto{

private:

    static const char TRANSITABLE;   // Caracter que representa una casilla transitable
    static const char NO_TRANSITABLE;// Caracter que representa una casilla no transitable
    static const char SALIDA;        // Caracter que representa una casilla de salida

    static const vector<Direccion> DIRECCIONES;

    vector<vector<char>> laberinto;      // Vector bidimensional que representa el laberinto

public:

    /**
     * @brief Constructor de la clase Laberinto
     * 
     * @param fils Número de filas del laberinto
     * @param cols Número de columnas del laberinto
     * @param exit Casilla de salida
     */
    Laberinto(int fils, int cols, const Casilla& exit){

        laberinto = vector<vector<char>>(fils, vector<char>(cols, Laberinto::TRANSITABLE));
        laberinto[exit.first][exit.second] = Laberinto::SALIDA;
    }

    /**
     * @brief Get the Direcciones object
     * 
     * @return const vector<Direccion>&  Vector de direcciones posibles
     */
    static const vector<Direccion>& getDirecciones(){
        return Laberinto::DIRECCIONES;
    }

    /**
     * @brief Set the Casilla object
     * 
     * @param cas Casilla a modificar
     * @param c Caracter a añadir
     */
    void setCasilla(const Casilla& cas, char c){
        laberinto[cas.first][cas.second] = c;
    }

    /**
     * @brief Añade un muro en una casilla
     * 
     * @param c Casilla donde añadir el muro
     */
    void addMuro(const Casilla& c){
        setCasilla(c, Laberinto::NO_TRANSITABLE);
    }

    /**
     * @brief Comprueba si una casilla está libre
     * 
     * @param c Casilla a comprobar
     * @return true Si está libre (está dentro de los límites y no es un muro)
     * @return false En caso contrario
     */
    bool casillaLibre(const Casilla& c) const{
        return posOK(c) && laberinto[c.first][c.second] != Laberinto::NO_TRANSITABLE;
    }

    /**
     * @brief Comprueba si una casilla es la salida
     * 
     * @param c Casilla a comprobar
     * @return true Si es la salida
     * @return false En caso contrario
     */
    bool casillaSalida(const Casilla& c) const{
        return posOK(c) && laberinto[c.first][c.second] == Laberinto::SALIDA;
    }

    /**
     * @brief Devuelve una representación en string del laberinto
     * 
     * @return string Representación en string del laberinto
     */
    string toString() const{
        string res = "";
        for (int i=0; i<laberinto.size(); ++i){
            for (int j=0; j<laberinto[i].size(); ++j){
                if (laberinto[i][j] == Laberinto::TRANSITABLE)
                    res += ".";
                else if (laberinto[i][j] == Laberinto::NO_TRANSITABLE)
                    res += "X";
                else
                    res += laberinto[i][j];
                res += " ";
            }
            res += "\n";
        }
        return res;
    }

private:
    /**
     * @brief Comprueba si una casilla está dentro de los límites del laberinto
     * 
     * @param c Casilla a comprobar
     * @return true  Si está dentro de los límites
     * @return false  En caso contrario
     */
    bool posOK(const Casilla& c) const{
        return 0 <= c.first && c.first < laberinto.size() && 0 <= c.second && c.second < laberinto[0].size();
    }
};
const vector<pair<int, int>> Laberinto::DIRECCIONES = {
    {1, 0},         // Abajo
    {-1, 0},        // Arriba
    {0, 1},         // Derecha
    {0, -1}         // Izquierda
};
const char Laberinto::TRANSITABLE = 't';
const char Laberinto::NO_TRANSITABLE = 'n';
const char Laberinto::SALIDA = 's';



/**
 * @brief Clase Nodo. Representa un nodo en el árbol de exploración del laberinto
 *      con un camino y su longitud
 */
class Nodo{

    public:
        // Se dejan públicos para simplificar el código
        vector<Casilla> camino;
        int longitud;

    public:
        /**
         * @brief Devuelve una representación en string del camino
         * 
         * @param lab Laberinto a resolver, donde se marcarán las casillas del camino
         * @pre camino.size() > 0
         * @return string Representación en string del camino
         */
        string toString(const Laberinto& lab){
            const char CAMINO = 'C';
            const char INICIO = 'I';
            Laberinto lab_modificado = lab;
            lab_modificado.setCasilla(camino.front(), INICIO);
            for (auto it = ++camino.begin(); it != --camino.end(); ++it){
                lab_modificado.setCasilla(*it, CAMINO);
            }
            return lab_modificado.toString();
        }
        
        /**
         * @brief Comprueba si una casilla es factible para avanzar
         * 
         * @param lab  Laberinto a resolver, con las casillas ocupadas
         * @param nueva Casilla a comprobar si es factible
         * @return true Si está libre y no está en el camino
         * @return false En caso contrario
         */
        bool factible(const Laberinto& lab, const Casilla& nueva){
            return lab.casillaLibre(nueva) && (find(camino.begin(), camino.end(), nueva) == camino.end());
        }
};

/**
 * @brief Función recursiva que resuelve un laberinto mediante backtracking
 * 
 * @param lab Laberinto a resolver
 * @param e_nodo Nodo actual en exploración
 * @param nodo_sol Nodo solución, con el camino más corto encontrado hasta el momento
 */
void resolverLaberinto(const Laberinto& lab, Nodo &e_nodo, Nodo &nodo_sol){

    // Caso base: hemos llegado a la salida
    if (lab.casillaSalida(e_nodo.camino.back())){
        
        // Si el camino actual es más corto que el mejor camino encontrado hasta ahora
        if (e_nodo.longitud < nodo_sol.longitud)
            nodo_sol = e_nodo;
    }
    else{
        // Movimientos posibles
        for (auto dir : Laberinto::getDirecciones()){
            Casilla ultima = e_nodo.camino.back();

            // Desplazamiento en la dirección correspondiente
            Casilla nueva = {ultima.first + dir.first, ultima.second + dir.second};

            // Si la casilla es factible, podemos avanzar
            if (e_nodo.factible(lab, nueva)){
                e_nodo.camino.push_back(nueva);
                e_nodo.longitud++;

                // Si queremos considerarla (no es una solución peor que la actual), seguimos explorando
                if(e_nodo.longitud < nodo_sol.longitud)
                    resolverLaberinto(lab, e_nodo, nodo_sol);

                // Deshacemos el movimiento
                e_nodo.camino.pop_back();
                e_nodo.longitud--;
            }
        } // Fin bucle direcciones
    }

    
}

/**
 * @brief Función que resuelve un laberinto mediante backtracking
 * 
 * @param lab Laberinto a resolver
 * @param inicio Casilla de inicio
 */
void resolverLaberinto(const Laberinto& lab, const Casilla& inicio){
    
    // Nodo inicial
    Nodo nodo_inicial;
    nodo_inicial.camino.push_back(inicio);
    nodo_inicial.longitud = 0;

    // Nodo solución, inicialmente con longitud infinita
    Nodo nodo_sol;
    nodo_sol.longitud = INT_MAX;

    // Llamada a la función recursiva
    resolverLaberinto(lab, nodo_inicial, nodo_sol);
    if (nodo_sol.camino.size() < 1){
        cout << "No hay camino posible desde la casilla (" << inicio.first << ", " << inicio.second << ")" << endl;
    }
    else{
        cout << "Camino encontrado: " << endl;
        cout << nodo_sol.toString(lab) << endl;
        cout << "Longitud del camino: " << nodo_sol.longitud << endl;
    }
}


int main(int argc, char **argv){

    // Laberinto de 7x7 con muchos muros y una salida en la casilla (6, 6)
    Laberinto lab(7, 7, {6, 6});
    lab.addMuro({1,0});
    lab.addMuro({5,2});
    lab.addMuro({4,6});
    lab.addMuro({0,4});
    lab.addMuro({1,1});
    lab.addMuro({3,4});
    lab.addMuro({3,2});
    lab.addMuro({0,5});
    lab.addMuro({6,2});
    lab.addMuro({3,3});

    cout << "Laberinto: " << endl;
    cout << lab.toString() << endl << endl;

    resolverLaberinto(lab, {0, 0});

    return 0;
}


