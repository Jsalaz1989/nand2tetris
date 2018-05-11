#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "structs.h"
#include "printFunctions.h"
#include "parse.h"
#include "symbolizer.h"




void push(lineNode *head, int val)
{
    lineNode *current = head;

    while (current->next != NULL)
        current = current->next;

    // Now we can add a new variable
    current->next = malloc(sizeof(lineNode));
    if (current->next == NULL)
    {
        fprintf(stderr, "Could not create head of list.\n");
        //return;
    }

    current->next->val = val;
    current->next->next = NULL;
}


void addFromFileToListUntilDelimiter(lineNode *head, FILE *inptr, int delimiter)
{
    char val = getc(inptr);

    // Complete the list (the entire command) by appending nodes to the head node
    while (val != EOF)
    {
        if (val == delimiter || val == '\n')
        {
            push(head, '\0');
            break;
        }
        else
        {
            push(head, val);
        }


        val = getc(inptr);
    }
}

/*
void addFromFileToListUntilDelimiter(lineNode *head, FILE *inptr, int delimiter)
{
    char val = getc(inptr);

    // Complete the list (the entire command) by appending nodes to the head node
    while (val != EOF)
    {
        if (val != delimiter)
        {
            push(head, '\0');
            break;
        }
        else
        {
            push(head, val);
        }
    }
}
*/


/*
void addFromFileToListUntilDelimiter(lineNode *head, FILE *inptr, int delimiter)
{
    // Complete the list (the entire command) by appending nodes to the head node
    while (1)
    {
        char val = getc(inptr);

        if (val == delimiter)         // newline 10
            break;
        else
            push(head, val);
    }
}
*/

_Bool searchList(lineNode *head, int val)
{
    lineNode *current = head;

    while (current != NULL)
    {
        if (current->val == val)
            return 1;

        current = current->next;
    }

    return 0;
}



lineNode *copy(lineNode *head) // Based off "copy" function from: https://stackoverflow.com/questions/13633182/c-program-to-make-a-second-copy-of-a-linked-list
{
    if (head == NULL)
        return NULL;

    lineNode *headC = (lineNode *)malloc(sizeof(lineNode));
    headC->val = head->val;
    headC->next = copy(head->next);

    return headC;
}


void addFromListToListUntilDelimiter(lineNode *headC, lineNode *head, int delimiter)
{
    // Complete the list (the entire command) by appending nodes to the head node
    while (head !=NULL && head->val != delimiter)
    {
        push(headC, head->val);

        head = head->next;
    }

    push(headC, '\0');
}

lineNode *copyList(lineNode *head, int delimiter)
{
    lineNode *newHead = malloc(sizeof(lineNode));
    if (newHead == NULL)
    {
        fprintf(stderr, "Could not create newHead\n");
        return NULL;
    }

    lineNode *current = head;

    while (current != NULL  && current->next != NULL)
    {
        if (current->next->val != delimiter)
        {
            push(newHead, current->val);
        }

        current = current->next;
    }
    push(newHead, '\0');

    return newHead;
}


int getListLength(lineNode *head)
{
    int length = 0;

    lineNode *current = head;

    while (current != NULL && current->next != NULL)
    {
        length++;
        current = current->next;
    }

    return length;
}

void push2(entryNode *head, char *symbol, int address)
{
    entryNode *current = head;
    while (current->next != NULL)
        current = current->next;

    // Now we can add a new variable
    current->next = malloc(sizeof(entryNode));
    current->next->symbol = symbol;
    current->next->address = address;
    current->next->next = NULL;
}









_Bool compareLists(lineNode *listA, lineNode *listB)
{
    if (listA == NULL || listB == NULL)
    {
        //printf("null list(s) \n");
        return 0;
    }
    else
    {
        lineNode *currentA = listA;
        lineNode *currentB = listB;

        while (currentA != NULL && currentB != NULL)
        {
            if (currentA->val != currentB->val)
            {
                //printf("different \n");
                return 0;
            }

            currentA = currentA->next;
            currentB = currentB->next;
        }

        //printf("same list \n");
        return 1;
    }

    //return 1;

}

_Bool compareListAndString(lineNode *listA, char *str)
{
    if (listA == NULL || str == NULL)
    {
        //printf("null list(s) \n");
        return 0;
    }
    else
    {
        lineNode *currentA = listA;
        //lineNode *currentB = str;
        int i = 0;

        while (currentA != NULL && str[i] != '\0')
        {
            if (currentA->val != str[i])
            {
                //printf("different \n");
                return 0;
            }

            currentA = currentA->next;
            i++;
        }

        //printf("same list \n");
        return 1;
    }

    //return 1;

}


