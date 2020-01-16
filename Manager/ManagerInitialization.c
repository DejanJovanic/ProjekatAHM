#include "ManagerInitialization.h"

BOOL ManagerInitialization_initialize_manager(unsigned heap_count) {
	BOOL ret = TRUE;
	manager = HeapManagerOperations_initialize_heap_manager(0, heap_count);
	if (manager != NULL) {
		Heap heap;

		for (unsigned i = 0; i < heap_count; i++) {
			if (!HeapAddingOperations_add_infinite_heap(manager, &heap, 50000000)) {
				ret = FALSE;
				break;
			}
		}
		if (!ret)
			HeapManagerOperations_destroy_manager_with_heaps(&manager);
		else {
			dictionary = (Dictionary*)malloc(sizeof(Dictionary));
			if(dictionary != NULL)
				dictionary->items = NULL;
			InitializeCriticalSection(&dictionary->cs);
		}
	}


	return ret;
}

BOOL ManagerInitialization_destroy_manager()
{
	BOOL ret = FALSE;
	if (manager != NULL) {
		HeapManagerOperations_destroy_manager_with_heaps(&manager);
		free(manager);
		DictItem* current_item, * tmp;
		HASH_ITER(hh, dictionary->items, current_item, tmp) {
			HASH_DEL(dictionary->items, current_item);  /* delete; users advances to next */
			free(current_item);            /* optional- if you want to free  */
		}
		DeleteCriticalSection(&dictionary->cs);
		free(dictionary);
		ret = TRUE;
	}
	return ret;
}