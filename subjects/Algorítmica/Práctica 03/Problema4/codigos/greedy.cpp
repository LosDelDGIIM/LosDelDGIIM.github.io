#include <bits/stdc++.h>
#include "../../../Include/City.h"
using namespace std;

#define D(x) cerr << #x << ": " << x << endl

typedef pair<int,int> Edge;

#define TIME
//#define COST
//#define TSP

#ifndef TIME 
    #ifndef COST
        #define TSP
    #endif
#endif

void make_set(int node,vector<int> & parent, vector<int> & rank){
    parent[node] = node;
    rank[node] = 0;
}

int find_set(int node, vector<int> & parent){
    if(parent[node] == node) return node;
    return parent[node] = find_set(parent[node],parent);
}

bool union_sets(int u, int v, vector<int> & parent, vector<int> & rank){
    int pu = find_set(u,parent);
    int pv = find_set(v,parent);

    if(pu == pv) // Nothing to join here
        return false;

    if(rank[pu] < rank[pv])
        swap(pu,pv);
    parent[pv] = pu;
    if(rank[pu] == rank[pv])
        ++rank[pu];
    return true;
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

void TSP_greedy_v3(int origin, int n, City cities[], vector<int> & ans) {
    vector<Edge> edges;
    edges.reserve((n*(n-1)/2));
    for(int i = 0; i < n; ++i){
        for(int j = i+1; j < n; ++j){
            edges.push_back({i,j});
        }
    }

    sort(edges.begin(),edges.end(),[&cities](Edge& a, Edge & b){
        return cities[a.first] - cities[a.second] < cities[b.first] - cities[b.second];
    });
   
    int n_edges = edges.size();
    int ind_edge = 0;
    int n_sets = n;
    vector<int> parent(n),rank(n),degree(n,0);

    // Initialize connected components
    for(int i = 0; i < n; ++i){
        make_set(i,parent,rank);
    }

    vector<vector<int>> tree(n); // Adjacency list
    while(n_sets > 1){
        Edge edge = edges[ind_edge++];
        int u = edge.first;
        int v = edge.second;
        if(degree[u] < 2 && degree[v] < 2){
            if(union_sets(u,v,parent,rank)){
                --n_sets;
                ++degree[u];
                ++degree[v];
                tree[u].push_back(v);
                tree[v].push_back(u);
            }
        }
    }

    dfs(origin,-1,tree,ans);
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
    TSP_greedy_v3(origin_index,n,cities,ans);
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
