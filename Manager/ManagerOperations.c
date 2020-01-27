#include "ManagerOperations.h"
/// Zauzima trazenu memoriju.
/// To radi tako sto od manager-a trazi Heap iz kojeg moze da trazi memoriju,i tada radi alokaciju.
/// Heap se dobija po Round robin tehnici.
/// Ako se memorija uspesno alocira, ubacuje se u recnik pointer -> heap, sto omogucuje dealokaciju memorije.
void* thread_malloc(int bytes) {
	if (_manager == NULL && !_dictionary._is_initialized)
		exit(MANAGER_UNINITIALIZED_ERROR);

	Heap heap;
	void* pointer = NULL;
	if (bytes > 0 && HeapManipulationOperations_get_heap(_manager, &heap)) { ///< dobavlja heap
		pointer = HeapManipulation_allocate_memory(bytes, heap);
		BOOL is_inserted = FALSE;
		if (pointer != NULL) {
			EnterCriticalSection(&_dictionary._cs);
				is_inserted = HashTable_insert(_dictionary._table, pointer,heap); ///< ubacuje u recnik.
			LeaveCriticalSection(&_dictionary._cs);
		}
		if (is_inserted == FALSE) {
			HeapManipulation_free_memory(pointer, heap);
			pointer = NULL;
		}
	}

	return pointer;
}


/// Oslobadja memorijski blok na koji pokazuje pokazivac.
/// Trazi u recniku pokazivac, kako bi dobio heap na koji je alocirana memorija, a potom radi i oslobadjanje memorije iz tog heap-a.
void thread_free(void* pointer) {
	if (pointer == NULL)
		exit(NULL_SENT_ERROR);

	if (!_dictionary._is_initialized && _manager == NULL)
		exit(MANAGER_UNINITIALIZED_ERROR);

	Heap heap = NULL;
	BOOL is_deleted = FALSE;

	EnterCriticalSection(&_dictionary._cs);
		is_deleted = HashTable_delete(_dictionary._table, pointer, &heap);
	LeaveCriticalSection(&_dictionary._cs);
	
	if(is_deleted)
		HeapManipulation_free_memory(pointer, heap);

}