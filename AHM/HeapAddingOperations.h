#pragma once
#include "Structs.h"
#include "..\HeapOperations\HeapCreation.h"
#include "..\HeapOperations\HeapManipulation.h"

BOOL HeapAddingOperations_add_default_heap(HeapManager* manager, Heap* out_heap);
BOOL HeapAddingOperations_add_default_heap_with_alloc(HeapManager* manager, Heap* out_heap,int memory_size,void** pointer);

BOOL HeapAddingOperations_add_big_heap(HeapManager* manager, Heap* out_heap, int heap_size);
BOOL HeapAddingOperations_add_big_heap_with_alloc(HeapManager* manager, Heap* out_heap, int heap_size,void** pointer);

BOOL HeapAddingOperations_add_infinite_heap(HeapManager* manager, Heap* out_heap, int initial_commited_size);
BOOL HeapAddingOperations_add_infinite_heap_with_alloc(HeapManager* manager, Heap* out_heap, int memory_size, int initial_commited_size, void** out_pointer);
