#pragma once
#include "Windows.h"
#include "heapapi.h"

typedef HANDLE Heap;

BOOL HeapDestruction_destroy_heap(Heap heap);