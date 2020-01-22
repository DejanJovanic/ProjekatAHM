#include "Thread1Test.h"

HANDLE hSemaphore;
void StartTest1()
{

	clock_t start_time, end_time;
	double cpu_time_used;
	ManagerInitialization_initialize_manager(5); //5 je broj hipova
	
	DWORD id;
	HANDLE thread1;

	hSemaphore = CreateSemaphore(0, 0, 1, NULL);
	start_time = clock();
	thread1 = CreateThread(NULL, 0, &Test1, NULL, 0, &id);
	WaitForSingleObject(hSemaphore, INFINITE);
	end_time = clock();

	cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

	printf("\n Time for allocate and free with 1 thread in seconds %f\n", cpu_time_used);
	CloseHandle(thread1);
	CloseHandle(hSemaphore);
	ManagerInitialization_destroy_manager();

	/*hSemaphore = CreateSemaphore(0, 0, 1, NULL);
	start_time = clock();
	thread1 = CreateThread(NULL, 0, &Test1Malloc, NULL, 0, &id);
	WaitForSingleObject(hSemaphore, INFINITE);
	end_time = clock();

	cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

	printf("\n Time for allocate and free with 1 thread with MALLOC in seconds %f\n", cpu_time_used);*/
	
}
DWORD WINAPI Test1(LPVOID lpParam) {
	void* items[10000];

	for (int i = 0; i < 10000; i++) {
		items[i] = thread_malloc(400000);
	}

	for (int i = 0; i < 10000; i++) {
		thread_free(items[i]);
	}
	
	ReleaseSemaphore(hSemaphore, 1, NULL);
	return 0;

}

/*DWORD WINAPI Test1Malloc(LPVOID lpParam)
{
	void* items[10000];

	for (int i = 0; i < 10000; i++) {
		items[i] = malloc(400000);

	}

	for (int i = 0; i < 10000; i++) {
		free(items[i]);
	}


}*/