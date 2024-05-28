#include "ReverseSearch.h"

set<set<int>> ReverseSearch::reverseSearch(Graph g, int k)
{
    this->k = k;
    graph = g;
    for (auto& v : graph.V) {

        vector<int> U;
        map<int, int>  P, D;
        U.push_back(v);
        P[v] = -1;
        D[v] = 0;
        enumerateCIS(U, P, D, graph.getNeighbors(v));
    }

    return subGraphs;
}

void ReverseSearch::enumerateCIS(vector<int> U, map<int, int> P, map<int, int> D, set<int> C)
{
    for (auto& v : C)
    {
        if (P.find(v) == P.end())
            P[v] = U.back();
        if (D.find(v) == D.end())
            D[v] = D[U.back()] + 1;
        if (U.size() == k)
        {
            subGraphs.insert(set<int>(U.begin(), U.end()));
            break;
        }
        if (isValidExtension(U, D, v))
        {
            vector<int> newU(U.begin(), U.end());
            set<int> newC = graph.getNeighbors(v);
            newU.push_back(v);
            newC.insert(C.begin(), C.end());
            enumerateCIS(newU, P, D, newC);

        }
    }
}

bool ReverseSearch::isValidExtension(vector<int> U, map<int, int> D, int v)
{
    int anchor = U.front();
    int last = U.back();
    if (v < anchor)
        return false;
    if (D[v] > D[last])
        return true;
    return D[v] == D[last] && v > last;
}