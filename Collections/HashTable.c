#include "HashTable.h"

uint32_t _HashTable_get_hash(void* key) {
	return ((uintptr_t)key * UINT32_C(2654435769)) >> 5 + ((sizeof(uintptr_t) - sizeof(uint32_t)) * 8);
}

BOOL HashTable_initialize_table(HashTable* table, unsigned int buckets, BOOL(*key_comparer)(void*, void*)) {
	BOOL ret = TRUE;
	table->entries = 0;
	if(buckets > 0 && key_comparer != NULL)
		table->_table = (HashNode**)malloc(sizeof(HashNode*) * buckets);
	if (table->_table != NULL) {
		table->size = buckets;
		for (int i = 0; i < buckets; i++)
			table->_table[i] = NULL;
		table->key_comparer_function = key_comparer;
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

BOOL HashTable_insert(HashTable* table, HashNode* node) {
	HashNode* node_temp;

	if (HashTable_get(table, node->key) == NULL) {
		uint32_t index = _HashTable_get_hash(node->key) % table->size;
		node->next = table->_table[index];
		table->_table[index] = node;
		table->entries++;
	}
	else
		return FALSE;
}

BOOL HashTable_delete(HashTable* table, void* key,HashNode** out_node) {
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
		*out_node = node;
		return TRUE;
	}
	else
		return FALSE;
	
	


}