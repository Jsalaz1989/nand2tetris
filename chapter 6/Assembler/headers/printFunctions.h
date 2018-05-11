void printFields(infoStruct solutions);

void printList(lineNode *head);
void printList2(lineNode *head);
void printInstructionType(_Bool instructionType, _Bool dest, _Bool jump);
void printFields2(_Bool instructionType, _Bool destPresent, _Bool jumpPresent, char *value, char *dest, char *comp, char *jump);
void printBinary(_Bool binInstruction[]);
void printBinaryComp(_Bool binInstruction[]);
void printBinaryDest(_Bool binInstruction[]);
void printBinaryJump(_Bool binInstruction[]);
void printBinarySolutions(binStruct binarySolutions);
void printBinaryInstruction(int binInstruction[]);
void printHashTable(entryNode *hashTable[], int tableSize);
void printHashTableRow(entryNode *hashTable[], int tableSize, int row);

