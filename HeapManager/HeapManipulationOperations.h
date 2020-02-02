#pragma once
#include "Structs.h"
#include "..\HeapOperations\HeapManipulation.h"

/**
* Dobavlja Handle na heap u HeapManageru.
* Odredjivanje povratnog heap-a se vrsi Round robin tehnikom.
* U slucaju da je prosledjeni manager objekat NULL, rezultat operacije ce biti FALSE.
* U slucaju da se u manager-u ne nalazi nijedan heap, rezultat operacije ce biti FALSE.
* HeapManager objekat mora biti inicijalizovan, u suprotnom ce sama operacija baciti exception.
*
* manager: pokazivac na HeapManager objekta koji sadrzi heap koji ce biti vracen.
* out_heap: pokazivac na heap objekat, koji ce biti izmenjen tako da pokazuje na odabran heap.
*
* return: BOOL vrednost koja indicira na uspesnost izvrsene operacije.
*/
BOOL HeapManipulationOperations_get_heap(HeapManager* manager, Heap* out_heap);

void* HeapManipulationOperations_get_memory(HeapManager* manager, int memory_size);