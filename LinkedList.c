#include "LinkedList.h"
#include <limits.h>
#include <assert.h>

struct Node{
	struct Node *next;
	struct Node *prev;
	int numb;
};

struct List{
	struct Node *head;
	struct Node *tail;
	int size;
};

List *createList(int item){
	//get space for a list struct
	List *list = (List *) malloc (sizeof(List));
	if(list != NULL){
		//create a new node for the list
		Node *newNode = (Node *) malloc (sizeof (Node));
		newNode->numb = item;
		newNode->next = NULL;
		newNode->prev = NULL;
		list->head = newNode;
		list->tail = newNode;
		//return the new node;
		list->size = 1;
	}
	return list;
}

List *createListFromArray(int *items, size_t length){
	List *list = createList(items[0]);
	if(list != NULL){
		int index;
		for(index = 1; index < length; index++)
			addBack(items[index], list);
	}
	return list;
}

Node *addFront(int item, List *list){
	assert (list != NULL && list->head != NULL);
	Node *node = (Node *) malloc (sizeof (Node));
	//malloc could fail.
	if(node != NULL){
		node->numb = item;
		node->next = list->head;
		node->prev = NULL;
		list->head->prev = node;
		list->head = node;
		list->size++;
	}
	return node;
}

Node *addBack(int item, List *list){
	assert (list != NULL && list->head != NULL);
	Node *node = (Node *) malloc (sizeof (Node));
	if(node != NULL){
		node->numb = item;
		node->next = NULL;
		node->prev = list->tail;
		list->tail->next = node;
		list->tail = node;
		list->size++;
	}
	return node;
}

//Add new struct Node after given struct Node.
//returns null if not successful. 
Node *addItem(int item, List *list, Node *currentNode){
	assert (list != NULL && list->head != NULL);
	assert(currentNode != NULL);
	if (currentNode == list->tail)
		return addBack(item, list);
	
	Node *node = (Node *) malloc (sizeof (Node));
	if(node != NULL){
		node->numb = item;
		node->prev = currentNode;
		node->next = currentNode->next;
		currentNode->next->prev = node;
		currentNode->next = node;
		list->size++;
	}
	return node;
}

Node *addAt(int item, List *list, int position){
	assert (list != NULL && list->head != NULL);
	assert (position >= 0);
	assert (position <= getSize(list));
	Node *n = list->head;
	int i;
	for(i = 0; (i < position) && (n->next != NULL); i++)
		n = n->next;
	if(n != NULL)
		return addItem(item, list, n);
	return NULL;
}

int removeFront(List *list){
	assert (list != NULL && list->head != NULL);
	int returnItem = list->head->numb;
	Node *temp_head = list->head;
	if(list->head->next != NULL)
		list->head->next->prev = NULL;
	else
		list->tail = NULL;
	list->head = list->head->next;
	list->size--;
	free(temp_head);
	return returnItem;
}

int removeBack(List *list){
	assert (list != NULL && list->head != NULL);
	int returnItem = list->tail->numb;
	Node *temp_tail = list->tail;
	if(list->tail->prev != NULL)
		list->tail->prev->next = NULL;
	else
		list->head = NULL;
	list->tail = list->tail->prev;
	list->size--;
	free(temp_tail);
	return returnItem;
}

//returns struct Node's number
int removeNode (List *list, Node *node){
	assert (list != NULL && list->head != NULL);
	assert (node != NULL);
	if(node == list->head)
		return removeFront(list);
	else if(node == list->tail)
		return removeBack(list);
	else{
		int returnItem = node->numb;
		node->prev->next = node->next;
		node->next->prev = node->prev;
		list->size--;
		free(node);
		return returnItem;
	}			
}

int removeAt(int position , List *list){
	assert (list != NULL && list->head != NULL);
	assert (position >= 0);
	assert (position < getSize(list));
	
	Node *n = list->head;
	int i;
	for(i = 0; (i < position) && (n->next != NULL); i++)
		n = n->next;
	if(n != NULL){
		return removeNode(list, n);
	}
	return INT_MIN;
}

//returns Node's number 
//or minimum integer if not found.
int removeItem(int item, List *list){
	assert (list != NULL && list->head != NULL);
	struct Node *n;
	for(n = list->head; n != NULL; n = n->next){
		if(n->numb == item){
			return removeNode(list, n);
		}
	}
	return INT_MIN;

}

Node *getFront(List *list){
	assert (list != NULL && list->head != NULL);
	return list->head;
}

Node *getBack(List *list){
	assert (list != NULL && list->head != NULL);
	return list->tail;
}

int getSize(List *list){
	assert (list != NULL && list->head != NULL);
	return list->size;
}

int getItem(Node *node){
	return node->numb;
}

Node *getNode(int item, List *list){
	assert (list != NULL && list->head != NULL);
	Node *n;
	for(n = list->head; n != NULL; n = n->next){
		if(n->numb == item)
			return n;
	}
	return NULL;
}

Node *getNodeAt(int position, List *list){
	assert (list != NULL && list->head != NULL);
	assert (position >= 0);
	assert (position < getSize(list));
	Node *n = list->head;
	int i;
	for(i = 0; (i < position) && (n->next != NULL); i++)
		n = n->next;
	return n;
}

int getMiddleNode(List *list, Node *node){
	Node *slow_node = list->head;
	Node *fast_node = list->head;
	int position = 0;

	while(fast_node != NULL && fast_node->next != NULL){
		fast_node = fast_node->next->next;
		slow_node = slow_node->next;
		position++;
	}
	if(node != NULL)
		*node = *slow_node;
	return position;

}

int *listToArray(List *list){
	assert (list != NULL && list->head != NULL);
	int *array = (int *) calloc(list->size, sizeof(int));
	Node *itr;
	int index = 0;
	for(itr = list->head; itr != NULL && index < (list->size); itr = itr->next)
		array[index++] = itr->numb;
	return array;	
}

void printList(List *list){
	assert (list != NULL);
	if(list->head == NULL)
		printf("NULL\n");
	else{
		Node *itr = list->head;
		printf("{");
		while(itr->next != NULL){
			printf("%d, ", itr->numb);
			itr = itr->next;
		}
		printf("%d} Size: %d\n", itr->numb, getSize(list));
	}
}

void destroyList(List *list){
	assert (list != NULL);
	if(list->head == NULL){
		free(list);
		return;
	}else if(list->head->next == NULL){
		free(list->head);
		free(list);
	}else{
		Node *delete_node = list->head;
		Node *itr_node = list->head->next;
		while(itr_node != NULL){
			free(delete_node);
			delete_node = itr_node;
			itr_node = itr_node->next;
		}
		free(delete_node);
		free(list);
	}
}

/*int main(){
	int array[] = {1,2,3,4,5,6,7,8,9,10};
	List *list = createListFromArray(array, 10);
	printList(list);
	printf("Index: %d\n", getMiddleNode(list, NULL));
}*/

