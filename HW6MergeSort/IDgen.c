// generate the IDs by random numbers
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char * * argv)
{
  // argv[1]: number of students
  if (argc < 1)
    {
      return EXIT_FAILURE;
    }
  int numstu = (int) strtol(argv[1], NULL, 10);
  int ID = rand() % 1000;
  printf("%d\n", ID);
  for (int ind = 1; ind < numstu; ind ++)
    {
      ID += rand() % 1000 + 2;
      printf("%d\n", ID);
    }
  return EXIT_SUCCESS;
}
