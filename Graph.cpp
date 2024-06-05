#include "Graph.h"


void Graph::addEdge(int v1, int v2) {
    V.insert(v1);
    V.insert(v2);
    adj[v1].insert(v2);
    adj[v2].insert(v1);
}

set<int> Graph::getNeighbors(int v) {
    return adj[v];
}

void Graph::deleteVertex(int v)
{
    V.erase(v);
    adj.erase(v);
    for (auto& it : adj)
        it.second.erase(v);
}

int Graph::deg(int v)
{
    if (V.count(v) == 0)
        return 0;
    return adj[v].size();
}
