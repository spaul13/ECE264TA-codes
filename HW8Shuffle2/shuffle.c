#include "shuffle.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

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


#ifdef TEST_DIVIDE
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

#ifdef TEST_INTERLEAVE
void interleaveHelper(CardDeck leftDeck, CardDeck rightDeck,
		      CardDeck newDeck,
		      int leftind, int rightind, int newind,
		      int round)
{
  int ind;
  if (leftind == -1) // no more card
    {
      for (ind = 0; ind <= rightind; ind ++)
	{
	  newDeck.cards[ind] = rightDeck.cards[ind];
	}
      shuffle(newDeck, round - 1);
      return; 
    }
  if (rightind == -1) // no more card
    {
      for (ind = 0; ind <= leftind; ind ++)
	{
	  newDeck.cards[ind] = leftDeck.cards[ind];
	}
      shuffle(newDeck, round - 1);
      return; 
    }

  newDeck.cards[newind] = leftDeck.cards[leftind];
  interleaveHelper(leftDeck, rightDeck, newDeck,
		   leftind - 1, rightind, newind - 1,
		   round);
  newDeck.cards[newind] = rightDeck.cards[rightind];
  interleaveHelper(leftDeck, rightDeck, newDeck,
		   leftind, rightind - 1, newind - 1,
		   round);
}

void interleave(CardDeck leftDeck, CardDeck rightDeck, int round)
{
  CardDeck newDeck;
  newDeck.size = leftDeck.size + rightDeck.size;
  interleaveHelper(leftDeck, rightDeck, newDeck,
		   leftDeck.size - 1, rightDeck.size - 1,
		   newDeck.size - 1, round);
}
#endif

#ifdef TEST_SHUFFLE
void shuffle(CardDeck origDeck, int round)
{
  if (round == 0)
    {
      printDeck(origDeck);
      return;
    }
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
      interleave(leftDeck[ind], rightDeck[ind], round);
    }
  free (leftDeck);
  free (rightDeck);
  
}
#endif
