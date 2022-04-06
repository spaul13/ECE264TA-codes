// ***
// *** You MUST modify this file
// ***

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h> 
#include <string.h> 

#ifdef TEST_ELIMINATE
// 100% of the score
void eliminate(int n, int k)
{
  // allocate an arry of n elements
  int * arr = malloc(sizeof(* arr) * n);
  // check whether memory allocation succeeds.
  // if allocation fails, stop
  if (arr == NULL)
    {
      fprintf(stderr, "malloc fail\n");
      return;
    }
	
  // Note that from here on, you can access elements of the arr with
  // expressions like a[i]

  int * mark = malloc(sizeof(* mark) * n);
  // initialize all elements
  for(int i=0;i<n;i++)
  {
	arr[i] = i;
	mark[i] = 0;//nothing is marked
  }

  

  //extra counters needed
  int left = n; //remaning persons in the list, and left-=1 when one element is marked
  int count = 0;
  

   while(left>1){
	for(int i=0;i<n;i++)
	{
				
		if(mark[i]==0){
			count+=1;
			// counting to k
			// mark the eliminated element
  			// print the index of the marked element 	
			if(count%k == 0)
			{
				left-=1;
				mark[i] = 1;
				fprintf(stdout, "%d\n", i);
				count=0;
			}
		}
			
	}
	//count=0;//reset the counter
   }


  
  for(int i=0; i<n; i++)
  {
	if(mark[i]==0)
		fprintf(stdout, "%d\n", i);
  }
  // mark the eliminated element
  // print the index of the marked element
  // repeat until only one element is unmarked




  // print the last one
  




  // release the memory of the array
  free (arr);
}
#endif
