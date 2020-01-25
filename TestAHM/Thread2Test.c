#include "Thread2Test.h"

int a = 0;
CRITICAL_SECTION mutex;

void StartTest2()
{
	clock_t start_time, end_time;
	double cpu_time_used;

	ManagerInitialization_initialize_manager(5); //5 je broj hipova
	InitializeCriticalSection(&mutex);

	DWORD ids[2];
	HANDLE threads[2];

	start_time = clock();
	for (int i = 0; i < 2; i++){

		threads[i] = CreateThread(NULL, 0, &Test2, NULL, 0, &ids[i]);
	}

	int temp = 0;
	while(1)
	{
		EnterCriticalSection(&mutex);
		temp = a;
	
			LeaveCriticalSection(&mutex);
			if (temp == 2)
				break;
	}
	end_time = clock();

	cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

	printf("\n Time for allocate and free with 2 threads in seconds %f\n", cpu_time_used);

	for (int i = 0; i < 2; i++) {

		CloseHandle(threads[i]);
	}
	a = 0;
	temp = 0;
	ManagerInitialization_destroy_manager();
	DeleteCriticalSection(&mutex);
	/*start_time = clock();
	for (int i = 0; i < 2; i++) {

		threads[i] = CreateThread(NULL, 0, &Test2Malloc, NULL, 0, &ids[i]);
	}

	while (1)
	{
		EnterCriticalSection(&mutex);
		temp = a;

		LeaveCriticalSection(&mutex);
		if (temp == 2)
			break;
	}
	end_time = clock();

	cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

	printf("\n Time for allocate and free with MALLOC function in seconds %f\n", cpu_time_used);*/

}
DWORD WINAPI Test2(LPVOID lpParam) {
	void* items[10000];

	for (int i = 0; i < 10000; i++) {
		items[i] = thread_malloc(400000);
	}

	for (int i = 0; i < 10000; i++) {
		if(items[i] != NULL)
			thread_free(items[i]);
	}

	EnterCriticalSection(&mutex);
	a++;
	LeaveCriticalSection(&mutex);
	return 0;

}

/*DWORD WINAPI Test2Malloc(LPVOID lpParam)
{
	void* items[10000];

	for (int i = 0; i < 10000; i++) {
		items[i] = malloc(200000);
		
	}

	for (int i = 0; i < 10000; i++) {
		free(items[i]);
	}

	EnterCriticalSection(&mutex);
	a++;
	LeaveCriticalSection(&mutex);
	return 0;
}*/