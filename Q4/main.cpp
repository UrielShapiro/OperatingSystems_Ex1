#include <iostream>
#include <vector>
#include "libdijkstra.hpp"

int main()
{
    vector<vector<int>> graph = {{}};
    input_graph(graph);
    vector<int> dist = dijkstra(graph, 0);
    cout << printSolution(dist) << endl;

    return 0;
}