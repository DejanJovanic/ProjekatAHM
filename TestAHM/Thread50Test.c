#include "Thread50Test.h"
int e = 0;
CRITICAL_SECTION mutex;

void StartTest50()
{

	clock_t start_time, end_time;
	double cpu_time_used;
	ManagerInitialization_initialize_manager(5); //5 je broj hipova
	InitializeCriticalSection(&mutex);
	DWORD ids[50];
	HANDLE threads[50];
	start_time = clock();
	for (int i = 0; i < 50; i++) {

		threads[i] = CreateThread(NULL, 0, &Test50, NULL, 0, &ids[i]);
	}

	int temp = 0;

	while (1)
	{
		EnterCriticalSection(&mutex);
		temp = e;

		LeaveCriticalSection(&mutex);
		if (temp == 50)
			break;
	}

	end_time = clock();
	e = 0;
	temp = 0;
	cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

	printf("\n Time for allocate and free with 50 threads  in seconds %f\n", cpu_time_used);
	for (int i = 0; i < 50; i++) {

		CloseHandle(threads[i]);
	}
	ManagerInitialization_destroy_manager();
	DeleteCriticalSection(&mutex);
	/*start_time = clock();
	for (int i = 0; i < 50; i++) {

		threads[i] = CreateThread(NULL, 0, &Test50Malloc, NULL, 0, &ids[i]);
	}

	while (1)
	{
		EnterCriticalSection(&mutex);
		temp = e;

		LeaveCriticalSection(&mutex);
		if (temp == 50)
			break;
	}
	end_time = clock();

	cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

	printf("\n Time for allocate and free with 50 threads with MALLOC in seconds %f\n", cpu_time_used);*/
}
DWORD WINAPI Test50(LPVOID lpParam) {

	void* items[10000];

	for (int i = 0; i < 10000; i++) {
		items[i] = thread_malloc(8000);
	}

	for (int i = 0; i < 10000; i++) {
		if(items[i] != NULL)
			thread_free(items[i]);
	}

	EnterCriticalSection(&mutex);
	e++;
	LeaveCriticalSection(&mutex);
	return 0;

}

/*DWORD WINAPI Test50Malloc(LPVOID lpParam)
{
	void* items[10000];


	for (int i = 0; i < 10000; i++) {
		items[i] = malloc(8000);
	}

	for (int i = 0; i < 10000; i++) {
		free(items[i]);
	}

	EnterCriticalSection(&mutex);
	e++;
	LeaveCriticalSection(&mutex);
	return 0;
}*/