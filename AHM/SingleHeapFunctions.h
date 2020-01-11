#pragma once

#include "Windows.h"
#include "heapapi.h"

HANDLE create_default_heap(int heap_size);

HANDLE create_big_heap(int heap_size);


void* try_allocate_memory(int bytes, HANDLE heapHandle);


BOOL try_free_memory(void* pointer, HANDLE heapHandle);

BOOL try_destroy_heap(HANDLE heapHandle);

