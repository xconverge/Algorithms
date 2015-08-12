// Dijkstra's shortest path algorithm

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

// Edge structure to be used in graph data structure (array of edges)
struct edge
{
	// 2nd node to make the edge
	int node2;

	// Length value for edge
	int length;

	// Connected edge for dijkstra calculation
	edge *nextEdge;
};

// Dijkstra's shortest path algorithm
// Dist will be 1000000 if no path found
void Dijkstra(edge **graph, vector<int>& dist, int startNode, int numNodes)
{ 
	//Create a flag for whether or not a node has been visited and initialize to false
	vector<bool> visited(numNodes + 1, false);

	visited[startNode] = true;
	dist[startNode] = 0;

	// Iterate over all nodes to calculate shortest path between them and startNode (1)
	for (int i = 2; i <= numNodes; i++)
	{
		int node2, length = 1000000;

		// Calculate shortest path by adding all edges in a BFS manner
		for (int i = 1; i <= numNodes; i++)
		{
			if (visited[i])
			{
				edge *tmp = graph[i];
				while (tmp != NULL)
				{
					// Calculate path to see if shorter
					if (!visited[tmp->node2] && (dist[i] + tmp->length)<length)
					{
						node2 = tmp->node2;
						length = (dist[i] + tmp->length);
					}
					tmp = tmp->nextEdge;
				}
			}
		}
		visited[node2] = true;
		dist[node2] = length;
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
	ifstream file("C:/Users/sean/Downloads/dijkstraData.txt", ios::in);

	string tmp;
	int shortestPath = 0;

	// Add 1 to keep index inline with node number
	int numNodes = 200 + 1;

	// Create graph data structure
	edge **graph = new edge*[200+1];

	// Create structure to hold the distance data for each instance of node 1 to node X
	vector<int> dist(numNodes + 1);

	// Initialize the graph to be empty and have "infinite" distances
	for (int i = 0; i < numNodes; i++)
	{
		graph[i] = NULL;
		dist[i] = 1000000;
	}

	//Read file into graph structure
	while (!file.eof())
	{
		getline(file, tmp);
		vector<string> splitLine = split(tmp, '\t');
		if (splitLine.size() == 0)
			continue;

		for (int i = 1; i < (int)splitLine.size(); i++)
		{
			//Get comma separated node,length to create edge
			vector<string> splitEdge = split(splitLine[i], ',');

			edge *addEdge = new edge;
			addEdge->node2 = stoi(splitEdge[0]);
			addEdge->length = stoi(splitEdge[1]);
			addEdge->nextEdge = graph[stoi(splitLine[0])];
			graph[stoi(splitLine[0])] = addEdge;
		}
	}
	file.close();

	//Run Dijkstra's shortest path algorithm
	Dijkstra(graph, dist, 1, numNodes);

	// Output shortest path distances found
	int i = 0;
	for (int i = 1;i<numNodes; i++) {
		printf("Node %i: ", i);
		cout << dist[i] << endl;
	}

	// Desired shortest paths for the answers
	int answers[10] = { 7, 37, 59, 82, 99, 115, 133, 165, 188, 197 };

	// Print the answer
	for (int i = 0; i < (int)size(answers); i++) {
		cout << dist[answers[i]] << " ";
	}
	cout << endl;

	getchar();
	return 0;
}