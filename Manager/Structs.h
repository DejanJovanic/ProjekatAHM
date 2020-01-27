#pragma once
#include "..\BaseManagerOperations\Structs.h"
#include "..\Collections\HashTable.h"

typedef struct dict {
	BOOL _is_initialized; ///< polje koje oznacava da li je recnik inicijalizovan.
	HashTable* _table; ///< pokazivac na HashTable objekat.
	Heap _dict_heap; ///< Handle privatnog heap-a recnika koji sadrzi hash tabelu u sve njene elemente. Korisit se heap koji nije thread-safe.
	CRITICAL_SECTION _cs; ///< Propusnica kriticne sekcije, koja omogucava thread-safe operacije nad recnikom.
} Dictionary;