#pragma once
#include "Structs.h"
#include "..\HeapOperations\HeapCreation.h"
#include "..\HeapOperations\HeapDestruction.h"


/**
* Kreira i inicijalizuje heap manager.
* Heap manager ce se nalaziti na procesnom default heap-u.
* U slucaju neuspeha operacije se vraca NULL.
* Ako je prosledjen maksimalan broj heap-ova <= 0, rezultat operacije ce biti NULL.
* U slucaju da je prosledjena velicina heap-a <= 0, velicina "default" heap-a ce biti 50 MB.
*
* heap_size: velicina heap-a u byte-ima, koja predstavlja maksimalnu velicinu "default" heap-a.
* heap_count: maksimalan broj heap-ova.
*
* return: pokazivac na inicijalizovan HeapManager.
*/
HeapManager* HeapManagerInitialization_initialize_heap_manager(int heap_size, int maximal_heap_count);

/**
* Funkcija unistava heap manager i postavlja prosledjeni pokazivac na manager na NULL.
* Funkcija nece unistiti heap-ove.
* Funkcija ce osloboditi memoriju manager objekta.
*
* manager: pokazivac na pokazivac na objekat heap managera kojeg je potrebno unistiti. 
*/
void HeapManagerInitialization_destroy_manager(HeapManager** manager);

/**
* Funkcija unistava heap manager i postavlja prosledjeni pokazivac na manager na NULL.
* Funkcija ce unistiti i heap-ove i invalidirati njihove Handle-ove.
* Funkcija ce osloboditi memoriju manager objekta.
*
* manager: pokazivac na pokazivac na objekat heap managera kojeg je potrebno unistiti.
*/
void HeapManagerInitialization_destroy_manager_with_heaps(HeapManager** manager);