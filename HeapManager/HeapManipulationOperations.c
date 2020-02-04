#include "HeapManipulationOperations.h"

BOOL HeapManipulationOperations_get_heap(HeapManager* manager, Heap* out_heap) {
	BOOL ret = FALSE;

	if (manager != NULL && manager->heap_count > 0) {
		Heap temp;
		EnterCriticalSection(&manager->manager_mutex);
		temp = manager->heap_array[manager->current_heap];
		manager->current_heap = (manager->current_heap + 1) % manager->heap_count; ///< Round robin tehnika.
		LeaveCriticalSection(&manager->manager_mutex);
		if (temp != NULL) {
			*out_heap = temp;
			ret = TRUE;
		}
	}
	return ret;

}

void* HeapManipulationOperations_get_memory(HeapManager* manager, int memory_size,Heap* out_heap) {
	if (manager != NULL && memory_size > 0) {
		Heap heap;
		if (HeapManipulationOperations_get_heap(manager, &heap)) {
			void* ret = HeapManipulation_allocate_memory(memory_size, heap);
			if (ret != NULL) {
				*out_heap = heap;
				return ret;
			}
			else
				return NULL;
		}
		else
			return NULL;
	}
	else
		return NULL;
}

BOOL HeapManipulationOperations_free_memory(HeapManager* manager, void* pointer, Heap heap) {
	if (manager != NULL && pointer != NULL && heap != NULL) {
		return HeapManipulation_free_memory(pointer, heap);
	}
	else
		return FALSE;
}