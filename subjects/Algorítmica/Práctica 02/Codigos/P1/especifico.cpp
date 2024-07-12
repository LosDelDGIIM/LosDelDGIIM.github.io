#include <iostream>
#include <cassert>
using namespace std;

typedef long long ll;

struct subsequent{
    ll val,ini,fin;
    subsequent(ll val = 0, ll ini  = 0, ll fin = 0) : val(val), ini(ini), fin(fin) {}

    friend bool operator<(const subsequent & a,const subsequent & b){
        return a.val < b.val;
    }

    friend ostream & operator<<(ostream & os, const subsequent & ind){
        os << ind.val << " [" << ind.ini << ", " << ind.fin << "]"; 
        return os;
    }
};

struct tupla
{
    subsequent mcss,max_prefix,max_sufix;
    ll total;

    tupla(subsequent mcss = subsequent(), subsequent p = subsequent(), subsequent s = subsequent(), ll t = 0) :
     mcss(mcss), max_prefix(p), max_sufix(s), total(t) {}

    friend ostream & operator<<(ostream & os, const tupla & t){
        os << "mcss: " << t.mcss << endl;
        os << "max_prefix: " << t.max_prefix << endl;
        os << "max_sufix: " << t.max_sufix << endl;
        os << "total: " << t.total;
        return os;
    }
};

tupla lineal(int ini, int fin, ll a[]){
    tupla ans;
    // Initialise mcss and max_prefix to the first element of the array
    ans.mcss.ini = ans.max_prefix.ini = ini;
    ans.mcss.val = ans.max_prefix.val = a[ini];
    ans.mcss.fin = ans.max_prefix.fin = ini+1;
    ll ac = 0; // Accumulator
    int loc_ini = 0;
    ll max_array_ind = 0; // Index of the maximum element of the array
    for(int i=ini; i<fin; ++i){
        ac += a[i];
        if(ac < 0){ // If the accumulator is negative, we reset it (as well as the local starting position)
            ac = 0;
            loc_ini = i+1;
        }
        if(ac > ans.mcss.val){ // If the accumulator is greater than the current mcss, then it is updated
            ans.mcss.val = ac;
            ans.mcss.fin = i+1;
            ans.mcss.ini = loc_ini;
        }
        if(a[max_array_ind] < a[i]){ // Calculating subsequent of the maximum element of the array
            max_array_ind = i;
        }
        ans.total += a[i]; // Calculating total of the array
        if(ans.total > ans.max_prefix.val){ // If the current total of the array [0,i] is greater than max_prefix, then it is updated
            ans.max_prefix.val = ans.total;
            ans.max_prefix.fin = i+1;
        }
    }

    if(!ans.mcss.val){ // If mcss is 0, then all the array is negative and mcss is the maximum element of the array
        ans.mcss.ini = max_array_ind;
        ans.mcss.fin = max_array_ind+1;
        ans.mcss.val = a[max_array_ind];
    }

    // Initialise max_sufix to the last element of the array
    ans.max_sufix.val = a[fin-1];
    ans.max_sufix.ini = fin-1;
    ans.max_sufix.fin = fin;
    ll sum = 0;
    for(int i=fin-1; i>=ini; --i){
        sum += a[i]; // Calculating sum of [i,fin)
        if(sum > ans.max_sufix.val){ // If [i,fin) is greater than max_sufix, then it is updated
            ans.max_sufix.val = sum;
            ans.max_sufix.ini = i;
        }
    }

    return ans;
}

int main(int argc, char *argv[]) {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    if (argc == 2)
        n = atoi(argv[1]);
    else {
        cout << "Introduce número de elementos del vector: ";
        cin >> n;
    }

    ll *a = new ll[n];
    assert(a);

    srand(time(0));

    for (int i = 0; i < n; ++i) {
        a[i] = (rand() - RAND_MAX/2); // Random pos and neg values
    }

    clock_t t_antes = clock();

    subsequent ans = lineal(0, n, a).mcss;

    clock_t t_despues = clock();

    delete[] a;

    cout << n << " " << ((double)(t_despues - t_antes)) / CLOCKS_PER_SEC << endl;

    return 0;
}
