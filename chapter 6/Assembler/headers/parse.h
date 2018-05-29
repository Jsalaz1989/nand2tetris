// Contains the instruction type and related info
typedef struct instructionTypeInfo 
{
	int instructionType;
	int valuePresent;
	int userSymbolPresent;
	int destPresent;
	int jumpPresent;
} 
instrTypeInfo;


// Contains the instruction's components
typedef struct instructionComponents
{
	int value;
	//char *userSymbol;
	//char *label;
	//char *dest;
	//char *comp;
	//char *jump;
	char userSymbol[20];
	char label[20];
	char dest[10];
	char comp[10];
	char jump[10];
} 
instrComponents;


// Determine the instruction type and related info
instrTypeInfo getInstructionType(char *line);


int indexInString(char *str, char needle);


// Determine instruction components: value, user symbol, label, dest, comp, or jump commands
instrComponents getInstructionComponents (char *line, instrTypeInfo instructionInfo);


// Parse the current line in the input file into the instruction components
instrComponents parse(FILE *inFile);


// Print the instructiont type and whether value, user symbol, dest, and/or jump command present 
void printInstructionInfo(instrTypeInfo instructionInfo);


// Print instruction components: value, user symbol, label, dest, comp, or jump commands
void printInstructionComponents(instrTypeInfo instructionTypeInfo, instrComponents instructionComponents);
