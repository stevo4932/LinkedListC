#ifndef LINKED_LIST_HEADER
#define LINKED_LIST_HEADER

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

	typedef struct Node Node;
	typedef struct List List;

	//Creates a new List structure with one node.
	struct List *createList(int item);
	//Creates a new list from the given array.
	List *createListFromArray(int *items, size_t length);
	//frees node and list memory.
	void destroyList(List *list);

	//Add items to from or back of list
	//returns created node or null if unsucessful. 
	Node *addFront(int item, List *list);
	Node *addBack(int item, List *list);
	//Add item after "currentNode" 
	//returns created node or null if unsucessful.
	Node *addItem(int item, List *list, Node *currentNode);
	Node *addAt(int item, List *list, int position);

	//Remove items from front or back of list
	//returns item that was removed(not the node).
	int removeFront(List *list);
	int removeBack(List *list);
	//Remove given node from the list
	//returns item that was removed (not the node).
	int removeNode (List *list, Node *node);
	//Remove node that matches the given item or position in the list
	//returns item that was removed or INT_MIN if not found. 
	int removeItem(int item, List *list);
	int removeAt(int position , List *list);

	//returns the node from the front or back of the list
	//does not remove the node from the list.
	Node *getFront(List *list);
	Node *getBack(List *list);
	//returns the node matching the item or position in the list
	//does not remove the node from the list.
	Node *getNode(int item, List *list);
	Node *getNodeAt(int position, List *list);
	//get's the middle item and node from the list.
	//returns the item and the middle node is set to given node variable.
	//if returned node is not needed, pass in NULL for node variable. 
	int getMiddleNode(List *list, Node *node);
	//Get's the item from a given node.
	int getItem(Node *node);
	//Get's the size of the list O(1);
	int getSize(List *list);

	//converts the list to a integer array.
	int *listToArray(List *list);
	//prints the list to standard out.
	void printList(List *list);

#endif
