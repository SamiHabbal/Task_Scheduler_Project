#ifndef _LIST_API_
#define _LIST_API_

#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>



typedef struct task{
    char* title;
    char* description;
    char* time;
    int month;
    int day;
    int year;
    int hour;
    int minute;
    int duration;
} Task;

/**
 * Node of a linked list. This list is doubly linked, meaning that it has points to both the node immediately in front 
 * of it, as well as the node immediately behind it.
 **/
typedef struct listNode{
    Task* task;
    struct listNode* next;
} Node;

/**
 * Metadata head of the list. 
 * Contains no actual data but contains
 * information about the list (head and tail) as well as the function pointers
 * for working with the abstracted list data.
 **/
typedef struct listHead{
    Node* head;
    int length;
} List;

Task* initializeTask(char* title, char* description, char* time, int month, int day, int year, int minute, int duration);

/*Mostly for debugging.
Given the list head, traverse the list and 
print out the contents of all the nodes*/
void printList(List* list);

/**Function for creating a node for the linked list. 
* This node contains abstracted (void *) data as well as previous and next
* pointers to connect to other nodes in the list
*@pre data should be of same size of void pointer on the users machine to avoid size conflicts. data must be valid.
*data must be cast to void pointer before being added.
*@post data is valid to be added to a linked list
*@return On success returns a node that can be added to a linked list. On failure, returns NULL.
*@param data - a void * pointer to any data type.  Data must be allocated on the heap.
**/
Node* initializeNode(Task* task);

//Simply set list head to NULL and length to 0
List* initializeList();

/**Inserts a Node at the front of a linked list.  List metadata is updated
* so that head and tail pointers are correct.
*@pre 'List' type must exist and be used in order to keep track of the linked list.
*@param list pointer to the List struct
*@param toBeAdded - a pointer to data that is to be added to the linked list
**/
void insertFront(List* list, Task* toBeAdded);

int compareTask(Task* task, Task* task2);

/**Inserts a Node at the back of a linked list. 
*List metadata is updated so that head and tail pointers are correct.
*@pre 'List' type must exist and be used in order to keep track of the linked list.
*@param list pointer to the List struct
*@param toBeAdded - a pointer to data that is to be added to the linked list
**/
void insertBack(List* list, Task* toBeAdded);

/** Deletes the entire linked list, freeing all memory asssociated with the list, including the list struct itself.
* Uses the supplied function pointer to release allocated memory for the data.
* @pre 'List' type must exist and be used in order to keep track of the linked list.
* @param list pointer to the List struct
**/
void freeList(List* list);

/** Clears the list: frees the contents of the list - Node structs and data stored in them - 
 * without deleting the List struct
 * uses the supplied function pointer to release allocated memory for the data
 * @pre 'List' struct must exist and be used in order to keep track of the linked list.
 * @post List struct still exists, list head = list tail = NULL, list length = 0
 * @param list pointer to the List-type dummy node
 * @return  on success: NULL, on failure: head of list
**/
void clearList(List* list);

/** Uses the comparison function pointer to place the element in the 
* appropriate position in the list.
* should be used as the only insert function if a sorted list is required.  
*@pre List exists and has memory allocated to it. Node to be added is valid.
*@post The node to be added will be placed immediately before or after the first occurrence of a related node
*@param list - a pointer to the List struct
*@param toBeAdded - a pointer to data that is to be added to the linked list
**/
Node* insertSorted(Task* toBeAdded);



/** Removes data from from the list, deletes the node and frees the memory,
 * changes pointer values of surrounding nodes to maintain list structure.
 * returns the data 
 * You can assume that the list contains no duplicates
 *@pre List must exist and have memory allocated to it
 *@post toBeDeleted will have its memory freed if it exists in the list.
 *@param list - a pointer to the List struct
 *@param toBeDeleted - a pointer to data that is to be removed from the list
 *@return on success: void * pointer to data  on failure: NULL
 **/
Task* deleteDataFromList(List* list, Task* task);



/**Returns a pointer to the data at the front of the list. Does not alter list structure.
 *@pre The list exists and has memory allocated to it
 *@param list - a pointer to the List struct
 *@return pointer to the data located at the head of the list
 **/
void* getFromFront(List* list);



/**Returns a pointer to the data at the back of the list. Does not alter list structure.
 *@pre The list exists and has memory allocated to it
 *@param list - a pointer to the List struct
 *@return pointer to the data located at the tail of the list
 **/
void* getFromBack(List* list);



/**Returns a string that contains a string representation of
the list traversed from  head to tail. Utilize the list's printData function pointer to create the string.
returned string must be freed by the calling function.
 *@pre List must exist, but does not have to have elements.
 *@param list - a pointer to the List struct
 *@return on success: char * to string representation of list (must be freed after use).  on failure: NULL
 **/
char* toString(List* list);

/**Returns the number of elements in the list.
 *@pre List must exist, but does not have to have elements.
 *@param list - a pointer to the List struct.
 *@return on success: number of eleemnts in the list (0 or more).  on failure: -1 (e.g. list not initlized correctly)
 **/
int getLength(List* list);


/** Function that searches for an element in the list using a comparator function.
 * If an element is found, a pointer to the data of that element is returned
 * Returns NULL if the element is not found.
 *@pre List exists and is valid.  Comparator function has been provided.
 *@post List remains unchanged.
 *@return The data associated with the list element that matches the search criteria.  If element is not found, return NULL.
 *@param list - a pointer to the List sruct
 *@param customCompare - a pointer to comparator function for customizing the search
 *@param searchRecord - a pointer to search data, which contains seach criteria
 *Note: while the arguments of compare() and searchRecord are all void, it is assumed that records they point to are
 *      all of the same type - just like arguments to the compare() function in the List struct
 **/
void* findElement(List * list, bool (*customCompare)(const void* first,const void* second), const void* searchRecord);

#endif