#pragma once

typedef struct Paket {
	int num;		// number
	struct Paket* next;
}pak;

typedef struct ZPaket {
	int num;		// number
}zpak;

void Serialize(pak*, zpak**, int);
void Deserialize(pak**, pak**, char*, int);