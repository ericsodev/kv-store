#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "dict.h"


Dict* createDict() {
	Dict* dict = malloc(sizeof(Dict));
	dict->numBuckets = NUM_BUCKETS;

	// create buckets
	dict->buckets = malloc(NUM_BUCKETS * sizeof(Bucket));

	for (int i = 0; i < NUM_BUCKETS; ++i) {
		dict->buckets[i].size = 0;
		dict->buckets[i].capacity = INIT_CAP;
		dict->buckets[i].items = malloc(INIT_CAP * sizeof(Item));

		for (int j = 0; j < INIT_CAP; ++j) {
			dict->buckets[i].items[j].key = NULL;
			dict->buckets[i].items[j].grave = 0;
			dict->buckets[i].items[j].value = NULL;
		}
	}

	return dict;
}

void freeDict(Dict* dict) {
	for (int i = 0; i < dict->numBuckets; ++i) {
		for (int j = 0; j < dict->buckets[i].capacity; ++j) {
			if (dict->buckets[i].items[j].key != NULL) {
				free(dict->buckets[i].items[j].key);
			}
			if (dict->buckets[i].items[j].value != NULL) {
				printf("%i %i free\n", i, j);
				free(dict->buckets[i].items[j].value);
			}
		}
		free(dict->buckets[i].items);
	}
	free(dict->buckets);
	free(dict);
}

unsigned int hash(char* str) {
	const unsigned int fnv_prime = 0x811C9DC5;
	unsigned int hash = 0;
	unsigned int i = 0;

	for (i = 0; i < strnlen(str, MAX_KEY_LEN); str++, i++)
	{
		hash *= fnv_prime;
		hash ^= (*str);
	}

	return hash;
}


Item* getItem(Dict* dict, char* key) {
	unsigned int hashed = hash(key);
	Bucket *b = dict->buckets + (hashed % dict->numBuckets);
	unsigned int itemHash = hashed % b->capacity;

	Item* i;
	for (int j=0; j<b->capacity; j++) {
		i = b->items + itemHash;
		if (i->key == NULL) {
			return NULL;
		} else if (i->grave) {
			continue;
		} else if (strncmp(key, i->key, MAX_KEY_LEN)==0) {
			return i;
		}
		itemHash = (itemHash + 1) % b->capacity;
	}
	return NULL;
}

void deleteItem(Dict* dict, char* key) {
	unsigned int hashed = hash(key);
	Bucket *b = dict->buckets + (hashed % dict->numBuckets);

	// check if item is in dict. 
	unsigned int itemHash = hashed % b->capacity;

	Item* item;
	for (int j=0; j<b->capacity; ++j) {
		item = b->items + (itemHash + j) % b->capacity;
		if (item->key == NULL) {
			// not in dict
			break;
		} else if (strncmp(key, item->key, MAX_KEY_LEN)==0) {
			// correct item/key
			// free space and place gravestone
			free(item->key);
			free(item->value);
			item->key=NULL;
			item->value=NULL;
			item->grave=1;
			return;
		}
	}
}

void addItem(Dict* dict, char* key, char* val) {
	unsigned int hashed = hash(key);
	Bucket *b = dict->buckets + (hashed % dict->numBuckets);

	// check if item is in dict. if so, only need to update value
	unsigned int itemHash = hashed % b->capacity;

	Item* item;
	for (int j=0; j<b->capacity; ++j) {
		item = b->items + (itemHash + j) % b->capacity;
		if (item->key == NULL) {
			// not in dict
			break;
		} else if (strncmp(key, item->key, MAX_KEY_LEN)==0) {
			// correct item/key
			free(item->value);
			item->value = strndup(val, MAX_VAL_LEN);
			return;
		}
	}
	

	if ((b->size + 1) >= b->capacity/2) {
		// need to expand
		Item* oldItems = b->items;

		// create new item list and init
		unsigned int oldCap = b->capacity;
		b->capacity = b->capacity * 2;
		b->items = malloc(b->capacity*sizeof(Item));
		b->size=0;
		for (int i = 0; i<b->capacity*2;++i) {
			b->items[i].key = NULL;
			b->items[i].value = NULL;
			b->items[i].grave = 0;
		}

		// move items over
		for (int i = 0; i<oldCap;++i) {
			item = oldItems + i;
			if (item->grave) {
				continue;
			} else if (item->key != NULL) {
				addItem(dict, item->key, item->value);
				free(item->key);
				free(item->value);
				b->size++;
			}
		}
		free(oldItems);
	} 


	// add item
	itemHash = hashed % b->capacity;

	Item* newItem;
	for (int j=0; j<b->capacity; ++j) {
		newItem = b->items + (itemHash + j) % b->capacity;
		if (newItem->key == NULL || newItem->grave) {
			newItem->grave = 0;
			newItem->key = strndup(key, MAX_KEY_LEN);
			newItem->value = strndup(val, MAX_VAL_LEN);
			b->size++;
			break;
		} 
	}
}

