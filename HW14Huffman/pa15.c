#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"

void writeSortedAsciiCount(char *filename, ListNode *list)
{
   FILE *fp = fopen(filename, "w");

   if (fp == NULL) {
      fprintf(stderr, "can't open the output file\n.");
   }
   printList(list, fp);
}
  

/* take an array of ascii counts, enqueue into a list */

ListNode *enqueAsciiCount(long *asciiCount) 
{
   ListNode *list = NULL;
   int i;
   for (i = 0; i < ASCII_SIZE; i++) {
      if (asciiCount[i] > 0) {
         TreeNode *newTreeNode = buildTreeNode(i, NULL, NULL);
         if (newTreeNode == NULL) {
            fprintf(stderr, "in enqueAsciiCount.  cannot allocate memory to create new TreeNode.  Quit.\n");
            freeList(list);
            return NULL;
         }
         newTreeNode->count = asciiCount[i];
         ListNode *newListNode = addListNode(&list, newTreeNode, treeNodeCompare);
         if (newListNode == NULL) {
            fprintf(stderr, "in enqueAsciiCount.  cannot allocate memory to create new ListNode.  Quit.\n");
            freeHuffmanTree(newTreeNode);
            freeList(list);
            return NULL;
         }
      }
   }
   return list;
}

/* count the occurrences in a file */

long *countLetters(FILE *fp)
{
   long *asciiCount = (long *)malloc(sizeof(long)*ASCII_SIZE);
   if (asciiCount == NULL) {
      return NULL;
   }
   int ch;
   for (ch = 0; ch < ASCII_SIZE; ch++) {
      asciiCount[ch] = 0;
   }
   fseek(fp, 0, SEEK_SET);
   while ((ch = fgetc(fp)) != EOF) {
      asciiCount[ch] += 1;
   }
   return asciiCount;
}

/* print the huffman code */

void printHuffmanTree(char *filename, TreeNode *huffman)
{
   FILE *fp = fopen(filename, "w");

   if (fp == NULL) {
      fprintf(stderr, "can't open the output file\n");
   }
   huffmanPrint(huffman,fp);
}

void huffmanHeadingBitsHelper(FILE *fp, TreeNode *huffman, int *byte, int *count)
{
   if (huffman == NULL) {
      return;
   }
   const int BYTE_SIZE = 8;
   if (isLeafNode(huffman) == 1) {
      // find the position for the 1 bit
      int onePosition = BYTE_SIZE - 1 - *count;
      // get the one bit at the correct position
      int oneBit = 1 << onePosition;
      // include the one bit in *byte
      *byte = *byte | oneBit;
      // inclement *count
      *count += 1;
      // if *count == BYTE_SIZE put it in the fp
      // reset *byte and *count;
      if (*count == BYTE_SIZE) {
         fputc(*byte, fp);
         *byte = 0;
         *count = 0;
      } 
      // if *count == 0, put huffman->label in fp
      // else put part of huffman->label into *byte, put it in fp
      // update *byte with the remaining part of huffman->label
      if (*count == 0) {
         fputc(huffman->label, fp);
      } else {
         // number of more significant bits to be included in *byte
         *byte = *byte | (huffman->label >> *count);
         fputc(*byte, fp);
         // now update *byte to store the less significant bit of huffman->label
         // at the higher significant position of *byte
         // *count stays the same 
         int MS_count = BYTE_SIZE - *count;  
         *byte = (huffman->label & (0xFF >> MS_count)) << MS_count;        
      }
      return;
   }
   // since *byte was initialized with 0, we have to increment *count to store bit 0 for root node
   // inclement *count
   *count += 1;
   if (*count == BYTE_SIZE) {
      fputc(*byte, fp);
      *byte = 0;
      *count = 0;
   }
   huffmanHeadingBitsHelper(fp, huffman->left, byte, count);
   huffmanHeadingBitsHelper(fp, huffman->right, byte, count);
   // if *count == BYTE_SIZE put it in the fp
   // reset *byte and *count;

}


void huffmanHeadingBits(char *filename, TreeNode *huffman)
{
   FILE *fp = fopen(filename, "w");
   if (fp == NULL) {
      fprintf(stderr, "can't open the output file\n.");
   }
   int currentByte = 0;
   int currentCount = 0;
   huffmanHeadingBitsHelper(fp, huffman, &currentByte, &currentCount);
   if (currentCount == 0) {
      fputc(0, fp);
   } else {
      fputc(currentByte, fp);
   }
   fclose(fp);
}

int main(int argc, char **argv)
{
   if (argc != 5) {
    printf("Not enough arguments");
    return EXIT_FAILURE;
   }
   FILE * inFile = fopen(argv[1], "r");
   if (inFile == NULL) {
      fprintf(stderr, "can't open the input file.  Quit.\n");
      return EXIT_FAILURE;
   }

   /* read and count the occurrences of characters */
   long *asciiCount = countLetters(inFile);
   fclose(inFile);

   if (asciiCount == NULL) {
      fprintf(stderr, "cannot allocate memory to count the characters in input file.  Quit.\n");
      return EXIT_FAILURE;
   }

   /* enqueue the non-zero characters into list */
   ListNode *list = enqueAsciiCount(asciiCount);
   free(asciiCount);
  
   if (list == NULL) {
      fprintf(stderr, "cannot allocate memory to store the ascii in priority queue.  Quit.\n");
      return EXIT_FAILURE;
   }

   writeSortedAsciiCount(argv[2], list);

   /* build the huffman tree */
   TreeNode *huffman = buildHuffmanTree(list);
   if (huffman == NULL) {
      fprintf(stderr, "cannot allocate memory to store a huffman coding tree.  Quit.\n");
      return EXIT_FAILURE;
   }

   /* print the huffman code */
   printHuffmanTree(argv[3], huffman);
   huffmanHeadingBits(argv[4], huffman);
   freeHuffmanTree(huffman);

   return EXIT_SUCCESS;
}
