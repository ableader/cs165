//============================================================================
// Name        : project1.cpp
// Course      : CS165 Project in Algorithms
// Authors     : Gregory Jeckell, Andrew Leader
// Description : Finds the indices of array elements that have the k
//               largest values, in descending value order, from an
//               array of n elements. Outputs metrics on algorithm.
//============================================================================

#include <iostream>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <iomanip>
#include "COMPARE.c"
using namespace std;

int doalg(int n, int k);
template <typename T>
vector<T> quickSort(vector<T>& v);
template <typename T>
vector<T> concatenate(const vector<T>& greater, int pivot, const vector<T>& less);
template <typename T>
vector<T> mergeSort(vector<T>& v);
template <typename T>
vector<T> merge(vector<T>& left, vector<T>& right);
template <typename T>
int quickSelect(vector<T>& list, int left, int right, int n);
template <typename T>
int partition(vector<T>& list, int left, int right, int pivotIndex);

int main() {
	int n[] = { 15, 100, 1000, 10000 };
	int k[] = { 3, 10, 20, 40 };
	int testRuns = 1000;

	cout.setf(ios::fixed,ios::floatfield);
	cout.precision(3);
	cout << "---------------------------------------------------" << endl;
	cout << setw(8) << "n" << setw(5) << "k" << setw(10) << "Min." << setw(10) << "Max"
			<< setw(15) << "Avg." << endl;
	cout << "---------------------------------------------------" << endl;

	for (int i=0; i < 4; ++i) {
		int worstCase = 0;
		int bestCase = 0;
		double sum = 0;

		for (int j=0; j < testRuns; ++j) {
			int c = doalg(n[i], k[i]);
			if (c > worstCase) {
				worstCase = c;
			}
			if (bestCase == 0 || c < bestCase) {
				bestCase = c;
			}
			sum += c;
		}

		cout << setw(8) << n[i] << setw(5) << k[i] << setw(10) << bestCase
				<< setw(10) << worstCase << setw(15) << (double)sum / testRuns << endl;
	}

	return 0;
}

int doalg(int n, int k)
{
	COMPARE(0, n);

	vector<int> indexArray;
	for (int i=0; i < n; ++i) {
		indexArray.push_back(i+1);
	}

	int found = quickSelect(indexArray, 0, indexArray.size()-1, n-k);

	vector<int> partialSort;
	for (unsigned int i=found; i < indexArray.size(); ++i) {
		partialSort.push_back(indexArray[i]);
	}

	vector<int> result = mergeSort(partialSort);
	int* best = new int[k+1];
	for (int i=1; i <= k; ++i) {
		best[i] = result[i-1];
	}

	int comparisons = COMPARE(-1, k, best);
	return comparisons;
}

template <typename T>
vector<T> quickSort(vector<T>& v)
{
	if (v.size() <= 1) { return v; }
	int pivot = (rand() % (int)v.size());
	vector<T> less;
	vector<T> greater;

	// swap
	T tmp = v[pivot];
	v[pivot] = v[0];
	v[0] = tmp;

	for (unsigned int i=1; i < v.size(); ++i) {
		if (COMPARE(v[i], v[0]) == 1) {
			greater.push_back(v[i]);
		} else {
			less.push_back(v[i]);
		}
	}

	return concatenate(quickSort(greater), v[0], quickSort(less));
}

template <typename T>
vector<T> concatenate(const vector<T>& greater, int pivot, const vector<T>& less)
{
	vector<int> v;
	for (unsigned int i=0; i < greater.size(); ++i) {
		v.push_back(greater[i]);
	}
	v.push_back(pivot);
	for (unsigned int i=0; i < less.size(); ++i) {
		v.push_back(less[i]);
	}
	return v;
}

template <typename T>
vector<T> mergeSort(vector<T>& v)
{
	if (v.size() <= 1) return v;

	typename vector<T>::iterator middle = v.begin() + (v.size() / 2);
	vector<T> left(v.begin(), middle);
	vector<T> right(middle, v.end());

	left = mergeSort(left);
	right = mergeSort(right);
	return merge(left, right);
}

template <typename T>
vector<T> merge(vector<T>& left, vector<T>& right)
{
	vector<T> result;
	unsigned int i = 0, j = 0;

	while (i < left.size() && j < right.size()) {
		if (COMPARE(left[i], right[j]) == 1) {
			result.push_back(left[i++]);
		}
		else {
			result.push_back(right[j++]);
		}
	}

	while (i < left.size()) {
		result.push_back(left[i++]);
	}

	while (j < right.size()) {
		result.push_back(right[j++]);
	}

	return result;
}

template <typename T>
int quickSelect(vector<T>& list, int left, int right, int n)
{
	if (left == right)
		return left;
	int pivotIndex = left + (rand() % (int)(right - left + 1));
	pivotIndex = partition(list, left, right, pivotIndex);

	if (pivotIndex == n)
		return n;
	else if (n < pivotIndex)
		return quickSelect(list, left, pivotIndex-1, n);
	else
		return quickSelect(list, pivotIndex+1, right, n);
}

template <typename T>
int partition(vector<T>& list, int left, int right, int pivotIndex)
{
	T pivotValue = list[pivotIndex];

	// swap
	T tmp = list[right];
	list[right] = list[pivotIndex];
	list[pivotIndex] = tmp;

	int storeIndex = left;
	for (int i=left; i < right; ++i) {
		if (COMPARE(list[i], pivotValue) == 2) {
			T tmp = list[i];
			list[i] = list[storeIndex];
			list[storeIndex++] = tmp;
		}
	}

	tmp = list[storeIndex];
	list[storeIndex] = list[right];
	list[right] = tmp;

	return storeIndex;
}

