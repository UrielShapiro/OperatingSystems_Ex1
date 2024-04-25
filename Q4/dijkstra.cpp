#include <iostream>
#include <climits>
#include <vector>
#include <string>
using namespace std;

void input_graph(vector<vector<int>> &graph)
{
    size_t mat_len = SIZE_MAX;
    for (size_t i = 0; i < mat_len; i++)
    {
        if (i == 1)
        {
            mat_len = graph.at(0).size();
            graph.resize(mat_len);
        }
        size_t j = 0;
        bool run = true;
        char input;
        cout << "Enter the weight of the edge between vertice " << i << " to vertice " << j << ": " << endl;
        cin.clear();
        while ((input = cin.get()) != '\n' && run == true)
        {
            cout << "Input was: " << input << endl;
            if (input == '\n' || input == '\0' || input == EOF)
            {
                run = false;
                break;
            }
            else if (input == ' ' || isalpha(input))
            {
                continue;
            }
            if (j >= mat_len)
            {
                cerr << "Error: the amount of weights entered is not equal to the amount of vertices!" << endl;
                exit(1);
            }
            int weight = input - '0';
            if (weight < 0)
            {
                cerr << "Error: weight must be a positive number! but it is: " << weight << endl;
                exit(1);
            }
            if (j == i && weight != 0)
            {
                cerr << "Error: the weight of the edge between vertice " << i << " and itself must be 0!" << endl;
                exit(1);
            }
            cout << "Weight was: " << weight << endl;
            graph.at(i).push_back(weight);
            j++;
            cout << "j is now: " << j << endl;
        }
    }
}

// A utility function to print the constructed distance array
void printSolution(vector<int> dist)
{
    cout << "Vertex \t Distance from Source" << endl;
    for (size_t i = 0; i < dist.size(); i++)
        cout << i << " \t" << dist[i] << endl;
}

// A utility function to find the vertex with minimum
// distance value, from the set of vertices not yet included
// in shortest path tree
int MinNeighbor(size_t V, vector<int> dist, vector<bool> converged)
{
    // Initialize min value
    int min = INT_MAX, min_index;

    for (size_t v = 0; v < V; v++)
        if (converged[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

bool relaxed(int u, int v, int weight, vector<int> dist)
{
    if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
    {
        return true;
    }
    return false;
}

// Function that implements Dijkstra's single source shortest path algorithm
// for a graph represented using adjacency matrix representation
void dijkstra(vector<vector<int>> graph, int src)
{
    vector<int> dist; // The output array.  dist[i] will hold the
                      // shortest distance from src to i

    vector<bool> converged; // converged[i] will be true if vertex i is
                            // included in shortest path tree or shortest distance from src to i is finalized

    // Initialize all distances as INFINITE and stpSet[] as false;
    dist.assign(graph.size() - 1, INT_MAX);
    converged.assign(graph.size() - 1, false);

    // Distance of source vertex from itself is always 0
    dist.at((size_t)src) = 0;

    // Find shortest path for all vertices
    for (size_t count = 0; count < graph.size(); count++)
    {
        // Pick the minimum distance vertex from the set of
        // vertices not yet processed. u is always equal to
        // src in the first iteration.
        int u = MinNeighbor(graph.size(), dist, converged);

        // Mark the picked vertex as processed
        converged[u] = true;

        // Update dist value of the adjacent vertices of the picked vertex.
        for (size_t v = 0; v < graph.size(); v++)

            // Update dist[v] only if is not in converged,
            // there is an edge from u to v, and total
            // weight of path from src to  v through u is
            // smaller than current value of dist[v]
            if (!converged[v] && graph.at(u).at(v) && relaxed(u, v, graph.at(u).at(v), dist))
                dist[v] = dist[u] + graph[u][v];
    }

    // print the constructed distance array
    printSolution(dist);
}

int main()
{
    vector<vector<int>> graph = {{}};
    input_graph(graph);
    dijkstra(graph, 0);

    // std::cout << "Enter the amount of vertices: " << std::endl;
    // int V;
    // std::cin >> V;

    // int graph[V][V];

    // for (size_t i = 0; i < V; i++)
    // {
    //     for (size_t j = 0; j < V; j++)
    //     {
    //         std::cout << "Enter the weight of the edge between vertice " << i << "to vertice " << j << ": " << std::endl;
    //         int weight;
    //         std::cin >> weight;
    //         if(weight < 0)
    //         {
    //             std::cout << "Error: weight must be a positive number!" << std::endl;
    //             return 1;
    //         }
    //         graph[i][j] = weight;
    //     }
    // }

    // for (size_t i = 0; i < V; i++)
    // {
    //     if(graph[i][i] != 0)
    //     {
    //         std::cout << "Error: the weight of the edge between vertice " << i << " and itself must be 0!" << std::endl;
    //         return 1;
    //     }
    // }

    // dijkstra(V, graph, 0);

    return 0;
}
