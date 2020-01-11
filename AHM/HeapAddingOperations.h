#pragma once
#include "Structs.h"
#include "..\HeapOperations\HeapCreation.h"
#include "..\HeapOperations\HeapManipulation.h"
#include "..\Collections\list.h"

BOOL HeapAddingOperations_add_default_heap(HeapManager* manager, HANDLE* heap_handle);
BOOL HeapAddingOperations_add_default_heap_with_alloc(HeapManager* manager, HANDLE* heap_handle,int memory_size,void** pointer);
BOOL HeapAddingOperations_add_big_heap(HeapManager* manager, HANDLE* heap_handle, int heap_size);
BOOL HeapAddingOperations_add_big_heap_with_alloc(HeapManager* manager, HANDLE* heap_handle, int heap_size,void** pointer);
