#include "doctest.h"
#include "libdijkstra.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <cstdlib>      // To use rand()
#include <sstream>      // To use istringstream
#include <climits>      // To use INT_MAX
#include <algorithm>    // To use std::min_element
#include <set>          // To use set in MinNeighbor

using std::vector;

TEST_CASE("Test input_graph - Valid input")
{
    vector<vector<int>> graph = {{}};
    std::istringstream input("0 11 2\n1 0 3\n2 03 0\n");
    std::cin.rdbuf(input.rdbuf()); // Redirect cin to our input stream
    input_graph(graph);
    CHECK(graph[0][0] == 0);
    CHECK(graph[0][1] == 11);
    CHECK(graph[0][2] == 2);
    CHECK(graph[1][0] == 1);
    CHECK(graph[1][1] == 0);
    CHECK(graph[1][2] == 3);
    CHECK(graph[2][0] == 2);
    CHECK(graph[2][1] == 3);
    CHECK(graph[2][2] == 0);

    vector<vector<int>> graph2 = {{}};
    std::istringstream input2("0 1 2 3\n1 0 3 4\n2 3 0 5\n3 4 5 0\n");
    std::cin.rdbuf(input2.rdbuf()); 
    input_graph(graph2);
    CHECK(graph2[0][0] == 0);
    CHECK(graph2[0][1] == 1);
    CHECK(graph2[0][2] == 2);
    CHECK(graph2[0][3] == 3);
    CHECK(graph2[1][0] == 1);
    CHECK(graph2[1][1] == 0);
    CHECK(graph2[1][2] == 3);
    CHECK(graph2[1][3] == 4);
    CHECK(graph2[2][0] == 2);
    CHECK(graph2[2][1] == 3);
    CHECK(graph2[2][2] == 0);
    CHECK(graph2[2][3] == 5);
    CHECK(graph2[3][0] == 3);
    CHECK(graph2[3][1] == 4);
    CHECK(graph2[3][2] == 5);
    CHECK(graph2[3][3] == 0);
}

TEST_CASE("Test input_graph - Negative weight")
{
    vector<vector<int>> graph = {{}};
    std::istringstream input("0 -1 2\n1 0 3\n2 3 0\n");
    std::cin.rdbuf(input.rdbuf()); 
    CHECK_THROWS_AS(input_graph(graph), std::invalid_argument);
}

TEST_CASE("Test input_graph - Weighted vertex")
{
    vector<vector<int>> graph = {{}};
    std::istringstream input("1 1 2\n1 0 3\n2 3 0\n");
    std::cin.rdbuf(input.rdbuf()); 
    CHECK_THROWS_AS(input_graph(graph), std::invalid_argument);
}

TEST_CASE("Test input_graph - Too few vertices")
{
    vector<vector<int>> graph = {{}};
    std::istringstream input("0 1 2 3\n1 0 3\n2 3 0\n");
    std::cin.rdbuf(input.rdbuf()); 
    CHECK_THROWS_AS(input_graph(graph), std::length_error);
}

TEST_CASE("Test input_graph - Too many vertices")
{
    vector<vector<int>> graph = {{}};
    std::istringstream input("0 1\n1 0 3\n2 3 0\n");
    std::cin.rdbuf(input.rdbuf()); 
    CHECK_THROWS_AS(input_graph(graph), std::out_of_range);
}

