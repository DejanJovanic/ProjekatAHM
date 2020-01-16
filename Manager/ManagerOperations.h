#pragma once
#include "..\BaseManagerOperations\HeapManipulationOperations.h"
#include "..\HeapOperations\HeapManipulation.h"
#include "Structs.h"

extern HeapManager* manager;
extern Dictionary dictionary;

void* thread_malloc(unsigned bytes);

void thread_free(void* pointer);