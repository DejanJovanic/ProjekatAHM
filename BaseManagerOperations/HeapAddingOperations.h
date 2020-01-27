#pragma once
#include "Structs.h"
#include "..\HeapOperations\HeapCreation.h"
#include "..\HeapOperations\HeapManipulation.h"
#include "..\HeapOperations\HeapDestruction.h"

/**
* Funkcija koja u heap manager dodaje heap predodredjene maksimalne velicine, cija je inicijalna komitovana memorija jednaka 1/4 
* maksimalne memorije heap-a.
* Vrednost maksimalne velicine heap-a se uzima iz prosledjenog HeapManager objekta.
* HeapManager objekat mora biti inicijalizovan, u suprotnom ce sama operacija baciti exception.
* U slucaju da je pokazivac na manager objekat NULL ili nema mesta za novi heap u HeapManager-u, rezultat operacije ce biti FALSE.
* U slucaju da nije moguce stvoriti nov heap, rezultat operacije ce biti FALSE.
*
* manager: pokazivac na inicijalizovan HeapManager objekat, u koji se smesta novi heap.
* out_heap: pokazivac na Handle heap-a, u koji ce posle operacije pokazivati na novo-dodat heap.
*
* return: BOOL vrednost koja oznacava uspesnost operacije.
*/
BOOL HeapAddingOperations_add_default_heap(HeapManager* manager, Heap* out_heap);

/**
* Funkcija koja u heap manager dodaje heap predodredjene maksimalne velicine, cija je inicijalna komitovana memorija jednaka 1/4
* maksimalne memorije heap-a. Takodje, vrsi se alokacija memorije iz novo-dodatog heap-a.
* Vrednost maksimalne velicine heap-a se uzima iz prosledjenog HeapManager objekta.
* HeapManager objekat mora biti inicijalizovan, u suprotnom ce sama operacija baciti exception.
* Operacija izvrsava alokaciju memorije u novo-dodat heap, ciji je broj bajta prosledjen.
* U slucaju da je pokazivac na manager objekat NULL, nema mesta za novi heap u HeapManager-u ili prosledjena velicina memorije za alokaciju je <= 0, rezultat operacije ce biti FALSE.
* U slucaju da nije moguce stvoriti nov heap, rezultat operacije ce biti FALSE.
* U slucaju da je heap uspesno stvoren, a nije moguce alocirati memoriju, heap ce biti unisten i rezultat operacije ce biti FALSE.
*
* manager: pokazivac na inicijalizovan HeapManager objekat, u koji se smesta novi heap.
* out_heap: pokazivac na Handle heap-a, u koji ce posle operacije pokazivati na novo-dodat heap.
* memory_size: broj bajta koji je potrebno alocirati u novo-dodat-om heap-u.
* out_pointer: pokazivac na pokazivac koji ce pokazivati na alociranu memoriju.
*
* return: BOOL vrednost koja oznacava uspesnost operacije.
*/
BOOL HeapAddingOperations_add_default_heap_with_alloc(HeapManager* manager, Heap* out_heap,int memory_size,void** out_pointer);


/**
* Funkcija koja u heap manager dodaje heap predodredjene maksimalne velicine, cija je inicijalna komitovana memorija jednaka 
* maksimalnoj memoriji heap-a.
* Vrednost maksimalne velicine heap-a se prosledjuje.
* HeapManager objekat mora biti inicijalizovan, u suprotnom ce sama operacija baciti exception.
* U slucaju da je pokazivac na manager objekat NULL ili nema mesta za novi heap u HeapManager-u, rezultat operacije ce biti FALSE.
* U slucaju da nije moguce stvoriti nov heap, rezultat operacije ce biti FALSE.
*
* manager: pokazivac na inicijalizovan HeapManager objekat, u koji se smesta novi heap.
* out_heap: pokazivac na Handle heap-a, u koji ce posle operacije pokazivati na novo-dodat heap.
* heap_size: maksimalna velicina heap-a u bajtima.
*
* return: BOOL vrednost koja oznacava uspesnost operacije.
*/
BOOL HeapAddingOperations_add_big_heap(HeapManager* manager, Heap* out_heap, int heap_size);

