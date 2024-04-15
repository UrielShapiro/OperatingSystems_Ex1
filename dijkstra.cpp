#include <iostream>
#include <climits>

////////////////////DOES NOT WORK////////////////////

int main()
{
    std::cout << "Enter the amount of vertices: " << std::endl;
    int V;
    std::cin >> V;

    int graph[V][V];

    for (size_t i = 0; i < V; i++)
    {
        for (size_t j = 0; j < V; j++)
        {
            std::cout << "Enter the weight of the edge between vertice " << i << "to vertice " << j << ": " << std::endl;
            int weight;
            std::cin >> weight;
            if(weight < 0)
            {
                std::cout << "Error: weight must be a positive number!" << std::endl;
                return 1;
            }
            graph[i][j] = weight;
        } 
    }

    for (size_t i = 0; i < V; i++)
    {
        if(graph[i][i] != 0)
        {
            std::cout << "Error: the weight of the edge between vertice " << i << " and itself must be 0!" << std::endl;
            return 1;
        }
    }
    
    dijkstra(V, graph, 0);
    
    return 0;
}


// A utility function to find the vertex with minimum
// distance value, from the set of vertices not yet included
// in shortest path tree
int relax(int V, int dist[], bool sptSet[])
{
    // Initialize min value
    int min = INT_MAX, min_index;
 
    for (int v = 0; v < V; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;
 
    return min_index;
}

// A utility function to print the constructed distance array
void printSolution(int V, int dist[])
{
    std::cout << "Vertex \t Distance from Source" << std::endl;
    for (int i = 0; i < V; i++)
        std::cout << i << " \t\t\t\t" << dist[i] << std::endl;
}

// Function that implements Dijkstra's single source shortest path algorithm
// for a graph represented using adjacency matrix representation
void dijkstra(int V, int** graph, int src)
{
    int dist[V]; // The output array.  dist[i] will hold the
                 // shortest
    // distance from src to i
 
    bool sptSet[V]; // sptSet[i] will be true if vertex i is
                    // included in shortest
    // path tree or shortest distance from src to i is
    // finalized
 
    // Initialize all distances as INFINITE and stpSet[] as
    // false
    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX, sptSet[i] = false;
 
    // Distance of source vertex from itself is always 0
    dist[src] = 0;
 
    // Find shortest path for all vertices
    for (int count = 0; count < V - 1; count++) {
        // Pick the minimum distance vertex from the set of
        // vertices not yet processed. u is always equal to
        // src in the first iteration.
        int u = relax(dist, sptSet);
 
        // Mark the picked vertex as processed
        sptSet[u] = true;
 
        // Update dist value of the adjacent vertices of the
        // picked vertex.
        for (int v = 0; v < V; v++)
 
            // Update dist[v] only if is not in sptSet,
            // there is an edge from u to v, and total
            // weight of path from src to  v through u is
            // smaller than current value of dist[v]
            if (!sptSet[v] && graph[u][v]
                && dist[u] != INT_MAX
                && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }
 
    // print the constructed distance array
    printSolution(dist);
}