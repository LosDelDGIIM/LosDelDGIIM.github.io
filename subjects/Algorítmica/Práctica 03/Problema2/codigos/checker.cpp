#include <utility>
#include <vector>
#include <iostream>
#include <algorithm>
#include <iomanip>

using namespace std;

/**
 * @brief Estructura que permite gestionar la información relativa a un examen
*/
struct info_exam {

    int start_time;      // [0-minutos_del_día[ , indica en qué minuto 
                         // del día empieza el examen
    int duration;        // duración del examen


    // métodos

    // constructores
    info_exam(int hour=0, int minutes=0, int duration=0){
        set_info_exam(hour, minutes, duration);
    }

    info_exam(int minutes, int duration): duration(duration), start_time(minutes) {}

    /**
     * @brief Modifica la información del examen
     * @param start_time Tiempo de inicio del examen (mínuto del día)
     * @param duration Duración del examen
    */
    void set_info_exam(int start_time, int duration) {
        this->start_time = start_time;
        this->duration = duration;
    }

    /**
     * @brief Modifica la información del examen dado la hora de inicio 
     * en formato usual
     * @param h hora del día en que empieza el examen
     * @param m minuto de la hora en que empieza
     * @param duration Duración del examen
    */

    void set_info_exam(int h, int m, int duration) {
        this->start_time = hour2minFormat(h, m);
        this->duration = duration;
    }
    
    /**
     * @brief Devuelve la hora de finalización del examen en formato "mínuto del día" 
    */
    int get_finish_time(void) const {
        return start_time + duration;
    }
    
    /**
     * @brief Devuelve por referencia la hora de finalición del examen en
     * formato usual
     * @param h hora en que termina el examen
     * @param m minuto de la hora en que termina el examen
    */
    void get_finish_time(int &h, int &m) const{
        int aux = start_time + duration;
        min2hourFormat(aux, h, m);
    }

    /**
     * @brief Indica si el examen @p e puede realizarse/tiene lugar tras 
     * la finalización examen implícito
     * @return true si se puede, false en caso contrario
    */

    bool canGoAfter(info_exam e) {
        return get_finish_time() <= e.start_time;
    }

    /**
     * @brief Operador relacional que compara si la hora de inicio del 
     * examen @p e es posterior al del implícito
    */

    bool operator<(info_exam e) {
        return this->start_time < e.start_time;
    }
    

    private:

    /**
     * @brief Dado los argumentos, @p hour , @p minutes retorna 
     * la hora que indican en formato "minutos del día"
     * @param hour la hora de la hora que indica
     * @param minutes los minutos de la hora que indica
     * @return la equivalencia de la hora indicada en formato "mínutos del día"
    */

    int hour2minFormat(int hour, int minutes) const{
        return hour*60 + minutes;
    }

    /**
     * @brief Dado una hora en formato "mínutos del día", retorna 
     * por referencia su equivalente en formato usual
     * @param minutes la hora expresada en formato "mínutos del día"
     * @param h la hora de la hora que indica
     * @param m los minutos de la hora que indica
    */
    void min2hourFormat(int minutes, int& h, int& m) const{
        h = minutes/60;
        m = minutes%60;
    }

    public:

    /**
     * @brief Operador de entrada para una estructura info_exam, lee en 
     * formato "hora:minutos"
     * @param inputStream el flujo de entrada
     * @param e objeto info_exam a leer
     * @return referencia al flujo de entrada
    */

    friend std::istream& operator>>(std::istream& inputStream, info_exam& e){

        int h, m, duration;
        char c;
        inputStream >> h >> c >> m >> duration;

        e.set_info_exam(h, m, duration);

        return inputStream;
    }

    /**
     * @brief Operador de salida para una estructura info_exam, imprime 
     * en formato hora:minutos
     * @param outputStream flujo de salida
     * @param e estructura info_exam a imprimir
     * @return referencia al flujo de salida
    */
    friend ostream& operator<<(ostream& outputStream, const info_exam& e){

        int h, m;
        e.min2hourFormat(e.start_time, h,m);
        outputStream << "[" << h << ":" << setfill('0') << setw(2) << right << m << "," << e.duration << " min]";
        return outputStream;
    }

};

/**
 * @brief Algoritmo greedy que determina el máximo número de exámenes que se solapan 
 * en el tiempo, que también coincide con el mínimo número de aulas a reservar.
 * @param all_exams Los examenes a realizar
 * @return el número máximo de examenes que se solapan en el tiempo
*/

int greedy(vector<info_exam> & all_exams) {

    // Construir estructura de eventos

    vector<pair<int,int>> events;

    for (int i=0; i < all_exams.size(); ++i) {
        events.emplace_back(all_exams[i].start_time, 1);            // 1: Empieza un examen
        events.emplace_back(all_exams[i].get_finish_time(), -1);    //-1: Termina un examen
    }

    // Se ordenan los eventos 
    sort(events.begin(), events.end(), [](pair<int,int> a, pair<int,int> b)->bool{ return a.first < b.first;});    

    int count = 0;          // Número de exámenes que se solapan en el momento
    int max_count = 0;      // Máximo número de examenes que se han solapado hasta el momento

    for (int i=0; i < events.size(); ++i) {
        count += events[i].second;

        if (count > max_count) {
            max_count = count;
        }
    }

    return max_count;
}

int main (int argc, char* argv[]) {

    int n;

    std::cin >> n;

    info_exam aux;
    vector<info_exam> all_exams;

    for (int i=0; i < n; i++) {
        std::cin >> aux;
        all_exams.push_back(aux);
    }

    std::cout << endl << greedy(all_exams) << endl;

    return 0;

}