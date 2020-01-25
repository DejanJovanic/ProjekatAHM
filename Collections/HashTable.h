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
	void*(*bucket_list_allocating_function)(int);
	void(*bucket_list_free_function)(HashNode**);
	BOOL(*key_comparer_function)(void*, void*);
	void(*node_free_function)(HashNode*);
	void*(*node_allocate_function)();
} HashTable;

BOOL HashTable_delete(HashTable* table, void* key, void** out_value);
BOOL HashTable_insert(HashTable* table, void* key,void* value);
HashNode* HashTable_get(HashTable* table, void* key);
BOOL HashTable_initialize_table(HashTable* table, unsigned int buckets,BOOL (*key_comparer)(void*,void*), void* (*bucket_list_allocating_function)(int), void(*bucket_list_free_function)(HashNode**), void*(*node_allocate_function)(), void(*node_free_function)(HashNode*));
BOOL HashTable_deinitialize_table(HashTable* table);