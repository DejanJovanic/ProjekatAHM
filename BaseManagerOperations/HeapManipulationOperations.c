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