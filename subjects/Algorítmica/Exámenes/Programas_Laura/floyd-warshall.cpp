int n; // Num nodes
int dist[n][n]; // dp (min distance to go from i to j)

for(int k = 0; k < n; k++){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(dist[i][j] > dist[i][k] + dist[k][j]){
                dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }
}