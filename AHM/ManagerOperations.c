#include "ManagerOperations.h"

HeapManager* ManagerOperations_initialize_heap_manager(int heap_size,int heap_count) {
	HeapManager* manager = (HeapManager*)malloc(sizeof(HeapManager));
	if (manager != NULL) {
		if (heap_count > 0) {

			manager->heap_array = (Heap*)malloc(heap_count * sizeof(Heap));
		}
		manager->heap_size = heap_size;
		manager->max_heaps = heap_count;
		manager->heap_count = 0;
		manager->current_heap = -1;
		InitializeCriticalSection(&manager->manager_mutex);
	}
	return manager;
}

void ManagerOperations_destroy_manager(HeapManager** manager) {
	HeapManager* temp = *manager;
	free(temp->heap_array);
	free(temp->current_heap);
	DeleteCriticalSection(&temp->manager_mutex);
}