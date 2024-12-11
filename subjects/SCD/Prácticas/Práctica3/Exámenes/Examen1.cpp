/**
 * @file Examen1.cpp
 * @author Arturo Olivares Martos
 * 
 * @details La descripción, junto con el enunciado, se encuentran en   ./ExamenI.md
 * 
 * https://github.com/LosDelDGIIM/LosDelDGIIM.github.io/blob/main/subjects/SCD/Prácticas/Práctica3/Exámenes/Examen1.md
 */
#include <iostream>
#include <string>
#include <random>
#include <chrono>
#include <thread>
#include <mpi.h>
using namespace std ;

const int   ID_YOSHI = 0,
            ID_MARIO = 1,
            ID_PEACH = 2,
            num_jugadores = 2,
            num_procesos_esperados = num_jugadores + 1;

const double TERMINAR = -1;

const int   tag_jugador = 1,
            tag_yoshi = 2;


/**
 * @brief Función que produce un número aleatorio real entre dos valores.
 *          El número aleatorio se genera en el rango [min, max].
 * 
 * @param min Valor mínimo. Incluido.
 * @param max Valor máximo. Incluido.
 * 
 * @return double Número aleatorio generado.
 */
double aleatorio_real(int min, int max) {
   static const int precision = 1e3;
	static default_random_engine generador( (random_device())() );
	static uniform_int_distribution<int> distribucion_uniforme( 0, precision ) ;
   double valor_aleatorio = distribucion_uniforme( generador )/((double)precision);
	return min + valor_aleatorio * (max - min);
}

/**
 * @brief Función que produce un número aleatorio entero entre dos valores.
 *         El número aleatorio se genera en el rango [min, max].
 * 
 * @param min Valor mínimo. Incluido.
 * @param max Valor máximo. Incluido.
 * @return int Número aleatorio generado.
 */
int aleatorio_entero(int min, int max) {
   return round(aleatorio_real(min, max));
}

/**
 * @brief Función que bloquea el hilo actual durante un número de milisegundos.
 * 
 * @param num_milisegundos Número de milisegundos a bloquear.
 */
void bloquear(int num_milisegundos) {
   chrono::milliseconds duracion(num_milisegundos);
   this_thread::sleep_for(duracion);
}

/**
 * @brief Dado un id, devuelve el nombre del jugador/NPC correspondiente.
 * 
 * @param id ID del jugador/NPC.
 * @return string Nombre del jugador/NPC.
 */
string id_a_nombre(int id) {
   switch (id) {
      case ID_YOSHI:
         return "Yoshi";
      case ID_MARIO:
         return "Mario";
      case ID_PEACH:
         return "Peach";
      default:
         return "Desconocido";
   }
}


/**
 * @brief Función que ejecuta la hebra de Yoshi.
 * 
 */
void funcion_yoshi() {
   const int   num_reposiciones = 10,
               num_tartas_max_por_reposicion = 2,
               peso_minimo_tarta = 1,
               peso_maximo_tarta = 10;
   
   int puntos[num_jugadores] = {0};

   MPI_Status estado;

   // Cada ronda
   for (int i = 0; i < num_reposiciones; i++) {

      // Enviamos las tartas a los jugadores
      for (int id_jugador = 1; id_jugador <= num_jugadores; id_jugador++) {
         // Número de tartas a enviar al jugador j
         int num_tartas = aleatorio_entero(1, num_tartas_max_por_reposicion);

         // Pesos de las tartas a enviar
         double * pesos_tartas = new double[num_tartas];
         for (int k = 0; k < num_tartas; k++) 
            pesos_tartas[k] = aleatorio_real(peso_minimo_tarta, peso_maximo_tarta);

         // Producción de tartas
         bloquear(aleatorio_entero(10, 200));
         cout << "Yoshi: Número de tartas producidas para " << id_a_nombre(id_jugador) << ": " << num_tartas << endl;
         
         // Enviamos las tartas
         MPI_Send(pesos_tartas, num_tartas, MPI_DOUBLE, id_jugador, tag_yoshi, MPI_COMM_WORLD);

         delete[] pesos_tartas;
      }

      // Esperamos a recibir los pesos comidos por los jugadores
      double peso_comido_jugador;
      double peso_comido_max = 0;
      int id_ganador_ronda;
      for (int j = 1; j <= num_jugadores; j++) {
         MPI_Recv(&peso_comido_jugador, 1, MPI_DOUBLE, MPI_ANY_SOURCE, tag_jugador, MPI_COMM_WORLD, &estado);
         if (peso_comido_jugador > peso_comido_max) {
            peso_comido_max = peso_comido_jugador;
            id_ganador_ronda = estado.MPI_SOURCE;
         }
      }

      // Sumamos un punto al jugador que más haya comido. Si hay empate, al que haya comido antes
      puntos[id_ganador_ronda - 1]++;

      // Informamos de los puntos actuales
      cout << "Yoshi: Punto para " << id_a_nombre(id_ganador_ronda) << endl;
      cout << "Yoshi: Puntos en la ronda " << i+1 << ": " << endl;
      for (int j = 0; j < num_jugadores; j++)
         cout << "\t- " << id_a_nombre(j+1) << ": " << puntos[j] << " puntos." << endl;
      cout << "---------------------------------" << endl;
   }

   // Finalizamos el juego
   for (int j = 1; j <= num_jugadores; j++)
      MPI_Send(&TERMINAR, 1, MPI_DOUBLE, j, tag_yoshi, MPI_COMM_WORLD);
   

   // Informamos del ganador. Si hay empate, se queda con el que se apuntase antes
   int id_ganador = 0;
   for (int j = 0; j < num_jugadores; j++)
      if (puntos[j] > puntos[id_ganador])
         id_ganador = j;
   

   cout << "Yoshi: ¡El ganador es " << id_a_nombre(id_ganador + 1) << "!" << endl;
}

