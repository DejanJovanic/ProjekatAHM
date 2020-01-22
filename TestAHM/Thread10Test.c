#include "Thread10Test.h"
int c = 0;
CRITICAL_SECTION mutex;

void StartTest10()
{

	clock_t start_time, end_time;
	double cpu_time_used;
	ManagerInitialization_initialize_manager(5); //5 je broj hipova
	InitializeCriticalSection(&mutex);
	DWORD ids[10];
	HANDLE threads[10];
	start_time = clock();
	for (int i = 0; i < 10; i++) {

		threads[i] = CreateThread(NULL, 0, &Test10, NULL, 0, &ids[i]);
	}

	int temp = 0;

	while (1)
	{
		EnterCriticalSection(&mutex);
		temp = c;

		LeaveCriticalSection(&mutex);
		if (temp == 10)
			break;
	}
	
	end_time = clock();
	c = 0;
	temp = 0;
	cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

	printf("\n Time for allocate and free with 10 threads  in seconds %f\n", cpu_time_used);
	for (int i = 0; i < 10; i++) {

		CloseHandle(threads[i]);
	}
	ManagerInitialization_destroy_manager();

	/*start_time = clock();
	for (int i = 0; i < 10; i++) {

		threads[i] = CreateThread(NULL, 0, &Test10Malloc, NULL, 0, &ids[i]);
	}

	while (1)
	{
		EnterCriticalSection(&mutex);
		temp = b;

		LeaveCriticalSection(&mutex);
		if (temp == 10)
			break;
	}
	end_time = clock();

	cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

	printf("\n Time for allocate and free with 10 threads with MALLOC in seconds %f\n", cpu_time_used);*/
}
DWORD WINAPI Test10(LPVOID lpParam) {


	void* items[10000];



	for (int i = 0; i < 10000; i++) {
		items[i] = thread_malloc(40000);
	}

	for (int i = 0; i < 10000; i++) {
		thread_free(items[i]);
	}

	EnterCriticalSection(&mutex);
	c++;
	LeaveCriticalSection(&mutex);
	return 0;

}

/*DWORD WINAPI Test10Malloc(LPVOID lpParam)
{
	void* items[10000];


	for (int i = 0; i < 10000; i++) {
		items[i] = malloc(40000);
	}

	for (int i = 0; i < 10000; i++) {
		free(items[i]);
	}

	EnterCriticalSection(&mutex);
	c++;
	LeaveCriticalSection(&mutex);
	return 0;
}*/