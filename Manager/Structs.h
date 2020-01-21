#pragma once
#include "..\BaseManagerOperations\Structs.h"
#include "..\Collections\uthash.h"

typedef struct dict_item {
	void* pointer; //key
	Heap heap;
	UT_hash_handle hh;
} DictItem;

typedef struct dict {
	BOOL _is_initialized;
	DictItem* _items;
	Heap _dict_heap;
	CRITICAL_SECTION _cs;
} Dictionary;