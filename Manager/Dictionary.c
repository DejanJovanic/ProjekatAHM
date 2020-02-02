#include "Structs.h"
#include "..\HeapOperations\HeapCreation.h"
#include "..\HeapOperations\HeapDestruction.h"
#include "..\HeapOperations\HeapManipulation.h"

extern Dictionary* _dictionary;

inline void node_free_function(HashNode* node) {
	HeapManipulation_free_memory_unlocked(node, _dictionary->_dict_heap);
}
inline void* node_allocate_function() {
	return HeapManipulation_allocate_memory_unlocked(sizeof(HashNode), _dictionary->_dict_heap);
}
inline void* bucket_list_allocating_function(int buckets) {
	return HeapManipulation_allocate_memory_unlocked(sizeof(HashNode*) * buckets, _dictionary->_dict_heap);
}
inline void bucket_list_free_function(HashNode** table) {
	HeapManipulation_free_memory_unlocked(table, _dictionary->_dict_heap);
}
BOOL static Dictionary_create(int minimal_size) {
	BOOL is_ok = FALSE;
	_dictionary = malloc(sizeof(Dictionary));
	if (_dictionary != NULL) {
		InitializeCriticalSection(&_dictionary->_cs);

		/// Pokusava da napravi privatni heap u koji ce bit smesteni heap tabela i svi njeni elementi.
		/// Takodje, pokusava da napravi hash tabelu i tada vraca TRUE.
		if ((_dictionary->_dict_heap = HeapCreation_create_infinite_heap_unlocked(0)) != NULL) {
			_dictionary->_table = HeapManipulation_allocate_memory(sizeof(HashTable), _dictionary->_dict_heap);

			/// Inicijalizuje hash tabelu
			if (_dictionary->_table != NULL && HashTable_initialize_table(_dictionary->_table, minimal_size, bucket_list_allocating_function, bucket_list_free_function, node_allocate_function, node_free_function))
				is_ok = TRUE;
			else {
				DeleteCriticalSection(&_dictionary->_cs);
				HeapDestruction_destroy_heap(_dictionary->_dict_heap);
			}
		}
		else {
			DeleteCriticalSection(&_dictionary->_cs);
		}
	}
	return is_ok;
}

BOOL static Dictionary_insert(void* key, void* value) {
	BOOL is_inserted = FALSE;
	EnterCriticalSection(&_dictionary->_cs);
		is_inserted = HashTable_insert(_dictionary->_table, key,value); ///< ubacuje u recnik.
	LeaveCriticalSection(&_dictionary->_cs);
	return is_inserted;
}

BOOL static Dictionary_remove(void* key, void** value){
	BOOL is_removed = FALSE;
	EnterCriticalSection(&_dictionary->_cs);
		is_removed = HashTable_delete(_dictionary->_table, key, value);
	LeaveCriticalSection(&_dictionary->_cs);
	return is_removed;
}

void static Dictionary_destroy() {
	if (_dictionary != NULL) {
		EnterCriticalSection(&_dictionary->_cs);
		HashTable_deinitialize_table(_dictionary->_table); ///< Deinicijalizuj hash tabelu.
		HeapManipulation_free_memory(_dictionary->_table, _dictionary->_dict_heap); ///< oslobodi memoriju hash tabele.
		LeaveCriticalSection(&_dictionary->_cs);

		DeleteCriticalSection(&_dictionary->_cs);
		HeapDestruction_destroy_heap(_dictionary->_dict_heap); ///< Unisti privatni heap recnika.
		free(_dictionary);
	}
}