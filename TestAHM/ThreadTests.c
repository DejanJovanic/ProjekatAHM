#include "ThreadTests.h"

void ThreadTests_custom_malloc_initialize(int number_of_threads){

	clock_t start_time, end_time;
	double cpu_time_used;
	int number_of_bytes = 400000 / number_of_threads;

	printf("\n\tCustom malloc i free funkcije\n");
	
	HANDLE* threads;
	threads = (HANDLE)malloc(number_of_threads * sizeof(HANDLE));
	
	start_time = clock();
	for (int i = 0; i < number_of_threads; i++) {
		*(threads + i) = CreateThread(NULL, 0, &ThreadTests_custom_malloc_and_custom_free, (LPVOID)number_of_bytes, 0, NULL);
	}

	for (int i = 0; i < number_of_threads; i++) {
		WaitForSingleObject(*(threads + i), INFINITE);
	}
	end_time = clock();

	cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

	printf("\nBroj tredova: %d\nPotrebno vreme za zauzimanje i oslobadjanje memorije: %f sekundi\n", number_of_threads, cpu_time_used);
	printf("\n----------------------------------------------------------------------\n");
	for (int i = 0; i < number_of_threads; i++) {
		CloseHandle(*(threads + i));
	}
	free(threads);


	return 0;
}
void ThreadTests_malloc_initialize(int number_of_threads){
	
	clock_t start_time, end_time;
	double cpu_time_used;
	int number_of_bytes = 400000 / number_of_threads;

	HANDLE* threads;
	threads = (HANDLE)malloc(number_of_threads * sizeof(HANDLE));
	printf("\n\tMalloc i free funkcije\n");

	start_time = clock();
	for (int i = 0; i < number_of_threads; i++) {
		*(threads + i) = CreateThread(NULL, 0, &ThreadTests_malloc_and_free, (LPVOID)number_of_bytes, 0, NULL);
	}

	for (int i = 0; i < number_of_threads; i++) {
		WaitForSingleObject(*(threads + i), INFINITE);
	}
	end_time = clock();

	cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

	printf("\nBroj tredova: %d\nPotrebno vreme za zauzimanje i oslobadjanje memorije: %f sekundi\n", number_of_threads, cpu_time_used);
	printf("\n----------------------------------------------------------------------\n");
	for (int i = 0; i < number_of_threads; i++) {
		CloseHandle(*(threads + i));
	}
	free(threads);
}

DWORD WINAPI ThreadTests_custom_malloc_and_custom_free(LPVOID lpParam) {

	void* items[10000];
	int number_of_bytes = (int)lpParam;

	for (int i = 0; i < 10000; i++) {
		items[i] = advanced_malloc(number_of_bytes);
	}

	for (int i = 0; i < 10000; i++) {
		if (items[i] != NULL)
		{
			advanced_free(items[i]);
		}
	}

	return 0;
}
DWORD WINAPI ThreadTests_malloc_and_free(LPVOID lpParam){

	void* items[10000];
	int number_of_bytes = (int)lpParam;

	for (int i = 0; i < 10000; i++) {
		items[i] = malloc(number_of_bytes);
	}

	for (int i = 0; i < 10000; i++) {
		if (items[i] != NULL)
			free(items[i]);
	}
	
	return 0;
}
