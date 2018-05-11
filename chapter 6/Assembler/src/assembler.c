#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "boilDown.h"

#include "structs.h"
#include "functions.h"
#include "parse.h"
#include "printFunctions.h"
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

    // Open input file
    char *inFilename = argv[1];
    FILE *inFile = fopen(inFilename, "r");
    if (inFile == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", inFilename);
        return 2;
    }


    // Eliminate white spaces and comments from the input file
    eliminateSpacesAndComments(inFile);



    // Open intermediate output file to store symbolLess version
    FILE *spaceLessFile1 = fopen("spaceLess1.txt", "r");
    if (spaceLessFile1 == NULL)
    {
        //fclose(inFile);
        fprintf(stderr, "Could not open symbolLess file 1.\n");
        return 3;
    }

    // Open intermediate output file to store symbolLess version
    FILE *symbolLessFile = fopen("symbolLess.txt", "w");
    if (symbolLessFile == NULL)
    {
        //fclose(inFile);
        fprintf(stderr, "Could not create symbolLess file.\n");
        return 3;
    }

    FILE *testFile = fopen("test.txt", "r");
    if (testFile == NULL)
    {
        fprintf(stderr, "Could not open test file.\n");
        return 3;
    }


    searchAndDestroySymbols(spaceLessFile1, symbolLessFile);



    symbolLessFile = fopen("symbolLess.txt", "r");


    // Prepare output file name
    int length = strlen(argv[1]);
    char outFilename[length+2];         // +1 because ".asm" to ".hack" but +2 to include null terminator
    int k;
    for (k = 0; k < length; k++)
    {
        if (argv[1][k] == '.')
        {
            outFilename[k] = argv[1][k];
            outFilename[k+1] = 'h';
            outFilename[k+2] = 'a';
            outFilename[k+3] = 'c';
            outFilename[k+4] = 'k';
            outFilename[k+5] = '\0';
            break;
        }
        else
        {
            outFilename[k] = argv[1][k];
        }
    }

    // Open output file
    FILE *outFile = fopen(outFilename, "w");
    if (outFile == NULL)
    {
        fclose(symbolLessFile);
        fprintf(stderr, "Could not create output file.\n");
        return 3;
    }



    convertToBinary(symbolLessFile, outFile);




    // close infile
    fclose(symbolLessFile);

    // close outfile
    fclose(outFile);


    return 0;
}
