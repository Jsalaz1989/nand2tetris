
typedef struct node {
    char val;
    struct node *next;
} lineNode;

typedef struct info {
    int instructionType;
    char *value;
    char *userSymbol;
    char *label;
    char *dest;
    char *comp;
    char *jump;
} infoStruct;





typedef struct bin {
    _Bool bin0;
    _Bool bin1;
    _Bool bin2;
    _Bool bin3;
    _Bool bin4;
    _Bool bin5;
    _Bool bin6;
    _Bool bin7;
    _Bool bin8;
    _Bool bin9;
    _Bool bin10;
    _Bool bin11;
    _Bool bin12;
    _Bool bin13;
    _Bool bin14;
    _Bool bin15;
} binStruct;


typedef struct hashTableEntry {
    char *symbol;
    int address;
    struct hashTableEntry *next;
} entryNode;



typedef struct instructInfo {
    int instructionNum;
    int currentRAMaddress;
} instructionInfo;


