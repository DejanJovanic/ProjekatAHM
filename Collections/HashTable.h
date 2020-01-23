#pragma once
#include <stdint.h>
#include "Windows.h"
typedef struct hash_node {
	void* key;
	void* value;
	struct hash_node* next;
} HashNode;

typedef struct hash_table {
	HashNode** _table;
	int size;
	int entries;
	BOOL(*key_comparer_function)(void*, void*);
} HashTable;

BOOL HashTable_delete(HashTable* table, void* key, HashNode** out_node);
BOOL HashTable_insert(HashTable* table, HashNode* node);
HashNode* HashTable_get(HashTable* table, void* key);
BOOL HashTable_initialize_table(HashTable* table, unsigned int buckets,BOOL (*key_comparer)(void*,void*));