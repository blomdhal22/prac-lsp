#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void handler(int signo)
{
	printf("signal no(%d) Received\n", signo);
}

int main()
{
	if (signal(SIGUSR1, handler) == SIG_ERR) {
		fprintf(stderr, "cannot set USR1\n");
		exit(1);
	}

	if (signal(SIGUSR2, handler) == SIG_ERR) {
		fprintf(stderr, "cannot set USR2\n");
		exit(1);
	}
	
	for(;;) pause();

	return 0;
}
