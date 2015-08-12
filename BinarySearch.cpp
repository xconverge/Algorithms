// Basic Binary search that searches a sorted array for a number

#include "stdafx.h"
#include <iostream>

#define arrayLength (10)
int a[arrayLength] = { 5, 7, 8, 9, 10, 11, 12, 13, 14, 15 };

using namespace std;

//Recursive function that splits array in half and searches for num
int BinarySearch(int *a, int high, int low, int num)
{
	int idx;
	
	//If the array is too small with no result found return -1
	if (high < low)
		idx = -1;
	else
	{
		// Calculate new middle to split the array  around
		int mid = (high + low) / 2;

		//If num is found as the middle, return the index
		if (a[mid] == num)
			idx = mid;
		else
		{
			if (num < a[mid])
			{
				//If num is on the left, recursively search that portion
				idx = BinarySearch(a, mid - 1, low, num);
			}
			else
			{
				//If num is on the right, recursively search that portion
				idx = BinarySearch(a, high, mid + 1, num);
			}
		}
	}
	//Return the index where num was found (-1 if was not found)
	return idx;
}

int _tmain(int argc, _TCHAR* argv[])
{
	// Print entire array
	for (int i = 0; i < 10; i++)
	{
		printf("%d: %d \n",i,a[i]);
	}

	int size = arrayLength;
	int num;
	printf("Enter number to search for: ");
	cin >> num;

	//Perform recursive search for index where num is on a sorted array
	int idx = BinarySearch(a, size, 0, num);

	printf("\n%d is at index: %d", num, idx);

	return 0;
}

