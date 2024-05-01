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
    try
    {
        input_graph(graph);
    }
    catch(const std::invalid_argument& e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }
    catch(const std::out_of_range& e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }
    catch(const std::length_error& e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }
    vector<int> dist(dijkstra(graph, 0));
    std::cout << print_dists(dist) << std::endl;
    
    return 0;
}
