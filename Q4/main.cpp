#include <iostream>
#include <vector>
#include "libdijkstra.hpp"

using std::vector;

/*
Main function that receives a graph represented as an adjacency matrix and calculates
the shortest path from the source (first vertex) to all other vertices.
*/
int main()
{
    vector<vector<int>> graph = {{}};
    input_graph(graph);
    vector<int> dist = dijkstra(graph, 0);
    std::cout << print_solution(dist) << std::endl;

    return 0;
}
