#include "List.h"


void Data_push(pak** head, pak** tail, int size, char* data){

	pak* packet = (pak*)malloc(sizeof(pak));
	packet->data = data;
	packet->size = size;
	packet->next = NULL;

	if (*head == NULL) {
		*head = *tail = packet;
		return;
	}

	//tekuci kraj da pokazuje na novi paket
	(*tail)->next = packet;
	//novi kraj je sada ovaj tek napravljeni paket
	(*tail) = packet;

}
pak Data_pop(pak** head, pak** tail) {
	pak packet = (**head);
	(*head) = (*head)->next;
	return packet;
}
void Data_print_list(pak* head) {
	while (head != NULL) {
		printf("%s, length: %d", head->data, head->size);
		head = head->next;
	}
}
