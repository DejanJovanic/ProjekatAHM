#include "ManagerOperations.h"

void* thread_malloc(unsigned bytes) {
	if (_manager == NULL && !_dictionary._is_initialized)
		exit(MANAGER_UNINITIALIZED_ERROR);

	Heap heap;
		
	if (HeapManipulationOperations_get_heap(_manager, &heap)) {
		void* pointer =	HeapManipulation_allocate_memory(bytes, heap);

		if (pointer != NULL) {
			HashNode* item = HeapManipulation_allocate_memory(sizeof(HashNode), _dictionary._dict_heap);
			//HashNode* item = (HashNode*)malloc(sizeof(HashNode));
			if (item != NULL) {
				item->value = heap;
				item->key = pointer;
				EnterCriticalSection(&_dictionary._cs);
				//HASH_ADD_PTR(_dictionary._items, pointer, item);
				HashTable_insert(_dictionary._table, item);
				LeaveCriticalSection(&_dictionary._cs);
			}

		}
			
		return pointer;
	}
	else 
		return NULL;
}

void thread_free(void* pointer) {
	if (pointer == NULL)
		exit(NULL_SENT_ERROR);

	if (!_dictionary._is_initialized && _manager == NULL)
		exit(MANAGER_UNINITIALIZED_ERROR);

	HashNode* node = NULL;
	EnterCriticalSection(&_dictionary._cs);
	
	if (HashTable_delete(_dictionary._table,pointer,&node)) {
		LeaveCriticalSection(&_dictionary._cs);
		HeapManipulation_free_memory(pointer, node->value);
		HeapManipulation_free_memory(node, _dictionary._dict_heap);
	}
	else
		LeaveCriticalSection(&_dictionary._cs);

		

}