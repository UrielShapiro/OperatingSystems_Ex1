#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <vector>
#include <string>
using namespace std;

void input_graph(vector<vector<int>> &graph);
vector<int> dijkstra(vector<vector<int>> graph, int src);
string printSolution(vector<int> dist);
bool shouldRelax(int u, int v, int weight, vector<int> dist);
int MinNeighbor(vector<int> dist, vector<bool> converged);

#endif
