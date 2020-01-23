#include "Thread1Test.h"
#include "Thread2Test.h"
#include "Thread5Test.h"
#include "Thread10Test.h"
#include "Thread20Test.h"
#include "Thread50Test.h"

int main() {
	

	StartTest1();
	//a = getchar();
	StartTest2();
	//a = getchar();
	StartTest5();
	//a = getchar();
	StartTest10();
	StartTest20();
	StartTest50();
	return 0;
}