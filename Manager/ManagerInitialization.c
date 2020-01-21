#include "ManagerInitialization.h"

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
			_dictionary._items = NULL;
			InitializeCriticalSection(&_dictionary._cs);
			if ((_dictionary._dict_heap = HeapCreation_create_infinite_heap(5000)) != NULL)
				_dictionary._is_initialized = TRUE;
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
		DictItem* current_item, * tmp;
		HASH_ITER(hh, _dictionary._items, current_item, tmp) {
			HASH_DEL(_dictionary._items, current_item);  /* delete; users advances to next */
			free(current_item);            /* optional- if you want to free  */
		}
		DeleteCriticalSection(&_dictionary._cs);
		_dictionary._is_initialized = FALSE;
		ret = TRUE;
	}
	
	return ret;
}