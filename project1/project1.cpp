//============================================================================
// Name        : ics165-p1.cpp
// Author      : Gregory Jeckell, Andrew Leader
// Version     :
// Copyright   :
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "COMPARE.c"
using namespace std;

void doalg(int n, int k);
void quickSort(int arr[], int left, int right);

int main() {
	doalg(15, 3);
	return 0;
}

void doalg(int n, int k)
{
	COMPARE(0, n);

	int* indexArray = new int[n];
	for (int i=0; i < n; ++i) {
		indexArray[i] = i+1;
	}

	quickSort(indexArray, indexArray[0], indexArray[n]);

	for (int i=0; i < n; ++i) {
		cout << indexArray[i] << " ";
	}
}


void quickSort(int arr[], int left, int right)
{
      int i = left, j = right;
      int tmp;
      int pivot = arr[(left + right) / 2];

      /* partition */
      cout << "comparing i=" << i << " j=" << j << endl;
      while (COMPARE(i, j) == 2) {
            while (COMPARE(arr[i], pivot) == 2)
                  i++;
            while (COMPARE(arr[j], pivot) == 1)
                  j--;
            if (COMPARE(i, j) == 2) {
                  tmp = arr[i];
                  arr[i] = arr[j];
                  arr[j] = tmp;
                  i++;
                  j--;
            }
      }

      /* recursion */
      if (COMPARE(left, j) == 2)
            quickSort(arr, left, j);
      if (COMPARE(i, right) == 2)
            quickSort(arr, i, right);
}

/*
void quickSort(int arr[], int left, int right)
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
