#ifndef _MSORT_H
#define _MSORT_H

#include <stdlib.h>
#include "student.h"

/*
Merge sort function. Sorts an array base, with nel elements

INPUT:
base: the array to be sorted
nel: the number of elements in the array pointed to by base
compar: a function pointer to compare two elements in the base array

OUTPUT:
base now points to a sorted array
*/
void msort(Student * base, int nel, int (*compar)(const void *, const void *));

/*
Merge two sorted arrays together to produce a new sorted array

INPUT:
base1: the address of the beginning of sorted array 1
nel1: the number of elements in array 1
base2: the address of the beginning of sorted array 2
nel2: the number of elements in array 2
compar: a function pointer to compare two elements in the base array

OUTPUT:
return value: a pointer to a newly-allocated sorted array that is the merged version of the two input arrays
*/
Student * merge(Student * base1, int nel1, Student * base2, int nel2, int (*compar)(const void *, const void *));

/*
Copy contents of array from to array to
*/
void copy(Student * to, Student * from, int nel);

#endif
