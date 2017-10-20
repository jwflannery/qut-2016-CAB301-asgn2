//Functionality Random
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <time.h>
#include <windows.h>
#include <stdlib.h>     /* srand, rand */
#include <vector>
#include <algorithm>
using namespace std;

vector<vector<int>> CreateArrays(int);
unsigned long long int BruteForceMedian(vector<int> &, int);
unsigned long long int Median(vector<int> &, int);
int Select(vector<int> &, int, int, int);
int Partition(vector<int> &, int, int);

int TEST_STEP = 10;
int SET_SIZE = 100;
int VARIANCE = 10000;
int NUM_TESTS = 1000;

unsigned long long int basicCount;

int main()
{
	srand(time(NULL));

	ofstream out_data;
	out_data.open("../../outAvgBasics.txt");

	for (int i = 1; i <= NUM_TESTS; i++)
	{
		if (i % TEST_STEP == 0)
		{
			vector<vector<int>> tests = CreateArrays(i);

			int opCount = 0;
			for (int a = 0; a < SET_SIZE; a++)
			{
				opCount = BruteForceMedian(tests[a], i) + opCount;
			}
			cout << i << "\n";
			out_data << i << "; " << opCount / SET_SIZE << " ";

			opCount = 0;

			for (int a = 0; a < SET_SIZE; a++)
			{
				opCount = Median(tests[a], i) + opCount;
			}
			out_data << "; " << opCount / SET_SIZE << "\n";
		}
	}
	return 0;
}

//Create a number of randomly populated arrays of a given size.
vector<vector<int>> CreateArrays(int size)
{
	vector<vector<int>> tests;
	for (int i = 0; i < SET_SIZE; i++)
	{
		std::vector<int> testSet;
		for (int x = 0; x < size; x++)
		{
			testSet.push_back(rand() % VARIANCE);
		}
		tests.push_back(testSet);
	}
	return tests;
}

unsigned long long int BruteForceMedian(vector<int> &A, int n)
{
	unsigned long long int opCount = 0;
	//Kth element
	int k;
	//Number of elements smaller than A[i]
	int numsmaller;
	//Number of elements equal to A[i]
	int numequals;

	//Returns the median value of array, Kth element (n/2) when array was sorted
	k = ceil(n / 2.0);

	for (int i = 0; i <= n - 1; i++)
	{
		numsmaller = 0;
		numequals = 0;

		for (int j = 0; j <= n - 1; j++)
		{
			opCount++;

			if (A[j] < A[i])
			{
				numsmaller++;
			}
			else if (A[j] == A[i])
			{
				numequals++;
			}
		}
		if (numsmaller < k && k <= (numsmaller + numequals))
		{
			//Return the Kth element of the array
			return opCount;
		}
	}
}

unsigned long long Median(vector<int> &A, int n)
{
	//Basic operation count set to zero
	basicCount = 0;
	// Returns the median value of array A of n numbers.
	if (n == 1)
		return basicCount;
	else
	{
		Select(A, 0, floor(n / 2), n - 1); // NB: The third argument is rounded down
		return basicCount;
	}
}

int Select(vector<int> &A, int l, int m, int h)
{
	// Returns the value at index m in array slice A[l..h], if the slice were sorted into nondecreasing order.
	int pos = Partition(A, l, h);

	if (pos == m)return A[pos];
	if (pos > m)return Select(A, l, m, pos - 1);
	if (pos < m)return Select(A, pos + 1, m, h);
}

int Partition(vector<int> &A, int l, int h)
{
	// Partitions array slice A[l..h] by moving element A[l] to the position
	// it would have if the array slice was sorted, and by moving all
	// values in the slice smaller than A[l] to earlier positions, and all values
	// larger than or equal to A[l] to later positions. Returns the index at which
	// the ¡®pivot¡¯ element formerly at location A[l] is placed.

	int pivotval = A[l]; // Choose first value in slice as pivot value
	int	pivotloc = l; // Location to insert pivot value
	for (int j = l + 1; j <= h; j++)
	{
		basicCount++;
		if (A[j] < pivotval)
		{
			pivotloc++; //Increment pivot location

			swap(A[pivotloc], A[j]); // Swap elements around pivot
		}
	}
	swap(A[l], A[pivotloc]); // Put pivot element in place

	return pivotloc;
}
