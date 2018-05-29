/*

Converts a program in the Hack assembly language into binary instructions.

First eliminates all the spaces and comments, then resolves the symbols, and finally converts to binary.
	
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "boilDown.h"
#include "parse.h"
#include "converter.h"
#include "symbolizer.h"



int main(int argc, char *argv[])
{
    // Check for correct number of args
    if (argc != 2)
    {
        printf("Usage: Assembler Prog.asm\n");
        return 1;
    }


    // Eliminate white spaces and comments from the input file
    eliminateSpacesAndComments(argv[1]);


	// Resolve symbols
	searchAndDestroySymbols();


	// Convert to binary
    convertToBinary(argv[1]);


    return 0;
}

