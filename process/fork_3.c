#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
	pid_t pid;

    pid = fork();

	if (pid >0) {
		printf("parent pid=%d\n", getpid());
	} else if (pid == 0) {
		printf("child pid=%d\n", getpid());
	} else {
		perror("fork");
	}

	return 0;
}
