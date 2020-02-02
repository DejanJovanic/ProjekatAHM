#pragma once
#include "Structs.h"
#include "..\HeapOperations\HeapCreation.h"
#include "..\HeapOperations\HeapDestruction.h"
#include "..\HeapOperations\HeapManipulation.h"

extern Dictionary* _dictionary;

BOOL _Dictionary_create(int minimal_size);
BOOL _Dictionary_insert(void* key, void* value);
BOOL _Dictionary_remove(void* key, void** value);
void _Dictionary_destroy();