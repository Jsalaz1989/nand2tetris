unsigned int hashFunction(char *symbol, int tableSize);
void initializeHashTable(entryNode *hashTable[], int tableSize);
_Bool searchHashTable(entryNode *hashTable[], int tableSize, char needle[]);
void addSymbol(char *symbol, int address, entryNode *hashTable[], int tableSize);
void addLabelSymbols(FILE *inFile, entryNode* hashTable[]);
void addUserSymbols(FILE *inFile, entryNode* hashTable[], int tableSize);
int getSymbolAddress(entryNode *hashTable[], int tableSize, char needle[]);
void replaceSymbols(FILE *inFile, FILE *outFile, entryNode *hashTable[], int tableSize);
void searchAndDestroySymbols(FILE *inFile, FILE *outFile);

