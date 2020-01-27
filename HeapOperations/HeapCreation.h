#pragma once
#include "Windows.h"
#include "heapapi.h"

typedef HANDLE Heap;

/**
* Funkcija koja pravi heap sa maksimalnom velicinom koja se prosledjuje.
* Inicijalna komitovana kolicina memorije je 1/4 maksimalne velicine heap-a.
* U slucaju da heap nije moguce stvoriti, ili je prosledjena vrednost < 0, povratna vrednost je NULL.
*
* heap_size: maksimalna velicina heap-a u byte-ima.
*
* return: Handle na stvoren heap (NULL u slucaju neuspesnog stvaranja heap-a).
*/
Heap HeapCreation_create_default_heap(int heap_size);

/**
* Funkcija koja pravi heap sa maksimalnom velicinom koja se prosledjuje.
* Inicijalna komitovana kolicina memorije je maksimalnoj velicini heap-a.
* U slucaju da heap nije moguce stvoriti, ili je prosledjena vrednost < 0, povratna vrednost je NULL.
*
* heap_size: maksimalna velicina heap-a u byte-ima.
*
* return: Handle na stvoren heap (NULL u slucaju neuspesnog stvaranja heap-a).
*/
Heap HeapCreation_create_big_heap(int heap_size);

/**
* Funkcija koja pravi heap cija se velicina "beskonacno" povecava.
* Ako je prosledjena vrednost < 0, stvara se heap sa inicijalnom komitovanom velicinom od 50 MB.
* U slucaju da heap nije moguce stvoriti, povratna vrednost je NULL.
*
* initial_commited_bytes: inicijana velicina komitovane memorije u byte-ima.
*
* return: Handle na stvoren heap (NULL u slucaju neuspesnog stvaranja heap-a).
*/
Heap HeapCreation_create_infinite_heap(int initial_commited_bytes);

/**
* Funkcija koja pravi heap cija se velicina "beskonacno" povecava.
* Heap nije "thread-safe".
* Ako je prosledjena vrednost < 0, stvara se heap sa inicijalnom komitovanom velicinom od 50 MB.
* U slucaju da heap nije moguce stvoriti, povratna vrednost je NULL.
*
* initial_commited_bytes: inicijana velicina komitovane memorije u byte-ima.
*
* return: Handle na stvoren heap (NULL u slucaju neuspesnog stvaranja heap-a).
*/
Heap HeapCreation_create_infinite_heap_unlocked(int initial_commited_bytes);

