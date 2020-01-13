#pragma once
#include "Structs.h"
#include "..\HeapOperations\HeapCreation.h"

HeapManager* ManagerOperations_initialize_heap_manager(int heap_size, int heap_count);

void ManagerOperations_destroy_manager(HeapManager** manager);

void ManagerOperations_destroy_manager_with_heaps(HeapManager** manager);