char *listToString(lineNode *head)
{
    char *str = NULL;
    int length = getListLength(head);
    str = malloc(length * sizeof(char));
    if (str == NULL)
    {
        fprintf(stderr, "Could not create str\n");
    }

    lineNode *current = head;

    int i = 0;
    while (current != NULL)
    {
        str[i] = current->val;

        i++;
        current = current->next;
    }

    return str;
}






int getNumberOfDigits(int value)
{
    int numDigits = 0;
    int power = 0;
    while (power < value)
    {
        numDigits++;

        power = pow(10, numDigits);
    }

    return numDigits;
}

lineNode *initializeList(char val)
{
     // Create first node
    lineNode *head = NULL;
    head = malloc(sizeof(lineNode));
    if (head == NULL)
    {
        fprintf(stderr, "Could not create head of list.\n");
    }

    head->val = val;
    head->next = NULL;

    return head;
}


int positionInList(lineNode *head, int value)
{
    lineNode *current = head;
    int count = 0;

    while (current != NULL)
    {
        if (current->val == value)
            return count;

        count++;
        current = current->next;
    }

    return 0;
}

char valueInList(lineNode *head, int position)
{
    lineNode *current = head;

    int i;
    for (i = 0; i < position; i++)
    {
        current = current->next;
    }

    return current->val;
}


char *listToString2(lineNode *head, int startPos, int endPos)
{
    char *str = NULL;
    str = malloc(sizeof(char));
    if (str == NULL)
    {
        fprintf(stderr, "Could not create str\n");
    }

    int i;
    for (i = startPos; i < endPos; i++)
    {
            //printf("valueInList(%i) = %c \n", i, valueInList(head, i));
            str[i-startPos] = valueInList(head, i);
    }
    str[i+1] = '\0';

    return str;
}

int listToInt(lineNode *head)
{
    /*
    The lists contain their digits as characters.
    Convert each character to its numerical value and sum them up.
    Eg. 452 = 4x100 + 5x10 + 2x1
    */
    int listLength = getListLength(head);
    lineNode *currentDigit = head;
    long value = 0;
    while (listLength > 0)
    {
        listLength--;

        int digit = atoi(&currentDigit->val);       // Eg.    4
        int digitPlace = pow(10,listLength);        //      100
        int digitValue = digit * digitPlace;        //    4x100

        value = value + digitValue;

        currentDigit = currentDigit->next;
    }

    return value;
}

void addLabelSymbols2(FILE *inptr, entryNode* hashTable[], int tableSize)
{
    int instructionNum = 0;

    while (getc(inptr) != EOF)
    {
        int address = 0;

        infoStruct solutions = parse(inptr);
        //printFields(solutions.instructionType, solutions.destPresent, solutions.jumpPresent, solutions.value, solutions.dest, solutions.comp, solutions.jump);

        if (solutions.instructionType == 1)
        {
            if (strchr(solutions.comp, ')') != NULL)
            {
                //printf("strlen(comp) = %lu \n", strlen(solutions.comp));

                char *symbol = NULL;
                symbol = malloc(sizeof(symbol));
                if (symbol == NULL)
                {
                    fprintf(stderr, "Could not create symbol.\n");
                }

                int i = 0;
                if (strchr(solutions.comp, '(') != NULL)
                {
                    for (i = 1; i < strlen(solutions.comp) - 1; i++)
                    {
                        symbol[i-1] = solutions.comp[i];
                        //printf("solutions.comp[%i] = %c \n", i, solutions.comp[i]);
                        //printf("symbol[%i] = %c \n", i, symbol[i]);
                    }

                    address = instructionNum;
                }
                else if (strchr(solutions.comp, ')') != NULL)
                {
                    for (i = 0; i < strlen(solutions.comp) - 1; i++)
                    {
                        symbol[i] = solutions.comp[i];
                        //printf("solutions.comp[%i] = %c \n", i, solutions.comp[i]);
                        //printf("symbol[%i] = %c \n", i, symbol[i]);
                    }

                    address = instructionNum-1;

                }
                symbol[i+1] = '\0';

                //printf("symbol = %s \n", symbol);


                //if (searchHashTable(hashTable, tableSize, symbol) == 0)
                    addSymbol(symbol, address, hashTable, tableSize);
            }
        }

        if (solutions.instructionType == 0)
        {
            instructionNum++;
        }
        else if (solutions.instructionType ==1)
        {
            if (solutions.comp != NULL)
            {
                if (strchr(solutions.comp, '(') == NULL)
                    instructionNum++;
            }
        }

    }
}




