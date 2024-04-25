#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>
#include <vector>
#include <sstream>
#include "dijkstra.cpp" // Assuming the function is in this file

TEST_CASE("Test populateGraph function")
{
    std::vector<std::vector<int>> graph;

    SUBCASE("Test with valid input")
    {
        std::istringstream input("0 1 2\n1 0 3\n2 3 0\n");
        std::cin.rdbuf(input.rdbuf()); // Redirect cin to our input stream
        input_graph(graph);
        CHECK(graph[0][0] == 0);
        CHECK(graph[0][1] == 1);
        CHECK(graph[0][2] == 2);
        CHECK(graph[1][0] == 1);
        CHECK(graph[1][1] == 0);
        CHECK(graph[1][2] == 3);
        CHECK(graph[2][0] == 2);
        CHECK(graph[2][1] == 3);
        CHECK(graph[2][2] == 0);
    }

    SUBCASE("Test with invalid input - more weights than vertices")
    {
        std::istringstream input("0 1 2 3\n1 0 3\n2 3 0\n");
        std::cin.rdbuf(input.rdbuf()); // Redirect cin to our input stream
        CHECK_THROWS_WITH(populateGraph(graph), "Error: the amount of weights entered is more than the amount of vertices!");
    }

    SUBCASE("Test with invalid input - negative weight")
    {
        std::istringstream input("0 -1 2\n1 0 3\n2 3 0\n");
        std::cin.rdbuf(input.rdbuf()); // Redirect cin to our input stream
        CHECK_THROWS_WITH(populateGraph(graph), "Error: weight must be a positive number! but it is: -1\n");
    }

    SUBCASE("Test with invalid input - non-zero weight for vertex to itself")
    {
        std::istringstream input("1 1 2\n1 0 3\n2 3 0\n");
        std::cin.rdbuf(input.rdbuf()); // Redirect cin to our input stream
        CHECK_THROWS_WITH(populateGraph(graph), "Error: the weight of the edge between vertice 0 and itself must be 0!\n");
    }
}

#include <cstdlib>
#include "doctest.h"
#include "dijkstra.hpp"
#include <vector>
#include <iostream>
#include <string>
using namespace std;

/*
 * This function simulates a key press in the terminal.
 * It does so by setting the terminal to non-canonical mode (disabling line buffering and echoing) and
 * writing the desired key to the input buffer.
 */
void simulateKeyboardInput(size_t size)
{
    char *output = new char[size];
    output[0] = 0;
    output[1] = ' ';
    for (size_t i = 2; i < (size / 2) - 1; i++)
    {
        cout << "output[i]: " << output[i] << endl;
        output[i] = (char)rand();
        output[i + 1] = ' ';
    }
    output[size - 1] = '\n';
    system(output);
    delete[] output;
}
namespace Test
{
    void run()
    {
        doctest::Context context;
        context.addFilter("test-case", "Test inputGraph - Valid input"); // only run test cases with "inputGraph" in their name
        context.run();
    }
}

TEST_CASE("Test inputGraph - Valid input")
{
    vector<vector<int>> graph;
    std::istringstream input("0 1 2\n1 0 3\n2 3 0\n");
    std::cin.rdbuf(input.rdbuf()); // Redirect cin to our input stream
    input_graph(graph);
    CHECK(graph[0][0] == 0);
    CHECK(graph[0][1] == 1);
    CHECK(graph[0][2] == 2);
    CHECK(graph[1][0] == 1);
    CHECK(graph[1][1] == 0);
    CHECK(graph[1][2] == 3);
    CHECK(graph[2][0] == 2);
    CHECK(graph[2][1] == 3);
    CHECK(graph[2][2] == 0);
}

TEST_CASE("Test inputGraph - Negative weight")
{
    vector<vector<int>> graph;
    std::istringstream input("0 -1 2\n1 0 3\n2 3 0\n");
    std::cin.rdbuf(input.rdbuf()); // Redirect cin to our input stream
    CHECK_THROWS_AS(input_graph(graph), invalid_argument);
}

TEST_CASE("Test inputGraph - Weighted vertice")
{
    vector<vector<int>> graph;
    istringstream input("1 1 2\n1 0 3\n2 3 0\n");
    cin.rdbuf(input.rdbuf()); // Redirect cin to our input stream
    CHECK_THROWS_AS(input_graph(graph), invalid_argument);
}

