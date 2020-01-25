#include "ManagerInitialization.h"

inline BOOL compare_keys(void* key1, void* key2) {
	return key1 == key2;
}
inline void node_free_function(HashNode* node) {
	HeapManipulation_free_memory(node, _dictionary._dict_heap);
}
inline void* node_allocate_function() {
	return HeapManipulation_allocate_memory(sizeof(HashNode), _dictionary._dict_heap);
}
inline void* bucket_list_allocating_function(int buckets) {
	return HeapManipulation_allocate_memory(sizeof(HashNode*) * buckets, _dictionary._dict_heap);
}
inline void bucket_list_free_function(HashNode** table) {
	HeapManipulation_free_memory(table, _dictionary._dict_heap);
}
BOOL ManagerInitialization_initialize_manager(unsigned heap_count) {
	BOOL ret = TRUE;
	_manager = HeapManagerOperations_initialize_heap_manager(0, heap_count);
	if (_manager != NULL) {
		Heap heap;

		for (unsigned i = 0; i < heap_count; i++) {
			if (!HeapAddingOperations_add_infinite_heap(_manager, &heap, 50000000)) {
				ret = FALSE;
				break;
			}
		}
		if (!ret)
			HeapManagerOperations_destroy_manager_with_heaps(&_manager);
		else {
			InitializeCriticalSection(&_dictionary._cs);
			if ((_dictionary._dict_heap = HeapCreation_create_infinite_heap_unlocked(5000)) != NULL) {
				_dictionary._table = HeapManipulation_allocate_memory(sizeof(HashTable), _dictionary._dict_heap);
				if (_dictionary._table != NULL && HashTable_initialize_table(_dictionary._table, 1000,compare_keys,bucket_list_allocating_function,bucket_list_free_function,node_allocate_function,node_free_function))
					_dictionary._is_initialized = TRUE;			
			
			}
			else {
				DeleteCriticalSection(&_dictionary._cs);
				HeapManagerOperations_destroy_manager_with_heaps(&_manager);
				ret = FALSE;
			}
				
		}
	}


	return ret;
}

BOOL ManagerInitialization_destroy_manager()
{
	BOOL ret = FALSE;
	if (_manager != NULL) {
		HeapManagerOperations_destroy_manager_with_heaps(&_manager);
		free(_manager);
		ret = TRUE;
	}
	if (_dictionary._is_initialized) {
		HashNode* current;
		HashNode* next;
		EnterCriticalSection(&_dictionary._cs);
		HashTable_deinitialize_table(_dictionary._table);
		HeapManipulation_free_memory(_dictionary._table, _dictionary._dict_heap);
		LeaveCriticalSection(&_dictionary._cs);
		DeleteCriticalSection(&_dictionary._cs);
		HeapDestruction_destroy_heap(_dictionary._dict_heap);
		_dictionary._is_initialized = FALSE;
		ret = TRUE;
	}
	
	return ret;
}