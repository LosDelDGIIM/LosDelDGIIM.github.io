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
    // Cities of the problem
    std::vector<City> cities;
    // Current best answer, at the end will be the solution
    std::vector<int> best_ans;
    // Global bound, at the end will be cost of the solution
    ld cost;

    // Number of prunes
    int podas;
    // Number of generated nodes
    int generated;
    // Version of inferior bound function
    int version;

public:

    /**
     * @brief Default constructor
     * Initializes @p podas and @p generated to 0 and @p cost to INF
    */
    TSP_solution();

    /**
     * @brief Constructor of the class
     * Initializes @p podas and @p generated to 0, and @p best_ans and @p cost
     * to the result of an initial Greedy approach.
     * @param v A vector with the cities of the problem
    */
    TSP_solution(const std::vector<City>& v);

    /**
     * @brief Consultor of @p cities. Query method.
     * @return @p cities
    */
    std::vector<City> getCities() const;

    /**
     * @brief Consultor of @p best_ans. Query method.
     * @return @p best_ans
    */
    std::vector<int> getSol() const;

    /**
     * @brief Consultor of @p cost. Query method.
     * @return @p cost
    */
    ld getCost() const;

    /**
     * @brief Consultor of @p podas. Query method.
     * @return @p podas
    */
    int getPodas() const;

    /**
     * @brief Consultor of @p generated. Query method.
     * @return @p generated
    */
    int getGeneratedNodes() const;

    /**
     * @brief Returns the number of nodes that would be generated
     * in a brute force approach. Query method.
     * @return Number of possible nodes if no prunes occur.
    */
    ll getPossibleNodes() const;

    /**
     * @brief Sets the bound function version. Modifier method.
    */
    void setCotaVersion(int version);

    /**
     * @brief The public method which solves the problem. 
     * @see algorithm
    */
    void solve();

    /**
     * @brief Prints the answer.
     * @see printCycle
    */
    void printAns();

private:
    /**
     * @brief Virtual method to implement the algorithm
     * @param e_node First e_node in B&B (iterative), current in BK (recursive)
    */
    virtual void algorithm(Track & e_node) = 0;

    /**
     * @brief First bound function.
     * @param e_node Current node in expansion, with information of the followed track.
     * @param node Candidate node to choose.
     * @return Minimum global edge times the number of not visited nodes.
    */
    ld f_cota1(Track& e_node, int node);

    /**
     * @brief Second bound function.
     * @param e_node Current node in expansion, with information of the followed track.
     * @param node Candidate node to choose.
     * @return The sum of the minimum edge cost for each node plus the minimum edge 
     * to enter the track (node 0).
    */
    ld f_cota2(Track& e_node, int node);

    /**
     * @brief Third bound function.
     * @param e_node Current node in expansion, with information of the followed track.
     * @param node Candidate node to choose.
     * @return The sum of the minimum cost to visit each node plus the minimum
     * cost to visit the track (enter to node 0 and exit from @p node ).
    */
    ld f_cota3(Track& e_node, int node);

    /**
     * @brief Fourth bound function.
     * @param e_node Current node in expansion, with information of the followed track.
     * @param node Candidate node to choose.
     * @return Minimum edge among those that connect not visited nodes between them
     * and a not visited node to the track (node 0 or @p node )
    */
    ld f_cota4(Track& e_node, int node);

    /**
     * @brief Fifth bound function.
     * @param e_node Current node in expansion, with information of the followed track.
     * @param node Candidate node to choose.
     * @return The minimum cost of the remaining edges of the track.
    */
    ld f_cota5(Track& e_node, int node);

    /**
     * @brief Sums the result of calling @p enter_min_cost to every
     * not visited node.
     * @return The mentioned sum.
    */
    ld sumMinEnter(const std::vector<bool>& visited, int node);

    /**
     * @brief Sums the result of calling @p visit_min_cost to every
     * not visited node.
     * @return The mentioned sum.
    */
    ld sumMinVisit(const std::vector<bool>& visited, int node);

    /**
     * @brief Calculates the minimum cost to enter @p node .
     * @param visited Visited nodes (in track).
     * @param node The node we are considering.
     * @return Minimum cost to enter @p node (shortest edge).
     * @see shortest_edges.
    */
    ld enter_min_cost(const std::vector<bool>& visited, int node);

    /**
     * @brief Calculates the minimum cost to visit @p node .
     * @param visited Visited nodes (in track).
     * @param node The node we are considering.
     * @return Minimum cost to visit @p node (average cost between shortest
     * edge and second shortest edge).
     * @see shortest_edges.
    */
    ld visit_min_cost(const std::vector<bool>& visited, int node);

    /**
     * @brief Calculates the two minimum edges connecting a node.
     * @param visited Visited nodes (in track).
     * @param node The node we are considering.
     * @return A pair with the two minimum shortest edges connecting the node.
    */
    std::pair<ld,ld> shortest_two_edges(const std::vector<bool>& visited, int node);

    /**
     * @brief Calculates the minimum cost of the remaining edges.
     * @param nCiudadesRestantes Number of remaining cities.
     * @return Minimum cost of the remaining edges.
    */
    ld minimoCosteAristasRestantes(int nCiudadesRestantes);

    /**
     * @brief Calculates the minimum cost of all the edges
     * Stores all costs in an static vector.
    */
    void calcularMinimoCosteAristas();

    /**
     * @brief Calculates the cost of the minimum edge.
     * @return That minimum cost.
    */
    ld min_edge();

    /**
     * @brief Calculates the cost of the minimum possible edge expanding the node.
     * @param e_node The node in expansion, with information of the track.
     * @return The cost of the minimum possible edge.
    */
    ld min_edge(const Track& e_node);

    /**
     * @brief Greedy approach for the TSP problem. 
     * Implements the closest neighbour approach.
    */
    void TSP_greedy();

protected:

    /**
     * @brief Calculates the local inferior bound for @p e_node track
     * following @p node branch.
     * @param e_node
     * @param node
     * @return Local inferior bound, depending on @p version attribute.
     * @see f_cota1
     * @see f_cota2
     * @see f_cota3
     * @see f_cota4
     * @see f_cota5
    */
    ld f_cota(Track& e_node, int node);

    /**
     * @brief Estimates if the branch @p node is feasible from track
     * @p e_node .
    */
    std::pair<bool, ld> feasible(Track& e_node, int node);

    /**
     * @brief Processes the final solution of a track, changing the
     * global solution @p best_ans and @p cost if necessary.
     * @param track The final resulting track.
    */
    void processSolution(const std::vector<int>& track);
};

#endif
