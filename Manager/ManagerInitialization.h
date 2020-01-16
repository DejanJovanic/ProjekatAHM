#pragma once
#include "..\BaseManagerOperations\HeapManagerOperations.h"
#include "..\BaseManagerOperations\HeapAddingOperations.h"
#include "Structs.h"

HeapManager* manager;
Dictionary* dictionary;


BOOL ManagerInitialization_initialize_manager(unsigned heap_count);

BOOL ManagerInitialization_destroy_manager();
