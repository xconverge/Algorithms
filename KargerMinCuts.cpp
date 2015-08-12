#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <time.h>
#include <vector>
#include <iterator>
#include <sstream>
#include <map>
#include <string>

using namespace std;

int Karger(map<int, vector<int>> data)
{
	int rand1, rand2;
	int v1, v2;

	// Loop while there are more than 2 nodes (the entire graph has not been randomly contracted completely
	while (data.size() > 2)
	{
		//Retreive a random key/node from the graph
		auto it = data.begin();
		std::advance(it, rand() % data.size());
		rand1 = it->first;

		//Retreive a random node from the list associated with the first node
		rand2 = rand() % data[rand1].size();

		//2 random verticies to merge
		v1 = rand1;
		v2 = data[rand1][rand2];

		//Append nodes from v2 adjacency list to the v1 node list
		data[v1].reserve(data[v1].size() + distance(data[v2].begin() , data[v2].end()));
		data[v1].insert(data[v1].end(), data[v2].begin() , data[v2].end());

		//Iterate through all nodes and replace all instances of v2 with v1
		map < int, vector < int> >::iterator map_it;
		for (map_it = data.begin(); map_it != data.end(); ++map_it){

			for (int i = 0; i < (*map_it).second.size(); i++)
			{
				if ((*map_it).second[i] == v2){
					(*map_it).second.erase((*map_it).second.begin() + i);
					(*map_it).second.shrink_to_fit();
					i--;
				}
			}
			(*map_it).second.push_back(v1);
		}

		// Remove all self loop nodes in the list for the node
		for (int k = 0; k < (int)data[v1].size(); k++)
		{
			// Remove self loops
			if (data[v1][k] == v1)
			{
				data[v1].erase(data[v1].begin() + k);
				data[v1].shrink_to_fit();
				//Iterator has changed when element was erased so backtrack 1 element
				k--;
			}
		}
		//Remove the contracted unused node
		data.erase(v2);
	}

	//Return the number of cross links
	return data[v1].size();
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
	ifstream file("C:/Users/sean/Downloads/test.txt", ios::in);

	string tmp;
	int minCut = 0;
	int bestMinCut = 0;
	int numTrials = 100;

	// Change the random seed value
	srand((int)time(NULL));

	// Create graph data structure
	map<int,vector<int>> graph;

	//Read file into graph structure
	while (!file.eof())
	{
		getline(file, tmp);
		vector<string> splitLine = split(tmp, ' ');
		if (splitLine.size() == 0)
			continue;

		for (int i = 1; i < (int)splitLine.size(); i++)
		{
			graph[stoi(splitLine[0])].push_back(stoi(splitLine[i]));
		}

	}
	file.close();

	// Iterate over the algorithm many times to get a higher probability of getting the correct number of cuts
	for (int j = 0; j < numTrials; j++)
	{
		map<int, vector<int>> temp = graph;

		//Perform the random contraction algorithm
		minCut = Karger(graph);
		cout << minCut << endl;

		//If first iteration, take this value as the minum
		if (j == 0)
			bestMinCut = minCut;
		//If not first iteration, check for lower value and set that to the best
		else if (minCut < bestMinCut)
			bestMinCut = minCut;
	}

	cout << "The Minimum number of cuts is: " << bestMinCut << endl;;

	getchar();
	return 0;
}