#include "HeapCreation.h"

Heap HeapCreation_create_default_heap(int heap_size) {
	if (heap_size > 0)
		return HeapCreate(0, heap_size / 4, heap_size);
	else
		return NULL;
}

Heap HeapCreation_create_big_heap(int heap_size) {
	if (heap_size > 0)
		return HeapCreate(0, heap_size, heap_size + 20);
	else
		return NULL;
}

Heap HeapCreation_create_infinite_heap(int initial_commited_bytes) {
	return HeapCreate(0, initial_commited_bytes, 0);
}

Heap HeapCreation_create_infinite_heap_unlocked(int initial_commited_bytes) {
	return HeapCreate(HEAP_NO_SERIALIZE, initial_commited_bytes, 0);
}