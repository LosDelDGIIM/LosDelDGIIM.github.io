#ifndef SOLUTION_H
#define SOLUTION_H

#include "City.h"

/**
 * @brief Removes element @p elem from vector @p v
 * @param v
 * @param elem
*/
template<typename T>
void remove(std::vector<T>& v, const T& elem);

/**
 * @struct Track
 * @brief Represents a track cities storing the inferior bound and current cost
 * Specially useful for BranchAndBound
*/
struct Track {
    // The track as an integer vector
    std::vector<int> track;
    // Information of visited cities
    std::vector<bool> visited;
    // Inferior bound for track
    ld aprox_cost;
    // Current cost of the track
    ld current_cost;

    /**
     * @brief Default constructor for Track
     * @param n Number of cities in the track
    */
    Track(int n = 0) : visited(n, false), aprox_cost(0), current_cost(0) {
        track.reserve(n);
    }
    /**
     * @brief Constructor of Track
     * @param track
     * @param visited
     * @param cost
     * @param current_cost
    */
    Track(std::vector<int>& track, std::vector<bool>& visited, ld cost, ld current_cost) 
    : track(track), visited(visited), aprox_cost(cost), current_cost(current_cost) {}

    /**
     * @brief Greater operator acording to @p aprox_cost
    */
    bool operator>(Track other) const {
        return this->aprox_cost > other.aprox_cost;
    }
};

/**
 * @class TSP_solution
 * @brief Main class for the BK and B&B solution to TSP
*/
class TSP_solution {

protected:
    std::vector<City> cities;
    std::vector<int> best_ans;
    ld cost;

    int podas;
    int generated;
    int version;

public:
    TSP_solution();
    TSP_solution(const std::vector<City>& v, int version = 0);

    std::vector<City> getCities() const;
    std::vector<int> getSol() const;
    ld getCost() const;
    int getPodas() const;
    int getGeneratedNodes() const;
    ll getPossibleNodes() const;

    void solve();
    void printAns();

private:
    virtual void algorithm(Track & e_node) = 0;

    ld f_cota1(Track& e_node, int node);
    ld f_cota2(Track& e_node, int node);
    ld f_cota3(Track& e_node, int node);
    ld f_cota4(Track& e_node, int node);
    ld f_cota5(Track& e_node, int node);

    ld sumMinEnter(const std::vector<bool>& visited, int node);
    ld sumMinVisit(const std::vector<bool>& visited, int node);
    ld enter_min_cost(const std::vector<bool>& visited, int node);
    ld visit_min_cost(const std::vector<bool>& visited, int node);
    std::pair<ld,ld> shortest_two_edges(const std::vector<bool>& visited, int node);
    ld minimoCosteAristasRestantes(int nCiudadesRestantes);
    void calcularMinimoCosteAristas();
    ld min_edge();
    ld min_edge(const Track& e_node);

    void TSP_greedy();

protected:
    ld f_cota(Track& e_node, int node);
    std::pair<bool, ld> feasible(Track& e_node, int node);
    void processSolution(const std::vector<int>& track);
};
#endif
