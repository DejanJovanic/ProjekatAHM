#pragma once
#include <stdlib.h>
#include "DataSerializationOperations.h"

void Serialize(pak* head, zpak**serializedData, int n) {
	*serializedData = (zpak*)malloc(sizeof(zpak) * n);

	for (int i = 0; i < n; i++) {
		(*serializedData)[i].data = head->data;
		(*serializedData)[i].size = head->size;
		head = head->next;
	}
}

void Deserialize(pak** head, pak**tail, char* niz, int brojBajtova) {
	zpak* nizPaketa = (zpak*)niz;

	for (int i = 0; i < (brojBajtova / (int)sizeof(zpak)); i++) {
		pak *p = (pak*)malloc(sizeof(pak));
		p->data = nizPaketa[i].data;
		p->next = NULL;

		if (*head == NULL) {
			*head = *tail = p;
			continue;
		}

		(*tail)->next = p;
		*tail = p;
	}

	return;
}