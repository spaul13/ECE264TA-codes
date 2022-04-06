// main.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "list.h"
#include "tree.h"
int main(int argc, char ** argv)
{
  if (argc < 2)
    {
      return EXIT_FAILURE;
    }
  FILE * fptr = fopen(argv[1], "r");
  if (fptr == NULL)
    {
      return EXIT_FAILURE;
    }
  fseek(fptr, 0, SEEK_END);
  long filelen = ftell(fptr);
  unsigned char * buf = malloc(sizeof(unsigned char) * (int) filelen);
  fseek(fptr, 0, SEEK_SET);
  if (fread(buf, sizeof(unsigned char), filelen, fptr) != filelen)
    {
      printf("ERROR\n");
    }
  // printf("filelen = %ld\n", filelen);
  bool finished = false;
  ListNode * listhead = NULL;
  ListNode * listtail = NULL;
  int numone = 0;
  int numzero = 0;
  int ind = 0;
  while (finished == false)
    {
      if (buf[ind] == '1')
	{
	  ind ++;
	  List_insert(& listhead, & listtail, buf[ind]);
	  ind ++;
	  numone ++;
	}
      else
	{
	  List_merge(& listhead, & listtail);
	  ind ++;
	  numzero ++;
	}
      if (numone == numzero)
	{
	  finished = true;
	}
    }
  if (listtail != listhead)
    {
      printf("ERROR\n");
    }
  Tree_printCode(listhead -> tnptr, buf, 0);
  List_destroy(listhead);
  fclose(fptr);
  free (buf);
  return EXIT_SUCCESS;
}