TEST_CASE("Test dijkstra")
{
    vector<vector<int>> graph = {
        {0, 1, 2},
        {1, 0, 3},
        {2, 3, 0}};
    vector<int> dist(dijkstra(graph, 0));
    CHECK(dist[0] == 0);
    CHECK(dist[1] == 1);
    CHECK(dist[2] == 2);

    vector<vector<int>> graph2 = {
        {0, 1, 2, 3},
        {1, 0, 3, 4},
        {2, 3, 0, 5},
        {3, 4, 5, 0}};

    vector<int> dist2(dijkstra(graph2, 0));
    CHECK(dist2[0] == 0);
    CHECK(dist2[1] == 1);
    CHECK(dist2[2] == 2);
    CHECK(dist2[3] == 3);

    // Test with a random amount of vertices - which are not connected
    vector<vector<int>> graph3;
    size_t amount = (size_t)(rand() % 100) + 5;
    for (size_t i = 0; i < amount; i++)
    {
        vector<int> row;
        for (size_t j = 0; j < amount; j++)
        {
            if (i == j)
            {
                row.push_back(0);
            }
            else
            {
                row.push_back(INT_MAX);
            }
        }
        graph3.push_back(row);
    }
    for (size_t i = 0; i < amount; i++)
    {
        graph3.at(amount - (amount % 5)).at(i) = INT_MAX;
    }
    vector<int> dist3(dijkstra(graph3, 0));
    CHECK(dist3.at(amount - (amount % 5)) == INT_MAX);
}
TEST_CASE("Test print_dists")
{
    vector<int> dist = {0, 1, 2};
    CHECK(print_dists(dist) == "Vertex\tDistance from Source\n0\t0\n1\t1\n2\t2\n");

    vector<int> dist2 = {0, INT_MAX, 2};
    CHECK(print_dists(dist2) == "Vertex\tDistance from Source\n0\t0\n1\tNot Connected\n2\t2\n");

    // Test with a random amount of vertices - One of which is not connected
    vector<int> dist3;
    size_t amount = (size_t)(rand() % 100) + 5;
    for (size_t i = 0; i < amount ; i++)
    {
        dist3.push_back((rand() % 100) + 1);
    }
    dist3.at(amount - (amount % 5)) = INT_MAX;
    CHECK(print_dists(dist3).find("\tNot Connected\n") != std::string::npos); // Check if the output contains "Not Connected"

    // Test with a random amount of vertices - All connected
    vector<int> dist4;
    size_t amount2 = (size_t)(rand() % 100) + 5;
    for (size_t i = 0; i < amount2 ; i++)
    {
        dist4.push_back((rand() % 100) + 1);
    }
    CHECK(print_dists(dist4).find("Not Connected") == std::string::npos); 
}

TEST_CASE("Test should_relax - Relax")
{
    vector<int> dist = {0, 1, 2};
    CHECK(should_relax(0, 1, 1, dist) == true);

    // Test with a random amount of vertices which are all connected.
    vector<int> dist2((rand() % 50) + 5, (rand() % 50) + 5);
    CHECK(should_relax(0, 1, 0, dist2) == true);
}

TEST_CASE("Test should_relax - Don't relax")
{
    vector<int> dist = {0, 1, 2};
    CHECK(should_relax(0, 1, INT_MAX, dist) == false);

    // Test with a random amount of vertices which are all not connected.
    vector<int> dist2((rand() % 50) + 5, INT_MAX);
    CHECK(should_relax(0, 1, 1, dist2) == false);
}

TEST_CASE("Test min_neighbor")
{
    vector<int> dist = {0, 1, 2};
    vector<bool> converged = {false, false, false};
    CHECK(min_neighbor(dist, converged) == 0);   // The minimum neighbor is the src.

    // Test with a random amount of vertices which are all connected.
    size_t amount = (size_t)(rand() % 50) + 5;
    vector<int> dist2;
    std::set<int> dist2_set;
    vector<bool> converged2(amount, false);
    for (size_t i = 0; i < amount; i++)
    {
        int data = (rand() % 100) + 1;
        if(dist2_set.count(data) == 0)
        {
            dist2.push_back(data);
            dist2_set.insert(data);
        }
        else
        {
            data = (rand() % 100) + 1;
            i--;
        }
    }
    auto iterator = std::min_element(dist2.begin(), dist2.end());   // Find the minimum element in the vector (get an iterator to that position)
    
    int minIndex = std::distance(dist2.begin(), iterator);          // Get the index of the minimum element by calculating the distance 
                                                                    // between the beginning of the vector and the iterator
    CHECK(min_neighbor(dist2, converged2) == minIndex);
}
