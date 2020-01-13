#include "HeapManipulation.h"


void* HeapManipulation_allocate_memory(int bytes, Heap heap) {
	if (bytes > 0 && heap != NULL)
		HeapAlloc(heap, 0, bytes);
	else
		return NULL;
}

BOOL HeapManipulation_free_memory(void* pointer, Heap heap) {
	if (heap != NULL && pointer != NULL) {
		return HeapFree(heap, 0, pointer);
	}
}