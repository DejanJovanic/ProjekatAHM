#pragma once
#include "..\BaseManagerOperations\Structs.h"
#include "..\Collections\HashTable.h"

//typedef struct dict_item {
//	void* pointer; //key
//	Heap heap;
//	UT_hash_handle hh;
//} DictItem;

typedef struct dict {
	BOOL _is_initialized;
	HashTable* _table;
	Heap _dict_heap;
	CRITICAL_SECTION _cs;
} Dictionary;