#pragma once
#include "Windows.h"
#include "heapapi.h"

typedef HANDLE Heap;

extern void* HeapManipulation_allocate_memory(int bytes, Heap heap);

extern BOOL HeapManipulation_free_memory(void* pointer, Heap heap);