/**
 * @brief Función que ejecuta la hebra de Mario o Peach.
 * 
 * @param id_jugador ID del jugador.
 */
void funcion_player(int id_jugador) {
   
   MPI_Status estado;
   int num_tartas;
   double peso_total, peso_comido;

   while (true) {

      // Esperamos a recibir el número de tartas
      MPI_Probe(ID_YOSHI, tag_yoshi, MPI_COMM_WORLD, &estado);
      MPI_Get_count(&estado, MPI_DOUBLE, &num_tartas);

      // Una vez sabemos cuántas tartas hay, creamos un vector para almacenar sus pesos
      double * pesos_tartas = new double[num_tartas];

      // Recibimos las tartas
      MPI_Recv(pesos_tartas, num_tartas, MPI_DOUBLE, estado.MPI_SOURCE, estado.MPI_TAG, MPI_COMM_WORLD, &estado);

      // Comprobamos si se ha recibido el mensaje de terminar
      if (num_tartas == 1 && pesos_tartas[0] == TERMINAR) {
         cout << id_a_nombre(id_jugador) << ": ¡Termino!" << endl;
         delete[] pesos_tartas;
         break;
      }

      // Informamos de las tartas recibidas, y calculamos el peso total
      peso_total = 0;
      cout << id_a_nombre(id_jugador) << ": Número de tartas recibidas: " << num_tartas << endl;
      for (int i = 0; i < num_tartas; i++) {
         cout << "\t- Tarta " << i << ": " << pesos_tartas[i] << " kg."<< endl;
         peso_total += pesos_tartas[i];
      }

      // Calculamos el peso que vamos a comer
      peso_comido = aleatorio_real(0, peso_total);

      // Simulamos acción de comer
      cout << id_a_nombre(id_jugador) << ": Voy a comerme " << peso_comido << " kg de tarta." << endl << endl;
      bloquear(aleatorio_entero(10, 200));

      // Informamos de que hemos terminado de comer
      MPI_Send(&peso_comido, 1, MPI_DOUBLE, ID_YOSHI, tag_jugador, MPI_COMM_WORLD);
      delete[] pesos_tartas;
   }
}

// ---------------------------------------------------------------------
int main (int argc, char* argv[]) {
   int id_propio, num_procesos_actual;

   MPI_Init(&argc, &argv);
   MPI_Comm_rank(MPI_COMM_WORLD, &id_propio);
   MPI_Comm_size(MPI_COMM_WORLD, &num_procesos_actual);

   if (num_procesos_actual != num_procesos_esperados) {
      if (id_propio == 0) {
         cerr << "El número de procesos esperados es " << num_procesos_esperados << " y el número de procesos actual es " << num_procesos_actual << endl;
      }
      MPI_Finalize();
      return 1;
   }

   if (id_propio == ID_YOSHI) {  // Se trata de Yoshi
      funcion_yoshi();
   } else { // Se trata de un jugador
      funcion_player(id_propio);
   }

   MPI_Finalize();
   return 0;
}
