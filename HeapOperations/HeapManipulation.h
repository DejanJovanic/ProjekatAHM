#pragma once
#include "Windows.h"
#include "heapapi.h"

typedef HANDLE Heap;

void* HeapManipulation_allocate_memory(int bytes, Heap heap);

BOOL HeapManipulation_free_memory(void* pointer, Heap heap);
