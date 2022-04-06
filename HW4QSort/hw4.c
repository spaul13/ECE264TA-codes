// ***
// *** You MUST modify this file.
// ***

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#ifdef TEST_COUNTINT
int countInt(char * filename)
{
  // count the number of integers in the file
  // Please notice that if a file contains
  // 124 378 -56
  // There are three integers: 124, 378, -56
  // DO NOT count individual character '1', '2', '4' ...
  //
  // If fopen fails, return -1

  // remember to fclose if fopen succeeds
  FILE * fptr = fopen(filename, "r");

  if (fptr == NULL)
  {
    fprintf(stderr, "countInt Error: Could not open file.\n");
    fclose(fptr);
    return -1;
  }

  int inc = 0;
  int count = 0;

  while (fscanf(fptr, "%d", &inc) == 1)
  {
    count++;
  }
  
  fclose(fptr);

  return count;
}
#endif

#ifdef TEST_READINT
bool readInt(char* filename, int * intArr, int size)
{
  // if fopen fails, return false
  // read integers from the file.
  // 
  //
  // if the number of integers is different from size (too
  // few or too many) return false
  // 
  // if everything is fine, fclose and return true

  // May have to use malloc for this function. Reads integers of the input file and assigns to the intArr.

  FILE * fptr2 = fopen(filename, "r");

  if (fptr2 == NULL)
  {
    fprintf(stderr, "readInt Error: Could not open file.\n");
    fclose(fptr2);
    return -1;
  }

  int inc = 0;
  int val;
  while (fscanf(fptr2, "%d", &val) == 1) 
  {
    if (inc == size) 
    {
      fclose(fptr2);
      return false;
    }
    
    intArr[inc++] = val;
  }

  if (inc != size) 
  {
    fclose(fptr2);
    return false;
  }

  fclose(fptr2);

  return true;
}
#endif

#ifdef TEST_COMPAREINT
int compareInt(const void *p1, const void *p2)
{
  // needed by qsort
  //
  // return an integer less than, equal to, or greater than zero if
  // the first argument is considered to be respectively less than,
  // equal to, or greater than the second.
  int a = *(const int *)p1;
  int b = *(const int *)p2;
  if (a < b)
  {
    return -1;
  }
  else if (a > b)
  {
    return 1;
  }

  return 0;
}
#endif

#ifdef TEST_WRITEINT
bool writeInt(char* filename, int * intArr, int size)
{
  // if fopen fails, return false
  // write integers to the file.
  // one integer per line
  // 
  // fclose and return true
  FILE * fptr3 = fopen(filename, "w");

  if (fptr3 == NULL)
  {
    fprintf(stderr, "writeInt Error: Could not open file.\n");
    fclose(fptr3);
    return false;
  }

  for (int rep = 0; rep < size; rep++)
  {
    fprintf(fptr3, "%d\n", intArr[rep]);
  }

  fclose(fptr3);

  return true;
}
#endif

