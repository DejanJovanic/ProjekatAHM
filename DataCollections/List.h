#pragma once
#include <stdlib.h>
#include "Windows.h"

typedef struct Paket {
	struct Paket* head;
	struct Paket* tail;
	int size;
	char *data;
}pak;

typedef struct ZipPaket {
	int size;
	char *data;
}zpak;

pak* PacketCreate(pak* head, pak* tail, int size, char* data);
BOOL PacketDelete(pak* head, pak* tail, int size, char* data);
void Push(pak* head, pak* tail, int size, char* data);
void Pop(pak* head, pak* tail);