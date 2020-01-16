#pragma once
#include "Structs.h"
#include "..\HeapOperations\HeapCreation.h"
#include "..\HeapOperations\HeapDestruction.h"

HeapManager* HeapManagerOperations_initialize_heap_manager(int heap_size, int heap_count);

void HeapManagerOperations_destroy_manager(HeapManager** manager);

void HeapManagerOperations_destroy_manager_with_heaps(HeapManager** manager);