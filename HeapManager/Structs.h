#pragma once
#include "Windows.h"

typedef HANDLE Heap;

typedef struct manager_struct {
	Heap* heap_array; ///< niz heap-ova
	int heap_size; ///< maksimalna velicina "default" heap-a.
	int heap_count; ///< broj trenutno koriscenih heap-ova.
	int max_heaps; ///< maksimalan broj heap-ova.
	int current_heap; ///< index trenutno selektovanog heap-a.
	CRITICAL_SECTION manager_mutex; ///< propusnica kriticne sekcije
} HeapManager;