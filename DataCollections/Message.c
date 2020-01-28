#include "Message.h"

int Data_generate_message(char** message) {
	srand(time(NULL));
	int length = rand() % 10 + 1 + 1;	//prvi +1 da nikad ne bude 0, drugi +1 za NULL terminator
	*message = malloc(sizeof(char) * length);
	for (int i = 0; i < length - 1; i++) {
		(*message)[i] = '0' + (i % 10);
	}
	(*message)[length - 1] = 0;
	return length;
}