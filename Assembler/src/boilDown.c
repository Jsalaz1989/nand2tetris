/*
    Reduce a Hack assembly program to the commands while eliminating white space and comments.

    Functions boilDowno() and boilDown1() are two stages of the larger function boilDown(), reducing the input file to a blank header
    along with the assembly commands and subsequently eliminating the blank header
*/


#include <stdio.h>


// Copies the input file ignoring comments and most white space, but will leave a blank header on top
void eliminateSpacesAndComments0(FILE *inFile, FILE *outFile)
{
    char currentChar = getc(inFile);

    while (currentChar != EOF)
    {
        // Ignore comments
        if (currentChar == '/')
        {
            while (currentChar != '\n')
            {
                currentChar = getc(inFile);
            }
        }
        // Ignore spaces and tabs
        else if (currentChar == ' ' || currentChar == '\t')
        {
            currentChar = getc(inFile);
        }
        // Copy over all valid characters
        else
        {
            putc(currentChar, outFile);

            currentChar = getc(inFile);
        }
    }
}


// Eliminates the blank header left behind by boilDown1() by copying over everything after the first few newlines
void eliminateSpacesAndComments1(FILE *inFile, FILE *outFile)
{
    char currentChar = getc(inFile);

    int header = 1;     // to check if we have left the header behind

    while (currentChar != EOF)
    {
        // Consider the header over once the first non-newline character is reached
        if (currentChar != '\n')
        {
            header = 0;
        }

        // If no longer in the header, copy remaining characters over
        if (header == 0)
        {
            while (currentChar != EOF)
            {
                putc(currentChar, outFile);

                currentChar = getc(inFile);
            }
        }

        currentChar = getc(inFile);
    }
}


// Eliminates all white space and comments from the input file in two stages (first stage leaves a blank header and the second stage removes it)
int eliminateSpacesAndComments(FILE *inFile)
{
    // Open intermediate file to store spaceLess version, will retain a blank header
    FILE *spaceLessFile0 = fopen("spaceLess0.txt", "w");
    if (spaceLessFile0 == NULL)
    {
        fclose(inFile);
        fprintf(stderr, "Could not create spaceLess file 0.\n");
        return 3;
    }

    // Remove white space and comments but leave a blank header
    eliminateSpacesAndComments0(inFile, spaceLessFile0);

    fclose(inFile);
    fclose(spaceLessFile0);


    // Open previous file, but in read mode, so a new spaceLess version can be created without the blank header
    spaceLessFile0 = fopen("spaceLess0.txt", "r");

    FILE *spaceLessFile1 = fopen("spaceLess1.txt", "w");
    if (spaceLessFile1 == NULL)
    {
        fclose(spaceLessFile0);
        fprintf(stderr, "Could not create spaceLess file 1.\n");
        return 3;
    }

    // Remove the blank header
    eliminateSpacesAndComments1(spaceLessFile0, spaceLessFile1);

    fclose(spaceLessFile0);
    fclose(spaceLessFile1);

    return 0;
}