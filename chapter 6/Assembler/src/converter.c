/*
    Converts an assembly command into binary.
    If it receives an A-instruction, it converts the numerical value into a 16-bit binary number.
    If it receives a C-instruction, it converts the comp command and then, optionally, the dest and/or jump commands.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "structs.h"
#include "functions.h"
#include "parse.h"
#include "printFunctions.h"

/*
    A-instructions are converted first from separate characters to an int
    and then the int is converted into binary
    */
int *convertAinstruction(char value[])
{
    static int binInstruction[16];      // will contain the 16-bit word (the instruction)


    // A-instructions always start with a 0
    binInstruction[0] = 0;

    int intValue = atoi(value);


    // Convert the numerical value into 16-bit binary form
    int i;
    for (i = 1; i <= 15; i++)
    {
        int bitPlace = pow(2,15-i);                 // Eg. 18384, 8192, 4096, ..., 16, 8, 4, 2, 1
        //printf("bitPlace = %i\n", bitPlace);
        int rem = intValue - bitPlace;

        if (rem >= 0)
        {
            binInstruction[i] = 1;
            intValue = rem;
        }
        else
        {
            binInstruction[i] = 0;
        }
    }

    return binInstruction;

}


int *convertCinstruction(char dest[], char comp[], char jump[])
{
    static int binInstruction[16];      // will contain the 16-bit word (the instruction)


    /*
    C-instructions consist of [dest=]comp[;jump] = 1 1 1 a c1 c2 c3 c4 c5 c6 d1 d2 d3 j1 j2 j3, where dest and jump are optional
    The comp command is categorized by its length (1, 2, or 3) and each case is searched for certain characters
    The dest command
    */
    // C-instructions always start with three 1's
    binInstruction[0] = 1;
    binInstruction[1] = 1;
    binInstruction[2] = 1;

    /*
    Convert comp command
    Starting with bit "a" (binInstruction[3])
    Then "c1" (binInstruction[4]) through "c6" (binInstruction[9])
    */

    // Bit "a" depends on whether comp contains "M" (a = 1) or "A" (a = 0)
    //if (searchList(solutions.headC1, 'M'))
    if (strlen(comp) != 0 && strchr(comp, 'M') != NULL)
        binInstruction[3] = 1;
    else
        binInstruction[3] = 0;



    if (strlen(comp) != 0)
    {
        // Compare the comp list to each possible string
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
    }


    /*
    Convert the dest command (if it exists)
    */

    // If the dest command doesn't exist, d1 d2 d3 = 000
    if (strlen(dest) == 0)
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


    // If the jump command doesn't exist, j1 j2 j3 = 000
    if (strlen(jump) == 0)
    {
        binInstruction[13] = 0;
        binInstruction[14] = 0;
        binInstruction[15] = 0;
    }
    // If the jump command exists, search each case to determine the command: "JGT", "JEQ", "JGE", "JLT", "JNE", "JLE", or "JMP"
    else
    {

        if (jump !=NULL)
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
    }


    return binInstruction;
}



void convertToBinary(FILE *inFile, FILE *outFile)
{
    rewind(inFile);

    // Loop through the input file's lines until EOF
    while (getc(inFile) != EOF)
    {
        //fseek(inFile, -1, SEEK_CUR);         // undo forward seek of previous getc()

        // Parse instruction
        infoStruct solutions = parse(inFile);
        printFields(solutions);


        int *binarySolutions = NULL;
        // Convert to binary depending on whether A- or C-instruction
        if (solutions.instructionType == 0)
        {
            binarySolutions = convertAinstruction(solutions.value);
        }
        else if (solutions.instructionType == 2)
        {
            binarySolutions = convertCinstruction(solutions.dest, solutions.comp, solutions.jump);
        }
        //printBinaryInstruction(binarySolutions);


        // Write to output file
        int i;
        for (i = 0; i <= 15; i++)
        {
            printf("%d", binarySolutions[i]);
            fprintf(outFile, "%d", binarySolutions[i]);
        }
        printf("\n\n");

        putc('\r', outFile);   // carriage return before \n for Windows Notepad
        putc('\n', outFile);
    }
}