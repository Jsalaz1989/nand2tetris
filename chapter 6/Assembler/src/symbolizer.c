#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "structs.h"
#include "functions.h"
#include "parse.h"
#include "printFunctions.h"


#define HASH_TABLE_SIZE 5


unsigned int hashFunction(char *symbol, int tableSize)
{
    if (symbol != NULL)
    {
        int i;
        int sum = 0;
        unsigned int hashReturn;

        for (i = 0; symbol[i] != '\0'; i++)
            sum = sum + symbol[i];

        return hashReturn = sum % tableSize;
    }

    return tableSize+1;
}



void initializeHashTable(entryNode *hashTable[], int tableSize)
{
    int i;
    for (i = 0; i < 23; i++)
    {
        char *symbol = NULL;
        int address = 0;

        if (i == 0)
        {
            symbol = "R0";
            address = 0;
        }
        else if (i == 1)
        {
            symbol = "R1";
            address = 1;
        }
        else if (i == 2)
        {
            symbol = "R2";
            address = 2;
        }
        else if (i == 3)
        {
            symbol = "R3";
            address = 3;
        }
        else if (i == 4)
        {
            symbol = "R4";
            address = 4;
        }
        else if (i == 5)
        {
            symbol = "R5";
            address = 5;
        }
        else if (i == 6)
        {
            symbol = "R6";
            address = 6;
        }
        else if (i == 7)
        {
            symbol = "R7";
            address = 7;
        }
        else if (i == 8)
        {
            symbol = "R8";
            address = 8;
        }
        else if (i == 9)
        {
            symbol = "R9";
            address = 9;
        }
        else if (i == 10)
        {
            symbol = "R10";
            address = 10;
        }
        else if (i == 11)
        {
            symbol = "R11";
            address = 11;
        }
        else if (i == 12)
        {
            symbol = "R12";
            address = 12;
        }
        else if (i == 13)
        {
            symbol = "R13";
            address = 13;
        }
        else if (i == 14)
        {
            symbol = "R14";
            address = 14;
        }
        else if (i == 15)
        {
            symbol = "R15";
            address = 15;
        }
        else if (i == 16)
        {
            symbol = "SP";
            address = 0;
        }
        else if (i == 17)
        {
            symbol = "LCL";
            address = 1;
        }
        else if (i == 18)
        {
            symbol = "ARG";
            address = 2;
        }
        else if (i == 19)
        {
            symbol = "THIS";
            address = 3;
        }
        else if (i == 20)
        {
            symbol = "THAT";
            address = 4;
        }
        else if (i == 21)
        {
            symbol = "SCREEN";
            address = 16384;
        }
        else if (i == 22)
        {
            symbol = "KBD";
            address = 24576;
        }


        entryNode *current = NULL;
        current = malloc(sizeof(entryNode));
        if (current == NULL)
            fprintf(stderr, "Could not create head of list.\n");
        current->symbol = symbol;
        current->address = address;
        current->next = NULL;

        unsigned int hashValue = hashFunction(symbol, tableSize);

        if (hashTable[hashValue] == NULL)
            hashTable[hashValue] = current;
        else
            push2(hashTable[hashValue], current->symbol, current->address);
    }
}



_Bool searchHashTable(entryNode *hashTable[], int tableSize, char needle[])
{
    int i;
    for (i = 0; i < tableSize; i++)
    {
        if (hashTable[i] != NULL)
        {
            entryNode *current = hashTable[i];

            while (current != NULL && current->symbol != NULL && needle != NULL)
            {
                if(strcmp(current->symbol, needle) == 0)
                {
                    return 1;
                }

                current = current->next;
            }
        }
    }

    return 0;
}

void addSymbol(char *symbol, int address, entryNode *hashTable[], int tableSize)
{
    unsigned int hashValue = hashFunction(symbol, tableSize);

    push2(hashTable[hashValue], symbol, address);

    entryNode *current = hashTable[hashValue];
    while (current->next != NULL)
        current = current->next;
}


