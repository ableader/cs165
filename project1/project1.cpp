//============================================================================
// Name        : ics165-p1.cpp
// Author      : Gregory Jeckell, Andrew Leader
// Version     :
// Copyright   :
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include "COMPARE.c"
using namespace std;

int doalg(int n, int k);
vector<int> quickSort(vector<int>& v);
vector<int> concatenate(const vector<int>& less, int pivot, const vector<int>& greater);
vector<int> quickSelect(vector<int>& list, int left, int right, int n);
void partition(vector<int>& list, int left, int right, int pivotIndex);

int main() {
	int total = 0;
	int max = 1000;
	for (int i=0; i < max; ++i) {
		int c = doalg(15, 3);
		cout << "comparison = " << c << endl;
		total += c;
	}
	cout << "average = " << (double)total / max << endl;
	return 0;
}

int doalg(int n, int k)
{
	COMPARE(0, n);

	vector<int> indexArray;
	for (int i=0; i < n; ++i) {
		indexArray.push_back(i+1);
	}

	vector<int> result = quickSort(indexArray);
	int* best = new int[k+1];
	for (int i=1; i <= k; ++i) {
		best[i] = result[i-1];
	}

	for (int i=0; i < result.size(); ++i) {
		cout << result[i] << " ";
	} cout << endl;

	int comparisons = COMPARE(-1, k, best);
	return comparisons;
}


vector<int> quickSort(vector<int>& v)
{
	if (v.size() <= 1) { return v; }
	int pivot = v.size() / 2;
	vector<int> less;
	vector<int> greater;

	int tmp = v[pivot];
	v[pivot] = v[0];
	v[0] = tmp;

	for (int i=1; i < v.size(); ++i) {
		if (COMPARE(v[i], v[0]) == 1) {
			less.push_back(v[i]);
		} else {
			greater.push_back(v[i]);
		}
	}

	return concatenate(quickSort(less), v[0], quickSort(greater));
}

vector<int> concatenate(const vector<int>& less, int pivot, const vector<int>& greater)
{
	vector<int> v;
	for (int i=0; i < less.size(); ++i) {
		v.push_back(less[i]);
	}
	v.push_back(pivot);
	for (int i=0; i < greater.size(); ++i) {
		v.push_back(greater[i]);
	}
	return v;
}

vector<int> quickSelect(vector<int>& list, int left, int right, int n)
{

}

void partition(vector<int>& list, int left, int right, int pivotIndex)
{

}

/*
void quickSort(int* arr, int left, int right)
{
      int i = left, j = right;
      int tmp;
      int pivot = arr[(left + right) / 2];

      // partition
      while (i <= j) {
            while (arr[i] < pivot)
                  i++;
            while (arr[j] > pivot)
                  j--;
            if (i <= j) {
                  tmp = arr[i];
                  arr[i] = arr[j];
                  arr[j] = tmp;
                  i++;
                  j--;
            }
      }

      // recursion
      if (left < j)
            quickSort(arr, left, j);
      if (i < right)
            quickSort(arr, i, right);
}
*/
