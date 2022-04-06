#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
  int data;
  struct node * next;
} node_t;

void printIter(const node_t * n) {
  while (n != NULL) {
    printf("%d ", n->data);
    n = n->next;
  }
}

void printRecur(const node_t * n) {
  if (n == NULL) {
    return;
  }

  printRecur(n->next);
  printf("%d ", n->data);
}

void custom(const node_t * n) {
  if (n == NULL) {
    return;
  }
  
  if (n->next != NULL) {
    custom(n->next->next);
  }

  printf("%d ", n->data);
}

int main(int argc, char ** argv) {
  node_t * head = NULL;

  int LIST_SIZE = 6;

  // note the index starts at 1 and goes until equal to LIST_SIZE
  for (int i = 1; i <= LIST_SIZE; i++) {
    node_t * tmp = head;
    head = (node_t *)malloc(sizeof(node_t));
    head->data = i;
    head->next = tmp;
  }

  // Visual representation of linked list
  // head --> 6 --> 5 --> 4 --> 3 --> 2 --> 1

  printIter(head);        // answer Q4.A
  printf("\n");
  printRecur(head);       // answer Q4.B
  printf("\n");
  custom(head);           // answer Q4.C
  printf("\n");
  return EXIT_SUCCESS;
}
