// Singly-linked list
typedef struct linkedListnode 
{
    char val;
    struct linkedListnode *next;
} 
listNode;


// Push a value onto the end of the list
void pushList(listNode *head, int val);


// Determine length of a list
int getListLength(listNode *head);


// Convert linked list to string
char *listToString(listNode *head);


// Free every node in a list
void freeList(listNode *head);


// Print out index and values of a list
void printListIndexed(listNode *head);
