#include "HashTable.h"

inline uint32_t _HashTable_get_hash(void* key) {
	uintptr_t a = (uintptr_t)key;
	a -= (a << 6);
	a ^= (a >> 17);
	a -= (a << 9);
	a ^= (a << 4);
	a -= (a << 3);
	a ^= (a << 10);
	a ^= (a >> 15);
	return a >> ((sizeof(uintptr_t) - sizeof(uint32_t)) * 8);
}

BOOL HashTable_initialize_table(HashTable* table, unsigned int buckets, BOOL(*key_comparer)(void*, void*), void* (*bucket_list_allocating_function)(int), void(*bucket_list_free_function)(HashTable*), void* (*node_allocate_function)(), void(*node_free_function)(HashNode*)) {
	BOOL ret = TRUE;
	table->entries = 0;
	table->key_comparer_function = key_comparer;
	table->bucket_list_allocating_function = bucket_list_allocating_function;
	table->bucket_list_free_function = bucket_list_free_function;
	table->node_allocate_function = node_allocate_function;
	table->node_free_function = node_free_function;
	if(buckets > 0 && key_comparer != NULL)
		table->_table = table->bucket_list_allocating_function(buckets);
	if (table->_table != NULL) {
		table->size = buckets;
		for (int i = 0; i < buckets; i++)
			table->_table[i] = NULL;

	}
		
	else
		ret = FALSE;

	return ret;
}

HashNode* HashTable_get(HashTable* table, void* key) {
	uint32_t hash = _HashTable_get_hash(key);
	uint32_t index = hash % table->size;
	HashNode* node;
	uintptr_t pointer_value = (uintptr_t)key;
	for (node = table->_table[index]; node != NULL; node = node->next) {
		if (table->key_comparer_function(key,node->key))
			break;
	}

	return node;
}

void HashTable_rebuild_table(HashTable* table) {
	HashNode** old_table, * next, * current;
	unsigned int old_size, index, i;

	old_table = table->_table;
	old_size = table->size;
	table->_table = table->bucket_list_allocating_function(old_size * 2);
	table->size <<= 1;
	for (int i = 0; i < table->size; i++) {
		table->_table[i] = NULL;
	}
	
	for (i = 0; i < old_size; i++) {
		next = old_table[i];
		while (next) {
			current = next;
			next = next->next;
			index = _HashTable_get_hash(current->key) % table->size;
			current->next = table->_table[index];
			table->_table[index] = current;
		}
	}
	table->bucket_list_free_function(old_table);
}

BOOL HashTable_insert(HashTable* table, void* key, void* value) {
	if (HashTable_get(table, key) == NULL) {
		while (table->entries >= table->size * 0.75)
			HashTable_rebuild_table(table);
		uint32_t index = _HashTable_get_hash(key) % table->size;
		HashNode* node = (HashNode*)table->node_allocate_function();
		node->key = key;
		node->value = value;
		node->next = table->_table[index];
		table->_table[index] = node;
		table->entries++;
		return TRUE;
	}
	else
		return FALSE;
}


BOOL HashTable_delete(HashTable* table, void* key,void** out_value) {
	HashNode* node;
	HashNode* last;

	node = HashTable_get(table, key);
	uint32_t index = _HashTable_get_hash(key) % table->size;
	if (node != NULL) {
		if (node == table->_table[index]) {
			table->_table[index] = node->next;
		}
		else {
			for (last = table->_table[index]; last != NULL && last->next != NULL; last = last->next) {
				if (last->next == node)
					break;
			}

			last->next = node->next;
		}
		table->entries--;
		*out_value = node->value;
		table->node_free_function(node);
		return TRUE;
	}
	else
		return FALSE;
}

BOOL HashTable_deinitialize_table(HashTable* table) {
	HashNode* current = NULL;
	HashNode* next = NULL;
	for (int i = 0; i < table->size; i++) {
		current = table->_table[i];
		while (current != NULL) {
			next = current->next;
			table->node_free_function(current);
			current = next;
		}
	}
	table->bucket_list_free_function(table->_table);
	table->size = 0;
	table->entries = 0;
	return TRUE;
}