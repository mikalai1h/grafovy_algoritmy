#pragma once
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include "Graph.h"

using namespace std;


class ReverseSearch
{
    Graph graph;
    set<set<int>> subGraphs;
    int k;
public:
    set<set<int>> reverseSearch(Graph, int);
    void enumerateCIS(vector<int>, map<int, int>, map<int, int>, set<int>);
    bool isValidExtension(vector<int>, map<int, int>, int);
};


