// Median Maintainance algorithm

// The goal of this problem is to implement the "Median Maintenance" algorithm (covered in the Week 5 lecture on heap applications). 
// The text file contains a list of the integers from 1 to 10000 in unsorted order; you should treat this as a stream of numbers, arriving one by one. 
// Letting xi denote the ith number of the file, the kth median mk is defined as the median of the numbers x1,…,xk. 
// (So, if k is odd, then mk is ((k+1)/2)th smallest number among x1,…,xk; if k is even, then mk is the (k/2)th smallest number among x1,…,xk.)
// In the box below you should type the sum of these 10000 medians, modulo 10000 (i.e., only the last 4 digits). That is, you should compute (m1+m2+m3+?+m10000)mod10000.

#include "stdafx.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <functional>
#include <vector>

using namespace std;

int main() {

	//Open file to process
	ifstream file("C:/Users/sean/Downloads/Median.txt", ios::in);

	// Max heap for the smaller numbers
	vector<int> maxHeap; 
	// Min heap for the bigger numbers
	vector<int> minHeap;

	// Data structure to hold the medians
	vector<int> medians;

	// Count number of iterations since started to know even/odd
	int i = 0;

	// Keep running sum of medians for the final answer
	int medianSum = 0;

	string line;
	int data;
	while (getline(file, line)) {
		istringstream iss(line);
		iss >> data;

		// Base case, first data is median
		if (medians.size() == 0) {
			// Add it the the maxHeap
			maxHeap.push_back(data);

			// Since it is the first data, it is also the median
			medians.push_back(data);
			medianSum += medians.back();
			continue;
		}

		// Which heap should the data go in, is it greater than the maxHeap (small numbers) biggest data?
		if (data <= maxHeap[0]) {
			// Add the heap of smaller numbers
			maxHeap.push_back(data);
			push_heap(maxHeap.begin(), maxHeap.end());
		}
		else {
			// Add to heap of larger numbers
			minHeap.push_back(data);
			push_heap(minHeap.begin(), minHeap.end(), greater<int>());
		}

		// Rebalance the min heap and the max heap if necessary
		if (maxHeap.size() > minHeap.size() + 1) {
			//Move datas from the maxHeap to the minHeap to rebalance
			pop_heap(maxHeap.begin(), maxHeap.end());

			minHeap.push_back(maxHeap.back());
			push_heap(minHeap.begin(), minHeap.end(), greater<int>());

			maxHeap.pop_back();
		}
		else if (minHeap.size() > maxHeap.size() + 1) {
			//Move datas from the minHeap to the maxHeap to rebalance
			pop_heap(minHeap.begin(), minHeap.end(), greater<int>());

			maxHeap.push_back(minHeap.back());
			push_heap(maxHeap.begin(), maxHeap.end());

			minHeap.pop_back();
		}

		// Iteration counter to know if we have an even or odd number of datas
		i = medians.size() + 1;

		// If even, take median from the smaller numbers (maxHeap)
		if (i % 2 == 0) {
			medians.push_back(maxHeap[0]);
		}
		else {
			// If odd, take median from the larger numbers (minHeap)
			if (maxHeap.size() >= minHeap.size()) {
				medians.push_back(maxHeap[0]);
			}
			else {
				medians.push_back(minHeap[0]);
			}
		}

		// Add the calculated median from this iteration to the sum
		medianSum += medians.back();
	}
	file.close();

	// Output the sum % 10000 to get the last 4 digits
	cout << "Sum of medians % 10000: " << medianSum % 10000 << endl;
	getchar();

	return 1;
}