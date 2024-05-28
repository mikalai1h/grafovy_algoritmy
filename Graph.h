#pragma once
#include <map>
#include <set>
#include <iostream>

using namespace std;


class Graph {

    std::map<int, set<int>> adj;
public:
    set<int> V;
    void addEdge(int, int);
    set<int> getNeighbors(int);
    void deleteVertex(int);
    void printGraph();
    int deg(int v);
};