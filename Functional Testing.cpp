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

unsigned long long int BruteForceMedian(vector<int> &);
unsigned long long int Median(vector<int> &);
int Select(vector<int> &, int, int, int);
int Partition(vector<int> &, int, int);
bool TestBruteMedian(vector<int> &, int);
bool TestSelectMedian(vector<int> &, int);
void TestRandom();
void TestSorted();
void TestReverseSorted();
void TestSameNumber();
int MAX_ARRAY_SIZE = 100;
int VARIANCE = 1000;
int NUM_TESTS = 100;


int main()
{
	srand(time(NULL));
	for (int i = 0; i < NUM_TESTS; i++) {
		TestRandom();
		TestSorted();
		TestReverseSorted();
		TestSameNumber();
		cout << endl;
	}

	cout << "ALL TESTS PASSED!" << endl;
	system("PAUSE");
	return 0;
}

void TestSameNumber()
{
	cout << "Testing same number array." << endl;
	int resultBruteForceMedian, resultMedian;
	vector<int> A;

	int x = rand() % 100;

	//Insert random numbers into the array
	for (int j = 0; j < 2 + rand() % MAX_ARRAY_SIZE; j++)
	{
		A.push_back(x);
	}

	resultBruteForceMedian = BruteForceMedian(A);
	resultMedian = Median(A);

	assert(TestBruteMedian(A, resultBruteForceMedian));
	assert(TestSelectMedian(A, resultMedian));

	cout << "Same number array test passed." << endl;
}

void TestReverseSorted()
{
	cout << "Testing reverse sorted array." << endl;
	int resultBruteForceMedian, resultMedian;
	vector<int> A;

	//Insert random numbers into the array
	for (int j = 0; j < 2 + rand() % MAX_ARRAY_SIZE; j++)
	{
		A.push_back(rand() % VARIANCE);
	}

	sort(A.rbegin(), A.rend());

	resultBruteForceMedian = BruteForceMedian(A);
	resultMedian = Median(A);

	assert(TestBruteMedian(A, resultBruteForceMedian));
	assert(TestSelectMedian(A, resultMedian));

	cout << "Reverse sorted array test passed." << endl;
}

void TestSorted()
{
	cout << "Testing sorted array." << endl;
	int resultBruteForceMedian, resultMedian;
	vector<int> A;

	//Insert random numbers into the array
	for (int j = 0; j < 2 + rand() % MAX_ARRAY_SIZE; j++)
	{
		A.push_back(rand() % VARIANCE);
	}

	sort(A.begin(), A.end());

	//Returns total number of basic operation
	resultBruteForceMedian = BruteForceMedian(A);
	resultMedian = Median(A);

	assert(TestBruteMedian(A, resultBruteForceMedian));
	assert(TestSelectMedian(A, resultMedian));

	cout << "Sorted array test passed." << endl;
}

void TestRandom()
{
	cout << "Testing random array." << endl;
	int resultBruteForceMedian, resultMedian;
	vector<int> A;

	//Insert random numbers into the array
	for (int j = 0; j < 2 + rand() % MAX_ARRAY_SIZE; j++)
	{
		A.push_back(rand() % VARIANCE);
	}

	//Returns total number of basic operation
	resultBruteForceMedian = BruteForceMedian(A);
	//Returns total number of basic operation
	resultMedian = Median(A);

	assert(TestBruteMedian(A, resultBruteForceMedian));
	assert(TestSelectMedian(A, resultMedian));

	cout << "Random array test passed." << endl;
}

unsigned long long int BruteForceMedian(vector<int> &A)
{
	int k;
	int numsmaller;
	int numequals;

	k = ceil(A.size() / 2.0);

	//Loop through the array
	for (int i = 0; i <= A.size() - 1; i++)
	{
		numsmaller = 0;
		numequals = 0;

		//Inner Loop through the array
		for (int j = 0; j <= A.size() - 1; j++)
		{

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
			return A[i];
		}
	}
}

unsigned long long Median(vector<int> &A)
{
	if (A.size() == 1)
		return A[0];
	else
		return Select(A, 0, floor(A.size() / 2), A.size() - 1); // NB: The third argument is rounded down
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

		if (A[j] < pivotval)
		{
			pivotloc++; //Increment pivot location

			swap(A[pivotloc], A[j]); // Swap elements around pivot
		}
	}
	swap(A[l], A[pivotloc]); // Put pivot element in place

	return pivotloc;
}

bool TestBruteMedian(vector<int> &A, int m)
{
	sort(A.begin(), A.end());
	return (A[(ceil(A.size() / 2.0)-1)] == m);
}

bool TestSelectMedian(vector<int> &A, int m)
{
	sort(A.begin(), A.end());
	return (A[(ceil(A.size() / 2))] == m);
}
