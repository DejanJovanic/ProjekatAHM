#pragma once
#include "Windows.h"
#include "heapapi.h"

HANDLE HeapCreation_create_default_heap(int heap_size);

HANDLE HeapCreation_create_big_heap(int heap_size);

BOOL HeapCreation_destroy_heap(HANDLE heapHandle);