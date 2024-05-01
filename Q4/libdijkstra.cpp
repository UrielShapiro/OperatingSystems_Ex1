#include <iostream>
#include <climits>
#include <vector>
#include <string>
#include <sstream>


using std::vector;

#define INFINITE INT_MAX

/*
A function that receives a graph represented as an adjacency matrix (line by line) and stores it in a 2D vector.
The function checks if the input is valid and throws an exception if it is not.
*/
void input_graph(vector<vector<int>> &graph)
{
    size_t mat_len = SIZE_MAX;                 // Setting the length of the matrix to the maximum value before the first iteration
                                               // In order to let the user enter the amount of vertices,
                                               // then limit the length of the matrix to that value.
    for (size_t row = 0; row < mat_len; row++)
    {
        size_t col = 0;
        std::cin.clear();                                                                  // Clearing the input buffer before each iteration.
        std::cout << "Enter the weight of the edges from vertex " << row << ": " << std::endl; // Prompting the user to enter the weights of the edges
        
        std::string buffer;
        std::getline(std::cin, buffer);
        std::istringstream iss(buffer);
        
        while (!iss.eof())                                           // Iterating through the input until the user presses enter ('\n')
        {
            int weight;
            iss >> weight;
            if (col >= mat_len) // If the amount of weights (edges) entered is more than the amount of vertices,
            {                   // an error will be thrown.
                throw std::out_of_range{"Error: the amount of weights entered is more than the amount of vertices!"};
            }
            if (weight < 0)           // Negative weights are not allowed.
            {                         // If a negative weight is entered, an exception will be thrown.
                throw std::invalid_argument{"Error: weight must be a positive number! but it is: " + std::to_string(weight) + "\n"};
            }
            if (col == row && weight != 0) // Checking if the distance between a vertex and itself isn't 0.
            {
                throw std::invalid_argument{"Error: the weight of the edge between vertex " + std::to_string(row) + " and itself must be 0!\n"};
            }
            graph.at(row).push_back(weight); // Storing the given weight at graph[row][col]
            col++;
        }
        if (row != 0 && col < mat_len) // If the amount of weights (edges) entered is less than the amount of vertices,
        {                              // an error will be thrown.
            throw std::length_error{"Error: the amount of weights entered is less than the amount of vertices!"};
        }

        if (row == 0) // After the user has entered the first row, then the length of the matrix is known
        {
            mat_len = graph.at(0).size();
            graph.resize(mat_len); // Resizing the matrix to the length of the matrix
        }
    }
}

/*
A function to print the array which stores the shortest distance from the source to each vertex in the graph.
*/
std::string print_dists(vector<int> dist)
{
    std::string output = "";
    output += "Vertex\tDistance from Source\n";
    for (size_t i = 0; i < dist.size(); i++)
    {
        if (dist[i] == INFINITE) // If dist[i] was not updated, then the vertex is not connected to the source.
        {
            output += std::to_string(i) + "\tNot Connected\n";
        }
        else
        {
            output += std::to_string(i) + "\t" + std::to_string(dist[i]) + "\n";
        }
    }
    return output; 
}

/*
A function to find the neighbor with the minimum distance from the source.
Assuming that that neighbor was not visited yet.
*/
int min_neighbor(vector<int> dist, vector<bool> converged)
{
    int min = INFINITE; 
    int min_index = 0; // Initializing it to -1 to avoid any errors when returning (uninitialized value otherwise).

    for (size_t vertex_i = 0; vertex_i < dist.size(); vertex_i++) // Looping through the vertices
        if (converged[vertex_i] == false && dist[vertex_i] <= min)  // If the neighbor was not visited yet and the distance
        // from the source is less or equal to the minimum distance from the source
        //This is the neighbor with the current minimum distance from the source.
        {
            min = dist[vertex_i]; // The unvisited neighbor with the minimum distance from the source is stored in min.
            min_index = vertex_i; // Updating min_index to the index of the neighbor with the minimum distance from the source.
        }
    return min_index; // Returning the index of the neighbor with the minimum distance from the source.
}

/*
A function that checks if a vertex should be relaxed or not.
*/
bool should_relax(int u, int v, int weight, vector<int> dist)
{
    // If the vertex was visited (it's distance from the origin was updated)
    // and the distance from the origin to that vertex from the path through vertex u is shorter than the current distance found from the origin to vertex v,
    if (dist[u] != INFINITE && dist[u] + weight <= dist[v])  
    {
        return true;
    }
    return false;
}

/*
Function that implements Dijkstra's single source shortest path algorithm 
for a graph represented using adjacency matrix
@return A vector that stores the shortest distance from the source to each vertex in the graph.
*/
vector<int> dijkstra(vector<vector<int>> graph, int src)
{
    vector<int> dist; // The output array.  dist[i] will hold the
                      // shortest distance from src to i

    vector<bool> converged; // converged[i] will be true if vertex i is
                            // included in shortest path tree or shortest distance from src to i is finalized

    // Initialize all distances as INFINITE and converged[] as false.
    dist.assign(graph.size(), INFINITE);
    converged.assign(graph.size(), false);

    dist.at((size_t)src) = 0;   // Distance of source vertex from itself is always 0

    // Find shortest path for all vertices
    for (size_t count = 0; count < graph.size(); count++)
    {
        // Pick the minimum distance vertex from the set of
        // vertices not yet processed. 
        // u = src in the first iteration
        int u = min_neighbor(dist, converged);

        // Mark the picked vertex as converged.
        converged[u] = true;

        // Update distance value of the adjacent vertices of the picked vertex. (Relaxation step)
        for (size_t v = 0; v < graph.size(); v++)

            // Update dist[v] only if is not in converged,
            // and there is an edge from u to v, 
            // and that vertex should relax (using the should_relax function)
            if (!converged[v] && graph[u][v] && should_relax(u, v, graph.at(u).at(v), dist))
            {
                dist[v] = dist[u] + graph[u][v];
            }
    }
    return dist;
}
