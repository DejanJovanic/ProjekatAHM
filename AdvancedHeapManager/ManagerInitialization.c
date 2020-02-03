#include "ManagerInitialization.h"
#include "Dictionary.h"
/// Funkcija inicijalizuje manager pa tabelu.
/// Ako je manager vec inicijalizovan, vraca false.
/// Ako manager nije inicijalizovan, a recnik jeste vratice true i nastavice da koristi vec inicijalizovan recnik.
BOOL ManagerInitialization_initialize_manager(unsigned heap_count) {
	BOOL ret = TRUE;

		/// Provera da li je heap_count > 0, vraca FALSE ako nije.
		if (heap_count > 0)
			_manager = HeapManagerInitialization_initialize_heap_manager(0, heap_count); ///< inicijalizuje manager.
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
			HeapManagerInitialization_destroy_manager_with_heaps(&_manager);
		else {
			ret = _Dictionary_create(1000);
		}

	return ret;
}

/// Unistava i recnik i manager.
/// Ako je bar jedno uspesno unisteno vraca true.
BOOL ManagerInitialization_destroy_manager()
{
	BOOL ret = FALSE;

	if (_manager != NULL) {
		HeapManagerInitialization_destroy_manager_with_heaps(&_manager);
		ret = TRUE;
	}
	if (_dictionary != NULL) {
		_Dictionary_destroy();
		ret = TRUE;
	}
	
	return ret;
}