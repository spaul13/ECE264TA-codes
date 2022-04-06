// Please edit this file as required.
// You may add more functions/variables/structures in this file (if needed).

#include "shuffle.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


#ifndef TEST_DIVIDE
// leftDeck and rightDeck are arrays of CardDeck
// This function creates pairs of left and right decks
// Each pair divides the original deck into two non-overlapping decks and
// together they form the original deck.
//
// You can think of the left deck held by the left hand taking some
// cards (at least one) from the top of the original deck.
//
// The right deck is held by the right hand taking some (at least one)
// cards from the bottom of the original deck.
void divide(CardDeck origDeck, CardDeck * leftDeck, CardDeck * rightDeck)
{
  int ind;
  int leftSize;
  int rightSize;
  for (ind = 0; ind < origDeck.size - 1; ind ++)
  {
    leftSize = ind + 1;
    rightSize = origDeck.size - 1 - ind;
    memcpy(leftDeck[ind].cards, origDeck.cards,
	   leftSize * sizeof(origDeck.cards[0]));
    memcpy(rightDeck[ind].cards, & origDeck.cards[ind + 1],
	   rightSize * sizeof(origDeck.cards[0]));
    leftDeck[ind].size = leftSize;
    rightDeck[ind].size = rightSize;
  }
}
#endif

#ifndef TEST_INTERLEAVE
// do not modify this function
static void printDeck(CardDeck deck)
{
  int ind;
  for (ind = 0; ind < deck.size; ind ++)
    {
      printf("%c ", deck.cards[ind]);
    }
  printf("\n");
}

void interleaveHelper(CardDeck leftDeck, CardDeck rightDeck,
		      CardDeck newDeck,
		      int leftind, int rightind, int newind)
{
  int ind;
  if (leftind == -1) // no more card
    {
      for (ind = 0; ind <= rightind; ind ++)
	{
	  newDeck.cards[ind] = rightDeck.cards[ind];
	}
      printDeck(newDeck);
      return; 
    }
  if (rightind == -1) // no more card
    {
      for (ind = 0; ind <= leftind; ind ++)
	{
	  newDeck.cards[ind] = leftDeck.cards[ind];
	}
      printDeck(newDeck);
      return; 
    }
  // two options: pick one from left deck or one from right deck
  // from left deck
  newDeck.cards[newind] = leftDeck.cards[leftind];
  interleaveHelper(leftDeck, rightDeck, newDeck,
		   leftind - 1, rightind, newind - 1);
  // must not use --

  // from right deck
  newDeck.cards[newind] = rightDeck.cards[rightind];
  interleaveHelper(leftDeck, rightDeck, newDeck,
		   leftind, rightind - 1, newind - 1);
}

// Interleave two decks to generate all possible results.
//
// If the leftDeck is {'A'} and the right deck is {'2', '3'}, this
// function prints
// A 2 3
// 2 A 3
// 2 3 A
//
// If the leftDeck is {'A', '2'} and the right deck is {'3', '4'}, this
// function prints 
// 3 4 A 2
// 3 A 4 2
// A 3 4 2 
// 3 A 2 4 
// A 3 2 4 
// A 2 3 4 
//
// Please notice the space does not matter because grading will use
// diff -w
//
// How to generate all possible interleaves?

// Understand that a card at a particular position can come from
// either left or right (two options). The following uses left for
// explanation but it is equally applicable to the right.
//
// After taking one card from the left deck, the left deck has one
// fewer card. Now, the problem is the same as the earlier problem
// (thus, this problem can be solved by using recursion), excecpt one
// left card has been taken. Again, the next card can come from left
// or right.
//
// This process continues until either the left deck or the right deck
// runs out of cards. The remaining cards are added to the result.
// 
// It is very likely that you want to create a "helper" function that
// can keep track of some more arguments.  If you create a helper
// function, please keep it inside #ifdef TEST_INTERLEAVE and #endif
// so that the function can be removed for grading other parts of the
// program.
void interleave(CardDeck leftDeck, CardDeck rightDeck)
{
  CardDeck newDeck;
  newDeck.size = leftDeck.size + rightDeck.size;
  interleaveHelper(leftDeck, rightDeck, newDeck,
		   leftDeck.size - 1, rightDeck.size - 1,
		   newDeck.size - 1);
}
#endif

#ifndef TEST_SHUFFLE
// The shuffle function has the following steps:

// 1. calculate the number of possible left and right decks. It is
// the number of cards - 1 because the left deck may have 1, 2,...,
// #cards - 1 cards.
//
// 2. allocate memory to store these possible pairs of left and right
// decks.
//
// 3. send each pair to the interleave function
//
// 4. release allocated memory
//
void shuffle(CardDeck origDeck)
{
  int numpairs = origDeck.size - 1;
  if (numpairs <= 0) // invalid inputs
    {
      return;
    }

  // allocate memory
  CardDeck * leftDeck;
  CardDeck * rightDeck;

  leftDeck = malloc(numpairs * sizeof(CardDeck));
  if (leftDeck == NULL)
    {
      return;
    }
  rightDeck = malloc(numpairs * sizeof(CardDeck));
  if (rightDeck == NULL)
    {
      free (leftDeck);
      return;
    }

  divide(origDeck, leftDeck, rightDeck);
  
  int ind;
  for (ind = 0; ind < numpairs; ind ++)
    {
      interleave(leftDeck[ind], rightDeck[ind]);
    }
  free (leftDeck);
  free (rightDeck);
  
}
#endif
