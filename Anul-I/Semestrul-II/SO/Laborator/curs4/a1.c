#include <stdio.h>
#include <unistd.h>

int main(int argc, char** argv)
{
	printf("a\n");
	fork();
	printf("b\n");
	(void)argc;
	(void)argv;
	return 0;
}
