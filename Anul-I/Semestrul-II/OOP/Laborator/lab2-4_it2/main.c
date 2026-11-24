#include "ui.h"
#include "tests.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <stdio.h>

int main()
{
	test_all();
	if (_CrtDumpMemoryLeaks() == 1)
	{
		printf("S-a gasit memory leak\n");
	}
	else
	{
		printf("Nu s-a gasit memory leak!\n");
	}
	Magazin m;
	initializare(&m);
	run(&m);
	destroy(&m);
	return 0;
}