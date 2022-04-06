#include <stdio.h>  
#include <stdlib.h> 
#include <string.h> 
#include <stdbool.h>

// input: arr is an array and its two parts
// arr[l..m] and arr[m+1..r] are already sorted
// l, m, r mean left, middle, and right respectively
//
// You can assume that l <= m <= r.
//
// output: arr is an array and all elements in arr[l..r] are sorted
// Do not worry about the elements in arr[0..l-1] or arr[r+1..]

void merge(int * arr, int l, int m, int r, int * mergecount)
{
  (* mergecount) ++;
  if ((l > m) || (m > r)) { return; } // one or both are empty
  int * temparr = malloc (sizeof (* temparr) * (r - l + 1));
  if (temparr == NULL) { return; } // malloc fail
   
  int ind1 = l;
  int ind2 = m + 1;
  int ind3 = 0;
  while ((ind1 <= m) && (ind2 <= r))
    {
      if (arr[ind1] < arr[ind2])
	{
	  temparr[ind3] = arr[ind1];
	  ind1 ++;
	}
      else
	{
	  temparr[ind3] = arr[ind2];
	  ind2 ++;
	}
      ind3 ++;
    }
  // copy the remaining elements
  while (ind1 <= m)
    {
       temparr[ind3] = arr[ind1];
       ind1 ++;
       ind3 ++;
    }
  while (ind2 <= r)
    {
       temparr[ind3] = arr[ind2];
       ind2 ++;
       ind3 ++;
    }

  // copy temparr to array
  ind3 = 0;
  for (ind1 = l; ind1 <= r; ind1 ++)
    {
      arr[ind1] = temparr[ind3];
      ind3 ++;
    }
  free (temparr); // release temporary memory
}

// merge sort has the following steps:
// 1. if the input array has one or no element, it is already sorted
// 2. break the input array into two arrays. Their sizes are the same,
//    or differ by one
// 3. send each array to the mergeSort function until the input array
//    is small enough (one or no element)
// 4. sort the two arrays 

void mergeSort(int * arr, int l, int r,
	       int * sortcount, int * mergecount) 
{
  (* sortcount) ++; 
  if (l > r)  { return; } // empty array, nothing to do
  if (l == r) { return; } // only one element, already sorted
  int m = (l + r)/2; 
  mergeSort(arr, l, m, sortcount, mergecount); 
  mergeSort(arr, m+1, r, sortcount, mergecount); 
  merge(arr, l, m, r, mergecount); 
} 

int main(int argc, char * * argv)
{
  int size;
  for (size = 2; size < 16; size *= 2)
    {
      int * arr = malloc(sizeof(int) * size);
      int ind;
      for (ind = 0; ind < size; ind ++) 
	{
	  arr[ind] = size - ind; // descending order
	}
      int sortcount = 0;  // how many times mergeSort is called
      int mergecount = 0; // how many times merge is called
      mergeSort(arr, 0, size - 1, & sortcount, & mergecount);
      printf("sortcount=%d, mergecount=%d\n", sortcount, mergecount);
      free (arr);
    }
  return EXIT_SUCCESS;
}
