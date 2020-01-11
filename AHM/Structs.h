#pragma once
#include "Windows.h"
#include "..\Collections\list.h"


typedef struct manager_struct {
	Node** heap_list;
	int heap_size;
	int heap_count;
	Node* current_heap;
	CRITICAL_SECTION manager_mutex;
} HeapManager;