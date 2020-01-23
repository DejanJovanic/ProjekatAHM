#include "stdio.h"
#include "time.h"
#include "..\Manager\ManagerInitialization.h"
#include "..\Manager\ManagerOperations.h"


int main() {
	ManagerInitialization_initialize_manager(5); //5 je broj hipova
	clock_t start_time, end_time;
	double cpu_time_used;

	void* items[10000];
	int count = 0;

	start_time = clock();
	for (int i = 0; i < 10000; i++) {
		items[i] = thread_malloc(400000);
		if (items[i] == NULL)
			count++;
	}

	for (int i = 0; i < 10000; i++) {
		thread_free(items[i]);
	}

	ManagerInitialization_destroy_manager();
	end_time = clock();

	cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

	printf("\n Time for allocate and free in seconds %f", cpu_time_used);
	return 0;
}