/**
* Funkcija koja u heap manager dodaje heap predodredjene maksimalne velicine, cija je inicijalna komitovana memorija jednaka 
* maksimalnoj memoriji heap-a. Takodje, vrsi se alokacija memorije iz novo-dodatog heap-a.
* Vrednost maksimalne velicine heap-a se prosledjuje.
* HeapManager objekat mora biti inicijalizovan, u suprotnom ce sama operacija baciti exception.
* Operacija izvrsava alokaciju memorije u novo-dodat heap, ciji je broj bajta jednak maksimalnoj velicini heap-a.
* U slucaju da je pokazivac na manager objekat NULL ili nema mesta za novi heap u HeapManager-u, rezultat operacije ce biti FALSE.
* U slucaju da nije moguce stvoriti nov heap, rezultat operacije ce biti FALSE.
* U slucaju da je heap uspesno stvoren, a nije moguce alocirati memoriju, heap ce biti unisten i rezultat operacije ce biti FALSE.
*
* manager: pokazivac na inicijalizovan HeapManager objekat, u koji se smesta novi heap.
* out_heap: pokazivac na Handle heap-a, u koji ce posle operacije pokazivati na novo-dodat heap.
* memory_size: broj bajta koji je potrebno alocirati u novo-dodat-om heap-u.
* out_pointer: pokazivac na pokazivac koji ce pokazivati na alociranu memoriju.
* out_pointer: pokazivac na pokazivac koji ce pokazivati na alociranu memoriju.
*
* return: BOOL vrednost koja oznacava uspesnost operacije.
*/
BOOL HeapAddingOperations_add_big_heap_with_alloc(HeapManager* manager, Heap* out_heap, int heap_size,void** out_pointer);

/**
* Funkcija koja u heap manager dodaje heap "beskonacne" maksimalne velicine, cija je inicijalna komitovana memorija jednaka prosledjenoj vrednosti.
* HeapManager objekat mora biti inicijalizovan, u suprotnom ce sama operacija baciti exception.
* U slucaju da je pokazivac na manager objekat NULL ili nema mesta za novi heap u HeapManager-u, rezultat operacije ce biti FALSE.
* U slicaju da je prosledjena inicijalna velicina komitovane memorije < 0, bice stvoren heap sa inicijalnom komitovanom memorijom od 50 MB.
* U slucaju da nije moguce stvoriti nov heap, rezultat operacije ce biti FALSE.
*
* manager: pokazivac na inicijalizovan HeapManager objekat, u koji se smesta novi heap.
* out_heap: pokazivac na Handle heap-a, u koji ce posle operacije pokazivati na novo-dodat heap.
* initial_commited_bytes: inicijana velicina komitovane memorije u byte-ima.
*
* return: BOOL vrednost koja oznacava uspesnost operacije.
*/
BOOL HeapAddingOperations_add_infinite_heap(HeapManager* manager, Heap* out_heap, int initial_commited_size);

/**
* Funkcija koja u heap manager dodaje heap "beskonacne" maksimalne velicine, cija je inicijalna komitovana memorija jednaka prosledjenoj vrednosti. Takodje, vrsi se alokacija memorije iz novo-dodatog heap-a.
* HeapManager objekat mora biti inicijalizovan, u suprotnom ce sama operacija baciti exception.
* Operacija izvrsava alokaciju memorije u novo-dodat heap, ciji je broj bajta prosledjen.
* U slucaju da je pokazivac na manager objekat NULL, nema mesta za novi heap u HeapManager-u ili prosledjena velicina memorije za alokaciju je <= 0, rezultat operacije ce biti FALSE.
* U slicaju da je prosledjena inicijalna velicina komitovane memorije < 0, bice stvoren heap sa inicijalnom komitovanom memorijom od 50 MB.
* U slucaju da nije moguce stvoriti nov heap, rezultat operacije ce biti FALSE.
* U slucaju da je heap uspesno stvoren, a nije moguce alocirati memoriju, heap ce biti unisten i rezultat operacije ce biti FALSE.

*
* manager: pokazivac na inicijalizovan HeapManager objekat, u koji se smesta novi heap.
* out_heap: pokazivac na Handle heap-a, u koji ce posle operacije pokazivati na novo-dodat heap.
* memory_size: broj bajta koji je potrebno alocirati u novo-dodat-om heap-u.
* initial_commited_bytes: inicijana velicina komitovane memorije u byte-ima.
* out_pointer: pokazivac na pokazivac koji ce pokazivati na alociranu memoriju.
*
* return: BOOL vrednost koja oznacava uspesnost operacije.
*/
BOOL HeapAddingOperations_add_infinite_heap_with_alloc(HeapManager* manager, Heap* out_heap, int memory_size, int initial_commited_size, void** out_pointer);
