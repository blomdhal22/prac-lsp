#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>

/* 
 * 1. 좀비 생성
 * 2. 해결 -> 동시성 깨지는 현상 발생
 * 3. 해결 -> 자식의 개수가 많을 때, 동시에 핸들러 호출 시, 좀비 발생
 * 4. 해결 -> 시간차를 두고 종료 시, 동시성이 깨지는 현상 발생
 * 5. 해결, waitpid
 */

/*
 * 여러 프로세스에서 종료 시, 핸들러가 자식의 개수만큼 호출되지 않을 수 있다.
 * 동시에 my_sig() -> wait()가 수행되는 동안에는 signal이 무시될 수 있다.
 * => solution, 자식의 종료를 모두 수거할 때 까지 loop
 *    - 자식을 수거하는 동안, 부모의 process의 동시성은 깨지게 된다.
 * => sig handler를 non-block을 이용하면 된다. waitpid(-1, 0, WNOHANG)
 * waitpid(-1, 0, WNOHANG)
 */
void my_sig(int signo)
{
	printf("my_sig. no=%d, pid=%d, tid=%ld\n", signo, getpid(), syscall(224));
	// non-block
	while(waitpid(-1, 0, WNOHANG) > 0)
		;
}

int main()
{
	pid_t pid;
	int i, j;

	signal(SIGCHLD, my_sig);

	for (i=0; i<5; i++) {
		pid = fork();

		if (pid == 0) {
			// 시간차 종료
			for(j=0; j<i+1; j++) {
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
