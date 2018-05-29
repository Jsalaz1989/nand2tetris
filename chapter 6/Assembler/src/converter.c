/*

Converts an assembly command into binary.

If it receives an A-instruction, it converts the numerical value into a 16-bit binary number.
If it receives a C-instruction, it converts the comp command and then, optionally, the dest and/or jump commands.

*/



#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "parse.h"
#include "converter.h"


// A-instructions are converted from an int to a 16-bit binary number
int *convertAinstruction(int value)
{
	// Set the 16-bit number to all 9's
    static int binInstruction[16];      
    int i;
    for (i = 0; i < 16; i++)
    	binInstruction[i] = 9;
    

    // A-instructions always start with a 0
    binInstruction[0] = 0;


    // Convert the numerical value into 16-bit binary form
    for (i = 1; i < 16; i++)
    {
        int bitPlace = pow(2,15-i);                 // 18384, 8192, 4096, ..., 16, 8, 4, 2, 1
        int rem = value - bitPlace;

        if (rem >= 0)
        {
            binInstruction[i] = 1;
            value = rem;
        }
        else
        {
            binInstruction[i] = 0;
        }
    }


    return binInstruction;
}



// C-instructions are converted by parts: first comp and then, optionally, dest and/or jump
int *convertCinstruction(char *dest, char *comp, char *jump)
{
    // Set the 16-bit number to all 9's
    static int binInstruction[16];      
    int i;
    for (i = 0; i < 16; i++)
    	binInstruction[i] = 9;
   

    //C-instructions consist of [dest=]comp[;jump] = 1 1 1 a c1 c2 c3 c4 c5 c6 d1 d2 d3 j1 j2 j3, where dest and jump are optional
    binInstruction[0] = 1;
    binInstruction[1] = 1;
    binInstruction[2] = 1;
    

    // In comp command, bit "a" depends on whether comp contains "M" (a = 1) or "A" (a = 0)
    if (strchr(comp, 'M') != NULL)
        binInstruction[3] = 1;
    else
        binInstruction[3] = 0;


    // Compare comp to each possible string
    if (strcmp(comp, "0") == 0)
    {
        binInstruction[4] = 1;
        binInstruction[5] = 0;
        binInstruction[6] = 1;
        binInstruction[7] = 0;
        binInstruction[8] = 1;
        binInstruction[9] = 0;
    }
    else if (strcmp(comp, "1") == 0)
    {
        binInstruction[4] = 1;
        binInstruction[5] = 1;
        binInstruction[6] = 1;
        binInstruction[7] = 1;
        binInstruction[8] = 1;
        binInstruction[9] = 1;
    }
    else if (strcmp(comp, "D") == 0)
    {
        binInstruction[4] = 0;
        binInstruction[5] = 0;
        binInstruction[6] = 1;
        binInstruction[7] = 1;
        binInstruction[8] = 0;
        binInstruction[9] = 0;
    }
    else if (strcmp(comp, "A") == 0 || strcmp(comp, "M") == 0)
    {
        binInstruction[4] = 1;
        binInstruction[5] = 1;
        binInstruction[6] = 0;
        binInstruction[7] = 0;
        binInstruction[8] = 0;
        binInstruction[9] = 0;
    }
    else if (strcmp(comp, "-1") == 0)
    {
        binInstruction[4] = 1;
        binInstruction[5] = 1;
        binInstruction[6] = 1;
        binInstruction[7] = 0;
        binInstruction[8] = 1;
        binInstruction[9] = 0;
    }
    else if (strcmp(comp, "!D") == 0)
    {
        binInstruction[4] = 0;
        binInstruction[5] = 0;
        binInstruction[6] = 1;
        binInstruction[7] = 1;
        binInstruction[8] = 0;
        binInstruction[9] = 1;
    }
    else if (strcmp(comp, "!A") == 0 || strcmp(comp, "!M") == 0)
    {
        binInstruction[4] = 1;
        binInstruction[5] = 1;
        binInstruction[6] = 0;
        binInstruction[7] = 0;
        binInstruction[8] = 0;
        binInstruction[9] = 1;
    }
    else if (strcmp(comp, "-D") == 0)
    {
        binInstruction[4] = 0;
        binInstruction[5] = 0;
        binInstruction[6] = 1;
        binInstruction[7] = 1;
        binInstruction[8] = 1;
        binInstruction[9] = 1;
    }
    else if (strcmp(comp, "-A") == 0 || strcmp(comp, "-M") == 0)
    {
        binInstruction[4] = 1;
        binInstruction[5] = 1;
        binInstruction[6] = 0;
        binInstruction[7] = 0;
        binInstruction[8] = 1;
        binInstruction[9] = 1;
    }
    else if (strcmp(comp, "D+1") == 0)
    {
        binInstruction[4] = 0;
        binInstruction[5] = 1;
        binInstruction[6] = 1;
        binInstruction[7] = 1;
        binInstruction[8] = 1;
        binInstruction[9] = 1;
    }
    else if (strcmp(comp, "A+1") == 0 || strcmp(comp, "M+1") == 0)
    {
        binInstruction[4] = 1;
        binInstruction[5] = 1;
        binInstruction[6] = 0;
        binInstruction[7] = 1;
        binInstruction[8] = 1;
        binInstruction[9] = 1;
    }
    else if (strcmp(comp, "D-1") == 0)
    {
        binInstruction[4] = 0;
        binInstruction[5] = 0;
        binInstruction[6] = 1;
        binInstruction[7] = 1;
        binInstruction[8] = 1;
        binInstruction[9] = 0;
    }
    else if (strcmp(comp, "A-1") == 0 || strcmp(comp, "M-1") == 0)
    {
        binInstruction[4] = 1;
        binInstruction[5] = 1;
        binInstruction[6] = 0;
        binInstruction[7] = 0;
        binInstruction[8] = 1;
        binInstruction[9] = 0;
    }
    else if (strcmp(comp, "D+A") == 0 || strcmp(comp, "D+M") == 0)
    {
        binInstruction[4] = 0;
        binInstruction[5] = 0;
        binInstruction[6] = 0;
        binInstruction[7] = 0;
        binInstruction[8] = 1;
        binInstruction[9] = 0;
    }
    else if (strcmp(comp, "D-A") == 0 || strcmp(comp, "D-M") == 0)
    {
        binInstruction[4] = 0;
        binInstruction[5] = 1;
        binInstruction[6] = 0;
        binInstruction[7] = 0;
        binInstruction[8] = 1;
        binInstruction[9] = 1;
    }
    else if (strcmp(comp, "A-D") == 0 || strcmp(comp, "M-D") == 0)
    {
        binInstruction[4] = 0;
        binInstruction[5] = 0;
        binInstruction[6] = 0;
        binInstruction[7] = 1;
        binInstruction[8] = 1;
        binInstruction[9] = 1;
    }
    else if (strchr(comp, '&') != NULL)
    {
        binInstruction[4] = 0;
        binInstruction[5] = 0;
        binInstruction[6] = 0;
        binInstruction[7] = 0;
        binInstruction[8] = 0;
        binInstruction[9] = 0;
    }
    else if (strchr(comp, '|') != NULL)
    {
        binInstruction[4] = 0;
        binInstruction[5] = 1;
        binInstruction[6] = 0;
        binInstruction[7] = 1;
        binInstruction[8] = 0;
        binInstruction[9] = 1;
    }
    

    // If the dest command doesn't exist, d1 d2 d3 = 000
    if (dest == NULL)
    {
        binInstruction[10] = 0;
        binInstruction[11] = 0;
        binInstruction[12] = 0;
    }
    // If the dest command exists, place a 1 in each bit corresponding to the chosen destination, ie, d1 d2 d3 = A D M
    else
    {
        if (strchr(dest, 'A') != NULL)
            binInstruction[10] = 1;
        else
            binInstruction[10] = 0;

        if (strchr(dest, 'D') != NULL)
            binInstruction[11] = 1;
        else
            binInstruction[11] = 0;

        if (strchr(dest, 'M') != NULL)
            binInstruction[12] = 1;
        else
            binInstruction[12] = 0;
    }


    // If the jump command doesn't exist, j1 j2 j3 = 0 0 0
    if (strlen(jump) == 0)
    {
        binInstruction[13] = 0;
        binInstruction[14] = 0;
        binInstruction[15] = 0;
    }
    // If the jump command exists, search each case to determine the command: "JGT", "JEQ", "JGE", "JLT", "JNE", "JLE", or "JMP"
    else
    {
        if (!strcmp(jump, "JGT"))
        {
            binInstruction[13] = 0;
            binInstruction[14] = 0;
            binInstruction[15] = 1;
        }
        else if (!strcmp(jump, "JEQ"))
        {
            binInstruction[13] = 0;
            binInstruction[14] = 1;
            binInstruction[15] = 0;
        }
        else if (!strcmp(jump, "JGE"))
        {
            binInstruction[13] = 0;
            binInstruction[14] = 1;
            binInstruction[15] = 1;
        }
        else if (!strcmp(jump, "JLT"))
        {
            binInstruction[13] = 1;
            binInstruction[14] = 0;
            binInstruction[15] = 0;
        }
        else if (!strcmp(jump, "JNE"))
        {
            binInstruction[13] = 1;
            binInstruction[14] = 0;
            binInstruction[15] = 1;
        }
        else if (!strcmp(jump, "JLE"))
        {
            binInstruction[13] = 1;
            binInstruction[14] = 1;
            binInstruction[15] = 0;
        }
        else if (!strcmp(jump, "JMP"))
        {
            binInstruction[13] = 1;
            binInstruction[14] = 1;
            binInstruction[15] = 1;
        }
    }
  

    return binInstruction;
}


