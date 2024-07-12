#ifndef CITY_H
#define CITY_H
#include <iostream>
#include <cmath>
#include <vector>

typedef long long ll;
typedef long double ld;

// Infinity (biggest possible number)
const ld INF = 1e18;

// Represents a city with coordinates (x,y)
// It implements dist() and operator p-q as the euclidean distance of 2 points
// Input and output operator are also implemented
struct City
{
    ld x,y;

    // Constructor
    City(ld x=0,ld y=0) : x(x), y(y) {}

    // Euclidean distance (symetrical)
    ld operator-(const City & other) const{
        return dist(other);
    }

    ld dist(const City & other) const{
        ld dx = x - other.x;
        ld dy = y - other.y;
        return sqrt(dx*dx+dy*dy);
    }

    // Sort by x axis
    friend bool operator<(const City & a, const City & b){
        if (a.x < b.x) {
            return true;
        }
        else if (a.x == b.x) {
            return a.y < b.y;
        }
        return false;
    }

    friend bool operator==(const City & a, const City & b){
        return a.x == b.x && a.y == b.y;
    }

    friend bool operator!=(const City & a, const City & b){
        return !(a == b);
    }

    // I/O operators
    friend std::istream & operator>>(std::istream & is, City & p){
        char c;
        is >> c >> p.x >> c >> p.y >> c;
        return is;
    }
    friend std::ostream & operator<<(std::ostream & os, const City &p){
        os << "(" << p.x << "," << p.y << ")";
        return os;
    }

};

/**
 * @brief Calculates the distance of the given cycle (cycle)
 * @param cycle the cycle to calculate the distance from
 * @param v the cities
 * @return the distance between ald the consecutive cities of the cycle
*/
ld cycleDistance(const std::vector<int> & cycle,const std::vector<City> & v)
{
    if(cycle.size() < 2) return 0;
    ld total = 0;
    for (int i = 0; i < (int)cycle.size()-1; i++)
    {
        total += (v[cycle[i+1]] - v[cycle[i]]);
    }
    total += (v[cycle[0]] - v[cycle[cycle.size() - 1]]);

    return total;
}

/**
 * @brief Prinst a cycle (index) starting and ending at origin
*/
void printCycle(const std::vector<int> & cycle, int origin = 0){
    int ini = 0;
    while(cycle[ini] != origin) ++ini;
    for(int i=ini; i<(int)cycle.size(); ++i){
        std::cout << cycle[i] << " ";
    }
    for(int i=0; i<ini; ++i){
        std::cout << cycle[i] << " ";
    }
    std::cout << origin << std::endl;
}

/**
 * @brief Prints a cycle (the cities) starting and ending at origin
*/
void printCycle(const std::vector<int> & cycle, const City & origin, const std::vector<City> & v){
    int ini = 0;
    while(v[cycle[ini]] != origin) ++ini;
    for(int i=ini; i<(int)cycle.size(); ++i){
        std::cout << v[cycle[i]] << std::endl;
    }
    for(int i=0; i<ini; ++i){
        std::cout << v[cycle[i]] << std::endl;
    }
    std::cout << origin << std::endl;
}
#endif
