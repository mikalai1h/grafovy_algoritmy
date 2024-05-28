#pragma once
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <utility>
#include <queue>
#include "Graph.h"

using namespace std;

struct CTNode {
    int vertexValue;
    bool N = true;
    vector<CTNode*> childs;
};


class CombinationTree {
    CTNode* root = new CTNode();
    map<int, set<int>> list;
    set<int> visited;
public:
    CTNode* combinationTree(int, int, Graph);
    void buildTree(CTNode*, int, Graph, int);
};

class CombinationsFromTree
{
public:
    set<set<CTNode*>> combinationsFromTree(CTNode* tree, int k);
    
    void kCombinations(const vector<CTNode*>& elements, int length, vector<CTNode*>& current, int index, vector<vector<CTNode*>>& result);
    void kCompositions(vector<int>&, int, int, vector<vector<int>>&);
    set<set<CTNode*>> unionProduct(set<set<CTNode*>>, set<set<CTNode*>>);
};

class ConSubg
{
    set<set<int>> allConnSubg;
public:
    set<set<int>> conSubg(int, Graph);
    set<set<int>> combinationWithV(int, int, Graph);
};