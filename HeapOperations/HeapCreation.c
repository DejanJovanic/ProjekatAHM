#include "HeapCreation.h"

void static HeapCreation_set_options(Heap heap) {
	HEAP_OPTIMIZE_RESOURCES_INFORMATION HeapInfo;
	HeapInfo.Version = HEAP_OPTIMIZE_RESOURCES_CURRENT_VERSION;
	HeapInfo.Flags = 0;
	HeapSetInformation(heap, HeapOptimizeResources, &HeapInfo, sizeof(HeapInfo)); ///< heap brze decommit-uje memoriju, optimizuje potrosnju memorije procesa.
	HeapSetInformation(heap, HeapEnableTerminationOnCorruption, NULL, 0); ///< ugasi proces ako je doslo do korupcije heap-a.
}

Heap HeapCreation_create_default_heap(int heap_size) {
	if (heap_size > 0) {
		Heap heap = HeapCreate(0, heap_size / 4, heap_size);
		if (heap != NULL) {
			HeapCreation_set_options(heap);
			return heap;
		}
		else
			return NULL;
	}
	else
		return NULL;
}

Heap HeapCreation_create_big_heap(int heap_size) {
	if (heap_size > 0) {
		Heap heap =  HeapCreate(0, heap_size, heap_size);
		if (heap != NULL) {
			HeapCreation_set_options(heap);
			return heap;
		}
		else
			return NULL;
	}
	else
		return NULL;
}

Heap HeapCreation_create_infinite_heap(int initial_commited_bytes) {
	if (initial_commited_bytes > 0) {
		Heap heap = HeapCreate(0, initial_commited_bytes, 0);
		if (heap != NULL) {
			HeapCreation_set_options(heap);
			return heap;
		}
		else return NULL;

	}

	else
		return HeapCreate(0, 50000000, 0);
}

Heap HeapCreation_create_infinite_heap_unlocked(int initial_commited_bytes) {
	if (initial_commited_bytes > 0) {
		Heap heap = HeapCreate(HEAP_NO_SERIALIZE, initial_commited_bytes, 0);
		if (heap != NULL) {
			HeapCreation_set_options(heap);
			return heap;
		}
		else return NULL;
	}
	else {
		Heap heap = HeapCreate(HEAP_NO_SERIALIZE, 50000000, 0);
		if (heap != NULL) {
			HeapCreation_set_options(heap);
			return heap;
		}
		else return NULL;
	}
}