// Convert A- and C-instructions and output them to a file
void convertToBinary(char *inFilename)
{
	// Open symbolless file
    FILE *symbolLessFile = fopen("symbolLess.txt", "r");
    if (symbolLessFile == NULL)
        fprintf(stderr, "Could not create symbolLess file.\n");
    
    
    // Prepare output file name
    int length = strlen(inFilename);
    char outFilename[length+2];         // +1 because ".asm" to ".hack" but +2 to include null terminator
    
    int i;
    for (i = 0; i < length; i++)
    {
        if (inFilename[i] == '.')
        {
            outFilename[i] = inFilename[i];
            outFilename[i+1] = 'h';
            outFilename[i+2] = 'a';
            outFilename[i+3] = 'c';
            outFilename[i+4] = 'k';
            outFilename[i+5] = '\0';
            break;
        }
        else
        {
            outFilename[i] = inFilename[i];
        }
    }
    
    // Open output file
    FILE *outFile = fopen(outFilename, "w");
    if (outFile == NULL)
    {
        fclose(symbolLessFile);
        fprintf(stderr, "Could not create output file.\n");
        //return 3;
    }
    
   
    // Loop through the input file's lines until EOF
    while (getc(symbolLessFile) != EOF)
    {
        fseek(symbolLessFile, -1, SEEK_CUR);         // undo forward seek of previous getc()
        

        instrComponents instructionComponents = parse(symbolLessFile);		// parse current line
        
		if (instructionComponents.value >=0 || strlen(instructionComponents.comp) != 0)
		{
		    int *binaryNumber = NULL;

		    if (instructionComponents.value >= 0)									// A-instruction
		        binaryNumber = convertAinstruction(instructionComponents.value);
		    else if (strlen(instructionComponents.comp) != 0)						// C-instruction
		        binaryNumber = convertCinstruction(instructionComponents.dest, instructionComponents.comp, instructionComponents.jump);
		    
		    printBinaryInstruction(binaryNumber);
		    
			if (binaryNumber[4] != 9)
			{
				// Write to output file
				for (i = 0; i <= 15; i++)
				    fprintf(outFile, "%i", binaryNumber[i]);


				putc('\r', outFile);   // carriage return before \n for Windows Notepad
				putc('\n', outFile);
			}
		}
    }


	// Closse the symbolless file	
	fclose(symbolLessFile);
	symbolLessFile = NULL;
	
	// Close the output file
	fclose(outFile);
	outFile = NULL;
}


// Print a 16-bit binary number
void printBinaryInstruction(int binInstruction[])
{
    printf("binInstruction = ");
    int i;
    for(i = 0; i<=15; i++)
    {
        printf("%i", binInstruction[i]);
    }
    printf("\n");
}


