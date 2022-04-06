#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
int main(int argc, char * * argv)
{
  // argv[1]: number of leaf nodes
  if (argc < 2)
    {
      return EXIT_FAILURE;
    }
  int numnode = (int) strtol(argv[1], NULL, 10);
  srand(time(NULL));
  if (numnode <= 0)
    {
      return EXIT_FAILURE;
    }
  unsigned char * output = malloc(sizeof(unsigned char) * 3 * numnode);
  int outputind = 0;
  int usedletter[256] = {0};
  int used = 0;
  while (used < numnode)
    {
      int letter = rand() % 256;
      // allow only letters
      int cond1 = ((letter >= 'A') && (letter <= 'Z'));
      int cond2 = ((letter >= 'a') && (letter <= 'z'));
      if (cond1 || cond2)
	{
	  if (usedletter[letter] == 0)
	    {
	      usedletter[letter] = 1;
	      used ++;
	    }
	}
    }
  int numone = 0;
  int numzero = 0;
  for (int ind = 0; ind < 256; ind ++)
    {
      if (usedletter[ind] == 1)
	{
	  // printf("using %c\n", ind);
	  if ((numone < (numzero + 2)) || ((rand() % 2) == 1))
	    {
	      output[outputind] = '1';
	      outputind ++;
	      output[outputind] = ind;
	      outputind ++;
	      numone ++;
	    }
	  else
	    {
	      output[outputind] = '0';
	      outputind ++;
	      numzero ++;
	    }
	}
    }
  while (numone > numzero) // finish the remaining zeros
    {
      output[outputind] = '0';
      outputind ++;
      numzero ++;
    }
  for (int ind = 0; ind < numnode * 3; ind ++)
    {
      printf("%c", output[ind]);
    }
  printf("\n");
  free (output);
  return EXIT_SUCCESS;
}
