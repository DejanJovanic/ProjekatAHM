#include "ManagerOperations.h"

HeapManager* ManagerOperations_initialize_heap_manager(int heap_size, int heap_count) {
	HeapManager* manager = (HeapManager*)malloc(sizeof(HeapManager));
	if (manager != NULL) {
		Node* head = NULL;
		if (heap_count > 0 && heap_size > 0) {

			HANDLE h;
			for (int i = 0; i < heap_count; i++) {
				h = HeapCreation_create_default_heap(heap_size);
				if (h != NULL)
					list_add_node(&head, h);
			}
		}
		if (head != NULL)
			manager->heap_list = &head;
		manager->heap_size = heap_size;
		manager->heap_count = heap_count;
		manager->current_heap = head;
		InitializeCriticalSection(&manager->manager_mutex);
	}
	return manager;
}

void ManagerOperations_destroy_manager(HeapManager** manager) {
	HeapManager* temp = *manager;
	list_delete_list(temp->heap_list);
	free(temp->current_heap);
	DeleteCriticalSection(&temp->manager_mutex);
}