// main.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "list.h"
#include "tree.h"

TreeNode * readTree(char * filename, int * length)
// length: over estimate of the code length
{
  FILE * fptr = fopen(filename, "r");
  if (fptr == NULL)
    {
      return NULL;
    }
  fseek(fptr, 0, SEEK_END);
  long filelen = ftell(fptr);
  * length = (int) filelen; 
  unsigned char * buf = malloc(sizeof(unsigned char) * (int) filelen);
  fseek(fptr, 0, SEEK_SET);
  if (fread(buf, sizeof(unsigned char), filelen, fptr) != filelen)
    {
      printf("ERROR: fread fail\n");
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
      printf("ERROR: listtail != listhead\n");
    }
  TreeNode * root = listhead -> tnptr;
  free (listhead);
  fclose(fptr);
  free (buf);
  return root;
}

int writeBit(FILE * fptr, unsigned char bit, 
	     unsigned char * whichbit, 
	     unsigned char * curbyte)
{
  printf("writeBit: %d\n", bit);
  if ((* whichbit) == 0)
    {
      // reset
      * curbyte = 0;
    }
  // shift the bit to the correct location
  unsigned char temp = bit << (7 - (* whichbit));
  * curbyte |= temp; // store the data
  int value = 0;
  if ((* whichbit) == 7)
    {
      int ret;
      ret = fwrite(curbyte, sizeof(unsigned char), 1, fptr);
      // printByte(* curbyte); // for debugging
      if (ret == 1)
	{
	  value = 1;
	}
      else
	{
	  value = -1;
	}
    }
  * whichbit = ((* whichbit) + 1) % 8;
  return value;
}

int padZero(FILE * fptr, unsigned char * whichbit, 
	    unsigned char * curbyte)
{
  int rtv;
  while ((* whichbit) != 0)
    {
      rtv = writeBit(fptr, 0, whichbit, curbyte);
      if (rtv == -1)
	{
	  return -1;
	}
    }
  return rtv;
}

void saveData(char * infile, char * outfile, int * * codebook)
{
  FILE * inptr = fopen(infile, "r");
  if (inptr == NULL)
    {
      return; 
    }
  FILE * outptr = fopen(outfile, "w");
  if (outptr == NULL)
    {
      return;
    }
  int ch;
  unsigned char whichbit = 0;
  unsigned char curbyte  = 0;
  while ((ch = fgetc(inptr)) != EOF)
    {
      if (codebook[ch][0] == -1)
	{
	  printf("ERROR: unknown character %c %d\n", ch, ch);
	}
      int col = 0;
      while (codebook[ch][col] != -1)
	{
	  writeBit(outptr, codebook[ch][col],
		   & whichbit, & curbyte);
	  col ++;
	}
    }
  padZero(outptr, & whichbit, & curbyte);
  fclose (inptr);
  fclose (outptr);
}

int main(int argc, char ** argv)
{
  if (argc < 4)
    {
      return EXIT_FAILURE;
    }
  int length = 0;
  TreeNode * root = readTree(argv[1], & length);
  if (root == NULL)
    {
      return EXIT_FAILURE;
    }
  int * * codebook;
  // codebook[row] stores the code of row, 0 <= row <= 255
  // if row does not show up, all elements are -1
  codebook = malloc(sizeof(int *) * 256);
  for (int row = 0; row < 256; row ++)
    {
      codebook[row] = malloc(sizeof(int) * length);
      for (int col = 0; col < length; col ++)
	{
	  codebook[row][col] = -1;
	}
    }
  unsigned char * buf = malloc(sizeof(unsigned char) * length);
  Tree_createCode(root, buf, 0, codebook);
  free (buf);

  saveData(argv[2], argv[3], codebook);
  
  for (int row = 0; row < 256; row ++)
    {
      if (codebook[row][0] != -1)
	{
	  int col = 0;
	  printf("%c:", row);
	  while (codebook[row][col] != -1)
	    {
	      printf("%d", codebook[row][col]);
	      col ++;
	    }
	  printf("\n");
	}
      free (codebook[row]);
    }
  Tree_destroy(root);
  return EXIT_SUCCESS;
}
