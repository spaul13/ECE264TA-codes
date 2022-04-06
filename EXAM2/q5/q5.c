#include <stdio.h>
#include <stdlib.h>
#include "list.h"

// Create a new node
static Node * node_construct(int val){
    Node * nd = malloc(sizeof (Node));
    nd -> next = NULL;
    nd -> value = val;
    return nd;
}

// Insert a node to the end of a linked list
void list_insert(List * list, int val){
    Node * ptr = node_construct(val);
    if(list -> head == NULL){
        list -> head = ptr;
        list -> tail = ptr;
    }
    //----QUESTION A: Fix the following code----
    else{
        [  ANSWER A  ] = ptr;
        list -> tail = ptr;
    }
}

// Print the values of all nodes in the linked list
void list_print(List * list){
    Node * nd = list -> head;
    while (nd != NULL){
        printf ("%d ", nd -> value);
        nd = nd -> next;
    }
    printf("\n");
}

// Destroy the entire linked list
void list_destroy(List * list){
    Node * nd = list -> head;
    Node * ptr;
    while (nd != NULL){
        ptr = nd -> next;
        free (nd);
        nd = ptr;
    }
    //----QUESTION B: Fix the following code----
    free([  ANSWER B  ]);
}

int main(int argc, char * * argv) {
    if (argc < 2) {
        printf("Not enough inputs.\n");
        return EXIT_FAILURE;
    }

    // Create a linked list with the input values
    List * llist = malloc(sizeof(*llist));
    llist -> head = NULL;
    llist -> tail = NULL;
    int value;
    for(int i = 1; i < argc; i++) {
        value = (int) strtol(argv[i], NULL, 10);
        list_insert(llist, value);
    }
    list_print(llist);
    list_destroy(llist);
    return EXIT_SUCCESS;
}
