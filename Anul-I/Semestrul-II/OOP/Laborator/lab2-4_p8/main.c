#include "ui.h"
#include "tests.h"

int main()
{
	test_all();
	Magazin m;
	initializare(&m);
	run(&m);
	return 0;
}