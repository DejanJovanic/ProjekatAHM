#include "stdio.h"
#include "..\Manager\ManagerInitialization.h"
#include "..\Manager\ManagerOperations.h"


int main() {
	ManagerInitialization_initialize_manager(5);
	void* items[10];
	for (int i = 0; i < 10; i++) {
		items[i] = thread_malloc(100);
	}
	printf("\nAllocated");
	for (int i = 0; i < 10; i++) {
		thread_free(items[i]);
	}
	printf("\nFreed");
	ManagerInitialization_destroy_manager();

	return 0;
}