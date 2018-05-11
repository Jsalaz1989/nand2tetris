#include <stdio.h>
#include <stdlib.h>

#include "structs.h"
#include "functions.h"
#include "symbolizer.h"


void printFields(infoStruct solutions)
{
    printf("instructionType = %i \n", solutions.instructionType);

    if (solutions.instructionType == 0)
    {
        if (solutions.value != NULL)
        printf("value = %s \n", solutions.value);

        if (solutions.userSymbol != NULL)
        printf("userSymbol = %s \n", solutions.userSymbol);
    }
    else if (solutions.instructionType == 1)
    {
        printf("label = %s \n", solutions.label);
    }
    else if (solutions.instructionType == 2)
    {
        if (solutions.dest != NULL)
            printf("dest = %s \n", solutions.dest);

        if (solutions.comp != NULL)
            printf("comp = %s \n", solutions.comp);

        if (solutions.jump != NULL)
            printf("jump = %s \n", solutions.jump);
    }
    printf("\n");
}

void printList(lineNode *head)
{
    lineNode *current = head;

    while (current != NULL)
    {
        printf("%c = %d\n", current->val, current->val);
        current = current->next;
    }
    printf("\n");
}



void printList2(lineNode *head)
{
    lineNode *current = head;

    while (current != NULL)
    {
        printf("%c", current->val);
        current = current->next;
    }
    printf("\n");
}

void printFields2(_Bool instructionType, _Bool destPresent, _Bool jumpPresent, char *value, char *dest, char *comp, char *jump)
{
    if (instructionType == 0)
        printf("value = %s \n", value);

    if (destPresent == 1)
        printf("dest = %s \n", dest);

    if (instructionType == 1)
        printf("comp = %s \n", comp);

    if (jumpPresent == 1)
        printf("jump = %s \n", jump);

    printf("\n");
}


void printInstructionType(_Bool instructionType, _Bool dest, _Bool jump)
{
    printf("instructionType = %i \n", instructionType);

    if (instructionType == 1)
    {
        printf("dest = %i \n", dest);
        printf("jump = %i \n\n", jump);
    }
}


void printBinary(_Bool binInstruction[])
{
    printf("binInstruction = ");
    int i;
    for(i = 0; i<=15; i++)
    {
        if (binInstruction[i] == 0)
            printf("0");
        else
            printf("1");
    }
    printf("\n");
}

void printBinaryComp(_Bool binInstruction[])
{
    printf("comp = ");
    int i;
    for(i = 3; i<=9; i++)
    {
        if (binInstruction[i] == 0)
            printf("0");
        else
            printf("1");
    }
    printf("\n");
}

void printBinaryDest(_Bool binInstruction[])
{
    printf("dest = ");
    int i;
    for(i = 10; i<=12; i++)
    {
        if (binInstruction[i] == 0)
            printf("0");
        else
            printf("1");
    }
    printf("\n");
}

void printBinaryJump(_Bool binInstruction[])
{
    printf("jump = ");
    int i;
    for(i = 13; i<=15; i++)
    {
        if (binInstruction[i] == 0)
            printf("0");
        else
            printf("1");
    }
    printf("\n");
}

void printBinarySolutions(binStruct binarySolutions)
{
    printf("binary = ");
    if (binarySolutions.bin0 == 0)
        printf("0");
    else
        printf("1");

    if (binarySolutions.bin1 == 0)
        printf("0");
    else
        printf("1");

    if (binarySolutions.bin2 == 0)
        printf("0");
    else
        printf("1");

    if (binarySolutions.bin3 == 0)
        printf("0");
    else
        printf("1");

    if (binarySolutions.bin4 == 0)
        printf("0");
    else
        printf("1");

    if (binarySolutions.bin5 == 0)
        printf("0");
    else
        printf("1");

    if (binarySolutions.bin6 == 0)
        printf("0");
    else
        printf("1");

    if (binarySolutions.bin7 == 0)
        printf("0");
    else
        printf("1");

    if (binarySolutions.bin8 == 0)
        printf("0");
    else
        printf("1");

    if (binarySolutions.bin9 == 0)
        printf("0");
    else
        printf("1");

    if (binarySolutions.bin10 == 0)
        printf("0");
    else
        printf("1");

    if (binarySolutions.bin11 == 0)
        printf("0");
    else
        printf("1");

    if (binarySolutions.bin12 == 0)
        printf("0");
    else
        printf("1");

    if (binarySolutions.bin13 == 0)
        printf("0");
    else
        printf("1");

    if (binarySolutions.bin14 == 0)
        printf("0");
    else
        printf("1");

    if (binarySolutions.bin15 == 0)
        printf("0");
    else
        printf("1");

    printf("\n");
}

void printBinaryInstruction(int binInstruction[])
{
    printf("binInstruction = ");
    int i;
    for(i = 0; i<=15; i++)
    {
        if (binInstruction[i] == 0)
            printf("0");
        else
            printf("1");
    }
    printf("\n");
}




void printHashTableRow(entryNode *hashTable[], int tableSize, int row)
{
    if (hashTable[row] != NULL)
    {
        entryNode *current = hashTable[row];

        while (current != NULL)
        {
            unsigned int hashReturn = hashFunction(current->symbol, tableSize);

            printf("%s\t%i\t%i\n", current->symbol, current->address, hashReturn);

            current = current->next;
        }
    }
}

void printHashTable(entryNode *hashTable[], int tableSize)
{
    printf("Symbol\tAddress\tHash\n");
    int i;
    for (i = 0; i < tableSize; i++)
    {
        printHashTableRow(hashTable, tableSize, i);
    }
    printf("\n");
}
