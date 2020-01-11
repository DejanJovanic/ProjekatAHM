#include "HeapManipulation.h"


void* HeapManipulation_allocate_memory(int bytes, HANDLE heap_handle) {
	if (bytes > 0 && heap_handle != NULL)
		HeapAlloc(heap_handle, 0, bytes);
	else
		return NULL;
}

BOOL HeapManipulation_free_memory(void* pointer, HANDLE heap_handle) {
	if (heap_handle != NULL && pointer != NULL) {
		return HeapFree(heap_handle, 0, pointer);
	}
}