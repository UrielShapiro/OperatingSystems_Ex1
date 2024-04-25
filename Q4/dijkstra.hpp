#include <vector>
using namespace std;

void input_graph(vector<vector<int>> &graph);
void dijkstra(vector<vector<int>> &graph, int src);
void printSolution(vector<int> dist);
bool shouldRelax(int u, int v, int weight, vector<int> dist);
