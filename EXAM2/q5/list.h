#ifndef _LIST_H
#define _LIST_H

typedef struct node {
    int value;
    struct node * next;
} Node;

typedef struct {
    Node * head;
    Node * tail;
} List;

#endif