void addLabelSymbols(FILE *inFile, entryNode* hashTable[])
{
    int instructionNum = 0;

    while (getc(inFile) != EOF)
    {
        infoStruct solutions = parse(inFile);

        if (solutions.instructionType == 1)
        {
            if (searchHashTable(hashTable, HASH_TABLE_SIZE, solutions.label) == 0)
            {
                int address = instructionNum;

                addSymbol(solutions.label, address, hashTable, HASH_TABLE_SIZE);
            }
        }

        if (solutions.instructionType != 1)
            instructionNum++;
    }
}


void addUserSymbols(FILE *inFile, entryNode* hashTable[], int tableSize)
{
    int availableRAMaddress = 16;

    while (getc(inFile) != EOF)
    {
        infoStruct solutions = parse(inFile);

        // Search for symbol in A-instruction, to be stored in head node
        if (solutions.userSymbol != NULL)
        {
            if (searchHashTable(hashTable, tableSize, solutions.userSymbol) == 0)
            {
                addSymbol(solutions.userSymbol, availableRAMaddress, hashTable, tableSize);

                availableRAMaddress++;
            }
        }
    }
}


int getSymbolAddress(entryNode *hashTable[], int tableSize, char needle[])
{
    int i;
    for (i = 0; i < tableSize; i++)
    {
        if (hashTable[i] != NULL)
        {
            entryNode *current = hashTable[i];

            while (current != NULL)
            {
                if(strcmp(current->symbol, needle) == 0)
                {
                    //printf("%s found \n", needle);
                    return current->address;
                }

                current = current->next;
            }
        }
    }

    return 0;
}


void replaceSymbols(FILE *inFile, FILE *outFile, entryNode *hashTable[], int tableSize)
{
    char currentChar = getc(inFile);
    while (currentChar != EOF)
    {
        infoStruct solutions = parse(inFile);
        //printFields(solutions);

        if (solutions.instructionType == 0)
        {
            if (solutions.userSymbol != NULL)
            {
                putc('@', outFile);

                if (searchHashTable(hashTable, tableSize, solutions.userSymbol))
                {
                    int address = getSymbolAddress(hashTable, HASH_TABLE_SIZE, solutions.userSymbol);
                    fprintf(outFile, "%i", address);
                    fprintf(outFile, "\n");
                }
            }
            else if (solutions.value != NULL)
            {
                putc('@', outFile);
                fprintf(outFile, "%s", solutions.value);
                fprintf(outFile, "\n");
            }
        }
        else if (solutions.instructionType == 1)
        {
          //  currentChar = getc(inFile);
            //printf("out of loop currentChar = %c \n", currentChar);
            //while (currentChar != '@' || )
            //{

              //  currentChar = getc(inFile);
                //printf("in loop currentChar = %c \n", currentChar);


                // do nothing
                // maybe print newline?
        //    }
        }
        else if (solutions.instructionType == 2)
        {
            if (strlen(solutions.dest) != 0)
            {
                fprintf(outFile, "%s", solutions.dest);
                putc('=', outFile);
            }

            fprintf(outFile, "%s", solutions.comp);

            if (strlen(solutions.jump) != 0)
            {
                putc(';', outFile);
                fprintf(outFile, "%s", solutions.jump);
            }

            putc('\n', outFile);
        }

        currentChar = getc(inFile);
    }

    printf("\n");
}



void searchAndDestroySymbols(FILE *inFile, FILE *outFile)
{
    entryNode *hashTable[HASH_TABLE_SIZE];
    int i;
    for (i = 0; i < HASH_TABLE_SIZE; i++)
    {
        hashTable[i] = NULL;
    }

    // Initialize hash table with pre-defined symbols
    initializeHashTable(hashTable, HASH_TABLE_SIZE);


    // Execute an entire passthrough of the file to add labels to the symbol table
    addLabelSymbols(inFile, hashTable);


    // Rewind file stream for second pass-through
    fseek(inFile, 0, SEEK_SET);

    // Execute an entire passthrough of the file to add user-defined symbols to the symbol table
    addUserSymbols(inFile, hashTable, HASH_TABLE_SIZE);


    // Rewind file stream for final pass-through (replacement stage)
    fseek(inFile, 0, SEEK_SET);


    printHashTable(hashTable, HASH_TABLE_SIZE);


    replaceSymbols(inFile, outFile, hashTable, HASH_TABLE_SIZE);

    fclose(inFile);
    fclose(outFile);
}

