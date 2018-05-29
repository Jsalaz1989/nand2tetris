/*

Resolves symbols in a Hack assembly program.

Stores predefined symbols, labels, and user symbols in a hash table with their corresponding RAM or instruction address.

*/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "parse.h"
#include "symbolizer.h"


#define HASH_TABLE_SIZE 5


tableNode *hashTable[HASH_TABLE_SIZE];


// Simple hash function returning a string's corresponding hash value between 0 and HASH_TABLE_SIZE
unsigned int hashFunction(char *symbol)
{
    if (symbol != NULL)
    {
        int i;
        int sum = 0;
        unsigned int hashReturn;

        for (i = 0; symbol[i] != '\0'; i++)
            sum = sum + symbol[i];

        return hashReturn = sum % HASH_TABLE_SIZE;
    }

    return 0;
}


// Creates a hash table node and fills it with a symbol and an address
void pushTable(tableNode *head, char *symbol, int address)
{  
    tableNode *current = head;
    
    // Find the end of the list
    while (current->next != NULL)
        current = current->next;

    // Now we can add a new variable
    current->next = malloc(sizeof(tableNode));
    if (current->next == NULL)
        fprintf(stderr, "Could not malloc current->next. \n");
	
	// Copy symbol to new pointer in case old pointer is free'd			
	char *symbol2 = malloc(strlen(symbol)+1);
	symbol2 = strcpy(symbol2, symbol);
    
    // Fill new node with the symbol and address
    current->next->symbol = symbol2;
    current->next->address = address;
    current->next->next = NULL;
}


// Create a hash table to contain symbols and their adddress and fill with predefined symbols
void initializeHashTable(void)
{
    // Ensure all pointers start as null
    int i;
    for (i = 0; i < HASH_TABLE_SIZE; i++)
    {
        hashTable[i] = NULL;
    }

	// Hardcode predefined symbols and their address into hash table
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


        unsigned int hashValue = hashFunction(symbol);
        
        // On first occurence of hash value start a list for that hash value, otherwise push onto existing list
        if (hashTable[hashValue] == NULL)
        {
            // Create a new list of table nodes
            hashTable[hashValue] = malloc(sizeof(tableNode));
		    if (hashTable[hashValue] == NULL)
		        fprintf(stderr, "Could not malloc . \n");

			// Copy symbol to new pointer in case old pointer is free'd			
			char *symbol2 = malloc(strlen(symbol)+1);
			symbol2 = strcpy(symbol2, symbol);
	
	    	// Fill new node with the symbol and address
			hashTable[hashValue]->symbol = symbol2;
		    hashTable[hashValue]->address = address;
		    hashTable[hashValue]->next = NULL;
        }
        else
        {
            pushTable(hashTable[hashValue], symbol, address);
		}
    }
}


// Return true if a hash table contains a symbol, return false if symbol not found
int searchHashTable(char *needle)
{
    unsigned int hashValue = hashFunction(needle);
    tableNode *current = hashTable[hashValue];
   
   	// Iterate through list searching for the symbol
	while (current != NULL)
	{	
		// If symbol is found, return true
	    if (strcmp(current->symbol, needle) == 0)
		   	return 1;
		
        current = current->next;
    }
    
    // Symbol was not found
    return 0;
}


// Search for labels in the program and add them to the hash table with their corresponding instruction number
void addLabelSymbols(void)
{
    // Open spaceless file 
    FILE *spaceLessFile1 = fopen("spaceLess1.txt", "r");
    if (spaceLessFile1 == NULL)
        fprintf(stderr, "Could not open spaceless file 1. \n");


    int instructionNum = 0;		// keeps track of current instruction number

	// Iterate through file searching for labels and assigning its corresponding instruction number
    while (getc(spaceLessFile1) != EOF)
    {
    	fseek(spaceLessFile1, -1, SEEK_CUR);	// undo forward seek of previous getc()
    	
        instrComponents instructionComponents = parse(spaceLessFile1);		// parse current line

        // If line is a label, push it onto hash table with its corresponding instruction number
        if (strlen(instructionComponents.label) != 0)
        {     			  			
    		unsigned int hashValue = hashFunction(instructionComponents.label);
    		pushTable(hashTable[hashValue], instructionComponents.label, instructionNum);
        }
		else
		{
            instructionNum++;
   		}
    }
    
    
    // Close spaceless file
    fclose(spaceLessFile1);
    spaceLessFile1 = NULL;
}


// Search for user-defined symbols in the program and add them to the hash table with their corresponding RAM address
void addUserSymbols(void)
{
    // Open spaceless file 
    FILE *spaceLessFile1 = fopen("spaceLess1.txt", "r");
    if (spaceLessFile1 == NULL)
        fprintf(stderr, "Could not open spaceless file 1. \n");
    
    
    int availableRAMaddress = 16;	// keeps track of current instruction number

	// Iterate through file searching for user-defined symbols and assigning its corresponding RAM address
    while (getc(spaceLessFile1) != EOF)
    {
    	fseek(spaceLessFile1, -1, SEEK_CUR);	// undo forward seek of previous getc()
    	
        instrComponents instructionComponents = parse(spaceLessFile1);		// parse current line
      
        // If line is a user symbol and it is not already in the hash table, push it with its corresponding instruction number
        if (strlen(instructionComponents.userSymbol) != 0)
        {
            if (searchHashTable(instructionComponents.userSymbol) == 0)
            {              
    			unsigned int hashValue = hashFunction(instructionComponents.userSymbol);
    			pushTable(hashTable[hashValue], instructionComponents.userSymbol, availableRAMaddress);

                availableRAMaddress++; 
            }
        }   
    }
    
    
    // Close spaceless file
    fclose(spaceLessFile1);
    spaceLessFile1 = NULL;
}


