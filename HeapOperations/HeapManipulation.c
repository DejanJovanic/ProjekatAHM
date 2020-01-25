#include "HeapManipulation.h"


inline void* HeapManipulation_allocate_memory(int bytes, Heap heap) {
	if (bytes > 0 && heap != NULL)
		return HeapAlloc(heap, 0, bytes);
	else
		return NULL;
}

inline BOOL HeapManipulation_free_memory(void* pointer, Heap heap) {
	if (heap != NULL && pointer != NULL) {
		return HeapFree(heap, 0, pointer);
	}
	else
		return FALSE;
}