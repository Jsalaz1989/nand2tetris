/*
    Parses a line from an input file containing a Hack assembly program (Example.asm) into its underlying fields.
    If it receives an A-instruction, it extracts its numerical value.
    If it recieves a C-instruction, it parses it into one, two, or three components: [dest=]comp;[jump]
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structs.h"
#include "functions.h"
#include "printFunctions.h"




infoStruct parse(FILE *inFile)
{
    int commandLength = 0;

    fseek(inFile, -1, SEEK_CUR);


    while (getc(inFile) != '\n')
    {
        commandLength++;
    }

    //printf("commandLength = %i \n", commandLength);


    fseek(inFile, -commandLength-1, SEEK_CUR);



    char* command = NULL;
    command = malloc(commandLength+1);
    if (command == NULL)
        printf("Failed to allocate \n");

    int i;
    for (i = 0; i <= commandLength-1; i++)
    {
        command[i] = getc(inFile);
        //printf("command[%i] = %c \n", i, command[i]);

        if (command[i] == '\n')
            command[i] = '\0';
    }

    fseek(inFile, 1, SEEK_CUR);

    int instructionType;

    if (strchr(command, '@') != NULL)
        instructionType = 0;
    else if (strchr(command, '(') != NULL)
        instructionType = 1;
    else
        instructionType = 2;

    //printf("instructionType = %i \n", instructionType);

    int destLength = 0;
    int compLength = 0;
    int jumpLength = 0;

    char *value = NULL;
    char *userSymbol = NULL;
    char *label = NULL;


    int equalSignPos = 0;
    int semiColonPos = 0;

    if (instructionType == 0)
    {
        if (command[1] >= '0' && command[1] <= '9')
        {
            value = malloc(strlen(command));

            for (i = 0; i < strlen(command)-1; i++)
            {
                value[i] = command[i+1];
            }
            value[strlen(command)-1] = '\0';

            //printf("value = %s \n", value);
            //printf("strlen = %lu \n", strlen(value));
        }
        else
        {
            userSymbol = malloc(strlen(command));

            for (i = 0; i < strlen(command)-1; i++)
            {
                userSymbol[i] = command[i+1];
            }
            userSymbol[strlen(command)-1] = '\0';

            //printf("userSymbol = %s \n", userSymbol);
            //printf("strlen = %lu \n", strlen(userSymbol));
        }
    }
    else if (instructionType == 1)
    {
        label = malloc(strlen(command)-1);

        for (i = 0; i < strlen(command)-2; i++)
        {
            label[i] = command[i+1];
        }
        label[strlen(command)-1] = '\0';

        //printf("label = %s \n", label);
    }
    else if (instructionType == 2)
    {
        for (i = 0; i < strlen(command); i++)
        {
            if (command[i] == '=')
            {
                equalSignPos = i;
                destLength = equalSignPos;
                //printf("equalSignPos = %i \n", equalSignPos);
            }

            if (command[i] == ';')
            {
                semiColonPos = i;
                jumpLength = strlen(command) - semiColonPos - 1;
                //printf("semiColonPos = %i \n", semiColonPos);
            }
        }

        //printf("destLength = %i \n", destLength);
        //printf("jumpLength = %i \n", jumpLength);



        if (destLength != 0)
        {
            if (jumpLength != 0)
            {
                compLength = strlen(command) - destLength - jumpLength - 2;
            }
            else if (jumpLength == 0)
            {
                compLength = strlen(command) - destLength - 1;
            }
        }
        else if (destLength == 0)
        {
            if (jumpLength != 0)
            {
                compLength = strlen(command) - jumpLength - 1;
            }
            else if (jumpLength == 0)
            {
                compLength = strlen(command);
            }
        }
    }


    char dest[destLength+1];
    char comp[compLength+1];
    char jump[jumpLength+1];

    if (destLength != 0)
    {
        for (i = 0; i < destLength; i++)
        {
            dest[i] = command[i];
        }
        dest[destLength] = '\0';

        for (i = 0; i < compLength; i++)
        {
            comp[i] = command[equalSignPos+1+i];
        }
    }
    else if (destLength == 0)
    {
        dest[0] = '\0';

        for (i = 0; i < compLength; i++)
        {
            comp[i] = command[equalSignPos+i];
        }
    }
    comp[compLength] = '\0';


    for (i = 0; i < jumpLength; i++)
    {
        jump[i] = command[semiColonPos+1+i];
    }
    jump[jumpLength] = '\0';

    //printf("dest = %s \n", dest);


    infoStruct solutions;
    solutions.instructionType = instructionType;
    solutions.value = value;
    solutions.userSymbol = userSymbol;
    solutions.label = label;
    solutions.dest = dest;
    solutions.comp = comp;
    solutions.jump = jump;



    return solutions;
}
