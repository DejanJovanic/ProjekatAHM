#include "HeapDestruction.h"

BOOL HeapDestruction_destroy_heap(Heap heap) {
	if (heap != NULL) {
		return HeapDestroy(heap);
	}
	else
		return FALSE;
}