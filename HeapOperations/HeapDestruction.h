#pragma once
#include "Windows.h"
#include "heapapi.h"

typedef HANDLE Heap;

/**
* Funkcija koja unistava prosledjen heap i invalidira handle na dati heap.
* Ako je prosledjena vrednost NULL, rezultat operacije ce biti FALSE.
* Funkcija je "thread-safe", ako je i heap "thread-safe".
*
* heap: Handle na heap koji je potrebno unistiti.
*
* return: BOOL vrednost koja oznacava da li je operacija uspesno izvrsena.
*/
BOOL HeapDestruction_destroy_heap(Heap heap);