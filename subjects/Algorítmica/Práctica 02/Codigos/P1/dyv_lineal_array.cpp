#include <iostream>
using namespace std;

typedef long long ll;

const int UMBRAL = 10;

// [ini,fin)
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

tupla dyv(int ini, int fin, ll a[]){
    // Base case
    if(fin - ini <= UMBRAL){
        //return tupla(subsequent(a[ini],ini,fin),subsequent(a[ini],ini,fin),subsequent(a[ini],ini,fin),a[ini]);
        return lineal(ini,fin,a);
    }

    // Divide 
    int mid = (fin + ini)/2;
    tupla t1,t2;
    t1 = dyv(ini,mid,a);
    t2 = dyv(mid,fin,a);

    // Fusion
    tupla ans;

    // mcss
    // mcss is the maximum of the solution of both sides and the sufix of the left side combined with
    // the prefix of the right side

    // ans.mcss = max(max(t1.mcss,t2.mcss),t1.max_sufix + t2.max_prefix)
     ans.mcss = max(t1.mcss, t2.mcss);
    /*if(t1.mcss.val > t2.mcss.val){ // ans.mcss = max(t1.mcss, t2.mcss)
        ans.mcss = t1.mcss;
    }else{
        ans.mcss = t2.mcss;
    }*/
    if(t1.max_sufix.val + t2.max_prefix.val > ans.mcss.val){
        ans.mcss = t1.max_sufix.val + t2.max_prefix.val;
        ans.mcss.ini = t1.max_sufix.ini;
        ans.mcss.fin = t2.max_prefix.fin;
    }

    // max_prefix
    // max_prefix is the maximum between the max_prefix of the left side 
    // and the whole of the left side plus the max_prefix of the right side
    if(t1.max_prefix.val > t1.total + t2.max_prefix.val){
        ans.max_prefix = t1.max_prefix;
    }else{
        ans.max_prefix.val = t1.total + t2.max_prefix.val;
        ans.max_prefix.ini = ini;
        ans.max_prefix.fin = t2.max_prefix.fin;
    }

    // max_sufix
    // max_sufix is the maximum between the max_sufix of the right side 
    // and the whole of the right side plus the max_sufix of the left side
    if(t2.max_sufix.val > t2.total + t1.max_sufix.val){
        ans.max_sufix = t2.max_sufix;
    }else{
        ans.max_sufix.val = t2.total + t1.max_sufix.val;
        ans.max_sufix.ini = t1.max_sufix.ini;
        ans.max_sufix.fin = fin;
    }

    // total
    // total is the total sum of both sides
    ans.total = t1.total + t2.total;

    return ans;
}


int main(){
    // Faster I/O (can be removed)
    ios::sync_with_stdio(false);
    cin.tie(0);

    // INPUT
    int n;
    cin >> n;
    ll a[n];
    for(int i=0; i<n; ++i) cin >> a[i];

    // MCSS
    subsequent ans = dyv(0,n,a).mcss;
    
    // OUTPUT
    cout << ans.fin-ans.ini << endl;
    for(int i=ans.ini; i<ans.fin; ++i)
        cout << a[i] << " ";
    cout << endl;
}