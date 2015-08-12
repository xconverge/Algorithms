// 2-Sum Algorithm

// The goal of this problem is to implement a variant of the 2-SUM algorithm (covered in the Week 6 lecture on hash table applications).
// The file contains 1 million integers, both positive and negative(there might be some repetitions!).This is your array of integers, with the ith row of the file specifying the ith entry of the array.
// Your task is to compute the number of target values t in the interval[-10000, 10000](inclusive) such that there are distinct numbers x, y in the input file that satisfy x + y = t. 
// (NOTE: ensuring distinctness requires a one - line addition to the algorithm from lecture.)

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

#define SIZE 1000000

int main()
{
	//Open file to process
	ifstream file("C:/Users/sean/Downloads/2sum.txt", ios::in);

	vector<double> a(SIZE);

	//Create array of elements from the file
	string tmp;
	for (int i = 0; i < SIZE; i++)
	{
		file >> tmp;
		a[i] = stod(tmp);
	}
	file.close();

	//Sort the array
	sort(a.begin(),a.end());

	// Create a map of the sums for calculating results at the end
	map<double, int> sums;

	// Initialize all sums as not found and add them to the map
	for (int i = (-10000); i <= 10000; i++) {
		sums[i] = 0;
	}
	// Create a map and populate with the keys from the input file
	map<double, int> vals;
	for (int i = 0; i < a.size(); i++) {
		vals[a[i]] = 1;
	}

	// For each value in the hash table, look for all possible values that can create a sum within -10000 and 10000
	typedef map<double, int>::iterator it_type;
	for (it_type bucketX = vals.begin(); bucketX != vals.end(); bucketX++) {
		
		//Only search for keys that would match the sum critera
		for (double i = (-10000 - bucketX->first); i <= (10000 - bucketX->first); i++) {

			//If key doesn't exist, skip and move on
			if (vals.find(i) == vals.end())
				continue;

			//Verify the criteria is met with the 2 keys and adjust the sums map accordingly
			if (abs(bucketX->first + i) <= 10000)
			{
				sums[bucketX->first + i] = 1;
			}
		}
	}
	
	double result = 0;
	// Compute how many values between -10000 and 10000 were accounted for by 2-Sums
	for (it_type iterator = sums.begin(); iterator != sums.end(); iterator++) {

		// If the sum is 1, then add it to the result count
		if (iterator->second == 1)
			result++;
	}

	// Print the number of distinct sums that are possible from the input file
	cout << "Number: " << result;
	
	getchar();

}

