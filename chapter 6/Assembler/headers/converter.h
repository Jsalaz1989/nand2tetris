// A-instructions are converted from an int to a 16-bit binary number
int *convertAinstruction(int value);


// C-instructions are converted by parts: first comp and then, optionally, dest and/or jump
int *convertCinstruction(char *dest, char *comp, char *jump);


// Convert A- and C-instructions and output them to a file
void convertToBinary(char *outFilename);


// Print a 16-bit binary number
void printBinaryInstruction(int binInstruction[]);
