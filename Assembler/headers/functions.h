



void push(lineNode *head, int val);
void addFromFileToListUntilDelimiter(lineNode *head, FILE *inptr, int delimiter);
_Bool searchList(lineNode *head, int val);
void addFromListToListUntilDelimiter(lineNode *headC0, lineNode *head, int delimiter);
lineNode *copyList(lineNode *head, int delimiter);
int getListLength(lineNode *head);
lineNode *copy(lineNode *head);
void push2(entryNode *head, char *symbol, int address);
unsigned int hash(char *symbol, int tableSize);
void initializeHashTable(entryNode *hashTable[], int tableSize);
_Bool compareLists(lineNode *listA, lineNode *listB);
_Bool compareListAndString(lineNode *listA, char *str);
char *listToString(lineNode *head);
int getNumberOfDigits(int value);
lineNode *initializeList(char val);
int positionInList(lineNode *head, int value);
char valueInList(lineNode *head, int position);
char *listToString2(lineNode *head, int startPos, int endPos);
int listToInt(lineNode *head);
void addLabelSymbols2(FILE *inptr, entryNode* hashTable[], int tableSize);
void addUserSymbols2(FILE *inptr, entryNode* hashTable[], int tableSize);









