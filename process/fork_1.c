#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
	fork();
	printf("hello world. pid=%d\n", getpid());
	return 0;
}
