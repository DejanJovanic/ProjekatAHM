#include "HeapManagerOperations.h"


HeapManager* HeapManagerOperations_initialize_heap_manager(int heap_size,int heap_count) {
	HeapManager* manager = (HeapManager*)malloc(sizeof(HeapManager));
	if (manager != NULL) {
		if (heap_count > 0) {

			manager->heap_array = (Heap*)malloc(heap_count * sizeof(Heap));
		}
		manager->heap_size = heap_size;
		manager->max_heaps = heap_count;
		manager->heap_count = 0;
		manager->current_heap = 0;
		InitializeCriticalSection(&manager->manager_mutex);
		for (int i = 0; i < heap_count; i++) {
			manager->heap_array[i] = NULL;
		}
	}
	return manager;
}

void HeapManagerOperations_destroy_manager(HeapManager** manager) {
	HeapManager* temp = *manager;
	free(temp->heap_array);
	DeleteCriticalSection(&temp->manager_mutex);
}

void HeapManagerOperations_destroy_manager_with_heaps(HeapManager** manager) {
	HeapManager* temp = *manager;
	for (int i = 0; i < temp->max_heaps; i++) {
		if (temp->heap_array[i] != NULL) {
			HeapDestruction_destroy_heap(temp->heap_array[i]);
		}
	}
	free(temp->heap_array);
	DeleteCriticalSection(&temp->manager_mutex);
}