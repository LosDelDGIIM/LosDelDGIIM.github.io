const int INF = 1e9; // Infinito
int n; // Numero de nodos
vector<vector<pair<int, int>>> adjacency_list; // Lista de adyacencia
void dijkstra(int s){
    // d[i] = distancia (minima) de s a i
    vector<int> d(n,INF);
    d[s] = 0;
    // p[i] va antes que i en el camino de s a i
    vector<int> p(n,-1);
    // selected[i] si ya hemos seleccionado (calculado la distancia minima) de i
    vector<bool> selected(n,false);
    for(int i=0; i<n; ++i){
        int selected_node = -1;
        for (int j = 0; j < n; ++j){
            if(!selected[j] && (selected_node == -1 || d[j] < d[selected_node]))
                selected_node = j;
        }
        
        // Marcamos como seleccionado al nuevo nodo seleccionado
        selected[selected_node] = true;

        // Actualizamos las distancias de sus vecinos en caso de haga falta
        for(auto edge : adjacency_list[selected_node]){
            int neighbour = edge.first;
            int cost = edge.second;

            // Si podemos mejorar la distancia al vecino pasando 
            // por el nuevo nodo seleccionado
            if(d[selected_node] + cost < d[neighbour]){
                d[neighbour] = d[selected_node] + cost;
                p[neighbour] = selected_node;
            }
        }
    }
}