#include "HeapAddingOperations.h"

BOOL HeapAddingOperations_add_default_heap(HeapManager* manager,HANDLE* heap_handle) {
	BOOL ret = FALSE;
	if (manager != NULL) {
		HANDLE h = HeapCreation_create_default_heap(manager->heap_size);
		if (h != NULL) {
			EnterCriticalSection(&manager->manager_mutex);
			if (list_add_node(manager->heap_list, h)) {
				manager->heap_count += 1;
				*heap_handle = h;
				ret = TRUE;
			}
			LeaveCriticalSection(&manager->manager_mutex);
		}
	}
	return ret;
}

BOOL HeapAddingOperations_add_default_heap_with_alloc(HeapManager* manager, HANDLE* heap_handle,int memory_size,void** pointer) {
	BOOL ret = FALSE;
	if (manager != NULL) {
		HANDLE h = HeapCreation_create_default_heap(manager->heap_size);
		if (h != NULL) {
			void* p = HeapManipulation_allocate_memory(memory_size, h);
			if (p != NULL) {
				EnterCriticalSection(&manager->manager_mutex);
				if (list_add_node(manager->heap_list, h)) {
					manager->heap_count += 1;
					*heap_handle = h;
					*pointer = p;
					ret = TRUE;
				}
				LeaveCriticalSection(&manager->manager_mutex);
			}
			
		}
	}
	return ret;
}

BOOL HeapAddingOperations_add_big_heap(HeapManager* manager, HANDLE* heap_handle, int heap_size) {
	BOOL ret = FALSE;
	if (manager != NULL) {
		HANDLE h = HeapCreation_create_big_heap(heap_size);
		if (h != NULL) {
			EnterCriticalSection(&manager->manager_mutex);
			if (list_add_node(manager->heap_list, h)) {
				manager->heap_count += 1;
				*heap_handle = h;
				ret = TRUE;
			}
			LeaveCriticalSection(&manager->manager_mutex);
		}
	}
	return ret;
}

BOOL HeapAddingOperations_add_big_heap_with_alloc(HeapManager* manager, HANDLE* heap_handle, int heap_size,void** pointer) {
	BOOL ret = FALSE;
	if (manager != NULL) {
		HANDLE h = HeapCreation_create_big_heap(heap_size);
		if (h != NULL) {
			void* p = HeapManipulation_allocate_memory(heap_size,h);
			if (p != NULL) {
				EnterCriticalSection(&manager->manager_mutex);
				if (list_add_node(manager->heap_list, h)) {
					manager->heap_count += 1;
					*heap_handle = h;
					*pointer = p;
					ret = TRUE;
				}
				LeaveCriticalSection(&manager->manager_mutex);
			}
			
		}
	}
	return ret;
}