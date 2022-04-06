#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * * argv)
{
  if (argc != 2)
    {
      fprintf(stderr, "Need one input file\n");
      return EXIT_FAILURE;
    }
  FILE * fptr = fopen(argv[1], "r");
  if (fptr == NULL) // fopen fail
    {
      return EXIT_FAILURE;
    }
  int count = 0;
  // -------------------
  // treat the input as integers
  count = 0;
  fseek(fptr, 0, SEEK_SET); // return to the beginning of the file
  int ival;
  while (fscanf(fptr, "%d", & ival) == 1)
    {
      count ++; 
    }
  printf("The file has %d integers.\n", count); // <=== ANSWER A
  printf("The last read integer is %d.\n", ival); // <=== ANSWER B
  // -------------------
  // treat the input as float
  count = 0;
  fseek(fptr, 0, SEEK_SET); // return to the beginning of the file
  float fval;
  while (fscanf(fptr, "%f", & fval) == 1)
    {
      count ++; 
    }
  printf("The file has %d float.\n", count); // <=== ANSWER C
  printf("The last floating-point is %f.\n", fval); // <=== ANSWER D
  // -------------------
  // understand the sizes of different types
  // assume
  // sizeof(char)   is 1
  // sizeof(int)    is 4
  // sizeof(int*)   is 8
  // sizeof(double) is 8
  double darr[] = {2.64, 20.11, 0.9, 2.8};
  int sizediff = (int)sizeof(darr) - (int)sizeof(darr[0]);
  printf("%d\n", sizediff); // <=== ANSWER E
  return EXIT_SUCCESS;
}
