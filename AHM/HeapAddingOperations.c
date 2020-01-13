#include "HeapAddingOperations.h"

BOOL HeapAddingOperations_add_default_heap(HeapManager* manager,Heap* out_heap) {
	BOOL ret = FALSE;
	if (manager != NULL && manager->heap_count < manager->max_heaps) {
		HANDLE h = HeapCreation_create_default_heap(manager->heap_size);
		if (h != NULL) {
			EnterCriticalSection(&manager->manager_mutex);		
			if (manager->heap_array[manager->heap_count] == NULL) {
				manager->heap_array[manager->heap_count] = h;
				manager->heap_count += 1;
				*out_heap = h;
				ret = TRUE;
			}
			LeaveCriticalSection(&manager->manager_mutex);
		}
	}
	return ret;
}

BOOL HeapAddingOperations_add_default_heap_with_alloc(HeapManager* manager, Heap* out_heap,int memory_size,void** out_pointer) {
	BOOL ret = FALSE;
	if (manager != NULL && manager->heap_count < manager->max_heaps) {
		HANDLE h = HeapCreation_create_default_heap(manager->heap_size);
		if (h != NULL) {
			void* p = HeapManipulation_allocate_memory(memory_size, h);
			if (p != NULL) {
				EnterCriticalSection(&manager->manager_mutex);
				if (manager->heap_array[manager->heap_count] == NULL) {
					manager->heap_array[manager->heap_count] = h;
					manager->heap_count += 1;
					*out_heap = h;
					*out_pointer = p;
					ret = TRUE;
				}
				LeaveCriticalSection(&manager->manager_mutex);
			}
			
		}
	}
	return ret;
}

BOOL HeapAddingOperations_add_big_heap(HeapManager* manager, Heap* out_heap, int heap_size) {
	BOOL ret = FALSE;
	if (manager != NULL && manager->heap_count < manager->max_heaps) {
		HANDLE h = HeapCreation_create_big_heap(heap_size);
		if (h != NULL) {
			EnterCriticalSection(&manager->manager_mutex);
			if (manager->heap_array[manager->heap_count] == NULL) {
				manager->heap_array[manager->heap_count] = h;
				manager->heap_count += 1;
				*out_heap = h;
				ret = TRUE;
			}
			LeaveCriticalSection(&manager->manager_mutex);
		}
	}
	return ret;
}

BOOL HeapAddingOperations_add_big_heap_with_alloc(HeapManager* manager, Heap* out_heap, int heap_size,void** out_pointer) {
	BOOL ret = FALSE;
	if (manager != NULL && manager->heap_count < manager->max_heaps) {
		HANDLE h = HeapCreation_create_big_heap(heap_size);
		if (h != NULL) {
			void* p = HeapManipulation_allocate_memory(heap_size,h);
			if (p != NULL) {
				EnterCriticalSection(&manager->manager_mutex);
				if (manager->heap_array[manager->heap_count] == NULL) {
					manager->heap_array[manager->heap_count] = h;
					manager->heap_count += 1;
					*out_heap = h;
					*out_pointer = p;
					ret = TRUE;
				}
				LeaveCriticalSection(&manager->manager_mutex);
			}
			
		}
	}
	return ret;
}

BOOL HeapAddingOperations_add_infinite_heap(HeapManager* manager, Heap* out_heap, int initial_commited_size) {
	BOOL ret = FALSE;
	if (manager != NULL && manager->heap_count < manager->max_heaps) {
		HANDLE h = HeapCreation_create_infinite_heap(initial_commited_size);
		if (h != NULL) {
			EnterCriticalSection(&manager->manager_mutex);
			if (manager->heap_array[manager->heap_count] == NULL) {
				manager->heap_array[manager->heap_count] = h;
				manager->heap_count += 1;
				*out_heap= h;
				ret = TRUE;
			}
			LeaveCriticalSection(&manager->manager_mutex);
		}
	}
	return ret;
}

BOOL HeapAddingOperations_add_infinite_heap_with_alloc(HeapManager* manager, Heap* out_heap, int memory_size, int initial_commited_size, void** out_pointer) {
	BOOL ret = FALSE;
	if (manager != NULL && manager->heap_count < manager->max_heaps && initial_commited_size > 0 && memory_size > 0) {
		HANDLE h = HeapCreation_create_infinite_heap(initial_commited_size);
		if (h != NULL) {
			void* p = HeapManipulation_allocate_memory(memory_size, h);
			if (p != NULL) {
				EnterCriticalSection(&manager->manager_mutex);
				if (manager->heap_array[manager->heap_count] == NULL) {
					manager->heap_array[manager->heap_count] = h;
					manager->heap_count += 1;
					*out_heap = h;
					*out_pointer = p;
					ret = TRUE;
				}
				LeaveCriticalSection(&manager->manager_mutex);
			}

		}
	}
	return ret;
}