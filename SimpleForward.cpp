#include "SimpleForward.h"

set<set<int>> SimpleForward::getSubGraphs(Graph g, int k)
{
    graph = g;
    this->k = k;
    set<set<pair<int, int>>> edgelist;
    while (graph.V.size() >= k)
    {
        int v = *graph.V.begin();
        set<int> P;
        set<int> X;
        P.insert(v);
        X = graph.getNeighbors(v);
        simpleForward(P, X);
        graph.deleteVertex(v);
    }

    return subGraphs;

}

bool SimpleForward::simpleForward(set<int> P, set<int> X)
{
    if (P.size() == k)
    {
        subGraphs.insert(P);
        return true;
    }
    bool hasIntLeaf = false;
    while (!X.empty())
    {
        int u = *X.begin();
        X.erase(u);
        set<int> newX(X.begin(), X.end());
        set<int> N = graph.getNeighbors(u);
        newX.insert(N.begin(), N.end());
        for (auto& v : P)
            newX.erase(v);
        set<int> newP(P.begin(), P.end());
        newP.insert(u);
        if (simpleForward(newP, newX))
            hasIntLeaf = true;
        else
            return hasIntLeaf;

    }
    return hasIntLeaf;
}