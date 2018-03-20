#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

int global=6;

int main()
{
	pid_t pid;

	pid = fork();

	if (pid == 0) {
		printf("child  : global=%d\n", ++global);
		exit(0);
	}

	wait(0);

	printf("parent : global=%d\n", global);

	return 0;
}
