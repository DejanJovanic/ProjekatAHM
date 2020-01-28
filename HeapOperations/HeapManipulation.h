#pragma once
#include "Windows.h"
#include "heapapi.h"

typedef HANDLE Heap;

/**
* Funkcija koja alocira memoriju.
* Funkcija je "thread-safe", ako je i heap "thread-safe".
* U slucaju da je prosledjena vrednost byte-a < 0 , ili je heap NULL, funkcija vraca NULL pokazivac.
* U slucaju da sistem nije u mogucnosti da suplementira potrebnu memoriju, funkcija vraca NULL pokazivac.
*
* bytes: broj byte-a koje je potrebno alocirati.
* heap: Handle heap-a iz kojeg je potrebno alocirati memoriju.
*
* return: pokazivac na alociranu memoriju (NULL u slucaju neuspeha).
*/
void* HeapManipulation_allocate_memory(int bytes, Heap heap);

/**
* Funkcija koja alocira memoriju.
* Funkcija nije "thread-safe".
* U slucaju da je prosledjena vrednost byte-a < 0 , ili je heap NULL, funkcija vraca NULL pokazivac.
* U slucaju da sistem nije u mogucnosti da suplementira potrebnu memoriju, funkcija vraca NULL pokazivac.
*
* bytes: broj byte-a koje je potrebno alocirati.
* heap: Handle heap-a iz kojeg je potrebno alocirati memoriju.
*
* return: pokazivac na alociranu memoriju (NULL u slucaju neuspeha).
*/
void* HeapManipulation_allocate_memory_unlocked(int bytes, Heap heap);
/**
* Funkcija koja dealocira memoriju.
* Funkcija je "thread-safe", ako je i heap "thread-safe".
* U slucaju da je prosledjen pointer NULL pokazivac , ili je heap NULL, funkcija vraca NULL pokazivac.
* U slucaju da pokazivac pokazuje na heap koji je drugaciji od prosledjenog, aplikacija baca exception.
*
* pointer: pokazivac na pocetak prethodno alociranog memorijskog bloka.
* heap: Handle heap-a iz kojeg je potrebno alocirati memoriju.
*
* return: BOOL vrednost koja oznacava uspesnost operacije.
*/
BOOL HeapManipulation_free_memory(void* pointer, Heap heap);

/**
* Funkcija koja dealocira memoriju.
* Funkcija nije "thread-safe".
* U slucaju da je prosledjen pointer NULL pokazivac , ili je heap NULL, funkcija vraca NULL pokazivac.
* U slucaju da pokazivac pokazuje na heap koji je drugaciji od prosledjenog, aplikacija baca exception.
*
* pointer: pokazivac na pocetak prethodno alociranog memorijskog bloka.
* heap: Handle heap-a iz kojeg je potrebno alocirati memoriju.
*
* return: BOOL vrednost koja oznacava uspesnost operacije.
*/
BOOL HeapManipulation_free_memory_unlocked(void* pointer, Heap heap);
