#pragma once
#include <stdlib.h>
#include <stdio.h>
#include "Windows.h"

/**
*	Paket() - Struktura podataka koja se koristi za listu
*
*	next: pokazivac na sledeci element liste
*	size: duzina niza karaktera
*	data: niz karaktera
**/
typedef struct Paket {
	struct Paket* next;
	int size;
	char *data;
}pak;

/**
*	Zip_paket() - Struktura podataka koja se koristi za serijalizovanu listu koja se salje kroz mrezu (bez pokazivaca)
*
*	size: duzina niza karaktera
*	data: niz karaktera
**/
typedef struct Zip_paket {
	int size;
	char *data;
}zpak;

/**
*	Data_push() - Kreira i ubacuje paket u listu paketa
*
*	head: pokazivac na pocetak liste
*	tail: pokazivac na kraj liste
*	size: duzina niza karaktera
*	data: niz karaktera
**/
void Data_push(pak** head, pak** tail, int size, char* data);
/**
*	Data_pop() - Izbacuje paket iz liste i vraca ga kao povratnu vrednost
*
*	head: pokazivac na pocetak liste
*	tail: pokazivac na kraj liste
**/
pak Data_pop(pak** head, pak** tail);
/**
*	Data_print_list() - Stampa kompletnu listu na terminal
*
*	head: pokazivac na pocetak liste
**/
void Data_print_list(pak* head);