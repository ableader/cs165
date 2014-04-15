//============================================================================
// Name        : ics165-p1.cpp
// Author      : Gregory Jeckell, Andrew Leader
// Version     :
// Copyright   :
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <sstream>
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
string vectorToString(const vector<T>& v);
template <typename T>
T quickSelect(vector<T>& list, int left, int right, int n);
template <typename T>
int partition(vector<T>& list, int left, int right, int pivotIndex);

int main() {
	int total = 0;
	int max = 10;
	for (int i=0; i < max; ++i) {
		int c = doalg(15, 3);
		//cout << "comparison = " << c << endl;
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

	cout << "indexArray = " << vectorToString(indexArray) << endl;



//	vector<int> result = quickSort(indexArray);
//	int* best = new int[k+1];
//	for (int i=1; i <= k; ++i) {
//		best[i] = result[i-1];
//	}
//
//	cout << "result = " << vectorToString(result) << endl;

	int comparisons = COMPARE(-1, k, best);
	return comparisons;
}


template <typename T>
vector<T> quickSort(vector<T>& v)
{
	if (v.size() <= 1) { return v; }
	int pivot = v.size() / 2;
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
	unsigned int left_it = 0, right_it = 0;

	while (left_it < left.size() && right_it < right.size()) {
		if (COMPARE(left[left_it], right[right_it]) == 1) {//(left[left_it] < right[right_it]) {
			result.push_back(left[left_it]);
			left_it++;
		}
		else {
			result.push_back(right[right_it]);
			right_it++;
		}
	}

	while (left_it < left.size()) {
		result.push_back(left[left_it]);
		left_it++;
	}

	while (right_it < right.size()) {
		result.push_back(right[right_it]);
		right_it++;
	}

	return result;
}

template <typename T>
string vectorToString(const vector<T>& v)
{
	stringstream ss;
	for (int i=0; i < v.size(); ++i) {
		ss << v[i] << " ";
	}
	return ss.str();
}


template <typename T>
T quickSelect(vector<T>& list, int left, int right, int n)
{
	if (left == right)
		return list[left];
	int pivotIndex = (right - left) / 2;
	pivotIndex = partition(list, left, right, pivotIndex);

	if (COMPARE(n, pivotIndex) == 1)
		return quickSelect(list, left, pivotIndex-1, n);
	else if (COMPARE(n, pivotIndex) == 2)
		return quickSelect(list, pivotIndex+1, right, n);
	else
		return list[n];
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
		if (COMPARE(list[i], pivotValue) == 1) {
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

