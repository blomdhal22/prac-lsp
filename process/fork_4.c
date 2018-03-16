#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
	pid_t pid;
	int i;

    pid = fork();

	if (pid == 0) {
		for(i = 0; i < 3; i++) {
			printf("\t\t\tchild. pid=%d\n", getpid());
			sleep(1);
		}
		exit(0);
	}
	
	while(1)
	{
		printf("parent. pid=%d\n", getpid());
		sleep(1);
	}
	return 0;
}
