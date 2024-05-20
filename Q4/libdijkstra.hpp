#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <vector>
#include <string>

/**
 * @brief A function that receives a graph represented as an adjacency matrix (line by line) and stores it in a 2D vector.
 * The function checks if the input is valid and throws an exception if it is not.
 */
void input_graph(std::vector<std::vector<int>> &graph);

/*
    * @brief Function that implements Dijkstra's single source shortest path algorithm 
    * for a graph represented using adjacency matrix
    * @return A vector that stores the shortest distance from the source to each vertex in the graph.
*/
std::vector<int> dijkstra(std::vector<std::vector<int>> graph, int src);

/*
    * @brief A function to print the array which stores the shortest distance from the source to each vertex in the graph.
    * @return A string that contains the vertex and its distance from the source.
*/
std::string print_dists(std::vector<int> dist);

/*
    * @brief A function that checks if a vertex should be relaxed or not.
    * @return True if the vertex should be relaxed, False otherwise.
*/
bool should_relax(int u, int v, int weight, std::vector<int> dist);

/*
    * @brief A function to find the neighbor with the minimum distance from the source.
    * Assuming that that neighbor was not visited yet.
    * @return The index of the neighbor with the minimum distance from the source.
*/
int min_neighbor(std::vector<int> dist, std::vector<bool> converged);

#endif
