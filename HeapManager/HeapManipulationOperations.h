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

/**
* Dobavlja memoriju iz trenutnog heap-a.
* Odredjivanje trenutnog heap-a se vrsi Round robin tehnikom.
* U slucaju da je prosledjeni manager objekat NULL ili je prosledjena velicina memorije <= 0, rezultat operacije ce biti FALSE.
* U slucaju da se u manager-u ne nalazi nijedan heap, rezultat operacije ce biti FALSE.
* HeapManager objekat mora biti inicijalizovan, u suprotnom ce sama operacija baciti exception.
* Operacija je "thread-safe".
*
* manager: pokazivac na HeapManager objekta koji sadrzi heap koji ce biti vracen.
* memory_size: velicina memorije u bajtima koju je potrebno alocirati.
* out_heap: pokazivac na heap objekat, koji ce biti izmenjen tako da pokazuje na odabran heap.
*
* return: BOOL vrednost koja indicira na uspesnost izvrsene operacije.
*/
void* HeapManipulationOperations_get_memory(HeapManager* manager, int memory_size,Heap* out_heap);

/**
* Oslobadja prethodno zauzetu memoriju iz prosledjenog heap-a.
* U slucaju da je prosledjeni manager objekat NULL, pokazivac NULL ili heap NULL, rezultat operacije ce biti FALSE.
* U slucaju da prosledjeni pokazivac ne pokazuje na pocetak bloka koji je uzet iz prosledjenog heap-a, operacija ce baciti exception.
* Operacija je "thread-safe" ako je i sam heap thread-safe.
*
* manager: pokazivac na HeapManager objekta koji sadrzi heap koji ce biti vracen.
* pointer: pokazivac na zauzetu memoriju koju je potrebno osloboditi.
* heap: heap u kojeg je potrebno vratiti zauzetu memoriju.
*
* return: BOOL vrednost koja indicira na uspesnost izvrsene operacije.
*/
BOOL HeapManipulationOperations_free_memory(HeapManager* manager, void* pointer, Heap heap);