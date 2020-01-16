#pragma once
#include "..\BaseManagerOperations\Structs.h"
#include "..\Collections\uthash.h"

typedef struct dict_item {
	void* pointer; //key
	Heap heap;
	UT_hash_handle hh;
} DictItem;

typedef struct dict {
	DictItem* items;
	CRITICAL_SECTION cs;
} Dictionary;