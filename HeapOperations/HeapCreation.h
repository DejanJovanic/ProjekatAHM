#pragma once
#include "Windows.h"
#include "heapapi.h"

typedef HANDLE Heap;

Heap HeapCreation_create_default_heap(int heap_size);

Heap HeapCreation_create_big_heap(int heap_size);

Heap HeapCreation_create_infinite_heap(int initial_commited_bytes);

BOOL HeapCreation_destroy_heap(Heap heap);