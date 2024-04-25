#include "doctest.h"
#include "libdijkstra.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <cstdlib>
#include <sstream>

using namespace std;

TEST_CASE("Test inputGraph - Valid input")
{
    vector<vector<int>> graph = {{}};
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
    vector<vector<int>> graph = {{}};
    std::istringstream input("0 -1 2\n1 0 3\n2 3 0\n");
    std::cin.rdbuf(input.rdbuf()); // Redirect cin to our input stream
    CHECK_THROWS_AS(input_graph(graph), invalid_argument);
}

TEST_CASE("Test inputGraph - Weighted vertice")
{
    vector<vector<int>> graph = {{}};
    istringstream input("1 1 2\n1 0 3\n2 3 0\n");
    cin.rdbuf(input.rdbuf()); // Redirect cin to our input stream
    CHECK_THROWS_AS(input_graph(graph), invalid_argument);
}

TEST_CASE("Test inputGraph - Too less vertices")
{
    vector<vector<int>> graph = {{}};
    std::istringstream input("0 1 2 3\n1 0 3\n2 3 0\n");
    std::cin.rdbuf(input.rdbuf()); // Redirect cin to our input stream
    CHECK_THROWS_AS(input_graph(graph), length_error);
}

TEST_CASE("Test inputGraph - Too much vertices")
{
    vector<vector<int>> graph = {{}};
    std::istringstream input("0 1\n1 0 3\n2 3 0\n");
    std::cin.rdbuf(input.rdbuf()); // Redirect cin to our input stream
    CHECK_THROWS_AS(input_graph(graph), out_of_range);
}

TEST_CASE("Test dijkstra - Valid input")
{
    vector<vector<int>> graph = {
        {0, 1, 2},
        {1, 0, 3},
        {2, 3, 0}};
    dijkstra(graph, 0);
    vector<int> dist = {0, 1, 2};
    CHECK(dist[0] == 0);
    CHECK(dist[1] == 1);
    CHECK(dist[2] == 2);
}

TEST_CASE("Test PrintSolution")
{
    vector<int> dist = {0, 1, 2};
    CHECK(printSolution(dist) == "Vertex\tDistance from Source\n0\t0\n1\t1\n2\t2\n");
}

TEST_CASE("Test shouldRelax - Relax")
{
    vector<int> dist = {0, 1, 2};
    CHECK(shouldRelax(0, 1, 1, dist) == true);
}
