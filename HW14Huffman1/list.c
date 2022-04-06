// list.c
#include "list.h"
#include "tree.h"
#include <stdlib.h>
ListNode * ListNode_create(unsigned char letter)
{
  ListNode * ln = malloc(sizeof(ListNode));
  TreeNode * tn = TreeNode_create(letter);
  ln -> next = NULL;
  ln -> prev = NULL;
  ln -> tnptr = tn;
  return ln;
}
void  List_insert(ListNode * * head, ListNode * * tail,
		  unsigned char letter)
{
  // printf("insert %c\n", letter);
  ListNode * ln = ListNode_create(letter);
  if ((* head) == NULL)
    {
      * head = ln;
      * tail = ln;
      return;
    }
  // no need for else
  (* tail) -> next = ln;
  ln -> prev = (* tail);
  * tail = ln;
}

void List_merge(ListNode * * head, ListNode * * tail)
{
  // printf("merge\n");
  if ((*head) == (*tail))
    {
      // nothing to merge
      return;
    }
  ListNode * last = (* tail);
  ListNode * secondlast = (* tail) -> prev;
  TreeNode * parent = Tree_merge(secondlast -> tnptr, last -> tnptr);
  secondlast -> tnptr = parent;
  secondlast -> next = NULL;
  free (* tail);
  * tail = secondlast;
}

void List_destroy(ListNode * head)
{
  // should have only one node
  if ((head -> next) != NULL)
    {
      printf("ERROR\n");
      return;
    }
  if ((head -> prev) != NULL)
    {
      printf("ERROR\n");
      return;
    }
  Tree_destroy(head -> tnptr);
  free (head);
}
