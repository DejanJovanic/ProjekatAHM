#include "ManagerOperations.h"

void* thread_malloc(unsigned bytes) {
	if (manager != NULL) {
		Heap heap;
		
		if (HeapManipulationOperations_get_heap(manager, &heap)) {
			void* pointer =	HeapManipulation_allocate_memory(bytes, heap);
			DictItem* item = (DictItem*)malloc(sizeof(DictItem));
			if (pointer != NULL && item != NULL) {
				item->heap = heap;
				item->pointer = pointer;
				EnterCriticalSection(&dictionary->cs);
				HASH_ADD_PTR(dictionary->items, pointer, item);
				LeaveCriticalSection(&dictionary->cs);
			}
			
			return pointer;
		}
		else {
			return NULL;
		}
	}
	else
		exit(-1);
}

void thread_free(void* pointer) {
	if (pointer != NULL) {
		DictItem* ptr = NULL;
		EnterCriticalSection(&dictionary->cs);
		HASH_FIND_PTR(dictionary->items, &pointer, ptr);
		if (ptr != NULL) {
			HASH_DEL(dictionary->items, ptr);	
		}
		LeaveCriticalSection(&dictionary->cs);
		if (ptr != NULL) {
			HeapManipulation_free_memory(pointer, ptr->heap);
			free(ptr);
		}

		
	}
	else
		exit(-1);
}