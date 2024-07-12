#include "../Include/City.h"

using namespace std;

ld City::operator-(const City& other) const {
    return dist(other);
}

ld City::dist(const City& other) const {
    ld dx = x - other.x;
    ld dy = y - other.y;
    return sqrt(dx * dx + dy * dy);
}

bool operator<(const City& a, const City& b) {
    if (a.x < b.x) {
        return true;
    } else if (a.x == b.x) {
        return a.y < b.y;
    }
    return false;
}

bool operator==(const City& a, const City& b) {
    return a.x == b.x && a.y == b.y;
}

bool operator!=(const City& a, const City& b) {
    return !(a == b);
}

istream& operator>>(istream& is, City& p) {
    char c;
    is >> c >> p.x >> c >> p.y >> c;
    return is;
}

ostream& operator<<(ostream& os, const City& p) {
    os << "(" << p.x << "," << p.y << ")";
    return os;
}

ld cycleDistance(const vector<int>& cycle, const vector<City>& v) {
    if (cycle.size() < 2) return 0;
    ld total = 0;
    for (int i = 0; i < (int)cycle.size() - 1; i++) {
        total += (v[cycle[i + 1]] - v[cycle[i]]);
    }
    total += (v[cycle[0]] - v[cycle[cycle.size() - 1]]);
    return total;
}

void printCycle(const vector<int>& cycle, int origin) {
    int ini = 0;
    while (cycle[ini] != origin) ++ini;
    for (int i = ini; i < (int)cycle.size(); ++i) {
        cout << cycle[i] << " ";
    }
    for (int i = 0; i < ini; ++i) {
        cout << cycle[i] << " ";
    }
    cout << origin << endl;
}

void printCycle(const vector<int>& cycle, const City& origin, const vector<City>& v) {
    int ini = 0;
    while (v[cycle[ini]] != origin) ++ini;
    for (int i = ini; i < (int)cycle.size(); ++i) {
        cout << v[cycle[i]] << endl;
    }
    for (int i = 0; i < ini; ++i) {
        cout << v[cycle[i]] << endl;
    }
    cout << origin << endl;
}