#include <bits/stdc++.h>
#include "../../Include/City.h"
#include "../../Include/Solution.h"

using namespace std;

#ifndef TIME 
    #ifndef COST
        #ifndef NODES
            #define TSP
        #endif
    #endif
#endif

//? En lugar de herencia se podría hacer una función a la que se le pase
//? TSP_solution

class BB_solution : public TSP_solution
{

public:
    
    BB_solution(const vector<City> & v) : TSP_solution(v) {};

private:

    void algorithm(Track& first_node) override {
        priority_queue<Track, vector<Track>, greater<Track>> nodos_vivos;
        nodos_vivos.push(first_node);

        while (!nodos_vivos.empty()) {
            generated++;
            Track e_node = nodos_vivos.top();
            nodos_vivos.pop();

            if (e_node.aprox_cost >= cost) continue;

            if (e_node.track.size() == cities.size()) {
                processSolution(e_node.track);
                continue;
            }

            for (int i = 1; i < cities.size(); ++i) {
                if (e_node.visited[i]) continue;
                pair<bool, double> viable = feasible(e_node, i);
                if (!viable.first) {
                    podas++;
                    continue;
                }
                Track aux = e_node;
                aux.current_cost += (cities[aux.track.back()] - cities[i]);
                aux.track.push_back(i);
                aux.aprox_cost = viable.second;
                aux.visited[i] = true;

                nodos_vivos.push(aux);
            }
        }
    }
};

int main(int argc, char** argv){
    // Faster I/O
    ios::sync_with_stdio(false);
    cin.tie(0);

    ifstream fin(argv[1],ios::in);
    int version = 1;
    if (argc == 3)
        version = atoi(argv[2]);

    // INPUT
    int n;
    fin >> n;
    vector<City> v;
    v.reserve(n);

    for(int i=0; i<n; ++i) {
        City aux;
        fin >> aux;

        v.push_back(aux);
    }

    BB_solution sol(v);

    sol.setCotaVersion(version);

    // TSP

    clock_t t_before = clock();
    sol.solve();
    clock_t t_after = clock();

    // OUTPUT
    #ifdef TSP
    sol.printAns();
    #endif

    #ifdef NODES
    cout << "nodes: " << sol.getGeneratedNodes() << " / " << sol.getPossibleNodes() << endl;
    cout << "podas: " << sol.getPodas() << endl;
    #endif

    #ifdef COST
    cout << n << " " << sol.getCost() << endl;
    #endif

    #ifdef TIME
    cout << n << " " << ((ld)(t_after - t_before)/ CLOCKS_PER_SEC) << endl;
    #endif

    return 0;
}