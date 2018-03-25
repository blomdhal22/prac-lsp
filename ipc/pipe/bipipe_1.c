#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

void client(int readfd, int writefd);
void server(int readfd, int writefd);

int main(void)
{
	int childpid, pipe1[2], pipe2[2];

	if ((pipe(pipe1)) < 0 || (pipe(pipe2) < 0)) {
		perror("pipe error");
		exit(1);
	}

	childpid = fork();

	if (childpid > 0) {
		/* parent process */
		close(pipe1[0]);
		close(pipe2[1]);
		client(pipe2[0], pipe1[1]);
		while (wait((int*)0) != childpid);
		close(pipe1[1]);
		close(pipe2[0]);
	} else {
		/* child proces */
		close(pipe1[1]);
		close(pipe2[0]);
		server(pipe1[0], pipe2[1]);
		close(pipe1[0]);
		close(pipe2[1]);
	}

	return 0;
}
