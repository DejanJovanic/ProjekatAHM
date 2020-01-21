#pragma once
#include "..\BaseManagerOperations\HeapManagerOperations.h"
#include "..\BaseManagerOperations\HeapAddingOperations.h"
#include "Structs.h"

#ifndef MANAGER_DEFINE
	HeapManager* _manager;
	Dictionary _dictionary;
#else
	extern HeapManager* _manager;
	extern Dictionary _dictionary;
#endif

BOOL ManagerInitialization_initialize_manager(unsigned heap_count);

BOOL ManagerInitialization_destroy_manager();
