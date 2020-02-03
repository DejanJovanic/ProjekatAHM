#include "Message.h"


int Data_generate_message(char ** message, int random_length)
{
	int length = (random_length * 2000000) + 1 + 1;	//prvi +1 da nikad ne bude 0, drugi +1 za NULL terminator
	*message = malloc(sizeof(char) * length);
	for (int i = 0; i < length - 1; i++) {
		(*message)[i] = '0' + (i % 10);
	}
	(*message)[length - 1] = 0;

	return length;
}
