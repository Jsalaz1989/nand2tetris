/*

Reduce a Hack assembly program to only the commands by eliminating white space and comments.

The two functions that make up eliminateSpacesAndComments() first reduce the input file to a blank header along with the assembly commands and subsequently eliminate the blank header. I was not able to do it in a just one passthrough :/

*/


#include <stdio.h>


// Copies the input file ignoring comments and most white space, but will leave a blank header on top
void eliminateEverythingButHeader(char *inFilename)
{
    // Open input file
    FILE *inFile = fopen(inFilename, "r");
    if (inFile == NULL)
        fprintf(stderr, "Could not open %s. \n", inFilename);
    
    // Open intermediate file to store spaceLess version, will retain a blank header
    FILE *spaceLessFile0 = fopen("spaceLess0.txt", "w");
    if (spaceLessFile0 == NULL)
    {
        fclose(inFile);
        inFile = NULL;
        fprintf(stderr, "Could not open spaceLess file 0. \n");
    }
    
    
    // Copy input file to spaceless file 0 without comments or spaces
    char currentChar = getc(inFile);
    while (currentChar != EOF)
    {   
        if (currentChar == '/')					        			// ignore comments
        {
            while (currentChar != '\n')
        	    currentChar = getc(inFile);
        }
        else if (currentChar == ' ' || currentChar == '\t')	        // ignore spaces and tabs
        {
            currentChar = getc(inFile);
        }
        else														// copy over all valid characters
        {
            putc(currentChar, spaceLessFile0);

            currentChar = getc(inFile);
        }
    }
    
    
    // Close input file
    fclose(inFile);
    inFile = NULL;
    
    // Close space less file 0
    fclose(spaceLessFile0);
    spaceLessFile0 = NULL;
}


// Eliminates the blank header left behind by boilDown1() by copying over everything after the first few newlines
void eliminateHeader(void)
{
    // Open previous file, but in read mode, so a new spaceLess version can be created without the blank header
    FILE *spaceLessFile0 = fopen("spaceLess0.txt", "r");
    if (spaceLessFile0 == NULL)
        fprintf(stderr, "Could not create spaceLess file 0. \n");

    FILE *spaceLessFile1 = fopen("spaceLess1.txt", "w");
    if (spaceLessFile1 == NULL)
    {
        fclose(spaceLessFile0);
        spaceLessFile0 = NULL;
        fprintf(stderr, "Could not create spaceLess file 1. \n");
    }

    
    int header = 1;     // to check if we have left the header behind

    // Copy spaceless file 0 to spaceless file 1 without the blank header
    char currentChar = getc(spaceLessFile0);
    while (currentChar != EOF)
    {
        // Consider the header over once the first non-newline character is reached
        if (currentChar != '\n')
            header = 0;


        // If no longer in the header, copy remaining characters over
        if (header == 0)
        {
            while (currentChar != EOF)
            {         
                putc(currentChar, spaceLessFile1);

                currentChar = getc(spaceLessFile0);
            }
        }

        currentChar = getc(spaceLessFile0);
    }
    
    
    // Close spaceless file 0
    fclose(spaceLessFile0);
    spaceLessFile0 = NULL;
    
    // Close spacelss file 1
    fclose(spaceLessFile1);
    spaceLessFile1 = NULL;
}


// Eliminates all white space and comments from the input file in two stages (first stage leaves a blank header and the second stage removes it)
int eliminateSpacesAndComments(char *inFilename)
{
    // Remove white space and comments but leave a blank header
    eliminateEverythingButHeader(inFilename);

    
    // Remove the blank header
    eliminateHeader();


    return 0;
}

