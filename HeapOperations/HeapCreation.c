#include "HeapCreation.h"

BOOL HeapCreation_destroy_heap(HANDLE heap_handle) {
	if (heap_handle != NULL) {
		return HeapDestroy(heap_handle);
	}
}

HANDLE HeapCreation_create_default_heap(int heap_size) {
	if (heap_size > 0)
		return HeapCreate(0, heap_size / 4, heap_size);
	else
		return NULL;
}

HANDLE HeapCreation_create_big_heap(int heap_size) {
	if (heap_size > 0)
		return HeapCreate(0, heap_size, heap_size + 20);
	else
		return NULL;
}