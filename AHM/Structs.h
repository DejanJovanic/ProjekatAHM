#pragma once
#include "Windows.h"

typedef HANDLE Heap;

typedef struct manager_struct {
	Heap* heap_array;
	int heap_size;
	int heap_count;
	int max_heaps;
	int current_heap;
	CRITICAL_SECTION manager_mutex;
} HeapManager;