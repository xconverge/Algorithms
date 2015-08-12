#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <iterator>
#include <sstream>
#include <list>
#include <string>
#include <stack>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> sccCount;
int sccSize;


class Graph
{
// Number of nodes
int n;
vector<int> *adj;

// Depth First Search
void DFS(int n, bool explored[]);

// Function to fill stack with nodes
void createStack(int n, bool explored[], stack<int> &Stack);

public:
Graph(int n);
void addEdge(int n, int w);

// Main function to run the SCC finding algorithm
void findSCCs();

// Function to transpose the graph for 2nd DFS
Graph Reverse();
};


Graph::Graph(int n)
{
	this->n = n;
	adj = new vector<int>[n];
}

// Depth First Search function
void Graph::DFS(int n, bool explored[])
{
	// Current node is now explored
	explored[n] = true;

	// Recursive iterations for all nodes
	vector<int>::iterator i;
	for (i = adj[n].begin(); i != adj[n].end(); ++i)
		if (!explored[*i])
		{
			DFS(*i, explored);
		}
	sccSize += 1;
}

//Function used to reverse the graph before 2nd DFS
Graph Graph::Reverse()
{
	Graph g(n);
	for (int j = 0; j < n; j++)
	{
		// Look at all adjacent nodes
		vector<int>::iterator i;
		for (i = adj[j].begin(); i != adj[j].end(); ++i)
		{
			g.adj[*i].push_back(j);
		}
	}
	return g;
}

void Graph::addEdge(int n, int w)
{
	adj[n].push_back(w);
}

void Graph::createStack(int n, bool explored[], stack<int> &Stack)
{
	// Mark the current node as explored and print it
	explored[n] = true;

	// Recur for all the nodes adjacent to this node
	vector<int>::iterator i;
	for (i = adj[n].begin(); i != adj[n].end(); ++i)
		if (!explored[*i])
			createStack(*i, explored, Stack);

	Stack.push(n);
}

// The main function that finds and prints all SCCs
void Graph::findSCCs()
{
	stack<int> Stack;

	// Mark all the nodes as unexplored
	bool *explored = new bool[n];
	for (int i = 0; i < n; i++)
		explored[i] = false;

	// Add nodes into stack
	for (int i = 0; i < n; i++)
	{
		if (explored[i] == false)
			createStack(i, explored, Stack);
	}

	// Create a reversed graph
	Graph gReversed = Reverse();

	// Mark all the nodes as unexplored
	for (int i = 0; i < n; i++)
		explored[i] = false;

	// Process all nodes in the reverse order from the first DFS
	while (Stack.empty() == false)
	{
		// Grab a node
		int v = Stack.top();
		Stack.pop();

		// Add SCC size to vector
		if (explored[v] == false)
		{
			sccSize = 0;
			gReversed.DFS(v, explored);
			sccCount.push_back(sccSize);
		}
	}
}

//Function used to split a string into a vector
vector<std::string> &split(const string &s, char delim, vector<string> &elems) {
	stringstream ss(s);
	string item;
	while (getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
}

//Function used to split a string into a vector
vector<string> split(const string &s, char delim) {
	vector<string> elems;
	split(s, delim, elems);
	return elems;
}

// Main function reads input from file and runs quicksort
int _tmain(int argc, _TCHAR* argv[])
{
	ifstream file("C:/Users/sean/Downloads/test1.txt", ios::in);

	string tmp;

	int numNodes = 0;

	numNodes = std::count(std::istreambuf_iterator<char>(file),
		std::istreambuf_iterator<char>(), '\n') + 1;

	file.clear();
	file.seekg(0, ios::beg);

	Graph g(numNodes);

	//Read file into graph structure
	while (!file.eof())
	{
		getline(file, tmp);
		vector<string> splitLine = split(tmp, ' ');
		if (splitLine.size() == 0)
			continue;

		for (int i = 1; i < (int)splitLine.size(); i++)
		{
			g.addEdge(stoi(splitLine[0]), stoi(splitLine[i]));
		}

	}
	file.close();

	cout << "Starting algorithm... \n";
	g.findSCCs();
	sort(sccCount.rbegin(), sccCount.rend());

	cout << "Top 5 SCC's are: \n";
	for (int i = 0; i < 5; i++)
	{
		cout << sccCount[i] << endl;;
	}

	getchar();
	return 0;
}