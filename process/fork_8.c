#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>

/* 
 * 1. 좀비 생성
 * 2. 해결 -> 동시성 깨지는 현상 발생
 * 3. 해결 -> 자식의 개수가 많을 때, 좀비 발생
 * 4. 해결 -> ?
 */

/*
 * 여러 프로세스에서 종료 시, 핸들러가 자식의 개수만큼 호출되지 않을 수 있다.
 * 동시에 my_sig() -> wait()가 수행되는 동안에는 signal이 무시될 수 있다.
 */
void my_sig(int signo)
{
	printf("my_sig. no=%d, pid=%d, tid=%ld\n", signo, getpid(), syscall(224));
	// solution, 자식의 종료를 모두 수거할 때 까지 loop
	while(wait(0) > 0)
		;
}

int main()
{
	pid_t pid;
	int i, j;

	signal(SIGCHLD, my_sig);

	for (i=0; i<30; i++) {
		pid = fork();

		if (pid == 0) {
			for(j = 0; j < 3; j++) {
				printf("\t\t\tchild. pid=%d\n", getpid());
				sleep(1);
			}
			exit(7);
		}
	}

	while(1)
	{
		printf("parent. pid=%d\n", getpid());
		sleep(1);
	}
	return 0;
}
