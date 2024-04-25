#include <iostream>
#include <climits>
#include <vector>
using namespace std;
/*
A function that receives a graph represented as an adjacency matrix (line by line) and stores it in a 2D vector.
The function checks if the input is valid and exits the program if it is not.
*/
void input_graph(vector<vector<int>> &graph)
{
    size_t mat_len = SIZE_MAX;                 // Setting the length of the matrix to the maximum value before the first iteration
                                               // In order to let the user enter the amount of vertices,
                                               // then limit the length of the matrix to that value.
    for (size_t row = 0; row < mat_len; row++) // Looping through the rows of the matrix
    {
        if (row == 1) // If the user has entered the first row, then the length of the matrix is known
        {
            mat_len = graph.at(0).size();
            graph.resize(mat_len); // Resizing the matrix to the length of the matrix
        }
        size_t col = 0;
        char input;
        cout << "Enter the weight of the edges from vertice " << row << ": " << endl; // Prompting the user to enter the weights of the edges
        cin.clear();                                                                  // Clearing the input buffer
        while ((input = cin.get()) != '\n')                                           // Looping through the input until the user presses enter ('\n')
        {
            if (input == ' ' || isalpha(input)) // If the input is a space or a letter or NaN, then it is ignored.
            {
                continue;
            }
            if (col >= mat_len) // If the amount of weights (edges) entered is more than the amount of vertices,
            {                   // an error will be printed and the program exits.
                cerr << "Error: the amount of weights entered is not equal to the amount of vertices!" << endl;
                exit(1);
            }
            int weight = input - '0'; // Parsing the input to an integer
            if (weight < 0)           // Negative weights are not allowed.
            {                         // If a negative weight is entered, an error will be printed and the program exits.
                cerr << "Error: weight must be a positive number! but it is: " << weight << endl;
                exit(1);
            }
            if (col == row && weight != 0) // Checking if the distance between a vertice and itself is 0.
            {
                cerr << "Error: the weight of the edge between vertice " << row << " and itself must be 0!" << endl;
                exit(1);
            }
            graph.at(row).push_back(weight); // Storing the weight at graph[row][col]
            col++;
        }
    }
}

/*
A function to print the array which stores the shortest distance from the source to each vertice in the graph.
*/
void printSolution(vector<int> dist)
{
    cout << "Vertex\tDistance from Source" << endl;
    for (size_t i = 0; i < dist.size(); i++)
    {
        if (dist[i] == INT_MAX) // If dist[i] was not updated, then the vertice is not connected to the source.
        {
            cout << i << "\t"
                 << "Not Connected" << endl;
        }
        else
        {
            cout << i << "\t" << dist[i] << endl;
        }
    }
}

/*
A function to find the neighbor with the minimum distance from the source.
Assuming that that neighbor was not visited yet.
*/
int MinNeighbor(vector<int> dist, vector<bool> converged)
{
    int min = INT_MAX, min_index;

    for (size_t vertex_i = 0; vertex_i < dist.size(); vertex_i++) // Looping through the vertices
        if (converged[vertex_i] == false && dist[vertex_i] <= min)
        {
            min = dist[vertex_i];   // The unvisited neighbor with the minimum distance from the source is stored in min.
            min_index = vertex_i;   // Updating min_index to the index of the neighbor with the minimum distance from the source.
        }
    return min_index;               // After iterating through all the vertices, the index of the neighbor with the minimum distance from the source is returned.
}
/*
A function that checks if a vertex should be relaxed or not.
*/
bool shouldRelax(int u, int v, int weight, vector<int> dist)
{
    if (dist[u] != INT_MAX && dist[u] + weight <= dist[v])
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
    dist.assign(graph.size(), INT_MAX);
    converged.assign(graph.size(), false);

    // Distance of source vertex from itself is always 0
    dist.at((size_t)src) = 0;

    // Find shortest path for all vertices
    for (size_t count = 0; count < graph.size(); count++)
    {
        // Pick the minimum distance vertex from the set of
        // vertices not yet processed. u is always equal to
        // src in the first iteration.
        int u = MinNeighbor(dist, converged);

        // Mark the picked vertex as processed
        converged[u] = true;

        // Update dist value of the adjacent vertices of the picked vertex.
        for (size_t v = 0; v < graph.size(); v++)

            // Update dist[v] only if is not in converged,
            // there is an edge from u to v, and total
            // weight of path from src to  v through u is
            // smaller than current value of dist[v]
            if (!converged[v] && graph[u][v] && shouldRelax(u, v, graph.at(u).at(v), dist))
            {
                dist[v] = dist[u] + graph[u][v];
            }
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
