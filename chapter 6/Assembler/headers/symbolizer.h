// Node for a hash table of symbols and their addresses
typedef struct hashTableEntry 
{
    char *symbol;
    int address;
    struct hashTableEntry *next;
} 
tableNode;



// Simple hash function returning a string's corresponding hash value between 0 and HASH_TABLE_SIZE
unsigned int hashFunction(char *symbol);


// Creates a hash table node and fills it with a symbol and an address
void pushTable(tableNode *head, char *symbol, int address);


// Create a hash table to contain symbols and their adddress and fill with predefined symbols
void initializeHashTable(void);


// Return true if a hash table contains a symbol, return false if symbol not found
int searchHashTable(char *needle);


// Search for labels in the program and add them to the hash table with their corresponding instruction number
void addLabelSymbols(void);


// Search for user-defined symbols in the program and add them to the hash table with their corresponding RAM address
void addUserSymbols(void);


// Returns the address associated with a symbol
int getSymbolAddress(char needle[]);


// Copy the program to a new file, substituting every symbol with its address
void replaceSymbols(void);


// Free every node in the hash table and the symbols in each node
void freeHashTable(void);


// Substitutes any symbols with their corresponding RAM address or instruction number
void searchAndDestroySymbols(void);


// Print the contents of the hash table by hash value 
void printHashTable(void);
