#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "list.h"

/** HELPER FUNCTIONS **/

//Count how many "turns" there are in a path. A turn happens whenever the direction changes.
int turnCount(char * path) {
	char curDir = path[0];
	int loc = 0;
	int turns = 0;
	while (path[loc] != '\0') {
		if (curDir != path[loc]) turns++;
		curDir = path[loc];
		loc++;
	}
	return turns;
}

//return <0 if path1 is shorter or alphabetically earlier than path2
//return 0 if path1 and path2 are equal
//return >0 otherwise
int comparePaths(char * path1, char * path2) {
	int lengthdiff = strlen(path1) - strlen(path2);
	int turndiff = turnCount(path1) - turnCount(path2);
	return (lengthdiff != 0) ? lengthdiff :
	  ((turndiff != 0) ? turndiff : strcmp(path1, path2));
}

//Add a node right in front of curPtr.
//curPtr points to a PathNode pointer that points to the node you want to 
//insert *in front of*. So, for example, if curPtr == &head, this method
//will insert at the front of the list.
void addNodeHere(PathNode * * curPtr, char * path) {
	PathNode * newNode = buildNode(path);
	
	newNode->next = (* curPtr);
	
	(* curPtr) = newNode;
}

//Remove the node pointed to by * curPtr
//e.g., to remove the first node in the list, call removeNodeHere(&head);
bool removeNodeHere(PathNode * * curPtr) {
	if (* curPtr == NULL) return false;
	
	//Create a temporary pointer to point to the node we want to replace
	PathNode * toDelete = * curPtr;
	
	//Point curPtr "past" the node to delete
	(* curPtr) = toDelete->next;
	
	//Delete toDelete
	freeNode(toDelete);
	
	return true;
}

//Search through the list to find a next pointer that *points to* the first
//node whose path is > the search path
PathNode * * findNodeGT(PathNode * * curPtr, char * path) {
	while ((* curPtr != NULL) && (comparePaths((* curPtr)->path, path) < 0)) {
		curPtr = &((* curPtr)->next);
	}
	
	return curPtr;
}

//Search through the list to find a next pointer that *points to* the first
//node whose path is == the search path
PathNode * * findNodeEQ(PathNode * * curPtr, char * path) {
	while ((* curPtr != NULL) && (!(strcmp((* curPtr)->path, path) == 0))) {
		curPtr = &((* curPtr)->next);
	}
	
	return curPtr;
}

/** INTERFACE FUNCTIONS **/

PathLL * buildPaths() {
	PathLL * retval = malloc(sizeof(PathLL));
	retval->head = NULL;
	return retval;
}

void freePaths(PathLL * p) {
	while (removeNodeHere(&(p->head))) {}
	free(p);
}

PathNode * buildNode(char * path) {
	PathNode * retval = malloc(sizeof(PathNode));
	retval->path = malloc((strlen(path) + 1) * sizeof(char));
	strcpy(retval->path, path);
	retval->next = NULL;
	return retval;
}

void freeNode(PathNode * p) {
	free(p->path);
	p->next = NULL;
	free(p);
}

bool addNode(PathLL * paths, char * path) {
	
	PathNode * * curPtr = findNodeGT(&(paths->head), path);
	
	//curPtr now *holds the address* of the "next" pointer that needs to be updated. (* curPtr) = ... will update the correct "next" pointer.
	
	//First, see whether we're pointing to an equivalent node. If we are, fail
	if ((* curPtr != NULL) && !strcmp((* curPtr)->path, path)) {
		return false;
	}
	
	addNodeHere(curPtr, path);
	
	return true;
}

bool removeNode(PathLL * paths, char * path) {
	
	PathNode * * curPtr = findNodeEQ(&(paths->head), path);
	
	//curPtr now *holds the address* of the "next" pointer pointing to the node that needs to be removed.
	
	return removeNodeHere(curPtr);
}

bool containsNode(PathLL * paths, char * path) {
	return (* findNodeEQ(&(paths->head), path)) != NULL;
}

void printPaths(PathLL * paths, FILE * fptr) {
	PathNode * curr = paths->head;
	int i = 0;
	while (curr != NULL) {
		fprintf(fptr, "Path %2d: %s\n", i, curr->path);
		i++;
		curr = curr->next;
	}
}