// Returns the address associated with a symbol
int getSymbolAddress(char needle[])
{
	// Iterate through lists of hash table looking for a symbol
    int i;
    for (i = 0; i < HASH_TABLE_SIZE; i++)
    {
        if (hashTable[i] != NULL)
        {
            tableNode *current = hashTable[i];

            while (current != NULL)
            {
            	// If symbol found, returns its address
                if (strcmp(current->symbol, needle) == 0)
                    return current->address;

                current = current->next;
            }
        }
    }

	// Symbol not found
    return 0;
}


// Copy the program to a new file, substituting every symbol with its address
void replaceSymbols(void)
{
    // Open spaceless file 
    FILE *spaceLessFile1 = fopen("spaceLess1.txt", "r");
    if (spaceLessFile1 == NULL)
        fprintf(stderr, "Could not open symbolLess file 1.\n");
    
    // Open intermediate output file to store symbolLess version
    FILE *symbolLessFile = fopen("symbolLess.txt", "w");
    if (symbolLessFile == NULL)
    {
        fclose(spaceLessFile1);
        fprintf(stderr, "Could not create symbolLess file.\n");
    }
    
	// Iterate through input file while outputting values, the value corresponding to user-defined symbols, and C-instructions
    char currentChar = getc(spaceLessFile1);
    while (currentChar != EOF)
    {
        fseek(spaceLessFile1, -1, SEEK_CUR);	// undo forward seek of previous getc()
        
        instrComponents instructionComponents = parse(spaceLessFile1);		// parse current line


        if (instructionComponents.value >= 0)							// value
        {
        	putc('@', symbolLessFile);
        	fprintf(symbolLessFile, "%i", instructionComponents.value);
        	putc('\n', symbolLessFile);
        }
        else if (strlen(instructionComponents.userSymbol) != 0)			// user symbol
        {
            putc('@', symbolLessFile);

            if (searchHashTable(instructionComponents.userSymbol))
            {
                int address = getSymbolAddress(instructionComponents.userSymbol);
                fprintf(symbolLessFile, "%i", address);
    			putc('\n', symbolLessFile);
            }
        }
		else if (strlen(instructionComponents.comp) != 0)				// C-instruction
        {
		    if (strlen(instructionComponents.dest) != 0)
		   	{
				fprintf(symbolLessFile, "%s", instructionComponents.dest);
				putc('=', symbolLessFile);
			}
			
			fprintf(symbolLessFile, "%s", instructionComponents.comp);  
			
			if (strlen(instructionComponents.jump) != 0)
			{
			    putc(';', symbolLessFile);
			    fprintf(symbolLessFile, "%s", instructionComponents.jump);
			}
			
			putc('\n', symbolLessFile);
		}
		
		
        currentChar = getc(spaceLessFile1);
    }

	
	// Close the spaceless file
	fclose(spaceLessFile1);
	spaceLessFile1 = NULL;
	
	// Close the symboless file
	fclose(symbolLessFile);
	symbolLessFile = NULL;
}


// Free every node in the hash table and the symbols in each node
void freeHashTable(void)
{
    tableNode *current;
    tableNode *temp;
    
    // Iterate over lists in hash table
    int i;
    for (i = 0; i < HASH_TABLE_SIZE; i++)
    {
        if (hashTable[i] != NULL)
        {
            current = hashTable[i];					// start at head of list
            
			while (current->next != NULL)			// loop through list
			{
				temp = current->next;		// save pointer to next node
				
				free(current->symbol);		// free symbol in current node
				current->symbol = NULL;

				free(current);				// free current node
				current = NULL;
				
	        	current = temp;				// move to next node
	        }
	        
			free(current->symbol);			// free symbol of last node
			current->symbol = NULL;
			
			free(current);					// free last node	
			current = NULL;	
        }
    }
}


// Substitutes any symbols with their corresponding RAM address or instruction number
void searchAndDestroySymbols(void)
{  
    // Initialize hash table with predefined symbols
    initializeHashTable();
        
        
    // Execute an entire passthrough of the file to add labels to the symbol table
    addLabelSymbols();


    // Execute an entire passthrough of the file to add user-defined symbols to the symbol table
    addUserSymbols();


	// Substitute symbols with their addresses
    replaceSymbols();


	// Free the hash table nodes (including the string in each node)
	freeHashTable();
}


// Print the contents of the hash table by hash value 
void printHashTable(void)
{
    printf("Symbol\tAddress\tHash\n");
    
    int i;
    for (i = 0; i < HASH_TABLE_SIZE; i++)
    {
		if (hashTable[i] != NULL)
		{
		    tableNode *current = hashTable[i];

		    while (current != NULL)
		    {
		        unsigned int hashReturn = hashFunction(current->symbol);

		        printf("%s\t%i\t%i\n", current->symbol, current->address, hashReturn);

		        current = current->next;
		    }
		}
    }
    
    printf("\n");
}
