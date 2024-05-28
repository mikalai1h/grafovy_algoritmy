#include <fstream>
#include <stdexcept>
#include <string>
#include <sstream>
#include <time.h> 
#include "ConSubG.h"
#include "ReverseSearch.h"
#include "SimpleForward.h"

void ConsoleClear();
void InitConSubg(Graph);
void InitReverseSearch(Graph);
void InitSimpleForward(Graph);
Graph InitEdgeList();
Graph InitAdjList();
int InitSelection();
int AlgorithmMenu(Graph);
int AlgorithmSelection();
void SubgraphsToFile(set<set<int>>, Graph);

int main()
{
	enum { EdgeList = 1, AdjacencyList, Exit };
	while (true)
	{
		int Key = InitSelection();

		if (Key == Exit)
			return 0;
		system("cls");
		Graph g;
		try {
			switch (Key)
			{
			case EdgeList:
				g = InitEdgeList();
				system("cls");
				break;
			case AdjacencyList:
				g = InitAdjList();
				system("cls"); 
				break;
			default:
				cout << "\nIncorrect input! Try again!";
				continue;
			}
			AlgorithmMenu(g);
		}
		catch (const std::string& error_message)
		{
			cout << error_message << endl;
			ConsoleClear();
		}
	}
}

void ConsoleClear()
{
	cout << endl;
	system("pause");
	system("cls");
}


void InitConSubg(Graph g)
{
	int k;
	cout << "\nEnter the size of subgraphs: ";
	cin >> k;
	system("cls");
	ConSubg consubg;
	time_t start, end;
	time(&start);
	set<set<int>> subg = consubg.conSubg(k, g);
	time(&end);
	SubgraphsToFile(subg, g);
	
}

void InitReverseSearch(Graph g)
{
	int k;
	cout << "\nEnter the size of subgraphs: ";
	cin >> k;
	system("cls");
	ReverseSearch rs;
	time_t start, end;
	time(&start);
	set<set<int>> subg = rs.reverseSearch(g, k);
	time(&end);
	SubgraphsToFile(subg, g);

}

void InitSimpleForward(Graph g)
{
	int k;
	cout << "\nEnter the size of subgraphs: ";
	cin >> k;
	system("cls");
	SimpleForward sf;
	time_t start, end;
	time(&start);
	set<set<int>> subg = sf.getSubGraphs(g, k);
	time(&end);
	SubgraphsToFile(subg, g);

}

int AlgorithmSelection()
{
	int k;
	cout << "\n Enter the number - subgraph search algorithm:"
		"\n 1 - ConSubg"
		"\n 2 - ReverseSearch"
		"\n 3 - SimpleForward"
		"\n 4 - BACK\n";
	cin >> k;
	return k;
}

int InitSelection()
{
	int k;
	cout << "\n Enter the number - type of graph initialization:"
		"\n 1 - Edge List"
		"\n 2 - Adjacency list"
		"\n 3 - EXIT\n";
	cin >> k;
	return k;
}

int AlgorithmMenu(Graph g)
{
	enum { ConSubg = 1, ReverseSearch, SimpleForward, Back };
	while (true)
	{
		int Key = AlgorithmSelection();
		int k = 0;
		if (Key == Back)
		{
			ConsoleClear();
			return 0;
		}
		system("cls");
		switch (Key)
		{
		case ConSubg:
			InitConSubg(g);
			ConsoleClear();
			break;
		case ReverseSearch:
			InitReverseSearch(g);
			ConsoleClear();
			break;
		case SimpleForward:
			InitSimpleForward(g);
			ConsoleClear();
			break;
		default:
			cout << "\nIncorrect input! Try again!";
		}
	}
}

Graph InitEdgeList()
{
	Graph g;
	string fileName, str;
	cout << "\nEnter graph filename: ";
	cin >> fileName;
	ifstream inFile(fileName);
	if (!inFile.is_open()) 
		throw string{"Unable to open file"};
	while (getline(inFile, str)) {
		int num1, num2;
		stringstream ss(str);
		if (ss >> num1 >> num2)
			g.addEdge(num1, num2);
		else
			throw string{"Invalid edge list in file"};
	}
	inFile.close();
	return g;
}

Graph InitAdjList()
{
	Graph g;
	string str, fileName;
	vector<set<int>> adjList;
	cout << "\nEnter graph filename: ";
	cin >> fileName;
	ifstream inFile(fileName);
	if (!inFile.is_open())
		throw string{ "Unable to open file" };

	while (getline(inFile, str)) {
		int n;
		stringstream ss(str);
		set<int> adj;
		while (ss >> n)
			adj.insert(n);
		adjList.push_back(adj);
	}
	inFile.close();
	int i = 1;
	for (set<int> adj : adjList)
	{
		for (int n : adj)
		{
			if(n > adjList.size())
				throw string{ "Invalid adjacency list in file" };
			g.addEdge(i, n);
		}
		i++;
	}
	return g;
}

void SubgraphsToFile(set<set<int>> subgraphs, Graph g)
{	
	set<int> visited;
	set<set<pair<int, int>>> edgelist;
	for (auto& subgraph : subgraphs)
	{
		set<int> visited;
		set<pair<int, int>> edges;
		for (auto& vertex : subgraph)
		{
			for (auto& n : g.getNeighbors(vertex))
			{
				if (subgraph.count(n) != 0 && visited.count(n) == 0)
				{
					edges.insert(make_pair(vertex, n));

				}
			}
			visited.insert(vertex);
		}
		edgelist.insert(edges);
	}
	std::ofstream out;          
	out.open("subgraphs.txt");
	if (out.is_open())
	{
		for (auto& comb : edgelist)
		{
			for (auto& pair : comb)
			{

				out << "(" << pair.first << ", " << pair.second << ") ";
			}
			out << endl;
		}
	}
}