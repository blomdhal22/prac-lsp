#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>

/* 
 * 1. 좀비 생성
 * 2. 해결 -> 동시성 깨지는 현상 발생
 * 3. 해결 -> ?
 */

void my_sig(int signo)
{
	printf("my_sig. no=%d, pid=%d, tid=%ld\n", signo, getpid(), syscall(224));
	wait(0);
}

int main()
{
	pid_t pid;
	int i;
	
	signal(SIGCHLD, my_sig);

	pid = fork();

	if (pid == 0) {
		for(i = 0; i < 3; i++) {
			printf("\t\t\tchild. pid=%d\n", getpid());
			sleep(1);
		}
		exit(7);
	}

	while(1)
	{
		printf("parent. pid=%d\n", getpid());
		sleep(1);
	}
	return 0;
}