TEST_CASE("Test inputGraph - Too less vertices")
{
    vector<vector<int>> graph;
    std::istringstream input("0 1 2 3\n1 0 3\n2 3 0\n");
    std::cin.rdbuf(input.rdbuf()); // Redirect cin to our input stream
    CHECK_THROWS_AS(input_graph(graph), length_error);
}

TEST_CASE("Test inputGraph - Too much vertices")
{
    vector<vector<int>> graph;
    std::istringstream input("0 1\n1 0 3\n2 3 0\n");
    std::cin.rdbuf(input.rdbuf()); // Redirect cin to our input stream
    CHECK_THROWS_AS(input_graph(graph), out_of_range);
}

// TEST_CASE("Test isConnected")
// {
//     ariel::Graph g;
//     vector<vector<int>> graph = {
//         {0, 1, 0},
//         {1, 0, 1},
//         {0, 1, 0}};
//     g.loadGraph(graph);
//     CHECK(ariel::Algorithms::isConnected(g) == true);

//     vector<vector<int>> graph2 = {
//         {0, 1, 1, 0, 0},
//         {1, 0, 1, 0, 0},
//         {1, 1, 0, 1, 0},
//         {0, 0, 1, 0, 0},
//         {0, 0, 0, 0, 0}};
//     g.loadGraph(graph2);
//     CHECK(ariel::Algorithms::isConnected(g) == false);
// }

// TEST_CASE("Test shortestPath")
// {
//     ariel::Graph g;
//     vector<vector<int>> graph = {
//         {0, 1, 0},
//         {1, 0, 1},
//         {0, 1, 0}};
//     g.loadGraph(graph);
//     CHECK(ariel::Algorithms::shortestPath(g, 0, 2) == "0->1->2");

//     vector<vector<int>> graph2 = {
//         {0, 1, 1, 0, 0},
//         {1, 0, 1, 0, 0},
//         {1, 1, 0, 1, 0},
//         {0, 0, 1, 0, 0},
//         {0, 0, 0, 0, 0}};
//     g.loadGraph(graph2);
//     CHECK(ariel::Algorithms::shortestPath(g, 0, 4) == "-1");
// }
// TEST_CASE("Test isContainsCycle")
// {
//     ariel::Graph g;
//     vector<vector<int>> graph = {
//         {0, 1, 0},
//         {1, 0, 1},
//         {0, 1, 0}};
//     g.loadGraph(graph);
//     CHECK(ariel::Algorithms::isContainsCycle(g) == false);

//     vector<vector<int>> graph2 = {
//         {0, 1, 1, 0, 0},
//         {1, 0, 1, 0, 0},
//         {1, 1, 0, 1, 0},
//         {0, 0, 1, 0, 0},
//         {0, 0, 0, 0, 0}};
//     g.loadGraph(graph2);
//     CHECK(ariel::Algorithms::isContainsCycle(g) == true);
// }
// TEST_CASE("Test isBipartite")
// {
//     ariel::Graph g;
//     vector<vector<int>> graph = {
//         {0, 1, 0},
//         {1, 0, 1},
//         {0, 1, 0}};
//     g.loadGraph(graph);
//     CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={0, 2}, B={1}");

//     vector<vector<int>> graph2 = {
//         {0, 1, 1, 0, 0},
//         {1, 0, 1, 0, 0},
//         {1, 1, 0, 1, 0},
//         {0, 0, 1, 0, 0},
//         {0, 0, 0, 0, 0}};
//     g.loadGraph(graph2);
//     CHECK(ariel::Algorithms::isBipartite(g) == "0");

//     vector<vector<int>> graph3 = {
//         {0, 1, 2, 0, 0},
//         {1, 0, 3, 0, 0},
//         {2, 3, 0, 4, 0},
//         {0, 0, 4, 0, 5},
//         {0, 0, 0, 5, 0}};
//     g.loadGraph(graph3);
//     CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={0, 2, 4}, B={1, 3}");
// }
// TEST_CASE("Test invalid graph")
// {
//     ariel::Graph g;
//     vector<vector<int>> graph = {
//         {0, 1, 2, 0},
//         {1, 0, 3, 0},
//         {2, 3, 0, 4},
//         {0, 0, 4, 0},
//         {0, 0, 0, 5}};
//     CHECK_THROWS(g.loadGraph(graph));
// }
