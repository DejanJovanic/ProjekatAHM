#pragma once
#include "..\BaseManagerOperations\HeapManipulationOperations.h"
#include "..\HeapOperations\HeapManipulation.h"
#include "Structs.h"

#ifndef ERRORS
#define MANAGER_UNINITIALIZED_ERROR -1
#define NULL_SENT_ERROR -2
#endif

#ifndef MANAGER_DEFINE
	HeapManager* _manager;
	Dictionary _dictionary;
#else
	extern HeapManager* _manager;
	extern Dictionary _dictionary;
#endif

void* thread_malloc(unsigned bytes);

void thread_free(void* pointer);