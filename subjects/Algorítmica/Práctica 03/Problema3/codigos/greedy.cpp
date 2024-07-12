#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <cstring>
#include "../../Include/City.h"

using namespace std;

// For shorter notation
template<typename T>
using min_priority_queue = priority_queue< T, vector<T>, greater<T> >;

// operator << for vector<City>
ostream& operator<<(ostream& os, vector<City> v) {
    for (int i=0; i < v.size(); i++) {
        os << v[i] << endl;
    }
    return os;
}

/**
 * @brief Calculates the minimum path from @p g [ @p origin ] to @p g [i] for i=1..n-1.
 * 
 * @param g The graph with the nodes. @p g [ @p origin ] is the node from which we are
 * calculating the minimum paths. Nodes are stored as indexes of a vector
 * of cities (first) and its euclidean distance to @p g [ @p origin ] (second).
 * @param dist The vector which will store the minimum distances from @p g [ @p origin ]
 * to every node. Initialized to INF for each node.
 * @param prev The vector which will store index of the previous node in 
 * the minimum path for each node to recover the minimum path.
 * Initialized to -1.
 * @param origin The index of the node from which we are calculating the minimum paths.
 * 
 * @pre The graph must be connected. It rather has cycles.
*/
void Dijkstra (const vector<vector<pair<int,ld>>> & g, vector<ld> & dist, 
                vector<int> & prev, int origin) {

    // Auxiliar priority queue data structure with unreached
    // nodes (modified to let the first element be the minimum)
    min_priority_queue<pair<ld,int>> q; 

    // First node (distance 0)
    q.push({0,origin}); 
    dist[origin] = 0;

    // While there are unreached nodes in q
    while(!q.empty()) {
        
        // Next unreached node (with minimum distance)
        auto p = q.top(); 
        q.pop();

        // Index (distance is not necessary, we only need the minimum distance)
        int node = p.second; 

        // For each adjacent node u      
        for (auto u : g[node]) {
            int v = u.first; // Index of u 

            // Distance from "node" to "v" (euclidean distance previously calculated)
            ld d = u.second; 

            // Compare the original distance "dist[v]" with the
            // distance through the new path "dist[node] + d"
            if (dist[node] + d < dist[v]) {

                // Update distance and previous node if necessary
                dist[v] = dist[node]+d;
                prev[v] = node;

                // Reached v --> explore it
                q.push({dist[v],v});
            }
        }
    }
}

int main (int argc, char** argv) {  

    // Faster I/O
    ios::sync_with_stdio(false);
    cin.tie(0);

    if (argc < 2) {
        cout << "Uso: ./greedy <input_file>" << endl;
        return 1;
    }

    // INPUT
/*
    Input format:
    3 --> number of cities
    1 2 --> origin and destination indexes
    (1,2) (2,0) (0,0) --> cities
    2 --> number of roads
    0 1 (road between (1,2) and (2,0))
    1 2 (road between (2,0) and (0,0))
*/
    char input_file[80] = "";
    strcat(input_file,argv[1]);   
    ifstream fin(input_file,ios::in);

    int n,origin,dest;
    fin >> n >> origin >> dest;

    vector<City> cities(n);
    vector<vector<pair<int,ld>>> roads(n);

    for (int i=0; i<n; i++) {
        City a;
        fin >> a;
        cities[i] = a;
    }

    int m;
    fin >> m;
    
    for (int i=0; i<m; i++) {
        int a,b;
        fin >> a >> b;
        ld dist = cities[a]-cities[b];

        roads[a].push_back({b,dist});
        roads[b].push_back({a,dist});
    }

    fin.close();

    vector<ld> dist(n,INF);
    vector<int> prev(n,-1);
    
    Dijkstra(roads,dist,prev,origin);

    vector<City> path;

    for (int i=dest; i!=-1; i=prev[i]) {
        path.insert(path.begin(),cities[i]);
    }
    
    // OUTPUT

    cout << path << endl;

    return 0;
}