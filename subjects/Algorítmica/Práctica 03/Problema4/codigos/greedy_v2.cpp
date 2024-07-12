#include <bits/stdc++.h>
#include "../../../Include/City.h"
using namespace std;

#define D(x) cerr << #x << ": " << x << endl

//#define MST
//#define TIME
//#define COST
//#define TSP

#ifndef TIME 
    #ifndef COST
        #ifndef MST
            #define TSP
        #endif
    #endif
#endif

/**
 * @brief Prim's algorithm. 
 * Constructs the Minimum Spanning Tree of the given cities using Euclidean Distance (dense graph)
 * @param origin index of the starting city (could be any city, but in this case
 * we rather it be the origin city)
 * @param cities nodes of the graph
 * @param mst where the Minimum Spanning Tree will be saved. Output parameter.
*/
void Prim(int origin, int n, City cities[], vector<vector<int>> & mst){
    // Adjacency matrix of the graph (the distances of all nodes between each other)
    vector<vector<ld>> dist(n,vector<ld>(n)); 
    for(int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j){
            dist[i][j] = cities[i] - cities[j];
        }
    }
    
    // visited[i] = whether we have already visited city i or not
    vector<bool> visited(n,false); 
    visited[origin] = true; // Initially we have only visited the origin city
    
    // nearest_visited_city[i] = the nearest city to city i of all the cities we have already visited
    // Initially we have only visited the origin city, so thats the nearest visited city to
    // every city
    vector<int> nearest_visited_city(n,origin);

    // Memory allocation for the answer graph
    mst.assign(n,vector<int>());
    
    for(int i = 1; i < n; ++i){ // We visited the remaining n-1 cities
        int v = -1; // Of all the remaining cities, the nearest one to the visited cities (we choose one of the visited cities)
        for (int u = 0; u < n; ++u){
            if(!visited[u] && (v == -1 || dist[u][nearest_visited_city[u]] < dist[v][nearest_visited_city[v]])){
                v = u;
            }
        }

        visited[v] = true; // We visit the selected city and add it to the solution
        mst[v].push_back(nearest_visited_city[v]);
        mst[nearest_visited_city[v]].push_back(v);

        #ifdef MST
            cout << cities[v] << endl;
            cout << cities[nearest_visited_city[v]] << endl;
            cout << endl;
        #endif

        // Update the nearest visited city to all cities (in case the newest visited city
        // is closer to them than their current nearest visited city)
        for (int to = 0; to < n; ++to){
            if(dist[v][to] < dist[to][nearest_visited_city[to]]){
                nearest_visited_city[to] = v;
            }
        }
        
    }
}

/**
 * @brief Depht First Search algorithm. 
 * Lists the tree in preorder
 * @param node current node
 * @param parent parent of the current node
 * @param tree tree to process
 * @param ans where the preorder of the tree will be saved
*/
void dfs(int node, int parent,vector<vector<int>> & tree, vector<int> & ans){
    ans.push_back(node); // Add the node to the answer
    for(int neighbour : tree[node]){ // Visit the node's neighbours
        // If the neighbour is not the node's parent, then it means it hasn't been visited
        // (since the given graph is a tree) so it is visited
        if(neighbour != parent){ 
            dfs(neighbour,node,tree,ans);
        }
    }
}

/**
 * @brief Travelling Salesman's Problem solving algorithm.
 * Provides an **aproximate** answer to the TSP for a given array of cities and origint city
 * @param origin Index of the origin city (in the array @p cities )
 * @param n Total number of cities to visit
 * @param cities the cities given and its coordinates
 * @param ans vector of index in which the answer to the problem will be given in the form
 * of index of the @p cities array (and **without** the origin city index at the end)
*/
void TSP_greedy_v2(int origin, int n, City cities[], vector<int> & ans) {
    // Construction of the Minimum Spanning Tree with Prim's algorithm
    vector<vector<int>> mst;
    Prim(origin,n,cities,mst);
    
    // The given tree is listed in preorder (turning the tree into a cycle)
    ans.reserve(n);
    dfs(origin,-1,mst,ans);
}

int main(int argc, char** argv) {
    // Faster I/O
    ios::sync_with_stdio(false);

    // Check given paremeters
    if (argc < 2) {
        cout << "Uso: ./greedy <input_file>" << endl;
        return 1;
    }

    // INPUT
    ifstream fin(argv[1],ios::in);

    int n;
    fin >> n;
    City cities[n];
    for(int i=0; i<n; ++i)
        fin >> cities[i];

    int origin_index = 0; // Origin city index

    // Answer
    vector<int> ans;

    // TSP
    clock_t t_before = clock();
    TSP_greedy_v2(origin_index,n,cities,ans);
    clock_t t_after = clock();

    // OUTPUT
    #ifdef TSP
    printCycle(ans,cities[origin_index],cities);
    #endif

    #ifdef COST
    cout << n << " " << cycleDistance(ans,cities) << endl;
    #endif

    #ifdef TIME
    cout << n << " " << ((double)(t_after - t_before)/ CLOCKS_PER_SEC) << endl;
    #endif
}