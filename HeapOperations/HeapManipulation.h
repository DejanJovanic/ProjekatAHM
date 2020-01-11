#pragma once
#include "Windows.h"
#include "heapapi.h"

void* HeapManipulation_allocate_memory(int bytes, HANDLE heapHandle);
BOOL HeapManipulation_free_memory(void* pointer, HANDLE heapHandle);
