#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <vector>
#include <string>

void input_graph(std::vector<std::vector<int>> &graph);
std::vector<int> dijkstra(std::vector<std::vector<int>> graph, int src);
std::string printSolution(std::vector<int> dist);
bool shouldRelax(int u, int v, int weight, std::vector<int> dist);
int MinNeighbor(std::vector<int> dist, std::vector<bool> converged);

#endif
