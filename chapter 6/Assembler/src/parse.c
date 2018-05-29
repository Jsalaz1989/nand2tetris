/*

Parses a line from an input file containing a Hack assembly program (Example.asm) into its underlying fields.

If it receives an A-instruction, it extracts its numerical value.
If it recieves a C-instruction, it parses it into one, two, or three components: [dest=]comp;[jump]

*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "list.h"
#include "parse.h"


// Determine the instruction type and related info
instrTypeInfo getInstructionType(char *line)
{
	int instructionType = 9;	// 0 = A-instruction, 1 = label, 2 = C-instruction
	int valuePresent = 0;
	int userSymbolPresent = 0;
	int destPresent = 0;
	int jumpPresent = 0;
	
	// Determine whether A-instruction (value or user symbol), label, or C-instruction (and whether it contains a dest and/or jump command)
	if (strchr(line, '@') != NULL)			// A-instruction
	{
		instructionType = 0;
	
		if (isdigit(line[1]))
			valuePresent = 1;				// value
		else
			userSymbolPresent = 1;			// user symbol
	}			
	else if (strchr(line, '(') != NULL)		// label
	{
		instructionType = 1;
	}
	else									// C-instruction
	{
		instructionType = 2;
		
		if (strchr(line, '=') != NULL)
			destPresent = 1;				// dest
	
		if (strchr(line, ';') != NULL)
			jumpPresent = 1;				// jump
	}
	
	
	// Return struct containing results	
	instrTypeInfo instructionInfo;
	instructionInfo.instructionType = instructionType;
	instructionInfo.valuePresent = valuePresent;
	instructionInfo.userSymbolPresent = userSymbolPresent;
	instructionInfo.destPresent = destPresent;
	instructionInfo.jumpPresent = jumpPresent;
	
	return instructionInfo;
}	


// Determine instruction components: value, user symbol, label, dest, comp, or jump commands
instrComponents getInstructionComponents (char *line, instrTypeInfo instructionInfo)
{
	instrComponents instructionComponents;
	instructionComponents.value = -1;
	instructionComponents.userSymbol[0] = '\0';
   	instructionComponents.label[0] = '\0';
   	instructionComponents.dest[0] = '\0';
	instructionComponents.comp[0] = '\0';
	instructionComponents.jump[0] = '\0';


	if (instructionInfo.instructionType == 0)
    {
        if (instructionInfo.valuePresent == 1)
        	sscanf(line, "@%i", &instructionComponents.value);
        
        if (instructionInfo.userSymbolPresent == 1)  		
    		sscanf(line, "@%s", instructionComponents.userSymbol);  
    }
    else if (instructionInfo.instructionType == 1)
    {    	
    	sscanf(line, "(%[^()])", instructionComponents.label);
    }
    else if (instructionInfo.instructionType == 2)
    {	
		if (instructionInfo.destPresent == 1 && instructionInfo.jumpPresent == 1)
			sscanf(line, "%[^=]=%[^;];%s", instructionComponents.dest, instructionComponents.comp, instructionComponents.jump); 
		else if (instructionInfo.destPresent == 1 && instructionInfo.jumpPresent == 0)
			sscanf(line, "%[^=]=%s", instructionComponents.dest, instructionComponents.comp);
		else if (instructionInfo.destPresent == 0 && instructionInfo.jumpPresent == 1)
			sscanf(line, "%[^;];%s", instructionComponents.comp, instructionComponents.jump);
		else if (instructionInfo.destPresent == 0 && instructionInfo.jumpPresent == 0)
			sscanf(line, "%s", instructionComponents.comp);
	}
	
		
	return instructionComponents;
}


// Parse the current line in the input file into the instruction components
instrComponents parse(FILE *inFile)
{
	// Create linked list to contain current line
	listNode *line = NULL;
	line = malloc(sizeof(listNode));
	if (line == NULL)
        fprintf(stderr, "Could not malloc line. \n");
	
	// Start list with the first character in the file
	char currentChar = getc(inFile);
	line->val = currentChar;
	line->next = NULL;

	// Fill list with characters until end of line
	while (currentChar != '\n')
	{
		currentChar = getc(inFile);
		
		if (currentChar != '\n')
			pushList(line, currentChar);			
	}


	// Convert linked list to string
	char *lineString = listToString(line);
	freeList(line);
	line = NULL;
	
	// Obtain instruction info from string
	instrTypeInfo instructionInfo = getInstructionType(lineString);

	// Obtain and return instruction components
	instrComponents instructionComponents = getInstructionComponents(lineString, instructionInfo);
	free(lineString);
	lineString = NULL;

    return instructionComponents;
}


// Print the instructiont type and whether value, user symbol, dest, and/or jump command present 
void printInstructionInfo(instrTypeInfo instructionInfo)
{
	printf("instructionType = %i \n", instructionInfo.instructionType);
	
	if (instructionInfo.instructionType == 0)					// if A-instruction, print whether value or user symbol present
	{
		if (instructionInfo.valuePresent == 1)
			printf("valuePresent = %i \n", instructionInfo.valuePresent);
	
		if (instructionInfo.userSymbolPresent == 1)
			printf("userSymbolPresent = %i \n", instructionInfo.userSymbolPresent);
	}		
	else if (instructionInfo.instructionType == 2)				// if C-instruction, print whether dest and/or jump present
	{
		if (instructionInfo.destPresent == 1)
			printf("destPresent = %i \n", instructionInfo.destPresent);
			
		if (instructionInfo.jumpPresent == 1)
			printf("jumpPresent = %i \n", instructionInfo.jumpPresent);
	}
}


// Print instruction components: value, user symbol, label, dest, comp, or jump commands
void printInstructionComponents(instrTypeInfo instructionTypeInfo, instrComponents instructionComponents)
{
	int i = 0;

    if (instructionTypeInfo.instructionType == 0)						// A-instruction
    {
		if (instructionTypeInfo.valuePresent == 1)		
		{			
			printf("value = %i \n", instructionComponents.value);
		}	
		else if (instructionTypeInfo.userSymbolPresent == 1)
		{
			printf("userSymbol = %s \n", instructionComponents.userSymbol);
			
    		for (i = 0; i < strlen(instructionComponents.userSymbol); i++)
				printf("userSymbol[%i] = %c \n", i, instructionComponents.userSymbol[i]);
	
        	printf("strlen(userSymbol) = %lu \n", strlen(instructionComponents.userSymbol));
	    }
    }  
    else if (instructionTypeInfo.instructionType == 1)					// label
    {
        printf("label = %s \n", instructionComponents.label);
        
        for (i = 0; i < strlen(instructionComponents.label); i++)
		    printf("label[%i] = %c \n", i, instructionComponents.label[i]);
    
        printf("strlen(label) = %lu \n", strlen(instructionComponents.label));
    }
    else if (instructionTypeInfo.instructionType == 2)					// C-instruction
    {
        if (instructionTypeInfo.destPresent == 1)
        {
        	printf("dest = %s \n", instructionComponents.dest);
            
            for (i = 0; i <= strlen(instructionComponents.dest); i++)    
            	printf("dest[%i] = %c \n", i, instructionComponents.dest[i]);

            printf("strlen(dest) = %lu \n", strlen(instructionComponents.dest));
        }
	
        printf("comp = %s \n", instructionComponents.comp);	
	
        for (i = 0; i <= strlen(instructionComponents.comp); i++)
	    	printf("comp[%i] = %c \n", i, instructionComponents.comp[i]);

        printf("strlen(comp) = %lu \n", strlen(instructionComponents.comp));

        if (instructionTypeInfo.jumpPresent == 1)
        {
            printf("jump = %s \n", instructionComponents.jump);
            
            for (i = 0; i <= strlen(instructionComponents.jump); i++)
	       		printf("jump[%i] = %c \n", i, instructionComponents.jump[i]);
           
            printf("strlen(jump) = %lu \n", strlen(instructionComponents.jump));
        }
    }

    printf("\n");
}
