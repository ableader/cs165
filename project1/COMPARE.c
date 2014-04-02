#include <stdio.h>
#define COMPARELIMIT 10000
double dshrandom( long );

#include <stdarg.h>
int COMPARE(int arg1, int arg2, ...) {
/*  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  */
/*	Comparisons to determine the biggest "k" array elements	*/
/*	COMPARE( 0,n ) initializes a random array of length n	*/
/*				all distinct values		*/
/*		returns  0 normally				*/
/*		returns -1 if n is out of range			*/
/*	COMPARE( x,y ) compares values of array[x] and array[y]	*/
/*		returns  1 if array[x] > array[y]		*/
/*		returns  2 if array[y] > array[x]		*/
/*		returns -1 if x or y is out of range		*/
/*	COMPARE( -1,k,best[] ) checks whether best[] contains	*/
/*			the indices of the biggest "k" in array	*/
/*		returns the number of comparisons performed	*/
/*			when the biggest "k" indices are okay	*/
/*		returns -1 if "k" is out of range		*/
/*		returns -1000 if any of the indices are wrong	*/
/*  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  */
	va_list ap;
	static int number[COMPARELIMIT+1];
	static int comp, size=0;
	int *best;
	int i,j,t;

	if (arg1==0) {
		if (arg2<3 || arg2>COMPARELIMIT) {
			printf("******* ERROR: COMPARE(0,size) -- 'size' out of range ********** size=%d\n",size);
			return(-1);
		}
		for (i=1; i<=arg2; i++) number[i] = i;
		for (i=arg2; i>=1; i--){
			j = i*dshrandom(0) + 1;
			if (j!=i) {
				t = number[i];
				number[i] = number[j];
				number[j] = t;
			}
		}
		comp = 0;
		size = arg2;
		return(0);
	}
	if (arg1==-1) {
		if (arg2<1 || arg2>size) {
			printf("******* ERROR: COMPARE(-1,k,best[]) -- 'k' out of range ********** k=%d\n",arg2);
			return(-1);
		}
		va_start(ap, arg2);
		best = va_arg(ap, int*);
		va_end(ap);
		for (i=1; i<=arg2; i++) {
			if ( best[i]<1 || best[i]>size
			   || number[ best[i] ] != size+1-i ) {
				printf("******* ERROR: COMPARE(-1,k,best[]) -- best[%d] = %d",i,best[i]);
				if ( best[i]<1 || best[i]>size )
					printf(" out of range **********\n");
				else	printf(" bad value **********\n");
/*
 *				printf("array= ");
 *				t = size;  if (t>100) t = 100;
 *				for (j=1; j<=t; j++) printf(" %2d",number[j]);
 *				printf("\nbest= ");
 *				t = arg2;  if (t>100) t = 100;
 *				for (j=1; j<=t; j++) printf(" %2d",best[j]);
 */
				return(-1000);
			}
		}
		return(comp);
	}
	if (arg1<1 || arg2<1 || arg1>size || arg2>size) return(-1);
	comp++;
	if (number[arg1]>number[arg2])
		return(1);
	else	return(2);
}
double dshrandom( long input ) {
/*  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  */
/*	Random Number Generator					*/
/*		first called with seed				*/
/*		thereafter called with 0			*/
/*	Based on code appearing in				*/
/*	"Random number generators: good ones are hard to find"	*/
/*		by Stephen Park and Keith Miller		*/
/*		CACM 31 (Oct 1988) 1192-1201.			*/
/*  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  */
	static long seed = 3125;
	static long a = 16807;
	static long m = 2147483647;
	static long q = 127773;      /* m div a */
	static long r = 2836;        /* m mod a */
	long lo, hi, test;

	if (input>0) seed = input;
	hi = seed/q;
	lo = seed - (hi*q);
	test = a*lo - r*hi;
	if (test>0) seed = test;
	else        seed = test+m;
				/* seed equally in range 0...2^31 -1  */
	return( ((double)seed)/(double)m );
}
