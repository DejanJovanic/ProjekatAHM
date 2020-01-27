#include "ManagerInitialization.h"


inline void node_free_function(HashNode* node) {
	HeapManipulation_free_memory(node, _dictionary._dict_heap);
}
inline void* node_allocate_function() {
	return HeapManipulation_allocate_memory(sizeof(HashNode), _dictionary._dict_heap);
}
inline void* bucket_list_allocating_function(int buckets) {
	return HeapManipulation_allocate_memory(sizeof(HashNode*) * buckets, _dictionary._dict_heap);
}
inline void bucket_list_free_function(HashNode** table) {
	HeapManipulation_free_memory(table, _dictionary._dict_heap);
}

/// Funkcija inicijalizuje manager pa tabelu.
/// Ako je manager vec inicijalizovan, vraca false.
/// Ako manager nije inicijalizovan, a recnik jeste vratice true i nastavice da koristi vec inicijalizovan recnik.
BOOL ManagerInitialization_initialize_manager(unsigned heap_count) {
	BOOL ret = TRUE;

	if (_manager != NULL) {

		/// Provera da li je heap_count > 0, vraca FALSE ako nije.
		if (heap_count > 0)
			_manager = HeapManagerOperations_initialize_heap_manager(0, heap_count); ///< inicijalizuje manager.
		else
			return FALSE;

		Heap heap;

		for (unsigned i = 0; i < heap_count; i++) {
			if (!HeapAddingOperations_add_infinite_heap(_manager, &heap, 50000000)) {
				ret = FALSE;
				break;
			}
		}
		/// Ako su svi heap-ovi uspesno dodati nastavlja dalje.
		if (ret == FALSE)
			HeapManagerOperations_destroy_manager_with_heaps(&_manager);
		else {
			if (_dictionary._is_initialized == FALSE) {
				InitializeCriticalSection(&_dictionary._cs);

				/// Pokusava da napravi privatni heap u koji ce bit smesteni heap tabela i svi njeni elementi.
				/// Takodje, pokusava da napravi hash tabelu i tada vraca TRUE.
				if ((_dictionary._dict_heap = HeapCreation_create_infinite_heap_unlocked(0)) != NULL) {
					_dictionary._table = HeapManipulation_allocate_memory(sizeof(HashTable), _dictionary._dict_heap);
					
					/// Inicijalizuje hash tabelu
					if (_dictionary._table != NULL && HashTable_initialize_table(_dictionary._table, 1000, compare_keys, bucket_list_allocating_function, bucket_list_free_function, node_allocate_function, node_free_function))
						_dictionary._is_initialized = TRUE;
				}
				else {
					DeleteCriticalSection(&_dictionary._cs);
					HeapManagerOperations_destroy_manager_with_heaps(&_manager);
					ret = FALSE;
				}
			}
		}
	}
	else
		return FALSE;

	return ret;
}

/// Unistava i recnik i manager.
/// Ako je bar jedno uspesno unisteno vraca true.
BOOL ManagerInitialization_destroy_manager()
{
	BOOL ret = FALSE;

	if (_manager != NULL) {
		HeapManagerOperations_destroy_manager_with_heaps(&_manager);
		ret = TRUE;
	}
	if (_dictionary._is_initialized) {
		EnterCriticalSection(&_dictionary._cs);
			HashTable_deinitialize_table(_dictionary._table); ///< Deinicijalizuj hash tabelu.
			HeapManipulation_free_memory(_dictionary._table, _dictionary._dict_heap); ///< oslobodi memoriju hash tabele.
		LeaveCriticalSection(&_dictionary._cs);

		DeleteCriticalSection(&_dictionary._cs);
		HeapDestruction_destroy_heap(_dictionary._dict_heap); ///< Unisti privatni heap recnika.
		_dictionary._is_initialized = FALSE;
		ret = TRUE;
	}
	
	return ret;
}