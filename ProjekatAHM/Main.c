#include "stdio.h"
#include "..\Manager\ManagerInitialization.h"
#include "..\Manager\ManagerOperations.h"


int main() {
	ManagerInitialization_initialize_manager(5);
	void* items[10000];
	int count = 0;
	for (int i = 0; i < 10000; i++) {
		items[i] = thread_malloc(200000);
		if (items[i] == NULL)
			count++;
	}
	printf("\nAllocated");

	for (int i = 0; i < 10000; i++) {
		thread_free(items[i]);
	}
	printf("\nFreed");
	ManagerInitialization_destroy_manager();

	return 0;
}