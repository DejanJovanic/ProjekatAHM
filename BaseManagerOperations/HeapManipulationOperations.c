#include "HeapManipulationOperations.h"

BOOL HeapManipulationOperations_get_heap(HeapManager* manager, Heap* heap) {
	int current = 0;
	Heap temp;
	EnterCriticalSection(&manager->manager_mutex);
	temp = manager->heap_array[manager->current_heap];
	manager->current_heap = (manager->current_heap + 1) % manager->heap_count;
	LeaveCriticalSection(&manager->manager_mutex);	
	if (temp != NULL) {
		*heap = temp;
		return TRUE;
	}
	else
		return FALSE;
}