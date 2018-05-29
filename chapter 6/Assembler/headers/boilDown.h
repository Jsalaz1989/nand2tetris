// Copies the input file ignoring comments and most white space, but will leave a blank header on top
void eliminateEverythingButHeader(char *inFilename);	


// Eliminates the blank header left behind by eliminateEverythingButHeader() by copying over everything after the first few newlines
void eliminateHeader(void);


// Eliminates all white space and comments from the input file in two stages (first stage leaves a blank header and the second stage removes it)
int eliminateSpacesAndComments(char *inFilename);

