#include "ManagerOperations.h"
#include "Dictionary.h"
/// Zauzima trazenu memoriju.
/// To radi tako sto od manager-a trazi Heap iz kojeg moze da trazi memoriju,i tada radi alokaciju.
/// Heap se dobija po Round robin tehnici.
/// Ako se memorija uspesno alocira, ubacuje se u recnik pointer -> heap, sto omogucuje dealokaciju memorije.
void* thread_malloc(int bytes) {
	if (_manager == NULL && _dictionary == NULL)
		exit(MANAGER_UNINITIALIZED_ERROR);

	Heap heap;
	void* pointer = NULL;
	if (bytes > 0) { ///< dobavlja heap
		pointer = HeapManipulationOperations_get_memory(_manager, bytes,&heap);
		BOOL is_inserted = FALSE;
		if (pointer != NULL) {
			is_inserted = _Dictionary_insert(pointer, heap);
		}
		else {
			int a = 2;
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

	if (_dictionary == NULL && _manager == NULL)
		exit(MANAGER_UNINITIALIZED_ERROR);

	Heap heap = NULL;
	BOOL is_removed = _Dictionary_remove(pointer,&heap);

	if (is_removed)
		HeapManipulationOperations_free_memory(_manager, pointer, heap);

}