#include "HeapManagerOperations.h"


HeapManager* HeapManagerOperations_initialize_heap_manager(int heap_size,int maximal_heap_count) {
	HeapManager* manager = (HeapManager*)malloc(sizeof(HeapManager));
	if (manager != NULL) {
		if (maximal_heap_count > 0) {
			manager->heap_array = (Heap*)malloc(maximal_heap_count * sizeof(Heap));
			if(manager->heap_array != NULL)
				for (int i = 0; i < maximal_heap_count; i++)
					manager->heap_array[i] = NULL; ///< inicijalizacija svih mesta za heap-ove na NULL. Potrebna za dodavanje heap-ova.
			else {
				free(manager); ///< Oslobadja se vec zauzeta memorija i inicijalizacija se proglasava neuspesnom.
				return NULL;
			}				
		}
		else {
			free(manager); ///< Oslobadja se vec zauzeta memorija i inicijalizacija se proglasava neuspesnom.
			return NULL;
		}
	
		if (heap_size > 0)
			manager->heap_size = heap_size;
		else
			manager->heap_size = 50000000; ///< default velicina "default" heap-a.
		manager->max_heaps = maximal_heap_count;
		manager->heap_count = 0;
		manager->current_heap = 0;
		InitializeCriticalSection(&manager->manager_mutex);
	}
	return manager;
}

void HeapManagerOperations_destroy_manager(HeapManager** manager) {
	if (manager != NULL) {
		HeapManager* temp = *manager;
		if (temp != NULL) {
			if(temp->heap_array != NULL)
				free(temp->heap_array);
			DeleteCriticalSection(&temp->manager_mutex);
			free(temp);
			manager = NULL;

		}
	}
}

void HeapManagerOperations_destroy_manager_with_heaps(HeapManager** manager) {
	if (manager != NULL) {
		HeapManager* temp = *manager;
		if (temp != NULL) {
			if (temp->heap_array != NULL) {
				/// Pored oslobadjanja niza heap-ova, vrsi se i unistavanje heap-ova.
				for (int i = 0; i < temp->max_heaps; i++) {
					if (temp->heap_array[i] != NULL) {
						HeapDestruction_destroy_heap(temp->heap_array[i]); 
					}
				}
				free(temp->heap_array);
			}
			DeleteCriticalSection(&temp->manager_mutex);
			free(temp);
			manager = NULL;
		}
	}
}