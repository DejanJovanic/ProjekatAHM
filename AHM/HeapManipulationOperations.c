#include "HeapManipulationOperations.h"

BOOL HeapManipulationOperations_get_heap(HeapManager* manager, HANDLE* heap_handle) {
	int current = 0;
	Node* current_heap = NULL;
	HANDLE temp;
	EnterCriticalSection(&manager->manager_mutex);
	temp = manager->current_heap->data;
	manager->current_heap = manager->current_heap->next;
	if (manager->current_heap == NULL)
		manager->current_heap = *manager->heap_list;
	LeaveCriticalSection(&manager->manager_mutex);
	if (temp != NULL) {
		*heap_handle = temp;
		return TRUE;
	}
	else
		return FALSE;
}