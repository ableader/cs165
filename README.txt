CS 165 Project01: Selection
-------------------------------------------------------------------------------

Gregory Jeckell
Andrew Leader 

SECTIONS:
-------------------------------------------------------------------------------
1. How to use the program:

terminal/command-line:
make -f Makefile
./project1


2. Data structures:

STL vectors are the most utilized containers in the program. No specialized 
structures have been created. The solution provided for the project uses the 
partial sorting characteristic of the quickSelect search algorithm in 
conjunction with a standard mergeSort.

3. Theoretical time analysis:

quickSelect: O(n) on average O(n^2) worst
mergeSort:   O(nlogn)

Our algorithm first uses quickSelect on the n-kth element in the random array, 
then performs mergeSort on the sublist from the index returned from 
quickSelect to the end of the array. 

Average ==> O(n + mlogm)
Worst   ==> O(n^2 + mlogm)

4. System time:

...

5. Space requirements:

random array      = O(n)
vector of indexes = O(n)
quickSelect       = in place
mergeSort         = O(m)

total             = O(n^2 * m)
