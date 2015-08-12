#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <time.h>

using namespace std;

// Input array size
#define SIZE (10000)
int numComparisons;

// Function used to swap elements in array (index b and c are swapped)
void Swap(int a[], int b, int c)
{
	//In place swap with temp variable
	int temp = a[b];
	a[b] = a[c];
	a[c] = temp;
}

// Partition function that will sort everything greater than the pivot element to the right and less than the pivot to the left
int Partition(int a[], int left, int right)
{
	// Find value of pivot element
	int pivot = a[left];
	// Create pivot element index
	int i = left + 1;

	//Iterate linearly through all elements and swap if necessary to sort around the pivot element
	for (int j = (left + 1); j <= right; j++)
	{
		if (a[j] < pivot)
		{
			Swap(a, j, i);
			i++;
		}
	}
	//Finally, swap the pivot element into the middle where the index currently is so that the array is correctly sorted
	Swap(a, left, i - 1);

	//Return pivot index of sorted array
	return (i - 1);
}

// Function used to choose pivot in multiple different ways
void ChoosePivot(int option, int a[], int left, int right)
{
	switch (option)
	{
		case 1:
		{
			//Use the first element of the array as the pivot, this is the default behavior so do nothing
			return;
		}
		case 2:
		{
			//Use the last element of the array as the pivot, therefore, swap the current bounds when calling sort
			Swap(a, left, right);
			return;
		}
		case 3:
		{
			//Use the median of 3 points, the first, middle and last element as the pivot. Swap the median value into place before performing the sort
			int l = a[left];
			int m = a[(left + right) / 2];
			int r = a[right];
			if ((l < m && m <= r) || (r <= m && m < l)) {
				Swap(a, left, (left + right) / 2);
			}
			else if ((m <= r && r < l) || (l < r && r <= m)) {
				Swap(a, left, right);
			}
			return;
		}
		case 4:
		{
			//Random selection of the pivot
			srand(time(NULL));
			int random = rand() % (right-left+1);
			Swap(a, left, random);
			return;
		}
	}
}

//Recursive function to perform the quick sort algorithm
void QuickSort(int a[], int left, int right)
{
	int p;

	// Only proceed if the array to sort contains more than 1 element (low index is less than the high index)
	if (left < right)
	{
		//Add the number of elements that will be compared in this recursive call for the comparison counter
		numComparisons = numComparisons + (right - left);

		// Function used to choose a variety of different pivot elements
		ChoosePivot(1, a, left, right);

		//Partition around the pivot element that was chosen
		p = Partition(a, left, right);

		//Recursively sort the low side of the array
		QuickSort(a, left, p - 1);

		//Recursively sort the high side of the array
		QuickSort(a, p + 1, right);
	}

}

// Main function reads input from file and runs quicksort
int _tmain(int argc, _TCHAR* argv[])
{
	ifstream file("C:/Users/sean/Downloads/test.txt", ios::in);

	int a[SIZE];
	int num;

	//Read file into array
	for (int j = 0; j < SIZE; j++)
	{
		file >> num;
		a[j] = num;
	}
	file.close();
	numComparisons = 0;
	//Perform Quicksort and count comparisons
	QuickSort(a, 0, SIZE - 1);

	printf("Quick Sort number of comparisons: %d\n", numComparisons);

	return 0;
}