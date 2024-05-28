#pragma once
#include "Graph.h"

class SimpleForward
{
    int k;
    Graph graph;
    set<set<int>> subGraphs;

public:
    set<set<int>> getSubGraphs(Graph, int);
    bool simpleForward(set<int>, set<int>);
};