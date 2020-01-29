#include "ThreadTests.h"

int main(int argc, char* argv[]) 
{
	if (argc != 2)
	{
		printf("Ne postoje argumenti komandne linije\n");
		return 0;
	}
	
	ThreadTests_custom_malloc_initialize(1, atoi(argv[1]));
	ThreadTests_custom_malloc_initialize(2, atoi(argv[1]));
	ThreadTests_custom_malloc_initialize(5, atoi(argv[1]));
	ThreadTests_custom_malloc_initialize(10, atoi(argv[1]));
	ThreadTests_custom_malloc_initialize(20, atoi(argv[1]));
	ThreadTests_custom_malloc_initialize(50, atoi(argv[1]));
	/*ThreadTests_malloc_initialize(1);
	ThreadTests_malloc_initialize(2);
	ThreadTests_malloc_initialize(5);
	ThreadTests_malloc_initialize(10);
	ThreadTests_malloc_initialize(20);
	ThreadTests_malloc_initialize(50);*/

	printf("\nPritisnite bilo sta za izlazak iz programa...\n");
	getchar();


	return 0;
}