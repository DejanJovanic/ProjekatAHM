#include "ManagerOperations.h"
#include "Dictionary.h"

/// Zauzima trazenu memoriju.
/// To radi tako sto od HeapManager-a trazi memoriju.
/// Ako se memorija uspesno alocira, ubacuje se u recnik pointer -> heap, sto omogucuje dealokaciju memorije.
void* advanced_malloc(int bytes) {

	if (_manager == NULL && _dictionary == NULL)
		exit(MANAGER_UNINITIALIZED_ERROR);

	Heap heap;
	void* pointer = NULL;
	if (bytes > 0) { 
		pointer = HeapManipulationOperations_get_memory(_manager, bytes,&heap);
		BOOL is_inserted = FALSE;
		if (pointer != NULL) {
			is_inserted = _Dictionary_insert(pointer, heap);
		}

		if (is_inserted == FALSE && pointer != NULL) {
			HeapManipulation_free_memory(pointer, heap);
			pointer = NULL;
		}
	}

	return pointer;
}


/// Oslobadja memorijski blok na koji pokazuje pokazivac.
/// Trazi u recniku pokazivac, kako bi dobio heap na koji je alocirana memorija, a potom radi i oslobadjanje memorije iz tog heap-a.
void advanced_free(void* pointer) {
	if (pointer == NULL)
		exit(NULL_SENT_ERROR);

	if (_dictionary == NULL && _manager == NULL)
		exit(MANAGER_UNINITIALIZED_ERROR);

	Heap heap = NULL;
	BOOL is_removed = _Dictionary_remove(pointer,&heap);

	if (is_removed)
		HeapManipulationOperations_free_memory(_manager, pointer, heap);

}