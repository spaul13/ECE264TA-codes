// list.h
#ifndef LIST_H
#define LIST_H
#include "tree.h"
#include <stdio.h>
typedef struct listnode
{
  struct listnode * next;
  struct listnode * prev;
  TreeNode * tnptr;
} ListNode;
void List_insert(ListNode * * head, ListNode * * tail, unsigned char letter);
void List_merge(ListNode * * head, ListNode * * tail);
void List_destroy(ListNode * head);
#endif
