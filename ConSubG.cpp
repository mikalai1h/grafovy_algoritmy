#include "ConSubG.h"

CTNode* CombinationTree::combinationTree(int v, int k, Graph g)
{
	root->vertexValue = v;
	list.clear();
	list[0] = set<int>{ v };
	buildTree(root, 1, g, k);
	return root;
}

void CombinationTree::buildTree(CTNode* node, int depth, Graph g, int k)
{
	list[depth] = list[depth - 1];
	for (auto& v : g.getNeighbors(node->vertexValue))
	{
		if (list[depth].count(v) == 0)
		{
			CTNode* new_node = new CTNode();
			new_node->vertexValue = v;
			node->childs.push_back(new_node);
			list[depth].insert(v);
			if (visited.count(v) == 0)
			{
				visited.insert(v);
			}
			else
				new_node->N = false;
			if (depth + 1 < k)
				buildTree(new_node, depth + 1, g, k);
		}
	}
}

set<set<CTNode*>> CombinationsFromTree::combinationsFromTree(CTNode* tree, int k)
{
	map<int, set<set<CTNode*>>> S;
	CTNode* t = tree;
	set<set<CTNode*>> lnodesets;
	if (k == 1) return set<set<CTNode*>>{{t}};
	for (int i = 1; i <= min((int)t->childs.size(), (k - 1)); i++)
	{
		vector<vector<CTNode*>> kCombs;
		vector<vector<int>> kCompos;
		vector<CTNode*> currentComb;
		vector<int> currentCompos;
		kCombinations(t->childs, i, currentComb, 0, kCombs);
		kCompositions(currentCompos, i, (k - 1), kCompos);
		for (auto& NodeComb : kCombs)
		{
			for (auto& StrComp : kCompos)
			{
				bool fail = false;
				for (int pos = 1; pos <= i; pos++)
				{
					CTNode* stRoot = NodeComb[pos - 1];
					int size = StrComp[pos - 1];
					S[pos - 1] = combinationsFromTree(stRoot, size);
					if (S[pos - 1].empty())
					{
						fail = true;
						break;
					}

				}
				if (fail == true)
					continue;
				set<set<CTNode*>> combProduct = S[0];
				for (int j = 1; j < i; j++)
					combProduct = unionProduct(combProduct, S[j]);
				for (auto& combP : combProduct)
				{
					set<CTNode*> temp{ combP };
					temp.insert(t);
					lnodesets.insert(temp);
				}

			}
		}
	}
	S.clear();
	return lnodesets;
};

void CombinationsFromTree::kCombinations(const vector<CTNode*>& elements, int length, vector<CTNode*>& current, int index, vector<vector<CTNode*>>& result) {
	if (length == 0) {
		result.push_back(current);
		return;
	}

	for (int i = index; i <= elements.size() - length; i++) {
		current.push_back(elements[i]);
		kCombinations(elements, length - 1, current, i + 1, result);
		current.pop_back();
	}
}


void CombinationsFromTree::kCompositions(vector<int>& current, int length, int k, vector<vector<int>>& result) {

	if (length == 1) {
		current.push_back(k);
		result.push_back(current);
		current.pop_back();
		return;
	}

	for (int i = 1; i <= k - length + 1; i++) {
		current.push_back(i);
		kCompositions(current, length - 1, k - i, result);
		current.pop_back();
	}

}
set<set<CTNode*>> CombinationsFromTree::unionProduct(set<set<CTNode*>> Str1, set<set<CTNode*>> Str2)
{
	if (Str1.empty())
		return set<set<CTNode*>>{};
	if (Str2.empty())
		return Str1;
	set<set<CTNode*>> productResult;
	for (auto& s1 : Str1)
	{
		for (auto& s2 : Str2)
		{
			set<CTNode*> res;
			bool isSame = false;
			bool existNew = false;
			bool sameChild = false;
			for (auto& node1 : s1)
			{
				res.insert(node1);
				for (auto& node2 : s2)
				{
					if (node1->vertexValue == node2->vertexValue)
					{
						isSame = true;
						break;
					}
					if (node2->N)
						existNew = true;
					for (auto& child : node1->childs)
					{
						if (child->vertexValue == node2->vertexValue)
						{
							sameChild = true;
							break;
						}
					}

					res.insert(node2);
				}
				if (isSame || (!existNew && sameChild))
					break;
			}
			if (isSame || (!existNew && sameChild))
				continue;
			productResult.insert(res);
		}
	}

	return productResult;
}

set<set<int>> ConSubg::conSubg(int k, Graph g)
{
	queue<int> q;
	for (auto& v : g.V)
		q.push(v);
	while (q.size() > 0)
	{
		int v = q.front();
		q.pop();
		set<set<int>> combs = combinationWithV(v, k, g);
		if (!combs.empty())
		{
			allConnSubg.insert(combs.begin(), combs.end());
		}
		g.deleteVertex(v);
	}

	return allConnSubg;
}

set<set<int>> ConSubg::combinationWithV(int v, int k, Graph g)
{
	set<set<int>> result;
	CombinationTree ctree;
	CombinationsFromTree cf;
	CTNode* root = ctree.combinationTree(v, k, g);
	set<set<CTNode*>> allCombs = cf.combinationsFromTree(root, k);
	for (auto& comb : allCombs)

	{
		set<int> temp;
		for (auto& node : comb)
		{
			temp.insert(node->vertexValue);
		}
		result.insert(temp);
	}
	return result;
}