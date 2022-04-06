#include "sort.h"

void ssort(int * arr, int size) {
	//if(0){
	int i, j, max_idx;
	for (i = 0; i < size-1; i++)
	{
		max_idx = i;
		for (j = i+1; j < size; j++)
			if (arr[j] > arr[max_idx])
				max_idx = j;
 
		//swap
		//if you forgot to assign integer pointers, assign the address
		//swap_1
		int* x_p = &arr[i];
		int* y_p = &arr[max_idx];
		int temp = *y_p;
		*y_p = *x_p;
		*x_p = temp;
		//swap_2	
		/*
		int temp = arr[i];
		arr[i] = arr[min_idx];
		arr[min_idx] = temp;
		*/    
	}
	//}

	//if we use same variables it gives the error of redeclaration of same variables without linkage
	#ifdef ASCENDING
	int k, l, min_idx;
	for (k = 0; k < size-1; k++)
	{
		min_idx = k;
		for (l = k+1; l < size; l++)
			if (arr[l] < arr[min_idx])
				min_idx = l;
 

		int temp = arr[k];
		arr[k] = arr[min_idx];
		arr[min_idx] = temp;   
	}


	#endif
}
