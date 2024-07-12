#include <bits/stdc++.h>
#include "City.h"
using namespace std;

/**
 * @brief Brute force solution to the Travelling Salesman Problem 
 * @param n number of cities to visit
 * @param cnt number of visited cities
 * @param prev index of the previous city
 * @param home_ind index of the home (origin) city 
 * @param v array of cities to visit
 * @param visited whether city i has been visited or not
 * @param dist current distance
 * @param best_dist best distance found until now
 * @param cur_cycle current path
 * @param best_cycle best cycle found until now
*/
void TSP_branch_bound(int n,int prev,int home_ind, int cnt,const City v[],bool visited[], ld dist, ld & best_dist, vector<int> cur_cycle, vector<int> &best_cycle){
    // Base case
    if(cnt == n-1){ // Already visited all cities
        // Add distance of the last city to the origin city
        ld new_dist = dist + v[prev].dist(v[home_ind]); 
        // If the new distance is better than current best distance
        // best distance and best cycle are updated
        if(new_dist < best_dist){ 
            best_dist = new_dist;
            best_cycle = cur_cycle;
        }
        return;
    }

    // Iterate for all the cities to visit
    for(int i=0; i<n; ++i){
        // If the city hasn't been visited we try visiting it
        if(!visited[i]){
            visited[i] = true; // Mark the city as visited
            // Add distance of the last city to this city to current distance
            ld new_dist = dist + v[i].dist(v[prev]);
            // If the new distance is better than current best distance
            // we try visiting this city
            if(new_dist < best_dist){
                // Add city to current cycle
                cur_cycle.push_back(i);
                // Proceded resolving the problem with one more city visited
                TSP_branch_bound(n,i,home_ind,cnt+1,v,visited,new_dist,best_dist,cur_cycle,best_cycle);
                // Erase the city of the current cycle
                cur_cycle.pop_back();
            }
            visited[i] = false; // Mark the city as not visited
        }
    }
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

    // Locate home index
    int home_ind = 0;
    while(v[home_ind] != home) ++home_ind;

    // Initialize best distance
    ld best_dist = INF; // Fake impossible value 
    // Initialize all cities to not visited except for origin city
    bool visited[n];
    memset(visited,false,sizeof(visited));
    visited[home_ind] = true; // Already visited origin city
    // Answer
    vector<int> ans;
    ans.reserve(n);
    ans.push_back(home_ind); // Already visited origin city

    // TSP
    TSP_branch_bound(n,home_ind,home_ind,0,v,visited,0,best_dist,ans,ans);

    // OUTPUT
    printCycle(ans,home,v);
}
