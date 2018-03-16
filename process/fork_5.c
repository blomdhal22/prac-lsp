#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>

/*
 * 1. 좀비는 개선
 * 2. 동시성이 깨진다. 그래서 fork쓴 의미가 없음.
 child. pid=5144
 child. pid=5144
 child. pid=5144
 parent. pid=5143
 parent. pid=5143
 parent. pid=5143
 */

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
		exit(7);
	}

	wait(0);
	while(1)
	{
		printf("parent. pid=%d\n", getpid());
		sleep(1);
	}
	return 0;
}
