#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

/*
 * 1. 문제점 blocking 된다.
 * 2. 해결, fork 이용
 * 3. 문제점, 오버헤드가 발생한다.
 */

void my_sig(int signo)
{
	printf("my_sig(%d)\n", signo);
	while(waitpid(-1, 0, WNOHANG) >0 );
}

int main()
{
	int sec;
	char line[128];
	char msg[64];

	signal(SIGCHLD, my_sig);

	while(1) {
		printf("Alarm> ");
		fgets(line, sizeof line, stdin); // 10 hello
		// 2 hello world
		sscanf(line, "%d %64[^\n]", &sec, msg);
		if (fork() == 0) {
			sleep(sec);
			printf("(%d) %s\n", sec, msg);
			exit(0);
		}
	}
	return 0;
}
