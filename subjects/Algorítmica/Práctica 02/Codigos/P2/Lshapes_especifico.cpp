#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

/**
 * @brief Adds 3 @p m x @p m squares forming an L slab with orientation @p orientation
 * @note @p orientation can be seen as an enum like this:
 * 0 1
 * 2 3
 * meaning that inserting an L slab in @p i @p j with orientation @p orientation it's
 * like filling the square above except @p orientation slab
 * 
 * @param v Matrix we are filling
 * @param m The level we are filling, meaning the side each one of the 3 squares that form the L slab
 * @param i The row of the position in the matrix
 * @param j The column of the position in the matrix
 * @param orientation An integer from 0 to 3 that provides information of the orientation of the slab
 * @param slab The number of the slab we are adding
*/
void add_slab_m(vector<vector<int>> & v, int m, int i, int j, int orientation, int & slab)
{
    // Variables to calculate where and how to add the L slabs
    int inc_i = orientation / 2 == 0 ? 1 : -1;
    int inc_j = orientation % 2 == 0 ? 1 : -1;

    // Level 1, base case
    if (m == 1)
    {
        v[i][j + inc_j] = v[i + inc_i][j] = v[i + inc_i][j + inc_j] = slab;
        ++slab;
    }
    else
    {
        // Level m > 1, add four L slabs of level m/2 following the pattern:

        // .   .   3   3
        // .   .   1   3
        // 2   1   1   4
        // 2   2   4   4

        // Calculate non-adjacent L orientations

        // orientation --> orientation1 orientation2

        // switch(orientation)
        // case 0 --> 1 2
        // case 1 --> 0 3
        // case 2 --> 3 0
        // case 3 --> 2 1
        int orientation1 = orientation + inc_j;
        int orientation2 = 3 - orientation1;

        // Escale variables to actual level
        inc_i *= (m/2);
        inc_j *= (m/2);

        // Add insider L in the same position of big slab with the same orientation
        add_slab_m(v, m / 2, i, j, orientation, slab);

        // Add 2 corner L's with calculated orientations and the following positions
        // (i +- m/2, j -+ m/2 +- 1)
        // (i -+ m/2 +- 1, j +- m/2)
        add_slab_m(v, m / 2, i + inc_i, j - inc_j + (abs(inc_j)/inc_j), orientation1, slab);
        add_slab_m(v, m / 2, i - inc_i + (abs(inc_i)/(inc_i)), j + inc_j, orientation2, slab);

        // Add outsider L with the same orientation as the big one.
        add_slab_m(v, m / 2, i + inc_i, j + inc_j, orientation, slab);
    }
}

/**
 * @brief Fills a @p n x @p n matrix @p v with L-shaped slabs
 * @note The algorithm follows this pattern to fill the matrix:
 *  .   1   2   2   4   4   4   4
 *  1   1   2   2   4   4   4   4
 *  2   2   2   2   4   4   4   4
 *  2   2   2   2   4   4   4   4
 *  4   4   4   4   4   4   4   4
 *  4   4   4   4   4   4   4   4
 *  4   4   4   4   4   4   4   4
 *  4   4   4   4   4   4   4   4
 * Adding a level m L slab in each iteration around the m x m gap,
 * and leaving a 2*m x 2*m gap for the next iteration.
 * @param v The matrix to fill
 * @param n The side of the matrix
 * @param r Row of the gap
 * @param c Comun of the gap
 * @param tile The number of level 1 slab we are adding, needed for
 * recursive calls of add_slab_m.
 * @see add_slab_m
*/
void fill_L(vector<vector<int>> & v,int n,int r, int c, int & tile){

    // Add log_2(n) - 1 slabs from level 1 to level n/2
    for (int m = 1; m < n; m *= 2)
    {
        // Calculate orientation
        int orientation = 2*((r/m) % 2) + ((c/m) % 2);

        // m x m square to left empty, starting from the original 1 x 1 in (r,c)
        int i = (r / m)*m; 
        int j = (c / m)*m;

        // Calculate position
        i += orientation / 2 == 0 ? m-1 : 0;
        j += orientation % 2 == 0 ? m-1 : 0;

        // Add slab of level m
        add_slab_m(v, m, i, j, orientation, tile); 
    }
}

int main(){
    // Faster I/O
    ios::sync_with_stdio(false);
    cin.tie(0);

    // INPUT
    int n,r,c; // n-size of the square (power of 2), (r,c) -> position of the square tile
    cin >> n >> r >> c;
    vector<vector<int>> v(n,vector<int>(n));
    int start_tile = 0;
    v[r][c] = start_tile++;
    fill_L(v,n,r,c,start_tile);

    // OUTPUT
    // for(int i=0; i<n; ++i){
    //     for(int j=0; j<n; ++j){
    //         cout << setw(3) << v[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    cout << "Last tile: " << start_tile-1 << endl;
    // Codeforces's Output (for testing)
    // https://codeforces.com/problemset/gymProblem/101845/L
    /*for(int i=0; i<n; ++i){
        for(int j=0; j<n; ++j){
            if(!v[i][j]){
                cout << ".";
            }else{
                cout << (char)((v[i][j]%26) + 'A');
            }
        }
        cout << endl;
    }*/
}