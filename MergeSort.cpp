// Test for number of inversions in an input file (value at index = i is greater than value at index > i)

#include "stdafx.h"
#include <iostream>
#include <fstream>

using namespace std;

// Number of inversions counter
double numInversions = 0;

//Size of input file desired (mostly used for debug to test on smaller subsets)
#define SIZE (100000)

void Merge(int a[], const int low, const int high, int mid)
{		
	//Clone the array for processing the left and right sides in place before copying back to a[]
	int * tmp = new int[high + 1 - low];

	//Index for filling the main array
	int idx = 0;

	//Index for "left" side
	int i = low;
	//Index for "right" side
	int j = mid + 1;

	//While both sides still have elements, compare values to merge into temp array
	while ((i <= mid) && (j <= high))
	{
		if (a[i] <= a[j])
		{
			tmp[idx] = a[i];
			i++;
		}
		else
		{
			tmp[idx] = a[j];
			//If a left side value is added before a right side, then there are inversions related to the number of elements left
			numInversions +=  mid + 1 - i;
			j++;
		}
		idx++;
	}
	
	//Only the left side has elements left, fill the temp array with them
	while (i <= mid)
	{
		tmp[idx] = a[i];
		i++;
		idx++;
	}

	//Only the right side has elements left, fill the temp array with them
	while (j <= high)
	{
		tmp[idx] = a[j];
		j++;
		idx++;
	}

	//Copy the temp array back into a[] before returning to complete the in place merge
	for (int p = 0; p <= high-low; p++)
	{
		a[p + low] = tmp[p];
	}

	//Clear temporary memory
	delete[] tmp;
}

//Recursive function to sort elements
void merge_sort(int a[], int low, int high)
{
	int mid;
	int inv1 = 0, inv2 = 0, inv3 = 0;
	if (low < high)
	{
		mid = (low + high) / 2;
		merge_sort(a, low, mid);
		merge_sort(a, mid + 1, high);
		Merge(a, low, high, mid);
	}
}

//Brute force inversion counter for verification
void BruteForce(int a[])
{
	double bruteCnt = 0;
	for (int i = 0; i < SIZE - 1; i++)
	{
		for (int j = i + 1; j < SIZE; j++)
		{
			if (a[i] > a[j])
				bruteCnt++;
		}
	}
	printf("Brute Inversions: %.0f\n", bruteCnt);
}


int _tmain(int argc, _TCHAR* argv[])
{
	//Open file to process
	ifstream file("C:/Users/sean/Downloads/test.txt", ios::in);

	int a[SIZE];

	//Create array of elements from the file
	int num;
	for (int i = 0; i < SIZE; i++)
	{
		file >> num;
		a[i] = num;
	}
	file.close();

	//Brute force to get a test result
	BruteForce(a);

	//Merge sort the elements and count inversions
	merge_sort(a, 0, SIZE-1);

	printf("Merge Inversions: %.0f\n", numInversions);

	getchar();
	return 0;
}