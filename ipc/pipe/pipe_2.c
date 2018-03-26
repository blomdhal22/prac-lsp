#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MSG_SIZE 20

int main()
{
	int fd[2], pid;
	char msgout[MSG_SIZE] = "Hello, World\n";
	char msgin[MSG_SIZE];

	if (pipe(fd) == -1) {
		perror("pipe()");
		exit(1);
	}

	if ((pid = fork()) > 0) {
		close(fd[0]);
		write(fd[1], msgout, MSG_SIZE);
	} else if (pid == 0) {
		close(fd[1]);
		read(fd[0], msgin, MSG_SIZE);
		puts(msgin);
		exit(0);
	} else {
		perror("fork()");
		exit(2);
	}

	wait(0);

	printf("Good bye\n");

	return 0;
}
