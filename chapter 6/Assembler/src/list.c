/*

Functions related to linked-lists.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"


// Push a value onto the end of the list
void pushList(listNode *head, int val)
{
	listNode *current = head;

	// Find end of list
	while (current->next != NULL)
		current = current->next;

	// Add new node
	current->next = NULL;
	current->next = malloc(sizeof(listNode));
	if (current->next == NULL)
        fprintf(stderr, "Could not malloc current->next. \n");
        
	// Fill new node with desired value
	current->next->val = val;
	current->next->next = NULL;
}


// Determine length of a list
int getListLength(listNode *head)
{
    int length = 0;

    listNode *current = head;

	// Increment length for each node in the list
    while (current != NULL)
    {
        length++;
        
        current = current->next;
    }

    return length;
}


// Convert linked list to string
char *listToString(listNode *head)
{
    int length = getListLength(head);

	// String to contain contents of linked list
    char *str = NULL;
    str = malloc(length + 1);
    if (str == NULL)
        fprintf(stderr, "Could not malloc str. \n");
    	

    listNode *current = head;

	
	// Copy characters from list to string and add null terminator
    int i = 0;
    while (current != NULL)
    {
        str[i] = current->val;

        i++;
        current = current->next;
    }
    str[length] = '\0';


    return str;
}


// Free every node in a list
void freeList(listNode *head)
{
    listNode *current = head;
    listNode *temp = NULL;
    
	while (current != NULL)
	{
		temp = current;
		
		current = current->next;
		
		free(temp);
	}
}


// Print out index and values of a list
void printListIndexed(listNode *head)
{
	listNode *current = head;	
	
	int i = 0;
	while (current != NULL)
	{
		printf("[%i] = %c \n", i, current->val);
	
		i++;
		current = current->next;
	}
}
