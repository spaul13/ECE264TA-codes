
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h> 
#include <string.h>
#include "hw10.h"

void printListNode(ListNode * head)
{
  ListNode * p = head;
  printf("printListNode: ");
  while (p != NULL)
    {
      printf("%7d ", p -> value);
      p = p -> next;
    }
  printf("\n");
}

#ifdef TEST_CREATELIST
// create a linked list storing values 0, 1, 2, ... valn - 1
// The first node (head) stores 0, the next node stores 1,
// ..., the last node stores valn - 1
// return the head of the linked listn
ListNode * createList(int valn)
{
  ListNode * head = NULL;
  ListNode * added = NULL;
  valn --; // first number is zero
  while (valn >= 0)
    {
      added = malloc(sizeof( * added));
      added -> value = valn;
      added -> next = head; // the new node is at the beginning
      head = added;
      valn --;
    }
  return head;
}
#endif

#ifdef TEST_ELIMINATE
// eliminate the nodes in the linked list
// starting from the head, move one node at a time and count to valk.
// eliminate that node, keep counting
//
// when reaching the end of the list, continue from the beginning of
// the list
//
// print the values of the nodes to be deleted
void eliminate(ListNode * head, int valk)
{
  ListNode * p = head;
  int count;
  p = head;
  while ((head -> next) != NULL)
    {
      count = valk;
      while (count > 0)
	{
	  if (p != NULL)
	    {
	      count --;
	    }
	  ListNode * q = p -> next;
	  if (count == 0)
	    {
#ifdef DEBUG
	      // this #ifdef ... #endif should be inside the condition
	      // *BEFORE* a node' value is printed and it is deleted
	      ListNode * todelete = p;
	      printListNode (todelete); 
#endif
	      printf("%d\n", p -> value);
	      head = deleteNode (head, p);
	    }
	  if (q != NULL)
	    {
	      p = q;
	    }
	  else
	    {
	      p = head;
	    }
	}
    }
  // print the last one
  printf("%d\n", head -> value);
  free (head);
}
#endif

#ifdef TEST_DELETENODE
// head points to the first node in the linked list
// todelete points  to the node to be deleted
//
// delete the node and return the head of the linked list
// release the memory of the deleted node
//
// should check several conditions:
// 1. If head is NULL, the list is empty and this function returns
//    NULL
// 2. If todelete is NULL, nothing can be deleted, return head
// 3. If todelete is not in the list, keep the list unchanged and
//    return head
// It is possible that todelete is the first node in the list (i.e.,
// the head). If this occurs, return the second node of the list.
ListNode * deleteNode(ListNode * head, ListNode * todelete)
{
  if (head == NULL) // nothing can be deleted
    {
      return NULL;
    }
  if (todelete == NULL) // nothing to be deleted
    {
      return head;
    }
  if (head == todelete) // delete the first node
    {
      ListNode * p = head -> next;
      free (head);
      return p;
    }
  // delete a node that is not the first
  ListNode * p = head; // the node before todelete
  while ((p != NULL) && ((p -> next) != todelete))
    // check p != NULL to protect the situation when
    // todelete is not in the list
    {
      p = p -> next;
    }
  if (p != NULL) // todelete in the list
    {
      p -> next = todelete -> next;
      free (todelete);
    }
  return head;
}
#endif

