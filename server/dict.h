#include <stdbool.h>

typedef struct {
	char* key;
	char* value;
	bool grave;
} Item;

typedef struct {
	unsigned int capacity;
	unsigned int size;
	Item* items;
} Bucket;

typedef struct { 
	unsigned int numBuckets;
	Bucket* buckets;
} Dict;


Dict* createDict();
void freeDict(Dict* dict);

void addItem(Dict* dict, char* key, char* value);
void deleteItem(Dict* dict, char* key);
Item* getItem(Dict* dict, char* key);

