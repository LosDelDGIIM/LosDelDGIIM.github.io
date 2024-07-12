#include <bits/stdc++.h>
#include "City.h"
#include <chrono>

using namespace std;

// TODO compatibilidad entre el brute force y el eficiente

const int UMBRAL = 2;

/**
 * @brief Branch and bound solution to the Travelling Salesman Problem (path).
 * @param n number of cities to visit
 * @param prev index of the previous city
 * @param cnt number of visited cities
 * @param v array of cities to visit
 * @param visited whether city i has been visited or not
 * @param dist distance of current cycle
 * @param best_dist best cycle distance so far
 * @param cur_cycle current cycle
 * @param best_cycle best cycle so far
*/
void TSP_branch_bound(int n,int prev, int cnt,const City v[],bool visited[], ld dist, ld & best_dist, vector<int> cur_cycle, vector<int> &best_cycle){
    if(cnt == n){ // Base case
        ld new_dist = dist + v[prev].dist(v[0]);
        if(new_dist < best_dist){
            best_dist = new_dist;
            best_cycle = cur_cycle;
        }
        return;
    }

    for(int i=0; i<n; ++i){
        if(!visited[i]){
            visited[i] = true;
            ld new_dist = dist + v[i].dist(v[prev]);
            if(new_dist < best_dist){
                cur_cycle.push_back(i);
                TSP_branch_bound(n,i,cnt+1,v,visited,new_dist,best_dist,cur_cycle,best_cycle);
                cur_cycle.pop_back();
            }
            visited[i] = false;
        }
    }
}

/**
 * @brief Divide and conquer approximated solution to the
 * Travelling Salesman Problem (path).
 * @param ini index of first city in @p v
 * @param fin one plus the index of the last city in @p v
 * @param v array of cities to visit
 * @param path Output parameter. Will contain the indexes
 * of the vector in cycle-order to visit, and a 0 at the end
 * for compatibility with brute force algorithm (base case)
 * in recursive calls.
 * @pre @p v is sorted by x axis.
*/
void dyv(int ini, int fin, City v[], vector<int> & path){

    if(fin - ini <= UMBRAL){
        ld best_dist = INF;
        bool visited[fin-ini] = {false}; // for compatibility
        TSP_branch_bound(fin-ini,0,0,v,visited,0,best_dist,path, path);
        return;
    }

    //Divide
    vector<int> path1,path2;
    int mid = (fin+ini)/2;
    dyv(ini,mid, v, path1);
    dyv(mid,fin, v, path2);

    // Adjust vectors from brute force algorithm

    for (int i=0; i < mid-ini+1; ++i) {
        path1[i] += ini;
    }

    for (int i=0; i < fin-mid+1; ++i) {
        path2[i] += mid;
    }

    // Most x-centered cities

    int r_nearest_city = mid;
    int l_nearest_city = mid-1;


    int x; // index of most x-centered city in path1
    for (int i=0; i < mid-ini; ++i) {
        if (path1[i] == l_nearest_city) {
            x = i;
            break;
        }
    }

    int z; // index of most x-centered in path2
    for (int i=0; i < fin-mid; ++i) {
        if (path2[i] == r_nearest_city) {          
            z = i;
            break;
        }
    }

    // Calculate which of the x adjacent cities (y1,y2) is more x-centered (y = y1 or y2)

    int inc_x = 1; // y = x + inc_x
    int y1 = (x+1)%(mid-ini), y2 = (x+mid-ini-1)%(mid-ini), y = y1;
    if (path1[y1] < path1[y2]) {
        inc_x = -1;
        y = y2;
    }

    // Calculate which of the z adjacent cities (t1,t2) is more x-centered (t = t1 or t2)

    int inc_z = 1; // t = z + inc_z
    int t1 = (z+1)%(fin-mid), t2 = (z+fin-mid-1)%(fin-mid), t = t1;
    if (path2[t2] < path2[t1]) {
        inc_z = -1;
        t = t2;
    }

    // Calculate distances of possible links

    ld xz = v[path1[x]].dist(v[path2[z]]);
    ld xt = v[path1[x]].dist(v[path2[t]]);
    ld yz = v[path1[y]].dist(v[path2[z]]);
    ld yt = v[path1[y]].dist(v[path2[t]]);

    // true if it's better to link x and z (then y and t), false if it's better to link x and t
    // (then y and z)
    bool link_xz = xt + yz > xz + yt; 
 
    // Push path1 to path from y to x going through the vector in cycle
    for (int i=y; i != x; i = (i+mid-ini+inc_x)%(mid-ini)) {
        path.push_back(path1[i]);
    }
    path.push_back(path1[x]);

    int start_z = link_xz ? z : t;
    int finish_z = start_z == z ? t : z;
    inc_z = start_z == z ? -inc_z : inc_z;

    // Push path2 to path from start_z to finish_z going through the vector in cycle
    for (int i=start_z; i != finish_z; i = (i+fin-mid+inc_z)%(fin-mid)) {
        path.push_back(path2[i]);
    }
    path.push_back(path2[finish_z]);

    // Adjust indexes to v size
    for (int i=0; i < path.size(); ++i) {
        path[i] -= ini;
    }

    // Know the cycle, not the order
}

int main(){
    // Faster I/O
    ios::sync_with_stdio(false);
    cin.tie(0);

    // INPUT
    int n;
    cin >> n;
    City v[n];
    for(int i=0; i<n; ++i)
        cin >> v[i];
    City home = v[0];

    sort(v,v+n); // sort by x axis

    vector<int> path;

    chrono::high_resolution_clock::time_point t_antes, t_despues; 
    chrono::duration<double> transcurrido;

    t_antes = chrono::high_resolution_clock::now();

    dyv(0,n,v,path); 

    t_despues = chrono::high_resolution_clock::now();

    transcurrido = chrono::duration_cast<chrono::duration<double>>(t_despues-t_antes);

    cout << endl << setw(10) << left << n << " " << transcurrido.count();

    // printCycle(path,home,v); // print path

    return 0;
}