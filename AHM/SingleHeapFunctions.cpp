// AHM.cpp : Defines the functions for the static library.
//

#include "SingleHeapFunctions.h"


HANDLE create_default_heap(int heap_size) {
	if (heap_size > 0)
		return HeapCreate(0, heap_size / 4, heap_size);
	else
		return NULL;
}

HANDLE create_big_heap(int heap_size) {
	if (heap_size > 0)
		return HeapCreate(0, heap_size, heap_size + 20);
	else
		return NULL;
}

void* try_allocate_memory(int bytes, HANDLE heap_handle) {
	if (bytes > 0 && heap_handle != NULL)
		HeapAlloc(heap_handle, 0, bytes);
	else
		return NULL;
}

BOOL try_free_memory(void* pointer, HANDLE heap_handle) {
	if (heap_handle != NULL && pointer != NULL) {
		return HeapFree(heap_handle, 0, pointer);
	}
}

BOOL try_destroy_heap(HANDLE heap_handle) {
	if (heap_handle != NULL) {
		return HeapDestroy(heap_handle);
	}
}
