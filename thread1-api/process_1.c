#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	pid_t pid;

	pid = fork();

	if (pid == 0) {
		printf("\t\t\tchild\n");
		exit(0);
	}

	wait(0);

	printf("parent\n");

	return 0;
}
