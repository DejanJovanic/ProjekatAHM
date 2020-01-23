#include "ManagerOperations.h"

void* thread_malloc(unsigned bytes) {
	if (_manager == NULL && !_dictionary._is_initialized)
		exit(MANAGER_UNINITIALIZED_ERROR);

	Heap heap;
		
	if (HeapManipulationOperations_get_heap(_manager, &heap)) {
		void* pointer =	HeapManipulation_allocate_memory(bytes, heap);

		if (pointer != NULL) {
			DictItem* item = HeapManipulation_allocate_memory(sizeof(DictItem), _dictionary._dict_heap);
			if (item != NULL) {
				item->heap = heap;
				item->pointer = pointer;
				EnterCriticalSection(&_dictionary._cs);
				HASH_ADD_PTR(_dictionary._items, pointer, item);
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

	DictItem* ptr = NULL;
	EnterCriticalSection(&_dictionary._cs);
	HASH_FIND_PTR(_dictionary._items, &pointer, ptr);
	if (ptr != NULL) {
		HASH_DEL(_dictionary._items, ptr);	
	}
	LeaveCriticalSection(&_dictionary._cs);
	if (ptr != NULL) {
		HeapManipulation_free_memory(pointer, ptr->heap);
		HeapManipulation_free_memory(ptr, _dictionary._dict_heap);
	}		

}