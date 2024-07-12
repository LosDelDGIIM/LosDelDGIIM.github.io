/* Recibe un archivo como entrada, que tiene el formato:
"
N
k
n1 n2 ... nN
"
Donde N es la cantidad de bienes, k es el número de bienes que puede llevar un hijo, y n1, n2, ..., nN son los valores de los bienes.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <set>

using namespace std;

#define DEBUG_PRINT 0 // If 1, prints the values of the goods, otherwise prints the time elapsed. Default is time elapsed.

int main (int argc, char *argv[]) {
    #include <fstream> // Include the necessary header file for std::ifstream
    #include <ios> // Include the necessary header file for std::ios::in

    if (argc < 2) {
        std::cerr << "Error: faltan parametros\n";
        std::cerr << "<nombre_fichero_entrada>" << std::endl;
        return -1;
    }

    std::ifstream fin(argv[1]);
    if (!fin) {
        std::cerr << "Error: no se pudo abrir el archivo " << argv[1] << std::endl;
        return -1;
    }

    clock_t tStart = clock();

    int N, k;
    fin >> N >> k;
    std::set <int> values; // Set to store the values of the goods
    for (int i = 0; i < N; ++i) {
        int n;
        fin >> n;
        values.insert(n);
    }
    //Ya los tenemos ordenados de menor a mayor, a continuación, elegimos el vector que será del hijo predilecto (k<=N/2?)

    std::vector <int> notPreSon;
    std::vector <int> preSon;

    if (k<=N/2){ //Si k es menor, el hijo predilecto tiene n-k elementos
        for (int i = 0; i < k; ++i){
            notPreSon.push_back(*values.begin());
            values.erase(values.begin());
        }
        while (!values.empty()){
            preSon.push_back(*values.begin());
            values.erase(values.begin());
        }
    }
    else{
        for (int i = 0; i < N-k; ++i){
            notPreSon.push_back(*values.begin());
            values.erase(values.begin());
        }
        while (!values.empty()){
            preSon.push_back(*values.begin());
            values.erase(values.begin());
        }
    }

    clock_t tEnd = clock();
    double elapsed = double(tEnd - tStart) / CLOCKS_PER_SEC;


    //Imprimimos los valores 
    if (DEBUG_PRINT){
        std::cout << N << " " << k << std::endl;
        int sumaNPS = 0, sumaPS = 0;
        for (int i = 0; i < notPreSon.size(); ++i){
            std::cout << notPreSon[i] << " ";
            sumaNPS += notPreSon[i];
        }
        cout << endl << "Suma no predilecto: " << sumaNPS << endl;
        std::cout << std::endl << "PRESON" << std::endl;
        for (int i = 0; i < preSon.size(); ++i){
            std::cout << preSon[i] << " ";
            sumaPS += preSon[i];
        }
        std::cout << std::endl << "Suma predilecto: " << sumaPS << std::endl;
    }
    else{
        std::cout << N << " " <<  elapsed << std::endl;
    }
    




    
    return 0;
}