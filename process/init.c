#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>
#include <string.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>


/*
   void my_sig(int signo)
   {
		printf("my_sig. no=%d, pid=%d, tid=%ld\n", signo, getpid(), syscall(224));
		// non-block
		while(waitpid(-1, 0, WNOHANG) > 0)
	;
	}
 */

int signal_fd;
int signal_recv_fd;

void my_sig(int signo)
{
	char s = 'w';
	write(signal_fd, &s, 1);
}

int main()
{
	pid_t pid;
	int i;
	int fd[2];
	char ch;

	struct sigaction act;
	memset(&act, 0, sizeof(act));
	act.sa_handler = my_sig;
	act.sa_flags = SA_NOCLDSTOP;

	//signal(SIGCHLD, my_sig);
	sigaction(SIGCHLD, &act, 0);
	socketpair(AF_UNIX, SOCK_STREAM, 0, fd);

	signal_fd = fd[0];
	signal_recv_fd = fd[1];

	pid = fork();

	if (pid == 0) {
		// 시간차 종료
		for(i=0; i<3; i++) {
			printf("\t\t\tchild. pid=%d\n", getpid());
			sleep(1);
		}
		exit(7);
	}

	while(1)
	{
		printf("parent. pid=%d\n", getpid());
		read(signal_recv_fd, &ch, 1);
		while(waitpid(-1, 0, WNOHANG) > 0)
			;
		printf("remove child. pid=%d\n", getpid());
		sleep(1);
	}
	return 0;
}
